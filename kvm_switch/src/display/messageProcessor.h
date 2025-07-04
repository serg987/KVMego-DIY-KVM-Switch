/*
 * messageProcessor.h
 *
 * Created: 9/14/2024 5:40:21 PM
 *  Author: user
 */ 

#ifndef MESSAGEPROCESSOR_H_
#define MESSAGEPROCESSOR_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef LCD_DEBUG

// Global variable declarations
uint8_t nextErrorPrintLine;
bool errorInLine[2];

// Function declarations
char convertSemiByte2Char(uint8_t semiByte);
void mainMessageProcessorRoutine(void);

#endif /* LCD_DEBUG */

#endif /* MESSAGEPROCESSOR_H_ */
