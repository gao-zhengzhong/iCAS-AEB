
#ifndef _FLTD_CFG_H_
#define _FLTD_CFG_H_


typedef struct
{
	const FLT_U8 periodTime; 	/* count * basetime */
	const FLT_U8 lostTimeOut;	/* count * basetime */
	const FLT_U8 recoverTime;	/* count * basetime */

	FLT_U8 sigPresentFlag;
	FLT_U8 sigCheckErrorFlag;
	FLT_U8 sigFaultFlag;

} FLTD_SigMonitorCfgType;

FLTD_SigMonitorCfgType FLTD_SigMonitorCfg[FLTD_SIG_MAX] =
{
	{10, 20, 10, 0xFF, 0xFF, 0xFF},
	{10, 20, 10, 0xFF, 0xFF, 0xFF},
	{10, 20, 10, 0xFF, 0xFF, 0xFF},
	{10, 20, 10, 0xFF, 0xFF, 0xFF},
	{10, 20, 10, 0xFF, 0xFF, 0xFF},
	{10, 20, 10, 0xFF, 0xFF, 0xFF},
	{10, 20, 10, 0xFF, 0xFF, 0xFF},
};




/* AD samples values is divided into five, in order to stop, low, normal, high, over, etc */
//---------- stop_t ----------------- low_t ------  high_t ------------------- over_t ---
//             |         |   lowHyst    |			 |	  highHyst	 |          |   
//			   |	     |			    |			 |				 |		    |
//     stop	   |   low      low/normal  |  normal	 | 	 normal/high     high   |	over
//---------------------------------------------------------------------------------------
typedef struct
{
	const FLT_U16 stopThreshold;
	const FLT_U16 lowThreshold;
	const FLT_U16 highThreshold;
	const FLT_U16 overThreshold;

	const FLT_U16 lowHyst;
	const FLT_U16 highHyst;
	const FLT_U16 filterTime; 		/* count * basetime */

	FLT_U16* adcValue;

} FLTD_AdcMonitorCfgType;

FLTD_AdcMonitorCfgType FLTD_AdcMonitorCfg[FLTD_ADC_MAX] =
{
	
// /*stop_t*/ /*low_t*/ /*high_t*/ /*over_t*/ /*lowHyst*/ /*highHyst*/ /*filter*/  /*location in the struct tAdcSample*/
	
	{200,	460,	820,	840,	10,		10,		10,	(FLT_U16*)&tAdcSample + 0},	//FLTD_ADC_ECU_VOLTAGE
	{102,	417,	964,	1005, 	162,	38, 	10, (FLT_U16*)&tAdcSample + 1},	//FLTD_ADC_ENV_TEMPERATURE
	{80,	220,	300,	340, 	10,		10,		10, (FLT_U16*)&tAdcSample + 2},	//FLTD_ADC_PEDAL_SENSOR_VOLTAGE
	{10,	102,	921,	950, 	10,		10,		10, (FLT_U16*)&tAdcSample + 3},	//FLTD_ADC_PEDAL_SENSOR_SIG1
	{10,	102,	921,	950, 	10,		10,		10, (FLT_U16*)&tAdcSample + 4},	//FLTD_ADC_PEDAL_SENSOR_SIG2
	{80,	220,	300,	340, 	10,		10,		10, (FLT_U16*)&tAdcSample + 6},	//FLTD_ADC_MAIN_CYLINDER_VOLTAGE
	{10,	102,	921,	950,	10,		10,		10, (FLT_U16*)&tAdcSample + 7},	//FLTD_ADC_MAIN_CYLINDER_SIG1
	{10,	102,	921,	950,	10,		10,		10, (FLT_U16*)&tAdcSample + 8},	//FLTD_ADC_MAIN_CYLINDER_SIG2
	{80,	102,	921,	940, 	10,		10,		10, (FLT_U16*)&tAdcSample + 10},	//FLTD_ADC_CURRENT_SENSOR_SIG
	
	{40,	45,		55,	 	60, 	3,		3, 		10, (FLT_U16*)&tAdcSample + 11},	//FLTD_ADC_VLINK_VOLTAGE
	{80,	220,	300,	340, 	10,		10,		10, (FLT_U16*)&tAdcSample + 12},	//FLTD_ADC_A_PHASE_VOLTAGE
	{80,	220,	300,	340, 	10,		10,		10, (FLT_U16*)&tAdcSample + 13},	//FLTD_ADC_B_PHASE_VOLTAGE
	
#if (1 == PRESSURE_SENSOR_SUPPORT_OR_NOT)
	{80,	220,	300,	340, 	10,		10,		10, (FLT_U16*)&tAdcSample + 14},	//FLTD_ADC_PRESSURE_SENSOR_VOLTAGE
	{80,	220,	300,	340, 	10,		10,		10, (FLT_U16*)&tAdcSample + 15}	//FLTD_ADC_PRESSURE_SENSOR_SIG
#endif
};

#endif
