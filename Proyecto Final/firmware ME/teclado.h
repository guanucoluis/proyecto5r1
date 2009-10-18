
//DEFINES RELATIVOS AL TECLADO

	#define NumeroDeColumnas		2					//Numero de columnas del teclado, menos 1
				
 
	//Valores asignados a cada tecla
		#define _NoTecla	 				0
		#define _TeclaOK	 				2
		#define _TeclaCL	 				1
		#define _TeclaDerecha 		4
		#define _TeclaIzquierda 	7
		#define _TeclaArriba 			6	
		#define _TeclaAbajo	 			3
		#define	_TeclaCancelar		8

	//Salidas del teclado
		#define	Salida0						PORTBbits.RB8
		#define	Salida1						PORTBbits.RB9
		#define	Salida2						PORTBbits.RB10

	//Entradas del teclado
		#define	Entrada0					PORTBbits.RB11
		#define	Entrada1					PORTBbits.RB12

//PROTOTIPOS DE FUNCIONES
	/*Función/Rutina Teclado------------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que barre el teclado matricial buscando cual ha sido presionada. Y luego asigna a Pres_Tec el valor de la tecla presionada 
	Entrada: nada
	Salida: nada
	//-------------------------------------------------------------------------------------------------------------------------------------*/
		void RutinaTeclado(void);

	/*Función/Rutina Teclas------------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que evalúa el valor de New_Tec (la tecla presionada) y toma una acción en función de éste 
	Entrada: nada
	Salida: nada
	//-------------------------------------------------------------------------------------------------------------------------------------*/
		void RutinaTeclado(void);

