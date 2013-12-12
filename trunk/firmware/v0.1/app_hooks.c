/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*                                      Application-Defined Task Hooks
*
*                                 (c) Copyright 2007; Micrium; Weston, FL
*                                           All Rights Reserved
*
* File    : APP_HOOKS.C
* By      : Fabiano Kovalski
*         : Eric Shufro
*********************************************************************************************************
*/

#include  <includes.h>

/*
*********************************************************************************************************
*                                          App_TaskCreateHook()
*
* Description: This function is called when a task is created.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being created.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/

#if (OS_APP_HOOKS_EN > 0)
void  App_TaskCreateHook (OS_TCB *ptcb)
{
#if (uC_PROBE_OS_PLUGIN > 0) && (OS_PROBE_HOOKS_EN > 0)
    OSProbe_TaskCreateHook(ptcb);
#else
    (void)ptcb;
#endif
}

/*
*********************************************************************************************************
*                                           App_TaskDelHook()
*
* Description: This function is called when a task is deleted.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being deleted.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/

void  App_TaskDelHook (OS_TCB *ptcb)
{
    (void)ptcb;
}

/*
*********************************************************************************************************
*                                             App_TaskIdleHook()
*
* Description: This function is called by the idle task.  This hook has been added to allow you to do  
*              such things as STOP the CPU to conserve power.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are enabled during this call.
*********************************************************************************************************
*/

#if OS_VERSION >= 251
void  App_TaskIdleHook (void)
{

}
#endif

/*
*********************************************************************************************************
*                                   App_TaskStatHook()
*
* Description: This function is called every second by uC/OS-II's statistics task.  This allows your 
*              application to add functionality to the statistics task.
*
* Returns    : none
*********************************************************************************************************
*/

void  App_TaskStatHook (void)
{
	
}

/*
*********************************************************************************************************
*                                           App_TaskSwHook()
*
* Description: This function is called when a task switch is performed.  This allows you to perform other
*              operations during a context switch.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are disabled during this call.
*              2) It is assumed that the global pointer 'OSTCBHighRdy' points to the TCB of the task that
*                 will be 'switched in' (i.e. the highest priority task) and, 'OSTCBCur' points to the 
*                 task being switched out (i.e. the preempted task).
*********************************************************************************************************
*/

#if OS_TASK_SW_HOOK_EN > 0
void  App_TaskSwHook (void)
{

}
#endif

/*
*********************************************************************************************************
*                                           App_TCBInitHook()
*
* Description: This function is called by OS_TCBInit() after setting up most of the TCB.
*
* Arguments  : ptcb    is a pointer to the TCB of the task being created.
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/

#if OS_VERSION >= 204
void  App_TCBInitHook (OS_TCB *ptcb)
{
    (void)ptcb;
}
#endif

/*
*********************************************************************************************************
*                                               App_TimeTickHook()
*
* Description: This function is called every tick.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/

#if OS_TIME_TICK_HOOK_EN > 0
void  App_TimeTickHook (void)
{
  //Este código se ejecuta cada 1 mseg

  //Actualización del timeout del ADS1147
  /*if (ADC.bMuestreando == 1)
  {
    if (ADC.timeout > 0)
      ADC.timeout--;
  }*/

  //Incrementar Contador Genérico de 1ms
  Contador1ms++;

  //Incrementar Contador de Titileo del Cursor de los objetos de interfaz cada 1 mseg
  contTitileo++;

  //Actualización de la estructura de tiempo
  tiempo.ms++;
  if (tiempo.ms >= 1000)	//¿Ya paso un segundo?
  {
    tiempo.ms = 0; //Reseteo el contador de milisegundos
    tiempo.seg++;
    config.contLuzFondo++;
    //adqui.bProcesarMuestra = 1;	//Indico que se debe guardar una nueva muestra
    if (tiempo.seg >= 60)	//¿Ya paso un minuto?
    {
      tiempo.seg = 0; //Reseteo el contador de segundos
      tiempo.min++;
      if (tiempo.min >= 60)	//¿Ya paso una hora?
      {
        tiempo.min = 0; //Reseteo el contador de minutos
        tiempo.hs++;		//El contador de horas se resetea solo al llegar a 256 + 1
      }
    }
  }

	

  /*adqui.contMuestreo++;
  if (adqui.contMuestreo >= PERIODO_MUESTREO)
  {
    adqui.contMuestreo = 0;
    adqui.bGuardarMuestra = 1;
    OSMboxPost(adqui.msgGuardarMuestra, 0);
  }*/

	//Actualización del tiempo de Muestreo
  /*adqui.contMuestreo++;
  if (adqui.contMuestreo >= adqui.periodoMuestreo)
  {
    adqui.contMuestreo = 0;
    adqui.bProcesarMuestra = 1;	//Indico que se debe procesar una nueva muestra
  }*/

  //Actualizar contadores de los sensores de velocidad
  if (pantallaActual == PANTALLA_MEDICIONES)
  {
		if(ensayo.bEnsayando == 1) //se inicio la medición?
		  if(tiempo.ms == 500 || tiempo.ms == 0) // parapadeo cada medio segundo
		  {
			  //se cambia el color para que parpadee
			  formMediciones.ptrObjetos[27].bColorNeg = !formMediciones.ptrObjetos[27].bColorNeg;
				formMediciones.ptrObjetos[27].bRedibujar = 1;	//Redibujar "Midiendo..."
			}
		
	  if (sV.tractor.contador >= sV.tractor.periodoMaxNuevoIman)
	  {
	    sV.tractor.contador = 0;
	    sV.tractor.bParado = 1;
	    //eventos.mBoxSensVel->OSEventPtr = 0;
	    /*if (eventos.mBoxSensVel != 0)	//¿El MailBox ya está inicializado?
	    	OSMboxPost(eventos.mBoxSensVel, (void *) &sV.tractor); //Enviamos un mensaje a la funcion que almacena los períodos
	  	*/
	  }
	  else
	    sV.tractor.contador++;
	
	  if (sV.maquina.contador >= sV.maquina.periodoMaxNuevoIman)
	  {
	    sV.maquina.contador = 0;
	    sV.maquina.bParado = 1;
	    //eventos.mBoxSensVel->OSEventPtr = 0;
	    /*if (eventos.mBoxSensVel != 0)	//¿El MailBox ya está inicializado?
	    	OSMboxPost(eventos.mBoxSensVel, (void *) &sV.maquina); //Enviamos un mensaje a la funcion que almacena los períodos
	 		*/
	  }
	  else
	    sV.maquina.contador++;
		
	}
	
  //sV.contPeriodoRefrescoSens++;

  //Actualización de la estructura de tiempo de los MsgBoxes
  if (c.msgBox.tipoMensaje == MENSAJE_POR_TIEMPO)
  {
    c.msgBox.tiempo.ms++;
    if (c.msgBox.tiempo.ms >= 1000)	//¿Ya paso un segundo?
    {
      c.msgBox.tiempo.ms = 0; //Reseteo el contador de milisegundos
      c.msgBox.tiempo.seg++;
      if (c.msgBox.tiempo.seg >= c.msgBox.segundos)
        c.msgBox.bCerrarMensaje = 1;
    }
  }

  //Incrementar Contador de Incrementos
  teclado.contIncremento++;
  if (teclado.contIncremento >= teclado.periodoIncremento)
  {
    teclado.contIncremento = 0;
    teclado.bHabIncremento = 1;
  }
}
#endif

#endif                                                                  /* End of OS_APP_HOOKS_EN                                   */
