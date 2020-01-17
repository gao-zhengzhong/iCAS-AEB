//****************************************************************************
// @Module        Analog / Digital Converter  (ADC0)
// @Filename      ADC0.c
// @Project       P300.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC2365B-40F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains functions that use the ADC0 module.
//
//----------------------------------------------------------------------------
// @Date          2019-11-04 16:14:55
//
//****************************************************************************

// USER CODE BEGIN (ADC0_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.h"

// USER CODE BEGIN (ADC0_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (ADC0_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (ADC0_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (ADC0_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (ADC0_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (ADC0_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (ADC0_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (ADC0_General,9)

// USER CODE END


//****************************************************************************
// @Function      void ADC0_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the ADC function 
//                library. It is assumed that the SFRs used by this library 
//                are in reset state. 
//                
//                Following SFR fields will be initialized:
//                GLOBCTR  - Global Control
//                RSPR0    - Priority and Arbitration Register
//                ASENR    - Arbitration slot enable register
//                CHCTRx   - Channel Control Register x
//                RCRx     - Result Control Register x
//                KSCFG    - Module configuration Register
//                INPCR    - Input class Registers
//                CHINPRx  - Channel Interrupt register
//                EVINPRx  - Event Interrupt register
//                SYNCTR   - Synchronisation control register
//                LCBRx    - Limit check boundary register
//                PISEL    - Port input selection
//                QMR0     - Sequential 0 mode register
//                CRMR1    - Parallel mode register
//                QMR2     - Sequential 2 mode register
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

// USER CODE BEGIN (ADC0_Init,1)

// USER CODE END

