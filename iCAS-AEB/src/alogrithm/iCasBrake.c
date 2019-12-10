/*
 * iCasBrake.c
 *
 *  Created on: 2019-5-8
 *      Author: admdtf
 */
#include"MAIN.h"



#define ABS(a) ((a)>0?(a):(-(a)))
#define SIGN(a) ((a)>0?1:((a)<0?-1:0))
#define MAX_RB_TORQ  28200
#define ZERO_RB_TORQ 30000
#define MAX_PEDALSPEED 85
#define BASETORQUE 50
#define MAXAPPROACH 6.0   // revised on 2019-11-20
#define RBQUITSPEED1 23000
#define RBQUITSPEED2 21500
#define RBENDOFQUITSPEED 21000
//#define DELTASPEED 900
#define UPPER_PDL_LOC 207 // 13mm, 1 AD值 = 50.27/800 = 0.0628375mm
#define UPPER_PDL_LOC1 239 // 15mm, 1 AD值 = 50.27/800 = 0.0628375mm


/*
 *********************************************************************************************************
 *                                               VARIABLES
 *********************************************************************************************************
 */
/*---------------助力控制系统参数----------------*/
FP32 MotorCurrent = 0;                    //助力电机电流
FP32 MotorCurrentLast = 0;
FP32 CylinderLocation,               //主缸推杆行程
     CylinLocVar = 2.0;              // 主缸空行程调整量, revised on 2019-11-20

FP32 PedalLocation;                  //踏板推杆行程
FP32 incrementValueLast = 0;
FP32 TargetCurrent = 0;              //电流环目标电流值
float fliter[8];
INT16S num=0;
INT16S BrakeState = 2;               //刹车状态
INT16U BrakeCount = 0;               //刹车计数，用于刹车从状态2，变为状态1的过渡计数
INT16U BS4Count = 255;
FP32 coef;
FP32 FrBrk_cylinder = 0;             //摩擦制动电流
FP32 Set_Prs=0.0;
FP32 Set_Cylinder = 0;
FP32 Target_Pressure;
FP32 Cylinder_Err ;
INT16S m_iPWMIntegral = 0;
INT16S MotorDuty;                    //电机占空比
INT16S motorDuty;
BOOLEAN StrMotor_DirL;               //电机正向置1
BOOLEAN StrMotor_DirR;               //电机反向置1
INT16U  ActuRBTorq[7];

BOOLEAN flag1_RBquit, flag2_RBquit;
INT8U   count_RBquit = 0;
INT16U	fric_torque_inc = 0;

FP32 VehicleSpeed = 0;
FP32 Acc = 0;

INT16S TotalTorqReq = ZERO_RB_TORQ;
INT16S RBStartQuitSpeed ;
INT16S FricTorq;

/*************************************************************/
/*            PWM积分项等参数初始化                          */
/*************************************************************/
INT16S m_iPWMP = 0;
INT16S m_iPWMI = 0;
INT16S m_iPWMD = 0;
INT16S m_iPWMPPOS = 0;
INT16S m_iPWMIPOS = 0;
INT16S m_iPWMDPOS = 0;

INT16S m_iPWMError = 0;
INT16S m_iPWMPError = 0;
INT16S m_iPWMIntePre = 0;
INT16S m_iLastPWM = 0;
INT16S m_iMaxPWM=1700;


FP32  targetCurrent_Test = 0;

struct _pid{
	FP32 SetValue;            //定义设定值
	FP32 ActualValue;         //定义实际值
	FP32 err;                 //定义偏差值
	FP32 err_pre;            //定义上一个偏差值
	FP32 err_pre_pre;         //定义上上一个偏差值
	FP32 Integral;
	FP32 Kp,Ki,Kd;            //定义比例、积分、微分系数
	FP32 Prs_Kp,Prs_Ki,Prs_Kd;
	FP32 Cylinder_Kp,Cylinder_Ki,Cylinder_Kd;
	INT16S travel[4], integ_trvl_rate;
	INT16S Pedal_rate, Pedal_rate_filtered;
	INT16S PedalLocPred;
	INT16U pdl_trvl;

}pid,posPID,pwm_pid;

 /**********************************************************************************************************
 *                                             C ENTRY POINT
 *********************************************************************************************************
 */
/*!************************************************************************************
 *	@fn	        void AD_to_real(void);
 *	@brief	    AD均值滤波函数
 *	@author     Matt Dou
 *	@param[in]	void
 *	@return	    void
 *	@note       在CCU60.c中CCU60_viNodeI3()函数中调用
 *	@Data       2019-3-12
 ****************************************************************************************/
void AD_Filtration(void)
{
	Motor_Cur_AD       = (Motor_Cur_ADLast*1 + Motor_Cur_AD*3)/4;
	BrakePressure_AD   = (BrakePressure_ADLast*1 + BrakePressure_AD*3)/4;
	Mastercyler_AD1    = (Mastercyler_AD1Last*1 + Mastercyler_AD1*3)/4;
	Mastercyler_AD2    = (Mastercyler_AD2Last*1 + Mastercyler_AD2*3)/4;
	Pedal_location_AD1 = (Pedal_location_AD1Last*1 + Pedal_location_AD1*3)/4;
	Pedal_location_AD2 = (Pedal_location_AD2Last*1 + Pedal_location_AD2*3)/4;

	Motor_Cur_ADLast       = Motor_Cur_AD;
	BrakePressure_ADLast   = BrakePressure_AD;
	Mastercyler_AD1Last    = Mastercyler_AD1;
	Mastercyler_AD2Last    = Mastercyler_AD2;
	Pedal_location_AD1Last = Pedal_location_AD1;
	Pedal_location_AD2Last = Pedal_location_AD2;
}
/*!************************************************************************************
 *	@fn	        void AD_to_real(void);
 *	@brief	    AD值转换函数
 *	@author     Matt Dou
 *	@param[in]	void
 *	@return	    void
 *	@note       在CCU60.c中CCU60_viNodeI3()函数中调用
 *	@Data       2019-3-12
 ****************************************************************************************/
