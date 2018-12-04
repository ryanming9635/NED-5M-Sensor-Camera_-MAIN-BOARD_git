//  **************************************************************************
//
//       Copyright (c) 1992-2006 Professonal Computer Technology Co., Ltd
//
//      All rights are reserved. Reproduction in whole or in parts is
//  prohibited without the prior written consent of the copyright owner.
//  --------------------------------------------------------------------------
//
//  Module: CommandSell.C
//
//  Purpose: Implementation of CommandSell.
//
//  Version: 0.01                                   2006/10/22 10:39�U��
//
//  Compiler: Keil 8051 C Compiler v7.2
//
//  Reference:
//
//
//
//  --------------------------------------------------------------------------
//  Modification:
//
//	R0.01 2006/10/22 10:39�U�� Phoenix Chuang
//	Reason:
//		1. Original.
//	Solution:
//	
//  **************************************************************************
// 	-----------------------------------
//			Header Files
//	----------------------------------- 
#include "types.h"
#include "CommandShell.h"
#include "UART.h"
#include "Timer.h"
#include "BusCtrl.h"
#include "TW2835_Init.h"
#include "TW28xx_Audio.h"
#include "TW28xx_Video.h"
#include "OSDCtrl.h"
#include "OSDAction.h"
#include "Main.h"

#include "NED.h"

// Table define on code


//	------------------------------------
//			Macro Definitions
//	------------------------------------ 
#define WINCH 		sysdat.channel_link
#define RECWINTYPE	sysdat.video_mix_type
#define RECLKTP 	sysdat.link_type
#define OSDREFALSH	msg.osd_falsh
#define selwintype 	msg.video_mix_type
	
//	------------------------------------
//			Type Definitions
//	------------------------------------
#define VERSION "34" //Kane @HS 2007 0725 Ver3.4  //

//	------------------------------------
//			Variables Definitions
//	------------------------------------
	SYS_DATA sysdat;
	SYS_MESSAGE msg;

extern U8 Com_pos;
extern  U8 Com_addr;
extern U8 Monitor_mode;
extern U8 Com_run;
//	------------------------------------
//			Function Prototypes
//	------------------------------------



// ***************************************************************************

// ===========================================================================
//                      Parallel function description
// ===========================================================================
//
// Get Command String from Command Buffer
//
U8 PCT_GetFirstStr(char **tagStr, char **sourceStr) 
{
	if( **sourceStr == '\0' ) return false;
	while(**sourceStr == ' ' ) (*sourceStr)++;
	*tagStr = *sourceStr;
	(*sourceStr)++;
	while(1) {
		if( **sourceStr==' ' ) {
			**sourceStr = '\0';
			(*sourceStr)++;
			return true;
		} else if( **sourceStr == '\0' ) {
			return true;
		} else (*sourceStr)++;
	}
	


}

// ===========================================================================
//
// String Transfer to Command Code 
//
U16 PCT_StrToCommCode(char *Str)
{
	data U16 ret=0;
	
	while(*Str != '\0' ) ret+=*Str++;
	return ret;
}

// ===========================================================================
//
// Send ACK to TW8806
//
void PCT_SendACK(void)
{
	#ifdef  SC16IS750_DEBUG_PRINT 
	RS_tx('A');
	RS_tx('C');
	RS_tx('K');
	#endif
}


// ===========================================================================
//
//
//

// ===========================================================================
//
//
//
void PCT_CheckVMixType(U8 _typ)
{
	data U8 tmplktp=0;
	
	tmplktp += (WINCH[0]&0x03); 
	tmplktp += (WINCH[1]&0x03)<<2; 
	tmplktp += (WINCH[2]&0x03)<<4; 
	tmplktp += (WINCH[3]&0x03)<<6; 
	
	if((RECWINTYPE==_typ)&&(tmplktp==RECLKTP)) {
		OSDREFALSH = OFF;
		return; 
	}
	OSDREFALSH = ON;
	RECLKTP = tmplktp;
	RECWINTYPE = _typ;
}


// ===========================================================================

// ***************************************************************************
// Process Command Shell Function
// ***************************************************************************
//
// This is to communicate with PC AP 
//
#if 0
void MoniReadPageBuffer(PCHAR szParam)
{
	data U8 page, start, end;

	sscanf(szParam, "%bx %bx %bx", &page, &start, &end); 

	do {
		printf("\n<R>%02bx[%02bx]=%02bx", page, start, TW28_ReadByte(page, start) );
		start++;
	}while(start != end);
}

