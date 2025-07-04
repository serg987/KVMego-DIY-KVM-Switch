/*
 * eventProcessor.c
 *
 * Created: 1/6/2025
 * Author: Refactored from eventProcessor.h
 */

#include <avr/io.h>
#include <stdbool.h>
#include <string.h>
#include "eventProcessor.h"
#include "../common/globalVars.h"
#include "../scheduler/scheduler.h"
#include "../uart/uartHelper.h"
#include "../uart/uartProtocolProcessor.h"
#include "../control/jiggler.h"
#include "../control/videoSwitchControl.h"

enum FirstStatusFrameState firstStatusFrameState = WasNotSent;

void inline checkfirstStatusFrameSent(void) {
	if (firstStatusFrameState == SecondSent) return;
	// the first frame sent will be used to switch its content (to allow Master to go to working state 1)
	else if (currentSlaveChStateFrame[0][7] == 0xFF && firstStatusFrameState == FirstSent) {
		// after the first state frame is sent to master, change it to dummy one ... 01 07 AC 20
		char *p = &currentSlaveChStateFrame[0][7];
		*p++ = 1;
		*p++ = 7;
		*p++ = 0xAC;
		*p = 0x20;
		firstStatusFrameState = SecondSent;
	} else {
		firstStatusFrameState = FirstSent;
	}
}

void inline masterEventRoutine(void) {
	if (portEvent[0] != EventNone) {
		switch (portEvent[0]) {
			case MasterVidPidStarted:
				// start new config
				if (pcState[0] != PcOff) pcState[0] = PcBeingInitialized;
				if (pcState[1] != PcOff) pcState[1] = PcBeingInitialized;
				if (pcState[2] != PcOff) pcState[2] = PcBeingInitialized;
				if (pcState[3] != PcOff) pcState[3] = PcBeingInitialized;
				break;
			case MasterDeviceDisconnect:
				if (pcState[1] != PcOff) transmit(1, deviceDisconnectedFrame, 3);
				if (pcState[2] != PcOff) transmit(2, deviceDisconnectedFrame, 3);
				if (pcState[3] != PcOff) transmit(3, deviceDisconnectedFrame, 3);
				break;
			case MasterStatusChange:
				if (pcState[1] != PcOff) transmit(1, statusChangeFrame, 4);
				if (pcState[2] != PcOff) transmit(2, statusChangeFrame, 4);
				if (pcState[3] != PcOff) transmit(3, statusChangeFrame, 4);
				break;
			case MasterGetVersionNumber:
				if (currentPcConnected > 0 && pcState[currentPcConnected] != PcOff) transmit(currentPcConnected, getVersionNumberFrame, 3);
				break;	
			case MasterTimeoutConfig:
				checkfirstStatusFrameSent();
				// not clear what to do with it - seems like send status frame after ~300 ms
				addSchedulerEvent(SendSlaveStatusToMaster, 600);
				break;
			case MasterStateRequest:
				// if jiggler is moving and it is moving on the current PC, just respond with the current state frame as it won't be sent later
				if (isJigglerMoving() && isJigglerActive[currentPcConnected]) transmit(0, currentSlaveChStateFrame[currentPcConnected], 11);
				checkfirstStatusFrameSent();
				bool anyPcOn = false;
				for (uint8_t i = 1; i < NUM_OF_UARTS; i++) {
					// send the State request only if there is no moving jiggler
					if ((pcState[i] != PcOff)  && !(isJigglerMoving() && isJigglerActive[i])) {
						sendRequestStateFrameToChannel(i);
						anyPcOn = true;
					}
				}
				if (anyPcOn) addSchedulerEvent(CheckPcConnectedAfterStatusFrame, 14);
				else transmit(0, currentSlaveChStateFrame[0], 11);
			
				if (isJigglerWaitingMasterStatusFrame) { 
					addSchedulerEvent(PrepareJigglerNextPoint, 4);
					isJigglerWaitingMasterStatusFrame = false;
				}
				break;
			case MasterVidPidReceived: ; // ; -  not a typo
				uint8_t statusFrameOffset = 5;
				if (receivedMasterDeviceConfig == 0) statusFrameOffset = 3;
				currentSlaveChStateFrame[0][statusFrameOffset] = vidPidDataFrame[receivedMasterDeviceConfig][vidPidDataSize[receivedMasterDeviceConfig] - 3];
				currentSlaveChStateFrame[0][statusFrameOffset + 1] = vidPidDataFrame[receivedMasterDeviceConfig][vidPidDataSize[receivedMasterDeviceConfig] - 2];
				addSchedulerEvent(CheckMasterVidPidTimeout, 20);
				break;
			case MasterKbMouseDataReceived:
				if (!isAnySlaveInitialized()) break;
				// data comes from a mouse (see CH9350L datasheet)
				uint8_t packetMasked = kbMouseData[4] & 0b00110000;
				bool isFromMouse = packetMasked == 0b00100000;
				if (isSelectedDeviceReady() && (isFromMouse || !isHotkeyPressed())) transmit(currentPcConnected, kbMouseData, kbMouseData[3] + 4);
				if (packetMasked == 0b00010000) {
					// data comes from a keyboard (see CH9350L datasheet)
					switch (kbMouseData[8]) {
						case 0:
							currentKeyPressed = KeyReleased;
							break;
						case 0x47:
							currentKeyPressed = ScrlLock;
							break;
						case 0x62:  // numpad
						case 0x27:  // main KB
							currentKeyPressed = Key0;
							break;
						case 0x59:  // numpad
						case 0x1E:  // main KB
							currentKeyPressed = Key1;
							break;
						case 0x5A:  // numpad
						case 0x1F:  // main KB
							currentKeyPressed = Key2;
							break;
						case 0x5B:  // numpad
						case 0x20:  // main KB
							currentKeyPressed = Key3;
							break;
						case 0x58:  // numpad
						case 0x28:  // main KB
							currentKeyPressed = Enter;
							break;
						case 0x56:  // numpad
						case 0x2D:  // main KB
							currentKeyPressed = KeyMinus;
							break;
						case 0x57:  // numpad
						case 0x2E:  // main KB
							currentKeyPressed = KeyPlus;
							break;
						case 0x0D:
							currentKeyPressed = KeyJ;
							break;
						default:
							currentKeyPressed = OtherKey;
							break;
				}
				// debouncing as sometimes same keycode is being sent twice
				if (previousKeyPressed != currentKeyPressed) previousKeyPressed = currentKeyPressed;
				else currentKeyPressed = KeyNone;
				} else if (isFromMouse) {
				// data comes from a mouse
					if (!isJigglerInitialized()) {
						// DO NOT move to scheduler - relies on data frame received
						switch(jigglerInitStep) {
							case 0:
								// copying mouse frame identifiers:
								// [2] command code 83/88
								// [3] length from 4th byte
								// [4] CH9350L labeling (see datasheet)
								// [5] first byte of mouse payload - it is a constant (in most cases?)
								memcpy(&jigglerMouseFrame[2], &kbMouseData[2], 4);
								jigglerMouseFrameLen = jigglerMouseFrame[3] + 4;
								// no break
							default:
								// seeding random generator with Timer3 low byte values. Should be pseudo-random enough as first mouse movement is not predictable
								randomState = randomState << 8;
								randomState += TCNT3L;
								break;
						}
						jigglerInitStep++;
					} else {
						// detecting a type of a mouse
						// seems need to leave as it is - sometimes for types 2 and 3 mouse cannot be identified from the first frame.
						// the drawback - if mouse is unknown indeed, this part will be executed on each frame - but should not be a big deal
						// just need to support another type of mouse
						if (mouseType == NoMouse || mouseType == UnknownMouse) {
							if (jigglerMouseFrameLen < 13) mouseType = Type1Mouse;
							else if (jigglerMouseFrameLen == 15) mouseType = Type4Mouse;
							else if ((int8_t)kbMouseData[8] < 0 && kbMouseData[9] == 0xFF) {
								if (((int8_t)kbMouseData[10] > 0 && kbMouseData[11] == 0) || ((int8_t)kbMouseData[10] < 0 && kbMouseData[11] == 0xFF)) mouseType = Type2Mouse;
							} else if (kbMouseData[7] != 0 && kbMouseData[7] == kbMouseData[10]) {
								if (kbMouseData[8] != 0 && kbMouseData[8] == kbMouseData[12]) mouseType = Type3Mouse;
							} else mouseType = UnknownMouse;
							if (mouseType != NoMouse && mouseType != UnknownMouse) addSchedulerEvent(JigglerPreparationStep1, 2);
						}
					}
			}
			if (isJigglerOn[currentPcConnected]) {
				isJigglerActive[currentPcConnected] = false;
				setActivateJigglerTime(currentPcConnected);
			}
			default:
			break;
		}
		portEvent[0] = EventNone;
	}
}

