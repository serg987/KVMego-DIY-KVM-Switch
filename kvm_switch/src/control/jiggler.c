/*
 * jiggler.c
 *
 * Created: 1/6/2025
 * Author: Refactored from jiggler.h
 */
#ifndef UNIT_TESTS
#include <avr/io.h>
#include <avr/interrupt.h>
#endif
#include <stdbool.h>
#include "jiggler.h"
#include "../scheduler/scheduler.h"

char jigglerMouseFrame[80] = {0x57, 0xAB, [2 ... 79] = 0};
int8_t cos_quarter_table[46] = {
	127, 127, 127, 126, 126, 125, 124, 123, 122, 121, 119, 118, 116, 114, 112, 110, 108, 105, 103, 100, 97, 94, 91, 88,
	85, 82, 78, 75, 71, 67, 64, 60, 56, 52, 48, 43, 39, 35, 31, 26, 22, 18, 13, 9, 4, 0
};

uint8_t jigglerMouseFrameLen = 0;
uint8_t jigglerInitStep = 0;
uint8_t jigglerFrameSerial = 1;
uint16_t virtualArcRadius = 0;
uint16_t virtualArcBeginningAngle = 0;
bool direction = false;
uint8_t numberOfPoints = 0;
uint8_t jigglerCurrentPoint = 0;
uint16_t step = 0;
bool isJigglerWaitingMasterStatusFrame = false;
uint32_t randomState = 0;

void sinCosCombined(uint8_t deg, int8_t* sin_val, int8_t* cos_val) {
	// Force inline for maximum speed - combines cosInt_inline approach with sincos_combined
	if (deg <= 45) {
		*cos_val = cos_quarter_table[deg];           // cos(0-45°)
		*sin_val = cos_quarter_table[45 - deg];     // sin = cos(90° - deg)
	}
	else if (deg <= 90) {
		*cos_val = -cos_quarter_table[90 - deg];     // cos(45-90°) = cos(90° - deg)
		*sin_val = cos_quarter_table[deg - 45];     // sin(45-90°) = cos(45° - (deg-45°))
	}
	else if (deg <= 135) {
		*cos_val = -cos_quarter_table[deg - 90];    // cos(90-135°) = -cos(deg - 90°)
		*sin_val = -cos_quarter_table[135 - deg];    // sin(90-135°) = cos(135° - deg)
	}
	else if (deg <= 180) {
		*cos_val = cos_quarter_table[180 - deg];    // cos(90-135°) = -cos(deg - 90°)
		*sin_val = -cos_quarter_table[deg - 135];    // sin(90-135°) = cos(135° - deg)
	}
	else if (deg <= 225) {
		*cos_val = cos_quarter_table[deg - 180];    // cos(90-135°) = -cos(deg - 90°)
		*sin_val = cos_quarter_table[225 - deg];    // sin(90-135°) = cos(135° - deg)
	}
	else {
		deg -= 15;
		*cos_val = -cos_quarter_table[255 - deg];   // cos(135-180°) = -cos(180° - deg)
		*sin_val = cos_quarter_table[deg - 210];   // sin(135-180°) = -cos(deg - 135°)
	}
}


