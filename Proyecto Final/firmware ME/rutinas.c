//INCLUDES
	#include "rutinas.h"
	#include "LCD.h"
	#include <stdio.h>	
	#include "main.h"
	#include "sensores.h"
//DECLARACION DE VARIABLES
	//Variables de Menús

		volatile unsigned char Cant_Mediciones = 0;	//es el numero maximo de mediciones que se han tomado correctamente
		volatile unsigned char Med_Actual = 1;		//indica las mediciones que han sido borradas, o no
	//valores para test
		volatile unsigned char Cont_Muestras = 9;	//valor cte, para prueba. Me lo debe pasar gonza.
	//	volatile unsigned int Fuerza = 850;			//Valores de prueba
		extern volatile float Vel_Prom_Trac;		
		extern volatile float Vel_Prom_Maq;	

	//Variables relativas a la fuerza
		volatile unsigned int BufferMuestras[16];
		volatile float BufferFuerza[16];
		volatile unsigned char i_RCF;
		volatile unsigned char i_ADCI;
		volatile float FuerzaPromedio;
		volatile float FuerzaInst;
		volatile unsigned int *ptrBufferMuestras;
		volatile unsigned long int SumatoriaFuerza;

		volatile char Cadena[17];
		volatile char *ptrMenuActual;
		volatile char MenuPrinc[9][17]={	"Tomar Medicion  ",
											"Tarar           ",
											"Borrar          ",
											"Ok para terminar",
											"",
											"bien almacenada ",
											"Tarar?          ",
											"Cancelar      Ok",
											"borrada         "};
		volatile unsigned char MenuSeleccionado = 0;		//para que en el menu empiece por Tomar Medicion 

		struct Med Mediciones[Cant_Max_Med];	//Inicializo la estructura Med.
		extern struct Sensores Band_Sensor;

	//Variables de BinarioABCD()
		volatile unsigned char Unidad;
		volatile unsigned char Decena;
		volatile unsigned char Centena;
		volatile unsigned char UnidadMil;
		volatile unsigned char CentenaMil;

//DEFINICIÓN DE FUNCIONES
	/*Función BinABCD-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que convierte 
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/		
		void BinABCD(void)
		{
			
		}

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
					break;
				case Menu_Tarar: 
					MenuSeleccionado = Tarar_Preg ;				
					break;
				case Menu_Borrar:
					MenuSeleccionado = Borrar_Medicion;
					break;
				case Terminar_Medicion:
					MenuSeleccionado = Guardar_en;
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
			/*		Offset = Fuerza;				//Igualo el offset a la fuerza promedio que este en ese momento
					FuerzaT= Fuerza - Offset;
					if(FuerzaT < 0)					//Si la fuerza promedio baja del valor al cual fue tarado con esta condicion va a imprimir cero en la pantalla
						FuerzaT = 0;	*/			
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

				case Menu_TomarMedicion:
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
		if(MenuSeleccionado == Guardar_en)
		{
			Med_Actual++;					
			if(Med_Actual>Cant_Max_Med)
					Med_Actual=1;
			while(Mediciones[Med_Actual].Usado==1)
			{	if(Med_Actual==Cant_Max_Med)
					Med_Actual=1;
				else
					Med_Actual++;
			}

		}
		if(MenuSeleccionado == Borrar_Medicion)
		{
			Med_Actual++;
			if(Med_Actual>Cant_Max_Med)
					Med_Actual=1;
			while(Mediciones[Med_Actual].Usado==0)			// usado = 0 el espacio para medicion esta libre
			{	if(Med_Actual==Cant_Max_Med)
					Med_Actual=1;
				else
					Med_Actual++;
			}
		
		}
		}

	/*Función Rutina_Tecla_Abajo-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que atiende la pulsación de la Tecla Abajo
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Abajo()
		{
		if(MenuSeleccionado == Guardar_en)
		{
			Med_Actual--;
			if(Med_Actual<1)
				Med_Actual=Cant_Max_Med;
			while(Mediciones[Med_Actual].Usado==1)
			{	if(Med_Actual==1)
					Med_Actual=Cant_Max_Med;
				else
					Med_Actual--;
			}

		}
		if(MenuSeleccionado == Borrar_Medicion)
		{
			Med_Actual--;
			if(Med_Actual<1)
				Med_Actual=Cant_Max_Med;
			while(Mediciones[Med_Actual].Usado==0)
			{	if(Med_Actual==1)
					Med_Actual=Cant_Max_Med;
				else
					Med_Actual--;
			}

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
					MenuSeleccionado = Menu_TomarMedicion;
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
					MenuSeleccionado = Menu_Borrar;
					break;
				case Menu_Tarar: 
					MenuSeleccionado = Menu_TomarMedicion;
					break;
				case Menu_Borrar:
					MenuSeleccionado = Menu_Tarar;
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
			//Limpiar Display
				LimpiarLCD();

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
					sprintf((char *) Cadena,"Borrar Med N %d",(char) Med_Actual);
					PrintfLCDXY(0,1,(char *) Cadena);
					break;
				case Menu_TomarMedicion:
				case Menu_Tarar:
				case Menu_Borrar:
				case Terminar_Medicion:
				case Guardar_en:

					if(Band_Sensor.Vel_Trac_Min == 1)
					{	
					sprintf((char *) Cadena,"%4d %s %s",(int) FuerzaPromedio,"--.--","--.--");
					PrintfLCDXY(0,1,(char *) Cadena);
					}	
					else 
						{
						if(Band_Sensor.Vel_Maq_Min == 1)
							{	
							sprintf((char *) Cadena,"%4d %5.2f %s",(int) FuerzaPromedio,(double) Vel_Prom_Trac,"--.--");
							PrintfLCDXY(0,1,(char *) Cadena);
							}
						else
							{
							sprintf((char *) Cadena,"%4d %5.2f %5.2f",(int) FuerzaPromedio, (double) Vel_Prom_Trac, (double) Vel_Prom_Maq);
							PrintfLCDXY(0,1,(char *) Cadena);

							}	
						}
					break;
			
				case Tarar_Preg:
					ptrMenuActual = (char *)&(MenuPrinc[MenuSeleccionado +1][0]);
					PrintfLCDXY(0,1,(char *) ptrMenuActual);
					break;	

				default:
					ptrMenuActual = &(MenuPrinc[MenuSeleccionado][0]);
					PrintfLCDXY(0,1,(char *) ptrMenuActual);
					break;	
			}
		}

	/*Función BinarioABCD()-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina encargada de convertir valores binarios tipo int a BCD
	Entrada: Binario: valor binario a convertir
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void BinarioABCD(unsigned int Binario)
		{
			
		}

	/*Función RutCalFuerza()-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina encargada de calcular el buffer de fuerza y la fuerza promedio
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void RutCalFuerza()
		{
			for(i_RCF=0;i_RCF<16;i_RCF++)
				SumatoriaFuerza = BufferMuestras[i_RCF];

			FuerzaPromedio = SumatoriaFuerza/16;

			FuerzaPromedio = FuerzaPromedio * Volts_Por_Bit * Kgm_Por_Volt;

		}
