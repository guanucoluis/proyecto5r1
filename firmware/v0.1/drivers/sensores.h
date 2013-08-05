#ifndef	SENSORES_H
#define SENSORES_H

#include <globals.h>
#include <ucos_ii.h>

#define	CANT_GRUP_PARAM	8

#define	DIAMETRO_TRAC_DEFECTO			180	//Valores en cent�metros
#define	DIAMETRO_NO_TRAC_DEFECTO	70	//Valores en cent�metros
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
#define CANT_PERIODOS_MAQ 30
#define CANT_PERIODOS_TRAC 30

struct Diametros{
	uint16_t	diametroTrac;		//Di�metro de la rueda de Tracci�n en cent�metros
	uint16_t	diametroNoTrac;	//Di�metro de la rueda de No Tracci�n	 en cent�metros
};

struct GrupoDeParam{
	unsigned bParamCargadosDesdeFlash	:1;	//Indica si los par�metros ya han sido cargados desde la Flash (1) o no (0)	

	uint8_t	iGdP;
	struct Diametros diametros[8];
};

struct SensVel{
	unsigned 	bBufferCompletoTrac	:	1;
	unsigned	bTractorParado			:	1;
	unsigned	bSensorTracAtendido	:	1;
	unsigned	bPeriodoTracAlmacenado : 1;
	unsigned	bRecalcularVelTrac	: 1;

	unsigned	bBufferCompletoMaq	:	1;
	unsigned	bMaquinaParada			:	1;
	unsigned	bSensorMaqAtendido	:	1;
	unsigned	bPeriodoMaqAlmacenado : 1;
	unsigned	bRecalcularVelMaq		: 1;

	OS_EVENT	*msgNuevoPeriodo;	//Manejador del mensaje que significa que un nuevo periodo ha sido leido y debe almacenarse en el buffer
	//uint16_t	NuevoPeriodo;			//Nuevo periodo ha sido leido y debe almacenarse en el buffer

	uint8_t  error;
	//uint16_t contPeriodoRefrescoSens;	//Contador para el per�odo  de refresco en pantalla de los sensores
	uint16_t	periodoMaxNuevoImanTrac;	//Per�odo m�ximo que se esperar� por el paso de un nuevo im�n
	uint16_t	periodoMaxNuevoImanMaq;	//Per�odo m�ximo que se esperar� por el paso de un nuevo im�n
	
	uint16_t nuevoPeriodoTrac;	//Almacena el �ltimo per�odo 
	uint16_t periodosTrac[CANT_PERIODOS_TRAC];	//Arreglo de per�odos entre im�n e im�n para el Tractor
	uint32_t sumatoriaTrac;	//Sumatoria del buffer de per�odos
	uint16_t contTrac; //Contador de milisegundos para el Tractor
	uint8_t	 iProximoPerTrac;			//Indice del pr�ximo periodo a ser almacenado
	float velocidadTrac;	//Velocidad del Tractor en m/seg
	uint8_t velTracStr[11];	//Cadena para la Velocidad de Tracci�n	

	uint16_t nuevoPeriodoMaq;	//Almacena el �ltimo per�odo
	uint16_t periodosMaq[CANT_PERIODOS_MAQ];	//Arreglo de per�odos entre im�n e im�n para la M�quina
	uint32_t sumatoriaMaq;	//Sumatoria del buffer de per�odos
	uint16_t contMaq;	//Contador de milisegundos para la M�quina
	uint8_t	 iProximoPerMaq;			//Indice del pr�ximo periodo a ser almacenado
	float velocidadMaq;	//Velocidad de la M�quina en m/seg
	uint8_t velMaqStr[11];	//Cadena para la Velocidad de la M�quina (Velocidad de No Tracci�n)
	
	float eficiencia; //Eficiencia de tracci�n
	uint8_t eficienciaStr[11];	//Cadena para la Eficiencia de Tracci�n
};

struct CeldaDeCarga{

	unsigned bBufferCompleto 	:1;
	unsigned bRecalcularFuerza:1;
		
	OS_EVENT	*msgMuestraLista;	//Manejador del mensaje que significa que una nueva muestra ha sido leida y debe almacenarse en el buffer

	uint8_t  error;
	
	uint16_t nuevaFuerza;	//Almacena el �ltimo per�odo 
	uint16_t fuerzas[CANT_MUESTRAS_FUERZA];	//Arreglo de fuerzas
	uint32_t sumatoria;	//Sumatoria del buffer de per�odos
	uint8_t	 iProximaFuerza;	//Indice del pr�ximo periodo a ser almacenado
	float fuerza;	//fuerza que realiza el tractor sobre  la m�quina en N
	uint8_t fuerzaStr[11];	//Cadena para la Fuerza
	
	float potencia;	//
	uint8_t potenciaStr[11];	//Cadena para la Potencia
};
	
//Variables
extern struct GrupoDeParam param;
extern struct SensVel sensVel;
extern struct CeldaDeCarga celdaDeCarga;

#endif //SENSORES_H

