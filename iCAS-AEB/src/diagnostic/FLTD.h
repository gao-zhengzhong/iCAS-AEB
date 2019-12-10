/***********************************************************************
*   Copyright (C) JWD Automotive Co., Ltd.				               * 
*		All Rights Reserved.          					               *
*   Department : iCAS SW      									       *
*   AUTHOR	   :            										   *
************************************************************************
* Object        : 
* Module        : FLTD.h
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

#if !defined _FLTD_H_
#define _FLTD_H_

#if !defined  FLTD_C_
#define _EXTERN_ extern
#else
#define _EXTERN_
#endif

#include "FLT_Types.h"

#define PRESSURE_SENSOR_SUPPORT_OR_NOT 0 /* pressure sensor not support */

typedef enum
{
	FLTD_SIG_VEHICLE_SPEED = 0,
	FLTD_SIG_GEAR,
	FLTD_SIG_RADAR,
	FLTD_SIG_CAMERA,
	FLTD_SIG_ANGLE_SENSOR,
	FLTD_SIG_YAW_VELOCITY,
	FLTD_SIG_HMI,

	FLTD_SIG_MAX
}FLTD_SigType;

typedef enum
{
	FLTD_SIG_NORMAL = 0,
	FLTD_SIG_TIMEOUT,
	FLTD_SIG_CHECK_ERROR,
	FLTD_SIG_FAULT
}FLTD_SigFaultType;



typedef enum
{
	FLTD_ADC_ECU_VOLTAGE = 0,
	FLTD_ADC_ENV_TEMPERATURE,
	FLTD_ADC_PEDAL_SENSOR_VOLTAGE,
	FLTD_ADC_PEDAL_SENSOR_SIG1,
	FLTD_ADC_PEDAL_SENSOR_SIG2,
	FLTD_ADC_MAIN_CYLINDER_VOLTAGE,
	FLTD_ADC_MAIN_CYLINDER_SIG1,
	FLTD_ADC_MAIN_CYLINDER_SIG2,
	FLTD_ADC_CURRENT_SENSOR_SIG,
	
	FLTD_ADC_VLINK_VOLTAGE,
	FLTD_ADC_A_PHASE_VOLTAGE,
	FLTD_ADC_B_PHASE_VOLTAGE,
	
#if (1 == PRESSURE_SENSOR_SUPPORT_OR_NOT)
	FLTD_ADC_PRESSURE_SENSOR_VOLTAGE,
	FLTD_ADC_PRESSURE_SENSOR_SIG,
#endif
	FLTD_ADC_MAX
}FLTD_AdcType;

typedef enum
{
    FLTD_VOL_NORMAL = 0,
    FLTD_VOL_STOP,
    FLTD_VOL_LOW,
    FLTD_VOL_HIGH,
    FLTD_VOL_OVER,
	
	/* used by module */
    FLTD_VOL_LOW_HYST,
    FLTD_VOL_HIGH_HYST
}FLTD_VOLModeType;

_EXTERN_ void FLTD_Init(void);
_EXTERN_ void FLTD_CyclicProcess(void);

_EXTERN_ void FLTD_SigSetPresentFlag(FLTD_SigType sigType);
_EXTERN_ void FLTD_SigSetCheckErrorFlag(FLTD_SigType sigType);
_EXTERN_ void FLTD_SigSetFaultFlag(FLTD_SigType sigType);

_EXTERN_ FLTD_SigFaultType FLTD_GetSigFaultType(FLTD_SigType sigtype);
_EXTERN_ FLTD_VOLModeType FLTD_GetAdcRangeType(FLTD_AdcType adctype);

#undef _EXTERN_
#endif
