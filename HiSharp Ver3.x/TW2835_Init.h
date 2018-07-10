//  **************************************************************************
//
//       Copyright (c) 1992-2006 Professonal Computer Technology Co., Ltd
//
//      All rights are reserved. Reproduction in whole or in parts is
//  prohibited without the prior written consent of the copyright owner.
//  --------------------------------------------------------------------------
//
//  Module: TW2835_InitTab.H
//
//  Purpose: Implementation of TW2835_InitTab.
//
//  Version: 0.01                                   2006/10/29 09:02�U��
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
//	R0.01 2006/10/29 09:02�U�� Phoenix Chuang
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
//#define SENSORCHANNEL 3  //mask by ryan..
#define SENSORCHANNEL	0
//
//	functions
//

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
	extern void PCT_InitialTW2835(void);
	extern void PCT_TW2835ResetN(void);
	extern void PCT_TW2835_Initial(void);
	extern void PCT_ChangeSystemType(U8 _sys);
	
// ===========================================================================
//			Hardware-independent ( Logical) primitives
// ===========================================================================
	
	

// ===========================================================================

// ===========================================================================
// END of File
// ===========================================================================