void AD_to_real(void)
{
	INT16S  Im=0;
	FP32    Pedalx=0;
	FP32    Cylinder=0;

	if(Pedal_location_AD1<=Pedal_Init_loc_AD)
		Pedalx=Pedal_Init_loc_AD;
	if(Pedal_location_AD1>Pedal_Init_loc_AD)
		Pedalx=Pedal_location_AD1;


	if(Mastercyler_AD1<=Mastercyler_Init_loc_AD)
		Cylinder=Mastercyler_Init_loc_AD;
	if(Mastercyler_AD1>Mastercyler_Init_loc_AD)
		Cylinder=Mastercyler_AD1;

	CylinderLocation=(FP32)((Cylinder-Mastercyler_Init_loc_AD)/800*39.64);  //39.64，100~897，50~447

	pid.pdl_trvl = Pedalx - Pedal_Init_loc_AD;
	PedalLocation=((FP32)(pid.pdl_trvl)/((FP32)800) * ((FP32)50.27));       //50.27，100~897，50~447
    if(PedalLocation < 1.5)
	   iCAS_BrakeFlagBit = 0;
    else
       iCAS_BrakeFlagBit = 1;

	MasterCylinderPrs=(FP32)((FP32)BrakePressure_AD/51.2);          //主缸压力，单位MPa，0~15

	if(Motor_Cur_AD<=510)                           //读取电机电流,使电机电流从0逐渐增大
	{
		Curflag =0;
	}

	if(Motor_Cur_AD>510)                            //读取电机电流,电机电流从2048逐渐增加
	{
		Curflag =1;
	}

	Im=Motor_Cur_AD - 510;

	MotorCurrent=(FP32)((FP32)Im/2.73);              //助力电机电流,单位A0~30

	MotorCurrent = MotorCurrent/8 + MotorCurrentLast*7/8;
	if(ABS(MotorCurrent)<0.1)MotorCurrent = 0;

	MotorCurrentLast = MotorCurrent;

	VehicleSpeed = VCU_VehicleSpeed * 56.25/1000;

	Acc = ((FP32)(2059 - Receive_ACC)) * 0.0277;
}
/*!************************************************************************************
 *	@fn	        Cylinder_Set (void);
 *	@brief	            主缸位移给定函数
 *	@author     Matt Dou
 *	@param[in]	void
 *	@return	    void
 *	@note       在CCU60.c中CCU60_viNodeI3()函数中调用
 *	@Data       2019-3-12
 ****************************************************************************************/
FP32 Cylinder_Set (FP32 trval_Location)
{
	FP32 set_cylinder = 0;

/*-----------------更新时间11月21日----------------*/
	/*if( trval_Location < 1.0)
	    set_cylinder = 0;
	else if(trval_Location < 8.8)
		set_cylinder = trval_Location  * 0.641 + 1.359 + CylinLocVar;  // revised on 2019-11-20
	else if(trval_Location < 15)
		set_cylinder = trval_Location  * 0.81  - 0.1 + CylinLocVar;  // revised on 2019-11-20
	else if(trval_Location < 22)
		set_cylinder = trval_Location  * 0.86 - 0.86 + CylinLocVar;  // revised on 2019-11-20
	else
		set_cylinder = trval_Location - 5 + CylinLocVar; */ // revised on 2019-11-20`
/*---------------------更新时间11月22日-----------------*/
	/*if( trval_Location <= 1.0)
		set_cylinder = 0;
	else if(trval_Location <= 8.8)
		set_cylinder = trval_Location  * 0.641 + 1.359 + CylinLocVar;  // revised on 2019-11-20
	else if(trval_Location <= 15)
		set_cylinder = trval_Location  * 0.81  - 0.1 + CylinLocVar;  // revised on 2019-11-20
	else if(trval_Location <= 22)
		set_cylinder = trval_Location  * 0.61 + 2.9 + CylinLocVar;  // revised on 2019-11-20
	else
		set_cylinder = trval_Location - 5.68 + CylinLocVar;*/  // revised on 2019-11-20

	/*---------------------更新时间11月23日(最新踏板感曲线)-----------------*/
	/*--------------------大制动力段接近评价优，小行程段合格线以上-------------*/
	/*--------------------该制动踏板曲线为最终确定的演示踏板曲线-------------*/
	/*if( trval_Location <= 1.0)
		set_cylinder = 0;
	else if(trval_Location <= 11.5)
		set_cylinder = trval_Location * 1.1429 + 0.8571 + CylinLocVar;
	else if(trval_Location <= 22)
		set_cylinder = trval_Location * 0.2143 + 11.536 + CylinLocVar;
	else
		set_cylinder = trval_Location - 5.75 + + CylinLocVar;
	return set_cylinder;*/

	/*---------------------更新时间11月25日(最新踏板感曲线)-----------------*/
	/*-------------------设计间隙消除点时推杆行程位置为20.5mm----------------*/
	/*if( trval_Location <= 1.0)
		set_cylinder = 0;
	else if(trval_Location <= 9.2)
		set_cylinder = trval_Location * 0.8988 + 1.1012 + CylinLocVar;
	else if(trval_Location <= 20.5)
		set_cylinder = trval_Location * 0.277 + 6.8217 + CylinLocVar;
	else
		set_cylinder = trval_Location - 8 + + CylinLocVar;
	return set_cylinder;*/

	/*---------------------更新时间11月26日(最新踏板感曲线)-----------------*/
	/*------------------设计间隙消除点时推杆行程位置为19mm-----------------*/
	if( trval_Location <= 1.0)
			set_cylinder = 0;
		else if(trval_Location <= 7.455)
			set_cylinder = trval_Location * 0.8988 + 1.1012 + CylinLocVar;
		else if(trval_Location <= 19)
			set_cylinder = trval_Location * 0.277 + + 5.7365 + CylinLocVar;
		else
			set_cylinder = trval_Location - 8 + + CylinLocVar;
		return set_cylinder;
}
/*!************************************************************************************
 *	@fn	        void PID_init();
 *	@brief	            主缸位移给定函数
 *	@author     Matt Dou
 *	@param[in]	void
 *	@return	    void
 *	@note       在CCU60.c中CCU60_viNodeI3()函数中调用
 *	@Data       2019-3-12
 ****************************************************************************************/
