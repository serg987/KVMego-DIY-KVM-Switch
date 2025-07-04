/*
 * globalVars.h
 *
 * Created: 8/18/2024 8:42:11 PM
 *  Author: user
 */ 

#ifndef GLOBALVARS_H_
#define GLOBALVARS_H_

#include <stdint.h>
#include <stdbool.h>
#include "../common/config.h"

enum KeyboardKeys {KeyNone, ScrlLock, KeyJ, Key0, Key1, Key2, Key3, KeyPlus, KeyMinus, Enter, OtherKey, KeyReleased};
enum KeyboardControlState {WaitingFirstScrlLock, PressedFirstScrlLock, WaitingSecondScrlLock, PressedSecondScrlLock,
						   WaitingCommandKey, PressedJigglerKey, WaitingJigglerState};
extern enum KeyboardKeys currentKeyPressed;
extern enum KeyboardKeys previousKeyPressed;
extern enum KeyboardControlState kbControlState;

enum BlinkKeyboardLedsState {BlinkNone, BlinkCommandKeyOnce, BlinkCurrentPc, BlinkSwitchedPc, BlinkJigglerState, BlinkJigglerConfirm, BlinkError}; 
extern enum BlinkKeyboardLedsState blinkKeyboardLedsState;

extern char rxBufferCh0[RX_BUFFER_SIZE];
extern volatile uint8_t rxBufferCh0Index;
	
#ifdef LCD_DEBUG
extern char* emptyLcdLine;        // must be exactly 16 chars
extern char* welcomeLcdMessage;   // must be exactly 16 chars
extern char* kbPcStateMessage;    // must be exactly 16 chars
extern char* jigglerStateMessage; // must be exactly 16 chars

// ERROR handling
enum ErrorStatus {ErrorNone, UnknownCommandByteMaster, UnknownCommandByteSlave, KbMouseDataSizeExceed, VidPidDataSizeExceed, QueueOverflow};

enum ErrorStatus errorStatusCurrent;
char errorChar;
char slaveChannelError;

#endif /* LCD_DEBUG */

// CH9350 vars
// will use same numeration for uarts -  [0] will be controller's response to master device. Others will hold the real response from slave ones
extern char currentSlaveChStateFrame[NUM_OF_UARTS][11];
extern char blinkingStateFrame[11];
extern uint8_t receivedMasterDeviceConfig;
extern char vidPidDataFrame[2][VID_PID_DATA_SIZE];
extern uint16_t vidPidDataSize[2];
	
// device global vars
extern uint8_t countToSendRequestStatusFrame[NUM_OF_UARTS];
extern bool isSlaveStatusFrameReceived[NUM_OF_UARTS];
extern uint8_t slaveStatusFramesBeforeDisconnected[NUM_OF_UARTS];
extern uint8_t currentPcConnected;  // should be > 0, will be initialized if the first initialized slave appears
extern uint8_t previousPcConnected;
extern bool isJigglerOn[NUM_OF_UARTS];

enum PcStateEnum {PcOff, PcBeingInitialized, PcConnected};
extern enum PcStateEnum pcState[NUM_OF_UARTS];

// timings
extern bool tick32ms;

// workaround for enums to be treated as bytes for tests (otherwise - uint32)
enum __attribute__ ((__packed__)) SchedulerEventType {ScEventTypeNone, SendStatusRequest1, SendStatusRequest2, SendStatusRequest3, CheckPcConnectedAfterStatusFrame,
													LcdInitStep1, LcdInitStep2, LcdInitStep3, LcdInitStep4, LcdInitStep5, ResetVideoSwitchControlPort, SendSlaveStatusToMaster,
													CheckMasterVidPidTimeout, JigglerPreparationStep1, JigglerPreparationStep2, JigglerPreparationStep3, JigglerPreparationStep4,
													JigglerPreparationStep5, JigglerPreparationStep6, JigglerPreparationStep7, PrepareJigglerNextPoint, SendJigglerFrame,
													BlinkKeyboardLeds};


// global events
enum EventName {EventNone, MasterTimeoutConfig, MasterStateRequest, MasterVidPidStarted, MasterVidPidReceived, MasterKbMouseDataReceived, SlaveStatusReceived,
				MasterDeviceDisconnect, MasterStatusChange, MasterGetVersionNumber};

extern enum EventName portEvent[NUM_OF_UARTS];
	
// jiggler vars
uint8_t timeToActivateJiggler[NUM_OF_UARTS];
bool isJigglerActive[NUM_OF_UARTS];
// so far 3 types of mouses are known:
// Type 1: 12 bytes frame: 57 AB 83 08 22 01 00 FA FE 00 8E 88, x and y movements on [7] and [8] indexes, no repeats
// Type 2: 16 bytes frame: 57 AB 83 0C 23 01 00 00 12 00 F9 FF 00 00 19 7C, x and y movements are words, LSb first, indexes: [8,9], [10,11], no repeats
// Type 3: 16 bytes frame: 57 AB 83 0C 22 01 00 F4 FE 00 F4 FF FE FF 19 7C, x and y movements are bytes at [7], [8], with repeats as words, LSb first, [10,11],[12,13]
// Type 4: 15 bytes frame: 57 AB 83 0B 23 02 00 14 00 F6 FF 00 00 7E 81, x and y movements are words, LSb first, indexes: [7,8], [9,10], no repeats
enum MouseTypeEnum {NoMouse, UnknownMouse, Type1Mouse, Type2Mouse, Type3Mouse, Type4Mouse};
enum MouseTypeEnum mouseType;

// Function prototypes that were missing from enum definitions
//void sendRequestStateFrameToChannel(uint8_t channel);
//bool scheduleSendSlaveStatusRequest(uint8_t device, uint16_t delay);
//void sendVidPidFrame(uint8_t deviceIndex, uint8_t port);

#endif /* GLOBALVARS_H_ */
