#define AEB_GLOBALS

#define SPEED_IS_Standby                   80                   //速度阈值
#define Sig_delay_t                        0.1
#define Prs_delay_t                        0.3
#define Ep_acce_ego                        6.0
#define Ep_acce_frt                        6.0
#define SonRes_time                        0.8
#define HapRes_time                        0.6
#define dis_S0                             3.0
#define dis_time                           31


#include "main.h"

/*************special argument define**************/
FP32 EP[2] = {0.0,0.0};

/* all the argument initialization*/
void AebInit(void){
	testCount  = 0;
	TTC        = 20;
	isSteering = 0;
	phase      = 0;
	dis_brake  = 100.0;
	State_max  = 0;
	p_aeb_s    = AEB_S_array;
	speed_time = 0;
	test05     = 0;
	Status     = 0;
	prec       = 0.0;
	temp01     = 0;

	IsCondSatis      = 0;
	distance_long    = 12000;
	isSpeedSatf      = 0;           //0:速度未激活  1：速度激活
	AEB_State_now    = 0;
	CountNumberRadar = 0;
	SpeedStandbyCount= 0;

	pv   = v_d;
	p_t  = &TTC;
	pa   = acce_d;
	pp   = pres_d;
	pl   = lca_d;
	p_ep = EP;

	TargetPressure = 0;
	AutoMode = 0;
	//AutoBrakeEnable = 0;
	//AebBrakeEnable = 0;
	BrakeSysMode = BoosterBrakeMode;
	AebStandtime = 0 ;
	AebStandMode = 0;
	SteerInterSta =0;

	/*Meye*/
	eyeObstacleNum = 0;
	laneLeftX = 0.0;
	laneRightX = 0.0;
	canCount769 = 0;
	canCount768 = 0;
	canCount767 = 0;
	canCount766 = 0;
}


/****************Aeb Function**********/
void AebAlgorithm(void){

   /*  FindDangerObject_lp();           //危险目标检测
     getInfo();
     calc_ttc(v_rel/3.6, dis_rel);    //计算TTC

     if(VechileSpeed<150)             //车速大于15KM/H，AEB起作用
     {
    	 if(AEB_State_now!=3)        //车速小于15km/h时，未进入紧急制动则退出
    	 {
        	 TTC = 20;
    	 }
    	 else
    	 {
    		 if(VechileSpeed<10)  //紧急制动后车辆静止判断
    		 {
    			 AebStandMode =1;
    		 }
    	 }
     }

     if(!SteerInterSta)   //转向未干预时触发AEB逻辑判断，通过TTC进行阶段区分
     {
    	 if(TTC<1.7)//紧急制动阶段
    	 {
    		 AEB_State_now = 3;
    		 Aeb_targetpress_value=45;
    	 }
    	 else if((TTC<3.5)&&(AEB_State_now!=3))//间歇制动阶段
    	 {
    		 AEB_State_now = 2;
    		 Aeb_targetpress_value=0;      //此阶段压力未控制
    	 }
    	 else if((TTC<5)&&(AEB_State_now!=3))//预制动阶段
    	 {
    	     AEB_State_now = 1;
    	     Aeb_targetpress_value=0;
    	 }
    	 else if(AEB_State_now==3)
    	 {
    	     AEB_State_now = 3;
    	     if(AebStandMode==1)     //进入紧急制动后停车，降压驻车
    	     {
    	         Aeb_targetpress_value=10;
    	     }
    	     else
    	     {
    	         Aeb_targetpress_value=45;
    	     }
    	 }
    	 else                         //无碰撞危险阶段
    	 {
    	     AEB_State_now = 0;
    	     Aeb_targetpress_value=0;
    	 }
     }
     else                   //转向干预
     {
    	 AEB_State_now = 0;
    	 Aeb_targetpress_value=0;
     }



     if(BrakeSysMode!=APABrakeMode)//刹车模式不处于主动制动模式时，可进入AEB模式
     {
         if(AEB_State_now==3)     //紧急制动阶段，使能AEB线控刹车
         {
            BrakeSysMode=AebBrakeMode;
         }
         else                       //非紧急制动阶段，回到助力模式
         {
            BrakeSysMode=BoosterBrakeMode;
            Aeb_targetpress_value =0;
         }
     }*/



/*-----------------凌鹏AEB算法已屏蔽-------------*/
     //p_p = pa_sort();
    /* isSpeedSatf = IsSpeedStandby();
     isSteering = IsSWStandBy();

     resumeFunc();

     IsCondSatis = CondFunc();

     IsCondSatis = 1;
     dis_rel = 10.0;
     v_ego = 42;
     v_rel = -1*v_ego;

     if (IsCondSatis){
    	 //AEB_State_now = calc_state(v_ego/3.6, v_rel/3.6, dis_rel);//此函数影响程序运行，运行时影响障碍物距离检测及部分AD采样

    	 if（TTC<EmrgBrake_TtcL）
    	 {
    		 AEB_State_now = 3;
    		 Aeb_targetpress_value=40;
    	 }
    	 else if(TTC<InterBrake_TtcL)
    	 {
    		 AEB_State_now = 2;
    		 Aeb_targetpress_value=0;
    	 }
    	 else if(TTC<PreBrake_TtcL)
    	 {
    		 AEB_State_now = 1;
    		 Aeb_targetpress_value=0;
    	 }
    	 else
    	 {
    		 AEB_State_now = 0;
    		 Aeb_targetpress_value=0;
    	 }




         prec          = accury_calc();
         prec = 0.0;
         AedBrake();
     } else {
    	 AEB_State_now = 0;
    	 Aeb_targetpress_value=0;
    	 //AedBrake();
     }
     //if(Pedal_location_AD1 <= (Pedal_Init_loc_AD + 20))
     //MC_Presure_PID(30);
     //AedBrake();*/
}

