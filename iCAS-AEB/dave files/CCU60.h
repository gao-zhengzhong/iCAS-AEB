//****************************************************************************
// @Module        Capture / Compare Unit 60 (CCU60)
// @Filename      CCU60.h
// @Project       P300.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC2365B-40F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains all function prototypes and macros for 
//                the CCU60 module.
//
//----------------------------------------------------------------------------
// @Date          2019-11-04 16:14:55
//
//****************************************************************************

// USER CODE BEGIN (CCU60_Header,1)

// USER CODE END



#ifndef _CCU60_H_
#define _CCU60_H_

//****************************************************************************
// @Project Includes
//****************************************************************************

// USER CODE BEGIN (CCU60_Header,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (CCU60_Header,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

//   This parameter identifies CCU60 timer 12
#define CCU60_TIMER_12 12

//   This parameter identifies CCU60 timer 13
#define CCU60_TIMER_13 13

//   This parameter identifies CCU60 channel 0
#define CCU60_CHANNEL_0 0

//   This parameter identifies CCU60 channel 1
#define CCU60_CHANNEL_1 1

//   This parameter identifies CCU60 channel 2
#define CCU60_CHANNEL_2 2

//   This parameter identifies CCU60 channel 3
#define CCU60_CHANNEL_3 3


// USER CODE BEGIN (CCU60_Header,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (CCU60_Header,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (CCU60_Header,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (CCU60_Header,7)

// USER CODE END


//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************

void CCU60_vInit(void);


// USER CODE BEGIN (CCU60_Header,8)

// USER CODE END


//****************************************************************************
// @Macro         CCU60_vStartTmr(TimerNr) 
//
//----------------------------------------------------------------------------
// @Description   This macro starts the selected CCU60 timer. The timer 
//                continues counting from where it stopped. 
//                
//                The following definitions for TimerNr are available: 
//                CCU60_TIMER_12
//                CCU60_TIMER_13
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    TimerNr: 
//                Name of the CCU60 timer to be started
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

#define CCU60_vStartTmr(TimerNr) CCU60_vStartTmr_##TimerNr()
#define CCU60_vStartTmr_CCU60_TIMER_12() CCU60_TCTR4 |= 0x0002
#define CCU60_vStartTmr_CCU60_TIMER_13() CCU60_TCTR4 |= 0x0200


//****************************************************************************
// @Macro         CCU60_vStopTmr(TimerNr) 
//
//----------------------------------------------------------------------------
// @Description   This macro stops the selected CCU60 timer. The content of 
//                the timer register remains unchanged. 
//                
//                The following definitions for TimerNr are available: 
//                CCU60_TIMER_12
//                CCU60_TIMER_13
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    TimerNr: 
//                Name of the CCU60 timer to be stopped
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

#define CCU60_vStopTmr(TimerNr) CCU60_vStopTmr_##TimerNr()
#define CCU60_vStopTmr_CCU60_TIMER_12() CCU60_TCTR4 |= 0x0001
#define CCU60_vStopTmr_CCU60_TIMER_13() CCU60_TCTR4 |= 0x0100


//****************************************************************************
// @Macro         CCU60_vResetTmr(TimerNr) 
//
//----------------------------------------------------------------------------
// @Description   This macro sets the selected CCU60 timer counter register 
//                to zero. Timer is not stopped.
//                
//                The following definitions for TimerNr are available: 
//                CCU60_TIMER_12
//                CCU60_TIMER_13
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    TimerNr: 
//                Name of the CCU60 timer to be cleared
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

#define CCU60_vResetTmr(TimerNr) CCU60_vResetTmr_##TimerNr()
#define CCU60_vResetTmr_CCU60_TIMER_12() CCU60_TCTR4 |= 0x0004
#define CCU60_vResetTmr_CCU60_TIMER_13() CCU60_TCTR4 |= 0x0400


//****************************************************************************
// @Macro         CCU60_vSetTmrPeriod(TimerNr, Value) 
//
//----------------------------------------------------------------------------
// @Description   This macro loads the period register of the selected CCU60 
//                timer.
//                
//                Note: Call the macro CCU60_vEnableShadowTransfer() to 
//                enable the shadow transfer.
//                The following definitions for TimerNr are available: 
//                CCU60_TIMER_12
//                CCU60_TIMER_13
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    TimerNr: 
//                Name of the CCU60 timer to be used
// @Parameters    Value: 
//                16-bit Value with which the CCU60 timer reload register is 
//                to be loaded
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

#define CCU60_vSetTmrPeriod(TimerNr, Value) CCU60_vSetTmrPeriod_##TimerNr(Value)
#define CCU60_vSetTmrPeriod_CCU60_TIMER_12(Value) CCU60_T12PR = Value
#define CCU60_vSetTmrPeriod_CCU60_TIMER_13(Value) CCU60_T13PR = Value


