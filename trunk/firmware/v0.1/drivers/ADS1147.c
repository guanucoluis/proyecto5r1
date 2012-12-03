#include "ADS1147.h"
//VECTORES DE OBJETOS
//#pragma udata Adquisicion = 0x600 // Cada bloque de RAM tiene 256 bytes

//Variables
volatile struct ADConverter ADC;
unsigned char backUpSSPSTAT;	//Variables para salvar temporalmente el estado de este reg y luego restaurarlo
unsigned char backUpSSPCON1;	//Variables para salvar temporalmente el estado de este reg y luego restaurarlo

//#pragma udata // udata = Variables no inicializadas


/*Función WriteRegADC------------------------------------------------------------------------------------------------------------------------
Descripción: Escribe un solo byte hacia el Bus SPI1.
Entrada: un byte de dato para escribir en el Bus SPI1
Salida: el byte de estado para la deteccion del WCOL
//-------------------------------------------------------------------------------------------------------------------------------------*/
unsigned char WriteSpiADC( unsigned char data_out )
{
  /*
	unsigned char TempVar;  
  backUpSSPSTAT = SSP1STAT;	//Salvamos el registro SSPSTAT
  backUpSSPCON1 = SSPCON1;	//Salvamos el registro SSPCON1
  SSP1STAT = 0b00000000;
	SSP1CON1 = 0b00100000;
  TempVar = SSP1BUF;           // Clears BF
  PIR1bits.SSP1IF = 0;         // Clear interrupt flag
  SSP1CON1bits.WCOL = 0;			//Clear any previous write collision
  SSP1BUF = data_out;          // write byte to SSP1BUF register
  if ( SSP1CON1 & 0x80 )       // test if write collision occurred
   return ( -1 );              // if WCOL bit is set return negative #
  else
   //while( !SSP1STATbits.BF ); // wait until bus cycle complete 
   while(!PIR1bits.SSP1IF); // wait until bus cycle complete
  SSP1STAT = backUpSSPSTAT;	//Restauramos el registro SSPSTAT
  SSPCON1 = backUpSSPCON1;	//Restauramos el registro SSPCON1
  return ( 0 );                // if WCOL bit is not set return non-negative#
	*/
}//Fin WriteSpiADC()

/*Función ReadSpiADC------------------------------------------------------------------------------------------------------------------------
Descripción: Lee un solo byte desde el Bus SPI1.
Entrada: nada
Salida: el contenido del registro SSP1BUF
//-------------------------------------------------------------------------------------------------------------------------------------*/
unsigned char ReadSpiADC( void )
{
	/*
  unsigned char TempVar;
  backUpSSPSTAT = SSP1STAT;	//Salvamos el registro SSPSTAT
  backUpSSPCON1 = SSPCON1;	//Salvamos el registro SSPCON1
  SSP1STAT = 0b00000000;
	SSP1CON1 = 0b00100000;
  TempVar = SSP1BUF;       //Clear BF
  PIR1bits.SSP1IF = 0;     //Clear interrupt flag
  SSP1BUF = 0xFF;          // initiate bus cycle
  //while ( !SSP1STATbits.BF );                // wait until cycle complete
  while(!PIR1bits.SSP1IF); //wait until cycle complete
  SSP1STAT = backUpSSPSTAT;	//Restauramos el registro SSPSTAT
  SSPCON1 = backUpSSPCON1;	//Restauramos el registro SSPCON1
  return ( SSP1BUF );      // return with byte read 
	*/
}//Fin ReadSpiADC()

/*Función WriteRegADC------------------------------------------------------------------------------------------------------------------------
Descripción: escribe el registro reg del ADC con el valor dato
Entrada:
	reg: número de registro a escribir
	dato: dato a escribir en reg
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void WriteRegADC(unsigned char reg, unsigned char dato)
{
	/*
	START_PIN = 1;
	WriteSpiADC(0x40 | reg);	//Enviamos el código de escritura de registros (0x40) y el registro inicial reg
	WriteSpiADC(0);	//Indicamos que vamos a escribir solo 1 registro
	WriteSpiADC(dato);	//Enviamos el dato que queremos que se escriba en el registro
	START_PIN = 0;
	*/
}//Fin WriteRegADC()

