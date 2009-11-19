/*=======================================================================
PROYECTO	:		Firmware del Medidor de Eficiencia
PRIMERA VERSION: 1.00.00								AUTOR(es): 	Bongiovanni Pablo
																										Guanuco Luis
																										Sans� Marco
																										Vassia Gonzalo
INICIO: 26-09-09												
=======================================================================*/

/*=======================================================================
MODULO: main
INICIO: 26-09-09
ULTIMA REVISION	: 26-09-09
COMENTARIO:  
=======================================================================*/


//INCLUDES
	#include "main.h"


//DECLARACION DE VARIABLES
	//Variables relativas al Salvado de Contexto
		volatile unsigned char SaveLowFSR0H;
		volatile unsigned char SaveLowFSR0L;
		volatile unsigned char SaveHiFSR0H;
		volatile unsigned char SaveHiFSR0L;

	//Variables de Teclado
		extern volatile unsigned char Columna;					//Variable que indica cual de las columnas (salidas) tiene que ser activada
		extern volatile unsigned char Aux_Col;					//Almacena temporalmente el n�mero de columna (salida) activada
		extern volatile unsigned char Aux_Fila;					//Almacena temporalmente el n�mero de fila (entrada) activada
		extern volatile unsigned char Verif_Antirreb;		//Contador de la cantidad de veces que una tecla debe ser detectada para ser tomada como v�lida
		extern volatile unsigned char Tecla_Temp;				//Almacena la tecla que se ha detectado en el flujo actual de la rutina
		extern volatile unsigned char Tecla_Actual;			//Almacena la tecla que se ha detectado en el flujo anterior de la rutina
		extern volatile unsigned char Tecla_Ultima;			//Almacena la �ltima tecla que fue presionada
		extern volatile unsigned char Tecla_Presionada;	//Almacena la tecla que est� siendo presionada y que ya a pasado la comprobaci�n antirrebote
	
	//Variables de Men�s
		extern volatile char *ptrMenuActual;
		extern volatile const char MenuPrinc[14][17];
		extern volatile char MenuSeleccionado; 

		extern volatile unsigned char Esperar_Para_Mostrar;

	//Variables relativas al procesamieto de datos
		extern volatile unsigned char UnidadVelTrac;		//Almacena la unidad de la velocidad de TRACCION
		extern volatile unsigned char DecenaVelTrac;		//Almacena la decena de la velocidad de TRACCION
		extern volatile unsigned char UnidadVelAvan;		//Almacena la unidad de la velocidad de TRACCION
		extern volatile unsigned char DecenaVelAvan;		//Almacena la decena de la velocidad de TRACCION
	
	//Variables de los sensores

		volatile unsigned char Indice_Buffer_Maq;
		volatile unsigned char Indice_Buffer_Trac;
		extern volatile int Timer_Inst_Trac[Cant_Tim_Inst];
		extern volatile int Timer_Inst_Maq[Cant_Tim_Inst];
		extern volatile unsigned char  Cant_Elem_Usados_Maq;
		extern volatile unsigned char  Cant_Elem_Usados_Trac;

		
	//Variables relativas a la Fuerza
		//extern volatile unsigned int BufferMuestras[Cant_Muest_Fuerza];
		//extern volatile unsigned int BufferFiltrado[Cant_Muest_Fuerza];
		extern volatile unsigned int *ptrBufferMuestras;
		extern volatile unsigned char i_RCF;
		extern volatile unsigned char i_ADCI;
		extern volatile unsigned char i_ADCI;
		extern volatile float	FuerzaPromedio;
		extern volatile unsigned long int SumatoriaFuerza;
		extern volatile float FuerzaInst;

	//Variables relativas al filtrado
		//extern fractional BufferMuestras[Cant_Muest_Fuerza];	//Buffer con las muestras tomadas desde el AD
		//extern FIRStruct FiltroFilter; 
		//fractional BufferFiltrado[Cant_Muest_Fuerza] ; //Buffer de Salida ya filtrado  
                                       
	//Variables de LCD
	//Variables de Generales
		volatile unsigned int Esperar;
	//Variables de Procesos/Rutinas
		struct VariablesDeProcesos Proc;
		//estructura de las banderas de los sensores
		struct Sensores Band_Sensor;		//inicializo la estructura



