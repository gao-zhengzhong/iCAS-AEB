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
#include "adc_sample.h"
#include "FLTD.h"
#include "FLTD_Cfg.h"

/**** Definition of variables ****/
static FLTD_SigFaultType sigFaultType[FLTD_SIG_MAX] = {0};
static FLTD_VOLModeType adcVoltModeSts[FLTD_ADC_MAX] = {0};

/**** Declaration of functions ****/
static void FLTD_SigMonitor(void);
static void FLTD_AdcMonitor(void);
static void FLTD_AdcResultHandle(FLTD_AdcType adcIndex);


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
	FLTD_SigMonitorCfg[sigType].sigPresentFlag = TRUE;
}
void FLTD_SigSetCheckErrorFlag(FLTD_SigType sigType)
{
	FLTD_SigMonitorCfg[sigType].sigCheckErrorFlag = TRUE;
}
void FLTD_SigSetFaultFlag(FLTD_SigType sigType)
{
	FLTD_SigMonitorCfg[sigType].sigFaultFlag = TRUE;
}

static void FLTD_SigMonitor(void)
{
	FLT_U8 sigIndex = 0x00;
	FLTD_SigMonitorCfgType* ptrSigMonitorCfg;
	static FLT_U8 g_u8SigOnMonitorCnt[FLTD_SIG_MAX] = {0,0,0,0,0,0,0};
	static FLT_U8 g_u8SigOffMonitorCnt[FLTD_SIG_MAX] = {0,0,0,0,0,0,0};

	for (sigIndex = 0; sigIndex < FLTD_SIG_MAX; sigIndex++)
	{
		ptrSigMonitorCfg = (FLTD_SigMonitorCfgType*) &FLTD_SigMonitorCfg[sigIndex];

		if (TRUE == ptrSigMonitorCfg->sigPresentFlag)
		{
			ptrSigMonitorCfg->sigPresentFlag = FALSE;
			g_u8SigOffMonitorCnt[sigIndex] = 0;

			if (g_u8SigOnMonitorCnt[sigIndex] > ptrSigMonitorCfg->recoverTime)
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
			if (g_u8SigOffMonitorCnt[sigIndex] > ptrSigMonitorCfg->lostTimeOut)
			{
				sigFaultType[sigIndex] = FLTD_SIG_TIMEOUT;
			}
			else
			{
				g_u8SigOffMonitorCnt[sigIndex]++;
				if (g_u8SigOffMonitorCnt[sigIndex] > ptrSigMonitorCfg->periodTime)
				{
					g_u8SigOnMonitorCnt[sigIndex] = 0;
				}
			}
		}
	}
}

//***************************************************************************************
// @Function      FLTD_SigFaultType FLTD_GetSigFaultType(FLTD_SigType sigtype) 
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
FLTD_SigFaultType FLTD_GetSigFaultType(FLTD_SigType sigType)
{
	return sigFaultType[sigType];
}



