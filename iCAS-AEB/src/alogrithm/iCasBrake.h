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
#define TempPrott_H    75         //�¶ȱ���������ֵ
#define TempPrott_L    50         //�¶ȱ��������ֵ
#define TempPrott_Limt    50      //�¶ȱ���ʱ������ϵ��δ0.5*100
#define TempPrott_Normal    100   //δ�����¶ȱ���ʱ������ϵ��Ϊ1*100
#define TempPrott_Time    80  //80*2.5ms  //�¶ȱ�����������̳���ʱ��
#define TempPrott_Time2    20  //20*2.5ms  //�¶ȴﵽ�����¶Ⱥ󣬳�����ʱ��󣬴��������

#define Pedal_Init_loc_AD   125        //̤���г̴�������ʼֵ
#define Mastercyler_Init_loc_AD   205  //�����г̴�������ʼֵ

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
