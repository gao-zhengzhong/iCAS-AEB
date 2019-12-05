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
*	@brief	         任务1函数
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       在CCU60.c中CCU60_viNodeI2()函数中调用
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
*	@brief	         任务1上电测试函数
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       在Task1.c的task1()函数中调用
*	@Data       2019-3-12
****************************************************************************************/
void task1PowerUpTest_v_s(void){

}

/*!************************************************************************************
*	@fn	        void task1Normal_v_s(void)
*	@brief	         任务1正常模式函数
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       在Task1.c的task1()函数中调用；另外icas-brake算法放在此函数中
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
	    /*---------------------电流采样--------------------*/
		 Motor_Cur=SingleADSample_v_g(0,CUR_SAMPLE_ADC0);
		 /*---------------------压力传感器采样--------------------*/
		 BrakePressure_AD=SingleADSample_v_g(1,BRAKE_PRESSURE_ADC1);
		 /*---------------------主缸行程采样--------------------*/
		 ADC0_vStartSeq2ReqChNum(0,0,0,2); //旋变采样
		 while(ADC0_uwBusy());
	     while(ADC1_uwBusy());
	     Mastercyler_AD1  = ADC0_uwGetResultData_RESULT_REG_1;
	     Mastercyler_AD2  = ADC1_uwGetResultData_RESULT_REG_1;

	     /*---------------------踏板行程采样--------------------*/
		 ADC0_vStartSeq2ReqChNum(0,0,0,0); //旋变采样
		 while(ADC0_uwBusy());
	     while(ADC1_uwBusy());
	     Pedal_location_AD1  = ADC0_uwGetResultData_RESULT_REG_0;
	     Pedal_location_AD2  = ADC1_uwGetResultData_RESULT_REG_0;
	     /*--------------------制动开关信号及预驱状态信号采样-----------------*/
	     BrakeSW=BRAKE_SIGNEL;
	 	 PreDriverStatus=PRE_ERR_SIGNEL;
	 	/*--------------------AB相电压采样-----------------*/
    	 AphasePwr_AD=SingleADSample_v_g(0,APHASE_BATT_SAMPLE_ADC0); //A相电压采样
    	 BphasePwr_AD=SingleADSample_v_g(0,BPHASE_BATT_SAMPLE_ADC0); //B相电压采样
	     /*--------------------icas-brake助力算法--------------------------*/


	 	 /*--------------------PWM赋值给底层接口----------------------------*/
	 	 PWMA_u16_Sig=((INT32U)MotorPwm_Ctrl*2000)>>12;
	 	 PWMB_u16_Sig=2000-PWMA_u16_Sig;

}
/*!************************************************************************************
*	@fn	        void task1PowerDownTest_v_s(void)
*	@brief	         任务1下电测试模式函数
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       在Task1.c的task1()函数中调用
*	@Data       2019-3-12
****************************************************************************************/
void task1PowerDownTest_v_s(void){

}
/*!************************************************************************************
*	@fn	        void task1PowerDown_v_s(void)
*	@brief	         任务1下电模式函数
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       在Task1.c的task1()函数中调用
*	@Data       2019-3-12
****************************************************************************************/
void task1PowerDown_v_s(void){

}
/*!************************************************************************************
*	@fn	        void task1Fault_v_s(void)
*	@brief	         任务1故障模式函数
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       在Task1.c的task1()函数中调用
*	@Data       2019-3-12
****************************************************************************************/
void task1Fault_v_s(void)
{

}
