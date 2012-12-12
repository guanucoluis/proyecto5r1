
#include "globals.h"
//#include "configinterfaz.h"

//VARIABLES GLOBALES

//Variables para la conversión de punto flotante a decimal y luego a string
struct FloatToStr fToStr;

//Variables de tiempo
struct Tiempo tiempo;

//Variables de Configuración
int8_t buffFlash[64*8];	//Buffer temporal para los datos leidos desde la Flash
struct ConfigdsPIC33 config;
int8_t flashData[TAMANIO_BLOQUE_BORRADO] __attribute__((space(prog),section("FlashData"),address(BLOQUE_FLASH))); 

//Variables de la función BinBCD()
unsigned char BCD[9];
signed char signo;
unsigned char iBBCD;

//Variables de la función FloatToString()
unsigned char iFTS;
unsigned char jFTS;
unsigned char kFTS;
float floatFTS;

//Variables de la función FloatToScientific()
unsigned char iFTSci;

//Variables de CargarFocos()
unsigned char iCF;

//Variables  del AD
//unsigned int Muestras[105];

//Variable Contadora Genérica
volatile unsigned int Contador1ms;

//Variables auxiliares
/*float e,f,g,h;
unsigned char dato1;*/
signed int offsetADC;
signed int gainADC;
/*unsigned char aux_a = 42;
unsigned char aux_b = 30;
signed int valor_aux;*/
unsigned int valor_aux1;
char iaux,jaux;

#pragma romdata eedata = 0xF00000 // Estos valores se pregraban en la EEPROM */
#pragma romdata

