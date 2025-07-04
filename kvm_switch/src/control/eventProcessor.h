/*
 * eventProcessor.h
 *
 * Created: 8/27/2024 8:51:21 PM
 *  Author: user
 */ 

#ifndef EVENTPROCESSOR_H_
#define EVENTPROCESSOR_H_

#include <stdint.h>
#include <stdbool.h>

#define isSelectedDeviceReady() (currentPcConnected > 0 && pcState[currentPcConnected] == PcConnected)

enum FirstStatusFrameState {SecondSent, FirstSent, WasNotSent}; // going backwards to have the most common one compiled as 0

// Global variable declarations
extern enum FirstStatusFrameState firstStatusFrameState;

// Function declarations
void checkfirstStatusFrameSent(void);
void masterEventRoutine(void);
void slaveEventRoutine(void);
void mainEventProcessorRoutine(void);

#endif /* EVENTPROCESSOR_H_ */