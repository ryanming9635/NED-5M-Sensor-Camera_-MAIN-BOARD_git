//  **************************************************************************
//
//       Copyright (c) 1992-2006 Professonal Computer Technology Co., Ltd
//
//      All rights are reserved. Reproduction in whole or in parts is
//  prohibited without the prior written consent of the copyright owner.
//  --------------------------------------------------------------------------
//
//  Module: UART.H
//
//  Purpose: Implementation of UART.
//
//  Version: 0.01                                   2006/10/22 09:26�U��
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


//	------------------------------------
//			Macro Definitions
//	------------------------------------ 
//
//	functions
//
//#define XTAL40	40    //mask by ryan.

#ifndef XTAL40
	#define XTAL	22118400
#endif

//	��_�������W�v��Q�㰣�ɡA�����ϥέp�⤽���C 
#ifdef XTAL
	#define SET_BAUDRATE(x,y) 256-(XTAL*(1+y)/32/12/x)	// for SMOD = 0 
//	#define SET_BAUDRATE(x) 256-((XTAL*2)/32/12/x)	// for SMOD = 1 


#endif

//
//		XTAL = 40MHz Baudrate Setting
//
#ifdef XTAL40
	#define B1200	169
	#define B2400	213
	#define B4800	234
	#define B9600	245
	#define B19200	251
	#define B28800	252
	#define B38400	253
	#define B57600	254
	#define B115200	255
#endif

//	
//	terminals
//	


//	------------------------------------
//			Type Definitions
//	------------------------------------


//	------------------------------------
//			Variables Definitions
//	------------------------------------
		
	
//	------------------------------------
//			Function Prototypes
//	------------------------------------


// ===========================================================================
//			Hardware-dependent ( Physical) primitives
// ===========================================================================
	extern void InitialUART(void);
	extern BYTE RS_RxReady(void);
	extern BYTE RS_rx(void);
//	extern void RS_tx(BYTE tx_buf);
	 void RS_tx(BYTE tx_buf);
extern void CommandShell(void);
	
// ===========================================================================
//			Hardware-independent ( Logical) primitives
// ===========================================================================
	
	
// ===========================================================================
// END of File
// ===========================================================================
