//  **************************************************************************
//
//       Copyright (c) 1992-2006 Professonal Computer Technology Co., Ltd
//
//      All rights are reserved. Reproduction in whole or in parts is
//  prohibited without the prior written consent of the copyright owner.
//  --------------------------------------------------------------------------
//
//  Module: Main.C
//
//  Purpose: Implementation of Main.
//
//  Version: 0.01                                   2006/10/22 10:39下午
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
//	R0.01 2006/10/22 10:39下午 Phoenix Chuang
//	Reason:
//		1. Original.
//	Solution:
//	
//  **************************************************************************
// 	-----------------------------------
//			Header Files
//	----------------------------------- 
#include "types.h"
#include "Main.h"
#include "Timer.h"
#include "UART.h"
#include "BusCtrl.h"
#include "TW2835_Init.h"
#include "CommandShell.h"
#include "OSDAction.h"
#include "NED.h"    //add by ryan.
#include "Printf.h"
//#include "SST89x5xxRD2.H"

//	------------------------------------
//			Macro Definitions
//	------------------------------------ 


//	------------------------------------
//			Type Definitions
//	------------------------------------


//	------------------------------------
//			Variables Definitions
//	------------------------------------
	U16 _delay;
	U8 bdata commFlag;
	sbit comm_chk_flag = commFlag^0;
	sbit osd_chk_flag = commFlag^1;
	COMMAND_BUFFER RScommand;
	bit VlossFlag;
//------------------------------
bit data_chk_flag=0;    //ryan..
  
U16 ADC_Val[2]={0,0};
U8 m_current=0;
U8 PIP_flag=0;
U8 Main_f=1;
U8 Small_f=2;
U8 timer2_loop;
U8 boot_flag=1;
extern U8 Temp_timeout;
extern U8 Com_pos;
extern U8 Com_Addr;
extern U8 Com_start;
extern U8 Com_end;
extern U8 Com_run;
extern U8 Monitor_current;
extern U8 Monitor_mode;
extern U8 Monitor_state;
extern U8 Back_f;
extern U8 Shrink_f;
extern  U8 Crop_f;//20150413
extern  U8 DRP_ID[9];
extern BYTE RsRxRp,RsRxWp;
extern U8 Camera_temp0;
extern U8 Camera_temp1;
extern U8 Camera_press0;
extern U8 Camera_press1;
extern U8 Camera_press2;
extern U8 Camera_press3;
extern U16 SC16_busy_flag;
extern  U8 work_flag=0;//20150814
 U8 SC16_com_state=0;
extern U8 Camera_ver0;
extern U8 Camera_ver1;
extern U8 Camera_ver2;

extern U8 get_data_addr;
extern U8 get_data_val;

extern U8 Camera_flag;

U16 timerout1=0;  
U16 timerout2=0;  
U16 timerout3=0; 
U16 timerout4=0;
U8 Temp_timeout=1;
U8 CB_flag=0;
U8 CB_timeout=0;
//extern U16 USERTMVAL6;
//-------------------------------

//data U8 *mode="mode 0\r\n";
// char *test="hscom 1 1 ch0:1%1bx ch1:0%1bx ch2:0%1bx ch3:0%1bx\n\r";

//code U8 *test="hscom 1 1 ch1:12 ch0:02 ch2:02 ch3:03\r\n";  //camA
 //char *test="hscom 1 1 ch1:12 ch0:02 ch2:02 ch3:03\n\r";  //camB
 //char *test="hscom 2 2 ch0:12 ch1:02 ch2:02 ch3:03\n\r";  //camB+A
 //char *test="hscom 2 2 ch2:02 ch3:13 ch0:02 ch1:02\n\r";  //camR+C
 
//	------------------------------------
//			Function Prototypes
//	------------------------------------



// ===========================================================================
//                      Parallel function description
// ===========================================================================
//
//	Command Shell for Debug
//