// ***************************************************************************
//
// This is to communicate with PC AP 
//
void MoniReadOneBuffer(PCHAR szParam)
{
	data U8 page, addr;

	sscanf(szParam, "%bx %bx", &page, &addr); 

	printf("\n<R>%02bx[%02bx]=%02bx", page, addr, TW28_ReadByte(page, addr) );
}

// ***************************************************************************
//
// This is to communicate with PC AP 
//
void MoniWriteOneBuffer(PCHAR szParam)
{
	data U8 page, addr, dat;

	sscanf(szParam, "%bx %bx %bx", &page, &addr, &dat); 
	TW28_WriteByte(page, addr, dat);
}
#endif
// ***************************************************************************
//
// Monitor ASCIBUS Write Byte
//
void MoniWriteAsicByte(PCHAR szParam)
{
	data U8 _dev=0;
	data U8 _pg=0;
	data U8 _addr=0;
	data U8 _wdat=0;
	
	sscanf(szParam, "%bx %bx %bx %bx ", &_dev, &_pg, &_addr, &_wdat);
	TW28_WriteByte(_pg, _addr, _wdat);
}

// ***************************************************************************
//
// Monitor ASCIBUS Write Byte
//
#if 0
void MoniReadAsicByte(PCHAR szParam)
{
	data U8 _dev=0;
	data U8 _pg=0;
	data U8 _addr=0;
	data U8 _rdat=0;
	
	sscanf(szParam, "%1bx %1bx %1bx ", &_dev, &_pg, &_addr);
	_rdat = TW28_ReadByte(_pg, _addr);
	printf("ReadAsicByte == %bx \n", _rdat);
}
#endif
// ***************************************************************************
//
// Monitor Audio Mixing 
// Format : amix N ch0:val ch1:val ch2:val ch3:val ch4:val 
//
#if 0
void MoniAudioMixing(PCHAR szParam)
{
	data U8 selch0,selch1,selch2,selch3,selch4;	
	data U8 valch0,valch1,valch2,valch3,valch4;	
	char *getStr;
	code U8 chaddr[] = {ADO_MIX_MUTE_AIN0, \
						ADO_MIX_MUTE_AIN1, \
						ADO_MIX_MUTE_AIN2, \
						ADO_MIX_MUTE_AIN3, \
						ADO_MIX_MUTE_PBAI \
	};	

	PCT_GetFirstStr(&getStr,&szParam);

	PCT_AudioMixMute(0, ADO_MIX_MUTE_AIN0+ \
					 	ADO_MIX_MUTE_AIN1+ \
						ADO_MIX_MUTE_AIN2+ \
						ADO_MIX_MUTE_AIN3+ \
						ADO_MIX_MUTE_PBAI, OFF);

	switch( atoi(getStr) ) {
	case 1:
		sscanf(szParam,"ch%bd:%bd ",&selch0,&valch0);
		PCT_AudioMixCtrl(0, selch0, valch0);
		PCT_AudioMixMute(0, chaddr[selch0], ON);
		break;
	
	case 2:
		sscanf(szParam,"ch%bd:%bd ch%bd:%bd ", \
			&selch0, &valch0, &selch1, &valch1);
		PCT_AudioMixCtrl(0, selch0, valch0);
		PCT_AudioMixCtrl(0, selch1, valch1);
		PCT_AudioMixMute(0, chaddr[selch0]+chaddr[selch1], ON);
		break;
	
	case 3:
		sscanf(szParam,"ch%bd:%bd ch%bd:%bd ch%bd:%bd ", \
			&selch0, &valch0, &selch1, &valch1, &selch2, &valch2);
		PCT_AudioMixCtrl(0, selch0, valch0);
		PCT_AudioMixCtrl(0, selch1, valch1);
		PCT_AudioMixCtrl(0, selch2, valch2);
		PCT_AudioMixMute(0, chaddr[selch0]+chaddr[selch1]+chaddr[selch2], ON);
		break;
	
	case 4:
		sscanf(szParam,"ch%bd:%bd ch%bd:%bd ch%bd:%bd ch%bd:%bd ", \
			&selch0, &valch0, &selch1, &valch1, &selch2, &valch2, &selch3, &valch3);
		PCT_AudioMixCtrl(0, selch0, valch0);
		PCT_AudioMixCtrl(0, selch1, valch1);
		PCT_AudioMixCtrl(0, selch2, valch2);
		PCT_AudioMixCtrl(0, selch3, valch3);

		PCT_AudioMixMute(0, chaddr[selch0]+chaddr[selch1]+chaddr[selch2]+chaddr[selch3], ON);
		break;

	case 5:
		sscanf(szParam,"ch%bd:%bd ch%bd:%bd ch%bd:%bd ch%bd:%bd ch%bd:%bd ", \
			&selch0, &valch0, &selch1, &valch1, &selch2, &valch2, &selch3, &valch3,  &selch4, &valch4 );
		PCT_AudioMixCtrl(0, selch0, valch0);
		PCT_AudioMixCtrl(0, selch1, valch1);
		PCT_AudioMixCtrl(0, selch2, valch2);
		PCT_AudioMixCtrl(0, selch3, valch3);
		PCT_AudioMixCtrl(0, selch4, valch4);

		PCT_AudioMixMute(0, chaddr[selch0]+chaddr[selch1]+chaddr[selch2]+chaddr[selch3]+chaddr[selch4], ON);
		break;
	
	default:
		break;
	}
}

