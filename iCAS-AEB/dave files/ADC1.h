//****************************************************************************
// @Module        Analog / Digital Converter (ADC1)
// @Filename      ADC1.h
// @Project       P300.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC2365B-40F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains all function prototypes and macros for 
//                the ADC1 module.
//
//----------------------------------------------------------------------------
// @Date          2019-11-04 16:14:55
//
//****************************************************************************

// USER CODE BEGIN (ADC1_Header,1)

// USER CODE END


#ifndef _ADC1_H_

#define _ADC1_H_

//****************************************************************************
// @Project Includes
//****************************************************************************

// USER CODE BEGIN (ADC1_Header,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (ADC1_Header,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

//   This parameter identifies ADC1 analog channel 0
#define ADC1_ANA_0 0

//   This parameter identifies ADC1 analog channel 1
#define ADC1_ANA_1 1

//   This parameter identifies ADC1 analog channel 2
#define ADC1_ANA_2 2

//   This parameter identifies ADC1 analog channel 3
#define ADC1_ANA_3 3

//   This parameter identifies ADC1 analog channel 4
#define ADC1_ANA_4 4

//   This parameter identifies ADC1 analog channel 5
#define ADC1_ANA_5 5

//   This parameter identifies ADC1 analog channel 6
#define ADC1_ANA_6 6

//   This parameter identifies ADC1 analog channel 7
#define ADC1_ANA_7 7

//   This parameter identifies ADC1 -Source 0
#define ADC1_SOURCE_0 0

//   This parameter identifies ADC1 -Source 1
#define ADC1_SOURCE_1 1

//   This parameter identifies ADC1 -Source 2
#define ADC1_SOURCE_2 2


// USER CODE BEGIN (ADC1_Header,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************


// USER CODE BEGIN (ADC1_Header,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (ADC1_Header,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (ADC1_Header,7)

// USER CODE END


//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************

void ADC1_vInit(void);
void ADC1_vStartSeq0ReqChNum(ubyte ubExtTrg, ubyte ubEnIntr, ubyte ubRFill, ubyte ubChannelNum);
void ADC1_vStartSeq2ReqChNum(ubyte ubExtTrg, ubyte ubEnIntr, ubyte ubRFill, ubyte ubChannelNum);
void ADC1_vAliasChNum(ubyte ubAliasChNum, ubyte ubReqChNum);


// USER CODE BEGIN (ADC1_Header,8)

// USER CODE END


//****************************************************************************
// @Macro         uword ADC1_uwBusy() 
//
//----------------------------------------------------------------------------
// @Description   This macro checks the conversion state of the current ADC 
//                channel by examination of the busy flag (BUSY).It returns 
//                '1' while a conversion is running.
//
//----------------------------------------------------------------------------
// @Returnvalue   Returns a 1 if A/D converter is active, else 0
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

#define ADC1_uwBusy()  (ADC1_GLOBSTR & 0x0001)

//****************************************************************************
// @Macro         void ADC1_vSetSeq2QueueFlush() 
//
//----------------------------------------------------------------------------
// @Description   This macro Flushes the Sequential source 2 Queue
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

#define ADC1_vSetSeq2QueueFlush()  (ADC1_QMR2 |= 0x0400)

//****************************************************************************
// @Macro         uword ADC1_uwGetSeq2QueueEmpty() 
//
//----------------------------------------------------------------------------
// @Description   This macro checks whether Sequential source 2 Queue depth 
//                is empty or not
//
//----------------------------------------------------------------------------
// @Returnvalue   Returns '1' if sequential 2 queue is empty, else '0'
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

#define ADC1_uwGetSeq2QueueEmpty()  ((ADC1_QSR2 & 0x0020) >> 5)

