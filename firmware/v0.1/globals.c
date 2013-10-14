
#include "globals.h"
//#include "interfaz_cfg.h"

//VARIABLES GLOBALES

struct Eventos eventos;

//Variables para la conversi�n de punto flotante a decimal y luego a string
struct FloatToStr fToStr;

//Variables de tiempo
struct Tiempo tiempo;

//Variables de Configuraci�n
int8_t buffFlash[64*8];	//Buffer temporal para los datos leidos desde la Flash
struct ConfigdsPIC33 config;
int8_t flashData[TAMANIO_BLOQUE_BORRADO] __attribute__((space(prog),section("FlashData"),address(BLOQUE_FLASH))); 

//Variables de la funci�n BinBCD()
unsigned char BCD[10]; // ya que convierte un signed long int que va -2147483648 a 2147483647
signed char signo;
unsigned char iBBCD;

//Variables de la funci�n FloatToString()
unsigned char iFTS;
unsigned char jFTS;
unsigned char kFTS;
float floatFTS;

//Variables de la funci�n FloatToScientific()
unsigned char iFTSci;

//Variables de CargarFocos()
unsigned char iCF;

//Variables  del AD
//unsigned int Muestras[105];

//Variable Contadora Gen�rica
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

//DEFINICI�N DE FUNCIONES GLOBALES
/*Funci�n BinBCD------------------------------------------------------------------------------------------------------------------------
Descripci�n: Funci�n que descompone un signed int en unidad, decena, centena, unidad de mil y decena de mil 
Entrada:
		valor: signed long int que se desea convertir a BCD
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void BinBCD(signed long int valor)
{
	//unsigned char iBBCD;

	//Reseteamos BCD
	for(iBBCD=0;iBBCD<10;iBBCD++)
		BCD[iBBCD] = CERO_ASCII;

	//Determinamos signo
	if (valor >= 0)
		signo = 1;
	else
	{
		signo = -1;
		valor = -valor;
	}
	// lo comentamos para que el tiempo sea menor y menor memoria de prog., ya que no se usan todos los d�gitos
	//Unidad de mil de mill�n
	if (valor >= 1000000000) 
		while(valor >= 1000000000)
		{
			BCD[9]++;
			valor = valor - 1000000000;
		}
	//Centena de mill�n
	if (valor >= 100000000) 
		while(valor >= 100000000)
		{
			BCD[8]++;
			valor = valor - 100000000;
		}
	//Decena de mill�n
	if (valor >= 10000000) 
		while(valor >= 10000000)
		{
			BCD[7]++;
			valor = valor - 10000000;
		}
	//Unidad de mill�n
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

/*Funci�n FloatToString------------------------------------------------------------------------------------------------------------------------
Descripci�n: Funci�n que convierte un float a una cadena de caracteres 
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void FloatToString(char floatStr[], unsigned char formato)
{
  //unsigned char iFTS;
  //unsigned char jFTS;
  //unsigned char kFTS;
  //float floatFTS;

  // Como FloatToString() no trabaja con n�meros negativos debido a que se tiene en cuenta antes
  // si fToStr.flotante es negativo le cambiamos el signo
  if(fToStr.flotante < 0)
    fToStr.flotante = -fToStr.flotante;

  //Reseteamos la cadena a imprimir colocando todos espacios
  for(iFTS=0;iFTS<8;iFTS++)
    floatStr[iFTS] = ' ';
  floatStr[8] = 0;	//Colocamos NULL al final de la cadena

  floatFTS = fToStr.flotante;
  fToStr.expNeg = 0;
  if (((unsigned long int) floatFTS) < ((unsigned long int) 10000))	//�La parte entera tiene 4 o menos cifras?
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
      fToStr.expNeg++;	//Ponemos esto en uno para que no entre en la condici�n "fToStr.expNeg == 0" puesta m�s adelante
    //A esta altura, el n�mero es si o si mayor que 10000, es decir, tiene 5 o m�s cifras enteras
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
        floatStr[7] = ' ';	//No lleva ning�n multiplicador
        fToStr.nroCifrasHastaComa = 5 - fToStr.expNeg;
      }
    }
  }
  fToStr.parteEntera = (signed long int) floatFTS;
  if (fToStr.expNeg == 0)	//Si el n�mero originalmente era mayor a 10000
  {
    //Calculamos el n�mero de cifras de la parte entera
    fToStr.multi = 1;
    fToStr.nroCifrasEnteras = 1;	//Considero por defecto una cifra entera porque el n�mero es mayor que 1
    if (fToStr.parteEntera != 0)
    {
      while(fToStr.parteEntera >= (fToStr.multi * 10))
      {
        fToStr.nroCifrasEnteras++;
        fToStr.multi = fToStr.multi * 10;
      }
    }
    //Calculamos el n�mero de cifras antes de la coma
    if (fToStr.multi >= 1000000)	//El n�mero es mayor que 1M
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
        floatStr[7] = ' ';	//Ning�n multiplicador
        fToStr.nroCifrasHastaComa = fToStr.nroCifrasEnteras;
      }
    }
  }

  //Convertimos la parte entera a BCD
  BinBCD(fToStr.parteEntera);
  if (floatFTS != 0)
  {
    iFTS = 8;	//Nos ubicamos en la centena de mill�n
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
  if (formato == MENOS_DE_CINCO_CIFRAS_SIGNIF)	//�Se desea imprimir menos  de cinco cifras significativas?
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

/*Funci�n FloatToScientific------------------------------------------------------------------------------------------------------------------------
Descripci�n: Funci�n que formatea la cadena floatStr a un formato cient�fico 
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void FloatToScientific(char floatStr[], unsigned char formato)
{
  if (formato == CINCO_CIFRAS_SIGNIF)	//�Se desea imprimir cinco cifras significativas?
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

/*Funci�n SetPWMDutyCycle------------------------------------------------------------------------------------------------------------------------
Descripci�n: Funci�n que setea el duty cycle del PWM de 10 bits
Entrada: 
	dutyCycle: Valor entre 0 y PR3 indicando el duty cycle al que se desea setear el PWM
	module: n�mero del m�dulo al que se desea setearle el duty cycle
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

/*Funci�n InicConfig------------------------------------------------------------------------------------------------------------------------
Descripci�n: Funci�n que inicializa la estructura de configuraci�n del dispositivo
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void InicConfig(void)
{	
  //Configurar Encendido/Apagado
  /*TRIS_POWER_ON_OFF = 1;	//Seteamos el pin como entrada
  IE_POWER_ON_OFF	= 1; //Habilitamos la interrupci�n
  IF_POWER_ON_OFF	= 0;
  IP_POWER_ON_OFF	= 0; //Seteamos la interrupci�n como de prioridad baja
  EDGE_POWER_ON_OFF = 0; //Indicamos que la interrupci�n sea por flanco ascendente
  config.bDurmiendo = 0;*/

  //Configuraci�n del timer3
  T3CONbits.TCKPS = 0;	//Prescaler = 0
  PR3 = 4000;
  T3CONbits.TON = 1;

  AD1PCFGLbits.PCFG5 = 1;	//RB3 - Contraste
  AD1PCFGLbits.PCFG4 = 1;	//RB2 - Backlight
  TRIS_GLCD_CONTRASTE = 0;
  TRIS_GLCD_BACKLIGHT	= 0;

  //Configurar PWM del contraste y del DutyCycle (Configuraci�n del Output Compare)
  RPOR1bits.RP2R = 0b10010;	//RP2 conectado a Output Compare 1
  OC1CONbits.OCTSEL = 1;	//El clock del PWM es el Timer3
  OC1CONbits.OCM = 0b110;	//PWM mode on OCx, Fault pin disabled
  OC1RS = 3850;

  RPOR1bits.RP3R = 0b10011;	//RP3 conectado a Output Compare 2
  OC2CONbits.OCTSEL = 1;	//El clock del PWM es el Timer3
  OC2CONbits.OCM = 0b110;	//PWM mode on OCx, Fault pin disabled
  OC2RS = 3850;

  CargarConfigFlash();	//Cargamos la estructura de configuraci�n con los datos de la Mem Flash

  //Setear contraste y Backlight
  SetLuzFondo();
  SetContraste();
}// Fin InicConfig()

