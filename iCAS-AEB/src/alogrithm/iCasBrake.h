/*
 * iCasBrake.h
 *
 *  Created on: 2019-5-11
 *      Author: admdtf
 */

#ifndef ICASBRAKE_H_
#define ICASBRAKE_H_

/*********************************************************************************************************
*                                          FUNCTION PROTOTYPES
*********************************************************************************************************
*/
//extern INT16S MCTimer;
#define TempPrott_H    75         //温度保护触发限值
#define TempPrott_L    50         //温度保护解除限值
#define TempPrott_Limt    50      //温度保护时，控制系数未0.5*100
#define TempPrott_Normal    100   //未启用温度保护时，控制系数为1*100
#define TempPrott_Time    80  //80*2.5ms  //温度保护降额触发过程持续时间
#define TempPrott_Time2    20  //20*2.5ms  //温度达到保护温度后，持续该时间后，触发降额功能

#define Pedal_Init_loc_AD   125        //踏板行程传感器初始值
#define Mastercyler_Init_loc_AD   205  //主缸行程传感器初始值

#define BoosterBrakeMode  0
#define APABrakeMode      1
#define AebBrakeMode      2

void AD_Filtration(void);
void AD_to_real(void);
FP32 Cylinder_Set (FP32 trval_Location);
void PID_init();
float PID_realize_location(float Value);
float PID_Cylinder(float Value);
void MC_Location_PID(void);
void MC_Presure_PID(FP32 Value);
int PID_Pressure(float Value);
void Real_To_Can(void);
void Cylinder_Autoset(void);
void APAFunction(void);

#endif /* ICASBRAKE_H_ */
