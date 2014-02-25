#ifndef GLOBALS_H
#define GLOBALS_H

//INCLUDES

#include <dsPIC_delay.h>
#include  <p33FJ128GP804.h>
#include	<stdint.h>
#include <cpu.h>
#include <includes.h>

//DEFINES RELATIVOS A LAS BASES DE TIEMPO
#define TOSC				0.000000203021	//0.000000040200
#define TCY					((float) 4 * (float) TOSC)
#define	FCY					10000000UL
//#define	BASE_T0			(TCY * 10000)			

//DEFINES GENERALES	
//Defines utilizados para hacer demoras
#define NOP5 Nop();Nop();Nop();Nop();Nop();
#define NOP10 NOP5 NOP5
#define NOP15 NOP10 NOP5
#define NOP20 NOP10 NOP10
#define NOP30 NOP20 NOP10
#define NOP40 NOP20 NOP20
#define NOP50 NOP40 NOP10
#define NOP100 NOP50 NOP50

#ifndef	NULL
#define	NULL	0
#endif


//#define	Sleep();	_asm SLEEP _endasm
//#define	Reset();	_asm RESET _endasm

//#define PIN_POWER_ON_OFF	
//#define TRIS_POWER_ON_OFF	
#define IE_POWER_ON_OFF		INTCON3bits.INT3IE
#define IF_POWER_ON_OFF		INTCON3bits.INT3IF
#define IP_POWER_ON_OFF		INTCON2bits.INT3IP
#define	EDGE_POWER_ON_OFF	INTCON2bits.INTEDG3

//VARIABLES GLOBALES

extern OS_EVENT	*mBoxPromData;	//Manejador del MailBox que significa que un nuevo periodo ha sido leido y debe almacenarse en el buffer

extern struct ConfigdsPIC33 config;

#define TIMEOUT_PEND_MBOX	50000

//DIO variable
extern uint16_t ValChZero, CntData ;
extern float Prom;
extern float *PtrPromFromMBox;
extern float PromFromMbox;
extern uint16_t whole;
extern uint16_t decimal;
extern char array[];
extern float TmpCnt;

extern uint8_t err;
extern uint8_t iiTaskUart;

extern float TmpCnt;

extern OS_EVENT	*mBoxPromData;	//Manejador del MailBox que significa que un nuevo periodo ha sido leido y debe almacenarse en el buffer



#endif //GLOBALS_H


