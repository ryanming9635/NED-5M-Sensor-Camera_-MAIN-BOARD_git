// ===========================================================================
//
//	Inital a division into one window
//

#include "NED.h"

code WRITE_REG_DATA Init_Vido_W1[]={
		// ************* Type 1 NTSC ****************
		// Channel scaling on Window 0-3
		{0xFFFF,0x00},	// Horizontal Scale
		{0xFFFF,0x00},	// Vertical   Scale
	
		// Window 0 Locate address
		{0x0130,   0},	// Left  
		{0x0131, 180},  // Right 
		{0x0132,   0},  // TOP   
		{0x0133, 120},  // Button
	
		// Window 1 Locate address
		{0x0134,   0},	// Left  
		{0x0135, 180},  // Right 
		{0x0136,   0},  // TOP   
		{0x0137, 120},  // Button
	
		// Window 2 Locate address
		{0x0138,   0},	// Left  
		{0x0139, 180},  // Right 
		{0x013A,   0},  // TOP   
		{0x013B, 120},  // Button
	
		// Window 3 Locate address
		{0x013C,   0},	// Left  
		{0x013D, 180},  // Right 
		{0x013E,   0},  // TOP   
		{0x013F, 120},  // Button
	
		{0xFFFF,0xFF},
	
		// ************* Type 1 PAL ****************
		// Channel scaling on Window 0-3
		{0xFFFF,0x00},	// Horizontal Scale
		{0xFFFF,0x00},	// Vertical   Scale
	
		// Window 0 Locate address
		{0x0130,   0},	// Left  
		{0x0131, 180},  // Right 
		{0x0132,   0},  // TOP   
		{0x0133, 144},  // Button
	
		// Window 1 Locate address
		{0x0134,   0},	// Left  
		{0x0135, 180},  // Right 
		{0x0136,   0},  // TOP   
		{0x0137, 144},  // Button
	
		// Window 2 Locate address
		{0x0138,   0},	// Left  
		{0x0139, 180},  // Right 
		{0x013A,   0},  // TOP   
		{0x013B, 144},  // Button
	
		// Window 3 Locate address
		{0x013C,   0},	// Left  
		{0x013D, 180},  // Right 
		{0x013E,   0},  // TOP   
		{0x013F, 144},  // Button
	
		{0xFFFF,0xFF},
};