/*Funci�n GuardarFocos------------------------------------------------------------------------------------------------------------------------
Descripci�n: Funci�n que almacena los focos de las pantallas en la Memoria Flash
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void GuardarFocos(void)
{
  /*config.address.u24 = BLOQUE_FLASH;	//Cargamos la direcci�n del bloque con el que queremos trabajar
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

/*Funci�n CargarFocos------------------------------------------------------------------------------------------------------------------------
Descripci�n: Funci�n que carga los focos de las pantallas desde la Memoria Flash
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void CargarFocos(void)
{
  //unsigned char iCF;

  /*config.address.u24 = BLOQUE_FLASH;	//Cargamos la direcci�n del bloque con el que queremos trabajar
  FlashBlockRead();	//Leemos el bloque de Flash completo
  //Cargamos los focos le�dos desde la Memoria Flash
  config.ptrStruct = (void *) (gDataBuffer + OFFSET_FOCOS);
  for(iCF=0;iCF<NUM_PANTALLAS-1;iCF++)
    if (*((unsigned char*) config.ptrStruct + iCF) == 255)  //�Los focos por alg�n motivo no est�n inicializados?
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


/*Funci�n ApagarLuzFondo------------------------------------------------------------------------------------------------------------------------
Descripci�n: Funci�n que apaga la Luz de Fondo (BackLight)
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ApagarLuzFondo(void)
{
  SetPWMDutyCycle(0, PWM_LUZ_FONDO);
}// Fin ApagarLuzFondo()

/*Funci�n SetLuzFondo------------------------------------------------------------------------------------------------------------------------
Descripci�n: Funci�n que setea la Luz de Fondo (BackLight)
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetLuzFondo(void)
{
  SetPWMDutyCycle((unsigned int) config.luzFondo * 266, PWM_LUZ_FONDO);
}// Fin SetLuzFondo()

/*Funci�n SetContraste------------------------------------------------------------------------------------------------------------------------
Descripci�n: Funci�n que setea el contraste
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetContraste(void)
{
  SetPWMDutyCycle((unsigned int) config.contraste * 60 + 3100, PWM_CONTRASTE);
}// Fin SetContraste()

/*Funci�n GuardarConfigFlash()------------------------------------------------------------------------------------------------------------------------
Descripci�n: Funci�n que guarda la configuraci�n en la memoria flash
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void GuardarConfigFlash(void)
{
  #if (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
  CPU_SR        cpu_sr;
  #endif

  OS_ENTER_CRITICAL();

  //Indicamos la direcci�n del bloque de Flash
  config.rtsp.nvmAdru=__builtin_tblpage(&flashData); // NVM = NON VOLATILE MEMORY
  config.rtsp.nvmAdr=__builtin_tbloffset(&flashData);
  config.rtsp.nvmAdrPageAligned = config.rtsp.nvmAdr & 0xFC00;			// Get the Flash Page Aligned address
  config.rtsp.nvmRow=((config.rtsp.nvmAdr>>7) & 7);					// Row in the page
  config.rtsp.nvmSize=64;

  flashPageRead(config.rtsp.nvmAdru, config.rtsp.nvmAdrPageAligned, buffFlash);	//Leemos el bloque de flash y lo almacenamos en buffFlash

  //Modificamos el arreglo con los cambios que queremos aplicar
  config.ptrStruct = (void *) (buffFlash + OFFSET_CONFIG);
  ((struct ConfigdsPIC33*) config.ptrStruct)->luzFondo = config.luzFondo;
  ((struct ConfigdsPIC33*) config.ptrStruct)->contraste = config.contraste;
  ((struct ConfigdsPIC33*) config.ptrStruct)->bDuracionLuzFondo = config.bDuracionLuzFondo;
  ((struct ConfigdsPIC33*) config.ptrStruct)->duracionLuzFondo = config.duracionLuzFondo;

  flashPageErase(config.rtsp.nvmAdru, config.rtsp.nvmAdrPageAligned);	//Borramos  la p�gina que queremos escribir
  flashPageWrite(config.rtsp.nvmAdru, config.rtsp.nvmAdrPageAligned, buffFlash);	//Escribimos la p�gina en Flash con el buffer modificado

  OS_EXIT_CRITICAL();
}// Fin GuardarConfigFlash()

/*Funci�n CargarConfigFlash()------------------------------------------------------------------------------------------------------------------------
Descripci�n: Funci�n que setea el valor de los par�metros de configuraci�n carg�ndolos desde la Memoria Flash
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
  config.bDuracionLuzFondo = ((struct ConfigdsPIC33*) config.ptrStruct)->bDuracionLuzFondo;
  if (((struct ConfigdsPIC33*) config.ptrStruct)->duracionLuzFondo != 0xFFFF)
    config.duracionLuzFondo = ((struct ConfigdsPIC33*) config.ptrStruct)->duracionLuzFondo;
  else
    config.duracionLuzFondo = DUR_LUZ_FONDO_DEF;

  OS_EXIT_CRITICAL();
}// Fin CargarConfigFlash()()

/*Funci�n ActualizarPantallaParametros------------------------------------------------------------------------------------------------------------------------
Descripci�n: Funci�n que actualiza y redibuja los componentes de PANTALLA_PARAMETROS
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ActualizarPantallaParametros(void)
{
  //Actualizamos los componentes de la pantalla seg�n el n�mero de programa y segmento
  vPSpinEdits[10].valor.word = (unsigned int) param.diametros[param.iGdP].diametroTrac;
  vPSpinEdits[11].valor.word = (unsigned int) param.diametros[param.iGdP].diametroNoTrac;

  //Ordenamos a todos los componentes de PANTALLA_PROGRAMA que se redibujen
  formParametros.ptrObjetos[8].bRedibujar = 1;	//OBJETO 8 --> SPINEDIT "GRUPO DE PARAMETROS:"	--> formParametros --> IndValProp = 9
  formParametros.ptrObjetos[9].bRedibujar = 1;	//OBJETO 9 --> SPINEDIT "Diametro Traccion:"	--> formParametros --> IndValProp = 10
  formParametros.ptrObjetos[10].bRedibujar = 1;	//OBJETO 10 --> SPINEDIT "Diametro no Traccion:"	--> formParametros --> IndValProp = 11
}// Fin ActualizarPantallaParametros()

/*Funci�n IniciarEnsayo------------------------------------------------------------------------------------------------------------------------
Descripci�n: Funci�n que setea lo necesario para comenzar un Ensayo
Entrada: nada
Salida:
	IniciarEnsayo(): Si se pudo iniciar el Ensayo, devuelve (1), sino (0)
//-------------------------------------------------------------------------------------------------------------------------------------*/
unsigned char IniciarEnsayo(void)
{
  if (param.bParamCargadosDesdeFlash == 0)	//�Todav�a no fueron cargados los par�metros desde la Flash?
    CargarParametros();	//Actualizamos el arreglo de Par�metros

  /*if (sd.bSDInic == 1) //�La SD se encuentra presente e inicializada?
  {
    adqui.nroMuestra = 1;
    OpenNewMed();
    adqui.bGuardarEnSD = 1;
    GLCD_Relleno(120,58,4,4,BLANCO);
  }*/

  if (formMediciones.ptrObjetos[22].bChequeado == 1)	//�El ensayo es con duraci�n?	//OBJETO 23 --> CHECKBOX "Dur:   min"
	{
		ensayo.duracion.hs = (uint8_t) ((float) vPSpinEdits[4].valor.word / (float) 60);
		ensayo.duracion.min = (vPSpinEdits[4].valor.word % 60);
	}
	else	//El ensayo no tiene duraci�n
		ensayo.duracion.min = ENSAYO_SIN_DURACION;

  //Reseteamos  el tiempo
  tiempo.seg = 0;
  tiempo.min = 0;
  tiempo.hs = 0;
												  
  ensayo.bEnsayando = 1;
	//ensayo.bIniciarEnsayo = 0;

  return 1;	//Se pudo Iniciar el Ensayo
}// Fin IniciarEnsayoProgramado()

/*Funci�n TerminarEnsayo------------------------------------------------------------------------------------------------------------------------
Descripci�n: Funci�n que setea lo necesario para terminar un Ensayo Programado
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void TerminarEnsayo(void)
{
  /*if ((sd.bSDInic == 1) && (sd.pNewFile != NULL)) //�La SD se encuentra presente, inicializada y hay un archivo abierto?
  {
    FSfclose(sd.pNewFile); //Cierra el archivo
    adqui.bGuardarEnSD = 0;
    //GLCD_Relleno(120,58,4,4,NEGRO);
  }*/

  adqui.numMedActual++;
  ensayo.bEnsayando = 0; //Indicamos que hemos finalizado el ensayo
  adqui.contMuestreo = 0;

	ensayo.bTerminarEnsayo = 1;

  //Ac� habr�a que mostrar un mensaje
	
}// Fin TerminarEnsayo()

