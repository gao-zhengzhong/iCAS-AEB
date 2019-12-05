/*
 * Task1.c
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
void task1(void);
void task1Normal_v_s(void);
void task1PowerUpTest_v_s(void);
void task1PowerDownTest_v_s(void);
void task1PowerDown_v_s(void);
void task1Fault_v_s(void);

/*
*********************************************************************************************************
*                                             C ENTRY POINT
*********************************************************************************************************
*/
/*!************************************************************************************
*	@fn	        void task1(void)
*	@brief	         ����1����
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       ��CCU60.c��CCU60_viNodeI2()�����е���
*	@Data       2019-3-12
****************************************************************************************/
void task1(void)
{
	   switch(SystemMode_u8_Sig)
		{
		case PowerUpTestMode:
			task1PowerUpTest_v_s();
		break;

		case NormalMode:
			task1Normal_v_s();
		break;

		case FaultMode:
			task1Fault_v_s();
		break;

		case PowerDownTestMode:
			task1PowerDownTest_v_s();
		break;

		case PowerDownMode:
			task1PowerDown_v_s();
		break;

		default:

		break;

		}


}
/*!************************************************************************************
*	@fn	        void task1PowerUpTest_v_s(void)
*	@brief	         ����1�ϵ���Ժ���
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       ��Task1.c��task1()�����е���
*	@Data       2019-3-12
****************************************************************************************/
void task1PowerUpTest_v_s(void){

}

/*!************************************************************************************
*	@fn	        void task1Normal_v_s(void)
*	@brief	         ����1����ģʽ����
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       ��Task1.c��task1()�����е��ã�����icas-brake�㷨���ڴ˺�����
*	@Data       2019-3-12
****************************************************************************************/

INT16U vspyTestVal_1 = 2;
INT16U vspyTestVal_2 = 5;
INT16U vspyTestVal_addr;
void task1Normal_v_s(void)
{
	Adc_Func();
	FLTD_CyclicProcess();
	
		vspyTestVal_addr = &vspyTestVal_1;
	    /*---------------------��������--------------------*/
		 Motor_Cur=SingleADSample_v_g(0,CUR_SAMPLE_ADC0);
		 /*---------------------ѹ������������--------------------*/
		 BrakePressure_AD=SingleADSample_v_g(1,BRAKE_PRESSURE_ADC1);
		 /*---------------------�����г̲���--------------------*/
		 ADC0_vStartSeq2ReqChNum(0,0,0,2); //�������
		 while(ADC0_uwBusy());
	     while(ADC1_uwBusy());
	     Mastercyler_AD1  = ADC0_uwGetResultData_RESULT_REG_1;
	     Mastercyler_AD2  = ADC1_uwGetResultData_RESULT_REG_1;

	     /*---------------------̤���г̲���--------------------*/
		 ADC0_vStartSeq2ReqChNum(0,0,0,0); //�������
		 while(ADC0_uwBusy());
	     while(ADC1_uwBusy());
	     Pedal_location_AD1  = ADC0_uwGetResultData_RESULT_REG_0;
	     Pedal_location_AD2  = ADC1_uwGetResultData_RESULT_REG_0;
	     /*--------------------�ƶ������źż�Ԥ��״̬�źŲ���-----------------*/
	     BrakeSW=BRAKE_SIGNEL;
	 	 PreDriverStatus=PRE_ERR_SIGNEL;
	 	/*--------------------AB���ѹ����-----------------*/
    	 AphasePwr_AD=SingleADSample_v_g(0,APHASE_BATT_SAMPLE_ADC0); //A���ѹ����
    	 BphasePwr_AD=SingleADSample_v_g(0,BPHASE_BATT_SAMPLE_ADC0); //B���ѹ����
	     /*--------------------icas-brake�����㷨--------------------------*/


	 	 /*--------------------PWM��ֵ���ײ�ӿ�----------------------------*/
	 	 PWMA_u16_Sig=((INT32U)MotorPwm_Ctrl*2000)>>12;
	 	 PWMB_u16_Sig=2000-PWMA_u16_Sig;

}
/*!************************************************************************************
*	@fn	        void task1PowerDownTest_v_s(void)
*	@brief	         ����1�µ����ģʽ����
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       ��Task1.c��task1()�����е���
*	@Data       2019-3-12
****************************************************************************************/
void task1PowerDownTest_v_s(void){

}
/*!************************************************************************************
*	@fn	        void task1PowerDown_v_s(void)
*	@brief	         ����1�µ�ģʽ����
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       ��Task1.c��task1()�����е���
*	@Data       2019-3-12
****************************************************************************************/
void task1PowerDown_v_s(void){

}
/*!************************************************************************************
*	@fn	        void task1Fault_v_s(void)
*	@brief	         ����1����ģʽ����
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       ��Task1.c��task1()�����е���
*	@Data       2019-3-12
****************************************************************************************/
void task1Fault_v_s(void)
{

}