//DEFINICIÓN DE FUNCIONES GLOBALES
/*Función BinBCD------------------------------------------------------------------------------------------------------------------------
Descripción: Función que descompone un signed int en unidad, decena, centena, unidad de mil y decena de mil 
Entrada:
		valor: signed long int que se desea convertir a BCD
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void BinBCD(signed long int valor)
{
	//unsigned char iBBCD;

	//Reseteamos BCD
	for(iBBCD=0;iBBCD<9;iBBCD++)
		BCD[iBBCD] = CERO_ASCII;

	//Determinamos signo
	if (valor >= 0)
		signo = 1;
	else
	{
		signo = -1;
		valor = -valor;
	}
	//Centena de millón
	if (valor >= 100000000) 
		while(valor >= 100000000)
		{
			BCD[8]++;
			valor = valor - 100000000;
		}
	//Decena de millón
	if (valor >= 10000000) 
		while(valor >= 10000000)
		{
			BCD[7]++;
			valor = valor - 10000000;
		}
	//Unidad de millón
	if (valor >= 1000000) 
		while(valor >= 1000000)
		{
			BCD[6]++;
			valor = valor - 1000000;
		}
	//Centena de mil
	if (valor >= 100000) 
		while(valor >= 100000)
		{
			BCD[5]++;
			valor = valor - 100000;
		}
	//Decena de mil
	if (valor >= 10000) 
		while(valor >= 10000)
		{
			BCD[4]++;
			valor = valor - 10000;
		}
	//Unidad de mil
	if (valor >= 1000) 
		while(valor >= 1000)
		{
			BCD[3]++;
			valor = valor - 1000;
		}
	//Centena
	if (valor >= 100) 
		while(valor >= 100)
		{
			BCD[2]++;
			valor = valor - 100;
		}
	//Decena
	if (valor >= 10) 
		while(valor >= 10)
		{
			BCD[1]++;
			valor = valor - 10;
		}
	//Unidad
	if (valor >= 1) 
		while(valor >= 1)
		{
			BCD[0]++;
			valor = valor - 1;
		}
}// Fin BinBCD(signed int valor)

/*Función FloatToString------------------------------------------------------------------------------------------------------------------------
Descripción: Función que convierte un float a una cadena de caracteres 
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void FloatToString(char floatStr[], unsigned char formato)
{
	//unsigned char iFTS;
	//unsigned char jFTS;
	//unsigned char kFTS;
	//float floatFTS;
	
	//Como FloatToString() no trabaja con números negativos, si fToStr.flotante es negativo, le cambiamos el signo
	if	(fToStr.flotante < 0)
	 	fToStr.flotante = -fToStr.flotante;

	//Reseteamos la cadena a imprimir colocando todos espacios
	for(iFTS=0;iFTS<8;iFTS++)
		floatStr[iFTS] = ' ';
	floatStr[8] = 0;	//Colocamos NULL al final de la cadena
	
	floatFTS = fToStr.flotante;
	fToStr.expNeg = 0;
	if (((unsigned long int) floatFTS) < ((unsigned long int) 10000))	//¿La parte entera tiene 4 o menos cifras? 
	{
		if (floatFTS != 0)
		{
			while(((unsigned long int) floatFTS) < ((unsigned long int) 10000))
			{
				floatFTS = ((float) floatFTS) * ((float) 10); //Corremos la coma 1 lugar
				fToStr.expNeg++;
			}
		}
		else
			fToStr.expNeg++;	//Ponemos esto en uno para que no entre en la condición "fToStr.expNeg == 0" puesta más adelante
		//A esta altura, el número es si o si mayor que 10000, es decir, tiene 5 o más cifras enteras
		if (fToStr.expNeg >= 8)
		{
			floatStr[7] = 'u';
			fToStr.nroCifrasHastaComa = 11 - fToStr.expNeg;
		}
		else
		{
			if (fToStr.expNeg >= 5)
			{
				floatStr[7] = 'm';
				fToStr.nroCifrasHastaComa = 8 - fToStr.expNeg;
			}
			else
			{
				floatStr[7] = ' ';	//No lleva ningún multiplicador
				fToStr.nroCifrasHastaComa = 5 - fToStr.expNeg;
			}
		}
	}
	fToStr.parteEntera = (signed long int) floatFTS;
	if (fToStr.expNeg == 0)	//Si el número originalmente era mayor a 10000
	{
		//Calculamos el número de cifras de la parte entera
		fToStr.multi = 1;
		fToStr.nroCifrasEnteras = 1;	//Considero por defecto una cifra entera porque el número es mayor que 1
		if (fToStr.parteEntera != 0)
		{
			while(fToStr.parteEntera >= (fToStr.multi * 10))
			{
				fToStr.nroCifrasEnteras++;
				fToStr.multi = fToStr.multi * 10;
			}
		}
		//Calculamos el número de cifras antes de la coma
		if (fToStr.multi >= 1000000)	//El número es mayor que 1M
		{
			floatStr[7] = 'M';
			fToStr.nroCifrasHastaComa = fToStr.nroCifrasEnteras - 6;
		}
		else
		{
			if (fToStr.multi >= 1000)
			{
				floatStr[7] = 'K';
				fToStr.nroCifrasHastaComa = fToStr.nroCifrasEnteras - 3;
			}
			else
			{
				floatStr[7] = ' ';	//Ningún multiplicador
				fToStr.nroCifrasHastaComa = fToStr.nroCifrasEnteras;
			}	
		}
	}

	//Convertimos la parte entera a BCD
	BinBCD(fToStr.parteEntera);
	if (floatFTS != 0)
	{
		iFTS = 8;	//Nos ubicamos en la centena de millón
		while(BCD[iFTS] == CERO_ASCII)	//Salteamos los ceros a la izquierda de la parte entera convertida a BCD
		{
			if (iFTS > 0)
				iFTS--;
			else	//Seguimos hasta que terminamos la cadena
				break;
		}	  
	}
	else
	{
		iFTS = 4;
		fToStr.nroCifrasHastaComa = 1;
	}
	//Copiamos la parte entera en BCD a la cadena
	if (formato == MENOS_DE_CINCO_CIFRAS_SIGNIF)	//¿Se desea imprimir menos  de cinco cifras significativas?
	{
		if (fToStr.flotante >= 100)
		{
			kFTS=1;	//Imprimimos 4 cifras significativas
			floatStr[5] = NULL;	//Colocamos un NULL de fin de cadena
		}
		else
		{
			if (fToStr.flotante < 1)
			{
				kFTS=6;	//Hacemos esto para que no haga el bucle
				floatStr[0] = '0';
				floatStr[1] = '.';
				floatStr[2] = BCD[iFTS];
				floatStr[3] = ' ';
				floatStr[4] = ' ';	
				floatStr[5] = NULL;	//Colocamos un NULL de fin de cadena
				/*floatStr[6] = ' ';
				floatStr[7] = ' ';*/
			}
			else
			{
				if (fToStr.flotante < 10)
				{
					kFTS=3;	//Imprimimos 2 cifras significativas
					floatStr[3] = ' ';
					floatStr[4] = ' ';	
					floatStr[5] = NULL;	//Colocamos un NULL de fin de cadena
				}
				else
				{
					if (fToStr.flotante < 100)
					{
						kFTS=2;	//Imprimimos 3 cifras significativas
						floatStr[4] = ' ';
						floatStr[5] = NULL;	//Colocamos un NULL de fin de cadena
					}
					else
					{
						kFTS=1;	//Imprimimos 4 cifras significativas
						floatStr[5] = 0;	//Colocamos un NULL de fin de cadena
					}
				}	
			}
		}
	}
	else	//Se desea imprimir cinco cifras significativas
		kFTS=0;	//Imprimimos 5 cifras significativas
	for(jFTS=0;kFTS<6;jFTS++,kFTS++)
	{
		if (jFTS == fToStr.nroCifrasHastaComa)
			floatStr[jFTS] = '.';
		else
		{
			floatStr[jFTS] = BCD[iFTS];
			iFTS--;
		}
	}
				
}// Fin FloatToString()