//DEFINICI�N DE FUNCIONES
	/*Funci�n Main-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Funci�n principal (hilo principal)
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
		int main(void)
		{   
			//Inicializaci�n de variables
				//Inicializaci�n de variables de Teclado
					Columna	=	0;			
					Tecla_Presionada = 0;
					Tecla_Actual = Tecla_No_Pres;

				//Inicializaci�n de variables de LCD
					Esperar_Para_Mostrar = Delay_Refresco;

				//Inicializaci�n de variables de Generales

				//Inicializaci�n de banderas del sensor
					Band_Sensor.Vel_Trac_Min  = 0;
					Band_Sensor.Vel_Maq_Min   = 0;
					Band_Sensor.Band_Trac = 0;
					Band_Sensor.Band_Maq = 0;
					Indice_Buffer_Maq = 0;
					Indice_Buffer_Trac = 0;
					Cant_Elem_Usados_Trac = 0;	
					Cant_Elem_Usados_Maq = 0;			
					Band_Sensor.Buffer_Completo_Trac = 0;
					Band_Sensor.Buffer_Completo_Maq = 0;
					
				//Inicializaci�n de variables de Procesos/Rutinas
					Proc.EjecRutMenu 		= 0;
					Proc.EjecRutTeclado = 0;
					Proc.EjecRutTeclas 	= 0;
					Proc.HabRutMenu 		= 1;
					Proc.HabRutSensores		= 1;
					Proc.HabRutCalFuerza 		= 1;
					Proc.HabRutTeclado 	= 1;
					Proc.HabRutTeclas 	= 1;
					Proc.ContEspMenu 		= CEMenu;
					Proc.ContEspTeclado	=	CETeclado;
					Proc.ContEspTeclas	=	CETeclas;


			//Configuraci�n de Perif�ricos
				//Configuraci�n del Timer1 (Asignado a )
					OpenTimer1(				T1_ON 
											& T1_GATE_OFF 
											& PrescalerT1 
											& T1_SYNC_EXT_OFF 
											&	T1_SOURCE_INT	//Origen interno del clock
											, PeriodoT1);
				//Configuraci�n del Timer2 (Asignado a )
					OpenTimer2(				T2_OFF 
											& T2_GATE_OFF 
											& PrescalerT2 
											&	T2_SOURCE_INT	//Origen interno del clock
											, PeriodoT2);
				//Configuraci�n del Timer3 (Asignado a )
					OpenTimer3(				T3_ON 
											& T3_GATE_OFF 
											& PrescalerT3 
											&	T3_SOURCE_INT	//Origen interno del clock
											, PeriodoT3);

				//Configuraci�n del Timer4 (Asignado a sensor 1 )
					OpenTimer4(				T4_ON 
											& T4_GATE_OFF 
											& PrescalerT4 
											&	T4_SOURCE_INT	//Origen interno del clock
											, PeriodoT4);
				//Configuraci�n del Timer5 (Asignado a sensor2)
					OpenTimer5(				T5_ON 
											& T5_GATE_OFF 
											& PrescalerT5 
											&	T5_SOURCE_INT	//Origen interno del clock
											, PeriodoT5);
				//Configuraci�n del A/D
					//Configuraci�n de ADCON1
        		ADCON1bits.FORM = 0b00;	//Formato del resultado: Fraccional con signo
        		ADCON1bits.SSRC = 0b10;	//La conversi�n es gatillada por el Timer3	
        		ADCON1bits.ASAM = 1;	//Muestreo autom�tico habilitado	
					//Configuraci�n de ADCON2
						ADCON2bits.VCFG = 0b0;						//Ref+ = AVdd	- Ref- = AVss
							ADCON2bits.SMPI = MuestPorInt;	//Interrumpir cada 16 muestras tomadas 
						//ADCON2bits.CHPS = 0;						//Convertir solo el canal CH0
						//ADCON2bits.BUFS	= 0;
						ADCON2bits.BUFM = 0;						//Buffer �nico de 16 palabras
					//Configuraci�n de ADCON3
						//Presuponiendo una Fcy = 20Mhz, tenemos Tcy = 50 nseg 
						ADCON3bits.ADCS = 0b111111;	//Tad = 32 * Tcy
						ADCON3bits.SAMC = 0b11111;		//Tmuestreo = 31 * Tad
					//Configuraci�n de ADCHS
						ADCHS = 1;	//Pin AN1 seleccionado como entrada anal�gica para conversi�n en Mux A			
        	//Configuraci�n de ADCSSL
        		ADCSSL = 0;	//Desactivar escaneo de canales
					//Configuraci�n de ADPCFG
						ADPCFG = 0xFFFF;	//Todos los pines como digitales
        		ADPCFGbits.PCFG0 = 0;	//Setear el pin AN0 como anal�gico
						ADPCFGbits.PCFG1 = 0;	//Setear el pin AN1 como anal�gico
					ADCON1bits.ADON = 1; //Encender A/D
			
			//Configuraci�n de puertos de entrada/salida
				TRISA = 0b0000100000000000;
				TRISB = 0b0000000000000111;
				//TRISC = 0b00000000 00000011;
				TRISD = 0b0000001000000000;
				TRISF = 0b0000001000000101;

			//Inicializaci�n del Display
				InicializarDisplay();

			//Configuraci�n de Interrupciones
				INTCON1bits.NSTDIS = 0;	//Habilitar interrupciones anidadas
				INTCON2bits.ALTIVT = 0;	//No usar la Tabla de Vectores de Interrupci�n Alternativa
				//Configuraci�n de las prioridades de Interrupci�n
					IPC0 = ((PrioridadT1 * 0x1000) | (PrioridadINT0 * 0x0001));	//Asigno prioridad a Timer1 e INT0
					IPC1 = ((PrioridadT3 * 0x1000) | (PrioridadT2 * 0x0100));	//Asigno prioridad a Timer3 e Timer2
					IPC2 = ((PrioridadAD * 0x1000));	//Asigno prioridad a AD
					IPC4 = ((PrioridadINT1 * 0x0001));	//Asigno prioridad a INT1
					IPC5 = ((PrioridadINT2 * 0x1000) | (PrioridadT5 * 0x0100) | (PrioridadT4 * 0x0010));	//Asigno prioridad a INT2, Timer5 y Timer4
				//Resetear Flags de Interrupci�n
					IFS0 = 0;
					IFS1 = 0;
					IFS2 = 0;
				//Habilitar Interrupciones
					/*IEC0 = 0b1000100000001001;
					IEC1 = 0b0000000010000000;
					IEC2 = 0b0000000000000000;*/
					IEC0 = 0b1000100010001001;
					IEC1 = 0b0000000011100000;
					IEC2 = 0b0000000000000000;

				//////////////////
				//ptrMenuActual = &(MenuPrinc[3][0]);
				//PrintfLCDXY(0,0, (char *) ptrMenuActual);
				//////////////

				//FIRDelayInit(&FiltroFilter);

				Nop();

				//FIR(Cant_Muest_Fuerza,&BufferFiltrado[0],&BufferMuestras[0],&FiltroFilter);

				Nop();

				/*TRISB = 0b0000000000000000;

				Entrada1 = 0;
				Entrada0 = 0;

				Nop();
				Nop();*/

