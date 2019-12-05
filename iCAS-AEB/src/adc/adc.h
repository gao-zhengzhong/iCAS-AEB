/***********************************************************************
*   Copyright (C) JWD Automotive Co., Ltd.				                     * 
*		All Rights Reserved.          					                           *
*   Department : iCAS SW      									                       *
*   AUTHOR	   :            										                       *
************************************************************************
* Object        : 
* Module        : adc.h
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

#ifndef _ADC_H_
#define _ADC_H_

#include "Para_Fun_Type.h"
#include "IO.h"

#ifdef   ADC_GLOBALS
	#define  ADC_EXT
#else
	#define  ADC_EXT  extern
#endif
	
#ifdef   ADC_GLOBALS
	#define  ADC_STAT
#else
	#define  ADC_STAT static
#endif

/* ADC function switch setting */
#ifndef ADC_SAMPLE_CHECK
	#define ADC_SAMPLE_CHECK DISABLE
#endif	

/**** Definition of macro ****/
#define ADC_FILTER_PARM (25u)
	
/* enable main relay on/off */
#define ENABLE_MAIN_RELAY_ON	 SETIO_P10_4	
#define ENABLE_MAIN_RELAY_OFF  CLEARIO_P10_4
	
/* enable pre_driver on/off */
#define EANBLE_PRE_DRIVER_ON   SETIO_P0_7
#define EANBLE_PRE_DRIVER_OFF  CLEARIO_P0_7

/* enable main power supply on/off */
#define ENABLE_MAIN_POWER_ON   SETIO_P1_7
#define ENABLE_MAIN_POWER_OFF  CLEARIO_P1_7

/* enable main cylinder pressure sensor power supply on/off */
#define ENABLE_PRESSURE_SENSOR_POWER_ON   SETIO_P7_0
#define ENABLE_PRESSURE_SENSOR_POWER_OFF  CLEARIO_P7_0

/* enable main cylinder power supply on/off */
#define ENABLE_MAIN_CYLINDER_POWER_ON   SETIO_P7_1
#define ENABLE_MAIN_CYLINDER_POWER_OFF  CLEARIO_P7_1

/* enable brake pedal power supply on/off */
#define ENABLE_BRAKE_PEDAL_POWER_ON   SETIO_P7_4
#define ENABLE_BRAKE_PEDAL_POWER_OFF  CLEARIO_P7_4

/* enable CAN0 transceiver on/off */ 
#define ENABLE_CAN0_TRACV_ON   SETIO_P1_5
#define ENABLE_CAN0_TRACV_OFF  CLEARIO_P1_5

/* enable CAN1 transceiver on/off */ 
#define ENABLE_CAN1_TRACV_ON   SETIO_P1_4
#define ENABLE_CAN1_TRACV_OFF  CLEARIO_P1_4

/* enable brake status lamp on/off */
#define ENABLE_BRAKE_LAMP_ON   SETIO_P6_2
#define ENABLE_BRAKE_LAMP_OFF  CLEARIO_P6_2

/* brake apply status input signal */
#define DIO_SIGNAL_INPUT_BRAKE_STATUS()  INIO_P4_0  
	
/* pre-driver error status input signal */
#define DIO_SIGNAL_INPUT_PRE_DRIVER_ERR()  INIO_P6_0

/* IG status input signal */
#define DIO_SIGNAL_INPUT_IG()  INIO_P7_3

/* watchdog error status input signal */
#define DIO_SIGNAL_INPUT_WATCHDOG()  INIO_P4_3

#define DIO_SIGNAL_OUTPUT_FEED_WATCHDOG()  TOGGLEIO_P10_1
	
/**** Definition of data structure ****/
typedef enum{
	ADC0_CAHNNEL_VEHILCE_POWER_VOLTAGE = 3,    //vehicle battery voltage sample channel of ADC0 core
	ADC0_CAHNNEL_MOTOR_BPHASE_VOLTAGE,         //motor B phase voltage sample channel of ADC0 core
	ADC0_CAHNNEL_MOTOR_APHASE_VOLTAGE,         //motor B phase voltage sample channel of ADC0 core
	ADC0_CHANNEL_MOTOR_VLINK_VOLTAGE = 8,      //motor vlink vlotage sample channel of ADC0 core
	ADC0_CHANNEL_TEMPERTURE,                   //temperature sample channel of ADC0 core
	ADC0_CHANNEL_MAIN_CYLINDER_VOLTAGE,        //main cylinder voltage sample channel of ADC0 core
	ADC0_CHANNEL_BRAKE_PEDAL_VOLTAGE,          //brake pedal voltage sample channel of ADC0 core
	ADC0_CHANNEL_PRESSURE_SENSOR_VOLTAGE = 13, //main cylinder pressure sensor voltage sample channel of ADC0 core
	ADC0_CHANNEL_MOTOR_CURRENT = 15            //motor current sample channel of ADC0 core	
};

typedef enum{
	ADC1_CHANNEL_PRESSURE_SENSOR_MAIN_CYLINDER = 4, //main cylinder pressure channel of ADC1 core
	ADC1_CHANNEL_REFERENCE_1,                       //reference 1 not use
	ADC1_CHANNEL_REFERENCE_2                        //reference 2 not use
};
	
typedef enum{
	CORE_ADC0,
	CORE_ADC1
};	
	
typedef enum{
	PHASE_A,
	PHASE_B
};

typedef enum{
	CHANNEL1,
	CHANNEL2,
	VERIFICATION
};

/* Input ADC sample signal */
typedef struct{
	INT16U powerVoltage_Adc;
	INT16U temperatureValue_Adc;
	INT16U brakePedalVoltage_Adc;
	INT16U brakePedalTrip_Adc[3];
	INT16U mainCylinderVoltage_Adc;
	INT16U mainCylinderTrip_Adc[3];
	
	INT16U motorCurrent_Adc;
	INT16U motorVLinkVoltage_Adc;
	INT16U motorPhaseVoltage_Adc[2];
	INT16U pressureSensorVoltage_Adc;
	INT16U mainCylinderPressure_Adc;
}T_ADC;

/**** Declaration of variables ****/
ADC_EXT T_ADC tAdcSample;

/**** Declaration of functions ****/
ADC_EXT void Adc_Init(void);
ADC_EXT void Adc_DeInit(void);
ADC_EXT void Adc_Func(void);
ADC_EXT const T_ADC* Adc_SampleData(void);
ADC_EXT INT16U Adc_SignalSample(INT8U adcCore, INT8U adcChannel);

#endif