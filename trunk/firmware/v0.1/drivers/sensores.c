
//INCLUDES
#include <stdio.h>	
#include "sensores.h"
#include "FlashMem_cfg.h"

//DECLARACION DE VARIABLES
struct GrupoDeParam param;
struct SensVel sV;
struct CeldaDeCarga celdaDeCarga;


volatile float FuerzaPromedio = 0;
//volatile uint16_t *ptrBufferMuestras;
//volatile unsigned long int SumatoriaFuerza;
volatile float Offset = 0;                            

/*Función InicSensores------------------------------------------------------------------------------------------------------------------------
Descripción: función que inicializa los sensores
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void InicSensores(void)
{	
  uint8_t iIS;
  
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

	//Se inicializa las variables de la celda de carga
  celdaDeCarga.iProximaFuerza = 0;
  for (iIS=0;iIS < CANT_MUESTRAS_FUERZA;iIS++)
    celdaDeCarga.fuerzas[iIS] = 0;
	celdaDeCarga.tara = 0;

  adqui.contMuestreo = 0;

	//Se inicializa las variables de los sensores de rapidez
  sV.tractor.periodoMaxNuevoIman = 100;
  sV.maquina.periodoMaxNuevoIman = 100;

  sV.tractor.iProximoPeriodo = 0;
  sV.maquina.iProximoPeriodo = 0;

  sV.tractor.bParado = 0;
  sV.tractor.bSensorAtendido = 0;
  sV.tractor.bPeriodoAlmacenado = 1;
  sV.tractor.bRecalcularVel = 0;
  sV.tractor.bBufferCompleto = 0;

  sV.maquina.bParado = 0;
  sV.maquina.bSensorAtendido = 0;
  sV.maquina.bPeriodoAlmacenado = 1;
  sV.maquina.bRecalcularVel = 0;
  sV.maquina.bBufferCompleto = 0;

  sV.tractor.contador = 0;
  sV.maquina.contador = 0;

  for (iIS=0;iIS < CANT_PERIODOS;iIS++)
  {
    sV.tractor.periodos[iIS] = 0; //se inicializa el vector de períodos de velocidad de tractor
    sV.maquina.periodos[iIS] = 0; //se inicializa el vector de períodos de velocidad de máquina
	}
} //Fin InicSensores

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
    if ((SENSOR_TRAC_IN == 0) && (sV.tractor.bSensorAtendido == 0))	//¿Interrumpió el sensor del Tractor?
    {
      if (sV.tractor.bParado == 0)	//¿El tractor no está parado?
        sV.tractor.nuevoPeriodo = sV.tractor.contador;
      sV.tractor.contador = 0;	//Reseteamos el contador de mseg
      sV.tractor.bParado = 0;
      sV.tractor.bSensorAtendido = 1;
      sV.tractor.bPeriodoAlmacenado = 0;
      //OSMboxPost(eventos.mBoxSensVel, &sV.tractor.nuevoPeriodo); //Enviamos un mensaje a la funcion que almacena la velocidad
    	OSMboxPost(eventos.mBoxSensVel, &sV.tractor); //Enviamos un mensaje a la funcion que almacena la velocidad
    }
    else
    {
      if (SENSOR_TRAC_IN == 1)
        sV.tractor.bSensorAtendido = 0;
      Nop();
    }

    if ((SENSOR_MAQ_IN == 0) && (sV.maquina.bSensorAtendido == 0))	//¿Interrumpió el sensor de la Máquina?
    {
      if (sV.maquina.bParado == 0)	//¿La Máquina no está parada?
        sV.maquina.nuevoPeriodo = sV.maquina.contador;
      sV.maquina.contador = 0;	//Reseteamos el contador de mseg
      sV.maquina.bParado = 0;
      sV.maquina.bSensorAtendido = 1;
      sV.maquina.bPeriodoAlmacenado = 0;
      //OSMboxPost(eventos.mBoxSensVel, &sV.maquina.nuevoPeriodo); //Enviamos un mensaje a la funcion que almacena la velocidad
      OSMboxPost(eventos.mBoxSensVel, &sV.maquina); //Enviamos un mensaje a la funcion que almacena la velocidad
    }
    else
    {
      if (SENSOR_MAQ_IN == 1)
        sV.maquina.bSensorAtendido = 0;
      Nop();
    }
  }

} //Fin ISRCruceIman

/*Función ActualizarEsperas------------------------------------------------------------------------------------------------------------------------
Descripción: esta función actualiza el período de espera máximo para cada sensor
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ActualizarEsperas(void)
{
	uint8_t iGP;	//Índice del for

  if (sV.tractor.bParado == 1)
  {
    sV.tractor.nuevoPeriodo = sV.tractor.periodoMaxNuevoIman * 2;
    sV.tractor.periodoMaxNuevoIman = sV.tractor.periodoMaxNuevoIman + (uint16_t) ((float) sV.tractor.periodoMaxNuevoIman * 0.5);
    if (sV.tractor.periodoMaxNuevoIman > PERIODO_RUEDA_PARADA)
    {
      sV.tractor.periodoMaxNuevoIman = PERIODO_RUEDA_PARADA;
      sV.tractor.nuevoPeriodo = 65535;
    }
  }
  else
    sV.tractor.periodoMaxNuevoIman = sV.tractor.nuevoPeriodo + (uint16_t) ((float) sV.tractor.nuevoPeriodo * 2);

 	if (sV.maquina.bParado == 1)
  {
    sV.maquina.nuevoPeriodo = sV.maquina.periodoMaxNuevoIman * 2;
    sV.maquina.periodoMaxNuevoIman = sV.maquina.periodoMaxNuevoIman + (uint16_t) ((float) sV.maquina.periodoMaxNuevoIman * 0.5);
    if (sV.maquina.periodoMaxNuevoIman > PERIODO_RUEDA_PARADA)
    {
      sV.maquina.periodoMaxNuevoIman = PERIODO_RUEDA_PARADA;
      sV.maquina.nuevoPeriodo = 65535;
    }
  }
  else
    sV.maquina.periodoMaxNuevoIman = sV.maquina.nuevoPeriodo + (uint16_t) ((float) sV.maquina.nuevoPeriodo * 2);
  
} //Fin ActualizarEsperas

/*Función GuardarPeriodo------------------------------------------------------------------------------------------------------------------------
Descripción: esta función se ejecuta cada vez que hay un nuevo periodo para guardar en el buffer
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void GuardarPeriodo(struct SensorDeVelocidad * senVel)
{
	uint8_t iGP;	//Índice del for
  //struct SensorDeVelocidad *senVel;
  
  //senVel = (struct SensorDeVelocidad *) eventos.mBoxSensVel->OSEventPtr;
  //senVel = msg;
  
  //if (eventos.mBoxSensVel->.OSTCBStat == OS_STAT_MBOX)  
  if (senVel->bPeriodoAlmacenado == 0)
  {
		if ((senVel->periodoMaxNuevoIman >= PERIODO_RUEDA_PARADA) && (senVel->bParado == 0))
		  for (iGP=0;iGP < CANT_PERIODOS;iGP++)
		    senVel->periodos[iGP] = senVel->nuevoPeriodo;
		else
		  senVel->periodos[senVel->iProximoPeriodo] = senVel->nuevoPeriodo;
		
		if (senVel->iProximoPeriodo >= CANT_PERIODOS)
		{
		  senVel->iProximoPeriodo = 0;
		  senVel->bBufferCompleto = 1;
		}
		else
		  senVel->iProximoPeriodo++;
		senVel->bParado = 0;
		senVel->bPeriodoAlmacenado = 1;
		senVel->bRecalcularVel = 1;
	}

}//Fin GuardarPeriodo

/*Función CalcularVelocidades------------------------------------------------------------------------------------------------------------------------
Descripción: esta función calcula el promedio de períodos de cada sensor y luego su velocidad
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void CalcularVelocidades(void)
{
	uint8_t iCV;	//Índice del for
	
  if((sV.tractor.bRecalcularVel == 1) && (sV.tractor.bBufferCompleto == 1))
  //if(sV.tractor.bBufferCompleto == 1)
  {
    sV.tractor.sumatoria = 0; //se inicializa la sumatoria
    for(iCV=0;iCV < CANT_PERIODOS;iCV++)
      sV.tractor.sumatoria += sV.tractor.periodos[iCV]; //se acumulan los períodos
    sV.tractor.velocidad = ((float) param.diametros[param.iGdP].diametroTrac * (float) PI_SOBRE_8 * (float) CAMBIO_UNIDAD) / ((float) sV.tractor.sumatoria / (float) CANT_PERIODOS);
		if (sV.tractor.velocidad < 0.1)
			sV.tractor.velocidad = 0;
		sV.tractor.bRecalcularVel = 0;
    //sV.tractor.bBufferCompleto = 0; //se reinicia el fubber

    fToStr.flotante = sV.tractor.velocidad; //se direcciona el puntero que va a ser usado por FLoatToString
    FloatToString((char *) &(sV.tractor.velStr[0]), CINCO_CIFRAS_SIGNIF); //se grafica
  }

  if((sV.maquina.bRecalcularVel == 1) && (sV.maquina.bBufferCompleto == 1))
  //if(sV.maquina.bBufferCompleto == 1)
  {
    sV.maquina.sumatoria = 0; //se inicializa la sumatoria
    for(iCV=0;iCV < CANT_PERIODOS;iCV++)
      sV.maquina.sumatoria += sV.maquina.periodos[iCV]; //se acumulan los períodos
    sV.maquina.velocidad = ((float) param.diametros[param.iGdP].diametroNoTrac * (float) PI_SOBRE_8 * (float) CAMBIO_UNIDAD) / ((float) sV.maquina.sumatoria / (float) CANT_PERIODOS);
    if (sV.maquina.velocidad < 0.1)
			sV.maquina.velocidad = 0;
		sV.maquina.bRecalcularVel = 0;
    //sV.maquina.bBufferCompleto = 0; //se reinicia el fubber

    fToStr.flotante = sV.maquina.velocidad; //se direcciona el puntero que va a ser usado por FLoatToString
    FloatToString((char *) &(sV.maquina.velStr[0]), CINCO_CIFRAS_SIGNIF); //se grafica
  }
} //Fin CalcularVelocidades

/*Función CalcularEficiencia()-----------------------------------------------------------------------------------------------------------------------
Descripción: Esta función se encarga de calcular el valor de eficiencia
Entrada: nada
Salida: nada
//------------------------------------------------------------------------------------------------------------------------*/
void CalcularEficiencia(void)
{
	sV.eficiencia = (sV.maquina.velocidad / sV.tractor.velocidad) * 100; //calculo de eficiencia en porcentaje
	if (sV.eficiencia > 100)
		sV.eficiencia = 100;
}//Fin CalcularEficiencia(void)