/*Función WriteRegsADC------------------------------------------------------------------------------------------------------------------------
Descripción: Envía un comando al ADC para habilitar la escritura de n registros consecutivos a partir de reg (permite escritura por bloques)
Entrada:
	reg: número de registro a partir del cual se quiere escribir
	n: número de registros a escribir
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void WriteRegsADC(unsigned char reg, unsigned char n)
{
	START_PIN = 1;
	n--; //Decrementamos esta variable porque al ADC debemos pasarle el número de registros menos 1
	WriteSpiADC(0x40 | reg);	//Enviamos el código de escritura de registros (0x40) y el registro inicial reg
	WriteSpiADC(n);	//Enviamos la cantidad de registros que deseamos escribir
	START_PIN = 0;
}//Fin WriteRegsADC()

/*Función ReadRegADC------------------------------------------------------------------------------------------------------------------------
Descripción: lee el registro reg desde el ADC y lo devuelve
Entrada:
	reg: número de registro a leer
Salida: el contenido del registro reg
//-------------------------------------------------------------------------------------------------------------------------------------*/
unsigned char ReadRegADC(unsigned char reg)
{
	START_PIN = 1;
	//-+-+*WriteSpiADC(0x20 | reg);	//Enviamos el código de lectura de registros (0x20) y el registro inicial reg
	//-+-+*WriteSpiADC(0);	//Indicamos que vamos a leer solo 1 registro
	START_PIN = 0;
	return (ReadSpiADC());	//Esperamos el valor devuelto por el ADC
}//Fin ReadRegADC()

