/*=======================================================================
PROYECTO	:		Firmware del Medidor de Eficiencia
PRIMERA VERSION: 1.00.00								AUTOR(es): 	Bongiovanni Pablo
																										Guanuco Luis
																										Sans� Marco
																										Vassia Gonzalo

INICIO: 												
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
					Last_Tec	=	0;
					New_Tec	=	0;
					Temp_Tec	=	0;
					Ult_Tec	= 0;
					Pres_Tec	= 0;
				//Inicializaci�n de variables de LCD
					
				//Inicializaci�n de variables de Generales
					
				//Inicializaci�n de variables de Procesos/Rutinas
					Proc.EjecRutMenu 		= 0;
					Proc.EjecRutTeclado = 0;
					Proc.EjecRutTeclas 	= 0;
					Proc.HabRutMenu 		= 0;
					Proc.HabRutTeclado 	= 0;
					Proc.HabRutTeclas 	= 0;
					Proc.ContEspMenu 		= CEMenu;
					Proc.ContEspTeclado	=	CETeclado;
					Proc.ContEspTeclas	=	CETeclas;

			//Configuraci�n de Perif�ricos
				//Configuraci�n del Timer1 (Asignado a )
					OpenTimer1(	T1_ON 
											& T1_GATE_OFF 
											& T1_PS_1_8 
											& T1_SYNC_EXT_OFF 
											&	T1_SOURCE_INT
											, PeriodoT1);
					EnableIntT1;										//Habilitar interrupci�n del Timer1
					SetPriorityIntT1(PrioridadT1);						//Setear nivel de prioridad del Timer1 a 7
				
				//Configuraci�n del Timer2 (Asignado a )
					OpenTimer2(	T2_ON 
											& T2_GATE_OFF 
											& T2_PS_1_8 
											&	T2_SOURCE_INT
											, PeriodoT2);
					EnableIntT2;										//Habilitar interrupci�n del Timer2
					SetPriorityIntT2(PrioridadT2);						//Setear nivel de prioridad del Timer2
				//Configuraci�n del Timer2 (Asignado a )
					OpenTimer3(	T3_ON 
											& T3_GATE_OFF 
											& T3_PS_1_8 
											&	T3_SOURCE_INT
											, PeriodoT3);
					EnableIntT3;										//Habilitar interrupci�n del Timer3
					SetPriorityIntT3(PrioridadT3);						//Setear nivel de prioridad del Timer3
				//Configuraci�n del A/D
					
Main:
				//BLOQUE DE EJECUCI�N DE PROCESOS
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