void PID_init(){

	m_iPWMP = 0;
	m_iPWMI = 0;
	m_iPWMD = 0;
	m_iPWMError = 0;
	m_iPWMIntegral = 0;
	m_iPWMPError = 0;
	m_iPWMIntePre = 0;
	m_iLastPWM = 0;

	pid.SetValue=0;
	pid.ActualValue=0;
	pid.err=0.0;
	pid.err_pre=0.0;
	pid.err_pre_pre=0.0;
	pid.Integral=0.0;

}
/*!************************************************************************************
 *	@fn	        FP32 PID_realize_location(FP32 Value);
 *	@brief	            主缸位移PID控制函数
 *	@author     Matt Dou
 *	@param[in]	void
 *	@return	    void
 *	@note       在CCU60.c中CCU60_viNodeI3()函数中调用
 *	@Data       2019-3-12
 ****************************************************************************************/
FP32 PID_realize_location(FP32 Value)
{
	INT16S incrementValue;
	if(Value<1&&MasterCylinderPrs<0.1)return 0;

	pid.Prs_Kp = 20;
	pid.Prs_Ki   = 0.2;
	pid.Prs_Kd   = 1;

	pid.SetValue=Value;

	pid.err=pid.SetValue-pid.ActualValue;

	m_iPWMIntePre = pid.Integral;

	if(ABS(pid.err)>1)pid.Integral=pid.Integral*0.99 + pid.err;

	incrementValue=pid.Prs_Kp*pid.err+pid.Prs_Ki*pid.Integral;

	m_iPWMP = (INT16S)(pid.Prs_Kp*pid.err);
	m_iPWMI = (INT16S)(pid.Prs_Ki*pid.Integral);
	m_iPWMD = (INT16S)(pid.Prs_Kd*(pid.err-pid.err_pre));
	m_iPWMError = pid.err;
	m_iPWMIntegral = pid.Integral;
	m_iPWMPError = pid.err-pid.err_pre;

	if(ABS(incrementValue)>m_iMaxPWM) incrementValue = m_iMaxPWM*SIGN(incrementValue);
	pid.err_pre=pid.err;
	m_iLastPWM = incrementValue;
	return  incrementValue;
}

/*========== 根据推杆行程计算前馈目标电流(A)============*/
FP32 fun_currentFF( FP32 frBrk_cylinder)  // 推杆行程初始位置AD值
{   FP32      motor_current;

    if(frBrk_cylinder < 1)
    	motor_current = 0;
    else if( frBrk_cylinder < 3.5)
		motor_current = 2.98;
	else if(frBrk_cylinder <= 7)
		motor_current = frBrk_cylinder * 1.16 + 0.93;
	else if(frBrk_cylinder <= 14)
		motor_current = frBrk_cylinder * 2.29 - 6.97;
	else if(frBrk_cylinder < 18)
	    motor_current = frBrk_cylinder * 3.42 - 22.8;
	else
		motor_current = frBrk_cylinder * 3.65 - 26.0;

		if(frBrk_cylinder >= 13.5)
		{
			INT8U u;
			u = (INT8U)(motor_current - 23.945);
			//u = u - (u>>2);
			u =u - (u>>3);
			motor_current = motor_current - (FP32)(u);
		}

	return(motor_current);
}

/*========== 根据摩擦力矩计算前馈目标电流(A)============*/
FP32 fun_currentFF2( INT16S  fricTorq)
{
	FP32  motor_current;
	INT16U x;
	if(fricTorq <= 0)
		motor_current = 3;
	else if( fricTorq <= 50 ){
		x = (fricTorq + 77)/22;
		motor_current = (FP32)(x);
	}
	else if(fricTorq <= 3621) {
		x = ((fricTorq << 2) + 1663)/323;
		motor_current = (FP32)(x);
	}
	else
		motor_current = 50;

	return(motor_current);
}

INT16U fun_loc_pred(INT16S Pdl_rate)
{
	INT16U  x, rtn;

	if(Pdl_rate < pid.Pedal_rate_filtered) //pid.Pedal_rate_filtered,踏板速度滤波后值
	{
		x = pid.Pedal_rate_filtered - Pdl_rate + 8;
		x = (x>>4);
		pid.Pedal_rate_filtered = pid.Pedal_rate_filtered - x;
	}
	else
	{
		x = Pdl_rate - pid.Pedal_rate_filtered + 8;
		x = (x>>4);
		pid.Pedal_rate_filtered = pid.Pedal_rate_filtered + x;
	}

	if(pid.Pedal_rate_filtered < 0)
	{
		x = - pid.Pedal_rate_filtered;
		x = (x<<3); // 预测80个控制周期，即200ms，即200ms后的踏板位置

		if(pid.pdl_trvl < x)   //回程时，200ms后，踏板位置预测小于0，不符合实际，返回值为零
			rtn = 0;
		else
			rtn = pid.pdl_trvl - x; // 1 AD值 = 50.27/800 = 0.0628375mm
	}
	else
	{
		x = (x<<3); // 预测80个控制周期，即200ms

		rtn = pid.pdl_trvl + x; // 1 AD值 = 50.27/800 = 0.0628375mm
	}
	return (rtn);
}

/*!************************************************************************************
 *	@fn	        float PID_Cylinder(float Value);
 *	@brief	            主缸位移PID控制函数
 *	@author     Dou
 *	@param[in]	void
 *	@return	    void
 *	@note       在CCU60.c中CCU60_viNodeI3()函数中调用
 *	@Data       2019-3-12
 ****************************************************************************************/
