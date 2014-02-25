#include "SD.h"
#include "adquisicion.h"
#include "globals.h"
#include "FSIO.h"
#include <os_cpu.h>
#include <cpu.h>

//Variables generales del m�dulo de SD
struct SDCard sd;
char newFile[13];

//Variables de GetLastMed()
unsigned int iGLM;

//Variables de GuardarMuestra()
char cadenaMuestra[78];
#ifdef	IMPRIMIR_PARAM_PID
char cadenaAuxiliar[10];
#endif	//Fin IMPRIMIR_PARAM_PID	
unsigned char iGM;

//Variables de ImprimirEncabezado()
unsigned char iIE;

//Cadenas de encabezado

const char diamTrac[] = "Diametro de la rueda de tracci�n:	xxxx [um]";	
const char diamNoTrac[] = "Diametro de la rueda de NO tracci�n:	xxxx [um]";

const char titulos0[] = "N�   	hh:mm:ss	Fuerza[N]	VT[Km/h]	VNT[Km/h]	Eficiencia	Potencia";	//63 catacteres

//#ifdef SD_CARD

/*Funci�n GetLastMed------------------------------------------------------------------------------------------------------------------------
Descripci�n: funci�n que setea el valor de sd.numMedActual con la �ltima medici�n tomada
Entrada: nada
Salida: valor de la �ltima medici�n tomada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void GetLastMed(void)
{	
  #if (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
  CPU_SR        cpu_sr;
  #endif
  //unsigned int iGLM;

  //Escribimos el nombre del que ser�a el primer archivo
  adqui.numMedActual = 0;
  newFile[0] = 'M';
  newFile[1] = 'E';
  newFile[2] = 'D';
  newFile[3] = 'I';
  newFile[4] = '_';
  newFile[5] = '0';
  newFile[6] = '0';
  newFile[7] = '0';
  newFile[8] = '.';
  newFile[9] = 't';
  newFile[10] = 'x';
  newFile[11] = 't';
  newFile[12] = 0;	//NULL

  for(iGLM=0;iGLM<100;iGLM++)
  {
    OS_ENTER_CRITICAL();
    OSSchedLock();
    if (FindFirst(sd.newFile, ATTR_ARCHIVE, (SearchRec *) &cadenaMuestra[0]))	//�NO encontr� (distinto de cero) el archivo?
    {

    }
    else	//Encontr� el archivo (valor devuelto igual a cero)
    {
      adqui.numMedActual = iGLM;
    }
    OSSchedUnlock();
    OS_EXIT_CRITICAL();
    //Armamos el nombre del pr�ximo archivo
    BinBCD(iGLM + 1);
    newFile[5] = BCD[2]; //centenas
    newFile[6] = BCD[1]; //decenas
    newFile[7] = BCD[0]; //unidades
  }
} //Fin GetLastMed

/*Funci�n OpenNewMed------------------------------------------------------------------------------------------------------------------------
Descripci�n: funci�n que abre un nuevo archivo con un n�mero mayor (en una unidad) que la �ltima medici�n 
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void OpenNewMed(void)
{	
  //bytesWritten = FSfwrite ((void *) Cadena, 1, 11, pNewFile);
  //FSfwrite ((void *) Cadena, 1, 11, pNewFile);
  //FSfclose(pNewFile);

  //GetLastMed();
  //adqui.numMedActual++;	//Creamos una a continuaci�n

	adqui.numMedActual = vPSpinEdits[11].valor.word;

  //Armamos el nombre del nuevo archivo
  newFile[0] = 'M';
  newFile[1] = 'E';
  newFile[2] = 'D';
  newFile[3] = 'I';
  newFile[4] = '_';
  BinBCD(adqui.numMedActual);
  newFile[5] = BCD[2];
  newFile[6] = BCD[1];
  newFile[7] = BCD[0];
  newFile[8] = '.';
  newFile[9] = 't';
  newFile[10] = 'x';
  newFile[11] = 't';

	/*#if (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
  CPU_SR        cpu_sr;
  #endif
	
  OS_ENTER_CRITICAL();
  OSSchedLock();*/

  //Abrimos el nuevo archivo
  sd.pNewFile = FSfopen((const char *) sd.newFile,(const char *) &sd.mode);
  //Imprimimos el encabezado para dejarlo listo
  ImprimirEncabezado();

	/*OSSchedUnlock();
  OS_EXIT_CRITICAL();*/

} //Fin OpenNewMed