/*Función ReadRegsADC------------------------------------------------------------------------------------------------------------------------
Descripción: Envía un comando al ADC para habilitar la lectura de n registros consecutivos a partir de reg (permite lectura por bloques)
Entrada:
	reg: número de registro a partir del cual se quiere leer
	n: número de registros a leer
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ReadRegsADC(unsigned char reg, unsigned char n)
{
	START_PIN = 1;
	n--; //Decrementamos esta variable porque al ADC debemos pasarle el número de registros menos 1
	//-+-+*WriteSpiADC(0x20 | reg);	//Enviamos el código de lectura de registros (0x20) y el registro inicial reg
	//-+-+*WriteSpiADC(n);	//Enviamos la cantidad de registros que deseamos leer
	START_PIN = 0;
}//Fin ReadRegsADC()

/*Función IniciarMuestra------------------------------------------------------------------------------------------------------------------------
Descripción: función que inicia la conversión de una nueva muestra enviando un breve pulso de START al ADS1147
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void IniciarMuestra(void)
{
	SelecADC(); 		//Seleccionamos (mediante el CS) el ADC para comunicación SPI
	START_PIN = 1;	//Lanzamos la conversión poniendo STAR_PIN en 1
	DelayTcy(1);			//Delay10TCYx(1);	//Hacemos una pequeña demora para que el cambio de estado sea reconocido por el ADC
	START_PIN = 0;	//Volvemos STAR_PIN a 0
	DeselecADC(); 	//Deseleccionamos (mediante el CS) el ADC para comunicación SPI 

} //Fin IniciarMuestra

/*Función TomarMuestra------------------------------------------------------------------------------------------------------------------------
Descripción: función que adquiere "nroMuestras" parciales y guarda el promedio de las mismas en "valor"
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void TomarMuestra(void)
{
	ADC.bValorListo = 0;	//Indicamos que el valor en "valor" ya no es válido
	ADC.bMuestraLista = 0;	//Todavía no se ha tomado ninguna muestra
	ADC.contMuestras = 0;	//Reseteamos el contador de muestras
	ADC.sumaMuestras = 0;	//Reseteamos la sumatoria
	ADC.timeout	= TIMEOUT_MUESTREO; //Reseteamos el timeout	
	ADC.bMuestreando = 1;	//Indico que el ADC está en proceso de muestreo
	
	IniciarMuestra();	//Iniciar muestra enviando un pulso por START

} //Fin TomarMuestra

/*Función LeerMuestraADC------------------------------------------------------------------------------------------------------------------------
Descripción: función que pide al ADC que le envíe la muestra y la almacena en ADC.valorTemp
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void LeerMuestraADC(void)
{
	SelecADC();
	//START_PIN = 1;
	//Delay10TCYx(10);	//Esperamos 32.8 useg
	//-+-+*ReadOnceADC();
	//Delay10TCYx(10);	//Esperamos 32.8 useg
	*((unsigned char *) &ADC.valorTemp + 1) = (unsigned char) ReadSpiADC();	//Obtenemos la parte alta de la conversión
	*((unsigned char *) &ADC.valorTemp + 0) = (unsigned char) ReadSpiADC();	//Obtenemos la parte baja de la conversión
	//START_PIN = 0;
	DeselecADC();
} //Fin LeerMuestraADC

/*Función SetBurnOutCurrent------------------------------------------------------------------------------------------------------------------------
Descripción: función que setea la corriente de prueba para saber si el sensor está ausente o quemado
Entrada:
		burnOutCurrent: código que simboliza la corriente de BurnOut que se quiere setear
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetBurnOutCurrent(unsigned char burnOutCurrent)
{
	unsigned char dato;
	
	SelecADC(); //Seleccionamos (mediante el CS) el ADC para comunicación SPI
	dato = ReadRegADC(MUX0);	//Leemos el registro desde el ADC
	dato = dato & 0b00111111;	//Limpiamos la información que había antes sobre lo que nos interesa cambiar
	dato = dato | (burnOutCurrent << 6);	//Seteamos el nuevo valor
	WriteRegADC(MUX0, dato);	//Escribimos el nuevo valor en el registro
	DeselecADC(); 	//Deseleccionamos (mediante el CS) el ADC para comunicación SPI 
	
} //Fin SetBurnOutCurrent

/*Función SetPosIn------------------------------------------------------------------------------------------------------------------------
Descripción: función que setea la entrada positiva para la conversión
Entrada:
		PosIn: código que simboliza la entrada positiva
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetPosIn(unsigned char PosIn)
{
	unsigned char dato;
	
	SelecADC(); //Seleccionamos (mediante el CS) el ADC para comunicación SPI
	dato = ReadRegADC(MUX0);	//Leemos el registro desde el ADC
	dato = dato & 0b11000111;	//Limpiamos la información que había antes sobre lo que nos interesa cambiar
	dato = dato | (PosIn << 3);	//Seteamos el nuevo valor
	WriteRegADC(MUX0, dato);	//Escribimos el nuevo valor en el registro
	DeselecADC(); 	//Deseleccionamos (mediante el CS) el ADC para comunicación SPI 
	
} //Fin SetPosIn

/*Función SetNegIn------------------------------------------------------------------------------------------------------------------------
Descripción: función que setea la entrada negativa para la conversión
Entrada:
		NegIn: código que simboliza la entrada negativa
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetNegIn(unsigned char NegIn)
{
	unsigned char dato;
	
	SelecADC(); //Seleccionamos (mediante el CS) el ADC para comunicación SPI
	dato = ReadRegADC(MUX0);	//Leemos el registro desde el ADC
	dato = dato & 0b11111000;	//Limpiamos la información que había antes sobre lo que nos interesa cambiar
	dato = dato | NegIn;	//Seteamos el nuevo valor
	WriteRegADC(MUX0, dato);	//Escribimos el nuevo valor en el registro
	DeselecADC(); 	//Deseleccionamos (mediante el CS) el ADC para comunicación SPI 
	
} //Fin SetNegIn

/*Función SetFuenteConv------------------------------------------------------------------------------------------------------------------------
Descripción: función que setea el canal que el ADC usará para realizar la adquisición
Entrada:
		canal: entero que representa el canal desde donde se hace la adquisición
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetFuenteConv(unsigned char canal)
{
	switch (canal)
	{
		case CANAL_0:	//El canal cero es PosIn = AIN0 y NegIn = AIN1
			SetPosIn(CANAL0_POS_IN);	//Seteamos la entrada positiva
			SetNegIn(CANAL0_NEG_IN); //Seteamos la entrada negativa
			break;
		case CANAL_1:	//El canal uno es PosIn = AIN2 y NegIn = AIN3
			//SetPosIn(AIN2);	//Seteamos la entrada positiva
			//SetNegIn(AIN3); //Seteamos la entrada negativa
			SetPosIn(CANAL1_POS_IN);	//Seteamos la entrada positiva
			SetNegIn(CANAL1_NEG_IN); //Seteamos la entrada negativa
			break;
	}
	ADC.canal = canal;
} //Fin SetFuenteConv

/*Función SetVBias------------------------------------------------------------------------------------------------------------------------
Descripción: función que configura las tensiones de polarización (AVDD-AVSS)/2 aplicadas a las entradas
Entrada:
		RefInt: código que simboliza la entrada sobre la que se quiere aplicar la tensión de polarización
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetVBias(unsigned char entradaVBias)
{
	unsigned char dato;
	
	SelecADC(); //Seleccionamos (mediante el CS) el ADC para comunicación SPI
	dato = ReadRegADC(VBIAS);	//Leemos el registro desde el ADC
	dato = dato | entradaVBias;	//Seteamos el nuevo valor
	WriteRegADC(VBIAS, dato);	//Escribimos el nuevo valor en el registro
	DeselecADC(); 	//Deseleccionamos (mediante el CS) el ADC para comunicación SPI 
	
} //Fin SetVBias

/*Función ConfRefInt------------------------------------------------------------------------------------------------------------------------
Descripción: función que configura la referencia interna del ADC
Entrada:
		RefInt: código que simboliza la configuración deseada para la referencia interna
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ConfRefInt(unsigned char RefInt)
{
	unsigned char dato;
	
	SelecADC(); //Seleccionamos (mediante el CS) el ADC para comunicación SPI
	dato = ReadRegADC(MUX1);	//Leemos el registro desde el ADC
	dato = dato & 0b10011111;	//Limpiamos la información que había antes sobre lo que nos interesa cambiar
	dato = dato | (RefInt << 5);	//Seteamos el nuevo valor
	WriteRegADC(MUX1, dato);	//Escribimos el nuevo valor en el registro
	DeselecADC(); 	//Deseleccionamos (mediante el CS) el ADC para comunicación SPI 
	
} //Fin ConfRefInt

/*Función SetRef------------------------------------------------------------------------------------------------------------------------
Descripción: función que setea la referencia para el ADC
Entrada:
		Ref: código que simboliza la configuración deseada para la referencia del ADC
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetRef(unsigned char Ref)
{
	unsigned char dato;
	
	SelecADC(); //Seleccionamos (mediante el CS) el ADC para comunicación SPI
	dato = ReadRegADC(MUX1);	//Leemos el registro desde el ADC
	dato = dato & 0b11100111;	//Limpiamos la información que había antes sobre lo que nos interesa cambiar
	dato = dato | (Ref << 3);	//Seteamos el nuevo valor
	WriteRegADC(MUX1, dato);	//Escribimos el nuevo valor en el registro
	DeselecADC(); 	//Deseleccionamos (mediante el CS) el ADC para comunicación SPI 
	
} //Fin SetRef

/*Función SetSystemMonitor------------------------------------------------------------------------------------------------------------------------
Descripción: función que setea el monitor del sistema (modo de operación) del ADC
Entrada:
		Ref: código que simboliza el modo de operación deseado
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetSystemMonitor(unsigned char estadoSysMon)
{
	unsigned char dato;
	
	SelecADC(); //Seleccionamos (mediante el CS) el ADC para comunicación SPI
	dato = ReadRegADC(MUX1);	//Leemos el registro desde el ADC
	dato = dato & 0b11111000;	//Limpiamos la información que había antes sobre lo que nos interesa cambiar
	dato = dato | estadoSysMon;	//Seteamos el nuevo valor
	WriteRegADC(MUX1, dato);	//Escribimos el nuevo valor en el registro
	DeselecADC(); 	//Deseleccionamos (mediante el CS) el ADC para comunicación SPI 
	
	ADC.estadoSysMon = estadoSysMon;	//Guardamos cual es el estado del System Monitor
	
} //Fin SetSystemMonitor

/*Función SetPGAGain------------------------------------------------------------------------------------------------------------------------
Descripción: función que setea la ganancia del PGA interno del ADC
Entrada:
		Ref: código que simboliza la ganancia que se desea setear
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetPGAGain(unsigned char gain)
{
	unsigned char dato;
	
	SelecADC(); //Seleccionamos (mediante el CS) el ADC para comunicación SPI
	dato = ReadRegADC(SYS0);	//Leemos el registro desde el ADC
	dato = dato & 0b00001111;	//Limpiamos la información que había antes sobre lo que nos interesa cambiar
	dato = dato | (gain << 4);	//Seteamos el nuevo valor
	WriteRegADC(SYS0, dato);	//Escribimos el nuevo valor en el registro
	DeselecADC(); 	//Deseleccionamos (mediante el CS) el ADC para comunicación SPI 
	
} //Fin SetPGAGain

/*Función SetFrecMuestreo------------------------------------------------------------------------------------------------------------------------
Descripción: función que setea la frecuencia de muestreo del ADC en modo continuo
Entrada:
		Ref: código que simboliza la frecuencia de muestreo que se desea setear
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetFrecMuestreo(unsigned char frec)
{
	unsigned char dato;
	
	SelecADC(); //Seleccionamos (mediante el CS) el ADC para comunicación SPI
	dato = ReadRegADC(SYS0);	//Leemos el registro desde el ADC
	dato = dato & 0b01110000;	//Limpiamos la información que había antes sobre lo que nos interesa cambiar
	dato = dato | frec;	//Seteamos el nuevo valor
	WriteRegADC(SYS0, dato);	//Escribimos el nuevo valor en el registro
	DeselecADC(); 	//Deseleccionamos (mediante el CS) el ADC para comunicación SPI 
	
} //Fin SetFrecMuestreo

/*Función SetIDACCurrent------------------------------------------------------------------------------------------------------------------------
Descripción: función que setea el valor de la corriente de salida de las fuentes de corriente internas de ADC
Entrada:
		Ref: código que simboliza corriente de salida
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetIDACCurrent(unsigned char current)
{
	unsigned char dato;
	
	SelecADC(); //Seleccionamos (mediante el CS) el ADC para comunicación SPI
	dato = ReadRegADC(IDAC0);	//Leemos el registro desde el ADC
	dato = dato & 0b11111000;	//Limpiamos la información que había antes sobre lo que nos interesa cambiar
	dato = dato | current;	//Seteamos el nuevo valor
	WriteRegADC(IDAC0, dato);	//Escribimos el nuevo valor en el registro
	DeselecADC(); 	//Deseleccionamos (mediante el CS) el ADC para comunicación SPI 
	
} //Fin SetIDACCurrent

/*Función SetIDAC1Out------------------------------------------------------------------------------------------------------------------------
Descripción: función que setea el pin de salida al cual se va a aplicar la corriente de IDAC1
Entrada:
		Ref: código que simboliza el pin de salida
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetIDAC1Out(unsigned char pin)
{
	unsigned char dato;
	
	SelecADC(); //Seleccionamos (mediante el CS) el ADC para comunicación SPI
	dato = ReadRegADC(IDAC1);	//Leemos el registro desde el ADC
	dato = dato & 0b00001111;	//Limpiamos la información que había antes sobre lo que nos interesa cambiar
	dato = dato | (pin << 4);	//Seteamos el nuevo valor
	WriteRegADC(IDAC1, dato);	//Escribimos el nuevo valor en el registro
	DeselecADC(); 	//Deseleccionamos (mediante el CS) el ADC para comunicación SPI 
	
} //Fin SetIDAC1Out

/*Función SetIDAC2Out------------------------------------------------------------------------------------------------------------------------
Descripción: función que setea el pin de salida al cual se va a aplicar la corriente de IDAC2
Entrada:
		Ref: código que simboliza el pin de salida
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetIDAC2Out(unsigned char pin)
{
	unsigned char dato;
	
	SelecADC(); //Seleccionamos (mediante el CS) el ADC para comunicación SPI
	dato = ReadRegADC(IDAC1);	//Leemos el registro desde el ADC
	dato = dato & 0b11110000;	//Limpiamos la información que había antes sobre lo que nos interesa cambiar
	dato = dato | pin;	//Seteamos el nuevo valor
	WriteRegADC(IDAC1, dato);	//Escribimos el nuevo valor en el registro
	DeselecADC(); 	//Deseleccionamos (mediante el CS) el ADC para comunicación SPI 
	
} //Fin SetIDAC2Out

/*Función LeerRegistrosADC------------------------------------------------------------------------------------------------------------------------
Descripción: función que lee todos los registros del ADC y los guarda en vecAux[]
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void LeerRegistrosADC(void)
{
	/*SelecADC();
	ReadRegsADC(MUX0, 15);
	START_PIN = 1;
	vecAux[0] = ReadSpiADC();	
	vecAux[1] = ReadSpiADC();
	vecAux[2] = ReadSpiADC();
	vecAux[3] = ReadSpiADC();
	vecAux[4] = ReadSpiADC();
	vecAux[5] = ReadSpiADC();
	vecAux[6] = ReadSpiADC();
	vecAux[7] = ReadSpiADC();
	vecAux[8] = ReadSpiADC();
	vecAux[9] = ReadSpiADC();
	vecAux[10] = ReadSpiADC();
	vecAux[11] = ReadSpiADC();
	vecAux[12] = ReadSpiADC();
	vecAux[13] = ReadSpiADC();
	vecAux[14] = ReadSpiADC();
	
	*((unsigned char *) &offsetADC + 1) = (unsigned char) vecAux[6];
	*((unsigned char *) &offsetADC + 0) = (unsigned char) vecAux[5];
	
	*((unsigned char *) &gainADC + 1) = (unsigned char) vecAux[9];
	*((unsigned char *) &gainADC + 0) = (unsigned char) vecAux[8];

	START_PIN = 0;
	DeselecADC();*/
} //Fin LeerRegistrosADC

