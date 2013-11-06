/*
*********************************************************************************************************
*                                                MeDEf
*                                         Medidor de Eficiencia
*
*                                     UTN - Facultad Regional Córdoba
*
* File : APP.C
* 
*********************************************************************************************************
*/

#include <includes.h>
#include <globals.h>
#include <interfaz.h>

/*
*********************************************************************************************************
*                                                CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                                VARIABLES
*********************************************************************************************************
*/

OS_STK  tareaInicioStk[TAREA_INICIO_STK_SIZE];
OS_STK  tareaSDStk[TAREA_SD_STK_SIZE];
OS_STK  tareaAdquisicionStk[TAREA_ADQUISICION_STK_SIZE];
OS_STK  tareaCeldaDeCargaStk[TAREA_CELDA_DE_CARGA_STK_SIZE];
OS_STK  tareaSensVelStk[TAREA_SENS_VEL_STK_SIZE];
OS_STK  tareaInterfazStk[TAREA_INTERFAZ_STK_SIZE];
OS_STK  tareaRefrescoStk[TAREA_REFRESCO_STK_SIZE];

OS_STK_DATA StartTaskStkData;
OS_STK_DATA SDStkData;
OS_STK_DATA AdquisicionStkData;
OS_STK_DATA CeldaDeCargaStkData;
OS_STK_DATA SensVelStkData;
OS_STK_DATA InterfazStkData;
OS_STK_DATA RefrescoStkData;
uint8_t errorStkChk;

/*
*********************************************************************************************************
*                                            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  TareaInicio(void *p_arg);
static  void  AppTaskCreate(void);

static  void  TareaSD(void);
static  void  TareaAdquisicion(void);
static  void  TareaCeldaDeCarga(void);
static  void  TareaSensVel(void);
static  void  InterfazTask(void);
static  void  TareaRefresco(void);

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.
* Arguments   : none
*********************************************************************************************************
*/

CPU_INT16S  main (void)
{
  CPU_INT08U  err;
	
  BSP_IntDisAll();                                                    /* Disable all interrupts until we are ready to accept them */
	
  SD_CS_TRIS = 0;
  SD_CS = 1;            //Chip Select de la SD
  TRIS_CS_PIN = 0;      //Chip Select del ADC
  CS_ADC_PIN = 1;
	
  RCON = 0;
	
  InicConfig();         //Inicializar estructura de Configuración
  GLCD_Init(NEGRO);     //Inicializa el GLCD
		
  OSInit();                                                           /* Initialize "uC/OS-II, The Real-Time Kernel"              */

  OSTaskCreateExt(TareaInicio,
                    (void *)0,
                    (OS_STK *)&tareaInicioStk[0],
                    TAREA_INICIO_PRIO,
                    TAREA_INICIO_PRIO,
                    (OS_STK *)&tareaInicioStk[TAREA_INICIO_STK_SIZE-1],
                    TAREA_INICIO_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

#if OS_TASK_NAME_SIZE > 11
  OSTaskNameSet(TAREA_INICIO_PRIO, (CPU_INT08U *)"Start Task", &err);
#endif

  OSStart();                                                          /* Start multitasking (i.e. give control to uC/OS-II)       */

	return (-1);                                                        /* Return an error - This line of code is unreachable       */
}


/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'TareaInicio()' by 'OSTaskCreate()'.
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*               2) Interrupts are enabled once the task start because the I-bit of the CCR register was
*                  set to 0 by 'OSTaskCreate()'.
*********************************************************************************************************
*/

static  void  TareaInicio (void *p_arg)
{
  CPU_INT08U  i;
  CPU_INT08U  j;

  (void)p_arg;
  BSP_Init();                                                         /* Initialize BSP functions                                 */

#if OS_TASK_STAT_EN > 0
  OSStatInit();                                                       /* Determine CPU capacity                                   */
#endif

  AppTaskCreate();                                                    /* Create additional user tasks                             */

  //Se crea un MailBox para indicar cuando hay un nuevo periodo de velocidad
  eventos.mBoxSensVel = OSMboxCreate((void *)0);
  //Se crean los semáforos
  eventos.semCelda = OSSemCreate((void *)0);
  eventos.semMuestra = OSSemCreate((void *)0);
  eventos.semGuardar = OSSemCreate((void *)0);
	
  while (DEF_TRUE) 
  {   /* Task body, always written as an infinite loop.           */
    //Chequeamos el tamaño de Stack de esta tarea
    //errorStkChk = OSTaskStkChk(TAREA_INICIO_PRIO, &StartTaskStkData);

    if (adqui.bMuestreando == 1)
      TomarMuestra(); //Lanzamos una nueva muestra
    OSTimeDly(PERIODO_MUESTREO);
  }
}//Fin TareaInicio ()

