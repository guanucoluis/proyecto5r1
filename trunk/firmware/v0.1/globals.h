#ifndef GLOBALS_H
#define GLOBALS_H

//INCLUDES
#include "glcdK0108.h"
#include "objetos.h"
#include <dsPIC_delay.h>
#include  <p33FJ128GP804.h>

#include <adquisicion.h>
#include <sensores.h>
#include <SD.h>

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

#define PIN_POWER_ON_OFF	PORTBbits.RB3
#define TRIS_POWER_ON_OFF	TRISBbits.RB3
#define IE_POWER_ON_OFF		INTCON3bits.INT3IE
#define IF_POWER_ON_OFF		INTCON3bits.INT3IF
#define IP_POWER_ON_OFF		INTCON2bits.INT3IP
#define	EDGE_POWER_ON_OFF	INTCON2bits.INTEDG3

//Defines del CAC
//#define PIN_SALIDA_CAC	PORTBbits.RB3		//Pin de salida de la señal de Control del Ángulo de Conducción hacia el circuito de potencia
//#define PIN_ENTRADA_CC	PORTBbits.RB4		//Pin de entrada de la señal de Cruce por Cero proveniente del opto
#define RET_DET_CC			238							// A - Retardo hasta la Detección del Cruce por Cero.
#define RET_CP					50							// C - Retardo de propagación de la señal en el Circuito de Potencia. Podría despreciarse
#define ANCHO_PULSO_DISPARO	500					// D - Ancho del  Pulso que Dispara al TRIAC. Mientras más chico, mejor.
#define DEM_CC					340							// E - Demora desde que entra la interrupción del Cruce por Cero hasta que este ocurre efectivamente
#define SEM_PER_LINEA		10000						// SP - Mitad del período de la línea de 220
#define PRESC_TIMER			4								//Prescaler del Timer						
#define K1							((float) 1 / (float) ((float) PRESC_TIMER * (float) 1000000 * (float) TCY)) //Cuentas por useg. Factor de cálculo
#define PNC_CAC_INI			0.5		//Porcentaje del semiciclo que no estará en conducción
#define PER_NO_CONDUC_CAC_INI 	(unsigned int) (((float) SEM_PER_LINEA * (float) PNC_CAC_INI))
#define PER_PS_HIGH_CAC_INI 		(unsigned int) (256 - ((float) ((float) K1 *  (float) (PER_NO_CONDUC_CAC_INI - RET_DET_CC - RET_CP) ) / ((float) 256)))
#define PER_PS_LOW_CAC_INI 			(unsigned int) (256 - ((float) ((float) K1 *  (float) (PER_NO_CONDUC_CAC_INI - RET_DET_CC - RET_CP) ) - (float) ((float) PER_PS_HIGH_CAC_INI * (float) 256)))
#define PER_SS_HIGH_CAC_INI 		(unsigned int) (256 - ((float) ((float) K1 *  (float) (PER_NO_CONDUC_CAC_INI + DEM_CC - RET_CP) ) / ((float) 256)))
#define PER_SS_LOW_CAC_INI 			(unsigned int) (256 - ((float) ((float) K1 *  (float) (PER_NO_CONDUC_CAC_INI + DEM_CC - RET_CP) ) - (float) ((float) PER_SS_HIGH_CAC_INI * (float) 256)))
#define PER_D_HIGH_CAC 					(unsigned int) (256 - ((float) ((float) K1 *  (float) (ANCHO_PULSO_DISPARO)) / (float) 256))
#define PER_D_LOW_CAC		 				(unsigned int) (256 - ((float) ((float) K1 *  (float) (ANCHO_PULSO_DISPARO)) - (float) ((float) PER_D_HIGH_CAC * (float) 256)))

//Defines del módulo de PWM
#define OC1	1
#define	OC2	2
//#define DUTY_CYCLE_CCP4_INI	100
//#define DUTY_CYCLE_CCP5_INI	700

//Defines de la Configuración
#define PWM_LUZ_FONDO	OC1
#define PWM_CONTRASTE	OC2
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


//Variables del CAC (Control del Ángulo de Conducción)
extern volatile float pNCCAC;								//Porcentaje de No Conducción. pNC < 1
extern volatile unsigned int  perNoConducCAC;	//Cuentas que tiene que hacer el Timer
extern volatile unsigned char perPSHighCAC; //Parte alta de la cuenta hasta el disparo en el primer semiciclo. Parte baja de F
extern volatile unsigned char perPSLowCAC; 	//Parte baja de la cuenta hasta el disparo en el primer semiciclo. Parte alta de F
extern volatile unsigned char perSSHighCAC; //Parte alta de la cuenta hasta el disparo en el segundo semiciclo. Parte baja de G
extern volatile unsigned char perSSLowCAC; 	//Parte baja de la cuenta hasta el disparo en el segundo semiciclo. Parte alta de G
extern volatile unsigned char perDHighCAC; 	//Parte alta de la cuenta hasta la finalización del disparo. Parte baja de D
extern volatile unsigned char perDLowCAC; 	//Parte baja de la cuenta hasta la finalización del disparo. Parte alta de D
extern volatile unsigned char bHabCAC;		//Bandera de habilitación del CAC

//Variable Contadora Genérica
extern volatile unsigned int Contador1ms;

//Variables para la conversión de punto flotante a decimal
//extern signed int parteDecimal;
//extern signed int parteEntera;

//ESTRUCTURAS

//Estructura de PWM
/*struct PWM{
	float	porcentDutyCycle;			//Porcentaje entre cero y uno del duty cycle
	unsigned int 	dutyCycle;		//
};*/

//Estructura de tiempo
struct Tiempo{
	unsigned int 	ms;		//Milisegundos
	unsigned char seg;	//Segundos
	unsigned char min;	//Minutos
	unsigned char hs;		//Horas
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

/*union Int16{
	unsigned char byte;
	unsigned int word;
	struct {
		unsigned char LB; //Lower Byte
		unsigned char HB; //High Byte
	};
};*/

//Estructura de configuración
struct Config{
	unsigned bDurmiendo	:1;		//Indica si el Microcontrolador está duermiendo (1) o no (0)
	unsigned bNoEsPrimerEncendido	:1;	//Indica si Mecoel se acaba de despertar de un apagado desde el botón de PowerOff (1) o no (0)

	unsigned luzFondo		:4;		//Valor de la Luz de Fondo (BackLight)
	unsigned contraste	:4;		//Valor del contraste

	//Variables de la Lectura/Escritura en la Flash
	union Int32 address;	//Dirección para la lectura/borrado/escritura
	union Int16 data;
	unsigned char*	ptrBuffer;	//Puntero al buffer usado para leer/escribir en la Flash
	void*	ptrStruct;	//Puntero a la esctructura que se quiere cargar/guardar en la Memoria Flash
};

//VARIABLES GLOBALES

//Variables para la conversión de punto flotante a decimal y luego a string
extern struct FloatToStr fToStr;

//Variables de tiempo
extern struct Tiempo tiempo;

//Variables de Configuración
extern struct Config config;

//variables de la función BinBCD
extern unsigned char BCD[9];
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
unsigned char IniciarEnsayoProgramado(void);
void SetPWMDutyCycle(unsigned int dutyCycle, unsigned char module);
void DespertarMecoel(void);
void DormirMecoel(void);

void SetLuzFondo(void);
void SetContraste(void);
void GuardarConfigFlash(void);
void CargarConfigFlash(void);

#endif //GLOBALS_H


