/*
 * lcdProcessor.c
 *
 * Created: 1/6/2025
 * Author: Refactored from lcdProcessor.h
 */

#include "../common/config.h"

#ifdef LCD_DEBUG

#ifndef UNIT_TESTS
#include <avr/io.h>
#endif /* UNIT_TESTS */
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "../common/globalVars.h"
#include "../display/lcdProcessor.h"
#include "../scheduler/scheduler.h"

uint8_t updateStep = 0;
char charLine[2][16] = {0};

void lcd_write_command(uint8_t command) {
	LCD_DATA_PORT = command;
	LCD_CONTROL_PORT |= (1 << LCD_E_PIN);
	(void) OCR5A;  // dummy 16 bit operation for 400 ns delay
	(void) OCR5A;
	LCD_CONTROL_PORT &= ~(1 << LCD_E_PIN);
}

void inline lcd_write_data(uint8_t data) {
	LCD_DATA_PORT = data;
	LCD_CONTROL_PORT |= (1 << LCD_RS_PIN);
	LCD_CONTROL_PORT |= (1 << LCD_E_PIN);
	(void) OCR5A;  // dummy 16 bit operation for 400 ns delay
	(void) OCR5A;
	LCD_CONTROL_PORT &= ~(1 << LCD_E_PIN);
	LCD_CONTROL_PORT &= ~(1 << LCD_RS_PIN);
}

void printToLcd(char data[], uint8_t line) {
	// the printed line should be exactly 16 symbols
	updateStep = 1;
	memcpy(charLine[line], data, 16);
}


void inline mainDisplayRoutine() {
	if (updateStep) {
		if (updateStep == 1 || updateStep == 18) {
			uint8_t addr = 0;
			if (updateStep == 18) addr = 0x40;
			addr |= 128;
			lcd_write_command(addr);
			} else {
			uint8_t lineIndex = 0;
			int8_t charIndex = updateStep - 2;
			if (updateStep > 18) {
				lineIndex = 1;
				charIndex = updateStep - 19;
			}
			lcd_write_data(charLine[lineIndex][charIndex]);
		}
		if (updateStep == 34) updateStep = 0;
		else updateStep++;
	}
}


void inline lcd_init_routine() {
	addSchedulerEvent(LcdInitStep1, 2);
	addSchedulerEvent(LcdInitStep2, 4);
	addSchedulerEvent(LcdInitStep3, 6);
	addSchedulerEvent(LcdInitStep4, 8);
	addSchedulerEvent(LcdInitStep5, 12);
}


void inline lcd_port_init() {
	LCD_DATA_PORT = 0;
	LCD_DATA_PORT_DDR = 255;
	LCD_CONTROL_PORT &= ~((1 << LCD_RS_PIN) | (1 << LCD_E_PIN));
	LCD_CONTROL_PORT_DDR |= (1 << LCD_RS_PIN) | (1 << LCD_E_PIN);
}


void inline lcd_init() {
	lcd_port_init();
	lcd_init_routine();
}

#endif /* LCD_DEBUG */
