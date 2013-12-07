#ifndef GLOBALS_H
#define GLOBALS_H

//INCLUDES
#include "glcdK0108.h"
#include "objetos.h"
#include "interfaz.h"
#include <dsPIC_delay.h>
#include  <p33FJ128GP804.h>
#include	<stdint.h>

#include <adquisicion.h>
#include <sensores.h>
#include <SD.h>
#include <interfaz_cfg.h>
#include <FlashMem_cfg.h>
#include <cpu.h>
#include <interfaz.h>
#include <ADS1147.h>

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

#define	MENOS_DE_CINCO_CIFRAS_SIGNIF 	0
#define	CINCO_CIFRAS_SIGNIF						1

//#define	Sleep();	_asm SLEEP _endasm
//#define	Reset();	_asm RESET _endasm

//#define PIN_POWER_ON_OFF	
//#define TRIS_POWER_ON_OFF	
#define IE_POWER_ON_OFF		INTCON3bits.INT3IE
#define IF_POWER_ON_OFF		INTCON3bits.INT3IF
#define IP_POWER_ON_OFF		INTCON2bits.INT3IP
#define	EDGE_POWER_ON_OFF	INTCON2bits.INTEDG3

//Defines del módulo de PWM
#define OC1	1
#define	OC2	2
//#define DUTY_CYCLE_CCP4_INI	100
//#define DUTY_CYCLE_CCP5_INI	700

//Defines de la Configuración
#define PWM_LUZ_FONDO	OC1
#define PWM_CONTRASTE	OC2
#define DUR_LUZ_FONDO_DEF	10
#define GLCD_CONTRASTE	PORTBbits.RB3
#define	TRIS_GLCD_CONTRASTE		TRISBbits.TRISB3
#define GLCD_BACKLIGHT	PORTBbits.RB2
#define	TRIS_GLCD_BACKLIGHT		TRISBbits.TRISB2
#define LUZ_FONDO_INI	0
#define CONTRASTE_INI	1023



//Defines de la conversión de punto flotante a char
/*#define UNA_CIFRA_DECIMAL			10
#define DOS_CIFRAS_DECIMALES	100
#define TRES_CIFRAS_DECIMALES	1000*/

//Variable Contadora Genérica
extern volatile unsigned int Contador1ms;

//ESTRUCTURAS
//Estructura de tiempo
#ifndef TIEMPO
#define TIEMPO
extern struct Tiempo{
	unsigned int 	ms;		//Milisegundos
	unsigned char seg;	//Segundos
	unsigned char min;	//Minutos
	unsigned char hs;		//Horas
};
#endif

//Estructura para los semáforos
struct Eventos{
	
		OS_EVENT	*mBoxSensVel;	//Manejador del MailBox que significa que un nuevo periodo ha sido leido y debe almacenarse en el buffer
		OS_EVENT	*semCelda;		//Manejador del mensaje que significa que un nuevo periodo ha sido leido y debe almacenarse en el buffer
		OS_EVENT	*semMuestra;	//Manejador del mensaje que significa que un nuevo periodo ha sido leido y debe almacenarse en el buffer
		OS_EVENT	*semGuardar;	//Manejador del mensaje que significa que un nuevo periodo ha sido leido y debe almacenarse en el buffer
};

//Estrucutra para la conversión de punto flotante a decimal y luego a string
struct FloatToStr{
	float flotante;
	signed long int parteDecimal;
	signed long int parteEntera;
	//unsigned char letraMulti;	//Letra multiplicadora: nada,u,m,K o M
	//unsigned char nroCifras;
	unsigned char nroCifrasHastaComa;	//Número de cifras enteras antes de la coma
	unsigned char nroCifrasEnteras;
	//unsigned char nroCifrasDecimales;
	unsigned char expNeg;
	unsigned long int multi;		//Multiplicador (corre la coma "nroDecimales" veces)
};	

#ifndef _INT16_
#define	_INT16_
union Int16{
	unsigned char byte;
	unsigned int word;
	struct {
		unsigned char LB; //Lower Byte
		unsigned char HB; //High Byte
	};
};
#endif

union Int32{
	unsigned char byte;
	unsigned int word;
	unsigned long u32;
	struct {	//Acceso por bytes
		unsigned char LB;	//Lower Byte
		unsigned char HB;	//High Byte
		unsigned char UB;	//Upper Byte
		unsigned char MB;	//Most Byte
	};
};

//Estructura de la Lectura/Escritura en la Flash
struct RTSP{
	int16_t nvmAdr;
	int16_t nvmAdru;
	int16_t nvmAdrPageAligned;
	int16_t nvmRow;
	int16_t nvmSize;
};

//Estructura de configuración
struct ConfigdsPIC33{
	unsigned bDurmiendo	:1;		//Indica si el Microcontrolador está duermiendo (1) o no (0)
	unsigned bNoEsPrimerEncendido	:1;	//Indica si MeDEf se acaba de despertar de un apagado desde el botón de PowerOff (1) o no (0)

	unsigned luzFondo		:4;		//Valor de la Luz de Fondo (BackLight)
	unsigned contraste	:4;		//Valor del contraste
	unsigned bDuracionLuzFondo :1;	//Indica si se selecciono (1) o no (0) que la luz de fondo tenga una duración
	uint16_t duracionLuzFondo;			//Duración en segundos de la luz de fondo
	uint16_t contLuzFondo;					//Contador para determinar cuando apagar la luz de fondo

	//Variables de la Lectura/Escritura en la Flash
	struct RTSP rtsp;
	//unsigned char*	ptrBuffer;	//Puntero al buffer usado para leer/escribir en la Flash
	void*	ptrStruct;	//Puntero a la esctructura que se quiere cargar/guardar en la Memoria Flash
};

//VARIABLES GLOBALES

//Variables de Configuración
extern struct ConfigdsPIC33 config;

extern struct Eventos eventos;

//Variables para la conversión de punto flotante a decimal y luego a string
extern struct FloatToStr fToStr;

//Variables de tiempo
extern struct Tiempo tiempo;

//variables de la función BinBCD
extern unsigned char BCD[10]; // ya que convierte un signed long int que va -2147483648 a 2147483647
extern signed char signo;

//variables auxiliares
extern float e,f,g,h;
extern unsigned char dato1;
extern signed int	offsetADC;
extern signed int gainADC;
extern unsigned char aux_a; 
extern unsigned char aux_b;
extern signed int valor_aux;
extern unsigned int valor_aux1;
extern char iaux,jaux;
extern unsigned char vecAux[15];
extern char pruebCadena[5]; // = {'L','i','m','a','\0'};

//PROTOTIPOS DE FUNCIONES GLOBALES
void BinBCD(signed long int valor);
void FloatToString(char *floatStr, unsigned char formato);
void FloatToScientific(char floatStr[], unsigned char formato);
unsigned char IniciarEnsayoProgramado(void);
void SetPWMDutyCycle(unsigned int dutyCycle, unsigned char module);
//void DespertarMecoel(void);
//void DormirMecoel(void);

extern struct ValPropSpinEdit vPSpinEdits[];
extern struct ValPropProgBar vPProgBars[];

void SetLuzFondo(void);
void SetContraste(void);

#endif //GLOBALS_H


