

#define	I2C_SCL		P2_5
#define	I2C_SDA		P2_6
#define	Power_EN1  	P4_1
#define	Power_EN2  	P4_2
#define	Power_EN3  	P3_4
#define SC16_RST  P3_5 

#define  DVR_address    0x98
#define RF_ID_address   0x92
#define PIC32_address  0x9a
#define Temp_address  0x90



#define USERTMADDR	user_timer
#define USERTMVAL0	user_timer[0]
#define USERTMVAL1	user_timer[1]
#define USERTMVAL2	user_timer[2]
#define Camera_p 0
#define Rear_p 1
#define DVR_p 2

//camera move flag //ryan@20150417
#define CAM_MOV  0x08

//command list

#define STX 0x02
#define ETX 0x03
#define ACK 0x06 
#define NAK 0x15
#define Monitor_Com    0x37
#define Monitor_offset  0x4a
#define PWM_Com 	  0x38
#define PWM1_offset    0x3d   ///LED3
#define PWM2_offset    0x43   ///LED4
#define PWM3_offset    0x49  ///LED5
#define PWM4_offset    0x4f  ///LED6
#define PWM5_offset    0x55  ///LED7
#define PWM6_offset    0x5b  ///LED8

//version 
#define Ver0   (0)  
//#define Ver1   (9)
#define Ver1   (0x31)  //0x31+0x30=0x61=a
//#define Ver2   (2) //20150302
//efine Ver2   (3) //20150306
//#define Ver2   (4)//20150331
//#define Ver2   (5)//20150416
//#define Ver2   (6)//20150417
//#define Ver2   (3)//20150420
///#define Ver2   (4)//20150522
//#define Ver2   (5)//20150602
//#define Ver2   (6)//20150605
//#define Ver2   (7)//20150706
//#define Ver2   (8)//20150706
//#define Ver2   (0x61)//20150706   V0.9.a
//#define Ver2   (0x63)//20150706   V0.9.c
//#define Ver2   (0x64)//20151019   V0.9.d
//#define Ver2   (0x65)//20151019   V0.9.e
//#define Ver2   (0x66)//20151019   V0.9.f
//#define Ver2   (0x30)//20151019   V0.9.a
//#define Ver2   (0x32)//20151019   V0.a.3//ryan@20151210
//#define Ver2   (0x33)//20151019   V0.a.3//ryan@20160226
//#define Ver2   (0x34)//20151019   V0.a.4//ryan@20160303
//#define Ver2   (0x35)//20180710   V0.a.5//ryan@20180710
//#define Ver2   (0x36)//20180710   V0.a.6//ryan@20180727
//#define Ver2   (0x37)//20180731   V0.a.7//ryan@20180731
//#define Ver2   (0x38)//20180731   V0.a.8//ryan@20180921
//#define Ver2   (0x39)//20180731   V0.a.9//ryan@20181204
#define Ver2   (0x61)//V0.a.a//ryan@20181217
//#warning "NED-5M-Sensor-Camera V0.a.9"

#define _LED_PWM_HALF 1 ////ryan@20180731 奈良要求LED PWM 變成一半?
#define _LED_PWM_DECREASE   1 ////ryan@20180921 奈良要求LED PWM 在減少。

//#define buff_num      13///ryan@20151029		#define buff_num      12
#define buff_num      6///ryan@20151029		#define buff_num      12

#define buff_sel(x)    (BIT0<<x)

//----------------------------
#define camera_temp 	BIT0
#define camera_press	 	BIT1
#define _camera_ang	 	BIT2
#define _camera_rang	BIT3
//#define _camera_IRD0		BIT4
//#define _camera_IRD1		BIT5
//#define _camera_IRD2		BIT6
//#define _camera_IRD3		BIT7
//#define _camera_IRD4		BIT8
//#define _camera_IRD5		BIT9
//#define _camera_IRD6		BIT10
//#define _dvr_temp 			BIT11
//#define camera_version  	BIT12

#define _dvr_temp 			BIT4
#define camera_version  	BIT5



//#define BCC_noSTXEXT
//#define  SC16IS750_DEBUG_PRINT 
//#define UART_debug
//#define v_data
//#define ADT75_Debug
//#define screen3
#define OSD_off
//#define power_startup_check
//#define black_change
//#define dvr_parity
//#define TW2835_degug
//#define black_boundary
//void Set_PWM_Output (U8 addr,U8 val);
//void PWM_init(void);
#define get_data_buff
#define PIP_adjust
//#define Monitor_debug
#define Crop_Shrink_flag  //ryan@20150413 //add crop+shrink views
//#define get_data_debug
#define Move_Camera
//#define press_debug
//#define camera_speed
#define Camera_test 1


U16 ADC_read(U8 sel);

void Send_Camera_Ver(void);
void Get_Camera_Ver(void);
void Send_Camera_Temp(void);
void Send_Camera_Press(void);

void Get_Camera_Ang(void);
void Sent_Camera_Ang(void);
void Get_Camera_RAng(void);
void Sent_Camera_RAng(void);

void Get_Camera_IRD(U8 sel);
void Sent_Camera_IRD(U8 sel);

void Get_DVR_temp(void);
void Sent_DVR_temp(void);
void Get_DVR_ver(void);
void Sent_DVR_ver(void);
void Get_DVR_Year(void);
void Sent_DVR_Year(void);
void Get_DVR_MD(void);
void Sent_DVR_MDr(void);
void Get_DVR_HS(void);
void Sent_DVR_HS(void);


void Set_Camera_speed(U8 val);


 void I2Cdelay(void);
  void I2Cdelay2(void);
 void I2CStart(void);
 void I2CStart2(void);
 void I2CStop(void);
  void I2CStop2(void);
 void I2C_ACK(void);
 void I2CWriteData(BYTE value);
 void I2CWriteData2(BYTE value);
 
