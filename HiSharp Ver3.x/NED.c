#include "types.h"
#include "NED.h"                  //add by ryan.
#include "Main.h"
#include "printf.h"
//#include "Timer.h"
#include "UART.h"
#include "BusCtrl.h"
//#include "TW2835_Init.h"
#include "CommandShell.h"
//#include "OSDAction.h"

#define	I2C_SCL		P2_5
#define	I2C_SDA		P2_6

#define SC16IS750_CRYSTCAL_FREQ 1843200  ///1.8432MHz


#define I2C_time 100
#define SC16_data_buf (6*3)
#define BaudRate_sel 38400
//#define BaudRate_sel 9600

#define dvr_com_flag 1
#define camera_com_flag 2

 //U8 Com_buf[8]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};  
 U8 Com_pos=0;
 U8 Com_addr=0;
 U8 Com_start=0;
  U8 Com_end=0;
  U8 Com_run=0;
//U8 Monitor_mode=Monitor_offset;
//U8 Monitor_current=Monitor_offset;
U8 Monitor_mode=Monitor_offset+3;
U8 Monitor_state=Monitor_offset;
U8 Monitor_current=1;  //CR
U8 Back_f=0;
U8 Shrink_f=0;

U8 Crop_f=0;//ryan@21050413
//U8 Main_p=Camera_p;
//U8 Small_p=Rear_p;
extern U8 work_flag;
 U8 Com_flag=0;    
 U8 Com_temp=0;
 U8 INT_flag=0;
 U8 DRP_ID[9]={DVR_address,RF_ID_address,PIC32_address,RF_ID_address\
 		,PIC32_address,DVR_address,PIC32_address,DVR_address,RF_ID_address};

 U8 SC16_Com[9];   //0-15, 0-5=DVR, 6-11=RF, 12-16=PIC32
 U8 SC16_ComAddr=0;
 U8 GPIO_current=0;
 U8 DVR_startup_flag=0;
 U8 Cam_startup_flag=0;
 U8 DVR_Com[5]={0x02,0x37,0x32,0x03,0x04};
 U8 DVR_Com_p=0;
 U8 Cam_Com[5]={0x02,0x37,0x33,0x03,0x05};
 U8 Cam_Com_p=0;
//camera temp data
U8 Camera_ver0=0x30;
U8 Camera_ver1=0x30;
U8 Camera_ver2=0x30;
U8 Camera_temp0=0x30;
U8 Camera_temp1=0x30;
U8 Camera_press0=0x30;
U8 Camera_press1=0x30;
U8 Camera_press2=0x30;
U8 Camera_press3=0x30;

U8 Camera_IRDA[28]={0x30,0x30,0x30,0x30,0x30,0x30,0x30,\
					0x30,0x30,0x30,0x30,0x30,0x30,0x30,
					0x30,0x30,0x30,0x30,0x30,0x30,0x30,
					0x30,0x30,0x30,0x30,0x30,0x30,0x30};
//U8 Camera_IRDA1[4]={0x30,0x30,0x30,0x30};
//U8 Camera_IRDA2[4]={0x30,0x30,0x30,0x30};
//U8 Camera_IRDA3[4]={0x30,0x30,0x30,0x30};
//U8 Camera_IRDA4[4]={0x30,0x30,0x30,0x30};
//U8 Camera_IRDA5[4]={0x30,0x30,0x30,0x30};
//U8 Camera_IRDA6[4]={0x30,0x30,0x30,0x30};


U8 Camera_Ang[4]={0x30,0x30,0x30,0x30};
U8 Camera_RAng[4]={0x30,0x30,0x30,0x30};


//dvr temp data
U8 DVR_ver[3]={0x30,0x30,0x30};
U8 DVR_temp[2]={0x30,0x30};
U8 DVR_Y[4]={0x30,0x30,0x30,0x30};
U8 DVR_MD[4]={0x30,0x30,0x30,0x30};
U8 DVR_MH[4]={0x30,0x30,0x30,0x30};


 //get data from sc16--------------------
 U16 SC16_busy_flag=0;
// U8 SC16_com_state=0;
 U8 SC16_com_buff[9]={0,0,0,0,0,0,0,0,0};
 U8 data_flag=0;
//----------------------------------------
U8 Cam_boot_flag=0;
//U8 Cam_boot_count_flag=0;

U8 get_data_addr=0;
U8 get_data_val=0;
 //U16 BaudRate[3]={12,6,3};  //9600/19200/38400
 //U8 BaudRate_sel=9600;  //Default 9600
 //U32 BaudRate_sel=9600;  //Default 9600
//U32 BaudRate_sel=19200;  //Default 9600
//U32 BaudRate_sel=38400;  //Default 9600
#ifdef Move_Camera
U8 Camera_flag=0;

#endif
  
 U8 OUTPUT=0;
 U8 peek_flag=0,peek_buf=0;
extern data user_timer[TIMER_NUM];

//extern user_timer[3];
 
//-------------I2C 
 void I2Cdelay(void)
 {
	 #if 1//ryan@20151106


	//for(i=0; i<(1); i++)
	// 	{
	// 	}
	 
	 #else
		 U16 i; 
	 for(i=0; i<(20-12); i++){
//          for(i=0; i<(20+120); i++){  //ryan..
	 }
	 #endif
 }
#if 0
 void I2Cdelay2(void)
 {
	 U16 i;
	 for(i=0; i<(20); i++){
//          for(i=0; i<(20+120); i++){  //ryan..
	 }
 }

void I2C_100Khz(void)
{

while(USERTMVAL1>=2);
USERTMVAL1=2;
}
#endif
void I2CStart(void)
{
#if 1
      I2C_SDA = 1;	I2Cdelay(); 
	I2C_SCL = 1;	I2Cdelay();
	I2C_SDA = 0;	I2Cdelay();
	I2C_SCL = 0;
#else
//I2C_100Khz();
    I2C_SCL = 1;
// DELAY_FOR(10);///  I2Cdelay();
    I2C_SDA = 1;
    DELAY_FOR(I2C_time);///  I2Cdelay();
    I2C_SDA = 0;

DELAY_FOR(I2C_time);///  I2Cdelay();
I2C_SCL = 0;

    //DELAY_FOR(I2C_time);///  I2Cdelay();
   // I2Cdelay();

#endif
}
#if 0
void I2CStart2(void)
{

      I2C_SDA = 1;	I2Cdelay2(); 
	I2C_SCL = 1;	I2Cdelay2();
	I2C_SDA = 0;	I2Cdelay2();
	I2C_SCL = 0;
}
#endif
void I2CStop(void)
{
   #if 1
	I2C_SDA = 0;	I2Cdelay();
	I2C_SCL = 1;	I2Cdelay();
	I2C_SDA = 1;
    #else
      //DELAY_FOR(I2C_time);///I2Cdelay();  
   I2C_SCL = 1;
       //I2C_100Khz();
         DELAY_FOR(I2C_time);///I2Cdelay();  
   I2C_SDA = 0;
      //      I2C_100Khz();
      DELAY_FOR(I2C_time);/// I2Cdelay();

    I2C_SDA = 1; 
        // I2C_100Khz();
    	DELAY_FOR(I2C_time);///  I2Cdelay();

    #endif
}
#if 0
void I2CStop2(void)
{
   
	I2C_SDA = 0;	I2Cdelay2();
	I2C_SCL = 1;	I2Cdelay2();
	I2C_SDA = 1;
}
#endif
void I2CWriteData(BYTE value)
{
   #if 1
	I2C_SCL=0;	I2C_SDA=(value & 0x80)? 1:0;	I2Cdelay(); I2C_SCL=1;	I2Cdelay();
	I2C_SCL=0;	I2C_SDA=(value & 0x40)? 1:0;	I2Cdelay(); I2C_SCL=1;	I2Cdelay();
	I2C_SCL=0;	I2C_SDA=(value & 0x20)? 1:0;	I2Cdelay();I2C_SCL=1;	I2Cdelay();
	I2C_SCL=0;	I2C_SDA=(value & 0x10)? 1:0;	I2Cdelay(); I2C_SCL=1;	I2Cdelay();

	I2C_SCL=0;	I2C_SDA=(value & 0x08)? 1:0;	I2Cdelay(); I2C_SCL=1;	I2Cdelay();
	I2C_SCL=0;	I2C_SDA=(value & 0x04)? 1:0;	I2Cdelay(); I2C_SCL=1;	I2Cdelay();
	I2C_SCL=0;	I2C_SDA=(value & 0x02)? 1:0;	I2Cdelay(); I2C_SCL=1;	I2Cdelay();
	I2C_SCL=0;	I2C_SDA=(value & 0x01)? 1:0;	I2Cdelay(); I2C_SCL=1;	I2Cdelay();


	I2C_SCL = 0;	// HHY 3.00
	I2C_SCL = 0;	// HHY 3.00
	I2C_SCL = 0;	//I2Cdelay();
      I2C_SDA = 1;	//I2Cdelay();
      
	I2C_SCL = 1;	// HHY 3.00
	I2C_SCL = 1;	// HHY 3.00
	I2C_SCL = 1;
		I2Cdelay();
	I2C_SCL = 0;
	      I2Cdelay();
    #else
	BYTE i, tmpbyte = value;
      //  tmpbyte=0x55;
//I2Cdelay();
	for(i = 0; i < 8; i++)
	{
		if((0x80 & tmpbyte))
			I2C_SDA=1;///GPIO_SetBits(GPIOB, I2C2_SDA);
		else
			I2C_SDA=0;///GPIO_ResetBits(GPIOB, I2C2_SDA);
			//I2C_100Khz();
            
		//I2Cdelay();
	       	DELAY_FOR(I2C_time);///  I2Cdelay();
             I2C_SCL=1;
             //I2C_100Khz();
              	DELAY_FOR(I2C_time);///  I2Cdelay();
             I2C_SCL=0;
              	DELAY_FOR(I2C_time);///  I2Cdelay();
             //I2C_100Khz();
             //DELAY_FOR(5);///I2Cdelay();
		//I2CDLY_5uSec(1);
		///GPIO_SetBits(GPIOB, I2C2_SCL);
		///I2CDLY_5uSec(1);
		///GPIO_ResetBits(GPIOB, I2C2_SCL);
		tmpbyte = tmpbyte << 1;
	}
         //DELAY_FOR(10);///I2Cdelay();
      //I2Cdelay();
	//I2C_SDA = 1;	    //ACK
	// I2C_SCL=1;
	// DELAY_FOR(10);///I2Cdelay();
     //I2Cdelay();//ryan..
	//I2C_SCL = 1;	// HHY 3.00
	//I2Cdelay(); //ryan..
	//I2C_SCL = 0;
	//I2Cdelay(); //ryan..
  //    I2C_SDA = 1;	//	I2Cdelay();//ryan.
//     I2Cdelay(); //ryan..
    
     #endif
}

#if 0
void I2CWriteData2(BYTE value)
{
  
	I2C_SCL=0;	I2C_SDA=(value & 0x80)? 1:0;	I2Cdelay2(); I2C_SCL=1;	I2Cdelay2();
	I2C_SCL=0;	I2C_SDA=(value & 0x40)? 1:0;	I2Cdelay2(); I2C_SCL=1;	I2Cdelay2();
	I2C_SCL=0;	I2C_SDA=(value & 0x20)? 1:0;	I2Cdelay2();I2C_SCL=1;	I2Cdelay2();
	I2C_SCL=0;	I2C_SDA=(value & 0x10)? 1:0;	I2Cdelay(); I2C_SCL=1;	I2Cdelay2();

	I2C_SCL=0;	I2C_SDA=(value & 0x08)? 1:0;	I2Cdelay2(); I2C_SCL=1;	I2Cdelay2();
	I2C_SCL=0;	I2C_SDA=(value & 0x04)? 1:0;	I2Cdelay2(); I2C_SCL=1;	I2Cdelay2();
	I2C_SCL=0;	I2C_SDA=(value & 0x02)? 1:0;	I2Cdelay2(); I2C_SCL=1;	I2Cdelay2();
	I2C_SCL=0;	I2C_SDA=(value & 0x01)? 1:0;	I2Cdelay2(); I2C_SCL=1;	I2Cdelay2();


	I2C_SCL = 0;	// HHY 3.00
	I2C_SCL = 0;	// HHY 3.00
	I2C_SCL = 0;	//I2Cdelay();
      I2C_SDA = 1;	//I2Cdelay();
      
	I2C_SCL = 1;	// HHY 3.00
	I2C_SCL = 1;	// HHY 3.00
	I2C_SCL = 1;
		I2Cdelay2();
	I2C_SCL = 0;
	      I2Cdelay2();
}
#endif


