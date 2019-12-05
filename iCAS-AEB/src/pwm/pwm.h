/***********************************************************************
*   Copyright (C) JWD Automotive Co., Ltd.				                     * 
*		All Rights Reserved.          					                           *
*   Department : iCAS SW      									                       *
*   AUTHOR	   :            										                       *
************************************************************************
* Object        : 
* Module        : pwm.h
* Instance      : 
* Description   : pwm output
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

#ifndef _PWM_H_
#define _PWM_H_

#include "Para_Fun_Type.h"

#ifdef   PWM_GLOBALS
	#define  PWM_EXT
#else
	#define  PWM_EXT  extern
#endif
	
#ifdef   PWM_GLOBALS
	#define  PWM_STAT
#else
	#define  PWM_STAT static
#endif	

/**** Definition of macro ****/
#define PWM_AMPLITUDE_LOWER    (548u)
#define PWM_AMPLITUDE_UPPER    (3548u)
#define PWM_AMPLITUDE_DEFAULT  (2048u)

/**** Definition of data structure ****/
typedef struct{
	INT16U motorCtrl;
	
	INT16U channelDutyA;
	INT16U channelDutyB;
}T_PWM;

/**** Declaration of functions ****/
PWM_EXT void Pwm_Init(void);
PWM_EXT void Pwm_DeInit(void);
PWM_EXT void Pwm_Control(INT16S pwmValue);
PWM_EXT const T_PWM* Pwm_ControlData(void);

#endif