/*
 * Bus_Line.c
 *
 *  Created on: 2015-5-21
 *      Author: zhangguangyao
 */
#define   BUS_LINE_GLOBALS
#include "MAIN.h"
#include "busline.h"
/*
*********************************************************************************************************
*                                                MACROS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                               VARIABLES
*********************************************************************************************************
*/
/*-------------------------------CAN0 ID�����ʼ��--------------------------------*/
INT16U  Can0ID_u16a64_Sig[64]=
{
REC_CAN0ID_0, REC_CAN0ID_1, REC_CAN0ID_2, REC_CAN0ID_3, REC_CAN0ID_4, REC_CAN0ID_5, REC_CAN0ID_6, REC_CAN0ID_7,
REC_CAN0ID_8, REC_CAN0ID_9, REC_CAN0ID_10,REC_CAN0ID_11,REC_CAN0ID_12,REC_CAN0ID_13,REC_CAN0ID_14,REC_CAN0ID_15,
REC_CAN0ID_16,REC_CAN0ID_17,REC_CAN0ID_18,REC_CAN0ID_19,REC_CAN0ID_20,REC_CAN0ID_21,REC_CAN0ID_22,REC_CAN0ID_23,
REC_CAN0ID_24,REC_CAN0ID_25,REC_CAN0ID_26,REC_CAN0ID_27,REC_CAN0ID_28,REC_CAN0ID_29,REC_CAN0ID_30,REC_CAN0ID_31,
REC_CAN0ID_32,REC_CAN0ID_33,REC_CAN0ID_34,REC_CAN0ID_35,REC_CAN0ID_36,REC_CAN0ID_37,REC_CAN0ID_38,REC_CAN0ID_39,
REC_CAN0ID_48,REC_CAN0ID_49,REC_CAN0ID_50,REC_CAN0ID_51,REC_CAN0ID_52,REC_CAN0ID_53,REC_CAN0ID_54,REC_CAN0ID_55,
REC_CAN0ID_56,REC_CAN0ID_57,REC_CAN0ID_58,REC_CAN0ID_59,REC_CAN0ID_60,REC_CAN0ID_61,REC_CAN0ID_62,REC_CAN0ID_63
};
/*-------------------------------CAN1 ID�����ʼ��--------------------------------*/
INT16U  Can1ID_u16a10_Sig[10]=
{
REC_CAN1ID_0,REC_CAN1ID_1,REC_CAN1ID_2,REC_CAN1ID_3,REC_CAN1ID_4,
REC_CAN1ID_5,REC_CAN1ID_6,REC_CAN1ID_7,REC_CAN1ID_8,REC_CAN1ID_9
};


/*
*********************************************************************************************************
*                                          FUNCTION PROTOTYPES
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                             C ENTRY POINT
*********************************************************************************************************
*/

