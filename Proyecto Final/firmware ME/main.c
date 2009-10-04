/*=======================================================================
PROYECTO	:		Firmware del Medidor de Eficiencia
PRIMERA VERSION: 1.00.00								AUTOR(es): 	Bongiovanni Pablo
																										Guanuco Luis
																										Sansó Marco
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
		extern volatile unsigned char Columna;	
		extern volatile unsigned char Temp_Tec;						//Almacena la supuesta nueva tecla presionada
		extern volatile unsigned char Last_Tec;						//Almacena la ultima tecla presionada
		extern volatile unsigned char Pres_Tec;						//Almacena la tecla que se acaba de presionar o se mantiene presionada
		extern volatile unsigned char New_Tec;							//Almacena la nueva y ultima tecla presionada, pero al contario de Pres_Tec, no se actualiza constantemente
		extern volatile unsigned char New_Tec_Aux;					//Sirve para que las acciones sobre la tecla presionada se ejecuten una sola vez
		extern volatile unsigned char Ult_Tec;							//Almacena la ultima tecla presionada	
	
	//Variables de LCD
	//Variables de Generales
	//Variables de Procesos/Rutinas
		struct VariablesDeProcesos Proc;
		

//DEFINICIÓN DE FUNCIONES
	/*Función Main-----------------------------------------------------------------------------------------------------------------------
	Descripción: Función principal (hilo principal)
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
		int main(void)
		{   
			//Inicialización de variables
				//Inicialización de variables de Teclado
					Columna	=	0;			
					Last_Tec	=	0;
					New_Tec	=	0;
					Temp_Tec	=	0;
					Ult_Tec	= 0;
					Pres_Tec	= 0;
				//Inicialización de variables de LCD
					
				//Inicialización de variables de Generales
					
				//Inicialización de variables de Procesos/Rutinas
					Proc.EjecRutMenu 		= 0;
					Proc.EjecRutTeclado = 0;
					Proc.EjecRutTeclas 	= 0;
					Proc.HabRutMenu 		= 0;
					Proc.HabRutTeclado 	= 0;
					Proc.HabRutTeclas 	= 0;
					Proc.ContEspMenu 		= CEMenu;
					Proc.ContEspTeclado	=	CETeclado;
					Proc.ContEspTeclas	=	CETeclas;

			//Configuración de Periféricos
				//Configuración del Timer1 (Asignado a )
					OpenTimer1(	T1_ON 
											& T1_GATE_OFF 
											& T1_PS_1_8 
											& T1_SYNC_EXT_OFF 
											&	T1_SOURCE_INT	//Origen interno del clock
											, PeriodoT1);
					//EnableIntT1;	//Habilitar interrupción del Timer1
					//SetPriorityIntT1(PrioridadT1);	//Setear nivel de prioridad del Timer1 a 7
				//Configuración del Timer2 (Asignado a )
					OpenTimer2(	T2_ON 
											& T2_GATE_OFF 
											& T2_PS_1_8 
											&	T2_SOURCE_INT	//Origen interno del clock
											, PeriodoT2);
					//EnableIntT2;	//Habilitar interrupción del Timer2
					//SetPriorityIntT2(PrioridadT2);	//Setear nivel de prioridad del Timer2
				//Configuración del Timer2 (Asignado a )
					OpenTimer3(	T3_ON 
											& T3_GATE_OFF 
											& T3_PS_1_8 
											&	T3_SOURCE_INT	//Origen interno del clock
											, PeriodoT3);
					//EnableIntT3;	//Habilitar interrupción del Timer3
					//SetPriorityIntT3(PrioridadT3);	//Setear nivel de prioridad del Timer3
				//Configuración del A/D
					//Configuración de ADCON1
        		ADCON1bits.FORM = 0b11;	//Formato del resultado: Fraccional con signo
        		ADCON1bits.SSRC = 0b10;	//La conversión es gatillada por el Timer3	
        		ADCON1bits.ASAM = 1;	//Muestreo automático habilitado	
					//Configuración de ADCON2
						ADCON2bits.VCFG = 0b0;						//Ref+ = AVdd	- Ref- = AVss
						ADCON2bits.SMPI = MuestPorInt;	//Interrumpir cada 16 muestras tomadas 
						//ADCON2bits.CHPS = 0;						//Convertir solo el canal CH0
						//ADCON2bits.BUFS	= 0;
						ADCON2bits.BUFM = 0;						//Buffer único de 16 palabras
					//Configuración de ADCON3
						//Presuponiendo una Fcy = 20Mhz, tenemos Tcy = 50 nseg 
						ADCON3bits.ADCS = 0b111111;	//Tad = 32 * Tcy
						ADCON3bits.SAMC = 0b11111;		//Tmuestreo = 31 * Tad
					//Configuración de ADCHS
						ADCHS = 1;	//Pin AN1 seleccionado como entrada analógica para conversión en Mux A			
        	//Configuración de ADCSSL
        		ADCSSL = 0;	//Desactivar escaneo de canales
					//Configuración de ADPCFG
						ADPCFG = 0xFFFF;	//Todos los pines como digitales
        		ADPCFGbits.PCFG0 = 0;	//Setear el pin AN0 como analógico
						ADPCFGbits.PCFG1 = 0;	//Setear el pin AN1 como analógico
					ADCON1bits.ADON = 1; //Encender A/D

			//Configuración de Interrupciones
				INTCON1bits.NSTDIS = 0;	//Habilitar interrupciones anidadas
				INTCON2bits.ALTIVT = 0;	//No usar la Tabla de Vectores de Interrupción Alternativa
				//Configuración de las prioridades de Interrupción
					IPC0 = ((PrioridadT1 * 0x1000) | (PrioridadINT0 * 0x0001));	//Asigno prioridad a Timer1 e INT0
					IPC1 = ((PrioridadT3 * 0x1000) | (PrioridadT2 * 0x0100));	//Asigno prioridad a Timer3 e Timer2
					IPC2 = ((PrioridadAD * 0x1000));	//Asigno prioridad a AD
					IPC4 = ((PrioridadINT1 * 0x0001));	//Asigno prioridad a INT1
					IPC5 = ((PrioridadINT2 * 0x1000) | (PrioridadT5 * 0x0100) | (PrioridadT4 * 0x0010));	//Asigno prioridad a INT2, Timer5 y Timer4
					
				//Resetear Flags de Interrupción
					IFS0 = 0;
					IFS1 = 0;
					IFS2 = 0;
					
									
Main:
				//BLOQUE DE EJECUCIÓN DE PROCESOS
					//Proceso/Rutina de Menu
						if (Proc.HabRutMenu == 1)
							if(Proc.EjecRutMenu == 1)
							{
								
								Proc.EjecRutMenu = 0;
								goto Main;
							}
					//Proceso/Rutina de Teclado
						if (Proc.HabRutTeclado == 1)
							if(Proc.EjecRutTeclado == 1)
							{
								
								Proc.EjecRutTeclado = 0;
								goto Main;
							}	
					//Proceso/Rutina de Teclas
						if (Proc.HabRutTeclas == 1)
							if(Proc.EjecRutTeclas == 1)
							{
								
								Proc.EjecRutTeclas = 0;
								goto Main;
							}
	
			return 0;	
		}  