/*
*********************************************************************************************************
*                                   Tarea de Guardado en la Tarjeta SD
* Description : Tarea de almacenamiento de muestras en la Tarjeta SD
* Arguments   : 
* Notes       :                 
*********************************************************************************************************
*/
static  void  TareaSD(void)
{
	#if (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
  CPU_SR        cpu_sr;
  #endif
  
  static uint8_t error;
				  
	INT16U backUpSPISTAT_SD;	//Variables para salvar temporalmente el estado de este reg y luego restaurarlo
	INT16U backUpSPICON1_SD;	//Variables para salvar temporalmente el estado de este reg y luego restaurarlo

  //la tarea se auto suspende hasta que entre en Adquisición
  OSTaskSuspend(OS_PRIO_SELF); //se auto suspende

  while (DEF_TRUE)     // All tasks bodies include an infinite loop.
  {
    //Chequeamos el tamaño de Stack de esta tarea
    //errorStkChk = OSTaskStkChk(TAREA_SD_PRIO, &SDStkData);
    Nop();

    OSSemPend(eventos.semGuardar, PERIODO_CHEQUEO_SD, &error); //Esperamos a que termine la muestra
		
		if ((error == OS_TIMEOUT) && (ensayo.bTerminarEnsayo == 0))	//¿Ocurrió un timeout?
		{
			//Realizamos  el chequeo de la SD
			if (MDD_MediaDetect())	//¿La SD está presente?
			{
			  if (sd.bSDInic == 0)	//¿La SD no está inicializada?
					InicSD();	//Inicializamos la SD
			}
			else
			{
			  sd.bSDPresente = 0; //La SD NO se encuentra en el sócalo
			  sd.bSDInic = 0;	//La SD no ha podido ser inicializada
			}
			error = 0;
		}
		else
		{
			if ((ensayo.bEnsayando == 1) || (ensayo.bTerminarEnsayo == 1)) //¿Se está ejecutando un ensayo?
			{
				if (sd.pNewFile == NULL) //¿Todavía no se abrió el archivo?
				{
					OS_ENTER_CRITICAL();
				  OSSchedLock();
				  
					adqui.nroMuestra = 1;
					OpenNewMed();
					adqui.bGuardarEnSD = 1;
	
					OSSchedUnlock();
	  			OS_EXIT_CRITICAL();
					    	
				}
				
				if ((ensayo.bTerminarEnsayo == 1) && (sd.pNewFile != NULL)) //¿La SD se encuentra presente, inicializada y hay un archivo abierto?
				{
				  OS_ENTER_CRITICAL();
				  OSSchedLock();
	  
					FSfclose(sd.pNewFile); //Cierra el archivo
					sd.pNewFile = NULL;
					
					OSSchedUnlock();
	  			OS_EXIT_CRITICAL()
	  			
					adqui.bGuardarEnSD = 0;
					ensayo.bTerminarEnsayo = 0;
				}
				
				if (sd.pNewFile != NULL) //¿Hay un archivo abierto?
				{
					OS_ENTER_CRITICAL();
				  OSSchedLock();
				  
					adqui.bGuardandoEnSD = 1;	//Indicamos que vamos a guardar en la SD
					GuardarMuestra();
					adqui.bGuardandoEnSD = 0;
					
					OSSchedUnlock();
	  			OS_EXIT_CRITICAL()
				}
			}
		}
		
		SD_CS = 1;

	}
}//Fin TareaGuardarEnSD()


