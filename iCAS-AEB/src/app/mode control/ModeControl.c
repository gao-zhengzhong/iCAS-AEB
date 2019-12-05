/*
 * File: ModeControl.c
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

#include "ModeControl.h"
#include "ModeControl_private.h"

/* Named constants for Chart: '<Root>/MaintenJudge' */
#define ModeControl_IN_High            ((uint8_T)1U)
#define ModeControl_IN_Idle            ((uint8_T)1U)
#define ModeControl_IN_Low             ((uint8_T)2U)
#define ModeControl_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define ModeControl_IN_Stage1          ((uint8_T)2U)
#define ModeControl_IN_Stage2          ((uint8_T)2U)

/* Named constants for Chart: '<Root>/mode control' */
#define ModeControl_IN_FailureMode     ((uint8_T)1U)
#define ModeControl_IN_MaintenanceMode ((uint8_T)2U)
#define ModeControl_IN_Normal          ((uint8_T)3U)
#define ModeControl_IN_PowerDown       ((uint8_T)4U)
#define ModeControl_IN_PowerDownTest   ((uint8_T)5U)
#define ModeControl_IN_PowerUpTest     ((uint8_T)6U)
#define ModeControl_IN_dummy           ((uint8_T)7U)

/* Block signals and states (auto storage) */
D_Work_ModeControl ModeControl_DWork;

/* External outputs (root outports fed by signals with auto storage) */
ExternalOutputs_ModeControl ModeControl_Y;

/* Forward declaration for local functions */
static uint8_T ModeControl_MaintenHigh(void);
static uint8_T ModeControl_MaintenLow(void);
static uint8_T ModeControl_One2Two(void);
static uint8_T ModeControl_Zero2One(void);
static uint8_T ModeControl_ignON(void);
static uint8_T ModeControl_ignOFF(void);
static uint8_T ModeControl_FAILtoMTAIN(void);
static uint8_T ModeControl_NMtoPDT(void);
static uint8_T ModeControl_NMtoFAIL(void);
static uint8_T ModeControl_NMtoMTAIN(void);
static uint8_T ModeControl_PDtoOFF(void);
static uint8_T ModeControl_PDTtoPD(void);
static uint8_T ModeControl_PDTtoPUT(void);
static uint8_T ModeControl_PDTtoFAIL(void);
static uint8_T ModeControl_PUTtoNM(void);
static uint8_T ModeControl_PUTtoFAIL(void);
static uint8_T ModeControl_PUTtoPD(void);

/* Function for Chart: '<Root>/MaintenJudge' */
static uint8_T ModeControl_MaintenHigh(void)
{
  /* Graphical Function 'MaintenHigh': '<S1>:19' */
  /* Transition: '<S1>:22' */
  return (uint8_T)(MaintenLevel_u8_Sig != 0);
}

/* Function for Chart: '<Root>/MaintenJudge' */
static uint8_T ModeControl_MaintenLow(void)
{
  /* Graphical Function 'MaintenLow': '<S1>:8' */
  /* Transition: '<S1>:11' */
  return (uint8_T)(MaintenLevel_u8_Sig == 0);
}

/* Function for Chart: '<Root>/MaintenJudge' */
static uint8_T ModeControl_One2Two(void)
{
  /* Graphical Function 'One2Two': '<S1>:27' */
  /* Transition: '<S1>:30' */
  return (uint8_T)(((ModeControl_DWork.MaintenStage == 1) &&
                    (ModeControl_DWork.MaintenLowCnt < 4000U)) &&
                   (ModeControl_DWork.MaintenLowCnt > 2000U));
}

/* Function for Chart: '<Root>/MaintenJudge' */
static uint8_T ModeControl_Zero2One(void)
{
  /* Graphical Function 'Zero2One': '<S1>:62' */
  /* Transition: '<S1>:64' */
  return (uint8_T)(ModeControl_DWork.MaintenStage == 0);
}

