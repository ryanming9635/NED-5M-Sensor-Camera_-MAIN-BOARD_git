#ifndef __PRINTF__
#define __PRINTF__

#define SERIAL
#define KEILC	
#define CODE_P

#define _outchar(c) while(1) { if( !RS_Xbusy ) { SBUF = c; RS_Xbusy=1; break; } }
#define Putch(c) _outchar(c)

//#ifdef SERIAL

 void Printf ( const char CODE_P *fmt, ... );
 void Puts ( CODE_P char *ptr );

#define TW2835Cmd(a)   Puts ( a )

#else

 #undef  DEBUG
 #define Printf(a,b)	//
 #define Puts(a)   		//

#endif


#ifndef DEBUG

 #define dPuts(a)		//
 #define wPuts(a)		//
 #define ePuts(a)		//

#else

 void dPrintf( const char CODE_P *fmt, ... );
 void wPrintf( const char CODE_P *fmt, ... );
 void ePrintf( const char CODE_P *fmt, ... );

 void dPuts( CODE_P char *ptr );
 void wPuts( CODE_P char *ptr );
 void ePuts( CODE_P char *ptr );

#endif	// DEBUG

BYTE Getch(void);
BYTE Getche(void);


//#endif	//__PRINTF__
