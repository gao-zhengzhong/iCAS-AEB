/***********************************************************************
*   Copyright (C) JWD Automotive Co., Ltd.				               * 
*	All Rights Reserved.          					                   *
*   Department : iCAS SW      									       *
*   AUTHOR	   :            										   *
************************************************************************
* Object        : 
* Module        : apa.c
* Instance      : 
* Description   : APA brake algorithm
*-----------------------------------------------------------------------
* Version: v0.1
* Date   : Dec 7,2019 
* Author : Gao zehngzhong
***********************************************************************/
/*-History--------------------------------------------------------------
* Version    Date           Name            Changes and comments
------------------------------------------------------------------------
* 0.1	     Dec 7,2019     Gao Zhengzhong  Initial version
*=====================================================================*/

#include <stdlib.h>
#include <string.h>

#include "wire_control.h"
#include "adc_sample.h"
#include "Busline.h"
#include "pid.h"

#define WIRE_CONTROL_GLOBALS

/**** Definition of variables ****/
WIRE_CONTROL_STAT T_WIRE_CONTROL tWireControl = {0u};

/**** Declaration of functions ****/
WIRE_CONTROL_STAT WireControl_ConversionObjPressure(void);


/***********************************************************************
*  Name        : WireControl_Init
*  Description : After power on, initiliaze wire control alogrithm variable
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void WireControl_Init(void)
{
	memset(&tWireControl, 0, sizeof(tWireControl));
	return;
}

/***********************************************************************
*  Name        : WireControl_DeInit
*  Description : During running, need initilize wire control algorithm variable
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void WireControl_DeInit(void)
{
	memset(&tWireControl, 0, sizeof(tWireControl));
	return;
}

/***********************************************************************
*  Name        : WireControl_Algorithm
*  Description : Wire brake control algorithm
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void WireControl_Algorithm(void)
{
	const T_ADC_APP *ptr_adc = AdcApp_SampleData();

	if (TRUE == APA_BrakeFlag)
	{
		tWireControl.APARequestFeedback = TRUE;

		/* If APA emergency brake, apply maximum parking pressure, else
		 * according to the brake percentage to apply. */
		if (APA_EMERGENCY_BRAKE_VALID == APA_EmgBrakeFlag)
		{
			Pid_PressureClosedLoopControl(APA_EMERGENCY_BRAKE_PRESSURE);
		}
		else
		{
			WireControl_ConversionObjPressure();
			Pid_PressureClosedLoopControl(tWireControl.mainCylinderObjPressure);
		}
		
		/* Feedback the actual main cylinder pressure and limit the amplitude. */
		if (ptr_adc->mainCylinderPressure >= APA_BRAKE_PRESSURE_UPPER_LIMIT)
		{
			tWireControl.APApressureFeedback = APA_BRAKE_PRESSURE_UPPER_LIMIT;
		}
		else
		{
			if (ptr_adc->mainCylinderPressure <= 0u)
			{
				tWireControl.APApressureFeedback = 0u;
			}
			else
			{
				tWireControl.APApressureFeedback = ptr_adc->mainCylinderPressure;
			}
		}
	}
	else
	{
		WireControl_DeInit();	
	}

	return;
}

/***********************************************************************
*  Name        : WireControl_ConversionObjPressure
*  Description : APA function get percentage to conversion brake main
*                cylinder control object pressure.
*  Parameter   : None
*  Returns     : None
***********************************************************************/
WIRE_CONTROL_STAT WireControl_ConversionObjPressure(void)
{
	/* APA_TargetPrs signal from CAN, represent the percentage of brake pressure 0~100%, 
	 * corresponding main cylinder object pressure 0~2000kpa. */
	tWireControl.mainCylinderObjPressure = APA_TargetPrs * APA_EMERGENCY_BRAKE_PRESSURE / 100u;
	return;
}

/***********************************************************************
*  Name        : WireControl_AlogrithmData
*  Description : Wire Control brake control alogrithm data
*  Parameter   : None
*  Returns     : APA brake control alogrithm data structure access address
***********************************************************************/
const T_WIRE_CONTROL* WireControl_AlogrithmData(void)
{
	return (&tWireControl);
}	