/*Función MuestraADCLista()-----------------------------------------------------------------------------------------------------------------------
Descripción: Esta función señaliza el semaforo semCelda para que TareaCeldaDeCarga guarde la muestra
Entrada: nada
Salida: nada
//------------------------------------------------------------------------------------------------------------------------*/	
void MuestraADCLista(void)
{
  OSSemPost(eventos.semCelda);	//Indicamos a la tarea TareaCeldaDeCarga que ha llegado una nueva muestra y debe ser almacenada en el buffer
}//Fin MuestraADCLista()

/*Función GuardarFuerza()-----------------------------------------------------------------------------------------------------------------------
Descripción: Esta función se encarga de almacenar la nueva muestra de fuerza en el buffer
Entrada: nada
Salida: nada
//------------------------------------------------------------------------------------------------------------------------*/	
void GuardarFuerza(void)
{
  LeerMuestraADC(); //Se lee y almacena la muestra en adc.valorTemp[1:0]
  celdaDeCarga.fuerzas[celdaDeCarga.iProximaFuerza] = adc.valorTemp; //se copia la muestra en el buffer(vector)

  if (celdaDeCarga.iProximaFuerza >= CANT_MUESTRAS_FUERZA) //¿es el final del buffer?
  {
    celdaDeCarga.iProximaFuerza = 0; //se inicializa el índice del buffer
    celdaDeCarga.bBufferCompleto = 1; //se avisa que el buffer está completo
  }
  else
    celdaDeCarga.iProximaFuerza++; //se incrementa el índice del buffer
}//Fin GuardarFuerza()

