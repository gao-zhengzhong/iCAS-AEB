/*
 * Fun.h
 *
 *  Created on: 2019-3-8
 *      Author: Administrator
 */

#ifndef FUN_H_
#define FUN_H_

#ifdef   FUN_GLOBALS
	#define  FUN_EXT
#else
	#define  FUN_EXT  extern
#endif


#define IG_OFF 0 //IG状态为OFF
#define IG_ON  1 //IG状态为ON

#define FIFTY_PWM 1000 //50%PWM占空比


#define PREDRIVER_ON_DELAYTIME 40   //预驱延时打开时间
#define IG_ON_DURATION         40   //IG ON持续判断时间
#define IG_OFF_DURATION        80   //IG OFF持续判断时间


FUN_EXT INT8U TempValueTab[50];
FUN_EXT FP32 TempADTab[50];
FUN_EXT INT8U temploc;
FUN_EXT FP32 RealTemperature;

/****************lp argument end***********/
FUN_EXT INT16U PWMA_u16_Sig;//A相PWM占空比
FUN_EXT INT16U PWMB_u16_Sig;//B相PWM占空比

FUN_EXT INT8U IGStatus_v_g();//IG状态获取函数
FUN_EXT INT8U Driver_v_g();//预驱驱动函数
FUN_EXT INT8U FineTab(FP32 *a, INT8U TabLong, INT16U data);//温度查表定位函数
FUN_EXT FP32 Account_temp(INT16U data);//温度计算函数

#endif /* FUN_H_ */
