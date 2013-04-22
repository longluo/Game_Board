/************************************************************************************
** File: - E:\ARM\lm3s8962projects\Game\3DRayCast\Usr\globals.h
**  
** Copyright (C), Long.Luo, All Rights Reserved!
** 
** Description: 
**      globals.h - Shared configuration and global variables.
** 
** Version: 1.0
** Date created: 23:37:23,27/10/2012
** Author: Long.Luo
** 
** --------------------------- Revision History: --------------------------------
** 	<author>	<data>			<desc>
** 
************************************************************************************/

#ifndef __GLOBALS_H__
#define __GLOBALS_H__


#include <stdint.h>

#include "hw_ints.h"
#include "hw_types.h"


//*****************************************************************************
//
// The clock rate for the SysTick interrupt.  All events in the application
// occur at some fraction of this clock rate.
//
//*****************************************************************************
#define CLOCK_RATE              1000


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
// data structure.
//
//*****************************************************************************
typedef struct 
{
	uint32_t ulPlayerX;
	uint32_t ulPlayerY;
	uint32_t ulDei;
} 
render_t;

typedef struct 
{
	uint32_t ulColumnNum;
	uint32_t ulWallHeight;
	uint8_t *pucTexture;
	uint32_t ulTextureOffset;
} 
columnWall_t;

#endif /* __GLOBALS_H__ */

