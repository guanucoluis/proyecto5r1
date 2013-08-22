#ifndef	SENSORES_H
#define SENSORES_H

#include <globals.h>
#include <ucos_ii.h>

#define	CANT_GRUP_PARAM	8

#define	DIAMETRO_TRAC_DEFECTO			180	//Valores en centímetros
#define	DIAMETRO_NO_TRAC_DEFECTO	70	//Valores en centímetros
#define PI_SOBRE_8	0.392699	//Pi dividido en 8
#define CAMBIO_UNIDAD	36	//Para pasar de cm/mseg a m/seg

#define SENSOR_TRAC_IN	PORTCbits.RC3
#define SENSOR_MAQ_IN		PORTCbits.RC4	

#define PIN_DATO_FUERZA_LISTO	PORTBbits.RB5

#define	CANT_MUESTRAS_FUERZA 5

#define PERIODO_MAX 500
//#define TIME_OUT_POR_PERIODO_MAX	0x0A
#define PERIODO_RUEDA_PARADA	1000
#define PERIODO_REFRESCO_SENS	400
#define CANT_PERIODOS 30

struct Diametros{
	uint16_t	diametroTrac;		//Diámetro de la rueda de Tracción en centímetros
	uint16_t	diametroNoTrac;	//Diámetro de la rueda de No Tracción	 en centímetros
};

struct GrupoDeParam{
	unsigned bParamCargadosDesdeFlash	:1;	//Indica si los parámetros ya han sido cargados desde la Flash (1) o no (0)	

	uint8_t	iGdP;
	struct Diametros diametros[8];
};

struct SensorDeVelocidad{
	unsigned 	bBufferCompleto	:	1;
	unsigned	bParado					:	1;
	unsigned	bSensorAtendido	:	1;
	unsigned	bPeriodoAlmacenado : 1;
	unsigned	bRecalcularVel	: 1;
	
	uint16_t	periodoMaxNuevoIman;	//Período máximo que se esperará por el paso de un nuevo imán
	uint16_t nuevoPeriodo;	//Almacena el último período 
	uint16_t periodos[CANT_PERIODOS];	//Arreglo de períodos entre imán e imán
	uint32_t sumatoria;	//Sumatoria del buffer de períodos
	uint16_t contador; //Contador de milisegundos
	uint8_t	 iProximoPeriodo;			//Indice del próximo periodo a ser almacenado
	float velocidad;	//Velocidad en m/seg
	uint8_t velStr[11];	//Cadena para la Velocidad	
};

struct SensVel{

	uint8_t  error;

	struct SensorDeVelocidad tractor;	//Sensor de velocidad del Tractor
	struct SensorDeVelocidad maquina;	//Sensor de velocidad del Tractor
		
	float eficiencia; //Eficiencia de tracción
	uint8_t eficienciaStr[11];	//Cadena para la Eficiencia de Tracción
};

struct CeldaDeCarga{

	unsigned bBufferCompleto 	:1;
	unsigned bRecalcularFuerza:1;
		
	OS_EVENT	*msgMuestraLista;	//Manejador del mensaje que significa que una nueva muestra ha sido leida y debe almacenarse en el buffer

	uint8_t  error;
	
	uint16_t nuevaFuerza;	//Almacena el último período 
	uint16_t fuerzas[CANT_MUESTRAS_FUERZA];	//Arreglo de fuerzas
	uint32_t sumatoria;	//Sumatoria del buffer de períodos
	uint8_t	 iProximaFuerza;	//Indice del próximo periodo a ser almacenado
	float fuerza;	//fuerza que realiza el tractor sobre  la máquina en N
	uint8_t fuerzaStr[11];	//Cadena para la Fuerza
	
	float potencia;	//
	uint8_t potenciaStr[11];	//Cadena para la Potencia
};
	
//Variables
extern struct GrupoDeParam param;
extern struct SensVel sV;
extern struct CeldaDeCarga celdaDeCarga;

#endif //SENSORES_H

