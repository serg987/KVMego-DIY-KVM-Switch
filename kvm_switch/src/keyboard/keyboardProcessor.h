/*
 * keyboardProcessor.h
 *
 * Created: 9/14/2024 5:30:06 PM
 *  Author: user
 */ 

#ifndef KEYBOARDPROCESSOR_H_
#define KEYBOARDPROCESSOR_H_

#include <stdint.h>
#include <stdbool.h>

// Function declarations
void mainKeyboardProcessorRoutine(void);

#define processScrollLock(key, nextState) ({\
	if (currentKeyPressed == key) {\
		kbControlState = nextState;\
		setKeyboardResetTime(TIME_TO_WAIT_SCRLLOCK_PRESSED_HALF_MS); \
	} else kbControlState = WaitingFirstScrlLock;\
})

#define toggleJiggler(channel) ({\
	if (pcState[channel] == PcConnected) {\
		isJigglerOn[channel] = !isJigglerOn[channel];\
		blinkKeyboardLedsState = BlinkJigglerConfirm;\
		} else {\
		blinkKeyboardLedsState = BlinkError;\
	}\
	setKeyboardResetTime(TIME_TO_CONFIRM_CONTROL_STATE_HALF_MS); \
	if (isJigglerOn[channel]) { \
		if (channel != currentPcConnected) isJigglerActive[channel] = true; \
	} else isJigglerActive[channel] = false; \
})

#define switchPcConnected(channel) ({\
	if (pcState[channel] == PcConnected) {\
		currentPcConnected = channel;\
		blinkKeyboardLedsState = BlinkSwitchedPc;\
		} else {\
		blinkKeyboardLedsState = BlinkError;\
	}\
	setKeyboardResetTime(TIME_TO_CONFIRM_CONTROL_STATE_HALF_MS); \
})

#endif /* KEYBOARDPROCESSOR_H_ */
