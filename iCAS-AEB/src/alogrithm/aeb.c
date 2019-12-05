/***********************************************************************
*   Copyright (C) JWD Automotive Co., Ltd.				                     * 
*		All Rights Reserved.          					                           *
*   Department : iCAS SW      									                       *
*   AUTHOR	   :            										                       *
************************************************************************
* Object        : 
* Module        : aeb.c
* Instance      : 
* Description   : aeb brake algorithm
*-----------------------------------------------------------------------
* Version: v0.1
* Date   : Dec 8,2019 
* Author : Gao zehngzhong
***********************************************************************/
/*-History--------------------------------------------------------------
* Version    Date           Name            Changes and comments
------------------------------------------------------------------------
* 0.1	       Dec 8,2019     Gao Zhengzhong  Initial version
*=====================================================================*/

#include <stdlib.h>
#include <string.h>

#include "XC23xxBREGS.h"

#include "aeb.h"
#include "adc.h"
#include "booster.h"
#include "can_com.h"
#include "pid.h"
#include "pwm.h"

#define AEB_GLOBALS

/**** Definition of variables ****/
AEB_STAT T_AEB tAeb = {0u};
AEB_STAT INT16U TargetInfo0[4][20];
AEB_STAT INT16U TargetInfo1[4][20];

/**** Declaration of functions ****/
#if( AEB_DET_DISTANCE == ENABLE )
	AEB_STAT void Aeb_DistanceStandby(void);
#endif
#if( AEB_DET_VELOCITY == ENABLE ) 
	AEB_STAT void Aeb_VelocityStandby(void);
#endif
#if( AEB_DET_RRAODRADIUS == ENABLE ) 
	AEB_STAT void Aeb_RoadCurvatureRadiusStandby(void);
#endif
#if( AEB_DET_GEAR == ENABLE )
	AEB_STAT void Aeb_VehicleGearStandby(void);
#endif
#if( AEB_DET_TURNLAMP == ENABLE )
	AEB_STAT void Aeb_TurnLampProhibit(void);
#endif
#if( AEB_DET_STEERING == ENABLE )
	AEB_STAT void Aeb_SteeringProhibit(void);
#endif
#if( AEB_DET_DRIVER_BRAKE == ENABLE )
	AEB_STAT void Aeb_driverBrakeStatusProhibit(void);
#endif
#if( AEB_DET_BRAKE_PEDAL == ENABLE )
	AEB_STAT void Aeb_brakePedalStatusProhibit(void);
#endif

AEB_STAT void Aeb_GetVehicleInfo(void);
AEB_STAT void Aeb_FindDangerTarget(void);
AEB_STAT void Aeb_CalculateFrontSpeed(void);
AEB_STAT void Aeb_CalculateTTC(void);
AEB_STAT void Aeb_JudgeFuncCondition(void);
AEB_STAT void Aeb_FuncControlStatus(void);
AEB_STAT void Aeb_AdcSampleCylinderPressure(void);
AEB_STAT void Aeb_MainCylinderPressure_PID(void);

