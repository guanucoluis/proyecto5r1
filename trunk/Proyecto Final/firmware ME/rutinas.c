//INCLUDES
	#include "rutinas.h"
	#include "LCD.h"
	#include <stdio.h>	
	#include "main.h"
	#include "sensores.h"
	#include <dsp.h>

//DECLARACION DE VARIABLES
	//Variables de Menús

		volatile unsigned char Cant_Mediciones = 0;	//es el numero maximo de mediciones que se han tomado correctamente
		volatile unsigned char Med_Actual = 1;		//indica las mediciones que han sido borradas, o no
	//valores para test
		volatile unsigned char Cont_Muestras = 9;	//valor cte, para prueba. Me lo debe pasar gonza.
		extern volatile float Vel_Prom_Trac;		
		extern volatile float Vel_Prom_Maq;	

		volatile unsigned char Esperar_Para_Mostrar;

		volatile unsigned char Radio_Tractor = 7;
		volatile unsigned char Radio_Maquina = 7;
		volatile unsigned char Var_Radio = 1;

	//Variables relativas a la Fuerza
		volatile unsigned char i_RCF;
		volatile unsigned char i_ADCI;
		volatile unsigned int i_Buffer_Muestras;
		volatile unsigned int i_Buffer_Muestras_Aux;

		volatile float FuerzaPromedio = 0;
		//volatile float FuerzaInst;
		volatile unsigned int *ptrBufferMuestras;
		volatile unsigned long int SumatoriaFuerza;
		volatile float Offset = 0;

	//Variables de Procesos/Rutinas
		extern struct VariablesDeProcesos Proc;

	//Variables relativas a la Tarjeta SD y los archivos
		volatile FSFILE *pNewFile;
		//int bytesRead, bytesWritten;
 		const char newFile[] = "MEDICION.txt";
		const char mode[] = "w"; 

		volatile char Cadena[18];
		volatile char *ptrMenuActual;
		volatile char const MenuPrinc[14][17]={	"Tomar Medicion  ",					// 0 
																			"Tarar           ",					// 1
																			"Borrar          ",					// 2 
																			"Ok para terminar",					// 3 
																			"del tractor     ",					// 4 
																			"bien almacenada ",					// 5 
																			"Tarar?          ",					// 6
																			"Cancelar      Ok",					// 7 
																			"borrada         ",					// 8
																			"Opc. Avanzadas  ",					// 9
																			"Cambiar Radio   ",					// 10
																			"Ingrese Valor de",					// 11
																			"de la maquina   "};				// 12

		volatile unsigned char MenuSeleccionado = 0;		//para que en el menu empiece por Tomar Medicion 

		volatile struct Med Mediciones[Cant_Max_Med];	//Inicializo la estructura Med.
		extern volatile struct Sensores Band_Sensor;

	//Variables relativas al filtrado
		volatile fractional BufferMuestras[Tamanio_Buffer_Fuerza];	//Buffer con las muestras tomadas desde el AD
		//extern volatile FIRStruct FPB_1K_HFilter; 
		//volatile fractional BufferFiltrado[Tamanio_Buffer_Fuerza] ; //Buffer de Salida ya filtrado  
                                       

	/*Función Rutina_Tecla_OK-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que atiende la pulsación de la Tecla OK
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_OK()
		{
			Nop();
			Nop();
			switch (MenuSeleccionado) // ¿En que menú estoy?
			{
			
				case Menu_TomarMedicion:
					MenuSeleccionado = Terminar_Medicion;
					//Crear el archivo donde se almacenarán las muestras
						pNewFile = FSfopen(newFile, mode);
					//Empezar el almacenamiento de las muestras
						Proc.HabRutAlmacenam	= 1;
					break;
				case Menu_Tarar: 
					MenuSeleccionado = Tarar_Preg ;				
					break;
				case Menu_Borrar:
					MenuSeleccionado = Borrar_Medicion;
					break;
				case Terminar_Medicion:
					MenuSeleccionado = Guardar_en;
					//Terminar el almacenamiento de las muestras
						Proc.HabRutAlmacenam	= 0;
					//Cerrar Archivo
						FSfclose(pNewFile);		
					break;					
				case Guardar_en:
					MenuSeleccionado = Medicion_ok;	
					break;					
				case Medicion_ok:
				  Cant_Mediciones++;
					Mediciones[Med_Actual].Usado=1;
					Mediciones[Med_Actual].Cant_Muestras=Cont_Muestras;  //Me lo debe pasar gonza
					MenuSeleccionado = Menu_TomarMedicion;
					break;

				case Tarar_Preg :
					Offset = FuerzaPromedio;				//Igualo el offset a la fuerza promedio que este en ese momento
					MenuSeleccionado = Menu_TomarMedicion;
					break;

				case Borrar_Medicion:
					if(Cant_Mediciones ==0)
					{
						MenuSeleccionado = Menu_TomarMedicion;
						break;
					}

					Cant_Mediciones--;
					Mediciones[Med_Actual].Usado=0;		
					MenuSeleccionado = Borrado_ok;
					break;

				case Borrado_ok:
					MenuSeleccionado = Menu_Borrar;
					break;

				case Menu_Avanzado: 
					MenuSeleccionado = Radio_Trac;	
					break;

				case Radio_Trac: 
					MenuSeleccionado = Ingresar_Radio_Trac;	
					break;

				case Radio_Maq: 
					MenuSeleccionado = Ingresar_Radio_Maq;	
					break;

				case Ingresar_Radio_Trac: 
																	//Var_Radio es el valor que voy a variar del radio entre 1 y 99
																	//no utilizo el radio directamente porque sino por cada vez que vaya cambiando este valor van a ir cambiando lo que se ve en el display los calculos de la velocidad
					Radio_Tractor = Var_Radio;								//una vez que termino de variar la variable del radio al valor que deseo lo guardo en la variable Radio que es la que se va a usar para los calculos. 
					MenuSeleccionado = Menu_TomarMedicion;			
					break;

				case Ingresar_Radio_Maq: 
					Radio_Maquina = Var_Radio;							
					MenuSeleccionado = Menu_TomarMedicion;			
					break;
			}
			
		}

	/*Función Rutina_Tecla_Cancelar-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que atiende la pulsación de la Tecla Cancelar
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Cancelar()
		{
			switch (MenuSeleccionado) // ¿En que menú estoy?
			{
				
				case Terminar_Medicion:
					MenuSeleccionado = Menu_TomarMedicion;
					break;			
				
				case Guardar_en:
					MenuSeleccionado = Menu_TomarMedicion;
					break;	
	
				case Medicion_ok:
					MenuSeleccionado = Menu_TomarMedicion;
					break;

				case Tarar_Preg :
					MenuSeleccionado = Menu_Tarar;
					break;

				case Borrar_Medicion:
					MenuSeleccionado = Menu_Borrar;
					break;

				case Borrado_ok:
					MenuSeleccionado = Menu_Borrar;
					break;

				case Radio_Trac:
				case Radio_Maq:
					MenuSeleccionado = Menu_Avanzado;
					break;

				case Ingresar_Radio_Trac:
					MenuSeleccionado = Radio_Trac;
					break;

				case Ingresar_Radio_Maq:
					MenuSeleccionado = Radio_Maq;
					break;

			}
		}

	/*Función Rutina_Tecla_Arriba-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que atiende la pulsación de la Tecla Arriba
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Arriba()
		{
		switch (MenuSeleccionado)
		{
		case Guardar_en:
			Med_Actual++;					
			if(Med_Actual>Cant_Max_Med)
					Med_Actual=1;
			while(Mediciones[Med_Actual].Usado==1)
			{	if(Med_Actual==Cant_Max_Med)
					Med_Actual=1;
				else
					Med_Actual++;
			}
			break;

		case Borrar_Medicion:
			Med_Actual++;
			if(Med_Actual>Cant_Max_Med)
					Med_Actual=1;
			while(Mediciones[Med_Actual].Usado==0)			// usado = 0 el espacio para medicion esta libre
			{	if(Med_Actual==Cant_Max_Med)
					Med_Actual=1;
				else
					Med_Actual++;
			}
			break;

		case Ingresar_Radio_Trac:
		case Ingresar_Radio_Maq:
			Var_Radio++;
			if (Var_Radio > Radio_Max)
					Var_Radio = 1;		
			break;

		}
		}

	/*Función Rutina_Tecla_Abajo-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que atiende la pulsación de la Tecla Abajo
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Abajo()
		{
		switch (MenuSeleccionado)	
		{
		case Guardar_en:
			Med_Actual--;
			if(Med_Actual<1)
				Med_Actual=Cant_Max_Med;
			while(Mediciones[Med_Actual].Usado==1)
			{	if(Med_Actual==1)
					Med_Actual=Cant_Max_Med;
				else
					Med_Actual--;
			}
			break;

		case Borrar_Medicion:
			Med_Actual--;
			if(Med_Actual<1)
				Med_Actual=Cant_Max_Med;
			while(Mediciones[Med_Actual].Usado==0)
			{	if(Med_Actual==1)
					Med_Actual=Cant_Max_Med;
				else
					Med_Actual--;
			}
			break;

		case Ingresar_Radio_Trac:
		case Ingresar_Radio_Maq:
			Var_Radio--;
			if (Var_Radio < 1)
					Var_Radio = Radio_Max;		
			break;
		}
		}

	/*Función Rutina_Tecla_Derecha-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que atiende la pulsación de la Tecla Derecha
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Derecha()
		{
			switch (MenuSeleccionado) // ¿En que menú estoy?
			{
				//Grupo del Menu principal
				case Menu_TomarMedicion:
					MenuSeleccionado = Menu_Tarar;
					break;
				case Menu_Tarar: 
					MenuSeleccionado = Menu_Borrar;
					break;
				case Menu_Borrar:
					MenuSeleccionado = Menu_Avanzado;
					break;
				case Menu_Avanzado:
					MenuSeleccionado = Menu_TomarMedicion;
					break;
				case Radio_Trac:	
					MenuSeleccionado = Radio_Maq;
					break;
				case Radio_Maq:	
					MenuSeleccionado = Radio_Trac;
					break;
			}
		}

	/*Función Rutina_Tecla_Izquierda-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que atiende la pulsación de la Tecla Izquierda
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Izquierda()
		{
			switch (MenuSeleccionado) // ¿En que menú estoy?
			{
				//Grupo del Menu principal
				case Menu_TomarMedicion:
					MenuSeleccionado = Menu_Avanzado;
					break;
				case Menu_Tarar: 
					MenuSeleccionado = Menu_TomarMedicion;
					break;
				case Menu_Borrar:
					MenuSeleccionado = Menu_Tarar;
					break;
				case Menu_Avanzado:
					MenuSeleccionado = Menu_Borrar;
					break;
				case Radio_Trac:	
					MenuSeleccionado = Radio_Maq;
					break;

				case Radio_Maq:	
					MenuSeleccionado = Radio_Trac;
					break;
			}
		}

	/*Función RutinaMenu-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina encargada de graficar el texto que corresponda en el LCD
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void RutinaMenu()
		{
			Nop();

			//Parte SUPERIOR del Display
			switch(MenuSeleccionado)
			{
				case Guardar_en:
					while(Mediciones[Med_Actual].Usado==1)
					{	if(Med_Actual==Cant_Max_Med)
							Med_Actual=1;
						else
							Med_Actual++;
					}
					sprintf((char *) Cadena,"Guardar en: %02d  ",(char) Med_Actual);
					PrintfLCDXY(0,0,(char *) Cadena);					
					break;
				case Medicion_ok:
					sprintf((char *) Cadena,"Medicion N %02d   ", (char) Med_Actual);
					PrintfLCDXY(0,0,(char *) Cadena);
					break;
				case Borrar_Medicion:
					sprintf((char *) Cadena,"Hay %02d Medicione",(char) Cant_Mediciones);
					PrintfLCDXY(0,0,(char *) Cadena);
					break;
				case Borrado_ok:
					sprintf((char *) Cadena,"Medicion N %02d   ",(char) Med_Actual);
					PrintfLCDXY(0,0,(char *) Cadena);
					break;

				case Radio_Trac:
				case Radio_Maq:
					ptrMenuActual = (char *)&(MenuPrinc[10][0]);
					PrintfLCDXY(0,0,(char *) ptrMenuActual);
					break;

				case Ingresar_Radio_Trac:
				case Ingresar_Radio_Maq:
					ptrMenuActual = (char *)&(MenuPrinc[11][0]);
					PrintfLCDXY(0,0,(char *) ptrMenuActual);
					break;

				default:
					ptrMenuActual = (char *)&(MenuPrinc[MenuSeleccionado][0]);
					PrintfLCDXY(0,0,(char *) ptrMenuActual);            
					break;
			}
 
					//Parte INFERIOR del Display
			switch(MenuSeleccionado)						//Muestro la parte de abajo del display
			{
				case Borrar_Medicion:
					while(Mediciones[Med_Actual].Usado==0)			// usado = 0 el espacio para medicion esta libre
					{	if(Med_Actual==Cant_Max_Med)
							Med_Actual=1;
						else
							Med_Actual++;
					}
					sprintf((char *) Cadena,"Borrar Med N %02d ",(char) Med_Actual);
					PrintfLCDXY(0,1,(char *) Cadena);
					break;

				case Ingresar_Radio_Trac:
				case Ingresar_Radio_Maq:
					sprintf((char *) Cadena,"radio en cm: %02d ",(char) Var_Radio);
					PrintfLCDXY(0,1,(char *) Cadena);
					break;

				case Menu_TomarMedicion:
				case Menu_Tarar:
				case Menu_Borrar:
				case Terminar_Medicion:
				case Guardar_en:
				case Menu_Avanzado:

					if(FuerzaPromedio < 0)
						FuerzaPromedio = 0;
					if(Band_Sensor.Vel_Trac_Min == 1)
					{	
					sprintf((char *) Cadena,"%4d %s %s",(int) FuerzaPromedio,"--.--","--.--");
					PrintfLCDXY(0,1,(char *) Cadena);
					}	
					else 
					{
						if (Esperar_Para_Mostrar == 0)	//Pregunto si ya es hora de mostrar
						{
							if(Band_Sensor.Vel_Maq_Min == 1)
							{	
								sprintf((char *) Cadena,"%4d %5.2f %s",(int) FuerzaPromedio ,(double) Vel_Prom_Trac,"--.--");
								PrintfLCDXY(0,1,(char *) Cadena);
							}
							else
							{
								sprintf((char *) Cadena,"%4d %5.2f %5.2f",(int) FuerzaPromedio, (double) Vel_Prom_Trac, (double) Vel_Prom_Maq);
								PrintfLCDXY(0,1,(char *) Cadena);
							}	
							Esperar_Para_Mostrar = Delay_Refresco;
						}
						else
						{
							Esperar_Para_Mostrar--;
						}		
					}
					break;
			
				case Tarar_Preg:
					ptrMenuActual = (char *)&(MenuPrinc[MenuSeleccionado +1][0]);
					PrintfLCDXY(0,1,(char *) ptrMenuActual);
					break;	

				case Radio_Trac:
					ptrMenuActual = (char *)&(MenuPrinc[4][0]);
					PrintfLCDXY(0,1,(char *) ptrMenuActual);
					break;	

				case Radio_Maq:
					ptrMenuActual = (char *)&(MenuPrinc[12][0]);
					PrintfLCDXY(0,1,(char *) ptrMenuActual);
					break;	

				default:
					ptrMenuActual = (char *)&(MenuPrinc[MenuSeleccionado][0]);
					PrintfLCDXY(0,1,(char *) ptrMenuActual);
					break;	
			}
		}

	/*Función RutCalFuerza()-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina encargada de calcular el buffer de fuerza y la fuerza promedio
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void RutCalFuerza()
		{

			/*//Calcular la Fuerza promedio
				SumatoriaFuerza = 0;
				if(i_Buffer_Muestras == 0)
					i_Buffer_Muestras_Aux = Tamanio_Buffer_Fuerza - Cant_Muest_Por_Int;
				else
					i_Buffer_Muestras_Aux = i_Buffer_Muestras - Cant_Muest_Por_Int;
				for(i_RCF=0;i_RCF<Cant_Muest_Por_Int;i_RCF++)
				{
					SumatoriaFuerza = SumatoriaFuerza + BufferMuestras[i_Buffer_Muestras_Aux];
					if (i_Buffer_Muestras_Aux >= Tamanio_Buffer_Fuerza)
						i_Buffer_Muestras_Aux = 0;
					else
						i_Buffer_Muestras_Aux++;
				}
			FuerzaPromedio = (float) ((float) SumatoriaFuerza / (float) Cant_Muest_Por_Int);
			FuerzaPromedio = (float) ((float) FuerzaPromedio * (float) Volts_Por_Bit * (float) Kgf_Por_Volt);
			FuerzaPromedio = FuerzaPromedio - Offset;*/

			////////////
			FuerzaPromedio = (float) ((float) BufferMuestras[0] * (float) Volts_Por_Bit * (float) Kgf_Por_Volt);
			FuerzaPromedio = FuerzaPromedio - Offset;
			////////////

		}

	/*Función del Puerto Serie----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina encargada de enviar los datos por el puerto serie
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void RutinaPuertoSerie()
		{
			Nop();
			U2TXREG = 10;
			Nop();		
		}


	/*Función Filtrado-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que realiza el filtrado de las muestras tomadas del AD
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void RutinaFiltrado()
		{
//			FIRDelayInit(&FPB_1K_HFilter);
//			FIR(Tamanio_Buffer_Fuerza,&BufferFiltrado[0],&BufferMuestras[0],&FPB_1K_HFilter);
		}
		
	/*Rutina de Almacenamiento-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que almacena los valores de fuerza y velocidad en la SD
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void RutinaAlmacenam()
		{
			sprintf((char *) Cadena,"%4d %5.2f %5.2f",(int) FuerzaPromedio, (double) Vel_Prom_Trac, (double) Vel_Prom_Maq);
			Cadena[4] = 9; //Inserto una tabulación
			Cadena[10] = 9; //Inserto una tabulación
			Cadena[7] = 44;	//Cambio el punto por la coma
			Cadena[13] = 44;	//Cambio el punto por la coma
			Cadena[16] = 13;	//Inserto enter al final
			FSfwrite ((void *) Cadena, 1, 17, pNewFile);
			
		}