// ---------------------------------------------------------------------------
//
//	Inital a division into two window
//
code WRITE_REG_DATA Init_Vido_W2[]={
		// ************* Type 1 NTSC ****************
		// Channel scaling on Window 0-1
		{0xFFFF,0x00},	// Horizontal Scale
		{0x7FFF,0x00},	// Vertical   Scale
	
		// Window 0 Locate address
		{0x0130,   0},	// Left
		{0x0131, 180},	// Right
		{0x0132,   0},	// TOP
		{0x0133,  60},	// Button
		// Window 1 Locate address
		{0x0134,   0},	// Left  
		{0x0135, 180},  // Right 
		{0x0136,  60},  // TOP   
		{0x0137, 120},  // Button
	
		{0xFFFF,0xFF},
	
		// ************* Type 2 NTSC ****************
		// Channel scaling on Window 0-1
		//ryan {0xFFFF,0x00},	// Horizontal Scale
		//ryan {0xFFFF,0x00},	// Vertical   Scale 


        // Channel scaling on Window 0
		#ifdef PIP_adjust//ryan@20150331
		{(21845),0x00},	// Horizontal Scale
		{(21845),0x00},	// Vertical   Scale
	//	{(0x7fff),0x00},	// Horizontal Scale
	//	{(0x7fff),0x00},	// Vertical   Scale

		#else
		{0x3FFF+8190+4095+1000+100,0x00},	// Horizontal Scale
		{0x3FFF+8190+4095+1000+100,0x00},	// Vertical   Scale
		#endif
	
		// Channel scaling on Window 1
		{0xFFFF,0x01},	// Horizontal Scale
		{0xFFFF,0x01},	// Vertical   Scale	
		// Window 0 Locate address
#ifdef PIP_adjust
		//{0x0130,   0+100-10},	// Left
		//{0x0131,  90+80},	// Right
		//{0x0132,   0+60-5},	// TOP
		//{0x0133, 120-10},	// Button
	//{0x0130,   90},	// Left  
	//{0x0131,  180},  // Right 
	//{0x0132,  60},	// TOP   
	//{0x0133, 120},  // Button

	{0x0130,   120},	// Left  
	{0x0131,  180},  // Right 
	{0x0132,  80},	// TOP   
	{0x0133, 120},  // Button

#else
		{0x0130,   0+100-10},	// Left
		{0x0131,  90+80},	// Right
		{0x0132,   0+60-5},	// TOP
		{0x0133, 120-10},	// Button
#endif		
		// Window 1 Locate address
		{0x0134,  90-90},	// Left  
		{0x0135, 180},  // Right 
		{0x0136,   0},  // TOP   
		{0x0137, 120},  // Button
	
		{0xFFFF,0xFF},

		// ************* Type 1 PAL ****************
		// Channel scaling on Window 0-1
		{0xFFFF,0x00},	// Horizontal Scale
		{0x7FFF,0x00},	// Vertical   Scale
	
		// Window 0 Locate address
		{0x0130,   0},	// Left
		{0x0131, 180},	// Right
		{0x0132,   0},	// TOP
		{0x0133,  72},	// Button
		// Window 1 Locate address
		{0x0134,   0},	// Left  
		{0x0135, 180},  // Right 
		{0x0136,  72},  // TOP   
		{0x0137, 144},  // Button
	
		{0xFFFF,0xFF},
	
		// ************* Type 2 PAL ****************
		// Channel scaling on Window 0-1
		{0x7FFF,0x00},	// Horizontal Scale
		{0xFFFF,0x00},	// Vertical   Scale
	
		// Window 0 Locate address
		{0x0130,   0},	// Left
		{0x0131,  90},	// Right
		{0x0132,   0},	// TOP
		{0x0133, 144},	// Button
		// Window 1 Locate address
		{0x0134,  90},	// Left  
		{0x0135, 180},  // Right 
		{0x0136,   0},  // TOP   
		{0x0137, 144},  // Button
	
		{0xFFFF,0xFF},
};

