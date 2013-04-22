/************************************************************************************
** File: - E:\ARM\lm3s8962projects\Game\3DRayCast\RayCast\render.c
**  
** Copyright (C), Long.Luo, All Rights Reserved!
** 
** Description: 
**      render.c
** 
** Version: 1.0
** Date created: 11:33:10,28/10/2012
** Author: Long.Luo
** 
** --------------------------- Revision History: --------------------------------
** 	<author>	<data>			<desc>
** 
************************************************************************************/

#include "render.h"


//*****************************************************************************
//
// var
//
//*****************************************************************************
const fixed_t sinTable[180] = 
{
	0,9,18,27,36,44,54,63,71,80,89,98,107,116,125,134,
	143,151,160,169,178,187,195,204,213,222,230,239,248,
	256,265,274,282,291,299,308,316,325,333,342,350,359,
	367,375,384,392,400,408,416,425,433,441,449,457,465,
	473,481,489,496,504,512,520,527,535,543,550,558,565,
	573,580,587,595,602,609,616,623,630,637,644,651,658,
	665,672,679,685,692,698,705,711,718,724,730,737,743,
	749,755,761,767,773,779,784,790,796,801,807,812,818,
	823,828,834,839,844,849,854,859,864,868,873,878,882,
	887,891,896,900,904,908,912,916,920,924,928,932,935,
	939,942,946,949,953,956,959,962,965,968,971,974,977,
	979,982,984,987,989,991,994,996,998,1000,1002,1003,
	1005,1007,1008,1010,1011,1013,1014,1015,1016,1017,
	1018,1019,1020,1021,1022,1022,1023,1023,1023,1024,
	1024,1024
};

const fixed_t tanTable[180] =
{
	0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,
	153,162,171,181,290,199,208,218,227,236,246,255,265,
	274,284,297,303,313,323,333,343,353,363,373,383,393,
	403,414,424,435,445,456,467,477,488,499,511,522,533,
	544,556,568,579,591,603,615,628,640,652,665,678,691,
	704,717,730,744,758,772,786,800,815,829,844,859,875,
	890,906,922,938,955,972,989,1006,1024,1042,1060,1079,
	1098,1117,1137,1157,1178,1199,1220,1242,1265,1287,1311,
	1335,1359,1384,1409,1436,1462,1490,1518,1547,1577,1607,
	1639,1671,1704,1738,1774,1810,1847,1886,1926,1967,2010,
	2054,2100,2147,2196,2247,2300,2355,2412,2472,2534,2600,
	2668,2739,2813,2892,2974,3060,3152,3248,3349,3457,3571,
	3692,3822,3960,4107,4265,4435,4619,4818,5033,5268,5525,
	5807,6119,6465,6852,7286,7778,8340,8988,9743,10635,
	11704,13011,14644,16742,19539,23453,29324,39105,58665,
	117339
};


