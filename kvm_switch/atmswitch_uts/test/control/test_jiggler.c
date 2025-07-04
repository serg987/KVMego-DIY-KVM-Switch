#define UNIT_TESTS

#include "unity.h"
void addSchedulerEvent(uint8_t, uint16_t) {};
uint8_t TCCR3A;
uint8_t TCCR3B;

#include <stdbool.h>
#include "../../../src/common/globalVars.h"
#include "../../../src/control/jiggler.c"

void setUp(void) {}
void tearDown(void) {}

void test_int_sincos(void)
{
  int8_t sin;
  int8_t cos;
  sinCosCombined(0, &sin, &cos);
  TEST_ASSERT_EQUAL_INT(0, sin);
  TEST_ASSERT_EQUAL_INT(127, cos);
  sinCosCombined(15, &sin, &cos);
  TEST_ASSERT_EQUAL_INT(64, sin);
  TEST_ASSERT_EQUAL_INT(110, cos);
  sinCosCombined(30, &sin, &cos);
  TEST_ASSERT_EQUAL_INT(110, sin);
  TEST_ASSERT_EQUAL_INT(64, cos);
  sinCosCombined(45, &sin, &cos);
  TEST_ASSERT_EQUAL_INT(127, sin);
  TEST_ASSERT_EQUAL_INT(0, cos);
  sinCosCombined(60, &sin, &cos);
  TEST_ASSERT_EQUAL_INT(110, sin);
  TEST_ASSERT_EQUAL_INT(-64, cos);
  sinCosCombined(75, &sin, &cos);
  TEST_ASSERT_EQUAL_INT(64, sin);
  TEST_ASSERT_EQUAL_INT(-110, cos);
  sinCosCombined(90, &sin, &cos);
  TEST_ASSERT_EQUAL_INT(0, sin);
  TEST_ASSERT_EQUAL_INT(-127, cos);
  sinCosCombined(110, &sin, &cos);
  TEST_ASSERT_EQUAL_INT(-82, sin);
  TEST_ASSERT_EQUAL_INT(-97, cos);
  sinCosCombined(130, &sin, &cos);
  TEST_ASSERT_EQUAL_INT(-125, sin);
  TEST_ASSERT_EQUAL_INT(-22, cos);
  sinCosCombined(135, &sin, &cos);
  TEST_ASSERT_EQUAL_INT(-127, sin);
  TEST_ASSERT_EQUAL_INT(0, cos);
  sinCosCombined(150, &sin, &cos);
  TEST_ASSERT_EQUAL_INT(-110, sin);
  TEST_ASSERT_EQUAL_INT(64, cos);
  sinCosCombined(170, &sin, &cos);
  TEST_ASSERT_EQUAL_INT(-43, sin);
  TEST_ASSERT_EQUAL_INT(119, cos);
  sinCosCombined(180, &sin, &cos);
  TEST_ASSERT_EQUAL_INT(0, sin);
  TEST_ASSERT_EQUAL_INT(127, cos);
  sinCosCombined(192, &sin, &cos);
  TEST_ASSERT_EQUAL_INT(52, sin);
  TEST_ASSERT_EQUAL_INT(116, cos);
  sinCosCombined(204, &sin, &cos);
  TEST_ASSERT_EQUAL_INT(94, sin);
  TEST_ASSERT_EQUAL_INT(85, cos);
  sinCosCombined(217, &sin, &cos);
  TEST_ASSERT_EQUAL_INT(122, sin);
  TEST_ASSERT_EQUAL_INT(35, cos);
  sinCosCombined(225, &sin, &cos);
  TEST_ASSERT_EQUAL_INT(127, sin);
  TEST_ASSERT_EQUAL_INT(0, cos);
  sinCosCombined(229, &sin, &cos);
  TEST_ASSERT_EQUAL_INT(126, sin);
  TEST_ASSERT_EQUAL_INT(-18, cos);
  sinCosCombined(231, &sin, &cos);
  TEST_ASSERT_EQUAL_INT(124, sin);
  TEST_ASSERT_EQUAL_INT(-26, cos);
  sinCosCombined(243, &sin, &cos);
  TEST_ASSERT_EQUAL_INT(103, sin);
  TEST_ASSERT_EQUAL_INT(-75, cos);
  sinCosCombined(255, &sin, &cos); 
  TEST_ASSERT_EQUAL_INT(64, sin);
  TEST_ASSERT_EQUAL_INT(-110, cos);
}

