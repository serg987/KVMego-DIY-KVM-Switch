/*
 * videoSwitchControl.h
 *
 * Created: 9/7/2024 8:26:47 PM
 *  Author: user
 */ 

#ifndef VIDEOSWITCHCONTROL_H_
#define VIDEOSWITCHCONTROL_H_

#include <stdint.h>
#include <stdbool.h>

#define OUT_PORT PORTB
#define OUT_PORT_DDR DDRB
#define OUT_PORT_PIN PINB
#define OUT_3 PINB5
#define OUT_2 PINB6
#define OUT_1 PINB7  // atmega pro board has a LED at PB7

// Function declarations
void portInit(void);
uint8_t resetPort(void);
void setOut(void);

#endif /* VIDEOSWITCHCONTROL_H_ */