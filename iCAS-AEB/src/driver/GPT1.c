//****************************************************************************
// @Module        General Purpose Timer Unit (GPT1)
// @Filename      GPT1.c
// @Project       P300.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC2365B-40F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains functions that use the GPT1 module.
//
//----------------------------------------------------------------------------
// @Date          2019-11-04 16:14:54
//
//****************************************************************************

// USER CODE BEGIN (GPT1_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.h"

// USER CODE BEGIN (GPT1_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (GPT1_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (GPT1_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (GPT1_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (GPT1_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (GPT1_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (GPT1_General,8)
extern void task3(void);
extern void task4(void);
// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (GPT1_General,9)

// USER CODE END


//****************************************************************************
// @Function      void GPT1_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the GPT1 function 
//                library. It is assumed that the SFRs used by this library 
//                are in reset state. 
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

// USER CODE BEGIN (Init,1)

// USER CODE END

void GPT1_vInit(void)
{

  volatile unsigned int uwTemp;

  // USER CODE BEGIN (Init,2)

  // USER CODE END
  ///  -----------------------------------------------------------------------
  ///  Configuration of Timer Block Prescaler 1:
  ///  -----------------------------------------------------------------------
  GPT12E_KSCCFG  =  0x0003;      // Module Enable

  uwTemp         =  GPT12E_KSCCFG;  // dummy read to avoid pipeline effects

  ///  -----------------------------------------------------------------------
  ///  Configuration of Timer Block Prescaler 1:
  ///  -----------------------------------------------------------------------
  ///  - prescaler for timer block 1 is 4


  ///  -----------------------------------------------------------------------
  ///  Configuration of the GPT1 Core Timer 3:
  ///  -----------------------------------------------------------------------
  ///  - timer 3 works in timer mode
  ///  - external up/down control is disabled
  ///  - prescaler factor is 4
  ///  - up/down control bit is reset
  ///  - alternate output function T3OUT () is disabled
  ///  - timer 3 output toggle latch (T3OTL) is set to 0
  ///  - timer 3 run bit is reset

  GPT12E_T3CON   =  0x0800;      // load timer 3 control register
  GPT12E_T3      =  0xFFF6;      // load timer 3 register

  ///  -----------------------------------------------------------------------
  ///  Configuration of the GPT1 Auxiliary Timer 2:
  ///  -----------------------------------------------------------------------
  ///  - timer 2 works in timer mode
  ///  - external up/down control is disabled
  ///  - prescaler factor is 4
  ///  - up/down control bit is reset
  ///  - timer 2 run bit is reset

  GPT12E_T2CON   =  0x0000;      // load timer 2 control register
  GPT12E_T2      =  0xFFF6;      // load timer 2 register

  ///  -----------------------------------------------------------------------
  ///  Configuration of the GPT1 Auxiliary Timer 4:
  ///  -----------------------------------------------------------------------
  ///  - timer 4 works in timer mode
  ///  - external up/down control is disabled
  ///  - prescaler factor is 4
  ///  - up/down control bit is reset
  ///  - timer 4 run bit is reset

  GPT12E_T4CON   =  0x0000;      // load timer 4 control register
  GPT12E_T4      =  0xFFF6;      // load timer 4 register

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used GPT1 Port Pins:
  ///  -----------------------------------------------------------------------



  ///  -----------------------------------------------------------------------
  ///  Configuration of the used GPT1 Interrupts:
  ///  -----------------------------------------------------------------------
  ///  timer 2 service request node configuration:
  ///  - timer 2 interrupt priority level (ILVL) = 10
  ///  - timer 2 interrupt group level (GLVL) = 0
  ///  - timer 2 group priority extension (GPX) = 0

  GPT12E_T2IC    =  0x0068;     

  ///  timer 3 service request node configuration:
  ///  - timer 3 interrupt priority level (ILVL) = 9
  ///  - timer 3 interrupt group level (GLVL) = 0
  ///  - timer 3 group priority extension (GPX) = 0

  GPT12E_T3IC    =  0x0064;     

  ///  timer 4 service request node configuration:
  ///  - timer 4 interrupt priority level (ILVL) = 8
  ///  - timer 4 interrupt group level (GLVL) = 0
  ///  - timer 4 group priority extension (GPX) = 0

  GPT12E_T4IC    =  0x0060;     


  // USER CODE BEGIN (GPT1_Function,3)

  // USER CODE END

} //  End of function GPT1_viTmr4


//****************************************************************************
// @Function      void GPT1_viTmr3(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the interrupt service routine for the GPT1 timer 3. 
//                It is called up in the case of over or underflow of the 
//                timer 3 register.
//                If the incremental interface mode is selected it is called 
//                up if count edge or count direction was detected.
//                
//                Please note that you have to add application specific code 
//                to this function.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

// USER CODE BEGIN (Tmr3,1)

// USER CODE END

void GPT1_viTmr3(void) interrupt T3INT
{
  // USER CODE BEGIN (Tmr3,2)
	GPT12E_T3IC &= 0xFFBF;
	GPT1_vLoadTmr_GPT1_TIMER_3(0xFFF6);
	task3();
  // USER CODE END


  // USER CODE BEGIN (Tmr3,5)

  // USER CODE END

} //  End of function GPT1_viTmr3


