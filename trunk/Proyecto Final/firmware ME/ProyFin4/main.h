#ifndef _MAIN_H
   #define _MAIN_H
   	    #include <p30fxxxx.h> /*El compilador se fija cual es el micro e incluye el header indicado */
        #include <stdio.h>
		#include "MDD File System\FSIO.h"
		#include "FSconfig.h"
		#include "HardwareProfile.h"

		
		
//#define MxBufferSize 120 // Tiene que ser menor que 255 por el tamaño de un banco.
#define MAX_BUFFER 100
#define TPO_TECLA	5     // 20mS  Hago el Barrido
#define TPO_TECLADO	2     // 50mS  Me fijo q tecla se presionó

struct banderas{
	unsigned teclado      :1;
	unsigned teclas	      :1;
	unsigned uart_write   :1;
	unsigned uart		  :1;
	unsigned disp_hora    :1;
	unsigned disp_menu    :1;
	unsigned disp_pulso   :1;
	unsigned disp_corazon :1;
	unsigned hora         :1;
	};

void isr_low(void);
void low_isr(void);

#endif
