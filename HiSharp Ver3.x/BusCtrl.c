//  **************************************************************************
//
//       Copyright (c) 1992-2006 Professonal Computer Technology Co., Ltd
//
//      All rights are reserved. Reproduction in whole or in parts is
//  prohibited without the prior written consent of the copyright owner.
//  --------------------------------------------------------------------------
//
//  Module: BUSCTRL.C
//
//  Purpose: Implementation of BUSCTRL.
//
//  Version: 0.01                                   2006/10/22 10:39¤U¤È
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
#include "types.h"
#include "BusCtrl.h"

#include "NED.h"
//	------------------------------------
//			Macro Definitions
//	------------------------------------ 


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
//                      Parallel function description
//==================================================================================
//	
//	
//	
void PCT_WriteAsicByte(U8 _dvc, U8 _pg, U8 _addr, U8 _wdat)
{
	_dvc = 0;			//... temporal

	EA = OFF;		// Disable All Interrupt
	//... P[7:4]:INT[5:2], P1_3:HALE, P1_2:HRDB, P1_1:HWRB, P1_0:HSPB
#ifdef NED
    MCTRL_set();
#else
    MCTRL = 0xf6;		//... initial state
#endif

	if(_pg == DVC_PG0){	HCSB1=0;	HCSB0=0;}
	else if(_pg == DVC_PG1){	HCSB1=0;	HCSB0=1;}
	else if(_pg == DVC_PG2){	HCSB1=1;	HCSB0=0;}
	MDATA =	_addr;
	HALE = 1;
                        #ifdef BDelay
                        //Wait_ms(Delay_val);//ryan..
                        DELAY_FOR(Delay_val); 
                        #endif
	HALE = 0;
	MDATA =	_wdat;
	HWRB = 0;
                        #ifdef BDelay
                        //Wait_ms(Delay_val);//ryan..
                        DELAY_FOR(Delay_val); 
                        #endif
                        
	HWRB = 1;

//	MCTRL_set();//MCTRL = 0xf6;		//... initial state
#ifdef NED
    MCTRL_set();
#else
    MCTRL = 0xf6;		//... initial state
#endif

	HCSB0=1;
	HCSB1=1;
	MDATA =	0xff;
	EA = ON;		// Enable All Interrupt
}

//==================================================================================
//	
//	
//	
void PCT_WriteAsicTable(U8 _dvc, U8 _pg, U8 _addr, U8 *_tbl_ptr, U8 _tbl_cnt)
{
	_dvc = 0;			//... temporal

	EA = OFF;		// Disable All Interrupt
	//... P[7:4]:INT[5:2], P1_3:HALE, P1_2:HRDB, P1_1:HWRB, P1_0:HSPB
	//MCTRL_set();///MCTRL = 0xf6;		//... initial state
#ifdef NED
    MCTRL_set();
#else
    MCTRL = 0xf6;		//... initial state
#endif

	if(_pg == DVC_PG0){	HCSB1=0;	HCSB0=0;}
	else if(_pg == DVC_PG1){	HCSB1=0;	HCSB0=1;}
	else if(_pg == DVC_PG2){	HCSB1=1;	HCSB0=0;}

	do {
		MDATA =	_addr++;
		HALE = 1;
                                #ifdef BDelay
                        //Wait_ms(Delay_val);//ryan..
                        DELAY_FOR(Delay_val); 
                        #endif

		HALE = 0;
	
		MDATA =	*_tbl_ptr++;
		HWRB = 0;
                                #ifdef BDelay
                        //Wait_ms(Delay_val);//ryan..
                        DELAY_FOR(Delay_val); 
                        #endif

		HWRB = 1;
	}while( --_tbl_cnt!=0 );

//	MCTRL_set();///MCTRL = 0xf6;		//... initial state
#ifdef NED
    MCTRL_set();
#else
    MCTRL = 0xf6;		//... initial state
#endif

	HCSB0=1;
	HCSB1=1;
	MDATA =	0xff;
	EA = ON;		// Enable All Interrupt
}

//==================================================================================
//	
//	
//	
U8 PCT_ReadAsicByte(U8 _dvc, U8 _pg, U8 _addr)
{
	register U8 _rdat_;

	EA = OFF;		// Disable All Interrupt
	//... P[7:4]:INT[5:2], P1_3:HALE, P1_2:HRDB, P1_1:HWRB, P1_0:HSPB
	//MCTRL_set();///MCTRL = 0xf6;		//... initial state
#ifdef NED
    MCTRL_set();
#else
    MCTRL = 0xf6;		//... initial state
#endif

	_dvc = 0;			//... temporal
	if(_pg == DVC_PG0){ HCSB1=0; HCSB0=0;}
	else if(_pg == DVC_PG1){ HCSB1=0; HCSB0=1;}
	else if(_pg == DVC_PG2){ HCSB1=1; HCSB0=0;}

	MDATA =	_addr;
	HALE = 1;
                            #ifdef BDelay
  				DELAY_FOR(Delay_val); 
                        //Wait_ms(Delay_val);//ryan..
                        #endif
	HALE = 0;
	MDATA =	0xff;		// port0(MDATA) input mode
	                  #ifdef BDelay
					  DELAY_FOR(Delay_val); 
                        //Wait_ms(Delay_val);//ryan..
                        #endif

	HRDB = 0;
	_rdat_ = MDATA;
	
                                                #ifdef BDelay
                        //Wait_ms(Delay_val);//ryan..
					DELAY_FOR(Delay_val); 
						#endif

	HRDB = 1;

//	MCTRL_set();///MCTRL = 0xf6;		//... initial state
#ifdef NED
    MCTRL_set();
#else
    MCTRL = 0xf6;		//... initial state
#endif

	HCSB0=1;
	HCSB1=1;
	EA = ON;		// Enable All Interrupt
	return _rdat_;
}


//==================================================================================
//	
//	Write Register Address & Data form Table until address=0xFFFF then STOP
//	
void PCT_WriteSTable(U8 _dvc, WRITE_REG_DATA *_tbl_ptr)
{
	#define PAGE GETHBYTE(_tbl_ptr->addr)
	#define ADDR GETLBYTE(_tbl_ptr->addr)

	_dvc = 0;
	while( _tbl_ptr->addr!=0xFFFF ) {
	    if(TW28_ReadByte(PAGE, ADDR) != _tbl_ptr->dat)//William @HS 2007 0829 Ver3.4
	    	{
		TW28_WriteByte(PAGE, ADDR, _tbl_ptr->dat);
	    	}
		_tbl_ptr++;	
	}
}

//==================================================================================
//	
// Change to I2C Control Mode
//	
void PTC_SwitchToI2CMode(void)
{
#ifdef TW28_I2CBUS
	HSPB 	= 1;
	HALE 	= 1;
	MDATA 	= 0xFF;	
	HCSB0 	= 0;
	HCSB1 	= 0;
	HRDB 	= 0;
	HWRB 	= 0;
#endif
}

/*
void MCTRL_set(void)
{

//... P[7:4]:INT[5:2], P2_3:HALE, P2_2:HRDB, P2_1:HWRB, P2_0:HSPB
P2_0=0;///HSPB=0;
P2_1=1;///HWRB=1;
P2_2=1;///HRDB=1;
P2_3=0;///HALE=0;
}
*/
// ===========================================================================
// END of File 
// ===========================================================================

