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
#pragma section code="COPY_OE"
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
#pragma endsection
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
#pragma section code="COPY_0xE0"

INT16U EepRom_erase_sector (INT32U ulSector_Addr) 
{
	(*((INT16U far *) (base |0xAA))) = 0x80;       // Erase Sector (1. Cycle)
	(*((INT16U far *) (base |0x54))) = 0xAA;       // Erase Sector (2. Cycle)
	(*((INT16U far *) (ulSector_Addr))) = 0x33;    // Erase Sector (3. Cycle)
	return (EepRom_Check());                        // Check until Device Ready
}
#pragma endsection
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
#pragma section code="COPY_0xE0"
INT16U EepRom_erase_page (INT32U ulPage_Addr) 
{
	(*((INT16U far *) (base |0xAA))) = 0x80;       // Erase Sector (1. Cycle)
	(*((INT16U far *) (base |0x54))) = 0xAA;       // Erase Sector (2. Cycle)
	(*((INT16U far *) (ulPage_Addr))) = 0x03;      // Erase Sector (3. Cycle)
	return (EepRom_Check());                             // Check until Device Ready
}
#pragma endsection
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
#pragma section code="COPY_0xE0"

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
#pragma endsection

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
				CopyString_v_g(&CnterPTV,       0xC41000,sizeof(CnterPTV),0);//1
				CopyString_v_g(&FricPlateMorfct,0xC41001,sizeof(FricPlateMorfct),0); //1
				CopyString_v_g(&NLOffsetV,      0xC41002,sizeof(NLOffsetV),0); //1

				CopyString_v_g(&NLTTCTrsh, 0xC41003,sizeof(NLTTCTrsh),0); 
				CopyString_v_g(&TagPVACoef,0xC41004,sizeof(TagPVACoef),0); 
				CopyString_v_g(&TagPVI,    0xC41005,sizeof(TagPVI),0); 
				CopyString_v_g(&TagPVMaxSA,0xC41006,sizeof(TagPVMaxSA),0); 
				CopyString_v_g(&TagPVSAr,  0xC41007,sizeof(TagPVSAr),0); 
				CopyString_v_g(&TDCal,     0xC41008,sizeof(TDCal),0); 
				CopyString_v_g(&TDeltaD,   0xC41009,sizeof(TDeltaD),0); 
				CopyString_v_g(&THapRes,   0xC4100A,sizeof(THapRes),0); 
				CopyString_v_g(&TPrsDelay, 0xC4100B,sizeof(TPrsDelay),0); 
				CopyString_v_g(&TPrsRise,  0xC4100C,sizeof(TPrsRise),0); 
				CopyString_v_g(&Track,     0xC4100D,sizeof(Track),0); 
				CopyString_v_g(&TSonRes,   0xC4100E,sizeof(TSonRes),0); 
				CopyString_v_g(&TTCTrsh,   0xC4100F,sizeof(TTCTrsh),0); 
				CopyString_v_g(&VehW,      0xC41010,sizeof(VehW),0); 
				CopyString_v_g(&WBase,     0xC41011,sizeof(WBase),0);


				CopyString_v_g(&ATagE,         0xC41020,sizeof(ATagE),0); 
				CopyString_v_g(&ATagL,         0xC41022,sizeof(ATagL),0); 
				CopyString_v_g(&CentTRA,       0xC41024,sizeof(CentTRA),0); 
				CopyString_v_g(&DLatLatOs,     0xC41026,sizeof(DLatLatOs),0); 
				CopyString_v_g(&DLatLgOs,      0xC41028,sizeof(DLatLgOs),0); 
				CopyString_v_g(&LdF,           0xC4102A,sizeof(LdF),0); 
				CopyString_v_g(&LdId,          0xC4102C,sizeof(LdId),0); 
				CopyString_v_g(&LdR,           0xC4102E,sizeof(LdR),0); 
				CopyString_v_g(&MinDRel,       0xC41030,sizeof(MinDRel),0); 
				CopyString_v_g(&NLSWATrsh,     0xC41032,sizeof(NLSWATrsh),0); 
				CopyString_v_g(&NLSWAVTrsh,    0xC41034,sizeof(NLSWAVTrsh),0); 
				CopyString_v_g(&NLTRTrsh,      0xC41036,sizeof(NLTRTrsh),0); 
				CopyString_v_g(&SSysGR,        0xC41038,sizeof(SSysGR),0); 
				CopyString_v_g(&TireRaFricCoef,0xC4103A,sizeof(TireRaFricCoef),0); 
				CopyString_v_g(&TRTrsh,        0xC4103C,sizeof(TRTrsh),0); 
				CopyString_v_g(&VehLen,        0xC4103E,sizeof(VehLen),0);

				CopyString_v_g(&VSAEB,     0xC41040,  sizeof(VSAEB),0); 
				CopyString_v_g(&Sp0,       0xC41042,  sizeof(Sp0),0); 
				CopyString_v_g(&Sp1,       0xC41044,  sizeof(Sp1),0); 
				CopyString_v_g(&Sp2,       0xC41046,  sizeof(Sp2),0); 
				CopyString_v_g(&Sp3,       0xC41048,  sizeof(Sp3),0); 
				CopyString_v_g(&Sp4,       0xC4104A,  sizeof(Sp4),0); 
				CopyString_v_g(&Sp5,       0xC4104C,  sizeof(Sp5),0); 
				CopyString_v_g(&Sp6,       0xC4104E,  sizeof(Sp6),0); 
				CopyString_v_g(&Sp7,       0xC41050,  sizeof(Sp7),0); 
				CopyString_v_g(&Sp8,       0xC41052,  sizeof(Sp8),0); 
				CopyString_v_g(&Sp9,       0xC41054,  sizeof(Sp9),0); 
				CopyString_v_g(&Kp_Sp,     0xC41056,sizeof(Kp_Sp),0); 
				CopyString_v_g(&Ki_Sp,     0xC41058,sizeof(Ki_Sp),0); 
				CopyString_v_g(&Kd_Sp,     0xC4105A,sizeof(Kd_Sp),0); 

				CopyString_v_g(&Sv0,       0xC4105C,sizeof(Sv0),0); 
				CopyString_v_g(&Sv1,       0xC4105E,sizeof(Sv1),0); 
				CopyString_v_g(&Sv2,       0xC41060,sizeof(Sv2),0); 
				CopyString_v_g(&Sv3,       0xC41062,sizeof(Sv3),0); 
				CopyString_v_g(&Sv4,       0xC41064,sizeof(Sv4),0); 
				CopyString_v_g(&Sv5,       0xC41066,sizeof(Sv5),0); 
				CopyString_v_g(&Sv6,       0xC41068,sizeof(Sv6),0); 
				CopyString_v_g(&Sv7,       0xC4106A,sizeof(Sv7),0); 
				CopyString_v_g(&Sv8,       0xC4106C,sizeof(Sv8),0); 
				CopyString_v_g(&Sv9,       0xC4106E,sizeof(Sv9),0); 
				CopyString_v_g(&Kp_Sv,     0xC41070,sizeof(Kp_Sv),0); 
				CopyString_v_g(&Ki_Sv,     0xC41072,sizeof(Ki_Sv),0); 
				CopyString_v_g(&Kd_Sv,     0xC41074,sizeof(Kd_Sv),0); 

				CopyString_v_g(&Current0,  0xC41076,sizeof(Current0),0); 
				CopyString_v_g(&Current1,  0xC41078,sizeof(Current1),0); 
				CopyString_v_g(&Current2,  0xC4107A,sizeof(Current2),0); 
				CopyString_v_g(&Current3,  0xC4107C,sizeof(Current3),0); 
				CopyString_v_g(&Current4,  0xC4107E,sizeof(Current4),0); 
				CopyString_v_g(&Current5,  0xC41080,sizeof(Current5),0); 
				CopyString_v_g(&Current6,  0xC41082,sizeof(Current6),0); 
				CopyString_v_g(&Current7,  0xC41084,sizeof(Current7),0); 
				CopyString_v_g(&Current8,  0xC41086,sizeof(Current8),0); 
				CopyString_v_g(&Current9,  0xC41088,sizeof(Current9),0); 
				CopyString_v_g(&Kp_Current,0xC4108A,sizeof(Kp_Current),0); 
				CopyString_v_g(&Ki_Current,0xC4108C,sizeof(Ki_Current),0); 
				CopyString_v_g(&Kd_Current,0xC4108E,sizeof(Kd_Current),1);    
					
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
				ReadString_v_g((INT8U *)&CnterPTV,       0xC41000,sizeof(CnterPTV));//1
				ReadString_v_g((INT8U *)&FricPlateMorfct,0xC41001,sizeof(FricPlateMorfct)); //1
				ReadString_v_g((INT8U *)&NLOffsetV,      0xC41002,sizeof(NLOffsetV)); //1

				ReadString_v_g((INT8U *)&NLTTCTrsh, 0xC41003,sizeof(NLTTCTrsh)); 
				ReadString_v_g((INT8U *)&TagPVACoef,0xC41004,sizeof(TagPVACoef)); 
				ReadString_v_g((INT8U *)&TagPVI,    0xC41005,sizeof(TagPVI)); 
				ReadString_v_g((INT8U *)&TagPVMaxSA,0xC41006,sizeof(TagPVMaxSA)); 
				ReadString_v_g((INT8U *)&TagPVSAr,  0xC41007,sizeof(TagPVSAr),0); 
				ReadString_v_g((INT8U *)&TDCal,     0xC41008,sizeof(TDCal)); 
				ReadString_v_g((INT8U *)&TDeltaD,   0xC41009,sizeof(TDeltaD)); 
				ReadString_v_g((INT8U *)&THapRes,   0xC4100A,sizeof(THapRes)); 
				ReadString_v_g((INT8U *)&TPrsDelay, 0xC4100B,sizeof(TPrsDelay)); 
				ReadString_v_g((INT8U *)&TPrsRise,  0xC4100C,sizeof(TPrsRise)); 
				ReadString_v_g((INT8U *)&Track,     0xC4100D,sizeof(Track)); 
				ReadString_v_g((INT8U *)&TSonRes,   0xC4100E,sizeof(TSonRes)); 
				ReadString_v_g((INT8U *)&TTCTrsh,   0xC4100F,sizeof(TTCTrsh)); 
				ReadString_v_g((INT8U *)&VehW,      0xC41010,sizeof(VehW)); 
				ReadString_v_g((INT8U *)&WBase,     0xC41011,sizeof(WBase));


				ReadString_v_g((INT8U *)&ATagE,         0xC41020,sizeof(ATagE)); 
				ReadString_v_g((INT8U *)&ATagL,         0xC41022,sizeof(ATagL)); 
				ReadString_v_g((INT8U *)&CentTRA,       0xC41024,sizeof(CentTRA)); 
				ReadString_v_g((INT8U *)&DLatLatOs,     0xC41026,sizeof(DLatLatOs)); 
				ReadString_v_g((INT8U *)&DLatLgOs,      0xC41028,sizeof(DLatLgOs)); 
				ReadString_v_g((INT8U *)&LdF,           0xC4102A,sizeof(LdF)); 
				ReadString_v_g((INT8U *)&LdId,          0xC4102C,sizeof(LdId)); 
				ReadString_v_g((INT8U *)&LdR,           0xC4102E,sizeof(LdR)); 
				ReadString_v_g((INT8U *)&MinDRel,       0xC41030,sizeof(MinDRel)); 
				ReadString_v_g((INT8U *)&NLSWATrsh,     0xC41032,sizeof(NLSWATrsh)); 
				ReadString_v_g((INT8U *)&NLSWAVTrsh,    0xC41034,sizeof(NLSWAVTrsh)); 
				ReadString_v_g((INT8U *)&NLTRTrsh,      0xC41036,sizeof(NLTRTrsh)); 
				ReadString_v_g((INT8U *)&SSysGR,        0xC41038,sizeof(SSysGR)); 
				ReadString_v_g((INT8U *)&TireRaFricCoef,0xC4103A,sizeof(TireRaFricCoef)); 
				ReadString_v_g((INT8U *)&TRTrsh,        0xC4103C,sizeof(TRTrsh)); 
				ReadString_v_g((INT8U *)&VehLen,        0xC4103E,sizeof(VehLen));

				ReadString_v_g((INT8U *)&VSAEB,     0xC41040,  sizeof(VSAEB)); 
				ReadString_v_g((INT8U *)&Sp0,       0xC41042,  sizeof(Sp0)); 
				ReadString_v_g((INT8U *)&Sp1,       0xC41044,  sizeof(Sp1)); 
				ReadString_v_g((INT8U *)&Sp2,       0xC41046,  sizeof(Sp2)); 
				ReadString_v_g((INT8U *)&Sp3,       0xC41048,  sizeof(Sp3)); 
				ReadString_v_g((INT8U *)&Sp4,       0xC4104A,  sizeof(Sp4)); 
				ReadString_v_g((INT8U *)&Sp5,       0xC4104C,  sizeof(Sp5)); 
				ReadString_v_g((INT8U *)&Sp6,       0xC4104E,  sizeof(Sp6)); 
				ReadString_v_g((INT8U *)&Sp7,       0xC41050,  sizeof(Sp7)); 
				ReadString_v_g((INT8U *)&Sp8,       0xC41052,  sizeof(Sp8)); 
				ReadString_v_g((INT8U *)&Sp9,       0xC41054,  sizeof(Sp9)); 
				ReadString_v_g((INT8U *)&Kp_Sp,     0xC41056,  sizeof(Kp_Sp)); 
				ReadString_v_g((INT8U *)&Ki_Sp,     0xC41058,  sizeof(Ki_Sp)); 
				ReadString_v_g((INT8U *)&Kd_Sp,     0xC4105A,  sizeof(Kd_Sp)); 

				ReadString_v_g((INT8U *)&Sv0,       0xC4105C,sizeof(Sv0)); 
				ReadString_v_g((INT8U *)&Sv1,       0xC4105E,sizeof(Sv1)); 
				ReadString_v_g((INT8U *)&Sv2,       0xC41060,sizeof(Sv2)); 
				ReadString_v_g((INT8U *)&Sv3,       0xC41062,sizeof(Sv3)); 
				ReadString_v_g((INT8U *)&Sv4,       0xC41064,sizeof(Sv4)); 
				ReadString_v_g((INT8U *)&Sv5,       0xC41066,sizeof(Sv5)); 
				ReadString_v_g((INT8U *)&Sv6,       0xC41068,sizeof(Sv6)); 
				ReadString_v_g((INT8U *)&Sv7,       0xC4106A,sizeof(Sv7)); 
				ReadString_v_g((INT8U *)&Sv8,       0xC4106C,sizeof(Sv8)); 
				ReadString_v_g((INT8U *)&Sv9,       0xC4106E,sizeof(Sv9)); 
				ReadString_v_g((INT8U *)&Kp_Sv,     0xC41070,sizeof(Kp_Sv)); 
				ReadString_v_g((INT8U *)&Ki_Sv,     0xC41072,sizeof(Ki_Sv)); 
				ReadString_v_g((INT8U *)&Kd_Sv,     0xC41074,sizeof(Kd_Sv)); 

				ReadString_v_g((INT8U *)&Current0,  0xC41076,sizeof(Current0)); 
				ReadString_v_g((INT8U *)&Current1,  0xC41078,sizeof(Current1)); 
				ReadString_v_g((INT8U *)&Current2,  0xC4107A,sizeof(Current2)); 
				ReadString_v_g((INT8U *)&Current3,  0xC4107C,sizeof(Current3)); 
				ReadString_v_g((INT8U *)&Current4,  0xC4107E,sizeof(Current4)); 
				ReadString_v_g((INT8U *)&Current5,  0xC41080,sizeof(Current5)); 
				ReadString_v_g((INT8U *)&Current6,  0xC41082,sizeof(Current6)); 
				ReadString_v_g((INT8U *)&Current7,  0xC41084,sizeof(Current7)); 
				ReadString_v_g((INT8U *)&Current8,  0xC41086,sizeof(Current8)); 
				ReadString_v_g((INT8U *)&Current9,  0xC41088,sizeof(Current9)); 
				ReadString_v_g((INT8U *)&Kp_Current,0xC4108A,sizeof(Kp_Current)); 
				ReadString_v_g((INT8U *)&Ki_Current,0xC4108C,sizeof(Ki_Current)); 
				ReadString_v_g((INT8U *)&Kd_Current,0xC4108E,sizeof(Kd_Current)); 
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

