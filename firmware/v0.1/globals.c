#include "globals.h"

//VARIABLES GLOBALES
uint8_t err;

float TmpCnt;

OS_EVENT	*mBoxPromData;	//Manejador del MailBox que significa que un nuevo periodo ha sido leido y debe almacenarse en el buffer

//DIO variable
uint16_t ValChZero, CntData = 0;
float Prom = 0;
float *PtrPromFromMBox;
float PromFromMbox;
uint16_t whole = 0;
uint16_t decimal = 0;
char array[9];
float TmpCnt;
uint8_t iiTaskUart;