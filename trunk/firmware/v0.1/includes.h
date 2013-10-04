/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                                 (c) Copyright 2006, Micrium, Weston, FL
*                                           All Rights Reserved
*
*                                           MASTER INCLUDE FILE
*********************************************************************************************************
*/

#ifndef     INCLUDES_H
#define     INCLUDES_H

#include    <stdio.h>
#include    <string.h>
#include    <ctype.h>
#include    <stdlib.h>

#include    <p33FJ128GP804.h>

#include    <cpu.h>
#include    <ucos_ii.h>

#include    <lib_def.h>
#include    <lib_str.h>
#include    <lib_mem.h>

//#include    <bsp.h>
//#include    <lcd.h>
#include    <dsPIC_cfg.h>

#include <glcdK0108.h>
#include <interfaz_cfg.h>
#include <teclado.h>
#include <interfaz.h>
#include <sensores.h>

#if (uC_PROBE_OS_PLUGIN > 0)
#include  <os_probe.h>
#endif

#if (uC_PROBE_COM_MODULE > 0)
#include  <probe_com.h>

#if (PROBE_COM_METHOD_RS232 > 0)
#include  <probe_rs232.h>
#endif
#endif


#endif                                                                  /* End of File                                              */

