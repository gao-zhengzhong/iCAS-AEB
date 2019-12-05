/*
 * File: ModeControl.h
 *
 * Code generated for Simulink model 'ModeControl'.
 *
 * Model version                  : 1.25
 * Simulink Coder version         : 8.2 (R2012a) 29-Dec-2011
 * TLC version                    : 8.2 (Dec 29 2011)
 * C/C++ source code generated on : Tue Oct 23 15:44:42 2012
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->HC(S)12
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Safety precaution
 *    3. MISRA-C:2004 guidelines
 * Validation result: Not run
 */

#ifndef RTW_HEADER_ModeControl_h_
#define RTW_HEADER_ModeControl_h_
#ifndef ModeControl_COMMON_INCLUDES_
# define ModeControl_COMMON_INCLUDES_
#include <string.h>
#include "rtwtypes.h"
#endif                                 /* ModeControl_COMMON_INCLUDES_ */

#include "ModeControl_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((void*) 0)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((void) 0)
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((void*) 0)
#endif

/* Block signals and states (auto storage) for system '<Root>' */
typedef struct {
  uint16_T MaintenLowCnt;              /* '<Root>/MaintenJudge' (DWork 5)  */
  uint8_T is_active_c2_ModeControl;    /* '<Root>/mode control' (DWork 1)  */
  uint8_T is_c2_ModeControl;           /* '<Root>/mode control' (DWork 2)  */
  uint8_T is_active_c1_ModeControl;    /* '<Root>/MaintenJudge' (DWork 1)  */
  uint8_T is_c1_ModeControl;           /* '<Root>/MaintenJudge' (DWork 2)  */
  uint8_T is_High;                     /* '<Root>/MaintenJudge' (DWork 3)  */
  uint8_T is_Low;                      /* '<Root>/MaintenJudge' (DWork 4)  */
  uint8_T MaintenStage;                /* '<Root>/MaintenJudge' (DWork 6)  */
  uint8_T LevelHighCnt;                /* '<Root>/MaintenJudge' (DWork 7)  */
  uint8_T LevelLowCnt;                 /* '<Root>/MaintenJudge' (DWork 8)  */
} D_Work_ModeControl;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  uint8_T Tssadjstatus;                /* '<Root>/Tssadjstatus' */
} ExternalOutputs_ModeControl;

/* Block signals and states (auto storage) */
extern D_Work_ModeControl ModeControl_DWork;

/* External outputs (root outports fed by signals with auto storage) */
extern ExternalOutputs_ModeControl ModeControl_Y;

/* Model entry point functions */
extern void ModeControl_initialize(void);
extern void ModeControl_step(void);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'ModeControl'
 * '<S1>'   : 'ModeControl/MaintenJudge'
 * '<S2>'   : 'ModeControl/mode control'
 */

/*-
 * Requirements for '<Root>': ModeControl
 */
#endif                                 /* RTW_HEADER_ModeControl_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
