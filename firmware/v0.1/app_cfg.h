/*
*********************************************************************************************************
*                              uC/OS-II Application Configuration
*
*                       DO NOT DELETE THIS FILE, IT IS REQUIRED FOR OS_VER > 2.80
*
*                                   CHANGE SETTINGS ACCORDINGLY
*
*
* File : app_cfg.h
* By   : Eric Shufro
*********************************************************************************************************
*/

#ifndef  APP_CFG_H
#define  APP_CFG_H


/*
*********************************************************************************************************
*                                       INCLUDES
*********************************************************************************************************
*/

#include <lib_def.h>


/*
*********************************************************************************************************
*                                       ADDITIONAL uC/MODULE ENABLES
*********************************************************************************************************
*/

#define  LIB_STR_CFG_FP_EN                DEF_DISABLED


/*
*********************************************************************************************************
*                                       TASK PRIORITIES
*********************************************************************************************************
*/

#define  APP_TASK_START_PRIO	0                       /* Lower numbers are of higher priority                     */
#define  OS_TASK_TMR_PRIO			10

#define	TAREA_ADQUISICION_PRIO	8
#define	TAREA_SENS_VEL_PRIO			9
#define	TAREA_REFRESCO_PRIO			11
#define	TAREA_NANOGUI_PRIO			12

/*
*********************************************************************************************************
*                                       TASK STACK SIZES
*
* Notes :   1) Warming, setting a stack size too small may result in the OS crashing. It the OS crashes
*              within a deep nested function call, the stack size may be to blame. The current maximum
*              stack usage for each task may be checked by using uC/OS-View or the stack checking
*              features of uC/OS-II.
*********************************************************************************************************
*/

#define  APP_TASK_START_STK_SIZE		128

#define  TAREA_ADQUISICION_STK_SIZE	256
#define  TAREA_REFRESCO_STK_SIZE		256
#define  TAREA_NANOGUI_STK_SIZE			256
#define  TAREA_SENS_VEL_STK_SIZE		256
/*
*********************************************************************************************************
*                                          uC/LCD
*********************************************************************************************************
*/

#define  DISP_BUS_WIDTH                         8                       /* Data bus width: 4 or 8 bit                               */

#endif                                                                  /* End of file                                              */