/*Función FloatToScientific------------------------------------------------------------------------------------------------------------------------
Descripción: Función que formatea la cadena en temp y conduc a un  formato científico 
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void FloatToScientific(char floatStr[], unsigned char formato)
{
	if (formato == CINCO_CIFRAS_SIGNIF)	//¿Se desea imprimir cinco cifras significativas?
	{ 
		floatStr[6] = 'e';
		floatStr[8] = '0';
		switch(floatStr[7])
		{
			case 'u':
				floatStr[7] = '-';
				floatStr[9] = '6';
				floatStr[10] = NULL;
				break;
			case 'm':
				floatStr[7] = '-';
				floatStr[9] = '3';
				floatStr[10] = NULL;
				break;
			case ' ':
				floatStr[7] = '+';
				floatStr[9] = '0';
				floatStr[10] = NULL;
				break;
			case 'K':
				floatStr[7] = '+';
				floatStr[9] = '3';
				floatStr[10] = NULL;
				break;
			case 'M':
				floatStr[7] = '+';
				floatStr[9] = '6';
				floatStr[10] = NULL;
				break;
		}
	}
	//Buscamos y reemplazamos el punto por la coma
	for(iFTSci=0;iFTSci<9;iFTSci++)
	{
		if (floatStr[iFTSci] == '.')
			floatStr[iFTSci] = ',';
	}
}// Fin FloatToScientific()

/*Función SetPWMDutyCycle------------------------------------------------------------------------------------------------------------------------
Descripción: Función que setea el duty cycle del PWM de 10 bits
Entrada: 
	dutyCycle: Valor entre 0 y PR3 indicando el duty cycle al que se desea setear el PWM
	module: número del módulo al que se desea setearle el duty cycle
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetPWMDutyCycle(unsigned int dutyCycle, unsigned char module)
{
	switch (module)
	{
		case OC1:
			OC1RS = dutyCycle;
			break;
		case OC2:
			OC2RS = dutyCycle;
			break;
	}
}// Fin SetPWMDutyCycle(unsigned int dutyCycle)

/*Función InicConfig------------------------------------------------------------------------------------------------------------------------
Descripción: Función que inicializa la estructura de configuración del dispositivo
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void InicConfig(void)
{	
	//Configurar Encendido/Apagado
	/*TRIS_POWER_ON_OFF = 1;	//Seteamos el pin como entrada
	IE_POWER_ON_OFF	= 1; //Habilitamos la interrupción
	IF_POWER_ON_OFF	= 0;
	IP_POWER_ON_OFF	= 0; //Seteamos la interrupción como de prioridad baja
	EDGE_POWER_ON_OFF = 0; //Indicamos que la interrupción sea por flanco ascendente
	config.bDurmiendo = 0;*/
	
	//Configuración del timer3
	T3CONbits.TCKPS = 0;	//Prescaler = 0
	PR3 = 4000;
	T3CONbits.TON = 1;

	AD1PCFGLbits.PCFG5 = 1;	//RB3 - Contraste
	AD1PCFGLbits.PCFG4 = 1;	//RB2 - Backlight
	TRIS_GLCD_CONTRASTE = 0;
	TRIS_GLCD_BACKLIGHT	= 0;

	//Configurar PWM del contraste y del DutyCycle (Configuración del Output Compare)
	RPOR1bits.RP2R = 0b10010;	//RP2 conectado a Output Compare 1
	OC1CONbits.OCTSEL = 1;	//El clock del PWM es el Timer3
	OC1CONbits.OCM = 0b110;	//PWM mode on OCx, Fault pin disabled
	OC1RS = 3850;

	RPOR1bits.RP3R = 0b10011;	//RP3 conectado a Output Compare 2
	OC2CONbits.OCTSEL = 1;	//El clock del PWM es el Timer3
	OC2CONbits.OCM = 0b110;	//PWM mode on OCx, Fault pin disabled
	OC2RS = 3850;

	CargarConfigFlash();	//Cargamos la estructura de configuración con los datos de la Mem Flash

	//Setear contraste y Backlight
	SetLuzFondo();
	SetContraste();
}// Fin InicConfig()