/***********************************************************************
*  Name        : Aeb_Init
*  Description : After power on, initiliaze aeb alogrithm variable
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Aeb_Init(void)
{
	memset(&tAeb, 0, sizeof(tAeb));
	return;
}

/***********************************************************************
*  Name        : Aeb_DeInit
*  Description : During running, need initilize aeb algorithm variable
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Aeb_DeInit(void)
{
	//memset(&tAeb, 0, sizeof(tAeb));
	
	tAeb.objPressure = 0u;
	return;
}

/***********************************************************************
*  Name        : Aeb_AdcSampleCylinderPressure
*  Description : Main cylinder pressure 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
AEB_STAT void Aeb_AdcSampleCylinderPressure(void)
{
	const T_ADC *ptr = Adc_SampleData();

	tAeb.mainCylinderPressure = (FP32)((FP32)(ptr->mainCylinderPressure_Adc) / MAIN_CYLINDER_PRESSURE_PARAM);
	return;
}

/***********************************************************************
*  Name        : Aeb_Algorithm
*  Description : AEB control algorithm
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Aeb_Algorithm(void)
{
	Aeb_GetVehicleInfo();
	Aeb_FindDangerTarget();
	Aeb_CalculateFrontSpeed();
	Aeb_CalculateTTC();
	
#if( AEB_DET_DISTANCE == ENABLE )	
	Aeb_DistanceStandby();
#endif
#if( AEB_DET_VELOCITY == ENABLE ) 
	Aeb_VelocityStandby();
#endif
#if( AEB_DET_RRAODRADIUS == ENABLE ) 
	Aeb_RoadCurvatureRadiusStandby();
#endif
#if( AEB_DET_GEAR == ENABLE )
	Aeb_VehicleGearStandby();
#endif
#if( AEB_DET_TURNLAMP == ENABLE )
	Aeb_TurnLampProhibit();
#endif
#if( AEB_DET_STEERING == ENABLE )
	Aeb_SteeringProhibit();
#endif
#if( AEB_DET_DRIVER_BRAKE == ENABLE )
	Aeb_driverBrakeStatusProhibit();
#endif
#if( AEB_DET_BRAKE_PEDAL == ENABLE )
	Aeb_brakePedalStatusProhibit();
#endif

	Aeb_JudgeFuncCondition();

	if (FALSE == tAeb.funcDisableStatus)
	{
		Aeb_FuncControlStatus();
	}
	else
	{
		Aeb_DeInit();
	}
	
	return;
}

/***********************************************************************
*  Name        : Aeb_FindDangerTarget
*  Description : Detect danger target through minimum distance 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
AEB_STAT void Aeb_FindDangerTarget(void)
{
	INT8U i;
	
	tAeb.targetLongtitudeDistance = AEB_DISTANCE_MAX;
	
	/* Find the target with the minimum longtitude distance from the vehicle, and get target information */
	for (i=0u; i<20u; i++)
	{
		if (tAeb.targetLongtitudeDistance > TargetInfo1[0][i])
		{
			tAeb.targetLongtitudeDistance = TargetInfo1[0][i];                        // uint:m * 100
			tAeb.targetLateralDistance = TargetInfo1[1][i];                           // uint:m * 100			
			tAeb.targetLongtitudeVelocity = ((FP32)TargetInfo1[2][i] * 18.0f) / 5.0f; // uint:km/h * 10
			tAeb.targetLateralVelocity = ((FP32)TargetInfo1[3][i] * 18.0f) / 5.0f;    // uint:km/h * 10
		}
	}
	
	return;
}

/***********************************************************************
*  Name        : Aeb_GetVehicleInfo
*  Description : Switch target and vehicle information, will be used in alogrithm
*  Parameter   : None
*  Returns     : None
***********************************************************************/
AEB_STAT void Aeb_GetVehicleInfo(void)
{
	const T_CAN_COM *ptr = CanCom_VehicleData();
	
	/* vehicle information */
	tAeb.driverBrakeStatus = DIO_SIGNAL_INPUT_BRAKE_STATUS();
	tAeb.vehicleVelocity = (FP32)(ptr->tVehicle.speed) / 10.0f;  // uint:km/h 
	tAeb.vehicleAcceleration = (FP32)(ptr->tVehicle.accelerationY) + 0.0f;  // uint:m/s^2 
	
	tAeb.turnLamp = (INT8U)(ptr->tVehicle.turnLamp);
	tAeb.gearPosition = (INT8U)(ptr->tVehicle.gear);
	tAeb.steeringAngle = (INT16S)(ptr->tVehicle.steeringAngle);
	tAeb.roadCurvatureRadius = (INT16U)(ptr->tVehicle.roadCurvatureRadius);
		
	/* target information */
	tAeb.relativeVelocity = (FP32)(ptr->tTarget.longtitudeVelocity - ptr->tVehicle.speed) / 10.0f;  // uint:km/h 
	tAeb.relativeDistance = (FP32)(ptr->tTarget.longtitudeDistance) / 100.0f;  // uint:m
	
	return;
}

/***********************************************************************
*  Name        : Aeb_CalculateFrontSpeed
*  Description : Calculate front speed, judge if or not have dangerous object
*  Parameter   : None
*  Returns     : None
***********************************************************************/
AEB_STAT void Aeb_CalculateFrontSpeed(void)
{
	const T_CAN_COM *ptr = CanCom_VehicleData();
	
	/* 200 means no dangerous target is in front */
	if (ptr->tTarget.longtitudeDistance > AEB_DISTANCE_MAX)
	{
		tAeb.speedFront = 200u;
	}
	else
	{
		tAeb.speedFront = tAeb.vehicleVelocity + tAeb.relativeVelocity;
	}
	
	return;
}