void inline slaveEventRoutine(void) {
	for (uint8_t i = 1; i < NUM_OF_UARTS; i++) {
		if (portEvent[i] == SlaveStatusReceived) {
			if (pcState[0] != PcConnected) {
				portEvent[i] = EventNone;
				continue;
			}
			isSlaveStatusFrameReceived[i] = true;
			slaveStatusFramesBeforeDisconnected[i] = SLAVE_STATUS_FRAMES_BEFORE_CONSIDER_DISCONNECT;
			if (pcState[i] == PcOff) pcState[i] = PcBeingInitialized;
			
			if (pcState[i] == PcConnected) {
				if (i == currentPcConnected && blinkKeyboardLedsState == BlinkNone) {
					transmit(0, currentSlaveChStateFrame[currentPcConnected], 11);
				}
			} else {
				if (currentSlaveChStateFrame[i][8] != 0x07) {
					transmit(i, timeoutConfigFrame, 3);
					scheduleSendSlaveStatusRequest(i, 520);
				} else {
					bool usbDeviceZeroMissed = currentSlaveChStateFrame[i][3] != currentSlaveChStateFrame[0][3] || currentSlaveChStateFrame[i][4] != currentSlaveChStateFrame[0][4];
					bool usbDeviceOneMissed = currentSlaveChStateFrame[i][5] != currentSlaveChStateFrame[0][5] || currentSlaveChStateFrame[i][6] != currentSlaveChStateFrame[0][6];
					if (usbDeviceZeroMissed || usbDeviceOneMissed) {
						bool schedulePcConnected = scheduleSendSlaveStatusRequest(i, 1400);
						if (schedulePcConnected) addSchedulerEvent(CheckPcConnectedAfterStatusFrame, 1415);
					}

					if (usbDeviceZeroMissed) {
						sendVidPidFrame(0, i);
					} else if (usbDeviceOneMissed) {
						sendVidPidFrame(1, i);
					} else {
						pcState[i] = PcConnected;
						// on the startup, the first initialized slave will be the current connected PC
						if (currentPcConnected == 0) currentPcConnected = i;
					}
				}
			}
			// update master status with leds from the current device:
			if (i == currentPcConnected) currentSlaveChStateFrame[0][7] = currentSlaveChStateFrame[i][7];
		}
		portEvent[i] = EventNone;
	}
}

void mainEventProcessorRoutine(void) {
	masterEventRoutine();
	slaveEventRoutine();
}