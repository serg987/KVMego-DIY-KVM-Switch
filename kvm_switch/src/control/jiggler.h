/*
 * jiggler.h
 *
 * Created: 9/7/2024 8:27:02 PM
 *  Author: user
 */ 

#ifndef JIGGLER_H_
#define JIGGLER_H_

#include <stdint.h>
#include <stdbool.h>

#define minRadius 100
#define minAngle 20
#define minNumberOfPoints 35
#define minTimeBetweenRunsHalfMs 20000 // ~10 secs b/w jiggler run at minimum + shifting 8bit random value by 7 bits will have 20K-52K x 500 us -> 10-26s

// Global variable declarations
char jigglerMouseFrame[80];
int8_t cos_quarter_table[46];
uint8_t jigglerMouseFrameLen;
uint8_t jigglerInitStep;
uint8_t jigglerFrameSerial;
uint16_t virtualArcRadius;
uint16_t virtualArcBeginningAngle;
bool direction;
uint8_t numberOfPoints;
uint8_t jigglerCurrentPoint;
uint16_t step;
bool isJigglerWaitingMasterStatusFrame;
uint32_t randomState;

// Function declarations
void sinCosCombined(uint8_t deg, int8_t* sin_val, int8_t* cos_val);
void composeJigglerFrame(int8_t xMove, int8_t yMove);
void jigglerPreparationStep1(void);
void jigglerPreparationStep2(void);
void jigglerPreparationStep3(void);
void jigglerPreparationStep4(void);
void jigglerPreparationStep5(void);
void jigglerPreparationStep6(void);
void jigglerPreparationStep7(void);
void prepareJigglerPoint(void);
void initJigglerTimer(void);

// Jiggler macros
#define isJigglerInitialized() (jigglerInitStep > 3)
#define isJigglerMoving() (jigglerInitStep > 0 && jigglerInitStep < 8)

#endif /* JIGGLER_H_ */