/*Función GuardarFocos------------------------------------------------------------------------------------------------------------------------
Descripción: Función que almacena los focos de las pantallas en la Memoria Flash
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void GuardarFocos(void)
{
	/*config.address.u24 = BLOQUE_FLASH;	//Cargamos la dirección del bloque con el que queremos trabajar
	FlashBlockRead();	//Leemos el bloque de Flash completo
	//Modificamos el arreglo con los cambios que queremos aplicar
	config.ptrStruct = (void *) (gDataBuffer + OFFSET_FOCOS);
	*((unsigned char*) config.ptrStruct + 0) = formInicio.saveFoco;
	*((unsigned char*) config.ptrStruct + 1) = formEnsayo.saveFoco;
	*((unsigned char*) config.ptrStruct + 2) = formComposite.saveFoco;
	*((unsigned char*) config.ptrStruct + 3) = formEnsayoLibre.saveFoco;
	*((unsigned char*) config.ptrStruct + 4) = formProgramas.saveFoco;
	*((unsigned char*) config.ptrStruct + 5) = formConfig.saveFoco;
	*((unsigned char*) config.ptrStruct + 6) = formConfigEnsayo.saveFoco;
	//NOTA: Antes de realizar una escritura a la mem flash,  se debe borrar el bloque donde se desea escribir
	FlashBlockErase();	//Borramos el bloque de Flash completo
	FlashBlockWrite();	//Escribimos el bloque entero en la Mem Flash*/
}// Fin GuardarFocos()

/*Función CargarFocos------------------------------------------------------------------------------------------------------------------------
Descripción: Función que carga los focos de las pantallas desde la Memoria Flash
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void CargarFocos(void)
{
  //unsigned char iCF;

	/*config.address.u24 = BLOQUE_FLASH;	//Cargamos la dirección del bloque con el que queremos trabajar
	FlashBlockRead();	//Leemos el bloque de Flash completo
	//Cargamos los focos leídos desde la Memoria Flash
	config.ptrStruct = (void *) (gDataBuffer + OFFSET_FOCOS);
  for(iCF=0;iCF<NUM_PANTALLAS-1;iCF++)
    if (*((unsigned char*) config.ptrStruct + iCF) == 255)  //¿Los focos por algún motivo no están inicializados?
        *((unsigned char*) config.ptrStruct + iCF) = 0; //Los inicializamos  a cero por defecto
	formInicio.saveFoco = *((unsigned char*) config.ptrStruct + 0);
	formEnsayo.saveFoco = *((unsigned char*) config.ptrStruct + 1);
	formComposite.saveFoco = *((unsigned char*) config.ptrStruct + 2);
	formEnsayoLibre.saveFoco = *((unsigned char*) config.ptrStruct + 3);
	formProgramas.saveFoco = *((unsigned char*) config.ptrStruct + 4);
	formConfig.saveFoco = *((unsigned char*) config.ptrStruct + 5);
	formConfigEnsayo.saveFoco = *((unsigned char*) config.ptrStruct + 6);
	//NOTA: Antes de realizar una escritura a la mem flash,  se debe borrar el bloque donde se desea escribir*/
}// Fin CargarFocos()

/*Función DespertarMecoel------------------------------------------------------------------------------------------------------------------------
Descripción: Función que despierta el Microcontrolador. Esto se hace por medio de un reseteo para 
							asegurarnos una correcta inicialización de todos los dispositivos
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void DespertarMecoel(void)
{
	//Resetear las variables clave
	/*pot.bHabPotencia = 0;
	ADC.bCalibrando = 0;
	ADC.bCalibInter = 0;
	procADC.bActivo = 0;
	procAdquisicion.bActivo = 0;
	procMedTemp.bActivo = 0; 
	procConduc.bActivo = 0;
	temp.bCalibrado = 0;
	controlTemp.bHabControlTemp = 0;
	conduc.bCalibrado = 0;
	conduc.bCalibrarPuntas = 0;
	//Seteamos la variables de configuración
	config.bDurmiendo = 0;	//Indicamos que el MCU ya no está durmiendo y se tiene que despertar
	config.bDurmiendo = 1;
	
	_asm GOTO 0x00000 _endasm	//Reset();	//Reseteamos  el MCU para prenderlo*/
}// Fin DespertarMecoel()

