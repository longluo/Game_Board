/************************************************************************************
** File: - E:\ARM\lm3s8962projects\Game\MazeGame\Usr\globals.h
**  
** Copyright (C), Long.Luo, All Rights Reserved!
** 
** Description: 
**      globals.h - Shared configuration and global variables.
** 
** Version: 1.0
** Date created: 11:41:01,27/10/2012
** Author: Long.Luo
** 
** --------------------------- Revision History: --------------------------------
** 	<author>	<data>			<desc>
** 
************************************************************************************/

#ifndef __GLOBALS_H__
#define __GLOBALS_H__

//*****************************************************************************
//
// The clock rate for the SysTick interrupt.  All events in the application
// occur at some fraction of this clock rate.
//
//*****************************************************************************
#define CLOCK_RATE              300

//*****************************************************************************
//
// A set of flags used to track the state of the application.
//
//*****************************************************************************
extern unsigned long g_ulFlags;
#define FLAG_CLOCK_TICK         0           // A timer interrupt has occurred
#define FLAG_CLOCK_COUNT_LOW    1           // The low bit of the clock count
#define FLAG_CLOCK_COUNT_HIGH   2           // The high bit of the clock count
#define FLAG_UPDATE             3           // The display should be updated
#define FLAG_BUTTON             4           // Debounced state of the button
#define FLAG_DEBOUNCE_LOW       5           // Low bit of the debounce clock
#define FLAG_DEBOUNCE_HIGH      6           // High bit of the debounce clock
#define FLAG_BUTTON_PRESS       7           // The button was just pressed
#define FLAG_ENET_RXPKT         8           // An Ethernet Packet received
#define FLAG_ENET_TXPKT         9           // An Ethernet Packet transmitted

//*****************************************************************************
//
// The speed of the processor.
//
//*****************************************************************************
extern unsigned long g_ulSystemClock;

//*****************************************************************************
//
// Storage for a local frame buffer.
//
//*****************************************************************************
extern unsigned char g_pucFrame[6144];

//*****************************************************************************
//
// The set of switches that are currently pressed.
//
//*****************************************************************************
extern unsigned char g_ucSwitches;


#endif /* __GLOBALS_H__ */

