/***********************************************************************
*   Copyright (C) JWD Automotive Co., Ltd.				                     * 
*		All Rights Reserved.          					                           *
*   Department : iCAS SW      									                       *
*   AUTHOR	   :            										                       *
************************************************************************
* Object        : 
* Module        : adc.c
* Instance      : 
* Description   : ADC sample
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

#include <string.h>

#include "XC23xxBREGS.h"

#include "adc.h"
#include "ADC0.h"
#include "ADC1.h"

#define ADC_GLOBALS

/**** Definition of variables ****/
T_ADC tAdcSample = {0u};
ADC_STAT T_ADC tAdcSamplePre = {0u};

/**** Declaration of functions ****/
ADC_STAT void Adc_Sample(void);

ADC_STAT void Adc_SamplePowerVoltage(void);
ADC_STAT void Adc_SampleBrakePedalVoltage(void);
ADC_STAT void Adc_SampleMainCylinderVoltage(void);
ADC_STAT void Adc_SamplePressureSensorVoltage(void);
ADC_STAT void Adc_SampleMotorVlinkVoltage(void);
ADC_STAT void Adc_SampleTemperature(void);

ADC_STAT void Adc_SampleMotorCurrent(void);
ADC_STAT void Adc_SampleMainCylinderPressure(void);
ADC_STAT void Adc_SampleBrakePedalTrip(void);
ADC_STAT void Adc_SampleMainCylinderTrip(void);
ADC_STAT void Adc_SampleMotorPhase(void);
ADC_STAT void Adc_SampleFilter(void);
ADC_STAT void Adc_SampleUpdate(void);

#if( ENABLE == ADC_SAMPLE_CHECK )	
	ADC_STAT INT16S Adc_SampleSignalCheck(INT16S *array);
#endif

/***********************************************************************
*  Name        : Adc_Init
*  Description : After power on, initiliaze ADC sample variable
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Adc_Init(void)
{
	memset(&tAdcSample, 0, sizeof(tAdcSample));
	memset(&tAdcSamplePre, 0, sizeof(tAdcSamplePre));	
	return;
}

/***********************************************************************
*  Name        : Adc_DeInit
*  Description : During running, need initilize ADC sample variable
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Adc_DeInit(void)
{
	return;
}

/***********************************************************************
*  Name        : Adc_Func
*  Description : ADC sample main function
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Adc_Func(void)
{
	Adc_Sample();
	Adc_SampleFilter();
	Adc_SampleUpdate();
	return;
}

/***********************************************************************
*  Name        : Adc_Sample
*  Description : ADC sample handle
*  Parameter   : None
*  Returns     : None
***********************************************************************/
ADC_STAT void Adc_Sample(void)
{
	Adc_SamplePowerVoltage();
	Adc_SampleBrakePedalVoltage();
	Adc_SampleMainCylinderVoltage();
	Adc_SamplePressureSensorVoltage();
	Adc_SampleMotorVlinkVoltage();
	Adc_SampleTemperature();
	Adc_SampleMotorCurrent();
	Adc_SampleMainCylinderPressure();
	Adc_SampleBrakePedalTrip();
	Adc_SampleMainCylinderTrip();
	Adc_SampleMotorPhase();
	return;
}

