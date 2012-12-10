#include "SD.h"
#include "adquisicion.h"
#include "globals.h"
#include <FSIO.h>
#include <os_cpu.h>
#include <cpu.h>

//Variables generales del módulo de SD
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
const char composite[] = "Composite:	";	//11 caracteres
const char diametro[] = "Diametro:	xxxx [um]";	
const char espesor[] = "Espesor:	xxxx [um]";
#ifdef IMPRIMIR_PARAM_PID
	const char titulos0[] = "N°   	hh:mm:ss	T[°C]	SP[°C]    	R [Ohm]   	S [S/m]   	Potencia  	Salida PID";	//75 caracteres      	
	const char titulos1[] = "Error      	Error Acum 	Error Difer	Term. Prop 	Term. Integ	Term. Deriv";	//71 catacteres
	//const char titulos0[] = "N°   	hh:mm:ss	T[°C]	R [Ohm]   	S [S/m]   	Potencia  	Salida PID 	Error      ";	//77 caracteres      	
	//const char titulos1[] = "Error Acum 	Error Difer	Term. Prop 	Term. Integ	Term. Deriv";	//59 catacteres
#else
	const char titulos0[] = "N°   	hh:mm:ss	T[°C]	SP[°C]    	R [Ohm]   	S [S/m]   	Potencia";	//62 catacteres
	//const char titulos0[] = "N°   	hh:mm:ss	T[°C]	R [Ohm]   	S [S/m]   	Potencia";	//51 catacteres
#endif	//Fin IMPRIMIR_PARAM_PID
//const char titulos[] = "Muestra		hh:mm:ss	T [°C]		R [Ohm]		S [S/m]";

//#ifdef SD_CARD

/*Función GetLastMed------------------------------------------------------------------------------------------------------------------------
Descripción: función que setea el valor de sd.numMedActual con la última medición tomada
Entrada: nada
Salida: valor de la última medición tomada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void GetLastMed(void)
{	
	#if (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
  CPU_SR        cpu_sr;
	#endif
	//unsigned int iGLM;
	
	//Escribimos el nombre del que sería el primer archivo
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
	
	/*for(iGLM=0;iGLM<100;iGLM++)
	{
		OS_ENTER_CRITICAL();
		if (FindFirst(sd.newFile, ATTR_ARCHIVE, (void *) &cadenaMuestra[0]))	//¿NO encontró (distinto de cero) el archivo?
		{
			
		}	
		else	//Encontró el archivo (valor devuelto igual a cero)
		{
			adqui.numMedActual = iGLM;
		}
		OS_EXIT_CRITICAL();
		//Armamos el nombre del próximo archivo
		BinBCD(iGLM + 1);
		newFile[5] = BCD[2];
		newFile[6] = BCD[1];
		newFile[7] = BCD[0];
	}*/
} //Fin GetLastMed

