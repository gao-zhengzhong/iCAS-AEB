/***********************************************************************
*   Copyright (C) JWD Automotive Co., Ltd.				               * 
*		All Rights Reserved.          					               *
*   Department : iCAS SW      									       *
*   AUTHOR	   :            										   *
************************************************************************
* Object        : 
* Module        : FLTD.c
* Instance      : 
* Description   :  fault diagnosis
*-----------------------------------------------------------------------
* Version: v0.1
* Date   : Nov 12,2019 
* Author : Zhu jinfeng
***********************************************************************/
/*-History--------------------------------------------------------------
* Version    Date           Name            Changes and comments
------------------------------------------------------------------------
* 0.1	    Nov 12,2019     Zhu jinfeng     Initial version
*=====================================================================*/

#define  FLTD_C_
#include "string.h"
#include "MAIN.h"
#include "adc.h"
#include "FLTD_Types.h"
#include "FLTD.h"
#include "FLTD_Cfg.h"

/**** Definition of variables ****/
static FLTD_SigFaultType sigFaultType[FLTD_SIG_MAX];
static FLTD_VOLModeType adcVoltModeSts[FLTD_ADC_MAX];

/**** Declaration of functions ****/
static void FLTD_SigMonitor(void);
static void FLTD_AdcMonitor(void);


//***************************************************************************************
// @Function      void FLTD_Init(void)
//
//---------------------------------------------------------------------------------------
// @Description   FLTD module initialization function.Perform initialization as needed.
//
//---------------------------------------------------------------------------------------
// @Returnvalue   none 
//
//---------------------------------------------------------------------------------------
// @Parameters    none
//
//---------------------------------------------------------------------------------------
// @Date          2019/11/7
//
//***************************************************************************************
void FLTD_Init(void)
{
	memset(&sigFaultType, 0, FLTD_SIG_MAX);
	memset(&adcVoltModeSts, 0, FLTD_ADC_MAX);	
}

//***************************************************************************************
// @Function      void FLTD_CyclicProcess(void)
//
//---------------------------------------------------------------------------------------
// @Description   FLTD module cycle task function. AD sampling value range judgment and 
//				  signal fault processing are performed according to the scheduling cycle.
//
//---------------------------------------------------------------------------------------
// @Returnvalue   none 
//
//---------------------------------------------------------------------------------------
// @Parameters    none
//
//---------------------------------------------------------------------------------------
// @Date          2019/11/7
//
//***************************************************************************************
void FLTD_CyclicProcess(void)
{
	FLTD_SigMonitor();
	FLTD_AdcMonitor();
}



void FLTD_SigSetPresentFlag(FLTD_SigType sigType)
{
	FLTD_SigMonitorCfg[sigType].SigPresentFlag = TRUE;
}
void FLTD_SigSetCheckErrorFlag(FLTD_SigType sigType)
{
	FLTD_SigMonitorCfg[sigType].SigCheckErrorFlag = TRUE;
}
void FLTD_SigSetFaultFlag(FLTD_SigType sigType)
{
	FLTD_SigMonitorCfg[sigType].SigFaultFlag = TRUE;
}

static void FLTD_SigMonitor(void)
{
	FLTD_U8 sigIndex = 0x00;
	FLTD_SigMonitorCfgType* ptrSigMonitorCfg;
	static FLTD_U8 g_u8SigOnMonitorCnt[FLTD_SIG_MAX];
	static FLTD_U8 g_u8SigOffMonitorCnt[FLTD_SIG_MAX];

	for (sigIndex = 0; sigIndex < FLTD_SIG_MAX; sigIndex++)
	{
		ptrSigMonitorCfg = (FLTD_SigMonitorCfgType*) &FLTD_SigMonitorCfg[sigIndex];

		if (TRUE == ptrSigMonitorCfg->SigPresentFlag)
		{
			ptrSigMonitorCfg->SigPresentFlag = FALSE;
			g_u8SigOffMonitorCnt[sigIndex] = 0x00;

			if (g_u8SigOnMonitorCnt[sigIndex] > ptrSigMonitorCfg->recovertime)
			{
				sigFaultType[sigIndex] = FLTD_SIG_NORMAL;
			}
			else
			{
				g_u8SigOnMonitorCnt[sigIndex]++;
			}
		}
		else
		{
			if (g_u8SigOffMonitorCnt[sigIndex] > ptrSigMonitorCfg->losttimeOut)
			{
				sigFaultType[sigIndex] = FLTD_SIG_TIMEOUT;
			}
			else
			{
				g_u8SigOffMonitorCnt[sigIndex]++;
				if (g_u8SigOffMonitorCnt[sigIndex] > ptrSigMonitorCfg->periodtime)
				{
					g_u8SigOnMonitorCnt[sigIndex] = 0;
				}
			}
		}
	}
}

FLTD_SigFaultType FLTD_GetSigFaultType(FLTD_SigType sigtype)
{
	return sigFaultType[sigtype];
}