// ***************************************************************************
//
// Monitor Audio Mute 
// Format : amute
//
void MoniAudioMute(void)
{
	PCT_AudioMixMute(0, ADO_MIX_MUTE_AIN0+ \
					 	ADO_MIX_MUTE_AIN1+ \
						ADO_MIX_MUTE_AIN2+ \
						ADO_MIX_MUTE_AIN3+ \
						ADO_MIX_MUTE_PBAI, OFF);
	PCT_AudioSelLive(0, 0xFF);
}

// ***************************************************************************
//
// Monitor Audio Mixing 
// Format : again N ch0:val ch1:val ch2:val ch3:val ch5:val
//
void MoniAudioGain(PCHAR szParam)
{
	data U8 selch0,selch1,selch2,selch3,selch4;	
	data U8 ch0val,ch1val,ch2val,ch3val,ch4val;	
	char *getStr;

	PCT_GetFirstStr(&getStr,&szParam);

	switch( atoi(getStr) ) {
	case 1:
		sscanf(szParam,"ch%bd:%bd ",&selch0,&ch0val);
		PCT_AudioGainCtrl(0, selch0, ch0val);
		break;
	
	case 2:
		sscanf(szParam,"ch%bd:%bd ch%bd:%bd ", \
			&selch0, &ch0val, &selch1, &ch1val);
		PCT_AudioGainCtrl(0, selch0, ch0val);
		PCT_AudioGainCtrl(0, selch1, ch1val);
		break;
	
	case 3:
		sscanf(szParam,"ch%bd:%bd ch%bd:%bd ch%bd:%bd ", \
			&selch0, &ch0val, &selch1, &ch1val, &selch2, &ch2val);
		PCT_AudioGainCtrl(0, selch0, ch0val);
		PCT_AudioGainCtrl(0, selch1, ch1val);
		PCT_AudioGainCtrl(0, selch2, ch2val);
		break;
	
	case 4:
		sscanf(szParam,"ch%bd:%bd ch%bd:%bd ch%bd:%bd ch%bd:%bd ", \
			&selch0, &ch0val, &selch1, &ch1val, &selch2, &ch2val, &selch3, &ch3val);
		PCT_AudioGainCtrl(0, selch0, ch0val);
		PCT_AudioGainCtrl(0, selch1, ch1val);
		PCT_AudioGainCtrl(0, selch2, ch2val);
		PCT_AudioGainCtrl(0, selch3, ch3val);
		break;
	
	case 5:
		sscanf(szParam,"ch%bd:%bd ch%bd:%bd ch%bd:%bd ch%bd:%bd ch%bd:%bd ", \
			&selch0, &ch0val, &selch1, &ch1val, &selch2, &ch2val, &selch3, &ch3val, &selch4, &ch4val);
		PCT_AudioGainCtrl(0, selch0, ch0val);
		PCT_AudioGainCtrl(0, selch1, ch1val);
		PCT_AudioGainCtrl(0, selch2, ch2val);
		PCT_AudioGainCtrl(0, selch3, ch3val);
		PCT_AudioGainCtrl(0, selch4, ch4val);
		break;
	
	default:
		break;
	}
}

// ***************************************************************************
//
// Monitor Select Live or Mixing Mode 
// alive chan (chan=0xFF is Mixing Mode)
//
void MoniAudioLive(PCHAR szParam)
{
	data U8 chan;

	sscanf(szParam, "%bd ", &chan);

	PCT_AudioSelLive(0,chan);
}