/*Función GetOffset------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que lee el offset del ADC
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void GetOffset()
{
	ConfRefInt(ALWAYS_ON);	//Enciendo la referencia interna
	SetRef(REF_INT);	//Selecciono la referencia interna
	SetSystemMonitor(OFFSET); //Seteamos el valor del MUXCAL[2:0] a '011' para obtener la temperatura.
	TomarMuestra();	//Ordenamos la toma de la muestra de temperatura ambiente
} //Fin GetOffset
	
/*Función CalibrarADC------------------------------------------------------------------------------------------------------------------------
Descripción: función que mide el offset del ADC
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void CalibrarADC(void)
{
	unsigned char i;
	//La calibración Interna siempre se lleva a cabo, no importando el valor de bModoConecDir
	ADC.bLibre = 0;	//Bloqueamos el ADC hasta que se termine la calibración
	ADC.bCalibrando = 1;	//Indicamos que el ADS1147 se encuentra en proceso de calibración
	ADC.timeout	= TIMEOUT_CALIB_INTER; //Fijamos un timeout (tiempo límite) para el proceso de calibración
	
	/////////////////////////////
	/*SetSystemMonitor(NORMAL); //Seteamos el valor del MUXCAL[2:0] a '011' para obtener la temperatura.
	ConfRefInt(ALWAYS_ON);	//Enciendo la referencia interna
	SetRef(REF0);	//Selecciono la referencia interna
	SetFuenteConv(CANAL_0);
	SetIDAC1Out(IDAC_AIN0);
	SetIDAC2Out(IDAC_AIN1);
	SetIDACCurrent(IDAC_250U);
	Delay10KTCYx(1);	//Espero 1.64 mseg hasta que la referencia se setee al 0.1%*/
	/////////////////////////////
	
	SelecADC(); //Selecciona (mediante el CS) el ADC para comunicación SPI
	//-+-+*SelfOCalADC(); //Ejecutamos una calibración interna del ADC
	ADC.bMuestreando = 1;	//Indico que el ADC está en proceso de muestreo
	ADC.bMuestraLista = 0;	//Todavía no se ha tomado ninguna muestra
	DeselecADC(); //Deseleccionamos (mediante el CS) el ADC para comunicación SPI 
	
} //Fin CalibrarADC()
	
