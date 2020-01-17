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
*	@brief	          模式控制参数初始化及CAN使能
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       在MAIN.c的main()函数中调用
*	@Data       2019-3-12
****************************************************************************************/
void ISOInit_v_g(void)
{
	SystemMode_u8_Sig=0;        /* 系统模式 */
	PDTFinish_u8_Sig=0;         /* PowerDown模式结束标志位 */
	PUTFinish_u8_Sig=0;         /* PowerUpTest模式结束标志位 */
	PDFinish_u8_Sig=0;          /* PowerDownTest模式结束标志位*/
	NormalFinish_u8_Sig=0;      /* Normal模式结束标志位 */
	PDTtoPUTflag_u8_Sig=0;      /* PowerDown到PowerUpTest模式标志位*/
	MaintenStatus_u8_Sig=0;     /* 维护模式标志位  */
	IGNStatus_u8_Sig=0;         /* 点火信号状态*/
	MaintenLevel_u8_Sig=0;      /* 维护信号状态*/
	FaultLevel_u8_Sig=0;        /* 目前所发生故障的等级*/
	VehicleStatus_u8_Sig=0;     /* 车辆状态 是否为停止状态 */
	VehSpeedFault_u8_Sig=0;     /* 车速故障标识位*/
	DriverRampDownCnt_u16_Sig=0;/* IG OFF延时计数变量*/

	TimeBaseCounter=-1;         /*时序计数器初始化赋值*/
	Testtimenum = 0;

	CanEnbale_v_g();            /*CAN0、CAN1 transfer使能*/
}
/*!************************************************************************************
*	@fn	        void TimingSchedule_v_g(void)
*	@brief	          时序调度函数,用于打开不同任务的中断
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       在CCU61.c中的CCU61_viNodeI0()函数调用
*	@Data       2019-3-12
****************************************************************************************/

void TimingSchedule_v_g(void)
{

	     TimeBaseCounter ++;/*---轮询计数器计数---*/
	     Testtimenum++;
		  switch (TimeBaseCounter)
		  {
		    case 0:
		    	CCU60_2IC   |= 0x0040;  //---打开Task1的CCU60_T12定时器中断
			break;
		    case TASK1_CNT:
		    	CCU60_3IC   |= 0x0040;  //---打开Task2的CCU60_T13定时器中断
		    break;
		    case TASK2_CNT:
		    	GPT12E_T3IC |= 0x0040;  //---打开Task3的T3定时器中断
		    break;

		    case TASK3_CNT:
		    	GPT12E_T4IC |= 0x0040;  //---打开Task4的T4定时器中断
		    break;

		    case TASK4_CNT:
		    	TimeBaseCounter=-1;     //周期计数清0
		    break;
		  }
}
/*!************************************************************************************
*	@fn	        void TimingStart_v_g(void)
*	@brief	           时序有关定时器初始化
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       在MAIN.c的main()函数中调用
*	@Data       2019-3-12
****************************************************************************************/
void TimingStart_v_g(void)
{
	  CCU61_vStartTmr_CCU61_TIMER_12();    /*---开启4路PWM输出定时器---*/

	  CCU60_vStartTmr_CCU60_TIMER_12();    /*---开启Task1定时器---*/
	  CCU60_vStartTmr_CCU60_TIMER_13();    /*---开启Task2定时器---*/

	  CCU60_2IC &= 0xFFBF;/*---关闭Task1中断使能---*/
	  CCU60_3IC &= 0xFFBF;/*---关闭Task2中断使能---*/



	  //CC2_vStartTmr_CC2_TIMER_7();

	  GPT12E_T3IC &= 0xFFBF;/*---关闭轮询诊断中断使能---*/
	  GPT12E_T4IC &= 0xFFBF;/*---关闭公共轮询中断使能---*/
	  GPT12E_T2IC &= 0xFFBF;/*---关闭定时轮询中断使能---*/

	  GPT1_vStartTmr_GPT1_TIMER_3();/*---开启T3定时器*/
	  GPT1_vStartTmr_GPT1_TIMER_4();/*---开启T4定时器*/
	  GPT1_vStartTmr_GPT1_TIMER_2();/*---开启T2定时器*/
	  //GPT12E_T2IC |= 0x0040;
}
/*!************************************************************************************
*	@fn	        void WaitAssistRampDown_v_g(void)
*	@brief	    IG OFF时驱动力 Ramp Down
*	@author     Matt Zhang
*	@param[in]	void
*	@return	    void
*	@note       在task4.c的task4()函数中调用
*	@Data       2019-3-12
****************************************************************************************/
void WaitDriverRampDown_v_g (void)
{
    if((IGNStatus_u8_Sig == 0) != 0)//IG状态判断
    {
        DriverRampDownCnt_u16_Sig++;//时间计数
        if((DriverRampDownCnt_u16_Sig >= IG_RAMP_DOWN) != 0)//时间到达判断
        {
            NormalFinish_u8_Sig = 1;//正常模式结束置位
        } else{
        }

    } else{
    	DriverRampDownCnt_u16_Sig = 0;//计数清0
    }

}

