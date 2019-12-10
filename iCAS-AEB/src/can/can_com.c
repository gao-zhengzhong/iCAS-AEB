/***********************************************************************
*   Copyright (C) JWD Automotive Co., Ltd.				                     * 
*		All Rights Reserved.          					                           *
*   Department : iCAS SW      									                       *
*   AUTHOR	   :            										                       *
************************************************************************
* Object        : 
* Module        : can_com.c
* Instance      : 
* Description   : can communication
*-----------------------------------------------------------------------
* Version: v0.1
* Date   : Dec 11,2019 
* Author : Gao zehngzhong
***********************************************************************/
/*-History--------------------------------------------------------------
* Version    Date           Name            Changes and comments
------------------------------------------------------------------------
* 0.1	       Dec 11,2019     Gao Zhengzhong  Initial version
*=====================================================================*/

#include "XC23xxBREGS.h"

#include "adc.h"
#include "can.h"
#include "can_com.h"
#include "adsample.h"
#include "FLTD.h"

#define CAN_COM_GLOBALS

/**** Definition of variables ****/
CAN_COM_STAT T_CAN_COM tCanCom = {0};

CAN_COM_STAT INT16U  CAN0ID_u16_Sig; //CAN0 receive ID
CAN_COM_STAT INT16U  CAN1ID_u16_Sig; //CAN1 receive ID

CAN_COM_STAT INT16U Can0ID_u16a64_Sig[CAN0ID_NUM] = {
	REC_CAN0ID_0, REC_CAN0ID_1, REC_CAN0ID_2, REC_CAN0ID_3, REC_CAN0ID_4, REC_CAN0ID_5, REC_CAN0ID_6, REC_CAN0ID_7,
	REC_CAN0ID_8, REC_CAN0ID_9, REC_CAN0ID_10,REC_CAN0ID_11,REC_CAN0ID_12,REC_CAN0ID_13,REC_CAN0ID_14,REC_CAN0ID_15,
	REC_CAN0ID_16,REC_CAN0ID_17,REC_CAN0ID_18,REC_CAN0ID_19,REC_CAN0ID_20,REC_CAN0ID_21,REC_CAN0ID_22,REC_CAN0ID_23,
	REC_CAN0ID_24,REC_CAN0ID_25,REC_CAN0ID_26,REC_CAN0ID_27,REC_CAN0ID_28,REC_CAN0ID_29,REC_CAN0ID_30,REC_CAN0ID_31,
	REC_CAN0ID_32,REC_CAN0ID_33,REC_CAN0ID_34,REC_CAN0ID_35,REC_CAN0ID_36,REC_CAN0ID_37,REC_CAN0ID_38,REC_CAN0ID_39,
	REC_CAN0ID_40,REC_CAN0ID_41,REC_CAN0ID_42,REC_CAN0ID_43,REC_CAN0ID_44,REC_CAN0ID_45,REC_CAN0ID_46,REC_CAN0ID_47,
	REC_CAN0ID_48,REC_CAN0ID_49,REC_CAN0ID_50,REC_CAN0ID_51,REC_CAN0ID_52,REC_CAN0ID_53,REC_CAN0ID_54,REC_CAN0ID_55,
	REC_CAN0ID_56,REC_CAN0ID_57,REC_CAN0ID_58,REC_CAN0ID_59,REC_CAN0ID_60,REC_CAN0ID_61,REC_CAN0ID_62,REC_CAN0ID_63
};

CAN_COM_STAT INT16U Can1ID_u16a10_Sig[CAN1ID_NUM] = {
	REC_CAN1ID_0,REC_CAN1ID_1,REC_CAN1ID_2,REC_CAN1ID_3,REC_CAN1ID_4,
	REC_CAN1ID_5,REC_CAN1ID_6,REC_CAN1ID_7,REC_CAN1ID_8,REC_CAN1ID_9
};

/* CAN0 receive data array initialize */
CAN_COM_STAT INT8U Can0Rec0data[CAN0ID_NUM][CAN_DATA_NUM] = {
	{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}
};

/* CAN1 receive data array initialize */
CAN_COM_STAT INT8U Can1Recdata[CAN1ID_NUM][CAN_DATA_NUM] = {
	{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}
};