float PID_Cylinder(FP32 Value)
{
	FP32 incrementValue;
	FP32 incrementCurrent;
	FP32 currentFF;
	FP32 exCurrent;
	FP32 pid_pos_p;
	FP32 pid_pos_i;
	FP32 pid_pos_d;
	INT16S i=0;
	FP32 temp = 0;
	INT16S Cylinder_rate = 0;
	INT16S Pedal_rate = 0;
	FP32 damping_current = 0;

          /*------根据踏板行程获得前馈电流值-------------*/
/*-----前馈目标电流加上位置环PID增量，获得电流环目标电流值---------*/
	if(BrakeState)
		currentFF = fun_currentFF(Value - CylinLocVar);//主缸位移-电流，电流前馈 // revised on 2019-11-20
	    //currentFF =fun_currentFF2( FricTorq );
	else
		currentFF = 0;

	SetCurrent_CAN = (INT16S)(currentFF*100);
	/*位置跟踪，电流补偿*/
	posPID.Cylinder_Kp = 2;
	posPID.Cylinder_Ki = 0;
	posPID.Cylinder_Kd = 0;

	if(Value<0.01) {
		posPID.err = 0;
		posPID.Integral = 0;
		posPID.err_pre = 0;
	}

	posPID.SetValue= Value;

	posPID.ActualValue= CylinderLocation;

	posPID.err = posPID.SetValue - posPID.ActualValue;

	posPID.Integral = posPID.Integral*0.9999 + posPID.err;

	pid_pos_p = posPID.Cylinder_Kp * posPID.err;


	pid_pos_i = posPID.Cylinder_Ki*posPID.Integral;
	pid_pos_d = posPID.Cylinder_Kd*(posPID.err-posPID.err_pre);


	if(ABS(pid_pos_p)>30)pid_pos_p = 30*SIGN(pid_pos_p);
	if(ABS(pid_pos_i)>30)pid_pos_i = 30*SIGN(pid_pos_i);
	if(ABS(pid_pos_d)>5)pid_pos_d = 5*SIGN(pid_pos_d);

	incrementCurrent = pid_pos_p + pid_pos_i +pid_pos_d;

	m_iPWMPPOS = (int)pid_pos_p;
	m_iPWMIPOS = (int)pid_pos_i;
	m_iPWMDPOS = (int)pid_pos_d;
	if(ABS(incrementCurrent)>40) incrementCurrent = 40*SIGN(incrementCurrent);//期望位移与实际位移->电流补偿
	posPID.err_pre = posPID.err;

	/*---------------顶杆速度补偿值---------------*/
	Cylinder_rate = 2 * Mastercyler_AD1 + pid.travel[3] - pid.travel[1] - 2 * pid.travel[0]; // Moving speed of Cylinder

	if((Cylinder_rate < 0)&&(Pedal_rate <0 )&&( Pedal_rate > Cylinder_rate))
	{
		damping_current = (Pedal_rate - Cylinder_rate)/8;
	}
	else
	{
		damping_current = 0;
	}
	pid.travel[0] = pid.travel[1];
	pid.travel[1] = pid.travel[2];
	pid.travel[2] = pid.travel[3];
	pid.travel[3] = Mastercyler_AD1;

    /*--------------踏板踩踏速度补偿值---------*/
	Pedal_rate = 2 * Pedal_location_AD1 + pwm_pid.travel[3] - pwm_pid.travel[1] - 2 * pwm_pid.travel[0];
	pid.PedalLocPred = fun_loc_pred(Pedal_rate);
	Pedal_rate = Pedal_rate * 5;
	pid.Pedal_rate = Pedal_rate;

	/*if(Pedal_rate > 50){
		 currentCP = Pedal_rate/10 - 5;
		  if( pid.err >0 )
		   	 currentCP = currentCP + pid.Cylinder_Kp * pid.err;
	  }
	  else{
		currentCP = 0;
	}*/

	pwm_pid.travel[0] = pwm_pid.travel[1];
	pwm_pid.travel[1] = pwm_pid.travel[2];
	pwm_pid.travel[2] = pwm_pid.travel[3];
	pwm_pid.travel[3] = Pedal_location_AD1;

	if(Pedal_rate < -250) temp = -250;
	else if(Pedal_rate > 250) temp = 250;
	else temp = Pedal_rate;

	pwm_pid.integ_trvl_rate = pwm_pid.integ_trvl_rate - pwm_pid.integ_trvl_rate / 64;
	pwm_pid.integ_trvl_rate = pwm_pid.integ_trvl_rate + temp;
	Current_AD_CAN = pwm_pid.integ_trvl_rate;

	if(currentFF > 4.5 && pwm_pid.integ_trvl_rate < 160) // 若前馈电流较大且制动踏板处于回程或极慢去程
	{
		temp = 160 - pwm_pid.integ_trvl_rate;
		temp = temp / 80;         // 目标电流的摩擦补偿量, A
		if(temp > 10) temp = 10;  // 目标电流最大摩擦补偿量10A

		currentFF = currentFF - temp;
		if(ABS(currentFF) < 2) currentFF = 2;  // 前馈目标电流最小5A
	}
	if(ABS(PedalLocation)<2)currentFF = 2.2;

	exCurrent = currentFF + incrementCurrent;

	if(exCurrent < 0) exCurrent = 0;

	targetCurrent_Test = exCurrent;

	return exCurrent;
}
/*!************************************************************************************
 *	@fn	        float PID_Current(FP32 exCurrent);
 *	@brief	         电流跟踪PID控制函数
 *	@author     Dou
 *	@param[in]	void
 *	@return	    void
 *	@note       在CCU60.c中CCU60_viNodeI3()函数中调用
 *	@Data       2019-3-12
 ****************************************************************************************/
