/*
 * uartHelper.h
 *
 * Created: 8/18/2024 8:09:42 PM
 *  Author: user
 */ 

#ifndef UARTHELPER_H_
#define UARTHELPER_H_

#include <stdint.h>
#include <stdbool.h>
#include "../common/globalVars.h"

// Global variable declarations
extern volatile uint8_t currentFrameByte[NUM_OF_UARTS];
extern volatile char* txData[NUM_OF_UARTS];
extern volatile uint8_t lenTxData[NUM_OF_UARTS];
extern volatile uint8_t currentTxByte[NUM_OF_UARTS];

// Function declarations
void initUart(void);
void transmit(uint8_t port, char* data, uint8_t len);

 // the implementation is in scheduler
void setScheduledTransmit(uint8_t port, char* data, uint8_t len, uint16_t timeFromNow);  // implementation is in scheduler

// inline reusable code
#define txIntProcedure(channel, udrreg, udcsrreg, udrien) ({\
	if (currentTxByte[channel] < lenTxData[channel]) {\
		udrreg = *(txData[channel] + currentTxByte[channel]++);\
		} else {\
		udcsrreg &= ~(1 << udrien);\
		currentTxByte[channel] = 0;\
		lenTxData[channel] = 0;\
	}})

#define rxSlaveIntProcedure(channel, udrreg) ({\
		uint8_t received = udrreg; \
		uint8_t frameByte = currentFrameByte[channel]; \
		switch (frameByte) { \
			case 0: \
			if (received != 0x57) { \
				currentFrameByte[channel] = 0; \
				return; \
			} \
			break; \
			case 1: \
			if (received != 0xAB) { \
				currentFrameByte[channel] = 0; \
				return; \
			} \
			break; \
			case 2: \
			if (received != 0x12) { \
				currentFrameByte[channel] = 0; \
				return; \
			} \
			default: \
			break; \
		} \
		currentSlaveChStateFrame[channel][frameByte] = received; \
		currentFrameByte[channel] = ++frameByte; \
	})
	
#define txInitProcedure(channel, udrreg, udcsrreg) ({\
		udrreg = *(txData[channel] + currentTxByte[channel]++);\
		udcsrreg |= (1 << UDRIE0);\
	})

// 115.2k at 14.7456M
#define ubrrInit(ubrrregh, ubrrregl) ({\
		ubrrregh = 0;\
		ubrrregl = 7;\
	})

#define ucsrXaInit(ucsrreg) (ucsrreg = (1 << TXC0))
#define ucsrXbInit(ucsrreg) (ucsrreg = (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0))  // Enable TX, TX and ISRs for them
#define ucsrXcInit(ucsrreg) (ucsrreg = (1 << UCSZ01) | (1 << UCSZ00))  // 8 bit transfer, 1 stop bit, no parity

// this does not depend on NUM_OF_UARTS, but seems it is the fastest way w/o using loops
#define isNoTransmittingReceiving() ((currentFrameByte[0] == 0 && lenTxData[0] == 0) \
	&& (currentFrameByte[1] == 0 && lenTxData[1] == 0) \
	&& (currentFrameByte[2] == 0 && lenTxData[2] == 0) \
	&& (currentFrameByte[3] == 0 && lenTxData[3] == 0))


#define isNoReceiving() (currentFrameByte[0] == 0 && currentFrameByte[1] == 0  \
	&& currentFrameByte[2] == 0 && currentFrameByte[3] == 0)


#endif /* UARTHELPER_H_ */
