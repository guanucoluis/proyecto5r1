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

OS_STK  AppStartTaskStk[APP_TASK_START_STK_SIZE];
OS_STK  AppLCDTaskStk[APP_TASK_LCD_STK_SIZE];

OS_STK  NanoGUITaskStk[NANOGUI_TASK_STK_SIZE];
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
	
	//BSP_Init();                                                         /* Initialize BSP functions                                 */
	
	SD_CS_TRIS = 0;	
	SD_CS = 1;				//Chip Select de la SD
	TRIS_CS_PIN	=	0;	//Chip Select del ADC
	CS_ADC_PIN = 1;
	
	InicConfig();	//Inicializar estructura de Configuración
	GLCD_Init(NEGRO);	//Inicializa el GLCD
	InicInterfaz();	//Inicializar Interfaz
	IniTeclado();	//Inicializar Teclado
	
	//InicAdquisicion();	//Inicializar el módulo de Adquisición
	InicConversorAD();	//Inicializar ADC

  OSInit();                                                           /* Initialize "uC/OS-II, The Real-Time Kernel"              */

  OSTaskCreateExt(AppStartTask,
                    (void *)0,
                    (OS_STK *)&AppStartTaskStk[0],
                    APP_TASK_START_PRIO,
                    APP_TASK_START_PRIO,
                    (OS_STK *)&AppStartTaskStk[APP_TASK_START_STK_SIZE-1],
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

  while (DEF_TRUE) {                                                  /* Task body, always written as an infinite loop.           */
		Nop();
		Nop();
		//OSTimeDlyHMSM(0, 0, 0, 200);	
		OSTimeDly(10);
		///////////////////////////PRUEBA
		/*if (GLCD_E == 0)
			GLCD_E = 1;
		else
			GLCD_E = 0;*/
		///////////////////////////////////		
  }
}


/*
*********************************************************************************************************
*                                          LCD TASK
*
* Description : This example task writes messages to the Explorer16 LCD screen.
*
* Arguments   : p_arg   is the argument passed to 'AppStartTask()' by 'OSTaskCreate()'.
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*               2) Interrupts are enabled once the task start because the I-bit of the CCR register was
*                  set to 0 by 'OSTaskCreate()'.
*********************************************************************************************************
*/

static  void  AppLCDTask (void *p_arg)
{

	while (DEF_TRUE)                                           // All tasks bodies include an infinite loop.  
	{
		Nop();
		Nop();
		//OSTimeDlyHMSM(0, 0, 0, 100);
		OSTimeDly(10);
		///////////////////////////PRUEBA
		/*if (GLCD_E == 0)
			GLCD_E = 1;
		else
			GLCD_E = 0;*/
		///////////////////////////////////	
	}
}


/*
*********************************************************************************************************
*                                          NanoGUI TASK
*
* Description : Tarea de Interfaz
*
* Arguments   : p_arg   is the argument passed to 'AppStartTask()' by 'OSTaskCreate()'.
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*               2) Interrupts are enabled once the task start because the I-bit of the CCR register was
*                  set to 0 by 'OSTaskCreate()'.
*********************************************************************************************************
*/

static  void  NanoGUITask (void)
{

	while(1)
	{
		//Realizamos  el Chequeo de la SD
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


    OSTaskCreateExt(AppLCDTask,
                    (void *)0,
                    (OS_STK *)&AppLCDTaskStk[0],
                    APP_TASK_LCD_PRIO,
                    APP_TASK_LCD_PRIO,
                    (OS_STK *)&AppLCDTaskStk[APP_TASK_LCD_STK_SIZE-1],
                    APP_TASK_LCD_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

	OSTaskCreateExt(NanoGUITask,
                    (void *)0,
                    (OS_STK *)&NanoGUITaskStk[0],
                    NANOGUI_TASK_PRIO,
                    NANOGUI_TASK_PRIO,
                    (OS_STK *)&NanoGUITaskStk[APP_TASK_LCD_STK_SIZE-1],
                    NANOGUI_TASK_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP);

OS_STK  NanoGUITaskStk[NANOGUI_TASK_STK_SIZE];

#if OS_TASK_NAME_SIZE > 11
    OSTaskNameSet(APP_TASK_LCD_PRIO, (CPU_INT08U *)"LCD Task", &err);
#endif
}


