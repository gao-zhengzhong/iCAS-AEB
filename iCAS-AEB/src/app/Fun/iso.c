/*
 * ISO.c
 *
 *  Created on: 2015-5-19
 *      Author: zhangguangyao
 */
#define   ISO_GLOBALS
#include "MAIN.h"
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
*	@fn	        void ISOInit_v_g(void)
*	@brief	          ģʽ���Ʋ�����ʼ����CANʹ��
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       ��MAIN.c��main()�����е���
*	@Data       2019-3-12
****************************************************************************************/
void ISOInit_v_g(void)
{
	SystemMode_u8_Sig=0;        /* ϵͳģʽ */
	PDTFinish_u8_Sig=0;         /* PowerDownģʽ������־λ */
	PUTFinish_u8_Sig=0;         /* PowerUpTestģʽ������־λ */
	PDFinish_u8_Sig=0;          /* PowerDownTestģʽ������־λ*/
	NormalFinish_u8_Sig=0;      /* Normalģʽ������־λ */
	PDTtoPUTflag_u8_Sig=0;      /* PowerDown��PowerUpTestģʽ��־λ*/
	MaintenStatus_u8_Sig=0;     /* ά��ģʽ��־λ  */
	IGNStatus_u8_Sig=0;         /* ����ź�״̬*/
	MaintenLevel_u8_Sig=0;      /* ά���ź�״̬*/
	FaultLevel_u8_Sig=0;        /* Ŀǰ���������ϵĵȼ�*/
	VehicleStatus_u8_Sig=0;     /* ����״̬ �Ƿ�Ϊֹͣ״̬ */
	VehSpeedFault_u8_Sig=0;     /* ���ٹ��ϱ�ʶλ*/
	DriverRampDownCnt_u16_Sig=0;/* IG OFF��ʱ��������*/

	TimeBaseCounter=-1;         /*ʱ���������ʼ����ֵ*/
	Testtimenum = 0;

	CanEnbale_v_g();            /*CAN0��CAN1 transferʹ��*/
}
/*!************************************************************************************
*	@fn	        void TimingSchedule_v_g(void)
*	@brief	          ʱ����Ⱥ���,���ڴ򿪲�ͬ������ж�
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       ��CCU61.c�е�CCU61_viNodeI0()��������
*	@Data       2019-3-12
****************************************************************************************/

void TimingSchedule_v_g(void)
{

	     TimeBaseCounter ++;/*---��ѯ����������---*/
	     Testtimenum++;
		  switch (TimeBaseCounter)
		  {
		    case 0:
		    	CCU60_2IC   |= 0x0040;  //---��Task1��CCU60_T12��ʱ���ж�
			break;
		    case TASK1_CNT:
		    	CCU60_3IC   |= 0x0040;  //---��Task2��CCU60_T13��ʱ���ж�
		    break;
		    case TASK2_CNT:
		    	GPT12E_T3IC |= 0x0040;  //---��Task3��T3��ʱ���ж�
		    break;

		    case TASK3_CNT:
		    	GPT12E_T4IC |= 0x0040;  //---��Task4��T4��ʱ���ж�
		    break;

		    case TASK4_CNT:
		    	TimeBaseCounter=-1;     //���ڼ�����0
		    break;
		  }
}
/*!************************************************************************************
*	@fn	        void TimingStart_v_g(void)
*	@brief	           ʱ���йض�ʱ����ʼ��
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       ��MAIN.c��main()�����е���
*	@Data       2019-3-12
****************************************************************************************/
void TimingStart_v_g(void)
{
	  CCU61_vStartTmr_CCU61_TIMER_12();    /*---����4·PWM�����ʱ��---*/

	  CCU60_vStartTmr_CCU60_TIMER_12();    /*---����Task1��ʱ��---*/
	  CCU60_vStartTmr_CCU60_TIMER_13();    /*---����Task2��ʱ��---*/

	  CCU60_2IC &= 0xFFBF;/*---�ر�Task1�ж�ʹ��---*/
	  CCU60_3IC &= 0xFFBF;/*---�ر�Task2�ж�ʹ��---*/



	  //CC2_vStartTmr_CC2_TIMER_7();

	  GPT12E_T3IC &= 0xFFBF;/*---�ر���ѯ����ж�ʹ��---*/
	  GPT12E_T4IC &= 0xFFBF;/*---�رչ�����ѯ�ж�ʹ��---*/
	  GPT12E_T2IC &= 0xFFBF;/*---�رն�ʱ��ѯ�ж�ʹ��---*/

	  GPT1_vStartTmr_GPT1_TIMER_3();/*---����T3��ʱ��*/
	  GPT1_vStartTmr_GPT1_TIMER_4();/*---����T4��ʱ��*/
	  GPT1_vStartTmr_GPT1_TIMER_2();/*---����T2��ʱ��*/
	  //GPT12E_T2IC |= 0x0040;
}
/*!************************************************************************************
*	@fn	        void WaitAssistRampDown_v_g(void)
*	@brief	    IG OFFʱ������ Ramp Down
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       ��task4.c��task4()�����е���
*	@Data       2019-3-12
****************************************************************************************/
void WaitDriverRampDown_v_g (void)
{
    if((IGNStatus_u8_Sig == 0) != 0)//IG״̬�ж�
    {
        DriverRampDownCnt_u16_Sig++;//ʱ�����
        if((DriverRampDownCnt_u16_Sig >= IG_RAMP_DOWN) != 0)//ʱ�䵽���ж�
        {
            NormalFinish_u8_Sig = 1;//����ģʽ������λ
        } else{
        }

    } else{
    	DriverRampDownCnt_u16_Sig = 0;//������0
    }

}

