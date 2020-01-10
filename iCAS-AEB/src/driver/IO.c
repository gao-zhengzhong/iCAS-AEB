//****************************************************************************
// @Module        Parallel Ports
// @Filename      IO.c
// @Project       P300.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC2365B-40F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains functions that use the IO module.
//
//----------------------------------------------------------------------------
// @Date          2019-11-04 16:14:54
//
//****************************************************************************

// USER CODE BEGIN (IO_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.h"

// USER CODE BEGIN (IO_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (IO_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (IO_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (IO_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (IO_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (IO_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (IO_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (IO_General,9)

// USER CODE END


//****************************************************************************
// @Function      void IO_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the IO function 
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

// USER CODE BEGIN (IO_Function,1)

// USER CODE END

void IO_vInit(void)
{
  // USER CODE BEGIN (IO_Function,2)

  // USER CODE END


  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P0:
  ///  -----------------------------------------------------------------------
  ///  P0.0 is used as alternate output for the CCU61 output (CC60)
  ///  - push/pull output is selected
  ///  P0.1 is used as alternate output for the CCU61 output (CC61)
  ///  - push/pull output is selected
  ///  P0.2 is used as alternate output for the  CCU61 output (CC62)
  ///  - push/pull output is selected
  ///  P0.3 is used as alternate output for the CCU61 output (COUT60)
  ///  - push/pull output is selected
  ///  P0.4 is used as alternate output for the CCU61 output (COUT61)
  ///  - push/pull output is selected
  ///  P0.5 is used as alternate output for the  CCU61 output (COUT62)
  ///  - push/pull output is selected
  ///  P0.7 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level

  ///  P0.0 - P0.3 output driver characteristic: strong driver
  ///  P0.4 - P0.7 output driver characteristic: strong driver

  ///  P0.0 - P0.3 output edge characteristic: sharp edge mode
  ///  P0.4 - P0.7 output edge characteristic: sharp edge mode

  P0_IOCR07      =  0x0080;      // load port control register 7

  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P1:
  ///  -----------------------------------------------------------------------
  ///  P1.4 is used as general input
  ///  - pull device is tristate 
  ///  P1.5 is used as general input
  ///  - pull device is tristate 
  ///  P1.7 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level

  ///  P1.0 - P1.3 output driver characteristic: strong driver
  ///  P1.4 - P1.7 output driver characteristic: strong driver

  ///  P1.0 - P1.3 output edge characteristic: sharp edge mode
  ///  P1.4 - P1.7 output edge characteristic: sharp edge mode

  P1_IOCR07      =  0x0080;      // load port control register 7

  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P2:
  ///  -----------------------------------------------------------------------
  ///  P2.0 is used as alternate input for the CAN0 Receive input(RXDC0C)
  ///  P2.1 is used as alternate output for the CAN0 Transmit output(TXDC0C)
  ///  - push/pull output is selected
  ///  P2.2 is used as alternate output for the CAN1 Transmit output(TXDC1B)
  ///  - push/pull output is selected
  ///  P2.4 is used as alternate input for the CAN1 Receive input(RXDC1A)

  ///  P2.0 - P2.3 output driver characteristic: strong driver
  ///  P2.4 - P2.7 output driver characteristic: strong driver
  ///  P2.8 - P2.13 output driver characteristic: strong driver

  ///  P2.0 - P2.3 output edge characteristic: sharp edge mode
  ///  P2.4 - P2.7 output edge characteristic: sharp edge mode
  ///  P2.8 - P2.13 output edge characteristic: sharp edge mode


  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P4:
  ///  -----------------------------------------------------------------------
  ///  P4.0 is used as general input
  ///  - pull device is tristate 
  ///  P4.1 is used as general input
  ///  - pull device is tristate 
  ///  P4.2 is used as general input
  ///  - pull device is tristate 
  ///  P4.3 is used as general input
  ///  - pull device is tristate 

  ///  P4.0 - P4.3 output driver characteristic: strong driver

  ///  P4.0 - P4.3 output edge characteristic: sharp edge mode


  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P5:
  ///  -----------------------------------------------------------------------
  ///  P5.0 is used as alternate input for the  Analog Input Pin (AN50)
  ///  P5.2 is used as alternate input for the  Analog Input Pin (AN52)
  ///  P5.3 is used as alternate input for the  Analog Input Pin (AN53)
  ///  P5.4 is used as alternate input for the  Analog Input Pin (AN54)
  ///  P5.5 is used as alternate input for the  Analog Input Pin (AN55)
  ///  P5.8 is used as alternate input for the  Analog Input Pin (AN58)
  ///  P5.9 is used as alternate input for the  Analog Input Pin (AN59)
  ///  P5.10 is used as alternate input for the  Analog Input Pin (AN510)
  ///  P5.11 is used as alternate input for the  Analog Input Pin (AN511)
  ///  P5.13 is used as alternate input for the  Analog Input Pin (AN513)
  ///  P5.15 is used as alternate input for the  Analog Input Pin (AN515)


  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P6:
  ///  -----------------------------------------------------------------------
  ///  P6.0 is used as general input
  ///  - pull device is tristate 
  ///  P6.2 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level

  ///  P6.0 - P6.2 output driver characteristic: strong driver

  ///  P6.0 - P6.2 output edge characteristic: sharp edge mode

  P6_IOCR02      =  0x0080;      // load port control register 2

  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P7:
  ///  -----------------------------------------------------------------------
  ///  P7.0 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level
  ///  P7.1 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level
  ///  P7.3 is used as general input
  ///  - pull device is tristate 
  ///  P7.4 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level

  ///  P7.0 - P7.3 output driver characteristic: strong driver
  ///  P7.4 - P7.4 output driver characteristic: strong driver

  ///  P7.0 - P7.3 output edge characteristic: sharp edge mode
  ///  P7.4 - P7.4 output edge characteristic: sharp edge mode

  P7_IOCR00      =  0x0080;      // load port control register 0
  P7_IOCR01      =  0x0080;      // load port control register 1
  P7_IOCR04      =  0x0080;      // load port control register 4

  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P10:
  ///  -----------------------------------------------------------------------
  ///  P10.1 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level
  ///  P10.4 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level

  ///  P10.0 - P10.3 output driver characteristic: strong driver
  ///  P10.4 - P10.7 output driver characteristic: strong driver
  ///  P10.8 - P10.11 output driver characteristic: strong driver
  ///  P10.12 - P10.15 output driver characteristic: strong driver

  ///  P10.0 - P10.3 output edge characteristic: sharp edge mode
  ///  P10.4 - P10.7 output edge characteristic: sharp edge mode
  ///  P10.8 - P10.11 output edge characteristic: sharp edge mode
  ///  P10.12 - P10.15 output edge characteristic: sharp edge mode

  P10_IOCR01     =  0x0080;      // load port control register 1
  P10_IOCR04     =  0x0080;      // load port control register 4

  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P15:
  ///  -----------------------------------------------------------------------
  ///  P15.0 is used as alternate input for the  Analog Input Pin (AN0)
  ///  P15.2 is used as alternate input for the  Analog Input Pin (AN2)
  ///  P15.4 is used as alternate input for the  Analog Input Pin (AN4)



  // USER CODE BEGIN (IO_Function,3)

  // USER CODE END

} //  End of function IO_vInit




// USER CODE BEGIN (IO_General,10)

// USER CODE END