/***********************************************************************
*  Name        : Adc_SamplePowerVoltage
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
ADC_STAT void Adc_SamplePowerVoltage(void)
{
	tAdcSample.powerVoltage_Adc = Adc_SignalSample(0,ADC0_CAHNNEL_VEHILCE_POWER_VOLTAGE);
	return;
}

/***********************************************************************
*  Name        : Adc_SampleBrakePedalVoltage
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
ADC_STAT void Adc_SampleBrakePedalVoltage(void)
{
	tAdcSample.brakePedalVoltage_Adc = Adc_SignalSample(0,ADC0_CHANNEL_BRAKE_PEDAL_VOLTAGE);
	return;
}
/***********************************************************************
*  Name        : Adc_SampleMainCylinderVoltage
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
ADC_STAT void Adc_SampleMainCylinderVoltage(void)
{
	tAdcSample.mainCylinderVoltage_Adc = Adc_SignalSample(0,ADC0_CHANNEL_MAIN_CYLINDER_VOLTAGE);
	return;
}

/***********************************************************************
*  Name        : Adc_SamplePressureSensorVoltage
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
ADC_STAT void Adc_SamplePressureSensorVoltage(void)
{
	tAdcSample.pressureSensorVoltage_Adc = Adc_SignalSample(0,ADC0_CHANNEL_PRESSURE_SENSOR_VOLTAGE);
	return;
}

/***********************************************************************
*  Name        : Adc_SampleMotorVlinkVoltage
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
ADC_STAT void Adc_SampleMotorVlinkVoltage(void)
{
	tAdcSample.motorVLinkVoltage_Adc = Adc_SignalSample(0,ADC0_CHANNEL_MOTOR_VLINK_VOLTAGE);
	return;
}

/***********************************************************************
*  Name        : Adc_SampleTemperature
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
ADC_STAT void Adc_SampleTemperature(void)
{
	tAdcSample.temperatureValue_Adc = Adc_SignalSample(0,ADC0_CHANNEL_TEMPERTURE);
	return;
}

/***********************************************************************
*  Name        : Adc_SampleMotorCurrent
*  Description : ADC sample motor current 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
ADC_STAT void Adc_SampleMotorCurrent(void)
{
	tAdcSample.motorCurrent_Adc = Adc_SignalSample(0, ADC0_CHANNEL_MOTOR_CURRENT);
	return;
}

/***********************************************************************
*  Name        : Adc_SampleMainCylinderPressure
*  Description : ADC sample main cylinder pressure
*  Parameter   : None
*  Returns     : None
***********************************************************************/
ADC_STAT void Adc_SampleMainCylinderPressure(void)
{
	tAdcSample.mainCylinderPressure_Adc = Adc_SignalSample(1, ADC1_CHANNEL_PRESSURE_SENSOR_MAIN_CYLINDER);
	return;
}

/***********************************************************************
*  Name        : Adc_SampleBrakePedalTrip
*  Description : ADC sample brake pedal location
*  Parameter   : None
*  Returns     : None
***********************************************************************/
ADC_STAT void Adc_SampleBrakePedalTrip(void)
{
	ADC0_vStartSeq2ReqChNum(0,0,0,0);
	while(ADC0_uwBusy());
	while(ADC1_uwBusy());

	tAdcSample.brakePedalTrip_Adc[CHANNEL1] = ADC0_uwGetResultData_RESULT_REG_0;
	tAdcSample.brakePedalTrip_Adc[CHANNEL2] = ADC1_uwGetResultData_RESULT_REG_0;
#if( ENABLE == ADC_SAMPLE_CHECK )
	tAdcSample.brakePedalTrip_Adc[VERIFICATION] = Adc_SampleSignalCheck(&tAdcSample.brakePedalTrip_Adc);
#else
	tAdcSample.brakePedalTrip_Adc[VERIFICATION] = tAdcSample.brakePedalTrip_Adc[CHANNEL1];	
#endif
	return;
}

/***********************************************************************
*  Name        : Adc_SampleMainCylinderTrip
*  Description : ADC sample main cylinder trip
*  Parameter   : None
*  Returns     : None
***********************************************************************/
ADC_STAT void Adc_SampleMainCylinderTrip(void)
{
	ADC0_vStartSeq2ReqChNum(0,0,0,2);
	while(ADC0_uwBusy());
	while(ADC1_uwBusy());

	tAdcSample.mainCylinderTrip_Adc[CHANNEL1] = ADC0_uwGetResultData_RESULT_REG_1;
	tAdcSample.mainCylinderTrip_Adc[CHANNEL2] = ADC1_uwGetResultData_RESULT_REG_1;
#if( ENABLE == ADC_SAMPLE_CHECK )	
	tAdcSample.mainCylinderTrip_Adc[VERIFICATION] = Adc_SampleSignalCheck(&tAdcSample.mainCylinderTrip_Adc);
#else
	tAdcSample.mainCylinderTrip_Adc[VERIFICATION] = tAdcSample.mainCylinderTrip_Adc[CHANNEL1];	
#endif
	return;
}

/***********************************************************************
*  Name        : Adc_SampleMotorPhase
*  Description : ADC sample motor phase
*  Parameter   : None
*  Returns     : None
***********************************************************************/
ADC_STAT void Adc_SampleMotorPhase(void)
{
	tAdcSample.motorPhaseVoltage_Adc[PHASE_A] = Adc_SignalSample(0, ADC0_CAHNNEL_MOTOR_APHASE_VOLTAGE);
	tAdcSample.motorPhaseVoltage_Adc[PHASE_B] = Adc_SignalSample(0, ADC0_CAHNNEL_MOTOR_BPHASE_VOLTAGE);	
	return;
}