/***********************************************************************
*  Name        : Aeb_CalculateTTC
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
AEB_STAT void Aeb_CalculateTTC(void)
{
	FP32 temp;
	
	/* A positive relative speed indicates that the target vehicle is faraway */ 
	if (tAeb.relativeVelocity >= 0.0f)
	{
		tAeb.ttc = AEB_TTC_NO_WARNING;
	}
	else
	{
		/* A negative relative speed indicates that the target vehicle is approaching */
		temp = (FP32)(abs(tAeb.relativeDistance / tAeb.relativeVelocity));
		tAeb.ttc = (temp >= AEB_TTC_NO_WARNING) ? AEB_TTC_NO_WARNING : temp;
	}
	
	return;
}
#if( AEB_DET_DISTANCE == ENABLE )
/***********************************************************************
*  Name        : Aeb_DistanceStandby
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
AEB_STAT void Aeb_DistanceStandby(void)
{
	AEB_STAT INT8U standbyCount = 0u;
	
	/* AEB work distance conditions: < 80m */
	if (FALSE == tAeb.restrictCondition[DISTANCE])
	{
		/* relative distance > 80m, AEB not work */
		if (tAeb.relativeDistance > AEB_RELATIVE_DISTANCE_THRESHOLD)
		{
			standbyCount++;
			if (standbyCount >= AEB_STANDBY_TIMEOUT)
			{
				standbyCount = AEB_STANDBY_TIMEOUT;
				tAeb.restrictCondition[DISTANCE] = TRUE;
			}
		}
		else
		{
			standbyCount = 0u;
		}
	}
	else
	{
		if (tAeb.relativeDistance <= AEB_RELATIVE_DISTANCE_THRESHOLD)
		{
			standbyCount = 0u;
			tAeb.restrictCondition[DISTANCE] = FALSE;
		}
	}
	
	return;
}
#endif
#if( AEB_DET_VELOCITY == ENABLE ) 
/***********************************************************************
*  Name        : Aeb_VelocityStandby
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
AEB_STAT void Aeb_VelocityStandby(void)
{
	AEB_STAT INT8U standbyCount = 0u;
	
	/* AEB work velocity conditions: > 5km/h and < 70km/h */
	if (FALSE == tAeb.restrictCondition[VELOCITY])
	{
		/* velocity <= 5km/h or >= 70km/h, AEB not work */
		if ((tAeb.vehicleVelocity <= AEB_VELOCITY_LOWER) ||
			  (tAeb.vehicleVelocity >= AEB_VELOCITY_UPPER))
		{
			standbyCount++;
			if (standbyCount >= AEB_STANDBY_TIMEOUT)
			{
				standbyCount = AEB_STANDBY_TIMEOUT;
				tAeb.restrictCondition[VELOCITY] = TRUE;
			}
		}
		else
		{
			standbyCount = 0u;
		}
	}
	else
	{
		if ((tAeb.vehicleVelocity > AEB_VELOCITY_LOWER) &&
			  (tAeb.vehicleVelocity < AEB_VELOCITY_UPPER))
		{
			standbyCount = 0u;
			tAeb.restrictCondition[VELOCITY] = FALSE;
		}
	}
	
	return;
}
#endif
#if( AEB_DET_RRAODRADIUS == ENABLE ) 
/***********************************************************************
*  Name        : Aeb_RoadCurvatureRadiusStandby
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
AEB_STAT void Aeb_RoadCurvatureRadiusStandby(void)
{
	AEB_STAT INT8U standbyCount = 0u;
	
	/* AEB work road conditions must be straight line */
	if (FALSE == tAeb.restrictCondition[ROAD_RADIUS])
	{
		/* road of curvature of radius <= 250m, AEB not work */
		if (tAeb.roadCurvatureRadius <= AEB_ROAD_RADIUS_CURVATURE)
		{
			standbyCount++;
			if (standbyCount >= AEB_STANDBY_TIMEOUT)
			{
				standbyCount = AEB_STANDBY_TIMEOUT;
				tAeb.restrictCondition[ROAD_RADIUS] = TRUE;
			}
		}
		else
		{
			standbyCount = 0u;
		}
	}
	else
	{
		if (tAeb.roadCurvatureRadius > AEB_ROAD_RADIUS_CURVATURE)
		{
			standbyCount = 0u;
			tAeb.restrictCondition[ROAD_RADIUS] = FALSE;		
		}
	}
	
	return;
}
#endif
#if( AEB_DET_GEAR == ENABLE )
/***********************************************************************
*  Name        : Aeb_VehicleGearStandby
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
AEB_STAT void Aeb_VehicleGearStandby(void)
{
	AEB_STAT INT8U standbyCount = 0u;
	
	/* AEB work vehicle gear conditions must be D position */	
	if (FALSE == tAeb.restrictCondition[GEAR])
	{
		if (D_Gear != tAeb.gearPosition)
		{
			standbyCount++;
			if (standbyCount >= AEB_STANDBY_TIMEOUT)
			{
				standbyCount = AEB_STANDBY_TIMEOUT;
				tAeb.restrictCondition[GEAR] = TRUE;
			}	
		}
		else
		{
			standbyCount = 0u;
		}
	}
	else
	{
		if (D_Gear == tAeb.gearPosition)
		{
			standbyCount = 0u;
			tAeb.restrictCondition[GEAR] = FALSE;
		}
	}

	return;
}
#endif
#if( AEB_DET_TURNLAMP == ENABLE )
/***********************************************************************
*  Name        : Aeb_TurnLampProhibit
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
AEB_STAT void Aeb_TurnLampProhibit(void)
{
	AEB_STAT INT8U prohibitCount = 0u;
	
	/* left or right or both turn lamp is on indicate the driver has been intervene vehicle,
	 * the AEB will prohibit function */
	if (FALSE == tAeb.restrictCondition[TURN_LAMP])
	{
		if (EXTINCT != tAeb.turnLamp)
		{
			prohibitCount++;
			if (prohibitCount >= AEB_PROHIBIT_TIMEOUT)
			{
				prohibitCount = AEB_PROHIBIT_TIMEOUT;
				tAeb.restrictCondition[TURN_LAMP] = TRUE;
			}
		}
		else
		{
			prohibitCount = 0u;
		}
	}
	else
	{
		if (EXTINCT == tAeb.turnLamp)
		{
			prohibitCount = 0u;
			tAeb.restrictCondition[TURN_LAMP] = FALSE;
		}
	}
	
	return;
}
#endif
#if( AEB_DET_STEERING == ENABLE )
/***********************************************************************
*  Name        : Aeb_SteeringProhibit
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
AEB_STAT void Aeb_SteeringProhibit(void)
{
	AEB_STAT INT8U prohibitCount = 0u;

	/* the driver turns the steering wheel is on indicate the driver has been intervene vehicle,
	 * the AEB will prohibit function */	
	if (FALSE == tAeb.restrictCondition[STEERING])
	{
		if ((tAeb.steeringAngle > AEB_STEERING_POSITIVE_ANGLE) || (tAeb.steeringAngle < AEB_STEERING_NEGATIVE_ANGLE))
		{
			prohibitCount++;
			if (prohibitCount >= AEB_PROHIBIT_TIMEOUT)
			{
				prohibitCount = AEB_PROHIBIT_TIMEOUT;
				tAeb.restrictCondition[STEERING] = TRUE;
			}
		}
		else
		{
			prohibitCount = 0u;
		}
	}
	else
	{
		if ((tAeb.steeringAngle <= AEB_STEERING_POSITIVE_ANGLE) || (tAeb.steeringAngle >= AEB_STEERING_NEGATIVE_ANGLE))
		{
			prohibitCount = 0u;
			tAeb.restrictCondition[STEERING] = FALSE;			
		}
	}
	
	return;
}
#endif
#if( AEB_DET_DRIVER_BRAKE == ENABLE )
/***********************************************************************
*  Name        : Aeb_driverBrakeStatusProhibit
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
AEB_STAT void Aeb_driverBrakeStatusProhibit(void)
{
	AEB_STAT INT8U prohibitCount = 0u;

	/* the driver apply braking is on indicate the driver has been intervene vehicle,
	 * the AEB will prohibit function */	
	if (FALSE == tAeb.restrictCondition[DRIVER_BRAKE])
	{
		if (TRUE == tAeb.driverBrakeStatus)
		{
			prohibitCount++;
			if (prohibitCount >= AEB_PROHIBIT_TIMEOUT)
			{
				prohibitCount = AEB_PROHIBIT_TIMEOUT;
				tAeb.restrictCondition[DRIVER_BRAKE] = TRUE;
			}
		}
		else
		{
			prohibitCount = 0u;
		}
	}
	else
	{
		if (FALSE == tAeb.driverBrakeStatus)
		{
			prohibitCount = 0u;
			tAeb.restrictCondition[DRIVER_BRAKE] = FALSE;
		}
	}
	
	return;
}
#endif
#if( AEB_DET_BRAKE_PEDAL == ENABLE )
/***********************************************************************
*  Name        : Aeb_brakePedalStatusProhibit
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
AEB_STAT void Aeb_brakePedalStatusProhibit(void)
{
	AEB_STAT INT8U prohibitCount = 0u;
	const T_BOOSTER *ptr = Booster_AlogrithmData();

	/* the driver wipes off the brake pedal is on indicate the driver has been intervene vehicle,
	 * the AEB will prohibit function */	
	if (FALSE == tAeb.restrictCondition[BRAKE_PEDAL])
	{
		/* brake pedal travel more than initialize postion, indicate brake pedal be wiped off by driver */
		if (ptr->brakePedalLocation > BRAKE_PEDAL_INIT_LOCATION)
		{
			prohibitCount++;
			if (prohibitCount >= AEB_PROHIBIT_TIMEOUT)
			{
				prohibitCount = AEB_PROHIBIT_TIMEOUT;
				tAeb.restrictCondition[BRAKE_PEDAL] = TRUE;
			}
		}
		else
		{
			prohibitCount = 0u;
		}
	}
	else
	{
		if (ptr->brakePedalLocation <= BRAKE_PEDAL_INIT_LOCATION)
		{
			prohibitCount = 0u;
			tAeb.restrictCondition[BRAKE_PEDAL] = FALSE;
		}
	}
	
	return;
}
#endif
/***********************************************************************
*  Name        : Aeb_JudgeFuncCondition
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
AEB_STAT void Aeb_JudgeFuncCondition(void)
{
	INT8U i;
	
	/* judge AEB function disable condition */
	tAeb.funcDisableStatus = FALSE;
	for (i=0u; i<MAX_RESTRICT_CONDITION; i++)
	{
		tAeb.funcDisableStatus |= tAeb.restrictCondition[i];
	}
	
	return;
}