/*
*********************************************************************************************************
*                                   Tarea de Adquisicion de muestras
* Description : Tarea de adquisicion y almacenamiento de las muestras de velocidad y fuerza
* Arguments   : 
* Notes       :                 
*********************************************************************************************************
*/
static  void  TareaAdquisicion(void)
{
  InicConversorAD();	//Inicializar ADC
  InicAdquisicion();	//Inicializar el driver de adquisicion

  //la tarea se auto suspende hasta que entre en Adquisición
  OSTaskSuspend(OS_PRIO_SELF); //se auto suspende

  while (DEF_TRUE)                                           // All tasks bodies include an infinite loop.
  {
    //Chequeamos el tamaño de Stack de esta tarea
    //errorStkChk = OSTaskStkChk(TAREA_ADQUISICION_PRIO, &AdquisicionStkData);
    Nop();

    if (adqui.bMuestreando == 1)
    {
			OSSemPend(eventos.semMuestra, 0, &sV.error); //Esperamos a que termine la muestra

			if ((sV.tractor.bRecalcularVel == 1) || (sV.maquina.bRecalcularVel == 1))
			{
				CalcularVelocidades();
				CalcularEficiencia();
			}

			if (celdaDeCarga.bBufferCompleto == 1)
			{
				CalcularFuerza();
				celdaDeCarga.bBufferCompleto = 0;
			}

			if (ensayo.bEnsayando == 1)
				if (sd.bSDInic == 1)	//Está la SD presente e inicializada
				{
					if (((tiempo.hs >= ensayo.duracion.hs) && (tiempo.min >= ensayo.duracion.min)) && (ensayo.duracion.min != ENSAYO_SIN_DURACION))
					{
						TerminarEnsayo();
						MostrarMsg(MENSAJE_FIN_ENSAYO, "El ensayo ha finalizado.", MENSAJE_OK, 70, 0);
					}

					OSSemPost(eventos.semGuardar);	//Indicamos a la TareaSD que ya puede guardar la muestra
				}
		}
    else
      OSTimeDly(PERIODO_MUESTREO);
  }
}//Fin TareaAdquisicion()

/*
*********************************************************************************************************
*                                   Tarea Celda de Carga
* Description : Tarea que almacena las muestras de fuerza tomadas desde la Celda de Carga
* Arguments   : 
* Notes       :                 
*********************************************************************************************************
*/
static  void  TareaCeldaDeCarga(void)
{
  //la tarea se auto suspende hasta que entre en Adquisición
  OSTaskSuspend(OS_PRIO_SELF); //se auto suspende

  while (DEF_TRUE)  // All tasks bodies include an infinite loop.
  {
    //Chequeamos el tamaño de Stack de esta tarea
    //errorStkChk = OSTaskStkChk(TAREA_CELDA_DE_CARGA_PRIO, &CeldaDeCargaStkData);
    Nop();

    OSSemPend(eventos.semCelda, TIMEOUT_ADC, &sV.error); //Esperamos a que termine la muestra

		if (sV.error == OS_ERR_TIMEOUT)	//Ocurrio un error de Timeout porque el ADC no respondió
    	adc.valorTemp = 0;
    	
		GuardarFuerza();
		
    OSSemPost(eventos.semMuestra);	//Indicamos a la tarea Adquisición que ha llegado una nueva muestra al buffer
  }
}//Fin TareaCeldaDeCarga()

/*
*********************************************************************************************************
*                                   Tarea de los sensores de velocidad
* Description : Tarea de almacenamiento y cálculo de la información de los sensores de velocidad
* Arguments   : 
* Notes       :                 
*********************************************************************************************************
*/
static  void  TareaSensVel (void)
{
  InicSensores();	//Inicializar Sensores
  if (param.bParamCargadosDesdeFlash == 0)	//Todavía no fueron cargados los parámetros desde la Flash
    CargarParametros();	//Actualizamos el arreglo de Parámetros

  //la tarea se auto suspende hasta que entre en Adquisición
  OSTaskSuspend(OS_PRIO_SELF); //se auto suspende

  while (DEF_TRUE)                                           // All tasks bodies include an infinite loop.
  {
    //Chequeamos el tamaño de Stack de esta tarea
    //errorStkChk = OSTaskStkChk(TAREA_SENS_VEL_PRIO, &SensVelStkData);
    Nop();

    OSMboxPend(eventos.mBoxSensVel, PERIODO_REFRESCO_SENS, &sV.error); //Esperamos a que llegue un nuevo dato

    GuardarPeriodo();
  }
}//Fin TareaSensVel()