//*****************************************************************************
//
// the main render function
//
//*****************************************************************************
void render (render_t *pstRend, map_t *pstMap)
{
	/*define of the local var */
	static uint32_t ulCurColumn;          /*the current Column to render */
	static fixed_t hdist, vdist, dist;
	
    // distance to the closest horizontal and vertical intersection, shortest dist is used
	static int32_t hoff, voff;	// offset along wall (used for texturing)
	static fixed_t x ;
	static fixed_t y ;	// intersection test points / tracer points

	static fixed_t stepx, stepy;		// step increment values

	static uint8_t	*htex;
	static uint8_t  *vtex;	// texture to be used
	static uint8_t ucMapTemp;// map number

	static fixed_t temp;  //use for calculate sin cos
	static angle_t currentAngle; //the angle of the ray
	static fixed_t caltemp1, caltemp2, caltemp3;   //临时测试
	static columnWall_t stWallColumn;	   /*the column str for one column render */
	

/*the main loop from 0~WIDTH_SCREEN------------------------------------------*/
	for (ulCurColumn = 0; ulCurColumn < WIDTH_SCREEN; ulCurColumn ++)
	{
		hdist = i2fx(30000); hoff = 0;
		vdist = i2fx(30000); voff = 0;
		htex = vtex = *map_1.ppucTexListH;
/*which column in buffer to render-------------------------------------------*/	
		stWallColumn.ulColumnNum = ulCurColumn +  X_OFFSET;	
/*Cacluate the current scan ray angle----------------------------------------*/
		currentAngle = pstRend->ulDei + HALF_WIDTH_SCREEN - ulCurColumn;
/*fit the currentAngle into 0~719.5------------------------------------------*/		
		if (currentAngle < 0)
		{
			currentAngle = 720 + currentAngle;
		}
		
		if (currentAngle >= 720)
		{
			currentAngle = currentAngle - 720;
		}	 
		
/*ray------------------------------------------------------------------------*/
		temp = fsin(currentAngle);
		
		// move to first intersection point and calculate tracer increments
		if (temp != 0) 
		{ // if not parallel	不垂直于地图
			x =	i2fx(pstRend->ulPlayerX);
			y =	i2fx(pstRend->ulPlayerY);	// intersection test points / tracer points
			
			if (temp > 0)
			{
				// up
				x += fdiv((y % GRID_SIZEF), (ftan(currentAngle)));
				y += -(y % GRID_SIZEF);

				stepx = fdiv(GRID_SIZEF, (ftan(currentAngle)));
				stepy = -GRID_SIZEF;
			}
			
			if (temp < 0)
			{
				//down
				x += fdiv((GRID_SIZEF-(y%GRID_SIZEF)), (-ftan(currentAngle)));
				y += (GRID_SIZEF-(y%GRID_SIZEF));

				stepx = fdiv(GRID_SIZEF, (-ftan(currentAngle)));
				stepy = GRID_SIZEF;
			}

			while (	y > 0 && y < i2fx(pstMap->ulHeigth * GRID_SIZE)
				&&	x > 0 && x < i2fx(pstMap->ulWidth * GRID_SIZE))
				{
					// check if we hit a wall by checking the intersection point + 1 unit into the cell				
					ucMapTemp =*( pstMap->pucMap+((fx2i(y) + ((stepy>0) ? 1 : -1)) / GRID_SIZE)* (pstMap->ulWidth) + (fx2i(x) / GRID_SIZE));							

					if (0xff != ucMapTemp )
					{	
						htex = *(pstMap->ppucTexListH + ucMapTemp);
						caltemp1 = i2fx(pstRend->ulPlayerX) - x;
						
						if (caltemp1 < 0)
						{
							caltemp1 = -caltemp1;
						}
						
						caltemp2 = i2fx(pstRend->ulPlayerY)-y;
						if (caltemp2 < 0)
						{
							caltemp2 = -caltemp2;
						}
					
						if (caltemp1 > caltemp2)
						{
					    	hdist = fdiv(caltemp1, fcos(currentAngle));
						}
						else
						{
					    	hdist = fdiv(caltemp2, fsin(currentAngle));
						}
						
						if (hdist < 0)
						{
					    	hdist = -hdist;
					    }
					    
						// set a minimum draw distance, one unit
						if (hdist >= i2fx(1))
						{
							hoff = (fx2i(x) % GRID_SIZE);

							if (stepy > 0)
							{
								hoff = GRID_SIZE-1 - hoff;	
							}
							break;
						}
						else
						{
							hdist = i2fx(30000);
						}
					}

					x += stepx;
					y += stepy;
				}
			}
			
			temp = fcos(currentAngle);
			if (temp != 0) 
			{ 
				//不平行于地图.
				x =	i2fx(pstRend->ulPlayerX);
				y =	i2fx(pstRend->ulPlayerY);	
				
				// move to first intersection point and calculate tracer increments			
				if (temp > 0)	// right
				{
					y += fmul((GRID_SIZEF - (x%GRID_SIZEF)), (-ftan(currentAngle)));
					x += (GRID_SIZEF - (x%GRID_SIZEF));

					stepy = fmul(GRID_SIZEF, (-ftan(currentAngle)));
					stepx = GRID_SIZEF;
				}
				else			// left
				{
					y += fmul((x % GRID_SIZEF), ftan(currentAngle));
					x += -(x % GRID_SIZEF);
					stepy = fmul(GRID_SIZEF, ftan(currentAngle));
					stepx = -GRID_SIZEF;
				}
				
				// check for intersections and increment the tracer
				while (y > 0 && y < i2fx(pstMap->ulHeigth * GRID_SIZE)
				&& x > 0 && x < i2fx(pstMap->ulWidth * GRID_SIZE))
				{
                	// check if we hit a wall by checking the intersection point + 1 unit into the cell
                	ucMapTemp =*(pstMap->pucMap +(fx2i(y) / GRID_SIZE)* (pstMap->ulWidth)+ ((fx2i(x) + ((stepx>0) ? 1 : -1)) / GRID_SIZE));				
	                if (0xff !=ucMapTemp )
					{	
						vtex = *(pstMap->ppucTexListV +ucMapTemp);
						caltemp1 = i2fx(pstRend->ulPlayerX)-x;
						
						if (caltemp1<0)
						{
							caltemp1 = -caltemp1;
						}
						
						caltemp2 = i2fx(pstRend->ulPlayerY)-y;
						if (caltemp2<0)
						{
							caltemp2 = -caltemp2;
						}
						
						if (caltemp1  >= caltemp2 )
						{
						    vdist = fdiv(caltemp1, fcos(currentAngle));
						}						   
						else
						{
						    vdist = fdiv(caltemp2, fsin(currentAngle));
						}
						    
						if (vdist < 0)
						{
						    vdist = -vdist;
						}

	                    // set a minimum draw distance, one unit
						if (vdist >= i2fx(1))
						{
							voff = (fx2i(y) % GRID_SIZE);
							
							if (stepx < 0)
							{
								voff = GRID_SIZE-1 - voff;	
							}
			                break;
						}
						else
						{
							vdist = i2fx(30000);
						}
					}
				
					x += stepx;
					y += stepy;
				}
			}
			
		// which is closer
/*which line of the texture was used-----------------------------------------*/
/*which texture was used-----------------------------------------------------*/	
    	if (hdist < vdist)
	    {
			dist = hdist;
			stWallColumn.ulTextureOffset = hoff;
			stWallColumn.pucTexture = htex;
		}
		else
		{
		    dist = vdist;
			stWallColumn.ulTextureOffset = voff;
			stWallColumn.pucTexture = vtex;
		}	
/*the height of the texture in this column-----------------------------------*/
		// adjust for fish-eye effect
		caltemp3= currentAngle - pstRend->ulDei;
		if (caltemp3 < 0)
		{
			caltemp3 = -caltemp3;
		}
		
		dist = fmul(dist, fcos(caltemp3));
		// calculate projected column height				
		stWallColumn.ulWallHeight = fx2i( fmul(fdiv(GRID_SIZEF,dist), DISTANCE_TO_SCREEN_F) );
/*render every column--------------------------------------------------------*/
		DrawColumnWall(&stWallColumn);	
/*---------------------------------------------------------------------------*/	
	}//end of for loop 
}


