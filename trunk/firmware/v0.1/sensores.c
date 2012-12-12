
//INCLUDES
#include <stdio.h>	
#include "sensores.h"

//DECLARACION DE VARIABLES

struct GrupoDeParam param;

//Variables de GuardarParametros()
unsigned char iGP;	//Índice del for

//Variables de	CargarParametros()
unsigned char iCParam;	//Índice del for

//valores para test
extern volatile float Vel_Prom_Trac;		
extern volatile float Vel_Prom_Maq;	

volatile unsigned char Radio_Tractor = 7;
volatile unsigned char Radio_Maquina = 7;
volatile unsigned char Var_Radio = 1;

//Variables relativas a la Fuerza
volatile unsigned char i_RCF;
volatile unsigned char i_ADCI;
volatile unsigned int i_Buffer_Muestras;
volatile unsigned int i_Buffer_Muestras_Aux;

volatile float FuerzaPromedio = 0;
volatile unsigned int *ptrBufferMuestras;
volatile unsigned long int SumatoriaFuerza;
volatile float Offset = 0;

//Variables de Procesos/Rutinas
extern struct VariablesDeProcesos Proc;

//volatile struct Med Mediciones[Cant_Max_Med];	//Inicializo la estructura Med.
extern volatile struct Sensores Band_Sensor;
                                     

/*Función InicSensores------------------------------------------------------------------------------------------------------------------------
Descripción: función que inicializa los sensores
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void InicSensores(void)
{
	param.iGdP = 0;
	
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


/*Función RutCalFuerza()-----------------------------------------------------------------------------------------------------------------------
Descripción: Rutina encargada de calcular el buffer de fuerza y la fuerza promedio
Entrada: nada
Salida: nada
//------------------------------------------------------------------------------------------------------------------------*/	
void RutCalFuerza()
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


		