/*Función DormirMecoel------------------------------------------------------------------------------------------------------------------------
Descripción: Función que manda al Microcontrolador a dormir anulando la entrada de clock del núcleo y de los
							periféricos
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void DormirMecoel(void)
{
	//Guardamos los Focos
	/*GuardarFocos();
	//Apagamos  los Timers
	T0CONbits.TMR0ON = 0;	//Apagamos el Timer0
	T1CONbits.TMR1ON = 0;	//Apagamos el Timer1
	T2CONbits.TMR2ON = 0;	//Apagamos el Timer2
	T3CONbits.TMR3ON = 0;	//Apagamos el Timer3
	T4CONbits.TMR4ON = 0;	//Apagamos el Timer4
	//Apagamos los PWMs que controlan el display
	CCP4CONbits.CCP4M3 = 0;	
	CCP4CONbits.CCP4M2 = 0;	
	CCP5CONbits.CCP5M3 = 0;	
	CCP5CONbits.CCP5M2 = 0;	
	PIN_PWM_LUZ_FONDO	= 0;
	PIN_PWM_CONTRASTE	= 0;
	//Apago el LCD	
	ApagarDisplay();
	//PIN_DISPLAY_ON_OFF	= 0;
	//Deshabilitamos todas  las interrupciones
	INTCON = 0;
	INTCON2 = 0;
	INTCON3 = 0;
	IPR1 = 0;
	IPR2 = 0;
	IPR3 = 0;
	PIE1 = 0;
	PIE2 = 0;
	PIE3 = 0;
	PIR1 = 0;
	PIR2 = 0;
	PIR3 = 0;
	//Habilitamos  solo la interrupción que me enteresa, que es la de PowerOn
	TRIS_POWER_ON_OFF = 1;	//Seteamos el pin como entrada
	IE_POWER_ON_OFF	= 1; //Habilitamos la interrupción
	IF_POWER_ON_OFF	= 0;
	IP_POWER_ON_OFF	= 0; //Seteamos la interrupción como de prioridad baja
	EDGE_POWER_ON_OFF = 0; //Indicamos que la interrupción sea por flanco ascendente
	//Preparamos el MCU para mandarlo a dormir
	config.bDurmiendo = 1;
	config.bNoEsPrimerEncendido	= 1;
	INTCONbits.GIE = 1;
	INTCONbits.PEIE = 1;
	OSCCONbits.IDLEN = 0;
	//Ponemos el MCU a dormir
	Sleep();*/
}// Fin DormirMecoel()

