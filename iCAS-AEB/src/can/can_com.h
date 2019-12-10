/***********************************************************************
*   Copyright (C) JWD Automotive Co., Ltd.				                     * 
*		All Rights Reserved.          					                           *
*   Department : iCAS SW      									                       *
*   AUTHOR	   :            										                       *
************************************************************************
* Object        : 
* Module        : can_com.h
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

#ifndef _CAN_COM_H_
#define _CAN_COM_H_

#include "Para_Fun_Type.h"

#ifdef   CAN_COM_GLOBALS
	#define  CAN_COM_EXT
#else
	#define  CAN_COM_EXT  extern
#endif
	
#ifdef   CAN_COM_GLOBALS
	#define  CAN_COM_STAT
#else
	#define  CAN_COM_STAT static
#endif		

/**** Definition of macro ****/
#define REC_CAN0ID_0   1 //CAN0 Receive CANID 11Bit  Can0Rec0data[0][0]-Can0Rec0data[0][7]
#define REC_CAN0ID_1   2  //CAN0 Receive CANID 11Bit  Can0Rec0data[1][0]-Can0Rec0data[1][7]
#define REC_CAN0ID_2   3  //CAN0 Receive CANID 11Bit  Can0Rec0data[2][0]-Can0Rec0data[2][7]
#define REC_CAN0ID_3   4  //CAN0 Receive CANID 11Bit  Can0Rec0data[3][0]-Can0Rec0data[3][7]
#define REC_CAN0ID_4   5  //CAN0 Receive CANID 11Bit  Can0Rec0data[4][0]-Can0Rec0data[4][7]
#define REC_CAN0ID_5   6  //CAN0 Receive CANID 11Bit  Can0Rec0data[5][0]-Can0Rec0data[5][7]
#define REC_CAN0ID_6   7  //CAN0 Receive CANID 11Bit  Can0Rec0data[6][0]-Can0Rec0data[6][7]
#define REC_CAN0ID_7   8  //CAN0 Receive CANID 11Bit  Can0Rec0data[7][0]-Can0Rec0data[7][7]
#define REC_CAN0ID_8   9  //CAN0 Receive CANID 11Bit  Can0Rec0data[8][0]-Can0Rec0data[8][7]
#define REC_CAN0ID_9   10 //CAN0 Receive CANID 11Bit  Can0Rec0data[9][0]-Can0Rec0data[9][7]
#define REC_CAN0ID_10  11 //CAN0 Receive CANID 11Bit  Can0Rec0data[10][0]-Can0Rec0data[10][7]
#define REC_CAN0ID_11  12 //CAN0 Receive CANID 11Bit  Can0Rec0data[11][0]-Can0Rec0data[11][7]
#define REC_CAN0ID_12  13 //CAN0 Receive CANID 11Bit  Can0Rec0data[12][0]-Can0Rec0data[12][7]
#define REC_CAN0ID_13  14 //CAN0 Receive CANID 11Bit  Can0Rec0data[13][0]-Can0Rec0data[13][7]
#define REC_CAN0ID_14  15 //CAN0 Receive CANID 11Bit  Can0Rec0data[14][0]-Can0Rec0data[14][7]
#define REC_CAN0ID_15  16 //CAN0 Receive CANID 11Bit  Can0Rec0data[15][0]-Can0Rec0data[15][7]
#define REC_CAN0ID_16  17 //CAN0 Receive CANID 11Bit  Can0Rec0data[16][0]-Can0Rec0data[16][7]
#define REC_CAN0ID_17  18 //CAN0 Receive CANID 11Bit  Can0Rec0data[17][0]-Can0Rec0data[17][7]
#define REC_CAN0ID_18  19 //CAN0 Receive CANID 11Bit  Can0Rec0data[18][0]-Can0Rec0data[18][7]
#define REC_CAN0ID_19  20 //CAN0 Receive CANID 11Bit  Can0Rec0data[19][0]-Can0Rec0data[19][7]
#define REC_CAN0ID_20  21 //CAN0 Receive CANID 11Bit  Can0Rec0data[20][0]-Can0Rec0data[20][7]
#define REC_CAN0ID_21  22 //CAN0 Receive CANID 11Bit  Can0Rec0data[21][0]-Can0Rec0data[21][7]
#define REC_CAN0ID_22  23 //CAN0 Receive CANID 11Bit  Can0Rec0data[22][0]-Can0Rec0data[22][7]
#define REC_CAN0ID_23  24 //CAN0 Receive CANID 11Bit  Can0Rec0data[23][0]-Can0Rec0data[23][7]
#define REC_CAN0ID_24  25 //CAN0 Receive CANID 11Bit  Can0Rec0data[24][0]-Can0Rec0data[24][7]
#define REC_CAN0ID_25  26 //CAN0 Receive CANID 11Bit  Can0Rec0data[25][0]-Can0Rec0data[25][7]
#define REC_CAN0ID_26  27 //CAN0 Receive CANID 11Bit  Can0Rec0data[26][0]-Can0Rec0data[26][7]
#define REC_CAN0ID_27  28 //CAN0 Receive CANID 11Bit  Can0Rec0data[27][0]-Can0Rec0data[27][7]
#define REC_CAN0ID_28  29 //CAN0 Receive CANID 11Bit  Can0Rec0data[28][0]-Can0Rec0data[28][7]
#define REC_CAN0ID_29  30 //CAN0 Receive CANID 11Bit  Can0Rec0data[29][0]-Can0Rec0data[29][7]
#define REC_CAN0ID_30  31 //CAN0 Receive CANID 11Bit  Can0Rec0data[30][0]-Can0Rec0data[30][7]
#define REC_CAN0ID_31  32 //CAN0 Receive CANID 11Bit  Can0Rec0data[31][0]-Can0Rec0data[31][7]
#define REC_CAN0ID_32  33 //CAN0 Receive CANID 11Bit  Can0Rec0data[32][0]-Can0Rec0data[32][7]
#define REC_CAN0ID_33  34 //CAN0 Receive CANID 11Bit  Can0Rec0data[33][0]-Can0Rec0data[33][7]
#define REC_CAN0ID_34  35 //CAN0 Receive CANID 11Bit  Can0Rec0data[34][0]-Can0Rec0data[34][7]
#define REC_CAN0ID_35  36 //CAN0 Receive CANID 11Bit  Can0Rec0data[35][0]-Can0Rec0data[35][7]
#define REC_CAN0ID_36  37 //CAN0 Receive CANID 11Bit  Can0Rec0data[36][0]-Can0Rec0data[36][7]
#define REC_CAN0ID_37  38 //CAN0 Receive CANID 11Bit  Can0Rec0data[37][0]-Can0Rec0data[37][7]
#define REC_CAN0ID_38  39 //CAN0 Receive CANID 11Bit  Can0Rec0data[38][0]-Can0Rec0data[38][7]
#define REC_CAN0ID_39  40 //CAN0 Receive CANID 11Bit  Can0Rec0data[39][0]-Can0Rec0data[39][7]
#define REC_CAN0ID_40  41 //CAN0 Receive CANID 11Bit  Can0Rec0data[40][0]-Can0Rec0data[40][7]
#define REC_CAN0ID_41  42 //CAN0 Receive CANID 11Bit  Can0Rec0data[41][0]-Can0Rec0data[41][7]
#define REC_CAN0ID_42  43 //CAN0 Receive CANID 11Bit  Can0Rec0data[42][0]-Can0Rec0data[42][7]
#define REC_CAN0ID_43  44 //CAN0 Receive CANID 11Bit  Can0Rec0data[43][0]-Can0Rec0data[43][7]
#define REC_CAN0ID_44  45 //CAN0 Receive CANID 11Bit  Can0Rec0data[44][0]-Can0Rec0data[44][7]
#define REC_CAN0ID_45  46 //CAN0 Receive CANID 11Bit  Can0Rec0data[45][0]-Can0Rec0data[45][7]
#define REC_CAN0ID_46  47 //CAN0 Receive CANID 11Bit  Can0Rec0data[46][0]-Can0Rec0data[46][7]
#define REC_CAN0ID_47  48 //CAN0 Receive CANID 11Bit  Can0Rec0data[47][0]-Can0Rec0data[47][7]
#define REC_CAN0ID_48  49 //CAN0 Receive CANID 11Bit  Can0Rec0data[48][0]-Can0Rec0data[48][7]
#define REC_CAN0ID_49  50 //CAN0 Receive CANID 11Bit  Can0Rec0data[49][0]-Can0Rec0data[49][7]
#define REC_CAN0ID_50  51 //CAN0 Receive CANID 11Bit  Can0Rec0data[50][0]-Can0Rec0data[50][7]
#define REC_CAN0ID_51  52 //CAN0 Receive CANID 11Bit  Can0Rec0data[51][0]-Can0Rec0data[51][7]
#define REC_CAN0ID_52  53 //CAN0 Receive CANID 11Bit  Can0Rec0data[52][0]-Can0Rec0data[52][7]
#define REC_CAN0ID_53  54 //CAN0 Receive CANID 11Bit  Can0Rec0data[53][0]-Can0Rec0data[53][7]
#define REC_CAN0ID_54  55 //CAN1 Receive CANID 11Bit  Can0Rec0data[54][0]-Can0Rec0data[54][7]
#define REC_CAN0ID_55  56 //CAN0 Receive CANID 11Bit  Can0Rec0data[55][0]-Can0Rec0data[55][7]
#define REC_CAN0ID_56  57 //CAN0 Receive CANID 11Bit  Can0Rec0data[56][0]-Can0Rec0data[56][7]
#define REC_CAN0ID_57  58 //CAN0 Receive CANID 11Bit  Can0Rec0data[57][0]-Can0Rec0data[57][7]
#define REC_CAN0ID_58  59 //CAN0 Receive CANID 11Bit  Can0Rec0data[58][0]-Can0Rec0data[58][7]
#define REC_CAN0ID_59  60 //CAN0 Receive CANID 11Bit  Can0Rec0data[59][0]-Can0Rec0data[59][7]
#define REC_CAN0ID_60  61 //CAN0 Receive CANID 11Bit  Can0Rec0data[60][0]-Can0Rec0data[60][7]
#define REC_CAN0ID_61  62 //CAN0 Receive CANID 11Bit  Can0Rec0data[61][0]-Can0Rec0data[61][7]
#define REC_CAN0ID_62  63 //CAN0 Receive CANID 11Bit  Can0Rec0data[62][0]-Can0Rec0data[62][7]
#define REC_CAN0ID_63  64 //CAN0 Receive CANID 11Bit  Can0Rec0data[63][0]-Can0Rec0data[63][7]

