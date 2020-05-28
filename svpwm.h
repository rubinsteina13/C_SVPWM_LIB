/**
  ***********************************************************************************
  * @file    svpwm.h
  * @author  Serhii Yatsenko [royalroad1995@gmail.com]
  * @version V1.0
  * @date    May-2020
  * @brief   This file contains the type definition of data structure and function
  *	     prototypes for implementation the SVPWM - Space-Vector Pulse Width 
  *	     Modulation
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

/* Define to prevent recursive inclusion ------------------------------------------*/
#ifndef __SVPWM_H__
#define __SVPWM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------------*/
#include <stdint.h>
#include <math.h>

/* Exported types -----------------------------------------------------------------*/

/** 
  * @brief SVPWM module data input type
  */
typedef enum
{
	AlBe	= 0x00U,		// Alpha-Beta component input
	UsAng	= 0x01U			// Magnitude-Angle component input
} tInType;

/** 
  * @brief "SVPWM Module" data structure
  */
typedef struct sSVPWM
{
// Inputs:
	tInType	enInType;		// SVPWM module data input type
	float	fUdc;			// DC Link voltage, Volts
	float	fUdcCCRval;		// Counter compare register value which is
																		// equivalent to full DC Link voltage
	// enInType == AlBe:
	float	fUal;			// Alpha input, Volts
	float	fUbe;			// Beta input, Volts
	// enInType == UsAng:
	float	fUs;			// Magnitude input, Volts (enInType == UsAng)
	float	fAngRad;		// Angle input, Rad (enInType == UsAng)
// Outputs:
	float	fCCRA;			// Counter compare register A value
	float	fCCRB;			// Counter compare register B value
	float	fCCRC;			// Counter compare register C value
// Functions:
	void (*m_calc)(struct sSVPWM*);	// Pointer to SVPWM calculation function
} tSVPWM;

/* Exported constants -------------------------------------------------------------*/

/** 
  * @brief Initialization constant with defaults for user variables
  *	   with "tSVPWM" type
  */
#define SVPWM_DEFAULTS {		\
	.enInType	= AlBe,		\
	.fUal		= 0.0f,		\
	.fUbe		= 0.0f,		\
	.fUs		= 0.0f,		\
	.fAngRad	= 0.0f,		\
	.fUdc		= 0.0f,		\
	.fUdcCCRval	= 0.0f,		\
	.fCCRA		= 0.0f,		\
	.fCCRB		= 0.0f,		\
	.fCCRC		= 0.0f,		\
	.m_calc		= tSVPWM_calc	\
}

/* Exported macro -----------------------------------------------------------------*/
/* Exported functions -------------------------------------------------------------*/

/* SVPWM Duty Cycles calculation function prototype ********************************/
void tSVPWM_calc(tSVPWM*);

#ifdef __cplusplus
}
#endif

#endif /* __SVPWM_H__ */

/*********************************** END OF FILE ***********************************/
