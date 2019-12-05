//****************************************************************************
// @Module        Capture / Compare Unit 61 (CCU61)
// @Filename      CCU61.h
// @Project       P300.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC2365B-40F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains all function prototypes and macros for 
//                the CCU61 module.
//
//----------------------------------------------------------------------------
// @Date          2019-11-04 16:14:55
//
//****************************************************************************

// USER CODE BEGIN (CCU61_Header,1)

// USER CODE END



#ifndef _CCU61_H_
#define _CCU61_H_

//****************************************************************************
// @Project Includes
//****************************************************************************

// USER CODE BEGIN (CCU61_Header,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (CCU61_Header,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

//   This parameter identifies CCU61 timer 12
#define CCU61_TIMER_12 12

//   This parameter identifies CCU61 timer 13
#define CCU61_TIMER_13 13

//   This parameter identifies CCU61 channel 0
#define CCU61_CHANNEL_0 0

//   This parameter identifies CCU61 channel 1
#define CCU61_CHANNEL_1 1

//   This parameter identifies CCU61 channel 2
#define CCU61_CHANNEL_2 2

//   This parameter identifies CCU61 channel 3
#define CCU61_CHANNEL_3 3


// USER CODE BEGIN (CCU61_Header,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (CCU61_Header,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (CCU61_Header,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (CCU61_Header,7)

// USER CODE END


//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************

void CCU61_vInit(void);


// USER CODE BEGIN (CCU61_Header,8)

// USER CODE END


//****************************************************************************
// @Macro         CCU61_vStartTmr(TimerNr) 
//
//----------------------------------------------------------------------------
// @Description   This macro starts the selected CCU61 timer. The timer 
//                continues counting from where it stopped. 
//                
//                The following definitions for TimerNr are available: 
//                CCU61_TIMER_12
//                CCU61_TIMER_13
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    TimerNr: 
//                Name of the CCU61 timer to be started
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

#define CCU61_vStartTmr(TimerNr) CCU61_vStartTmr_##TimerNr()
#define CCU61_vStartTmr_CCU61_TIMER_12() CCU61_TCTR4 |= 0x0002
#define CCU61_vStartTmr_CCU61_TIMER_13() CCU61_TCTR4 |= 0x0200


//****************************************************************************
// @Macro         CCU61_vStopTmr(TimerNr) 
//
//----------------------------------------------------------------------------
// @Description   This macro stops the selected CCU61 timer. The content of 
//                the timer register remains unchanged. 
//                
//                The following definitions for TimerNr are available: 
//                CCU61_TIMER_12
//                CCU61_TIMER_13
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    TimerNr: 
//                Name of the CCU61 timer to be stopped
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

#define CCU61_vStopTmr(TimerNr) CCU61_vStopTmr_##TimerNr()
#define CCU61_vStopTmr_CCU61_TIMER_12() CCU61_TCTR4 |= 0x0001
#define CCU61_vStopTmr_CCU61_TIMER_13() CCU61_TCTR4 |= 0x0100


//****************************************************************************
// @Macro         CCU61_vSetTmrPeriod(TimerNr, Value) 
//
//----------------------------------------------------------------------------
// @Description   This macro loads the period register of the selected CCU61 
//                timer.
//                
//                Note: Call the macro CCU61_vEnableShadowTransfer() to 
//                enable the shadow transfer.
//                The following definitions for TimerNr are available: 
//                CCU61_TIMER_12
//                CCU61_TIMER_13
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    TimerNr: 
//                Name of the CCU61 timer to be used
// @Parameters    Value: 
//                16-bit Value with which the CCU61 timer reload register is 
//                to be loaded
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

#define CCU61_vSetTmrPeriod(TimerNr, Value) CCU61_vSetTmrPeriod_##TimerNr(Value)
#define CCU61_vSetTmrPeriod_CCU61_TIMER_12(Value) CCU61_T12PR = Value
#define CCU61_vSetTmrPeriod_CCU61_TIMER_13(Value) CCU61_T13PR = Value