// Test Type1Mouse - both zeros
void test_compose_jiggler_frame_mouse_type_1_both_zeros(void) {
    uint8_t jigglerMouseFrameInit[12] = { 0x57, 0xAB, 0x83, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    memcpy(jigglerMouseFrame, jigglerMouseFrameInit, sizeof(jigglerMouseFrameInit));
    jigglerFrameSerial = 1;
    jigglerMouseFrameLen = 12;
    mouseType = Type1Mouse;
    
    composeJigglerFrame(0, 0);
    uint8_t jigglerMouseFrameExpected[12] = { 0x57, 0xAB, 0x83, 0, 0, 0, 0, 0, 0, 0, 1, 1 };
    TEST_ASSERT_EQUAL_UINT8_ARRAY(jigglerMouseFrameExpected, jigglerMouseFrame, 12);
}

// Test Type1Mouse - positive and negative
void test_compose_jiggler_frame_mouse_type_1_pos_neg(void) {
    uint8_t jigglerMouseFrameInit[12] = { 0x57, 0xAB, 0x83, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    memcpy(jigglerMouseFrame, jigglerMouseFrameInit, sizeof(jigglerMouseFrameInit));
    jigglerFrameSerial = 3;
    mouseType = Type1Mouse;
    jigglerMouseFrameLen = 12;
    
    composeJigglerFrame(-5, 10);
    uint8_t jigglerMouseFrameExpected[12] = { 0x57, 0xAB, 0x83, 0, 0, 0, 0, -5, 10, 0, 3, 8 };
    TEST_ASSERT_EQUAL_INT8_ARRAY(jigglerMouseFrameExpected, jigglerMouseFrame, 12);
}

// Test Type2Mouse - positive values
void test_compose_jiggler_frame_mouse_type_2_positive(void) {
    uint8_t jigglerMouseFrameInit[16] = { 0x57, 0xAB, 0x83, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    memcpy(jigglerMouseFrame, jigglerMouseFrameInit, sizeof(jigglerMouseFrameInit));
    jigglerFrameSerial = 5;
    mouseType = Type2Mouse;
    jigglerMouseFrameLen = 16;
    
    composeJigglerFrame(15, 25);
    uint8_t jigglerMouseFrameExpected[16] = { 0x57, 0xAB, 0x83, 0, 0, 0, 0, 0, 15, 0, 25, 0, 0, 0, 5, 45 };
    TEST_ASSERT_EQUAL_UINT8_ARRAY(jigglerMouseFrameExpected, jigglerMouseFrame, 16);
}

// Test Type2Mouse - negative values
void test_compose_jiggler_frame_mouse_type_2_negative(void) {
    uint8_t jigglerMouseFrameInit[16] = { 0x57, 0xAB, 0x83, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    memcpy(jigglerMouseFrame, jigglerMouseFrameInit, sizeof(jigglerMouseFrameInit));
    jigglerFrameSerial = 2;
    mouseType = Type2Mouse;
    jigglerMouseFrameLen = 16;
    
    composeJigglerFrame(-10, -20);
    uint8_t jigglerMouseFrameExpected[16] = { 0x57, 0xAB, 0x83, 0, 0, 0, 0, 0, -10, 0xFF, -20, 0xFF, 0, 0, 2, 0xE2 };
    TEST_ASSERT_EQUAL_INT8_ARRAY(jigglerMouseFrameExpected, jigglerMouseFrame, 16);
}

// Test Type3Mouse - positive values
void test_compose_jiggler_frame_mouse_type_3_positive(void) {
    uint8_t jigglerMouseFrameInit[16] = { 0x57, 0xAB, 0x83, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    memcpy(jigglerMouseFrame, jigglerMouseFrameInit, sizeof(jigglerMouseFrameInit));
    jigglerFrameSerial = 7;
    mouseType = Type3Mouse;
    jigglerMouseFrameLen = 16;
    
    composeJigglerFrame(12, 8);
    uint8_t jigglerMouseFrameExpected[16] = { 0x57, 0xAB, 0x83, 0, 0, 0, 0, 12, 8, 0, 12, 0, 8, 0, 7, 47 };
    TEST_ASSERT_EQUAL_UINT8_ARRAY(jigglerMouseFrameExpected, jigglerMouseFrame, 16);
}

// Test Type3Mouse - negative values
void test_compose_jiggler_frame_mouse_type_3_negative(void) {
    uint8_t jigglerMouseFrameInit[16] = { 0x57, 0xAB, 0x83, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    memcpy(jigglerMouseFrame, jigglerMouseFrameInit, sizeof(jigglerMouseFrameInit));
    jigglerFrameSerial = 4;
    mouseType = Type3Mouse;
    jigglerMouseFrameLen = 16;
    
    composeJigglerFrame(-6, -3);
    uint8_t jigglerMouseFrameExpected[16] = { 0x57, 0xAB, 0x83, 0, 0, 0, 0, -6, -3, 0, -6, 0xFF, -3, 0xFF, 4, 0xF0 };
    TEST_ASSERT_EQUAL_INT8_ARRAY(jigglerMouseFrameExpected, jigglerMouseFrame, 16);
}

// Test Type4Mouse - positive values
void test_compose_jiggler_frame_mouse_type_4_positive(void) {
    uint8_t jigglerMouseFrameInit[15] = { 0x57, 0xAB, 0x83, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    memcpy(jigglerMouseFrame, jigglerMouseFrameInit, sizeof(jigglerMouseFrameInit));
    jigglerFrameSerial = 9;
    mouseType = Type4Mouse;
    jigglerMouseFrameLen = 15;
    
    composeJigglerFrame(20, 30);
    uint8_t jigglerMouseFrameExpected[15] = { 0x57, 0xAB, 0x83, 0, 0, 0, 0, 20, 0, 30, 0, 0, 0, 9, 59 };
    TEST_ASSERT_EQUAL_UINT8_ARRAY(jigglerMouseFrameExpected, jigglerMouseFrame, 15);
}

// Test Type4Mouse - negative values
void test_compose_jiggler_frame_mouse_type_4_negative(void) {
    uint8_t jigglerMouseFrameInit[15] = { 0x57, 0xAB, 0x83, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    memcpy(jigglerMouseFrame, jigglerMouseFrameInit, sizeof(jigglerMouseFrameInit));
    jigglerFrameSerial = 6;
    mouseType = Type4Mouse;
    jigglerMouseFrameLen = 15;
    
    composeJigglerFrame(-15, -8);
    uint8_t jigglerMouseFrameExpected[15] = { 0x57, 0xAB, 0x83, 0, 0, 0, 0, -15, 0xFF, -8, 0xFF, 0, 0, 6, 0xED };
    TEST_ASSERT_EQUAL_INT8_ARRAY(jigglerMouseFrameExpected, jigglerMouseFrame, 15);
}