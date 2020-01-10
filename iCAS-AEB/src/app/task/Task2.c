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
*	@brief	          ����2����
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       ��CCU60.c��CCU60_viNodeI3()�����е���
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
*	@brief	         ����2�ϵ���Ժ���
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       ��Task2.c��task2()�����е���
*	@Data       2019-3-12
****************************************************************************************/
void task2PowerUpTest_v_s(void)
{

}


/*!************************************************************************************
*	@fn	        void task2Normal_v_s(void)
*	@brief	         ����2����ģʽ����
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       ��Task2.c��task2()�����е��ã�����AEB�㷨���ڴ˺�����
*	@Data       2019-3-12
****************************************************************************************/
INT32U testvalue11=0;
INT32U testvalue12=0;
INT32U testvalue13=0;
void task2Normal_v_s(void)
{
/*------------------AEB�����㷨--------------------*/
	//AebAlgorithm();

/*--------------------PWM��ֵ���ײ�ӿ�----------------------------*/
PWMA_u16_Sig=((INT32U)MotorPwm_Ctrl*2000)>>12;
PWMB_u16_Sig=2000-PWMA_u16_Sig;
/*--------------------�ƶ��ƿ���------------------*/

if(BrakeLight==1)
{
CTRL_LAMP_ON;//���ƶ���
}
else
{
CTRL_LAMP_OFF;//���ƶ���
}

}
/*!************************************************************************************
*	@fn	        void task2PowerDownTest_v_s(void)
*	@brief	         ����2�µ����ģʽ����
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       ��Task2.c��task2()�����е���
*	@Data       2019-3-12
****************************************************************************************/
void task2PowerDownTest_v_s(void)
{

}
/*!************************************************************************************
*	@fn	        void task2PowerDown_v_s(void)
*	@brief	         ����2�µ�ģʽ����
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       ��Task2.c��task2()�����е���
*	@Data       2019-3-12
****************************************************************************************/
void task2PowerDown_v_s(void){

}
/*!************************************************************************************
*	@fn	        void task2Fault_v_s(void)
*	@brief	         ����2����ģʽ����
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       ��Task2.c��task2()�����е���
*	@Data       2019-3-12
****************************************************************************************/
void task2Fault_v_s(void)
{

}

