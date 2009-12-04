	#include "teclado.h"
	#include "curso_main.h"

//DECLARACION DE VARIABLES
	//Variables de Teclado
		extern unsigned char Columna;						//Variable que indica cual de las columnas (salidas) tiene que ser activada
		extern unsigned char Aux_Col;						//Almacena temporalmente el número de columna (salida) activada
		extern unsigned char Aux_Fila;					//Almacena temporalmente el número de fila (entrada) activada
		extern unsigned char Verif_Antirreb;		//Contador de la cantidad de veces que una tecla debe ser detectada para ser tomada como válida
		extern unsigned char Tecla_Temp;				//Almacena la tecla que se ha detectado en el flujo actual de la rutina
		extern unsigned char Tecla_Actual;			//Almacena la tecla que se ha detectado en el flujo anterior de la rutina
		extern unsigned char Tecla_Presionada;	//Almacena la tecla que está siendo presionada y que ya a pasado la comprobación antirrebote, pero solo es tomada una sola vez
		extern unsigned char Tecla_Sostenida;		//Almacena la tecla que está siendo presionada y sostenida en el tiempo por el usuari
		extern unsigned char i;
		extern unsigned char Cadena[16];
		unsigned char contador;


//DEFINICIÓN DE FUNCIONES
	/*Función Teclado------------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que barre el teclado matricial buscando cual tecla ha sido presionada. Y luego asigna a Tecla_Presionada el valor de la tecla presionada 
	Entrada: nada
	Salida: nada
	//-------------------------------------------------------------------------------------------------------------------------------------*/
		void RutinaTeclado(void)
		{
//			unsigned int ValTrisB;
//			unsigned int ValPORTB;
			
			//Salvar estado en que se encuntra el puerto
//				ValPORTB = PORTB;
//				ValTrisB = TRISB; 
			//Configuración de los puertos como entrada o salida
				PORTCbits.RC0 = 0;
	
				Delay10us();	//Hago una demora para que se estabilicen los valores del puerto D en cero y se anulen los transitorios. Sin esta demora no funciona						
		
			//Apagar todas las salidas
				Salida0 = 1;    
		//		Salida1 = 0;
//				Salida2 = 0;

			//Poner en 1 una de las salidas dependiendo del valor de Columna
//				Aux_Col = Columna + 1;
//				if (--Aux_Col == 0)
//					Salida0 = 1;
//				if (--Aux_Col == 0)
//					Salida1 = 1;
//				if (--Aux_Col == 0)
//					Salida2 = 1;
	
//			Aux_Col = Aux_Col + 2;	//Incremento en dos para que me quede Aux_Col > 0 (para 2 columnas)
//			Aux_Col = Aux_Col + 1;	//Incremento en dos para que me quede Aux_Col > 0 (para 1 columna)
			
//			Aux_Col = Aux_Col + 0;	//Incremento en dos para que me quede Aux_Col > 0 (como son 1 columna)

			//Recorrer las entradas preguntando si están en 1 y setear Aux_Fila a un valor dependiendo de cual este activada
				Aux_Fila = Tecla_No_Pres;
				if (Entrada0 == 1)
					Aux_Fila = 0;
				if (Entrada1 == 1)
					Aux_Fila = NumFilas + 1;
				if (Entrada2 == 1)
					Aux_Fila = NumFilas + 2;
				if (Entrada3 == 1)
					Aux_Fila = NumFilas + 3;
			
			//Detectar si se presionó una tecla
				if (Aux_Fila != Tecla_No_Pres)	//SI se presionó una tecla
				{	
					Tecla_Temp = Aux_Col + Aux_Fila; //Calcular la tecla
					//Verificar si es o no igual a la última tecla presionada
						if (Tecla_Temp == Tecla_Actual) //SI son iguales
						{
							Verif_Antirreb++;	//Incrementar el contador de verificaciones antirrebote
							if (Verif_Antirreb == Antirrebote) //Si ya se han cumplido las verificaciones antirrebote
							{
								Verif_Antirreb = 0;
								if (Tecla_Sostenida == Tecla_No_Pres)		//Esto se hace para evitar que una misma tecla sea tomada dos veces al mantenerla apretada
								{
									Tecla_Presionada = Tecla_Actual;
									Tecla_Sostenida = Tecla_Actual;
								}	
							}
						}
						else	//NO son iguales
						{
							Tecla_Actual = Tecla_Temp;
						}				
				}
				else	//NO se presionó una tecla
				{
					Tecla_Presionada = Tecla_No_Pres;	//No se presionó ninguna tecla
					Tecla_Sostenida  = Tecla_No_Pres;	//No está siendo sostenida ninguna tecla
					Columna++;	//Pasar a otra columna
					if (Columna == NumColum)
						Columna = 0;	
				}
	}

	/*Función/Rutina Teclas------------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que evalúa el valor de Tecla_Presionada (la tecla que actualmente está siendo presionada) y toma una acción en función de ésta 
	Entrada: nada
	Salida: nada
	//-------------------------------------------------------------------------------------------------------------------------------------*/
		void RutinaTeclas(void)
		{
			switch (Tecla_Presionada) // ¿Que tecla presione?
			{
				case Tecla_OK:
					Rutina_Tecla_OK();
					break;
				case Tecla_Derecha:
					Rutina_Tecla_Derecha();
					break;
				case Tecla_Izquierda:
					Rutina_Tecla_Izquierda();
					break;
				case Tecla_Cancelar:
					Rutina_Tecla_Cancelar();
					break;
			}
			Tecla_Presionada = Tecla_No_Pres;
		}




	void Delay10us()
		{
			for(i=0;i<50;i++)
				Nop();
		}


	/*Función Rutina_Tecla_OK-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que atiende la pulsación de la Tecla OK
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_OK(void)
		{
			contador++;
			if(contador==200)
				contador=0;
			sprintf((char *)Cadena, "Cont: %03d OK  ", contador);
			PrintfLcdXY(0,1,(char *)Cadena);
		}

	/*Función Rutina_Tecla_Cancelar-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que atiende la pulsación de la Tecla Cancelar
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Cancelar(void)
		{
			contador++;
			if(contador==200)
				contador=0;
			sprintf((char *)Cadena, "Cont: %03d CANC", contador);
			PrintfLcdXY(0,1,(char *)Cadena);
		}

	/*Función Rutina_Tecla_Izquierda-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que atiende la pulsación de la Tecla Izquierda
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Izquierda(void)
		{
			contador++;
			if(contador==200)
				contador=0;
			sprintf((char *)Cadena, "Cont: %03d IZQ ", contador);
			PrintfLcdXY(0,1,(char *)Cadena);
		}

	/*Función Rutina_Tecla_Abajo-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que atiende la pulsación de la Tecla Derecha
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Derecha(void)
		{
			contador++;
			if(contador==200)
				contador=0;
			sprintf((char *)Cadena, "Cont: %03d DER ", contador);
			PrintfLcdXY(0,1,(char *)Cadena);
		}