/* find the nearest objection */
void FindDangerObject_lp(void)
{
    INT8U i;
    distance_long = 12000;
    for ( i = 0; i < 20; i++){

    	  if ( distance_long > ObjectInfo1[0][i]){   //!CountNumberRadar &&
    		 //testCount++;
             distance_long    =        ObjectInfo1[0][i];             //unit:m   * 100
             distance_lateral = (      ObjectInfo1[1][i]);            //unit:m   * 100
             speed_longtitude = ((FP32)ObjectInfo1[2][i]*18/5);       //unit:km/h* 10
             speed_lateral    = ((FP32)ObjectInfo1[3][i]*18/5);       //unit:km/h* 10
             break;
          }
          if ( distance_long > ObjectInfo0[0][i]){  //CountNumberRadar &&
             distance_long    =        ObjectInfo0[0][i];             // same as previous
             distance_lateral = (      ObjectInfo0[1][i]);
             speed_longtitude = ((FP32)ObjectInfo0[2][i]*18/5);
             speed_lateral    = ((FP32)ObjectInfo0[3][i]*18/5);
          }
    }

}

/********** assist function 01: sort function *********/
void sort(FP32 * data, INT16U n) {
	INT16U step,i,j;
	FP32   key;

    //将数组按照STEP分组，不断二分到每组只剩下一个元素
    for(step=n/2;step>0;step/=2) {
        //将每组中的元素排序，小的在前
        for(i=step;i<n;i++) {
            key = data[i];
            for(j=i-step;j>=0 && key<data[j];j-=step) {
                data[j+step] = data[j];
            }
            //和上面的for循环一起，将组中小的元素换到数组的前面
            data[j+step] = key;
        }
    }
}

/********** assist function 02: mean function *********/
//求一个数组从n项到m项的平均值(包含n项，m项）
FP32 mean_array(FP32 * p, INT16U n, INT16U m) {
	FP32   total = 0.0;
	INT16S i = n;
	INT16S j = 0, total_num = 0;
    while (i < m+1) {
        total += *(p + i);
        i += 1;
    }
    /*while (j < m){
        if (*(p + j))
            total_num += 1;
        j += 1;
    }*/
    return total / (m+1-n);
}
/********** assist function 02: round function *********/
INT16S round(FP32 t){
	FP32 md;
    md = t - (INT16S) t;
    if (md>= 0.5)
        return (INT16S)(t+1);
    else
        return (INT16S)t;
}

