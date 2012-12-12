#ifndef TECLADO_H
	#define TECLADO_H

//INCLUDES
#include "libpic30.h"
#include "globals.h"
#include "ADS1147.h"

//DEFINES RELATIVOS AL TECLADO

//DEFINES RELATIVOS A LA ACELERACION
#define ESPERA_VEL_0	5		//40 //Cantidad de veces que se debe reconocer una tecla sostenida para pasar a la siguiente velocidad de incremento
#define ESPERA_VEL_1	40	//20
#define ESPERA_VEL_2	20	//10
#define	ESPERA_VEL_3	10	//10
#define	ESPERA_VEL_4	10	//10
#define	ESPERA_VEL_5	10	//10
#define	PERIODO_INCR_0	200	//Cantidad de mseg entre incremento e incremento al iniciar el ciclo de aceleración
#define	PERIODO_INCR_1	200	
#define	PERIODO_INCR_2	170
#define	PERIODO_INCR_3	150
#define	PERIODO_INCR_4	80
#define	PERIODO_INCR_5	50
#define	PERIODO_INCR_6	50
#define CANT_INCREMENTOS_0	0	//Cantidad de incrementos para cada velocidad
#define CANT_INCREMENTOS_1	1
#define CANT_INCREMENTOS_2	1
#define	CANT_INCREMENTOS_3	2
#define	CANT_INCREMENTOS_4	2
#define	CANT_INCREMENTOS_5	3
#define	CANT_INCREMENTOS_6	5


//Defines Generales
#define NUM_COLUM			4					//Numero de columnas del teclado
#define NUM_FILAS			4					//Numero de filas del teclado
#define ANTIRREBOTE 	15				//Indica la cantidad de veces que una tecla debe ser detectada para ser tomada como válida

//Valores asignados a cada tecla
#define TECLA_NO_PRES		31
//Teclado de Control
#define TECLA_ACEPTAR		12
#define	TECLA_CANCELAR	4
#define	TECLA_DERECHA		5
#define	TECLA_IZQUIERDA	13
#define	TECLA_ARRIBA		10
#define	TECLA_ABAJO			9
//Teclado Numérico
#define TECLA_0 		13	//Tecla con el número 0 escrito
#define TECLA_1 		0		//Tecla con el número 1 escrito
#define TECLA_2 		1		//Tecla con el número 2 escrito
#define TECLA_3 		2
#define TECLA_4 		3
#define TECLA_5 		TECLA_ARRIBA
#define TECLA_6 		6
#define TECLA_7 		TECLA_IZQUIERDA
#define TECLA_8 		TECLA_ABAJO
#define TECLA_9 		TECLA_DERECHA

#define PUERTO_TECLADO			PORTB
#define TRIS_PUERTO_TECLADO	TRISB
//#define VAL_TRIS_PUERTO_TECLADO	0b11110000

//Salidas del teclado
#define	salida0						PORTBbits.RB8
#define	salida1						PORTBbits.RB9
#define	salida2						PORTBbits.RB10
#define	salida3						PORTBbits.RB11

//Entradas del teclado
#define	entrada0					PORTBbits.RB12
#define	entrada1					PORTBbits.RB13
#define	entrada2					PORTBbits.RB14
#define	entrada3					PORTBbits.RB15

//ESTRUCTURAS RELATIVAS AL TECLADO
struct Tecla{
	char bPulsada		:1;	//Indica que la tecla ha sido pulsada, pero ya está libre
	char bSostenida:1; //Indica que la tecla ha sido pulsada y continúa siendo presionada
};

struct Teclado{
	//Declaración de teclas
	struct Tecla arriba;
	struct Tecla abajo;
	struct Tecla derecha;
	struct Tecla izquierda;
	struct Tecla aceptar;
	struct Tecla cancelar;
	
	//Variables de Teclado
	volatile unsigned columna	:	5;					//Variable que indica cual de las columnas (salidas) tiene que ser activada
	volatile unsigned auxCol	:	5;					//Almacena temporalmente el número de columna (salida) activada
	volatile unsigned auxFila	:	5;					//Almacena temporalmente el número de fila (entrada) activada
	volatile unsigned char cuentaAntirreb;	//Contador de la cantidad de veces que una tecla debe ser detectada para ser tomada como válida
	volatile unsigned teclaActual	:	5;			//Almacena la tecla que se ha detectado en el flujo actual de la rutina
	volatile unsigned teclaAnterior	:	5;		//Almacena la tecla que se ha detectado la vez anterior que se ejecuto la rutina
	volatile unsigned teclaPulsada	:	5;		//Almacena la tecla que está siendo presionada y que ya a pasado la comprobación antirrebote, pero solo es tomada una sola vez
	volatile unsigned teclaSostenida	:	5;	//Almacena la tecla que está siendo presionada y sostenida en el tiempo por el usuario
	volatile unsigned int contTeclaSostenida; //Contador que almacena la cuenta de la cantidad de veces que se he tenido sostenida una tecla
	volatile unsigned int periodoIncremento; 	//Almacena el período con el que se hacen los incrementos
	volatile unsigned int contIncremento; 	//Contador usado para determinar la frecuencia de incrementos
	volatile unsigned velIncremento		:	3;	//Almacena la velocidad con la que debieran hacerse los incrementos en función del tiempo transcurrido desde que se presiono la tecla	
	volatile unsigned bHabIncremento	: 1;	//Bandera que indica cuando se puede realizar un incremento
};

//VARIABLES GLOBALES DE TECLADO
extern struct Teclado teclado;
 
//PROTOTIPOS DE FUNCIONES
void IniTeclado(void);
void ProcesoTeclado(void);

#endif //TECLADO_H
