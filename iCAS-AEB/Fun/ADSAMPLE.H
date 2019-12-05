/*
 * signal_sample.h
 *
 *  Created on: 2015-5-20
 *      Author: zhangguangyao
 */

#ifndef AD_SAMPLE_H_
#define AD_SAMPLE_H_

#ifdef   AD_SAMPLE_GLOBALS
	#define  AD_SAMPLE_EXT
#else
	#define  AD_SAMPLE_EXT  extern
#endif

#define BATT_SAMPLE_ADC0 3 //电源电压AD通道
#define BPHASE_BATT_SAMPLE_ADC0 4 //B相电压AD通道
#define APHASE_BATT_SAMPLE_ADC0 5 //A相电压AD通道
#define DRIVER_TEMP_SAMPLE_ADC0 9 //温度AD通道
#define MASTERPWR_SAMPLE_ADC0 10 //主缸电压AD通道
#define PEDALPWR_SAMPLE_ADC0 11 //踏板电压AD通道
#define PRSPWR_SAMPLE_ADC0 13  //压力电压AD通道
#define VLINK_SAMPLE_ADC0 8   //母线电压AD通道
#define CUR_SAMPLE_ADC0 15   //电流AD通道


#define BRAKE_PRESSURE_ADC1 4   //压力传感器AD通道
#define Rev1_ADC1 5   //预留AD输入1
#define Rev2_ADC1 6   //预留AD输入2

#define MAINRELAY_ENABLE_ON   SETIO_P10_4  //主继电器打开
#define MAINRELAY_ENABLE_OFF  CLEARIO_P10_4//主继电器关闭

#define PREDRIVER_ENABLE_ON   SETIO_P0_7   //预驱打开
#define PREDRIVER_ENABLE_OFF  CLEARIO_P0_7 //预驱关闭

#define POWER_ENABLE_ON       SETIO_P1_7   //主电源打开
#define POWER_ENABLE_OFF      CLEARIO_P1_7 //主电源关闭

#define PREPWR_ENABLE_ON      SETIO_P7_0   //压力电源打开
#define PREPWR_ENABLE_OFF     CLEARIO_P7_0 //压力电源关闭

#define MASTERPWR_ENABLE_ON   SETIO_P7_1  //主缸电源打开
#define MASTERPWR_ENABLE_OFF  CLEARIO_P7_1//主缸电源关闭

#define PEDALPWR_ENABLE_ON    SETIO_P7_4  //踏板电源打开
#define PEDALPWR_ENABLE_OFF   CLEARIO_P7_4//踏板电源关闭


#define CAN1_ENABLE_ON  SETIO_P1_5    //CAN0 Transfer使能
#define CAN1_ENABLE_OFF  CLEARIO_P1_5 //CAN0 Transfer关闭

#define CAN2_ENABLE_ON   SETIO_P1_4    //CAN1 Transfer使能
#define CAN2_ENABLE_OFF   CLEARIO_P1_4 //CAN1 Transfer关闭


#define CTRL_LAMP_ON   SETIO_P6_2    //制动灯打开
#define CTRL_LAMP_OFF  CLEARIO_P6_2  //制动灯关闭

#define BRAKE_SIGNEL   INIO_P4_0//制动踏板开关信号
#define PRE_ERR_SIGNEL   INIO_P6_0//预驱故障状态信号
#define IG_STATUS   INIO_P7_3//IG状态信号

#define WATCHDOG_ERR_SIGNEL   INIO_P4_3//狗状态信号
#define FEED_WATCHDOG   TOGGLEIO_P10_1 //喂狗信号输出




AD_SAMPLE_EXT INT16U  MotorPwm_Ctrl;//输出占空比信号
AD_SAMPLE_EXT INT16U  Motor_Cur; //电流信号变量
AD_SAMPLE_EXT INT8U   PrsPwrfail;//压力传感器电源检测状态
AD_SAMPLE_EXT INT16U  PrsPwr_AD; //压力传感器电源变量
AD_SAMPLE_EXT INT16U  BrakePressure_AD;//压力传感器AD变量
AD_SAMPLE_EXT INT8U   MasterPwrfail;   //踏板传感器电源检测状态
AD_SAMPLE_EXT INT16U  MasterPwr_AD;    //踏板传感器电源变量

AD_SAMPLE_EXT INT16U  Mastercyler_AD1;//主缸行程AD1值
AD_SAMPLE_EXT INT16U  Mastercyler_AD2;//主缸行程AD2值

AD_SAMPLE_EXT INT8U   PedalPwrfail;//踏板传感器电源检测状态
AD_SAMPLE_EXT INT16U  PedalPwr_AD;//踏板传感器电源变量

AD_SAMPLE_EXT INT16U  Pedal_location_AD1;//踏板行程AD1变量
AD_SAMPLE_EXT INT16U  Pedal_location_AD2;//踏板行程AD2变量
AD_SAMPLE_EXT INT8U   BrakeLight;     //制动灯控制变量
AD_SAMPLE_EXT INT8U   BrakeSW;        //制动踏板开关信号变量
AD_SAMPLE_EXT INT8U   Resrd12VPwrFail;//12V电源状态
AD_SAMPLE_EXT INT8U   Resrd5VPwrFail; //5V电源状态


AD_SAMPLE_EXT INT16U  Resrd12VPwr_AD;//12V电源AD值
AD_SAMPLE_EXT INT16U  Resrd5VPwr_AD; //5V源AD值

AD_SAMPLE_EXT INT16U  ResrdAD;
AD_SAMPLE_EXT INT8U   Can0Rec0data[64][8];//CAN0接收数据存放数组
AD_SAMPLE_EXT INT8U   Can0Rec1data[64][8];//CAN0接收数据存放数组
AD_SAMPLE_EXT INT8U   Can0Revdata[4][8];  //CAN0发送数据存放数组

AD_SAMPLE_EXT INT8U   Can1Recdata[10][8]; //CAN1接收数据存放数组
AD_SAMPLE_EXT INT8U   Can1Revdata[4][8];  //CAN1发送数据存放数组



AD_SAMPLE_EXT INT16U  VlinkPwr_AD;  //母线电压AD值
AD_SAMPLE_EXT INT16U  AphasePwr_AD; //A相电电压AD值
AD_SAMPLE_EXT INT16U  BphasePwr_AD; //B相电电压AD值
AD_SAMPLE_EXT INT16U  Tempreture_AD;//温度AD值

AD_SAMPLE_EXT INT16U  IgStatus;       //Ig采样值
AD_SAMPLE_EXT INT16U  PreDriverStatus;//预驱动故障状态值

AD_SAMPLE_EXT INT16U  SingleADSample_v_g(INT8U AdcCore,INT8U Channel);//AD单采样。AdcCore：0代表ADC0,1代表ADC1；Channel：代表通道
#endif /* SIGNAL_SAMPLE_H_ */