#define REC_CAN1ID_0   1  //CAN1 Receive CANID 11Bit  Can1Recdata[0][0]-Can1Recdata[0][7]
#define REC_CAN1ID_1   2  //CAN1 Receive CANID 11Bit  Can1Recdata[1][0]-Can1Recdata[1][7]
#define REC_CAN1ID_2   3  //CAN1 Receive CANID 11Bit  Can1Recdata[2][0]-Can1Recdata[2][7]
#define REC_CAN1ID_3   4  //CAN1 Receive CANID 11Bit  Can1Recdata[3][0]-Can1Recdata[3][7]
#define REC_CAN1ID_4   5  //CAN1 Receive CANID 11Bit  Can1Recdata[4][0]-Can1Recdata[4][7]
#define REC_CAN1ID_5   6  //CAN1 Receive CANID 11Bit  Can1Recdata[5][0]-Can1Recdata[5][7]
#define REC_CAN1ID_6   7  //CAN1 Receive CANID 11Bit  Can1Recdata[6][0]-Can1Recdata[6][7]
#define REC_CAN1ID_7   8  //CAN1 Receive CANID 11Bit  Can1Recdata[7][0]-Can1Recdata[7][7]
#define REC_CAN1ID_8   9  //CAN1 Receive CANID 11Bit  Can1Recdata[8][0]-Can1Recdata[8][7]
#define REC_CAN1ID_9   10 //CAN1 Receive CANID 11Bit  Can1Recdata[9][0]-Can1Recdata[9][7]

