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
/*-------------------------------CAN0 ID数组初始化--------------------------------*/
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
/*-------------------------------CAN1 ID数组初始化--------------------------------*/
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
*	@brief	    CAN Transfer 使能函数
*	@author     Matt Zhang
*	@param[in]	Null
*	@return	    Null
*	@note       在iso.c的ISOInit_v_g()函数中调用
*	@Data       2019-03-12
****************************************************************************************/
void CanEnbale_v_g(void)
{
	CAN1_ENABLE_ON;//CAN0 ENABLE
	CAN2_ENABLE_ON;//CAN1 ENABLE
}
/*!************************************************************************************
*	@fn	        void CanSendMsg_v_g(INT8U ubObjNr, INT8U *ubpubData,INT8U Len)
*	@brief	    CAN 发送函数
*	@author     Matt Zhang
*	@param[in]	ubObjNr代表MessgeObject;ubpubData代表发送数据;Len代表发送长度
*	@return	    Null
*	@note
*	@Data       2019-03-12
****************************************************************************************/
void  CanSendMsg_v_g(INT8U ubObjNr, INT8U *ubpubData,INT8U Len)
{
 ubyte len;
 len = Len + 0x10;

 CAN_HWOBJ[ubObjNr].uwMOFCRH &= (~(uword)0x0F00);//长度赋值
 CAN_HWOBJ[ubObjNr].uwMOFCRH |= (((uword)(len & 0x0F)) << 8);//长度赋值
 CAN_vLoadData(ubObjNr,ubpubData);//加载CAN发送数据
 CAN_vTransmit(ubObjNr);//发送指令
}
/*!************************************************************************************
*	@fn	        INT8U  CanRecMsg_v_g(INT8U ubObjNr, INT8U *ubpubData,INT8U *Len)
*	@brief	    CAN查询接收函数
*	@author     Matt Zhang
*	@param[in]	ubObjNr代表MessgeObject;ubpubData代表接收数据;Len代表接收长度
*	@return	    1代表接收数据成功;0代表未有数据接收到
*	@note
*	@Data       2019-03-12
****************************************************************************************/
INT8U  CanRecMsg_v_g(INT8U ubObjNr, INT8U *ubpubData,INT8U *Len)
{
	ubyte i;
if(CAN_ubNewData(ubObjNr))//判断MessgeObject是否有新的数据接收到
{
	Len[0]= (ubyte)((CAN_HWOBJ[ubObjNr].uwMOFCRH & 0x0F00) >> 8); //获取接收的数据长度
	for( i = 0; i <= Len[0]; i++ )
	{
		ubpubData[i]=CAN_HWOBJ[ubObjNr].ubData[i];//获取接收的数据
	}
	CAN_HWOBJ[ubObjNr].uwMOCTRL = 0x0008;//清除标志位
return 1;
}
return 0;
}
/*!************************************************************************************
*	@fn	        void Can0RecDeal_v_g(void)
*	@brief	    Can0接收数据处理函数
*	@author     Matt Zhang
*	@param[in]	CanId：CAN0接收的CANID
*	@return	    Null
*	@note       在CAN.c的CAN_viSRN0()函数中调用
*	@Data       2019-03-12
****************************************************************************************/
void    Can0RecDeal_v_g(INT16U CanId)
{
INT8U i;
for(i=0;i<CAN0ID_NUM;i++)
{
	if(CanId=Can0ID_u16a64_Sig[i])//判断接收ID，获取对应存放数据的数组起始元素
	{
		Can0Rec0data[i][0]=CAN_HWOBJ[0].ubData[0];//获取CAN0第0个MessageObject的0Byte数值
		Can0Rec0data[i][1]=CAN_HWOBJ[0].ubData[1];//获取CAN0第0个MessageObject的1Byte数值
		Can0Rec0data[i][2]=CAN_HWOBJ[0].ubData[2];//获取CAN0第0个MessageObject的2Byte数值
		Can0Rec0data[i][3]=CAN_HWOBJ[0].ubData[3];//获取CAN0第0个MessageObject的3Byte数值
		Can0Rec0data[i][4]=CAN_HWOBJ[0].ubData[4];//获取CAN0第0个MessageObject的4Byte数值
		Can0Rec0data[i][5]=CAN_HWOBJ[0].ubData[5];//获取CAN0第0个MessageObject的5Byte数值
		Can0Rec0data[i][6]=CAN_HWOBJ[0].ubData[6];//获取CAN0第0个MessageObject的6Byte数值
		Can0Rec0data[i][7]=CAN_HWOBJ[0].ubData[7];//获取CAN0第0个MessageObject的7Byte数值
	break;
	}
}
}

