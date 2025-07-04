/*
 * uartHelper.c
 *
 * Created: 1/6/2025
 * Author: Refactored from uartHelper.h
 */

#include <string.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uartHelper.h"

volatile uint8_t currentFrameByte[NUM_OF_UARTS] = { 0 };
volatile char* txData[NUM_OF_UARTS] = {NULL};
volatile uint8_t lenTxData[NUM_OF_UARTS] = {0};
volatile uint8_t currentTxByte[NUM_OF_UARTS] = {0};

// will be working at 14.7456M to avoid UART timing errors
void initUart(void) {
	// 4 UARTs will be similar
	ucsrXaInit(UCSR0A);
	ucsrXaInit(UCSR1A);
	ucsrXaInit(UCSR2A);
	ucsrXaInit(UCSR3A);
	ucsrXbInit(UCSR0B);
	ucsrXbInit(UCSR1B);
	ucsrXbInit(UCSR2B);
	ucsrXbInit(UCSR3B);
	ucsrXcInit(UCSR0C);
	ucsrXcInit(UCSR1C);
	ucsrXcInit(UCSR2C);
	ucsrXcInit(UCSR3C);
	ubrrInit(UBRR0H, UBRR0L);
	ubrrInit(UBRR1H, UBRR1L);
	ubrrInit(UBRR2H, UBRR2L);
	ubrrInit(UBRR3H, UBRR3L);
}

void transmit(uint8_t port, char* data, uint8_t len) {
	if (lenTxData[port] == 0) {
		txData[port] = data;
		lenTxData[port] = len;
		currentTxByte[port] = 0;
		switch (port) {
			case 0:
			txInitProcedure(0, UDR0, UCSR0B);
			break;
			case 1:
			txInitProcedure(1, UDR1, UCSR1B);
			break;
			case 2:
			txInitProcedure(2, UDR2, UCSR2B);
			break;
			case 3:
			txInitProcedure(3, UDR3, UCSR3B);
			break;
		}
	} else setScheduledTransmit(port, data, len, (lenTxData[port] / 4) + 1);
}


ISR (USART0_UDRE_vect) {
	txIntProcedure(0, UDR0, UCSR0B, UDRIE0);
}

ISR (USART1_UDRE_vect) {
	txIntProcedure(1, UDR1, UCSR1B, UDRIE1);
}

ISR (USART2_UDRE_vect) {
	txIntProcedure(2, UDR2, UCSR2B, UDRIE2);
}

ISR (USART3_UDRE_vect) {
	txIntProcedure(3, UDR3, UCSR3B, UDRIE3);
}

ISR (USART0_RX_vect) {
	rxBufferCh0[rxBufferCh0Index++] = UDR0;
}

ISR (USART1_RX_vect) {
	rxSlaveIntProcedure(1, UDR1);
}

ISR (USART2_RX_vect) {
	rxSlaveIntProcedure(2, UDR2);
}

ISR (USART3_RX_vect) {
	rxSlaveIntProcedure(3, UDR3);
}
