/*
 * eepRom.h
 *
 *  Created on: 2015-5-28
 *      Author: zhangguangyao
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#ifdef   EEPROM_GLOBALS
	#define  EEPROM_EXT
#else
	#define  EEPROM_EXT  extern
#endif

//****************************************************************************
//                                  MACROS
//****************************************************************************

#define  DISABLE_INTTRUPT	      PSW_IEN        =  0;
#define  ENSABLE_INTTRUPT		  PSW_IEN        =  1;

#define PAGE_0TO7               0
#define PAGE_8TO15              1
#define PAGE_16TO31             2
#define PAGE_32TO39             3
#define PAGE_40TO47             4
#define PAGE_48TO87             5
#define PAGE_88TO127            6
#define PAGE_128TO135           7
#define PAGE_126TO149           8


#define PAGE_NUMBER             9


#define  EEPROM_START           0xC40000
//****************************************************************************
//                                  VARIABLES
//****************************************************************************

struct FlashBlocks  {
  INT32U   szBlock;     // Size in Bytes
  INT32U   AddrBlock;     // Address of Blocks
};

union uniIMB_FSR_BUSY{
	INT16U v;
  struct b {
	INT16U busyfm1  : 1;
	INT16U busyfm2  : 1;
	INT16U busyfm3  : 1;
	INT16U res3     : 1;
	INT16U res4     : 1;
	INT16U res5     : 1;
	INT16U res6     : 1;
	INT16U res7     : 1;
	INT16U pagem1   : 1;
	INT16U pagem2   : 1;
	INT16U pagem3   : 1;
    //uword reserved_10_15: 6;
  } b;
};


union  uniIMB_FSR_OP{                // Flash State Operations
    INT16U v;
  struct o{
	INT16U prog   : 1;
	INT16U erase  : 1;
	INT16U power  : 1;
	INT16U mar    : 1;
	INT16U sqer   : 1;
	INT16U oper   : 1;
    //uword reserved_6_15: 10;
  } b;
};

union uniIMB_FSR_PROT {                // Flash State Protection
	INT16U v;
  struct p {
	INT16U proin  : 1;
	INT16U proiner: 1;
	INT16U rprodis: 1;
	INT16U wprodis: 1;
	INT16U proer  : 1;
    //uword reserved_5_15: 11;
  } b;
};

enum
{
	  noErr = 0,
	  FlashProgramError = 1,  //Flash Programming Error
	  FlashEraseError = 2,    //Flash Erase Error
	  Successful=3

};


EEPROM_EXT INT16U CnterPTV;


EEPROM_EXT INT8U EepromErasePage_bl_Sig[142];

EEPROM_EXT INT8U ECUParaCaliEn2_u8_Par;
EEPROM_EXT INT8U ECUParaCaliEn1_u8_Par;
EEPROM_EXT INT8U EPSParaCaliEn2_u8_Par;
EEPROM_EXT INT8U EPSParaCaliEn1_u8_Par;
EEPROM_EXT INT8U VehicleTuneEn1_u8_Par;
EEPROM_EXT INT8U VehicleTuneEn2_u8_Par;

EEPROM_EXT void EepPhyCheck_v_g(void);
EEPROM_EXT void ReadZeroAngleSensorOffset_v_g(void);
EEPROM_EXT void HellaTAS_AngleCal_V0p16alpha_FixInitialize_v_g(void);
EEPROM_EXT void ReadEVandFF_v_g(void);
EEPROM_EXT void ReadTfAndCRC_v_g(void);
EEPROM_EXT void UpdataTfFlag_v_g(void);
EEPROM_EXT void FACRC_Check_v_g(void);
EEPROM_EXT void  TFCRC_Check_v_g(void);
EEPROM_EXT void  SaveData_v_g(void);
EEPROM_EXT void  ReadFITDisableFlagInEE_v_g();
EEPROM_EXT void  ReadString_v_g(volatile INT8U *DestAdr,INT32U SourceAdr , INT16U Len);

EEPROM_EXT INT16U EepRom_Check (void);
EEPROM_EXT INT16U EepRom_Init (INT32U adr) ;
EEPROM_EXT INT16U EepRom_erase_sector (INT32U ulSector_Addr) ;
EEPROM_EXT INT16U EepRom_ProgramPage (INT32U page_adr, void *buf);
EEPROM_EXT INT16U EepRom_erase_page (INT32U ulPage_Addr);

EEPROM_EXT void EarsePageEeprom_v_g(INT16U Page);
EEPROM_EXT void CopyString_v_g(void *SourceAdr, INT32U DestAdr, INT16U Len,INT8U WrBlg);
EEPROM_EXT void ReadData_v_g(void);

#endif /* EEPROM_H_ */