//***************************************************************************************
// @Function      static void FLTD_AdcMonitor(void) 
//
//---------------------------------------------------------------------------------------
// @Description   AD samples values is divided into five, in order to stop, low,  
// 				  normal, high, over, etc.
//
//---------- stop_t ----------------- low_t ------  high_t ------------------- over_t ---
//             |         |   low_hyst   |			 |	  high_hyst	 |          |   
//			   |	     |			    |			 |				 |		    |
//     stop	   |   low      low/normal  |  normal	 | 	 normal/high     high   |	over
//---------------------------------------------------------------------------------------
// @Returnvalue   None
//
//---------------------------------------------------------------------------------------
// @Parameters    None
//
//---------------------------------------------------------------------------------------
// @Date          2019/11/7
//
//***************************************************************************************
static void FLTD_AdcMonitor(void)
{
	FLTD_U8 adcIndex = 0x00;

	static FLTD_VOLModeType adcVoltModeTemp[FLTD_ADC_MAX];
	static FLTD_VOLModeType adcVoltModeStsLast[FLTD_ADC_MAX];
	static FLTD_U16 g_u16VoltModeFilterCnt[FLTD_ADC_MAX];
	FLTD_AdcMonitorCfgType* ptrAdcMonitorCfg;

	for (adcIndex = 0; adcIndex < FLTD_ADC_MAX; adcIndex++)
	{
		ptrAdcMonitorCfg = (FLTD_AdcMonitorCfgType*) &FLTD_AdcMonitorCfg[adcIndex];
		
		if ((*ptrAdcMonitorCfg->adcValue >= ptrAdcMonitorCfg->low_threshold)
				&& (*ptrAdcMonitorCfg->adcValue <= ptrAdcMonitorCfg->high_threshold)) /* low ~ high */
		{
			adcVoltModeTemp[adcIndex] = FLTD_VOL_NORMAL;
		}
		else
		{
			if (*ptrAdcMonitorCfg->adcValue > ptrAdcMonitorCfg->high_threshold)
			{
				if (*ptrAdcMonitorCfg->adcValue < (ptrAdcMonitorCfg->high_threshold + ptrAdcMonitorCfg->high_hyst)) /* high ~ (high + high_hyst) */
				{
					adcVoltModeTemp[adcIndex] = FLTD_VOL_HIGH_HYST;
				}
				else if (*ptrAdcMonitorCfg->adcValue <= ptrAdcMonitorCfg->over_threshold) /* (high + high_hyst) ~ over */
				{
					adcVoltModeTemp[adcIndex] = FLTD_VOL_HIGH;
				}
				else																	 /*  over ~ */
				{
					adcVoltModeTemp[adcIndex] = FLTD_VOL_OVER;
				}
			}
			else
			{
				if (*ptrAdcMonitorCfg->adcValue > (ptrAdcMonitorCfg->low_threshold - ptrAdcMonitorCfg->low_hyst)) /* (low - low_hyst) ~ low */
				{
					adcVoltModeTemp[adcIndex] = FLTD_VOL_LOW_HYST;
				}
				else if (*ptrAdcMonitorCfg->adcValue >= ptrAdcMonitorCfg->stop_threshold) /* stop ~ (low - low_hyst)*/
				{
					adcVoltModeTemp[adcIndex] = FLTD_VOL_LOW;
				}
				else																	 /* ~ stop */
				{
					adcVoltModeTemp[adcIndex] = FLTD_VOL_STOP;
				}
			}
		}

		if (adcVoltModeTemp[adcIndex] != adcVoltModeSts[adcIndex])
		{
			if (g_u16VoltModeFilterCnt[adcIndex] < ptrAdcMonitorCfg->filtertime)
			{
				g_u16VoltModeFilterCnt[adcIndex]++;
			}
			else
			{
				adcVoltModeSts[adcIndex] = adcVoltModeTemp[adcIndex];
				g_u16VoltModeFilterCnt[adcIndex] = 0;
			}
		}
		else
		{
			g_u16VoltModeFilterCnt[adcIndex] = 0;
		}

		if (FLTD_VOL_LOW_HYST == adcVoltModeSts[adcIndex])
		{
			if ((FLTD_VOL_LOW == adcVoltModeStsLast[adcIndex])
				|| (FLTD_VOL_STOP == adcVoltModeStsLast[adcIndex]))
			{
				adcVoltModeSts[adcIndex] = FLTD_VOL_LOW;
			}
			else
			{
				adcVoltModeSts[adcIndex] = FLTD_VOL_NORMAL;
			}
		}
		else if (FLTD_VOL_HIGH_HYST == adcVoltModeSts[adcIndex])
		{
			if ((FLTD_VOL_HIGH == adcVoltModeStsLast[adcIndex])
				|| (FLTD_VOL_OVER == adcVoltModeStsLast[adcIndex]))
			{
				adcVoltModeSts[adcIndex] = FLTD_VOL_HIGH;
			}
			else
			{
				adcVoltModeSts[adcIndex] = FLTD_VOL_NORMAL;
			}
		}
		else
		{

		}

		adcVoltModeStsLast[adcIndex] = adcVoltModeSts[adcIndex];

	}
}

//***************************************************************************************
// @Function      FLTD_VOLModeType FLTD_GetAdcRangeType(FLTD_AdcType adctype) 
//
//---------------------------------------------------------------------------------------
// @Description   Get the range of AD sampling value of each channel.
//
//---------------------------------------------------------------------------------------
// @Returnvalue   adcVoltModeSts: 
//				  The range of AD values for a particular channel, In the following
//				  FLTD_VOL_NORMAL,FLTD_VOL_STOP,FLTD_VOL_LOW,FLTD_VOL_HIGH.
//---------------------------------------------------------------------------------------
// @Parameters    adctype:
//				  Enumeration of each AD channel.
//
//---------------------------------------------------------------------------------------
// @Date          2019/11/7
//
//***************************************************************************************
FLTD_VOLModeType FLTD_GetAdcRangeType(FLTD_AdcType adctype)
{
	return adcVoltModeSts[adctype];
}