void ADC0_vInit(void)
{
  volatile unsigned int uwTemp;

  // USER CODE BEGIN (ADC0_Init,2)

  // USER CODE END

  ///  -----------------------------------------------------------------------
  ///  Configuration of ADC0 kernel configuration register:
  ///  -----------------------------------------------------------------------

  ADC0_KSCFG     =  0x0003;      // load ADC0 kernel configuration register

  ///  - the ADC module clock is enabled
  ///  - the ADC module clock = 80.00 MHz

  uwTemp         =  ADC0_KSCFG;  // dummy read to avoid pipeline effects

  ///  -----------------------------------------------------------------------
  ///  Configure global control register:
  ///  -----------------------------------------------------------------------
  ///  --- Conversion Timing -----------------
  ///  - Conversion time (CTC) = 00.85 us
  ///  - Analog clock is 1/4th of module clock and digital clock is 1/1 times 
  ///  of module clock

  ///  - the permanent arbitration mode is selected

  ADC0_GLOBCTR   =  0x0003;      // load global control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Arbitration Slot enable register and also the Source 
  ///  Priority register:
  ///  -----------------------------------------------------------------------
  ///  - Arbitration Slot 0 is enabled
  ///  - Arbitration Slot 1 is disabled
  ///  - Arbitration Slot 2 is enabled
  ///  - the priority of request source 0 is high
  ///  - the wait-for-start mode is selected for source 0
  ///  - the priority of request source 1 is low
  ///  - the wait-for-start mode is selected for source 1
  ///  - the priority of request source 2 is high
  ///  - the wait-for-start mode is selected for source 2

  ADC0_ASENR     =  0x0005;      // load Arbitration Slot enable register

  ADC0_RSPR0     =  0x0303;      // load Priority and Arbitration register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Channel Control Registers:
  ///  -----------------------------------------------------------------------
  ///  Configuration of Channel 0
  ///  - the result register0 is selected
  ///  - the limit check 0 is selected
  ///  - the reference voltage selected is Standard Voltage (Varef)
  ///  - the input class selected is Input Class 1
  ///  - LCBR0 is selected as upper boundary
  ///  - LCBR1 is selected as lower boundary

  ADC0_CHCTR0    =  0x0084;      // load channel control register

  ///  Configuration of Channel 2
  ///  - the result register1 is selected
  ///  - the limit check 0 is selected
  ///  - the reference voltage selected is Standard Voltage (Varef)
  ///  - the input class selected is Input Class 1
  ///  - LCBR0 is selected as upper boundary
  ///  - LCBR1 is selected as lower boundary

  ADC0_CHCTR2    =  0x1484;      // load channel control register

  ///  Configuration of Channel 3
  ///  - the result register3 is selected
  ///  - the limit check 0 is selected
  ///  - the reference voltage selected is Standard Voltage (Varef)
  ///  - the input class selected is Input Class 1
  ///  - LCBR0 is selected as upper boundary
  ///  - LCBR1 is selected as lower boundary

  ADC0_CHCTR3    =  0x3004;      // load channel control register

  ///  Configuration of Channel 4
  ///  - the result register3 is selected
  ///  - the limit check 0 is selected
  ///  - the reference voltage selected is Standard Voltage (Varef)
  ///  - the input class selected is Input Class 1
  ///  - LCBR0 is selected as upper boundary
  ///  - LCBR1 is selected as lower boundary

  ADC0_CHCTR4    =  0x3004;      // load channel control register

  ///  Configuration of Channel 5
  ///  - the result register3 is selected
  ///  - the limit check 0 is selected
  ///  - the reference voltage selected is Standard Voltage (Varef)
  ///  - the input class selected is Input Class 1
  ///  - LCBR0 is selected as upper boundary
  ///  - LCBR1 is selected as lower boundary

  ADC0_CHCTR5    =  0x3484;      // load channel control register

  ///  Configuration of Channel 8
  ///  - the result register3 is selected
  ///  - the limit check 0 is selected
  ///  - the reference voltage selected is Standard Voltage (Varef)
  ///  - the input class selected is Input Class 1
  ///  - LCBR0 is selected as upper boundary
  ///  - LCBR1 is selected as lower boundary

  ADC0_CHCTR8    =  0x3004;      // load channel control register

  ///  Configuration of Channel 9
  ///  - the result register3 is selected
  ///  - the limit check 0 is selected
  ///  - the reference voltage selected is Standard Voltage (Varef)
  ///  - the input class selected is Input Class 1
  ///  - LCBR0 is selected as upper boundary
  ///  - LCBR1 is selected as lower boundary

  ADC0_CHCTR9    =  0x3004;      // load channel control register

  ///  Configuration of Channel 10
  ///  - the result register3 is selected
  ///  - the limit check 0 is selected
  ///  - the reference voltage selected is Standard Voltage (Varef)
  ///  - the input class selected is Input Class 1
  ///  - LCBR0 is selected as upper boundary
  ///  - LCBR1 is selected as lower boundary

  ADC0_CHCTR10   =  0x3004;      // load channel control register

  ///  Configuration of Channel 11
  ///  - the result register3 is selected
  ///  - the limit check 0 is selected
  ///  - the reference voltage selected is Standard Voltage (Varef)
  ///  - the input class selected is Input Class 1
  ///  - LCBR0 is selected as upper boundary
  ///  - LCBR1 is selected as lower boundary

  ADC0_CHCTR11   =  0x3004;      // load channel control register

  ///  Configuration of Channel 13
  ///  - the result register3 is selected
  ///  - the limit check 0 is selected
  ///  - the reference voltage selected is Standard Voltage (Varef)
  ///  - the input class selected is Input Class 1
  ///  - LCBR0 is selected as upper boundary
  ///  - LCBR1 is selected as lower boundary

  ADC0_CHCTR13   =  0x3004;      // load channel control register

  ///  Configuration of Channel 15
  ///  - the result register3 is selected
  ///  - the limit check 0 is selected
  ///  - the reference voltage selected is Standard Voltage (Varef)
  ///  - the input class selected is Input Class 1
  ///  - LCBR0 is selected as upper boundary
  ///  - LCBR1 is selected as lower boundary

  ADC0_CHCTR15   =  0x3004;      // load channel control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Sample Time and Resolution:
  ///  -----------------------------------------------------------------------

  ///  10 bit resolution selected

  ADC0_INPCR0    =  0x0000;      // load input class0 register

  ///  10 bit resolution selected

  ADC0_INPCR1    =  0x0000;      // load input class1 register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Result Control Registers:
  ///  -----------------------------------------------------------------------
  ///  Configuration of Result Control Register 0
  ///  - the data reduction filter is disabled
  ///  - the event interrupt is disabled
  ///  - the wait-for-read mode is disabled
  ///  - the FIFO functionality is disabled

  ADC0_RCR0      =  0x0000;      // load result control register 0

  ///  Configuration of Result Control Register 1
  ///  - the data reduction filter is disabled
  ///  - the event interrupt is disabled
  ///  - the wait-for-read mode is disabled
  ///  - the FIFO functionality is disabled

  ADC0_RCR1      =  0x0000;      // load result control register 1

  ///  Configuration of Result Control Register 2
  ///  - the data reduction filter is disabled
  ///  - the event interrupt is disabled
  ///  - the wait-for-read mode is disabled
  ///  - the FIFO functionality is disabled

  ADC0_RCR2      =  0x0000;      // load result control register 2

  ///  Configuration of Result Control Register 3
  ///  - the data reduction filter is disabled
  ///  - the event interrupt is disabled
  ///  - the wait-for-read mode is disabled
  ///  - the FIFO functionality is disabled

  ADC0_RCR3      =  0x0000;      // load result control register 3

  ///  Configuration of Result Control Register 4
  ///  - the data reduction filter is disabled
  ///  - the event interrupt is disabled
  ///  - the wait-for-read mode is disabled
  ///  - the FIFO functionality is disabled

  ADC0_RCR4      =  0x0000;      // load result control register 4

  ///  Configuration of Result Control Register 5
  ///  - the data reduction filter is disabled
  ///  - the event interrupt is disabled
  ///  - the wait-for-read mode is disabled
  ///  - the FIFO functionality is disabled

  ADC0_RCR5      =  0x0000;      // load result control register 5

  ///  Configuration of Result Control Register 6
  ///  - the data reduction filter is disabled
  ///  - the event interrupt is disabled
  ///  - the wait-for-read mode is disabled
  ///  - the FIFO functionality is disabled

  ADC0_RCR6      =  0x0000;      // load result control register 6

  ///  Configuration of Result Control Register 7
  ///  - the data reduction filter is disabled
  ///  - the event interrupt is disabled
  ///  - the wait-for-read mode is disabled
  ///  - the FIFO functionality is disabled

  ADC0_RCR7      =  0x0000;      // load result control register 7

  ///  -----------------------------------------------------------------------
  ///  Configuration of Channel Interrupt Node Pointer Register:
  ///  -----------------------------------------------------------------------
  ///  - the SR0 line become activated if channel 0 interrupt is generated
  ///  - the SR0 line become activated if channel 2 interrupt is generated
  ///  - the SR0 line become activated if channel 3 interrupt is generated

  ADC0_CHINPR0   =  0x0000;      // load channel interrupt node pointer 
                                 // register

  ///  - the SR0 line become activated if channel 4 interrupt is generated
  ///  - the SR0 line become activated if channel 5 interrupt is generated

  ADC0_CHINPR4   =  0x0000;      // load channel interrupt node pointer 
                                 // register

  ///  - the SR0 line become activated if channel 8 interrupt is generated
  ///  - the SR0 line become activated if channel 9 interrupt is generated
  ///  - the SR0 line become activated if channel 10 interrupt is generated
  ///  - the SR0 line become activated if channel 11 interrupt is generated

  ADC0_CHINPR8   =  0x0000;      // load channel interrupt node pointer 
                                 // register

  ///  - the SR0 line become activated if channel 13 interrupt is generated
  ///  - the SR0 line become activated if channel 15 interrupt is generated

  ADC0_CHINPR12  =  0x0000;      // load channel interrupt node pointer 
                                 // register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Event Interrupt Node Pointer Register for Source 
  ///  Interrupts:
  ///  -----------------------------------------------------------------------
  ///  - the SR 0 line become activated if the event 0 interrupt is generated
  ///  - the SR 0 line become activated if the event 2 interrupt is generated

  ADC0_EVINPR0   =  0x0000;      // load event interrupt set flag register 

  ///  -----------------------------------------------------------------------
  ///  Configuration of Event Interrupt Node Pointer Register for Result 
  ///  Interrupts:
  ///  -----------------------------------------------------------------------

  ADC0_EVINPR8   =  0x0000;      // load event interrupt set flag register 


  ADC0_EVINPR12  =  0x0000;      // load event interrupt set flag register 

  ///  -----------------------------------------------------------------------
  ///  Configuration of Service Request Nodes 0 - 3 :
  ///  -----------------------------------------------------------------------

  ///  -----------------------------------------------------------------------
  ///  Configuration of Limit Check Boundary:
  ///  -----------------------------------------------------------------------

  ADC0_LCBR0     =  0x0198;      // load limit check boundary register 0

  ADC0_LCBR1     =  0x0E64;      // load limit check boundary register 1

  ADC0_LCBR2     =  0x0554;      // load limit check boundary register 2

  ADC0_LCBR3     =  0x0AA8;      // load limit check boundary register 3

  ///  -----------------------------------------------------------------------
  ///  Configuration of Gating source and External Trigger Control:
  ///  -----------------------------------------------------------------------
  ///  - No Gating source selected for Arbitration Source 0

  ///  - the trigger input selection is not enabled for source 0

  ADC0_RSIR0     =  0x0000;      // load external trigger control register 
                                 // for Request Source 0

  ///  - No Gating source selected for Arbitration Source 1

  ///  - the trigger input TRSEL selection is not enabled for Source 1

  ADC0_RSIR1     =  0x0000;      // load external trigger control register 
                                 // for Request Source 1

  ///  - No Gating source selected for Arbitration Source 2

  ///  - the trigger input TRSEL selection is not enabled for Source 2

  ADC0_RSIR2     =  0x0000;      // load external trigger control register 
                                 // for Request Source 2

  ///  -----------------------------------------------------------------------
  ///  Configuration of Conversion Queue Mode Register:Sequential Source 0
  ///  -----------------------------------------------------------------------
  ///  - the gating line is permanently Enabled
  ///  - the external trigger is disabled

  ADC0_QMR0      =  0x0001;      // load queue mode register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Conversion Queue Mode Register:Sequential Source 2
  ///  -----------------------------------------------------------------------
  ///  - the gating line is permanently Enabled
  ///  - the external trigger is disabled

  ADC0_QMR2      =  0x0001;      // load queue mode register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Conversion Request Mode Registers:Parallel Source 
  ///  -----------------------------------------------------------------------
  ///  - the gating line is permanently Disabled
  ///  - the external trigger is disabled
  ///  - the source interrupt is disabled
  ///  - the autoscan functionality is disabled

  ADC0_CRMR1     =  0x0000;      // load conversion request mode register 1

  ///  -----------------------------------------------------------------------
  ///  Configuration of Synchronisation Registers:
  ///  -----------------------------------------------------------------------
  ///  - ADC0 is master 

  ADC0_SYNCTR   |=  0x0010;      // Synchronisation register

  P5_DIDIS       =  0xAF3D;      // Port 5 Digital input disable register



  // USER CODE BEGIN (ADC0_Init,3)

  // USER CODE END

} //  End of function ADC0_vInit


