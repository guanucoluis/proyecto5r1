
#include "includes.h"

/*
*********************************************************************************************************
*                                               CONSTANTES
*********************************************************************************************************
*/

#define		TASK_STK_SIZE     512	/* Size of each task's stacks (# of WORDs)       */

#define CFG_H		1

/*
*********************************************************************************************************
*                                              VARIABLES
*********************************************************************************************************
*/

OS_STK           TaskStartStk[TASK_STK_SIZE];		/* Startup    task stack                         */
OS_STK           TaskTxStk[TASK_STK_SIZE];             	/* Task Tx    task stack                         */
OS_STK           TaskTimesStk[TASK_STK_SIZE];           /* Task Times task stack                         */
OS_STK           TaskRxStk[TASK_STK_SIZE];             	/* Task RX    task stack                         */

OS_EVENT *BorrarPantallaMbox;
OS_EVENT *BorrarPantallaKernelMbox;
OS_EVENT *ImpresionLineaMbox;
OS_EVENT *LecturaPuertoMbox;

OS_EVENT		*MedicionesListasSem;
OS_EVENT		*ImpresionesListasSem;
OS_EVENT		*TransmisionesListasSem;

/*******Variables globales*************/


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void	TaskStart (void *data);               /* Function prototypes of tasks                  */
void    Task_Rx (void *data);
void   	Task_Tx (void *data);
void   	Task_Times (void *data);

/*
*********************************************************************************************************
*                                                  MAIN
*********************************************************************************************************
*/

void main (void)
{
	PC_DispClrScr(DISP_FGND_WHITE);    /* Clear the screen                         */
	OSInit();                          /* Initialize uC/OS-II                      */
	PC_DOSSaveReturn();                /* Save environment to return to DOS        */
	PC_VectSet(uCOS, OSCtxSw);         /* Install uC/OS-II's context switch vector */
	PC_ElapsedInit();                  /* Initialized elapsed time measurement     */

	CommInit();
	//Crear los MailBoxes (Buzones)
	BorrarPantallaMbox = OSMboxCreate((void *)0);
	BorrarPantallaKernelMbox = OSMboxCreate((void *)0);
	ImpresionLineaMbox = OSMboxCreate((void *)0);
	LecturaPuertoMbox = OSMboxCreate((void *)0);

	//Crear los Semaphores (Buzones)
	MedicionesListasSem = OSSemCreate(0);
	ImpresionesListasSem = OSSemCreate(1);
	TransmisionesListasSem = OSSemCreate(1);

	OSTaskCreate(TaskStart, (void *)0, &TaskStartStk[TASK_STK_SIZE-1], 0);

	OSStart();                        /* Start multitasking                       */
}
/*
*********************************************************************************************************
*                                               STARTUP TASK
*********************************************************************************************************
*/

void  TaskStart (void *data)
{
	char   s[80];
	WORD key;

	data = data;                      /* Prevent compiler warning                 */

	PC_DispStr(25, 27, "<-PRESS 'ESC' TO QUIT->", DISP_FGND_WHITE + DISP_BLINK);
	PC_DispStr(16,  1, "Trabajo Final - uC/OS-II, The Real-Time Kernel", DISP_FGND_WHITE + DISP_BGND_RED + DISP_BLINK);

	OS_ENTER_CRITICAL();              /* Install uC/OS-II's clock tick ISR        */
	PC_VectSet(0x08, OSTickISR);
	PC_SetTickRate(OS_TICKS_PER_SEC); /* Reprogram tick rate                      */
	OS_EXIT_CRITICAL();
	OSStatInit();

       //OSTaskCreate(Task_Tx, (void *)0, &TaskTxStk[TASK_STK_SIZE-1], 6);
	OSTaskCreate(Task_Times, (void *)0, &TaskTimesStk[TASK_STK_SIZE-1], 7);
	OSTaskCreate(Task_Rx, (void *)0, &TaskRxStk[TASK_STK_SIZE-1], 8);


	for (;;)
	{
		PC_DispStr(16,  1, "Trabajo Final - uC/OS-II, The Real-Time Kernel", DISP_FGND_WHITE + DISP_BGND_RED + DISP_BLINK);
		PC_DispStr(25, 27, "<-PRESS 'ESC' TO QUIT->", DISP_FGND_WHITE + DISP_BLINK);
		if (PC_GetKey(&key)== TRUE)	/* See if key has been pressed              */
		{
			if (key == 0x1B)	/* Yes, see if it's the ESCAPE key          */
			{
				PC_DOSReturn();       /* Yes, return to DOS                       */
			}
		}
		OSTimeDlyHMSM(0, 0, 0, 200);          /* Espera 1 segundo */
	}
}

