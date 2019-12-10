#ifndef _FLTM_H_
#define _FLTM_H_

#ifndef  _FLTM_C_
#define _EXTERN_ extern
#else
#define _EXTERN_
#endif

#include "FLT_Types.h"

typedef struct
{
	FLT_U8 dtc;
	FLT_U8 dtcNum;
	FLT_U16 vehicleSpeed;
	
	union
	{
		FLT_U8 dtcStatus;
		struct
		{
			/* DTC Status Bit Mask */
			FLT_U8 TEST_FAILED_BIT_MASK                              :1;
			FLT_U8 TEST_FAILED_THIS_OPERATION_CYCLE_BIT_MASK         :1;
			FLT_U8 PENDING_DTC_BIT_MASK                              :1;
			FLT_U8 CONFIRMED_DTC_BIT_MASK                            :1;
			FLT_U8 TEST_NOT_COMPLETED_SINCE_LAST_CLEAR_BIT_MASK      :1;
			FLT_U8 TEST_FAILED_SINCE_LAST_CLEAR_BIT_MASK             :1;
			FLT_U8 TEST_NOT_COMPLETED_THIS_OPERATION_CYCLE_BIT_MASK  :1;
			FLT_U8 WARNING_INDICATOR_REQUESTED_BIT_MASK              :1;
		};
	};
	
}FLTM_DtcType;


_EXTERN_ void FLTM_Init(void);
_EXTERN_ void FLTM_CyclicProcess(void);

#endif