void CommandShell(void)
{

		data BYTE ch;
		static BYTE etx_flag=0;//ryan@20150605

		if( RS_RxReady() == true )
		{	
		
		WDTCR|=0x10;
				ch=RS_rx();

						#ifdef  UART_debug
						printf("%x",(U16)(ch));
						#endif
									
				#if 1        
					
					if(ch==STX&&Com_start==0)
	 				{
					Com_pos=1;
					//RScommand.WritePtr=1;
					SC16_Com[0]=ch;	
						#ifdef  SC16IS750_DEBUG_PRINT 
						printf("\r\nCom_pos=%x  data=%x",(U16) (Com_pos-1), (U16) SC16_Com[Com_pos-1]);
						printf("\r\nCom_start");
						#endif	
					Com_start=1;
	 				}
					///ryan@20150605
				else if((ch==ETX)&&((SC16_Com[1]==0x52)||(SC16_Com[1]==0x53))&&(etx_flag==0)&&Com_pos<=3)
						{
						etx_flag=1;
						SC16_Com[Com_pos]=ch;						
						Com_pos++;
						}
					else if(ch==ETX&&Com_end==0)
					{

						SC16_Com[Com_pos]=ch;						
						Com_pos++;
						Com_end=1;
						etx_flag=0;///end of loop
						#ifdef  SC16IS750_DEBUG_PRINT 
						printf("\r\nCom_pos=%x  data=%x",(U16) (Com_pos-1), (U16) SC16_Com[Com_pos-1]);
						printf("\r\nCom_end");
						#endif	
					}
					else if(Com_end==1)
					{
						
					SC16_Com[Com_pos]=ch;	

						#ifdef  SC16IS750_DEBUG_PRINT 
						printf("\r\nCom_pos=%x  data=%x",(U16) (Com_pos), (U16) SC16_Com[Com_pos]);
						printf("\r\nBCC check..");
						#endif	
	   	         			#ifdef  UART_debug
						printf("*");
						#endif
							
						if(SC16_BCC_Check(&SC16_Com[0],4))
						{
						RScommand.commFlage = true;

							RScommand.commBuf[0]=SC16_Com[1];  
							RScommand.commBuf[1]='\0';
						
						Com_run=SC16_Com[2];
				
						RScommand.WritePtr=2;
						}
						else	
						{							
						ResetCommSell();
						}
		
					}
					else
						{
						SC16_Com[Com_pos]=ch;						
						Com_pos++;
						if(Com_pos>8) ResetCommSell();
	
						#ifdef  SC16IS750_DEBUG_PRINT 
						printf("\r\nCom_pos=%x  data=%x",(U16) (Com_pos-1), (U16) SC16_Com[Com_pos-1]);
						#endif	
						}

#else
		switch(ch) {
			    #if 1
				
			case 0x03:
				RScommand.commBuf[RScommand.WritePtr] = '\0';
				RScommand.commFlage = true;
				chkStartCommShell(RScommand.commBuf);
				if( comm_chk_flag ) NewLine();

				#ifdef  SC16IS750_DEBUG_PRINT 
     printf("\r\nget data=%x %x %x %x",(U16)RScommand.commBuf[0],(U16)RScommand.commBuf[1]\
       ,(U16)RScommand.commBuf[2],(U16)RScommand.commBuf[3]);
				
		  		#endif  
				
				break;
				#elif 0
				
			case '\r':
				RScommand.commBuf[RScommand.WritePtr] = '\0';
				RScommand.commFlage = true;
				chkStartCommShell(RScommand.commBuf);
				if( comm_chk_flag ) NewLine();
				break;
				#endif	
			case 0x08:
				RScommand.WritePtr--;
				break;

			default:
				RScommand.commBuf[RScommand.WritePtr] = ch;
				RScommand.WritePtr++;
				break;

				
		}
		#endif

	}
     else
     	{
timerout4=0;
     	}
     

     
}


// ===========================================================================
//
//
//
void NewLine(void)
{
	puts("\r\n");								    
}

// ===========================================================================
//
//
//
void PutsP(BYTE *ptr)
{
	data BYTE ch;
	
	while(*ptr!='\0') {
		ch = *ptr++;
		RS_tx(ch);
	}
}

// ===========================================================================
//
//	Restart Command Shell 
//
void ResetCommSell(void)
{
	//if( comm_chk_flag ) PutsP("Debug Program >");
	
	Com_start=0;  //ryan..
	Com_end=0;
	Com_pos=0;
	SC16_Com[0]=0;
	SC16_Com[1]=0;
	SC16_Com[2]=0;
	SC16_Com[3]=0;
	SC16_Com[4]=0;
	SC16_Com[5]=0;
	SC16_Com[6]=0;
	SC16_Com[7]=0;
	SC16_Com[8]=0;
	
	RScommand.WritePtr = 0;
	RScommand.commFlage = false;
	RScommand.commBuf[0] = '\0';
}

// ===========================================================================
//
//	Falsh OSD Contril
//
void PCT_FlashOSDCtrl(U8 _on)
{
	if(_on) osd_chk_flag=false;
	else osd_chk_flag=true;
}


// ===========================================================================
//
//	Initial Command Shell 
//
void InitialCommShell(void)
{
	comm_chk_flag=false;
	osd_chk_flag=false;

	//VlossState=0;
	VlossFlag=0;
	VlossCount=0;
}

// ===========================================================================
//
//	Start Command Shell 
//
void chkStartCommShell(char *ptr)
{
	if( comm_chk_flag ) return;
	if( strcmp(ptr,"PCT")==0 ) comm_chk_flag=true;
}

void Wait_ms(U16 Tms)

{
//	#define CPU_CLK_KHZ		40000
#define CPU_CLK_KHZ		22118
#define CPU_SPEED	1
#define CountStick      (1000000U/((CPU_CLK_KHZ*CPU_SPEED)/12))/20    

//#define CountStick      (1000000U/((CPU_CLK_KHZ*CPU_SPEED)/12))/10  
           U16 count;

           while(Tms)

           {

                     for(count=0; count<CountStick; count++);//total 20 clock for this loop

                     Tms--;

           }
}

// ===========================================================================
//
//
//