U8 I2CReadData(void)
{
#if 1
	U16 i;
	U8 value=0;

	I2C_SDA = 1;	I2Cdelay();
	I2C_SCL = 0;
	
	for(i=0; i<8; i++) {
            I2Cdelay();
		I2C_SCL = 1;
		value <<= 1;
		if(I2C_SDA) value |= 1;
        I2Cdelay();
		I2C_SCL = 0;
		    I2Cdelay();
	}
 
       I2Cdelay();
	//I2C_SCL = 1;	// HHY 3.00
	//I2C_SCL = 1;	// HHY 3.00
	//I2C_SCL = 1; 
	 I2Cdelay();
      //  I2C_SCL = 0;
        I2Cdelay();
	return value;
#else
	BYTE i, bitt, ReadValue = 0,vall[8]={0,0,0,0,0,0,0,0};
      U16 val2=0;
	  
	//GPIO_InitTypeDef GPIO_InitStruct;

       //I2Cdelay();
	//I2C_SDA = 1;	I2Cdelay();
	//I2C_SCL = 0; I2Cdelay();
    
	for(i = 0; i < 8; i++)
	{

		if( I2C_SDA==1)	bitt = 0x01;
		else	                   bitt = 0x00;

    // vall[i]=bitt;

   		//I2C_100Khz();
  	 DELAY_FOR(I2C_time);///  I2Cdelay();
          //DELAY_FOR(5);/// I2Cdelay();
            I2C_SCL = 1;
	 DELAY_FOR(I2C_time);///  I2Cdelay();
        //DELAY_FOR(5);/// I2Cdelay();
            I2C_SCL = 0;
	 DELAY_FOR(I2C_time);///  I2Cdelay();
           //DELAY_FOR(5);///   I2Cdelay();
            //I2Cdelay();          
		//I2CDLY_5uSec(1);
		//GPIO_SetBits(GPIOB, I2C2_SCL);
		//I2CDLY_5uSec(1);		
		//GPIO_ResetBits(GPIOB, I2C2_SCL);		
		//I2CDLY_5uSec(1);
		ReadValue = (ReadValue<<1)|bitt;
	}
//val2=ReadValue;

//Printf("Val=%X %X %X %X %X %X %X %X \r\n",vall[7],vall[6],vall[5],vall[4],vall[3],vall[2],vall[1],vall[0]);
//Printf("Val= %x\r\n",val2);


      //  I2C_SDA = 1;	    //ACK
	// I2C_SCL=1;
        // DELAY_FOR(10);///   I2Cdelay();
	 //I2Cdelay();  
	//GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	//GPIO_InitStruct.GPIO_Pin = I2C2_SDA | I2C2_SCL;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	//GPIO_Init(GPIOB, &GPIO_InitStruct);
//	I2C_SDA = 0;	    //ACK
 //    I2Cdelay();//ryan..
//	I2C_SCL = 1;	// HHY 3.00
// 	I2Cdelay(); //ryan..
 //      I2C_SCL = 0;
	//I2Cdelay(); //ryan..
     // I2C_SDA = 1;	//	I2Cdelay();//ryan.
      // I2Cdelay(); //ryan..
	return ReadValue;
#endif
}
#if 0
U8 I2CReadData2(void)
{

	U16 i;
	U8 value=0;

	I2C_SDA = 1;	I2Cdelay2();
	I2C_SCL = 0;
	
	for(i=0; i<8; i++) {
            I2Cdelay2();
		I2C_SCL = 1;
		value <<= 1;
		if(I2C_SDA) value |= 1;
        I2Cdelay2();
		I2C_SCL = 0;
		    I2Cdelay2();
	}
 
       I2Cdelay2();
	//I2C_SCL = 1;	// HHY 3.00
	//I2C_SCL = 1;	// HHY 3.00
	//I2C_SCL = 1; 
	 I2Cdelay2();
      //  I2C_SCL = 0;
        I2Cdelay2();
	return value;
}
#endif
U8 I2CReadDataWithACK(void)
{
  #if 1
	U16 i;
	U8 value=0;

	I2C_SDA = 1;	I2Cdelay();
	I2C_SCL = 0;

	for(i=0; i<8; i++) {
		 I2Cdelay();
		I2C_SCL = 1;
		value <<= 1;
		if(I2C_SDA) value |= 1;
		 I2Cdelay();
		I2C_SCL = 0;
		 I2Cdelay();
	}
	
	I2C_SDA = 0;//	I2Cdelay();		//ack
	//I2C_SCL = 1;	I2Cdelay();
	//I2C_SCL = 0;

       I2Cdelay();    //ACk
	 I2C_SCL = 1;	// HHY 3.00
	 I2C_SCL = 1;	// HHY 3.00
	 I2C_SCL = 1; 
	 I2Cdelay();
        I2C_SCL = 0;
        I2Cdelay();

	return value;
	
   #else
    
    	BYTE i, bitt, ReadValue = 0;
	//GPIO_InitTypeDef GPIO_InitStruct;

	for(i = 0; i < 8; i++)
	{

		if( I2C_SDA==1)	bitt = 0x01;
		else	                   bitt = 0x00;
        
            I2Cdelay();
            I2C_SCL = 1;
            I2Cdelay();
            I2C_SCL = 0;
            I2Cdelay();          
		//I2CDLY_5uSec(1);
		//GPIO_SetBits(GPIOB, I2C2_SCL);
		//I2CDLY_5uSec(1);		
		//GPIO_ResetBits(GPIOB, I2C2_SCL);		
		//I2CDLY_5uSec(1);
		ReadValue = (ReadValue<<1)|bitt;
	}
    
	I2C_SDA = 0;	I2Cdelay();		//ack
	I2C_SCL = 1;	I2Cdelay();
	I2C_SCL = 0;
	//GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	//GPIO_InitStruct.GPIO_Pin = I2C2_SDA | I2C2_SCL;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	//GPIO_Init(GPIOB, &GPIO_InitStruct);
	return ReadValue;
    
    #endif
}
#if 0
U8 I2CReadDataWithACK2(void)
{
//#if 1
	U16 i;
	U8 value=0;

	I2C_SDA = 1;	I2Cdelay2();
	I2C_SCL = 0;

	for(i=0; i<8; i++) {
		 I2Cdelay2();
		I2C_SCL = 1;
		value <<= 1;
		if(I2C_SDA) value |= 1;
		 I2Cdelay2();
		I2C_SCL = 0;
		 I2Cdelay2();
	}
	
	I2C_SDA = 0;//	I2Cdelay();		//ack
	//I2C_SCL = 1;	I2Cdelay();
	//I2C_SCL = 0;

       I2Cdelay2();    //ACk
	 I2C_SCL = 1;	// HHY 3.00
	 I2C_SCL = 1;	// HHY 3.00
	 I2C_SCL = 1; 
	 I2Cdelay2();
        I2C_SCL = 0;
        I2Cdelay2();

	return value;
}
#endif
void WriteI2C(U8 addr, U8 index, U8 val)
{

#if 1
	I2CStart();
	I2CWriteData(addr);
	I2CWriteData(index<<3);
	I2CWriteData(val);
	I2CStop();

#else
	I2CStart();
	I2CWriteData(addr);
       I2C_ACK2();
	I2CWriteData((index<<3));
       I2C_ACK2();
	I2CWriteData(val);
       I2C_ACK2();
       I2CStop();
#endif
}

U8 ReadI2C(U8 addr, U8 index)
{
U8 val;//,x,y,z,val2[16];

       #if 1
	I2CStart();
	I2CWriteData(addr);
	I2CWriteData(index<<3);
	I2CStart();
	I2CWriteData(addr | 0x01);
	val = I2CReadData();
          //val = I2CReadDataWithACK();
 
	I2CStop();
      #else
      	I2CStart();
     	I2CWriteData(addr);
     I2C_ACK2(); 
    I2CWriteData((index<<3));
     I2C_ACK2();  
	 
    I2CStart();
          //   P2M0|=0x40;
   //DELAY_FOR(20);/// I2Cdelay();
 //USERTMVAL1=2; 
 
     I2CWriteData(addr|0x01);
  
   I2C_ACK2(); 

//for(x=0;x<=14;x++)
//{
      val = I2CReadData();
           //  P2M0&=0xBF;
   //DELAY_FOR(20);/// I2Cdelay();
//val2[x]=val;
           // I2C_ACK2();  
         //val = I2CReadDataWithACK();
         //I2C_ACK2(); 
//}

      val = I2CReadData();
	//  val2[15]=val;
 I2CStop();

#if 0
Printf("-> \r\n",(U16) x,(U16) val2[x]);  //ryan 	  
for(x=0;x<=15;x++)
{

Printf("Addr=%x  Data=%x \r\n",(U16) x,(U16) val2[x]);  //ryan 

}
Printf("                    <-\r\n",(U16) x,(U16) val2[x]);  //ry		
#endif

        #endif
		//Printf("Data=%x \r\n",(U16)val);  //ryan
	return val;
}
//---------------------------------------
#if 0
void WriteI2C2(U8 addr, U8 index, U8 val)
{
	I2CStart();
	I2CWriteData(addr);
	I2CWriteData(index);
	I2CWriteData(val);
	I2CStop();

}
//---------------------------------------
U8 ReadI2C2(U8 addr, U8 index)
{
      U8 val;
	  
	I2CStart();
	I2CWriteData(addr);
	I2CWriteData(index);
	I2CStart();
	I2CWriteData(addr | 0x01);
	val = I2CReadData();
          //val = I2CReadDataWithACK();
	I2CStop();	
return 1;  
}

//----------------------------------------
 void I2C_ACK(void)
{
     
           // I2Cdelay();		//ack
 
          I2Cdelay();		//ack
	I2C_SCL = 1;
          I2Cdelay();
	I2C_SCL = 0;
          I2Cdelay();
	   I2C_SDA = 1;
}

 void I2C_ACK2(void)
{
     //while(I2C_SDA==1);
    //  DELAY_FOR(10);///   I2Cdelay();		//ack
   // I2C_SDA = 0;
      //  I2Cdelay();		//ack
       // DELAY_FOR(5);///     I2Cdelay   
	 DELAY_FOR(I2C_time);///  I2Cdelay();     
	I2C_SCL = 1;
	 DELAY_FOR(I2C_time);///  I2Cdelay();
     //DELAY_FOR(5);///     I2Cdelay();
	I2C_SCL = 0;
	 DELAY_FOR(I2C_time);///  I2Cdelay();
// DELAY_FOR(5);///    I2Cdelay();
 //I2C_SDA = 1;
   //  DELAY_FOR(10);///     I2Cdelay();
       
}
 #endif
//----------------------------------------

U16 ReadI2CWORD(BYTE addr, BYTE index)
{
	U16 val=0;

	I2CStart();
	I2CWriteData(addr);
      //I2C_ACK();
	I2CWriteData(index);
      //I2C_ACK();
    
	I2CStart();
	I2CWriteData(addr | 0x01);
	
	val = I2CReadDataWithACK();
	val = val<<8;
	val |= I2CReadData();
	I2CStop();

	return val;
}
//---------------------------------------
#if 0
void WriteI2CWORD(U8 addr, U8 index, U16 Data)
{
      U8 tempL,tempH;

	tempH=((Data>>8)&0x00ff);
	tempL=(Data&0x00ff);
	I2CStart();
	I2CWriteData(addr);
	I2CWriteData(index);
	I2CWriteData(tempH);
	I2CWriteData(tempL);
	I2CStop();
}
#endif
//----------------------------------------