/*Funci�n InicSD------------------------------------------------------------------------------------------------------------------------
Descripci�n: funci�n que inicializa la tarjeta SD
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void InicSD(void)
{
  #if (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
  CPU_SR        cpu_sr;
  #endif

  OS_ENTER_CRITICAL();

  //if (SD_CARD_DETECT == 1)	//�La SD No est� presente?
          //return;

  RPINR20bits.SDI1R = 0b10001;	//SDI conectado al RP17-RC1
  RPOR8bits.RP16R = 0b00111;	//SDO conectado al RP16-RC0
  RPOR9bits.RP18R = 0b01000;	//SCK conectado al RP18-RC2

  SD_CS_TRIS = 0;
  SD_CD_TRIS = 1;
  SD_WE_TRIS = 1;
  SPICLOCK =	0;
  SPIIN = 1;
  SPIOUT = 0;

  //Setear puertos como digitales
  AD1PCFGLbits.PCFG6 = 1;	//RC0 - SDO
  AD1PCFGLbits.PCFG7 = 1;	//RC1 - SDI
  AD1PCFGLbits.PCFG8 = 1;	//RC2 - SCK

	//PARA INICIALIZAR LA SD, LA FRECUENCIA DEBE SER MENOR A 400 KHZ!!!!!!!!!!!!!
	//Por lo tanto, seteamos al principio la frecuencia m�s baja
  SPICON1bits.PPRE = PPRE_LENTO;	//Preescaler primario de 64
  SPICON1bits.SPRE = SPRE_LENTO;	//Preescaler secundario de 8

  sd.bSDInic = 0;	//La SD todav�a no est� inicializada
  //Detecci�n de la presencia de la SD
  if (MDD_MediaDetect())
  {
    sd.bSDPresente = 1;	//La SD se encuentra en el s�calo
    sd.bFrecuenciaRapida = 0;	//Hacemos esto para que la SD se inicialice con una frecuencia menor a 400 Khz
    if (FSInit())
    {
      sd.bSDInic = 1;	//La SD ha sido inicializada
      sd.bFrecuenciaRapida = 1;
    }
    else
      sd.bSDInic = 0;	//La SD no ha podido ser inicializada
  }
  else
    sd.bSDPresente = 0; //La SD NO se encuentra en el s�calo

  OS_EXIT_CRITICAL();

  sd.mode = 'w';
	//sd.mode = FS_WRITE;
	
  newFile[0] = 'M';
  newFile[1] = 'E';
  newFile[2] = 'D';
  newFile[3] = 'I';
  newFile[4] = '_';
  newFile[5] = '0';
  newFile[6] = '0';
  newFile[7] = '0';
  newFile[8] = '.';
  newFile[9] = 't';
  newFile[10] = 'x';
  newFile[11] = 't';

  sd.newFile = &newFile[0];

	sd.pNewFile = NULL;

  adqui.numMedActual = 0;	//Por defecto elegimos la primera medici�n
} //Fin InicSD

/*Funci�n ImprimirEncabezado------------------------------------------------------------------------------------------------------------------------
Descripci�n: funci�n que Imprime el encabezado del archivo
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ImprimirEncabezado(void)
{
  //unsigned char iIE;
	
  //Preparar la primera l�nea del encabezado
  for(iIE=0;iIE<63;iIE++)
          cadenaMuestra[iIE] = titulos0[iIE];
  cadenaMuestra[63] = '\n';	//Colocamos un enter
  //Escribimos la primera l�nea del encabezado
  FSfwrite ((const void *) cadenaMuestra, 1, 64, sd.pNewFile);
} //Fin ImprimirEncabezado

/*Funci�n GuardarMuestra------------------------------------------------------------------------------------------------------------------------
Descripci�n: funci�n que guarda en la SD una Muestra
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void GuardarMuestra(void)
{
	uint8_t error;
	
  /*#if (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
  CPU_SR        cpu_sr;
  #endif

  OS_ENTER_CRITICAL();
  OSSchedLock();*/

  //Preparar N�mero de muestra
  BinBCD(adqui.nroMuestra);
  cadenaMuestra[0] = BCD[4];
  cadenaMuestra[1] = BCD[3];
  cadenaMuestra[2] = BCD[2];
  cadenaMuestra[3] = BCD[1];
  cadenaMuestra[4] = BCD[0];
  cadenaMuestra[5] = 9;	//Insertamos tabulaci�n
  //cadenaMuestra[6] = NULL;
  //cadenaMuestra[7] = NULL;
  adqui.nroMuestra++;
  //Escribir N�mero de muestra
  error = FSfwrite ((void *) cadenaMuestra, 1, 6, sd.pNewFile);

  //Preparar tiempo
  sprintf((char *) cadenaMuestra,"%2u:%2u:%2u\t", tiempo.hs, tiempo.min, tiempo.seg);
  if (tiempo.hs <= 9)
          cadenaMuestra[0] = '0';
  if (tiempo.min <= 9)
          cadenaMuestra[3] = '0';
  if (tiempo.seg <= 9)
          cadenaMuestra[6] = '0';
  //Escribir tiempo
  FSfwrite ((void *) cadenaMuestra, 1, 9, sd.pNewFile);

  //Preparar Fuerza
  fToStr.flotante = celdaDeCarga.fuerza;
	FloatToString((char *) &(celdaDeCarga.fuerzaStr[0]), CINCO_CIFRAS_SIGNIF);
  FloatToScientific((char *) &(celdaDeCarga.fuerzaStr[0]), CINCO_CIFRAS_SIGNIF);
  sprintf((char *) cadenaMuestra,"%s\t", &celdaDeCarga.fuerzaStr[0]);
  //Escribir Fuerza
  FSfwrite ((void *) cadenaMuestra, 1, 11, sd.pNewFile);

  fToStr.flotante = sV.tractor.velocidad;
	FloatToString((char *) &(sV.tractor.velStr[0]), CINCO_CIFRAS_SIGNIF);
  //Preparar Velocidad de Tracci�n (VT)
  FloatToScientific((char *) &(sV.tractor.velStr[0]), CINCO_CIFRAS_SIGNIF);
  sprintf((char *) cadenaMuestra,"%s\t", &sV.tractor.velStr[0]);
  //Escribir Velocidad de Tracci�n (VT)
  FSfwrite ((void *) cadenaMuestra, 1, 11, sd.pNewFile);

  fToStr.flotante = sV.maquina.velocidad;
	FloatToString((char *) &(sV.maquina.velStr[0]), CINCO_CIFRAS_SIGNIF);
  //Preparar Velocidad de No Tracci�n (VNT)
  FloatToScientific((char *) &(sV.maquina.velStr[0]), CINCO_CIFRAS_SIGNIF);
  sprintf((char *) cadenaMuestra,"%s\t", &sV.maquina.velStr[0]);
  //Escribir Velocidad de No Tracci�n (VNT)
  FSfwrite ((void *) cadenaMuestra, 1, 11, sd.pNewFile);

  //Preparar Eficiencia
  fToStr.flotante = sV.eficiencia;
	FloatToString((char *) &(sV.eficienciaStr[0]), CINCO_CIFRAS_SIGNIF);
  FloatToScientific((char *) &(sV.eficienciaStr[0]), CINCO_CIFRAS_SIGNIF);
  sprintf((char *) cadenaMuestra,"%s\t", &sV.eficienciaStr[0]);
  //Escribir Eficiencia
  FSfwrite ((void *) cadenaMuestra, 1, 11, sd.pNewFile);

  //Preparar Potencia
  fToStr.flotante = celdaDeCarga.potencia;
	FloatToString((char *) &(celdaDeCarga.potenciaStr[0]), CINCO_CIFRAS_SIGNIF);
  FloatToScientific((char *) &(celdaDeCarga.potenciaStr[0]), CINCO_CIFRAS_SIGNIF);
  sprintf((char *) cadenaMuestra,"%s\n", &celdaDeCarga.potenciaStr[0]);
  //Escribir Potencia
  FSfwrite ((void *) cadenaMuestra, 1, 11, sd.pNewFile);
	
  /*OSSchedUnlock();
  OS_EXIT_CRITICAL();*/
		
} //Fin GuardarMuestra

//#endif SD_CARD