/*Función SetLuzFondo------------------------------------------------------------------------------------------------------------------------
Descripción: Función que setea la Luz de Fondo (BackLight)
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetLuzFondo(void)
{
	SetPWMDutyCycle((unsigned int) config.luzFondo * 266, PWM_LUZ_FONDO);
}// Fin SetLuzFondo()

/*Función SetContraste------------------------------------------------------------------------------------------------------------------------
Descripción: Función que setea el contraste
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetContraste(void)
{
	SetPWMDutyCycle((unsigned int) config.contraste * 60 + 3100, PWM_CONTRASTE);
}// Fin SetContraste()

/*Función GuardarConfigFlash()------------------------------------------------------------------------------------------------------------------------
Descripción: Función que guarda la configuración en la memoria flash
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void GuardarConfigFlash(void)
{
	#if (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
  CPU_SR        cpu_sr;
	#endif

	OS_ENTER_CRITICAL();

	//Indicamos la dirección del bloque de Flash
	config.rtsp.nvmAdru=__builtin_tblpage(&flashData);
	config.rtsp.nvmAdr=__builtin_tbloffset(&flashData);
	config.rtsp.nvmAdrPageAligned = config.rtsp.nvmAdr & 0xFC00;			// Get the Flash Page Aligned address
	config.rtsp.nvmRow=((config.rtsp.nvmAdr>>7) & 7);					// Row in the page	 				
	config.rtsp.nvmSize=64;

	flashPageRead(config.rtsp.nvmAdru, config.rtsp.nvmAdrPageAligned, buffFlash);	//Leemos el bloque de flash y lo almacenamos en buffFlash

	//Modificamos el arreglo con los cambios que queremos aplicar
	config.ptrStruct = (void *) (buffFlash + OFFSET_CONFIG);
	((struct ConfigdsPIC33*) config.ptrStruct)->luzFondo = config.luzFondo;
	((struct ConfigdsPIC33*) config.ptrStruct)->contraste = config.contraste;
	((struct ConfigdsPIC33*) config.ptrStruct)->duracionLuzFondo = config.duracionLuzFondo;

	flashPageErase(config.rtsp.nvmAdru, config.rtsp.nvmAdrPageAligned);	//Borramos  la página que queremos escribir
	flashPageWrite(config.rtsp.nvmAdru, config.rtsp.nvmAdrPageAligned, buffFlash);	//Escribimos la página en Flash con el buffer modificado 

	OS_EXIT_CRITICAL();
}// Fin GuardarConfigFlash()

/*Función CargarConfigFlash()------------------------------------------------------------------------------------------------------------------------
Descripción: Función que setea el valor de los parámetros de configuración cargándolos desde la Memoria Flash
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void CargarConfigFlash(void)
{
	#if (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
  CPU_SR        cpu_sr;
	#endif

	OS_ENTER_CRITICAL();

	config.rtsp.nvmAdru=__builtin_tblpage(&flashData);
	config.rtsp.nvmAdr=__builtin_tbloffset(&flashData);
	config.rtsp.nvmAdrPageAligned = config.rtsp.nvmAdr & 0xFC00;			// Get the Flash Page Aligned address
	config.rtsp.nvmRow=((config.rtsp.nvmAdr>>7) & 7);					// Row in the page	 				
	config.rtsp.nvmSize=64;

	flashPageRead(config.rtsp.nvmAdru, config.rtsp.nvmAdrPageAligned, buffFlash);	//Leemos el bloque de flash y lo almacenamos en buffFlash

	//Modificamos el arreglo con los cambios que queremos aplicar
	config.ptrStruct = (void *) (buffFlash + OFFSET_CONFIG);
	config.luzFondo = ((struct ConfigdsPIC33*) config.ptrStruct)->luzFondo;
	config.contraste = ((struct ConfigdsPIC33*) config.ptrStruct)->contraste;
	config.duracionLuzFondo = ((struct ConfigdsPIC33*) config.ptrStruct)->duracionLuzFondo;

	OS_EXIT_CRITICAL();
}// Fin CargarConfigFlash()()

/*Función ActualizarPantallaParametros------------------------------------------------------------------------------------------------------------------------
Descripción: Función que actualiza y redibuja los componentes de PANTALLA_PARAMETROS
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ActualizarPantallaParametros(void)
{

	//Actualizamos los componentes de la pantalla según el número de programa y segmento
	vPSpinEdits[10].valor.word = (unsigned int) param.diametros[param.iGdP].diametroTrac;
	vPSpinEdits[11].valor.word = (unsigned int) param.diametros[param.iGdP].diametroNoTrac;
	
	//Ordenamos a todos los componentes de PANTALLA_PROGRAMA que se redibujen
	formParametros.ptrObjetos[8].bRedibujar = 1;	//OBJETO 8 --> SPINEDIT "GRUPO DE PARAMETROS:"	--> formParametros --> IndValProp = 9
	formParametros.ptrObjetos[9].bRedibujar = 1;	//OBJETO 9 --> SPINEDIT "Diametro Traccion:"	--> formParametros --> IndValProp = 10
	formParametros.ptrObjetos[10].bRedibujar = 1;	//OBJETO 10 --> SPINEDIT "Diametro no Traccion:"	--> formParametros --> IndValProp = 11

}// Fin ActualizarPantallaParametros()

/*Función IniciarEnsayoLibre------------------------------------------------------------------------------------------------------------------------
Descripción: Función que setea lo necesario para  comenzar un Ensayo Libre
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void IniciarEnsayoLibre(void)
{
	/*
	ensayo.bEnsayando = 0;
	ensayo.TipoEnsayo = ENSAYO_LIBRE;
	conduc.bCalibrado = 0;
	CalibrarConduc();	
	*/
}// Fin IniciarEnsayoLibre()

/*Función TerminarEnsayoLibre------------------------------------------------------------------------------------------------------------------------
Descripción: Función que setea lo necesario para terminar un Ensayo Libre
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void TerminarEnsayoLibre(void)
{
	/*
	if (formEnsayoLibre.ptrObjetos[19].bChequeado == 1) //¿Se deben guardar los datos en la SD?	//OBJETO 19 --> CHECKBOX "Guardar en SD"
  {
		if ((sd.bSDInic == 1) && (sd.pNewFile != NULL)) //¿La SD se encuentra presente, inicializada y hay un archivo abierto?
		{
    	FSfclose(sd.pNewFile);
    	adqui.bGuardarEnSD = 0;
    	GLCD_Relleno(120,58,4,4,NEGRO);
		}
  }
  formEnsayoLibre.ptrObjetos[19].bEditable = 1;  //Desbloqueamos el CheckBox de guardar datos
	controlTemp.bHabControlTemp = 0;	//Inhabilitamos el control de temperatura (el PID)
	pot.bHabPotencia = 0;
	PIN_SALIDA_POTENCIA = 0;
	procControlTemp.bActivo = 0;
	ensayo.bEnsayando = 0; //Indicamos que hemos finalizado el ensayo
	adqui.modo = MODO_CONTINUO;
	adqui.periodoMuestreo = PERIODO_MUESTREO_CONTINUO;
	adqui.contMuestreo = 0;
	ensayo.TipoEnsayo = ENSAYO_NINGUNO;
	*/
}// Fin TerminarEnsayoLibre()

