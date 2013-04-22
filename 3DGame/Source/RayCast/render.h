/************************************************************************************
** File: - E:\ARM\lm3s8962projects\Game\3DRayCast\RayCast\render.h
**  
** Copyright (C), Long.Luo, All Rights Reserved!
** 
** Description: 
**      render.h
** 
** Version: 1.0
** Date created: 11:32:32,28/10/2012
** Author: Long.Luo
** 
** --------------------------- Revision History: --------------------------------
** 	<author>	<data>			<desc>
** 
************************************************************************************/

#ifndef __RENDER_H__
#define __RENDER_H__


#include "globals.h"
#include "render.h"
#include "map.h"


//*****************************************************************************
//
// definiens for the screen
//
//*****************************************************************************
// 16.16 is too prone to integer overflow and 24.8 is not accurate enough.
// it's really about finding a sweet spot when choosing your level of precision
#define FRACBITS    10
#define FLOATMUL    1024	/* 1 << FRACBITS */

#define WIDTH_SCREEN       128
							           /*the width of the screen             */
#define HALF_WIDTH_SCREEN  64

#define HEIGHT_SCREEN      76

#define HALF_SCREEN        38
									   /*the height of the screen            */
#define X_OFFSET           0
									   /*the x shift of screen to main one   */
#define Y_OFFSET	       0
									   /*the Y shift of screen to main one   */
#define TEXTURE_SIZE       64

#define GRID_SIZE          64  			/* height and width of map grid cells */
#define GRID_SIZEF         (64<<FRACBITS)	/* fixed point representation */        
									   /*the texture size in pixel           */
#define DISTANCE_TO_SCREEN 104
									   /*the distance from player to screen  */
#define DISTANCE_TO_SCREEN_F (104<<FRACBITS)

#define ABS(x)      ((x) < 0 ? -(x) : (x))

#define PI  		3.1415926535897932384626433832795
#define PI2			6.283185307179586476925286766559
#define DEGTORAD    0.0174532925199432957692369076848
#define RADTODEG    57.295779513082320876798154814105



typedef int32_t     fixed_t;	 //it is 22.10type
typedef int16_t     angle_t;

#define i2fx(x)     ((x) << FRACBITS)
#define fx2i(x)     ((x) >> FRACBITS)
#define f2fx(x)     ((fixed_t)((x) * FLOATMUL))
#define fx2f(x)     ((float)(x) / FLOATMUL)
#define d2fx(x)     ((fixed_t)((x) * FLOATMUL))
#define fx2d(x)     ((double)(x) / FLOATMUL)

#define fmul(x,y)   ( ((int64_t)(x) * (int64_t)(y)) >> FRACBITS )
#define fdiv(x,y)   ( ((int64_t)(x) << FRACBITS) / (y) )

#define	d2a(x)		(angle_t)((x/360.0)*(double)0x10000)/* degrees <-> angle */
#define a2d(x)		(((double)x/(double)0x10000)*360.0)
#define	r2a(x)		(angle_t)((x/PI2)*(double)0x10000)	/* radians <-> angle */
#define a2r(x)		(((double)x/(double)0x10000)*PI2)

// separate fixed-point math functions for texture mapping.
// 22.10 fixed-point isn't accurate enough here.
//16.16

#define TEXTURE_FRACBITS    16

#define i2fxt(x)     	((x) << TEXTURE_FRACBITS)
#define fx2it(x)     	((x) >> TEXTURE_FRACBITS)
#define fmult(x,y)   ( ((int64_t)(x) * (int64_t)(y)) >> TEXTURE_FRACBITS )
#define fdivt(x,y)   ( ((int64_t)(x) << TEXTURE_FRACBITS) / (y) )


//*****************************************************************************
//
// var
//
//*****************************************************************************


//*****************************************************************************
//
// Prototypes for the function APIs.
//
//*****************************************************************************
extern void render (render_t *pstRend, map_t *pstMap);
extern void DrawColumnWall (columnWall_t *pstColWall);
extern fixed_t fsin(angle_t dei);
extern fixed_t fcos(angle_t dei);
extern fixed_t ftan(angle_t dei);
extern void DrawSky(void);


#endif /* __RENDER_H__ */

