#include "ADS1147.h"
//VECTORES DE OBJETOS
//#pragma udata Adquisicion = 0x600 // Cada bloque de RAM tiene 256 bytes

//Variables
volatile struct ADConverter adc;
INT16U backUpSPISTAT;	//Variables para salvar temporalmente el estado de este reg y luego restaurarlo
INT16U backUpSPICON1;	//Variables para salvar temporalmente el estado de este reg y luego restaurarlo
//INT16U backUpSPICON2;	//Variables para salvar temporalmente el estado de este reg y luego restaurarlo

//#pragma udata // udata = Variables no inicializadas

INT8U	vecAux[15];

/*Funci�n WriteRegADC------------------------------------------------------------------------------------------------------------------------
Descripci�n: Escribe un solo byte hacia el Bus SPI1.
Entrada: un byte de dato para escribir en el Bus SPI1
Salida: el byte de estado para la deteccion del WCOL
//-------------------------------------------------------------------------------------------------------------------------------------*/
unsigned char WriteSpiADC( unsigned char data_out )
{
	unsigned char TempVar;  

	DelayTcy(100);	//Esperamos aprox. 2.5useg

  backUpSPISTAT = SPISTAT;	//Salvamos el registro SSPSTAT
  backUpSPICON1 = SPICON1;	//Salvamos el registro SSPCON1
	//backUpSPICON2 = SPICON2;	//Salvamos el registro SSPCON1

  //Configuramos el SPI para comunicarse con el ADC
	SPISMP = 0;	//Input data sampled at middle of data output time
	SPICKE = 0;	//Serial output data changes on transition from Idle clock state to active clock state
	SPICKP = 0; //Idle state for clock is a low level; active state is a high level
	SPIEN	= 1;	//Habilitamos el SPI
  TempVar = SPIBUF;           // Clears BF
  SPIIF = 0;         // Clear interrupt flag

  SPIBUF = data_out;          // write byte to SPIBUF register
  while( !SPIRBF ); // wait until bus cycle complete

  SPISTAT = backUpSPISTAT;	//Restauramos el registro SSPSTAT
  SPICON1 = backUpSPICON1;	//Restauramos el registro SSPCON1

	DelayTcy(100);	//Esperamos aprox. 2.5useg

  return ( 0 );                // if WCOL bit is not set return non-negative#
	
}//Fin WriteSpiADC()

/*Funci�n ReadSpiADC------------------------------------------------------------------------------------------------------------------------
Descripci�n: Lee un solo byte desde el Bus SPI1.
Entrada: nada
Salida: el contenido del registro SSP1BUF
//-------------------------------------------------------------------------------------------------------------------------------------*/
unsigned char ReadSpiADC( void )
{
  unsigned char TempVar;

	DelayTcy(100);	//Esperamos aprox. 2.5useg

 	backUpSPISTAT = SPISTAT;	//Salvamos el registro SSPSTAT
  backUpSPICON1 = SPICON1;	//Salvamos el registro SSPCON1
	//backUpSPICON2 = SPICON2;	//Salvamos el registro SSPCON1

  //Configuramos el SPI para comunicarse con el ADC
	SPISMP = 0;	//Input data sampled at middle of data output time
	SPICKE = 0;	//Serial output data changes on transition from Idle clock state to active clock state
	SPICKP = 0; //Idle state for clock is a low level; active state is a high level
	SPIEN	= 1;	//Habilitamos el SPI
  TempVar = SPIBUF;           // Clears BF
  SPIIF = 0;         // Clear interrupt flag

  SPIBUF = 0xFF;          // initiate bus cycle
  while( !SPIRBF ); // wait until bus cycle complete

  SPISTAT = backUpSPISTAT;	//Restauramos el registro SSPSTAT
  SPICON1 = backUpSPICON1;	//Restauramos el registro SSPCON1

	DelayTcy(100);	//Esperamos aprox. 2.5useg

  return ( SPIBUF );      // return with byte read 
}//Fin ReadSpiADC()