// ***************************************************************************
//
// TW2835 Register All Dump
//
void MoniRegisterDump(void)
{
	data U8 addr,page;
	

	for(page=0;page<3;page++) {
		printf("\n ======== PAGE %b2x =============\n",page);
		addr = 0;
		do {
			printf("%b2x\t", TW28_ReadByte(page, addr));
			addr++;
			if((addr%16)==0)  printf("\n"); 
		} while( addr );
	}
}

// ***************************************************************************
//
// video signal mixing to windows
//
void MoniVideoMixWin(PCHAR szParam)
{
	data U8 chose,wintp;

	sscanf(szParam, "%1bx %1bx ch%1bx ch%1bx ch%1bx ch%1bx ",
					&chose, &wintp, &WINCH[0], &WINCH[1], &WINCH[2], &WINCH[3]);
	chose = (chose<<4)+(wintp&0x0F);
	PCT_SetXVideoMixing(chose, WINCH);	
}




// ***************************************************************************
//
// setting windows attribute
//
void MoniVideoMixAttr(PCHAR szParam)
{
	data U16 chose;
	data U8	attrsel,setval;
	data U8 	winNm[4],wincnt=0;
	data U8 	division;
	char *getStr;

	PCT_GetFirstStr(&getStr,&szParam);
	division = atoi(getStr); 

	PCT_GetFirstStr(&getStr,&szParam);
	chose = PCT_StrToCommCode(getStr); 

	if( chose==PCT_StrToCommCode("enrecall") ) {
		attrsel = WIN_RECALL_EN;
		setval  = ON;
	} else if ( chose==PCT_StrToCommCode("enfreeze") ) {
		attrsel = WIN_FREEZE;
		setval  = ON;
	} else if ( chose==PCT_StrToCommCode("enhmirror") ) {
		attrsel = WIN_HMIRROR;
		setval  = ON;
	} else if ( chose==PCT_StrToCommCode("envmirror") ) {
		attrsel = WIN_VMIRROR;
		setval  = ON;
	} else if ( chose==PCT_StrToCommCode("enenhance") ) {
		attrsel = WIN_ENHANCE;
		setval  = ON;
	} else if ( chose==PCT_StrToCommCode("enblank") ) {
		attrsel = WIN_BLANK;
		setval  = ON;
	} else if ( chose==PCT_StrToCommCode("enbound") ) {
		attrsel = WIN_BOUND;
		setval  = ON;
	} else if ( chose==PCT_StrToCommCode("enblink") ) {
		attrsel = WIN_BLINK;
		setval  = ON;
	} else if ( chose==PCT_StrToCommCode("disrecall") ) {
		attrsel = WIN_RECALL_EN;
		setval  = OFF;
	} else if ( chose==PCT_StrToCommCode("disfreeze") ) {
		attrsel = WIN_FREEZE;
		setval  = OFF;
	} else if ( chose==PCT_StrToCommCode("dishmirror") ) {
		attrsel = WIN_HMIRROR;
		setval  = OFF;
	} else if ( chose==PCT_StrToCommCode("disvmirror") ) {
		attrsel = WIN_VMIRROR;
		setval  = OFF;
	} else if ( chose==PCT_StrToCommCode("disenhance") ) {
		attrsel = WIN_ENHANCE;
		setval  = OFF;
	} else if ( chose==PCT_StrToCommCode("disblank") ) {
		attrsel = WIN_BLANK;
		setval  = OFF;
	} else if ( chose==PCT_StrToCommCode("disbound") ) {
		attrsel = WIN_BOUND;
		setval  = OFF;
	} else if ( chose==PCT_StrToCommCode("disblink") ) {
		attrsel = WIN_BLINK;
		setval  = OFF;
	} else {
		return;
	}

	while( PCT_GetFirstStr(&getStr,&szParam) ) {
		if(*getStr=='w' && *(getStr+1)=='i' && *(getStr+2)=='n') 
		{
			winNm[wincnt] = atoi(getStr+3);
			wincnt++;
		}
	}
	for( ; wincnt!=0; wincnt--) {
		if( winNm[wincnt-1]<division ) {
			PCT_WinAttrCtrl(winNm[wincnt-1], attrsel, setval);
		}
	}
}
#endif
// ***************************************************************************
//
// Monitor Video Y Channel Select Live or Mixing Mode 
// yvmix chan (chan=0x04 is Mixing Mode)
//
void MoniYVideoMix(PCHAR szParam)
{
	data U8 chan;

	sscanf(szParam, "%bd ", &chan);
	PCT_SetYVideoMixing(chan);
}