/* Function for Chart: '<Root>/mode control' */
static uint8_T ModeControl_ignON(void)
{
  /* Graphical Function 'ignON': '<S2>:12' */
  /* Transition: '<S2>:15' */
  return (uint8_T)(IGNStatus_u8_Sig == 1);
}

/* Function for Chart: '<Root>/mode control' */
static uint8_T ModeControl_ignOFF(void)
{
  /* Graphical Function 'ignOFF': '<S2>:39' */
  /* Transition: '<S2>:42' */
  return (uint8_T)(IGNStatus_u8_Sig == 0);
}

/* Function for Chart: '<Root>/mode control' */
static uint8_T ModeControl_FAILtoMTAIN(void)
{
  /* Graphical Function 'FAILtoMTAIN': '<S2>:148' */
  /* Transition: '<S2>:151' */
  return (uint8_T)(((IGNStatus_u8_Sig == 1) && (MaintenStatus_u8_Sig == 1)) &&
                   ((VehicleStatus_u8_Sig == 0) || (VehSpeedFault_u8_Sig == 1)));
}

/* Function for Chart: '<Root>/mode control' */
static uint8_T ModeControl_NMtoPDT(void)
{
  /* Graphical Function 'NMtoPDT': '<S2>:164' */
  /* Transition: '<S2>:167' */
  return (uint8_T)(((IGNStatus_u8_Sig == 0) && (NormalFinish_u8_Sig == 1)) &&
                   ((FaultLevel_u8_Sig == 0) || (FaultLevel_u8_Sig == 1)));
}

/* Function for Chart: '<Root>/mode control' */
static uint8_T ModeControl_NMtoFAIL(void)
{
  /* Graphical Function 'NMtoFAIL': '<S2>:110' */
  /* Transition: '<S2>:113' */
  return (uint8_T)((FaultLevel_u8_Sig == 2) || (FaultLevel_u8_Sig == 3));
}

/* Function for Chart: '<Root>/mode control' */
static uint8_T ModeControl_NMtoMTAIN(void)
{
  /* Graphical Function 'NMtoMTAIN': '<S2>:116' */
  /* Transition: '<S2>:119' */
  return (uint8_T)((MaintenStatus_u8_Sig == 1) && ((VehicleStatus_u8_Sig == 0) ||
                    (VehSpeedFault_u8_Sig == 1)));
}

/* Function for Chart: '<Root>/mode control' */
static uint8_T ModeControl_PDtoOFF(void)
{
  /* Graphical Function 'PDtoOFF': '<S2>:142' */
  /* Transition: '<S2>:145' */
  return (uint8_T)(PDFinish_u8_Sig == 1);
}

/* Function for Chart: '<Root>/mode control' */
static uint8_T ModeControl_PDTtoPD(void)
{
  /* Graphical Function 'PDTtoPD': '<S2>:120' */
  /* Transition: '<S2>:123' */
  return (uint8_T)(((IGNStatus_u8_Sig == 0) && (PDTFinish_u8_Sig == 1)) &&
                   ((FaultLevel_u8_Sig == 0) || (FaultLevel_u8_Sig == 1)));
}

/* Function for Chart: '<Root>/mode control' */
static uint8_T ModeControl_PDTtoPUT(void)
{
  /* Graphical Function 'PDTtoPUT': '<S2>:124' */
  /* Transition: '<S2>:127' */
  return (uint8_T)(((IGNStatus_u8_Sig == 1) && (PDTFinish_u8_Sig == 1)) &&
                   ((FaultLevel_u8_Sig == 0) || (FaultLevel_u8_Sig == 1)));
}

/* Function for Chart: '<Root>/mode control' */
static uint8_T ModeControl_PDTtoFAIL(void)
{
  /* Graphical Function 'PDTtoFAIL': '<S2>:128' */
  /* Transition: '<S2>:131' */
  return (uint8_T)((FaultLevel_u8_Sig == 2) || (FaultLevel_u8_Sig == 3));
}

