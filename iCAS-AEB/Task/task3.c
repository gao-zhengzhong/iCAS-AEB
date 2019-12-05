/*
 * Task3.c
 *
 *  Created on: 2019-3-5
 *      Author: Administrator
 */
#include"MAIN.h"


/*
*********************************************************************************************************
*                                                MACROS
*********************************************************************************************************
*/


#define MAIN_RELAY_OFF_DELAYTIME 8

/*
*********************************************************************************************************
*                                               VARIABLES
*********************************************************************************************************
*/


INT8U Task3SchedCnt=0;
INT8U xxmsg[8] = {1,2,3,4,5,6,7,8};
/*
*********************************************************************************************************
*                                          FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void task3(void);
void task3Normal_v_s(void);
void task3PowerUpTest_v_s(void);
void task3PowerDownTest_v_s(void);
void task3PowerDown_v_s(void);
void task3Fault_v_s(void);

extern void ccploop_v_g(void);
/*
*********************************************************************************************************
*                                             C ENTRY POINT
*********************************************************************************************************
*/

/*!************************************************************************************
*	@fn	        void task3(void)
*	@brief	          ����3����
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       ��GPT1.c��GPT1_viTmr3()�����е���
*	@Data       2019-3-12
****************************************************************************************/

void task3(void)
{
	switch(SystemMode_u8_Sig)
	{
	case PowerUpTestMode:
		task3PowerUpTest_v_s();
	break;

	case NormalMode:
		task3Normal_v_s();
	break;

	case FaultMode:
		task3Fault_v_s();
	break;

	case PowerDownTestMode:
		task3PowerDownTest_v_s();
	break;

	case PowerDownMode:
		task3PowerDown_v_s();
	break;

	default:

	break;

	}
	#if 0
	Can1RecDeal_v_g();//����CAN�������ݴ��� CAN1
	#endif
//	CanSendMsg_v_g(10,xxmsg,8);
	ccploop_v_g();//CCPЭ��궨
}
/*!************************************************************************************
*	@fn	        void task3PowerUpTest_v_s(void)
*	@brief	          ����3�ϵ���Ժ���
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       �˺� �����ϵ��Լ캯����ÿ����ź�ͨ���������¼��ֱ�����ȫ��ͨ��;��Task3.c��task3()������
*	@Data       2019-3-12
****************************************************************************************/
void task3PowerUpTest_v_s(void)
{
	switch (PowerUpTestState) {

		  case EcmStart:

			POWER_ENABLE_ON;    //�����Դʹ��
			PREPWR_ENABLE_ON;   //ѹ����������Դʹ��
			MASTERPWR_ENABLE_ON;//�����г̵�Դʹ��
			PEDALPWR_ENABLE_ON; //̤���г̵�Դʹ��
			CTRL_LAMP_OFF;      //�ƶ����عر�

			PowerUpTestPhase.BIT.Phase0 =1;//��1�������һ�����
			if (PowerUpTestPhase.BIT.Phase0 == 1){
				PowerUpTestState = EcmWait1;//Step��λ��һ��
			}
			break;

			case EcmWait1:


			PowerUpTestPhase.BIT.Phase1 = 1;//��1�������һ�����

			if (PowerUpTestPhase.BIT.Phase1 == 1){
				PowerUpTestState = EcmWait2;//Step��λ��һ��
			}
			break;

			case EcmWait2:

			PowerUpTestPhase.BIT.Phase2 = 1;
			if (PowerUpTestPhase.BIT.Phase2 == 1){
				PowerUpTestState = EcmWait3;
			}
			break;

			case EcmWait3:


			Resrd12VPwr_AD=SingleADSample_v_g(0,BATT_SAMPLE_ADC0);//��Դ��ѹ����


		    PowerUpTestPhase.BIT.Phase3 = 1;
			if (PowerUpTestPhase.BIT.Phase3 == 1){
				PowerUpTestState = EcmWait4;
			}
		    break;

		    case EcmWait4:

		    PowerUpTestPhase.BIT.Phase4 = 1;
			if (PowerUpTestPhase.BIT.Phase4 == 1){
				PowerUpTestState = EcmWait5;
			}
		    break;

			case EcmWait5:

			PowerUpTestPhase.BIT.Phase5 = 1;
			if (PowerUpTestPhase.BIT.Phase5 == 1){
				PowerUpTestState = EcmWait6;
			}
		    break;

			case EcmWait6:
			MAINRELAY_ENABLE_ON;//�����̵�����

			PowerUpTestPhase.BIT.Phase6 = 1;

            if (PowerUpTestPhase.BIT.Phase6== 1){
				PowerUpTestState = EcmWait7;
			}
			break;

			case EcmWait7:
			if(Driver_v_g()==1)	{//Ԥ������
			PowerUpTestPhase.BIT.Phase7 = 1;
			}
			if (PowerUpTestPhase.BIT.Phase7 == 1){
				PowerUpTestState = EcmWait8;
			}
			break;

			case EcmWait8:
			Tempreture_AD=SingleADSample_v_g(0,DRIVER_TEMP_SAMPLE_ADC0);//�¶Ȳ���
			VlinkPwr_AD=SingleADSample_v_g(0,VLINK_SAMPLE_ADC0);        //ĸ�ߵ�ѹ����
			AphasePwr_AD=SingleADSample_v_g(0,APHASE_BATT_SAMPLE_ADC0); //A���ѹ����
			BphasePwr_AD=SingleADSample_v_g(0,BPHASE_BATT_SAMPLE_ADC0); //B���ѹ����
			PrsPwr_AD=SingleADSample_v_g(0,PRSPWR_SAMPLE_ADC0);         //ѹ����������ѹ����
			MasterPwr_AD=SingleADSample_v_g(0,MASTERPWR_SAMPLE_ADC0);   //���׵�ѹ����
			PedalPwr_AD=SingleADSample_v_g(0,PEDALPWR_SAMPLE_ADC0);     //̤���ѹ����

			PowerUpTestPhase.BIT.Phase8 = 1;
			if (PowerUpTestPhase.BIT.Phase8 == 1){
				PowerUpTestState = EcmEnd;
			}
			else {

			}
			break;

			case EcmEnd:


			PUTFinish_u8_Sig = 1;		//�ϵ����ģʽ����
			PowerUpTestState = EcmStart;		//����ת������ʼ״̬

			/* --- �ָ������׶���ɶ��� --- */
			PowerUpTestPhase.BIT.Phase0 = 0;
			PowerUpTestPhase.BIT.Phase1 = 0;
			PowerUpTestPhase.BIT.Phase2 = 0;
			PowerUpTestPhase.BIT.Phase3 = 0;
			PowerUpTestPhase.BIT.Phase4 = 0;
			PowerUpTestPhase.BIT.Phase5 = 0;
			PowerUpTestPhase.BIT.Phase6 = 0;
			PowerUpTestPhase.BIT.Phase7 = 0;
			PowerUpTestPhase.BIT.Phase8 = 0;
			PowerUpTestPhase.BIT.Phase9 = 0;
			break;

			default:

			break;

			}




}
/*!************************************************************************************
*	@fn	        void task3Normal_v_s(void)
*	@brief	          ����3����ģʽ����
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       ��Դ�źŵĲ�������ϣ���Ϸ���ɺ�������;��Task3.c��task3()������
*	@Data       2019-3-12
****************************************************************************************/
void task3Normal_v_s(void)
{

    /* --- task3��Ƶ12.5ms --- */
    Task3SchedCnt++;
    /* --- �ȴ�100ms������ ramp down ��������λ����ģʽ���� --- */
    WaitDriverRampDown_v_g();


	switch (Task3SchedCnt) {

	     case 1:
	    	 Resrd12VPwr_AD=SingleADSample_v_g(0,BATT_SAMPLE_ADC0);      //��Դ��ѹ����

	            break;

	     case 2:
	    	 Tempreture_AD=SingleADSample_v_g(0,DRIVER_TEMP_SAMPLE_ADC0);//�¶Ȳ���
	            break;

	     case 3:
	    	 VlinkPwr_AD=SingleADSample_v_g(0,VLINK_SAMPLE_ADC0);        //ĸ�ߵ�ѹ����
	            break;

	     case 4:
	    	 PrsPwr_AD=SingleADSample_v_g(0,PRSPWR_SAMPLE_ADC0);         //ѹ����������ѹ����
	            break;

	     case 5:
	    	 MasterPwr_AD=SingleADSample_v_g(0,MASTERPWR_SAMPLE_ADC0);   //���׵�ѹ����
	    	 PedalPwr_AD=SingleADSample_v_g(0,PEDALPWR_SAMPLE_ADC0);     //̤���ѹ����

	    	 Task3SchedCnt=0;
	         break;


	     default:
	            break;
	     }

}
/*!************************************************************************************
*	@fn	        void task3PowerDownTest_v_s(void)
*	@brief	          ����3�µ���Ժ���
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       �µ������Ҫ��PWMռ�ձ�50%�趨���ر�Ԥ�����ر����̵���;��Task3.c��task3()������
*	@Data       2019-3-12
****************************************************************************************/
void task3PowerDownTest_v_s(void)
{
	static INT8U Delay=0;
		switch (PowerDownTestState) {

					case EcmStart:
					PWMA_u16_Sig=FIFTY_PWM;//�µ��趨�ٷ�֮50ռ�ձ�
					PWMB_u16_Sig=FIFTY_PWM;//�µ��趨�ٷ�֮50ռ�ձ�
					PowerDownTestPhase.BIT.Phase0 = 1;
					if(PowerDownTestPhase.BIT.Phase0 == 1){
					PowerDownTestState = EcmWait1;
					}
					break;

					case EcmWait1:
				    PREDRIVER_ENABLE_OFF;//Ԥ���ر�
					PowerDownTestPhase.BIT.Phase1 = 1;
					if(PowerDownTestPhase.BIT.Phase1 == 1){
						PowerDownTestState = EcmWait2;
					}
					break;

					case EcmWait2:
					MAINRELAY_ENABLE_OFF;//���̵����ر�
				    Delay++;
					if(Delay==MAIN_RELAY_OFF_DELAYTIME)//���̵����ر���ʱ30ms
					{
						Delay=0;
						PowerDownTestPhase.BIT.Phase2 = 1;
					}

					if(PowerDownTestPhase.BIT.Phase2 == 1){
						PowerDownTestState = EcmEnd;
					}
				    break;

					case EcmEnd:
					/* --- �µ����ģʽ���� --- */

					PDTFinish_u8_Sig = 1;
					 /* --- ����ת������ʼ״̬ --- */
					PowerDownTestState = EcmStart;
					PowerDownTestPhase.BIT.Phase0 = 0;
					PowerDownTestPhase.BIT.Phase1 = 0;
					PowerDownTestPhase.BIT.Phase2 = 0;
					break;

					default:

					break;
			}

}
/*!************************************************************************************
*	@fn	        void task3PowerDown_v_s(void)
*	@brief	          ����3�µ纯��
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       ��Task3��task3()������
*	@Data       2019-3-12
****************************************************************************************/
void task3PowerDown_v_s(void){
	PDFinish_u8_Sig=1;
	POWER_ENABLE_OFF;//�ر�����Դ��POWEROFF

}
/*!************************************************************************************
*	@fn	        void task3Fault_v_s(void)
*	@brief	          ����3����ģʽ����
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       ��Task3.c��task3()������
*	@Data       2019-3-12
****************************************************************************************/
void task3Fault_v_s(void)
{

}









