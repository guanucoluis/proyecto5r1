
//INCLUDES
#include <stdio.h>	
#include "sensores.h"

//DECLARACION DE VARIABLES
struct GrupoDeParam param;
struct SensVel sensVel;
struct CeldaDeCarga celdaDeCarga;

//Variables de GuardarParametros()
uint8_t iGP;	//Índice del for

//Variables de void InicSensores()
uint8_t iIS; 

//Variables de GuardarPeriodo()
uint8_t iGP;	//Índice del for

//Variables de CalcularVelocidades()
uint8_t iCV;	//Índice del for

//Variables de	CargarParametros()
uint8_t iCParam;	//Índice del for

volatile float FuerzaPromedio = 0;
volatile uint16_t *ptrBufferMuestras;
volatile unsigned long int SumatoriaFuerza;
volatile float Offset = 0;                            

/*Función InicSensores------------------------------------------------------------------------------------------------------------------------
Descripción: función que inicializa los sensores
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void InicSensores(void)
{
	param.iGdP = 0;

	//Inicializar Sensores de Velocidad
	CNEN2bits.CN25IE = 1;	//Habilitamos la interrupción del sensor1
	CNEN2bits.CN28IE = 1;	//Habilitamos la interrupción del sensor2
	CNPU2bits.CN25PUE = 0;	//Deshabilitamos el weak Pull-Up
	CNPU2bits.CN28PUE = 0;	//Deshabilitamos el weak Pull-Up
	TRISCbits.TRISC3 = 1;	//Seteamos como entrada
	TRISCbits.TRISC4 = 1;	//Seteamos como entrada
	//Inicializar Celda de Carga
	CNEN2bits.CN27IE = 1;	//Habilitamos la interrupción del ADC
	CNPU2bits.CN27PUE = 0;	//Deshabilitamos el weak Pull-Up
	TRISBbits.TRISB5 = 1;	//Seteamos como entrada

	IEC1bits.CNIE = 1;	//Habilitamos las interrupciones por "Change Notification (CN)"
	IPC4bits.CNIP = 0b0001;	//Seteamos la prioridad de interrupción como la más baja
	
	celdaDeCarga.iProximaFuerza = 0;
	for (iIS=0;iIS < CANT_MUESTRAS_FUERZA;iIS++)
		celdaDeCarga.fuerzas[iIS] = 0;
		
	adqui.contMuestreo = 0;
	
	sensVel.periodoMaxNuevoImanTrac	= 100;
	sensVel.periodoMaxNuevoImanMaq	= 100;

	sensVel.iProximoPerTrac = 0;
	sensVel.iProximoPerMaq = 0;

	sensVel.bTractorParado = 0;
	sensVel.bMaquinaParada = 0;
	sensVel.bSensorMaqAtendido = 0;
	sensVel.bSensorTracAtendido = 0;
	sensVel.bPeriodoTracAlmacenado = 1;
	sensVel.bPeriodoMaqAlmacenado = 1;
	sensVel.bRecalcularVelTrac = 0;
	sensVel.bRecalcularVelMaq = 0;
	sensVel.bBufferCompletoMaq = 0;
	sensVel.bBufferCompletoTrac = 0;

	sensVel.contTrac = 0;
	sensVel.contMaq = 0;
	
	for (iIS=0;iIS < CANT_PERIODOS_TRAC;iIS++)
		sensVel.periodosTrac[iIS] = 0;

	for (iIS=0;iIS < CANT_PERIODOS_MAQ;iIS++)
		sensVel.periodosMaq[iIS] = 0;
} //Fin InicSensores

/*Función CargarParametros------------------------------------------------------------------------------------------------------------------------
Descripción: función que actualiza el arreglo de parámetros según lo que lee desde la Flash
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void CargarParametros(void)
{
	//unsigned char iCParam;	//Índice del for
	#if (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
  CPU_SR        cpu_sr;
	#endif

	OS_ENTER_CRITICAL();

	//Indicamos la dirección del bloque de Flash
	config.rtsp.nvmAdru=__builtin_tblpage(&flashData);
	config.rtsp.nvmAdr=__builtin_tbloffset(&flashData);
	config.rtsp.nvmAdrPageAligned = config.rtsp.nvmAdr & 0xFC00;			// Get the Flash Page Aligned address
	config.rtsp.nvmRow=((config.rtsp.nvmAdr>>7) & 7);					// Row in the page	 				
	config.rtsp.nvmSize=64;

	flashPageRead(config.rtsp.nvmAdru, config.rtsp.nvmAdrPageAligned, buffFlash);	//Leemos el bloque de flash y lo almacenamos en buffFlash

	//Modificamos el arreglo con los cambios que queremos aplicar
	config.ptrStruct = (void *) (buffFlash + OFFSET_PARAMETROS);
	for (iCParam=0;iCParam < CANT_GRUP_PARAM; iCParam++)
	{
		//Actualizamos la estructura
		if (((struct GrupoDeParam *) config.ptrStruct)->diametros[iCParam].diametroTrac != 0xFFFF)
			param.diametros[iCParam].diametroTrac = ((struct GrupoDeParam *) config.ptrStruct)->diametros[iCParam].diametroTrac;
		else
			param.diametros[iCParam].diametroTrac = DIAMETRO_TRAC_DEFECTO;

		if (((struct GrupoDeParam *) config.ptrStruct)->diametros[iCParam].diametroNoTrac != 0xFFFF)
			param.diametros[iCParam].diametroNoTrac = ((struct GrupoDeParam *) config.ptrStruct)->diametros[iCParam].diametroNoTrac;
		else
			param.diametros[iCParam].diametroNoTrac = DIAMETRO_NO_TRAC_DEFECTO;
	}
	param.bParamCargadosDesdeFlash = 1;	//Indicamos que los  parametros  ya han sido cargados

	OS_EXIT_CRITICAL();
} //Fin CargarParametros()

/*Función GuardarParametros------------------------------------------------------------------------------------------------------------------------
Descripción: función que guarda el arreglo de parámetros en la Flash
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void GuardarParametros(void)
{
	//unsigned char iGP;	//Índice del for
	#if (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
  CPU_SR        cpu_sr;
	#endif

	OS_ENTER_CRITICAL();

	//Indicamos la dirección del bloque de Flash
	config.rtsp.nvmAdru=__builtin_tblpage(&flashData);
	config.rtsp.nvmAdr=__builtin_tbloffset(&flashData);
	config.rtsp.nvmAdrPageAligned = config.rtsp.nvmAdr & 0xFC00;			// Get the Flash Page Aligned address
	config.rtsp.nvmRow=((config.rtsp.nvmAdr>>7) & 7);					// Row in the page	 				
	config.rtsp.nvmSize=64;

	flashPageRead(config.rtsp.nvmAdru, config.rtsp.nvmAdrPageAligned, buffFlash);	//Leemos el bloque de flash y lo almacenamos en buffFlash

	//Modificamos el arreglo con los cambios que queremos aplicar
	config.ptrStruct = (void *) (buffFlash + OFFSET_PARAMETROS);
	for (iGP=0;iGP < CANT_GRUP_PARAM; iGP++)
	{
		//Actualizamos la estructura
		((struct GrupoDeParam *) config.ptrStruct)->diametros[iGP].diametroTrac = param.diametros[iGP].diametroTrac;
		((struct GrupoDeParam *) config.ptrStruct)->diametros[iGP].diametroNoTrac = param.diametros[iGP].diametroNoTrac;
	}

	flashPageErase(config.rtsp.nvmAdru, config.rtsp.nvmAdrPageAligned);	//Borramos  la página que queremos escribir
	flashPageWrite(config.rtsp.nvmAdru, config.rtsp.nvmAdrPageAligned, buffFlash);	//Escribimos la página en Flash con el buffer modificado 
		
	param.bParamCargadosDesdeFlash = 1;	//Indicamos que los  parametros  ya han sido cargados

	OS_EXIT_CRITICAL();
} //Fin GuardarParametros()

/*Función ISRCruceIman------------------------------------------------------------------------------------------------------------------------
Descripción: esta función se ejecuta cada vez que un imán cruza por cualquiera de los dos sensores
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ISRCruceIman(void)
{
	if (IFS1bits.CNIF == 1)	//¿Interrumpieron los sensores de velocidad?
	{
		IFS1bits.CNIF = 0;	//Reseteo por software del flag de interrupción
		if ((SENSOR_TRAC_IN == 0) && (sensVel.bSensorTracAtendido == 0))	//¿Interrumpió el sensor del Tractor?
		{
			if (sensVel.bTractorParado == 0)	//¿El tractor no está parado?	
				sensVel.nuevoPeriodoTrac = sensVel.contTrac;
			sensVel.contTrac = 0;	//Reseteamos el contador de mseg
			sensVel.bTractorParado = 0;
			sensVel.bSensorTracAtendido = 1;
			sensVel.bPeriodoTracAlmacenado = 0;
			OSMboxPost(sensVel.msgNuevoPeriodo, &sensVel.nuevoPeriodoTrac); //Enviamos un mensaje a la funcion que almacena la velocidad
		}
		else
		{
			if (SENSOR_TRAC_IN == 1)
				sensVel.bSensorTracAtendido = 0;
			Nop();
		}
		
		if ((SENSOR_MAQ_IN == 0) && (sensVel.bSensorMaqAtendido == 0))	//¿Interrumpió el sensor de la Máquina?
		{
			if (sensVel.bMaquinaParada == 0)	//¿La Máquina no está parada?	
				sensVel.nuevoPeriodoMaq = sensVel.contMaq;
			sensVel.contMaq = 0;	//Reseteamos el contador de mseg
			sensVel.bMaquinaParada = 0;
			sensVel.bSensorMaqAtendido = 1;
			sensVel.bPeriodoMaqAlmacenado = 0;
			OSMboxPost(sensVel.msgNuevoPeriodo, &sensVel.nuevoPeriodoMaq); //Enviamos un mensaje a la funcion que almacena la velocidad
		}
		else
		{
			if (SENSOR_MAQ_IN == 1)
				sensVel.bSensorMaqAtendido = 0;
			Nop();
		}
	}

} //Fin ISRCruceIman

/*Función GuardarPeriodo------------------------------------------------------------------------------------------------------------------------
Descripción: esta función se ejecuta cada vez que hay un nuevo periodo para guardar en el buffer
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void GuardarPeriodo(void)
{
	if ((sensVel.bPeriodoTracAlmacenado == 0) || 	(sensVel.bTractorParado == 1))
	{
		if (sensVel.bTractorParado == 1)
		{
				sensVel.nuevoPeriodoTrac = sensVel.periodoMaxNuevoImanTrac * 2;
				sensVel.periodoMaxNuevoImanTrac = sensVel.periodoMaxNuevoImanTrac + (uint16_t) ((float) sensVel.periodoMaxNuevoImanTrac * 0.5);
				if (sensVel.periodoMaxNuevoImanTrac > PERIODO_RUEDA_PARADA)
				{
					sensVel.periodoMaxNuevoImanTrac = PERIODO_RUEDA_PARADA;
					sensVel.nuevoPeriodoTrac = 65535;
				}
		}
		else
			sensVel.periodoMaxNuevoImanTrac = sensVel.nuevoPeriodoTrac + (uint16_t) ((float) sensVel.nuevoPeriodoTrac * 2);
		if ((sensVel.periodoMaxNuevoImanTrac >= PERIODO_RUEDA_PARADA) && (sensVel.bTractorParado == 0))
		{
			for (iGP=0;iGP < CANT_PERIODOS_TRAC;iGP++)
				sensVel.periodosTrac[iGP] = sensVel.nuevoPeriodoTrac;
		}
		else
			sensVel.periodosTrac[sensVel.iProximoPerTrac] = sensVel.nuevoPeriodoTrac;
			
		if (sensVel.iProximoPerTrac >= CANT_PERIODOS_TRAC)
		{
			sensVel.iProximoPerTrac = 0;
			sensVel.bBufferCompletoTrac = 1;
		}
		else
			sensVel.iProximoPerTrac++;
		sensVel.bTractorParado = 0;
		sensVel.bPeriodoTracAlmacenado = 1;
		sensVel.bRecalcularVelTrac = 1;
	}
	
	if ((sensVel.bPeriodoMaqAlmacenado == 0) || 	(sensVel.bMaquinaParada == 1))
	{
		if (sensVel.bMaquinaParada == 1)
		{
				sensVel.nuevoPeriodoMaq = sensVel.periodoMaxNuevoImanMaq * 2;
				sensVel.periodoMaxNuevoImanMaq = sensVel.periodoMaxNuevoImanMaq + (uint16_t) ((float) sensVel.periodoMaxNuevoImanMaq * 0.5);
				if (sensVel.periodoMaxNuevoImanMaq > PERIODO_RUEDA_PARADA)
				{
					sensVel.periodoMaxNuevoImanMaq = PERIODO_RUEDA_PARADA;
					sensVel.nuevoPeriodoMaq = 65535;
				}
		}
		else
			sensVel.periodoMaxNuevoImanMaq = sensVel.nuevoPeriodoMaq + (uint16_t) ((float) sensVel.nuevoPeriodoMaq * 2);
		if ((sensVel.periodoMaxNuevoImanMaq >= PERIODO_RUEDA_PARADA) && (sensVel.bMaquinaParada == 0))
		{
			for (iGP=0;iGP < CANT_PERIODOS_MAQ;iGP++)
				sensVel.periodosMaq[iGP] = sensVel.nuevoPeriodoMaq;
		}
		else
			sensVel.periodosMaq[sensVel.iProximoPerMaq] = sensVel.nuevoPeriodoMaq;
			
		if (sensVel.iProximoPerMaq >= CANT_PERIODOS_MAQ)
		{
			sensVel.iProximoPerMaq = 0;
			sensVel.bBufferCompletoMaq = 1;
		}
		else
			sensVel.iProximoPerMaq++;
		sensVel.bMaquinaParada = 0;
		sensVel.bPeriodoMaqAlmacenado = 1;
		sensVel.bRecalcularVelMaq = 1;
	}
}	//Fin GuardarPeriodo

/*Función CalcularVelocidades------------------------------------------------------------------------------------------------------------------------
Descripción: esta función calcula el promedio de períodos de cada sensor y luego su velocidad
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void CalcularVelocidades(void)
{
	if((sensVel.bRecalcularVelTrac == 1) && (sensVel.bBufferCompletoTrac == 1))
	{
		sensVel.sumatoriaTrac = 0;
		for(iCV=0;iCV < CANT_PERIODOS_TRAC;iCV++)
			sensVel.sumatoriaTrac = sensVel.sumatoriaTrac + sensVel.periodosTrac[iCV];
		sensVel.velocidadTrac = ((float) param.diametros[param.iGdP].diametroTrac * (float) PI_SOBRE_8 * (float) CAMBIO_UNIDAD) / ((float) sensVel.sumatoriaTrac / (float) CANT_PERIODOS_TRAC);
		sensVel.bRecalcularVelTrac = 0;
		
		fToStr.flotante = sensVel.velocidadTrac;
		FloatToString((char *) &(sensVel.velTracStr[0]), CINCO_CIFRAS_SIGNIF);
	}
	
	if((sensVel.bRecalcularVelMaq == 1) && (sensVel.bBufferCompletoMaq == 1))
	{
		sensVel.sumatoriaMaq = 0;
		for(iCV=0;iCV < CANT_PERIODOS_MAQ;iCV++)
			sensVel.sumatoriaMaq = sensVel.sumatoriaMaq + sensVel.periodosMaq[iCV];
		sensVel.velocidadMaq = ((float) param.diametros[param.iGdP].diametroNoTrac * (float) PI_SOBRE_8 * (float) CAMBIO_UNIDAD) / ((float) sensVel.sumatoriaMaq / (float) CANT_PERIODOS_MAQ);
		sensVel.bRecalcularVelMaq = 0;
		
		fToStr.flotante = sensVel.velocidadMaq;
		FloatToString((char *) &(sensVel.velMaqStr[0]), CINCO_CIFRAS_SIGNIF);
	}
} //Fin CalcularVelocidades

/*Función GuardarFuerza()-----------------------------------------------------------------------------------------------------------------------
Descripción: Esta función se encarga de almacenar la nueva muestra de fuerza en el buffer
Entrada: nada
Salida: nada
//------------------------------------------------------------------------------------------------------------------------*/	
void GuardarFuerza()
{
	LeerMuestraADC();	
	celdaDeCarga.fuerzas[celdaDeCarga.iProximaFuerza] = adc.valorTemp;
	
	if (celdaDeCarga.iProximaFuerza >= CANT_MUESTRAS_FUERZA)
	{
		celdaDeCarga.iProximaFuerza = 0;
		celdaDeCarga.bBufferCompleto = 1;
	}
	else
		celdaDeCarga.iProximaFuerza++;
		
	
}	//Fin GuardarFuerza()

/*Función CalcularFuerza()-----------------------------------------------------------------------------------------------------------------------
Descripción: Esta función se encarga de calcular el valor de fuerza en [N] partiendo de lo almacenado en el buffer
Entrada: nada
Salida: nada
//------------------------------------------------------------------------------------------------------------------------*/	
void CalcularFuerza()
{
	fToStr.flotante = celdaDeCarga.fuerza;
	FloatToString((char *) &(celdaDeCarga.fuerzaStr[0]), CINCO_CIFRAS_SIGNIF);
}	//Fin CalcularFuerza()

		