/* Function for Chart: '<Root>/mode control' */
static uint8_T ModeControl_PUTtoNM(void)
{
  /* Graphical Function 'PUTtoNM': '<S2>:99' */
  /* Transition: '<S2>:102' */
  return (uint8_T)(((IGNStatus_u8_Sig == 1) && (PUTFinish_u8_Sig == 1)) &&
                   ((FaultLevel_u8_Sig == 0) || (FaultLevel_u8_Sig == 1)));
}

/* Function for Chart: '<Root>/mode control' */
static uint8_T ModeControl_PUTtoFAIL(void)
{
  /* Graphical Function 'PUTtoFAIL': '<S2>:103' */
  /* Transition: '<S2>:106' */
  return (uint8_T)((FaultLevel_u8_Sig == 2) || (FaultLevel_u8_Sig == 3));
}

/* Function for Chart: '<Root>/mode control' */
static uint8_T ModeControl_PUTtoPD(void)
{
  /* Graphical Function 'PUTtoPD': '<S2>:160' */
  /* Transition: '<S2>:163' */
  return (uint8_T)((IGNStatus_u8_Sig == 0) && ((FaultLevel_u8_Sig == 0) ||
    (FaultLevel_u8_Sig == 1)));
}

/* Model step function */
void ModeControl_step(void)
{
  boolean_T guard;
  boolean_T guard_0;

  /* Chart: '<Root>/MaintenJudge' */
  /* Gateway: MaintenJudge */
  /* During: MaintenJudge */
  if (ModeControl_DWork.is_active_c1_ModeControl == 0) {
    /* Entry: MaintenJudge */
    ModeControl_DWork.is_active_c1_ModeControl = 1U;

    /* Entry Internal: MaintenJudge */
    /* Transition: '<S1>:54' */
    ModeControl_DWork.is_c1_ModeControl = ModeControl_IN_High;

    /* Entry 'High': '<S1>:52' */
    ModeControl_DWork.LevelHighCnt = 0U;
    ModeControl_DWork.LevelLowCnt = 0U;
    MaintenStatus_u8_Sig = 0U;

    /* Entry Internal 'High': '<S1>:52' */
    /* Transition: '<S1>:58' */
    ModeControl_DWork.is_High = ModeControl_IN_Idle;
  } else {
    guard = FALSE;
    guard_0 = FALSE;
    if (ModeControl_DWork.is_c1_ModeControl == ModeControl_IN_High) {
      /* During 'High': '<S1>:52' */
      if (ModeControl_MaintenLow() != 0) {
        /* Transition: '<S1>:55' */
        ModeControl_DWork.LevelLowCnt = (uint8_T)(ModeControl_DWork.LevelLowCnt
          + 1);
        ModeControl_DWork.LevelHighCnt = 0U;
        if (ModeControl_DWork.LevelLowCnt >= 20) {
          /* Transition: '<S1>:78' */
          /* Exit Internal 'High': '<S1>:52' */
          ModeControl_DWork.is_High = ModeControl_IN_NO_ACTIVE_CHILD;
          ModeControl_DWork.is_c1_ModeControl = ModeControl_IN_Low;

          /* Entry 'Low': '<S1>:53' */
          ModeControl_DWork.LevelLowCnt = 0U;

          /* Entry Internal 'Low': '<S1>:53' */
          /* Transition: '<S1>:68' */
          ModeControl_DWork.is_Low = ModeControl_IN_Idle;
        } else {
          /* Transition: '<S1>:80' */
          guard_0 = TRUE;
        }
      } else {
        guard_0 = TRUE;
      }
    } else {
      /* During 'Low': '<S1>:53' */
      if (ModeControl_MaintenHigh() != 0) {
        /* Transition: '<S1>:56' */
        ModeControl_DWork.LevelHighCnt = (uint8_T)
          (ModeControl_DWork.LevelHighCnt + 1);
        ModeControl_DWork.LevelLowCnt = 0U;
        if (ModeControl_DWork.LevelHighCnt >= 20) {
          /* Transition: '<S1>:82' */
          /* Exit Internal 'Low': '<S1>:53' */
          ModeControl_DWork.is_Low = ModeControl_IN_NO_ACTIVE_CHILD;
          ModeControl_DWork.is_c1_ModeControl = ModeControl_IN_High;

          /* Entry 'High': '<S1>:52' */
          ModeControl_DWork.LevelHighCnt = 0U;
          MaintenStatus_u8_Sig = 0U;

          /* Entry Internal 'High': '<S1>:52' */
          /* Transition: '<S1>:58' */
          ModeControl_DWork.is_High = ModeControl_IN_Idle;
        } else {
          /* Transition: '<S1>:84' */
          guard = TRUE;
        }
      } else {
        guard = TRUE;
      }
    }

    if (((int16_T)guard_0) == ((int16_T)TRUE)) {
      if (ModeControl_DWork.is_High == ModeControl_IN_Idle) {
        /* During 'Idle': '<S1>:57' */
        if (ModeControl_One2Two() != 0) {
          /* Transition: '<S1>:60' */
          ModeControl_DWork.is_High = ModeControl_IN_Stage2;

          /* Entry 'Stage2': '<S1>:59' */
          ModeControl_DWork.MaintenStage = 2U;
          ModeControl_DWork.MaintenLowCnt = 0U;
        } else {
          /* Transition: '<S1>:73' */
          ModeControl_DWork.MaintenLowCnt = 0U;
          ModeControl_DWork.MaintenStage = 0U;
          MaintenStatus_u8_Sig = 0U;
        }
      } else {
        /* During 'Stage2': '<S1>:59' */
        MaintenStatus_u8_Sig = 1U;
      }
    }

    if (((int16_T)guard) == ((int16_T)TRUE)) {
      if (ModeControl_DWork.is_Low == ModeControl_IN_Idle) {
        /* During 'Idle': '<S1>:61' */
        if (ModeControl_Zero2One() != 0) {
          /* Transition: '<S1>:67' */
          ModeControl_DWork.is_Low = ModeControl_IN_Stage1;

          /* Entry 'Stage1': '<S1>:66' */
          ModeControl_DWork.MaintenStage = 1U;
          ModeControl_DWork.MaintenLowCnt = 0U;
        } else {
          /* Transition: '<S1>:75' */
          ModeControl_DWork.MaintenLowCnt = 0U;
          ModeControl_DWork.MaintenStage = 0U;
        }
      } else {
        /* During 'Stage1': '<S1>:66' */
        if (ModeControl_DWork.MaintenLowCnt > 12000U) {
          /* Transition: '<S1>:70' */
          ModeControl_DWork.MaintenLowCnt = 0U;
        }

        ModeControl_DWork.MaintenLowCnt = ModeControl_DWork.MaintenLowCnt +
          ((uint16_T)1);
      }
    }
  }

  /* End of Chart: '<Root>/MaintenJudge' */

  /* Chart: '<Root>/mode control' */
  /* Gateway: mode control */
  /* During: mode control */
  if (ModeControl_DWork.is_active_c2_ModeControl == 0) {
    /* Entry: mode control */
    ModeControl_DWork.is_active_c2_ModeControl = 1U;

    /* Entry Internal: mode control */
    /* Transition: '<S2>:2' */
    ModeControl_DWork.is_c2_ModeControl = ModeControl_IN_dummy;

    /* Entry 'dummy': '<S2>:1' */
    SystemMode_u8_Sig = 0U;
  } else {
    switch (ModeControl_DWork.is_c2_ModeControl) {
     case ModeControl_IN_FailureMode:
      /* During 'FailureMode': '<S2>:5' */
      if (ModeControl_ignOFF() != 0) {
        /* Transition: '<S2>:147' */
        ModeControl_DWork.is_c2_ModeControl = ModeControl_IN_PowerDown;

        /* Entry 'PowerDown': '<S2>:30' */
        SystemMode_u8_Sig = 9U;
        PDFinish_u8_Sig = 0U;
      } else if (ModeControl_FAILtoMTAIN() != 0) {
        /* Transition: '<S2>:152' */
        ModeControl_DWork.is_c2_ModeControl = ModeControl_IN_MaintenanceMode;

        /* Entry 'MaintenanceMode': '<S2>:36' */
        SystemMode_u8_Sig = 5U;
      } else {
        SystemMode_u8_Sig = 110U;
      }
      break;

     case ModeControl_IN_MaintenanceMode:
      /* During 'MaintenanceMode': '<S2>:36' */
      if (ModeControl_ignOFF() != 0) {
        /* Transition: '<S2>:154' */
        ModeControl_DWork.is_c2_ModeControl = ModeControl_IN_PowerDown;

        /* Entry 'PowerDown': '<S2>:30' */
        SystemMode_u8_Sig = 9U;
        PDFinish_u8_Sig = 0U;
      } else {
        SystemMode_u8_Sig = 5U;
      }
      break;

     case ModeControl_IN_Normal:
      /* During 'Normal': '<S2>:24' */
      if (ModeControl_NMtoPDT() != 0) {
        /* Transition: '<S2>:108' */
        /* Exit 'Normal': '<S2>:24' */
        NormalFinish_u8_Sig = 0U;
        ModeControl_DWork.is_c2_ModeControl = ModeControl_IN_PowerDownTest;

        /* Entry 'PowerDownTest': '<S2>:34' */
        SystemMode_u8_Sig = 8U;
        PDTFinish_u8_Sig = 0U;
      } else if (ModeControl_NMtoFAIL() != 0) {
        /* Transition: '<S2>:114' */
        /* Exit 'Normal': '<S2>:24' */
        NormalFinish_u8_Sig = 0U;
        ModeControl_DWork.is_c2_ModeControl = ModeControl_IN_FailureMode;

        /* Entry 'FailureMode': '<S2>:5' */
        SystemMode_u8_Sig = 110U;
      } else if (ModeControl_NMtoMTAIN() != 0) {
        /* Transition: '<S2>:115' */
        /* Exit 'Normal': '<S2>:24' */
        NormalFinish_u8_Sig = 0U;
        ModeControl_DWork.is_c2_ModeControl = ModeControl_IN_MaintenanceMode;

        /* Entry 'MaintenanceMode': '<S2>:36' */
        SystemMode_u8_Sig = 5U;
      } else {
        SystemMode_u8_Sig = 2U;
      }
      break;

     case ModeControl_IN_PowerDown:
      /* During 'PowerDown': '<S2>:30' */
      if (ModeControl_PDtoOFF() != 0) {
        /* Transition: '<S2>:141' */
        /* Exit 'PowerDown': '<S2>:30' */
        PDFinish_u8_Sig = 0U;
        ModeControl_DWork.is_c2_ModeControl = ModeControl_IN_dummy;

        /* Entry 'dummy': '<S2>:1' */
        SystemMode_u8_Sig = 0U;
      } else {
        SystemMode_u8_Sig = 9U;
      }
      break;

     case ModeControl_IN_PowerDownTest:
      /* During 'PowerDownTest': '<S2>:34' */
      if (ModeControl_PDTtoPD() != 0) {
        /* Transition: '<S2>:133' */
        /* Exit 'PowerDownTest': '<S2>:34' */
        PDTFinish_u8_Sig = 0U;
        ModeControl_DWork.is_c2_ModeControl = ModeControl_IN_PowerDown;

        /* Entry 'PowerDown': '<S2>:30' */
        SystemMode_u8_Sig = 9U;
        PDFinish_u8_Sig = 0U;
      } else if (ModeControl_PDTtoPUT() != 0) {
        /* Transition: '<S2>:132' */
        PDTtoPUTflag_u8_Sig = 1U;

        /* Exit 'PowerDownTest': '<S2>:34' */
        PDTFinish_u8_Sig = 0U;
        ModeControl_DWork.is_c2_ModeControl = ModeControl_IN_PowerUpTest;

        /* Entry 'PowerUpTest': '<S2>:3' */
        SystemMode_u8_Sig = 1U;
        PUTFinish_u8_Sig = 0U;
      } else if (ModeControl_PDTtoFAIL() != 0) {
        /* Transition: '<S2>:134' */
        /* Exit 'PowerDownTest': '<S2>:34' */
        PDTFinish_u8_Sig = 0U;
        ModeControl_DWork.is_c2_ModeControl = ModeControl_IN_FailureMode;

        /* Entry 'FailureMode': '<S2>:5' */
        SystemMode_u8_Sig = 110U;
      } else {
        SystemMode_u8_Sig = 8U;
      }
      break;

     case ModeControl_IN_PowerUpTest:
      /* During 'PowerUpTest': '<S2>:3' */
      if (ModeControl_PUTtoNM() != 0) {
        /* Transition: '<S2>:94' */
        /* Exit 'PowerUpTest': '<S2>:3' */
        PUTFinish_u8_Sig = 0U;
        ModeControl_DWork.is_c2_ModeControl = ModeControl_IN_Normal;

        /* Entry 'Normal': '<S2>:24' */
        SystemMode_u8_Sig = 2U;
        NormalFinish_u8_Sig = 0U;
      } else if (ModeControl_PUTtoFAIL() != 0) {
        /* Transition: '<S2>:107' */
        /* Exit 'PowerUpTest': '<S2>:3' */
        PUTFinish_u8_Sig = 0U;
        ModeControl_DWork.is_c2_ModeControl = ModeControl_IN_FailureMode;

        /* Entry 'FailureMode': '<S2>:5' */
        SystemMode_u8_Sig = 110U;
      } else if (ModeControl_PUTtoPD() != 0) {
        /* Transition: '<S2>:109' */
        /* Exit 'PowerUpTest': '<S2>:3' */
        PUTFinish_u8_Sig = 0U;
        ModeControl_DWork.is_c2_ModeControl = ModeControl_IN_PowerDown;

        /* Entry 'PowerDown': '<S2>:30' */
        SystemMode_u8_Sig = 9U;
        PDFinish_u8_Sig = 0U;
      } else {
        SystemMode_u8_Sig = 1U;
      }
      break;

     default:
      /* During 'dummy': '<S2>:1' */
      if (ModeControl_ignON() != 0) {
        /* Transition: '<S2>:4' */
        ModeControl_DWork.is_c2_ModeControl = ModeControl_IN_PowerUpTest;

        /* Entry 'PowerUpTest': '<S2>:3' */
        SystemMode_u8_Sig = 1U;
        PUTFinish_u8_Sig = 0U;
      } else {
        SystemMode_u8_Sig = 0U;
      }
      break;
    }
  }

  /* End of Chart: '<Root>/mode control' */
}