extern  U8 Cam_boot_flag;//ryan@20151201
void main(void)
{
	U8 Counter=0;
	U16 readtemp=0;
	U8 OsdCount1=200;//Kane @HS 2007 0725 Ver3.4
	U8 OsdCount2=100;//Kane @HS 2007 0725 Ver3.4
	U8 Camera_speed=0;
  // U8 loop=0,lp2=0,lp3=0;  //ryan..
 // U8 x,y,z;

  #if 0
 char busw1[14]={"busw 0 1 A1 11"};  
 char busw2[14]={"busw 0 1 A2 D7"};  
 char yvmix[8]={"yvmix 2 "};
 
char mode[7]={"mode 0 "};
 char test[38]={"hscom 3 3 ch0:12 ch1:12 ch2:12 ch3:03 "};

 #endif

InitialMPU();	
 PWM_init(); 

//ADC_FPBS();
#if 0

  while(0)
{
//P0=0x00;
//printf(">");//ryan..
//HCSB1=0; HCSB0=0;
//P3_1=0;
I2C_SDA=1;
USERTMVAL1=2;
while(USERTMVAL1>=2);
I2C_SDA=0;
USERTMVAL1=2;
while(USERTMVAL1>=2);

#if 0
MDATA=0x00;	
HSPB	=	0;
HWRB	=	0;
HRDB	=	0;
HALE	=	0;
HCSB0	=	0;
HCSB1	=	0;


//	MCTRL=1;
Wait_ms(1);
//P3_1=1;

MDATA=0xff;	
HSPB	=	1;
HWRB	=	1;
HRDB	=	1;
HALE	=	1;
HCSB0	=	1;
HCSB1	=	1;
//	MCTRL=0;
Wait_ms(1);
#endif
//P0=0xff;
//HCSB1=1; HCSB0=1;
//Wait_ms(20);
//ping(DVR_address);
//ping(RF_ID_address);
//ping(Camera_address);

}

#endif

	InitialCommShell();
	ResetCommSell();

#if 1
/*
Set_PWM_Output(0,0);
Set_PWM_Output(1,0);
Set_PWM_Output(2,0);
Set_PWM_Output(3,0);
Set_PWM_Output(4,0);
Set_PWM_Output(5,0);
*/
Power_onoff(0);
SC16_init();


Monitor_set(Monitor_offset+3);

///TW28_WriteByte(1,0xab,0x0a);//ryan@20150522 color bar


#endif

#if 0 
TW28_WriteByte(1,0x11,0x00);
TW28_WriteByte(1,0x19,0x00);
TW28_WriteByte(1,0x21,0x00);
TW28_WriteByte(1,0x29,0x00);
#endif

GPIO_check();   //TX有錯誤所以開機只做一次baudrate設定

//TW28_WriteByte(0,0x25,0x80);  //ryan
EnUserTimer(USERTMID3,40);    
EnUserTimer(USERTMID4,480);
timerout1=480;
//EnUserTimer(USERTMID5,16);//for camera moving//300ms
EnUserTimer(USERTMID5,4);//for camera moving//300ms
timerout2=600+600+600;//for camera speed//15s
//EnUserTimer(USERTMID6,600+600+600);//for camera speed//15s
Camera_speed=(((DVR_GetIO()&0x3f)&0x10)>>4);

	while(1){
      
	CommandShell();
	if(RScommand.commFlage == true) PCT_RunCommShell(RScommand.commBuf); 
	if(RScommand.commFlage == true) ResetCommSell(); 
	   
	if(VlossFlag==1)
	{
		if(PCT_CheckSystem())//Kane Modified
			VlossFlag=0;
	}

	//<<<<<<<<<<<<<<<<<<<<<<<
		
	if(RS_RxReady()) EnUserTimer(USERTMID1,OsdCount1);//Kane @HS 2007 0725 Ver3.4



	if(USERTMVAL1==1)
	{
	//PCT_AudioActionForHS();
	//PCT_OSDActionForHS();
	//PCT_FlashOSDCtrl(OFF);
	DisUserTimer(USERTMID1);
	EnUserTimer(USERTMID0,OsdCount2);//Kane @HS 2007 0725 Ver3.4	// Reset Scan Time, Delay Check and show
	}

						 if((USERTMVAL0==1)&&(Com_start==0)) 
						{
						 // Temp_check(); 
	  						//Press_check(); 
						PCT_GetVideoSignalStatus();	// Check and Show "VLoss", scan time = 500ms
						//GPIO_check();   //ryan..
						#ifndef screen3
							if(Monitor_state!=Monitor_mode)
							{
							Monitor_set(Monitor_mode);
							}
						#endif
						
						//#if 1///#ifdef  get_data_debug
							//printf("\r\n RsRxRp=%x",(U16) RsRxRp); 	
							//#endif
							
						EnUserTimer(USERTMID0,20);
							
						 }

 	if((USERTMVAL5==1)&&(Camera_flag>=1)&&(Cam_boot_flag==1))//trigger the  up,down,ccw,cw functions
	{
		EnUserTimer(USERTMID5,4);
		Camera_move();
	 
	}


	

	  #if 0///ryan@20150804
	   Temp_check(); 
	  	Press_check(); 
	  #else

	
		if((USERTMVAL3==1)&&(Camera_flag==0)&&(Cam_boot_flag==1)) 
		{
	 		#ifdef  get_data_debug
	  		printf("\r\n SC16_com_state=%x",(U16) SC16_com_state);
	  		#endif  

		SC16_data_reset(buff_sel(SC16_com_state));
		SC16_com_state++;
		EnUserTimer(USERTMID3,40);
		if(SC16_com_state>=buff_num) SC16_com_state=0;
		//work_flag=1;
		} 
		else
		SC16_DataCheck();   //check sc16i750 


		if(timerout1==1)
		{
		SC16_busy_flag=0;
		timerout1=480;
   					#ifdef  get_data_debug
					printf("\r\n SC16_busy_flag_clear=%x",(U16) SC16_busy_flag);
					#endif  
		}
#endif


	//SC16_DataCheck();   //check sc16i750 

//set camera speed
if((timerout2==1)&&(Cam_boot_flag==1))
{
Set_Camera_speed(Camera_speed);	
timerout2=0;
}

 		WDTCR|=0x10;

		#if 0//ryan@20151106
		while(CB_flag==1)
		{
			//if((get_data_addr)&&(timerout3>=CB_delay))
			if(timerout3>=CB_delay)
			{
			Get_Data(get_data_addr, get_data_val);
			
			CB_flag=0;
			timerout4=0;
			}
			WDTCR|=0x10;			 		
		}
		
		timerout3=0;
		#endif



	}
	OsdCount1=10;//Kane @HS 2007 0725 Ver3.4
	OsdCount2 = 20;//Kane @HS 2007 0725 Ver3.4

   
}