void Bound_Set(U8 val)
{


//U8 loop;
U8 Mask[3]={0x11,0x19,0x21};

#ifdef black_boundary
switch(val)
{
case 1:	TW28_WriteByte(1,0x11,0x02); 
		TW28_WriteByte(1,0x0f,0x00);
		break;
case 2:	TW28_WriteByte(1,0x19,0x02);
		TW28_WriteByte(1,0x0f,0x00);
		break;
case 4:	TW28_WriteByte(1,0x21,0x02);
		TW28_WriteByte(1,0x0f,0x00);
		break;
default:
		
		//TW28_WriteByte(1,0x0f,0x03);
		TW28_WriteByte(1,0x11,0x00);
		TW28_WriteByte(1,0x19,0x00);
		TW28_WriteByte(1,0x21,0x00);
	      break;	
}
#else
switch(val)
{
case 1:	TW28_WriteByte(1,0x11,0x02); 
		TW28_WriteByte(1,0x0f,0x33);
		break;
case 2:	TW28_WriteByte(1,0x19,0x02);
		TW28_WriteByte(1,0x0f,0x33);
		break;
case 4:	TW28_WriteByte(1,0x21,0x02);
		TW28_WriteByte(1,0x0f,0x33);
		break;
default:
		
		//TW28_WriteByte(1,0x0f,0x03);
		TW28_WriteByte(1,0x11,0x00);
		TW28_WriteByte(1,0x19,0x00);
		TW28_WriteByte(1,0x21,0x00);
	      break;	
}

#endif
/*
for(loop=0;loop<=2;loop++)
{
	if((val&0x01)==1)
		{
		TW28_WriteByte(1,Mask[loop],0x02);	
		return;
		}
	//else
		//TW28_WriteByte(1,Mask[loop],0x00);	
	
	val>>=1;
}
*/


}

//---------------------------------------
#if 0
void Set_channel(U8 addr)
{
TW28_WriteByte(1,0x10,0x00); //C
TW28_WriteByte(1,0x18,0x00);  //R
TW28_WriteByte(1,0x20,0x00);  //D


	switch(addr)
	{
case 0x10: TW28_WriteByte(1,0x10,0x80); break;  //C
case 0x20: TW28_WriteByte(1,0x20,0x82); break;  //R
case 0x40: TW28_WriteByte(1,0x18,0x81); break;  //D
case 0x12: Bound_Set(0x01); break;  //CR
case 0x21: Bound_Set(0x01); break;  //RC
case 0x14: Bound_Set(0x01); break;  //DC
case 0x41: Bound_Set(0x02); break;  //CD
case 0x24: Bound_Set(0x01); break;  //DR
case 0x42: Bound_Set(0x01); break;  //RD
default:
		 break;

	}
 
}
#endif


//----------------------------------------

U16 ADC_read(U8 sel)
{
    
ADCTL=0x80|0x08|sel;  //start adc sampling

while(ADCTL&0x08);// printf("ADC is busying\r\n");  //wating for adc

return (U16)(((ADCVL&0x03) |(ADCV<<2))&0x03ff);

}

//20160226
//-----------------------------------------
void Set_Video(U8 addr, U8 val)
{
switch (addr)
{
case 0: TW28_WriteByte(0,0x09,val); //VIN0 CONT,TW2871
		break;
case 1: TW28_WriteByte(0,0x0a,val);//VIN0 BRT,TW2871
		break;
case 2:  TW28_WriteByte(0,0x19,val);//VIN1 CONT,Recorder
		break;
case 3:  TW28_WriteByte(0,0x1a,val);//VIN1 BRT,Recorder
		break;
case 4:	TW28_WriteByte(0,0x29,val); //VIN2 CONT,Back cam
		break;
case 5:  TW28_WriteByte(0,0x2a,val);//VIN2 BRT,Back cam
		break;
default:
	break;

}


}


//-----------------------------------------
#if 0
void Send_Camera_Ver(void)
{
U8 loop;

SC16_Com[0]=STX;
SC16_Com[1]=0x32;
SC16_Com[2]=0x4f;
SC16_Com[3]=Camera_ver2;
SC16_Com[4]=Camera_ver1;
SC16_Com[5]=Camera_ver0;
SC16_Com[6]=0x20;
SC16_Com[7]=ETX;
SC16_Com[8]=BCC_Cal(SC16_Com, 8);

	for(loop=0;loop<=8;loop++)
	{
	RS_tx(SC16_Com[loop]);
	}
}
#endif
void Get_Camera_Ver(void)
{
WriteByte(DRP_ID[2], 0x02);
WriteByte(DRP_ID[2], 0x31);
WriteByte(DRP_ID[2], 0x4f);
WriteByte(DRP_ID[2], 0x03);
WriteByte(DRP_ID[2], 0x7f);
}

//-----------------------------------------
void Send_Camera_Temp(void)
{

U8 loop;

SC16_Com[0]=STX;
SC16_Com[1]=0x32;
SC16_Com[2]=0x31;
SC16_Com[3]=Camera_temp1;
SC16_Com[4]=Camera_temp0;
SC16_Com[5]=0x20;
SC16_Com[6]=0x20;
SC16_Com[7]=ETX;
SC16_Com[8]=BCC_Cal(SC16_Com, 8);

	for(loop=0;loop<=8;loop++)
	{
	RS_tx(SC16_Com[loop]);
	}


}

//----------------------------------------

void Send_Camera_Press(void)
{
U8 loop;

SC16_Com[0]=STX;
SC16_Com[1]=0x32;
SC16_Com[2]=0x33;
#if 0
SC16_Com[3]=Camera_press1;
SC16_Com[4]=Camera_press0;
SC16_Com[5]=0x20;
SC16_Com[6]=0x20;
#else
SC16_Com[3]=Camera_press3;
SC16_Com[4]=Camera_press2;
SC16_Com[5]=Camera_press1;
SC16_Com[6]=Camera_press0;
#endif
SC16_Com[7]=ETX;
SC16_Com[8]=BCC_Cal(SC16_Com, 8);

	for(loop=0;loop<=8;loop++)
	{
	RS_tx(SC16_Com[loop]);
	}



}

//----------------------------------------
void Get_Camera_Ang(void)
{
WriteByte(DRP_ID[2], 0x02);
WriteByte(DRP_ID[2], 0x31);
WriteByte(DRP_ID[2], 0x34);
WriteByte(DRP_ID[2], 0x03);
WriteByte(DRP_ID[2], 0x04);

}

void Sent_Camera_Ang(void)
{

U8 loop;

SC16_Com[0]=STX;
SC16_Com[1]=0x32;
SC16_Com[2]=0x34;
SC16_Com[3]=Camera_Ang[3];
SC16_Com[4]=Camera_Ang[2];
SC16_Com[5]=Camera_Ang[1];
SC16_Com[6]=Camera_Ang[0];
SC16_Com[7]=ETX;
SC16_Com[8]=BCC_Cal(SC16_Com, 8);

	for(loop=0;loop<=8;loop++)
	{
	RS_tx(SC16_Com[loop]);
	}

}
//----------------------------------------
void Get_Camera_RAng(void)
{
WriteByte(DRP_ID[2], 0x02);
WriteByte(DRP_ID[2], 0x31);
WriteByte(DRP_ID[2], 0x35);
WriteByte(DRP_ID[2], 0x03);
WriteByte(DRP_ID[2], 0x05);
}

void Sent_Camera_RAng(void)
{

U8 loop;

SC16_Com[0]=STX;
SC16_Com[1]=0x32;
SC16_Com[2]=0x35;
SC16_Com[3]=Camera_RAng[3];
SC16_Com[4]=Camera_RAng[2];
SC16_Com[5]=Camera_RAng[1];
SC16_Com[6]=Camera_RAng[0];
SC16_Com[7]=ETX;
SC16_Com[8]=BCC_Cal(SC16_Com, 8);

	for(loop=0;loop<=8;loop++)
	{
	RS_tx(SC16_Com[loop]);
	}

}
//----------------------------------------
#if 0
void Get_Camera_IRD(U8 sel)
{
//U8 bcc[4]={0x02,0x31,0,0x03},bcc_val;
U8 bcc_val=0;

bcc_val^=STX;
bcc_val^=0x31;
bcc_val^=sel;
bcc_val^=ETX;
	
//bcc_val=BCC_Cal(&bcc[0],4);
	
WriteByte(DRP_ID[2],STX);
WriteByte(DRP_ID[2],0x31);
WriteByte(DRP_ID[2], sel);
WriteByte(DRP_ID[2], ETX);
WriteByte(DRP_ID[2], bcc_val );

}
#endif
void Sent_Camera_IRD(U8 sel)
{
	
U8 loop;
U8 temp=0;

RS_tx(NAK);
return;//ryan@20150908

temp=(sel-0x41);
temp=temp*4;
SC16_Com[0]=STX;
SC16_Com[1]=0x32;
SC16_Com[2]=sel;
SC16_Com[3]=Camera_IRDA[temp+3];
SC16_Com[4]=Camera_IRDA[temp+2];
SC16_Com[5]=Camera_IRDA[temp+1];
SC16_Com[6]=Camera_IRDA[temp+0];
SC16_Com[7]=ETX;
SC16_Com[8]=BCC_Cal(SC16_Com, 8);

	for(loop=0;loop<=8;loop++)
	{
	RS_tx(SC16_Com[loop]);
	}

}

//----------------------------------------

void Get_DVR_temp(void)
{
WriteByte(DRP_ID[0], STX);
WriteByte(DRP_ID[0], 0x33);
WriteByte(DRP_ID[0], 0x31);
WriteByte(DRP_ID[0], ETX);
WriteByte(DRP_ID[0], 0x03);
}


void Sent_DVR_temp(void)
{
U8 loop;

SC16_Com[0]=STX;
SC16_Com[1]=0x34;
SC16_Com[2]=0x31;
SC16_Com[3]=DVR_temp[1];
SC16_Com[4]=DVR_temp[0];
SC16_Com[5]=0x20;
SC16_Com[6]=0x20;
SC16_Com[7]=ETX;
SC16_Com[8]=BCC_Cal(SC16_Com, 8);

	for(loop=0;loop<=8;loop++)
	{
	RS_tx(SC16_Com[loop]);
	}


}

#if 0
void Get_DVR_ver(void)
{
WriteByte(DRP_ID[0], STX);
WriteByte(DRP_ID[0], 0x33);
WriteByte(DRP_ID[0], 0x4F);
WriteByte(DRP_ID[0], ETX);
WriteByte(DRP_ID[0], 0x7D);
}
void Sent_DVR_ver(void)
	{
U8 loop;

SC16_Com[0]=STX;
SC16_Com[1]=0x34;
SC16_Com[2]=0x4f;
SC16_Com[3]=DVR_ver[2];
SC16_Com[4]=DVR_ver[1];
SC16_Com[5]=DVR_ver[0];
SC16_Com[6]=0x20;
SC16_Com[7]=ETX;
SC16_Com[8]=BCC_Cal(SC16_Com, 8);

	for(loop=0;loop<=8;loop++)
	{
	RS_tx(SC16_Com[loop]);
	}

	}

void Get_DVR_Year(void)
{
WriteByte(DRP_ID[0], STX);
WriteByte(DRP_ID[0], 0x33);
WriteByte(DRP_ID[0], 0x35);
WriteByte(DRP_ID[0], ETX);
WriteByte(DRP_ID[0], 0x07);
}

