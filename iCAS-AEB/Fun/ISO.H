/*
 * iso.h
 *
 *  Created on: 2019-3-5
 *      Author: Administrator
 */

#ifndef ISO_H_
#define ISO_H_

#ifdef   ISO_GLOBALS
	#define  ISO_EXT
#else
	#define  ISO_EXT  extern
#endif


#define   TASK1_CNT      6  //时间300us,6个Ticks
#define   TASK2_CNT      32 //时间1300us,26个Ticks
#define   TASK3_CNT      40 //时间400us ,8个Ticks
#define   TASK4_CNT      50 //时间500us ,10个Ticks

#define   IG_RAMP_DOWN   40 //RAMP DOWN 持续时间

typedef enum {
		EcmStart, // Start new cycle.
		EcmWait1, // Wait for the first response.
		EcmWait2,  // Wait for the second response.
		EcmWait3,
		EcmWait4,
		EcmWait5,
		EcmWait6,
		EcmWait7,
		EcmWait8,
		EcmWait9,
		EcmEnd
} EcmControlStates; //上电检测或者下电检测的Step


/*!
*	@union	UN_PHASE
*	阶段完成标志位联合体
*/
typedef union {
	struct {
		INT8U Phase0       :1;                                       /* 阶段 0 完成 */
		INT8U Phase1       :1;                                       /* 阶段 1 完成 */
		INT8U Phase2       :1;                                       /* 阶段 2 完成 */
		INT8U Phase3       :1;                                       /* 阶段 3 完成 */
		INT8U Phase4       :1;                                       /* 阶段 4 完成 */
		INT8U Phase5       :1;                                       /* 阶段 5 完成 */
		INT8U Phase6       :1;                                       /* 阶段6 完成 */
		INT8U Phase7       :1;                                       /* 阶段7 完成 */
		INT8U Phase8       :1;                                       /* 阶段 8 完成 */
		INT8U Phase9       :1;                                       /* 阶段 9 完成 */
		INT8U Phase10       :1;                                      /* 阶段 10 完成 */
		INT8U Phase11       :1;                                      /* 阶段 11 完成 */
		INT8U Phase12       :1;                                      /* 阶段 12 完成 */
		INT8U Phase13       :1;                                      /* 阶段 13 完成 */
		INT8U Phase14       :1;                                      /* 阶段 14 完成 */
		INT8U Phase15       :1;                                      /* 阶段 15 完成 */
		} BIT;
} UN_PHASE;

#define  PowerUpTestMode 1     //上电测试模式
#define  NormalMode  2         //正常模式
#define  PowerDownTestMode  8  //下电测试模式
#define  PowerDownMode  9      //下电模式
#define  FaultMode  110        //故障模式

ISO_EXT UN_PHASE  PowerUpTestPhase;
ISO_EXT UN_PHASE  PowerDownTestPhase;
ISO_EXT EcmControlStates PowerUpTestState;
ISO_EXT EcmControlStates PowerDownTestState;

ISO_EXT INT8U  SystemMode_u8_Sig;      /*系统模式  */
ISO_EXT INT8U  PDTFinish_u8_Sig;       /*下电测试模式结束标志位  */
ISO_EXT INT8U  PUTFinish_u8_Sig;       /*上电测试模式结束标志位  */
ISO_EXT INT8U  PDFinish_u8_Sig;        /*下电模式结束标志位  */
ISO_EXT INT8U  NormalFinish_u8_Sig;    /*正常模式结束标志位 */
ISO_EXT INT8U  PDTtoPUTflag_u8_Sig;    /*下电测试模式到上电测试模式标志位 */
ISO_EXT INT8U  MaintenStatus_u8_Sig;   /* */
ISO_EXT INT8U  IGNStatus_u8_Sig;       /*IG状态变量 */
ISO_EXT INT8U  MaintenLevel_u8_Sig;    /* */
ISO_EXT INT8U  FaultLevel_u8_Sig;      /* 故障等级*/
ISO_EXT INT8U  VehicleStatus_u8_Sig;   /* */
ISO_EXT INT8U  VehSpeedFault_u8_Sig;   /* */
ISO_EXT INT8S  TimeBaseCounter;        /* 时序计数变量*/
ISO_EXT INT16U DriverRampDownCnt_u16_Sig;


ISO_EXT void ISOInit_v_g(void);//初始化函数
ISO_EXT void WaitDriverRampDown_v_g (void);
ISO_EXT void TimingSchedule_v_g(void);//时序调度函数
ISO_EXT void TimingStart_v_g(void);//时序定时器启动函数


#endif /* ISO_H_ */