/*
*********************************************************************************************************
*                                   Tarea de Actualización de los valores en pantalla
* Description : Esta tarea se encarga de setea los valores de los objetos gráficos de velocidad, fuerza, etc.
* Arguments   : 
* Notes       :                
*********************************************************************************************************
*/
static  void  TareaRefresco(void)
{
  //la tarea se auto suspende hasta que entre en Adquisición
  OSTaskSuspend(OS_PRIO_SELF); //se auto suspende

  while (DEF_TRUE)  // All tasks bodies include an infinite loop.
  {
    //Chequeamos el tamaño de Stack de esta tarea
    //errorStkChk = OSTaskStkChk(TAREA_REFRESCO_PRIO, &RefrescoStkData);
    Nop();

    switch(pantallaActual)
    {
      case PANTALLA_MEDICIONES:
        //Actualizamos el valor de velocidad VT en la pantalla
        vPSpinEdits[7].valor.word = (uint8_t) sV.tractor.velocidad; //Parte entera de la velocidad en Km/h
        formMediciones.ptrObjetos[20].bRedibujar = 1;
        vPSpinEdits[9].valor.word = (uint8_t) (10 * (sV.tractor.velocidad - (float) ((uint8_t) sV.tractor.velocidad))); //Parte decimal de la velocidad en Km/h
        formMediciones.ptrObjetos[23].bRedibujar = 1;

        //Actualizamos el valor de velocidad VNT en la pantalla
        vPSpinEdits[8].valor.word = (uint8_t) sV.maquina.velocidad; //Parte entera de la velocidad en Km/h
        formMediciones.ptrObjetos[21].bRedibujar = 1;
        vPSpinEdits[10].valor.word = (uint8_t) (10 * (sV.maquina.velocidad - (float) ((uint8_t) sV.maquina.velocidad))); //Parte decimal de la velocidad en Km/h
        formMediciones.ptrObjetos[24].bRedibujar = 1;

				//Actualizamos el valor de la eficiencia
				vPSpinEdits[6].valor.word = (uint16_t) sV.eficiencia; //Eficiencia
        formMediciones.ptrObjetos[19].bRedibujar = 1;

        //Se actualiza el valor de la fuerza
        vPSpinEdits[5].valor.word = (uint16_t) celdaDeCarga.fuerza; //Fuerza en Kgf
        formMediciones.ptrObjetos[18].bRedibujar = 1;

				if (ensayo.bEnsayando == 1) //¿Se está realizando un ensayo?
				{
					vPSpinEdits[1].valor.word = tiempo.hs;
					formMediciones.ptrObjetos[14].bRedibujar = 1;
					vPSpinEdits[2].valor.word = tiempo.min;
					formMediciones.ptrObjetos[15].bRedibujar = 1;
					vPSpinEdits[3].valor.word = tiempo.seg;
					formMediciones.ptrObjetos[16].bRedibujar = 1;
				}
      break;
      case PANTALLA_TARAR:
				if(vPSpinEdits[13].valor.word != (uint16_t) celdaDeCarga.tara)//se comprueba que el valor de tara no sea el mismo que el anterior
				{
					vPSpinEdits[13].valor.word = (uint16_t) celdaDeCarga.tara; //se pasa el Fuerza en Kgf al valor del spinEdit
					formTarar.ptrObjetos[6].bRedibujar = 1;
				}

				//Se actualiza el valor de la Fuerza Actual
        vPSpinEdits[14].valor.word = (uint16_t) celdaDeCarga.fuerza; //se pasa el Fuerza en Kgf al valor del spinEdit
        formTarar.ptrObjetos[7].bRedibujar = 1;
      break;
		}

    OSTimeDly(300);
  }
}//Fin TareaSensVel()

