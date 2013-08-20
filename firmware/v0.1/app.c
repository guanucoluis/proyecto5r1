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

OS_STK  appStartTaskStk[APP_TASK_START_STK_SIZE];
OS_STK  tareaGuardarEnSDStk[TAREA_GUARDAR_EN_SD_STK_SIZE];
OS_STK  tareaAdquisicionStk[TAREA_ADQUISICION_STK_SIZE];
OS_STK  tareaCeldaDeCargaStk[TAREA_CELDA_DE_CARGA_STK_SIZE];
OS_STK  tareaSensVelStk[TAREA_SENS_VEL_STK_SIZE];
OS_STK  tareaNanoGUIStk[TAREA_NANOGUI_STK_SIZE];
OS_STK  tareaRefrescoStk[TAREA_REFRESCO_STK_SIZE];

OS_STK_DATA StartTaskStkData;
OS_STK_DATA GuardarEnSDStkData;
OS_STK_DATA AdquisicionStkData;
OS_STK_DATA CeldaDeCargaStkData;
OS_STK_DATA SensVelStkData;
OS_STK_DATA NanoGUIStkData;
OS_STK_DATA RefrescoStkData;
uint8_t errorStkChk;

/*
*********************************************************************************************************
*                                            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  AppStartTask(void *p_arg);
static  void  AppLCDTask(void *p_arg);
static  void  AppTaskCreate(void);

static  void  NanoGUITask(void);

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
	SD_CS = 1;				//Chip Select de la SD
	TRIS_CS_PIN	=	0;	//Chip Select del ADC
	CS_ADC_PIN = 1;
	
	RCON = 0;
	
	InicConfig();	//Inicializar estructura de Configuración
	GLCD_Init(NEGRO);	//Inicializa el GLCD
		
  OSInit();                                                           /* Initialize "uC/OS-II, The Real-Time Kernel"              */

  OSTaskCreateExt(AppStartTask,
                    (void *)0,
                    (OS_STK *)&appStartTaskStk[0],
                    APP_TASK_START_PRIO,
                    APP_TASK_START_PRIO,
                    (OS_STK *)&appStartTaskStk[APP_TASK_START_STK_SIZE-1],
                    APP_TASK_START_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

#if OS_TASK_NAME_SIZE > 11
  OSTaskNameSet(APP_TASK_START_PRIO, (CPU_INT08U *)"Start Task", &err);
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
* Arguments   : p_arg   is the argument passed to 'AppStartTask()' by 'OSTaskCreate()'.
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*               2) Interrupts are enabled once the task start because the I-bit of the CCR register was
*                  set to 0 by 'OSTaskCreate()'.
*********************************************************************************************************
*/

static  void  AppStartTask (void *p_arg)
{
  CPU_INT08U  i;
  CPU_INT08U  j;

 (void)p_arg;
	BSP_Init();                                                         /* Initialize BSP functions                                 */

#if OS_TASK_STAT_EN > 0
  OSStatInit();                                                       /* Determine CPU capacity                                   */
#endif

  AppTaskCreate();                                                    /* Create additional user tasks                             */

	//Creamos un MailBox para indicar cuando hay un nuevo periodo de velocidad
	sensVel.msgNuevoPeriodo = OSMboxCreate((void *)0);	
	adqui.msgGuardarMuestra = OSMboxCreate((void *)0);
	
  while (DEF_TRUE) {                                                  /* Task body, always written as an infinite loop.           */
		Nop();
		//Chekeamos el tamaño de Stack de esta tarea	
		errorStkChk = OSTaskStkChk(APP_TASK_START_PRIO, &StartTaskStkData);
		Nop();
		OSTimeDly(10);	
  }
}

