//  **************************************************************************
//
//       Copyright (c) 1992-2006 Professonal Computer Technology Co., Ltd
//
//      All rights are reserved. Reproduction in whole or in parts is
//  prohibited without the prior written consent of the copyright owner.
//  --------------------------------------------------------------------------
//
//  Module: UART.C
//
//  Purpose: Implementation of UART.
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
#include "UART.h"
#include "Main.h"
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

//#define RS_RECV_MAX_BUFF (80)
#define RS_RECV_MAX_BUFF (100)

//#define RS_RECV_MAX_BUFF (37)	
#ifdef SC16IS750_DEBUG_PRINT
#endif
#define no_parity
BYTE RS_RECVBUF[RS_RECV_MAX_BUFF];
BYTE RsRxRp,RsRxWp;


//	------------------------------------
//			Function Prototypes
//	------------------------------------



// ===========================================================================
//                      Parallel function description
// ===========================================================================
//
//		Initial UART  												   
//
void InitialUART (void)
{
	// Useing Interrupt RS
	#if 1
	PS=0;
	ES=1;
        #endif

#ifdef no_parity        
     	SCON = 0x52;	// Setup Serial control Register
#else
   SCON = 0xD0;//parity bit 
#endif
   
//	// Useing Interrupt Timer1
//	PT1=1;
//	ET1=1;

//	TH1 = B9600;				// 40M HZ		//modify by ryan.
//	TH1 = SET_BAUDRATE(115200);	// 22.118M HZ	  //remask by ryan.
//	TH1 = SET_BAUDRATE(76800);	// 22.118M HZ	  //remask by ryan.
//   TH1=254;
//	TH1 = SET_BAUDRATE(38400);	// 22.118M HZ	  //remask by ryan.
//	TH1 = SET_BAUDRATE(19200);	// 22.118M HZ	  //remask by ryan.
	TH1 = SET_BAUDRATE(9600,0);	// 22.118M HZ	  //remask by ryan.
//       TL1=255;

       //TH1=0;
       TL1=0;
	TR1 = 1; 					// Start timer 1

	RsRxRp = 0;
	RsRxWp = 0;
}

// ===========================================================================
//
//		Serial RX Check 												   
//
BYTE RS_RxReady (void)
{
	if( RsRxWp == RsRxRp ) return false;
	else return true;
}

//=============================================================================
//
//		Serial RX														   
//
BYTE RS_rx (void)
{
	register BYTE	ret;	
	//ES = 0;  //ryan..
	//Kane @HS 2007 0809 Ver3.5
	//if(RS_RECVBUF[RsRxRp+3]=='T' && RS_RECVBUF[RsRxRp+2]=='W' && RS_RECVBUF[RsRxRp+1]=='3'  && RS_RECVBUF[RsRxRp]=='T' )
	//	return TWCMD;
	ret = RS_RECVBUF[RsRxRp];
	RsRxRp++;
	if(RsRxRp >= RS_RECV_MAX_BUFF) 
		RsRxRp = 0;

		
	
	ES = 1;

	return ret;
}

//=============================================================================
//
//		Serial TX														   
//
void RS_tx (BYTE tx_buf)
{
	//TI=1;
		
#if 0


		while(TI==0); 

		
		#ifdef no_parity
				//#eldef UART_debug
					#else
						TB8=parity(tx_buf);
							#endif
			SBUF = tx_buf;


#else
	while(1)
	{
	
           if(TI) {
					#ifdef no_parity
					#else
					//TB8=parity(tx_buf);
					#endif


			//TB8=parity(tx_buf);

			SBUF=tx_buf;
			TI=0;
			break;
			}
	}

	#endif
}



// ===========================================================================
//
//		Serial Interrupt
//
void RS_interrupt(void) interrupt 4 using 1
{

	if( RI ) {					//--- Receive interrupt ----
		RI = 0;
		//WDTCR|=0x10;
	/*
		if(RsRxWp+1==RsRxRp) RsRxRp++;
		if(RsRxWp==RS_RECV_MAX_BUFF-1 && RsRxRp==0) RsRxRp++;
		
		if( RsRxRp >= RS_RECV_MAX_BUFF ) RsRxRp = 0;
*/

		RS_RECVBUF[RsRxWp] = SBUF;
		
				//RS_tx(RS_RECVBUF[RsRxWp] );//ryan..
		//printf(">");
		RsRxWp++;
		if( RsRxWp >= RS_RECV_MAX_BUFF ) RsRxWp = 0;
		
						//#ifdef  UART_debug
						//printf("%x",(U16)RS_RECVBUF[RsRxWp]);
						//#endif
			

	}
	
						
}

// ===========================================================================
// END of File 
// ===========================================================================