/*Función CalcularFuerza()-----------------------------------------------------------------------------------------------------------------------
Descripción: Esta función se encarga de calcular el valor de fuerza en [N] partiendo de lo almacenado en el buffer
Entrada: nada
Salida: nada
//------------------------------------------------------------------------------------------------------------------------*/	
void CalcularFuerza(void)
{
  uint8_t iCF;	//Índice del for
  
  if(celdaDeCarga.bBufferCompleto == 1)
  {
    celdaDeCarga.sumatoria = 0; //se inicializa la sumatoria
    for(iCF=0;iCF < CANT_MUESTRAS_FUERZA;iCF++)
      celdaDeCarga.sumatoria += celdaDeCarga.fuerzas[iCF]; //se acumulan las muestras de fuerza
    //celdaDeCarga.fuerza = ((float) param.diametros[param.iGdP].diametroNoTrac * (float) PI_SOBRE_8 * (float) CAMBIO_UNIDAD) / ((float) sV.maquina.sumatoria / (float) CANT_PERIODOS);
    
		
		celdaDeCarga.fuerza =(((float) celdaDeCarga.sumatoria / (float) CANT_MUESTRAS_FUERZA) * (float) KGF_SOBRE_BIT)
					 - (float) celdaDeCarga.tara; //se promedia las fuerzas, se convierte de bit a Kgf y se le quita el valor de tara
		if(celdaDeCarga.fuerza < 0)
			celdaDeCarga.fuerza = 0;

    celdaDeCarga.bBufferCompleto = 0; //se reinicia el fubber

		//se prepara el dato de fuerza para ser escrito en la SD
    fToStr.flotante = celdaDeCarga.fuerza; //se direcciona el puntero que va a ser usado por FLoatToString
    FloatToString((char *) &(celdaDeCarga.fuerzaStr[0]), CINCO_CIFRAS_SIGNIF); //se grafica
  }
}//Fin CalcularFuerza()

/*Función TararFuerza()-----------------------------------------------------------------------------------------------------------------------
Descripción: Esta función se encarga de calcular el valor de fuerza en [N] partiendo de lo almacenado en el buffer
Entrada: nada
Salida: nada
//------------------------------------------------------------------------------------------------------------------------*/
void TararFuerza(void)
{
	//(float) celdaDeCarga.sumatoria / (float) CANT_MUESTRAS_FUERZA);
	celdaDeCarga.tara = (uint16_t)(((float) celdaDeCarga.sumatoria / (float) CANT_MUESTRAS_FUERZA) * (float) KGF_SOBRE_BIT);
	//GuardarTarar();

}//Fin TararFuerza()



		