/*Función SetearProximoSegmento------------------------------------------------------------------------------------------------------------------------
Descripción: Función que actualiza el SetPoint y demás variables en función del programa y segmento en el que nos encontremos
Entrada: nada
Salida:
	SetearProximoSegmento(): Devuelve 1 si se pudo setear un segmento y cero si no se pudo setear
//-------------------------------------------------------------------------------------------------------------------------------------*/
unsigned char SetearProximoSegmento(void)
{
	/*
	do
	{
		//Probamos con el próximo segmento
		if ((controlTemp.prog[controlTemp.iProg].iSeg + 1) < CANT_SEGMENTOS)
			controlTemp.prog[controlTemp.iProg].iSeg++;
		else
			controlTemp.prog[controlTemp.iProg].iSeg = 0;	//Volvemos a empezar el programa
		//Preguntamos si el próximo segmento no es NULO
		if (controlTemp.prog[controlTemp.iProg].segmentos[controlTemp.prog[controlTemp.iProg].iSeg].tipo != SEG_NULO)
		{
			//Cargamos el SetPoint del próximo segmento
			controlTemp.setPoint = controlTemp.prog[controlTemp.iProg].segmentos[controlTemp.prog[controlTemp.iProg].iSeg].setPoint;
			//Reseteamos el contador de Duración de segmento
			controlTemp.contDuracionSeg = 0;
			//Cargamos el Diferencial del próximo segmento
			controlTemp.mitadDiferencial = (float) controlTemp.prog[controlTemp.iProg].segmentos[controlTemp.prog[controlTemp.iProg].iSeg].dif / 2;

			controlTemp.bCruceSetPoint = 0;
			controlTemp.bCalcularErrorInicial = 1;
			controlTemp.bTodosNulos = 0;	//Se encontró al menos un Segmento no NULO
			controlTemp.bCuentaHabilitada = 0;	//Por defecto, consideramos que estamos fuera del rango diferencial
			//Reseteamos los contadores
			controlTemp.contSeg = 0;	
			controlTemp.contMs = 0;

			if (controlTemp.prog[controlTemp.iProg].segmentos[controlTemp.prog[controlTemp.iProg].iSeg].tipo == SEG_FINAL)	//¿Llegamos  al segmento FINAL?
				controlTemp.bSegmentoFinal = 1;
			else
				controlTemp.bSegmentoFinal = 0;
		}
		else	//El próximo segmento es NULO
		{
			if ((controlTemp.prog[controlTemp.iProg].iSeg + 1) >= CANT_SEGMENTOS)	//¿Ya no hay más segmentos para analizar?
				if (controlTemp.bTodosNulos == 1)	//¿Todos los analizados hasta ahora fueron nulos?
					return 0;	//No existe ningún segmento válido => Terminamos  el programa sin hacer nada
		}
	} while (controlTemp.prog[controlTemp.iProg].segmentos[controlTemp.prog[controlTemp.iProg].iSeg].tipo == SEG_NULO);	//Continuamos recorriendo los segmentos hasta que encontremos alguno que no sea NULO
	*/
}// Fin SetearProximoSegmento()

