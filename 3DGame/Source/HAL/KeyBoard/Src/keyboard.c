/************************************************************************************
** File: - E:\ARM\lm3s8962projects\Game\3DRayCast\Usr\keyboard.c
**  
** Copyright (C), Long.Luo, All Rights Reserved!
** 
** Description: 
**      keyboard
** 
** Version: 1.0
** Date created: 11:45:20,28/10/2012
** Author: Long.Luo
** 
** --------------------------- Revision History: --------------------------------
** 	<author>	<data>			<desc>
** 
************************************************************************************/

#include <stdint.h>

#include "hw_types.h"
#include "hw_memmap.h"
#include "hw_gpio.h"
#include "gpio.h"

#include "keyboard.h"


/************************************************************************************
** Function: KeyboardHandler()
** Routine Description: - 
**     keyboard 
** Input parameters: - 
**    NONE 
** Output parameters: NONE
** Returned Value: NONE
** Remarks:
** 
** Date created: 12:54:36,28/10/2012
** Author: Long.Luo
************************************************************************************/
void KeyboardHandler(render_t *pstRend, map_t *pstMap)
{
    uint32_t ulData;
	fixed_t fdx,fdy;
	int32_t lNewX = pstRend->ulPlayerX, lNewY = pstRend->ulPlayerY;
	angle_t atAngleTemp = pstRend->ulDei;

    // Read the state of the push buttons.
    ulData = (GPIOPinRead(GPIO_PORTE_BASE, (GPIO_PIN_0 | GPIO_PIN_1 |
                                            GPIO_PIN_2 | GPIO_PIN_3)) |
              (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1) << 3));
              
	// handler for direction
	if (ulData & (1<<2))
	{
		atAngleTemp -= 5;	
	}

	if (ulData & (1<<3))
	{
		atAngleTemp += 5;	
	}

	if (atAngleTemp < 0)
	{
		atAngleTemp = 720 + atAngleTemp;
	}

	if (atAngleTemp >= 720)
	{
		atAngleTemp = atAngleTemp - 720;
	}
	pstRend->ulDei = atAngleTemp;
	
	// handler for move		
	if (!(ulData & 1))
	{
		fdy = -(fsin(atAngleTemp)*5);
		fdx = (fcos(atAngleTemp)*5);				
		lNewX += fx2i(fdx);
		lNewY += fx2i(fdy);
		
		if ((lNewX>66) && (lNewY>66) && (lNewX<1982) && (lNewY<1982)
			&&(0xFF == *(pstMap->pucMap + (lNewX>>6) + ((lNewY>>6) << 5))))
		{
			pstRend->ulPlayerX = lNewX;
			pstRend->ulPlayerY = lNewY;
		}
	}
}

