//****************************************************************************
// @Module        MultiCAN Module (CAN)
// @Filename      CAN.c
// @Project       P300.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC2365B-40F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains functions that use the CAN module.
//
//----------------------------------------------------------------------------
// @Date          2019-11-04 16:14:55
//
//****************************************************************************



// USER CODE BEGIN (CAN_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.h"

// USER CODE BEGIN (CAN_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (CAN_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (CAN_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (CAN_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (CAN_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************


// USER CODE BEGIN (CAN_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (CAN_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (CAN_General,9)

// USER CODE END


//****************************************************************************
// @Function      void CAN_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the CAN function 
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

void CAN_vInit(void)
{
  volatile unsigned int uwTemp;

  // USER CODE BEGIN (Init,2)

  // USER CODE END

  ///  -----------------------------------------------------------------------
  ///  Configuration of Kernel State Configuration Register:
  ///  -----------------------------------------------------------------------
  ///  - Enable the CAN module(MODEN)
  ///  - Enable Bit Protection for MODEN

    MCAN_KSCCFG  =  0x0003;      // load Kernel State Configuration Register

    uwTemp       =  MCAN_KSCCFG; // dummy read to avoid pipeline effects

  ///  -----------------------------------------------------------------------
  ///  Configuration of the Module Clock:
  ///  -----------------------------------------------------------------------
  ///  - the CAN module clock = 40.00 MHz
  ///  - Normal divider mode selected

    CAN_FDRL     =  0x43FE;      // load Fractional Divider Register

    uwTemp       =  CAN_FDRL;    // dummy read to avoid pipeline effects

  ///  -----------------------------------------------------------------------
  ///  Panel Control
  ///  -----------------------------------------------------------------------
  ///  - wait until Panel has finished the initialisation

    while(CAN_PANCTRL & CAN_PANCTR_BUSY){ // wait until Panel has finished 
                                          // the initialisation
      }                         

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAN Node 0:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Node 0:
  ///  - set INIT and CCE

    CAN_NCR0     =  0x0041;      // load NODE 0 control register[15-0]

  ///  - load NODE 0 interrupt pointer register

    CAN_NIPR0    =  0x0000;      // load NIPR0_LECINP, ALINP, CFCINP and TRINP

  ///  Configuration of the used CAN Port Pins:
  ///  - Loop-back mode is disabled
  ///  - P2.0 is used for CAN0 Receive input(RXDC0C)
  ///  - P2.1 is used for CAN0 Transmit output(TXDC0C)

  P2_IOCR01 = 0x0090;    //set direction register
    CAN_NPCR0    =  0x0002;      // load node0 port control register


  ///  Configuration of the Node 0 Baud Rate:
  ///  - required baud rate = 500.000 kbaud
  ///  - real baud rate     = 500.000 kbaud
  ///  - sample point       = 60.00 %
  ///  - there are 5 time quanta before sample point
  ///  - there are 4 time quanta after sample point
  ///  - the (re)synchronization jump width is 2 time quanta

    CAN_NBTR0L   =  0x3447;      // load NBTR0_DIV8, TSEG2, TSEG1, SJW and BRP

  ///  Configuration of the Node 0 Error Counter:
  ///  - the error warning threshold value (warning level) is 96

    CAN_NECNT0H = 0x0060;        // load NECNT0_EWRNLVL register
    CAN_NECNT0L = 0x0000;       

  ///  Configuration of the Frame Counter:
  ///  - Frame Counter Mode: the counter is incremented upon the reception 
  ///    and transmission of frames
  ///  - frame counter: 0x0000

    CAN_NFCR0H = 0x0000;         // load NFCR0_CFCOV, CFCIE, CFMOD, CFSEL
    CAN_NFCR0L = 0x0000;         // load NFCR0_CFC

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAN Node 1:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Node 1:
  ///  - set INIT and CCE

    CAN_NCR1     =  0x0041;      // load NODE 1 control register[15-0]

  ///  - load NODE 1 interrupt pointer register

    CAN_NIPR1    =  0x0000;      // load NIPR1_LECINP, ALINP, CFCINP and TRINP

  ///  Configuration of the used CAN Port Pins:
  ///  - Loop-back mode is disabled
  ///  - P2.4 is used for CAN1 Receive input(RXDC1A)
  ///  - P2.2 is used for CAN1 Transmit output(TXDC1B)

  P2_IOCR02 = 0x0090;    //set direction register
    CAN_NPCR1    =  0x0000;      // load node1 port control register


  ///  Configuration of the Node 1 Baud Rate:
  ///  - required baud rate = 500.000 kbaud
  ///  - real baud rate     = 500.000 kbaud
  ///  - sample point       = 60.00 %
  ///  - there are 5 time quanta before sample point
  ///  - there are 4 time quanta after sample point
  ///  - the (re)synchronization jump width is 2 time quanta

    CAN_NBTR1L   =  0x3447;      // load NBTR1_DIV8, TSEG2, TSEG1, SJW and BRP

  ///  Configuration of the Node 1 Error Counter:
  ///  - the error warning threshold value (warning level) is 96

    CAN_NECNT1H = 0x0060;        // load NECNT1_EWRNLVL register
    CAN_NECNT1L = 0x0000;       

  ///  Configuration of the Frame Counter:
  ///  - Frame Counter Mode: the counter is incremented upon the reception 
  ///    and transmission of frames
  ///  - frame counter: 0x0000

    CAN_NFCR1H = 0x0000;         // load NFCR1_CFCOV, CFCIE, CFMOD, CFSEL
    CAN_NFCR1L = 0x0000;         // load NFCR1_CFC

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAN Node 2:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Node 2:
  ///  - set INIT and CCE

    CAN_NCR2     =  0x0041;      // load NODE 2 control register[15-0]

  ///  -----------------------------------------------------------------------
  ///  Configuration of the CAN Message Object List Structure:
  ///  -----------------------------------------------------------------------

  ///  Allocate MOs for list 1:

    SetListCommand(0x0100,0x0002);  // MO0 for list 1 (Node 0)

    SetListCommand(0x0102,0x0002);  // MO2 for list 1 (Node 0)

    SetListCommand(0x0103,0x0002);  // MO3 for list 1 (Node 0)

    SetListCommand(0x0104,0x0002);  // MO4 for list 1 (Node 0)

    SetListCommand(0x0105,0x0002);  // MO5 for list 1 (Node 0)

    SetListCommand(0x0106,0x0002);  // MO6 for list 1 (Node 0)

    SetListCommand(0x0107,0x0002);  // MO7 for list 1 (Node 0)

    SetListCommand(0x0108,0x0002);  // MO8 for list 1 (Node 0)

    SetListCommand(0x0109,0x0002);  // MO9 for list 1 (Node 0)

  ///  Allocate MOs for list 2:

    SetListCommand(0x0201,0x0002);  // MO1 for list 2 (Node 1)

    SetListCommand(0x020A,0x0002);  // MO10 for list 2 (Node 1)

    SetListCommand(0x020B,0x0002);  // MO11 for list 2 (Node 1)

    SetListCommand(0x020C,0x0002);  // MO12 for list 2 (Node 1)

    SetListCommand(0x020D,0x0002);  // MO13 for list 2 (Node 1)

    SetListCommand(0x020E,0x0002);  // MO14 for list 2 (Node 1)

    SetListCommand(0x020F,0x0002);  // MO15 for list 2 (Node 1)

  ///  -----------------------------------------------------------------------
  ///  Configuration of the CAN Message Objects 0 - 63:
  ///  -----------------------------------------------------------------------
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 0:
  ///  MO 0 is named as : Message Object 0
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 0 :
  ///  - message object 0 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR0H = 0x00A0;        // load MO0 control register high
    CAN_MOCTR0L = 0x0000;        // load MO0 control register low

  ///  Configuration of Message Object 0 Arbitration:
  ///  - priority class 2; transmit acceptance filtering is based on the CAN 
  ///    identifier
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x6F0

    CAN_MOAR0H = 0x9BC0;         // load MO0 arbitration register high
    CAN_MOAR0L = 0x0000;         // load MO0 arbitration register low

  ///  Configuration of Message Object 0 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x000

    CAN_MOAMR0H = 0x2000;        // load MO0 acceptance mask register high
    CAN_MOAMR0L = 0x0000;        // load MO0 acceptance mask register low

  ///  Configuration of Message Object 0 interrupt pointer:
  ///  - use message pending register 0 bit position 0
  ///  - receive interrupt node pointer: MultiCAN SRN 0

    CAN_MOIPR0H = 0x0000;        // load MO0 interrupt pointer register high
    CAN_MOIPR0L = 0x0000;        // load MO0 interrupt pointer register low

  ///  Configuration of Message Object 0 FIFO/Gateway pointer:

    CAN_MOFGPR0H = 0x0000;       // load MO0 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR0L = 0x0000;       // load MO0 FIFO/gateway pointer register low


  ///  Configuration of Message Object 0 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes
  ///  - enable receive interrupt; bit RXPND is set after successful 
  ///    reception of a frame

    CAN_MOFCR0H = 0x0801;        // load MO0 function control register high
    CAN_MOFCR0L = 0x0000;        // load MO0 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 1:
  ///  MO 1 is named as : Message Object 1
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 1 :
  ///  - message object 1 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR1H = 0x00A0;        // load MO1 control register high
    CAN_MOCTR1L = 0x0000;        // load MO1 control register low

  ///  Configuration of Message Object 1 Arbitration:
  ///  - priority class 2; transmit acceptance filtering is based on the CAN 
  ///    identifier
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x6F1

    CAN_MOAR1H = 0x9BC4;         // load MO1 arbitration register high
    CAN_MOAR1L = 0x0000;         // load MO1 arbitration register low

  ///  Configuration of Message Object 1 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x000

    CAN_MOAMR1H = 0x2000;        // load MO1 acceptance mask register high
    CAN_MOAMR1L = 0x0000;        // load MO1 acceptance mask register low

  ///  Configuration of Message Object 1 interrupt pointer:
  ///  - use message pending register 0 bit position 1

    CAN_MOIPR1H = 0x0000;        // load MO1 interrupt pointer register high
    CAN_MOIPR1L = 0x0100;        // load MO1 interrupt pointer register low

  ///  Configuration of Message Object 1 FIFO/Gateway pointer:

    CAN_MOFGPR1H = 0x0000;       // load MO1 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR1L = 0x0000;       // load MO1 FIFO/gateway pointer register low


  ///  Configuration of Message Object 1 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR1H = 0x0800;        // load MO1 function control register high
    CAN_MOFCR1L = 0x0000;        // load MO1 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 2:
  ///  MO 2 is named as : Message Object 2
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 2 :
  ///  - message object 2 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR2H = 0x0EA8;        // load MO2 control register high
    CAN_MOCTR2L = 0x0000;        // load MO2 control register low

  ///  Configuration of Message Object 2 Arbitration:
  ///  - priority class 2; transmit acceptance filtering is based on the CAN 
  ///    identifier
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x035

    CAN_MOAR2H = 0x80D4;         // load MO2 arbitration register high
    CAN_MOAR2L = 0x0000;         // load MO2 arbitration register low

  ///  Configuration of Message Object 2 Data:

    CAN_MODATA2HH = 0x0000;      // load MO2 Data Bytes(DB7 & DB6)
    CAN_MODATA2HL = 0x0000;      // load MO2 Data Bytes(DB5 & DB4)
    CAN_MODATA2LH = 0x0000;      // load MO2 Data Bytes(DB3 & DB2)
    CAN_MODATA2LL = 0x0000;      // load MO2 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 2 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7F1

    CAN_MOAMR2H = 0x3FC4;        // load MO2 acceptance mask register high
    CAN_MOAMR2L = 0x0000;        // load MO2 acceptance mask register low

  ///  Configuration of Message Object 2 interrupt pointer:
  ///  - use message pending register 0 bit position 2

    CAN_MOIPR2H = 0x0000;        // load MO2 interrupt pointer register high
    CAN_MOIPR2L = 0x0200;        // load MO2 interrupt pointer register low

  ///  Configuration of Message Object 2 FIFO/Gateway pointer:

    CAN_MOFGPR2H = 0x0000;       // load MO2 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR2L = 0x0000;       // load MO2 FIFO/gateway pointer register low


  ///  Configuration of Message Object 2 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR2H = 0x0800;        // load MO2 function control register high
    CAN_MOFCR2L = 0x0000;        // load MO2 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 3:
  ///  MO 3 is named as : Message Object 3
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 3 :
  ///  - message object 3 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR3H = 0x00A0;        // load MO3 control register high
    CAN_MOCTR3L = 0x0000;        // load MO3 control register low

  ///  Configuration of Message Object 3 Arbitration:
  ///  - priority class 2; transmit acceptance filtering is based on the CAN 
  ///    identifier
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x035

    CAN_MOAR3H = 0x80D4;         // load MO3 arbitration register high
    CAN_MOAR3L = 0x0000;         // load MO3 arbitration register low

  ///  Configuration of Message Object 3 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR3H = 0x3FFF;        // load MO3 acceptance mask register high
    CAN_MOAMR3L = 0xFFFF;        // load MO3 acceptance mask register low

  ///  Configuration of Message Object 3 interrupt pointer:
  ///  - use message pending register 0 bit position 3

    CAN_MOIPR3H = 0x0000;        // load MO3 interrupt pointer register high
    CAN_MOIPR3L = 0x0300;        // load MO3 interrupt pointer register low

  ///  Configuration of Message Object 3 FIFO/Gateway pointer:

    CAN_MOFGPR3H = 0x0000;       // load MO3 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR3L = 0x0000;       // load MO3 FIFO/gateway pointer register low


  ///  Configuration of Message Object 3 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR3H = 0x0800;        // load MO3 function control register high
    CAN_MOFCR3L = 0x0000;        // load MO3 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 4:
  ///  MO 4 is named as : Message Object 4
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 4 :
  ///  - message object 4 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR4H = 0x0EA8;        // load MO4 control register high
    CAN_MOCTR4L = 0x0000;        // load MO4 control register low

  ///  Configuration of Message Object 4 Arbitration:
  ///  - priority class 2; transmit acceptance filtering is based on the CAN 
  ///    identifier
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x000

    CAN_MOAR4H = 0x8000;         // load MO4 arbitration register high
    CAN_MOAR4L = 0x0000;         // load MO4 arbitration register low

  ///  Configuration of Message Object 4 Data:

    CAN_MODATA4HH = 0x0000;      // load MO4 Data Bytes(DB7 & DB6)
    CAN_MODATA4HL = 0x0000;      // load MO4 Data Bytes(DB5 & DB4)
    CAN_MODATA4LH = 0x0000;      // load MO4 Data Bytes(DB3 & DB2)
    CAN_MODATA4LL = 0x0000;      // load MO4 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 4 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR4H = 0x3FFF;        // load MO4 acceptance mask register high
    CAN_MOAMR4L = 0xFFFF;        // load MO4 acceptance mask register low

  ///  Configuration of Message Object 4 interrupt pointer:
  ///  - use message pending register 0 bit position 4

    CAN_MOIPR4H = 0x0000;        // load MO4 interrupt pointer register high
    CAN_MOIPR4L = 0x0400;        // load MO4 interrupt pointer register low

  ///  Configuration of Message Object 4 FIFO/Gateway pointer:

    CAN_MOFGPR4H = 0x0000;       // load MO4 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR4L = 0x0000;       // load MO4 FIFO/gateway pointer register low


  ///  Configuration of Message Object 4 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR4H = 0x0800;        // load MO4 function control register high
    CAN_MOFCR4L = 0x0000;        // load MO4 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 5:
  ///  MO 5 is named as : Message Object 5
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 5 :
  ///  - message object 5 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR5H = 0x0EA8;        // load MO5 control register high
    CAN_MOCTR5L = 0x0000;        // load MO5 control register low

  ///  Configuration of Message Object 5 Arbitration:
  ///  - priority class 2; transmit acceptance filtering is based on the CAN 
  ///    identifier
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x000

    CAN_MOAR5H = 0x8000;         // load MO5 arbitration register high
    CAN_MOAR5L = 0x0000;         // load MO5 arbitration register low

  ///  Configuration of Message Object 5 Data:

    CAN_MODATA5HH = 0x0000;      // load MO5 Data Bytes(DB7 & DB6)
    CAN_MODATA5HL = 0x0000;      // load MO5 Data Bytes(DB5 & DB4)
    CAN_MODATA5LH = 0x0000;      // load MO5 Data Bytes(DB3 & DB2)
    CAN_MODATA5LL = 0x0000;      // load MO5 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 5 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR5H = 0x3FFF;        // load MO5 acceptance mask register high
    CAN_MOAMR5L = 0xFFFF;        // load MO5 acceptance mask register low

  ///  Configuration of Message Object 5 interrupt pointer:
  ///  - use message pending register 0 bit position 5

    CAN_MOIPR5H = 0x0000;        // load MO5 interrupt pointer register high
    CAN_MOIPR5L = 0x0500;        // load MO5 interrupt pointer register low

  ///  Configuration of Message Object 5 FIFO/Gateway pointer:

    CAN_MOFGPR5H = 0x0000;       // load MO5 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR5L = 0x0000;       // load MO5 FIFO/gateway pointer register low


  ///  Configuration of Message Object 5 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR5H = 0x0800;        // load MO5 function control register high
    CAN_MOFCR5L = 0x0000;        // load MO5 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 6:
  ///  MO 6 is named as : Message Object 6
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 6 :
  ///  - message object 6 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR6H = 0x0EA8;        // load MO6 control register high
    CAN_MOCTR6L = 0x0000;        // load MO6 control register low

  ///  Configuration of Message Object 6 Arbitration:
  ///  - priority class 2; transmit acceptance filtering is based on the CAN 
  ///    identifier
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x000

    CAN_MOAR6H = 0x8000;         // load MO6 arbitration register high
    CAN_MOAR6L = 0x0000;         // load MO6 arbitration register low

  ///  Configuration of Message Object 6 Data:

    CAN_MODATA6HH = 0x0000;      // load MO6 Data Bytes(DB7 & DB6)
    CAN_MODATA6HL = 0x0000;      // load MO6 Data Bytes(DB5 & DB4)
    CAN_MODATA6LH = 0x0000;      // load MO6 Data Bytes(DB3 & DB2)
    CAN_MODATA6LL = 0x0000;      // load MO6 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 6 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR6H = 0x3FFF;        // load MO6 acceptance mask register high
    CAN_MOAMR6L = 0xFFFF;        // load MO6 acceptance mask register low

  ///  Configuration of Message Object 6 interrupt pointer:
  ///  - use message pending register 0 bit position 6

    CAN_MOIPR6H = 0x0000;        // load MO6 interrupt pointer register high
    CAN_MOIPR6L = 0x0600;        // load MO6 interrupt pointer register low

  ///  Configuration of Message Object 6 FIFO/Gateway pointer:

    CAN_MOFGPR6H = 0x0000;       // load MO6 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR6L = 0x0000;       // load MO6 FIFO/gateway pointer register low


  ///  Configuration of Message Object 6 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 0 valid data bytes

    CAN_MOFCR6H = 0x0000;        // load MO6 function control register high
    CAN_MOFCR6L = 0x0000;        // load MO6 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 7:
  ///  MO 7 is named as : Message Object 7
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 7 :
  ///  - message object 7 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR7H = 0x0EA8;        // load MO7 control register high
    CAN_MOCTR7L = 0x0000;        // load MO7 control register low

  ///  Configuration of Message Object 7 Arbitration:
  ///  - priority class 2; transmit acceptance filtering is based on the CAN 
  ///    identifier
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x000

    CAN_MOAR7H = 0x8000;         // load MO7 arbitration register high
    CAN_MOAR7L = 0x0000;         // load MO7 arbitration register low

  ///  Configuration of Message Object 7 Data:

    CAN_MODATA7HH = 0x0000;      // load MO7 Data Bytes(DB7 & DB6)
    CAN_MODATA7HL = 0x0000;      // load MO7 Data Bytes(DB5 & DB4)
    CAN_MODATA7LH = 0x0000;      // load MO7 Data Bytes(DB3 & DB2)
    CAN_MODATA7LL = 0x0000;      // load MO7 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 7 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR7H = 0x3FFF;        // load MO7 acceptance mask register high
    CAN_MOAMR7L = 0xFFFF;        // load MO7 acceptance mask register low

  ///  Configuration of Message Object 7 interrupt pointer:
  ///  - use message pending register 0 bit position 7

    CAN_MOIPR7H = 0x0000;        // load MO7 interrupt pointer register high
    CAN_MOIPR7L = 0x0700;        // load MO7 interrupt pointer register low

  ///  Configuration of Message Object 7 FIFO/Gateway pointer:

    CAN_MOFGPR7H = 0x0000;       // load MO7 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR7L = 0x0000;       // load MO7 FIFO/gateway pointer register low


  ///  Configuration of Message Object 7 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 0 valid data bytes

    CAN_MOFCR7H = 0x0000;        // load MO7 function control register high
    CAN_MOFCR7L = 0x0000;        // load MO7 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 8:
  ///  MO 8 is named as : Message Object 8
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 8 :
  ///  - message object 8 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR8H = 0x0EA8;        // load MO8 control register high
    CAN_MOCTR8L = 0x0000;        // load MO8 control register low

  ///  Configuration of Message Object 8 Arbitration:
  ///  - priority class 2; transmit acceptance filtering is based on the CAN 
  ///    identifier
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x000

    CAN_MOAR8H = 0x8000;         // load MO8 arbitration register high
    CAN_MOAR8L = 0x0000;         // load MO8 arbitration register low

  ///  Configuration of Message Object 8 Data:

    CAN_MODATA8HH = 0x0000;      // load MO8 Data Bytes(DB7 & DB6)
    CAN_MODATA8HL = 0x0000;      // load MO8 Data Bytes(DB5 & DB4)
    CAN_MODATA8LH = 0x0000;      // load MO8 Data Bytes(DB3 & DB2)
    CAN_MODATA8LL = 0x0000;      // load MO8 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 8 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR8H = 0x3FFF;        // load MO8 acceptance mask register high
    CAN_MOAMR8L = 0xFFFF;        // load MO8 acceptance mask register low

  ///  Configuration of Message Object 8 interrupt pointer:
  ///  - use message pending register 0 bit position 8

    CAN_MOIPR8H = 0x0000;        // load MO8 interrupt pointer register high
    CAN_MOIPR8L = 0x0800;        // load MO8 interrupt pointer register low

  ///  Configuration of Message Object 8 FIFO/Gateway pointer:

    CAN_MOFGPR8H = 0x0000;       // load MO8 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR8L = 0x0000;       // load MO8 FIFO/gateway pointer register low


  ///  Configuration of Message Object 8 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 0 valid data bytes

    CAN_MOFCR8H = 0x0000;        // load MO8 function control register high
    CAN_MOFCR8L = 0x0000;        // load MO8 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 9:
  ///  MO 9 is named as : Message Object 9
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 9 :
  ///  - message object 9 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR9H = 0x0EA8;        // load MO9 control register high
    CAN_MOCTR9L = 0x0000;        // load MO9 control register low

  ///  Configuration of Message Object 9 Arbitration:
  ///  - priority class 2; transmit acceptance filtering is based on the CAN 
  ///    identifier
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x000

    CAN_MOAR9H = 0x8000;         // load MO9 arbitration register high
    CAN_MOAR9L = 0x0000;         // load MO9 arbitration register low

  ///  Configuration of Message Object 9 Data:

    CAN_MODATA9HH = 0x0000;      // load MO9 Data Bytes(DB7 & DB6)
    CAN_MODATA9HL = 0x0000;      // load MO9 Data Bytes(DB5 & DB4)
    CAN_MODATA9LH = 0x0000;      // load MO9 Data Bytes(DB3 & DB2)
    CAN_MODATA9LL = 0x0000;      // load MO9 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 9 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR9H = 0x3FFF;        // load MO9 acceptance mask register high
    CAN_MOAMR9L = 0xFFFF;        // load MO9 acceptance mask register low

  ///  Configuration of Message Object 9 interrupt pointer:
  ///  - use message pending register 0 bit position 9

    CAN_MOIPR9H = 0x0000;        // load MO9 interrupt pointer register high
    CAN_MOIPR9L = 0x0900;        // load MO9 interrupt pointer register low

  ///  Configuration of Message Object 9 FIFO/Gateway pointer:

    CAN_MOFGPR9H = 0x0000;       // load MO9 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR9L = 0x0000;       // load MO9 FIFO/gateway pointer register low


  ///  Configuration of Message Object 9 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 0 valid data bytes

    CAN_MOFCR9H = 0x0000;        // load MO9 function control register high
    CAN_MOFCR9L = 0x0000;        // load MO9 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 10:
  ///  MO 10 is named as : Message Object 10
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 10 :
  ///  - message object 10 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR10H = 0x0EA8;       // load MO10 control register high
    CAN_MOCTR10L = 0x0000;       // load MO10 control register low

  ///  Configuration of Message Object 10 Arbitration:
  ///  - priority class 2; transmit acceptance filtering is based on the CAN 
  ///    identifier
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x6F1

    CAN_MOAR10H = 0x9BC4;        // load MO10 arbitration register high
    CAN_MOAR10L = 0x0000;        // load MO10 arbitration register low

  ///  Configuration of Message Object 10 Data:

    CAN_MODATA10HH = 0x0000;     // load MO10 Data Bytes(DB7 & DB6)
    CAN_MODATA10HL = 0x0000;     // load MO10 Data Bytes(DB5 & DB4)
    CAN_MODATA10LH = 0x0000;     // load MO10 Data Bytes(DB3 & DB2)
    CAN_MODATA10LL = 0x0000;     // load MO10 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 10 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR10H = 0x3FFF;       // load MO10 acceptance mask register high
    CAN_MOAMR10L = 0xFFFF;       // load MO10 acceptance mask register low

  ///  Configuration of Message Object 10 interrupt pointer:
  ///  - use message pending register 0 bit position 10

    CAN_MOIPR10H = 0x0000;       // load MO10 interrupt pointer register high
    CAN_MOIPR10L = 0x0A00;       // load MO10 interrupt pointer register low

  ///  Configuration of Message Object 10 FIFO/Gateway pointer:

    CAN_MOFGPR10H = 0x0000;      // load MO10 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR10L = 0x0000;      // load MO10 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 10 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR10H = 0x0800;       // load MO10 function control register high
    CAN_MOFCR10L = 0x0000;       // load MO10 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 11:
  ///  MO 11 is named as : Message Object 11
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 11 :
  ///  - message object 11 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR11H = 0x0EA8;       // load MO11 control register high
    CAN_MOCTR11L = 0x0000;       // load MO11 control register low

  ///  Configuration of Message Object 11 Arbitration:
  ///  - priority class 2; transmit acceptance filtering is based on the CAN 
  ///    identifier
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x000

    CAN_MOAR11H = 0x8000;        // load MO11 arbitration register high
    CAN_MOAR11L = 0x0000;        // load MO11 arbitration register low

  ///  Configuration of Message Object 11 Data:

    CAN_MODATA11HH = 0x0000;     // load MO11 Data Bytes(DB7 & DB6)
    CAN_MODATA11HL = 0x0000;     // load MO11 Data Bytes(DB5 & DB4)
    CAN_MODATA11LH = 0x0000;     // load MO11 Data Bytes(DB3 & DB2)
    CAN_MODATA11LL = 0x0000;     // load MO11 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 11 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR11H = 0x3FFF;       // load MO11 acceptance mask register high
    CAN_MOAMR11L = 0xFFFF;       // load MO11 acceptance mask register low

  ///  Configuration of Message Object 11 interrupt pointer:
  ///  - use message pending register 0 bit position 11

    CAN_MOIPR11H = 0x0000;       // load MO11 interrupt pointer register high
    CAN_MOIPR11L = 0x0B00;       // load MO11 interrupt pointer register low

  ///  Configuration of Message Object 11 FIFO/Gateway pointer:

    CAN_MOFGPR11H = 0x0000;      // load MO11 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR11L = 0x0000;      // load MO11 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 11 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 0 valid data bytes

    CAN_MOFCR11H = 0x0000;       // load MO11 function control register high
    CAN_MOFCR11L = 0x0000;       // load MO11 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 12:
  ///  MO 12 is named as : Message Object 12
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 12 :
  ///  - message object 12 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR12H = 0x0EA8;       // load MO12 control register high
    CAN_MOCTR12L = 0x0000;       // load MO12 control register low

  ///  Configuration of Message Object 12 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x000

    CAN_MOAR12H = 0x4000;        // load MO12 arbitration register high
    CAN_MOAR12L = 0x0000;        // load MO12 arbitration register low

  ///  Configuration of Message Object 12 Data:

    CAN_MODATA12HH = 0x0000;     // load MO12 Data Bytes(DB7 & DB6)
    CAN_MODATA12HL = 0x0000;     // load MO12 Data Bytes(DB5 & DB4)
    CAN_MODATA12LH = 0x0000;     // load MO12 Data Bytes(DB3 & DB2)
    CAN_MODATA12LL = 0x0000;     // load MO12 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 12 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR12H = 0x3FFF;       // load MO12 acceptance mask register high
    CAN_MOAMR12L = 0xFFFF;       // load MO12 acceptance mask register low

  ///  Configuration of Message Object 12 interrupt pointer:
  ///  - use message pending register 0 bit position 12

    CAN_MOIPR12H = 0x0000;       // load MO12 interrupt pointer register high
    CAN_MOIPR12L = 0x0C00;       // load MO12 interrupt pointer register low

  ///  Configuration of Message Object 12 FIFO/Gateway pointer:

    CAN_MOFGPR12H = 0x0000;      // load MO12 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR12L = 0x0000;      // load MO12 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 12 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR12H = 0x0800;       // load MO12 function control register high
    CAN_MOFCR12L = 0x0000;       // load MO12 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 13:
  ///  MO 13 is named as : Message Object 13
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 13 :
  ///  - message object 13 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR13H = 0x0EA8;       // load MO13 control register high
    CAN_MOCTR13L = 0x0000;       // load MO13 control register low

  ///  Configuration of Message Object 13 Arbitration:
  ///  - priority class 2; transmit acceptance filtering is based on the CAN 
  ///    identifier
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x000

    CAN_MOAR13H = 0x8000;        // load MO13 arbitration register high
    CAN_MOAR13L = 0x0000;        // load MO13 arbitration register low

  ///  Configuration of Message Object 13 Data:

    CAN_MODATA13HH = 0x0000;     // load MO13 Data Bytes(DB7 & DB6)
    CAN_MODATA13HL = 0x0000;     // load MO13 Data Bytes(DB5 & DB4)
    CAN_MODATA13LH = 0x0000;     // load MO13 Data Bytes(DB3 & DB2)
    CAN_MODATA13LL = 0x0000;     // load MO13 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 13 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR13H = 0x3FFF;       // load MO13 acceptance mask register high
    CAN_MOAMR13L = 0xFFFF;       // load MO13 acceptance mask register low

  ///  Configuration of Message Object 13 interrupt pointer:
  ///  - use message pending register 0 bit position 13

    CAN_MOIPR13H = 0x0000;       // load MO13 interrupt pointer register high
    CAN_MOIPR13L = 0x0D00;       // load MO13 interrupt pointer register low

  ///  Configuration of Message Object 13 FIFO/Gateway pointer:

    CAN_MOFGPR13H = 0x0000;      // load MO13 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR13L = 0x0000;      // load MO13 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 13 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 0 valid data bytes

    CAN_MOFCR13H = 0x0000;       // load MO13 function control register high
    CAN_MOFCR13L = 0x0000;       // load MO13 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 14:
  ///  MO 14 is named as : Message Object 14
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 14 :
  ///  - message object 14 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR14H = 0x0EA8;       // load MO14 control register high
    CAN_MOCTR14L = 0x0000;       // load MO14 control register low

  ///  Configuration of Message Object 14 Arbitration:
  ///  - priority class 2; transmit acceptance filtering is based on the CAN 
  ///    identifier
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x000

    CAN_MOAR14H = 0x8000;        // load MO14 arbitration register high
    CAN_MOAR14L = 0x0000;        // load MO14 arbitration register low

  ///  Configuration of Message Object 14 Data:

    CAN_MODATA14HH = 0x0000;     // load MO14 Data Bytes(DB7 & DB6)
    CAN_MODATA14HL = 0x0000;     // load MO14 Data Bytes(DB5 & DB4)
    CAN_MODATA14LH = 0x0000;     // load MO14 Data Bytes(DB3 & DB2)
    CAN_MODATA14LL = 0x0000;     // load MO14 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 14 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR14H = 0x3FFF;       // load MO14 acceptance mask register high
    CAN_MOAMR14L = 0xFFFF;       // load MO14 acceptance mask register low

  ///  Configuration of Message Object 14 interrupt pointer:
  ///  - use message pending register 0 bit position 14

    CAN_MOIPR14H = 0x0000;       // load MO14 interrupt pointer register high
    CAN_MOIPR14L = 0x0E00;       // load MO14 interrupt pointer register low

  ///  Configuration of Message Object 14 FIFO/Gateway pointer:

    CAN_MOFGPR14H = 0x0000;      // load MO14 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR14L = 0x0000;      // load MO14 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 14 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR14H = 0x0800;       // load MO14 function control register high
    CAN_MOFCR14L = 0x0000;       // load MO14 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 15:
  ///  MO 15 is named as : Message Object 15
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 15 :
  ///  - message object 15 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR15H = 0x0EA8;       // load MO15 control register high
    CAN_MOCTR15L = 0x0000;       // load MO15 control register low

  ///  Configuration of Message Object 15 Arbitration:
  ///  - priority class 2; transmit acceptance filtering is based on the CAN 
  ///    identifier
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x000

    CAN_MOAR15H = 0x8000;        // load MO15 arbitration register high
    CAN_MOAR15L = 0x0000;        // load MO15 arbitration register low

  ///  Configuration of Message Object 15 Data:

    CAN_MODATA15HH = 0x0000;     // load MO15 Data Bytes(DB7 & DB6)
    CAN_MODATA15HL = 0x0000;     // load MO15 Data Bytes(DB5 & DB4)
    CAN_MODATA15LH = 0x0000;     // load MO15 Data Bytes(DB3 & DB2)
    CAN_MODATA15LL = 0x0000;     // load MO15 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 15 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR15H = 0x3FFF;       // load MO15 acceptance mask register high
    CAN_MOAMR15L = 0xFFFF;       // load MO15 acceptance mask register low

  ///  Configuration of Message Object 15 interrupt pointer:
  ///  - use message pending register 0 bit position 15

    CAN_MOIPR15H = 0x0000;       // load MO15 interrupt pointer register high
    CAN_MOIPR15L = 0x0F00;       // load MO15 interrupt pointer register low

  ///  Configuration of Message Object 15 FIFO/Gateway pointer:

    CAN_MOFGPR15H = 0x0000;      // load MO15 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR15L = 0x0000;      // load MO15 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 15 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR15H = 0x0800;       // load MO15 function control register high
    CAN_MOFCR15L = 0x0000;       // load MO15 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 16:
  ///  -----------------------------------------------------------------------
  ///  - message object 16 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 17:
  ///  -----------------------------------------------------------------------
  ///  - message object 17 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 18:
  ///  -----------------------------------------------------------------------
  ///  - message object 18 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 19:
  ///  -----------------------------------------------------------------------
  ///  - message object 19 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 20:
  ///  -----------------------------------------------------------------------
  ///  - message object 20 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 21:
  ///  -----------------------------------------------------------------------
  ///  - message object 21 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 22:
  ///  -----------------------------------------------------------------------
  ///  - message object 22 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 23:
  ///  -----------------------------------------------------------------------
  ///  - message object 23 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 24:
  ///  -----------------------------------------------------------------------
  ///  - message object 24 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 25:
  ///  -----------------------------------------------------------------------
  ///  - message object 25 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 26:
  ///  -----------------------------------------------------------------------
  ///  - message object 26 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 27:
  ///  -----------------------------------------------------------------------
  ///  - message object 27 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 28:
  ///  -----------------------------------------------------------------------
  ///  - message object 28 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 29:
  ///  -----------------------------------------------------------------------
  ///  - message object 29 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 30:
  ///  -----------------------------------------------------------------------
  ///  - message object 30 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 31:
  ///  -----------------------------------------------------------------------
  ///  - message object 31 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 32:
  ///  -----------------------------------------------------------------------
  ///  - message object 32 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 33:
  ///  -----------------------------------------------------------------------
  ///  - message object 33 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 34:
  ///  -----------------------------------------------------------------------
  ///  - message object 34 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 35:
  ///  -----------------------------------------------------------------------
  ///  - message object 35 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 36:
  ///  -----------------------------------------------------------------------
  ///  - message object 36 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 37:
  ///  -----------------------------------------------------------------------
  ///  - message object 37 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 38:
  ///  -----------------------------------------------------------------------
  ///  - message object 38 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 39:
  ///  -----------------------------------------------------------------------
  ///  - message object 39 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 40:
  ///  -----------------------------------------------------------------------
  ///  - message object 40 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 41:
  ///  -----------------------------------------------------------------------
  ///  - message object 41 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 42:
  ///  -----------------------------------------------------------------------
  ///  - message object 42 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 43:
  ///  -----------------------------------------------------------------------
  ///  - message object 43 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 44:
  ///  -----------------------------------------------------------------------
  ///  - message object 44 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 45:
  ///  -----------------------------------------------------------------------
  ///  - message object 45 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 46:
  ///  -----------------------------------------------------------------------
  ///  - message object 46 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 47:
  ///  -----------------------------------------------------------------------
  ///  - message object 47 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 48:
  ///  -----------------------------------------------------------------------
  ///  - message object 48 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 49:
  ///  -----------------------------------------------------------------------
  ///  - message object 49 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 50:
  ///  -----------------------------------------------------------------------
  ///  - message object 50 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 51:
  ///  -----------------------------------------------------------------------
  ///  - message object 51 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 52:
  ///  -----------------------------------------------------------------------
  ///  - message object 52 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 53:
  ///  -----------------------------------------------------------------------
  ///  - message object 53 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 54:
  ///  -----------------------------------------------------------------------
  ///  - message object 54 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 55:
  ///  -----------------------------------------------------------------------
  ///  - message object 55 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 56:
  ///  -----------------------------------------------------------------------
  ///  - message object 56 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 57:
  ///  -----------------------------------------------------------------------
  ///  - message object 57 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 58:
  ///  -----------------------------------------------------------------------
  ///  - message object 58 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 59:
  ///  -----------------------------------------------------------------------
  ///  - message object 59 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 60:
  ///  -----------------------------------------------------------------------
  ///  - message object 60 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 61:
  ///  -----------------------------------------------------------------------
  ///  - message object 61 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 62:
  ///  -----------------------------------------------------------------------
  ///  - message object 62 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 63:
  ///  -----------------------------------------------------------------------
  ///  - message object 63 is not valid

  ///  -----------------------------------------------------------------------
  ///  Configuration of Service Request Nodes 0 - 15:
  ///  -----------------------------------------------------------------------
  ///  SRN0 service request node configuration:
  ///  - SRN0 interrupt priority level (ILVL) = 11
  ///  - SRN0 interrupt group level (GLVL) = 0
  ///  - SRN0 group priority extension (GPX) = 0

  CAN_0IC        =  0x006C;     


  //   -----------------------------------------------------------------------
  //   Start the CAN Nodes:
  //   -----------------------------------------------------------------------

  ///  - ------------- CAN_NCR0 ----------------------------------------------

    CAN_NCR0 &= ~ (uword) 0x0041; // reset INIT and CCE
  ///  - ------------- CAN_NCR1 ----------------------------------------------

    CAN_NCR1 &= ~ (uword) 0x0041; // reset INIT and CCE



  // USER CODE BEGIN (Init,3)

  // USER CODE END

} //  End of function CAN_vInit