//****************************************************************************
// @Function      void ADC0_vStartSeq0ReqChNum(ubyte ubExtTrg, ubyte 
//                ubEnIntr, ubyte ubRFill, ubyte ubChannelNum) 
//
//----------------------------------------------------------------------------
// @Description   This function starts the conversion of the requested 
//                channel.
//                NOTE -
//                Before passing ubEnIntr argument as 1,make sure that Seq 0 
//                source interrupt is enabled.
//                External Trigger -> 0,Indicates software trigger 
//                (Conversion starts once this function is executed)
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubExtTrg: 
//                External Trigger : defines external trigger.
// @Parameters    ubEnIntr: 
//                Enable Source Interrupt : defines source interrupt
// @Parameters    ubRFill: 
//                Refill : defines the refill
// @Parameters    ubChannelNum: 
//                Channel number : Name of the Request Channel Number (0 - 
//                15)- see macros defined in the header file
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

void ADC0_vStartSeq0ReqChNum(ubyte ubExtTrg, ubyte ubEnIntr, ubyte ubRFill, ubyte ubChannelNum)
{

    uword uwVal = 0;
    if (ubExtTrg == 1)
    {
        uwVal = 0x0080;
    }
    if (ubEnIntr == 1)
    {
        uwVal = uwVal + 0x0040;
    }
    if (ubRFill == 1)
    {
        uwVal = uwVal + 0x0020;
    }
    uwVal = uwVal + (ubChannelNum & 0x001f);

   ADC0_QINR0 = uwVal; // requested channel 

} //  End of function ADC0_vStartSeq0ReqChNum


