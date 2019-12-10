/*
 * Task1.c
 *
 *  Created on: 2019-3-5
 *      Author: Administrator
 */
#include"MAIN.h"
#include"iCasBrake.h"

/*
*********************************************************************************************************
*                                                MACROS
*********************************************************************************************************
*/

#define ReceivePC_ID           0x31       // 上位机标识符
#define SendPC_ID0             0x21       // 发送标识符
#define SendPC_ID1             0x22       // 发送标识符
#define data_len_TX            8          // 发送数据长度
#define PWM_MAX   760
#define PWM_MIN   370
#define PRESSURE_MAX 1000                 // 200+80*10
#define PRESSURE_MIN 200                  // 200+80*0
#define INIT_PRESSURE 220
#define INTERRUPTTIME 50
// #define MotorDuty PWMDTY01

#define ABS(a) ((a)>0?(a):(-(a)))
#define SIGN(a) ((a)>0?1:((a)<0?-1:0))

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
void task1(void);                        //任务分配：上电自检、正常工作模式、断电检测、断电模式、故障模式
void task1PowerUpTest_v_s(void);         //上电自检
void task1Normal_v_s(void);              //正常工作模式：AD采样、助力系统控制
void task1PowerDownTest_v_s(void);       //断电检测
void task1PowerDown_v_s(void);           //断电模式
void task1Fault_v_s(void);               //故障模式

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
*	@note       在CCU60.c中CCU60_viNodeI2()函数中调用，该函数为OS系统任务分配函数
*	@Data       2019-3-12
****************************************************************************************/
void task1(void){

	   MCTimer++;
	   if(MCTimer>30000)
		   MCTimer = 0;

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
void task1Normal_v_s(void)                                 //AD采样加助力控制
{
	    /*---------------------电流采样--------------------*/
	     Motor_Cur_AD=SingleADSample_v_g(0,CUR_SAMPLE_ADC0);
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
    	 AD_Filtration();    //AD采样函数
         AD_to_real();       //AD采样转换成实际值

        // BrakeSysMode = APA_BrakeFlag;
     /*--------------------------踏板干预的判断逻辑--------------------------*/
         APA_Count ++;
         if(APA_Count >80) {
        	 APA_BrakeFlag = 0;
        	 APA_TargetPrs = 0;
        	 BrakeSysMode = 0;
        	 APA_Count = 0;
         }

         if((Pedal_location_AD1 > (Pedal_Init_loc_AD + 30))&&(BrakeSysMode!=BoosterBrakeMode))
         {
        	 BrakeSysMode=BoosterBrakeMode;
        	 AebStandMode =0;
        	 AEB_State_now =0;
        	 TTC=20;
         }


         if(BrakeSysMode==BoosterBrakeMode)         //  助力模式判定
         {
        	 MC_Location_PID();
         }

         else if(BrakeSysMode == APABrakeMode)       //  APA模式判定
         {
        	 APAFunction();
         }

         else if(BrakeSysMode==AebBrakeMode)        //  AEB模式判定
	     {
		    MC_Presure_PID(Aeb_targetpress_value);
	     }

         Real_To_Can();                             //   CAN发送整定

	 	 /*--------------------PWM赋值给底层接口----------------------------*/
	 	 PWMA_u16_Sig=((INT32U)MotorPwm_Ctrl*2000)>>12;
		 if(PWMA_u16_Sig>1900)
		 {
		 		PWMA_u16_Sig=1900;
		 }
		 else if(PWMA_u16_Sig<100)
		 {
			 PWMA_u16_Sig=100;
		 }
		 else
		 {
		 }
	 	 PWMB_u16_Sig=2000-PWMA_u16_Sig;



}
/*!************************************************************************************
*	@fn	        void AD_SampleTest (void)
*	@brief	         任务1下电流采样函数
*	@author     Matt Dou
*	@param[in]	void
*	@return	    void
*	@note       在Task1.c的task1()函数中调用
*	@Data       2019-3-12
****************************************************************************************/
void AD_SampleTest(void){                                                //AD采样函数
	        Motor_Cur_AD=SingleADSample_v_g(0,CUR_SAMPLE_ADC0);             //电机电流采样

	        BrakePressure_AD=SingleADSample_v_g(1,BRAKE_PRESSURE_ADC1);  //主缸压力采样

	        ADC0_vStartSeq2ReqChNum(0,0,0,2); //旋变采样
	          while(ADC0_uwBusy());
	          while(ADC1_uwBusy());
	        Mastercyler_AD1  = ADC0_uwGetResultData_RESULT_REG_1;        //主缸行程1采样
	        Mastercyler_AD2  = ADC1_uwGetResultData_RESULT_REG_1;        //主缸行程2采样

	        ADC0_vStartSeq2ReqChNum(0,0,0,0); //旋变采样
	          while(ADC0_uwBusy());
	          while(ADC1_uwBusy());
	        Pedal_location_AD1  = ADC0_uwGetResultData_RESULT_REG_0;     //踏板行程1采样
	        Pedal_location_AD2  = ADC1_uwGetResultData_RESULT_REG_0;     //踏板行程2采样

	        BrakeSW=BRAKE_SIGNEL;                                        //制动信号
	        PreDriverStatus=PRE_ERR_SIGNEL;

	        AphasePwr_AD=SingleADSample_v_g(0,APHASE_BATT_SAMPLE_ADC0); //A相电压采样
	        BphasePwr_AD=SingleADSample_v_g(0,BPHASE_BATT_SAMPLE_ADC0); //B相电压采样
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