/********** assist function 03: max function *********/
FP32 MAX(FP32 a, FP32 b){
    return (a>b) ? a : b;
}

INT16S MAX_int(INT16S a, INT16S b){
    return (a>b) ? a : b;
}


FP32 ABS_lp(FP32 a){
    return (a<0) ? a*(-1) : 2;
}

void v_delay(FP32 v) {
    INT16S i;
    for (i = (calc_t - 1); i > -1; i--) {
        if (i)
            *(pv + i) = *(pv + i - 1);
        else
            *pv = v;
    }
}

void pres_delay(FP32 pres) {
    INT16S i;
    for (i = (calc_t - 1); i > -1; i--) {
        if (i)
            *(pp + i) = *(pp + i - 1);
        else
            *pp = pres;
    }
}

void speed_time_delay(void) {
    INT16S i;
    for (i = (calc_t - 1); i > -1; i--) {
        if (i)
            speed_time_d[i] = speed_time_d[i-1];
        else
            speed_time_d[0] = speed_time;
    }
}

void acce_delay(FP32 acce_present){
    INT16S i;
    for (i = (calc_t - 1); i > -1; i--) {
        if (i)
            *(pa + i) = *(pa + i - 1);
        else
            *pa = acce_present;
    }
}

void l_delay(FP32 dis) {
    INT16S i;
    for (i = (calc_t - 1); i > -1; i--) {
        if (i)
            *(pl + i) = *(pl + i - 1);
        else
            *pl = dis;
    }
}

FP32 **pa_sort(void){
    INT16S i;
    FP32   * pa;
    FP32   * pointer_pressure;                      //pointer to pressure,pointer to acceleration.
    for (i=0 ; i < calc_t; i++){
        pres_s[i] = pres_d[i];
        acce_s[i] = acce_d[i];
    }

    sort(pres_s, calc_t);
    sort(acce_s, calc_t);

    p_array[0] = pointer_pressure = pres_s;
    p_array[1] = pa = acce_s;
    return p_array;
}


INT8U IsSpeedStandby(void)
{
   if(VechileSpeed>SPEED_IS_Standby)
       SpeedStandbyCount++;
   else {
       SpeedStandbyCount = 0;
       return 0;
    }
   if(SpeedStandbyCount > 30){
       SpeedStandbyCount = 30;
       return 1;
   }
   return 0;
}

//this function is not finished yet.
INT8U IsSWStandBy(void){
	if(RealAngle>100 || RealAngle<-340  ){    //RealAngle 度*10
		return 1;
	}
	return 0;
}

//calculate the ttc
void calc_ttc(FP32 v_rel,FP32 dis_rel){
	FP32 i = 20;
    if (v_rel >= 0)
        *p_t = 20;
    else
        i = (-1) * dis_rel / v_rel;                                               //
    *p_t = i > 20 ? 20.0 : i;
}

/* get & process all the information */
void getInfo(void){
	v_ego        = ((FP32)VechileSpeed)/10;          // unit: km/h
	v_rel        = ((FP32)speed_longtitude)/10;      // unit: km/h
	acce_present = (acce_ego.acceleration_y+0.0)*0.0277;    // unit: m/s^2
	dis_rel      = ((FP32)distance_long)/100;        // unit: m

	v_delay(v_ego/3.6);
	pres_delay(MasterCylinderPrs*10);
	speed_time_delay();                  //period: 2.5ms
	acce_delay(acce_present);
	l_delay(dis_rel);

	if (distance_long > 11800)
		speed_front = 200;               // 200 means no dangerous object is in front.
	else
		speed_front = v_ego + v_rel;
}