// ***************************************************************************
//
// Monitor Video Auto Detect Format 
//
#if 0
void MoniVideoAutoDetect(void)
{
	printf("===== Format : ch0=[%bx] ch1=[%bx] ch2=[%bx] ch3=[%bx] =====\n",	\ 
			PCT_DetectVideoFormat(0x00), \
			PCT_DetectVideoFormat(0x01), \
			PCT_DetectVideoFormat(0x02), \
			PCT_DetectVideoFormat(0x03) \
	);
}

// ***************************************************************************
//
// Monitor Setting Video Format 
//
void MoniSetVideoFormat(PCHAR szParam)
{
	data U8 selch0,selch1,selch2,selch3;	
	data U8 valch0,valch1,valch2,valch3;	
	char *getStr;

	PCT_GetFirstStr(&getStr,&szParam);

	switch( atoi(getStr) ) {
	case 1:
		sscanf(szParam,"ch%bd:%bd ",&selch0,&valch0);
		PCT_SetVideoFormat(0, selch0, valch0<<4);
		break;
	
	case 2:
		sscanf(szParam,"ch%bd:%bd ch%bd:%bd ", \
			&selch0, &valch0, &selch1, &valch1);
		PCT_SetVideoFormat(0, selch0, valch0<<4);
		PCT_SetVideoFormat(0, selch1, valch1<<4);
		break;
	
	case 3:
		sscanf(szParam,"ch%bd:%bd ch%bd:%bd ch%bd:%bd ", \
			&selch0, &valch0, &selch1, &valch1, &selch2, &valch2);
		PCT_SetVideoFormat(0, selch0, valch0<<4);
		PCT_SetVideoFormat(0, selch1, valch1<<4);
		PCT_SetVideoFormat(0, selch2, valch2<<4);
		break;
	
	case 4:
		sscanf(szParam,"ch%bd:%bd ch%bd:%bd ch%bd:%bd ch%bd:%bd ", \
			&selch0, &valch0, &selch1, &valch1, &selch2, &valch2, &selch3, &valch3);
		PCT_SetVideoFormat(0, selch0, valch0<<4);
		PCT_SetVideoFormat(0, selch1, valch1<<4);
		PCT_SetVideoFormat(0, selch2, valch2<<4);
		PCT_SetVideoFormat(0, selch3, valch3<<4);
		break;

	default:
		break;
	}
}

// ***************************************************************************
//
// Monitor Setting Video Format 
//
#endif
void MoniShowSODStr(PCHAR szParam)
{
	data U8 addrx,addry;
	char *getStr;
	
	PCT_GetFirstStr(&getStr,&szParam);
	addrx=atoi(getStr);
	PCT_GetFirstStr(&getStr,&szParam);
	addry=atoi(getStr);

	PCT_PreSetForegroundColor(OSD_COL_100WHT);
	PCT_PreSetBackgroundColor(OSD_COL_BLU);
	PCT_SetOSDDrawPage(WRPHX_PAGE5);
	PCT_ShowOSDString(PTH_X, addrx, addry, szParam);
	PCT_EnShowOSDPage(WRPHX_PAGE5);
}