//void main_loop(void)
//{


//}
// ===========================================================================
//
//
//
void InitialMPU(void){

	IP = 0x00;
	IE = 0x00;		

//	PCON = 0x80;	// Set SMOD bit7 in power ctrl reg     //smod=1
					// This bit doubles the baud rate 
	PCON = 0x00; 	// Clear SMOD bit7 in power ctrl reg   //smod=0
					// This bit doubles the baud rate 
	//watch dog
	 WDTCR=0x27;   //pre-scaling value: 256  //4s will reset
	 
	PSW  = 0x00;	// Set Program state Register
	TMOD = 0x22;	// Set Timer MODE Register
//	TMOD = 0x12;	// Set Timer MODE Register
					// Timer0: MODE=1, 16-BIT Timer
					// Timer1: MODE=2, 8-BIT Auto Reload )
  //  TCON = 0x00;	// Set Timer0/Timer1 Control Register
    TCON = 0x00;	// Set Timer0/Timer1 Control Register
					// Timer0=OFF,Timer1=OFF
//	SCON = 0x52;	// Setup Serial control Register
//	    SCON = 0x00;
					// Mode 1: Start Bit=1,Stop Bit=1,Data Bit=8 
					// and ready Transmit
					// REN: enable receiver 
	
	InitialUART();
	InitialTimer0();
      InitialTimer2();
    

//XICON=0x00;
//AUXIE=0x00; 
AUXR=0;
AUXR1=0;
	TI = 1; 		//* Set TI to indicate ready to xmit */
	EA=1;
	_nop_();
    


#if 0

CL=0; //PCA counter..
CH=0;
CMOD=0x04; // PWM use to  timer-0
CCON=0x40;  

//CMOD=0x00; // PWM use to  crystal
//CL=(65536-High);    //PCA counter..
//CH=(65536-High)>>8;
//CL=1;    //PCA counter..
//CH=128;

AUXR2|=0x80;    //Fosc/12 for timer-0
//CMOD=0x00;///  /12    ///22.1184MHz
//CMOD=0x02;/// /2

CCAP0L=0x00;
CCAP0H =(256-128);

CCAP1L=0x00;
CCAP1H =(256-128);

CCAP2L=0x00;
CCAP2H =(256-128);

CCAP3L=0x00;
CCAP3H =(256-128);

CCAP4L=0x00;
CCAP4H =(256-128);

CCAP5L=0x00;
CCAP5H =(256-128);

CCAPM0  = 0x42;
CCAPM1  = 0x42;
CCAPM2  = 0x42;
CCAPM3  = 0x42;
CCAPM4  = 0x42;
CCAPM5  = 0x42;

PCAPWM0 = 0x00;
PCAPWM1 = 0x00;
PCAPWM2 = 0x00;
PCAPWM3 = 0x00;
PCAPWM4 = 0x00;
PCAPWM5 = 0x00;


 //-------------------------------
#endif
P0M0=0;
P0M1=0;

P1M0|=0x03;   //ADC0 & ADC1
P1M1&=0xFC;  
 
P2M0=0;
P2M1=0;

P3M0=0x00;
P3M1=0x00;
 
P4M0=0x00;
P4M1=0x04;
P4_1=0;


P1_2=0;
P1_3=0;
P1_4=0;
P1_5=0;
P1_6=0;
P1_7=0;

//P1_1=1;//ryan@20150908

}
//----------------------------------------------------------

void Set_PWM_Output (U8 addr, U8 val)
{

U8 num[6]={255,200,150,100,50,0};


//CL=0; //PCA counter..
//CH=0;
//CMOD=0x04; // PWM use to  timer-0
//CCON=0x40; 
//AUXR2|=0x80;    //Fosc/12 for timer-0



 switch(addr)
    {
    case 0:	
						CCAP0L=0x00;  
		          if(val==0) 	CCAPM0=0x00;
 					else	 CCAPM0=0x42;									
							
                 CCAP0H =num[val];      
                 PCAPWM0 = 0x00;
                break;
    case 1: 
						CCAP1L=0x00;  
		          if(val==0) 	CCAPM1=0x00;
 					else	 CCAPM1=0x42;									
					
               CCAP1H =num[val];    
                PCAPWM1 = 0x00;
                break;
    case 2:  
						CCAP2L=0x00;  
		          if(val==0) 	CCAPM2=0x00;
 					else	 CCAPM2=0x42;
					
                CCAP2H =num[val];   
                PCAPWM2 = 0x00;
                break; 
    case 3:
						CCAP3L=0x00;  
		          if(val==0) 	CCAPM3=0x00;
 					else	 CCAPM3=0x42;	
					
                CCAP3H =num[val];   
                PCAPWM3 = 0x00;
                break;
    case 4:
						CCAP4L=0x00;  
		          if(val==0) 	CCAPM4=0x00;
 					else	 CCAPM4=0x42;	
					
                CCAP4H =num[val];  
                PCAPWM4 = 0x00;
                break;
    case 5:
						CCAP5L=0x00;  
		          if(val==0) 	CCAPM5=0x00;
 					else	 CCAPM5=0x42;
					
                CCAP5H =num[val];  
                PCAPWM5 = 0x00;
                break;
     default:	
			break;
    }


}