//****************************************************************************
// @Function      void ADC0_vStartSeq2ReqChNum(ubyte ubExtTrg, ubyte 
//                ubEnIntr, ubyte ubRFill, ubyte ubChannelNum) 
//
//----------------------------------------------------------------------------
// @Description   This function starts the conversion of the requested 
//                channel.
//                NOTE -
//                Before passing ubEnIntr argument as 1,make sure that Seq 2 
//                source interrupt is enabled.
//                External Trigger -> 0,Indicates software trigger 
//                (Conversion starts once this function is executed)
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubExtTrg: 
//                External Trigger : defines external trigger.
// @Parameters    ubEnIntr: 
//                Enable Source Interrupt : defines source interrupt
// @Parameters    ubRFill: 
//                Refill : defines the refill
// @Parameters    ubChannelNum: 
//                Channel number : Name of the Request Channel Number (0 - 
//                15)- see macros defined in the header file
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

void ADC0_vStartSeq2ReqChNum(ubyte ubExtTrg, ubyte ubEnIntr, ubyte ubRFill, ubyte ubChannelNum)
{

    uword uwVal = 0;
    if (ubExtTrg == 1)
    {
        uwVal = 0x0080;
    }
    if (ubEnIntr == 1)
    {
        uwVal = uwVal + 0x0040;
    }
    if (ubRFill == 1)
    {
        uwVal = uwVal + 0x0020;
    }
    uwVal = uwVal + (ubChannelNum & 0x001f);

  ADC0_QINR2 = uwVal; // requested channel 

} //  End of function ADC0_vStartSeq2ReqChNum