void Sent_DVR_Year(void)
{
U8 loop;

SC16_Com[0]=STX;
SC16_Com[1]=0x34;
SC16_Com[2]=0x35;
SC16_Com[3]=DVR_Y[3];
SC16_Com[4]=DVR_Y[2];
SC16_Com[5]=DVR_Y[1];
SC16_Com[6]=DVR_Y[0];
SC16_Com[7]=ETX;
SC16_Com[8]=BCC_Cal(SC16_Com, 8);

	for(loop=0;loop<=8;loop++)
	{
	RS_tx(SC16_Com[loop]);
	}


}

void Get_DVR_MD(void)
	{
WriteByte(DRP_ID[0], STX);
WriteByte(DRP_ID[0], 0x33);
WriteByte(DRP_ID[0], 0x36);
WriteByte(DRP_ID[0], ETX);
WriteByte(DRP_ID[0], 0x04);
}
void Sent_DVR_MDr(void)
	{}
void Get_DVR_HS(void)
	{
WriteByte(DRP_ID[0], STX);
WriteByte(DRP_ID[0], 0x33);
WriteByte(DRP_ID[0], 0x37);
WriteByte(DRP_ID[0], ETX);
WriteByte(DRP_ID[0], 0x05);
}
void Sent_DVR_HS(void){}
#endif
//-----------------------------------------

void Set_Camera_speed(U8 val)
{
	if(val)
		{
WriteByte(DRP_ID[2], STX);
WriteByte(DRP_ID[2], 0xFF);
WriteByte(DRP_ID[2], 0x90);
WriteByte(DRP_ID[2], ETX);
WriteByte(DRP_ID[2], 0x6E);
		}
	else
		{
WriteByte(DRP_ID[2], STX);
WriteByte(DRP_ID[2], 0xFF);
WriteByte(DRP_ID[2], 0x91);
WriteByte(DRP_ID[2], ETX);
WriteByte(DRP_ID[2], 0x6F);
		}

					#ifdef  camera_speed
					printf("\r\n Set_Camera_speed=%x",(U16) val);
					#endif  

}


//-----------------------------------------
void GPIO_check(void)
{
U8 GPIO_state,IO_flag=0x10,count=0;

GPIO_state=(DVR_GetIO()&0x3f);

if(GPIO_current==GPIO_state)
	return;
else	
{
	IO_flag=GPIO_state;
	while((IO_flag&0x01)!=0)
	{
	IO_flag>>=1;
	count++;
	}
}
	switch(count)
		{

		case 0:
				PCON = PCON&0x7f;				//  smod=0
   				TH1 = SET_BAUDRATE(9600,0);	// 22.118M HZ	  //remask by ryan.
   				break;
		case 1:	PCON = PCON&0x7f;				//  smod=0
				TH1 = SET_BAUDRATE(19200,0);	// 22.118M HZ	  //remask by ryan.
				break;
		case 2:
				PCON =PCON| 0x80;				//  smod=1
				TH1 = SET_BAUDRATE(38400,1);	// 22.118M HZ	  //remask by ryan.
				break;
		case 3:
				PCON =PCON| 0x80;				//smod=1
				TH1 = SET_BAUDRATE(76800,1);	// 22.118M HZ	  //remask by ryan.
				break;
		default:  PCON = PCON&0x7f;				//  smod=0
   				TH1 = SET_BAUDRATE(9600,0);	// 22.118M HZ	  //remask by ryan.
   				break;
		}	


			GPIO_current=GPIO_state;

			#ifdef  SC16IS750_DEBUG_PRINT 
  			printf("\r\n GPIO=%x",(U16)GPIO_state);
			#endif   
			
}

//-----------------------------------------
void Power_onoff(U8 sel)
{

Power_EN1=sel;
Power_EN2=sel;
Power_EN3=sel;
 Wait_ms(100);
//P2_4=1;
//P2_7=1;
//printf("power on");
}
//-----------------------------------------

U8 SC16_init(void)
{

U8 Dev_ID;

    SC16_RST=0;
        Wait_ms(20);
            SC16_RST=1;
 	        Wait_ms(20);

  #if 1
    for(Dev_ID=0;Dev_ID<=2;Dev_ID++)
    {		 
         ResetDevice(DRP_ID[Dev_ID]);
	  SetBaudrate(DRP_ID[Dev_ID],BaudRate_sel);
        SetLine(DRP_ID[Dev_ID],8,0,1);
        WriteI2C(DRP_ID[Dev_ID],FCR , 0x01);   //FIFO mode
    }
#endif

#ifdef dvr_parity
  SetLine(DVR_address,8,2,1);  //DVR parity even
#endif

	GPIOSetPortMode(DRP_ID[0],0);
	GPIOSetPortState(DRP_ID[0],0xff)	;
return 1;
}
//-----------------------------------------
extern data user_timer[TIMER_NUM];//ryan@20151216

U8 SC16_SendData(U8 val)
{
U8 error=0;
//U8 Dev_ID=0,Data,Error=FALSE;

#ifdef power_startup_check

	if((Com_flag==dvr_com_flag)&&(DVR_startup_flag==1))
	WriteByte(DRP_ID[0], val);	
	
	if((Com_flag==camera_com_flag)&&(Cam_startup_flag==1))
	WriteByte(DRP_ID[2], val);					
	
#else

WriteByte(DRP_ID[0], val);

//if((SC16_Com[1]==0x37)&&((SC16_Com[2]==0x31)|| (SC16_Com[2]==0x34)||(SC16_Com[2]==0x53)||
//	(SC16_Com[2]==0x41)||(SC16_Com[2]==0x42)));
//else
WriteByte(DRP_ID[2], val);

//#if 1//ryan@20151216
//if(Com_flag==camera_com_flag) user_timer[3]=(40+40);//reset polling timer..


#endif

//ryan@20150814			WriteByte(DRP_ID[1], val);

//WDTCR|=0x10;
return 1;

}
//-----------------------------------------

U8 SC16_SendDataSelect(U8 addr)
{

U8 loop=0,Error=0,count=0,data_temp=0;
//U8 count2=0,start=0,end=0,loop_flag;
U8 buff_flag=1,loop_temp=0;
U8 error_flag=1;
U8 etx_flag=0;///camera 
//data_flag=0;

//WDTCR|=0x10;
#if 0

while( (ReadI2C(DRP_ID[addr], LSR)&BIT0))
{
data_temp=ReadByte(DRP_ID[addr]);
//SC16_Com[count]=data_temp;
//count++;
Error=TRUE;

 RS_tx(data_temp); 
WriteByte(DRP_ID[addr+1],data_temp); 
WriteByte(DRP_ID[addr+2],data_temp); 
WDTCR|=0x10;
}


//if( (ReadI2C(DRP_ID[addr], LSR)&BIT1))

//}
#endif

#if 1
/*
	if( (ReadI2C(DRP_ID[addr], LSR)&BIT1))
	{
	WriteI2C(DRP_ID[addr],FCR,0x03);   //RXFIFO_reset 
	DELAY_FOR(50);
	WriteI2C(DRP_ID[addr],FCR,0x01);   //RXFIFO_reset 
	}
	else
		{
		*/
			if( ReadI2C(DRP_ID[addr], LSR)&BIT0)
			{   
				count=ReadI2C(DRP_ID[addr], RXLVL);
				//data_flag=count;
				
					 if(count==0) return 0;

					#ifdef  SC16IS750_DEBUG_PRINT 
					printf("\r\n SC16_ID=%x Data=",(U16) DRP_ID[addr]);
					#endif  

					#ifdef  SC16IS750_DEBUG_PRINT 
					printf("\r\n count=%x Data=",(U16) count);
					#endif  

				#ifdef get_data_buff

				data_temp=ReadByte(DRP_ID[addr]);

				if((data_temp==NAK)||(data_temp==ACK))
				{				
					if((addr==6)&&(data_temp==NAK));
					else
					RS_tx(data_temp); 
					
					#if 0//ryan@20151106¦^ÂÐ¤ÓºC®³±¼
					WriteByte(DRP_ID[addr+1],data_temp); 
					WriteByte(DRP_ID[addr+2],data_temp); 
					#endif

					//if(data_temp==NAK) 
						//printf("(N=%x)",(U16)addr);	
					
					#ifdef  SC16IS750_DEBUG_PRINT 
					printf("sc16_data=%x ",(U16)data_temp);					
					#endif  				
				}
				else if(data_temp==CAM_MOV) return 1;//ryan@20150417
//				else if((data_temp==STX)&&(count>=9))
				else if((data_temp==STX)&&(count>=5))
				{

				SC16_com_buff[0]=data_temp;

					loop=1;
					while((error_flag==1)&&(loop<=7))
					{
						
						
					SC16_com_buff[loop]=ReadByte(DRP_ID[addr]);


						#if 1///ryan@20150605
							if(SC16_com_buff[loop]==ETX&&((SC16_com_buff[1]>=0x52))&&(etx_flag==0)&&(loop<=3)) 
							{	
							etx_flag=1;
							//loop++;
							//SC16_com_buff[loop]=ReadByte(DRP_ID[addr]);
							//error_flag=0;//end loop   //ryan@20150420
							//printf("get first EXT");
							}
							else if(SC16_com_buff[loop]==ETX)
								{
								loop++;
								SC16_com_buff[loop]=ReadByte(DRP_ID[addr]);
								error_flag=0;///endi loop //ryan@20150420
								//printf("get data");
								}
						#else
						if(SC16_com_buff[loop]==ETX) 
						{	
						loop++;
						SC16_com_buff[loop]=ReadByte(DRP_ID[addr]);
						//buff_flag=0;
						error_flag=0;//ryan@20150420
						}
						#endif
						
					
						
					loop++;
				
					}

						//ryan
						if((SC16_com_buff[1]==0xff)&&(SC16_com_buff[2]==0x92))
						{
						//Cam_boot_count_flag++;						
						
							Cam_boot_flag=1;
							//printf("\r\nGot Camera ready");
					
						//WriteByte(DRP_ID[2],0x02); //view com.
						//WriteByte(DRP_ID[2],0x37); 
						//WriteByte(DRP_ID[2],0x52); 
						//WriteByte(DRP_ID[2],0x03); 
						//WriteByte(DRP_ID[2],0x64); 
						}
						
						loop_temp=loop-1;

						if((loop_temp<=4)&&(error_flag==0))
						{
						
						//printf("\r\nRecived a command from device1..");
							for(loop=0;loop<=4;loop++)
							{
							//data_temp=ReadByte(DRP_ID[addr]);			
							//SC16_Com[count]=ReadByte(DRP_ID[addr]);
							RS_tx(SC16_com_buff[loop]); 
							#if 0//ryan@20151106¦^ÂÐ¤ÓºC®³±¼
							WriteByte(DRP_ID[addr+1],SC16_com_buff[loop]); 
							WriteByte(DRP_ID[addr+2],SC16_com_buff[loop]); 				
							#endif
							}		
								//}
						return 1;//if buff are error...
						}
						else if((loop_temp<=6)&&(error_flag==0))///ryan@20150602
							{

							//printf("\r\nRecived a command from device2..");
							
							for(loop=0;loop<=6;loop++)
							{
							//data_temp=ReadByte(DRP_ID[addr]);			
							//SC16_Com[count]=ReadByte(DRP_ID[addr]);
							RS_tx(SC16_com_buff[loop]); 
							#if 0//ryan@20151106¦^ÂÐ¤ÓºC®³±¼
							WriteByte(DRP_ID[addr+1],SC16_com_buff[loop]); 
							WriteByte(DRP_ID[addr+2],SC16_com_buff[loop]); 				
							#endif
							}	
								return 1;//if buff are error...
							}
						
					//else if((SC16_ComCheck(&SC16_com_buff[0])==1)&&(loop>=8)&&(error_flag==0))
						#if 1//ryan@20150602
						else if((SC16_ComCheck(&SC16_com_buff[0])==1)&&(error_flag==0))
						{
						return 1;
						}
						#endif
						else if(error_flag==0)
						{
						//bcc check
						buff_flag=SC16_com_buff[0];
							
					for(loop=1;loop<=7;loop++)
							buff_flag^=SC16_com_buff[loop];
					
						if(buff_flag==SC16_com_buff[8])
						{
					//	printf("\r\nRecived a command from device3..");
						
							for(loop=0;loop<=loop_temp;loop++)
							{
							//data_temp=ReadByte(DRP_ID[addr]);			
							//SC16_Com[count]=ReadByte(DRP_ID[addr]);
							RS_tx(SC16_com_buff[loop]); 
							#if 0//ryan220151106
							WriteByte(DRP_ID[addr+1],SC16_com_buff[loop]); 
							WriteByte(DRP_ID[addr+2],SC16_com_buff[loop]); 
							#endif
							#ifdef  SC16IS750_DEBUG_PRINT 
							printf("%x ",(U16)SC16_com_buff[loop]);					
							#endif  	
							user_timer[3]=200;
							}
						}
						//else						
						//printf("ECOM,");
						
						return 1;
						}
						else
							return 1;
				}
				else
					{
				//if data isn't NAK or ACK of value that it should be send 1 byte to devices..
						#if 0
						RS_tx(data_temp); 
						WriteByte(DRP_ID[addr+1],data_temp); 
						WriteByte(DRP_ID[addr+2],data_temp); 

				//for(loop=1;loop<=(count-1);loop++)
						for(loop=1;loop<=4;loop++)
						{
						data_temp=ReadByte(DRP_ID[addr]);			
						//SC16_Com[count]=ReadByte(DRP_ID[addr]);
						RS_tx(data_temp); 
						WriteByte(DRP_ID[addr+1],data_temp); 
						WriteByte(DRP_ID[addr+2],data_temp); 
				
						#ifdef  SC16IS750_DEBUG_PRINT 
						printf("%x ",(U16)SC16_com_buff[loop]);					
						#endif  			
						}		

						//EnUserTimer(USERTMID3,40);
						user_timer[3]=200;
						//printf("\r\n count=%x",(U16) count);

						#endif
					}

				
				#else	
				//printf("\r\nRecived a command from device4..");
				for(loop=0;loop<=(count-1);loop++)
				{
				data_temp=ReadByte(DRP_ID[addr]);
				
				//SC16_Com[count]=ReadByte(DRP_ID[addr]);
				RS_tx(data_temp); 
				#if 0//ryan@20151106
				WriteByte(DRP_ID[addr+1],data_temp); 
				WriteByte(DRP_ID[addr+2],data_temp); 
				#endif
					#ifdef  SC16IS750_DEBUG_PRINT 
					printf("%x ",(U16)SC16_Com[loop]);					
					#endif  
			
				}
				#endif
				
			//count++;
			//Error=TRUE;
						
			}

	//}

//for(loop=0;loop<=(count-1);loop++) RS_tx(SC16_Com[loop]); 
//for(loop=0;loop<=(count-1);loop++) WriteByte(DRP_ID[addr+1],SC16_Com[loop]); 
//for(loop=0;loop<=(count-1);loop++) WriteByte(DRP_ID[addr+2],SC16_Com[loop]); 
				
#else

/*
	if( (ReadI2C(DRP_ID[addr], LSR)&BIT1))
	{
	WriteI2C(DRP_ID[addr],FCR,0x03);   //RXFIFO_reset 
	DELAY_FOR(50);
	WriteI2C(DRP_ID[addr],FCR,0x01);   //RXFIFO_reset 
	}
	else
		{
		*/
			while( (ReadI2C(DRP_ID[addr], LSR)&BIT0)&&(count<=17))
			{
			//data_temp=ReadByte(DRP_ID[addr]);
			SC16_Com[count]=ReadByte(DRP_ID[addr]);
			count++;
			Error=TRUE;
			}

	//	}

for(loop=0;loop<=(count-1);loop++) RS_tx(SC16_Com[loop]); 
for(loop=0;loop<=(count-1);loop++) WriteByte(DRP_ID[addr+1],SC16_Com[loop]); 
for(loop=0;loop<=(count-1);loop++) WriteByte(DRP_ID[addr+2],SC16_Com[loop]); 
#endif


return 0;

}
//----------------------------------------
/*
void Command_Check(U8 val)//ryan@20150417
{


}
*/
//----------------------------------------
void Repeat_PWM_Com(void)
{
				WriteByte(PIC32_address,SC16_Com[0]); 
				WriteByte(PIC32_address,SC16_Com[1]); 
				WriteByte(PIC32_address,SC16_Com[2]); 
				WriteByte(PIC32_address,SC16_Com[3]); 
				WriteByte(PIC32_address,SC16_Com[4]); 

				//printf("SET_LED");
}