//-----------------------------------------------------------
void PWM_init(void)
{

CL=0; //PCA counter..
CH=0;
CMOD=0x04; // PWM use to  timer-0
//CMOD=0x00; // PWM use to  timer-0

CCON=0x40;  

//CMOD=0x00; // PWM use to  crystal
//CL=(65536-High);    //PCA counter..
//CH=(65536-High)>>8;
//CL=1;    //PCA counter..
//CH=128;

AUXR2|=0x80;    //Fosc/12 for timer-0
//CMOD=0x00;///  /12    ///22.1184MHz
//CMOD=0x02;/// /2

/*
CCAP0L=0x00;
CCAP0H =(256-128);

CCAP1L=0x00;
CCAP1H =(256-128);

CCAP2L=0x00;
CCAP2H =(256-128);

CCAP3L=0x00;
CCAP3H =(256-128);

CCAP4L=0x00;
CCAP4H =(256-128);

CCAP5L=0x00;
CCAP5H =(256-128);

CCAPM0  = 0x42;
CCAPM1  = 0x42;
CCAPM2  = 0x42;
CCAPM3  = 0x42;
CCAPM4  = 0x42;
CCAPM5  = 0x42;

PCAPWM0 = 0x00;
PCAPWM1 = 0x00;
PCAPWM2 = 0x00;
PCAPWM3 = 0x00;
PCAPWM4 = 0x00;
PCAPWM5 = 0x00;
*/
}