/*Funci�n WriteRegADC------------------------------------------------------------------------------------------------------------------------
Descripci�n: escribe el registro reg del ADC con el valor dato
Entrada:
	reg: n�mero de registro a escribir
	dato: dato a escribir en reg
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void WriteRegADC(unsigned char reg, unsigned char dato)
{
	START_PIN = 1;
	WriteSpiADC(0x40 | reg);	//Enviamos el c�digo de escritura de registros (0x40) y el registro inicial reg
	WriteSpiADC(0);	//Indicamos que vamos a escribir solo 1 registro
	WriteSpiADC(dato);	//Enviamos el dato que queremos que se escriba en el registro
	START_PIN = 0;
}//Fin WriteRegADC()

/*Funci�n WriteRegsADC------------------------------------------------------------------------------------------------------------------------
Descripci�n: Env�a un comando al ADC para habilitar la escritura de n registros consecutivos a partir de reg (permite escritura por bloques)
Entrada:
	reg: n�mero de registro a partir del cual se quiere escribir
	n: n�mero de registros a escribir
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void WriteRegsADC(unsigned char reg, unsigned char n)
{
	START_PIN = 1;
	n--; //Decrementamos esta variable porque al ADC debemos pasarle el n�mero de registros menos 1
	WriteSpiADC(0x40 | reg);	//Enviamos el c�digo de escritura de registros (0x40) y el registro inicial reg
	WriteSpiADC(n);	//Enviamos la cantidad de registros que deseamos escribir
	START_PIN = 0;
}//Fin WriteRegsADC()

/*Funci�n ReadRegADC------------------------------------------------------------------------------------------------------------------------
Descripci�n: lee el registro reg desde el ADC y lo devuelve
Entrada:
	reg: n�mero de registro a leer
Salida: el contenido del registro reg
//-------------------------------------------------------------------------------------------------------------------------------------*/
unsigned char ReadRegADC(unsigned char reg)
{
	START_PIN = 1;
	WriteSpiADC(0x20 | reg);	//Enviamos el c�digo de lectura de registros (0x20) y el registro inicial reg
	WriteSpiADC(0);	//Indicamos que vamos a leer solo 1 registro
	START_PIN = 0;
	return (ReadSpiADC());	//Esperamos el valor devuelto por el ADC
}//Fin ReadRegADC()

