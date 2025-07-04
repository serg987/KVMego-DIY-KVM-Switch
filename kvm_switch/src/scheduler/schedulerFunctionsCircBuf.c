/*
 * schedulerFunctionsCircBuf.c
 *
 * Created: 1/6/2025
 * Author: Refactored from schedulerFunctionsCircBuf.h
 */

#ifndef UNIT_TESTS
#include <avr/io.h>
#include <avr/interrupt.h>
#endif /* UNIT_TESTS */
#include <stdbool.h>
#include "../scheduler/schedulerFunctionsCircBuf.h"


// Queue state
volatile uint8_t schedulerQueueHead = 0;        // Index of the first item
volatile uint8_t schedulerQueueTail = 0; 
volatile uint8_t schedulerQueueSize = 0;        // Current number of items in queue
volatile uint16_t schedulerCounter = 0;         // Current time counter

// Queue data
enum SchedulerEventType schedulerTypeQueue[SCHEDULER_QUEUE_SIZE] = { ScEventTypeNone };
uint16_t schedulerTimeQueue[SCHEDULER_QUEUE_SIZE] = { 0 };


/**
 * Check if a specific event type exists in the scheduler queue
 */
bool isEventInScheduler(enum SchedulerEventType eventType) {
    if (schedulerQueueSize == 0) return false;
	else if (schedulerQueueSize == 1) return schedulerTypeQueue[schedulerQueueHead] == eventType;
	else {
		uint8_t idx = schedulerQueueHead;
		while (idx != schedulerQueueTail && schedulerTypeQueue[idx] != eventType) idx = ((idx + 1) & QUEUE_MASK);
		return (idx != schedulerQueueTail || schedulerTypeQueue[idx] == eventType);
        }
    }

// for unit tests inlines do not work
#ifdef UNIT_TESTS
uint8_t findInsertPosition(uint16_t scheduledTime) {
#else
uint8_t inline findInsertPosition(uint16_t scheduledTime) {
#endif
	uint8_t pos;
	uint16_t currentElement;
    if (scheduledTime < schedulerCounter) {
        // time is wrapped around; going from the tail
        pos = schedulerQueueTail;
        currentElement = schedulerTimeQueue[pos];
			// the last element of queue is still before wrap, just add to the tail
        if (currentElement >= schedulerCounter || scheduledTime > currentElement) return (++pos) & QUEUE_MASK;
        else {
            uint8_t endPosition = (schedulerQueueTail - schedulerQueueSize) & QUEUE_MASK;
            while (currentElement >= scheduledTime && currentElement < schedulerCounter && pos != endPosition) {
                pos = (pos - 1) & QUEUE_MASK;
                currentElement = schedulerTimeQueue[pos];
			}
            if (pos != endPosition) pos = (pos + 1) & QUEUE_MASK;
		}
	}
    else {
        // going from the head
        pos = schedulerQueueHead;
        currentElement = schedulerTimeQueue[pos];
		// the first element of queue is after wrap, just add before head
        if (currentElement < schedulerCounter) return (--pos) & QUEUE_MASK;
        else {
			   // need to insert before the first element
            if (currentElement > scheduledTime) return (--pos) & QUEUE_MASK;
            uint8_t endPosition = (schedulerQueueHead + schedulerQueueSize) & QUEUE_MASK;
            while (currentElement < scheduledTime && currentElement >= schedulerCounter && pos != endPosition) {
                pos = (pos + 1) & QUEUE_MASK;
                currentElement = schedulerTimeQueue[pos];
			}
		}
	}
	return pos;
}

void addSchedulerEvent(enum SchedulerEventType eventType, uint16_t halfUsFromNow) {
    uint16_t insertTime = schedulerCounter + halfUsFromNow;
	// avoid 32ms patterns
	if (insertTime % 64 == 0) insertTime++;
    if (schedulerQueueSize == 0) {
        schedulerTimeQueue[schedulerQueueHead] = insertTime;
        schedulerTypeQueue[schedulerQueueHead] = eventType;
        schedulerQueueSize = 1;
        return;
	}
    // QUEUE_MASK indeed - we need one empty spot to distinguish b/w head vs tail
	else if (schedulerQueueSize == QUEUE_MASK) {
		#ifdef LCD_DEBUG
		errorStatusCurrent = QueueOverflow;
		#endif // LCD_DEBUG
		return;
	} 
	
    uint8_t insertPosition = findInsertPosition(insertTime);

    uint8_t outOfRangeHead = (schedulerQueueHead - 1) & QUEUE_MASK;
    uint8_t outOfRangeTail = (schedulerQueueTail + 1) & QUEUE_MASK;
    if (insertPosition == outOfRangeTail) {
        schedulerTimeQueue[insertPosition] = insertTime;
        schedulerTypeQueue[insertPosition] = eventType;
        schedulerQueueTail = outOfRangeTail;
	}
    else if (insertPosition == outOfRangeHead) {
        schedulerTimeQueue[insertPosition] = insertTime;
        schedulerTypeQueue[insertPosition] = eventType;
        schedulerQueueHead = outOfRangeHead;
	} else {
		// insert without changing HEAD
		if (schedulerTimeQueue[insertPosition] == insertTime) {
			// need to reschedule the event
			while (schedulerTimeQueue[insertPosition] == insertTime && insertPosition != outOfRangeTail) {
				insertPosition = ((insertPosition + 1) & QUEUE_MASK);
				insertTime++;
			}
			if (insertPosition == outOfRangeTail) {
				schedulerTimeQueue[insertPosition] = insertTime;
				schedulerTypeQueue[insertPosition] = eventType;
				schedulerQueueTail = outOfRangeTail;
				schedulerQueueSize++;
				return;
			}
		}
		uint8_t trgtIndx = outOfRangeTail;
		while (trgtIndx != insertPosition) {
			uint8_t srcIndx = (trgtIndx - 1) & QUEUE_MASK;
			schedulerTimeQueue[trgtIndx] = schedulerTimeQueue[srcIndx];
			schedulerTypeQueue[trgtIndx] = schedulerTypeQueue[srcIndx];
			trgtIndx = srcIndx;
		}
        
        schedulerTimeQueue[insertPosition] = insertTime;
        schedulerTypeQueue[insertPosition] = eventType;
        schedulerQueueTail = (schedulerQueueTail + 1) & QUEUE_MASK;
	}
    schedulerQueueSize++;
}

void addScheduledEventIfNotThere(enum SchedulerEventType eventType, uint16_t halfUsFromNow) {
	if (!isEventInScheduler(eventType)) addSchedulerEvent(eventType, halfUsFromNow);
	}

// for unit tests inlines do not work
#ifdef UNIT_TESTS
enum SchedulerEventType pullCurrentSchedulerEvent(void) {
#else
enum SchedulerEventType inline pullCurrentSchedulerEvent(void) {
#endif
	if (schedulerTimeQueue[schedulerQueueHead] == schedulerCounter && schedulerQueueSize > 0) {
		enum SchedulerEventType out = schedulerTypeQueue[schedulerQueueHead];
		schedulerTypeQueue[schedulerQueueHead] = ScEventTypeNone;
		if (schedulerQueueHead != schedulerQueueTail) schedulerQueueHead = (schedulerQueueHead + 1) & QUEUE_MASK;
        schedulerQueueSize--;
		return out;
	}
	else return ScEventTypeNone;
}
