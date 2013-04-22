/************************************************************************************
** File: - E:\ARM\lm3s8962projects\Game\3DRayCast\Game\structure.h
**  
** Copyright (C), Long.Luo, All Rights Reserved!
** 
** Description: 
**      structure.h
** 
** Version: 1.0
** Date created: 11:31:48,28/10/2012
** Author: Long.Luo
** 
** --------------------------- Revision History: --------------------------------
** 	<author>	<data>			<desc>
** 
************************************************************************************/

#ifndef	__STRUCTURE_H__
#define __STRUCTURE_H__

#include <stdint.h>

typedef struct 
{
	uint8_t *pucMap;
	uint32_t ulHeigth;
	uint32_t ulWidth;
	uint8_t **ppucTexListH;
	uint8_t **ppucTexListV;
} 
map_t;

#endif /* __STRUCTURE_H__ */

