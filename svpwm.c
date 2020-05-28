/**
  ***********************************************************************************
  * @file    svpwm.c
  * @author  Serhii Yatsenko [royalroad1995@gmail.com]
  * @version V1.0
  * @date    May-2020
  * @brief   This file provides firmware function for implementation the SVPWM - 
  *	     Space-Vector Pulse Width Modulation for power electronics application
  ***********************************************************************************
  * @license
  *
  * MIT License
  *
  * Permission is hereby granted, free of charge, to any person obtaining a copy
  * of this software and associated documentation files (the "Software"), to deal
  * in the Software without restriction, including without limitation the rights
  * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  * copies of the Software, and to permit persons to whom the Software is
  * furnished to do so, subject to the following conditions:
  *
  * The above copyright notice and this permission notice shall be included in all
  * copies or substantial portions of the Software.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  * SOFTWARE.
  *
  ***********************************************************************************
  */

/* Includes -----------------------------------------------------------------------*/
#include "svpwm.h"

/* Private typedef ----------------------------------------------------------------*/
/* Private define -----------------------------------------------------------------*/
#define M_Pi	3.1415926535897f // float type of Pi constant value
#define M_Pi_3	(M_Pi/3.0f)

/* Private constants --------------------------------------------------------------*/

/** 
  * @brief Matrix with cell indices in a time intervals table for SVPWM duty cycle
  *	   calculation technique
  */ 
const uint8_t au8PermuataionMatrix[6][3] =
{	
	{ 1, 2, 0 },
	{ 3, 1, 0 },
	{ 0, 1, 2 },
	{ 0, 3, 1 },
	{ 2, 0, 1 },
	{ 1, 0, 3 }
};

/* Private macro ------------------------------------------------------------------*/
/* Private variables --------------------------------------------------------------*/
/* Private function prototypes ----------------------------------------------------*/
/* Private functions --------------------------------------------------------------*/

/**
  * @brief  SVPWM calculation function. This function calculates three values of
  *	    duty cycle to generate a three-phase voltage vector with amplitude -
  *	    ptSVPWM->fUs and angle - ptSVPWM->fAngRad.
  * @param  ptSVPWM: pointer to user data structure with type "tSVPWM".               
  * @retval None
  */
void tSVPWM_calc(tSVPWM* ptSVPWM)
{	
	uint8_t	u8Sector;
	float	fMaxUs, fScaledUs, fBeta, fTb1, fTb2, afTi[4];
	
	fMaxUs = ptSVPWM->fUdc * (1.0f/sqrtf(3.0f));
	
	switch(ptSVPWM->enInType)
	{
		case AlBe:
			ptSVPWM->fUs = hypotf(ptSVPWM->fUbe, ptSVPWM->fUal);
			ptSVPWM->fAngRad = atan2f(ptSVPWM->fUbe, ptSVPWM->fUal);
		break;
		
		case UsAng:
			ptSVPWM->fUs = fabsf(ptSVPWM->fUs);
		break;
		
		default: return;
	}
	
	if(ptSVPWM->fUs > fMaxUs) ptSVPWM->fUs = fMaxUs;
	
	fScaledUs = ptSVPWM->fUs/fMaxUs;
	
	ptSVPWM->fAngRad += M_Pi;
	
	u8Sector = (uint8_t)(ptSVPWM->fAngRad * (1.0f/M_Pi_3));
	
	fBeta = ptSVPWM->fAngRad - M_Pi_3 * u8Sector;
	
	fTb1 = fScaledUs * sinf(M_Pi_3 - fBeta);
	fTb2 = fScaledUs * sinf(fBeta);
	
	afTi[0] = (1.0f - fTb1 - fTb2)*0.5f;
	afTi[1] = fTb1 + fTb2 + afTi[0];
	afTi[2] = fTb2 + afTi[0];
	afTi[3] = fTb1 + afTi[0];
		
	ptSVPWM->fCCRA = ptSVPWM->fUdcCCRval * afTi[au8PermuataionMatrix[u8Sector][0]];
	ptSVPWM->fCCRB = ptSVPWM->fUdcCCRval * afTi[au8PermuataionMatrix[u8Sector][1]];
	ptSVPWM->fCCRC = ptSVPWM->fUdcCCRval * afTi[au8PermuataionMatrix[u8Sector][2]];
}

/*********************************** END OF FILE ***********************************/