//****************************************************************************
// @Macro         uword ADC1_uwGetResultData(RegNum) 
//
//----------------------------------------------------------------------------
// @Description   This macro returns the left aligned, 10-bit result data of 
//                the last conversion from requested result register
//                Ex- RegNum = RESULT_REG_0,for Result register 0
//                    RegNum = RESULT_REG_2,for Result register 2
//                  - For 8 bit resolution user has to right shift the result
//                    by 2 bits as shown below
//                    uwResult = ADC0_uwGetResultData(RESULT_REG_0);
//                    uwResult >>= 2;
//                NOTE -
//                If this macro is called before ADC1_uwGetResultChNum macro 
//                for the same result register then channel information will 
//                be lost.So always call ADC1_uwGetResultChNum macro before 
//                this macro if channel information is required.
//
//----------------------------------------------------------------------------
// @Returnvalue   Returns result data from requested result register
//
//----------------------------------------------------------------------------
// @Parameters    RegNum: 
//                RegNum: defines the result register number
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

#define ADC1_uwGetResultData(RegNum)  (ADC1_uwGetResultData_##RegNum)
#define ADC1_uwGetResultData_RESULT_REG_0 ((ADC1_RCR0 & 0x1000) ? ((ADC1_RESR0 & 0x0fff) >> 2) : 0)
#define ADC1_uwGetResultData_RESULT_REG_1 ((ADC1_RCR1 & 0x1000) ? ((ADC1_RESR1 & 0x0fff) >> 2) : 0)
#define ADC1_uwGetResultData_RESULT_REG_2 ((ADC1_RCR2 & 0x1000) ? ((ADC1_RESR2 & 0x0fff) >> 2) : 0)
#define ADC1_uwGetResultData_RESULT_REG_3 ((ADC1_RCR3 & 0x1000) ? ((ADC1_RESR3 & 0x0fff) >> 2) : 0)
#define ADC1_uwGetResultData_RESULT_REG_4 ((ADC1_RCR4 & 0x1000) ? ((ADC1_RESR4 & 0x0fff) >> 2) : 0)
#define ADC1_uwGetResultData_RESULT_REG_5 ((ADC1_RCR5 & 0x1000) ? ((ADC1_RESR5 & 0x0fff) >> 2) : 0)
#define ADC1_uwGetResultData_RESULT_REG_6 ((ADC1_RCR6 & 0x1000) ? ((ADC1_RESR6 & 0x0fff) >> 2) : 0)
#define ADC1_uwGetResultData_RESULT_REG_7 ((ADC1_RCR7 & 0x1000) ? ((ADC1_RESR7 & 0x0fff) >> 2) : 0)

//****************************************************************************
// @Macro         ubyte ADC1_ubGetResultChNum(RegNum) 
//
//----------------------------------------------------------------------------
// @Description   This macro returns channel number from requested result 
//                register
//                Ex- RegNum = RESULT_REG_0,for Result register 0
//                    RegNum = RESULT_REG_2,for Result register 2
//                NOTE -
//                If only channel information is required then make sure that 
//                you call ADC1_vClearValidBit macro after reading the 
//                channel number.
//
//----------------------------------------------------------------------------
// @Returnvalue   Returns channel number from requested result register
//
//----------------------------------------------------------------------------
// @Parameters    RegNum: 
//                RegNum: defines the result register number
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

#define ADC1_ubGetResultChNum(RegNum)  (ADC1_ubGetResultChNum_##RegNum)
#define ADC1_ubGetResultChNum_RESULT_REG_0 ((ADC1_RCR0 & 0x1000) ? ((ADC1_RESRV0 & 0xf000) >> 12) : 0)
#define ADC1_ubGetResultChNum_RESULT_REG_1 ((ADC1_RCR1 & 0x1000) ? ((ADC1_RESRV1 & 0xf000) >> 12) : 0)
#define ADC1_ubGetResultChNum_RESULT_REG_2 ((ADC1_RCR2 & 0x1000) ? ((ADC1_RESRV2 & 0xf000) >> 12) : 0)
#define ADC1_ubGetResultChNum_RESULT_REG_3 ((ADC1_RCR3 & 0x1000) ? ((ADC1_RESRV3 & 0xf000) >> 12) : 0)
#define ADC1_ubGetResultChNum_RESULT_REG_4 ((ADC1_RCR4 & 0x1000) ? ((ADC1_RESRV4 & 0xf000) >> 12) : 0)
#define ADC1_ubGetResultChNum_RESULT_REG_5 ((ADC1_RCR5 & 0x1000) ? ((ADC1_RESRV5 & 0xf000) >> 12) : 0)
#define ADC1_ubGetResultChNum_RESULT_REG_6 ((ADC1_RCR6 & 0x1000) ? ((ADC1_RESRV6 & 0xf000) >> 12) : 0)
#define ADC1_ubGetResultChNum_RESULT_REG_7 ((ADC1_RCR7 & 0x1000) ? ((ADC1_RESRV7 & 0xf000) >> 12) : 0)

