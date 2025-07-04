/*
 * uartProtocolProcessor.c
 *
 * Created: 1/6/2025
 * Author: Refactored from uartProtocolProcessor.h
 */

#include <avr/io.h>
#include <stdbool.h>
#include "uartProtocolProcessor.h"
#include "uartHelper.h"
#include "../common/globalVars.h"
#include "../scheduler/scheduler.h"
#include "../control/jiggler.h"

// master command may be long (vid/pid frame), so making it separate
uint16_t currentMasterFrameByte = 0;
uint8_t sendingUsbConfigForPort = 0;
char commandByte = 0;
// keyboard/mouse data frame shouldn't exceed 16 bytes in most cases, per CH9350L datasheet it may be up to (up to?) 72 bytes + service bytes = 79 bytes, took 80
char kbMouseData[80] = {0x57, 0xAB, [2 ... 79] = 0};
// predefined commands, will use them to save time
char statusChangeFrame[4] = {0x57, 0xAB, 0x80, 0xFF};
// 57 AB 81 ... - goes to vid/pid config
char requestStateFrame[4] = {0x57, 0xAB, 0x82, 0xA3};
// 57 AB 83 ... - KB/Mouse data
//char resetDelayFrame[3] = {0x57, 0xAB, 0x84};
char deviceDisconnectedFrame[3] = {0x57, 0xAB, 0x86};
char getVersionNumberFrame[3] = {0x57, 0xAB, 0x87};
// 57 AB 88 ... - KB/Mouse data
char timeoutConfigFrame[3] = {0x57, 0xAB, 0x89};


void inline mainSlaveUARTRoutine(void) {
	if (currentFrameByte[1] > 10) {
		currentFrameByte[1] = 0;
		portEvent[1] = SlaveStatusReceived;
	}
	if (currentFrameByte[2] > 10) {
		currentFrameByte[2] = 0;
		portEvent[2] = SlaveStatusReceived;
	}
	if (currentFrameByte[3] > 10) {
		currentFrameByte[3] = 0;
		portEvent[3] = SlaveStatusReceived;
	}
}