Main:
			//BLOQUE DE EJECUCI�N DE PROCESOS
				//Proceso/Rutina de Menu
					if (Proc.HabRutCalFuerza == 1)
						if(Proc.EjecRutCalFuerza == 1)
						{
							RutCalFuerza();	
							Proc.EjecRutCalFuerza = 0;
							goto Main;
						}
				//Proceso/Rutina de Sensores
					if (Proc.HabRutSensores == 1)
						if(Proc.EjecRutSensores == 1)
						{
							RutinaSensores();	
							Proc.EjecRutSensores = 0;
							goto Main;
						}
				//Proceso/Rutina de Envio por Puerto Serie
					if (Proc.HabRutFiltrado == 1)
						if(Proc.EjecRutFiltrado == 1)
						{
							RutinaFiltrado();	
							Proc.EjecRutFiltrado = 0;
							goto Main;
						}
				//Proceso/Rutina de Envio por Puerto Serie
					if (Proc.HabRutPuertoSerie == 1)
						if(Proc.EjecRutPuertoSerie == 1)
						{
							RutinaPuertoSerie();	
							Proc.EjecRutPuertoSerie = 0;
							goto Main;
						}
				//Proceso/Rutina de Menu
					if (Proc.HabRutMenu == 1)
						if(Proc.EjecRutMenu == 1)
						{
							RutinaMenu();	
							Proc.EjecRutMenu = 0;
							goto Main;
						}
				//Proceso/Rutina de Teclado
					if (Proc.HabRutTeclado == 1)
						if(Proc.EjecRutTeclado == 1)
						{
							RutinaTeclado();
							Proc.EjecRutTeclado = 0;
							goto Main;
						}	
				//Proceso/Rutina de Teclas
					if (Proc.HabRutTeclas == 1)
						if(Proc.EjecRutTeclas == 1)
						{
							RutinaTeclas();	
							Proc.EjecRutTeclas = 0;
							goto Main;
						}
			goto Main;	
			return 0;	
		}  


