/*
 * scheduler.c
 *
 * Created: 1/6/2025
 * Author: Refactored from scheduler.h
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>
#include "scheduler.h"
#include "../common/globalVars.h"
#include "../uart/uartHelper.h"
#include "../uart/uartProtocolProcessor.h"
#include "../control/jiggler.h"
#include "../control/videoSwitchControl.h"

#ifdef LCD_DEBUG
#include "../display/lcdProcessor.h"
#include "../display/messageProcessor.h"
#endif

volatile bool isSchedulerTicked = false;
uint8_t tick1sec = 0;
char* transmitStr[NUM_OF_UARTS] = {NULL};
uint8_t transmitLength[NUM_OF_UARTS] = {0};
uint16_t transmitTime[NUM_OF_UARTS] = {0};
uint8_t vidPidFrameDevice[NUM_OF_UARTS] = {0};
bool scheduledPortTransmit[NUM_OF_UARTS] = {false};
uint16_t resetKeyboardTime = 0;

bool scheduleSendSlaveStatusRequest(uint8_t channel, uint16_t halfUsFromNow) {
	bool out = false;
	switch (channel) {
		case 1:
		if (!isEventInScheduler(SendStatusRequest1)) {
			addSchedulerEvent(SendStatusRequest1, halfUsFromNow);
			out = true;
		}
		break;
		case 2:
		if (!isEventInScheduler(SendStatusRequest2)) {
			addSchedulerEvent(SendStatusRequest2, halfUsFromNow);
			out = true;
		}
		break;
		case 3:
		if (!isEventInScheduler(SendStatusRequest3)) {
			addSchedulerEvent(SendStatusRequest3, halfUsFromNow);
			out = true;
		}
		break;
	}
	return out;
}


void setScheduledTransmit(uint8_t port, char* data, uint8_t len, uint16_t timeFromNow) {
	transmitStr[port] = data;
	transmitLength[port] = len;
	transmitTime[port] = schedulerCounter + timeFromNow;
	scheduledPortTransmit[port] = true;
}

uint8_t inline setBlinkingStateToConfirmSwitch(uint8_t channel) {
	return (1 << (channel - 1));
}

uint8_t inline setBlinkingStateToConfirmJiggler(void) {
	uint8_t blinkingStateToConfirm = 0;
	if (isJigglerOn[1]) blinkingStateToConfirm++;
	if (isJigglerOn[2]) blinkingStateToConfirm += 2;
	if (isJigglerOn[3]) blinkingStateToConfirm += 4;
	return blinkingStateToConfirm;
}

void inline setActivateJigglerTime(uint8_t channel) {
	timeToActivateJiggler[channel] = tick1sec + TIME_TO_ACTIVATE_JIGGLER_S;
}

void setKeyboardResetTime(uint16_t halfMsFromNow) {
	uint16_t insertTime = schedulerCounter + halfMsFromNow;
	insertTime &= ~63;
	if (insertTime == 0) insertTime += 64;
	resetKeyboardTime = insertTime;
}


void inline scheduledTxRoutine(void) {
	for (int i = 0; i < NUM_OF_UARTS; i++) {
		if (scheduledPortTransmit[i] && transmitTime[i] == schedulerCounter) {
			transmit(i, transmitStr[i], transmitLength[i]);
			scheduledPortTransmit[i] = false;
		}
	}
}

void inline sendNoninitializedSlaveStatusFrames32ms() {
	if (pcState[0] == PcConnected) {
		for (uint8_t i = 1; i < NUM_OF_UARTS; i++) {
			if (pcState[i] == PcOff) sendRequestStateFrameToChannel(i);
		}
	}
}

void inline activateJiggler(uint8_t channel) {
	if (isJigglerOn[channel]) {
		if (timeToActivateJiggler[channel] == tick1sec) {
			isJigglerActive[channel] = true;
		}
	}
}
#ifdef LCD_DEBUG
void inline updateDisplayMessages(void) {
	if (pcState[0] == PcConnected) {
		if (tick1sec & 1) {
			for (uint8_t i = 1; i < NUM_OF_UARTS; i++) {
				if (!isJigglerInitialized()) jigglerStateMessage[9 + i * 2] = 'X';
				else if (isJigglerActive[i]) jigglerStateMessage[9 + i * 2] = 'A';
				else if (isJigglerOn[i]) jigglerStateMessage[9 + i * 2] = 'v';
				else jigglerStateMessage[9 + i * 2] = 0xDB;
			}
			switch (mouseType) {
				case UnknownMouse:
				jigglerStateMessage[1] = 'U';
				break;
				case Type1Mouse:
				jigglerStateMessage[1] = '1';
				break;
				case Type2Mouse:
				jigglerStateMessage[1] = '2';
				break;
				case Type3Mouse:
				jigglerStateMessage[1] = '3';
				break;
				case Type4Mouse:
				jigglerStateMessage[1] = '4';
				break;
				default:
				jigglerStateMessage[1] = 'N';
				break;
			}
			if (!errorInLine[1]) printToLcd(jigglerStateMessage, 1);

			} else {
			for (uint8_t i = 1; i < NUM_OF_UARTS; i++) {
				if (pcState[i] == PcBeingInitialized) kbPcStateMessage[9 + i * 2] = 'I';
				else if (currentPcConnected == i) kbPcStateMessage[9 + i * 2] = 'v';
				else if (pcState[i] == PcConnected) kbPcStateMessage[9 + i * 2] = 0xDB;
				else kbPcStateMessage[9 + i * 2] = '_';
			}
			if (!errorInLine[0]) printToLcd(kbPcStateMessage, 0);
		}
	}
}
#endif /* LCD_DEBUG */