U16 ReadI2CWORD(BYTE addr, BYTE index);
void WriteI2CWORD(U8 addr, U8 index, U16 Data);

 U8 I2CReadData(void);
 U8 I2CReadData2(void);
  void I2C_ACK2(void);
U8 I2CReadDataWithACK(void);
U8 I2CReadDataWithACK2(void);
void WriteI2C(U8 addr, U8 index, U8 val);
U8 ReadI2C(U8 addr, U8 index);
void WriteI2C2(U8 addr, U8 index, U8 val);
U8 ReadI2C2(U8 addr, U8 index);
extern void Power_onoff(U8 val);
//U8 ADT75_init(void);
U8 Check_other_Com(void);
void check_startup(U8 addr);
void Set_channel(U8 addr);

extern U8 Monitor_set(U8 val);
extern U8 PWM_set(U8 val);

//SC16IS750-------------------------------------------

U8 SC16_init(void);
U8 SC16_DataCheck(void);
U8 SC16_SendData(U8 val);
U8 SC16_SendDataSelect(U8 addr);

U8 SC16_ComCheck(U8 *addr);
U8 SC16_BCC_Check(U8 *addr);
U8 BCC_Cal(U8 *addr,U8 count);

void SC16_data_reset(U16 sel);
extern void Get_Data(U8, U8);
U16 SetBaudrate(U8 addr, U32 baudrate);
void  ResetDevice(U8 addr);
void SetLine(U8 addr, U8 data_length, U8  parity_select, U8  stop_length );
void I2C_100Khz(void);

/*
//void GPIOSetPinMode(U8 addr,U8 pin_number, U8 i_o);
//void GPIOSetPinState(U8 addr,U8 pin_number, U8 pin_state);
//U8 GPIOGetPinState(U8 addr,U8 pin_number);
*/
void GPIOSetPortMode(U8 addr,U8 port_io);
void GPIOSetPortState(U8 addr,U8 port_state);
void GPIO_check(void);

U8 GPIOGetPortState(U8 addr);        
U8 FIFOAvailableData(U8 addr);
U8 FIFOAvailableSpace(U8 addr);
void EnableTransmit(U8 addr,U8 OnOff);
void flush(U8 addr) ;
U8 ping(U8 addr);  
void WriteByte(U8 addr, U8 val);
U8 ReadByte(U8 addr);
//void Set_INT(void);
void MCTRL_set(void);
U8 parity(U8 ino);

//void TW2835_get(U8 page);
void Bound_Set(U8 val);
void Camera_move(void);
//void Command_Check(U8 val);
void Repeat_PWM_Com(void);
void Set_Video(U8 addr, U8 val);

extern void RS_tx(U8);

//ADT75-------------------------------------

#define ADT75_SetCon(a)          	WriteI2C2(Temp_address,0x01,a)	
//#define ADT75_SetThyst(a)        	WriteI2CWORD(Temp_address,0x02,a)        
//#define ADT75_SetTOs(a)          	WriteI2CWORD(Temp_address,0x03,a)      
#define ADT75_SetOneShot(a)    	WriteI2C2(Temp_address,0x04,a)

//#define ADT75_GetCon()   	 		ReadI2C2(Temp_address,0x01)	
#define ADT75_GetCon()   	 		ReadI2CWORD(Temp_address,0x01)	

#define ADT75_GetTemp()        	ReadI2CWORD(Temp_address, 0)
#define ADT75_GetThyst()        	ReadI2CWORD(Temp_address,0x02)        
#define ADT75_GetTOs()          	ReadI2CWORD(Temp_address,0x03)      
#define ADT75_GetOneShot()    	ReadI2C2(Temp_address,0x04)


//SC16IS750 ----------------------------------------

#define  DVR_WriteByte(a,b)     	WriteI2C(DVR_address ,a ,b)
#define  DVR_SetIOMode()        	GPIOSetPortMode(DVR_address, IODir)
#define  DVR_SetIO()                	GPIOSetPortState(DVR_address, IOState)
#define  DVR_GetIO()                	GPIOGetPortState(DVR_address)
#define  DVR_SetBaudRate(a)         SetBaudrate(DVR_address, a)
#define  DVR_ReadByte(a)         	ReadI2C(DVR_address,a)

#define  RFID_WriteByte(a,b)    	WriteI2C(RF_ID_address ,a ,b)
#define  RFID_SetBaudRate(a)   	SetBaudrate(RF_ID_address, a)
#define  RFID_ReadByte(a)        	ReadI2C(RF_ID_address,a)

#define  PIC32_WriteByte(a,b) 	WriteI2C(PIC32_address,a ,b)
#define  PIC32_SetBaudRate(a)	SetBaudrate(RF_ID_address, a)
#define  PIC32_ReadByte(a)      	ReadI2C(PIC32_address ,a)

//SC16IS750 Register address---------------------------

#define RHR 0x00
#define THR 0x00
#define IER 0x01
#define FCR 0x02
#define IIR 0x02

#define LCR 0x03
#define MCR 0x04
#define LSR 0x05
#define MSR 0x06
#define SPR 0x07

#define TCR 0x06
#define TLR 0x07

#define TXLVL 0x08
#define RXLVL 0x09

#define IODir 0x0A
#define IOState 0x0B
#define IOIntEna 0x0C
#define IOContro 0x0E
#define EFCR 0x0E

#define DLL 0x00
#define DLH 0x01

//-----------------------------------------
//ADC
#define  ADC_FPBS()          ADC_read(0)
#define  ADC_TMPSER()      ADC_read(1)




