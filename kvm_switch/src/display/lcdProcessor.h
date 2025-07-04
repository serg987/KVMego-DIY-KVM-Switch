/*
 * lcdProcessor.h
 *
 * Created: 9/14/2024 5:40:07 PM
 *  Author: user
 */ 

#ifndef LCDPROCESSOR_H_
#define LCDPROCESSOR_H_

#ifdef LCD_DEBUG

#include <stdint.h>
#include <stdbool.h>


#define LCD_DATA_PORT PORTA
#define LCD_DATA_PORT_DDR DDRA
#define LCD_CONTROL_PORT PORTF
#define LCD_CONTROL_PORT_DDR DDRF
#define LCD_RS_PIN PINF0
#define LCD_E_PIN PINF1

// Global variable declarations
uint8_t updateStep;
char charLine[2][16];

// Function declarations
void lcd_write_command(uint8_t command);
void lcd_write_data(uint8_t data);
void printToLcd(char data[], uint8_t line);
void mainDisplayRoutine(void);
void lcd_init_routine(void);
void lcd_port_init(void);
void lcd_init(void);

#endif /* LCD_DEBUG */

#endif /* LCDPROCESSOR_H_ */