//RUTINAS DE SERVICIO DE INTERRUPCI�N (ISR)	
	/*ISR por defecto -----------------------------------------------------------------------------------------------------------------------
	Descripci�n: 	Ejecutada cuando la interrupci�n ocurrida no tiene asignado ning�n manejador. 
								Se escribe para evitar que si se ejecutan interrupciones no controladas, no se resetee el dsPIC 
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
		void __attribute__((interrupt, no_auto_psv)) _DefaultInterrupt(void)
		{			
		}

	/*ISR del Timer1 (Base de Tiempo Normal)-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina de la Base de tiempo normal donde se decrementan los contadores de espera y se setean las banderas de ejecuci�n
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
		void __attribute__((interrupt, auto_psv)) _T1Interrupt(void) //BASE DE TIEMPO NORMAL 
		{
			IFS0bits.T1IF = 0;
			
			//Proceso de Men�	
				Proc.ContEspMenu--;
				if (Proc.ContEspMenu == 0)
				{
					Proc.EjecRutMenu = 1;
					Proc.ContEspMenu = (unsigned) CEMenu;
				}
			
			//Proceso de Teclado	
				Proc.ContEspTeclado--;
				if (Proc.ContEspTeclado == 0)
				{
					Proc.EjecRutTeclado = 1;
					Proc.ContEspTeclado = CETeclado;
				}			

			//Proceso de Teclas	
				Proc.ContEspTeclas--;
				if (Proc.ContEspTeclas == 0)
				{
					Proc.EjecRutTeclas = 1;
					Proc.ContEspTeclas = CETeclas;
				}	
		
			//Decremento de la variable de espera
				Esperar--;
		}

	/*ISR del AD (Base de Tiempo Normal)-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina del AD
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
		void __attribute__((interrupt, auto_psv)) _ADCInterrupt(void)
		{
			IFS0bits.ADIF = 0;
			
			//Copiar buffer de muestras del AD al Buffer de Muestras
				ptrBufferMuestras = &(ADCBUF0);
			 	for(i_ADCI=0;i_ADCI<16;i_ADCI++)
//					BufferMuestras[i_ADCI] = (unsigned int) *(ptrBufferMuestras + (i_ADCI * 2));
			/*BufferMuestras[0] = ADCBUF0;
			BufferMuestras[1] = ADCBUF1;
			BufferMuestras[2] = ADCBUF2;
			BufferMuestras[3] = ADCBUF3;
			BufferMuestras[4] = ADCBUF4;
			BufferMuestras[5] = ADCBUF5;
			BufferMuestras[6] = ADCBUF6;
			BufferMuestras[7] = ADCBUF7;
			BufferMuestras[8] = ADCBUF8;
			BufferMuestras[9] = ADCBUF9;
			BufferMuestras[10] = ADCBUFA;
			BufferMuestras[11] = ADCBUFB;
			BufferMuestras[12] = ADCBUFC;
			BufferMuestras[13] = ADCBUFD;
			BufferMuestras[14] = ADCBUFE;
			BufferMuestras[15] = ADCBUFF;*/

			
			Proc.EjecRutCalFuerza = 1;
			Proc.EjecRutPuertoSerie = 1;
		}

	/*ISR del Sensor 1 -----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que atiende sensor de maquina
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
//Sucede cuando pasa un iman al frente del sensor 1
		void __attribute__((interrupt, auto_psv)) _INT0Interrupt(void) 
		{
			if(Band_Sensor.Band_Maq == 0)	//Si luego de pasar por el primer im�n, el timer no se desborda, entra aqui y habilita para mostrar las velocidades validas
				Band_Sensor.Vel_Maq_Min=0;
			if(Band_Sensor.Band_Maq == 1) //Primer iman despues de un desborde, por lo tanto no tomar el valor
			{
				Band_Sensor.Buffer_Completo_Maq  = 0;
				Band_Sensor.Band_Maq = 0;	//Ya ha pasado el primer im�n
				TMR4 = 0;	
			}
			else
				Indice_Buffer_Maq++;	//lleva la cuenta para ir guardando las velocidades instantaneas del tractor
					
			if (Band_Sensor.Buffer_Completo_Maq == 0)
				Cant_Elem_Usados_Maq = Indice_Buffer_Maq + 1;
			if(Indice_Buffer_Maq == Cant_Tim_Inst)
			{
				Indice_Buffer_Maq = 0;							//vuelve a cero para que vaya guardando las velocidades de forma ciclica
				Cant_Elem_Usados_Maq = Cant_Tim_Inst;
				Band_Sensor.Buffer_Completo_Maq = 1;
			}			

			Timer_Inst_Maq[Indice_Buffer_Maq] = TMR4;
			//	Desborde_T5 = 0;
			Proc.EjecRutSensores = 1;					//habilito la rutina sensores para que guarde siempre cada dato de velocidad

			TMR4=0;		//Seteo el timer en 0

			IFS0bits.INT0IF = 0;
		}

	/*ISR del Sensor 2 -----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que atiende sensor de tractor
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
//Sucede cuando pasa un iman al frente del sensor 2
		void __attribute__((interrupt, auto_psv)) _INT2Interrupt(void) 
		{

			if(Band_Sensor.Band_Trac == 0)	//Si luego de pasar por el primer im�n, el timer no se desborda, entra aqui y habilita para mostrar las velocidades validas
				Band_Sensor.Vel_Trac_Min=0;
			if(Band_Sensor.Band_Trac == 1) //Primer iman despues de un desborde, por lo tanto no tomar el valor
			{
				Band_Sensor.Buffer_Completo_Trac  = 0;
				Band_Sensor.Band_Trac = 0;	//Ya ha pasado el primer im�n
				TMR5 = 0;	
			}
			else
				Indice_Buffer_Trac++;	//lleva la cuenta para ir guardando las velocidades instantaneas del tractor
					
			if (Band_Sensor.Buffer_Completo_Trac == 0)
				Cant_Elem_Usados_Trac = Indice_Buffer_Trac + 1;
			if(Indice_Buffer_Trac == Cant_Tim_Inst)
			{
				Indice_Buffer_Trac = 0;							//vuelve a cero para que vaya guardando las velocidades de forma ciclica
				Cant_Elem_Usados_Trac = Cant_Tim_Inst;
				Band_Sensor.Buffer_Completo_Trac  = 1;
			}			

			Timer_Inst_Trac[Indice_Buffer_Trac] = TMR5;
			//	Desborde_T5 = 0;
			Proc.EjecRutSensores = 1;					//habilito la rutina sensores para que guarde siempre cada dato de velocidad

			/*if(Indice_Buffer_Trac == 10)
			{	
				Nop();
				Nop();
				Nop();	
			}*/

			TMR5=0;		//Seteo el timer en 0

			IFS1bits.INT2IF = 0;
		}

	/*ISR del Timer3 -----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que atiende 
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
	//Sucede cuando el timer3 se desborda
		void __attribute__((interrupt, auto_psv)) _T3Interrupt(void) //Timer de gatillado de la converci�n
		{
			IFS0bits.T3IF = 0;
			
		}

	/*ISR del Timer4 -----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que atiende 
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
	//Sucede cuando el timer4 se desborda
		void __attribute__((interrupt, auto_psv)) _T4Interrupt(void) //Timer para el sensor 1
		{
			IFS1bits.T4IF = 0;

			Indice_Buffer_Maq = 0;
			
			Band_Sensor.Buffer_Completo_Maq  =0;

			Band_Sensor.Band_Maq = 1;

			Band_Sensor.Vel_Maq_Min=1;			//La velocidad maxima no se tiene en cuenta pq nunca va a llegar a una velocidad mayor de 60Km/h 
			
			TMR4=0;		//Seteo el timer en 0
		}

	/*ISR del Timer5 -----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que atiende 
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
	//Sucede cuando el timer5 se desborda
		void __attribute__((interrupt, auto_psv)) _T5Interrupt(void) //Timer para el sensor 2
		{
			IFS1bits.T5IF = 0;

			Indice_Buffer_Trac = 0;
			
			Band_Sensor.Buffer_Completo_Trac  =0;

			Band_Sensor.Band_Trac = 1;

			Band_Sensor.Vel_Trac_Min=1;			//La velocidad maxima no se tiene en cuenta pq nunca va a llegar a una velocidad mayor de 60Km/h 
			
			TMR5=0;		//Seteo el timer en 0			
		}