//****************************************************************************
// @Function      void CAN_vTransmit(ubyte ubObjNr) 
//
//----------------------------------------------------------------------------
// @Description   This function triggers the CAN controller to send the 
//                selected message.
//                If the selected message object is a TRANSMIT OBJECT then 
//                this function triggers the sending of a data frame. If 
//                however the selected message object is a RECEIVE OBJECT 
//                this function triggers the sending of a remote frame.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the message object (0-63)
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

// USER CODE BEGIN (Transmit,1)

// USER CODE END

void CAN_vTransmit(ubyte ubObjNr)
{

  CAN_HWOBJ[ubObjNr].uwMOCTRH = 0x0720;  // set TXRQ,TXEN0,TXEN1,MSGVAL

} //  End of function CAN_vTransmit

//****************************************************************************
// @Function      void CAN_vConfigMsgObj(ubyte ubObjNr, stCAN_SWObj *pstObj) 
//
//----------------------------------------------------------------------------
// @Description   This function sets up the message objects. This includes 
//                the 8 data bytes, the identifier (11- or 29-bit), the 
//                acceptance mask (11- or 29-bit), the data number (0-8 
//                bytes), the DIR-bit (transmit or receive object), the 
//                IDE-bit (standard or extended  identifier), the MIDE-bit 
//                (accepts reception of both frames or matching IDE-bit 
//                frame) and  the frame counter value. 
//                The message is not sent; for this the function 
//                CAN_vTransmit must be called.
//                
//                The structure of the SW message object is defined in the 
//                header file CAN.h (see stCAN_SWObj).
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the message object to be configured (0-63)
// @Parameters    *pstObj: 
//                Pointer on a message object
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