float PID_Current(FP32 exCurrent)
{
	FP32 incrementValue;
	FP32 feedbackPWM;
	FP32 pid_cur_p;
	FP32 pid_cur_i;
	FP32 pid_cur_d;
	INT16S i=0;
	FP32 temp = 0;
	/*--------电流跟踪控制--------------*/
	/*-------exCurrent电流环输入值（获得PWM前馈量和电流PID增量）------*/

	if(ABS(exCurrent)>50)exCurrent = 50*SIGN(exCurrent);

	if(pwm_pid.integ_trvl_rate<-1000){
		pid.Cylinder_Kp = 0;
		pid.Cylinder_Ki = 0.1;
		pid.Cylinder_Kd = 0;
	}
                else{
		pid.Cylinder_Kp = 200;
		pid.Cylinder_Ki = 1;
		pid.Cylinder_Kd = 0;
	}
	/*-----------PWM前馈计算--------*/
	if(exCurrent<4.76) feedbackPWM = exCurrent*54;
	else if(exCurrent<42.85)
		feedbackPWM = exCurrent*26.332 +131.66;
	else
		feedbackPWM = 1260;
		feedbackPWM = feedbackPWM/2;

	if(exCurrent<0.01){
		exCurrent = 0;
		pid.err = 0;
		pid.Integral = 0;
		pid.err_pre = 0;
	}

	pid.SetValue= exCurrent;
	pid.ActualValue= MotorCurrent;
	pid.err=pid.SetValue-pid.ActualValue;
	pid.Integral = pid.Integral*0.998 + pid.err;

	pid_cur_p = pid.Cylinder_Kp*pid.err;
	pid_cur_i = pid.Cylinder_Ki*pid.Integral;
	pid_cur_d = pid.Cylinder_Kd*(pid.err-pid.err_pre);

	if(ABS(pid_cur_p)>1600)pid_cur_p = 1600*SIGN(pid_cur_p);
	if(ABS(pid_cur_i)>1200)pid_cur_i = 1500*SIGN(pid_cur_i);
	if(ABS(pid_cur_d)>300)pid_cur_d = 300*SIGN(pid_cur_d);

	incrementValue=pid_cur_p + pid_cur_i+ pid_cur_d + feedbackPWM;

	m_iPWMP = (int)pid_cur_p;
	m_iPWMI = (int)pid_cur_i;
	m_iPWMD = (int)pid_cur_d;

	if(ABS(incrementValue)>m_iMaxPWM) incrementValue = m_iMaxPWM*SIGN(incrementValue);
	pid.err_pre=pid.err;

	if(num<8){
		fliter[num] = incrementValue;
		num++;
	}else{
		num = 8;
		temp = 0;
		for(i=0;i<7;i++){
			fliter[i] = fliter[i+1];
			temp=temp+fliter[i];
		}
		incrementValue = (temp + incrementValue)/8;
		fliter[7] = incrementValue;
	}
	return  incrementValue;
}
/*!************************************************************************************
 *	@fn	        void StateTransfer(void);
 *	@brief	          制动状态判断
 *	@author     Matt Dou
 *	@param[in]	void
 *	@return	    void
 *	@note       在CCU60.c中CCU60_viNodeI3()函数中调用
 *	@Data       2019-3-12
 ****************************************************************************************/
void StateTransfer(void)
{
    INT8U cond = 0;
    INT16S pedallocpred ;
    FP32 x;

    pedallocpred = pid.PedalLocPred;

    x = pedallocpred *  0.0628375;

    Tx_ACC = (INT16S)(x * 100);

	if((MCU_MotActuSpd > RBENDOFQUITSPEED)
			&&(PedalLocation < 13)
			&&(VCU_AllowFeedbackFlag == 1)
			//&&(pid.Pedal_rate < MAX_PEDALSPEED)
			&&(pedallocpred <= UPPER_PDL_LOC)
			)
		cond=1;
    else
    	cond=0;
switch(BrakeState){
	 case 0:
		 Set_Cylinder = 0;
		if(PedalLocation > 1.0)
		{
			BrakeState = 1; // 摩擦制动状态
			BrakeCount = 0;
		}
		else
			BrakeCount = 0;

		break;
	 case 1:    //摩擦制动
			if(PedalLocation <= 1.0){
				BrakeState = 2;
				BrakeCount = 0;
			}
			else if(cond == 1 && BrakeCount > 80) {  // 转入混合制动状态
			    BrakeState = 3;   // transient state of quit of regenerative braking
				BrakeCount = 0;
			}
			BrakeCount++;
			break;
	 case 2:
		   if(PedalLocation > 1.0){
			  if(cond==1) // 进入混合制动状态
				BrakeState = 3; // transient state of quit of regenerative braking
			  else
				BrakeState = 1; // 摩擦制动状态
		   BrakeCount = 0;
		}
		else if(BrakeCount > 80){
			 BrakeState = 0;
			 BrakeCount = 0;
			 Set_Cylinder = 0;
			}
		else{
			 BrakeCount++;
			 TargetCurrent = TargetCurrent  * 0.975; // revised on 2019-11-20
			}
		break;

	 case 3:     // 混合制动
		  if(PedalLocation <= 1.0){
				BrakeState = 2;
				BrakeCount = 0;
			 }
		  else if ((pid.PedalLocPred >= UPPER_PDL_LOC1) || (PedalLocation > 13))
			  {
			  BrakeState = 1;
			  BrakeCount = 0;
			  }
		  else if(MCU_MotActuSpd < RBStartQuitSpeed){ // if vehicle speed less than 25 km/h
			BrakeState = 4; // transient state of quit of regenerative braking
			BS4Count = 0;
			}
	  break;
	 case 4:    //混合制动解除阶段
		if(PedalLocation <= 1.0){
			 BrakeState = 2;
			 BrakeCount = 0;
		 }
		else if ((pid.Pedal_rate > MAX_PEDALSPEED) || (PedalLocation > 17))
		  {
		  BrakeState = 1;
		  BrakeCount = 0;
		  }
		else if(MCU_MotActuSpd < RBENDOFQUITSPEED )
		{
			BrakeState = 1;
			BrakeCount = 0;
			coef = 0;
		}
		else if(BS4Count > 80
				&& MCU_MotActuSpd > RBStartQuitSpeed)  //RBSTARTQUITSPEED )
		{
			BrakeState = 3;
			BrakeCount = 0;
		}
		else
		{
			if(MCU_MotActuSpd <= RBENDOFQUITSPEED )
				coef = 0;
			//else if(MCU_MotActuSpd >= RBSTARTQUITSPEED )
			else if(MCU_MotActuSpd >= RBStartQuitSpeed )
				coef = 1;
			else
			{
				unsigned int u;
				u = MCU_MotActuSpd - RBENDOFQUITSPEED ;
				//coef = (FP32)(u) / (FP32)(DELTASPEED);
				coef = (FP32)(u) / (FP32)(RBStartQuitSpeed - RBENDOFQUITSPEED);
			}
		}
		 if(BS4Count < 200) BS4Count++;
		 break;
	  default:
			 BrakeState = 0;
			 BrakeCount  = BS4Count = 0;
		}
}

//================摩擦制动主缸目标行程输出===============//
FP32 fun_Fric_cylinder(INT16S x)
{
	FP32 y;

	if(x < 0)
		y = 3.5;
	else if(x < 280)
		y = 3.5 + (FP32)(x) * 0.0054;
	else if(x < 4723)
		y = 3.7474 + (FP32)(x) * 0.004474;
	else y = 25;

	return (y);
}