// ---------------------------------------------------------------------------
//
//	Inital a division into three window
//
code WRITE_REG_DATA Init_Vido_W3[]={
	// ************* Type 1 NTSC ****************
	// Channel scaling on Window 0
	{0xFFFF,0x00},	// Horizontal Scale
	{0x7FFF,0x00},	// Vertical   Scale
	// Channel scaling on Window 1
	{0x7FFF,0x01},	// Horizontal Scale
	{0x7FFF,0x01},	// Vertical   Scale
	// Channel scaling on Window 2
	{0x7FFF,0x02},	// Horizontal Scale
	{0x7FFF,0x02},	// Vertical   Scale

	// Window 0 Locate address
	{0x0130,   0},	// Left
	{0x0131, 180},	// Right
	{0x0132,   0},	// TOP
	{0x0133,  60},	// Button
	// Window 1 Locate address
	{0x0134,   0},	// Left  
	{0x0135,  90},  // Right 
	{0x0136,  60},  // TOP   
	{0x0137, 120},  // Button
	// Window 2 Locate address
	{0x0138,  90},	// Left  
	{0x0139, 180},  // Right 
	{0x013A,  60},	// TOP   
	{0x013B, 120},  // Button

	{0xFFFF,0xFF},

	// ************* Type 2 NTSC ****************
	// Channel scaling on Window 0
	{0x7FFF,0x00},	// Horizontal Scale
	{0x7FFF,0x00},	// Vertical   Scale
	// Channel scaling on Window 1
	{0x7FFF,0x01},	// Horizontal Scale
	{0x7FFF,0x01},	// Vertical   Scale
	// Channel scaling on Window 2
	{0xFFFF,0x02},	// Horizontal Scale
	{0x7FFF,0x02},	// Vertical   Scale

	// Window 0 Locate address
	{0x0130,   0},	// Left
	{0x0131,  90},	// Right
	{0x0132,   0},	// TOP
	{0x0133,  60},	// Button
	// Window 1 Locate address
	{0x0134,  90},	// Left  
	{0x0135, 180},  // Right 
	{0x0136,   0},  // TOP   
	{0x0137,  60},  // Button
	// Window 2 Locate address
	{0x0138,   0},	// Left  
	{0x0139, 180},  // Right 
	{0x013A,  60},	// TOP   
	{0x013B, 120},  // Button

	{0xFFFF,0xFF},

	// ************* Type 3 NTSC ****************
	// Channel scaling on Window 0
	{0x7FFF,0x00},	// Horizontal Scale
	{0xFFFF,0x00},	// Vertical   Scale
	// Channel scaling on Window 1
	{0x7FFF,0x01},	// Horizontal Scale
	{0x7FFF,0x01},	// Vertical   Scale
	// Channel scaling on Window 2
	{0x7FFF,0x02},	// Horizontal Scale
	{0x7FFF,0x02},	// Vertical   Scale

	// Window 0 Locate address
	{0x0130,   0},	// Left
	{0x0131,  90},	// Right
	{0x0132,   0},	// TOP
	{0x0133, 120},	// Button
	// Window 1 Locate address
	{0x0134,  90},	// Left  
	{0x0135, 180},  // Right 
	{0x0136,   0},  // TOP   
	{0x0137,  60},  // Button
	// Window 3 Locate address
	{0x0138,  90},	// Left  
	{0x0139, 180},  // Right 
	{0x013A,  60},	// TOP   
	{0x013B, 120},  // Button

	{0xFFFF,0xFF},

	// ************* Type 4 NTSC ****************
	// Channel scaling on Window 0
	{0x7FFF,0x00},	// Horizontal Scale
	{0x7FFF,0x00},	// Vertical   Scale
	// Channel scaling on Window 1
	{0x7FFF,0x01},	// Horizontal Scale
	{0xFFFF,0x01},	// Vertical   Scale
	// Channel scaling on Window 2
	{0x7FFF,0x02},	// Horizontal Scale
	{0x7FFF,0x02},	// Vertical   Scale

	// Window 0 Locate address
	{0x0130,   0},	// Left
	{0x0131,  90},	// Right
	{0x0132,   0},	// TOP
	{0x0133,  60},	// Button
	// Window 1 Locate address
	{0x0134,  90},	// Left  
	{0x0135, 180},  // Right 
	{0x0136,   0},  // TOP   
	{0x0137, 120},  // Button
	// Window 0 Locate address
	{0x0138,   0},	// Left  
	{0x0139,  90},  // Right 
	{0x013A,  60},	// TOP   
	{0x013B, 120},  // Button

	{0xFFFF,0xFF},

	// ************* Type 1 PAL ****************
	// Channel scaling on Window 0
	{0xFFFF,0x00},	// Horizontal Scale
	{0x7FFF,0x00},	// Vertical   Scale
	// Channel scaling on Window 1
	{0x7FFF,0x01},	// Horizontal Scale
	{0x7FFF,0x01},	// Vertical   Scale
	// Channel scaling on Window 2
	{0x7FFF,0x02},	// Horizontal Scale
	{0x7FFF,0x02},	// Vertical   Scale

	// Window 0 Locate address
	{0x0130,   0},	// Left
	{0x0131, 180},	// Right
	{0x0132,   0},	// TOP
	{0x0133,  72},	// Button
	// Window 1 Locate address
	{0x0134,   0},	// Left  
	{0x0135,  90},  // Right 
	{0x0136,  72},  // TOP   
	{0x0137, 144},  // Button
	// Window 2 Locate address
	{0x0138,  90},	// Left  
	{0x0139, 180},  // Right 
	{0x013A,  72},	// TOP   
	{0x013B, 144},  // Button

	{0xFFFF,0xFF},

	// ************* Type 2 PAL ****************
	// Channel scaling on Window 0
	{0x7FFF,0x00},	// Horizontal Scale
	{0x7FFF,0x00},	// Vertical   Scale
	// Channel scaling on Window 1
	{0x7FFF,0x01},	// Horizontal Scale
	{0x7FFF,0x01},	// Vertical   Scale
	// Channel scaling on Window 2
	{0xFFFF,0x02},	// Horizontal Scale
	{0x7FFF,0x02},	// Vertical   Scale

	// Window 0 Locate address
	{0x0130,   0},	// Left
	{0x0131,  90},	// Right
	{0x0132,   0},	// TOP
	{0x0133,  72},	// Button
	// Window 1 Locate address
	{0x0134,  90},	// Left  
	{0x0135, 180},  // Right 
	{0x0136,   0},  // TOP   
	{0x0137,  72},  // Button
	// Window 2 Locate address
	{0x0138,   0},	// Left  
	{0x0139, 180},  // Right 
	{0x013A,  72},	// TOP   
	{0x013B, 144},  // Button

	{0xFFFF,0xFF},

	// ************* Type 3 PAL ****************
	// Channel scaling on Window 0
	{0x7FFF,0x00},	// Horizontal Scale
	{0xFFFF,0x00},	// Vertical   Scale
	// Channel scaling on Window 1
	{0x7FFF,0x01},	// Horizontal Scale
	{0x7FFF,0x01},	// Vertical   Scale
	// Channel scaling on Window 2
	{0x7FFF,0x02},	// Horizontal Scale
	{0x7FFF,0x02},	// Vertical   Scale

	// Window 0 Locate address
	{0x0130,   0},	// Left
	{0x0131,  90},	// Right
	{0x0132,   0},	// TOP
	{0x0133, 144},	// Button
	// Window 1 Locate address
	{0x0134,  90},	// Left  
	{0x0135, 180},  // Right 
	{0x0136,   0},  // TOP   
	{0x0137,  72},  // Button
	// Window 3 Locate address
	{0x0138,  90},	// Left  
	{0x0139, 180},  // Right 
	{0x013A,  72},	// TOP   
	{0x013B, 144},  // Button

	{0xFFFF,0xFF},

	// ************* Type 4 PAL ****************
	// Channel scaling on Window 0
	{0x7FFF,0x00},	// Horizontal Scale
	{0x7FFF,0x00},	// Vertical   Scale
	// Channel scaling on Window 1
	{0x7FFF,0x01},	// Horizontal Scale
	{0xFFFF,0x01},	// Vertical   Scale
	// Channel scaling on Window 2
	{0x7FFF,0x02},	// Horizontal Scale
	{0x7FFF,0x02},	// Vertical   Scale

	// Window 0 Locate address
	{0x0130,   0},	// Left
	{0x0131,  90},	// Right
	{0x0132,   0},	// TOP
	{0x0133,  72},	// Button
	// Window 1 Locate address
	{0x0134,  90},	// Left  
	{0x0135, 180},  // Right 
	{0x0136,   0},  // TOP   
	{0x0137, 144},  // Button
	// Window 0 Locate address
	{0x0138,   0},	// Left  
	{0x0139,  90},  // Right 
	{0x013A,  72},	// TOP   
	{0x013B, 144},  // Button

	{0xFFFF,0xFF},
};

