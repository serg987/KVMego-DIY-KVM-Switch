/*
 * videoSwitchControl.c
 *
 * Created: 1/6/2025
 * Author: Refactored from videoSwitchControl.h
 */

#include <avr/io.h>
#include <stdbool.h>
#include "videoSwitchControl.h"
#include "../common/globalVars.h"
#include "../scheduler/scheduler.h"

void inline portInit() {
	// pulling up unused ports, see ATMEGA2560 Datasheet
	MCUCR &= ~(1 << PUD);
	PORTC = 0xFF;
	PORTD = 0xFF;
	PORTE = 0xFF;
	PORTF = 0b11111100;
	PORTG = 0xFF;
	PORTH = 0xFF;
	PORTJ = 0xFF;
	PORTK = 0xFF;
	PORTL = 0xFF;
	
	#ifndef RF_TRANSMITTER
	// this is a common case - everything is out and at low level
	OUT_PORT_DDR |= ((1 << OUT_1) | (1 << OUT_2) | (1 << OUT_3));
	OUT_PORT = 0xFF;
	#else
	// using RF transmitter - initial state is tri-z (inputs)
	OUT_PORT_DDR &= ~((1 << OUT_1) | (1 << OUT_2) | (1 << OUT_3));
	#endif /* RF_TRANSMITTER */
	OUT_PORT &= ~((1 << OUT_1) | (1 << OUT_2) | (1 << OUT_3));
}

uint8_t inline resetPort(void) {
	uint8_t currentPort = OUT_PORT_PIN;
	#ifdef RF_TRANSMITTER
	// make it hi-z again
	OUT_PORT_DDR &= ~((1 << OUT_1) | (1 << OUT_2) | (1 << OUT_3));
	#endif /* RF_TRANSMITTER */
	currentPort &= ~((1 << OUT_1) | (1 << OUT_2) | (1 << OUT_3));
	OUT_PORT_PIN = currentPort;
	return currentPort;
}

void addSchedulerEvent(enum SchedulerEventType eventType, uint16_t halfUsFromNow); // implementation is in the scheduler

void inline setOut(void) {
	if (previousPcConnected == currentPcConnected) return;
	uint8_t currentPort = resetPort();
	switch (currentPcConnected) {
		case 1:
		#ifdef RF_TRANSMITTER
		OUT_PORT_DDR |= (1 << OUT_1);
		#else
		currentPort |= (1 << OUT_1);
		#endif /* RF_TRANSMITTER */
		break;
		case 2:
		#ifdef RF_TRANSMITTER
		OUT_PORT_DDR |= (1 << OUT_2);
		#else
		currentPort |= (1 << OUT_2);
		#endif /* RF_TRANSMITTER */
		break;
		case 3:
		#ifdef RF_TRANSMITTER
		OUT_PORT_DDR |= (1 << OUT_3);
		#else
		currentPort |= (1 << OUT_3);
		#endif /* RF_TRANSMITTER */
		break;
	}
	OUT_PORT = currentPort;
	
	#ifdef RF_TRANSMITTER
	addSchedulerEvent(ResetVideoSwitchControlPort, 4000);
	#endif /* RF_TRANSMITTER */
	
	previousPcConnected = currentPcConnected;
}