/***********************************************************************
*  Name        : Adc_SampleFilter
*  Description : ADC sample first order filtering
*  Parameter   : None
*  Returns     : None
***********************************************************************/
ADC_STAT void Adc_SampleFilter(void)
{
	tAdcSample.motorCurrent_Adc = ((tAdcSamplePre.motorCurrent_Adc * ADC_FILTER_PARM) + 
																 (tAdcSample.motorCurrent_Adc * (100u - ADC_FILTER_PARM))) / 100u;
	
	tAdcSample.mainCylinderPressure_Adc = ((tAdcSamplePre.mainCylinderPressure_Adc * ADC_FILTER_PARM) + 
																				 (tAdcSample.mainCylinderPressure_Adc * (100u - ADC_FILTER_PARM))) / 100u;	
	
	tAdcSample.mainCylinderTrip_Adc[VERIFICATION] = ((tAdcSamplePre.mainCylinderTrip_Adc[VERIFICATION] * ADC_FILTER_PARM) + 
																				(tAdcSample.mainCylinderTrip_Adc[VERIFICATION] * (100u - ADC_FILTER_PARM))) / 100u;	

	tAdcSample.brakePedalTrip_Adc[VERIFICATION] = ((tAdcSamplePre.brakePedalTrip_Adc[VERIFICATION] * ADC_FILTER_PARM) + 
																			(tAdcSample.brakePedalTrip_Adc[VERIFICATION] * (100u - ADC_FILTER_PARM))) / 100u;	
	
	return;
}
#if( ENABLE == ADC_SAMPLE_CHECK )	
/***********************************************************************
*  Name        : Adc_SampleSignalCheck
*  Description : ADC sample check
*  Parameter   : None
*  Returns     : None
***********************************************************************/
ADC_STAT INT16S Adc_SampleSignalCheck(INT16S *array)
{
	INT16S retValue;
	FP32 signalValue[2] = {0.0f};
	FP32 multipleValue = 0.0f;
	
	/* The two channel signals are in a double relationship */
	signalValue[0] = (FP32)(*(array+0));
	signalValue[1] = (FP32)(*(array+1));
	multipleValue = signalValue[0] / signalValue[1];
	
	if (((multipleValue >= 0.45f) && (multipleValue <= 0.55f))
	|| (multipleValue >= 1.5f) && (multipleValue <= 2.5f))
	{
		retValue = *(array+0);
	}
	else
	{
		retValue = 0u;
	}
	
	return retValue;
}
#endif
/***********************************************************************
*  Name        : Adc_SampleUpdate
*  Description : Current cycle ADC sample update to pre-cycle ADC sample,
*                first order filter use this function
*  Parameter   : None
*  Returns     : None
***********************************************************************/
ADC_STAT void Adc_SampleUpdate(void)
{
	memcpy(&tAdcSamplePre, &tAdcSample, sizeof(tAdcSample));
	return;
}

/***********************************************************************
*  Name        : Adc_SignalSample
*  Description : signal ADC sample function
*  Parameter   : AdcCore:0-ADC0, 1-ADC1
*                adcChannel: ADC channel of ADC0/ADC1 core
*  Returns     : adcValue: ADC factual value
***********************************************************************/
ADC_EXT INT16U Adc_SignalSample(INT8U adcCore, INT8U adcChannel)
{
	INT16U adcValue = 0u;
	
	switch(adcCore)
	{
		case CORE_ADC0:
			ADC0_vStartSeq2ReqChNum(0,0,0,adcChannel);
			while(ADC0_uwBusy());
			adcValue = ADC0_uwGetResultData_RESULT_REG_3;
			break;
		
		case CORE_ADC1:
			ADC1_vStartSeq2ReqChNum(0,0,0,adcChannel);
			while(ADC1_uwBusy());
			adcValue  = ADC1_uwGetResultData_RESULT_REG_3;
			break;
		
		default:
			break;
	}
	
	return adcValue;
}

/***********************************************************************
*  Name        : Adc_SampleData
*  Description : ADC sample module interface
*  Parameter   : None
*  Returns     : ADC sample data structure access address
***********************************************************************/
const T_ADC* Adc_SampleData(void)
{
	return (&tAdcSample);
}	