// USER CODE BEGIN (ConfigMsgObj,1)

// USER CODE END

void CAN_vConfigMsgObj(ubyte ubObjNr, stCAN_SWObj *pstObj)
{

  ubyte i;

  CAN_HWOBJ[ubObjNr].uwMOCTRH = 0x0000;
  CAN_HWOBJ[ubObjNr].uwMOCTRL = 0x0020;        // reset MSGVAL

  //----- Configure identifier ---------------------------------------
  CAN_HWOBJ[ubObjNr].uwMOARH  &= ~(uword)0x3FFF;

  if(pstObj->ubMOCfg & 0x20)                   // if extended identifier
  {
    //----- Configure extended identifier(29bit) ----------------------
    CAN_HWOBJ[ubObjNr].uwMOARH  |= (uword)(0x2000 | ((pstObj->ulID >> 16) & 0x1FFF));
    CAN_HWOBJ[ubObjNr].uwMOARL   = (uword)(pstObj->ulID & 0xFFFF);
  }
  else                                         // standard identifier
  {
    //----- Configure standard identifier(11bit) ----------------------
    CAN_HWOBJ[ubObjNr].uwMOARH |= (uword)((pstObj->ulID & 0x07FF) << 2);
    CAN_HWOBJ[ubObjNr].uwMOARL = 0x0000;
  }

  //----- Configure acceptance mask -----------------------------------
  if((pstObj->ubMOCfg & 0x60) == 0x40) // if (IDE = 0 & MIDE = 1)
  {

    CAN_HWOBJ[ubObjNr].uwMOAMRH = (uword)((pstObj->ulMask & 0x07FF) << 2);
    CAN_HWOBJ[ubObjNr].uwMOAMRL = 0x0000;
  }
  else
  {

    CAN_HWOBJ[ubObjNr].uwMOAMRH = (uword)((pstObj->ulMask >> 16) & 0x1FFF);
    CAN_HWOBJ[ubObjNr].uwMOAMRL = (uword)(pstObj->ulMask & 0xFFFF);
  }

  //----- Configure Acceptance Mask -----------------------------------
  CAN_HWOBJ[ubObjNr].uwMOAMRH |= (((uword)(pstObj->ubMOCfg & 0x40)) << 7);

  //----- Configure Frame Counter -------------------------------------
  CAN_HWOBJ[ubObjNr].uwMOIPRH = pstObj->uwCounter;

  //----- Configure DLC & Data Bytes ----------------------------------
  CAN_HWOBJ[ubObjNr].uwMOFCRH &= (~(uword)0x0F00);
  CAN_HWOBJ[ubObjNr].uwMOFCRH |= (((uword)(pstObj->ubMOCfg & 0x0F)) << 8);

  if(pstObj->ubMOCfg & 0x10)                 // if transmit direction
  {
    //----- Configure message object data bytes -----------------------
    for(i = 0; i < (pstObj->ubMOCfg & 0x0F); i++)
    {
      CAN_HWOBJ[ubObjNr].ubData[i] = pstObj->ubData[i];
    }

    CAN_HWOBJ[ubObjNr].uwMOCTRH  = 0x0E28;  // set DIR, TXEN1, TXEN0, MSGVAL
                                            // and NEWDAT
  }
  else                                      // receive direction
  {
    CAN_HWOBJ[ubObjNr].uwMOCTRH  = 0x0020;  // set MSGVAL
    CAN_HWOBJ[ubObjNr].uwMOCTRL  = 0x0800;  // reset DIR
  }

  CAN_HWOBJ[ubObjNr].uwMOCTRL  = 0x0040;  // reset RTSEL

} //  End of function CAN_vConfigMsgObj