//-----------------------------------------
U8 Monitor_set(U8 val)
{
char busw1[14]={"busw 0 1 A1 11"};  
char busw2[14]={"busw 0 1 A2 D7"};  
char yvmix[8]={"yvmix 4 "};
char mode[7]={"mode 0 "};


//char conf[38]={"hscom 2 2 ch0:12 ch1:12 ch2:02 ch3:03 "};
//char conf1[38]={"hscom 1 1 ch0:12 ch1:02 ch2:02 ch3:03 "};
//ch0 Camera  
//ch1 DVR       
//ch2 Rear


#ifdef OSD_off

char conf1[38]={"hscom 1 1 ch0:10 ch1:00 ch2:00 ch3:00 "};   // C
char conf2[38]={"hscom 1 1 ch2:10 ch1:00 ch0:00 ch3:00 "};   // R
char conf3[38]={"hscom 1 1 ch1:10 ch0:00 ch2:00 ch3:00 "};  // D

char conf4[38]={"hscom 2 2 ch2:10 ch0:10 ch1:00 ch3:00 "};   //CR
char conf5[38]={"hscom 2 2 ch0:10 ch2:10 ch1:00 ch3:00 "};  //RC

char conf6[38]={"hscom 2 2 ch1:10 ch0:10 ch2:00 ch3:00 "};  // DC
char conf7[38]={"hscom 2 2 ch0:10 ch1:10 ch2:00 ch3:00 "};  // CD

char conf8[38]={"hscom 2 2 ch1:10 ch2:10 ch0:00 ch3:00 "};  // DR
char conf9[38]={"hscom 2 2 ch2:10 ch1:10 ch2:00 ch3:00 "};  // RD

char conf10[38]={"hscom 3 3 ch0:10 ch1:10 ch2:10 ch3:00 "};


#else
char conf1[38]={"hscom 1 1 ch0:12 ch1:02 ch2:02 ch3:03 "};   // C
char conf2[38]={"hscom 1 1 ch2:12 ch1:02 ch0:02 ch3:03 "};   // R
char conf3[38]={"hscom 1 1 ch1:12 ch0:02 ch2:02 ch3:03 "};  // D

char conf4[38]={"hscom 2 2 ch2:12 ch0:12 ch1:02 ch3:03 "};   //CR
char conf5[38]={"hscom 2 2 ch0:12 ch2:12 ch1:02 ch3:03 "};  //RC

char conf6[38]={"hscom 2 2 ch1:12 ch0:12 ch2:02 ch3:03 "};  // DC
char conf7[38]={"hscom 2 2 ch0:12 ch1:12 ch2:02 ch3:03 "};  // CD

char conf8[38]={"hscom 2 2 ch1:12 ch2:12 ch0:02 ch3:03 "};  // DR
char conf9[38]={"hscom 2 2 ch2:12 ch1:12 ch2:02 ch3:03 "};  // RD

char conf10[38]={"hscom 3 3 ch0:12 ch1:12 ch2:12 ch3:03 "};

#endif

char conf11[38]={"hscom 1 1 ch3:00 ch1:00 ch2:00 ch0:00 "};

//PU8  ptr;
U8 Error=0;
U8 ch=0;

ch=(val-Monitor_offset);

#ifdef Crop_Shrink_flag//20150413
if(ch>=10)
	ch=ch-4;
else
	Crop_f=0;//clear Crop_f	  

#endif

 Monitor_state=val;  

switch(ch)
{
case 0:	 PIP_flag=1; break;
case 1:  PIP_flag=0; break;
case 2: 
		Back_f=0;			
	      Main_f=1;  
		  break;		
case 3: 	Back_f=1;  
	      Main_f=2;
 		  break;		
case 4: 	Shrink_f=1;
		Main_f=4; 
		break;		
case 5:  Shrink_f=0;  
		Main_f=1;
	      break;
#ifdef Crop_Shrink_flag//ryan@20150413
case 6:	      //crop+shrink
	Crop_f=0x14;
	    break;
case 7:		 //shrink+crop
	Crop_f=0x41;	
	    break;
#endif
default: 	Main_f=1; break;
}


if(Crop_f>=1)
{
m_current=Crop_f;//ryan@20150413
}
else if(PIP_flag==1)
	{
		if(Back_f)
			{
						if(Shrink_f==1)
						{
						Main_f=2;
						Small_f=4;
						}
						else
						{
						Main_f=2;
						Small_f=1;						
						}
			}
		else
			{
						if(Shrink_f==1)
						{
						Main_f=4;
						Small_f=2;
						}
						else
						{
						Main_f=1;
						Small_f=2;						
						}

			}

		m_current=(Main_f<<4)|Small_f;
			
	}
else
{
			
			if(Back_f)
			{
						Main_f=2;
			}
			else
			{
						if(Shrink_f==1)
						{
						Main_f=4;
						Small_f=2;
						}
						else
						{
						Main_f=1;
						Small_f=2;						
						}

			}
				
		m_current=Main_f<<4;

}




if(boot_flag)
{

	//InitialCommShell();
	PCT_InitialTW2835();	// Initial RssetN for TW2835
	//ResetCommSell();

memcpy ((RScommand.commBuf), busw1, sizeof(busw1) );
PCT_RunCommShell(RScommand.commBuf); 

memcpy ((RScommand.commBuf), busw2, sizeof(busw2) );
PCT_RunCommShell(RScommand.commBuf); 

//memcpy ((RScommand.commBuf), yvmix, sizeof(yvmix) );
//PCT_RunCommShell(RScommand.commBuf); 

memcpy ((RScommand.commBuf), mode, sizeof(mode)  );
//printf("RScommand.commBuf=%s\r\n",RScommand.commBuf);  //ryan
PCT_RunCommShell(RScommand.commBuf); 
}
else
{
	#ifdef black_change
		#if 1 
		TW28_WriteByte(1,0x11,0x00);
		TW28_WriteByte(1,0x19,0x00);
		TW28_WriteByte(1,0x21,0x00);
		//TW28_WriteByte(1,0x29,0x00);

		TW28_WriteByte(0,0xc3,0xf8);
		TW28_WriteByte(0,0xc4,0xff);
		TW28_WriteByte(1,0x0f,0x00);/// black boundary color
		//TW28_WriteByte(1,0x5f,0x30);
		#endif
		
	memcpy ((RScommand.commBuf), conf11, sizeof(conf11) );
	PCT_RunCommShell(RScommand.commBuf); 
	Wait_ms(25+100+100);
	#endif


	
}


#ifdef screen3
if(boot_flag==1) m_current=10;
#endif

switch(m_current)
{
#if 1
	#if 1//ryan
case 0x10: memcpy ((RScommand.commBuf), conf1, sizeof(conf1) ); TW28_WriteByte(1,0x0f,0x03);break;  //C
case 0x20: memcpy ((RScommand.commBuf), conf2, sizeof(conf2) ); TW28_WriteByte(1,0x0f,0x03);break;  //R
case 0x40: memcpy ((RScommand.commBuf), conf1, sizeof(conf1) ); TW28_WriteByte(1,0x0f,0x03);break;  //D
case 0x12: memcpy ((RScommand.commBuf), conf4, sizeof(conf4) ); break;  //CR
case 0x21: memcpy ((RScommand.commBuf), conf5, sizeof(conf5) ); break;  //RC
case 0x14: memcpy ((RScommand.commBuf), conf6, sizeof(conf6) ); break;  //DC
case 0x41: memcpy ((RScommand.commBuf), conf7, sizeof(conf7) ); break;  //CD
case 0x24: memcpy ((RScommand.commBuf), conf5, sizeof(conf5) ); break;  //DR
case 0x42: memcpy ((RScommand.commBuf), conf4, sizeof(conf4) ); break;  //RD

	#else
case 0x10: memcpy ((RScommand.commBuf), conf1, sizeof(conf1) ); TW28_WriteByte(1,0x0f,0x03);break;  //C
case 0x20: memcpy ((RScommand.commBuf), conf2, sizeof(conf2) ); TW28_WriteByte(1,0x0f,0x03);break;  //R
case 0x40: memcpy ((RScommand.commBuf), conf3, sizeof(conf3) ); TW28_WriteByte(1,0x0f,0x03);break;  //D
case 0x12: memcpy ((RScommand.commBuf), conf4, sizeof(conf4) ); break;  //CR
case 0x21: memcpy ((RScommand.commBuf), conf5, sizeof(conf5) ); break;  //RC
case 0x14: memcpy ((RScommand.commBuf), conf6, sizeof(conf6) ); break;  //DC
case 0x41: memcpy ((RScommand.commBuf), conf7, sizeof(conf7) ); break;  //CD
case 0x24: memcpy ((RScommand.commBuf), conf8, sizeof(conf8) ); break;  //DR
case 0x42: memcpy ((RScommand.commBuf), conf9, sizeof(conf9) ); break;  //RD
	#endif
#ifdef screen3
case 10: 	    memcpy ((RScommand.commBuf), conf10, sizeof(conf10) ); break;
#endif

default:
		memcpy ((RScommand.commBuf), conf1, sizeof(conf1) ); break;
#else
case 0x00: memcpy ((RScommand.commBuf), conf1, sizeof(conf1) ); break;
case 0x01: memcpy ((RScommand.commBuf), conf2, sizeof(conf2) ); break;
case 0x10: memcpy ((RScommand.commBuf), conf4, sizeof(conf4) ); break;
case 0x11: memcpy ((RScommand.commBuf), conf3, sizeof(conf3) ); break;
#ifdef screen3
case 4: 	    memcpy ((RScommand.commBuf), conf5, sizeof(conf5) ); break;
#endif

default:
		memcpy ((RScommand.commBuf), conf1, sizeof(conf1) ); break;
#endif	
}

#ifdef screen3
if(boot_flag) 
{
	 m_current=0;	     
}
#endif

boot_flag=0;
//printf("RScommand.commBuf=%s\r\n",RScommand.commBuf);  //ryan
PCT_RunCommShell(RScommand.commBuf); 


switch(m_current)
{
//#if 1
case 0x10: Bound_Set(0x00); break;  //C
case 0x20: Bound_Set(0x00); break;  //R
case 0x40: Bound_Set(0x00);Error=1; break;  //D
case 0x12: Bound_Set(0x01); break;  //CR
case 0x21: Bound_Set(0x01); break;  //RC
case 0x14: Bound_Set(0x01); break;  //DC
case 0x41: Bound_Set(0x01); break;  //CD
case 0x24: Bound_Set(0x01); Error=1;break;  //DR
case 0x42: Bound_Set(0x01);Error=1; break;  //RD

default:
		 break;
}

#ifdef  black_change
TW28_WriteByte(0,0xc3,0x01);
TW28_WriteByte(0,0xc4,0x00);
#endif

		#ifdef  Monitor_debug
	printf("\r\nMonitor mode=%x, m_current=%x ",(U16)ch, (U16)m_current);	
		//printf(" ,return=%x", (U16)Error);
	
	   

		if(Error==1)
		{
			//SC16_Com
			 	//RS_tx(STX);
				// RS_tx(SC16_Com[1]);
				// RS_tx(SC16_Com[2]);				 				 
				// RS_tx(ETX);
				// RS_tx(SC16_Com[4]);
				 RS_tx(0x35);
			 RS_tx(0x35);
			  RS_tx(0x35);
  				printf(" Error=1");
		}	
		#endif  

return Error;

}