//-----------------------------------------
U8 SC16_DataCheck(void)
{

U8 Dev_ID=0,Error=FALSE,count=0;

		#if 0
			    if( (ReadI2C(DRP_ID[0], LSR)&BIT0))
			    	{
				       Data=ReadByte(DRP_ID[0]);
					SC16_Com[SC16_ComAddr]=Data;
					#ifdef  SC16IS750_DEBUG_PRINT 
					printf("\r\nSC16_Com[%x]=%x",(U16)SC16_ComAddr,(U16)Data);
					#endif   

					SC16_ComAddr++;	
					Error=TRUE;
			    	}
		//#elif 0
			for(Dev_ID=0;Dev_ID<=8;Dev_ID+=3)
			{
			    if( (ReadI2C(DRP_ID[Dev_ID], LSR)&BIT0))
			    	{			    		
			    		Data=ReadByte(DRP_ID[Dev_ID]);
					WriteByte(DRP_ID[Dev_ID+1], Data);
					WriteByte(DRP_ID[Dev_ID+2], Data);
					RS_tx(Data);
					//if(DRP_ID[Dev_ID]==DVR_address)
						//   SC16_Com[SC16_ComAddr]=Data;						
						
					#ifdef  SC16IS750_DEBUG_PRINT 
					printf("\r\nSC16_Com[%x]=%x",(U16)(SC16_ComAddr),(U16)Data);
					#endif   
					//SC16_ComAddr++;
					Error=TRUE;				
			    	}
				
				//Dev_ID+=2;
   			}
			
		   #else

   			  // if( ReadI2C(DRP_ID[0], LSR)&BIT0)  SC16_SendDataSelect(0);
   			  // if( ReadI2C(DRP_ID[3], LSR)&BIT0)  SC16_SendDataSelect(3);
   			 //  if( ReadI2C(DRP_ID[6], LSR)&BIT0)  SC16_SendDataSelect(6);

			   	    #ifdef power_startup_check
					
					    if(DVR_startup_flag==TRUE)
   					    SC16_SendDataSelect(0);
					    else
					    check_startup(0);		
		
					    if(Cam_startup_flag==TRUE)
   					    SC16_SendDataSelect(6);
					    else
					    check_startup(6);		
					
			        //  #else			
   				  
				    #endif	

				if(work_flag==0)	
					{
					  SC16_SendDataSelect(0);
					   //printf("\r\nSC16_SendDataSelect(0);");
					   work_flag=1;
					}
				else if(work_flag==1)
					{
   				    SC16_SendDataSelect(6);   
					  // printf("\r\nSC16_SendDataSelect(6);");
					work_flag=0;
					}
				//else if(work_flag==3)
				//	{
	 			  // SC16_SendDataSelect(3);
				  // work_flag=0;
					//}

			#endif
return Error; 
}
//----------------------------------------

void SC16_data_reset(U16 sel)
{
/*
#define camera_press	 	BIT1
#define _camera_ang	 	BIT2
#define _camera_rang	BIT3
#define _camera_IRD0		BIT4
#define _camera_IRD1		BIT5
#define _camera_IRD2		BIT6
#define _camera_IRD3		BIT7
#define _camera_IRD4		BIT8
#define _camera_IRD5		BIT9
#define _camera_IRD6		BIT10
#define _dvr_temp 			BIT11
*/
if(SC16_busy_flag&sel) return;

	switch(sel)
	{
	  case camera_temp:  Temp_check() ;break;     //0
	  case camera_press:  Press_check() ;break;	
	  case _camera_ang:  Get_Camera_Ang();break;
	  case _camera_rang: Get_Camera_RAng();break;	
#if 0//ryan@20151201
case _camera_IRD0: break;//Get_Camera_IRD(0x41);break;	
	  case _camera_IRD1: break;//Get_Camera_IRD(0x42);break;	
	  case _camera_IRD2: break;//Get_Camera_IRD(0x43);break;	
	  case _camera_IRD3: break;//Get_Camera_IRD(0x44);break;	
	  case _camera_IRD4: break;//Get_Camera_IRD(0x45);break;		///8
	  case _camera_IRD5: break;//Get_Camera_IRD(0x46);break;		///9
	  case _camera_IRD6: break;//Get_Camera_IRD(0x47);break;		//10
#endif
	  case _dvr_temp: Get_DVR_temp();break;				//11
	case camera_version: Get_Camera_Ver();break;				//11	
	  //case camera_version:    
	  //if(SC16_busy_flag&sel) return;
	  //				SC16_busy_flag|=sel;
	  //			Get_Camera_Ver(); break;

	default: break;
	}

//SC16_busy_flag=1;
}
//---------------------------------------
U8 Camera_move_loop=1;
extern U8 SC16_com_state;//ryan@20151216
void Camera_move(void)
{
//static U8 work_flag;
U8 mask[4]={0x01,0x02,0x10,0x20};
U8 cam[4]={0x31,0x34,0x41,0x42};
U8 BCC[4]={0x07,0x02,0x77,0x74};
//U8 loop;
#if 1//ryan@20151130

			if(Camera_move_loop==1)
			{
				if((Camera_flag&0x01)==0x01)
				{
				WriteByte(DRP_ID[2],0x02); 
				WriteByte(DRP_ID[2],0x37); 
				WriteByte(DRP_ID[2],0x31); 
				WriteByte(DRP_ID[2],0x03); 
				WriteByte(DRP_ID[2],0x07); 
				SC16_com_state=2;//rang. polling first//ryan@20151214
				}	

				if((Camera_flag&0x02)==0x02)
				{
				WriteByte(DRP_ID[2],0x02); 
				WriteByte(DRP_ID[2],0x37); 
				WriteByte(DRP_ID[2],0x34); 
				WriteByte(DRP_ID[2],0x03); 
				WriteByte(DRP_ID[2],0x02); 
				SC16_com_state=2;//rang. polling first//ryan@20151214
				}	
				Camera_move_loop=0;
			}
			else
			{
				if((Camera_flag&0x10)==0x10)
				{
				WriteByte(DRP_ID[2],0x02); 
				WriteByte(DRP_ID[2],0x37); 
				WriteByte(DRP_ID[2],0x41); 
				WriteByte(DRP_ID[2],0x03); 
				WriteByte(DRP_ID[2],0x77); 
					SC16_com_state=3;//rang. polling first//ryan@20151214
				}	

				if((Camera_flag&0x20)==0x20)
				{
				WriteByte(DRP_ID[2],0x02); 
				WriteByte(DRP_ID[2],0x37); 
				WriteByte(DRP_ID[2],0x42); 
				WriteByte(DRP_ID[2],0x03); 
				WriteByte(DRP_ID[2],0x74); 
					SC16_com_state=3;//rang. polling first//ryan@20151214
				}	

				Camera_move_loop=1;
			}
#else
		for(loop=0;loop<4;loop++)
		{
				if((Camera_flag&mask[loop])>=1)
				{
				WriteByte(DRP_ID[2],0x02); 
				WriteByte(DRP_ID[2],0x37); 
				WriteByte(DRP_ID[2],cam[loop]); 
				WriteByte(DRP_ID[2],0x03); 
				WriteByte(DRP_ID[2],BCC[loop]); 
				}	
		}
#endif
		
}

