//*****************************************************************************
//
// rit128x96x4.h - Prototypes for the driver for the RITEK 128x96x4 graphical
//                   OLED display.
//
// Copyright (c) 2007-2010 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 6075 of the EK-LM3S8962 Firmware Package.
//
//*****************************************************************************

#ifndef __RIT128X96X4F_H__
#define __RIT128X96X4F_H__

#include <stdint.h>


//*****************************************************************************
//
// Data types
//
//*****************************************************************************
typedef struct 
{
	const uint8_t  *pucImage;
	int32_t  lX;
	int32_t  lY;
	uint32_t ulWidth;
	uint32_t ulHeight;
	uint32_t ulAlpha;
}
tile_t;

typedef struct 
{
	const uint8_t *pcStr;
	uint32_t ulX;
	uint32_t ulY;
	uint8_t ucCharLv;
	uint8_t ucBgrLv;
}
string_t;

typedef struct 
{
	const uint8_t  *pucImage;
	int32_t  lX;
	int32_t  lY;
	uint32_t ulWidth;
	uint32_t ulHeight;
	uint32_t ukFrame;
	uint32_t ulAlpha;
}
sprite_t;


//*****************************************************************************
//
// Prototypes for the driver APIs.
//
//*****************************************************************************
extern void RIT128x96x4Clear(void);
extern void RIT128x96x4StringDraw(const char *pcStr,
                                    unsigned long ulX,
                                    unsigned long ulY,
                                    unsigned char ucLevel);
extern void RIT128x96x4ImageDraw(const unsigned char *pucImage,
                                   unsigned long ulX,
                                   unsigned long ulY,
                                   unsigned long ulWidth,
                                   unsigned long ulHeight);
extern void RIT128x96x4Init(unsigned long ulFrequency);
extern void RIT128x96x4Enable(unsigned long ulFrequency);
extern void RIT128x96x4Disable(void);
extern void RIT128x96x4DisplayOn(void);
extern void RIT128x96x4DisplayOff(void);

/* extend Display API */
extern void RIT_FreshScreen(void); /*use the buffer to freshen the oled  */

extern void RIT_ClearBuf(uint32_t ulLevel); /*use a color to clear the whole buff */
extern void RIT_DrawDotBuf(uint32_t ulX, uint32_t ulY, uint8_t ulLevel); /*draw a dot in the buff */
extern void RIT_DrawLineBuf(int32_t lX1, int32_t lY1, int32_t lX2, int32_t lY2, uint8_t ucLevel); /*draw a line in the buff             */

extern void RIT_DrawTileBuf(tile_t *pstImage);
									   /*draw the sprite in the buff, support*/
									   /*the specific Alpha                  */

extern void RIT_DrawStringBuf_F (string_t *pstStr);
                                       /*draw string in the buffer by a str  */

                                       
/* Todo API */						
//extern void RIT_DrawTileBuf_F(tile_t *pstImage);
                                       /*the fast version of RIT_DrawTileBuf */
									   /*not support Alpha and odd position  */
//extern void RIT_DrawHoriLineBuf (...);
//extern void RIT_DrawVertLineBuf (...);
                                       /*Don't support odd X position        */
//extern void RIT_DrawBoxBuf_F (...);
//extern void RIT_DrawCircleBuf (...);

//extern void RIT_DrawSpriteBuf (...);
                                       /*Don't support odd X position        */
//extern void RIT_DrawSpriteBuf_F (...);
									   /*fast version of RIT_DrawSpriteBuf   */
									   /*Don't support Alpha and odd position*/

/*The special version for 8*8 tile and sprite                                */
//extern void RIT_DrawTileBuf_8F (tile_t *pstImage);
//extern void RIT_DrawSpriteBuf_8 (...);
//extern void RIT_DrawSpriteBuf_8F (...);
//extern void RIT_DrawRollBuf_8F (...);
/*The function for the raycasting                                            */
//extern void RAY_VertZoomBuf( const uint8_t  *pucLine,
//                                   uint32_t   ulX,
//                                   uint32_t   ulZoom,);


#endif // __RIT128X96X4F_H__