/* cal dis 01*/
INT16U calc_state(FP32 v, FP32 v_rel, FP32 dis_rel){
	FP32   FrSt_t, v_f;
    FP32   t[dis_time], Sf[dis_time], Sr[dis_time], dis[dis_time], dis_haptic, dis_sound;
    INT16U i, AEB_state;

    //begin_time = speed_time;
    v_f = v_rel + v;

    for (i = 0; i < dis_time; ++i){
		t[i] = 0.2 * i;
		Sr[i] = Sf[i] = 0.0;
    }

    FrSt_t = v_f/Ep_acce_frt;
    for (i = 0; i < dis_time; ++i){
        if (t[i] <= FrSt_t)
            Sf[i] = v_f * t[i] - 0.5 * Ep_acce_frt * t[i]* t[i];
        else
            Sf[i] = Sf[i-1];
    }

    for (i = 0; i < dis_time; ++i){
        if (t[i] <= Sig_delay_t)
            Sr[i] = v * t[i];
        else if (t[i] <= (Sig_delay_t + Prs_delay_t))
            Sr[i] = v * Sig_delay_t + v * (t[i] - Sig_delay_t) - Ep_acce_ego * (t[i] - Sig_delay_t)*(t[i] - Sig_delay_t)*(t[i] - Sig_delay_t)/(6.0 * Prs_delay_t);
        else if (t[i] <= (Sig_delay_t + Prs_delay_t + (v - 0.5*Ep_acce_ego*Prs_delay_t)/Ep_acce_ego)){
            Sr[i] = v * (Sig_delay_t + Prs_delay_t) - Ep_acce_ego * Prs_delay_t*Prs_delay_t/6.0 + \
                 (v - 0.5 * Ep_acce_ego * Prs_delay_t) *  (t[i] - Sig_delay_t - Prs_delay_t)\
            - 0.5 * Ep_acce_ego * (t[i] - Sig_delay_t - Prs_delay_t)*(t[i] - Sig_delay_t - Prs_delay_t);}
        else
            Sr[i] = Sr[i-1];
    }


    for (i = 0; i < dis_time; ++i){
        dis[i] = Sf[i] - Sr[i];
    }

    sort(dis, dis_time);

    if (dis[0] < 0) {
      dis_brake = dis[0]*(-1) + dis_S0;
      dis_haptic = dis_brake + HapRes_time * ABS_lp(v_rel) ;
      dis_sound = dis_haptic + SonRes_time * ABS_lp(v_rel) ;

      if (dis_rel < dis_brake)
          AEB_state = 3;
      else if (dis_rel < dis_haptic)
          AEB_state = 2;
      else if (dis_rel < dis_sound)
          AEB_state = 1;
      else
          AEB_state = 0 ;
    }else{
        AEB_state = 0;
    }

    return AEB_state;
}