//***************************************************************************************
// @Function      static void FLTD_AdcMonitor(void) 
//
//---------------------------------------------------------------------------------------
// @Description   AD samples values is divided into five, in order to stop, low,  
// 				  normal, high, over, etc.
//
//---------- stop_t ----------------- low_t ------  high_t ------------------- over_t ---
//             |         |   lowHyst    |			 |	  highHyst	 |          |   
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
	FLTD_AdcType adcIndex = 0;

	static FLTD_VOLModeType adcVoltModeTemp[FLTD_ADC_MAX] = {0};
	static FLTD_VOLModeType adcVoltModeStsLast[FLTD_ADC_MAX] = {0};
	static FLT_U16 g_u16VoltModeFilterCnt[FLTD_ADC_MAX] = {0};
	FLTD_AdcMonitorCfgType* ptrAdcMonitorCfg;

	/* According to the sample AD value, determine which range it belongs to */
	for (adcIndex = 0; adcIndex < FLTD_ADC_MAX; adcIndex++)
	{
		ptrAdcMonitorCfg = (FLTD_AdcMonitorCfgType*) &FLTD_AdcMonitorCfg[adcIndex];
		
		if ((*ptrAdcMonitorCfg->adcValue >= ptrAdcMonitorCfg->lowThreshold)
			&& (*ptrAdcMonitorCfg->adcValue <= ptrAdcMonitorCfg->highThreshold)) /* low ~ high */
		{
			adcVoltModeTemp[adcIndex] = FLTD_VOL_NORMAL;
		}
		else
		{
			if (*ptrAdcMonitorCfg->adcValue > ptrAdcMonitorCfg->highThreshold) /* high ~  */
			{
				if (*ptrAdcMonitorCfg->adcValue < (ptrAdcMonitorCfg->highThreshold + ptrAdcMonitorCfg->highHyst)) /* high ~ (high + high_hyst) */
				{
					adcVoltModeTemp[adcIndex] = FLTD_VOL_HIGH_HYST;
				}
				else if (*ptrAdcMonitorCfg->adcValue <= ptrAdcMonitorCfg->overThreshold) /* (high + highHyst) ~ over */
				{
					adcVoltModeTemp[adcIndex] = FLTD_VOL_HIGH;
				}
				else																	 /* over ~  */
				{
					adcVoltModeTemp[adcIndex] = FLTD_VOL_OVER;
				}
			}
			else 																/*  ~ low */
			{
				if (*ptrAdcMonitorCfg->adcValue > (ptrAdcMonitorCfg->lowThreshold - ptrAdcMonitorCfg->lowHyst)) /* (low - low_hyst) ~ low */
				{
					adcVoltModeTemp[adcIndex] = FLTD_VOL_LOW_HYST;
				}
				else if (*ptrAdcMonitorCfg->adcValue >= ptrAdcMonitorCfg->stopThreshold) /* stop ~ (low - lowHyst)*/
				{
					adcVoltModeTemp[adcIndex] = FLTD_VOL_LOW;
				}
				else																	/*  ~ stop */
				{
					adcVoltModeTemp[adcIndex] = FLTD_VOL_STOP;
				}
			}
		}

		/* According to the judgment of the above process, filter the judgment result */
		if (adcVoltModeTemp[adcIndex] != adcVoltModeSts[adcIndex])
		{
			if (g_u16VoltModeFilterCnt[adcIndex] < ptrAdcMonitorCfg->filterTime)
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

		/* In both cases in the low or high hysteretic interval, 
		*  the result is normal if the entry is from the normal range;
		*  If the entry is from the corresponding low or high state, 
		*  the low or high state is maintained 
		*/
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

		FLTD_AdcResultHandle(adcIndex);
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
FLTD_VOLModeType FLTD_GetAdcRangeType(FLTD_AdcType adcType)
{
	return adcVoltModeSts[adcType];
}



static void FLTD_AdcResultHandle(FLTD_AdcType adcIndex)
{
	const T_ADC *ptr = Adc_SampleData();	

	switch(adcIndex)
	{
		case FLTD_ADC_ECU_VOLTAGE:
		{
			if(FLTD_VOL_NORMAL == FLTD_GetAdcRangeType(adcIndex))
			{
				//ECU voltage normal
			}
			else if(FLTD_VOL_LOW >= FLTD_GetAdcRangeType(adcIndex))
			{
				//ECU voltage low
			}	
			else 
			{
				//ECU voltage high
			}
			break;
		}
		
		case FLTD_ADC_ENV_TEMPERATURE:
		{
			if(FLTD_VOL_NORMAL == FLTD_GetAdcRangeType(adcIndex))
			{
				//temperature normal
			}	
			else if(FLTD_VOL_HIGH == FLTD_GetAdcRangeType(adcIndex))
			{
				//temperature too low
			}
			else if(FLTD_VOL_LOW == FLTD_GetAdcRangeType(adcIndex))
			{
				//temperature too high
			}
			else
			{
				//temperature sensor error
			}
			break;
		}
		
		case FLTD_ADC_PEDAL_SENSOR_VOLTAGE:
		{
			if(FLTD_VOL_NORMAL == FLTD_GetAdcRangeType(adcIndex))
			{
				//pedal sensor voltage normal
			}
			else if(FLTD_VOL_LOW >= FLTD_GetAdcRangeType(adcIndex))
			{
				//pedal sensor voltage low
			}	
			else 
			{
				//pedal sensor voltage high
			}
			break;
		}
		
		case FLTD_ADC_PEDAL_SENSOR_SIG1:
		case FLTD_ADC_PEDAL_SENSOR_SIG2:
		{
			if((ptr->brakePedalTrip_Adc[0] > (2 * ptr->brakePedalTrip_Adc[1] + 10))
				|| (ptr->brakePedalTrip_Adc[0] < (2 * ptr->brakePedalTrip_Adc[1] - 10)))
			{
				//Check failure
			}
			else
			{
				
			}	
			break;
		}
		
		case FLTD_ADC_MAIN_CYLINDER_VOLTAGE:
		{
			if(FLTD_VOL_NORMAL == FLTD_GetAdcRangeType(adcIndex))
			{
				//main cylinder voltage normal
			}
			else if(FLTD_VOL_LOW >= FLTD_GetAdcRangeType(adcIndex))
			{
				//main cylinder voltage low
			}	
			else 
			{
				//main cylinder voltage high
			}
			break;
		}
		
		case FLTD_ADC_MAIN_CYLINDER_SIG1:
		case FLTD_ADC_MAIN_CYLINDER_SIG2:
		{
			if((ptr->mainCylinderTrip_Adc[0] > (2 * ptr->mainCylinderTrip_Adc[1] + 10))
				|| (ptr->mainCylinderTrip_Adc[0] < (2 * ptr->mainCylinderTrip_Adc[1] - 10)))
			{
				//Check failure
			}
			else
			{
				
			}
			break;
		}
		
		case FLTD_ADC_CURRENT_SENSOR_SIG:
		{
			if(FLTD_VOL_NORMAL == FLTD_GetAdcRangeType(adcIndex))
			{
				//current normal
			}
			else 
			{
				//
			}
			break;
		}
	
		case FLTD_ADC_VLINK_VOLTAGE:
		{
			if(ptr->motorVLinkVoltage_Adc > (ptr->powerVoltage_Adc + 50))
			{
				//vlink voltage too high
			}
			else if(ptr->motorVLinkVoltage_Adc < (ptr->powerVoltage_Adc - 50))
			{
				//vlink voltage too low
			}
			else
			{
			}
			break;
		}
		
		case FLTD_ADC_A_PHASE_VOLTAGE:
		{
			break;
		}
		
		case FLTD_ADC_B_PHASE_VOLTAGE:
		{
			break;
		}
		
#if (1 == PRESSURE_SENSOR_SUPPORT_OR_NOT)
		case FLTD_ADC_PRESSURE_SENSOR_VOLTAGE:
		{
			break;
		}
		
		case FLTD_ADC_PRESSURE_SENSOR_SIG:
		{
			break;
		}
#endif
		
	}
}


