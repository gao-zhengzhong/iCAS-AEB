/*
 * aeb.h
 *
 *  Created on: 2019-5-30
 *      Author: lp
 */

#ifndef AEB_H_
#define AEB_H_

#define calc_t   55

#ifdef   AEB_GLOBALS
	#define  AEB_EXT
#else
	#define  AEB_EXT  extern
#endif




/****************lp argument begin***********/
// sensor data 01
AEB_EXT INT8U  ObjNum,  ASR_DataIndex, CountNumberRadar;
AEB_EXT INT16S RealAngle,distance_long, distance_lateral;
AEB_EXT INT16U VechileSpeed, testCount;
AEB_EXT INT16U TargetPressure,AutoMode,AutoBrakeEnable;
AEB_EXT FP32   speed_longtitude, speed_lateral;

//aeb data 02
AEB_EXT INT8U  isSpeedSatf, isSteering, phase, State_max, AEB_State_now, \
               SpeedStandbyCount, Status, IsCondSatis, Aeb_targetpress_value;
AEB_EXT INT16U add_pressure, speed_time, temp01 , test05;
AEB_EXT FP32   v_ego, v_rel, speed_front, pres_max, pres_min, prec, TTC, dis_rel,\
               dis_real, dis_brake, acce_present, Ep_add, prec;

// data array
AEB_EXT FP32   v_d[calc_t], pres_d[calc_t], acce_d[calc_t],lca_d[calc_t],\
               pres_s[calc_t],acce_s[calc_t], EP[2];
AEB_EXT INT16U speed_time_d[calc_t];
AEB_EXT INT8U  AEB_S_array[2];

// array pointer
AEB_EXT FP32 * pv, * pp , * pa, * p_t, ** p_p, *pl,* p_array[2], * p_ep;
AEB_EXT INT8U * p_aeb_s;

// radar data structure 01
typedef struct ars_o_status{
	INT8U Object_NofObjects;
	INT16U Object_MeasCounter;
	INT8U Object_InterfaceVersion;
} ars_o_status_01;
AEB_EXT ars_o_status_01 ars_ob_status;

// radar data structure 02
typedef struct arsObject{
	INT8U id;
	INT16S Obj_DistLong;
	INT16S Obj_DistLat;
	INT16S Obj_VrelLong;
	INT16S Obj_VrelLat;
	INT8U Obj_DynProp;
}arsObject1;
AEB_EXT arsObject1 ars_Object;

// acceleration and yaw data structure
typedef struct acceleration{
	FP32 acceleration_x;
	INT16S acceleration_y;
	FP32 acceleration_z;
	FP32 yaw_rate;
	INT16U acce_y;
}acceleration01;

/*Mobileye*/
typedef struct Lane
{
	INT16S id;
	FP32 c0, c1, c2, c3;
	INT16S laneType;
	INT16S laneQuality;
	INT16S modelDegree;
    FP32 leftMarkingWidth;
    FP32 viewRange;
    INT16S viewRangeFlag;
}laneLR[2];

typedef struct EyeObs
{
	FP32 obsPosX, obsPosY;
	FP32 obsRelativeVelX, obsRelativeVelY;
	FP32 obsWidth, obsLength;
	INT16S obsType, obsStatus;
}eyeObs[64];

AEB_EXT INT16S eyeObstacleNum;
AEB_EXT FP32 laneLeftX;
AEB_EXT FP32 laneRightX;
AEB_EXT INT8U canCount769, canCount768, canCount767, canCount766;

AEB_EXT acceleration01 acce_ego;

AEB_EXT FP32 MasterCylinderPrs;

// deposit radar information array
AEB_EXT INT16S ObjectInfo0[4][20], ObjectInfo1[4][20];

// Aeb的刹车使能状态位
AEB_EXT INT8U  BrakeSysMode;
AEB_EXT INT16U  AebStandtime;
AEB_EXT INT8U  AebStandMode;//
AEB_EXT INT8U  SteerInterSta;//转向干预状态

#define EmrgBrake_TtcL    5.0
#define InterBrake_TtcL    10.0
#define PreBrake_TtcL    15.0

/********************function Declaration**************/
void   AebAlgorithm(void);
void   FindDangerObject_lp(void);
void   AebInit(void);
void   sort(FP32 * data, INT16U n);
FP32   mean_array(FP32 * p, INT16U n, INT16U m);
INT16S round(FP32 t);
FP32   MAX(FP32 a, FP32 b);
INT16S MAX_int(INT16S a, INT16S b);
INT16U calc_state(FP32 v, FP32 v_rel, FP32 dis_rel);
FP32   ABS_lp(FP32 a);
void   getInfo(void);
void   calc_ttc(FP32 v_rel,FP32 dis_rel);
FP32 **pa_sort(void);
INT8U  IsSpeedStandby(void);
INT8U  IsSWStandBy(void);
void   resumeFunc(void);
INT8U  CondFunc(void);
FP32   accury_calc(void);
FP32   pres_p(void);
FP32   calc_ep(void);
void   AedBrake(void);


#endif