INT16U calc_state2(FP32 v, FP32 v_rel, FP32 dis_rel){
	FP32   FrSt_t, v_f;
    FP32   t[dis_time], Sf[dis_time], Sr[dis_time], dis[dis_time], dis_haptic, dis_sound;
    INT16U i, AEB_state;

    //begin_time = speed_time;
    v_f = v_rel + v;

    for (i = 0; i < dis_time; ++i){
		t[i] = 0.2 * i;
		Sr[i] = Sf[i] = 0.0;
    }

    FrSt_t = v_f/Ep_acce_frt;
    for (i = 0; i < dis_time; ++i){
        if (t[i] <= FrSt_t)
            Sf[i] = v_f * t[i] - 0.5 * Ep_acce_frt * t[i]* t[i];
        else
            Sf[i] = Sf[i-1];
    }

    for (i = 0; i < dis_time; ++i){
        if (t[i] <= Sig_delay_t)
            Sr[i] = v * t[i];
        else if (t[i] <= (Sig_delay_t + Prs_delay_t))
            Sr[i] = v * Sig_delay_t + v * (t[i] - Sig_delay_t) - Ep_acce_ego * (t[i] - Sig_delay_t)*(t[i] - Sig_delay_t)*(t[i] - Sig_delay_t)/(6.0 * Prs_delay_t);
        else if (t[i] <= (Sig_delay_t + Prs_delay_t + (v - 0.5*Ep_acce_ego*Prs_delay_t)/Ep_acce_ego)){
            Sr[i] = v * (Sig_delay_t + Prs_delay_t) - Ep_acce_ego * Prs_delay_t*Prs_delay_t/6.0 + \
                 (v - 0.5 * Ep_acce_ego * Prs_delay_t) *  (t[i] - Sig_delay_t - Prs_delay_t)\
            - 0.5 * Ep_acce_ego * (t[i] - Sig_delay_t - Prs_delay_t)*(t[i] - Sig_delay_t - Prs_delay_t);}
        else
            Sr[i] = Sr[i-1];
    }


    for (i = 0; i < dis_time; ++i){
        dis[i] = Sf[i] - Sr[i];
    }

    sort(dis, dis_time);

    if (dis[0] < 0) {
      dis_brake = dis[0]*(-1) + dis_S0;
      dis_haptic = dis_brake + HapRes_time * ABS_lp(v_rel) ;
      dis_sound = dis_haptic + SonRes_time * ABS_lp(v_rel) ;

      if (dis_rel < dis_brake)
          AEB_state = 3;
      else if (dis_rel < dis_haptic)
          AEB_state = 2;
      else if (dis_rel < dis_sound)
          AEB_state = 1;
      else
          AEB_state = 0 ;
    }else{
        AEB_state = 0;
    }

    return AEB_state;
}

void resumeFunc(void){
    if(VechileSpeed < 10){
		 test05++;
		 if (test05 > 400){
			test05 = 0;
			phase  = 1;
			Status = 0;
			Aeb_targetpress_value =0;
			//MC_Presure_PID(Aeb_targetpress_value);
		 }
    }
}

INT8U CondFunc(void){
	// 使能开关和踏板位置没有写
	if( (!isSteering) && isSpeedSatf && distance_long>3) {
        return 1;
	}else{
		Status       = 0;
		phase        = 2;
		State_max    = 0;
		*(p_aeb_s+1) = 0;
		*p_aeb_s     = 0;
		*(p_ep+1)    = 0;
		return 0;
	}
}

void AedBrake(void){
    //if(VechileGear==1){           //档位代码
        *(p_aeb_s + 1) = MAX_int(*p_aeb_s, *(p_aeb_s+1));
        *p_aeb_s       = AEB_State_now;
        State_max      = MAX_int(*p_aeb_s, *(p_aeb_s+1));

        switch (State_max){
            case 1:
                phase  = 3;
                Status = 1;
                Aeb_targetpress_value =0;
                //MC_Presure_PID(Aeb_targetpress_value);
                //BrakeSysMode=BoosterBrakeMode;
                break;

            case 2:
                phase  = 4;
                Status = 2;

               /*if(Interval_ctrl_flag==0) {
                   Interval_ctrl_time =0;
                   Interval_ctrl_flag=1;
                   Aeb_targetpress_value =0;
               }else if(Interval_ctrl_flag==1) {
                    if(Interval_ctrl_time>INTERVAL_BRAKE_TIME) {
                        Interval_ctrl_time =0;
                        Interval_ctrl_flag=2;
                        Aeb_targetpress_value = 10;
                    }
               }else {
                   Interval_ctrl_time =0;
                   Interval_ctrl_flag=1;
                   Aeb_targetpress_value = 10;
               }
               MC_Presure_PID(Aeb_targetpress_value);*/
                //BrakeSysMode=BoosterBrakeMode;
               break;

            case 3:
              phase  = 5;
              Status = 3;

              add_pressure          = (INT16S)pres_p();
              add_pressure = 0;
              Aeb_targetpress_value = 50 + add_pressure;
              //BrakeSysMode=AebBrakeMode;
              //Aeb_targetpress_value   = 100;
              //MC_Presure_PID(Aeb_targetpress_value);
              break;

            default:
               phase = 6;
               Aeb_targetpress_value =0;
               //MC_Presure_PID(Aeb_targetpress_value);
               //BrakeSysMode=BoosterBrakeMode;
               break;
          }

       // State_max =3;
       // Aeb_targetpress_value =10;
        //AEB_State_now
       /* if(BrakeSysMode!=AutoBrakeMode)
        {
        	if(AEB_State_now==3)
        	{
        		BrakeSysMode=AebBrakeMode;
        	}
        	else
        	{
        		BrakeSysMode=BoosterBrakeMode;
        		Aeb_targetpress_value =0;
        	}
        }*/
    //}
}