//----------------------------------------
#if 0
void check_startup(U8 addr)
{

U8 loop=0,Error=FALSE,count=0,data_temp=0;


			if( ReadI2C(DRP_ID[addr], LSR)&BIT0)
			{   
				count=ReadI2C(DRP_ID[addr], RXLVL);
				
					 if((count==0)||(count<=5)) return;
					 
					//#ifdef  SC16IS750_DEBUG_PRINT 
					//printf("\r\n SC16_ID=%x Data=",(U16) DRP_ID[addr]);
					//#endif  
					//#ifdef  SC16IS750_DEBUG_PRINT 
					//printf("\r\n count=%x Data=",(U16) count);
					//#endif  

				for(loop=0;loop<=(count-1);loop++)
				{
				data_temp=ReadByte(DRP_ID[addr]);

					if(addr==0)
					{
					   if(DVR_Com[loop]!=data_temp) return;
					   Error++;
					   	if(Error>=5) DVR_startup_flag=1;
							#ifdef  SC16IS750_DEBUG_PRINT 
							printf("\r\nDVR_startup=OK");					
							#endif 
					}
					else if(addr==6)
					{
					   if(Cam_Com[loop]!=data_temp) return;
					   Error++;
    					   	if(Error>=5) Cam_startup_flag=1;
							#ifdef  SC16IS750_DEBUG_PRINT 
							printf("\r\nCamera_startup=OK");					
							#endif 							
					}

			
				}
						
			}


}
#endif
//-----------------------------------------
//reset sc16 data
//-----------------------------------------
U8 SC16_ComCheck(U8 *addr)
{

//if(*addr!=0x02) return 0;
U8 pos=0,temp=0;
addr++;
 switch(*addr)
 	{
		case 0x32: 
			addr++;
			if(*addr==0x34)
			{
			addr++;
			Camera_Ang[3]=*addr;
			addr++;						
			Camera_Ang[2]=*addr;
			addr++;												
			Camera_Ang[1]=*addr;
			addr++;												
			Camera_Ang[0]=*addr;			
			SC16_busy_flag&=~(_camera_ang);
		       return 1;
			}					
			else if(*addr==0x35)
				{
				addr++;
				Camera_RAng[3]=*addr;
				addr++;						
				Camera_RAng[2]=*addr;
				addr++;												
				Camera_RAng[1]=*addr;
				addr++;												
				Camera_RAng[0]=*addr;			
				SC16_busy_flag&=~(_camera_rang);
				 return 1;
				}
			#if 0//ryan@20151106
			else if((*addr>=0x41)&&(*addr<=0x47))
				{
				pos=*addr;
				pos-=0x41;				
				temp=pos*4;
				addr++;
				Camera_IRDA[temp+3]=*addr;
				addr++;						
				Camera_IRDA[temp+2]=*addr;
				addr++;												
				Camera_IRDA[temp+1]=*addr;
				addr++;												
				Camera_IRDA[temp+0]=*addr;			
				SC16_busy_flag&=~(_camera_IRD0<<pos);
				 return 1;
				}
			#endif
				else  if(*addr==0x4f)
						{
						addr++;
						Camera_ver0=*addr;
						addr++;						
					 	Camera_ver1=*addr;
						addr++;												
					 	Camera_ver2=*addr;
						SC16_busy_flag&=~(camera_version);
						  return 1;
						}	
				
			
			break;
		case 0x34: 
						addr++;
						if(*addr==0x31)
						{
						addr++;
						DVR_temp[1]=*addr;
						addr++;						
						DVR_temp[0]=*addr;
						SC16_busy_flag&=~(_dvr_temp);
						return 1;
						}
						break;
		
		//case camera_temp:  Temp_check() ;break;
		//case camera_press:  Press_check() ;break;	    
		/*
		case 0x32: 
						addr++;
						if(*addr==0x4f)
						{
						addr++;
						Camera_ver0=*addr;
						addr++;						
					 	Camera_ver1=*addr;
						addr++;												
					 	Camera_ver2=*addr;
						SC16_busy_flag&=~(camera_version);
						  return 1;
						}								
						break;
				*/
		default:  //printf("\r\n not megawin com");	
						return 0;
								break;
 	}
	
return 0;
	
	//if(SC16_ComAddr>=(num-1))
	//{		
	//	if((SC16_Com[0]==STX)&&(SC16_BCC_Check(&SC16_Com[0],(num-1))))
	//	{
	//		switch(SC16_Com[1])
	//			{
	//				case Monitor_Com:
	//								Monitor_set(SC16_Com[2]);	
	//						             break;
	//				case PWM_Com:
	//								PWM_set(SC16_Com[2]);
	//						             break;										 
	//				default: 	             break;
	//	
	//			}
	//		return TRUE;
	//	}	
      //}

					//#ifdef get_data_buff 
					//printf("\r\n Got data from the sc16");					
					//#endif 
	 
     
}

//----------------------------------------

U8 BCC_Cal(U8 *addr,U8 count)
{
	U8 f_val=0;
	U8 s_val=0;
	U8 loop=0;
	count--;

for(loop=0;loop<=count;loop++)
{
  // f_val=*addr;  
   
   f_val^=*addr;  
  addr++;    
}
return f_val;

/*
   f_val=*addr;  //XOR 0-3  //0
   addr++;            ///1
   //com[0]=*addr;   
   f_val^=*addr;    
   addr++;          ///2
   //com[1]=*addr;
   f_val^=*addr;    
   addr++;    ///3
   f_val^=*addr;
   //addr++;

if(count==8)
	{
 addr++;    ///4
   f_val^=*addr;
 addr++;    ///5
   f_val^=*addr;
 addr++;    ///6
   f_val^=*addr;
 addr++;    ///7
   f_val^=*addr;
  
	}

   addr++;

//if(f_val==*addr)
	return f_val;
*/
}
//----------------------------------------
#if 0
void Get_Data(U8 addr,U8 val)
{

switch(addr)
{
case 1:	Send_Camera_Temp();  get_data_addr=0;break; ///1
case 2:	Send_Camera_Press();get_data_addr=0;	break;	///2
case 3:	Sent_Camera_Ang(); get_data_addr=0;break; //camera angle.///3
case 4: 	Sent_Camera_RAng(); get_data_addr=0;break; //camera Rangle.///4
case 5:	Sent_Camera_IRD(val);get_data_addr=0;get_data_val=0;break;  //camera IRD.///5	
case 6: Sent_DVR_temp();get_data_addr=0;break;  //DVR_tempe.///6
case 7: Version_check();  get_data_addr=0;break;		///megawin cpu version 	///7
case 8: Camera_Version_check();  get_data_addr=0;break;		///megawin cpu version 	///7
}
get_data_addr=0;
get_data_val=0;
}
#endif
//----------------------------------------
extern U16 timerout4;
extern U16 timerout3;
extern U8  CB_flag;
//#define get_delay 15-10
#define get_delay 50
U8 SC16_BCC_Check(U8 *addr )
{
	U8 loop;
	U8 f_val=0;
	U8 s_val=0;
   U8  com[3]; 

#ifdef BCC_noSTXEXT           
   addr++;       //XOR 1-2
   f_val=*addr;
   com[0]=*addr;
   addr++;
   f_val^=*addr;
   com[1]=*addr;
   addr++;

#else
   f_val=*addr;  //XOR 0-3  //0
   addr++;            ///1
   com[0]=*addr;   
   f_val^=*addr;    
   addr++;          ///2
   com[1]=*addr;
   f_val^=*addr;    
   addr++;    ///3
   com[2]=*addr;  
   f_val^=*addr;
   //addr++;

if(Com_pos==6)//ryan@20150602
{
 addr++;    ///4
   f_val^=*addr;
 addr++;    ///5
   f_val^=*addr;
}else if(Com_pos==8)
	{
 addr++;    ///4
   f_val^=*addr;
 addr++;    ///5
   f_val^=*addr;
 addr++;    ///6
   f_val^=*addr;
 addr++;    ///7
   f_val^=*addr;
  
	}
   #endif
   addr++;

		

									
		if(f_val==*addr)	
		{
			 if((com[0]==0x37)&&((com[1]>=0x4a&&com[1]<=0x4f)||(com[1]==0x54)||(com[1]==0x55)))
			{
				 RS_tx(STX);
				 RS_tx(com[0]);
				 RS_tx(com[1]);				 				 
				 RS_tx(ETX);
				 RS_tx(f_val);	

				#if 1//ryan@20150706 feeback pip of data to camera
		
				if(Cam_boot_flag==1)	
				{
				WriteByte(PIC32_address,STX); 
				WriteByte(PIC32_address,com[0]); 
				WriteByte(PIC32_address,com[1]); 
				WriteByte(PIC32_address,ETX); 
				WriteByte(PIC32_address,f_val); 
				}
				
				 #endif
			}   
			 else if(com[0]==0x38&&com[1]>=0x3d&&com[1]<=0x60)
			 	{
				 RS_tx(ACK);
			 	}	
			 #if 1//ryan@20150814
			 		else if((com[0]==0x31)&&(com[1]==0x31)) 
			 			{
			 			Send_Camera_Temp();
			 			//timerout3+=timerout4;
			 			//CB_flag=1;	///timerout3=get_delay;
						//get_data_addr=1;/// Send_Camera_Temp();		///1	
			 			}
					else if(com[0]==0x31&&(com[1]==0x33))	
							{
							Send_Camera_Press();
							//timerout3+=timerout4;
			 				//CB_flag=1;//timerout3=get_delay;
							//get_data_addr=2; ///Send_Camera_Press();		///2	
						}
					else if(com[0]==0x31&&(com[1]==0x34))
							{
							Sent_Camera_Ang();
							//timerout3+=timerout4;
			 				//CB_flag=1;//timerout3=get_delay;
							//get_data_addr=3;///	 Sent_Camera_Ang(); //camera angle.///3	
							}
					else if(com[0]==0x31&&(com[1]==0x35))
							{
							Sent_Camera_RAng();
							//timerout3+=timerout4;
			 				//CB_flag=1;//timerout3=get_delay;
							//get_data_addr=4;	/// Sent_Camera_RAng();  //camera Rangle.///4
							}
					#if 1//not check IRD
					else if(com[0]==0x31&&com[1]>=0x41&&com[1]<=0x47) 
						{
						Sent_Camera_IRD(0);
						//timerout3+=timerout4;
						//CB_flag=1;//timerout3=get_delay;
						//get_data_addr=5;	///Sent_Camera_IRD(com[1]);  //camera IRD.///5	
						//get_data_val=com[1];
						}
					#endif
					else if(com[0]==0x33&&(com[1]==0x31))
							{
							Sent_DVR_temp();
							//timerout3+=timerout4;
							//CB_flag=1;//timerout3=get_delay;
							//get_data_addr=6;/// Sent_DVR_temp();  //DVR_tempe.///6
						}
					else if(com[0]==0x31&&com[1]==0x50) 
							{
							Version_check();
							//timerout3+=timerout4;
							//CB_flag=1;//timerout3=get_delay;
							//get_data_addr=7;//// Version_check();  		///megawin cpu version 	///7	
							}
					else if(com[0]==0x31&&com[1]==0x4f) //Send_Camera_Ver();
						{
						Camera_Version_check();
						//timerout3+=timerout4;	
						//CB_flag=1;//timerout3=get_delay;
						//get_data_addr=8;//// Version_check();  		///PIC cpu s/w version 	///8
						}
			 #else
					else if((com[0]==0x31)&&(com[1]==0x31)) Send_Camera_Temp();		///1		      
					else if(com[0]==0x31&&(com[1]==0x33))	 Send_Camera_Press();		///2
					#if 1//ryan@20150804
					else if(com[0]==0x31&&(com[1]==0x34))	 Sent_Camera_Ang(); //camera angle.///3
					else if(com[0]==0x31&&(com[1]==0x35))	 Sent_Camera_RAng();  //camera Rangle.///4
					else if(com[0]==0x31&&com[1]>=0x41&&com[1]<=0x47)	Sent_Camera_IRD(com[1]);  //camera IRD.///5	
					else if(com[0]==0x33&&(com[1]==0x31))	 Sent_DVR_temp();  //DVR_tempe.///6
					#endif
					else if(com[0]==0x31&&com[1]==0x50)  Version_check();  		///megawin cpu version 	///7			
					//else if(com[0]==0x31&&com[1]==0x4f) Send_Camera_Ver();
				#endif
			 			 		else 
			 					{			 					

		
									
									#if 1//ryan@20150602
									///check all of command
									if(Check_other_Com())
									{
									
									for(loop=0;loop<=Com_pos;loop++) 			
							 		SC16_SendData(SC16_Com[loop]); 

									user_timer[5]=4;//ryan@20151130
									user_timer[3]=(20);//reset polling time..
									
									//printf("\r\n Sent COM to Camera");//ryan@20150908
									#ifdef power_startup_check
									if((Com_flag==dvr_com_flag)&&(DVR_startup_flag==0))
									RS_tx(NAK);

									if((Com_flag==camera_com_flag)&&(Cam_startup_flag==0))
									RS_tx(NAK);
									#endif
									
									}
									else
										{
										RS_tx(NAK);
										#ifdef  SC16IS750_DEBUG_PRINT 
										printf("\r\nCommand_Check fail");
	  									#endif      	
		
										}
									#endif
									
								return FALSE;
								}
							
			#ifdef  SC16IS750_DEBUG_PRINT 
			printf("\r\nSC16_BCC_Check pass");
	  		#endif
			return TRUE;
						
		}
		else
		{
			RS_tx(NAK);
			#ifdef  SC16IS750_DEBUG_PRINT 
			printf("\r\nSC16_BCC_Check fail");
	  		#endif      	
		      return FALSE;
		}

		
		
}