/*---------------------------------------------------------------------------*/	
/*fixed math-----------------------------------------------------------------*/	
/*---------------------------------------------------------------------------*/	
fixed_t fsin(angle_t dei)
{
	if ((dei<180)&&(dei>=0))
		return sinTable[dei];
	if ((dei>=180)&&(dei<360))
		return sinTable[359 - dei];
	if ((dei>=360)&&(dei<540))
		return -1*(sinTable[dei-360]);
	if ((dei>=540)&&(dei<720))
		return -1*(sinTable[719 - dei]);	
}


fixed_t fcos(angle_t dei)
{
    if ((dei<180)&&(dei>=0))
		return sinTable[179 - dei];
	if ((dei>=180)&&(dei<360))
		return -1*(sinTable[dei -180]);
	if ((dei>=360)&&(dei<540))
		return -1*(sinTable[539 - dei]);
	if ((dei>=540)&&(dei<720))
		return sinTable[dei - 540];
}


fixed_t ftan(angle_t dei)
{
	if ((dei<180)&&(dei>=0))
		return tanTable[dei];
	if ((dei>=180)&&(dei<360))
		return -tanTable[359 - dei];
	if ((dei>=360)&&(dei<540))
		return tanTable[dei - 360];
	if ((dei>=540)&&(dei<720))
		return -tanTable[719 - dei];
}