FP32 accury_calc(void){
	FP32 dis_r, dis_m, precs;
	FP32 tt;
    /*tt = speed_time_d[0] - speed_time_d[calc_t - 15];
    if (tt > 0)
        tt = tt*0.5/1000;
    else
        tt = (65536 + tt)*0.5/1000;*/
	tt = 0.1;

    dis_r    = mean_array(pl, calc_t-15, calc_t-10) - mean_array(pl, 0, 5);
    dis_real = dis_r > 0 ? dis_r : (-1*dis_r);
    dis_m    = v_ego*tt/3.6 - 0.5 * acce_present * tt * tt;

    if (speed_front<1)
    	precs = dis_m - dis_real;
    else
    	precs = 0;

    return precs;
}

FP32 calc_ep(void){
	/*FP32 * ps, s_m, a_e, acce_ms, v_ms,v_f;
    FP32 t_build = 0.3, v_ego_ms;

    ps   = *p_p;
    v_ms = v_ego/3.6;
    v_f  = v_rel + v_ego;
    s_m  = dis_rel + prec - dis_S0;                           //修正后的理论距离 = 实际距离 + 模型准确度

    v_ego_ms = v_ego/3.6;
    acce_ms  = acce_present*-1;

    if (v_f < 1 && (mean_array(ps, 0, 19) > mean_array(pp, 0, 9) * 0.9) &&\
        (mean_array(ps, calc_t-21, calc_t-1) < mean_array(pp, 0, 9)*1.1) &&\
        mean_array(pp, 0, 9) > 2  && v_ms > 1.0 && mean_array(ps, 0, 9)>2 &&\
        v_ego_ms/acce_ms > 0.5 && prec>0.5){

        phase = 7;
        /*a_e = -2*(6*s_m - 3*t_build*v_ego_ms + acce_ms*pow(t_build,2.0) - \
         pow((36*pow(s_m,2.0)+6*s_m*acce_ms*pow(t_build,2.0)-36*s_m*t_build*v_ego_ms\
         +pow(acce_ms,2.0)*pow(t_build,4.0)-6*acce_ms*v_ego_ms*pow(t_build,3.0) +\
         12*pow(t_build,2)*pow(v_ego_ms,2.0)),0.5))/pow(t_build,2.0);
        **

        a_e = 4;
        if (round(a_e) >= 1  && round(a_e) < 4.0)
            Ep_add = (round(a_e))*17.0;
        else if (round(a_e)<1 && round(a_e)>=0)
            Ep_add = 0.0;
        else if (round(a_e)>= 4.0)
            Ep_add = 70;
        else
            Ep_add = 0.0;

    } else */
    	if (TTC < 0.6 && TTC>0) {
        phase  = 8;
        Ep_add = 50.0;

    } else {
        phase  = 9;
        Ep_add = 0.0;
    }

    return Ep_add;
}

FP32 pres_p(void){
	FP32 exp_add;

    exp_add    = calc_ep();
    *(p_ep+1) = MAX(*p_ep, *(p_ep+1));
    *p_ep     = exp_add;

    return MAX(*p_ep, *(p_ep+1));
}


//2019年6月20日下午3点22分：大陆雷达断开后，最小距离一直是零，故在CondFunc()函数中添加了&& distance_long>3，来解决这一情况。