/*
*********************************************************************************************************
*                                   Tarea de Guardado en la Tarjeta SD
* Description : Tarea de almacenamiento de muestras en la Tarjeta SD
* Arguments   : 
* Notes       :                 
*********************************************************************************************************
*/
static  void  TareaGuardarEnSD(void)
{
		
	while (DEF_TRUE)                                           // All tasks bodies include an infinite loop.  
	{		
		//Chekeamos el tamaño de Stack de esta tarea
		errorStkChk = OSTaskStkChk(TAREA_GUARDAR_EN_SD_PRIO, &GuardarEnSDStkData);
		Nop();
		
		OSTimeDly(800);
	}
}	//Fin TareaGuardarEnSD()


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
	InicSD(); //Inicializar la Tarjeta SD
		
	while (DEF_TRUE)                                           // All tasks bodies include an infinite loop.  
	{		
		//Chekeamos el tamaño de Stack de esta tarea
		errorStkChk = OSTaskStkChk(TAREA_ADQUISICION_PRIO, &AdquisicionStkData);
		Nop();
		
		OSMboxPend(adqui.msgGuardarMuestra, PERIODO_MIN_ADQUI, &sensVel.error);
		
		if (adqui.bMuestreando == 1)
		{
			if ((sensVel.bRecalcularVelTrac == 1) || (sensVel.bRecalcularVelMaq == 1))
				CalcularVelocidades();
	
			if (celdaDeCarga.bRecalcularFuerza == 1) 
				CalcularFuerza();
				
			if ((adqui.bGuardarEnSD == 1) && (ensayo.bEnsayando == 1))
			{
				if (adqui.bGuardarMuestra == 1)
				{
					if (sd.bSDInic == 1)	//Está la SD presente e inicializada
					{
						adqui.bGuardandoEnSD = 1;	//Indicamos que vamos a guardar en la SD
						GuardarMuestra();
						adqui.bGuardandoEnSD = 0;	
					}
				}
			}
			TomarMuestra(); //Lanzamos una nueva muestra
		}
	}
}	//Fin TareaAdquisicion()

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
		
	while (DEF_TRUE)                                           // All tasks bodies include an infinite loop.  
	{		
		//Chekeamos el tamaño de Stack de esta tarea
		errorStkChk = OSTaskStkChk(TAREA_CELDA_DE_CARGA_PRIO, &CeldaDeCargaStkData);
		Nop();
		
		OSTimeDly(800);
	}
}	//Fin TareaCeldaDeCarga()

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

	while (DEF_TRUE)                                           // All tasks bodies include an infinite loop.  
	{
		//Chekeamos el tamaño de Stack de esta tarea
		errorStkChk = OSTaskStkChk(TAREA_SENS_VEL_PRIO, &SensVelStkData);
		Nop();
		
		OSMboxPend(sensVel.msgNuevoPeriodo, PERIODO_REFRESCO_SENS, &sensVel.error); //Esperamos a que llegue un nuevo dato
		
		GuardarPeriodo();
	}
}	//Fin TareaSensVel()

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

	while (DEF_TRUE)                                           // All tasks bodies include an infinite loop.  
	{
		//Chekeamos el tamaño de Stack de esta tarea
		errorStkChk = OSTaskStkChk(TAREA_REFRESCO_PRIO, &RefrescoStkData);
		Nop();
		
		//Actualizamos el valor de velocidad VT en la pantalla 
		vPSpinEdits[7].valor.word = (uint8_t) sensVel.velocidadTrac; //Parte entera de la velocidad en Km/h
		formMediciones.ptrObjetos[20].bRedibujar = 1;
		vPSpinEdits[9].valor.word = (uint8_t) (10 * (sensVel.velocidadTrac - (float) ((uint8_t) sensVel.velocidadTrac))); //Parte entera de la velocidad en Km/h
		formMediciones.ptrObjetos[23].bRedibujar = 1;
		
		//Actualizamos el valor de velocidad VNT en la pantalla 
		vPSpinEdits[8].valor.word = (uint8_t) sensVel.velocidadMaq; //Parte entera de la velocidad en Km/h
		formMediciones.ptrObjetos[21].bRedibujar = 1;
		vPSpinEdits[10].valor.word = (uint8_t) (10 * (sensVel.velocidadMaq - (float) ((uint8_t) sensVel.velocidadMaq))); //Parte entera de la velocidad en Km/h
		formMediciones.ptrObjetos[24].bRedibujar = 1;
		
		OSTimeDly(300);
	}
}	//Fin TareaSensVel()

/*
*********************************************************************************************************
*                                          Tarea NanoGUI
* Description : Tarea de Interfaz
* Arguments   : p_arg   is the argument passed to 'AppStartTask()' by 'OSTaskCreate()'.
* Notes       :
*********************************************************************************************************
*/
static  void  TareaNanoGUI (void)
{
	IniTeclado();	//Inicializar Teclado
	InicInterfaz();	//Inicializar Interfaz
	
	while(1)
	{
		//Chekeamos el tamaño de Stack de esta tarea
		errorStkChk = OSTaskStkChk(TAREA_NANOGUI_PRIO, &NanoGUIStkData);
		Nop();
		
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
	
}

/*
*********************************************************************************************************
*                              CREATE ADDITIONAL APPLICATION TASKS
*********************************************************************************************************
*/

static  void  AppTaskCreate (void)
{
  CPU_INT08U  err;
  
 	OSTaskCreateExt(TareaGuardarEnSD,
                   (void *)0,
                   (OS_STK *)&tareaGuardarEnSDStk[0],
                   TAREA_GUARDAR_EN_SD_PRIO,
                   TAREA_GUARDAR_EN_SD_PRIO,
                   (OS_STK *)&tareaGuardarEnSDStk[TAREA_GUARDAR_EN_SD_STK_SIZE-1],
                   TAREA_GUARDAR_EN_SD_STK_SIZE,
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

	OSTaskCreateExt(	TareaNanoGUI,
                  	(void *)0,
                    (OS_STK *)&tareaNanoGUIStk[0],
                    TAREA_NANOGUI_PRIO,
                    TAREA_NANOGUI_PRIO,
                    (OS_STK *)&tareaNanoGUIStk[TAREA_NANOGUI_STK_SIZE-1],
                    TAREA_NANOGUI_STK_SIZE,
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


