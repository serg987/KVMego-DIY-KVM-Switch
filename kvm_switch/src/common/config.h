/*
 * config.h
 *
 * Created: 1/6/2025
 * Author: Centralized configuration for ATM2560 Switch
 */

#ifndef CONFIG_H_
#define CONFIG_H_

// =============================================================================
// FEATURE CONFIGURATION
// =============================================================================

// Debug features
// some debug info may go to 1602 LCD display. However, there is a bug in arbitrary lines shifting,
// so it has limited usage. For production, comment out this line
#define LCD_DEBUG

// Hardware features
// if RF transmitter is used to control video switches, the logic is different - see videoSwitchControl
// so comment it out if it is not needed
#define RF_TRANSMITTER

// =============================================================================
// HARDWARE CONFIGURATION
// =============================================================================

// System clock frequency
#define F_CPU 14745600UL

// UART Configuration
#define NUM_OF_UARTS 4
#define RX_BUFFER_SIZE 8

// VID/PID Data Configuration
#define VID_PID_DATA_SIZE 512

// Scheduler Configuration
#define SCHEDULER_QUEUE_SIZE 16

// =============================================================================
// TIMING CONFIGURATION
// =============================================================================

// Keyboard control timing (in half milliseconds)
#define TIME_TO_WAIT_SCRLLOCK_PRESSED_HALF_MS 1000 // 0.5s to press, release and press and release for the second time (each item)
#define TIME_TO_WAIT_CONTROL_STATE_HALF_MS 12000 // 6s to change PC or jiggler state
#define TIME_TO_CONFIRM_CONTROL_STATE_HALF_MS 6000 // 3s to show/blink leds of the changed state

// Jiggler timing
#define TIME_TO_ACTIVATE_JIGGLER_S 120 // 8 bit - cannot be more than 256 secs
#define minTimeBetweenRunsHalfMs 20000 // ~10 secs b/w jiggler run at minimum + shifting 8bit random value by 7 bits will have 20K-52K x 500 us -> 10-26s

// Connection management
#define SLAVE_STATUS_FRAMES_BEFORE_CONSIDER_DISCONNECT 5

// =============================================================================
// JIGGLER CONFIGURATION
// =============================================================================

#define minRadius 100
#define minAngle 20
#define minNumberOfPoints 35

// =============================================================================
// UTILITY MACROS
// =============================================================================

// PC connection macros
#define isAnySlaveInitialized() (pcState[1] == PcConnected || pcState[2] == PcConnected || pcState[3] == PcConnected)
#define isPcConnected(port) (slaveStatusFramesBeforeDisconnected[port] > 0)
//#define isSelectedDeviceReady() (currentPcConnected > 0 && pcState[currentPcConnected] == PcConnected)

// Keyboard macros
#define isHotkeyPressed() (kbControlState == WaitingCommandKey || kbControlState == PressedJigglerKey || kbControlState == WaitingJigglerState)

// UART transmission macros
// this does not depend on NUM_OF_UARTS, but seems it is the fastest way w/o using loops
#define isNoTransmittingReceiving() ((currentFrameByte[0] == 0 && lenTxData[0] == 0) \
									&& (currentFrameByte[1] == 0 && lenTxData[1] == 0) \
									&& (currentFrameByte[2] == 0 && lenTxData[2] == 0) \
									&& (currentFrameByte[3] == 0 && lenTxData[3] == 0))

#endif /* CONFIG_H_ */
