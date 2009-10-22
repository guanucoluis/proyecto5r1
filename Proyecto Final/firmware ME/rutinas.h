//INCLUDES

//DEFINES RELATIVOS A CONSTANTES DEL PROGRAMA
	//#define	_CANT_MAX_MEDICIONES	10
	#define _Max_Bytes_Libres		30500;
	//#define _CANT_MAX_MUES_POR_SEG 	1000
	//#define _CANT_MIN_MUES_POR_SEG 	5
	//#define _No_Mem					160
	//#define _Tiempo_Max			1525 
	//#define	_Tiempo_Min			1
	//#define _Tiempo_De_Conv	0.0000992 //99.2 useg
	//#define	_Cant_Pag				500
	#define	_Volt_Por_Bit			0.0048828
	#define	_Kilo_Por_Volt		874.3
	//#define Kte							0
	#define	Vel_Min						0.0849 //[Km/h]			
 
//DEFINES RELATIVOS A LOS MENUS
	#define	Menu_TomarMedicion		0
	#define	Menu_Tarar						1	
	#define	Menu_Configuracion		2

//PROTOTIPOS DE FUNCIONES
	/*Funci�n Rutina_Tecla_OK-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que atiende la pulsaci�n de la Tecla OK
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_OK();

	/*Funci�n Rutina_Tecla_Cancelar-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que atiende la pulsaci�n de la Tecla Cancelar
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Cancelar();

	/*Funci�n Rutina_Tecla_Arriba-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que atiende la pulsaci�n de la Tecla Arriba
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Arriba();

	/*Funci�n Rutina_Tecla_Abajo-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que atiende la pulsaci�n de la Tecla Abajo
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Abajo();

	/*Funci�n Rutina_Tecla_Derecha-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que atiende la pulsaci�n de la Tecla Derecha
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Derecha();

	/*Funci�n Rutina_Tecla_Izquierda-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que atiende la pulsaci�n de la Tecla Izquierda
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Izquierda();
