/*
 * globals.c
 *
 * Created: 1/6/2025
 * Author: Global variable definitions extracted from headers
 */

#include <stdint.h>
#include <stdbool.h>
#include "../common/globalVars.h"

// Keyboard control variables
enum KeyboardKeys currentKeyPressed = KeyNone;
enum KeyboardKeys previousKeyPressed = KeyNone;
enum KeyboardControlState kbControlState = WaitingFirstScrlLock;
enum BlinkKeyboardLedsState blinkKeyboardLedsState = BlinkNone;

// UART variables
char rxBufferCh0[RX_BUFFER_SIZE] = {0};
volatile uint8_t rxBufferCh0Index = 0;

#ifdef LCD_DEBUG
char* emptyLcdLine =        "                "; // must be exactly 16 chars
char* welcomeLcdMessage =   "  KVMego Switch "; // must be exactly 16 chars
char* kbPcStateMessage =    "USB __  PC _ _ _"; // must be exactly 16 chars
char* jigglerStateMessage = "MN Jiggler _ _ _"; // must be exactly 16 chars

// ERROR handling
enum ErrorStatus errorStatusCurrent = ErrorNone;
char errorChar = 0;
char slaveChannelError = 0;
#endif

// CH9350 vars
// will use same numeration for uarts -  [0] will be controller's response to master device. Others will hold the real response from slave ones
char currentSlaveChStateFrame[NUM_OF_UARTS][11] = { [0 ... NUM_OF_UARTS - 1] = {0x57, 0xAB, 0x12, 0, 0, 0, 0, 0xFF, 0x07, 0xAC, 0x0A}};
char blinkingStateFrame[11] = {0};
uint8_t receivedMasterDeviceConfig = 0;
char vidPidDataFrame[2][VID_PID_DATA_SIZE] = {0};
uint16_t vidPidDataSize[2] = {0};

// device global vars
uint8_t countToSendRequestStatusFrame[NUM_OF_UARTS] = {0};
bool isSlaveStatusFrameReceived[NUM_OF_UARTS] = {false};
uint8_t slaveStatusFramesBeforeDisconnected[NUM_OF_UARTS] = {0};
uint8_t currentPcConnected = 0;  // should be > 0, will be initialized if the first initialized slave appears
uint8_t previousPcConnected = 0;
bool isJigglerOn[NUM_OF_UARTS] = {false};
enum PcStateEnum pcState[NUM_OF_UARTS] = {PcOff};

// timings
bool tick32ms = false;

// global events
enum EventName portEvent[NUM_OF_UARTS] = {EventNone};

// jiggler vars
uint8_t timeToActivateJiggler[NUM_OF_UARTS] = {0};
bool isJigglerActive[NUM_OF_UARTS] = {false};
enum MouseTypeEnum mouseType = NoMouse;
