/***********************************************************************
*   Copyright (C) JWD Automotive Co., Ltd.				                     * 
*		All Rights Reserved.          					                           *
*   Department : iCAS SW      									                       *
*   AUTHOR	   :            										                       *
************************************************************************
* Object        : 
* Module        : booster.h
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

#ifndef _BOOSTER_H_
#define _BOOSTER_H_

#include "Para_Fun_Type.h"

#ifdef   BOOSTER_GLOBALS
	#define  BOOSTER_EXT
#else
	#define  BOOSTER_EXT  extern
#endif
	
#ifdef   BOOSTER_GLOBALS
	#define  BOOSTER_STAT
#else
	#define  BOOSTER_STAT static
#endif

/* Booster function switch setting */
#ifndef BOOSTER_CURRENT_LOOP_PID
	#define BOOSTER_CURRENT_LOOP_PID DISABLE
#endif	

/**** Definition of macro ****/
#define SIGN(a) ((a)>0?1:((a)<0?-1:0))

#define BRAKE_PEDAL_INIT_LOCATION     (95u)
#define BRAKE_PEDAL_MECHANICAL_PARAM  (50.72f)
#define SENSOR_RANGE_PARAM            (400u)
		
#define MAIN_CYLINDER_INIT_LOCATION     (110u)
#define MAIN_CYLINDER_MECHANICAL_PARAM  (39.64f)	
	
#define MOTOR_CURRENT_THRESHOLD      (512u)
#define MOTOR_CURRENT_PARAM          (4.1f)

#define MAIN_CYLINDER_LOCATION_STEP1  (0.4f)
#define MAIN_CYLINDER_LOCATION_STEP2  (4.0f)
#define MAIN_CYLINDER_LOCATION_STEP3  (10.5f)
#define MAIN_CYLINDER_LOCATION_STEP4  (15.6f)

/**** Definition of data structure ****/
typedef struct{
	FP32 brakePedalLocation;
	FP32 mainCylinderLocation;
	FP32 motorCurrent;
	
	INT16S incrementalValue;
}T_BOOSTER;

/**** Declaration of functions ****/
BOOSTER_EXT void Booster_Init(void);
BOOSTER_EXT void Booster_DeInit(void);
BOOSTER_EXT void Booster_Algorithm(void);
BOOSTER_EXT const T_BOOSTER* Booster_AlogrithmData(void);

#endif