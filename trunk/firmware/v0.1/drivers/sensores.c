
//INCLUDES
#include <stdio.h>	
#include "sensores.h"

//DECLARACION DE VARIABLES
struct GrupoDeParam param;
struct SensVel sensVel;

//Variables de GuardarParametros()
uint8_t iGP;	//Índice del for

//Variables de void InicSensores()
uint8_t iIS; 

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
	IEC1bits.CNIE = 1;	//Habilitamos las interrupciones por "Change Notification (CN)"
	IPC4bits.CNIP = 0b0001;	//Seteamos la prioridad de interrupción como la más baja

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
			{
				sensVel.nuevoPeriodoTrac = sensVel.contTrac;
			}
			else
				sensVel.nuevoPeriodoTrac = PERIODO_MAX;
			OSMboxPost(sensVel.msgNuevoPeriodo, &sensVel.nuevoPeriodoTrac); //Enviamos un mensaje a la funcion que almacena y calcula la velocidad
			sensVel.contTrac = 0;	//Reseteamos el contador de mseg
			sensVel.bTractorParado = 0;
			sensVel.bSensorTracAtendido = 1;
			sensVel.bPeriodoTracAlmacenado = 0;
		}
		else 
		{
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
	if (sensVel.bPeriodoTracAlmacenado == 0)	//¿No se guardo el último periodo recibido?
	{
		sensVel.periodosTrac[sensVel.iProximoPerTrac] = sensVel.nuevoPeriodoTrac;
		if (sensVel.iProximoPerTrac >= CANT_PERIODOS_TRAC)
			sensVel.iProximoPerTrac = 0;
		else
			sensVel.iProximoPerTrac++;
		sensVel.bPeriodoTracAlmacenado = 1;
		sensVel.bRecalcularVelTrac = 1;
	}
}	//Fin GuardarPeriodo

/*Función CalcularVelocidades------------------------------------------------------------------------------------------------------------------------
Descripción: esta función calcula el promedio de períodos de cada sensor y luego su velocidad
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void CalcularVelocidades(void)
{
	if(sensVel.bRecalcularVelTrac == 1)
	{
		sensVel.sumatoriaTrac = 0;
		for(iCV=0;iCV < CANT_PERIODOS_TRAC;iCV++)
			sensVel.sumatoriaTrac = sensVel.sumatoriaTrac + sensVel.periodosTrac[iCV];
		sensVel.velocidadTrac = ((float) param.diametros[param.iGdP].diametroTrac * (float) PI_SOBRE_8 * (float) CAMBIO_UNIDAD) / ((float) sensVel.sumatoriaTrac / (float) CANT_PERIODOS_TRAC);
	}
} //Fin CalcularVelocidades

/*Función RutCalFuerza()-----------------------------------------------------------------------------------------------------------------------
Descripción: Rutina encargada de calcular el buffer de fuerza y la fuerza promedio
Entrada: nada
Salida: nada
//------------------------------------------------------------------------------------------------------------------------*/	
void CalcFuerza()
{

	/*//Calcular la Fuerza promedio
		SumatoriaFuerza = 0;
		if(i_Buffer_Muestras == 0)
			i_Buffer_Muestras_Aux = Tamanio_Buffer_Fuerza - Cant_Muest_Por_Int;
		else
			i_Buffer_Muestras_Aux = i_Buffer_Muestras - Cant_Muest_Por_Int;
		for(i_RCF=0;i_RCF<Cant_Muest_Por_Int;i_RCF++)
		{
			SumatoriaFuerza = SumatoriaFuerza + BufferMuestras[i_Buffer_Muestras_Aux];
			if (i_Buffer_Muestras_Aux >= Tamanio_Buffer_Fuerza)
				i_Buffer_Muestras_Aux = 0;
			else
				i_Buffer_Muestras_Aux++;
		}
	FuerzaPromedio = (float) ((float) SumatoriaFuerza / (float) Cant_Muest_Por_Int);
	FuerzaPromedio = (float) ((float) FuerzaPromedio * (float) Volts_Por_Bit * (float) Kgf_Por_Volt);
	FuerzaPromedio = FuerzaPromedio - Offset;*/

	////////////
	//FuerzaPromedio = (float) ((float) BufferMuestras[0] * (float) Volts_Por_Bit * (float) Kgf_Por_Volt);
	//FuerzaPromedio = FuerzaPromedio - Offset;
	////////////

}


		