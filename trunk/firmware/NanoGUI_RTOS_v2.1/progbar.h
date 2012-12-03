#ifndef  PROGBAR_H
#define PROGBAR_H

//INCLUDES
#include <interfaz.h>
//#include "globals.h"

#define	VERTICAL 1
#define	HORIZONTAL 0

#ifdef PROG_BAR
//Prototipos de ProgBar
void ProgBarActualizar(void);
void ProgBarOnKeyPress(void);
#endif //Fin PROG_BAR

#endif //end PROGBAR_H