/* Model initialize function */
void ModeControl_initialize(void)
{
  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)&ModeControl_DWork, 0,
                sizeof(D_Work_ModeControl));

  /* external outputs */
  (void) memset((void *)&ModeControl_Y, 0,
                sizeof(ExternalOutputs_ModeControl));

  /* ConstCode for Outport: '<Root>/Tssadjstatus' incorporates:
   *  Constant: '<Root>/Constant'
   */
  ModeControl_Y.Tssadjstatus = 0U;

  /* InitializeConditions for Chart: '<Root>/MaintenJudge' */
  ModeControl_DWork.is_High = 0U;
  ModeControl_DWork.is_Low = 0U;
  ModeControl_DWork.is_active_c1_ModeControl = 0U;
  ModeControl_DWork.is_c1_ModeControl = 0U;
  ModeControl_DWork.MaintenLowCnt = 0U;
  ModeControl_DWork.MaintenStage = 0U;
  ModeControl_DWork.LevelHighCnt = 0U;
  ModeControl_DWork.LevelLowCnt = 0U;
  MaintenStatus_u8_Sig = 0U;

  /* InitializeConditions for Chart: '<Root>/mode control' */
  ModeControl_DWork.is_active_c2_ModeControl = 0U;
  ModeControl_DWork.is_c2_ModeControl = 0U;
  PDTFinish_u8_Sig = 0U;
  PUTFinish_u8_Sig = 0U;
  PDFinish_u8_Sig = 0U;
  NormalFinish_u8_Sig = 0U;
  PDTtoPUTflag_u8_Sig = 0U;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