/*Función OpenNewMed------------------------------------------------------------------------------------------------------------------------
Descripción: función que abre un nuevo archivo con un número mayor (en una unidad) que la última medición 
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void OpenNewMed(void)
{	
	//bytesWritten = FSfwrite ((void *) Cadena, 1, 11, pNewFile);
	//FSfwrite ((void *) Cadena, 1, 11, pNewFile);
	//FSfclose(pNewFile);
	
	GetLastMed();	//Determinamos cual fue la última medición
	adqui.numMedActual++;	//Creamos una a continuación
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
	//Abrimos el nuevo archivo
	sd.pNewFile = FSfopen((const char *) sd.newFile,(const char *) &sd.mode);
	//Imprimimos el encabezado para dejarlo listo
	ImprimirEncabezado();
	
	
} //Fin OpenNewMed

/*Función InicSD------------------------------------------------------------------------------------------------------------------------
Descripción: función que inicializa la tarjeta SD
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void InicSD(void)
{
	#if (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
  CPU_SR        cpu_sr;
	#endif

	OS_ENTER_CRITICAL();

	RPINR20bits.SDI1R = 0b10001;	//SDI conectado al RP17-RC1
	RPOR8bits.RP16R = 0b00111;	//SDO conectado al RP16-RC0
	RPOR9bits.RP18R = 0b01000;	//SDO conectado al RP18-RC2

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
	
	SPICON1bits.PPRE = 0b01;	//Preescaler primario de 64
	SPICON1bits.SPRE = 0b001;	//Preescaler secundario de 8
	
	sd.bSDInic = 0;	//La SD todavía no está inicializada
	//Detección de la presencia de la SD
	if (MDD_MediaDetect())
	{
		sd.bSDPresente = 1;	//La SD se encuentra en el sócalo
		if (iGLM = FSInit())
			sd.bSDInic = 1;	//La SD ha sido inicializada
		else
			sd.bSDInic = 0;	//La SD no ha podido ser inicializada
	}
	else
		sd.bSDPresente = 0; //La SD NO se encuentra en el sócalo
		
	OS_EXIT_CRITICAL();

	sd.mode = 'w';
	
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
	
	adqui.numMedActual = 0;	//Por defecto elegimos la primera medición
} //Fin InicSD

/*Función ImprimirEncabezado------------------------------------------------------------------------------------------------------------------------
Descripción: función que Imprime el encabezado del archivo
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ImprimirEncabezado(void)
{
	//unsigned char iIE;
	
	//Preparar primera línea del encabezado	
	sprintf((char *) cadenaMuestra,"%s ", composite);
	//cadenaMuestra[12] = conduc.iComposite + CERO_ASCII; //Colocamos el número de composite
	cadenaMuestra[12] = 4 + CERO_ASCII; //Colocamos el número de composite
	cadenaMuestra[13] = '\n'; //Colocamos un enter
	//Escribimos la primer línea del encabezado
	FSfwrite ((const void *) cadenaMuestra, 1, 14, sd.pNewFile);
	
	//Preparar la segunda línea del encabezado	
	sprintf((char *) cadenaMuestra,"%s\n", diametro);
	BinBCD(10);
	cadenaMuestra[10] = BCD[3];	//unidad de mil
	cadenaMuestra[11] = BCD[2];	//centena
	cadenaMuestra[12] = BCD[1];	//decena
	cadenaMuestra[13] = BCD[0];	//unidad
	//cadenaMuestra[20] = 0; //Colocamos NULL
	//Escribimos la segunda línea del encabezado
	FSfwrite ((const void *) cadenaMuestra, 1, 20, sd.pNewFile);

	//Preparar la tercer línea del encabezado	
	sprintf((char *) cadenaMuestra,"%s\n\n", espesor);
	BinBCD(7);
	cadenaMuestra[9] = BCD[3];	//unidad de mil
	cadenaMuestra[10] = BCD[2];	//centena
	cadenaMuestra[11] = BCD[1];	//decena
	cadenaMuestra[12] = BCD[0];	//unidad
	//cadenaMuestra[20] = 0; //Colocamos NULL
	//Escribimos la tercer línea del encabezado
	FSfwrite ((const void *) cadenaMuestra, 1, 20, sd.pNewFile);
	
	#ifdef IMPRIMIR_PARAM_PID	//¿Se deben imprimir los parámetros del PID?
	//Preparar la primera parte de la quinta línea del encabezado	
	for(iIE=0;iIE<75;iIE++)
		cadenaMuestra[iIE] = titulos0[iIE];
	cadenaMuestra[75] = 9;	//Colocamos una tabulación
	//Escribimos la primera parte de la quinta línea del encabezado
	FSfwrite ((const void *) cadenaMuestra, 1, 76, sd.pNewFile);

	//Preparar la segunda parte de la quinta línea del encabezado
	for(iIE=0;iIE<71;iIE++)
		cadenaMuestra[iIE] = titulos1[iIE];
	cadenaMuestra[71] = 10;	//Colocamos un enter (line feed)
	//Escribimos la segunda parte de la quinta línea del encabezado
	FSfwrite ((const void *) cadenaMuestra, 1, 72, sd.pNewFile);

	#else	//No se deben imprimir los parámetros del PID
	//Preparar la quinta línea del encabezado	
	//sprintf((char *) cadenaMuestra,"%s\n", titulos0);
	for(iIE=0;iIE<62;iIE++)
		cadenaMuestra[iIE] = titulos0[iIE];
	cadenaMuestra[62] = 10;	//Colocamos un enter (line feed)
	//Escribimos la quinta línea del encabezado
	FSfwrite ((const void *) cadenaMuestra, 1, 63, sd.pNewFile);
	#endif	//Fin IMPRIMIR_PARAM_PID
	

} //Fin ImprimirEncabezado

/*Función GuardarMuestra------------------------------------------------------------------------------------------------------------------------
Descripción: función que guarda en la SD una Muestra de valores tiempo-temperatura-conductividad-resistencia
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void GuardarMuestra(void)
{
	/*
	//Preparar Número de muestra
	BinBCD(adqui.nroMuestra);
	cadenaMuestra[0] = BCD[4];
	cadenaMuestra[1] = BCD[3];
	cadenaMuestra[2] = BCD[2];
	cadenaMuestra[3] = BCD[1];
	cadenaMuestra[4] = BCD[0];
	cadenaMuestra[5] = 9;	//Insertamos tabulación
	//cadenaMuestra[6] = NULL;
	//cadenaMuestra[7] = NULL;
	adqui.nroMuestra++;
	//Escribir Número de muestra
	FSfwrite ((void *) cadenaMuestra, 1, 6, sd.pNewFile);
	
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
	
	//Preparar temperatura
	FloatToScientific((char *) &(temp.temperaturaStr[0]));
	sprintf((char *) cadenaMuestra,"%s\t" 
					, &temp.temperaturaStr[0]);
	//Escribir temperatura
	FSfwrite ((void *) cadenaMuestra, 1, 6, sd.pNewFile);
	
	//Preparar SetPoint
	//if (controlTemp.setPoint >= 0)
		fToStr.flotante = controlTemp.setPoint;
	//else
		//fToStr.flotante = -controlTemp.setPoint;	//Hacemos esto porque FloatToString() no maneja negativos
	FloatToString((char *) &(cadenaAuxiliar[0]));
	FloatToScientific((char *) &(cadenaAuxiliar[0]));
	sprintf((char *) cadenaMuestra," %s\t"
					, &cadenaAuxiliar[0]);
	if (controlTemp.setPoint >= 0)
		cadenaMuestra[0] = '+';
	else
		cadenaMuestra[0] = '-';
	//Escribir el SetPoint
	FSfwrite ((void *) cadenaMuestra, 1, 12, sd.pNewFile);

	//Preparar Resistencia
	FloatToScientific((char *) &(conduc.resistenciaStr[0]));
	sprintf((char *) cadenaMuestra,"%s\t" 
					, &conduc.resistenciaStr[0]);
	//Escribir Resistencia
	FSfwrite ((void *) cadenaMuestra, 1, 11, sd.pNewFile);
	
	//Preparar Conductividad
	FloatToScientific((char *) &(conduc.conductividadStr[0]));
	sprintf((char *) cadenaMuestra,"%s\t" 
					, &conduc.conductividadStr[0]);
	//Escribir Conductividad
	FSfwrite ((void *) cadenaMuestra, 1, 11, sd.pNewFile);
	
	//Preparar Potencia
	//if (pot.potencia >= 0)
		fToStr.flotante = pot.potencia;
	//else
		//fToStr.flotante = -pot.potencia;
	FloatToString((char *) &(pot.potenciaStr[0]));
	FloatToScientific((char *) &(pot.potenciaStr[0]));
	#ifdef	IMPRIMIR_PARAM_PID
	sprintf((char *) cadenaMuestra,"%s\t"
					, &pot.potenciaStr[0]);
	#else
	sprintf((char *) cadenaMuestra,"%s\n"
					, &pot.potenciaStr[0]);
	#endif //Fin IMPRIMIR_PARAM_PID
	//Escribir Potencia
	FSfwrite ((void *) cadenaMuestra, 1, 11, sd.pNewFile);

	#ifdef	IMPRIMIR_PARAM_PID
	//Preparar Salida del PID
	//if (pid.salida >= 0)
		fToStr.flotante = pid.salida;
	//else
		//fToStr.flotante = -pid.salida;	//Hacemos esto porque FloatToString() no maneja negativos
	FloatToString((char *) &(cadenaAuxiliar[0]));
	FloatToScientific((char *) &(cadenaAuxiliar[0]));
	sprintf((char *) cadenaMuestra," %s\t"
					, &cadenaAuxiliar[0]);
	if (pid.salida >= 0)
		cadenaMuestra[0] = '+';
	else
		cadenaMuestra[0] = '-';
	//Escribir Salida del PID
	FSfwrite ((void *) cadenaMuestra, 1, 12, sd.pNewFile);

	//Preparar Error
	//if (pid.error >= 0)
		fToStr.flotante = pid.error;
	//else
		//fToStr.flotante = -pid.error;	//Hacemos esto porque FloatToString() no maneja negativos
	FloatToString((char *) &(cadenaAuxiliar[0]));
	FloatToScientific((char *) &(cadenaAuxiliar[0]));
	sprintf((char *) cadenaMuestra," %s\t"
					, &cadenaAuxiliar[0]);
	if (pid.error >= 0)
		cadenaMuestra[0] = '+';
	else
		cadenaMuestra[0] = '-';
	//Escribir Error
	FSfwrite ((void *) cadenaMuestra, 1, 12, sd.pNewFile);

	//Preparar ErrorAcum
	//if (pid.errorAcum >= 0)
		fToStr.flotante = pid.errorAcum;
	//else
		//fToStr.flotante = -pid.errorAcum;	//Hacemos esto porque FloatToString() no maneja negativos
	FloatToString((char *) &(cadenaAuxiliar[0]));
	FloatToScientific((char *) &(cadenaAuxiliar[0]));
	sprintf((char *) cadenaMuestra," %s\t"
					, &cadenaAuxiliar[0]);
	if (pid.errorAcum >= 0)	//¿El error acumulado es positivo?
		cadenaMuestra[0] = '+';
	else
		cadenaMuestra[0] = '-';
	//Escribir ErrorAcum
	FSfwrite ((void *) cadenaMuestra, 1, 12, sd.pNewFile);

	//Preparar ErrorDifer
	//if (pid.errorDifer >= 0)
		fToStr.flotante = pid.errorDifer;
	//else
		//fToStr.flotante = -pid.errorDifer;	//Hacemos esto porque FloatToString() no maneja negativos
	FloatToString((char *) &(cadenaAuxiliar[0]));
	FloatToScientific((char *) &(cadenaAuxiliar[0]));
	sprintf((char *) cadenaMuestra," %s\t"
					, &cadenaAuxiliar[0]);
	if (pid.errorDifer >= 0)	//¿El error diferencial es positivo?
		cadenaMuestra[0] = '+';
	else
		cadenaMuestra[0] = '-';
	//Escribir ErrorDifer
	FSfwrite ((void *) cadenaMuestra, 1, 12, sd.pNewFile);

	//Preparar Término Proporcional
	//if (pid.terminoProp >= 0)
  	fToStr.flotante = pid.terminoProp;
	//else
		//fToStr.flotante = -pid.terminoProp;	//Hacemos esto porque FloatToString() no maneja negativos
	FloatToString((char *) &(cadenaAuxiliar[0]));
	FloatToScientific((char *) &(cadenaAuxiliar[0]));
	sprintf((char *) cadenaMuestra," %s\t"
					, &cadenaAuxiliar[0]);
	if (pid.terminoProp >= 0)	//¿El Término Proporcional es positivo? El Term Prop tiene  el mismo signo del  error
		cadenaMuestra[0] = '+';
	else
		cadenaMuestra[0] = '-';
	//Escribir Término Proporcional
	FSfwrite ((void *) cadenaMuestra, 1, 12, sd.pNewFile);

	//Preparar Término Integral
	//if (pid.terminoInteg >= 0)
		fToStr.flotante = pid.terminoInteg;
	//else
		//fToStr.flotante = -pid.terminoInteg;	//Hacemos esto porque FloatToString() no maneja negativos
	FloatToString((char *) &(cadenaAuxiliar[0]));
	FloatToScientific((char *) &(cadenaAuxiliar[0]));
	sprintf((char *) cadenaMuestra," %s\t"
					, &cadenaAuxiliar[0]);
	if (pid.terminoInteg >= 0)
		cadenaMuestra[0] = '+';
	else
		cadenaMuestra[0] = '-';
	//Escribir Término Integral
	FSfwrite ((void *) cadenaMuestra, 1, 12, sd.pNewFile);

	//Preparar Término Derivativo
	//if (pid.terminoDeriv >= 0)
		fToStr.flotante = pid.terminoDeriv;
	//else
		//fToStr.flotante = -pid.terminoDeriv;	//Hacemos esto porque FloatToString() no maneja negativos
	FloatToString((char *) &(cadenaAuxiliar[0]));
	FloatToScientific((char *) &(cadenaAuxiliar[0]));
	sprintf((char *) cadenaMuestra," %s\n"
					, &cadenaAuxiliar[0]);
	if (pid.terminoDeriv >= 0)
		cadenaMuestra[0] = '+';
	else
		cadenaMuestra[0] = '-';
	//Escribir Término Derivativo
	FSfwrite ((void *) cadenaMuestra, 1, 12, sd.pNewFile);
	#endif	//fin IMPRIMIR_PARAM_PID	
	
	*/
} //Fin GuardarMuestra

//#endif SD_CARD