//-----------------------------------------

U8 Check_other_Com(void)
{

if((SC16_Com[1]==0xff)){ //ryan@20150415
	Com_flag=camera_com_flag;  
	return TRUE;
}

//02,37,53,03,65, Camera Stop cammand..

if((SC16_Com[1]==0x37)&&((SC16_Com[2]==0x31)||(SC16_Com[2]==0x34)||(SC16_Com[2]==0x53))){

		if(SC16_Com[2]==0x31) //ryan@20150416
			{
			Camera_flag=((Camera_flag&0x30)|0x01);//set/clear  up move
			RS_tx(ACK);
			}
		else if(SC16_Com[2]==0x34)
			{
			Camera_flag=((Camera_flag&0x30)|0x02);//set/clear down move
			RS_tx(ACK);			
			}
		else
			Camera_flag=0x00; //clear all move

		
	Com_flag=camera_com_flag;  
	return TRUE;
}

if((SC16_Com[1]==0x37)&&(SC16_Com[2]>=0x41)&&(SC16_Com[2]<=0x47)) {

		if(SC16_Com[2]==0x41)//ryan@20150416
			{
			Camera_flag=((Camera_flag&0x03)|0x10);//set/clear CCW move
			RS_tx(ACK);
			}
		else if(SC16_Com[2]==0x42)
			{
			Camera_flag=((Camera_flag&0x03)|0x20);//set/clear CW move
			RS_tx(ACK);
			}

			
	Com_flag=camera_com_flag;  
	return TRUE;
}

if((SC16_Com[1]==0x31)&&(SC16_Com[2]>=0x57&&SC16_Com[2]<=0x5c))
			{
			RS_tx(ACK);
			Set_Video((SC16_Com[2]-0x57),SC16_Com[3]);//for TW2835 video set
			return TRUE;
			}



return TRUE;//ryan@21050602

if((SC16_Com[1]==0x37)&&(SC16_Com[2]>=0x50)&&(SC16_Com[2]<=0x52)) {
	Com_flag=dvr_com_flag;  
	return TRUE;
}

if((SC16_Com[1]==0x38)&&(SC16_Com[2]>=0x31)&&(SC16_Com[2]<=0x3c)) {
	Com_flag=camera_com_flag;  
	return TRUE;
}

if((SC16_Com[1]==0x31)&&((SC16_Com[2]==0x34)||(SC16_Com[2]==0x35))){
	Com_flag=camera_com_flag;  
	return TRUE;
}

if((SC16_Com[1]==0x31)&&(SC16_Com[2]>=0x41)&&(SC16_Com[2]<=0x47))  {
	Com_flag=camera_com_flag;  	
	return TRUE;
}
if((SC16_Com[1]==0x31)&&(SC16_Com[2]>=0x4f)&&(SC16_Com[2]<=0x53)) {
	Com_flag=camera_com_flag;  		
	return TRUE;
}


if((SC16_Com[1]==0x33)&&((SC16_Com[2]==0x31)||(SC16_Com[2]==0x4f))) {
	Com_flag=dvr_com_flag;  		
	return TRUE;
}

if((SC16_Com[1]==0x33)&&(SC16_Com[2]>=0x35)&&(SC16_Com[2]<=0x37)) {
	Com_flag=dvr_com_flag;  		
	return TRUE;
}

#if 1//ryan@20151210
if((SC16_Com[1]==0x33)&&(SC16_Com[2]>=0x51)&&(SC16_Com[2]<=0x5b)){
	Com_flag=dvr_com_flag;  		
	return TRUE;
}

if((SC16_Com[1]==0x33)&&((SC16_Com[2]>=0x5c)||(SC16_Com[2]==0x61))){
	Com_flag=camera_com_flag;  		
	return TRUE;
}

#else
if((SC16_Com[1]==0x33)&&(SC16_Com[2]>=0x51)&&(SC16_Com[2]<=0x53)){
	Com_flag=dvr_com_flag;  		
	return TRUE;
}

if((SC16_Com[1]==0x33)&&((SC16_Com[2]==0x5c)||(SC16_Com[2]==0x5d))){
	Com_flag=camera_com_flag;  		
	return TRUE;
}
#endif
//if((SC16_Com[1]==0x32)&&((SC16_Com[2]==0x31)||(SC16_Com[2]==0x4f))) {
//	Com_flag=dvr_com_flag;  		
//	return TRUE;
//}
//if((SC16_Com[1]==0x32)&&(SC16_Com[2]>=0x33)&&(SC16_Com[2]<=0x35)) return TRUE;
//if((SC16_Com[1]==0x32)&&(SC16_Com[2]>=0x41)&&(SC16_Com[2]<=0x47)) return TRUE;


if((SC16_Com[1]==0x37)&&(SC16_Com[2]>=0x50)&&(SC16_Com[2]<=0x52)){
	Com_flag=dvr_com_flag;  		
	return TRUE;
}


return FALSE;

}

//----------------------------------------
#if 0
U8 parity(U8 ino)
{
	U8 noofones = 0;
//	unsigned long mask = 0x00000001ul; /* start at first bit */

	U8 mask = 0x01; /* start at first bit */

	while(mask != 0) /* until all bits tested */
	{
		if(mask & ino) /* if bit is 1, increment noofones */
		{
			noofones++;
		}
		mask = mask << 1; /* go to next bit */
	}

	/* if noofones is odd, least significant bit will be 1 */
	return (noofones & 1); 


}
#endif
//-----------------------------------------
//U8 Com_check(U8 com,U8 start, U8 count)
//{
  

//}

//-----------------------------------------
#if 0
U8 ADT75_init(void)
{

U8 Ctemp=0;
U16 Dtemp=0;

//ADT75_SetCon(0x55);
//Dtemp=ADT75_GetTemp();
//Ctemp=ADT75_GetCon();
ADT75_SetThyst(0x4420);
ADT75_SetTOs(0x5220);
ADT75_SetCon(0x02);


#ifdef  ADT75_Debug
Printf("GetThyst=%X",(U16)ADT75_GetThyst());
Printf(" GetTOs=%X  ",(U16)ADT75_GetTOs());
Printf(" GetCon=%X  ",(U16)ADT75_GetCon());
    Printf("GetTemp=%X degree\r\n",(U16)((ADT75_GetTemp()>>4)/16));
 //   Printf("ADT75_GetCon=%X\r\n", ADT75_GetCon());
#endif   


return 1;

}
#endif
//-----------------------------------------

