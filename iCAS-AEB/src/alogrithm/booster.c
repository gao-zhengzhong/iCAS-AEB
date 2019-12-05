/***********************************************************************
*   Copyright (C) JWD Automotive Co., Ltd.				                     * 
*		All Rights Reserved.          					                           *
*   Department : iCAS SW      									                       *
*   AUTHOR	   :            										                       *
************************************************************************
* Object        : 
* Module        : booster.c
* Instance      : 
* Description   : booster brake algorithm
*-----------------------------------------------------------------------
* Version: v0.1
* Date   : Dec 7,2019 
* Author : Gao zehngzhong
***********************************************************************/
/*-History--------------------------------------------------------------
* Version    Date           Name            Changes and comments
------------------------------------------------------------------------
* 0.1	       Dec 7,2019     Gao Zhengzhong  Initial version
*=====================================================================*/

#include <stdlib.h>
#include <string.h>

#include "adc.h"
#include "booster.h"
#include "pid.h"
#include "pwm.h"

#define BOOSTER_GLOBALS

/**** Definition of variables ****/
BOOSTER_STAT FP32 setCylinderCurve = 0.0f;
BOOSTER_STAT T_BOOSTER tBooster = {0u};

/**** Declaration of functions ****/
BOOSTER_STAT void Booster_AdcSampleToRealSignal(void);
BOOSTER_STAT void Booster_AdcSampleToBrakePedalLocation(void);
BOOSTER_STAT void Booster_AdcSampleToMainCylinderLocation(void);
BOOSTER_STAT void Booster_AdcSampleToMotorCurrent(void);
BOOSTER_STAT void Booster_SettingMainCylinderLocationCurve(void);
BOOSTER_STAT void Booster_MainCylinderLocation_PID(void);

/***********************************************************************
*  Name        : Booster_Init
*  Description : After power on, initiliaze booster alogrithm variable
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Booster_Init(void)
{
	memset(&tBooster, 0, sizeof(tBooster));
	return;
}

/***********************************************************************
*  Name        : Booster_DeInit
*  Description : During running, need initilize booster algorithm variable
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Booster_DeInit(void)
{
	memset(&tBooster, 0, sizeof(tBooster));
	return;
}

/***********************************************************************
*  Name        : Booster_Algorithm
*  Description : Booster control algorithm
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Booster_Algorithm(void)
{
	Booster_AdcSampleToRealSignal();
	Booster_SettingMainCylinderLocationCurve();
	Booster_MainCylinderLocation_PID();
	return;
}

/***********************************************************************
*  Name        : Booster_AdcSampleToRealSignal
*  Description : ADC sample value switch to real signal which will be
*                used in booster control alogrithm
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOSTER_STAT void Booster_AdcSampleToRealSignal(void)
{
	Booster_AdcSampleToBrakePedalLocation();
	Booster_AdcSampleToMainCylinderLocation();
	Booster_AdcSampleToMotorCurrent();
	return;
}

/***********************************************************************
*  Name        : Booster_AdcSampleToBrakePedalLocation
*  Description : Brake pedal location 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOSTER_STAT void Booster_AdcSampleToBrakePedalLocation(void)
{
	FP32 temp;
	const T_ADC *ptr = Adc_SampleData();
	
	/* Limitter processing, lower than the initial position and handle as the initial position, 
	 * higher than the initial position and handle factual displacement */
	if (ptr->brakePedalTrip_Adc[VERIFICATION] <= BRAKE_PEDAL_INIT_LOCATION)
	{
		temp = BRAKE_PEDAL_INIT_LOCATION;
	}
	else
	{
		temp = ptr->brakePedalTrip_Adc[VERIFICATION];
	}
	
	if (temp >= BRAKE_PEDAL_INIT_LOCATION)
	{
		tBooster.brakePedalLocation = (FP32)(((temp - BRAKE_PEDAL_INIT_LOCATION) / SENSOR_RANGE_PARAM) * BRAKE_PEDAL_MECHANICAL_PARAM);		
	}

	return;
}

