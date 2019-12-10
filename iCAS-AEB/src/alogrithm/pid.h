#ifndef _PID_H_
#define _PID_H_

#include "Para_Fun_Type.h"

#define PID_PARA_CYLINDER_LOCATION_KP         (40.0f)
#define PID_PARA_CYLINDER_LOCATION_KI         (0.35f)
#define PID_PARA_CYLINDER_LOCATION_KD         (0.0f)
#define PID_PARA_CYLINDER_LOCATION_INCREMENT  (1500u)

#define PID_PARA_CYLINDER_PRESSURE_KP         (90.0f)
#define PID_PARA_CYLINDER_PRESSURE_KI         (0.7f)
#define PID_PARA_CYLINDER_PRESSURE_KD         (1.0f)
#define PID_PARA_CYLINDER_PRESSURE_INCREMENT  (1500u)

typedef struct{
	FP32 Kp;
	FP32 Ki;
	FP32 Kd;
	FP32 integral;
	
	FP32 settingValue;
	FP32 actualValue;
	FP32 diviationValue;
	FP32 diviationValuePre;
}T_PID;

#endif