//=====================制动力矩衰减==============//
INT16S torque_reduction(INT16S toq, FP32 coef)
{
	FP32 x, c;
	INT16U y;
	INT16S torque;

	if(toq > ZERO_RB_TORQ)torque = ZERO_RB_TORQ;
	else if(toq < MAX_RB_TORQ)torque = MAX_RB_TORQ;
	else torque = toq;

	y = ZERO_RB_TORQ - toq;

	if(coef > 1)c = 1;
	else if(coef<0)c = 0;
	else c = coef;

	x = (FP32)(y) * c;
	y = (INT16U)(x) ;
	torque = ZERO_RB_TORQ - y;

	return (torque);
}


//===================制动力矩计算===================//
INT16S torque_calc(FP32 travel)
{
	FP32 u;
	INT16U torque;

	if(travel > 5)           //整车制动力矩请求
	{

		u = travel * 223.5;
		torque = 30838 - (INT16U)(u);
	}
	else
	{
		u = travel * 120;
		torque = 30320 - (INT16U)(u);
	}

	if(torque > ZERO_RB_TORQ) torque = ZERO_RB_TORQ;

	return (torque);
}



INT16U torq_extent_check(INT16U torq)
{
    INT16U rtn;

    if(torq < MAX_RB_TORQ) rtn = MAX_RB_TORQ;
    else if(torq > ZERO_RB_TORQ) rtn = ZERO_RB_TORQ;
    else rtn = torq;

    return (rtn);
}

INT16S fun_RBTorqRate(INT16U ActuTorq)
{
	INT16S rate, i;

	rate = 7 * (ActuTorq - ActuRBTorq[0])
			+ 5 * (ActuRBTorq[6] - ActuRBTorq[1])
			+ 3 * (ActuRBTorq[5] - ActuRBTorq[2])
			+ (ActuRBTorq[4] - ActuRBTorq[3]);
	for(i = 0; i < 6; i++)
		ActuRBTorq[i] = ActuRBTorq[i+1];

	ActuRBTorq[6] = ActuTorq;

	return (rate);
}

INT16U fun_RBStartQuitSpd(INT16U totalTorq ){
    INT16U torq , quitSpeed;

    torq = ZERO_RB_TORQ - totalTorq;

    quitSpeed = 5 * torq/8 + 21408;

    if(quitSpeed > RBQUITSPEED1) quitSpeed = RBQUITSPEED1;
    else if(quitSpeed < RBQUITSPEED2) quitSpeed = RBQUITSPEED2;

    return (quitSpeed);
}


/*!************************************************************************************
 *	@fn	        FP32 RB_request(FP32 target_cylinder);
 *	@brief	          制动力分配函数
 *	@author     Matt Dou
 *	@param[in]	void
 *	@return	    void
 *	@note       在CCU60.c中CCU60_viNodeI3()函数中调用
 *	@Data       2019-3-12
 ****************************************************************************************/