//****************************************************************************
// @Macro         CCU60_uwGetTmrCounter(TimerNr) 
//
//----------------------------------------------------------------------------
// @Description   This macro returns the contens of the selected CCU60 timer 
//                counter register.
//                
//                The following definitions for TimerNr are available: 
//                CCU60_TIMER_12
//                CCU60_TIMER_13
//
//----------------------------------------------------------------------------
// @Returnvalue   16-bit counter value
//
//----------------------------------------------------------------------------
// @Parameters    TimerNr: 
//                Name of the CCU60 timer to be used
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

#define CCU60_uwGetTmrCounter(TimerNr) CCU60_uwGetTmrCounter_##TimerNr()
#define CCU60_uwGetTmrCounter_CCU60_TIMER_12() CCU60_T12
#define CCU60_uwGetTmrCounter_CCU60_TIMER_13() CCU60_T13


//****************************************************************************
// @Macro         CCU60_uwSetTmrCounter(TimerNr, Value) 
//
//----------------------------------------------------------------------------
// @Description   This macro loads the selected CCU60 timer counter register 
//                with the parameter Value . It is possible to use this macro 
//                only if the selected timer is stopped.
//                
//                The following definitions for TimerNr are available: 
//                CCU60_TIMER_12
//                CCU60_TIMER_13
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    TimerNr: 
//                Name of the CCU60 timer to be used
// @Parameters    Value: 
//                16-bit value with which the CCU60 counter register is to be 
//                loaded
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

#define CCU60_uwSetTmrCounter(TimerNr, Value) CCU60_uwSetTmrCounter_##TimerNr(Value)
#define CCU60_uwSetTmrCounter_CCU60_TIMER_12(Value) CCU60_T12 = Value
#define CCU60_uwSetTmrCounter_CCU60_TIMER_13(Value) CCU60_T13 = Value


//****************************************************************************
// @Macro         CCU60_vSetDeadTimePeriod(ubValue) 
//
//----------------------------------------------------------------------------
// @Description   This macro loads the counter of the deat time register.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubValue: 
//                counter value (ubValue = 0x01 .. 0x3F)
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

#define CCU60_vSetDeadTimePeriod(ubValue) CCU60_T12DTC = (CCU60_T12DTC & ~(uword)0x003F) | ubValue


//****************************************************************************
// @Macro         CCU60_vEnableShadowTransfer(TimerNr) 
//
//----------------------------------------------------------------------------
// @Description   This macro enables the transfer from the shadow registers 
//                to the actual CCU60 registers.
//                
//                The following definitions for TimerNr are available: 
//                CCU60_TIMER_12
//                CCU60_TIMER_13
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    TimerNr: 
//                Name of the CCU60 timer to be used
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

#define CCU60_vEnableShadowTransfer(TimerNr) CCU60_vEnableShadowTransfer_##TimerNr()
#define CCU60_vEnableShadowTransfer_CCU60_TIMER_12() CCU60_TCTR4 |= 0x0040
#define CCU60_vEnableShadowTransfer_CCU60_TIMER_13() CCU60_TCTR4 |= 0x4000


//****************************************************************************
// @Macro         CCU60_vLoadChannelShadowRegister(ChName, Value) 
//
//----------------------------------------------------------------------------
// @Description   This macro loads the selected CCU60 channel shadow register 
//                with the parameter Value. 
//                
//                The following definitions are available for RegName: 
//                CCU60_CHANNEL_0 .. CCU60_CHANNEL_3 (see @Defines in header 
//                file)
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ChName: 
//                Name of the CCU60 channel to be loaded
// @Parameters    Value: 
//                16-bit Value with which the CCU60 shadow register is to be 
//                loaded
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

#define CCU60_vLoadChannelShadowRegister(ChName, Value) CCU60_vLoadChannelShadowRegister_##ChName(Value)
#define CCU60_vLoadChannelShadowRegister_CCU60_CHANNEL_0(Value) CCU60_CC60SR = Value
#define CCU60_vLoadChannelShadowRegister_CCU60_CHANNEL_1(Value) CCU60_CC61SR = Value
#define CCU60_vLoadChannelShadowRegister_CCU60_CHANNEL_2(Value) CCU60_CC62SR = Value
#define CCU60_vLoadChannelShadowRegister_CCU60_CHANNEL_3(Value) CCU60_CC63SR = Value