#define TRS_CAN1ID_0   1   //CAN1 MessageObject10 CANID 11Bit  Can1Revdata[0][0]-Can1Revdata[0][7]
#define TRS_CAN1ID_1   2   //CAN1 MessageObject11 CANID 11Bit  Can1Revdata[1][0]-Can1Revdata[1][7]
#define TRS_CAN1ID_2   3   //CAN1 MessageObject12 CANID 11Bit  Can1Revdata[2][0]-Can1Revdata[2][7]
#define TRS_CAN1ID_3   4   //CAN1 MessageObject13 CANID 11Bit  Can1Revdata[3][0]-Can1Revdata[3][7]
#define TRS_CAN1ID_4   5   //CAN1 MessageObject14 CANID 11Bit  Rev
#define TRS_CAN1ID_5   6   //CAN1 MessageObject15 CANID 11Bit  Rev

#define TRS_CAN0ID_0   0x666   //CAN0 MessageObject4 CANID 11Bit  Can0Revdata[0][0]-Can0Revdata[0][7]
#define TRS_CAN0ID_1   0x667   //CAN0 MessageObject5 CANID 11Bit  Can0Revdata[1][0]-Can0Revdata[1][7]
#define TRS_CAN0ID_2   0x668   //CAN0 MessageObject6 CANID 11Bit  Can0Revdata[2][0]-Can0Revdata[2][7]
#define TRS_CAN0ID_3   0x669   //CAN0 MessageObject7 CANID 11Bit  Can0Revdata[3][0]-Can0Revdata[3][7]
#define TRS_CAN0ID_4   5   //CAN0 MessageObject8 CANID 11Bit  Rev
#define TRS_CAN0ID_5   6   //CAN0 MessageObject9 CANID 11Bit  Rev