void DrawColumnWall(columnWall_t *pstColWall)
{
	uint32_t  ulYCurrent,ulRenderLoop;   /*current y to draw and how many y to*/
	uint32_t  ulTexStrPoi;				/*texture start point 0~64           */
	uint32_t  ulDifFromTop;
	uint32_t  ulTexY;
	fixed_t fScale;
	uint8_t ulLevel;                    /*the color used to filled the buf */

/*decide from which Y point to rendom----------------------------------------*/	
	fScale = fdivt(i2fxt(TEXTURE_SIZE), i2fxt(pstColWall->ulWallHeight));
										/*zoom scale 64/height               */
	if (0 == pstColWall->ulWallHeight)
	{
		return ;
	}
	
	if (pstColWall->ulWallHeight > HEIGHT_SCREEN)
	{
		ulYCurrent = 0;
		ulDifFromTop=0;
		ulRenderLoop = HEIGHT_SCREEN;
		ulTexStrPoi = (fx2it(fmult(fScale, i2fxt(pstColWall->ulWallHeight - HEIGHT_SCREEN)))) >> 1; 
		              
	}
	else 
	{
		ulYCurrent =HALF_SCREEN - ((pstColWall->ulWallHeight)/2);
		ulDifFromTop = HALF_SCREEN - ((pstColWall->ulWallHeight)/2);
		ulRenderLoop = pstColWall->ulWallHeight;
		ulTexStrPoi = 0;
	}

/*---------------------------------------------------------------------------*/
	for (; ulRenderLoop>0; ulRenderLoop --)
	{		
		ulTexY = fx2it(fmult(fScale, i2fxt(ulYCurrent-ulDifFromTop))) + ulTexStrPoi;

		/*get the color from texture-------------------------------------------------*/
		if (ulTexY & 0x01)
		{
			ulLevel =(*(pstColWall->pucTexture +(pstColWall->ulTextureOffset<<5) + (ulTexY>>1))) 
		         & 0x0f;//if ulTexY is odd
		}
		else 
		{
			ulLevel =(*(pstColWall->pucTexture +(pstColWall->ulTextureOffset<<5) + (ulTexY>>1) ))
		         >>4;
		}
		
		/*draw dot to buf------------------------------------------------------------*/		
		if (pstColWall->ulColumnNum & 0x01)
		{
			g_pucFrame[(pstColWall->ulColumnNum>>1) + (ulYCurrent<<6)] = 
			((g_pucFrame[(pstColWall->ulColumnNum>>1) + (ulYCurrent<<6)] & 0xf0) |
	                     (ulLevel & 0x0f));
		}
		else
		{
			g_pucFrame[(pstColWall->ulColumnNum>>1) + (ulYCurrent<<6)] =
	        ((g_pucFrame[(pstColWall->ulColumnNum>>1) + (ulYCurrent<<6)] & 0x0f) |
	                     ((ulLevel & 0x0f) << 4));
		}
		
/*---------------------------------------------------------------------------*/
		ulYCurrent ++;
	}
}



void DrawSky(void)
{
	uint32_t ulLoop = 0;

	for (ulLoop = 0; ulLoop < 2432; ulLoop += 4)
	{
		*((unsigned long *)(g_pucFrame + ulLoop)) = 0x66666666;
	}

	for (ulLoop = 2432; ulLoop < 4864; ulLoop += 4)
	{
		*((unsigned long *)(g_pucFrame + ulLoop)) = 0x11111111;
	}

	for (ulLoop = 4864; ulLoop < 6144; ulLoop += 4)
	{
		*((unsigned long *)(g_pucFrame + ulLoop)) = 0x0;
	}
}
 