void inline blinkKeyboardLeds(void) {
	uint16_t nextEventTime = 0;
	switch (blinkKeyboardLedsState) {
		case BlinkCommandKeyOnce:
		if (blinkingStateFrame[7] == 0) blinkingStateFrame[7] = 7;
		else {
			blinkingStateFrame[7] = 0;
			if (kbControlState == WaitingCommandKey) blinkKeyboardLedsState = BlinkCurrentPc;
			if (kbControlState == WaitingJigglerState) blinkKeyboardLedsState = BlinkJigglerState;
		}
		nextEventTime = 1200;
		break;
		case BlinkSwitchedPc:
		case BlinkCurrentPc:
		if (blinkingStateFrame[7] == 0) blinkingStateFrame[7] = setBlinkingStateToConfirmSwitch(currentPcConnected);
		else blinkingStateFrame[7] = 0;
		if (blinkKeyboardLedsState == BlinkCurrentPc) nextEventTime = 1000;
		else nextEventTime = 720;
		break;
		case BlinkJigglerConfirm:
		case BlinkJigglerState:
		if (blinkingStateFrame[7] == 0) blinkingStateFrame[7] = setBlinkingStateToConfirmJiggler();
		else blinkingStateFrame[7] = 0;
		if (blinkKeyboardLedsState == BlinkJigglerState) nextEventTime = 1000;
		else nextEventTime = 720;
		break;
		case BlinkError:
		if (blinkingStateFrame[7] == 0) blinkingStateFrame[7] = 7;
		else blinkingStateFrame[7] = 0;
		nextEventTime = 386;
		break;
		default:
		break;
	}
	if (nextEventTime > 0) {
		transmit(0, blinkingStateFrame, 11);
		addScheduledEventIfNotThere(BlinkKeyboardLeds, nextEventTime);
	}
}

void inline checkPcConnectedAfterStatusFramesReceived() {
	for (uint8_t i = 1; i < NUM_OF_UARTS; i++) {
		if (!isSlaveStatusFrameReceived[i] && isPcConnected(i)) slaveStatusFramesBeforeDisconnected[i]--;
		if (!isPcConnected(i)) pcState[i] = PcOff;
	}
	if (pcState[currentPcConnected] == PcOff)	{
		// the current PC is not responding - it is disconnected, selecting another one
		uint8_t ch = 1;
		while (ch < NUM_OF_UARTS && pcState[ch] != PcConnected) ch++;
		if (ch < NUM_OF_UARTS) {
			currentPcConnected = ch;
			blinkKeyboardLedsState = BlinkSwitchedPc;
			addScheduledEventIfNotThere(BlinkKeyboardLeds, 2);
			setKeyboardResetTime(TIME_TO_CONFIRM_CONTROL_STATE_HALF_MS);
		}
	}
}

