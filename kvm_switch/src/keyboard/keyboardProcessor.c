/*
 * keyboardProcessor.c
 *
 * Created: 1/6/2025
 * Author: Refactored from keyboardProcessor.h
 */

#include <avr/io.h>
#include <stdbool.h>
#include <string.h>
#include "keyboardProcessor.h"
#include "../common/globalVars.h"
#include "../scheduler/scheduler.h"
#include "../control/jiggler.h"

void inline mainKeyboardProcessorRoutine(void) {
	if (currentKeyPressed != KeyNone) {
		switch (kbControlState) {
			case WaitingFirstScrlLock:
			processScrollLock(ScrlLock, PressedFirstScrlLock);
			break;
			case PressedFirstScrlLock:
			processScrollLock(KeyReleased, WaitingSecondScrlLock);
			break;
			case WaitingSecondScrlLock:
			processScrollLock(ScrlLock, PressedSecondScrlLock);
			break;
			case PressedSecondScrlLock:
			if (currentKeyPressed == KeyReleased) {
				kbControlState = WaitingCommandKey;
				memcpy(blinkingStateFrame, currentSlaveChStateFrame[0], 11);
				blinkingStateFrame[7] = 0;
				blinkKeyboardLedsState = BlinkCommandKeyOnce;
				addScheduledEventIfNotThere(BlinkKeyboardLeds, 2);
				setKeyboardResetTime(TIME_TO_WAIT_CONTROL_STATE_HALF_MS);
			} else kbControlState = WaitingFirstScrlLock;
			break;
			case WaitingCommandKey: ;
			uint8_t newPcConnected = currentPcConnected;
			switch (currentKeyPressed) {
				case KeyJ:
				kbControlState = PressedJigglerKey;
				setKeyboardResetTime(TIME_TO_WAIT_SCRLLOCK_PRESSED_HALF_MS);
				break;
				case Key0:
				case KeyPlus:
				case Enter: ;
				// same behavior - go to the next available input
				do {
					newPcConnected++;
					if (newPcConnected == NUM_OF_UARTS) newPcConnected = 1;
				}
				while (newPcConnected != currentPcConnected && pcState[newPcConnected] != PcConnected);
				if (newPcConnected == currentPcConnected) {
					// there is only one PC connected, nothing to switch
					blinkKeyboardLedsState = BlinkError;
					} else {
					currentPcConnected = newPcConnected;
					blinkKeyboardLedsState = BlinkSwitchedPc;
				}
				setKeyboardResetTime(TIME_TO_WAIT_CONTROL_STATE_HALF_MS);
				break;
				case KeyMinus: ;
				// go to the previous available input
				do {
					newPcConnected--;
					if (newPcConnected == 0) newPcConnected = NUM_OF_UARTS - 1;
				}
				while (newPcConnected != currentPcConnected && pcState[newPcConnected] != PcConnected);
				if (newPcConnected == currentPcConnected) {
					// there is only one PC connected, nothing to switch
					blinkKeyboardLedsState = BlinkError;
					} else {
					currentPcConnected = newPcConnected;
					blinkKeyboardLedsState = BlinkSwitchedPc;
				}
				setKeyboardResetTime(TIME_TO_WAIT_CONTROL_STATE_HALF_MS);
				break;
				case Key1:
				switchPcConnected(1);
				break;
				case Key2:
				switchPcConnected(2);
				break;
				case Key3:
				switchPcConnected(3);
				break;
				default:
				kbControlState = WaitingFirstScrlLock;
				break;
			}
			break;
			case PressedJigglerKey:
			if (currentKeyPressed == KeyReleased) {
				if (isJigglerInitialized()) {
					kbControlState = WaitingJigglerState;
					blinkKeyboardLedsState = BlinkCommandKeyOnce;
					blinkingStateFrame[7] = 0;
					} else {
					blinkKeyboardLedsState = BlinkError;
				}
				setKeyboardResetTime(TIME_TO_WAIT_CONTROL_STATE_HALF_MS);
			} else kbControlState = WaitingFirstScrlLock;
			break;
			case WaitingJigglerState:
			switch (currentKeyPressed) {
				case Key0:
				case Enter:
				// toggle jiggler for current PC
				toggleJiggler(currentPcConnected);
				break;
				case Key1:
				toggleJiggler(1);
				break;
				case Key2:
				toggleJiggler(2);
				break;
				case Key3:
				toggleJiggler(3);
				break;
				default:
				kbControlState = WaitingFirstScrlLock;
				break;
			}
			break;
			default:
			break;
		}
		currentKeyPressed =  KeyNone;
	}
}