/*
*******************************************************
*                            TASK_RX
*******************************************************
*/
void Task_Rx (void *data)
{
	INT8U	error, errSem;
	INT8U	i, c;
	INT8U	periodo[7],s[3];
	int k=0,kk=0 ,kdata = 0;
	INT8U	FlagInicio = 0;

	data = data;

	CommCfgPort(COMM2,9600,8,COMM_PARITY_NONE,1);
	CommSetIntVect(COMM2);
	CommRxIntEn(COMM2);

	for(;;)
	{
		PC_DispStr(28, 8, " Periodo recibido: ", DISP_FGND_YELLOW + DISP_BGND_BLUE);
		PC_DispStr(28, 10, " Char recibidos: ", DISP_FGND_YELLOW);

		if(!CommIsEmpty(COMM2))
		{
			c = CommGetChar(COMM2,&error);
			if(error==COMM_NO_ERR)
			{
				switch(c)
				{
					case 58:
						FlagInicio = 1;
						break;
					case 10:
						kdata = 0;
						FlagInicio = 0;
						errSem = OSSemPost (TransmisionesListasSem);
						break;
					default:
						if(FlagInicio == 1)
						{
							k++;
							kdata++;
							sprintf(s, "%d", k);
							PC_DispStr(60, 10, s, DISP_FGND_YELLOW);
							sprintf(s, "%c", (char)c);
							PC_DispStr(60+kdata, 8, s, DISP_FGND_YELLOW);
						}
				}
			}
		}

		OSTimeDlyHMSM(0, 0, 0, 500);
	}
}
/*
*********************************************************************************************************
*                                               Task_Times
*                                  Medicion de tiempos de ejecucion
*********************************************************************************************************
*/

void  Task_Times(void *data)
{
	INT16U      TimeBorrarPantalla;                       /* Execution time (in uS)                                  */
	INT16U      TimeBorrarPantallaKernel;
	INT16U      TimeImpresionLinea;
	INT16U      TimeLecturaPuerto;
	INT8U	err;
	INT8U 	errSem;
	char 	s[40];
	data = data;

	for (;;)
	{
		OSSemPend(TransmisionesListasSem,0,&errSem);
		//Borrar la pantalla con clrscr()
		//PC_ElapsedStart();
		//clrscr();
		//TimeBorrarPantalla = PC_ElapsedStop();

		//err = OSMboxPost(BorrarPantallaMbox, (void *)&TimeBorrarPantalla);
		//borrar la pantalla con funcion propia del kernel
		//PC_ElapsedStart();
		//PC_DispClrScr(DISP_FGND_WHITE);
		//TimeBorrarPantallaKernel = PC_ElapsedStop();
		//err = OSMboxPost(BorrarPantallaKernelMbox, (void *)&TimeBorrarPantallaKernel);

		//sprintf ( s, "%5d", TimeBorrarPantalla );
		//PC_DispStr(60,20, s, DISP_FGND_YELLOW);
		//sprintf ( s, "%5d", TimeBorrarPantallaKernel );
		//PC_DispStr(60,21, s, DISP_FGND_YELLOW);

		//impresion de una linea en pantalla
		//PC_ElapsedStart();
		//PC_DispStr(20,  25, "Impresion de una linea en pantalla", DISP_FGND_BLUE + DISP_BGND_GREEN);
		//TimeImpresionLinea = PC_ElapsedStop();
		//sprintf ( s, "%5d", TimeImpresionLinea );
		//PC_DispStr(60,22, s, DISP_FGND_YELLOW);
		//err = OSMboxPost(ImpresionLineaMbox, (void *)&TimeImpresionLinea);

		//leer datos del puerto
		//PC_ElapsedStart();

		//TimeLecturaPuerto = PC_ElapsedStop();
		//sprintf ( s, "%5d", TimeLecturaPuerto );
		//PC_DispStr(60,23, s, DISP_FGND_YELLOW);
		//err = OSMboxPost(LecturaPuertoMbox, (void *)&TimeLecturaPuerto);

		//PC_DispStr(10,20,"Tiempo de borrado de pantalla con clrscr() [us]:" , DISP_FGND_WHITE);     /* Message received, process      */
		//PC_DispStr(10,21,"Tiempo de borrado de pantalla con kernel [us]:" , DISP_FGND_WHITE);     /* Message received, process      */
		//PC_DispStr(10,22,"Tiempo en imprimir l¡nea [us]:" , DISP_FGND_WHITE);     /* Message received, process      */
		//PC_DispStr(10,23,"Tiempo en leer puerto [us]:" , DISP_FGND_WHITE);     /* Message received, process      */

		//errSem = OSSemPost (MedicionesListasSem);

		OSTimeDlyHMSM(0, 0, 0, 200);      /* Espera 1 Segundo   */
	}
}