//****************************************************************************
// @Function      void CAN_vLoadData(ubyte ubObjNr, ubyte *ubpubData) 
//
//----------------------------------------------------------------------------
// @Description   If a hardware TRANSMIT OBJECT has to be loaded with data 
//                but not with a new identifier, this function may be used 
//                instead of the function CAN_vConfigMsgObj. The message 
//                object should be accessed by calling the function 
//                CAN_ubRequestMsgObj before calling this function. This 
//                prevents the CAN controller from working with invalid data.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the message object to be configured (0-63)
// @Parameters    *ubpubData: 
//                Pointer on a data buffer
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

// USER CODE BEGIN (LoadData,1)

// USER CODE END

void CAN_vLoadData(ubyte ubObjNr, ubyte *ubpubData)
{
  ubyte i;

  CAN_HWOBJ[ubObjNr].uwMOCTRH = 0x0008;       // set NEWDAT

  for(i = 0; i < (CAN_HWOBJ[ubObjNr].uwMOFCRH & 0x0F00) >> 8; i++)
  {
    CAN_HWOBJ[ubObjNr].ubData[i] = *(ubpubData++); //load MODATA
  }

  CAN_HWOBJ[ubObjNr].uwMOCTRH = 0x0020;       // set MSGVAL
  CAN_HWOBJ[ubObjNr].uwMOCTRL = 0x0040;       // reset RTSEL

} //  End of function CAN_vLoadData