FP32 RB_request(FP32 target_cylinder)
{
	FP32 fricbrakeCylinder = 0;      //摩擦制动主缸位移
	INT16S TotalTorqReq = ZERO_RB_TORQ,       // 总的制动力矩请求
		   torque_VCU = ZERO_RB_TORQ;      // RB制动力矩请求
	INT16S mcu_motToqLmt = ZERO_RB_TORQ,    //最大制动扭矩限制
		    RB_torq_req = ZERO_RB_TORQ;          // requested RB torque

	INT16S mcu_motActuToq = ZERO_RB_TORQ;   //实际制动扭矩
	INT8U allowRBFlag = 0;           //能量回收标志位
	INT16S fricBrakeToq = ZERO_RB_TORQ;     //摩擦制动扭矩
	FP32 carMotorCylinder = 0;       //能量回收制动扭矩对应主缸位移
	INT16S delt_T = 0,               //力矩衰减系数
		RB_torque_rate;

	INT16U u = 0;

	//-------相关参数计算-------//
	target_cylinder = Set_Cylinder;
	Test_target_Cylinder = target_cylinder;

	mcu_motToqLmt = MCU_MotToqLmt;    //整车最大制动扭矩限制

    mcu_motToqLmt = torq_extent_check(mcu_motToqLmt);

	mcu_motActuToq = MCU_MotActuToq;  // 读取整车实际制动力矩
	mcu_motActuToq = torq_extent_check(mcu_motActuToq);

	//RB_torque_rate = fun_RBTorqRate(mcu_motActuToq);
	RB_torque_rate = fun_RBTorqRate(VCU_MotToqReq);

	allowRBFlag = VCU_AllowFeedbackFlag;     //允许制动能量回收标志位

	//-------逻辑判断与制动力分配-------//
	switch(BrakeState)
	{
	case 0:
		fricbrakeCylinder = 0;
		fricBrakeToq = 0;
		RB_torq_req = ZERO_RB_TORQ;
		TotalTorqReq = ZERO_RB_TORQ;
		count_RBquit = 0;
		fric_torque_inc = 0;
		break;

	case 1:
	case 2:
		   TotalTorqReq = torque_calc(target_cylinder -  CylinLocVar);  // 整车总制动力矩请求

		   RB_torq_req = ZERO_RB_TORQ - 100;  // 临时赋值10倍的再生制动力矩为100Nm
			if(mcu_motActuToq < RB_torq_req )  // 实际的再生制动力矩大于上述赋值
		{
		    fricBrakeToq = mcu_motActuToq - TotalTorqReq;

		    fricbrakeCylinder = fun_Fric_cylinder(fricBrakeToq) + CylinLocVar;
		}
			else  // 实际的再生制动力矩等于零 RB_torq_req
		{
		    fricBrakeToq = ZERO_RB_TORQ - TotalTorqReq ;
		    fricbrakeCylinder = target_cylinder ; 
		}

	        RB_torq_req = ZERO_RB_TORQ;

		break;

	case 3:
        TotalTorqReq = torque_calc(target_cylinder - CylinLocVar); // 整车总制动力矩请求
        RBStartQuitSpeed = fun_RBStartQuitSpd(TotalTorqReq);
		if( TotalTorqReq < mcu_motToqLmt)   // 请求的制动力矩大于允许值
			RB_torq_req = mcu_motToqLmt;
		else
			RB_torq_req = TotalTorqReq;

		RB_torq_req = torq_extent_check(RB_torq_req);

		fricBrakeToq = mcu_motActuToq - TotalTorqReq;

		fricbrakeCylinder = fun_Fric_cylinder(fricBrakeToq) + CylinLocVar;

		break;

	case 4:
        TotalTorqReq = torque_calc(target_cylinder - CylinLocVar); // 整车总制动力矩请求

		RB_torq_req = torque_reduction(TotalTorqReq, coef);

		if( RB_torq_req < mcu_motToqLmt)   // 请求的制动力矩大于允许值
			RB_torq_req = mcu_motToqLmt;

		RB_torq_req = torq_extent_check(RB_torq_req);

		//fricBrakeToq = RB_torq_req - TotalTorqReq;
		fricBrakeToq = mcu_motActuToq - TotalTorqReq;

		if (RB_torq_req > mcu_motActuToq){
			INT16S u,v;
			u = (RB_torq_req - mcu_motActuToq) ;

			u = (u >> 1);

			//v = ZERO_RB_TORQ - TotalTorqReq;
			/*if(v > 1200)
				u = 0;
			else if(v > 450)
				u = (1200 - v) * u / 750;*/
			fricBrakeToq = fricBrakeToq + u;
		}

		flag1_RBquit = flag2_RBquit;

		if(RB_torque_rate > 300)
			flag2_RBquit = 1;
		else
			flag2_RBquit = 0;

		if(flag1_RBquit == 0 && flag2_RBquit == 1 && count_RBquit ==0)
		{
			count_RBquit = 80;
			fric_torque_inc = ZERO_RB_TORQ - mcu_motActuToq;
			fric_torque_inc = (fric_torque_inc>>1);
			//fricBrakeToq = fricBrakeToq + fric_torque_inc;
		}
		else if(count_RBquit > 0)
		{
			if(count_RBquit < 20)
			fric_torque_inc = fric_torque_inc * count_RBquit/20;
			else if(count_RBquit > 60)
			fric_torque_inc = fric_torque_inc * (80 - count_RBquit)/20;

			fricBrakeToq = fricBrakeToq + fric_torque_inc;
			count_RBquit--;
		}

		fricbrakeCylinder = fun_Fric_cylinder(fricBrakeToq) + CylinLocVar;

		break;

	default:

		fricbrakeCylinder = 0;
		fricBrakeToq = 0;
		RB_torq_req = ZERO_RB_TORQ;
		TotalTorqReq = ZERO_RB_TORQ;
		break;

    }

	FricTorq = fricBrakeToq;

	if(BrakeState)
	{
		FP32 min_travel;

		min_travel = PedalLocation - MAXAPPROACH;

		if(fricbrakeCylinder < min_travel)
		{
			if(BrakeState == 3 || BrakeState == 4)
		    /*===========应减少RB力矩RB_torq_req===========*/
			{
				INT16S new_RB_torq, old_RB_torq;

				new_RB_torq = torque_calc(min_travel - CylinLocVar);
				old_RB_torq = torque_calc(fricbrakeCylinder - CylinLocVar);

				RB_torq_req = RB_torq_req - new_RB_torq + old_RB_torq;

				RB_torq_req = torq_extent_check(RB_torq_req);
			}

			fricbrakeCylinder = min_travel;
		}

	}

	//Test_u_CAN = fric_torque_inc;

	VCU_MotToqReq = RB_torq_req;

	Test_toqRequest = TotalTorqReq; // total braking torque

    Test_BrakeToqRequest = fricBrakeToq ;

    Test_fricbrakeCylinder = fricbrakeCylinder;

    return fricbrakeCylinder;
}

/*!************************************************************************************
 *	@fn	        INT16S PID_Pressure(FP32 Value);
 *	@brief	            主缸压力PID控制函数
 *	@author     Matt Dou
 *	@param[in]	void
 *	@return	    void
 *	@note       在CCU60.c中CCU60_viNodeI3()函数中调用
 *	@Data       2019-3-12
 ****************************************************************************************/
INT16S PID_Pressure(FP32 Value) {
	INT16S incrementValue;
	if(Value<1&&MasterCylinderPrs<0.1)
		return 0;

	pid.Prs_Kp = 75;
	pid.Prs_Ki = 0.05;
	pid.Prs_Kd = 0;

	pid.SetValue=Value;

	pid.err=pid.SetValue-MasterCylinderPrs*10;

	m_iPWMIntePre = pid.Integral;

	if(ABS(pid.err)>1)pid.Integral=pid.Integral*0.999 + pid.err;

	incrementValue=pid.Prs_Kp*pid.err+pid.Prs_Ki*pid.Integral;

	m_iPWMP = (INT16S)(pid.Prs_Kp*pid.err);
	m_iPWMI = (INT16S)(pid.Prs_Ki*pid.Integral);
	m_iPWMD = (INT16S)(pid.Prs_Kd*(pid.err-pid.err_pre));

	m_iPWMError = pid.err;
	m_iPWMIntegral = pid.Integral;
	m_iPWMPError = pid.err-pid.err_pre;

	if(ABS(incrementValue)>m_iMaxPWM) incrementValue = m_iMaxPWM*SIGN(incrementValue);
	pid.err_pre=pid.err;
	m_iLastPWM = incrementValue;
	return  incrementValue;
}
/*!************************************************************************************
 *	@fn	        void MC_Location_PID(void);
 *	@brief	            主缸行程给定、PID跟踪、输出处理，用于助力模式下的主缸位移跟踪
 *	@author     Matt Dou
 *	@param[in]	void
 *	@return	    void
 *	@note       在CCU60.c中CCU60_viNodeI3()函数中调用
 *	@Data       2019-3-12
 ****************************************************************************************/
