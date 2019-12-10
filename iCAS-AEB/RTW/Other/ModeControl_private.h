/*
 * File: ModeControl_private.h
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

#ifndef RTW_HEADER_ModeControl_private_h_
#define RTW_HEADER_ModeControl_private_h_
#include "rtwtypes.h"
#ifndef __RTWTYPES_H__
#error This file requires rtwtypes.h to be included
#else
#ifdef TMWTYPES_PREVIOUSLY_INCLUDED
#error This file requires rtwtypes.h to be included before tmwtypes.h
#else

/* Check for inclusion of an incorrect version of rtwtypes.h */
#ifndef RTWTYPES_ID_C08S16I16L32N16F0
#error This code was generated with a different "rtwtypes.h" than the file included
#endif                                 /* RTWTYPES_ID_C08S16I16L32N16F0 */
#endif                                 /* TMWTYPES_PREVIOUSLY_INCLUDED */
#endif                                 /* __RTWTYPES_H__ */

/* Imported (extern) block signals */
extern uint8_T SystemMode_u8_Sig;      /* '<Root>/mode control' (Output 1)  */
extern uint8_T PDTFinish_u8_Sig;       /* '<Root>/mode control' (Output 2)  */
extern uint8_T PUTFinish_u8_Sig;       /* '<Root>/mode control' (Output 3)  */
extern uint8_T PDFinish_u8_Sig;        /* '<Root>/mode control' (Output 4)  */
extern uint8_T NormalFinish_u8_Sig;    /* '<Root>/mode control' (Output 5)  */
extern uint8_T PDTtoPUTflag_u8_Sig;    /* '<Root>/mode control' (Output 6)  */
extern uint8_T MaintenStatus_u8_Sig;   /* '<Root>/MaintenJudge' (Output 1)  */
extern uint8_T IGNStatus_u8_Sig;       /* '<Root>/ign' */
extern uint8_T MaintenLevel_u8_Sig;    /* '<Root>/mainten' */
extern uint8_T FaultLevel_u8_Sig;      /* '<Root>/fault level' */
extern uint8_T VehicleStatus_u8_Sig;   /* '<Root>/vehicle status' */
extern uint8_T VehSpeedFault_u8_Sig;   /* '<Root>/vehicle speed fault' */

#endif                                 /* RTW_HEADER_ModeControl_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
