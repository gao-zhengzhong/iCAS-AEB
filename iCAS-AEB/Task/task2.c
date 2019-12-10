/*
 * Take2.c
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
void task2(void);
void task2Normal_v_s(void);
void task2PowerUpTest_v_s(void);
void task2PowerDownTest_v_s(void);
void task2PowerDown_v_s(void);
void task2Fault_v_s(void);


/*
*********************************************************************************************************
*                                             C ENTRY POINT
*********************************************************************************************************
*/
/*!************************************************************************************
*	@fn	        void task2(void)
*	@brief	          任务2函数
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       在CCU60.c中CCU60_viNodeI3()函数中调用
*	@Data       2019-3-12
****************************************************************************************/
void task2(void)
{
	   speed_time++;
	   if (speed_time > 1200){
		   speed_time = 0;
	   }

	   switch(SystemMode_u8_Sig)
		{
		case PowerUpTestMode:
			task2PowerUpTest_v_s();
		break;

		case NormalMode:
			task2Normal_v_s();
		break;

		case FaultMode:
			task2Fault_v_s();
		break;

		case PowerDownTestMode:
			task2PowerDownTest_v_s();
		break;

		case PowerDownMode:
			task2PowerDown_v_s();
		break;

		default:

		break;

		}
}
/*!************************************************************************************
*	@fn	        void task2PowerUpTest_v_s(void)
*	@brief	         任务2上电测试函数
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       在Task2.c的task2()函数中调用
*	@Data       2019-3-12
****************************************************************************************/
void task2PowerUpTest_v_s(void)
{

}


/*!************************************************************************************
*	@fn	        void task2Normal_v_s(void)
*	@brief	         任务2正常模式函数
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       在Task2.c的task2()函数中调用；另外AEB算法放在此函数中
*	@Data       2019-3-12
****************************************************************************************/
INT32U testvalue11=0;
INT32U testvalue12=0;
INT32U testvalue13=0;
void task2Normal_v_s(void)
{
/*------------------AEB功能算法--------------------*/
	//AebAlgorithm();

/*--------------------PWM赋值给底层接口----------------------------*/
PWMA_u16_Sig=((INT32U)MotorPwm_Ctrl*2000)>>12;
PWMB_u16_Sig=2000-PWMA_u16_Sig;
/*--------------------制动灯控制------------------*/

if(BrakeLight==1)
{
CTRL_LAMP_ON;//开制动灯
}
else
{
CTRL_LAMP_OFF;//关制动灯
}

}
/*!************************************************************************************
*	@fn	        void task2PowerDownTest_v_s(void)
*	@brief	         任务2下电测试模式函数
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       在Task2.c的task2()函数中调用
*	@Data       2019-3-12
****************************************************************************************/
void task2PowerDownTest_v_s(void)
{

}
/*!************************************************************************************
*	@fn	        void task2PowerDown_v_s(void)
*	@brief	         任务2下电模式函数
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       在Task2.c的task2()函数中调用
*	@Data       2019-3-12
****************************************************************************************/
void task2PowerDown_v_s(void){

}
/*!************************************************************************************
*	@fn	        void task2Fault_v_s(void)
*	@brief	         任务2故障模式函数
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       在Task2.c的task2()函数中调用
*	@Data       2019-3-12
****************************************************************************************/
void task2Fault_v_s(void)
{

}