//****************************************************************************
// @Macro         uword ADC1_uwResultValid(RegNum) 
//
//----------------------------------------------------------------------------
// @Description   This macro indicates that the contents of the result 
//                register x is valid or not valid.
//
//----------------------------------------------------------------------------
// @Returnvalue   1 for valid and 0 for not valid
//
//----------------------------------------------------------------------------
// @Parameters    RegNum: 
//                RegNum: defines the result register number
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

#define ADC1_uwResultValid(RegNum)  (ADC1_uwResultValid_##RegNum)
#define ADC1_uwResultValid_RESULT_REG_0 ((ADC1_RCR0 & 0x1000) && 0x1000) 
#define ADC1_uwResultValid_RESULT_REG_1 ((ADC1_RCR1 & 0x1000) && 0x1000) 
#define ADC1_uwResultValid_RESULT_REG_2 ((ADC1_RCR2 & 0x1000) && 0x1000) 
#define ADC1_uwResultValid_RESULT_REG_3 ((ADC1_RCR3 & 0x1000) && 0x1000) 
#define ADC1_uwResultValid_RESULT_REG_4 ((ADC1_RCR4 & 0x1000) && 0x1000) 
#define ADC1_uwResultValid_RESULT_REG_5 ((ADC1_RCR5 & 0x1000) && 0x1000) 
#define ADC1_uwResultValid_RESULT_REG_6 ((ADC1_RCR6 & 0x1000) && 0x1000) 
#define ADC1_uwResultValid_RESULT_REG_7 ((ADC1_RCR7 & 0x1000) && 0x1000) 

//****************************************************************************
// @Macro         ubyte ADC1_ubGetResultStatusChNum() 
//
//----------------------------------------------------------------------------
// @Description   This macro returns the channel number of latest result 
//                register(view without extension 'V') that has been read out.
//                
//                NOTE : This macro has to be called only after reading the 
//                channel Result data.
//
//----------------------------------------------------------------------------
// @Returnvalue   Channel number
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

#define ADC1_ubGetResultStatusChNum()  ( ADC1_RSSR & 0x001F )
//****************************************************************************
// @Macro         void ADC1_vClearValidBit(RegNum) 
//
//----------------------------------------------------------------------------
// @Description   This macro clears valid bit flag for the requested result 
//                register
//                Ex- RegNum = RESULT_REG_0,for Result register 0
//                    RegNum = RESULT_REG_2,for Result register 2
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    RegNum: 
//                RegNum: defines the result register number
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

#define ADC1_vClearValidBit(RegNum)  (ADC1_vClearValidBit_##RegNum)
#define ADC1_vClearValidBit_RESULT_REG_0 (ADC1_VFR = 0x0001)
#define ADC1_vClearValidBit_RESULT_REG_1 (ADC1_VFR = 0x0002)
#define ADC1_vClearValidBit_RESULT_REG_2 (ADC1_VFR = 0x0004)
#define ADC1_vClearValidBit_RESULT_REG_3 (ADC1_VFR = 0x0008)
#define ADC1_vClearValidBit_RESULT_REG_4 (ADC1_VFR = 0x0010)
#define ADC1_vClearValidBit_RESULT_REG_5 (ADC1_VFR = 0x0020)
#define ADC1_vClearValidBit_RESULT_REG_6 (ADC1_VFR = 0x0040)
#define ADC1_vClearValidBit_RESULT_REG_7 (ADC1_VFR = 0x0080)

//****************************************************************************
// @Interrupt Vectors
//****************************************************************************


// USER CODE BEGIN (ADC1_Header,9)

// USER CODE END


#endif  // ifndef _ADC1_H_