//-----------------------------------------

U8 PWM_set(U8 val)
{

U8 Error=0,ch=0,set_val=0;

if(val>=PWM1_offset&&val<=(PWM6_offset+6))
{
ch=((val-PWM1_offset)/6);
	set_val=(val-PWM1_offset)%6;

	
		Set_PWM_Output(ch,set_val);

		#ifdef  SC16IS750_DEBUG_PRINT 
		printf("\r\nPWM_set ch=%x , val=%x",(U16)ch,(U16)set_val);
	  	#endif   
		
			Error=1;
}

return Error;
}

//-----------------------------------------

void Temp_check(void)
{
U16 val=0;
//U8 loop=0;

//val=(ADT75_GetTemp()>>4)/16;
val=(ADT75_GetTemp()>>4)/16;
if((P1_1==0))
  val=99;
//else if(val&0x0800==1)
	//val=0;
#if 1

	//val&=99;//ryan@20150909

if((val%10)>9);
else
Camera_temp0=(U8)(val%10)+0x30;

Camera_temp1=(U8)(val/10)+0x30;
		
		//if(Temp_timeout==1)
		//	{
		//printf("\r\nTemp_check=%x",val);
		//Temp_timeout= 120;
		//	}
#else
SC16_Com[0]=STX;
SC16_Com[1]=0x32;
SC16_Com[2]=0x31;
SC16_Com[3]=(U8)(val/10)+0x30;
SC16_Com[4]=(U8)(val%10)+0x30;
SC16_Com[5]=0x20;
SC16_Com[6]=0x20;
SC16_Com[7]=ETX;
SC16_Com[8]=0;

#ifdef BCC_noSTXEXT          ////XOR 1-6
for(loop=1;loop<=6;loop++)
SC16_Com[8]^=SC16_Com[loop];
#else                                 //XOR 0-7
for(loop=0;loop<=7;loop++)
SC16_Com[8]^=SC16_Com[loop];
#endif



	for(loop=0;loop<=8;loop++)
	{
	RS_tx(SC16_Com[loop]);
	//DELAY_FOR(200);
	}
#endif

}

//---------------------------------------------------