//****************************************************************************
// @Function      void GPT1_viTmr2(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the interrupt service routine for the GPT1 timer 2. 
//                It is called up in the case of over or underflow of the 
//                timer 2 register.
//                If the incremental interface mode is selected and the 
//                interrupt for this mode is not disabled it is called up if 
//                count edge or count direction was detected.
//                
//                Please note that you have to add application specific code 
//                to this function.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

// USER CODE BEGIN (Tmr2,1)

// USER CODE END

void GPT1_viTmr2(void) interrupt T2INT
{
  // USER CODE BEGIN (Tmr2,2)
	GPT12E_T2IC &= 0xFFBF;
	GPT1_vLoadTmr_GPT1_TIMER_2(0xFFF6);

  // USER CODE END


  // USER CODE BEGIN (Tmr2,5)

  // USER CODE END

} //  End of function GPT1_viTmr2


//****************************************************************************
// @Function      void GPT1_viTmr4(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the interrupt service routine for the GPT1 timer 4. 
//                It is called up in the case of over or underflow of the 
//                timer 4 register.
//                If the incremental interface mode is selected and the 
//                interrupt for this mode is not disabled it is called up if 
//                count edge or count direction was detected.
//                
//                Please note that you have to add application specific code 
//                to this function.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

// USER CODE BEGIN (Tmr4,1)

// USER CODE END

void GPT1_viTmr4(void) interrupt T4INT
{
  // USER CODE BEGIN (Tmr4,2)
	GPT12E_T4IC &= 0xFFBF;
	GPT1_vLoadTmr_GPT1_TIMER_4(0xFFF6);
	task4();
  // USER CODE END


  // USER CODE BEGIN (Tmr4,5)

  // USER CODE END

} //  End of function GPT1_viTmr4


//****************************************************************************
// @Function      ubyte GPT1_ubCheckRotation(ubyte TimerNr) 
//
//----------------------------------------------------------------------------
// @Description   This function returns the status of the bit TxCHDIR of 
//                selected TimerNr and resets the status bit. If return value 
//                is 1 change of count direction was detected.
//                
//                Note:
//                Use this function only for TimerNr wich works in 
//                incremental interface mode (rotation detection mode) AND 
//                the interrupt for this mode is disabled.
//                
//                The following definitions are available for TimerNr:
//                GPT1_TIMER_2
//                GPT1_TIMER_3
//                GPT1_TIMER_4
//
//----------------------------------------------------------------------------
// @Returnvalue   1 if count direction was changed, else 0
//
//----------------------------------------------------------------------------
// @Parameters    TimerNr: 
//                The name of the timer to be used
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

// USER CODE BEGIN (CheckRotation,1)

// USER CODE END

ubyte GPT1_ubCheckRotation(ubyte TimerNr)
{
  ubyte ubReturnValue;

  ubReturnValue = 0;
  if(TimerNr == 2 && GPT12E_T2CON_T2CHDIR == 1)
  {
    ubReturnValue = 1;
    GPT12E_T2CON_T2CHDIR = 0;
  }

  if(TimerNr == 3 && GPT12E_T3CON_T3CHDIR == 1)
  {
    ubReturnValue = 1;
    GPT12E_T3CON_T3CHDIR = 0;
  }

  if(TimerNr == 4 && GPT12E_T4CON_T4CHDIR == 1)
  {
    ubReturnValue = 1;
    GPT12E_T4CON_T4CHDIR = 0;
  }


  return(ubReturnValue);

} //  End of function GPT1_ubCheckRotation


//****************************************************************************
// @Function      ubyte GPT1_ubCheckEdge(ubyte TimerNr) 
//
//----------------------------------------------------------------------------
// @Description   This function returns the status of the bit TxEDGE of 
//                selected TimerNr and resets the status bit. If return value 
//                is 1 successful edge was detected.
//                
//                Note:
//                Use this function only for TimerNr wich works in 
//                incremental interface mode (edge detection mode) AND the 
//                interrupt for this mode is disabled.
//                
//                The following definitions are available for TimerNr:
//                GPT1_TIMER_2
//                GPT1_TIMER_3
//                GPT1_TIMER_4
//
//----------------------------------------------------------------------------
// @Returnvalue   1 if successful edge was detected, else 0
//
//----------------------------------------------------------------------------
// @Parameters    TimerNr: 
//                The name of the timer to be used
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

// USER CODE BEGIN (CheckEdge,1)

// USER CODE END

ubyte GPT1_ubCheckEdge(ubyte TimerNr)
{
  ubyte ubReturnValue;

  ubReturnValue = 0;
  if(TimerNr == 2 && GPT12E_T2CON_T2EDGE == 1)
  {
    ubReturnValue = 1;
    GPT12E_T2CON_T2EDGE = 0;
  }

  if(TimerNr == 3 && GPT12E_T3CON_T3EDGE == 1)
  {
    ubReturnValue = 1;
    GPT12E_T3CON_T3EDGE = 0;
  }

  if(TimerNr == 4 && GPT12E_T4CON_T4EDGE == 1)
  {
    ubReturnValue = 1;
    GPT12E_T4CON_T4EDGE = 0;
  }


  return(ubReturnValue);

} //  End of function GPT1_ubCheckEdge




// USER CODE BEGIN (GPT1_General,10)

// USER CODE END