/***********************************************************************
*  Name        : CanCom_Init
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CanCom_Init(void)
{
	return;
}

/***********************************************************************
*  Name        : CanCom_DeInit
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CanCom_DeInit(void)
{
	return;
}

/***********************************************************************
*  Name        : CanCom_TransceiverEnable
*  Description : Enable CAN transceiver and start commnuication
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CanCom_TransceiverEnable(void)
{
	ENABLE_CAN0_TRACV_ON; //enable vehicle can(can0) transceiver
	ENABLE_CAN1_TRACV_ON; //enable private can(can1) transceiver
	
	return;
}

/***********************************************************************
*  Name        : CanCom_TransceiverDisable
*  Description : Disable CAN transceiver and start commnuication
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CanCom_TransceiverDisable(void)
{
	ENABLE_CAN0_TRACV_OFF; //disable vehicle can(can0) transceiver
	ENABLE_CAN1_TRACV_OFF; //disable private can(can1) transceiver
	
	return;
}

/***********************************************************************
*  Name        : CanCom_SendMsg
*  Description : CAN send message
*  Parameter   : ubObjNr - MessgeObject
*								 ubpubData - Send data
*                Len - Data length
*  Returns     : None
***********************************************************************/
void CanCom_SendMsg(INT8U ubObjNr, INT8U *ubpubData, INT8U Len)
{
	INT8U len;
	len = Len + 0x10;

	CAN_HWOBJ[ubObjNr].uwMOFCRH &= (~(uword)0x0F00);
	CAN_HWOBJ[ubObjNr].uwMOFCRH |= (((uword)(len & 0x0F)) << 8u);
	CAN_vLoadData(ubObjNr,ubpubData);
	CAN_vTransmit(ubObjNr);
	
	return;
}

/***********************************************************************
*  Name        : CanCom_ReceiveMsg
*  Description : CAN receive message
*  Parameter   : ubObjNr - MessgeObject
*								 ubpubData - Receive data
*                Len - Data length
*  Returns     : 1 - OK; 0 - Fail
***********************************************************************/
INT8U CanCom_ReceiveMsg(INT8U ubObjNr, INT8U *ubpubData, INT8U *Len)
{
	INT8U i;
	
	/* can message objects receive new message */
	if (CAN_ubNewData(ubObjNr))
	{
		/* get length of receive message */
		Len[0] = (INT8U)((CAN_HWOBJ[ubObjNr].uwMOFCRH & 0x0F00) >> 8u); 
		
		/* get receive message */
		for (i=0u; i<=Len[0]; i++)
		{
			ubpubData[i] = CAN_HWOBJ[ubObjNr].ubData[i];
		}
		
		/* clear receive flag */
		CAN_HWOBJ[ubObjNr].uwMOCTRL = 0x0008;
		return 1;
	}
	
	return 0;
}

/***********************************************************************
*  Name        : CanCom_Can0RecDeal
*  Description : CAN0 receive message handle data
*  Parameter   : canId - CAN0 CANID
*  Returns     : None
***********************************************************************/
void CanCom_Can0RecDeal(INT16U canId)
{
	INT8U i,j;
	
	/* judge receive CAN ID */
	for (i=0u; i<CAN0ID_NUM; i++)
	{
		if (canId == Can0ID_u16a64_Sig[i])
		{
			/* get CAN0 message object byte x */
			for (j=0u; j<CAN_DATA_NUM; j++)
			{
				Can0Rec0data[i][j] = CAN_HWOBJ[0].ubData[j];  
			}
		}
	}
	
	return;
}

/***********************************************************************
*  Name        : CanCom_Can1RecDeal
*  Description : CAN1 receive message handle data
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CanCom_Can1RecDeal(void)
{
	INT8U i,j;
	
	/* judge message object 1 receive new message */
	if (CAN_ubNewData(1))
	{
		/* get CAN ID */
		CAN1ID_u16_Sig = CAN_MOAR1H;
		CAN1ID_u16_Sig = (CAN1ID_u16_Sig >> 2u) & 0x7FF;

		/* judge receive CAN ID */
		for (i=0u; i<CAN1ID_NUM; i++)
		{
			if (CAN1ID_u16_Sig == Can1ID_u16a10_Sig[i])
			{
				/* get CAN0 message object byte x */
				for (j=0u; j<CAN_DATA_NUM; j++)
				{
					Can1Recdata[i][j] = CAN_HWOBJ[0].ubData[j];  
				}
			}
		}
		
		/* clear receive flag */
		CAN_HWOBJ[1].uwMOCTRL = 0x0008;
	}

	return;
}