void Press_check(void)
{

//#define _2V  101300  ///2.0V
//#define _3V  199400  ////3.0V
//#define _1V_step   311
//#define press_offset   0
//#define ap_offset 60-8


U16 val=0;
U8 loop=0;
#if 1


#define _2V  101300  ///2.0V
#define _3V  199400  ////3.0V
#define _1V_step   310//0//311///one step=0.0031V refernec voltage=3.3V
#define press_offset   (50+30-1) ///1.850V offset to 2.0V ryan@20180727
#define ap_offset 60-8

U32 temp_val=0;
val=ADC_FPBS();

val=val+press_offset;
temp_val=val;

#if 1//ryan@20180727
if(temp_val>=(645+1))   ///>2.0  645*0.0031=2.0V
{
		if(temp_val<=967)   ///<3V  967*0.0031=3.0V
			{
 		  temp_val=(((((temp_val*_1V_step)/100)-2000)*98)+101300);
			}
		else
			{
			 temp_val=199400;
			}
}
else         			  ///2.0V to 1.6V
{
	if(temp_val>=(516+1))   ///>1.6 V   516*0.0031=1.6V
			{
			  temp_val=(((((temp_val*_1V_step)/100)-1600)*98)+62100);
			}
		else
			{
			temp_val=62100;
			}
}
#else
if(temp_val>=(_1V_step*2))   ///>2.0  
{
		if(temp_val<=(_1V_step*3))   ///<3V
			{
			  //temp_val=(val-_1V_step)*487;
			  temp_val=((_1V_step*3)-temp_val)*(316+ap_offset);
			}
		else
			{
			 temp_val=199400;
			}
}
else         			  ///2.0V to 1.6V
{
	//if(temp_val>=328)   ///>1.6 V
	if(temp_val>=499)   ///>1.6 V
			{
			  //temp_val=((_1V_step*2)-val)*478;
			  temp_val=((_1V_step*2)-val)*210;
			}
		else
			{
			temp_val=62100;
			}
}
#endif

val=(temp_val/100);


temp_val=val;



if(val>9999)  val=9999;

//val=1994;

Camera_press3=(val/1000)+0x30;  val=(val%1000);
Camera_press2=(val/100)+0x30;  val=(val%100);
Camera_press1=(val/10)+0x30;  val=(val%10);
Camera_press0=val+0x30;


		#ifdef  press_debug 
		printf("\r\nGet_press=%x ",(U16)temp_val);
	  	#endif  




#else
Camera_press1=(U8)(val/10)+0x30;
Camera_press0=(U8)(val%10)+0x30;


/*
SC16_Com[0]=STX;
SC16_Com[1]=0x32;
SC16_Com[2]=0x31;
SC16_Com[3]=(U8)(val/10)+0x30;
SC16_Com[4]=(U8)(val%10)+0x30;
SC16_Com[5]=0x20;
SC16_Com[6]=0x20;
SC16_Com[7]=ETX;
SC16_Com[8]=0;

#ifdef BCC_noSTXEXT          ////XOR 1-6
for(loop=1;loop<=6;loop++)
SC16_Com[8]^=SC16_Com[loop];
#else                                 //XOR 0-7
for(loop=0;loop<=7;loop++)
SC16_Com[8]^=SC16_Com[loop];
#endif



	for(loop=0;loop<=8;loop++)
	{
	RS_tx(SC16_Com[loop]);
	//DELAY_FOR(200);
	}


		#ifdef  SC16IS750_DEBUG_PRINT 
		printf("\r\nGet_press=%x ",(U16)val);
	  	#endif  

		*/

#endif
}

//---------------------------------------------------
void Version_check(void)
{

//U16 val=0;
U8 loop;

SC16_Com[0]=STX;
SC16_Com[1]=0x32;
SC16_Com[2]=0x50;
SC16_Com[3]=Ver0+0x30;
SC16_Com[4]=Ver1+0x30;
//SC16_Com[5]=Ver2+0x30;
SC16_Com[5]=Ver2;
SC16_Com[6]=0x20;
SC16_Com[7]=ETX;
SC16_Com[8]=0;

#ifdef BCC_noSTXEXT          ////XOR 1-6
for(loop=1;loop<=6;loop++)
SC16_Com[8]^=SC16_Com[loop];
#else                                 //XOR 0-7
for(loop=0;loop<=7;loop++)
SC16_Com[8]^=SC16_Com[loop];
#endif



	for(loop=0;loop<=8;loop++)
	{
	RS_tx(SC16_Com[loop]);
	//DELAY_FOR(200);
	}

}

void Camera_Version_check(void)
{
//U16 val=0;
U8 loop;

SC16_Com[0]=STX;
SC16_Com[1]=0x32;
SC16_Com[2]=0x4f;
SC16_Com[3]=Camera_ver0;
SC16_Com[4]=Camera_ver1;
//SC16_Com[5]=Ver2+0x30;
SC16_Com[5]=Camera_ver2;
SC16_Com[6]=0x20;
SC16_Com[7]=ETX;
SC16_Com[8]=0;

#ifdef BCC_noSTXEXT          ////XOR 1-6
for(loop=1;loop<=6;loop++)
SC16_Com[8]^=SC16_Com[loop];
#else                                 //XOR 0-7
for(loop=0;loop<=7;loop++)
SC16_Com[8]^=SC16_Com[loop];
#endif



	for(loop=0;loop<=8;loop++)
	{
	RS_tx(SC16_Com[loop]);
	//DELAY_FOR(200);
	}

}
//---------------------------------------------------

// ===========================================================================
// END of File 
// ===========================================================================
