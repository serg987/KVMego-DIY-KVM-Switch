/*
 * uartProtocolProcessor.h
 *
 * Created: 8/20/2024 6:42:02 PM
 *  Author: user
 */ 

#ifndef UARTPROTOCOLPROCESSOR_H_
#define UARTPROTOCOLPROCESSOR_H_

#include <stdint.h>
#include <stdbool.h>

// Global variable declarations
extern uint16_t currentMasterFrameByte;
extern uint8_t sendingUsbConfigForPort;
extern char commandByte;
extern char kbMouseData[80];
extern char statusChangeFrame[4];
extern char requestStateFrame[4];
extern char deviceDisconnectedFrame[3];
extern char getVersionNumberFrame[3];
extern char timeoutConfigFrame[3];

// Function declarations
void processMasterReceivedByte(char receivedByte);
void mainMasterUARTRoutine(void);
void mainSlaveUARTRoutine(void);

// resuable code
#define sendRequestStateFrameToChannel(channel) ({\
	transmit(channel, requestStateFrame, 4);\
	isSlaveStatusFrameReceived[channel] = false;\
})

#endif /* UARTPROTOCOLPROCESSOR_H_ */
