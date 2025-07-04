/*
 * schedulerFunctionsCircBuf.h
 *
 * Created: 9/28/2024 11:22:36 AM
 *  Author: user
 */ 

#ifndef SCHEDULERFUNCTIONSCIRCBUF_H_
#define SCHEDULERFUNCTIONSCIRCBUF_H_

#include <stdint.h>
#include <stdbool.h>
#include "../common/globalVars.h"

#ifndef SCHEDULER_QUEUE_SIZE
#define SCHEDULER_QUEUE_SIZE 16
#endif /* SCHEDULER_QUEUE_SIZE */
#define QUEUE_MASK (SCHEDULER_QUEUE_SIZE - 1) 

// Global variable declarations
volatile uint8_t schedulerQueueHead;
volatile uint8_t schedulerQueueTail;
volatile uint8_t schedulerQueueSize;
volatile uint16_t schedulerCounter;
enum SchedulerEventType schedulerTypeQueue[SCHEDULER_QUEUE_SIZE];
uint16_t schedulerTimeQueue[SCHEDULER_QUEUE_SIZE];

// Function declarations
bool isEventInScheduler(enum SchedulerEventType eventType);
uint8_t findInsertPosition(uint16_t targetTime);
void addSchedulerEvent(enum SchedulerEventType eventType, uint16_t timeFromNow);
void addScheduledEventIfNotThere(enum SchedulerEventType eventType, uint16_t timeFromNow);
enum SchedulerEventType pullCurrentSchedulerEvent(void);

#endif /* SCHEDULERFUNCTIONSCIRCBUF_H_ */