/*Funci�n ReadRegsADC------------------------------------------------------------------------------------------------------------------------
Descripci�n: Env�a un comando al ADC para habilitar la lectura de n registros consecutivos a partir de reg (permite lectura por bloques)
Entrada:
	reg: n�mero de registro a partir del cual se quiere leer
	n: n�mero de registros a leer
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ReadRegsADC(unsigned char reg, unsigned char n)
{
	START_PIN = 1;
	n--; //Decrementamos esta variable porque al ADC debemos pasarle el n�mero de registros menos 1
	WriteSpiADC(0x20 | reg);	//Enviamos el c�digo de lectura de registros (0x20) y el registro inicial reg
	WriteSpiADC(n);	//Enviamos la cantidad de registros que deseamos leer
	START_PIN = 0;
}//Fin ReadRegsADC()

/*Funci�n IniciarMuestra------------------------------------------------------------------------------------------------------------------------
Descripci�n: funci�n que inicia la conversi�n de una nueva muestra enviando un breve pulso de START al ADS1147
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void IniciarMuestra(void)
{
	SelecADC(); 		//Seleccionamos (mediante el CS) el ADC para comunicaci�n SPI
	START_PIN = 1;	//Lanzamos la conversi�n poniendo STAR_PIN en 1
	DelayTcy(1);			//Delay10TCYx(1);	//Hacemos una peque�a demora para que el cambio de estado sea reconocido por el ADC
	START_PIN = 0;	//Volvemos STAR_PIN a 0
	DeselecADC(); 	//Deseleccionamos (mediante el CS) el ADC para comunicaci�n SPI 
} //Fin IniciarMuestra

/*Funci�n TomarMuestra------------------------------------------------------------------------------------------------------------------------
Descripci�n: funci�n que adquiere "nroMuestras" parciales y guarda el promedio de las mismas en "valor"
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void TomarMuestra(void)
{
	adc.bValorListo = 0;	//Indicamos que el valor en "valor" ya no es v�lido
	adc.bMuestraLista = 0;	//Todav�a no se ha tomado ninguna muestra
	adc.contMuestras = 0;	//Reseteamos el contador de muestras
	adc.sumaMuestras = 0;	//Reseteamos la sumatoria
	adc.timeout	= TIMEOUT_MUESTREO; //Reseteamos el timeout	
	adc.bMuestreando = 1;	//Indico que el ADC est� en proceso de muestreo
	
	IniciarMuestra();	//Iniciar muestra enviando un pulso por START

} //Fin TomarMuestra

/*Funci�n LeerMuestraADC------------------------------------------------------------------------------------------------------------------------
Descripci�n: funci�n que pide al ADC que le env�e la muestra y la almacena en adc.valorTemp
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void LeerMuestraADC(void)
{
	SelecADC();
	START_PIN = 1;
	DelayTcy(100);	//Esperamos 32.8 useg
	ReadOnceADC();
	DelayTcy(100);	//Esperamos 32.8 useg
	*((unsigned char *) &adc.valorTemp + 1) = (unsigned char) ReadSpiADC();	//Obtenemos la parte alta de la conversi�n
	*((unsigned char *) &adc.valorTemp + 0) = (unsigned char) ReadSpiADC();	//Obtenemos la parte baja de la conversi�n
	START_PIN = 0;
	DeselecADC();
} //Fin LeerMuestraADC

/*Funci�n SetBurnOutCurrent------------------------------------------------------------------------------------------------------------------------
Descripci�n: funci�n que setea la corriente de prueba para saber si el sensor est� ausente o quemado
Entrada:
		burnOutCurrent: c�digo que simboliza la corriente de BurnOut que se quiere setear
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetBurnOutCurrent(unsigned char burnOutCurrent)
{
	unsigned char dato;
	
	SelecADC(); //Seleccionamos (mediante el CS) el ADC para comunicaci�n SPI
	dato = ReadRegADC(MUX0);	//Leemos el registro desde el ADC
	dato = dato & 0b00111111;	//Limpiamos la informaci�n que hab�a antes sobre lo que nos interesa cambiar
	dato = dato | (burnOutCurrent << 6);	//Seteamos el nuevo valor
	WriteRegADC(MUX0, dato);	//Escribimos el nuevo valor en el registro
	DeselecADC(); 	//Deseleccionamos (mediante el CS) el ADC para comunicaci�n SPI 
	
} //Fin SetBurnOutCurrent

/*Funci�n SetPosIn------------------------------------------------------------------------------------------------------------------------
Descripci�n: funci�n que setea la entrada positiva para la conversi�n
Entrada:
		PosIn: c�digo que simboliza la entrada positiva
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetPosIn(unsigned char PosIn)
{
	unsigned char dato;
	
	SelecADC(); //Seleccionamos (mediante el CS) el ADC para comunicaci�n SPI
	dato = ReadRegADC(MUX0);	//Leemos el registro desde el ADC
	dato = dato & 0b11000111;	//Limpiamos la informaci�n que hab�a antes sobre lo que nos interesa cambiar
	dato = dato | (PosIn << 3);	//Seteamos el nuevo valor
	WriteRegADC(MUX0, dato);	//Escribimos el nuevo valor en el registro
	DeselecADC(); 	//Deseleccionamos (mediante el CS) el ADC para comunicaci�n SPI 
	
} //Fin SetPosIn

/*Funci�n SetNegIn------------------------------------------------------------------------------------------------------------------------
Descripci�n: funci�n que setea la entrada negativa para la conversi�n
Entrada:
		NegIn: c�digo que simboliza la entrada negativa
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetNegIn(unsigned char NegIn)
{
	unsigned char dato;
	
	SelecADC(); //Seleccionamos (mediante el CS) el ADC para comunicaci�n SPI
	dato = ReadRegADC(MUX0);	//Leemos el registro desde el ADC
	dato = dato & 0b11111000;	//Limpiamos la informaci�n que hab�a antes sobre lo que nos interesa cambiar
	dato = dato | NegIn;	//Seteamos el nuevo valor
	WriteRegADC(MUX0, dato);	//Escribimos el nuevo valor en el registro
	DeselecADC(); 	//Deseleccionamos (mediante el CS) el ADC para comunicaci�n SPI 
	
} //Fin SetNegIn

/*Funci�n SetFuenteConv------------------------------------------------------------------------------------------------------------------------
Descripci�n: funci�n que setea el canal que el ADC usar� para realizar la adquisici�n
Entrada:
		canal: entero que representa el canal desde donde se hace la adquisici�n
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
	adc.canal = canal;
} //Fin SetFuenteConv

/*Funci�n SetVBias------------------------------------------------------------------------------------------------------------------------
Descripci�n: funci�n que configura las tensiones de polarizaci�n (AVDD-AVSS)/2 aplicadas a las entradas
Entrada:
		RefInt: c�digo que simboliza la entrada sobre la que se quiere aplicar la tensi�n de polarizaci�n
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetVBias(unsigned char entradaVBias)
{
	unsigned char dato;
	
	SelecADC(); //Seleccionamos (mediante el CS) el ADC para comunicaci�n SPI
	dato = ReadRegADC(VBIAS);	//Leemos el registro desde el ADC
	dato = dato | entradaVBias;	//Seteamos el nuevo valor
	WriteRegADC(VBIAS, dato);	//Escribimos el nuevo valor en el registro
	DeselecADC(); 	//Deseleccionamos (mediante el CS) el ADC para comunicaci�n SPI 
	
} //Fin SetVBias

/*Funci�n ConfRefInt------------------------------------------------------------------------------------------------------------------------
Descripci�n: funci�n que configura la referencia interna del ADC
Entrada:
		RefInt: c�digo que simboliza la configuraci�n deseada para la referencia interna
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ConfRefInt(unsigned char RefInt)
{
	unsigned char dato;
	
	SelecADC(); //Seleccionamos (mediante el CS) el ADC para comunicaci�n SPI
	dato = ReadRegADC(MUX1);	//Leemos el registro desde el ADC
	dato = dato & 0b10011111;	//Limpiamos la informaci�n que hab�a antes sobre lo que nos interesa cambiar
	dato = dato | (RefInt << 5);	//Seteamos el nuevo valor
	WriteRegADC(MUX1, dato);	//Escribimos el nuevo valor en el registro
	DeselecADC(); 	//Deseleccionamos (mediante el CS) el ADC para comunicaci�n SPI 
	
} //Fin ConfRefInt

/*Funci�n SetRef------------------------------------------------------------------------------------------------------------------------
Descripci�n: funci�n que setea la referencia para el ADC
Entrada:
		Ref: c�digo que simboliza la configuraci�n deseada para la referencia del ADC
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetRef(unsigned char Ref)
{
	unsigned char dato;
	
	SelecADC(); //Seleccionamos (mediante el CS) el ADC para comunicaci�n SPI
	dato = ReadRegADC(MUX1);	//Leemos el registro desde el ADC
	dato = dato & 0b11100111;	//Limpiamos la informaci�n que hab�a antes sobre lo que nos interesa cambiar
	dato = dato | (Ref << 3);	//Seteamos el nuevo valor
	WriteRegADC(MUX1, dato);	//Escribimos el nuevo valor en el registro
	DeselecADC(); 	//Deseleccionamos (mediante el CS) el ADC para comunicaci�n SPI 
	
} //Fin SetRef

/*Funci�n SetSystemMonitor------------------------------------------------------------------------------------------------------------------------
Descripci�n: funci�n que setea el monitor del sistema (modo de operaci�n) del ADC
Entrada:
		Ref: c�digo que simboliza el modo de operaci�n deseado
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetSystemMonitor(unsigned char estadoSysMon)
{
	unsigned char dato;
	
	SelecADC(); //Seleccionamos (mediante el CS) el ADC para comunicaci�n SPI
	dato = ReadRegADC(MUX1);	//Leemos el registro desde el ADC
	dato = dato & 0b11111000;	//Limpiamos la informaci�n que hab�a antes sobre lo que nos interesa cambiar
	dato = dato | estadoSysMon;	//Seteamos el nuevo valor
	WriteRegADC(MUX1, dato);	//Escribimos el nuevo valor en el registro
	DeselecADC(); 	//Deseleccionamos (mediante el CS) el ADC para comunicaci�n SPI 
	
	adc.estadoSysMon = estadoSysMon;	//Guardamos cual es el estado del System Monitor
	
} //Fin SetSystemMonitor

/*Funci�n SetPGAGain------------------------------------------------------------------------------------------------------------------------
Descripci�n: funci�n que setea la ganancia del PGA interno del ADC
Entrada:
		Ref: c�digo que simboliza la ganancia que se desea setear
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetPGAGain(unsigned char gain)
{
	unsigned char dato;
	
	SelecADC(); //Seleccionamos (mediante el CS) el ADC para comunicaci�n SPI
	dato = ReadRegADC(SYS0);	//Leemos el registro desde el ADC
	dato = dato & 0b00001111;	//Limpiamos la informaci�n que hab�a antes sobre lo que nos interesa cambiar
	dato = dato | (gain << 4);	//Seteamos el nuevo valor
	WriteRegADC(SYS0, dato);	//Escribimos el nuevo valor en el registro
	DeselecADC(); 	//Deseleccionamos (mediante el CS) el ADC para comunicaci�n SPI 
	
} //Fin SetPGAGain

/*Funci�n SetFrecMuestreo------------------------------------------------------------------------------------------------------------------------
Descripci�n: funci�n que setea la frecuencia de muestreo del ADC en modo continuo
Entrada:
		Ref: c�digo que simboliza la frecuencia de muestreo que se desea setear
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetFrecMuestreo(unsigned char frec)
{
	unsigned char dato;
	
	SelecADC(); //Seleccionamos (mediante el CS) el ADC para comunicaci�n SPI
	dato = ReadRegADC(SYS0);	//Leemos el registro desde el ADC
	dato = dato & 0b01110000;	//Limpiamos la informaci�n que hab�a antes sobre lo que nos interesa cambiar
	dato = dato | frec;	//Seteamos el nuevo valor
	WriteRegADC(SYS0, dato);	//Escribimos el nuevo valor en el registro
	DeselecADC(); 	//Deseleccionamos (mediante el CS) el ADC para comunicaci�n SPI 
	
} //Fin SetFrecMuestreo

/*Funci�n SetIDACCurrent------------------------------------------------------------------------------------------------------------------------
Descripci�n: funci�n que setea el valor de la corriente de salida de las fuentes de corriente internas de ADC
Entrada:
		Ref: c�digo que simboliza corriente de salida
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetIDACCurrent(unsigned char current)
{
	unsigned char dato;
	
	SelecADC(); //Seleccionamos (mediante el CS) el ADC para comunicaci�n SPI
	dato = ReadRegADC(IDAC0);	//Leemos el registro desde el ADC
	dato = dato & 0b11111000;	//Limpiamos la informaci�n que hab�a antes sobre lo que nos interesa cambiar
	dato = dato | current;	//Seteamos el nuevo valor
	WriteRegADC(IDAC0, dato);	//Escribimos el nuevo valor en el registro
	DeselecADC(); 	//Deseleccionamos (mediante el CS) el ADC para comunicaci�n SPI 
	
} //Fin SetIDACCurrent

/*Funci�n SetIDAC1Out------------------------------------------------------------------------------------------------------------------------
Descripci�n: funci�n que setea el pin de salida al cual se va a aplicar la corriente de IDAC1
Entrada:
		Ref: c�digo que simboliza el pin de salida
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetIDAC1Out(unsigned char pin)
{
	unsigned char dato;
	
	SelecADC(); //Seleccionamos (mediante el CS) el ADC para comunicaci�n SPI
	dato = ReadRegADC(IDAC1);	//Leemos el registro desde el ADC
	dato = dato & 0b00001111;	//Limpiamos la informaci�n que hab�a antes sobre lo que nos interesa cambiar
	dato = dato | (pin << 4);	//Seteamos el nuevo valor
	WriteRegADC(IDAC1, dato);	//Escribimos el nuevo valor en el registro
	DeselecADC(); 	//Deseleccionamos (mediante el CS) el ADC para comunicaci�n SPI 
	
} //Fin SetIDAC1Out

/*Funci�n SetIDAC2Out------------------------------------------------------------------------------------------------------------------------
Descripci�n: funci�n que setea el pin de salida al cual se va a aplicar la corriente de IDAC2
Entrada:
		Ref: c�digo que simboliza el pin de salida
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetIDAC2Out(unsigned char pin)
{
	unsigned char dato;
	
	SelecADC(); //Seleccionamos (mediante el CS) el ADC para comunicaci�n SPI
	dato = ReadRegADC(IDAC1);	//Leemos el registro desde el ADC
	dato = dato & 0b11110000;	//Limpiamos la informaci�n que hab�a antes sobre lo que nos interesa cambiar
	dato = dato | pin;	//Seteamos el nuevo valor
	WriteRegADC(IDAC1, dato);	//Escribimos el nuevo valor en el registro
	DeselecADC(); 	//Deseleccionamos (mediante el CS) el ADC para comunicaci�n SPI 
	
} //Fin SetIDAC2Out

/*Funci�n LeerRegistrosADC------------------------------------------------------------------------------------------------------------------------
Descripci�n: funci�n que lee todos los registros del ADC y los guarda en vecAux[]
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void LeerRegistrosADC(void)
{
	SelecADC();
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
	
	*((unsigned char *) &adc.offsetADC + 1) = (unsigned char) vecAux[6];
	*((unsigned char *) &adc.offsetADC + 0) = (unsigned char) vecAux[5];
	
	*((unsigned char *) &adc.gainADC + 1) = (unsigned char) vecAux[9];
	*((unsigned char *) &adc.gainADC + 0) = (unsigned char) vecAux[8];

	START_PIN = 0;
	DeselecADC();
} //Fin LeerRegistrosADC

/*Funci�n GetOffset------------------------------------------------------------------------------------------------------------------------
Descripci�n: 	funci�n que lee el offset del ADC
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
	
/*Funci�n CalibrarADC------------------------------------------------------------------------------------------------------------------------
Descripci�n: funci�n que mide el offset del ADC
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void CalibrarADC(void)
{
	unsigned char i;
	//La calibraci�n Interna siempre se lleva a cabo, no importando el valor de bModoConecDir
	adc.bLibre = 0;	//Bloqueamos el ADC hasta que se termine la calibraci�n
	adc.bCalibrando = 1;	//Indicamos que el ADS1147 se encuentra en proceso de calibraci�n
	adc.timeout	= TIMEOUT_CALIB_INTER; //Fijamos un timeout (tiempo l�mite) para el proceso de calibraci�n
	
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
	
	SelecADC(); //Selecciona (mediante el CS) el ADC para comunicaci�n SPI
	//-+-+*SelfOCalADC(); //Ejecutamos una calibraci�n interna del ADC
	adc.bMuestreando = 1;	//Indico que el ADC est� en proceso de muestreo
	adc.bMuestraLista = 0;	//Todav�a no se ha tomado ninguna muestra
	DeselecADC(); //Deseleccionamos (mediante el CS) el ADC para comunicaci�n SPI 
	
} //Fin CalibrarADC()
	
/*Funci�n GetTempAmb------------------------------------------------------------------------------------------------------------------------
Descripci�n: 	funci�n que lee la temperatura ambiente desde el ADS1147 y almacena el resultado en adc.temperature
							Temperatura en grados Celsius (118mV a +25�C y un coef. de 405uV/�C, con un PGA = '1')
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

/*Funci�n InicConversorAD------------------------------------------------------------------------------------------------------------------------
Descripci�n: funci�n que inicializa el conversor AD
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void InicConversorAD(void)
{
	//Configuramos el m�dulo MSSP para trabajar como SPI. Para el correcto funcionamiento con el ADS1147, debe ser CKE = 0
	//SPISTAT = 0b00000000;
	//SPICON1 = 0b00100000;
	
	RPINR20bits.SDI1R = 0b10001;	//SDI conectado al RP17-RC1
	RPOR8bits.RP16R = 0b00111;	//SDO conectado al RP16-RC0
	RPOR9bits.RP18R = 0b01000;	//SDO conectado al RP18-RC2

	//Setear puertos como digitales
	AD1PCFGLbits.PCFG6 = 1;	//RC0 - SDO
	AD1PCFGLbits.PCFG7 = 1;	//RC1 - SDI
	AD1PCFGLbits.PCFG8 = 1;	//RC2 - SCK

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
	DRDY_IE = 0;	//Deshabilito temporalmente esta interrupci�n
	//DRDY_IP = 0; //Asigno prioridad baja de interrupci�n a DRDY
	//DRDY_EDGE	= 0; //Interrupci�n por flanco descendente para DRDY
	TRIS_RESET_PIN = 0;
	RESET_PIN = 1;	//Lo ponemos en estado no reseteado
	
	SPI1CON1bits.MSTEN = 1;
	//SPICON1bits.PPRE = 0b01;	//Preescaler primario de 4
	//SPICON1bits.SPRE = 0b001;	//Preescaler secundario de 1
	SPICON1bits.PPRE = 0b10;	//Preescaler primario de 4
	SPICON1bits.SPRE = 0b111;	//Preescaler secundario de 1

	//Inicializaci�n de flags
	adc.bMuestreando = 0;	
	adc.bMuestraLista = 0;
	adc.bValorListo = 0;
	adc.bLibre = 1;	
	adc.bCalibrando = 0;
	adc.bCalibInter = 0;
	adc.bErrorTimeout = 0;
	
	adc.nroMuestras = 1;	//Seteamos el n�mero de muestras a 1 por defecto
	
	//Reseteamos el ADC
	RESET_PIN = 0;
	DelayTcy(50000); //Delay10TCYx(10);	//Esperamos 32.8 useg
	RESET_PIN = 1;
	DelayTcy(50000); //Delay10KTCYx(255);	//Esperamos 0.418 mseg
	DelayTcy(50000); //Delay10KTCYx(255);	//Esperamos otros 0.196 mseg m�s

	///////////////
	//Nop();
	//LeerRegistrosADC();
	//Nop();
	///////////////
	
	//Detenemos el modo de muestreo continuo
	SelecADC();	//Seleccionamos el ADC mediante el chip select
	StopReadContADC();	//Detenemos el muestreo continuo
	SetPGAGain(GAIN_1);	//Seteamos la ganancia del PGA interno
	SetFrecMuestreo(SPS_10); //Seteamos la frecuencia de muestreo
	SetSystemMonitor(NORMAL); //Seteamos un estado por defecto para el System Monitor
	
	//adc.valorTemp = 6;	//Cargamos el primer offset con el valor de la �ltima vez que fue prendido el equipo
												//Esto se hace por si el valor de la conversi�n es mayor a 15 
	
	///////////////
	//Nop();
	//LeerRegistrosADC();
	//Nop();
	///////////////
	
	ConfRefInt(ALWAYS_ON);	//Enciendo la referencia interna
	SetRef(REF_INT);	//Selecciono la referencia interna
	CalibrarADC();	//Llamamos a la calibraci�n del offset Interno
	
	///////////////
	//Nop();
	//LeerRegistrosADC();
	//Nop();
	///////////////
	
	//DRDY_IF = 0; //Reseteo el flag por las dudas haya estado seteado
	DRDY_IE = 1;	//Habilito la interrupci�n del ADC
	START_PIN = 0;
	DeselecADC();	//Deseleccionamos el ADC mediante el chip select
	
} //Fin InicConversorAD