void eventSchedulerMainRoutine(void) {
	enum SchedulerEventType eventType = pullCurrentSchedulerEvent();
	switch (eventType) {
		case SendStatusRequest1:
		sendRequestStateFrameToChannel(1);
		break;
		case SendStatusRequest2:
		sendRequestStateFrameToChannel(2);
		break;
		case SendStatusRequest3:
		sendRequestStateFrameToChannel(3);
		break;
		case CheckPcConnectedAfterStatusFrame:
		checkPcConnectedAfterStatusFramesReceived();
		break;
		case SendSlaveStatusToMaster:
		transmit(0, currentSlaveChStateFrame[0], 11);
		break;
		case CheckMasterVidPidTimeout:
		if (currentFrameByte[0] == 0 || commandByte != 0x81) {
			// no new VidPid Frame - all the USB HID devices are initialized
			pcState[0] = PcConnected;
			#ifdef LCD_DEBUG
			if (vidPidDataFrame[0][0] == 0x57) kbPcStateMessage[4] = '1'; // CH9350L does not clean up vid-pid frame if device is disconnected, no need to update it
			if (vidPidDataFrame[1][0] == 0x57) kbPcStateMessage[5] = '2';
			#endif /* LCD_DEBUG */
		}
		break;
		case JigglerPreparationStep1:
		jigglerPreparationStep1();
		addSchedulerEvent(JigglerPreparationStep2, 1);
		break;
		case JigglerPreparationStep2:
		jigglerPreparationStep2();
		addSchedulerEvent(JigglerPreparationStep3, 1);
		break;
		case JigglerPreparationStep3:
		jigglerPreparationStep3();
		addSchedulerEvent(JigglerPreparationStep4, 1);
		break;
		case JigglerPreparationStep4:
		if (isNoReceiving()) {
			jigglerPreparationStep4();
			addSchedulerEvent(JigglerPreparationStep5, 1);
			} else {
			addSchedulerEvent(JigglerPreparationStep4, 1);
		}
		break;
		case JigglerPreparationStep5:
		jigglerPreparationStep5();
		addSchedulerEvent(JigglerPreparationStep6, 1);
		break;
		case JigglerPreparationStep6:
		jigglerPreparationStep6();
		// jps7 event is scheduled in jps5
		break;
		case JigglerPreparationStep7:
		jigglerPreparationStep7();
		break;
		case PrepareJigglerNextPoint:
		if (isNoReceiving()) {
			prepareJigglerPoint();
			} else {
			addSchedulerEvent(PrepareJigglerNextPoint, 1);
		}
		break;
		case SendJigglerFrame:
		for (uint8_t i = 1; i < NUM_OF_UARTS; i++) {
			if (isJigglerActive[i]) transmit(i, jigglerMouseFrame, jigglerMouseFrameLen);
		}
		break;
		case BlinkKeyboardLeds:
		blinkKeyboardLeds();
		break;
#ifdef LCD_DEBUG
		case LcdInitStep1:
		lcd_write_command(0b00111000);
		break;
		case LcdInitStep2:
		lcd_write_command(0b00001000);
		break;
		case LcdInitStep3:
		lcd_write_command(0b00001100);
		break;
		case LcdInitStep4:
		lcd_write_command(1);
		break;
		case LcdInitStep5:
		lcd_write_command(0b110);
		updateStep = 1;
		break;
#endif // LCD_DEBUG
		
#ifdef RF_TRANSMITTER
		case ResetVideoSwitchControlPort:
		resetPort();
		break;
#endif // RF_TRANSMITTER
		
		default:
		break;
	}
}

void inline mainSchedulerRoutine(void) {
	if (isSchedulerTicked) {
		schedulerCounter++;
		scheduledTxRoutine();
		eventSchedulerMainRoutine();
		#ifdef LCD_DEBUG
		mainDisplayRoutine();
		#endif /* LCD_DEBUG */
		if ((schedulerCounter & 2047) == 0) {
			// every 1 sec
			for (uint8_t i = 1; i < NUM_OF_UARTS; i++) {
				activateJiggler(i);
			}
			
			#ifdef LCD_DEBUG
			updateDisplayMessages();
			#endif /* LCD_DEBUG */
			tick1sec++;
		}
		if ((schedulerCounter & 63) == 0) {
			sendNoninitializedSlaveStatusFrames32ms();
			// send a single mouse packet to switched PC to wake it up
			// previousPcConnected = currentPcConnected is set in setOut()
			if ((previousPcConnected != currentPcConnected)) {
				if (!isJigglerActive[currentPcConnected] && !(mouseType == NoMouse || mouseType == UnknownMouse)) {
					transmit(currentPcConnected, jigglerMouseFrame, jigglerMouseFrameLen);
				}
			}
			setOut();
			if (resetKeyboardTime > 0 && resetKeyboardTime == schedulerCounter) {
				if (lenTxData[0] == 0) transmit(0, currentSlaveChStateFrame[currentPcConnected], 11);
				kbControlState = WaitingFirstScrlLock;
				blinkKeyboardLedsState = BlinkNone;
				resetKeyboardTime = 0;
			}
		}
		isSchedulerTicked = false;
	}
}

void sendVidPidFrame(uint8_t deviceIndex, uint8_t channel) {
	// this will chunk VidPid frame to 256 bytes. Note that if VidPidFrame goes >512 bytes, need to add another chunking (or do a loop)
	if (vidPidDataSize[deviceIndex] > 255) {
		transmit(channel, vidPidDataFrame[deviceIndex], 255);
		// time to the next packet: 115200 baud x 256 bytes = 86.806us x 256 / 499.10 = 44.52 overall + some timeout -> 47
		setScheduledTransmit(channel, &(*(vidPidDataFrame[deviceIndex] + 255)), vidPidDataSize[deviceIndex] - 255, 47);
		} else {
		transmit(channel, vidPidDataFrame[deviceIndex], vidPidDataSize[deviceIndex]);
	}
}

void inline schedulerInit() {
	// setting up Timer4 as scheduler dedicated
	TCCR4A = 0;
	TCCR4B = 11; // CTC mode and prescaler = CLK/64 => 4.34 us
	OCR4A = 115; // one loop is 499.10us ~500 us
	TIFR4 = 255; //  clear all the interrupt flags
	TIMSK4 = (1 << OCIE4A);
}


ISR(TIMER4_COMPA_vect) {
	isSchedulerTicked = true;
}