/*Función IniciarEnsayoProgramado------------------------------------------------------------------------------------------------------------------------
Descripción: Función que setea lo necesario para  comenzar un Ensayo Programado
Entrada: nada
Salida:
	IniciarEnsayoProgramado(): Si se pudo iniciar el Ensayo, devuelve (1), sino (0)
//-------------------------------------------------------------------------------------------------------------------------------------*/
unsigned char IniciarEnsayoProgramado(void)
{
	/*
	if (controlTemp.bProgCargadosDesdeSD == 0)	//Todavía no fueron cargados los programas desde la SD
		CargarProgramas();	//Actualizamos el arreglo de Programas con los datos que hay en la SD
	controlTemp.iProg = (unsigned char) vPSpinEdits[13].valor.word;
	controlTemp.prog[controlTemp.iProg].iSeg = 0;	//Apuntamos al primer Segmento
	controlTemp.bTodosNulos = 1;	//Asumimos por defecto que todos los segmentos son nulos
	//Verificamos si el primer segmento del programa elegido es de tipo NULO
	if (controlTemp.prog[controlTemp.iProg].segmentos[0].tipo == SEG_NULO) //¿El primer segmento es o NULO o FINAL?
	{
		if (SetearProximoSegmento() == 0)	//¿No se encontró un segmento válido?
			return	0;	//No se puede ejecutar el programa => no hacemos nada
	}
	else	//El primer segmento es un segmento válido
	{
		//Cargamos el SetPoint del primer segmento
		controlTemp.setPoint = controlTemp.prog[controlTemp.iProg].segmentos[0].setPoint;
		//Reseteamos el contador de Duración de segmento
		controlTemp.contDuracionSeg = 0;
		//Cargamos el Diferencial del primer segmento
		controlTemp.mitadDiferencial = (float) controlTemp.prog[controlTemp.iProg].segmentos[0].dif / 2;

		controlTemp.bCruceSetPoint = 0;
		controlTemp.bCalcularErrorInicial = 1;
		controlTemp.bCuentaHabilitada = 0;	//Por defecto, consideramos que estamos fuera del rango diferencial
		//Reseteamos los contadores
		controlTemp.contSeg = 0;	
		controlTemp.contMs = 0;

		if (controlTemp.prog[controlTemp.iProg].segmentos[0].tipo == SEG_FINAL)	//¿El primer segmento es segmento FINAL?
				controlTemp.bSegmentoFinal = 1;
		else
				controlTemp.bSegmentoFinal = 0;
	}
	
	if (conduc.bCompositesCargados == 0)	//¿Los composites todavía no han sido cargados desde la Flash?
		CargarComposites();
	
	conduc.iComposite = vPSpinEdits[12].valor.word;
	controlTemp.iProg = vPSpinEdits[13].valor.word;

	//Inicializamos los SpinEdits
  vPSpinEdits[14].valor.word = controlTemp.iProg;	//SpinEdit "P:"
	vPSpinEdits[15].valor.word = controlTemp.prog[controlTemp.iProg].iSeg;	//SpinEdit "S:"
	vPSpinEdits[17].valor.word = 0;	//SpinEdit "DS:"
  vPSpinEdits[18].valor.word = 0;	//SpinEdit "hs:"
  vPSpinEdits[19].valor.word = 0;	//SpinEdit "min:"
  vPSpinEdits[20].valor.word = 0;	//SpinEdit "seg:"
	vPSpinEdits[16].valor.word = conduc.iComposite;	//SpinEdit "C:"
	vPSpinEdits[21].valor.word = (unsigned int) controlTemp.setPoint;	//SpinEdit "SP:"

	ensayo.bEnsayando = 0; //El ensayo todavía no comenzó, hay que esperar a que se calibre la conductividad
	ensayo.TipoEnsayo = ENSAYO_PROGRAMADO;
	conduc.bCalibrado = 0;
	CalibrarConduc();	
	return 1;	//Se pudo Iniciar el Ensayo
	*/
}// Fin IniciarEnsayoProgramado()

/*Función TerminarEnsayoProgramado------------------------------------------------------------------------------------------------------------------------
Descripción: Función que setea lo necesario para terminar un Ensayo Programado
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void TerminarEnsayoProgramado(void)
{
	/*
	if (formConfigEnsayo.ptrObjetos[6].bChequeado == 1) //¿Se debían guardar datos en la SD?
  {
		if ((sd.bSDInic == 1) && (sd.pNewFile != NULL)) //¿La SD se encuentra presente, inicializada y hay un archivo abierto?
		{
    	FSfclose(sd.pNewFile);
    	adqui.bGuardarEnSD = 0;
    	GLCD_Relleno(120,58,4,4,NEGRO);
		}
  }
	controlTemp.bHabControlTemp = 0;	//Inhabilitamos el control de temperatura (el PID)
	pot.bHabPotencia = 0;
	PIN_SALIDA_POTENCIA = 0;
	procControlTemp.bActivo = 0;
	ensayo.bEnsayando = 0; //Indicamos que hemos finalizado el ensayo
	adqui.modo = MODO_CONTINUO;
	adqui.periodoMuestreo = PERIODO_MUESTREO_CONTINUO;
	adqui.contMuestreo = 0;

	//Acá habría que mostrar un mensaje

	if (controlTemp.bEjecucionCancelada == 0)	//¿La ejecución NO fue cancelada?
	{
		//Verificamos si se pidió que el equipo se apague solo
		if (formConfigEnsayo.ptrObjetos[7].bChequeado == 1) //¿Se pidió que Mecoel se apague al terminar?
			DormirMecoel(); //Dormimos ("Apagamos") el equipo
	}	
	ensayo.TipoEnsayo = ENSAYO_NINGUNO;
	*/
}// Fin TerminarEnsayoLibre()

/*Función GraficarNuevoPunto------------------------------------------------------------------------------------------------------------------------
Descripción: Función que grafica un nuevo punto en la pantalla cuando está ejecutándose el Ensayo Programado
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void GraficarNuevoPunto(void)
{
	/*
	if (adqui.posX < 126)	//¿La gráfica todavía no llegó al final de la pantalla?
	{
		adqui.posY = (unsigned char) (temp.temperatura * PIXELES_POR_GRADO + OFFSET_EN_Y_DEL_GRAFICO);
		adqui.posX++;
		GLCD_Punto(adqui.posX, adqui.posY, !COLOR_FONDO_DEF);
	}	
	else
	{
		
	}
	*/
}	// Fin GraficarNuevoPunto()

