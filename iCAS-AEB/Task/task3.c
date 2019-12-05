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
*	@brief	          任务3函数
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       在GPT1.c中GPT1_viTmr3()函数中调用
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
	Can1RecDeal_v_g();//整车CAN接收数据处理 CAN1
	#endif
//	CanSendMsg_v_g(10,xxmsg,8);
	ccploop_v_g();//CCP协议标定
}
/*!************************************************************************************
*	@fn	        void task3PowerUpTest_v_s(void)
*	@brief	          任务3上电测试函数
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       此函 数是上电自检函数，每检测信号通过继续往下检测直至检测全部通过;在Task3.c的task3()函数中
*	@Data       2019-3-12
****************************************************************************************/
void task3PowerUpTest_v_s(void)
{
	switch (PowerUpTestState) {

		  case EcmStart:

			POWER_ENABLE_ON;    //供电电源使能
			PREPWR_ENABLE_ON;   //压力传感器电源使能
			MASTERPWR_ENABLE_ON;//主缸行程电源使能
			PEDALPWR_ENABLE_ON; //踏板行程电源使能
			CTRL_LAMP_OFF;      //制动开关关闭

			PowerUpTestPhase.BIT.Phase0 =1;//置1后进行下一步检测
			if (PowerUpTestPhase.BIT.Phase0 == 1){
				PowerUpTestState = EcmWait1;//Step置位下一步
			}
			break;

			case EcmWait1:


			PowerUpTestPhase.BIT.Phase1 = 1;//置1后进行下一步检测

			if (PowerUpTestPhase.BIT.Phase1 == 1){
				PowerUpTestState = EcmWait2;//Step置位下一步
			}
			break;

			case EcmWait2:

			PowerUpTestPhase.BIT.Phase2 = 1;
			if (PowerUpTestPhase.BIT.Phase2 == 1){
				PowerUpTestState = EcmWait3;
			}
			break;

			case EcmWait3:


			Resrd12VPwr_AD=SingleADSample_v_g(0,BATT_SAMPLE_ADC0);//电源电压采样


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
			MAINRELAY_ENABLE_ON;//主机继电器打开

			PowerUpTestPhase.BIT.Phase6 = 1;

            if (PowerUpTestPhase.BIT.Phase6== 1){
				PowerUpTestState = EcmWait7;
			}
			break;

			case EcmWait7:
			if(Driver_v_g()==1)	{//预驱动打开
			PowerUpTestPhase.BIT.Phase7 = 1;
			}
			if (PowerUpTestPhase.BIT.Phase7 == 1){
				PowerUpTestState = EcmWait8;
			}
			break;

			case EcmWait8:
			Tempreture_AD=SingleADSample_v_g(0,DRIVER_TEMP_SAMPLE_ADC0);//温度采样
			VlinkPwr_AD=SingleADSample_v_g(0,VLINK_SAMPLE_ADC0);        //母线电压采样
			AphasePwr_AD=SingleADSample_v_g(0,APHASE_BATT_SAMPLE_ADC0); //A相电压采样
			BphasePwr_AD=SingleADSample_v_g(0,BPHASE_BATT_SAMPLE_ADC0); //B相电压采样
			PrsPwr_AD=SingleADSample_v_g(0,PRSPWR_SAMPLE_ADC0);         //压力传感器电压采样
			MasterPwr_AD=SingleADSample_v_g(0,MASTERPWR_SAMPLE_ADC0);   //主缸电压采样
			PedalPwr_AD=SingleADSample_v_g(0,PEDALPWR_SAMPLE_ADC0);     //踏板电压采样

			PowerUpTestPhase.BIT.Phase8 = 1;
			if (PowerUpTestPhase.BIT.Phase8 == 1){
				PowerUpTestState = EcmEnd;
			}
			else {

			}
			break;

			case EcmEnd:


			PUTFinish_u8_Sig = 1;		//上电测试模式结束
			PowerUpTestState = EcmStart;		//重新转换到初始状态

			/* --- 恢复各个阶段完成定义 --- */
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
*	@brief	          任务3正常模式函数
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       电源信号的采样及诊断，诊断方面可后续增加;在Task3.c的task3()函数中
*	@Data       2019-3-12
****************************************************************************************/
void task3Normal_v_s(void)
{

    /* --- task3分频12.5ms --- */
    Task3SchedCnt++;
    /* --- 等待100ms的驱动 ramp down 结束后置位正常模式结束 --- */
    WaitDriverRampDown_v_g();


	switch (Task3SchedCnt) {

	     case 1:
	    	 Resrd12VPwr_AD=SingleADSample_v_g(0,BATT_SAMPLE_ADC0);      //电源电压采样

	            break;

	     case 2:
	    	 Tempreture_AD=SingleADSample_v_g(0,DRIVER_TEMP_SAMPLE_ADC0);//温度采样
	            break;

	     case 3:
	    	 VlinkPwr_AD=SingleADSample_v_g(0,VLINK_SAMPLE_ADC0);        //母线电压采样
	            break;

	     case 4:
	    	 PrsPwr_AD=SingleADSample_v_g(0,PRSPWR_SAMPLE_ADC0);         //压力传感器电压采样
	            break;

	     case 5:
	    	 MasterPwr_AD=SingleADSample_v_g(0,MASTERPWR_SAMPLE_ADC0);   //主缸电压采样
	    	 PedalPwr_AD=SingleADSample_v_g(0,PEDALPWR_SAMPLE_ADC0);     //踏板电压采样

	    	 Task3SchedCnt=0;
	         break;


	     default:
	            break;
	     }

}
/*!************************************************************************************
*	@fn	        void task3PowerDownTest_v_s(void)
*	@brief	          任务3下电测试函数
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       下电测试主要是PWM占空比50%设定、关闭预驱、关闭主继电器;在Task3.c的task3()函数中
*	@Data       2019-3-12
****************************************************************************************/
void task3PowerDownTest_v_s(void)
{
	static INT8U Delay=0;
		switch (PowerDownTestState) {

					case EcmStart:
					PWMA_u16_Sig=FIFTY_PWM;//下电设定百分之50占空比
					PWMB_u16_Sig=FIFTY_PWM;//下电设定百分之50占空比
					PowerDownTestPhase.BIT.Phase0 = 1;
					if(PowerDownTestPhase.BIT.Phase0 == 1){
					PowerDownTestState = EcmWait1;
					}
					break;

					case EcmWait1:
				    PREDRIVER_ENABLE_OFF;//预驱关闭
					PowerDownTestPhase.BIT.Phase1 = 1;
					if(PowerDownTestPhase.BIT.Phase1 == 1){
						PowerDownTestState = EcmWait2;
					}
					break;

					case EcmWait2:
					MAINRELAY_ENABLE_OFF;//主继电器关闭
				    Delay++;
					if(Delay==MAIN_RELAY_OFF_DELAYTIME)//主继电器关闭延时30ms
					{
						Delay=0;
						PowerDownTestPhase.BIT.Phase2 = 1;
					}

					if(PowerDownTestPhase.BIT.Phase2 == 1){
						PowerDownTestState = EcmEnd;
					}
				    break;

					case EcmEnd:
					/* --- 下电测试模式结束 --- */

					PDTFinish_u8_Sig = 1;
					 /* --- 重新转换到初始状态 --- */
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
*	@brief	          任务3下电函数
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       在Task3的task3()函数中
*	@Data       2019-3-12
****************************************************************************************/
void task3PowerDown_v_s(void){
	PDFinish_u8_Sig=1;
	POWER_ENABLE_OFF;//关闭主电源，POWEROFF

}
/*!************************************************************************************
*	@fn	        void task3Fault_v_s(void)
*	@brief	          任务3故障模式函数
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       在Task3.c的task3()函数中
*	@Data       2019-3-12
****************************************************************************************/
void task3Fault_v_s(void)
{

}









