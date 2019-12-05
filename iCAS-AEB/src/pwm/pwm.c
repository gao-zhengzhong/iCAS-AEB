/***********************************************************************
*   Copyright (C) JWD Automotive Co., Ltd.				                     * 
*		All Rights Reserved.          					                           *
*   Department : iCAS SW      									                       *
*   AUTHOR	   :            										                       *
************************************************************************
* Object        : 
* Module        : pwm.c
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

#include <stdlib.h>
#include <string.h>

#include "pwm.h"

/**** Definition of variables ****/
PWM_STAT T_PWM tPwm = {0u};

/**** Declaration of functions ****/
PWM_STAT void Pwm_LimitAmplitude(INT16S pwmValue);
PWM_STAT void Pwm_ControlOutput(void);

/***********************************************************************
*  Name        : Pwm_Init
*  Description : After power on, initiliaze PWM sample variable
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Pwm_Init(void)
{
	memset(&tPwm, 0u, sizeof(tPwm));
	return;
}

/***********************************************************************
*  Name        : Pwm_DeInit
*  Description : During running, need initilize PWM sample variable
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Pwm_DeInit(void)
{
	return;
}

/***********************************************************************
*  Name        : Pwm_Control
*  Description : PWM control function
*  Parameter   : pwm control value
*  Returns     : None
***********************************************************************/
void Pwm_Control(INT16S pwmValue)
{
	Pwm_LimitAmplitude(pwmValue);
	Pwm_ControlOutput();
	return;
}

/***********************************************************************
*  Name        : Pwm_LimitAmplitude
*  Description : PWM amolitude limiting processing
*  Parameter   : None
*  Returns     : None
***********************************************************************/
PWM_STAT void Pwm_LimitAmplitude(INT16S pwmValue)
{
	INT16S motorDuty; 
	
	if (abs(pwmValue) <= 10u)
	{
		motorDuty = PWM_AMPLITUDE_DEFAULT;
	}
	else
	{
		motorDuty = pwmValue + PWM_AMPLITUDE_DEFAULT;
	
	if (motorDuty <= PWM_AMPLITUDE_LOWER)
	{
		motorDuty = PWM_AMPLITUDE_LOWER;
	}
	else if (motorDuty >= PWM_AMPLITUDE_UPPER)
	{
		motorDuty = PWM_AMPLITUDE_UPPER;
	}
	else
	{
		/* NOP */
		}		
	}
	
	tPwm.motorCtrl = motorDuty;
	return;
}

/***********************************************************************
*  Name        : Pwm_ControlOutput
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
PWM_STAT void Pwm_ControlOutput(void)
{
	INT32U temp;
	
	temp = ((INT32U)(tPwm.motorCtrl * 2000u)) >> 12u;
	
	/* PWM limiting processing */
	if (temp > 1900u)
	{
		tPwm.channelDutyA = 1900u;
	}
	else if (temp < 100u)
	{
		tPwm.channelDutyA = 100u;
	}
	else
	{
		tPwm.channelDutyA = (INT16U)temp;
	}
	
	tPwm.channelDutyB = 2000u - tPwm.channelDutyA;
	return;
}

/***********************************************************************
*  Name        : Pwm_ControlData
*  Description : PWM module interface
*  Parameter   : None
*  Returns     : PWM data structure access address
***********************************************************************/
const T_PWM* Pwm_ControlData(void)
{
	return (&tPwm);
}