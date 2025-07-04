#define UNIT_TESTS

#include "unity.h"
#include <stdbool.h>
#include <string.h>
#include "../../src/scheduler/schedulerFunctionsCircBuf.c"


void setUp(void) {
	for (int i = 0; i < SCHEDULER_QUEUE_SIZE; i++) {
		schedulerTypeQueue[i] = 0;
		schedulerTimeQueue[i] = 0;
	}
}
void tearDown(void) {}


void test_insert_position_empty_head_0(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 0;
    schedulerQueueSize = 0;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	//TEST_ASSERT_EQUAL_INT8(0, findInsertPosition(101)); - findInserPosition won't work if size=0
	
	addSchedulerEvent(42, 1);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 101, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(1, schedulerQueueSize);
}


void test_insert_position_empty_head_4(void) {
	schedulerQueueHead = 4;
    schedulerQueueTail = 4;
    schedulerQueueSize = 0;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	//TEST_ASSERT_EQUAL_INT8(4, findInsertPosition(1010));
	
	addSchedulerEvent(42, 910);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 1010, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(1, schedulerQueueSize);
}


void test_insert_position_empty_head_15(void) {
	schedulerQueueHead = 15;
    schedulerQueueTail = 15;
    schedulerQueueSize = 0;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	//TEST_ASSERT_EQUAL_INT8(15, findInsertPosition(20));
	
	addSchedulerEvent(42, 65456);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(15, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(15, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(1, schedulerQueueSize);
}


void test_insert_position_single_head_0_more_than_counter(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 0;
    schedulerQueueSize = 1;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(1, findInsertPosition(101));
	
	addSchedulerEvent(42, 1);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 100, 101, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(1, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(2, schedulerQueueSize);
}


void test_insert_position_single_head_0_less_than_counter(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 0;
    schedulerQueueSize = 1;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(1, findInsertPosition(20));
	
	addSchedulerEvent(42, 65456);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 120, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(1, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(2, schedulerQueueSize);
}


void test_insert_position_single_head_0_more_than_counter_1(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 0;
    schedulerQueueSize = 1;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(15, findInsertPosition(110));
	
	addSchedulerEvent(42, 10);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(15, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(2, schedulerQueueSize);
}


void test_insert_position_single_head_0_same_as_head(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 0;
    schedulerQueueSize = 1;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(0, findInsertPosition(120));
	
	addSchedulerEvent(42, 20);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 120, 121, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(1, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(2, schedulerQueueSize);
}


void test_insert_position_middle_head_0(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 2;
    schedulerQueueSize = 3;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 110, 150, 160, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(1, findInsertPosition(140));
	
	addSchedulerEvent(42, 40);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 110, 140, 150, 160, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 42, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(3, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueSize);
}


void test_insert_position_middle_head_5(void) {
	schedulerQueueHead = 5;
    schedulerQueueTail = 7;
    schedulerQueueSize = 3;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 100, 150, 160, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(6, findInsertPosition(140));
	
	addSchedulerEvent(42, 40);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 100, 140, 150, 160, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 1, 42, 2, 3, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(5, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(8, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueSize);
}


void test_bug(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 1;
    schedulerQueueSize = 2;
    schedulerCounter = 4422;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 4422, 5302, 3851, 1097, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 17, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(2, findInsertPosition(35686));
	
	addSchedulerEvent(42, 31264);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 4422, 5302, 35686, 1097, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 17, 10, 42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(2, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(3, schedulerQueueSize);
}


void test_bug_1(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 1;
    schedulerQueueSize = 2;
    schedulerCounter = 481;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 823, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(15, findInsertPosition(502));
	
	addSchedulerEvent(42, 21);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 823, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 502 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(15, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(1, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(3, schedulerQueueSize);
}


void test_single_wrapped_element_insert_wrapped_before(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 0;
    schedulerQueueSize = 1;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(15, findInsertPosition(15));
	
	addSchedulerEvent(42, 65451);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(15, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(2, schedulerQueueSize);
}


void test_single_wrapped_element_insert_wrapped_after(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 0;
    schedulerQueueSize = 1;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(1, findInsertPosition(70));
	
	addSchedulerEvent(42, 65506);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 50, 70, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(1, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(2, schedulerQueueSize);
}


void test_single_wrapped_element_insert_non_wrapped(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 0;
    schedulerQueueSize = 1;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(15, findInsertPosition(150));
	
	addSchedulerEvent(42, 50);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 150 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(15, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(2, schedulerQueueSize);
}


void test_multiple_non_wrapped_insert_beginning(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 2;
    schedulerQueueSize = 3;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 110, 150, 160, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(15, findInsertPosition(105));
	
	addSchedulerEvent(42, 5);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 110, 150, 160, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 105 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(15, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(2, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueSize);
}


void test_multiple_non_wrapped_insert_end(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 2;
    schedulerQueueSize = 3;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 110, 150, 160, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(3, findInsertPosition(170));
	
	addSchedulerEvent(42, 70);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 110, 150, 160, 170, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(3, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueSize);
}


void test_multiple_wrapped_insert_end(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 2;
    schedulerQueueSize = 3;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 110, 150, 160, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(3, findInsertPosition(70));
	
	addSchedulerEvent(42, 65506);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 110, 150, 160, 70, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(3, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueSize);
}


void test_multiple_non_wrapped_exact_match(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 2;
    schedulerQueueSize = 3;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 110, 150, 160, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(1, findInsertPosition(150));
	
	addSchedulerEvent(42, 50);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 110, 150, 151, 160, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 42, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(3, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueSize);
}


void test_multiple_wrapped_insert_beginning(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 2;
    schedulerQueueSize = 3;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 20, 50, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(15, findInsertPosition(10));
	
	addSchedulerEvent(42, 65446);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 20, 50, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(15, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(2, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueSize);
}


void test_multiple_wrapped_insert_non_wrapped_beginning(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 2;
    schedulerQueueSize = 3;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 20, 50, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(15, findInsertPosition(150));
	
	addSchedulerEvent(42, 50);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 20, 50, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 150 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(15, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(2, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueSize);
}


void test_multiple_wrapped_insert_middle(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 2;
    schedulerQueueSize = 3;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 20, 50, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(1, findInsertPosition(35));
	
	addSchedulerEvent(42, 65471);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 20, 35, 50, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 42, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(3, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueSize);
}


void test_mixed_queue_insert_non_wrapped_beginning(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 4;
    schedulerQueueSize = 5;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 110, 150, 20, 50, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(15, findInsertPosition(105));
	
	addSchedulerEvent(42, 5);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 110, 150, 20, 50, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 105 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(15, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(6, schedulerQueueSize);
}


void test_mixed_queue_insert_non_wrapped_middle(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 4;
    schedulerQueueSize = 5;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 110, 150, 20, 50, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(1, findInsertPosition(130));
	
	addSchedulerEvent(42, 30);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 110, 130, 150, 20, 50, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 42, 2, 3, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(5, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(6, schedulerQueueSize);
}


void test_mixed_queue_insert_wrapped_beginning(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 4;
    schedulerQueueSize = 5;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 110, 150, 20, 50, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(2, findInsertPosition(15));
	
	addSchedulerEvent(42, 65451);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 110, 150, 15, 20, 50, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 42, 3, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(5, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(6, schedulerQueueSize);
}


void test_mixed_queue_insert_wrapped_middle(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 4;
    schedulerQueueSize = 5;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 110, 150, 20, 50, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(3, findInsertPosition(35));
	
	addSchedulerEvent(42, 65471);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 110, 150, 20, 35, 50, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 42, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(5, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(6, schedulerQueueSize);
}


void test_circular_buffer_wrap_around(void) {
	schedulerQueueHead = 14;
    schedulerQueueTail = 1;
    schedulerQueueSize = 4;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 40, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110, 150 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(15, findInsertPosition(130));
	
	addSchedulerEvent(42, 30);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 150, 40, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110, 130 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 42 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(14, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(2, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(5, schedulerQueueSize);
}


void test_circular_buffer_wrap_around_near_end(void) {
	schedulerQueueHead = 12;
    schedulerQueueTail = 15;
    schedulerQueueSize = 4;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110, 150, 40, 60 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(13, findInsertPosition(130));
	
	addSchedulerEvent(42, 30);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110, 130, 150, 40 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 42, 2, 3 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(12, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(5, schedulerQueueSize);
}


void test_counter_at_zero(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 2;
    schedulerQueueSize = 3;
    schedulerCounter = 0;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 65500, 65520, 65535, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(1, findInsertPosition(65510));
	
	addSchedulerEvent(42, 65510);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 65500, 65510, 65520, 65535, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 42, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(3, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueSize);
}


void test_counter_at_65535(void) {
	schedulerQueueHead = 15;
    schedulerQueueTail = 15;
    schedulerQueueSize = 1;
    schedulerCounter = 65535;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 65535 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(0, findInsertPosition(0));
	
	addSchedulerEvent(42, 1);
	
	// [0] = 1 b/c of rescheduling at `t % 64`
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 65535 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(15, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(2, schedulerQueueSize);
}

void test_counter_at_65535_1(void) {
	schedulerQueueHead = 5;
    schedulerQueueTail = 5;
    schedulerQueueSize = 1;
    schedulerCounter = 65535;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 65535, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(6, findInsertPosition(0));
	
	addSchedulerEvent(42, 1);
	
	// [6] = 1 b/c of rescheduling at `t % 64`
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 65535, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 1, 42, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(5, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(6, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(2, schedulerQueueSize);
}


void test_counter_at_max_uint16(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 2;
    schedulerQueueSize = 3;
    schedulerCounter = 65535;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 100, 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(2, findInsertPosition(150));
	
	addSchedulerEvent(42, 151);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 0, 100, 150, 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 42, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(3, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueSize);
}


void test_all_elements_in_row(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 2;
    schedulerQueueSize = 3;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 100, 101, 102, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(0, findInsertPosition(100));
	
	addSchedulerEvent(42, 0);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 100, 101, 102, 103, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(3, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueSize);
}


void test_circular_mixed_queue_complex(void) {
	schedulerQueueHead = 12;
    schedulerQueueTail = 3;
    schedulerQueueSize = 8;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 10, 30, 50, 90, 0, 0, 0, 0, 0, 0, 0, 0, 110, 150, 200, 250 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 5, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(14, findInsertPosition(175));
	
	addSchedulerEvent(42, 75);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 250, 10, 30, 50, 90, 0, 0, 0, 0, 0, 0, 0, 110, 150, 175, 200 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 4, 5, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0, 1, 2, 42, 3 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(12, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(9, schedulerQueueSize);
}


void test_circular_mixed_queue_complex_1(void) {
	schedulerQueueHead = 12;
    schedulerQueueTail = 3;
    schedulerQueueSize = 8;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 10, 30, 50, 90, 0, 0, 0, 0, 0, 0, 0, 0, 110, 150, 200, 250 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 5, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(15, findInsertPosition(230));
	
	addSchedulerEvent(42, 130);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 250, 10, 30, 50, 90, 0, 0, 0, 0, 0, 0, 0, 110, 150, 200, 230 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 4, 5, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 42 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(12, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(9, schedulerQueueSize);
}


void test_circular_mixed_queue_complex_1_1(void) {
	schedulerQueueHead = 12;
    schedulerQueueTail = 3;
    schedulerQueueSize = 8;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 10, 30, 50, 90, 0, 0, 0, 0, 0, 0, 0, 0, 110, 150, 200, 250 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 5, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(0, findInsertPosition(260));
	
	addSchedulerEvent(42, 160);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 260, 10, 30, 50, 90, 0, 0, 0, 0, 0, 0, 0, 110, 150, 200, 250 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 42, 5, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(12, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(9, schedulerQueueSize);
}


void test_circular_mixed_queue_complex_2(void) {
	schedulerQueueHead = 12;
    schedulerQueueTail = 3;
    schedulerQueueSize = 8;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 10, 30, 50, 90, 0, 0, 0, 0, 0, 0, 0, 0, 110, 150, 200, 250 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 5, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(15, findInsertPosition(250));
	
	addSchedulerEvent(42, 150);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 251, 10, 30, 50, 90, 0, 0, 0, 0, 0, 0, 0, 110, 150, 200, 250 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 42, 5, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(12, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(9, schedulerQueueSize);
}


void test_circular_mixed_queue_complex_2_1(void) {
	schedulerQueueHead = 15;
    schedulerQueueTail = 3;
    schedulerQueueSize = 5;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 10, 30, 50, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 250 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 5, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(15, findInsertPosition(250));
	
	addSchedulerEvent(42, 150);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 251, 10, 30, 50, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 250 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 42, 5, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(15, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(6, schedulerQueueSize);
}


void test_circular_mixed_queue_complex_3(void) {
	schedulerQueueHead = 15;
    schedulerQueueTail = 3;
    schedulerQueueSize = 5;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 10, 30, 50, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 250 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 5, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(0, findInsertPosition(255));
	
	addSchedulerEvent(42, 155);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 255, 10, 30, 50, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 250 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 42, 5, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(15, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(6, schedulerQueueSize);
}


void test_circular_mixed_queue_complex_3_1(void) {
	schedulerQueueHead = 15;
    schedulerQueueTail = 3;
    schedulerQueueSize = 5;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 10, 30, 50, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 250 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 5, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(0, findInsertPosition(5));
	
	addSchedulerEvent(42, 65441);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 5, 10, 30, 50, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 250 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 42, 5, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(15, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(6, schedulerQueueSize);
}


void test_circular_mixed_queue_complex_4(void) {
	schedulerQueueHead = 13;
    schedulerQueueTail = 0;
    schedulerQueueSize = 4;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 250, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 150, 200 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(15, findInsertPosition(175));
	
	addSchedulerEvent(42, 75);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 200, 250, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 150, 175 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 42 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(13, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(1, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(5, schedulerQueueSize);
}


void test_circular_mixed_queue_complex_4_wrap_resch(void) {
	schedulerQueueHead = 13;
    schedulerQueueTail = 0;
    schedulerQueueSize = 4;
    schedulerCounter = 1000;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 250, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 150, 200 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(14, findInsertPosition(150));
	
	addSchedulerEvent(42, 64686);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 200, 250, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 150, 151 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 42 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(13, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(1, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(5, schedulerQueueSize);
}


void test_circular_mixed_queue_complex_4_resch_1(void) {
	schedulerQueueHead = 13;
    schedulerQueueTail = 0;
    schedulerQueueSize = 4;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 250, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 150, 200 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(15, findInsertPosition(200));
	
	addSchedulerEvent(42, 100);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 201, 250, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 150, 200 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 42, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(13, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(1, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(5, schedulerQueueSize);
}


void test_circular_mixed_queue_complex_4_wrap_resch_1(void) {
	schedulerQueueHead = 13;
    schedulerQueueTail = 0;
    schedulerQueueSize = 4;
    schedulerCounter = 1000;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 250, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 150, 200 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(15, findInsertPosition(200));
	
	addSchedulerEvent(42, 64736);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 201, 250, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 150, 200 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 42, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(13, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(1, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(5, schedulerQueueSize);
}


void test_circular_insert_wrapped_in_middle(void) {
	schedulerQueueHead = 12;
    schedulerQueueTail = 3;
    schedulerQueueSize = 8;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 10, 30, 50, 90, 0, 0, 0, 0, 0, 0, 0, 0, 110, 150, 200, 250 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 5, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(2, findInsertPosition(40));
	
	addSchedulerEvent(42, 65476);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 10, 30, 40, 50, 90, 0, 0, 0, 0, 0, 0, 0, 110, 150, 200, 250 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 5, 6, 42, 7, 8, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(12, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(9, schedulerQueueSize);
}


void test_queue_size_15_mixed(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 13;
    schedulerQueueSize = 14;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 110, 120, 130, 140, 150, 160, 170, 180, 10, 20, 30, 40, 50, 60, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(2, findInsertPosition(125));
	
	addSchedulerEvent(42, 25);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 110, 120, 125, 130, 140, 150, 160, 170, 180, 10, 20, 30, 40, 50, 60, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 42, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(14, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(15, schedulerQueueSize);
}


void test_queue_size_15_mixed_same(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 13;
    schedulerQueueSize = 14;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 110, 120, 130, 140, 150, 160, 170, 180, 10, 20, 30, 40, 50, 60, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(3, findInsertPosition(140));
	
	addSchedulerEvent(42, 40);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 110, 120, 130, 140, 141, 150, 160, 170, 180, 10, 20, 30, 40, 50, 60, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 42, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(14, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(15, schedulerQueueSize);
}


void test_queue_size_15_insert_wrapped(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 13;
    schedulerQueueSize = 14;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 110, 120, 130, 140, 150, 160, 170, 180, 10, 20, 30, 40, 50, 60, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(8, findInsertPosition(10));
	
	addSchedulerEvent(42, 65446);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 110, 120, 130, 140, 150, 160, 170, 180, 10, 11, 20, 30, 40, 50, 60, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 42, 10, 11, 12, 13, 14, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(14, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(15, schedulerQueueSize);
}


void test_queue_size_15_insert_non_wrapped(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 13;
    schedulerQueueSize = 14;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 110, 120, 130, 140, 150, 160, 170, 180, 10, 20, 30, 40, 50, 60, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(15, findInsertPosition(105));
	
	addSchedulerEvent(42, 5);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 110, 120, 130, 140, 150, 160, 170, 180, 10, 20, 30, 40, 50, 60, 0, 105 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 42 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(15, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(13, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(15, schedulerQueueSize);
}


void test_queue_size_15_insert_wrapped_same(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 13;
    schedulerQueueSize = 14;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 110, 120, 130, 140, 150, 160, 170, 180, 10, 20, 30, 40, 50, 60, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(10, findInsertPosition(30));
	
	addSchedulerEvent(42, 65466);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 110, 120, 130, 140, 150, 160, 170, 180, 10, 20, 30, 31, 40, 50, 60, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 42, 12, 13, 14, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(14, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(15, schedulerQueueSize);
}


void test_queue_size_15_insert_wrapped_end(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 13;
    schedulerQueueSize = 14;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 110, 120, 130, 140, 150, 160, 170, 180, 10, 20, 30, 40, 50, 60, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(14, findInsertPosition(80));
	
	addSchedulerEvent(42, 65516);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 110, 120, 130, 140, 150, 160, 170, 180, 10, 20, 30, 40, 50, 60, 80, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 42, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(14, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(15, schedulerQueueSize);
}


void test_insert_at_non_wrapped_wrapped_boundary(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 3;
    schedulerQueueSize = 4;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 150, 200, 20, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(4, findInsertPosition(90));
	
	addSchedulerEvent(42, 65526);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 150, 200, 20, 80, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(5, schedulerQueueSize);
}


void test_insert_non_wrapped_before_wrapped_section(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 3;
    schedulerQueueSize = 4;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 150, 200, 20, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(2, findInsertPosition(250));
	
	addSchedulerEvent(42, 150);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 150, 200, 250, 20, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 42, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(5, schedulerQueueSize);
}


void test_insert_wrapped_before_wrapped_section(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 3;
    schedulerQueueSize = 4;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 150, 200, 20, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(2, findInsertPosition(15));
	
	addSchedulerEvent(42, 65451);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 150, 200, 15, 20, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 42, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(5, schedulerQueueSize);
}


void test_insert_wrapped_same_before_wrapped_section(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 3;
    schedulerQueueSize = 4;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 150, 200, 20, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(2, findInsertPosition(20));
	
	addSchedulerEvent(42, 65456);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 150, 200, 20, 21, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 42, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(5, schedulerQueueSize);
}


void test_insert_non_wrapped_same_before_wrapped_section(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 3;
    schedulerQueueSize = 4;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 150, 200, 20, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(1, findInsertPosition(200));
	
	addSchedulerEvent(42, 100);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 150, 200, 201, 20, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 42, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(5, schedulerQueueSize);
}


void test_only_wrapped_elements_insert_beginning(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 3;
    schedulerQueueSize = 4;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 20, 40, 60, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(15, findInsertPosition(15));
	
	addSchedulerEvent(42, 65451);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 20, 40, 60, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(15, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(3, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(5, schedulerQueueSize);
}


void test_only_wrapped_elements_insert_end(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 3;
    schedulerQueueSize = 4;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 20, 40, 60, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(4, findInsertPosition(90));
	
	addSchedulerEvent(42, 65526);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 20, 40, 60, 80, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(5, schedulerQueueSize);
}


void test_only_wrapped_elements_insert_non_wrapped(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 3;
    schedulerQueueSize = 4;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 20, 40, 60, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(15, findInsertPosition(150));
	
	addSchedulerEvent(42, 50);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 20, 40, 60, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 150 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(15, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(3, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(5, schedulerQueueSize);
}


void test_maximum_wraparound_distance(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 3;
    schedulerQueueSize = 4;
    schedulerCounter = 32768;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 40000, 50000, 10000, 20000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(3, findInsertPosition(15000));
	
	addSchedulerEvent(42, 47768);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 40000, 50000, 10000, 15000, 20000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 42, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(5, schedulerQueueSize);
}


void test_single_element_at_buffer_end(void) {
	schedulerQueueHead = 15;
    schedulerQueueTail = 15;
    schedulerQueueSize = 1;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 120 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(14, findInsertPosition(110));
	
	addSchedulerEvent(42, 10);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110, 120 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42, 1 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(14, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(15, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(2, schedulerQueueSize);
}


void test_single_element_at_buffer_middle(void) {
	schedulerQueueHead = 8;
    schedulerQueueTail = 8;
    schedulerQueueSize = 1;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 120, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(9, findInsertPosition(130));
	
	addSchedulerEvent(42, 30);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 120, 130, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 42, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(8, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(9, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(2, schedulerQueueSize);
}


void test_insert_time_zero(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 2;
    schedulerQueueSize = 3;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 110, 120, 130, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(3, findInsertPosition(0));
	
	addSchedulerEvent(42, 65436);
	
	// [3] = 1 b/c of rescheduling at `t % 64`
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 110, 120, 130, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(3, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueSize);
}


void test_insert_time_zero_with_rescheduling(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 3;
    schedulerQueueSize = 4;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 110, 120, 130, 65535, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(3, findInsertPosition(65535));
	
	addSchedulerEvent(42, 65435);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 110, 120, 130, 65535, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(5, schedulerQueueSize);
}


void test_insert_time_max_uint16(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 2;
    schedulerQueueSize = 3;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 110, 120, 130, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(3, findInsertPosition(65535));
	
	addSchedulerEvent(42, 65435);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 110, 120, 130, 65535, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(3, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueSize);
}


void test_collision_causes_tail_append(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 2;
    schedulerQueueSize = 3;
    schedulerCounter = 0;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 100, 101, 102, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(0, findInsertPosition(100));
	
	addSchedulerEvent(42, 100);
	
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 100, 101, 102, 103, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
	TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(3, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueSize);
}

void test_memory_corruption_wraparound_boundary(void) {
    // Set up a scenario where head > tail (wraparound) and insertion happens near boundary
    schedulerQueueHead = 14;  // Near end of buffer
    schedulerQueueTail = 2;   // Wrapped around to beginning
    schedulerQueueSize = 5;   // Queue has 5 elements
    schedulerCounter = 1000;
    
    // Initialize queue with wrapped data: elements at positions 14, 15, 0, 1, 2
    uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 
        1020, 1030, 1040, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 1010 
    };
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 
        10, 20, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2 
    };
    
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
    
    // Try to insert at position 15 (between head=14 and the wraparound)
    // This should trigger the complex memmove logic in the wraparound case
	TEST_ASSERT_EQUAL_INT8(15, findInsertPosition(1005));
    addSchedulerEvent(99, 5); // insertTime = 1005
    
    // This test may reveal memory corruption if:
    // 1. copyLength calculation goes wrong: copyLength = QUEUE_MASK - insertPosition = 15 - 15 = 0
    // 2. memmove operations with zero or negative lengths
    // 3. Incorrect boundary handling when moving data across the wraparound point
    
    // Expected behavior (if working correctly):
    uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 
        1010, 1020, 1030, 1040, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 1005 
    };
    enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 
        2, 10, 20, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 99 
    };
    
	
	
    TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
    TEST_ASSERT_EQUAL_INT8(14, schedulerQueueHead);
    TEST_ASSERT_EQUAL_INT8(3, schedulerQueueTail);  // Should advance by 1
    TEST_ASSERT_EQUAL_INT8(6, schedulerQueueSize);
}

void test_memory_corruption_edge_case_zero_copy(void) {
    // Another potential corruption scenario: insertion at the very end
    schedulerQueueHead = 10;
    schedulerQueueTail = 14;
    schedulerQueueSize = 5;
    schedulerCounter = 500;
    
    uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 500, 510, 520, 530, 540, 0 
    };
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 0 
    };
    
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
    
    // Insert at position 15 (QUEUE_MASK) - this could cause copyLength = 0
    // and potentially corrupt memory with the complex memmove operations
    addSchedulerEvent(88, 50); // insertTime = 550
    
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 500, 510, 520, 530, 540, 550 
    };
    enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 88 
    };
	
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	
    // Check if memory corruption occurred by verifying untouched areas
    // and correct queue state
    TEST_ASSERT_EQUAL_INT8(10, schedulerQueueHead);
    TEST_ASSERT_EQUAL_INT8(15, schedulerQueueTail);
    TEST_ASSERT_EQUAL_INT8(6, schedulerQueueSize);
    
    // Verify the insertion happened correctly without corrupting other data
    TEST_ASSERT_EQUAL_UINT16(550, schedulerTimeQueue[15]);
    TEST_ASSERT_EQUAL_UINT8(88, schedulerTypeQueue[15]);
}

void test_memory_corruption_memmove_overlap(void) {
    // Test case that could cause overlapping memmove operations
    schedulerQueueHead = 12;
    schedulerQueueTail = 3;
    schedulerQueueSize = 8;  // Nearly full queue spanning wraparound
    schedulerCounter = 2000;
    
    // Fill queue: positions 12, 13, 14, 15, 0, 1, 2, 3
    uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 
        2070, 2080, 2090, 2100, 0, 0, 0, 0, 0, 0, 0, 0, 2000, 2010, 2020, 2030 
    };
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 
        70, 80, 90, 100, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4 
    };
    
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
    
    // Try to insert in the middle of the wrapped section
    // This exercises the most complex memmove path with potential for overlap
    addSchedulerEvent(77, 25); // insertTime = 2025, should go at position 15
    
	uint16_t schedulerTimeQueueExp[SCHEDULER_QUEUE_SIZE] = { 
        2030,  2070, 2080, 2090, 2100, 0, 0, 0, 0, 0, 0, 0, 2000, 2010, 2020, 2025 
    };
    enum SchedulerEventType schedulerTypeQueueExp[SCHEDULER_QUEUE_SIZE] = { 
        4, 70, 80, 90, 100, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 77
    };
	
	TEST_ASSERT_EQUAL_UINT16_ARRAY(schedulerTimeQueueExp, schedulerTimeQueue, 16);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(schedulerTypeQueueExp, schedulerTypeQueue, 16);
	
    // This could reveal corruption if memmove operations overlap incorrectly
    // or if the boundary calculations are wrong
    
    TEST_ASSERT_EQUAL_INT8(12, schedulerQueueHead);
    TEST_ASSERT_EQUAL_INT8(4, schedulerQueueTail);
    TEST_ASSERT_EQUAL_INT8(9, schedulerQueueSize);
}


// Test Case 1: Empty queue
void test_is_event_in_schedule_empty(void) {
    schedulerQueueHead = 0;
    schedulerQueueTail = 0;
    schedulerQueueSize = 0;
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    
    TEST_ASSERT(!isEventInScheduler(1));
}

// Test Case 2: Single element queue - event found
void test_is_event_in_schedule_single_found(void) {
    schedulerQueueHead = 5;
    schedulerQueueTail = 5;
    schedulerQueueSize = 1;
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    
    TEST_ASSERT(isEventInScheduler(3));
}

// Test Case 3: Single element queue - event not found
void test_is_event_in_schedule_single_not_found(void) {
    schedulerQueueHead = 5;
    schedulerQueueTail = 5;
    schedulerQueueSize = 1;
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    
    TEST_ASSERT(!isEventInScheduler(7));
}

// Test Case 4: Multiple elements, head < tail, event found at beginning
void test_is_event_in_schedule_multiple_head_less_tail_found_start(void) {
    schedulerQueueHead = 2;
    schedulerQueueTail = 5;
    schedulerQueueSize = 4;
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 9, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    
    TEST_ASSERT(isEventInScheduler(9));
}

// Test Case 5: Multiple elements, head < tail, event found in middle
void test_is_event_in_schedule_multiple_head_less_tail_found_middle(void) {
    schedulerQueueHead = 2;
    schedulerQueueTail = 5;
    schedulerQueueSize = 4;
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 9, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    
    TEST_ASSERT(isEventInScheduler(4));
}

// Test Case 6: Multiple elements, head < tail, event found at end
void test_is_event_in_schedule_multiple_head_less_tail_found_end(void) {
    schedulerQueueHead = 2;
    schedulerQueueTail = 5;
    schedulerQueueSize = 4;
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 9, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    
    TEST_ASSERT(isEventInScheduler(7));
}

// Test Case 7: Multiple elements, head < tail, event not found
void test_is_event_in_schedule_multiple_head_less_tail_not_found(void) {
    schedulerQueueHead = 2;
    schedulerQueueTail = 5;
    schedulerQueueSize = 4;
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 9, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    
    TEST_ASSERT(!isEventInScheduler(12));
}

// Test Case 8: Multiple elements, head > tail (wrap around), event found before wrap
void test_is_event_in_schedule_multiple_head_greater_tail_found_before_wrap(void) {
    schedulerQueueHead = 14;
    schedulerQueueTail = 2;
    schedulerQueueSize = 5;
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 6, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 5 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    
    TEST_ASSERT(isEventInScheduler(3));
}

// Test Case 9: Multiple elements, head > tail (wrap around), event found after wrap
void test_is_event_in_schedule_multiple_head_greater_tail_found_after_wrap(void) {
    schedulerQueueHead = 14;
    schedulerQueueTail = 2;
    schedulerQueueSize = 5;
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 6, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 5 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    
    TEST_ASSERT(isEventInScheduler(6));
}

// Test Case 10: Multiple elements, head > tail (wrap around), event found at wrap point
void test_is_event_in_schedule_multiple_head_greater_tail_found_at_wrap(void) {
    schedulerQueueHead = 14;
    schedulerQueueTail = 2;
    schedulerQueueSize = 5;
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 6, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 5 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    
    TEST_ASSERT(isEventInScheduler(5));
}

// Test Case 11: Multiple elements, head > tail (wrap around), event not found
void test_is_event_in_schedule_multiple_head_greater_tail_not_found(void) {
    schedulerQueueHead = 14;
    schedulerQueueTail = 2;
    schedulerQueueSize = 5;
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 6, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 5 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    
    TEST_ASSERT(!isEventInScheduler(99));
}

// Test Case 12: Queue at boundary positions (head = 0, tail near end)
void test_is_event_in_schedule_boundary_head_zero(void) {
    schedulerQueueHead = 0;
    schedulerQueueTail = 14;
    schedulerQueueSize = 15;
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 0 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    
    TEST_ASSERT(isEventInScheduler(1));
    TEST_ASSERT(isEventInScheduler(14));
    TEST_ASSERT(!isEventInScheduler(15));
	TEST_ASSERT(isEventInScheduler(0));
}

// Test Case 13: Queue at boundary positions (head near end, tail = 0)
void test_is_event_in_schedule_boundary_tail_zero(void) {
    schedulerQueueHead = 15;
    schedulerQueueTail = 0;
    schedulerQueueSize = 2;
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    
    TEST_ASSERT(isEventInScheduler(42));
    TEST_ASSERT(!isEventInScheduler(1));
	TEST_ASSERT(isEventInScheduler(0));
}

// Test Case 14: Full queue (assuming SCHEDULER_QUEUE_SIZE = 16)
void test_is_event_in_schedule_full_queue(void) {
    schedulerQueueHead = 3;
    schedulerQueueTail = 1;  // Full queue: tail is one behind head (with wrap)
    schedulerQueueSize = 15;
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 10, 11, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 13, 14, 15, 16 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    
    TEST_ASSERT(isEventInScheduler(1));   // First element
    TEST_ASSERT(isEventInScheduler(11));  // Last element 
    TEST_ASSERT(isEventInScheduler(8));   // Middle element
    TEST_ASSERT(!isEventInScheduler(99)); // Not in queue
}

// Test Case 15: Edge case - queue with duplicate values
void test_is_event_in_schedule_duplicate_values(void) {
    schedulerQueueHead = 1;
    schedulerQueueTail = 4;
    schedulerQueueSize = 4;
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    
    TEST_ASSERT(isEventInScheduler(5));   // Should find first occurrence
    TEST_ASSERT(!isEventInScheduler(3));  // Not in queue
}

// Test Case 16: Edge case - searching for value 0 (common default)
void test_is_event_in_schedule_search_zero(void) {
    schedulerQueueHead = 2;
    schedulerQueueTail = 5;
    schedulerQueueSize = 4;
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 99, 99, 0, 1, 2, 0, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    
    TEST_ASSERT(isEventInScheduler(0));   // Should find the 0 value in queue
    TEST_ASSERT(isEventInScheduler(1));   // Verify other values work
    TEST_ASSERT(!isEventInScheduler(99)); // Should not find values outside queue range
}

void test_pull_current_scheduler_event(void) {
	schedulerQueueHead = 0;
    schedulerQueueTail = 0;
    schedulerQueueSize = 1;
    schedulerCounter = 100;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(1, pullCurrentSchedulerEvent());
	
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueSize);
}

void test_pull_current_scheduler_event_bug(void) {
	schedulerQueueHead = 4;
    schedulerQueueTail = 4;
    schedulerQueueSize = 1;
    schedulerCounter = 12;
	
	uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 2, 4, 6, 8, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
	memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
	
	TEST_ASSERT_EQUAL_INT8(7, pullCurrentSchedulerEvent());
	
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueHead);
	TEST_ASSERT_EQUAL_INT8(4, schedulerQueueTail);
	TEST_ASSERT_EQUAL_INT8(0, schedulerQueueSize);
}

// Test Case 1: Empty queue
void test_pull_current_scheduler_event_empty(void) {
    schedulerQueueHead = 0;
    schedulerQueueTail = 0;
    schedulerQueueSize = 0;
    schedulerCounter = 100;
    
    uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
    
    TEST_ASSERT_EQUAL_INT8(0, pullCurrentSchedulerEvent());
    
    TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
    TEST_ASSERT_EQUAL_INT8(0, schedulerQueueTail);
    TEST_ASSERT_EQUAL_INT8(0, schedulerQueueSize);
}

// Test Case 2: Single element queue, time matches
void test_pull_current_scheduler_event_single_time_match(void) {
    schedulerQueueHead = 5;
    schedulerQueueTail = 5;
    schedulerQueueSize = 1;
    schedulerCounter = 200;
    
    uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
    
    TEST_ASSERT_EQUAL_INT8(3, pullCurrentSchedulerEvent());
    
    TEST_ASSERT_EQUAL_INT8(5, schedulerQueueHead);
    TEST_ASSERT_EQUAL_INT8(5, schedulerQueueTail);
    TEST_ASSERT_EQUAL_INT8(0, schedulerQueueSize);
}

// Test Case 3: Single element queue, time doesn't match
void test_pull_current_scheduler_event_single_time_no_match(void) {
    schedulerQueueHead = 5;
    schedulerQueueTail = 5;
    schedulerQueueSize = 1;
    schedulerCounter = 150;
    
    uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
    
    TEST_ASSERT_EQUAL_INT8(0, pullCurrentSchedulerEvent());
    
    TEST_ASSERT_EQUAL_INT8(5, schedulerQueueHead);
    TEST_ASSERT_EQUAL_INT8(5, schedulerQueueTail);
    TEST_ASSERT_EQUAL_INT8(1, schedulerQueueSize);
}

// Test Case 4: Multiple elements, head < tail, time matches
void test_pull_current_scheduler_event_multiple_head_less_tail_match(void) {
    schedulerQueueHead = 2;
    schedulerQueueTail = 5;
    schedulerQueueSize = 4;
    schedulerCounter = 300;
    
    uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 300, 400, 500, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 7, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
    
    TEST_ASSERT_EQUAL_INT8(7, pullCurrentSchedulerEvent());
    
    TEST_ASSERT_EQUAL_INT8(3, schedulerQueueHead);
    TEST_ASSERT_EQUAL_INT8(5, schedulerQueueTail);
    TEST_ASSERT_EQUAL_INT8(3, schedulerQueueSize);
}

// Test Case 5: Multiple elements, head < tail, time doesn't match
void test_pull_current_scheduler_event_multiple_head_less_tail_no_match(void) {
    schedulerQueueHead = 2;
    schedulerQueueTail = 5;
    schedulerQueueSize = 4;
    schedulerCounter = 250;
    
    uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 300, 400, 500, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 7, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
    
    TEST_ASSERT_EQUAL_INT8(0, pullCurrentSchedulerEvent());
    
    TEST_ASSERT_EQUAL_INT8(2, schedulerQueueHead);
    TEST_ASSERT_EQUAL_INT8(5, schedulerQueueTail);
    TEST_ASSERT_EQUAL_INT8(4, schedulerQueueSize); 
}

// Test Case 6: Multiple elements, head > tail (wrap around), time matches
void test_pull_current_scheduler_event_multiple_head_greater_tail_match(void) {
    schedulerQueueHead = 14;
    schedulerQueueTail = 2;
    schedulerQueueSize = 5;
    schedulerCounter = 600;
    
    uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 800, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 600, 700 };
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 12, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 11 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
    
    TEST_ASSERT_EQUAL_INT8(10, pullCurrentSchedulerEvent());
    
    TEST_ASSERT_EQUAL_INT8(15, schedulerQueueHead);
    TEST_ASSERT_EQUAL_INT8(2, schedulerQueueTail);
    TEST_ASSERT_EQUAL_INT8(4, schedulerQueueSize);
}

// Test Case 7: Multiple elements, head > tail (wrap around), time doesn't match
void test_pull_current_scheduler_event_multiple_head_greater_tail_no_match(void) {
    schedulerQueueHead = 14;
    schedulerQueueTail = 2;
    schedulerQueueSize = 5;
    schedulerCounter = 500;
    
    uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 800, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 600, 700 };
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 12, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 11 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
    
    TEST_ASSERT_EQUAL_INT8(0, pullCurrentSchedulerEvent());
    
    TEST_ASSERT_EQUAL_INT8(14, schedulerQueueHead);
    TEST_ASSERT_EQUAL_INT8(2, schedulerQueueTail);
    TEST_ASSERT_EQUAL_INT8(5, schedulerQueueSize);
}

// Test Case 8: Head wraps around boundary (15 -> 0)
void test_pull_current_scheduler_event_head_wrap_boundary(void) {
    schedulerQueueHead = 15;
    schedulerQueueTail = 3;
    schedulerQueueSize = 5;
    schedulerCounter = 1000;
    
    uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 1100, 1200, 1300, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000 };
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 21, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
    
    TEST_ASSERT_EQUAL_INT8(20, pullCurrentSchedulerEvent());
    
    TEST_ASSERT_EQUAL_INT8(0, schedulerQueueHead);
    TEST_ASSERT_EQUAL_INT8(3, schedulerQueueTail);
    TEST_ASSERT_EQUAL_INT8(4, schedulerQueueSize);
}

// Test Case 9: Queue becomes empty after pull (head catches up to tail)
void test_pull_current_scheduler_event_becomes_empty_after_pull(void) {
    schedulerQueueHead = 7;
    schedulerQueueTail = 8;
    schedulerQueueSize = 2;
    schedulerCounter = 1500;
    
    uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 1500, 1600, 0, 0, 0, 0, 0, 0, 0 };
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 30, 31, 0, 0, 0, 0, 0, 0, 0 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
    
    TEST_ASSERT_EQUAL_INT8(30, pullCurrentSchedulerEvent());
    
    TEST_ASSERT_EQUAL_INT8(8, schedulerQueueHead);
    TEST_ASSERT_EQUAL_INT8(8, schedulerQueueTail);
    TEST_ASSERT_EQUAL_INT8(1, schedulerQueueSize);
}

// Test Case 10: Queue with only one element left after multiple pulls
void test_pull_current_scheduler_event_last_element(void) {
    schedulerQueueHead = 10;
    schedulerQueueTail = 10;
    schedulerQueueSize = 1;
    schedulerCounter = 2000;
    
    uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2000, 0, 0, 0, 0, 0 };
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 40, 0, 0, 0, 0, 0 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
    
    TEST_ASSERT_EQUAL_INT8(40, pullCurrentSchedulerEvent());
    
    TEST_ASSERT_EQUAL_INT8(10, schedulerQueueHead);
    TEST_ASSERT_EQUAL_INT8(10, schedulerQueueTail);
    TEST_ASSERT_EQUAL_INT8(0, schedulerQueueSize);
}

// Test Case 11: Counter value of 0 (edge case)
void test_pull_current_scheduler_event_counter_zero(void) {
    schedulerQueueHead = 1;
    schedulerQueueTail = 3;
    schedulerQueueSize = 3;
    schedulerCounter = 0;
    
    uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 50, 51, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
    
    TEST_ASSERT_EQUAL_INT8(50, pullCurrentSchedulerEvent());
    
    TEST_ASSERT_EQUAL_INT8(2, schedulerQueueHead);
    TEST_ASSERT_EQUAL_INT8(3, schedulerQueueTail);
    TEST_ASSERT_EQUAL_INT8(2, schedulerQueueSize);
}

// Test Case 12: Maximum counter value (edge case)
void test_pull_current_scheduler_event_counter_max(void) {
    schedulerQueueHead = 12;
    schedulerQueueTail = 14;
    schedulerQueueSize = 3;
    schedulerCounter = 65535; // Max uint16_t
    
    uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 65535, 1000, 0, 0 };
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 60, 61, 0, 0 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
    
    TEST_ASSERT_EQUAL_INT8(60, pullCurrentSchedulerEvent());
    
    TEST_ASSERT_EQUAL_INT8(13, schedulerQueueHead);
    TEST_ASSERT_EQUAL_INT8(14, schedulerQueueTail);
    TEST_ASSERT_EQUAL_INT8(2, schedulerQueueSize);
}

// Test Case 13: max long queue with wrap
void test_pull_current_scheduler_event_max_long(void) {
    schedulerQueueHead = 14;
    schedulerQueueTail = 12;
    schedulerQueueSize = 15;
    schedulerCounter = 100; // Max uint16_t
    
    uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 0, 100, 200 };
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
    
    TEST_ASSERT_EQUAL_INT8(1, pullCurrentSchedulerEvent());
    
    TEST_ASSERT_EQUAL_INT8(15, schedulerQueueHead);
    TEST_ASSERT_EQUAL_INT8(12, schedulerQueueTail);
    TEST_ASSERT_EQUAL_INT8(14, schedulerQueueSize);
}

// Test Case 14: time matches but queue is empty
void test_pull_current_scheduler_empty_time_match(void) {
    schedulerQueueHead = 5;
    schedulerQueueTail = 5;
    schedulerQueueSize = 0;
    schedulerCounter = 800; // Max uint16_t
    
    uint16_t schedulerTimeQueueInit[SCHEDULER_QUEUE_SIZE] = { 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 0, 100, 200 };
    enum SchedulerEventType schedulerTypeQueueInit[SCHEDULER_QUEUE_SIZE] = { 0, 0, 0, 0, 0, 42, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
    memcpy(schedulerTypeQueue, schedulerTypeQueueInit, sizeof(schedulerTypeQueueInit));
    memcpy(schedulerTimeQueue, schedulerTimeQueueInit, sizeof(schedulerTimeQueueInit));
    
    TEST_ASSERT_EQUAL_INT8(0, pullCurrentSchedulerEvent());
    
    TEST_ASSERT_EQUAL_INT8(5, schedulerQueueHead);
    TEST_ASSERT_EQUAL_INT8(5, schedulerQueueTail);
    TEST_ASSERT_EQUAL_INT8(0, schedulerQueueSize);
}