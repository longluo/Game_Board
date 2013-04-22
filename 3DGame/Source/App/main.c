/************************************************************************************
** File: - E:\ARM\lm3s8962projects\Game\3DRayCast\Usr\main.c
**  
** Copyright (C), Long.Luo, All Rights Reserved!
** 
** Description: 
**      main 
** 
** Version: 1.0
** Date created: 23:37:46,27/10/2012
** Author: Long.Luo
** 
** --------------------------- Revision History: --------------------------------
** 	<author>	<data>			<desc>
** 
************************************************************************************/

#include <stdint.h>

#include "hw_types.h"
#include "hw_ints.h"
#include "hw_memmap.h"
#include "hw_sysctl.h"
#include "hw_gpio.h"
#include "sysctl.h"
#include "gpio.h"

#include "globals.h"
#include "rit128x96x4F.h"
#include "texture.h"
#include "render.h"
#include "map.h"
#include "keyboard.h"


volatile uint32_t g_ulTickCount = 0;

//*****************************************************************************
// Globe var
// Frame buffer
//*****************************************************************************
unsigned char g_pucFrame[6144];        /*the buffer for the frame            */

//*****************************************************************************
// Globe var
// The speed of the processor clock, which is therefore the speed of the clock
// that is fed to the peripherals.
//*****************************************************************************
unsigned long g_ulSystemClock;


void Delay_ms(uint16_t delay_time);


void Delay_ms(uint16_t delay_time)
{
	uint32_t wait_timestamp = g_ulTickCount + (uint32_t)delay_time;
									   /*wait_timestamp = tell the system,    */
									   /*from which time stamp it could       */
									   /*restart                              */
	while (g_ulTickCount != wait_timestamp)
	{
		;
	}
}



void SysTickIntHandler(void)
{
	g_ulTickCount++;
}


//*****************************************************************************
//
// main
//
//*****************************************************************************
int main(void)
{
	// Init part
	render_t Mainscreen =
	{ 
		128,
		300,
		0
	};

	// system clock
    if(REVISION_IS_A2)
	{
        SysCtlLDOSet(SYSCTL_LDO_2_75V);
    }

    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_8MHZ);
	g_ulSystemClock = SysCtlClockGet();

	/// oled init
    RIT128x96x4Init(1000000);
    
	// init the systick
	IntMasterEnable();
	SysTickPeriodSet(g_ulSystemClock / CLOCK_RATE);
    SysTickIntEnable();
    SysTickEnable();

	//	init the keyboard 
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    // Configure the GPIOs used to read the state of the on-board push buttons.
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE,
                         GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    GPIOPadConfigSet(GPIO_PORTE_BASE,
                     GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,
                     GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_1);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_STRENGTH_2MA,
                     GPIO_PIN_TYPE_STD_WPU);

	Delay_ms(100);

	// main loop
	while (true)
	{
		if (g_ulTickCount & (1<<6))
		{
			KeyboardHandler(&Mainscreen, &map_1);
			DrawSky();
			render(&Mainscreen, &map_1);
			RIT_FreshScreen(); 
		}
	}
}