/*!************************************************************************************
*	@fn	        void CanEnbale_v_g(void)
*	@brief	    CAN Transfer ʹ�ܺ���
*	@author     Matt Zhang
*	@param[in]	Null
*	@return	    Null
*	@note       ��iso.c��ISOInit_v_g()�����е���
*	@Data       2019-03-12
****************************************************************************************/
void CanEnbale_v_g(void)
{
	CAN1_ENABLE_ON;//CAN0 ENABLE
	CAN2_ENABLE_ON;//CAN1 ENABLE
}
/*!************************************************************************************
*	@fn	        void CanSendMsg_v_g(INT8U ubObjNr, INT8U *ubpubData,INT8U Len)
*	@brief	    CAN ���ͺ���
*	@author     Matt Zhang
*	@param[in]	ubObjNr����MessgeObject;ubpubData����������;Len�����ͳ���
*	@return	    Null
*	@note
*	@Data       2019-03-12
****************************************************************************************/
void  CanSendMsg_v_g(INT8U ubObjNr, INT8U *ubpubData,INT8U Len)
{
 ubyte len;
 len = Len + 0x10;

 CAN_HWOBJ[ubObjNr].uwMOFCRH &= (~(uword)0x0F00);//���ȸ�ֵ
 CAN_HWOBJ[ubObjNr].uwMOFCRH |= (((uword)(len & 0x0F)) << 8);//���ȸ�ֵ
 CAN_vLoadData(ubObjNr,ubpubData);//����CAN��������
 CAN_vTransmit(ubObjNr);//����ָ��
}
/*!************************************************************************************
*	@fn	        INT8U  CanRecMsg_v_g(INT8U ubObjNr, INT8U *ubpubData,INT8U *Len)
*	@brief	    CAN��ѯ���պ���
*	@author     Matt Zhang
*	@param[in]	ubObjNr����MessgeObject;ubpubData�����������;Len������ճ���
*	@return	    1����������ݳɹ�;0����δ�����ݽ��յ�
*	@note
*	@Data       2019-03-12
****************************************************************************************/
INT8U  CanRecMsg_v_g(INT8U ubObjNr, INT8U *ubpubData,INT8U *Len)
{
	ubyte i;
if(CAN_ubNewData(ubObjNr))//�ж�MessgeObject�Ƿ����µ����ݽ��յ�
{
	Len[0]= (ubyte)((CAN_HWOBJ[ubObjNr].uwMOFCRH & 0x0F00) >> 8); //��ȡ���յ����ݳ���
	for( i = 0; i <= Len[0]; i++ )
	{
		ubpubData[i]=CAN_HWOBJ[ubObjNr].ubData[i];//��ȡ���յ�����
	}
	CAN_HWOBJ[ubObjNr].uwMOCTRL = 0x0008;//�����־λ
return 1;
}
return 0;
}
/*!************************************************************************************
*	@fn	        void Can0RecDeal_v_g(void)
*	@brief	    Can0�������ݴ�����
*	@author     Matt Zhang
*	@param[in]	CanId��CAN0���յ�CANID
*	@return	    Null
*	@note       ��CAN.c��CAN_viSRN0()�����е���
*	@Data       2019-03-12
****************************************************************************************/
void    Can0RecDeal_v_g(INT16U CanId)
{
INT8U i, Can_i;
INT16U acce_y;

for(i=0;i<CAN0ID_NUM;i++)
{
	/*******���ײ��״�����ID 0x60A*******/
	if(CanId==Can0ID_u16a64_Sig[0])//�жϽ���ID����ȡ��Ӧ������ݵ�������ʼԪ��
	{
		Can0Rec0data[0][0]=CAN_HWOBJ[0].ubData[0];//��ȡCAN0��0��MessageObject��0Byte��ֵ
		Can0Rec0data[0][1]=CAN_HWOBJ[0].ubData[1];//��ȡCAN0��0��MessageObject��1Byte��ֵ
		Can0Rec0data[0][2]=CAN_HWOBJ[0].ubData[2];//��ȡCAN0��0��MessageObject��2Byte��ֵ
		Can0Rec0data[0][3]=CAN_HWOBJ[0].ubData[3];//��ȡCAN0��0��MessageObject��3Byte��ֵ
		/*******radar data process*******/
		VCU_BrkPdlSts = (Can0Rec0data[0][0]>>4)&0x01;
	break;
	}

	/*******************���ײ��״�����ID 0x60B**************************/
	if(CanId==Can0ID_u16a64_Sig[1])//�жϽ���ID����ȡ��Ӧ������ݵ�������ʼԪ��
	{
		Can0Rec0data[1][0]=CAN_HWOBJ[0].ubData[0];//��ȡCAN0��0��MessageObject��0Byte��ֵ
		Can0Rec0data[1][1]=CAN_HWOBJ[0].ubData[1];//��ȡCAN0��0��MessageObject��1Byte��ֵ
		Can0Rec0data[1][2]=CAN_HWOBJ[0].ubData[2];//��ȡCAN0��0��MessageObject��2Byte��ֵ
		Can0Rec0data[1][3]=CAN_HWOBJ[0].ubData[3];//��ȡCAN0��0��MessageObject��3Byte��ֵ
		Can0Rec0data[1][4]=CAN_HWOBJ[0].ubData[4];//��ȡCAN0��0��MessageObject��4Byte��ֵ
		Can0Rec0data[1][5]=CAN_HWOBJ[0].ubData[5];//��ȡCAN0��0��MessageObject��5Byte��ֵ
		Can0Rec0data[1][6]=CAN_HWOBJ[0].ubData[6];//��ȡCAN0��0��MessageObject��6Byte��ֵ
		Can0Rec0data[1][7]=CAN_HWOBJ[0].ubData[7];//��ȡCAN0��0��MessageObject��7Byte��ֵ

		VCU_VehOperatingMd = (Can0Rec0data[1][0]>>2)&0x07;
	break;
	}

	if(CanId==Can0ID_u16a64_Sig[2])//�жϽ���ID����ȡ��Ӧ������ݵ�������ʼԪ��
	{
		Can0Rec0data[2][0]=CAN_HWOBJ[0].ubData[0];//��ȡCAN0��0��MessageObject��0Byte��ֵ
		Can0Rec0data[2][1]=CAN_HWOBJ[0].ubData[1];//��ȡCAN0��0��MessageObject��1Byte��ֵ
		Can0Rec0data[2][2]=CAN_HWOBJ[0].ubData[2];//��ȡCAN0��0��MessageObject��2Byte��ֵ
		Can0Rec0data[2][3]=CAN_HWOBJ[0].ubData[3];//��ȡCAN0��0��MessageObject��3Byte��ֵ
		Can0Rec0data[2][4]=CAN_HWOBJ[0].ubData[4];//��ȡCAN0��0��MessageObject��4Byte��ֵ
		Can0Rec0data[2][5]=CAN_HWOBJ[0].ubData[5];//��ȡCAN0��0��MessageObject��5Byte��ֵ
		Can0Rec0data[2][6]=CAN_HWOBJ[0].ubData[6];//��ȡCAN0��0��MessageObject��6Byte��ֵ
		Can0Rec0data[2][7]=CAN_HWOBJ[0].ubData[7];//��ȡCAN0��0��MessageObject��7Byte��ֵ

		MCU_MotActuToq = Can0Rec0data[2][0]*256 +Can0Rec0data[2][1];
		MCU_MotActuSpd = Can0Rec0data[2][2]*256 +Can0Rec0data[2][3];
		//MCU_MotToqLmt = Can0Rec0data[2][4]*256 +Can0Rec0data[2][5];
		break;
	}

//*****************************������ȡ���ݳ��ٺͷ�����ת��**********************************//
	if(CanId==Can0ID_u16a64_Sig[4])//�жϽ���ID����ȡ��Ӧ������ݵ�������ʼԪ��
		{
			Can0Rec0data[4][0]=CAN_HWOBJ[0].ubData[0];//��ȡCAN0��0��MessageObject��0Byte��ֵ
			Can0Rec0data[4][1]=CAN_HWOBJ[0].ubData[1];//��ȡCAN0��0��MessageObject��1Byte��ֵ
			Can0Rec0data[4][2]=CAN_HWOBJ[0].ubData[2];//��ȡCAN0��0��MessageObject��2Byte��ֵ
			Can0Rec0data[4][3]=CAN_HWOBJ[0].ubData[3];//��ȡCAN0��0��MessageObject��3Byte��ֵ
			Can0Rec0data[4][4]=CAN_HWOBJ[0].ubData[4];//��ȡCAN0��0��MessageObject��4Byte��ֵ
			Can0Rec0data[4][5]=CAN_HWOBJ[0].ubData[5];//��ȡCAN0��0��MessageObject��5Byte��ֵ
			Can0Rec0data[4][6]=CAN_HWOBJ[0].ubData[6];//��ȡCAN0��0��MessageObject��6Byte��ֵ
			Can0Rec0data[4][7]=CAN_HWOBJ[0].ubData[7];//��ȡCAN0��0��MessageObject��7Byte��ֵ
			//********����Ϊ���ݽ���**********//
			TargetPressure = Can0Rec0data[4][2] ;
			AutoMode =(INT8U)(Can0Rec0data[4][0] >>3 & 0x01);
			AutoBrakeEnable =(INT8U)(Can0Rec0data[4][0] >>7 & 0x01);
			break;
		}


	//*****************************��MOBILEYE��ȡ����ID 0x738***************************//
		if(CanId==Can0ID_u16a64_Sig[5])//�жϽ���ID����ȡ��Ӧ������ݵ�������ʼԪ��
			{
				Can0Rec0data[5][0]=CAN_HWOBJ[0].ubData[0];//��ȡCAN0��0��MessageObject��0Byte��ֵ
				Can0Rec0data[5][1]=CAN_HWOBJ[0].ubData[1];//��ȡCAN0��0��MessageObject��1Byte��ֵ
				Can0Rec0data[5][2]=CAN_HWOBJ[0].ubData[2];//��ȡCAN0��0��MessageObject��2Byte��ֵ
				Can0Rec0data[5][3]=CAN_HWOBJ[0].ubData[3];//��ȡCAN0��0��MessageObject��3Byte��ֵ
				Can0Rec0data[5][4]=CAN_HWOBJ[0].ubData[4];//��ȡCAN0��0��MessageObject��4Byte��ֵ
				Can0Rec0data[5][5]=CAN_HWOBJ[0].ubData[5];//��ȡCAN0��0��MessageObject��5Byte��ֵ
				Can0Rec0data[5][6]=CAN_HWOBJ[0].ubData[6];//��ȡCAN0��0��MessageObject��6Byte��ֵ
				Can0Rec0data[5][7]=CAN_HWOBJ[0].ubData[7];//��ȡCAN0��0��MessageObject��7Byte��ֵ
				//********����Ϊ���ݽ���**********//

				MCU_MotToqLmt = Can0Rec0data[5][0]*256 +Can0Rec0data[5][1];
				VCU_AllowFeedbackFlag = Can0Rec0data[5][6] & 0x01;


				break;
			}
//*****************************��MOBILEYE��ȡ����ID 0x739***************************//
		 if(CanId==Can0ID_u16a64_Sig[6])//�жϽ���ID����ȡ��Ӧ������ݵ�������ʼԪ��
			{
				Can0Rec0data[6][0]=CAN_HWOBJ[0].ubData[0];//��ȡCAN0��0��MessageObject��0Byte��ֵ
				Can0Rec0data[6][1]=CAN_HWOBJ[0].ubData[1];//��ȡCAN0��0��MessageObject��1Byte��ֵ
				Can0Rec0data[6][2]=CAN_HWOBJ[0].ubData[2];//��ȡCAN0��0��MessageObject��2Byte��ֵ
	     		Can0Rec0data[6][3]=CAN_HWOBJ[0].ubData[3];//��ȡCAN0��0��MessageObject��3Byte��ֵ
				Can0Rec0data[6][4]=CAN_HWOBJ[0].ubData[4];//��ȡCAN0��0��MessageObject��4Byte��ֵ
				Can0Rec0data[6][5]=CAN_HWOBJ[0].ubData[5];//��ȡCAN0��0��MessageObject��5Byte��ֵ
				Can0Rec0data[6][6]=CAN_HWOBJ[0].ubData[6];//��ȡCAN0��0��MessageObject��6Byte��ֵ
				Can0Rec0data[6][7]=CAN_HWOBJ[0].ubData[7];//��ȡCAN0��0��MessageObject��7Byte��ֵ
				//********����Ϊ���ݽ���**********//
				VCU_VehicleSpeed = Can0Rec0data[6][5] *256 + (Can0Rec0data[6][6]>>3) & 0x1f;


				break;
			}
/*****************************��MOBILEYE��ȡ����ID 0x73A***************************/
		 if(CanId==Can0ID_u16a64_Sig[7])//�жϽ���ID����ȡ��Ӧ������ݵ�������ʼԪ��
		 	 {
		 	    Can0Rec0data[7][0]=CAN_HWOBJ[0].ubData[0];//��ȡCAN0��0��MessageObject��0Byte��ֵ
		 		Can0Rec0data[7][1]=CAN_HWOBJ[0].ubData[1];//��ȡCAN0��0��MessageObject��1Byte��ֵ
		 		Can0Rec0data[7][2]=CAN_HWOBJ[0].ubData[2];//��ȡCAN0��0��MessageObject��2Byte��ֵ
		 	    Can0Rec0data[7][3]=CAN_HWOBJ[0].ubData[3];//��ȡCAN0��0��MessageObject��3Byte��ֵ
		 		Can0Rec0data[7][4]=CAN_HWOBJ[0].ubData[4];//��ȡCAN0��0��MessageObject��4Byte��ֵ
		 		Can0Rec0data[7][5]=CAN_HWOBJ[0].ubData[5];//��ȡCAN0��0��MessageObject��5Byte��ֵ
		 		Can0Rec0data[7][6]=CAN_HWOBJ[0].ubData[6];//��ȡCAN0��0��MessageObject��6Byte��ֵ
		 		Can0Rec0data[7][7]=CAN_HWOBJ[0].ubData[7];//��ȡCAN0��0��MessageObject��7Byte��ֵ
		 				//********����Ϊ���ݽ���**********//
		 		Receive_ACC = (Can0Rec0data[7][3] & 0x0F)*256 + Can0Rec0data[7][4];

		 		break;
		 	}
/*****************************��MOBILEYE��ȡ����ID 0x73B***************************/
		 if(CanId==Can0ID_u16a64_Sig[8])//�жϽ���ID����ȡ��Ӧ������ݵ�������ʼԪ��
		  	 {
		 	    Can0Rec0data[8][0]=CAN_HWOBJ[0].ubData[0];//��ȡCAN0��0��MessageObject��0Byte��ֵ
		 		Can0Rec0data[8][1]=CAN_HWOBJ[0].ubData[1];//��ȡCAN0��0��MessageObject��1Byte��ֵ
		 		Can0Rec0data[8][2]=CAN_HWOBJ[0].ubData[2];//��ȡCAN0��0��MessageObject��2Byte��ֵ
		 	    Can0Rec0data[8][3]=CAN_HWOBJ[0].ubData[3];//��ȡCAN0��0��MessageObject��3Byte��ֵ
		 		Can0Rec0data[8][4]=CAN_HWOBJ[0].ubData[4];//��ȡCAN0��0��MessageObject��4Byte��ֵ
		 		Can0Rec0data[8][5]=CAN_HWOBJ[0].ubData[5];//��ȡCAN0��0��MessageObject��5Byte��ֵ
		 		Can0Rec0data[8][6]=CAN_HWOBJ[0].ubData[6];//��ȡCAN0��0��MessageObject��6Byte��ֵ
		 		Can0Rec0data[8][7]=CAN_HWOBJ[0].ubData[7];//��ȡCAN0��0��MessageObject��7Byte��ֵ
		 		 		//********����Ϊ���ݽ���**********//
		 		APA_BrakeFlag = (Can0Rec0data[8][5] >>7) & 0x01 ;
		 		BrakeSysMode = APA_BrakeFlag;
		 		APA_TargetPrs = Can0Rec0data[8][4];
		 		APA_Count = 0;
		 		break;
		 	}
/*****************************��MOBILEYE��ȡ����ID 0x766***************************/
		 if(CanId==Can0ID_u16a64_Sig[9])//�жϽ���ID����ȡ��Ӧ������ݵ�������ʼԪ��
		 	 {
		 	   Can0Rec0data[9][0]=CAN_HWOBJ[0].ubData[0];//��ȡCAN0��0��MessageObject��0Byte��ֵ
		       Can0Rec0data[9][1]=CAN_HWOBJ[0].ubData[1];//��ȡCAN0��0��MessageObject��1Byte��ֵ
	    	   Can0Rec0data[9][2]=CAN_HWOBJ[0].ubData[2];//��ȡCAN0��0��MessageObject��2Byte��ֵ
		 	   Can0Rec0data[9][3]=CAN_HWOBJ[0].ubData[3];//��ȡCAN0��0��MessageObject��3Byte��ֵ
		       Can0Rec0data[9][4]=CAN_HWOBJ[0].ubData[4];//��ȡCAN0��0��MessageObject��4Byte��ֵ
		 	   Can0Rec0data[9][5]=CAN_HWOBJ[0].ubData[5];//��ȡCAN0��0��MessageObject��5Byte��ֵ
		 	   Can0Rec0data[9][6]=CAN_HWOBJ[0].ubData[6];//��ȡCAN0��0��MessageObject��6Byte��ֵ
		 	   Can0Rec0data[9][7]=CAN_HWOBJ[0].ubData[7];//��ȡCAN0��0��MessageObject��7Byte��ֵ
		 		 		 		//********����Ϊ���ݽ���**********//
		 	  APA_EmgBrakeFlag = (Can0Rec0data[9][0] >>4) & 0x0F;
		 		 break;
		 	}

/*****************************��MOBILEYE��ȡ����ID 0x767***************************/
		 if(CanId==Can0ID_u16a64_Sig[10])//�жϽ���ID����ȡ��Ӧ������ݵ�������ʼԪ��
		 	{
		 	   Can0Rec0data[8][10]=CAN_HWOBJ[0].ubData[0];//��ȡCAN0��0��MessageObject��0Byte��ֵ
		 	   Can0Rec0data[8][10]=CAN_HWOBJ[0].ubData[1];//��ȡCAN0��0��MessageObject��1Byte��ֵ
		 	   Can0Rec0data[8][10]=CAN_HWOBJ[0].ubData[2];//��ȡCAN0��0��MessageObject��2Byte��ֵ
		 	   Can0Rec0data[8][10]=CAN_HWOBJ[0].ubData[3];//��ȡCAN0��0��MessageObject��3Byte��ֵ
		 	   Can0Rec0data[8][10]=CAN_HWOBJ[0].ubData[4];//��ȡCAN0��0��MessageObject��4Byte��ֵ
		 	   Can0Rec0data[8][10]=CAN_HWOBJ[0].ubData[5];//��ȡCAN0��0��MessageObject��5Byte��ֵ
		       Can0Rec0data[8][10]=CAN_HWOBJ[0].ubData[6];//��ȡCAN0��0��MessageObject��6Byte��ֵ
		 	   Can0Rec0data[8][10]=CAN_HWOBJ[0].ubData[7];//��ȡCAN0��0��MessageObject��7Byte��ֵ
		 		 		 		//********����Ϊ���ݽ���**********//

		 		 break;
		 		 	}
/*****************************��MOBILEYE��ȡ����ID 0x768***************************/
		  if(CanId==Can0ID_u16a64_Sig[11])//�жϽ���ID����ȡ��Ӧ������ݵ�������ʼԪ��
		 	 {
		 	    Can0Rec0data[11][0]=CAN_HWOBJ[0].ubData[0];//��ȡCAN0��0��MessageObject��0Byte��ֵ
		 	    Can0Rec0data[11][1]=CAN_HWOBJ[0].ubData[1];//��ȡCAN0��0��MessageObject��1Byte��ֵ
		 	    Can0Rec0data[11][2]=CAN_HWOBJ[0].ubData[2];//��ȡCAN0��0��MessageObject��2Byte��ֵ
		 	    Can0Rec0data[11][3]=CAN_HWOBJ[0].ubData[3];//��ȡCAN0��0��MessageObject��3Byte��ֵ
		 		Can0Rec0data[11][4]=CAN_HWOBJ[0].ubData[4];//��ȡCAN0��0��MessageObject��4Byte��ֵ
		 	    Can0Rec0data[11][5]=CAN_HWOBJ[0].ubData[5];//��ȡCAN0��0��MessageObject��5Byte��ֵ
		 		Can0Rec0data[11][6]=CAN_HWOBJ[0].ubData[6];//��ȡCAN0��0��MessageObject��6Byte��ֵ
		 		Can0Rec0data[11][7]=CAN_HWOBJ[0].ubData[7];//��ȡCAN0��0��MessageObject��7Byte��ֵ
		 				 		 		 		//********����Ϊ���ݽ���**********//
		 		 break;
		 		    }
/*****************************��MOBILEYE��ȡ����ID 0x769***********************/
          if(CanId==Can0ID_u16a64_Sig[12])//�жϽ���ID����ȡ��Ӧ������ݵ�������ʼԪ��
		 	 {
		 	    Can0Rec0data[12][0]=CAN_HWOBJ[0].ubData[0];//��ȡCAN0��0��MessageObject��0Byte��ֵ
		 	    Can0Rec0data[12][1]=CAN_HWOBJ[0].ubData[1];//��ȡCAN0��0��MessageObject��1Byte��ֵ
		 	    Can0Rec0data[12][2]=CAN_HWOBJ[0].ubData[2];//��ȡCAN0��0��MessageObject��2Byte��ֵ
		 	    Can0Rec0data[12][3]=CAN_HWOBJ[0].ubData[3];//��ȡCAN0��0��MessageObject��3Byte��ֵ
		 	    Can0Rec0data[12][4]=CAN_HWOBJ[0].ubData[4];//��ȡCAN0��0��MessageObject��4Byte��ֵ
		 		Can0Rec0data[12][5]=CAN_HWOBJ[0].ubData[5];//��ȡCAN0��0��MessageObject��5Byte��ֵ
		 		Can0Rec0data[12][6]=CAN_HWOBJ[0].ubData[6];//��ȡCAN0��0��MessageObject��6Byte��ֵ
		 	    Can0Rec0data[12][7]=CAN_HWOBJ[0].ubData[7];//��ȡCAN0��0��MessageObject��7Byte��ֵ

             	//********����Ϊ���ݽ���**********//

		 		 break;
		 	 }
    }
}

