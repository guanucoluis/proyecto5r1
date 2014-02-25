/*
*********************************************************************************************************
*                                         Luis Alberto Guanuco
*                                             Proyecto Final
*                                     Cátedra Software en Tiempo Real
*
*                                     UTN - Facultad Regional Córdoba
*
* File : APP.C
* 
*********************************************************************************************************
*/

#include <includes.h>
#include <globals.h>

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
OS_STK  tareaLuisTestStk[TAREA_LUISTEST_STK_SIZE];
OS_STK  tareaLuisTestTwoStk[TAREA_LUISTESTTWO_STK_SIZE];
OS_STK  tareaLuisTestThreeStk[TAREA_LUISTESTTHREE_STK_SIZE];
OS_STK  DIOTaskStk[DIO_TASK_STK_SIZE];

uint8_t errorStkChk;

/*
*********************************************************************************************************
*                                            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  TareaInicio(void *p_arg);
static  void  AppTaskCreate(void);
static  void  TareaLuisTest(void);
static  void  TareaLuisTestTwo(void);
static  void  TareaLuisTestThree(void);

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
	
  RCON = 0;
	
  OSInit();                                                           /* Initialize "uC/OS-II, The Real-Time Kernel"              */
	DIOInit();

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
  mBoxPromData= OSMboxCreate((void *) NULL);
  mBoxPromData->OSEventPtr = 0;

  while (DEF_TRUE) 
  {   /* Task body, always written as an infinite loop.           */
    //Chequeamos el tamaño de Stack de esta tarea
    //errorStkChk = OSTaskStkChk(TAREA_INICIO_PRIO, &tareaInicioStk);
    OSTimeDly(100);
  }
}//Fin TareaInicio ()

/*
*********************************************************************************************************
*                                          Tarea LuisTest
* Description : Tarea para testar el proyecto
* Arguments   : p_arg   is the argument passed to 'TareaInicio()' by 'OSTaskCreate()'.
* Notes       :
*********************************************************************************************************
*/
static  void  TareaLuisTest (void)
{
	
// Inicialización del módulo DIO
	
	DOCfgMode(0,DO_MODE_DIRECT,0);
	DICfgMode(0,DI_MODE_EDGE_HIGH_GOING);
	ValChZero = 0;
	CntData = 0;
	DIClr(0);
	
  while(1)
  {
		
		//Chequeamos el tamaño de Stack de esta tarea
    //errorStkChk = OSTaskStkChk(TAREA_LUISTEST_PRIO, &tareaLuisTestStk);
		DOSet(0,TRUE);
		OSTimeDlyHMSM(0,0,0,100);
		DOSet(0,FALSE);
		OSTimeDlyHMSM(0,0,1,0);
		
		ValChZero += DIGet(0);
		CntData++;
		DIClr(0);

		OSTimeDly(100);
  }
}//Fin  TareaLuisTest()

/*
*********************************************************************************************************
*                                          Tarea LuisTestTwo
* Description : Tarea para testar el proyecto
* Arguments   : p_arg   is the argument passed to 'TareaInicio()' by 'OSTaskCreate()'.
* Notes       :
*********************************************************************************************************
*/
static  void  TareaLuisTestTwo (void)
{
	TRISBbits.TRISB5 = 0;
  
	while(1)
  {
		//Chequeamos el tamaño de Stack de esta tarea
    //errorStkChk = OSTaskStkChk(TAREA_LUISTESTTWO_PRIO, &tareaLuisTestTwoStk);
		if(CntData!=0)
		{
			Prom = (float) ValChZero / (float) CntData;
			ValChZero = 0;
			CntData = 0;
		}
		else
			Prom = 0;
			
			
			
		OSMboxPost(mBoxPromData, &Prom); //Enviamos un mensaje a la funcion que transmite el dato (promedio de los pulsos recibidos
		OSTimeDlyHMSM(0,0,4,0);
  }
}//Fin  TareaLuisTest()

/*
*********************************************************************************************************
*                                          Tarea LuisTestThree
* Description : Tarea para testar el proyecto
* Arguments   : p_arg   is the argument passed to 'TareaInicio()' by 'OSTaskCreate()'.
* Notes       :
*********************************************************************************************************
*/
static  void  TareaLuisTestThree (void)
{
	uint8_t errorMboxPend;

	asm volatile ("mov #OSCCONL, w1  \n"
				  			"mov #0x46, w2     \n"
				  			"mov #0x57, w3     \n"
				  			"mov.b w2, [w1]    \n"
				  			"mov.b w3, [w1]    \n"
				  			"bclr OSCCON, #6");
				  

	RPINR18bits.U1RXR = 22;
	RPOR11bits.RP23R = 0b00011;
	
	asm volatile ("mov #OSCCONL, w1  \n"
				  			"mov #0x46, w2     \n"
				  			"mov #0x57, w3     \n"
				  			"mov.b w2, [w1]    \n"
				  			"mov.b w3, [w1]    \n"
				  			"bset OSCCON, #6");
	

	InitUART1();

  while(1)
  {
		//Chequeamos el tamaño de Stack de esta tarea
    //errorStkChk = OSTaskStkChk(TAREA_LUISTESTTHREE_PRIO, &tareaLuisTestThreeStk);

		PtrPromFromMBox = OSMboxPend(mBoxPromData, TIMEOUT_PEND_MBOX, &errorMboxPend); //Esperamos a que llegue un nuevo promedio
		PromFromMbox = *PtrPromFromMBox;
		whole=(int) PromFromMbox ; 										//obtains whole part 
		decimal=(int) ((PromFromMbox - (float) whole)*100.0); 	//obtains decimal part (1 digit)
		sprintf(array,":%04d.%02d\n",whole,decimal); 				//converts to string
		for(iiTaskUart = 0; iiTaskUart<9 ; iiTaskUart++)
		{
			while(U1STAbits.UTXBF != 0);
			U1TXREG = array[iiTaskUart];
		}
		
		OSTimeDlyHMSM(0,0,1,0);

  }
}//Fin  TareaLuisTest()


/*
*********************************************************************************************************
*                              CREATE ADDITIONAL APPLICATION TASKS
*********************************************************************************************************
*/

static  void  AppTaskCreate (void)
{
  CPU_INT08U  err;
  OSTaskCreateExt(TareaLuisTest,
              (void *)0,
              (OS_STK *)&tareaLuisTestStk[0],
              TAREA_LUISTEST_PRIO,
              TAREA_LUISTEST_PRIO,
              (OS_STK *)&tareaLuisTestStk[TAREA_LUISTEST_STK_SIZE-1],
              TAREA_LUISTEST_STK_SIZE,
              (void *)0,
              OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP);

	OSTaskCreateExt(TareaLuisTestTwo,
              (void *)0,
              (OS_STK *)&tareaLuisTestTwoStk[0],
              TAREA_LUISTESTTWO_PRIO,
              TAREA_LUISTESTTWO_PRIO,
              (OS_STK *)&tareaLuisTestTwoStk[TAREA_LUISTESTTWO_STK_SIZE-1],
              TAREA_LUISTESTTWO_STK_SIZE,
              (void *)0,
              OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP);

	OSTaskCreateExt(TareaLuisTestThree,
              (void *)0,
              (OS_STK *)&tareaLuisTestThreeStk[0],
              TAREA_LUISTESTTHREE_PRIO,
              TAREA_LUISTESTTHREE_PRIO,
              (OS_STK *)&tareaLuisTestThreeStk[TAREA_LUISTESTTHREE_STK_SIZE-1],
              TAREA_LUISTESTTHREE_STK_SIZE,
              (void *)0,
              OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP);

}