/***********************************************************************
*  Name        : CanCom_CanTx
*  Description : CAN send message
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CanCom_CanTx(void)
{
	CAN_COM_STAT INT8U CycleSchedCnt = 0u;
	const T_ADC *ptr = Adc_SampleData();
	
#if 0		
	*(INT16U*)&Can0Revdata[0][0] = ptr->powerVoltage_Adc | (FLTD_GetAdcRangeType(FLTD_ADC_ECU_VOLTAGE) << 12);
	*(INT16U*)&Can0Revdata[0][2] = ptr->temperatureValue_Adc | (FLTD_GetAdcRangeType(FLTD_ADC_ENV_TEMPERATURE) << 12);
	*(INT16U*)&Can0Revdata[0][4] = ptr->brakePedalVoltage_Adc | (FLTD_GetAdcRangeType(FLTD_ADC_PEDAL_SENSOR_VOLTAGE) << 12);
	*(INT16U*)&Can0Revdata[0][6] = ptr->brakePedalTrip_Adc[0] | (FLTD_GetAdcRangeType(FLTD_ADC_PEDAL_SENSOR_SIG1) << 12);
	*(INT16U*)&Can0Revdata[1][0] = ptr->brakePedalTrip_Adc[1] | (FLTD_GetAdcRangeType(FLTD_ADC_PEDAL_SENSOR_SIG2) << 12);
	*(INT16U*)&Can0Revdata[1][2] = ptr->brakePedalTrip_Adc[2];
	*(INT16U*)&Can0Revdata[1][4] = ptr->mainCylinderVoltage_Adc | (FLTD_GetAdcRangeType(FLTD_ADC_MAIN_CYLINDER_VOLTAGE) << 12);
	*(INT16U*)&Can0Revdata[1][6] = ptr->mainCylinderTrip_Adc[0] | (FLTD_GetAdcRangeType(FLTD_ADC_MAIN_CYLINDER_SIG1) << 12);
	*(INT16U*)&Can0Revdata[2][0] = ptr->mainCylinderTrip_Adc[1] | (FLTD_GetAdcRangeType(FLTD_ADC_MAIN_CYLINDER_SIG2) << 12);
	*(INT16U*)&Can0Revdata[2][2] = ptr->mainCylinderTrip_Adc[2];
	*(INT16U*)&Can0Revdata[2][4] = ptr->motorCurrent_Adc | (FLTD_GetAdcRangeType(FLTD_ADC_CURRENT_SENSOR_SIG) << 12);
	*(INT16U*)&Can0Revdata[2][6] = ptr->motorVLinkVoltage_Adc | (FLTD_GetAdcRangeType(FLTD_ADC_VLINK_VOLTAGE) << 12);
	*(INT16U*)&Can0Revdata[3][0] = ptr->motorPhaseVoltage_Adc[0] | (FLTD_GetAdcRangeType(FLTD_ADC_A_PHASE_VOLTAGE) << 12);
	*(INT16U*)&Can0Revdata[3][2] = ptr->motorPhaseVoltage_Adc[1] | (FLTD_GetAdcRangeType(FLTD_ADC_B_PHASE_VOLTAGE) << 12);
	*(INT16U*)&Can0Revdata[3][4] = ptr->pressureSensorVoltage_Adc | (FLTD_GetAdcRangeType(FLTD_ADC_PRESSURE_SENSOR_VOLTAGE) << 12);
	*(INT16U*)&Can0Revdata[3][6] = ptr->mainCylinderPressure_Adc | (FLTD_GetAdcRangeType(FLTD_ADC_PRESSURE_SENSOR_SIG) << 12);
#endif
	
	CycleSchedCnt++;
	
	switch(CycleSchedCnt)
	{
		case 1:
#if( 1 == CAN0TRS0_ENABLE )
			CAN_MOAR4H = 0x8000 + (TRS_CAN0ID_0 << 2u);
			CAN_MOAR4L = 0x0000;
			CanCom_SendMsg(4,&Can0Revdata[0][0],8);
#endif		
#if( 1 == CAN1TRS0_ENABLE )
			CAN_MOAR10H = 0x8000 + (TRS_CAN1ID_0 << 2u);
			CAN_MOAR10L = 0x0000;
			CanCom_SendMsg(10,&Can1Revdata[0][0],8);
#endif		
			break;
		
		case 2:
#if( 1 == CAN0TRS1_ENABLE )
			CAN_MOAR5H = 0x8000 + (TRS_CAN0ID_1 << 2u);
			CAN_MOAR5L = 0x0000;
			CanCom_SendMsg(5,&Can0Revdata[1][0],8);
#endif
#if( 1 == CAN1TRS1_ENABLE )
			CAN_MOAR11H = 0x8000 + (TRS_CAN1ID_1 << 2u);
			CAN_MOAR11L = 0x0000;
			CanCom_SendMsg(11,&Can1Revdata[1][0],8);
#endif		
			break;
		
		case 3:
#if( 1 == CAN0TRS2_ENABLE )
			CAN_MOAR6H = 0x8000 + (TRS_CAN0ID_2 << 2u);
			CAN_MOAR6L = 0x0000;
			CanCom_SendMsg(6,&Can0Revdata[2][0],8);
#endif
#if( 1 == CAN1TRS2_ENABLE )
			CAN_MOAR12H = 0x8000 + (TRS_CAN1ID_2 << 2u);
			CAN_MOAR12L = 0x0000;
			CanCom_SendMsg(12,&Can1Revdata[2][0],8);
#endif			
			break;
		
		case 4:
#if( 1 == CAN0TRS3_ENABLE )
			CAN_MOAR7H = 0x8000 + (TRS_CAN0ID_3 << 2u);
			CAN_MOAR7L = 0x0000;
			CanCom_SendMsg(7,&Can0Revdata[3][0],8);
#endif
#if( 1 == CAN1TRS3_ENABLE )
			CAN_MOAR13H = 0x8000 + (TRS_CAN1ID_3 << 2u);
			CAN_MOAR13L = 0x0000;
			CanCom_SendMsg(13,&Can1Revdata[3][0],8);
#endif
		 CycleSchedCnt = 0u;		
			break;
		
		default:
			break;
	}
	
	return;
}

CAN_COM_EXT const T_CAN_COM* CanCom_VehicleData(void)
{
	return (&tCanCom);
}