//****************************************************************************
// @Macro         CCU61_uwSetTmrCounter(TimerNr, Value) 
//
//----------------------------------------------------------------------------
// @Description   This macro loads the selected CCU61 timer counter register 
//                with the parameter Value . It is possible to use this macro 
//                only if the selected timer is stopped.
//                
//                The following definitions for TimerNr are available: 
//                CCU61_TIMER_12
//                CCU61_TIMER_13
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    TimerNr: 
//                Name of the CCU61 timer to be used
// @Parameters    Value: 
//                16-bit value with which the CCU61 counter register is to be 
//                loaded
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

#define CCU61_uwSetTmrCounter(TimerNr, Value) CCU61_uwSetTmrCounter_##TimerNr(Value)
#define CCU61_uwSetTmrCounter_CCU61_TIMER_12(Value) CCU61_T12 = Value
#define CCU61_uwSetTmrCounter_CCU61_TIMER_13(Value) CCU61_T13 = Value


//****************************************************************************
// @Macro         CCU61_vEnableShadowTransfer(TimerNr) 
//
//----------------------------------------------------------------------------
// @Description   This macro enables the transfer from the shadow registers 
//                to the actual CCU61 registers.
//                
//                The following definitions for TimerNr are available: 
//                CCU61_TIMER_12
//                CCU61_TIMER_13
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    TimerNr: 
//                Name of the CCU61 timer to be used
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

#define CCU61_vEnableShadowTransfer(TimerNr) CCU61_vEnableShadowTransfer_##TimerNr()
#define CCU61_vEnableShadowTransfer_CCU61_TIMER_12() CCU61_TCTR4 |= 0x0040
#define CCU61_vEnableShadowTransfer_CCU61_TIMER_13() CCU61_TCTR4 |= 0x4000


//****************************************************************************
// @Macro         CCU61_vLoadChannelShadowRegister(ChName, Value) 
//
//----------------------------------------------------------------------------
// @Description   This macro loads the selected CCU61 channel shadow register 
//                with the parameter Value. 
//                
//                The following definitions are available for RegName: 
//                CCU61_CHANNEL_0 .. CCU61_CHANNEL_3 (see @Defines in header 
//                file)
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ChName: 
//                Name of the CCU61 channel to be loaded
// @Parameters    Value: 
//                16-bit Value with which the CCU61 shadow register is to be 
//                loaded
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

#define CCU61_vLoadChannelShadowRegister(ChName, Value) CCU61_vLoadChannelShadowRegister_##ChName(Value)
#define CCU61_vLoadChannelShadowRegister_CCU61_CHANNEL_0(Value) CCU61_CC60SR = Value
#define CCU61_vLoadChannelShadowRegister_CCU61_CHANNEL_1(Value) CCU61_CC61SR = Value
#define CCU61_vLoadChannelShadowRegister_CCU61_CHANNEL_2(Value) CCU61_CC62SR = Value
#define CCU61_vLoadChannelShadowRegister_CCU61_CHANNEL_3(Value) CCU61_CC63SR = Value


//****************************************************************************
// @Macro         CCU61_uwGetChannelShadowRegister(ChName) 
//
//----------------------------------------------------------------------------
// @Description   This macro returns the content of the CCU61 capture/compare 
//                shadow register of the selected channel.
//                
//                The following definitions are available for RegName: 
//                CCU61_CHANNEL_0 .. CCU61_CHANNEL_3 (see @Defines in header 
//                file)
//
//----------------------------------------------------------------------------
// @Returnvalue   Current 16-bit value of the CCU61 shadow register
//
//----------------------------------------------------------------------------
// @Parameters    ChName: 
//                Name of the CCU61 channel to be readed
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

#define CCU61_uwGetChannelShadowRegister(ChName) CCU61_uwGetChannelShadowRegister_##ChName()
#define CCU61_uwGetChannelShadowRegister_CCU61_CHANNEL_0() CCU61_CC60SR
#define CCU61_uwGetChannelShadowRegister_CCU61_CHANNEL_1() CCU61_CC61SR
#define CCU61_uwGetChannelShadowRegister_CCU61_CHANNEL_2() CCU61_CC62SR
#define CCU61_uwGetChannelShadowRegister_CCU61_CHANNEL_3() CCU61_CC63SR


//****************************************************************************
// @Interrupt Vectors
//****************************************************************************

#define CCU61_NodeI0_INT    0x34


// USER CODE BEGIN (CCU61_Header,9)

// USER CODE END


#endif  // ifndef _CCU61_H_
