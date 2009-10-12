
//INCLUDES
	#include "teclado.h"	
	#include "p30fxxxx.h"
	//#include "p30f4013.h"
	#include "dsPIC_delay.h"

//DECLARACION DE VARIABLES
	//Variables de Teclado
		volatile unsigned char Columna;	
		volatile unsigned char Temp_Tec;						//Almacena la supuesta nueva tecla presionada
		volatile unsigned char Last_Tec;						//Almacena la ultima tecla presionada
		volatile unsigned char Pres_Tec;						//Almacena la tecla que se acaba de presionar o se mantiene presionada
		volatile unsigned char New_Tec;							//Almacena la nueva y ultima tecla presionada, pero al contario de Pres_Tec, no se actualiza constantemente
		volatile unsigned char New_Tec_Aux;					//Sirve para que las acciones sobre la tecla presionada se ejecuten una sola vez
		volatile unsigned char Ult_Tec;		

//DEFINICIÓN DE FUNCIONES
	/*Función Teclado------------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que barre el teclado matricial buscando cual ha sido presionada. Y luego asigna a Pres_Tec el valor de la tecla presionada 
	Entrada: nada
	Salida: nada
	//-------------------------------------------------------------------------------------------------------------------------------------*/
		void RutinaTeclado(void)
		{
			unsigned int ValTrisB;
			unsigned int ValPORTB;
			unsigned char Aux;
			
			//Salvar estado en que se encuntra el puerto
				ValPORTB = PORTB;
				ValTrisB = TRISB; 
			//Configuración de los puertos como entrada o salida
				TRISB = 0b0001100000000000;
				PORTB = 0;
	
			Delay_x100useg(1);	//Hago una demora para que se estabilicen los valores del puerto D en cero y se anulen los transitorios. Sin esta demora no funciona
			//Delay100TCYx(2);						
		
			//Apagar todas las salidas
				//bcf				PORTD,0,0
				Salida0 = 0;    
				//bcf				PORTD,1,0
				Salida1 = 0;
				//bcf				PORTD,2,0
				Salida2 = 0;
			//Poner en 1 una de las salidas dependiendo del valor de Columna
				Aux = Columna + 1;
				if (Aux-- == 0)
					Salida0 = 1;
				if (Aux-- == 0)
					Salida1 = 1;
				if (Aux-- == 0)
					Salida2 = 1;
				
				/*_asm
				incf			Columna,0,1			//Incrementa Columna y pone el resultado en W  	
				dcfsnz		WREG,1,0			
				bsf				PORTD,0,0
				dcfsnz		WREG,1,0			
				bsf				PORTD,1,0
				dcfsnz		WREG,1,0			
				bsf				PORTD,2,0*/
	
			//Recorrer las entradas preguntando si están en 1 y seteo W a un valor dependiendo de cual está activada
				if (Entrada0 == 1)
					Aux = 4;
				if (Entrada1 == 1)
					Aux = 8;
				if (Aux == 0)
					goto NoTec;

				/*btfsc			PORTD,3,0
				movlw			0x04
				btfsc			PORTD,4,0
				movlw			0x08
				movf			WREG,0,0				
				bz				NoTec*/
			
			//Si se detecta una tecla presionada, W será distinta de cero y se guarda en Temp_Tec su valor sumado al de Columna
				Temp_Tec = Aux + Columna;
				/*addwf			Columna,0,1   // Sumo el valor de W + Columna.
				movwf			Temp_Tec,1    // Guardar W + Columna en Temp_Tec*/
	
NoTec:				
			//Incrementar Columna. Si ha llegado a su valor máximo (número de salidas), ponerla en cero.
				Columna++;
				if (!(Columna > NumeroDeColumnas))
					goto NoPCe;
				Columna = 0;
				if (Temp_Tec != 0)
					goto SiTec;
				Last_Tec = 0;
				Ult_Tec = 0;
				Pres_Tec = 0;
				goto NoPCe;
				/*incf			Columna,1,1	  
				movlw			0x02					// Poner en W el valor máximo de Columna (número de salidas)
				cpfsgt		Columna,1			//¿Es Columna mayor que su máximo valor?
				goto			NoPCe					//Si Columna es menor que su valor máximo, salir de la Rutina					
				clrf			Columna,1			
			tstfsz		Temp_Tec,1			//Si Temp_Tec es distinto de cero, es porque hay una tecla presionada
			goto			SiTec						//Entonces saltar a SiTec (Si hay Tecla)
			clrf			Last_Tec,1			//Si Temp_Tec es cero, no hay tecla presionada y se borra Last_Tec
			clrf			Ult_Tec,1
			clrf			Pres_Tec,1		
			goto			NoPCe*/
	
SiTec:
			//Restar a Temp_Tec el número de columnas
				Temp_Tec = Temp_Tec - NumeroDeColumnas;
				if (Temp_Tec != Last_Tec)
					goto No_LEqu;
				Ult_Tec = Pres_Tec;
				Pres_Tec == Temp_Tec;
				Aux = 0;
				/*movlw   	0x02							
				subwf			Temp_Tec,1,1
			movf			Temp_Tec,0,1
			cpfseq		Last_Tec,1				//Comparar Last_Tec con Temp_Tec para ver si son iguales
			goto			No_LEqu						//Si las dos son iguales, se da como válida a Temp_Tec.
			movff			Pres_Tec,Ult_Tec	//Guardar la última tecla presionada antes de modificarla
			movwf			Pres_Tec,1				
			clrf			WREG,0*/
	
No_LEqu:
			Last_Tec = Aux;
			Temp_Tec = 0;
			/*movwf			Last_Tec,1    		//Si no fue igual, guarda en Last_Tec, para que en la prox vez lo compare bien.
			clrf			Temp_Tec,1*/
			
	
NoPCe:
			if (Ult_Tec != Pres_Tec) //Si la última tecla presionada es distinta de la que acabo de presionar
			{
				New_Tec = Pres_Tec;
				New_Tec_Aux = Pres_Tec;
				Ult_Tec = Pres_Tec;
			}
			TRISB = ValTrisB;
			PORTB = ValPORTB; 
			return ;
	}

	/*Función/Rutina Teclas------------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que evalúa el valor de New_Tec (la tecla presionada) y toma una acción en función de éste 
	Entrada: nada
	Salida: nada
	//-------------------------------------------------------------------------------------------------------------------------------------*/
		void RutinaTeclas(void)
		{
			switch (New_Tec) // ¿Que tecla presione?
			{
				case _TeclaOK:
					Nop();
					break;
				case _TeclaArriba: 
					Nop();
					break;
				case _TeclaAbajo: 
					Nop();
					break;
				case _TeclaDerecha:
					Nop();
					break;
				case _TeclaIzquierda:
					Nop();
					break;
				case _TeclaPausa:
					Nop();
					break;
			}
			New_Tec = _NoTecla;
		}
