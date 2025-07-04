/*
* i2c_switch.c
*
* Created: 8/27/2022 7:18:12 PM
* Author : user
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "avr/iotn85.h"

#define SDA1 DDB0
#define SDA2 DDB2
#define SDA1_PIN PINB0
#define SDA2_PIN PINB2
#define SCL1 DDB1
#define SCL2 DDB3
#define SCL1_PIN PINB1
#define SCL2_PIN PINB3
#define SCL1_DDR DDB1
#define SCL2_DDR DDB3
#define SDA1_INT PCINT0
#define SDA2_INT PCINT2
#define SWITCH_OUTPUT DDB4
#define port PORTB
#define portDDR DDRB
#define portPin PINB
#define portChangeMask (1 << SDA1_PIN | 1 << SDA2_PIN)
#define portChangeMaskCh1 (1 << SDA1_PIN)
#define portChnageMaskCh2 (1 << SDA2_PIN)
#define startCh1 (1 << SCL1_PIN)
#define stopCh1 (1 << SDA1_PIN | 1 << SCL1_PIN)
#define startCh2 (1 << SCL2_PIN)
#define stopCh2 (1 << SDA2_PIN | 1 << SCL2_PIN)




inline void resetPort(void) {
	port = 0; //~(1 << SWITCH_OUTPUT); // everything in high state except switch output
	portDDR = 1 << SWITCH_OUTPUT; // everything is input except switch output
}

inline void init(void) {
	// port preparation
	MCUCR &= ~(1 << PUD); // turning off all pullups
	resetPort();
}



int main(void)
{
	init();
	
	uint8_t currentMask = portChangeMask;
	uint8_t previousPortState = portPin & currentMask;
	
	while (1)
	{

		uint8_t portPinNew = portPin;
		uint8_t pinChanged = previousPortState ^ (portPinNew & currentMask);
		if (!pinChanged) continue;

		// start conditions
		if (currentMask == portChangeMask) {
			if ((portPinNew & stopCh1) == startCh1) {
				port |= (1 << SCL2); // set SCL2 to 1 before switching
				portDDR = (1 << SWITCH_OUTPUT | 1 << SCL2_DDR); // making SCL output
				port = 0;//~(1 << SWITCH_OUTPUT | 1 << SCL2); // put SCL of another connection to LOW and  // set output to 0
				currentMask = portChangeMaskCh1;
			} else if ((portPinNew & stopCh2) == startCh2) {
				port |= (1 << SCL1); // set SCL1 to 1 before switching
				portDDR = (1 << SWITCH_OUTPUT | 1 << SCL1_DDR); // making SCL output
				port = (1 << SWITCH_OUTPUT);//~(1 << SCL1); // put SCL of another connection to LOW and  // set output to 1	
				currentMask = portChnageMaskCh2;
			}
		}
		// stop conditions
		  else if (currentMask == portChangeMaskCh1 && (portPinNew & stopCh1) == stopCh1) {
			portDDR = (1 << SWITCH_OUTPUT); 
			port = 0;//~(1 << SWITCH_OUTPUT); // put SCL of another connection to High and  // set output to 0
			currentMask = portChangeMask;
		} else if (currentMask == portChnageMaskCh2 && (portPinNew & stopCh2) == stopCh2) {
			portDDR = (1 << SWITCH_OUTPUT);
			port = (1 << SWITCH_OUTPUT); // put SCL of another connection to High and  // set output to 1
			currentMask = portChangeMask;
		} 
		previousPortState = portPinNew & currentMask;
		
	}
	
}


