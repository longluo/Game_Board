/************************************************************************************
** File: - E:\ARM\lm3s8962projects\Game\MazeGame\Game\game.h
**  
** Copyright (C), Long.Luo, All Rights Reserved!
** 
** Description: 
**      game.h - Prototypes for the game.
** 
** Version: 1.0
** Date created: 11:40:08,27/10/2012
** Author: Long.Luo
** 
** --------------------------- Revision History: --------------------------------
** 	<author>	<data>			<desc>
** 
************************************************************************************/

#ifndef __GAME_H__
#define __GAME_H__

//*****************************************************************************
//
// Declarations for the game state variables.
//
//*****************************************************************************
extern unsigned long g_ulScore;
extern unsigned short g_usPlayerX;
extern unsigned short g_usPlayerY;
extern unsigned short g_pusMonsterX[100];
extern unsigned short g_pusMonsterY[100];
extern char g_ppcMaze[94][127];

//*****************************************************************************
//
// Prototypes for the game.
//
//*****************************************************************************
extern tBoolean MainScreen(void);
extern void PlayGame(void);

#endif /* __GAME_H__ */

