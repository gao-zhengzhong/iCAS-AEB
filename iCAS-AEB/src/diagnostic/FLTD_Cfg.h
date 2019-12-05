
#ifndef _FLTD_CFG_H_
#define _FLTD_CFG_H_


typedef struct
{
	const FLTD_U8 periodtime; 	/* count * basetime */
	const FLTD_U8 losttimeOut;	/* count * basetime */
	const FLTD_U8 recovertime;	/* count * basetime */

	FLTD_U8 SigPresentFlag;
	FLTD_U8 SigCheckErrorFlag;
	FLTD_U8 SigFaultFlag;

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
//             |         |   low_hyst   |			 |	  high_hyst	 |          |   
//			   |	     |			    |			 |				 |		    |
//     stop	   |   low      low/normal  |  normal	 | 	 normal/high     high   |	over
//---------------------------------------------------------------------------------------
typedef struct
{
	const FLTD_U16 stop_threshold;
	const FLTD_U16 low_threshold;
	const FLTD_U16 high_threshold;
	const FLTD_U16 over_threshold;

	const FLTD_U16 low_hyst;
	const FLTD_U16 high_hyst;
	const FLTD_U16 filtertime; 		/* count * basetime */

	FLTD_U16* adcValue;

} FLTD_AdcMonitorCfgType;

FLTD_AdcMonitorCfgType FLTD_AdcMonitorCfg[FLTD_ADC_MAX] =
{
	
// /*stop_t*/ /*low_t*/ /*high_t*/ /*over_t*/ /*low_hyst*/ /*high_hyst*/ /*filter*/  /*location in the struct tAdcSample*/

	{200,	460,	820,	840,	10,		10,		10,	(FLTD_U16*)&tAdcSample + 0},
	{102,	417,	964,	1005, 162,	38, 	10, (FLTD_U16*)&tAdcSample + 1},
	{80,	220,	300,	340, 	10,		10,		10, (FLTD_U16*)&tAdcSample + 2},
	{10,	102,	921,	950, 	10,		10,		10, (FLTD_U16*)&tAdcSample + 3},
	{10,	102,	921,	950, 	10,		10,		10, (FLTD_U16*)&tAdcSample + 4},
	{80,	220,	300,	340, 	10,		10,		10, (FLTD_U16*)&tAdcSample + 5},
	{10,	102,	921,	950,	10,		10,		10, (FLTD_U16*)&tAdcSample + 6},
	{10,	102,	921,	950,	10,		10,		10, (FLTD_U16*)&tAdcSample + 7},
	{80,	102,	921,	940, 	10,		10,		10, (FLTD_U16*)&tAdcSample + 8},
	
	{40,	45,		55,	 	60, 	3,		3, 		10, (FLTD_U16*)&tAdcSample + 9},
	{80,	220,	300,	340, 	10,		10,		10, (FLTD_U16*)&tAdcSample + 10},
	{80,	220,	300,	340, 	10,		10,		10, (FLTD_U16*)&tAdcSample + 11},
	{80,	220,	300,	340, 	10,		10,		10, (FLTD_U16*)&tAdcSample + 12},
	{80,	220,	300,	340, 	10,		10,		10, (FLTD_U16*)&tAdcSample + 13}
	
};

#endif