// ***************************************************************************
//
// Audio Control for HiSarp
//
#if 0
void PCT_AudioActionForHS(void)
{
	data U8 winid;
	data U8 muteFlage=true;

	// ------------- Control Audio ------------
	for(winid=0; winid<4; winid++) {
		if(SYSWINATTR[winid]&BIT4) {
			PCT_AudioSelLive(0,WINCH[winid]);
			muteFlage = false;
		}
	}

	if(muteFlage) {
		// Audio Mute
		PCT_AudioMixMute(0, ADO_MIX_MUTE_AIN0+ \
						 	ADO_MIX_MUTE_AIN1+ \
							ADO_MIX_MUTE_AIN2+ \
							ADO_MIX_MUTE_AIN3+ \
							ADO_MIX_MUTE_PBAI, OFF);
		PCT_AudioSelLive(0, 0xFF);
	}
	// ----------------------------------------
}
#endif
// ***************************************************************************
//
// Command Shell for HiSarp
//
BYTE xdata Original_selwintype = 0;//Kane @HS 2007 0724 Ver3.4
void MoniHSComm(PCHAR szParam) {
	data U8 winid;
	data U8 chose,wintp;
	
	sscanf(szParam, "%bx %bx ch%bx:%bx ch%bx:%bx ch%bx:%bx ch%bx:%bx ",
	&chose, &wintp, &WINCH[0], &SYSWINATTR[0], &WINCH[1], &SYSWINATTR[1], &WINCH[2], &SYSWINATTR[2], &WINCH[3], &SYSWINATTR[3]);

	selwintype = (SYSTYPE<<7)+(chose<<4)+(wintp&0x0F);

	// ----------- Y Chanle setting windows horizontal mirror ----------
		
	SYSCHATTR[WINCH[0]]=SYSWINATTR[0];
	SYSCHATTR[WINCH[1]]=SYSWINATTR[1];
	SYSCHATTR[WINCH[2]]=SYSWINATTR[2];
	SYSCHATTR[WINCH[3]]=SYSWINATTR[3];

	PCT_WinAttrCtrlY(0, WIN_HMIRROR, SYSCHATTR[0]&BIT0);	
	PCT_WinAttrCtrlY(1, WIN_HMIRROR, SYSCHATTR[1]&BIT0);	
	PCT_WinAttrCtrlY(2, WIN_HMIRROR, SYSCHATTR[2]&BIT0);	
	PCT_WinAttrCtrlY(3, WIN_HMIRROR, SYSCHATTR[3]&BIT0);	
	// -----------------------------------------------------------------

	// ------------- Control Video ------------
	//if(Original_selwintype != selwintype)//Kane @HS 2007 0724 Ver3.4


	PCT_RecompenseYHdelay(SYSCHATTR);
	PCT_SetVideoHDelay(selwintype, WINCH, SYSWINATTR);

	
	PCT_SetXVideoMixing(selwintype, WINCH);
	
	//PCT_VideoLastModify();
	for(winid=0; winid<4; winid++) 
		PCT_WinAttrCtrl(winid, WIN_HMIRROR, SYSWINATTR[winid]&BIT0);	
	// ----------------------------------------

#if 1
	// ------------- Control OSD ------------
	DisUserTimer(USERTMID0);		// Disable real-time detect VLoss
	EnUserTimer(USERTMID1,5);		// Enable OSD Delay Timer
	PCT_FlashOSDCtrl(ON);
	
	PCT_CheckVMixType(selwintype);
	PCT_DisShowOSDPage(DISOSD_PHX);
	PCT_ClearOSDPageX(WRPHX_PAGE0);
	PCT_ShowModeIcon();
	PCT_OSD_ActionPthX(SYSWINATTR);
	Original_selwintype = selwintype;//Kane @HS 2007 0724 Ver3.4
#else
	// ------------- Control OSD ------------
	DisUserTimer(USERTMID0);		// Disable real-time detect VLoss
	EnUserTimer(USERTMID1,5);		// Enable OSD Delay Timer
	PCT_FlashOSDCtrl(ON);
	PCT_CheckVMixType(selwintype);
	PCT_DisShowOSDPage(DISOSD_PHX);
	PCT_ClearOSDPageX(WRPHX_PAGE0);
	PCT_ShowModeIcon();
	PCT_OSD_ActionPthX(SYSWINATTR);
	Original_selwintype = selwintype;//Kane @HS 2007 0724 Ver3.4
#endif




	// --------------------------------------
}


// ***************************************************************************
//
// Real Time Check System Type PAL or NTSC
//
bit PCT_CheckSystem(void)
{
	//Kane add>>>>
	char TempSystem;
	TempSystem = PCT_DetectVideoFormat(SENSORCHANNEL);
	//if(SYSTYPE == PCT_DetectVideoFormat(SENSORCHANNEL)) return true;//Kane canceled
	if(TempSystem == NONE_SYSTEM)
		return FALSE;
	if(TempSystem == SYSTYPE)
		return TRUE;
	SYSTYPE = TempSystem;
	//Kane Add<<<<
	//SYSTYPE = PCT_DetectVideoFormat(SENSORCHANNEL);//Kane canceled
	SYSMIXTYP = (SYSTYPE<<7)|(SYSMIXTYP&0x7F);

	PCT_EnShowOSDPage(WRPHX_PAGE1);


	// ------------- Control Video ------------
	PCT_ChangeSystemType(SYSTYPE);
	PCT_RecompenseYHdelay(SYSCHATTR);	// preset Y Recompense
	PCT_SetVideoHDelay(RECWINTYPE, WINCH, SYSWINATTR);
	
	PCT_SetXVideoMixing(RECWINTYPE, WINCH);
	//PCT_VideoLastModify();
    
	// ------------- Control OSD ------------
	PCT_ClearOSDPageX(WRPHX_PAGE0);
	PCT_ShowModeIcon();
	PCT_OSD_ActionPthX(SYSWINATTR);
	PCT_OSDActionForHS();
	// --------------------------------------
	
	return 1;
}