/***********************************************************************
*  Name        : Booster_AdcSampleToMainCylinderLocation
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOSTER_STAT void Booster_AdcSampleToMainCylinderLocation(void)
{
	FP32 temp;
	const T_ADC *ptr = Adc_SampleData();

	if (ptr->mainCylinderTrip_Adc[VERIFICATION] <= MAIN_CYLINDER_INIT_LOCATION)
	{
		temp = MAIN_CYLINDER_INIT_LOCATION;
	}
	else
	{
		temp = ptr->mainCylinderTrip_Adc[VERIFICATION];
	}
	
	tBooster.mainCylinderLocation = (FP32)(((temp - MAIN_CYLINDER_INIT_LOCATION) / SENSOR_RANGE_PARAM) * MAIN_CYLINDER_MECHANICAL_PARAM);
	return;
}

/***********************************************************************
*  Name        : Booster_AdcSampleToMotorCurrent
*  Description : Motor current value and direction of rotation
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOSTER_STAT void Booster_AdcSampleToMotorCurrent(void)
{
	INT16S temp;
	const T_ADC *ptr = Adc_SampleData();	

/* Motor current closed loop control need to know motor forward or reverse */
#if ( ENABLE == BOOSTER_CURRENT_LOOP_PID )
	temp = ptr->motorCurrent_Adc - MOTOR_CURRENT_THRESHOLD;
#else
	temp = abs(ptr->motorCurrent_Adc - MOTOR_CURRENT_THRESHOLD);
#endif	
	tBooster.motorCurrent = (FP32)((FP32)(temp) / MOTOR_CURRENT_PARAM);
	return;
}

/***********************************************************************
*  Name        : Booster_SettingMainCylinderLocationCurve
*  Description : Setting main cylinder location preset curve
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOSTER_STAT void Booster_SettingMainCylinderLocationCurve(void)
{
	if (tBooster.mainCylinderLocation < MAIN_CYLINDER_LOCATION_STEP1)
	{
		setCylinderCurve = 0.0f;
	}
	else if (tBooster.mainCylinderLocation < MAIN_CYLINDER_LOCATION_STEP2)
	{
		setCylinderCurve = tBooster.mainCylinderLocation + 2.0f;
	}
	else if (tBooster.mainCylinderLocation < MAIN_CYLINDER_LOCATION_STEP3)
	{
		setCylinderCurve = tBooster.mainCylinderLocation * 0.77f + 2.92f;
	}
	else if (tBooster.mainCylinderLocation < MAIN_CYLINDER_LOCATION_STEP4)
	{
		setCylinderCurve = tBooster.mainCylinderLocation * 0.59f + 4.82f;
	}
	else
	{
		setCylinderCurve = tBooster.mainCylinderLocation - 1.6f;
	}
	
	return;
}

/***********************************************************************
*  Name        : Booster_MainCylinderLocation_PID
*  Description : PID control main cylinder location
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOSTER_STAT void Booster_MainCylinderLocation_PID(void)
{
	INT16S incrementalValue;
	BOOSTER_STAT T_PID tPid = {0u};
	
	tPid.Kp = PID_PARA_CYLINDER_LOCATION_KP;
	tPid.Ki = PID_PARA_CYLINDER_LOCATION_KI;
	tPid.Kd = PID_PARA_CYLINDER_LOCATION_KD;
	
	tPid.diviationValue = 10.0f * setCylinderCurve - 10.0f * tPid.actualValue;
		
	if (0.0f == setCylinderCurve)
	{
		tPid.integral = tPid.integral * 0.95f + tPid.diviationValue;
	}
	else
	{
		if (abs(tPid.diviationValue) > 1)
		{
			tPid.integral = tPid.integral * 0.994f + tPid.diviationValue;
		}		
	}
	
	/* Calculate PID main cylinder loacation incremental to control PWM output */
	incrementalValue = tPid.Kp * tPid.diviationValue +
										 tPid.Ki * tPid.integral +
										 tPid.Kd * (tPid.diviationValue - tPid.diviationValuePre);
	
	/* Incremental amplitude limiting processing */
	if (abs(incrementalValue) > PID_PARA_CYLINDER_LOCATION_INCREMENT)
	{
		tBooster.incrementalValue = PID_PARA_CYLINDER_LOCATION_INCREMENT * SIGN(incrementalValue);
	}
	else
	{
		tBooster.incrementalValue = incrementalValue;
	}

	/* Update main cylinder location diviation */
	tPid.diviationValuePre = tPid.diviationValue;
	
	/* Output PWM */
	Pwm_Control(tBooster.incrementalValue);
	
	return;
}

/***********************************************************************
*  Name        : Booster_AlogrithmData
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
const T_BOOSTER* Booster_AlogrithmData(void)
{
	return (&tBooster);
}