void inline processMasterReceivedByte(char charReceived) {
	// for all commands except 57 AB 81 we will be using currentFrameByte[0] as it's 8 bit.
	// if 57 AB 81 is recognized we will switch to currentMasterFrameByte - 16 bit
	switch (currentFrameByte[0]) {
		case 0:
		if (charReceived == 0x57) currentFrameByte[0] = 1;
		else currentFrameByte[0] = 0;
		break;
		case 1:
		if (charReceived == 0xAB) currentFrameByte[0] = 2;
		else currentFrameByte[0] = 0;
		break;
		case 2:
		commandByte = charReceived;
		switch (charReceived) {
			// 3b frames
			case 0x89:
			portEvent[0] = MasterTimeoutConfig;
			currentFrameByte[0] = 0;
			break;
			case 0x86:
			// this may or may not be sent on disconnection. Will just resend it to slave
			portEvent[0] = MasterDeviceDisconnect;
			currentFrameByte[0] = 0;
			break;
			case 0x87:
			// according to the CH9350L datasheet, this may have no response, ignore as of now
			portEvent[0] = MasterGetVersionNumber;
			case 0x84:
			// did not see it in real transactions, ignore as of now
			currentFrameByte[0] = 0;
			break;
			
			// 4b frames
			case 0x82:
			case 0x80:
			case 0x85:
			currentFrameByte[0] = 3;
			break;
			
			// others
			case 0x83:
			case 0x88:
			kbMouseData[2] = charReceived;
			currentFrameByte[0] = 3;
			break;
			case 0x81:
			currentFrameByte[0] = 3;
			portEvent[0] = MasterVidPidStarted;
			break;
			
			default:
			// unknown command, reset command tracker
			#ifdef LCD_DEBUG
			errorStatusCurrent = UnknownCommandByteMaster;
			errorChar = charReceived;
			#endif
			currentFrameByte[0] = 0;
		}
		break;
		case 3:
		switch (commandByte) {
			// 4b frames
			case 0x82:
			requestStateFrame[3] = charReceived;
			portEvent[0] = MasterStateRequest;
			currentFrameByte[0] = 0;
			break;
			case 0x80:
			// according to the CH9350L datasheet, this is used for states > 1; will ignore it
			// actually, 57 AB 80 FF is not used in CH9350L mode 1 - double check, but seems we can ignore it. Is being sent only on startup (for detecting mode > 1 devices???)
			// resend it to slave
			portEvent[0] = MasterStatusChange;
			case 0x85:
			// according to the CH9350L datasheet, this is used to chnage states to 2 and 3; will ignore it
			currentFrameByte[0] = 0;
			break;
			
			case 0x81:
			// 4th byte in 57 AB 81 is number of port VID/PID config assigned to, but masking to not go out of range
			sendingUsbConfigForPort = charReceived & 1;
			currentFrameByte[0] = 4;
			break;
			
			case 0x83:
			case 0x88:
			// 4th byte in 57 AB 83/88 is the length of the data frame
			kbMouseData[3] = charReceived;
			currentFrameByte[0] = 4;
			// here was a try to start to transmit kb/mouse data right away to avoid delays, BUT sometime the packet may be split, and we don't have the last bytes
			// when transmission is over. Transmit it only if the whole packet received, it will add ~1 ms delay though
			if (charReceived > 76) {
				#ifdef LCD_DEBUG
				errorStatusCurrent = KbMouseDataSizeExceed;
				errorChar = charReceived;
				#endif
				currentFrameByte[0] = 0;
			}
			break;
		}
		break;
		case 4:
		currentFrameByte[0] = 5;
		if (commandByte == 0x81) {
			vidPidDataFrame[sendingUsbConfigForPort][0] = 0x57;
			vidPidDataFrame[sendingUsbConfigForPort][1] = 0xAB;
			vidPidDataFrame[sendingUsbConfigForPort][2] = 0x81;
			vidPidDataFrame[sendingUsbConfigForPort][3] = sendingUsbConfigForPort;
			vidPidDataFrame[sendingUsbConfigForPort][4] = charReceived;
			vidPidDataSize[sendingUsbConfigForPort] = 9 + charReceived;
			} else {
			kbMouseData[4] = charReceived;
		}
		break;
		case 5:
		if (commandByte == 0x81) {
			// 1 is + 256 bytes, if we change vidpid data size (512 bytes), '2' should be changed as well
			if (charReceived < 2) {
				vidPidDataFrame[sendingUsbConfigForPort][5] = charReceived;
				vidPidDataSize[sendingUsbConfigForPort] += 256 * charReceived;
				currentMasterFrameByte = 6;
				currentFrameByte[0] = 6;
				} else {
				#ifdef LCD_DEBUG
				errorStatusCurrent = VidPidDataSizeExceed;
				errorChar = charReceived;
				#endif
				currentFrameByte[0] = 0;
			}
			} else {
			kbMouseData[5] = charReceived;
			currentFrameByte[0] = 6;
		}
		break;
		default:
		if (commandByte == 0x81) {
			vidPidDataFrame[sendingUsbConfigForPort][currentMasterFrameByte] = charReceived;
			currentMasterFrameByte++;
			if (currentMasterFrameByte == vidPidDataSize[sendingUsbConfigForPort]) {
				//  end of vid/pid data
				currentMasterFrameByte = 0;
				currentFrameByte[0] = 0;
				receivedMasterDeviceConfig = sendingUsbConfigForPort;
				portEvent[0] = MasterVidPidReceived;
			}
		}
		else {
			kbMouseData[currentFrameByte[0]] = charReceived;
			currentFrameByte[0]++;
			if (currentFrameByte[0] > kbMouseData[3] + 3) {
				// end of mouse data
				currentFrameByte[0] = 0;
				portEvent[0] = MasterKbMouseDataReceived;
			}
		}
		break;
	}
}

void inline mainMasterUARTRoutine(void) {
	uint8_t j = 0;
	while (rxBufferCh0Index > 0) {
		processMasterReceivedByte(rxBufferCh0[j++]);
		if (j == rxBufferCh0Index) rxBufferCh0Index = 0;
	}
}
