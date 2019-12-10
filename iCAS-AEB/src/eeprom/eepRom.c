/*
 * eepRom.c
 *
 *  Created on: 2015-5-28
 *      Author: zhangguangyao
 */
#define  EEPROM_GLOBALS
#include "MAIN.h"



//****************************************************************************
//                                  MACROS
//****************************************************************************


//****************************************************************************
//                                  VARIABLES
//****************************************************************************


// Software version number rules:
//< hardware version >.< major version >.< subversion >.< revision version >.< date > version stage

// Description of software version stage:
// *Alpha	: Realize software function primarily, internal version
// *Beta	: this version has no serious errors, but some defects
// *RC		: there are almost no bugs causing errors in this release
// *Release	: this Release is for final delivery
static INT8U SoftwareVersion[28] = "HW01.1.1.00.20191115_alpha";


//****************************************************************************
//                                  FUNCTION
//****************************************************************************

static INT32U base;
static INT16U EepromBuf[70];
//****************************************************************************
// @Function      uword Flash_Init (ulong adr)
//
//----------------------------------------------------------------------------
// @Description   Function to Initialize Flash Programming Functions
//
//----------------------------------------------------------------------------
// @Returnvalue   uword
//
//----------------------------------------------------------------------------
// @Parameters    adr
//
//----------------------------------------------------------------------------
// @Date          2013-6-25
//
//****************************************************************************

INT16U EepRom_Init (INT32U adr) 
{
  base = adr;
  return (0);
}
//****************************************************************************
// @Function      uword Flash_Check (void)
//
//----------------------------------------------------------------------------
// @Description    Function to Check Status of Flash Device
//
//----------------------------------------------------------------------------
// @Returnvalue    uword
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2013-6-25
//
//****************************************************************************

INT16U EepRom_Check (void) 
{
	union uniIMB_FSR_BUSY fbr;
	union uniIMB_FSR_OP fop;
	union uniIMB_FSR_PROT fpr;

	do 
	{
		fbr.v =  (IMB_FSR_BUSY);         // Read Busy Register
	} while (fbr.b.busyfm1 || fbr.b.busyfm2 || fbr.b.busyfm3); // Wait until Flash is Busy

	fop.v =  (IMB_FSR_OP);         //Read Operation Register
	fpr.v =  (IMB_FSR_PROT);       //Read Protection Register

	if (fop.b.prog || fop.b.erase) 
	{
		(*((INT16U far *) (base |0xAA))) = 0xF5;  // Clear Status
	}

	if (fop.b.oper || fop.b.sqer || fpr.b.proer) 
	{
		(*((INT16U far *) (base |0xAA))) = 0xF0;  // Reset to Read Mode
		return (1);                              // Failed
	}
	return (0);                                // Done
}

//****************************************************************************
// @Function      uword Flash_erase_sector (ulong ulSector_Addr)
//
//----------------------------------------------------------------------------
// @Description   Function to erase one sector of the flash
//
//----------------------------------------------------------------------------
// @Returnvalue    uword
//
//----------------------------------------------------------------------------
// @Parameters    ulSector_Addr
//
//----------------------------------------------------------------------------
// @Date          2013-6-25
//
//****************************************************************************

INT16U EepRom_erase_sector (INT32U ulSector_Addr) 
{
	(*((INT16U far *) (base |0xAA))) = 0x80;       // Erase Sector (1. Cycle)
	(*((INT16U far *) (base |0x54))) = 0xAA;       // Erase Sector (2. Cycle)
	(*((INT16U far *) (ulSector_Addr))) = 0x33;    // Erase Sector (3. Cycle)
	return (EepRom_Check());                        // Check until Device Ready
}

//****************************************************************************
// @Function      uword Flash_erase_page (ulong ulPage_Addr)
//
//----------------------------------------------------------------------------
// @Description   Function to erase one page of the flash
//
//----------------------------------------------------------------------------
// @Returnvalue   uword
//
//----------------------------------------------------------------------------
// @Parameters    ulPage_Addr
//
//----------------------------------------------------------------------------
// @Date          2013-6-25
//
//****************************************************************************

INT16U EepRom_erase_page (INT32U ulPage_Addr) 
{
	(*((INT16U far *) (base |0xAA))) = 0x80;       // Erase Sector (1. Cycle)
	(*((INT16U far *) (base |0x54))) = 0xAA;       // Erase Sector (2. Cycle)
	(*((INT16U far *) (ulPage_Addr))) = 0x03;      // Erase Sector (3. Cycle)
	return (EepRom_Check());                             // Check until Device Ready
}

//****************************************************************************
// @Function      uword Flash_ProgramPage (ulong page_adr, void *buf)
//
//----------------------------------------------------------------------------
// @Description   Write Flash
//
//----------------------------------------------------------------------------
// @Returnvalue   INT16U uwTmp
//
//----------------------------------------------------------------------------
// @Parameters    ulong page_adr, void *buf
//
//----------------------------------------------------------------------------
// @Date          2013-6-25
//
//****************************************************************************