//****************************************************************************
// @Macro         CCU60_uwGetChannelShadowRegister(ChName) 
//
//----------------------------------------------------------------------------
// @Description   This macro returns the content of the CCU60 capture/compare 
//                shadow register of the selected channel.
//                
//                The following definitions are available for RegName: 
//                CCU60_CHANNEL_0 .. CCU60_CHANNEL_3 (see @Defines in header 
//                file)
//
//----------------------------------------------------------------------------
// @Returnvalue   Current 16-bit value of the CCU60 shadow register
//
//----------------------------------------------------------------------------
// @Parameters    ChName: 
//                Name of the CCU60 channel to be readed
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

#define CCU60_uwGetChannelShadowRegister(ChName) CCU60_uwGetChannelShadowRegister_##ChName()
#define CCU60_uwGetChannelShadowRegister_CCU60_CHANNEL_0() CCU60_CC60SR
#define CCU60_uwGetChannelShadowRegister_CCU60_CHANNEL_1() CCU60_CC61SR
#define CCU60_uwGetChannelShadowRegister_CCU60_CHANNEL_2() CCU60_CC62SR
#define CCU60_uwGetChannelShadowRegister_CCU60_CHANNEL_3() CCU60_CC63SR


//****************************************************************************
// @Macro         CCU60_uwGetChannelRegister(ChName) 
//
//----------------------------------------------------------------------------
// @Description   This macro returns the content of the CCU60 capture/compare 
//                register of the selected channel.
//                
//                The following definitions are available for RegName: 
//                CCU60_CHANNEL_0 .. CCU60_CHANNEL_3 (see @Defines in header 
//                file)
//
//----------------------------------------------------------------------------
// @Returnvalue   Current 16-bit value of the CCU60 register
//
//----------------------------------------------------------------------------
// @Parameters    ChName: 
//                Name of the CCU60 channel to be readed
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

#define CCU60_uwGetChannelRegister(ChName) CCU60_uwGetChannelRegister_##ChName()
#define CCU60_uwGetChannelRegister_CCU60_CHANNEL_0() CCU60_CC60R
#define CCU60_uwGetChannelRegister_CCU60_CHANNEL_1() CCU60_CC61R
#define CCU60_uwGetChannelRegister_CCU60_CHANNEL_2() CCU60_CC62R
#define CCU60_uwGetChannelRegister_CCU60_CHANNEL_3() CCU60_CC63R


//****************************************************************************
// @Macro         CCU60_vSetStatusBit(ChName) 
//
//----------------------------------------------------------------------------
// @Description   This macro sets the capture / compare modifikation status 
//                bit of the selected CCU60 channel. 
//                The following definitions are available for ChName: 
//                CCU60_CHANNEL_0 .. CCU60_CHANNEL_3 (see @Defines in header 
//                file)
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ChName: 
//                Name of the CCU60 channel to be used
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

#define CCU60_vSetStatusBit(ChName) CCU60_vSetStatusBit_##ChName()
#define CCU60_vSetStatusBit_CCU60_CHANNEL_0() CCU60_CMPMODIF = 0x0001
#define CCU60_vSetStatusBit_CCU60_CHANNEL_1() CCU60_CMPMODIF = 0x0002
#define CCU60_vSetStatusBit_CCU60_CHANNEL_2() CCU60_CMPMODIF = 0x0004
#define CCU60_vSetStatusBit_CCU60_CHANNEL_3() CCU60_CMPMODIF = 0x0040


//****************************************************************************
// @Macro         CCU60_vResetStatusBit(ChName) 
//
//----------------------------------------------------------------------------
// @Description   This macro resets the capture / compare modifikation status 
//                bit of the selected CCU60 channel. 
//                The following definitions are available for ChName: 
//                CCU60_CHANNEL_0 .. CCU60_CHANNEL_3 (see @Defines in header 
//                file)
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ChName: 
//                Name of the CCU60 channel to be used
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

#define CCU60_vResetStatusBit(ChName) CCU60_vResetStatusBit_##ChName()
#define CCU60_vResetStatusBit_CCU60_CHANNEL_0() CCU60_CMPMODIF = 0x0100
#define CCU60_vResetStatusBit_CCU60_CHANNEL_1() CCU60_CMPMODIF = 0x0200
#define CCU60_vResetStatusBit_CCU60_CHANNEL_2() CCU60_CMPMODIF = 0x0400
#define CCU60_vResetStatusBit_CCU60_CHANNEL_3() CCU60_CMPMODIF = 0x4000


//****************************************************************************
// @Interrupt Vectors
//****************************************************************************

#define CCU60_NodeI2_INT    0x32
#define CCU60_NodeI3_INT    0x33


// USER CODE BEGIN (CCU60_Header,9)

// USER CODE END


#endif  // ifndef _CCU60_H_
