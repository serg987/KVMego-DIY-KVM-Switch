/*
 * atm2560_switch.c
 *
 * Created: 7/30/2024 6:34:05 PM
 * Author : user
 */ 

#include <avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include "common/config.h"
#include "common/globalVars.h"
#include "uart/uartHelper.h"
#include "control/videoSwitchControl.h"
#ifdef LCD_DEBUG 
#include "display/lcdProcessor.h"
#include "display/messageProcessor.h"
#endif /* LCD_DEBUG */
#include "uart/uartProtocolProcessor.h"
#include "control/jiggler.h"
#include "scheduler/scheduler.h"
#include "keyboard/keyboardProcessor.h"
#include "control/eventProcessor.h"


int main(void)
{
	cli();
	initJigglerTimer();
	initUart();
	schedulerInit();
	portInit();
	sei();
	
	#ifdef LCD_DEBUG
	lcd_init();
	printToLcd(welcomeLcdMessage, 0);
	printToLcd(emptyLcdLine, 1);
	updateStep = 0; // wait till LCD is initialized
	#endif /* LCD_DEBUG */

    while (1) 
    {	
		mainMasterUARTRoutine();
		mainSlaveUARTRoutine();
		mainEventProcessorRoutine();
		mainSchedulerRoutine();	
		if (isNoTransmittingReceiving()) {
			// here are non-urgent routines to process, to not use CPU while communication is happening
			#ifdef LCD_DEBUG 
			mainMessageProcessorRoutine();
			#endif /* LCD_DEBUG */

			mainKeyboardProcessorRoutine();
		}
    }
}