// for unit tests inlines do not work
#ifdef UNIT_TESTS
void composeJigglerFrame(int8_t xMove, int8_t yMove) {
#else
void inline composeJigglerFrame(int8_t xMove, int8_t yMove) {
#endif
		char *p = &jigglerMouseFrame[7];
		switch (mouseType) {
			case Type1Mouse:;
			*p++ = xMove;
			*p = yMove;
			break;
			case Type2Mouse:;
			p++;
			*p++ = xMove;
			*p++ = (xMove < 0) ? 0xFF : 0;
			*p++ = yMove;
			*p = (yMove < 0) ? 0xFF : 0;
			break;
			case Type3Mouse:;
			*p++ = xMove;
			*p++ = yMove;
			p++;  // Move to index 10
			*p++ = xMove;
			*p++ = (xMove < 0) ? 0xFF : 0;
			*p++ = yMove;
			*p = (yMove < 0) ? 0xFF : 0;
			break;
			case Type4Mouse:;
			*p++ = xMove;
			*p++ = (xMove < 0) ? 0xFF : 0;
			*p++ = yMove;
			*p = (yMove < 0) ? 0xFF : 0;
			break;
			default:
			break;
		}
		jigglerMouseFrame[jigglerMouseFrameLen - 2] = jigglerFrameSerial++;
		// adding checksum
		char *ptr = &jigglerMouseFrame[6];
		char *end = &jigglerMouseFrame[jigglerMouseFrameLen - 1];
		uint8_t checksum = jigglerMouseFrame[5];
		while (ptr < end) {
			checksum += *ptr++;
		}
		jigglerMouseFrame[jigglerMouseFrameLen - 1] = checksum;
	}

void inline jigglerPreparationStep1(void) {
	randomState ^= randomState << 13;
}

void inline jigglerPreparationStep2(void) {
	randomState ^= randomState >> 17;
}

void inline jigglerPreparationStep3(void) {
	randomState ^= randomState << 5;
}

void inline jigglerPreparationStep4(void) {
	uint8_t* randomBytes = (uint8_t*)(&randomState);
	
	virtualArcRadius = minRadius + randomBytes[3];
	
	uint8_t begAngle = randomBytes[2];
	uint8_t endAngle = randomBytes[1];
	
	// Branchless direction determination
	direction = endAngle > begAngle;
	uint8_t directionMask = -(uint8_t)direction;  // 0xFF if true, 0x00 if false
	
	// Calculate both possible step sizes
	uint8_t stepForward = endAngle - begAngle;
	uint8_t stepBackward = begAngle - endAngle;
	
	// Select step based on direction using bit manipulation
	step = (stepForward & directionMask) | (stepBackward & ~directionMask);
	
	// Branchless minimum angle enforcement
	uint8_t needsAdjustment = step < minAngle;
	uint8_t adjustment = (minAngle - step) & -(uint8_t)needsAdjustment;
	
	// Apply adjustment branchlessly
	uint8_t adjustMask = -(uint8_t)needsAdjustment;
	begAngle ^= (adjustment & adjustMask & ~directionMask);
	endAngle ^= (adjustment & adjustMask & directionMask);
	
	virtualArcBeginningAngle = begAngle;
	step = (step + adjustment) & (adjustMask | ~adjustMask);
	
	numberOfPoints = randomBytes[0] + (minNumberOfPoints & -(uint8_t)(randomBytes[0] < minNumberOfPoints));
}

void inline jigglerPreparationStep5(void) {
	uint16_t nextRunTime = (((uint8_t *)(&randomState))[2] & 0xF0) + (((uint8_t *)(&randomState))[1] & 0x0F);
	nextRunTime = nextRunTime << 7;
	nextRunTime += minTimeBetweenRunsHalfMs;
	addSchedulerEvent(JigglerPreparationStep7, nextRunTime);
}

void inline jigglerPreparationStep6(void) {
	virtualArcBeginningAngle = virtualArcBeginningAngle << 8;
	step = step * 256 / numberOfPoints;
}

void inline jigglerPreparationStep7(void) {
	isJigglerWaitingMasterStatusFrame = true;
}

void inline prepareJigglerPoint(void) {
	// Early return if we've completed all points
	if (jigglerCurrentPoint >= numberOfPoints) {
		jigglerCurrentPoint = 0;
		addSchedulerEvent(JigglerPreparationStep1, 4);
		return;
	}
	
	// Calculate angle progression
	uint8_t previousAngle = ((uint8_t *)(&virtualArcBeginningAngle))[1];
	
	// Update angle based on direction
	virtualArcBeginningAngle += direction ? step : -step;
	
	uint8_t currentAngle = ((uint8_t *)(&virtualArcBeginningAngle))[1];
	jigglerCurrentPoint++;
	
	// Early return if angle hasn't changed - no movement needed
	if (currentAngle == previousAngle) {
		// Handle minimal movement case - get mouse-type-specific pointers
		char *xPtr = &jigglerMouseFrame[7];
		char *yPtr = &jigglerMouseFrame[8];
		
		if (mouseType == Type2Mouse) {
			xPtr = &jigglerMouseFrame[8];
			yPtr = &jigglerMouseFrame[9];
			} else if (mouseType == Type4Mouse) {
			yPtr = &jigglerMouseFrame[9];
		}
		
		// Apply minimal movement constraints
		int8_t currentX = (int8_t)*xPtr;
		int8_t currentY = (int8_t)*yPtr;
		
		*xPtr = (currentX > 1) ? 1 : ((currentX < -1) ? 0xFF : currentX);
		*yPtr = (currentY > 1) ? 1 : ((currentY < -1) ? 0xFF : currentY);
		
		addSchedulerEvent(SendJigglerFrame, 14);
		addSchedulerEvent(PrepareJigglerNextPoint, 18);
		return;
	}
	
	// Calculate movement differences
	int8_t currentCos, currentSin, previousCos, previousSin;
	sinCosCombined(currentAngle, &currentSin, &currentCos);
	sinCosCombined(previousAngle, &previousSin, &previousCos);
	
	int16_t xDiff = virtualArcRadius * (currentCos - previousCos);
	int16_t yDiff = virtualArcRadius * (currentSin - previousSin);
	
	// Scale down the movement
	xDiff /= 128;
	yDiff /= 128;
	
	// Compose and send the frame
	composeJigglerFrame(((int8_t *)(&xDiff))[0], ((int8_t *)(&yDiff))[0]);
	
	addSchedulerEvent(SendJigglerFrame, 14);
	addSchedulerEvent(PrepareJigglerNextPoint, 18);
}

void inline initJigglerTimer(void) {
	// setting up Timer3 as for getting values to initially seed randomState
	TCCR3A = 0;
	TCCR3B = 1; // Normal mode and prescaler = CLK/1
}