//****************************************************************************
// @Macro         CAN_viSRN0() 
//
//----------------------------------------------------------------------------
// @Description   
//
//----------------------------------------------------------------------------
// @Returnvalue   
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2019-11-04
//
//****************************************************************************

// USER CODE BEGIN (SRN0,1)

// USER CODE END

void CAN_viSRN0(void) interrupt CAN_SRN0INT
{

  uword uwSRN0ObjHandler;

  // USER CODE BEGIN (SRN0,2)

  // USER CODE END

  CAN_MSIMASKH = 0x0000;          // set message index mask register
  CAN_MSIMASKL = 0x0001;

  while (CAN_MSID0 != 0x0020)
  {
    switch(CAN_MSID0){

    case 0: // message object 0 interrupt 
    
      uwSRN0ObjHandler = CAN_HWOBJ[0].uwMOCTRL;

      if(uwSRN0ObjHandler & MOSTAT_RXPND)          // if message object 0 receive interrupt
      {
            // USER CODE BEGIN (SRN0_OBJ0,1)

            // USER CODE END

        if(uwSRN0ObjHandler & MOSTAT_NEWDAT)       // if NEWDAT is set
        {
            // USER CODE BEGIN (SRN0_OBJ0,2)

            // USER CODE END

          if (uwSRN0ObjHandler & MOSTAT_MSGLST)    // if MSGLST is set
          {
            // Indicates that the CAN controller has stored a new 
            // message into this object, while NEWDAT was still set,
            // ie. the previously stored message is lost.

            // USER CODE BEGIN (SRN0_OBJ0,3)

            // USER CODE END

          }
          else
          {
            // The CAN controller has stored a new message into this object.


            // USER CODE BEGIN (SRN0_OBJ0,4)
        	    CAN0ID_u16_Sig=CAN_MOAR0H;
        	  	CAN0ID_u16_Sig=(CAN0ID_u16_Sig>>2)&0x7FF;
        	  	Can0RecDeal_v_g(CAN0ID_u16_Sig);
            // USER CODE END
          }

        }

        CAN_HWOBJ[0].uwMOCTRL = MOSTAT_RST_MNR;            // reset MSGLST + NEWDAT + RXPND

      }  // End of RXPND0


      CAN_MSPND0H = ~(uword) 0x0000; // reset PND bit
      CAN_MSPND0L = ~(uword) 0x0001;

      // USER CODE BEGIN (SRN0_OBJ0,7)

      // USER CODE END

      break;

    default:

      // USER CODE BEGIN (SRN0,3)

      // USER CODE END

      break;

    }  // end switch 

    // USER CODE BEGIN (SRN0,7)

    // USER CODE END

  }  // end of while CAN_MSID


  // USER CODE BEGIN (SRN0,15)

  // USER CODE END

} //  End of function CAN_viSRN0



// USER CODE BEGIN (CAN_General,10)

// USER CODE END

