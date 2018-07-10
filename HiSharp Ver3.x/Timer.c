//  **************************************************************************
//
//       Copyright (c) 1992-2006 Professonal Computer Technology Co., Ltd
//
//      All rights are reserved. Reproduction in whole or in parts is
//  prohibited without the prior written consent of the copyright owner.
//  --------------------------------------------------------------------------
//
//  Module: Interrupt.C
//
//  Purpose: Implementation of Soft Timer.
//
//  Version: 0.01                                   2007/4/27 04:27¤U¤È
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
//	R0.01 2007/4/27 04:27¤U¤È Phoenix Chuang
//	Reason:
//		1. Original.
//	Solution:
//	
//  **************************************************************************
// 	-----------------------------------
//			Header Files
//	----------------------------------- 
#include "Types.h"
#include "UART.h"
#include "Timer.h"


//	------------------------------------
//			Macro Definitions
//	------------------------------------ 


//	------------------------------------
//			Type Definitions
//	------------------------------------


//	------------------------------------
//			Variables Definitions
//	------------------------------------
data user_timer[TIMER_NUM];
extern U8 timer2_loop;
extern U8 get_data_addr;
extern U8 get_data_val;
extern void Get_Data(U8 addr, U8 val);
extern U8 Temp_timeout;
//	------------------------------------
//			Function Prototypes
//	------------------------------------



// ===========================================================================
//                      Parallel function description
// ===========================================================================
// ===========================================================================
//
//		Interrupt Initial
//
void InitialTimer0(void){
//	U8 i;
	
	//PT0=1;
	//ET0=1;
	//TH0 = 0;	// SET TIMER0 TH0
	//TL0 = 0;	// SET TIMER0 TL0
	//TH0 = TIME0H;	// SET TIMER0 TH0
	//TL0 = TIME0L;	// SET TIMER0 TL0
	//TH0 = (65536-10)>>8;	// SET TIMER0 TH0
	//TL0 =  (65536-10)&0xff;	// SET TIMER0 TL0

	TR0 = 1;		// SET ON TIMER0
      
    //TMOD|=0x02;  //8bit
   //TH0=184;    //TH0 184 for 100Hz 
#if 1
   // TH0=(184-100)+100;    //for 1.2KHz of PWM. 
#if 1		//ryan@20151019
TH0=239;    //for 5.08KHz of PWM. 
#else
TH0=(184-100)+87;    //171//for 1KHz of PWM. 
#endif   
//TH0=(184-100)+76;    //for 900Hz of PWM. 

#else
    TH0=184-100;    //TH0 84 for 500Hz 
#endif
	
  //  TH0=0;    //TH0 84 for 500Hz 

        TL0=0;

      //  TL0=0;
       //TMOD=0x01;    //16bit
	//TMOD=0x00;   ///  13bit

	//for(i=0; i<TIMER_NUM; i++)
	//	DisUserTimer(i);
}



void InitialTimer2(void)
{
	U8 i;

        TR2 =1;
        ET2=1;
        PT2=1;	
        T2MOD=0x00;
        T2CON=0x04;   // SET ON TIMER2

      TF2=0;
	TH2 = TIME2H;	// SET TIMER0 TH0
	TL2 = TIME2L;	// SET TIMER0 TL0
			
	for(i=0; i<TIMER_NUM; i++)
		DisUserTimer(i);

}






// ===========================================================================
//
//		Timer/Counter 0 Interrupt
//
void Timer0_interrupt(void) interrupt 1 using 1
{
    
	EA = OFF;		// Disable All Interrupt
	TH0 = TIME0H;	// SET TIMER0 TH0
	TL0 = TIME0L;	// SET TIMER0 TL0
	TF0 = OFF;

       // P0_0^=1;

	//if(USERTMVAL0>1) USERTMVAL0--;
	//if(USERTMVAL1>1) USERTMVAL1--;
	//if(USERTMVAL2>1) USERTMVAL2--;

	EA = ON;		// Enable All Interrupt
}
//-------------------------------------
extern U16 timerout3; 
extern U16 timerout4;
void Timer2_interrupt(void) interrupt 5 using 1		
{

	EA = OFF;		// Disable All Interrupt
	TH2 = TIME2H;	// SET TIMER0 TH0
	TL2 = TIME2L;	// SET TIMER0 TL0
//	TH2 = (65535-180)>>8;	// SET TIMER0 TH0
//	TL2 = ((65535-180)&0x00ff);	// SET TIMER0 TL0


       TF2 = OFF;

   // P0_0^=1;

	if(USERTMVAL0>1) USERTMVAL0--;
	if(USERTMVAL1>1) USERTMVAL1--;
	if(USERTMVAL2>1) USERTMVAL2--;

	if(USERTMVAL3>1) USERTMVAL3--;

	if(USERTMVAL4>1) USERTMVAL4--;
	if(USERTMVAL5>1) USERTMVAL5--;
	
	if(timerout1>1) timerout1--;	
	if(timerout2>1) timerout2--;
#if 0//ryan@20151106
	//if(timerout3>1) timerout3--;
	if(timerout3<=CB_delay) timerout3++;
	if(timerout4<=CB_delay) timerout4++;
#endif
	if(Temp_timeout>1)Temp_timeout--;//ryan@20150908
	EA = ON;		// Enable All Interrupt
}

// ===========================================================================
//
//		
//


// ===========================================================================
// END of File 
// ===========================================================================
