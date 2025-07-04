/*
 * messageProcessor.c
 *
 * Created: 1/6/2025
 * Author: Refactored from messageProcessor.h
 */
#include "../common/config.h"
#ifdef LCD_DEBUG

#ifndef UNIT_TESTS
#include <avr/io.h>
#endif /* UNIT_TESTS */
#include <stdbool.h>
#include "../common/globalVars.h"
#include "../display/messageProcessor.h"
#include "../display/lcdProcessor.h"

uint8_t nextErrorPrintLine = 1;
bool errorInLine[2] = {false};

char convertSemiByte2Char(uint8_t semiByte) {
	if (semiByte < 10) return '0' + semiByte;
	else return 'A' + semiByte - 10;
}

#ifdef UNIT_TESTS
void mainMessageProcessorRoutine(void) {
#else 
void inline mainMessageProcessorRoutine(void) {
#endif
	if (errorStatusCurrent != ErrorNone) {
		char* errorMsg = "                ";
		uint8_t hbyte = errorChar >> 4;
		uint8_t lbyte = errorChar & 0xF;
		switch (errorStatusCurrent) {
			case UnknownCommandByteMaster:
			errorMsg = "E: UnknCmdM     ";
			errorMsg[12] = convertSemiByte2Char(hbyte);
			errorMsg[13] = convertSemiByte2Char(lbyte);
			break;
			case UnknownCommandByteSlave:
			errorMsg = "E: UnknCmdS     ";
			errorMsg[11] = convertSemiByte2Char(slaveChannelError);
			errorMsg[13] = convertSemiByte2Char(hbyte);
			errorMsg[14] = convertSemiByte2Char(lbyte);
			break;
			case KbMouseDataSizeExceed:
			errorMsg = "E: KbMsDaSzEx   ";
			errorMsg[14] = convertSemiByte2Char(hbyte);
			errorMsg[15] = convertSemiByte2Char(lbyte);
			case VidPidDataSizeExceed:
			errorMsg = "E: VPSizeEx     ";
			errorMsg[12] = convertSemiByte2Char(hbyte);
			errorMsg[13] = convertSemiByte2Char(lbyte);
			break;
			case QueueOverflow:
			errorMsg = "E: QueueOvrflw  ";
			default:
			break;
		}
		if (nextErrorPrintLine == 1) {
			nextErrorPrintLine = 0;
			} else {
			nextErrorPrintLine = 1;
		}
		errorInLine[nextErrorPrintLine] = true;
		printToLcd(errorMsg, nextErrorPrintLine);
		errorStatusCurrent = ErrorNone;
		errorChar = 0;
	}
	
}

#endif /* LCD_DEBUG */