/*!************************************************************************************
*	@fn	        void Can1RecDeal_v_g(void)
*	@brief	    Can1接收数据处理函数
*	@author     Matt Zhang
*	@param[in]	Null
*	@return	    Null
*	@note       在task.c的task3()函数中调用
*	@Data       2019-03-12
****************************************************************************************/
void    Can1RecDeal_v_g()
{
INT8U i;
if(CAN_ubNewData(1))//判断MessgeObject1是否有新的数据接收到
{
	CAN1ID_u16_Sig=CAN_MOAR1H;//获取CANID
	CAN1ID_u16_Sig=(CAN1ID_u16_Sig>>2)&0x7FF;//CANID数值处理

	for(i=0;i<CAN1ID_NUM;i++)
	{
		if(CAN1ID_u16_Sig=Can1ID_u16a10_Sig[i])//判断接收ID，获取对应存放数据的数组起始元素
		{
			Can1Recdata[i][0]=CAN_HWOBJ[1].ubData[0];//获取CAN1第1个MessageObject的0Byte数值
			Can1Recdata[i][1]=CAN_HWOBJ[1].ubData[1];//获取CAN1第1个MessageObject的1Byte数值
			Can1Recdata[i][2]=CAN_HWOBJ[1].ubData[2];//获取CAN1第1个MessageObject的2Byte数值
			Can1Recdata[i][3]=CAN_HWOBJ[1].ubData[3];//获取CAN1第1个MessageObject的3Byte数值
			Can1Recdata[i][4]=CAN_HWOBJ[1].ubData[4];//获取CAN1第1个MessageObject的4Byte数值
			Can1Recdata[i][5]=CAN_HWOBJ[1].ubData[5];//获取CAN1第1个MessageObject的5Byte数值
			Can1Recdata[i][6]=CAN_HWOBJ[1].ubData[6];//获取CAN1第1个MessageObject的6Byte数值
			Can1Recdata[i][7]=CAN_HWOBJ[1].ubData[7];//获取CAN1第1个MessageObject的7Byte数值
		break;
		}
	}
	CAN_HWOBJ[1].uwMOCTRL = 0x0008;//清除标志位
}

}
/*!************************************************************************************
*	@fn	        void CanTx_v_g(void)
*	@brief	    CAN0、CAN1CAN发送函数
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       目前周期为10ms，如需要修改周期请设计计数器实现；在Task4.c的task4()函数中调用
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
/*---------------目前周期为10ms，如修改周期请添加计数器--------------------*/
		    	 CanSendMsg_v_g(4,&Can0Revdata[0][0],8);

#endif

#if CAN1TRS0_ENABLE==1
		    	 CAN_MOAR10H=(TRS_CAN1ID_0<<2);
		    	 CAN_MOAR10L=0x0000;
/*---------------目前周期为10ms，如修改周期请添加计数器--------------------*/
		    	 CanSendMsg_v_g(10,&Can1Revdata[0][0],8);

#endif
		            break;

		     case 2:
#if CAN0TRS1_ENABLE==1
		    	 CAN_MOAR5H=(TRS_CAN0ID_1<<2);
		    	 CAN_MOAR5L=0x0000;
/*---------------目前周期为10ms，如修改周期请添加计数器--------------------*/
		    	 CanSendMsg_v_g(5,&Can0Revdata[1][0],8);

#endif

#if CAN1TRS1_ENABLE==1
		    	 CAN_MOAR11H=(TRS_CAN1ID_1<<2);
		    	 CAN_MOAR11L=0x0000;
/*---------------目前周期为10ms，如修改周期请添加计数器--------------------*/
		    	 CanSendMsg_v_g(11,&Can1Revdata[1][0],8);

#endif
		            break;

		     case 3:
#if CAN0TRS2_ENABLE==1
		    	 CAN_MOAR6H=(TRS_CAN0ID_2<<2);
		    	 CAN_MOAR6L=0x0000;
/*---------------目前周期为10ms，如修改周期请添加计数器--------------------*/
		    	 CanSendMsg_v_g(6,&Can0Revdata[2][0],8);

#endif

#if CAN1TRS2_ENABLE==1
		    	 CAN_MOAR12H=(TRS_CAN1ID_2<<2);
		    	 CAN_MOAR12L=0x0000;
/*---------------目前周期为10ms，如修改周期请添加计数器--------------------*/
		    	 CanSendMsg_v_g(12,&Can1Revdata[2][0],8);

#endif
		            break;

		     case 4:

#if CAN0TRS3_ENABLE==1
		    	 CAN_MOAR7H=(TRS_CAN0ID_3<<2);
		    	 CAN_MOAR7L=0x0000;
/*---------------目前周期为10ms，如修改周期请添加计数器--------------------*/
		    	 CanSendMsg_v_g(7,&Can0Revdata[3][0],8);

#endif

#if CAN1TRS3_ENABLE==1
		    	 CAN_MOAR13H=(TRS_CAN1ID_3<<2);
		    	 CAN_MOAR13L=0x0000;
/*---------------目前周期为10ms，如修改周期请添加计数器--------------------*/
		    	 CanSendMsg_v_g(13,&Can1Revdata[3][0],8);

#endif
		    	 CycleSchedCnt=0;
		         break;

		     default:
		            break;
		     }
}