INT16U EepRom_ProgramPage (INT32U page_adr, void *buf) 
{
	INT16U cnt, uwTmp;
	// Enter Page Mode
	(*((INT16U far *) (base |0x00AA))) = 0x50;       // 1st cycle: write 50h to xx'00AAh
	(*((INT16U far *) (page_adr))) = 0xAA;     // 2nd cycle: write AAh to page start address
	uwTmp = (EepRom_Check());                            // Check until Device Ready

	if (uwTmp == 0)
	{
		// Load Page
		for (cnt = 0; cnt < 64; cnt++)  
		{
			(*((INT16U far *) (base |0x00F2))) = (*(uword *)buf);       // write word from R4 to xx'00F2h
			buf = (INT16U *) buf+1;
		}
		// Write Page
		(*((INT16U far *) (base |0x00AA))) = 0xA0;       // 1st cycle: write A0h to xx'00AAh
		(*((INT16U far *) (base |0x5A))) = 0xAA;         // 2nd cycle: : write AAh to xx'005A
		uwTmp = EepRom_Check();                          // Check until Device Ready
	}
	if(uwTmp == 1)
	{
		uwTmp=FlashProgramError;
	}
	return (uwTmp);
}


void EarsePageEeprom_v_g(INT16U Page)
{
	INT32U PageAdr;
	PageAdr = 0xC40000+ ((INT32U)Page*128);
	EepRom_Init(0xC40000);
	while(EepRom_erase_page (PageAdr)); // Erase 128k of Flash
}

void EepPhyCheck_v_g(void)
{

}
void ReadZeroAngleSensorOffset_v_g(void)
{

}
void HellaTAS_AngleCal_V0p16alpha_FixInitialize_v_g(void)
{

}
void ReadEVandFF_v_g(void)
{

}
void ReadTfAndCRC_v_g(void)
{

}
void UpdataTfFlag_v_g(void)
{

}
void FACRC_Check_v_g(void)
{

}
void TFCRC_Check_v_g(void)
{

}

void CopyString_v_g(void *SourceAdr, INT32U DestAdr, INT16U Len,INT8U WrBlg)
{
	static INT16U WriteLen=0;
	INT16U Wpage=0;
	INT8U *WrBuf;
	INT8U *Source;
	INT16U Page0,Page1;
	INT16U i;
	INT32U WrAdr;
	WrBuf=(INT8U *)EepromBuf;
	Source=SourceAdr;
	Page0=(INT16U)((DestAdr-0xC40000)/128);
	Page1=(INT16U)((DestAdr-0xC40000+Len-1)/128);
	
	for(i=Page0;i<=Page1;i++)
	{
		if(EepromErasePage_bl_Sig[i]==0)
		{
			EarsePageEeprom_v_g(i);
			EepromErasePage_bl_Sig[i]=1;
		}
	}
	for(i=0;i<Len;i++)
	{
		WrBuf[WriteLen]=Source[i];
		WriteLen++;
		if(WriteLen==128)
		{
			WriteLen=0;
			if(Page0==Page1)
			{
				Wpage=0;
			}
			WrAdr=0xC40000+(((INT32U)(Page0+Wpage))<<7);
			EepRom_ProgramPage(WrAdr,EepromBuf);
			Wpage++;
		}
	}

	if(WrBlg==1 && (WriteLen>0 && WriteLen<128))
	{
		WrAdr=(INT32U)0xC40000+(((INT32U)Page1)<<7);
		EepRom_ProgramPage(WrAdr,EepromBuf);
		WriteLen=0;
	}
}

void ReadString_v_g(volatile INT8U *DestAdr,INT32U SourceAdr,  INT16U Len)
{
	INT16U i;
	for(i=0;i<Len;i++)
	{
		DestAdr[i] = (*((INT8U far*)SourceAdr+i));
	}
}


void SaveData_v_g(void)
{
	INT8U page_num=0;
	for(page_num=0;page_num<PAGE_NUMBER;page_num++)
	{
		switch(page_num)
		{
			case PAGE_0TO7:
				CopyString_v_g(&CnterPTV, 0xC41000, sizeof(CnterPTV), 1);	
					
			break;

			case PAGE_8TO15:
				 
			break;

			case PAGE_16TO31:

			break;

			case PAGE_32TO39:

			break;

			case PAGE_40TO47:

			break;
			
			case PAGE_48TO87:
				
			break;
			
			case PAGE_88TO127:

			break;
			
			case PAGE_128TO135:

			break;
			
			case PAGE_126TO149:

			break;

		}
	}
}

void ReadData_v_g(void)
{
	INT8U page_num=0;
	for(page_num=0;page_num<PAGE_NUMBER;page_num++)
	{
		switch(page_num)
		{
			case PAGE_0TO7:
				ReadString_v_g((INT8U *)&CnterPTV, 0xC41000, sizeof(CnterPTV));

			break;

			case PAGE_8TO15:
				
			break;

			case PAGE_16TO31:

			break;

			case PAGE_32TO39:
				
			break;

			case PAGE_40TO47:

			break;

			case PAGE_48TO87:
			
			break;
			
			case PAGE_88TO127:

			break;
			
			case PAGE_128TO135:

			break;
			
			case PAGE_126TO149:

			break;

		}
	}
}