void MC_Location_PID(void) {
	unsigned int u;

	/*-------------控制器温度保护逻辑，超过设定温度，进行降额保护处理---------------*/
	if((TempDiagflag==0)&&(RealTempreture >= TempPrott_H))
	{
		TempDiagNum++;
		if(TempDiagNum>TempPrott_Time)
		{
			TempDiagflag=1;
		}
	}
	else if((TempDiagflag==1)&&(RealTempreture <= TempPrott_L))
	{
		TempDiagNum++;
		if(TempDiagNum>TempPrott_Time)
		{
			TempDiagflag=0;
			TempPtottIndex =TempPrott_Normal;
		}
	}
	else if((TempDiagflag==1)&&(RealTempreture > TempPrott_L))
	{
		TempProttNum++;
		if(TempProttNum>=TempPrott_Time2)
		{
			if(TempPtottIndex>TempPrott_Limt)
			{
				TempPtottIndex--;
			}
			TempProttNum=0;
		}
	}
	else
	{
		TempDiagNum =0;
	}
	/*----------制动力给定与温度保护---------*/
	Set_Cylinder = Cylinder_Set(PedalLocation);
	Set_Cylinder = Set_Cylinder*TempPtottIndex/100;

	//-----------再生制动开始退出速度计算--------------//

	//-----------制动状态判断与制动力分配--------------//
	StateTransfer();                      //制动状态判断

	BrakeState_CAN = BrakeState;

	FrBrk_cylinder = RB_request(Set_Cylinder);

	if(BrakeState != 2) TargetCurrent = PID_Cylinder(FrBrk_cylinder);

	motorDuty = PID_Current(TargetCurrent);  //主缸位置跟踪

	//motorDuty = 0;

	MotorDuty = motorDuty + 2048;

	TargetCurrent_CAN = (INT16S)(TargetCurrent*100);
	FrcCylinder_CAN = (INT16S)(FrBrk_cylinder*100);
	/*--------------------------占空比输出处理--------------------*/
	if(ABS(motorDuty)<=10)
		MotorDuty = 2048;

	if(MotorDuty >= 3748)
	{
		MotorDuty =3748;
	}
	if(MotorDuty <= 348)
	{
		MotorDuty = 348;
	}
	MotorPwm_Ctrl = MotorDuty;
}
/*!************************************************************************************
 *	@fn	        void MC_Location_PID(void);
 *	@brief	            主缸行程给定、PID跟踪、输出处理
 *	@author     Matt Dou
 *	@param[in]	void
 *	@return	    void
 *	@note       在CCU60.c中CCU60_viNodeI3()函数中调用
 *	@Data       2019-3-12
 ****************************************************************************************/
void Real_To_Can(void) {
	//PedalLocation_CAN = (INT16S)(PedalLocation*100);
	PedalLocation_CAN = (INT16S)(PedalLocation*10);
	//Set_Cylinder_CAN = (INT16S)(Set_Cylinder*100);
	//CylinderLocation_CAN = (INT16S)(CylinderLocation*100);
	CylinderLocation_CAN = (INT16S)(CylinderLocation*10);
	//MasterCylinderPrs_CAN =(INT16S)(MasterCylinderPrs*100) ;
	MasterCylinderPrs_CAN =(INT16S)(MasterCylinderPrs*10) ;
	//MotorCurrent_CAN =(INT16S)(MotorCurrent*100) ;
	MotorCurrent_CAN =(INT16S)((MotorCurrent + 2000)*10);
	//Tempreture_CAN = (INT16S)(Tempreture_AD);
	//motorDuty_CAN = MotorDuty ;
	Tx_ACC = (INT16S)((Acc + 125) *10);
	//Tx_ACC = (INT16S)((Acc) *100);


	/*m_iPWMP_CAN = m_iPWMP;
	m_iPWMI_CAN = m_iPWMI;
	m_iPWMD_CAN = m_iPWMD;

	m_iPWMP_CAN_POS = m_iPWMPPOS;
	m_iPWMI_CAN_POS = m_iPWMIPOS;
	m_iPWMD_CAN_POS = m_iPWMDPOS;*/

}
/*!************************************************************************************
 *	@fn	        void Cylinder_Autoset(void);
 *	@brief	            主缸目标行程测试给定值
 *	@author     Matt Dou
 *	@param[in]	void
 *	@return	    void
 *	@note       在CCU60.c中CCU60_viNodeI3()函数中调用
 *	@Data       2019-3-12
 ****************************************************************************************/
void Cylinder_Autoset(void) {
	if((MCTimer>=0)&&(MCTimer<=1500))
		Set_Cylinder = 2;
	if((MCTimer>1500)&&(MCTimer<=3000))
		Set_Cylinder = 0;
}
/*!************************************************************************************
 *	@fn	        void  MC_Location_PID(void);
 *	@brief	            主缸目标压力跟踪
 *	@author     Matt Dou
 *	@param[in]	void
 *	@return	    void
 *	@note       在CCU60.c中CCU60_viNodeI3()函数中调用
 *	@Data       2019-3-12
 ****************************************************************************************/
void MC_Presure_PID(FP32 Value) {

	motorDuty=PID_Pressure(Value);             //主缸压力跟踪

	MotorDuty = motorDuty + 2048;
	/*--------------------------占空比输出处理--------------------*/
	if(ABS(motorDuty)<=10)
		MotorDuty = 2048;

	if(MotorDuty >= 3548)
		MotorDuty =3548;

	if(MotorDuty <= 548)
		MotorDuty = 548;
	MotorPwm_Ctrl = MotorDuty;

}


void APAFunction(void){

   FP32 Prs = 0;
   Prs = APA_TargetPrs/2;    //数值范围0~200.  精度0.5，其中100表示2Mpa
   Prs = Prs/5;        //获得10倍的目标制动压力

   if( APA_BrakeFlag == 1){

       if(APA_EmgBrakeFlag == 0x02)  //判别是否为紧急制动
    	   Prs = 20;

	   MC_Presure_PID(Prs);

       APA_FeedBackFlag = 1;
       APA_FeedBackValue = (INT8U)(MasterCylinderPrs * 100);

       if(APA_FeedBackValue >= 250)APA_FeedBackValue = 250;
       if(APA_FeedBackValue <  0  )APA_FeedBackValue = 0;
   }

   if( APA_BrakeFlag == 0){

	   APA_FeedBackFlag = 0;
	   APA_FeedBackValue = 0;
   }

}