//****************************************************************************
// @Function      void ADC0_vAliasChNum(ubyte ubAliasChNum, ubyte ubReqChNum) 
//
//----------------------------------------------------------------------------
// @Description   This function assigns attributes of channel0 or channel1 to 
//                the requested channel
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubAliasChNum: 
//                AliasChNum: defines the Alias channel number (Ch0 and Ch1)
// @Parameters    ubReqChNum: 
//                ReqChNum: defines the channel number to be aliased
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

void ADC0_vAliasChNum(ubyte ubAliasChNum, ubyte ubReqChNum)
{

      if(ubAliasChNum == 0) 
      {
         ADC0_ALR0 = (ADC0_ALR0 & (0xff00)) | (uword)ubReqChNum; // updates requested channel to ALIAS 0 bit field 

      }
      else if(ubAliasChNum == 1) 
      {
         ADC0_ALR0 = (ADC0_ALR0 & (0x00ff)) | ((uword)ubReqChNum << 8); // updates requested channel to ALIAS 1 bit field 

      }
      else
      {
          //Do nothing 

      }

} //  End of function ADC0_vAliasChNum

//****************************************************************************
// @Function      void ADC0_vSeqSoftTrigger(ubyte ubSrc) 
//
//----------------------------------------------------------------------------
// @Description   This function sets TREV bit for the requested sequential 
//                source in the register QMRx.
//                It is applicable only when sequential source conversion 
//                request API is called with 'ubExtTrg' parameter set to '1'.
//                This API helps in triggering (software) all the sequential 
//                conversion requests which are waiting for external hardware 
//                trigger to occur.
//                Ex- ubSrc = ADC0_SOURCE_0,for sequential source 0
//                    ubSrc = ADC0_SOURCE_2,for sequential source 2
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubSrc: 
//                ubSrc: defines the sequential source number
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

void ADC0_vSeqSoftTrigger(ubyte ubSrc)
{

      if(ubSrc == 0) // sequential source 0
      {
         while(!(ADC0_QSR0 & 0x0020))  //Do until queue is empty
         {
            ADC0_QMR0 |= 0x0200; // software trigger event 
         }

      }

      else if(ubSrc == 2) //sequential source 2
      {
         while(!(ADC0_QSR2 & 0x0020))  //Do until queue is empty
         {
            ADC0_QMR2 |= 0x0200; // software trigger event 
         }

      }

      else
      {
          //Do nothing 

      }

} //  End of function ADC0_vSeqSoftTrigger



// USER CODE BEGIN (ADC0_General,10)

// USER CODE END

