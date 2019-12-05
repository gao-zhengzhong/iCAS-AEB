/***********************************************************************
*   Copyright (C) JWD Automotive Co., Ltd.				                     * 
*		All Rights Reserved.          					                           *
*   Department : iCAS SW      									                       *
*   AUTHOR	   :            										                       *
************************************************************************
* Object        : 
* Module        : aeb.h
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

#ifndef _AEB_H_
#define _AEB_H_

#include "Para_Fun_Type.h"
#include "rtwtypes.h"

#ifdef   AEB_GLOBALS
	#define  AEB_EXT
#else
	#define  AEB_EXT  extern
#endif
	
#ifdef   AEB_GLOBALS
	#define  AEB_STAT
#else
	#define  AEB_STAT static
#endif	

/* AEB function switch setting */
#ifndef AEB_DET_DISTANCE
	#define AEB_DET_DISTANCE ENABLE
#endif

#ifndef AEB_DET_VELOCITY
	#define AEB_DET_VELOCITY ENABLE
#endif

#ifndef AEB_DET_RRAODRADIUS
	#define AEB_DET_RRAODRADIUS ENABLE
#endif

#ifndef AEB_DET_GEAR
	#define AEB_DET_GEAR ENABLE
#endif

#ifndef AEB_DET_TURNLAMP
	#define AEB_DET_TURNLAMP ENABLE
#endif

#ifndef AEB_DET_STEERING
	#define AEB_DET_STEERING ENABLE
#endif

#ifndef AEB_DET_DRIVER_BRAKE
	#define AEB_DET_DRIVER_BRAKE ENABLE
#endif

#ifndef AEB_DET_BRAKE_PEDAL
	#define AEB_DET_BRAKE_PEDAL ENABLE
#endif

/**** Definition of macro ****/
#define AEB_STANDBY_TIMEOUT     (30u)
#define AEB_PROHIBIT_TIMEOUT    (30u)

#define AEB_DISTANCE_MAX      (12000u) // uint:m * 100

#define AEB_RELATIVE_DISTANCE_THRESHOLD  (80.0f)

#define AEB_VELOCITY_LOWER    (5.0f)
#define AEB_VELOCITY_UPPER    (70.0f)

#define AEB_ROAD_RADIUS_CURVATURE  (250u)

#define AEB_TTC_NO_WARNING     (20.0f)

#define AEB_STEERING_POSITIVE_ANGLE  (10)
#define AEB_STEERING_NEGATIVE_ANGLE  (-10)

#define MAIN_CYLINDER_PRESSURE_PARAM    (51.2f)

/**** Definition of data structure ****/
typedef enum{
	X_Gear,
	P_Gear,
	R_Gear,
	N_Gear,
	D_Gear
}E_GEAR_POSITION;

typedef enum{
	EXTINCT,
	LEFT,
	RIGHT,
	DOUBLE_FLASH
}E_TURN_LAMP;

typedef enum{
	DISTANCE,
	VELOCITY,
	ROAD_RADIUS,
	GEAR,
	TURN_LAMP,
	STEERING,
	DRIVER_BRAKE,
	BRAKE_PEDAL,
	MAX_RESTRICT_CONDITION
}E_RESTRICT_CONDITION;

typedef struct{
	/* target infromation from can bus */
	INT16S targetLongtitudeDistance;
	INT16S targetLateralDistance;
	
	FP32 targetLongtitudeVelocity;
	FP32 targetLateralVelocity;
	
	/* vehicle information from can bus */
	FP32 vehicleVelocity;
	FP32 vehicleAcceleration;
	
	FP32 relativeVelocity;
	FP32 relativeDistance;

	INT8U turnLamp;
	INT8U gearPosition;
	
	INT16S steeringAngle;	
	INT16U roadCurvatureRadius;	
	
	FP32 ttc;
	FP32 mainCylinderPressure;
	
	INT16U speedFront;
	INT16U objPressure;
	INT16S incrementalValue;
	
	BOOLEAN funcDisableStatus;
	BOOLEAN driverBrakeStatus;
	BOOLEAN brakePedalStatus;
	BOOLEAN restrictCondition[MAX_RESTRICT_CONDITION];
}T_AEB;

/**** Declaration of functions ****/
AEB_EXT void Aeb_Init(void);
AEB_EXT void Aeb_DeInit(void);
AEB_EXT void Aeb_Algorithm(void);

#endif