/*!************************************************************************************
*	@fn	        void Can1RecDeal_v_g(void)
*	@brief	    Can1�������ݴ�����
*	@author     Matt Zhang
*	@param[in]	Null
*	@return	    Null
*	@note       ��task.c��task3()�����е���
*	@Data       2019-03-12
****************************************************************************************/
void    Can1RecDeal_v_g()
{
INT8U i, Can_i;
INT16U acce_y;
INT16S realangle;
if(CAN_ubNewData(1))//�ж�MessgeObject1�Ƿ����µ����ݽ��յ�
{
	CAN1ID_u16_Sig=CAN_MOAR1H;//��ȡCANID
	CAN1ID_u16_Sig=(CAN1ID_u16_Sig>>2)&0x7FF;//CANID��ֵ����

	for(i=0;i<CAN1ID_NUM;i++)
	{
		if(CAN1ID_u16_Sig==Can1ID_u16a10_Sig[0])//�жϽ���ID����ȡ��Ӧ������ݵ�������ʼԪ��
		{
			Can1Recdata[0][0]=CAN_HWOBJ[1].ubData[0];//��ȡCAN1��1��MessageObject��0Byte��ֵ
			Can1Recdata[0][1]=CAN_HWOBJ[1].ubData[1];//��ȡCAN1��1��MessageObject��1Byte��ֵ
			Can1Recdata[0][2]=CAN_HWOBJ[1].ubData[2];//��ȡCAN1��1��MessageObject��2Byte��ֵ
			Can1Recdata[0][3]=CAN_HWOBJ[1].ubData[3];//��ȡCAN1��1��MessageObject��3Byte��ֵ
			Can1Recdata[0][4]=CAN_HWOBJ[1].ubData[4];//��ȡCAN1��1��MessageObject��4Byte��ֵ
			Can1Recdata[0][5]=CAN_HWOBJ[1].ubData[5];//��ȡCAN1��1��MessageObject��5Byte��ֵ
			Can1Recdata[0][6]=CAN_HWOBJ[1].ubData[6];//��ȡCAN1��1��MessageObject��6Byte��ֵ
			Can1Recdata[0][7]=CAN_HWOBJ[1].ubData[7];//��ȡCAN1��1��MessageObject��7Byte��ֵ

			realangle = (Can1Recdata[0][1]<<8) +Can1Recdata[0][2];
			if(realangle>32766)
				RealAngle = (realangle-65536)*5/8;
			else
				RealAngle = realangle*5/8;
			if(RealAngle>120)
			{
				SteerInterSta=1;
			}
			else
			{
				SteerInterSta=0;
			}
		break;
		}


		if(CAN1ID_u16_Sig==Can1ID_u16a10_Sig[1])//�жϽ���ID����ȡ��Ӧ������ݵ�������ʼԪ��
		{
			Can1Recdata[1][0]=CAN_HWOBJ[1].ubData[0];//��ȡCAN1��1��MessageObject��0Byte��ֵ
			Can1Recdata[1][1]=CAN_HWOBJ[1].ubData[1];//��ȡCAN1��1��MessageObject��1Byte��ֵ
			Can1Recdata[1][2]=CAN_HWOBJ[1].ubData[2];//��ȡCAN1��1��MessageObject��2Byte��ֵ
			Can1Recdata[1][3]=CAN_HWOBJ[1].ubData[3];//��ȡCAN1��1��MessageObject��3Byte��ֵ
			Can1Recdata[1][4]=CAN_HWOBJ[1].ubData[4];//��ȡCAN1��1��MessageObject��4Byte��ֵ
			Can1Recdata[1][5]=CAN_HWOBJ[1].ubData[5];//��ȡCAN1��1��MessageObject��5Byte��ֵ
			Can1Recdata[1][6]=CAN_HWOBJ[1].ubData[6];//��ȡCAN1��1��MessageObject��6Byte��ֵ
			Can1Recdata[1][7]=CAN_HWOBJ[1].ubData[7];//��ȡCAN1��1��MessageObject��7Byte��ֵ
			VechileSpeed = ((Can1Recdata[1][0]<<8) +Can1Recdata[1][1])/3;
			RealAngle = (Can1Recdata[1][2]<<8) +Can1Recdata[1][3];
			if (RealAngle<0){
			    RealAngle = 65535 - RealAngle;
			  }
		break;
		}

		if(CAN1ID_u16_Sig==Can1ID_u16a10_Sig[2])//�жϽ���ID����ȡ��Ӧ������ݵ�������ʼԪ��
				{
					Can1Recdata[2][0]=CAN_HWOBJ[1].ubData[0];//��ȡCAN1��1��MessageObject��0Byte��ֵ
					Can1Recdata[2][1]=CAN_HWOBJ[1].ubData[1];//��ȡCAN1��1��MessageObject��1Byte��ֵ
					Can1Recdata[2][2]=CAN_HWOBJ[1].ubData[2];//��ȡCAN1��1��MessageObject��2Byte��ֵ
					Can1Recdata[2][3]=CAN_HWOBJ[1].ubData[3];//��ȡCAN1��1��MessageObject��3Byte��ֵ
					//Can1Recdata[2][4]=CAN_HWOBJ[1].ubData[4];//��ȡCAN1��1��MessageObject��4Byte��ֵ
					//Can1Recdata[2][5]=CAN_HWOBJ[1].ubData[5];//��ȡCAN1��1��MessageObject��5Byte��ֵ
					//Can1Recdata[2][6]=CAN_HWOBJ[1].ubData[6];//��ȡCAN1��1��MessageObject��6Byte��ֵ
					//Can1Recdata[2][7]=CAN_HWOBJ[1].ubData[7];//��ȡCAN1��1��MessageObject��7Byte��ֵ
					//Can0Rec0data[0][0]=CAN_HWOBJ[0].ubData[0];//��ȡCAN0��0��MessageObject��0Byte��ֵ

				    /*******radar data process*******/

					break;
				}

		if(CAN1ID_u16_Sig==Can1ID_u16a10_Sig[3])//�жϽ���ID����ȡ��Ӧ������ݵ�������ʼԪ��
				{
					Can1Recdata[3][0]=CAN_HWOBJ[1].ubData[0];//��ȡCAN1��1��MessageObject��0Byte��ֵ
					Can1Recdata[3][1]=CAN_HWOBJ[1].ubData[1];//��ȡCAN1��1��MessageObject��1Byte��ֵ
					Can1Recdata[3][2]=CAN_HWOBJ[1].ubData[2];//��ȡCAN1��1��MessageObject��2Byte��ֵ
					Can1Recdata[3][3]=CAN_HWOBJ[1].ubData[3];//��ȡCAN1��1��MessageObject��3Byte��ֵ
					Can1Recdata[3][4]=CAN_HWOBJ[1].ubData[4];//��ȡCAN1��1��MessageObject��4Byte��ֵ
					Can1Recdata[3][5]=CAN_HWOBJ[1].ubData[5];//��ȡCAN1��1��MessageObject��5Byte��ֵ
					Can1Recdata[3][6]=CAN_HWOBJ[1].ubData[6];//��ȡCAN1��1��MessageObject��6Byte��ֵ
					Can1Recdata[3][7]=CAN_HWOBJ[1].ubData[7];//��ȡCAN1��1��MessageObject��7Byte��ֵ

					break;
				}
		if(CAN1ID_u16_Sig==Can1ID_u16a10_Sig[4])//�жϽ���ID����ȡ��Ӧ������ݵ�������ʼԪ��
						{
							Can1Recdata[4][0]=CAN_HWOBJ[1].ubData[0];//��ȡCAN1��1��MessageObject��0Byte��ֵ
							Can1Recdata[4][1]=CAN_HWOBJ[1].ubData[1];//��ȡCAN1��1��MessageObject��1Byte��ֵ
							Can1Recdata[4][2]=CAN_HWOBJ[1].ubData[2];//��ȡCAN1��1��MessageObject��2Byte��ֵ
							Can1Recdata[4][3]=CAN_HWOBJ[1].ubData[3];//��ȡCAN1��1��MessageObject��3Byte��ֵ
							Can1Recdata[4][4]=CAN_HWOBJ[1].ubData[4];//��ȡCAN1��1��MessageObject��4Byte��ֵ
							Can1Recdata[4][5]=CAN_HWOBJ[1].ubData[5];//��ȡCAN1��1��MessageObject��5Byte��ֵ
							Can1Recdata[4][6]=CAN_HWOBJ[1].ubData[6];//��ȡCAN1��1��MessageObject��6Byte��ֵ
							Can1Recdata[4][7]=CAN_HWOBJ[1].ubData[7];//��ȡCAN1��1��MessageObject��7Byte��ֵ

							break;
		}
	 }
	    CAN_HWOBJ[1].uwMOCTRL = 0x0008;//�����־λ
   }
}
/*!************************************************************************************
* @fn         void CanTx_v_g(void)
* @brief     CAN0��CAN1CAN���ͺ���
* @author     Matt Zhang
* @param[in] void
* @return     void
* @note       Ŀǰ����Ϊ10ms������Ҫ�޸���������Ƽ�����ʵ�֣���Task4.c��task4()�����е���
* @Data       2019-3-12
****************************************************************************************/
void CanTx_v_g(void)
{
  static INT8U CycleSchedCnt=0;
  CycleSchedCnt++;
  switch (CycleSchedCnt) {

       case 5:
#if CAN0TRS0_ENABLE==1
        CAN_MOAR4H=0x8000+(TRS_CAN0ID_0<<2);
        CAN_MOAR4L=0x0000;
/*---------------Ŀǰ����Ϊ10ms�����޸���������Ӽ�����--------------------*/
/*!************************************************************************************
      *	@brief	            CAN0�������
****************************************************************************************/
        //Can0Revdata[0][0] = (INT16S)VCU_MotToqReq>>8;//�ƶ�������
        //Can0Revdata[0][1] = (INT16S)VCU_MotToqReq;
        //Can0Revdata[0][2] = (INT16S)MasterCylinderPrs_CAN;//�ƶ�ѹ��
		/*Can0Revdata[0][3] = (INT16S)(CylinderLocation_CAN >>1);
		Can0Revdata[0][4] = (CylinderLocation_CAN<<7) + (PedalLocation_CAN >> 2); //�����ٶ�
		Can0Revdata[0][5] = (PedalLocation_CAN << 6)
				            + ((4 << iCAS_MotorState)&0x30)
				            +((iCAS_BrakeFault_Level << 1)&0x0E)
				            +(iCAS_BrakeFlagBit & 0X01);*/
		//Can0Revdata[0][6] = 0;         //�����ٶ�
		//Can0Revdata[0][7] = 0;

       /* Can0Revdata[0][0] = (INT16S)VCU_MotToqReq>>8;  //�������
        Can0Revdata[0][1] = (INT16S)VCU_MotToqReq;
        Can0Revdata[0][2] = 0;         //�������
        Can0Revdata[0][3] = 0;
		Can0Revdata[0][4] = 0;         //�����ٶ�
		Can0Revdata[0][5] = ((INT8U)iCAS_BrakeFlagBit & 0x01);
		Can0Revdata[0][6] = 0;         //�����ٶ�
		Can0Revdata[0][7] = 0;*/

        CanSendMsg_v_g(4,&Can0Revdata[0][0],8);
#endif

#if CAN1TRS0_ENABLE==1
        CAN_MOAR10H=0x8000+(TRS_CAN1ID_0<<2);
        CAN_MOAR10L=0x0000;
/*---------------Ŀ/ǰ����Ϊ10ms�����޸���������Ӽ�����--------------------*/
        Can1Revdata[0][0] = 0;
        Can1Revdata[0][1] = 0;
        Can1Revdata[0][2] = 0;
        Can1Revdata[0][3] = 0;
        Can1Revdata[0][4] = 0;
        Can1Revdata[0][5] = 0;
        Can1Revdata[0][6] = 0;
        Can1Revdata[0][7] = 0;
        CanSendMsg_v_g(10,&Can1Revdata[0][0],8);
#endif
		            break;

       case 10:
#if CAN0TRS1_ENABLE==1
        CAN_MOAR5H=0x8000+(TRS_CAN0ID_1<<2);
        CAN_MOAR5L=0x0000;
/*---------------Ŀǰ����Ϊ10ms�����޸���������Ӽ�����--------------------*/


        //Can0Revdata[1][0] = (INT8U)(((INT16S)(m_iPWMP_CAN))>>8);
		//Can0Revdata[1][1] = (INT8U)(INT16S)(m_iPWMP_CAN);
		//Can0Revdata[1][2] = (INT8U)(((INT16S)(m_iPWMI_CAN))>>8);
		//Can0Revdata[1][3] = (INT8U)(INT16S)(m_iPWMI_CAN);

        /*Can0Revdata[1][0] = (INT8U)(((INT16S)(Test_target_Cylinder*100))>>8);
        Can0Revdata[1][1] = (INT8U)(INT16S)(Test_target_Cylinder*100);
        Can0Revdata[1][2] = (INT8U)(((INT16S)(Test_fricbrakeCylinder*100))>>8);
        Can0Revdata[1][3] = (INT8U)(INT16S)(Test_fricbrakeCylinder*100);
        Can0Revdata[1][4] = (INT8U)((INT16S)Test_toq_err >>8);
        Can0Revdata[1][5] = (INT8U)(INT16S)BrakeState_CAN;
        Can0Revdata[1][6] = (INT8U)((INT16S)(Test_toqRequest >>8));
        Can0Revdata[1][7] = (INT8U)(INT16S)Test_toqRequest;*/

        //Can0Revdata[1][0] = (INT16S)(MotorCurrent_CAN >> 4);
		//Can0Revdata[1][1] = (INT16S)((MotorCurrent_CAN << 4)& 0xF0);
        Can0Revdata[1][0] = (INT16S)(MotorCurrent_CAN >> 8);
        Can0Revdata[1][1] = (INT16S)(MotorCurrent_CAN);
        Can0Revdata[1][2] = (INT8U)(INT16S)(MasterCylinderPrs_CAN);
		Can0Revdata[1][3] = 0;
		Can0Revdata[1][4] = 0;
		Can0Revdata[1][5] = (INT16S)(Tx_ACC >>4);
		Can0Revdata[1][6] = (INT16S)((Tx_ACC <<4) & 0xF0);
		Can0Revdata[1][7] = 0;

        CanSendMsg_v_g(5,&Can0Revdata[1][0],8);
#endif

#if CAN1TRS1_ENABLE==1
        CAN_MOAR11H=0x8000+(TRS_CAN1ID_1<<2);
        CAN_MOAR11L=0x0000;
/*---------------Ŀǰ����Ϊ10ms�����޸���������Ӽ�����--------------------*/
        Can1Revdata[1][0] = 0;
        Can1Revdata[1][1] = 0;
        Can1Revdata[1][2] = 0;
        Can1Revdata[1][3] = 0;
        Can1Revdata[1][4] = 0;
        Can1Revdata[1][5] = 0;
        Can1Revdata[1][6] = 0;
        Can1Revdata[1][7] = 0;
        CanSendMsg_v_g(11,&Can1Revdata[1][0],8);
#endif
		            break;

       case 15:
#if CAN0TRS2_ENABLE==1
        CAN_MOAR6H=0x8000+(TRS_CAN0ID_2<<2);
        CAN_MOAR6L=0x0000;
/*---------------Ŀǰ����Ϊ10ms�����޸���������Ӽ�����--------------------*/
        /*Can0Revdata[2][0] = (INT8U)(TargetCurrent_CAN>>8);                         // steering angle * 10
        Can0Revdata[2][1] = (INT8U)TargetCurrent_CAN;
        Can0Revdata[2][2] = (INT8U)(Test_BrakeToqRequest>>8);                        // longititude acceleration
        Can0Revdata[2][3] = (INT8U)Test_BrakeToqRequest;
        Can0Revdata[2][4] = (INT8U)(FrcCylinder_CAN >>8);                         // ego speed(km/h) * 10
        Can0Revdata[2][5] = (INT8U)FrcCylinder_CAN;
        Can0Revdata[2][6] = (INT8U)(MasterCylinderPrs_CAN >>8);
        Can0Revdata[2][7] = (INT8U)MasterCylinderPrs_CAN;*/

        Can0Revdata[2][0] = (INT16S)VCU_MotToqReq>>8;//�ƶ�������
		Can0Revdata[2][1] = (INT16S)VCU_MotToqReq;
		Can0Revdata[2][2] = (INT16S)MasterCylinderPrs_CAN;//�ƶ�ѹ��
		Can0Revdata[2][3] = (INT16S)(CylinderLocation_CAN >>1);
		Can0Revdata[2][4] = (CylinderLocation_CAN<<7) + (PedalLocation_CAN >> 2); //�����ٶ�
		Can0Revdata[2][5] = (PedalLocation_CAN << 6)
							+ ((4 << iCAS_MotorState)&0x30)
							+((iCAS_BrakeFault_Level << 1)&0x0E)
							+(iCAS_BrakeFlagBit & 0X01);
		Can0Revdata[2][6] = 0;         //�����ٶ�
		Can0Revdata[2][7] = 0;
        CanSendMsg_v_g(6,&Can0Revdata[2][0],8);
#endif
#if CAN1TRS2_ENABLE==1
        CAN_MOAR12H=0x8000+(TRS_CAN1ID_2<<2);
        CAN_MOAR12L=0x0000;
/*---------------Ŀǰ����Ϊ10ms�����޸���������Ӽ�����--------------------*/
        Can1Revdata[2][0] = 0;                          // steering angle * 10
        Can1Revdata[2][1] = 0;
        Can1Revdata[2][2] = 0;                          // longititude acceleration
        Can1Revdata[2][3] = 0;
        Can1Revdata[2][4] = 0;                          // ego speed(km/h) * 10
        Can1Revdata[2][5] = 0;
        Can1Revdata[2][6] = 0;
        Can1Revdata[2][7] = 0;
        CanSendMsg_v_g(12,&Can1Revdata[2][0],8);
#endif
		            break;

       case 20:
#if CAN0TRS3_ENABLE==1
        CAN_MOAR7H=0x8000+(TRS_CAN0ID_3<<2);
        CAN_MOAR7L=0x0000;
/*---------------Ŀǰ����Ϊ10ms�����޸���������Ӽ�����--------------------*/

        /*Can0Revdata[3][0] = (INT8U)(m_iPWMP_CAN>>8);
        Can0Revdata[3][1] = (INT8U)m_iPWMP_CAN;
        Can0Revdata[3][2] = (INT8U)(m_iPWMI_CAN>>8);
        Can0Revdata[3][3] = (INT8U)m_iPWMI_CAN;
        Can0Revdata[3][4] = (INT8U)(m_iPWMD_CAN>>8);
        Can0Revdata[3][5] = (INT8U)m_iPWMD_CAN;
        Can0Revdata[3][6] = (INT8U)(PedalLocation_CAN>>8);
        Can0Revdata[3][7] = (INT8U)PedalLocation_CAN;*/

        Can0Revdata[3][0] = (INT8U)(APA_FeedBackFlag);
		Can0Revdata[3][1] = (INT8U)APA_FeedBackValue;
		Can0Revdata[3][2] = (INT8U)(0>>8);
		Can0Revdata[3][3] = (INT8U)0;
		Can0Revdata[3][4] = (INT8U)(0>>8);
		Can0Revdata[3][5] = (INT8U)0;
		Can0Revdata[3][6] = (INT8U)(0>>8);
		Can0Revdata[3][7] = (INT8U)0;

        CanSendMsg_v_g(7,&Can0Revdata[3][0],8);

#endif

#if CAN1TRS3_ENABLE==1
        CAN_MOAR13H=0x8000+(TRS_CAN1ID_3<<2);
        CAN_MOAR13L=0x0000;
/*---------------Ŀǰ����Ϊ10ms�����޸���������Ӽ�����--------------------*/
        Can1Revdata[3][0] = 0;
        Can1Revdata[3][1] = 0;
        Can1Revdata[3][2] = 0;
        Can1Revdata[3][3] = 0;
        Can1Revdata[3][4] = 0;
        Can1Revdata[3][5] = 0;
        Can1Revdata[3][6] = 0;
        Can1Revdata[3][7] = 0;
        CanSendMsg_v_g(13,&Can1Revdata[3][0],8);
#endif
        break;


       case 25:
       #if CAN0TRS4_ENABLE==1
               CAN_MOAR8H=0x8000+(TRS_CAN0ID_4<<2);
               CAN_MOAR8L=0x0000;
       /*---------------Ŀǰ����Ϊ10ms�����޸���������Ӽ�����--------------------*/
               Can0Revdata[4][0] = (INT8U)(Set_Cylinder_CAN>>8);
               Can0Revdata[4][1] = (INT8U)Set_Cylinder_CAN;
               Can0Revdata[4][2] = (INT8U)(CylinderLocation_CAN>>8);
               Can0Revdata[4][3] = (INT8U)CylinderLocation_CAN;

               Can0Revdata[4][4] = (INT8U)(MotorCurrent_CAN>>8);
               Can0Revdata[4][5] = (INT8U)MotorCurrent_CAN;

               //Can0Revdata[4][6] = (INT8U)(motorDuty_CAN>>8);
               //Can0Revdata[4][7] = (INT8U)motorDuty_CAN;
               Can0Revdata[4][6] = (INT8U)(Tx_ACC>>8);
               Can0Revdata[4][7] = (INT8U)Tx_ACC;

               CanSendMsg_v_g(8,&Can0Revdata[4][0],8);
 #endif
       #if CAN1TRS4_ENABLE==1
               CAN_MOAR14H=0x8000+(TRS_CAN1ID_4<<2);
               CAN_MOAR14L=0x0000;
       /*---------------Ŀǰ����Ϊ10ms�����޸���������Ӽ�����--------------------*/
               Can1Revdata[4][0] = 0;
               Can1Revdata[4][1] = 0;
               Can1Revdata[4][2] = 0;
               Can1Revdata[4][3] = 0;
               Can1Revdata[4][4] = 0;
               Can1Revdata[4][5] = 0;
               Can1Revdata[4][6] = 0;
               Can1Revdata[4][7] = 0;

               CanSendMsg_v_g(14,&Can1Revdata[4][0],8);
       #endif
               break;


       case 30:
              #if CAN0TRS5_ENABLE==1
                CAN_MOAR9H=0x8000+(TRS_CAN0ID_5<<2);
                CAN_MOAR9L=0x0000;
              /*---------------Ŀǰ����Ϊ10ms�����޸���������Ӽ�����--------------------*/
                Can0Revdata[5][0] = (INT16S)VCU_MotToqReq>>8;  //�������
				Can0Revdata[5][1] = (INT16S)VCU_MotToqReq;
				Can0Revdata[5][2] = 0;         //�������
				Can0Revdata[5][3] = 0;
				Can0Revdata[5][4] = 0;         //�����ٶ�
				Can0Revdata[5][5] = ((INT8U)iCAS_BrakeFlagBit & 0x01);
				Can0Revdata[5][6] = 0;         //�����ٶ�
				Can0Revdata[5][7] = 0;
                CanSendMsg_v_g(9,&Can0Revdata[5][0],8);
              #endif
               CycleSchedCnt=0;
             break;
       default:
              break;
       }
}


