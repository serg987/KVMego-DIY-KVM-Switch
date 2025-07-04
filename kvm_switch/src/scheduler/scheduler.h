/*
 * scheduler.h
 *
 * Created: 8/18/2024 8:30:56 PM
 *  Author: user
 */ 

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <stdint.h>
#include <stdbool.h>
#include "schedulerFunctionsCircBuf.h"

// Global variable declarations
extern volatile bool isSchedulerTicked;
extern uint8_t tick1sec;
extern char* transmitStr[NUM_OF_UARTS];
extern uint8_t transmitLength[NUM_OF_UARTS];
extern uint16_t transmitTime[NUM_OF_UARTS];
extern uint8_t vidPidFrameDevice[NUM_OF_UARTS];
extern bool scheduledPortTransmit[NUM_OF_UARTS];
extern uint16_t resetKeyboardTime;

// Function declarations
bool scheduleSendSlaveStatusRequest(uint8_t channel, uint16_t halfUsFromNow);
void setScheduledTransmit(uint8_t port, char* data, uint8_t len, uint16_t timeFromNow);
uint8_t setBlinkingStateToConfirmSwitch(uint8_t channel);
uint8_t setBlinkingStateToConfirmJiggler(void);
void setActivateJigglerTime(uint8_t channel);
void setKeyboardResetTime(uint16_t halfMsFromNow);
void scheduledTxRoutine(void);
void sendNoninitializedSlaveStatusFrames32ms(void);
void activateJiggler(uint8_t channel);
void updateDisplayMessages(void);
void blinkKeyboardLeds(void);
void checkPcConnectedAfterStatusFramesReceived(void);
void eventSchedulerMainRoutine(void);
void mainSchedulerRoutine(void);
void sendVidPidFrame(uint8_t deviceIndex, uint8_t channel);
void schedulerInit(void);

#endif /* SCHEDULER_H_ */