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

#define TAREA_INICIO_PRIO					0                       /* Lower numbers are of higher priority                     */
#define	TAREA_LUISTEST_PRIO				5
#define	TAREA_LUISTESTTWO_PRIO		6
#define	TAREA_LUISTESTTHREE_PRIO	7
#define	TAREA_LUISTESTFOUR_PRIO		8

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

#define  TAREA_INICIO_STK_SIZE				126
#define  TAREA_LUISTEST_STK_SIZE		  253
#define  TAREA_LUISTESTTWO_STK_SIZE		253
#define  TAREA_LUISTESTTHREE_STK_SIZE	253

#endif                                                                  /* End of file                                              */