// ---------------------------------------------------------------------------
//
//	Inital a division into three window
//
code WRITE_REG_DATA Init_Vido_W4[]={
	// ************* Type 1 NTSC ****************
	// Channel scaling on Window 0~3
	{0x7FFF,0x00},	// Horizontal Scale
	{0x7FFF,0x00},	// Vertical   Scale

	// Window 0 Locate address
	{0x0130,   0},	// Left  
	{0x0131,  90},  // Right 
	{0x0132,   0},  // TOP   
	{0x0133,  60},  // Button
	// Window 1 Locate address
	{0x0134,  90},	// Left  
	{0x0135, 180},  // Right 
	{0x0136,   0},  // TOP   
	{0x0137,  60},  // Button
	// Window 2 Locate address
	{0x0138,   0},	// Left  
	{0x0139,  90},  // Right 
	{0x013A,  60},	// TOP   
	{0x013B, 120},  // Button
	// Window 3 Locate address
	{0x013C,  90},	// Left  
	{0x013D, 180},  // Right 
	{0x013E,  60},  // TOP   
	{0x013F, 120},  // Button

	{0xFFFF,0xFF},

	// ************* Type 1 PAL ****************
	// Channel scaling on Window 0~3
	{0x7FFF,0x00},	// Horizontal Scale
	{0x7FFF,0x00},	// Vertical   Scale

	// Window 0 Locate address
	{0x0130,   0},	// Left  
	{0x0131,  90},  // Right 
	{0x0132,   0},  // TOP   
	{0x0133,  72},  // Button
	// Window 1 Locate address
	{0x0134,  90},	// Left  
	{0x0135, 180},  // Right 
	{0x0136,   0},  // TOP   
	{0x0137,  72},  // Button
	// Window 2 Locate address
	{0x0138,   0},	// Left  
	{0x0139,  90},  // Right 
	{0x013A,  72},	// TOP   
	{0x013B, 144},  // Button
	// Window 3 Locate address
	{0x013C,  90},	// Left  
	{0x013D, 180},  // Right 
	{0x013E,  72},  // TOP   
	{0x013F, 144},  // Button

	{0xFFFF,0xFF},
};