// ***************************************************************************
//
// Command Shell for HiSarp Setting S or J Mode
//
void MoniHSCommSJmode(PCHAR szParam)
{
	sscanf(szParam, "%bd ", &SYSMODE);
}

// ***************************************************************************
//
// Command Shell for HiSarp Setting S or J Mode
//
#if 0
void MoniHSCommDisScroll(void)
{
	PCT_EnShowOSDPage(WRPHX_PAGE1);
}
// ***************************************************************************
//
// Command Shell for HiSarp Setting S or J Mode
//
void MoniHSCommVersion(void)
{
	RS_tx(VERSION[0]);
	RS_tx(VERSION[1]);
}
#endif

// ***************************************************************************
//
// Runing Command Shell
//

U8 PCT_RunCommShell(char *strptr)
{
	U16 commcode;
	char *getStr;  
 

//printf("char *strptr=%s\r\n",strptr);//ryan..


        	//MoniHSComm(strptr);
		//PCT_AudioActionForHS();
		//PCT_OSDActionForHS();  
           //PCT_FlashOSDCtrl(OFF);
          // return 0;
 //    getStr=&CommTable[0];
	// ---------- Run Command Shell Entry ----------
	//Kane @HS 2007 0809 Ver3.5>>>>
	PCT_GetFirstStr(&getStr, &strptr);
	//getStr=strptr+4;
	//Kane @HS 2007 0809 Ver3.5<<<<
	commcode = PCT_StrToCommCode(getStr); 
	#if 0
	if (commcode == PCT_StrToCommCode("&")) {
		//printf("Read Page Buffer Data");
		MoniReadPageBuffer(strptr);
	}else if( commcode == PCT_StrToCommCode("(")) {
		//printf("Read One Buffer Data");
		MoniReadOneBuffer(strptr);
	}else if( commcode == PCT_StrToCommCode(")")) {
		//printf("Write One Buffer Data");
		MoniWriteOneBuffer(strptr);
		
	}

	else
#endif
		if( commcode == PCT_StrToCommCode("busw")) {
		// ===== ASICBUS Write Byte ======
		//printf("Command is Write Bus");
		MoniWriteAsicByte(strptr);

	} 

#if 0
	else if (commcode == PCT_StrToCommCode("busr")) {
		// ===== ASICBUS Read Byte =======
		//printf("Command is Read Bus");
		MoniReadAsicByte(strptr);
	}

	else if (commcode == PCT_StrToCommCode("amix")) {
		// ===== Audio mix =======
		//printf("Command is Audio Mixing");
		MoniAudioMixing(strptr);
	} else if (commcode == PCT_StrToCommCode("amute")) {
		// ===== Audio Mute =======
		//printf("Command is Audio Mute");
		MoniAudioMute();
	} else if (commcode == PCT_StrToCommCode("adump")) {
		// ===== List Audio Register Value =======
		//printf("List Audio Register Value");
		PCT_AudioRegList();
	} else if (commcode == PCT_StrToCommCode("again")) {
		// ===== Audio Gain Control =======
		//printf("Audio Gain Control");
		MoniAudioGain(strptr);
	} else if (commcode == PCT_StrToCommCode("alive")) {
		// ===== Audio Select Live & Mixing Mode =======
		//printf("Audio Select Live & Mixing Mode");
		MoniAudioLive(strptr);
	} else if (commcode == PCT_StrToCommCode("busrt")) {
		// ===== All Register Dump =======
		//printf("All Register Dump");
		MoniRegisterDump();
	} else if (commcode == PCT_StrToCommCode("vmix")) {
		// ===== Video Mix's Windows Type Select =======
		//printf("Video Mix's Windows Type Select");
		PCT_WinAttrClear(WIN_FREEZE);
		MoniVideoMixWin(strptr);
		PCT_SendACK();
	} else if (commcode == PCT_StrToCommCode("vmixerr")) {
		// ===== Video Mix's Windows Type Select =======
		//printf("Video Mixerr's Windows Type Select");
		MoniVideoMixWin(strptr); 
	} else if (commcode == PCT_StrToCommCode("vattr")) {
		// ===== Video Mixing Control =======
		//printf("Video Attribute Control");
		MoniVideoMixAttr(strptr);
		
	} 


	else
#endif
		else if (commcode == PCT_StrToCommCode("yvmix")) {		// HiSharp has used
		// ===== Video Mixing Control =======
		PCT_SendACK();
		//printf("Video Attribute Control");
		MoniYVideoMix(strptr);
		
	}
	#if 0
	else if (commcode == PCT_StrToCommCode("init")) {
		// ===== TW2835 initial =======
		//printf("Initial TW2835");
		PCT_InitialTW2835();
	} else if (commcode == PCT_StrToCommCode("vdet")) {
		// ===== Video Mixing Control =======
		//printf("Auto Detectation Video Format");
		MoniVideoAutoDetect();
	} else if (commcode == PCT_StrToCommCode("vsetf")) {
		// ===== Video Mixing Control =======
		//printf("Setting Video Format Control");
		MoniSetVideoFormat(strptr);
	} else if (commcode == PCT_StrToCommCode("sstr")) {
		// ===== Show String on OSD =======
		//printf("Show String on OSD");
		MoniShowSODStr(strptr);
// --------------------------------------------------------------------------------

	}
#endif	
	else if (commcode == PCT_StrToCommCode("hscom")) {		// HiSharp has used
		PCT_SendACK();
		//printf("Command Shell for HiSharp");
		MoniHSComm(strptr);

#if 1
		PCT_OSDActionForHS();
		PCT_FlashOSDCtrl(OFF);
#else
		//PCT_AudioActionForHS();
		PCT_OSDActionForHS();
		PCT_FlashOSDCtrl(OFF);
#endif

		#ifdef TW2835_degug
		TW2835_get(0);
		#endif		


		
	} else if (commcode == PCT_StrToCommCode("mode")) {			// HiSharp has used
		PCT_SendACK();
		//printf("Command Shell for HiSharp Set S or J Mode");
		MoniHSCommSJmode(strptr);
	} 
#if 0
	else if (commcode == PCT_StrToCommCode("disscroll")) {	// HiSharp has used
		PCT_SendACK();
		//printf("Command Shell for HiSharp Disable Scroll!");
		MoniHSCommDisScroll();
	} else if (commcode == PCT_StrToCommCode("ver")) {	// HiSharp has used
		PCT_SendACK();
		//printf("Command Shell for HiSharp Disable Scroll!");
		MoniHSCommVersion();
		//PCT_InitialTW2835();//Kane @HS 2007 0723 Ver3.4
// --------------------------------------------------------------------------------
	} 
#endif
	else if(commcode == PCT_StrToCommCode("7"))
			{
				//Monitor_set((Com_pos));	
				 Monitor_mode=Com_run;
				 
			#ifdef  SC16IS750_DEBUG_PRINT 
			printf("\r\nget Monitor=%x",(U16) Com_run);
			#endif
			}
		   else if(commcode == PCT_StrToCommCode("8"))
		   	{

   				Repeat_PWM_Com();
				PWM_set(Com_run);	
				
				#ifdef  SC16IS750_DEBUG_PRINT 
				printf("\r\nget PWM=%x",(U16)Com_run);
				#endif		
				
		   	}
		      else if(commcode == PCT_StrToCommCode("0123456789ABCDEF"))
		      	{
			MoniShowSODStr(strptr);///re-build warning issue add by ryan@20181204
		      	}
		   #if 0//ryan@20150818
		   	else if (commcode == PCT_StrToCommCode("1"))
		   	{	   	
				if(SC16_Com[2]==0x31)
				{
				Temp_check();
				#ifdef  SC16IS750_DEBUG_PRINT 
				printf("\r\nget temp=%x",(U16)ADT75_GetTemp());
				#endif
				}
				else if(SC16_Com[2]==0x33)
				{
				Press_check();
				#ifdef  SC16IS750_DEBUG_PRINT 
				printf("\r\nget Press_check=%x",(U16)ADC_FPBS());
				#endif
				}
				else if(SC16_Com[2]==0x50)
					{
					Version_check();
					#ifdef  SC16IS750_DEBUG_PRINT 
					printf("\r\nget Version=%x%x%x",(U16)Ver0,(U16)Ver1,(U16)Ver2);
					#endif
					}
			
				
		   	}
			#endif
			else
				{
				}

	//ResetCommSell(); 
			
	// ---------------------------------------------
	return true;
}


// ===========================================================================
// END of File 
// ===========================================================================



