//  **************************************************************************
//
//       Copyright (c) 1992-2006 Professonal Computer Technology Co., Ltd
//
//      All rights are reserved. Reproduction in whole or in parts is
//  prohibited without the prior written consent of the copyright owner.
//  --------------------------------------------------------------------------
//
//  Module: Main.H
//
//  Purpose: Implementation of Main.
//
//  Version: 0.01                                   2006/10/22 09:26¤U¤È
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
//	R0.01 2006/10/22 10:39¤U¤È Phoenix Chuang
//	Reason:
//		1. Original.
//	Solution:
//	
//  **************************************************************************
// 	-----------------------------------
//			Header Files
//	----------------------------------- 


//	------------------------------------
//			Macro Definitions
//	------------------------------------ 
//
//	functions
//

//	
//	terminals
//	

                
//	------------------------------------
//			Type Definitions
//	------------------------------------
	#define COMM_MAX_BUF 40
	#define TWCMD	1
	typedef struct _COMMAND_BUFFER {
		BYTE commBuf[COMM_MAX_BUF];
		BYTE ReadPtr;
		BYTE WritePtr;
		BYTE commFlage;
//		char *commStr;
//		char *paramStr;
	} COMMAND_BUFFER,* PCOMMAND_BUFFER;

//	------------------------------------
//			Variables Definitions
//	------------------------------------
	extern U16 _delay;

	extern COMMAND_BUFFER RScommand;
	extern bit VlossFlag;
	
//	------------------------------------
//			Function Prototypes
//	------------------------------------


// ===========================================================================
//			Hardware-dependent ( Physical) primitives
// ===========================================================================
	extern void ResetCommSell (void);
	extern void InitialCommShell (void);
	extern void chkStartCommShell (char *ptr);
	extern void CommandShell (void);
	extern void NewLine (void);
	extern void PutsP (BYTE *);

	extern void InitialMPU (void);
	extern void PCT_SetChanelScale (U8 _ch, WRITE_REG_DATA *datptr);
	extern void PCT_FlashOSDCtrl(U8 _on);
	extern void Wait_ms(U16 Tms);
    //----------------------------
 //      void main_loop(void);
void Set_PWM_Output (U8 addr,U8 val);
void PWM_init(void);  
U8 Monitor_set(U8 val);
U8 PWM_set(U8 val);
void Temp_check(void);
void Version_check(void);
void Press_check(void);


extern U8 ping(U8 addr);
extern  U8 SC16_Com[9];   
extern  U8 SC16_ComAddr;



//extern  void Power_onoff(U8 sel);

	
// ===========================================================================
//			Hardware-independent ( Logical) primitives
// ===========================================================================
	
	
// ===========================================================================
// END of File
// ===========================================================================