// ---------------------------------------------------------------------------
//
//	Scale Horizontal Delay for Windows Type  
//
code WRITE_REG_DATA Video_HDelayInit[]= {
	{0x0002,0x15},
	{0x0012,0x1F},
	{0x0022,0x15},
	{0x0032,0x1F},
	{0xFFFF,0xFF},

	{0x0002,0x20},
	{0x0012,0x30},
	{0x0022,0x20},
	{0x0032,0x30},
	{0xFFFF,0xFF},
};

// ---------------------------------------------------------------------------
//
//	Scale Horizontal Delay for Windows Type  
//
//  ���� ==> 0:������		1:�L����
//  R/L  ==> 0:LEFT 		1:RIGHT	(�����Ω�e�������Υk�b��)
//  N/M  ==> 0:No Mirrir	1:Mirror
//  N/P  ==> 0:NTSC			1:PAL
//
#define BLACKING_RECOMPENSE

#if 1//BLACKING_RECOMPENSE
code unsigned char Video_HDelay[]={	//	���� L/R N/M N/P
	#if 0//Kane @HS 2007 @HS 2007 Ver3.4>>>>
	          0x00,						//	 0    0   0   0	//2 ���� Cam A
	          0x06,						//   	 0    0   0   1	
	          0x38,						//  	 0    0   1   0	//2 ���� Cam B
	          0x42,						//   	0    0   1   1	
	          0x36,						//   	0    1   0   0	
	          0x3B,						//   	0    1   0   1	
	          0x02,						//   	0    1   1   0	
	          0x0F,						//   	0    1   1   1	
	          0x15,						//   	1    0   0   0	Full Window
	          0x1D,						//   	1    0   0   1	
	          0x1E,						//   	1    0   1   0	
	          0x2B,						//   	1    0   1   1	
	          0x1C,						//   	1    1   0   0	
	          0x27,						//   	1    1   0   1	
	          0x1B,						//   	1    1   1   0	
	          0x20,						//   	1    1   1   1
	
	#else
//william-v2.36-971212	
	0X00,//0x10,						//	 0    0   0   0	// NTSC ���� Cam A Cam C Not mirror
	0X04,//0x04,						//   	 0    0   0   1	// PAL ���� Cam A Cam C Not mirror	
	0X32,//0x20,						//  	 0    0   1   0	// NTSC ���� Cam A Cam C  mirror
	0X46,//0x46,						//   	0     0   1   1	// PAL ���� Cam A Cam C  mirror
	0X2E,//0x1E,						//   	0    1   0   0	// NTSC  ���� Cam B Cam R Not  mirror
	0X40,//0x40,						//   	0    1   0   1	// ���� Cam B Cam R Not  mirror
	0X08,//0x1B,						//   	0    1   1   0	// NTSC  ���� Cam B Cam R   mirror
	0X0A,//0x0A,						//   	0    1   1   1	// ���� Cam B Cam R   mirror
	0x18,						//   	1    0   0   0	 NTSC Full Cam A Cam C Not mirror
	0x26,//<960904>0x1A,						//   	1    0   0   1	Full Cam A Cam C Not mirror
	0x1D,//<960904>0x22,						//   	1    0   1   0	 NTSC Full Cam A Cam C  mirror
	0x24,//<960904>0x2E,						//   	1    0   1   1	Full Cam A Cam C  mirror
	0x16,//<960904>0x20,						//   	1    1   0   0	 NTSC Full  Cam B Cam R Not  mirror
	0x26,//<960904>0x2A,						//   	1    1   0   1	Full Cam B Cam R Not  mirror
	0x1A,						//   	1    1   1   0	 NTSC Full Cam B Cam R   mirror
	0x24,//<960904>0x1E,						//   	1    1   1   1	Full Cam B Cam R   mirror
	#endif	
	//Kane @HS 2007 @HS 2007 Ver3.4<<<<
};
#else
code unsigned char Video_HDelay[]={	//	���� L/R N/M N/P		
	          0x00,					//	 0    0   0   0
	          0x02,					//   0    0   0   1	
	          0x38,					//   0    0   1   0	
	          0x47,					//   0    0   1   1	
	          0x36,					//   0    1   0   0	
	          0x43,					//   0    1   0   1	
	          0x02,					//   0    1   1   0	
	          0x06,					//   0    1   1   1	
	          0x1A,					//   1    0   0   0	
	          0x22,					//   1    0   0   1	
	          0x1D,					//   1    0   1   0	
	          0x27,					//   1    0   1   1	
	          0x1A,					//   1    1   0   0	
	          0x22,					//   1    1   0   1	
	          0x1D,					//   1    1   1   0	
	          0x27,					//   1    1   1   1	
};
#endif