/*
*********************************************************************************************************
*                                          Tarea Interfaz
* Description : Tarea de Interfaz
* Arguments   : p_arg   is the argument passed to 'TareaInicio()' by 'OSTaskCreate()'.
* Notes       :
*********************************************************************************************************
*/
static  void  TareaInterfaz (void)
{
  IniTeclado();   //Inicializar Teclado
  InicInterfaz(); //Inicializar Interfaz

  while(1)
  {
    //Chequeamos el tamaño de Stack de esta tarea
    //errorStkChk = OSTaskStkChk(TAREA_INTERFAZ_PRIO, &InterfazStkData);
    Nop();

    //Esperar x mseg
    if (pantallaActual == PANTALLA_PRESENTA)
      if(Contador1ms > MSEG_PANT_PRESENTA)
        CambiarPantalla(PANTALLA_INICIO);	//Setear Pantalla de Selección de Protocolo

    ProcesoTeclado();	//Proceso encargado de detectar teclas presionadas

    if (teclado.teclaPulsada != TECLA_NO_PRES || teclado.teclaSostenida != TECLA_NO_PRES) //¿Se presionó una tecla o se mantiene presionada una tecla?
      EventoTecla();

    ActualizarInterfaz();	//Proceso encargado de dibujar la interfaz

    if (config.bDuracionLuzFondo == 1)	//¿La duración de fondo está activada?
      if (config.contLuzFondo >= config.duracionLuzFondo)
        ApagarLuzFondo();	//Apagamos la Luz de Fondo

    OSTimeDly(10);
  }
}//Fin  TareaInterfaz()

/*
*********************************************************************************************************
*                              CREATE ADDITIONAL APPLICATION TASKS
*********************************************************************************************************
*/

static  void  AppTaskCreate (void)
{
  CPU_INT08U  err;
  
  OSTaskCreateExt(TareaSD,
             (void *)0,
             (OS_STK *)&tareaSDStk[0],
             TAREA_SD_PRIO,
             TAREA_SD_PRIO,
             (OS_STK *)&tareaSDStk[TAREA_SD_STK_SIZE-1],
             TAREA_SD_STK_SIZE,
             (void *)0,
             OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP);

  OSTaskCreateExt(TareaAdquisicion,
                  (void *)0,
             (OS_STK *)&tareaAdquisicionStk[0],
             TAREA_ADQUISICION_PRIO,
             TAREA_ADQUISICION_PRIO,
             (OS_STK *)&tareaAdquisicionStk[TAREA_ADQUISICION_STK_SIZE-1],
             TAREA_ADQUISICION_STK_SIZE,
             (void *)0,
             OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP);

  OSTaskCreateExt(TareaCeldaDeCarga,
              (void *)0,
              (OS_STK *)&tareaCeldaDeCargaStk[0],
              TAREA_CELDA_DE_CARGA_PRIO,
              TAREA_CELDA_DE_CARGA_PRIO,
              (OS_STK *)&tareaCeldaDeCargaStk[TAREA_CELDA_DE_CARGA_STK_SIZE-1],
              TAREA_CELDA_DE_CARGA_STK_SIZE,
              (void *)0,
              OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP);

  OSTaskCreateExt(TareaSensVel,
              (void *)0,
              (OS_STK *)&tareaSensVelStk[0],
              TAREA_SENS_VEL_PRIO,
              TAREA_SENS_VEL_PRIO,
              (OS_STK *)&tareaSensVelStk[TAREA_SENS_VEL_STK_SIZE-1],
              TAREA_SENS_VEL_STK_SIZE,
              (void *)0,
              OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP);

  OSTaskCreateExt(	TareaInterfaz,
                  (void *)0,
              (OS_STK *)&tareaInterfazStk[0],
              TAREA_INTERFAZ_PRIO,
              TAREA_INTERFAZ_PRIO,
              (OS_STK *)&tareaInterfazStk[TAREA_INTERFAZ_STK_SIZE-1],
              TAREA_INTERFAZ_STK_SIZE,
              (void *)0,
              OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP);

  OSTaskCreateExt(	TareaRefresco,
                  (void *)0,
              (OS_STK *)&tareaRefrescoStk[0],
              TAREA_REFRESCO_PRIO,
              TAREA_REFRESCO_PRIO,
              (OS_STK *)&tareaRefrescoStk[TAREA_REFRESCO_STK_SIZE-1],
              TAREA_REFRESCO_STK_SIZE,
              (void *)0,
              OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP);
}