void ResetDevice(U8 addr)
{
 register   U8 temp;
    temp = ReadI2C(addr, IOContro);
    temp |= 0x08;
     WriteI2C(addr, IOContro, temp);
      
//    WriteRegister(SC16IS750_REG_IOCONTROL, temp_iocontrol);   
//    temp_iocontrol = ReadRegister(SC16IS750_REG_IOCONTROL);
//    temp_iocontrol |= 0x08;
//    WriteRegister(SC16IS750_REG_IOCONTROL, temp_iocontrol); 
    
  //  return; 
}
//-----------------------------------------
U16 SetBaudrate(U8 addr, U32 baudrate) //return error of baudrate parts per thousand
{

//register   U16 divisor;
 U32 divisor;

 U8 prescaler;
 U8 temp_lcr;//,temp_mcr;
   
   // uint32_t actual_baudrate;
   //  int16_t error;
    //uint16_t divisor;
   // uint8_t prescaler;
   // uint32_t actual_baudrate;
  //  int16_t error;
   // uint8_t temp_lcr;

    if ( (ReadI2C(addr,MCR)&0x80) == 0) { //if prescaler==1
        prescaler = 1;
    } else {
        prescaler = 4;
    }

	//baudrate=9600;

   divisor = (SC16IS750_CRYSTCAL_FREQ/prescaler)/(baudrate*16);



#ifdef SC16IS750_DEBUG_PRINT
Printf("\r\n");
Printf("SetBaudrate_Dev_addr=%x\r\n",(U16) addr);
Printf("SetBaudrate_MCR=%x\r\n",(U16) ReadI2C(addr,MCR));
Printf("SetBaudrate_prescaler=%x\r\n",(U16) prescaler);
Printf("SetBaudrate_divisor=%x\r\n",(U16) divisor);
#endif 
		
 	WriteI2C(addr, LCR, 0x00); /// WriteRegister(SC16IS750_REG_LCR,temp_lcr); 

    temp_lcr = ReadI2C(addr,LCR); ///ReadRegister(SC16IS750_REG_LCR);
    	
    temp_lcr |= 0x80;
	
    WriteI2C(addr, LCR, temp_lcr); /// WriteRegister(SC16IS750_REG_LCR,temp_lcr); 
    //write to DLL
     WriteI2C(addr, DLL, (U8)divisor); ///WriteRegister(SC16IS750_REG_DLL,(uint8_t)divisor);
    //write to DLH
      WriteI2C(addr, DLH, (U8)(divisor>>8)); /// WriteRegister(SC16IS750_REG_DLH,(uint8_t)(divisor>>8));

#ifdef SC16IS750_DEBUG_PRINT
Printf("SetBaudrate_DLL=%x\r\n",(U16) ReadI2C(addr,DLL));
Printf("SetBaudrate_DLH=%x\r\n",(U16) ReadI2C(addr,DLH));
#endif 

    temp_lcr &= 0x7F;
   WriteI2C(addr, LCR, temp_lcr); ///WriteRegister(SC16IS750_REG_LCR,temp_lcr); 

return 1;
   /* 
    actual_baudrate = (SC16IS750_CRYSTCAL_FREQ/prescaler)/(16*divisor);
    error = ((float)actual_baudrate-baudrate)*1000/baudrate;
#ifdef  SC16IS750_DEBUG_PRINT   
    Serial.print("Desired baudrate: ");
    Serial.println(baudrate,DEC);
    Serial.print("Calculated divisor: ");
    Serial.println(divisor,DEC);
    Serial.print("Actual baudrate: ");
    Serial.println(actual_baudrate,DEC);    
    Serial.print("Baudrate error: ");
    Serial.println(error,DEC);    
#endif     
    
    return error;
 */
}
//-----------------------------------------
void SetLine(U8 addr, U8 data_length, U8  parity_select, U8  stop_length )
{
    U8 temp_lcr;
    temp_lcr = ReadI2C(addr,LCR); ///ReadRegister(SC16IS750_REG_LCR);
    temp_lcr &= 0xC0; //Clear the lower six bit of LCR (LCR[0] to LCR[5]
//#ifdef  SC16IS750_DEBUG_PRINT 
//    Serial.print("LCR Register:0x");
//    Serial.println(temp_lcr,DEC);
//#endif   
    switch (data_length) {            //data length settings
        case 5:
            break;
        case 6:
            temp_lcr |= 0x01;
            break;
        case 7:
            temp_lcr |= 0x02;
            break;
        case 8:
            temp_lcr |= 0x03;
            break;
        default:
            temp_lcr |= 0x03;
            break;
    }

    if ( stop_length == 2 ) {
        temp_lcr |= 0x04;
    }
    
    switch (parity_select) {            //parity selection length settings
        case 0:                         //no parity
             break;
        case 1:                         //odd parity
            temp_lcr |= 0x08;
            break;
        case 2:                         //even parity
            temp_lcr |= 0x18;
            break;
        case 3:                         //force '1' parity
            temp_lcr |= 0x03;
            break;
        case 4:                         //force '0' parity
            break;
        default:
            break;
    } 
    
    WriteI2C(addr, LCR, temp_lcr);/// WriteRegister(SC16IS750_REG_LCR,temp_lcr);
}
//-----------------------------------------
/*
void GPIOSetPinMode(U8 addr,U8 pin_number, U8 i_o)
{
    U8 temp_iodir;
    
    temp_iodir = ReadI2C(addr,IODir); ///ReadRegister(SC16IS750_REG_IODIR);
    if ( i_o == OUTPUT ) {
      temp_iodir |= (0x01 << pin_number);
    } else {
      temp_iodir &= (U8)~(0x01 << pin_number);
    } 
    
    WriteI2C(addr, IODir, temp_iodir);///WriteRegister(SC16IS750_REG_IODIR, temp_iodir);
    //return;
}

void GPIOSetPinState(U8 addr,U8 pin_number, U8 pin_state)
{
    U8 temp_iostate;
    
    temp_iostate =  ReadI2C(addr,IOState);///ReadRegister(SC16IS750_REG_IOSTATE);
    if ( pin_state == 1 ) {
      temp_iostate |= (0x01 << pin_number);
    } else {
      temp_iostate &= (U8)~(0x01 << pin_number);
    } 
    
    WriteI2C(addr, IODir, IOState);///WriteRegister(SC16IS750_REG_IOSTATE, temp_iostate);
  //  return;
}

U8 GPIOGetPinState(U8 addr,U8 pin_number)
{
     uint8_t temp_iostate;
    
    temp_iostate = ReadI2C(addr,IOState);///ReadRegister(SC16IS750_REG_IOSTATE);
    if ( temp_iostate & (0x01 << pin_number)== 0 ) {
      return 0;
    } 
    return 1;
   // return;
}

*/
//-----------------------------------------
void GPIOSetPortMode(U8 addr,U8 port_io)
{

 WriteI2C(addr, IODir, port_io); ///WriteRegister(SC16IS750_REG_IODIR, port_io);
  //  return;

}
//-----------------------------------------
void GPIOSetPortState(U8 addr,U8 port_state)
{
 WriteI2C(addr, IOState, port_state); /// WriteRegister(SC16IS750_REG_IOSTATE, port_state);
}
//-----------------------------------------
U8 GPIOGetPortState(U8 addr)
{
//#ifdef  SC16IS750_DEBUG_PRINT 
 //   printf("\r\n**Addr=%X PortState=%X\r\n",(U16)addr,(U16) ReadI2C(addr,IOState));
    //Serial.println(ReadRegister(SC16IS750_REG_RXLVL), DEC);
//#endif    
    return  ReadI2C(addr,IOState);////ReadRegister(SC16IS750_REG_IOSTATE);

}
//-----------------------------------------
#if 0
U8 FIFOAvailableData(U8 addr)
{
#ifdef  SC16IS750_DEBUG_PRINT 
    printf("\r\n**Available data=%X",(U16)ReadI2C(addr,RXLVL));
    //Serial.println(ReadRegister(SC16IS750_REG_RXLVL), DEC);
#endif      
   return ReadI2C(addr,RXLVL);///ReadRegister(SC16IS750_REG_RXLVL);
}
//-----------------------------------------
U8 FIFOAvailableSpace(U8 addr)
{

#ifdef  SC16IS750_DEBUG_PRINT 
    printf("\r\n**Available Space=%X",ReadI2C(addr,TXLVL));
    //Serial.println(ReadRegister(SC16IS750_REG_RXLVL), DEC);
#endif   
   return ReadI2C(addr,TXLVL);///ReadRegister(SC16IS750_REG_TXLVL);

}

//-----------------------------------------

void EnableTransmit(U8 addr,U8 OnOff)
{
    U8 temp_efcr;
    temp_efcr = ReadI2C(addr,EFCR);///ReadRegister(SC16IS750_REG_EFCR);
    if ( OnOff == 0) {
        temp_efcr |= 0x04;       
    } else {   
        temp_efcr &= 0xFB;
    }   
    WriteI2C(addr, EFCR, temp_efcr); ///WriteRegister(SC16IS750_REG_EFCR,temp_efcr);
    
    //return;
}
#endif
//-----------------------------------------
#if 0
void flush(U8 addr)  //Transmit Holding Register Empty indicator.
{
	U8 tmp_lsr;
	
	do {
             #ifdef  SC16IS750_DEBUG_PRINT 
             printf("\r\n**THR is busy..=%X",addr);
            //Serial.println(ReadRegister(SC16IS750_REG_RXLVL), DEC);
            #endif
		tmp_lsr = ReadI2C(addr,LSR);///ReadRegister(SC16IS750_REG_LSR);
		
	} while ((tmp_lsr&0x20) ==0);


}
#endif
//---------------------------------------------------------
#if 0
U8 ping(U8 addr)
{

	WriteI2C(addr, SPR, 0x55);///WriteRegister(SC16IS750_REG_SPR,0x55);
	///if (ReadRegister(SC16IS750_REG_SPR) !=0x55) {
if (ReadI2C(addr,SPR) !=0x55) {
             #ifdef  SC16IS750_DEBUG_PRINT 
             printf("*ping is fail(0x55)=%X\r\n",(U16)addr);
             #endif
		return 0;
	}

	WriteI2C(addr, SPR, 0xAA);///WriteRegister(SC16IS750_REG_SPR,0xAA);
	//if (ReadRegister(SC16IS750_REG_SPR) !=0xAA) {
      if (ReadI2C(addr,SPR)!=0xAA) {
            #ifdef  SC16IS750_DEBUG_PRINT 
            printf("*ping is fail(0xAA)=%X\r\n",(U16)addr);
             #endif
		return 0;
	}

            #ifdef  SC16IS750_DEBUG_PRINT 
             printf("*ping is pass, Address=%X\r\n",(U16)addr);
             #endif
            
	return 1;

}
#endif
//-----------------------------------------

//-----------------------------------------

void WriteByte(U8 addr, U8 val)
{

 /*  
	U8 tmp_lsr;
	while ( FIFOAvailableSpace() == 0 ){
#ifdef  SC16IS750_DEBUG_PRINT 
		Serial.println("No available space");
#endif  	
	
	};

#ifdef  SC16IS750_DEBUG_PRINT 
    Serial.println("++++++++++++Data sent");
#endif          
    WriteRegister(SC16IS750_REG_THR,val);
*/

//	do { 
//		tmp_lsr = ReadI2C(addr,LSR);///ReadRegister(SC16IS750_REG_LSR);
//	} while ((tmp_lsr&0x20) ==0);

	
	WriteI2C(addr, THR, val);///WriteRegister(SC16IS750_REG_THR,val);
	

    
}

U8 ReadByte(U8 addr)
{
//	volatile U8 val;
	U8 val;
	#if 1
	val = ReadI2C(addr,RHR);///ReadRegister(SC16IS750_REG_RHR);    
	  return val;
	#else
	if (FIFOAvailableData(addr) == 0)
	{

#ifdef  SC16IS750_DEBUG_PRINT 
printf("\r\n**No data available");
#endif          
		//return -1;
		return '\0';
	} 
	else 
	{
	  
		#ifdef  SC16IS750_DEBUG_PRINT 
		printf("\r\n** available ID=%x ,Data=%x",(U16)addr, (U16) ReadI2C(addr,RXLVL));
		#endif   

		val = ReadI2C(addr,RHR);///ReadRegister(SC16IS750_REG_RHR);    
	  return val;

	}

	#endif
	

}
#if 0
void TW2835_get(U8 page)
{
U8 x,loop=0,step=0;
U16 val=0;


step=0;
val=0;

/*
for(x=0;x<=2;x++)
{
val=(TW28_ReadByte(page,0x8c+step)+(((TW28_ReadByte(page,0x8f+step)&BIT2&BIT3)<<6)));
printf("\r\n Vin=%x,HDELAY_PB=%x",(U16) x ,(U16)val);
step+=0x10;
val=0;
}

*/
/*
step=0;
val=0;
for(x=0;x<=2;x++)
{
val=(TW28_ReadByte(page,0x02+step)+(((TW28_ReadByte(page,0x06+step)&BIT0&BIT1)<<8)));
printf("\r\n Vin=%x,HDELAY_XY=%x",(U16) x ,(U16)val);
step+=0x10;
val=0;
}
*/


step=0;
val=0;
for(x=0;x<=2;x++)
{
//TW28_WriteByte(page,0x24,0);
val=(TW28_ReadByte(page,0x04+step)+(((TW28_ReadByte(page,0x06+step)&BIT4)<<4)));
printf("\r\n Vin=%x,VDELAY_XY=%x",(U16) x ,(U16)val);
step+=0x10;
val=0;
}
TW28_WriteByte(1,0x74,10);
printf("\r\n OSD start=%x",(U16)TW28_ReadByte(1,0x74));


/*
step=0;
val=0;
for(x=0;x<=2;x++)
{
val=(TW28_ReadByte(page,0x03+step)+(((TW28_ReadByte(page,0x06+step)&BIT2&BIT3)<<6)));
printf("\r\n Vin=%x,HAvtive_XY=%x",(U16) x ,(U16)val);
step+=0x10;
val=0;
}

step=0;
val=0;
for(x=0;x<=2;x++)
{
val=(TW28_ReadByte(page,0x05+step)+(((TW28_ReadByte(page,0x06+step)&BIT5)<<3)));
printf("\r\n Vin=%x,VAvtive_XY=%x",(U16) x ,(U16)val);
step+=0x10;
val=0;
}
*/

}
#endif

//-----------------------------------------
#if 0
U16 peek(void)
{
	/*
	if ( peek_flag == 0 ) {	
		peek_buf =ReadByte();
		if (  peek_buf >= 0 ) { 
			peek_flag = 1;
		}
	} 
	*/
	return 1 ;//peek_buf;
		
}
#endif
//-----------------------------------------
#if 0
void Set_INT(void)
{
//INT_flag=0;

EX0=1;
IT0=1;
IE0=0;  //flag
    
EX1=1;
IT1=1;
IE1=0;  //flag

EX2=1;
IT2=1;    //'1' falling edge trigger/ '0' low level trigger
IE2=0;    //flag
}
#endif
//----------------------------------------

void MCTRL_set(void)
{

//... P[7:4]:INT[5:2], P2_3:HALE, P2_2:HRDB, P2_1:HWRB, P2_0:HSPB
P2_0=0;///HSPB=0;
P2_1=1;///HWRB=1;
P2_2=1;///HRDB=1;
P2_3=0;///HALE=0;
}
//-----------------------------------------
/*
//-----------------------------------------

void Int0_interrupt(void) interrupt 0 using 1
{

IE0=0;
EA=0;


EA=1;


}

void Int1_interrupt(void) interrupt 2 using 1
{
IE1=0;
EA=0;


EA=1;


}

void Int2_interrupt(void) interrupt 6 using 1
{

IE2=0;
EA=0;


EA=1;


}
*/