//	Modify Blanking 
code WRITE_REG_DATA VidoW2_ModifyACNM[]={
		// ************* NTSC ****************
		{0x0022,0x08/*0x02*/},  //Kane @HS 2007 0810 Ver3.4
		{0x0134,0x55}, 
		{0x0135,0xB0}, 
		{0xFFFF,0xFF}
};

code WRITE_REG_DATA VidoW2_ModifyACHM[]={
		// ************* NTSC ****************
		{0x0022,0x2E /*0x2B*/}, //Kane @HS 2007 0810 Ver3.4
		{0x0134,0x55}, 
		{0x0135,0xB0}, 
		{0xFFFF,0xFF}
};

code WRITE_REG_DATA VidoW2_ModifyRBNM[]={
		// ************* NTSC ****************
		{0x0032,0x2E /*0x32*/}, 
		{0x0130,0x07}, 
		{0x0131,0x60}, 
		{0xFFFF,0xFF}
};

code WRITE_REG_DATA VidoW2_ModifyRBHM[]={
		// ************* NTSC ****************
		{0x0032,0x08/*0x19*/}, //Kane @HS 2007 @HS 2007 Ver3.4
		{0x0130,0x07}, 
		{0x0131,0x60}, 
		{0xFFFF,0xFF}
};

//Kane @HS 2007 0813 Ver3.4
code WRITE_REG_DATA VidoW2_ModifyACHM_PAL[]={
		// ************* NTSC ****************
		{0x0022,0x38 }, 
		{0x0134,0x55}, 
		{0x0135,0xB0}, 
		{0xFFFF,0xFF}
};
// ---------------------------------------------------------------------------
//
//	Inital Y Channel Tyte 0-4
//
code WRITE_REG_DATA Init_Vido_Y[]={
// *** Channel 0 ***
	{0x0160,0xC0},
	{0x0163,0x81},
	{0x0166,0x82},
	{0x0169,0x83},

	{0x008A,0x01},
	{0x016C,0x03},
	{0x016D,0x00},
	{0xFFFF,0xFF},

// *** Channel 1 ***
	{0x0160,0x80},
	{0x0163,0xC1},
	{0x0166,0x82},
	{0x0169,0x83},

	{0x009A,0x41},
	{0x016C,0x0C},
	{0x016D,0x00},
	{0xFFFF,0xFF},

// *** Channel 2 ***
	{0x0160,0x80},
	{0x0163,0x81},
	{0x0166,0xC2},
	{0x0169,0x83},

	{0x00AA,0x81},
	{0x016C,0x30},
	{0x016D,0x00},
	{0xFFFF,0xFF},

// *** Channel 3 ***
	{0x0160,0x80},
	{0x0163,0x81},
	{0x0166,0x82},
	{0x0169,0xC3},

	{0x00BA,0xC1},
	{0x016C,0xC0},
	{0x016D,0x00},
	{0xFFFF,0xFF},

// *** Channel 0-3 ***
	{0x0160,0x80},
	{0x0163,0x81},
	{0x0166,0x82},
	{0x0169,0x83},

	{0x008A,0x31},
	{0x009A,0x71},
	{0x00AA,0xB1},
	{0x00BA,0xF1},
	{0x016C,0x00},
	{0x016D,0xE4},
	{0xFFFF,0xFF},
};