/***********************************************************************
*  Name        : Aeb_FuncControlStatus
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
AEB_STAT void Aeb_FuncControlStatus(void)
{
	Aeb_MainCylinderPressure_PID();
	return;
}

/***********************************************************************
*  Name        : Aeb_MainCylinderPressure_PID
*  Description : PID control main cylinder pressure
*  Parameter   : None
*  Returns     : None
***********************************************************************/
AEB_STAT void Aeb_MainCylinderPressure_PID(void)
{
	INT16S incrementalValue;
	AEB_STAT T_PID tPid = {0u};
	
	tPid.Kp = PID_PARA_CYLINDER_LOCATION_KP;
	tPid.Ki = PID_PARA_CYLINDER_LOCATION_KI;
	tPid.Kd = PID_PARA_CYLINDER_LOCATION_KD;

	Aeb_AdcSampleCylinderPressure();
	tPid.actualValue = tAeb.mainCylinderPressure;
	tPid.settingValue = tAeb.objPressure;
	
	tPid.diviationValue = tPid.settingValue - tPid.actualValue * 10.0f;
	
	if (abs(tPid.diviationValue) > 1)
	{
		tPid.integral = tPid.integral * 0.994 + tPid.diviationValue;
	}
	
	/* Calculate PID main cylinder pressure incremental to control PWM output */
	incrementalValue = tPid.Kp * tPid.diviationValue +
										 tPid.Ki * tPid.integral +
										 tPid.Kd * (tPid.diviationValue - tPid.diviationValuePre);
		
	/* Incremental amplitude limiting processing */
	if (abs(incrementalValue) > PID_PARA_CYLINDER_PRESSURE_INCREMENT)
	{
		tAeb.incrementalValue = PID_PARA_CYLINDER_PRESSURE_INCREMENT * SIGN(incrementalValue);
	}
	else
	{
		tAeb.incrementalValue = incrementalValue;
	}
	
	/* Update main cylinder location diviation */
	tPid.diviationValuePre = tPid.diviationValue;
	
	/* Output PWM */
	Pwm_Control(tAeb.incrementalValue);	
	
	return;
}