#define CAN0TRS0_ENABLE  0 //enable TRS_CAN0ID_0 message send 
#define CAN0TRS1_ENABLE  0 //enable TRS_CAN0ID_1 message send
#define CAN0TRS2_ENABLE  0 //enable TRS_CAN0ID_2 message send
#define CAN0TRS3_ENABLE  0 //enable TRS_CAN0ID_3 message send
#define CAN0TRS4_ENABLE  0 //enable TRS_CAN0ID_4 message send
#define CAN0TRS5_ENABLE  0 //enable TRS_CAN0ID_5 message send

#define CAN1TRS0_ENABLE  0 //enable TRS_CAN1ID_0 message send
#define CAN1TRS1_ENABLE  0 //enable TRS_CAN1ID_1 message send
#define CAN1TRS2_ENABLE  0 //enable TRS_CAN1ID_2 message send
#define CAN1TRS3_ENABLE  0 //enable TRS_CAN1ID_3 message send
#define CAN1TRS4_ENABLE  0 //enable TRS_CAN1ID_4 message send
#define CAN1TRS5_ENABLE  0 //enable TRS_CAN1ID_5 message send

#define RIGHTMSG  0x0FF0

#define CAN0ID_NUM    (64) //CAN0 receive ID number
#define CAN1ID_NUM    (10) //CAN1 receive ID number
#define CAN_DATA_NUM  (8)

#if 1
CAN_COM_EXT INT16U    CAN0ID_u16_Sig; 
CAN_COM_EXT INT16U    CAN1ID_u16_Sig; 
CAN_COM_EXT INT16U    Can0ID_u16a64_Sig[64];
CAN_COM_EXT INT16U    Can1ID_u16a10_Sig[10];
#endif

typedef struct{
	INT8U gear;
	INT8U turnLamp;
	
	INT16U speed;
	INT16U yawRate;
	INT16U accelerationY;
	INT16U accelerationZ;
	
	INT16S steeringAngle;
	INT16U roadCurvatureRadius;	
}T_CAN_COM_VEHICLE;

typedef struct{
	INT16S longtitudeDistance;
	INT16S lateralDistance;
	INT16U longtitudeVelocity;
	INT16U lateralVelocity;	
}T_CAN_COM_TARGET;

typedef struct{
	T_CAN_COM_TARGET   tTarget;
	T_CAN_COM_VEHICLE  tVehicle;
}T_CAN_COM;

/**** Declaration of functions ****/
CAN_COM_EXT void CanCom_Init(void);
CAN_COM_EXT void CanCom_DeInit(void);
CAN_COM_EXT void CanCom_TransceiverEnable(void);
CAN_COM_EXT void CanCom_TransceiverDisable(void);
CAN_COM_EXT void CanCom_CanTx(void);
CAN_COM_EXT void CanCom_Can0RecDeal(INT16U canId);
CAN_COM_EXT void CanCom_Can1RecDeal(void);
CAN_COM_EXT void CanCom_SendMsg(INT8U ubObjNr, INT8U *ubpubData, INT8U Len);
CAN_COM_EXT INT8U CanCom_ReceiveMsg(INT8U ubObjNr, INT8U *ubpubData, INT8U *Len);
CAN_COM_EXT const T_CAN_COM* CanCom_VehicleData(void);
#endif /* _CAN_COM_H_ */
