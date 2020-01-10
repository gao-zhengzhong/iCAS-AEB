/*
 * Bus_Line.c
 *
 *  Created on: 2015-5-21
 *      Author: zhangguangyao
 */
#define   BUS_LINE_GLOBALS
#include"MAIN.h"
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
INT8U i;
for(i=0;i<CAN0ID_NUM;i++)
{
	if(CanId=Can0ID_u16a64_Sig[i])//�жϽ���ID����ȡ��Ӧ������ݵ�������ʼԪ��
	{
		Can0Rec0data[i][0]=CAN_HWOBJ[0].ubData[0];//��ȡCAN0��0��MessageObject��0Byte��ֵ
		Can0Rec0data[i][1]=CAN_HWOBJ[0].ubData[1];//��ȡCAN0��0��MessageObject��1Byte��ֵ
		Can0Rec0data[i][2]=CAN_HWOBJ[0].ubData[2];//��ȡCAN0��0��MessageObject��2Byte��ֵ
		Can0Rec0data[i][3]=CAN_HWOBJ[0].ubData[3];//��ȡCAN0��0��MessageObject��3Byte��ֵ
		Can0Rec0data[i][4]=CAN_HWOBJ[0].ubData[4];//��ȡCAN0��0��MessageObject��4Byte��ֵ
		Can0Rec0data[i][5]=CAN_HWOBJ[0].ubData[5];//��ȡCAN0��0��MessageObject��5Byte��ֵ
		Can0Rec0data[i][6]=CAN_HWOBJ[0].ubData[6];//��ȡCAN0��0��MessageObject��6Byte��ֵ
		Can0Rec0data[i][7]=CAN_HWOBJ[0].ubData[7];//��ȡCAN0��0��MessageObject��7Byte��ֵ
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
INT8U i;
if(CAN_ubNewData(1))//�ж�MessgeObject1�Ƿ����µ����ݽ��յ�
{
	CAN1ID_u16_Sig=CAN_MOAR1H;//��ȡCANID
	CAN1ID_u16_Sig=(CAN1ID_u16_Sig>>2)&0x7FF;//CANID��ֵ����

	for(i=0;i<CAN1ID_NUM;i++)
	{
		if(CAN1ID_u16_Sig=Can1ID_u16a10_Sig[i])//�жϽ���ID����ȡ��Ӧ������ݵ�������ʼԪ��
		{
			Can1Recdata[i][0]=CAN_HWOBJ[1].ubData[0];//��ȡCAN1��1��MessageObject��0Byte��ֵ
			Can1Recdata[i][1]=CAN_HWOBJ[1].ubData[1];//��ȡCAN1��1��MessageObject��1Byte��ֵ
			Can1Recdata[i][2]=CAN_HWOBJ[1].ubData[2];//��ȡCAN1��1��MessageObject��2Byte��ֵ
			Can1Recdata[i][3]=CAN_HWOBJ[1].ubData[3];//��ȡCAN1��1��MessageObject��3Byte��ֵ
			Can1Recdata[i][4]=CAN_HWOBJ[1].ubData[4];//��ȡCAN1��1��MessageObject��4Byte��ֵ
			Can1Recdata[i][5]=CAN_HWOBJ[1].ubData[5];//��ȡCAN1��1��MessageObject��5Byte��ֵ
			Can1Recdata[i][6]=CAN_HWOBJ[1].ubData[6];//��ȡCAN1��1��MessageObject��6Byte��ֵ
			Can1Recdata[i][7]=CAN_HWOBJ[1].ubData[7];//��ȡCAN1��1��MessageObject��7Byte��ֵ
		break;
		}
	}
	CAN_HWOBJ[1].uwMOCTRL = 0x0008;//�����־λ
}

}
/*!************************************************************************************
*	@fn	        void CanTx_v_g(void)
*	@brief	    CAN0��CAN1CAN���ͺ���
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       Ŀǰ����Ϊ10ms������Ҫ�޸���������Ƽ�����ʵ�֣���Task4.c��task4()�����е���
*	@Data       2019-3-12
****************************************************************************************/
void CanTx_v_g(void)
{
	 static INT8U CycleSchedCnt=0;
	 CycleSchedCnt++;
		switch (CycleSchedCnt) {

		     case 1:
#if CAN0TRS0_ENABLE==1
		    	 CAN_MOAR4H=(TRS_CAN0ID_0<<2);
		    	 CAN_MOAR4L=0x0000;
/*---------------Ŀǰ����Ϊ10ms�����޸���������Ӽ�����--------------------*/
		    	 CanSendMsg_v_g(4,&Can0Revdata[0][0],8);

#endif

#if CAN1TRS0_ENABLE==1
		    	 CAN_MOAR10H=(TRS_CAN1ID_0<<2);
		    	 CAN_MOAR10L=0x0000;
/*---------------Ŀǰ����Ϊ10ms�����޸���������Ӽ�����--------------------*/
		    	 CanSendMsg_v_g(10,&Can1Revdata[0][0],8);

#endif
		            break;

		     case 2:
#if CAN0TRS1_ENABLE==1
		    	 CAN_MOAR5H=(TRS_CAN0ID_1<<2);
		    	 CAN_MOAR5L=0x0000;
/*---------------Ŀǰ����Ϊ10ms�����޸���������Ӽ�����--------------------*/
		    	 CanSendMsg_v_g(5,&Can0Revdata[1][0],8);

#endif

#if CAN1TRS1_ENABLE==1
		    	 CAN_MOAR11H=(TRS_CAN1ID_1<<2);
		    	 CAN_MOAR11L=0x0000;
/*---------------Ŀǰ����Ϊ10ms�����޸���������Ӽ�����--------------------*/
		    	 CanSendMsg_v_g(11,&Can1Revdata[1][0],8);

#endif
		            break;

		     case 3:
#if CAN0TRS2_ENABLE==1
		    	 CAN_MOAR6H=(TRS_CAN0ID_2<<2);
		    	 CAN_MOAR6L=0x0000;
/*---------------Ŀǰ����Ϊ10ms�����޸���������Ӽ�����--------------------*/
		    	 CanSendMsg_v_g(6,&Can0Revdata[2][0],8);

#endif

#if CAN1TRS2_ENABLE==1
		    	 CAN_MOAR12H=(TRS_CAN1ID_2<<2);
		    	 CAN_MOAR12L=0x0000;
/*---------------Ŀǰ����Ϊ10ms�����޸���������Ӽ�����--------------------*/
		    	 CanSendMsg_v_g(12,&Can1Revdata[2][0],8);

#endif
		            break;

		     case 4:

#if CAN0TRS3_ENABLE==1
		    	 CAN_MOAR7H=(TRS_CAN0ID_3<<2);
		    	 CAN_MOAR7L=0x0000;
/*---------------Ŀǰ����Ϊ10ms�����޸���������Ӽ�����--------------------*/
		    	 CanSendMsg_v_g(7,&Can0Revdata[3][0],8);

#endif

#if CAN1TRS3_ENABLE==1
		    	 CAN_MOAR13H=(TRS_CAN1ID_3<<2);
		    	 CAN_MOAR13L=0x0000;
/*---------------Ŀǰ����Ϊ10ms�����޸���������Ӽ�����--------------------*/
		    	 CanSendMsg_v_g(13,&Can1Revdata[3][0],8);

#endif
		    	 CycleSchedCnt=0;
		         break;

		     default:
		            break;
		     }
}