/*Función GetTempAmb------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que lee la temperatura ambiente desde el ADS1147 y almacena el resultado en ADC.temperature
							Temperatura en grados Celsius (118mV a +25ºC y un coef. de 405uV/ºC, con un PGA = '1')
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void GetTempAmb()
{
	ConfRefInt(ALWAYS_ON);	//Enciendo la referencia interna
	SetRef(REF_INT);	//Selecciono la referencia interna
	SetSystemMonitor(TEMPERATURE); //Seteamos el valor del MUXCAL[2:0] a '011' para obtener la temperatura.
	DelayTcy(10000);	//Delay10KTCYx(1);	//Espero 1.64 mseg hasta que la referencia se setee al 0.1%
	CalibrarADC();	//Calibramos para obtener mejores resultados
	//TomarMuestra();	//Ordenamos la toma de la muestra de temperatura ambiente
} //Fin GetTempAmb

/*Función InicConversorAD------------------------------------------------------------------------------------------------------------------------
Descripción: función que inicializa el conversor AD
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void InicConversorAD(void)
{
	//Configuramos el módulo MSSP para trabajar como SPI. Para el correcto funcionamiento con el ADS1147, debe ser CKE = 0
	/*SSP1STAT = 0b00000000;
	SSP1CON1 = 0b00100000;
	
	//Configuramos el puerto SPI y los pines de control del ADC
	TRIS_CS_PIN	=	0;	//Chip Select del ADC
	CS_ADC_PIN = 1;
	TRIS_DIN_PIN	= 1;	//Data In
	TRIS_DOUT_PIN	= 0;	//Data Out
	DOUT_PIN = 0;
	TRIS_SCK_PIN	= 0;	//Clock
	SCK_PIN	= 0;
	TRIS_START_PIN = 0;	//START
	START_PIN	= 0;	
	TRIS_DRDY_PIN	=	1;
	DRDY_IE = 0;	//Deshabilito temporalmente esta interrupción
	DRDY_IP = 0; //Asigno prioridad baja de interrupción a DRDY
	DRDY_EDGE	= 0; //Interrupción por flanco descendente para DRDY
	TRIS_RESET_PIN = 0;
	RESET_PIN = 1;	//Lo ponemos en estado no reseteado
	
	//Inicialización de flags
	ADC.bMuestreando = 0;	
	ADC.bMuestraLista = 0;
	ADC.bValorListo = 0;
	ADC.bLibre = 1;	
	ADC.bCalibrando = 0;
	ADC.bCalibInter = 0;
	ADC.bErrorTimeout = 0;
	
	ADC.nroMuestras = 1;	//Seteamos el número de muestras a 1 por defecto
	
	//Reseteamos el ADC
	RESET_PIN = 0;
	Delay10TCYx(10);	//Esperamos 32.8 useg
	RESET_PIN = 1;
	Delay10KTCYx(255);	//Esperamos 0.418 mseg
	Delay10KTCYx(255);	//Esperamos otros 0.196 mseg más

	///////////////
	Nop();
	LeerRegistrosADC();
	Nop();
	///////////////
	
	//Detenemos el modo de muestreo continuo
	SelecADC();	//Seleccionamos el ADC mediante el chip select
	Delay10TCYx(1);
	StopReadContADC();	//Detenemos el muestreo continuo
	Delay10TCYx(1);
	SetPGAGain(GAIN_1);	//Seteamos la ganancia del PGA interno
	SetFrecMuestreo(SPS_10); //Seteamos la frecuencia de muestreo
	SetSystemMonitor(NORMAL); //Seteamos un estado por defecto para el System Monitor
	
	//ADC.valorTemp = 6;	//Cargamos el primer offset con el valor de la última vez que fue prendido el equipo
												//Esto se hace por si el valor de la conversión es mayor a 15 
	
	///////////////
	//Nop();
	//LeerRegistrosADC();
	//Nop();
	///////////////
	
	ConfRefInt(ALWAYS_ON);	//Enciendo la referencia interna
	SetRef(REF_INT);	//Selecciono la referencia interna
	CalibrarADC();	//Llamamos a la calibración del offset Interno
	
	///////////////
	//Nop();
	//LeerRegistrosADC();
	//Nop();
	///////////////
	
	DRDY_IF = 0; //Reseteo el flag por las dudas haya estado seteado
	DRDY_IE = 1;	//Habilito la interrupción del ADC
	START_PIN = 0;
	DeselecADC();	//Deseleccionamos el ADC mediante el chip select
	*/
} //Fin InicConversorAD



