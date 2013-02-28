
//INCLUDES
#include "teclado.h"

//DECLARACION DE VARIABLES
struct Teclado teclado;

//VARIABLES DE ProcesoTeclado()
unsigned int valTrisDPT;
unsigned int valPortDPT;

//DEFINICIÓN DE FUNCIONES
/*IniTeclado------------------------------------------------------------------------------------------------------------------------
Descripción: Función que inicializa las variables, estructuras, puertos, etc del teclado 
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void IniTeclado(void)
{
	//Inicialización de las variables de teclado
	teclado.columna	=	0;			
	teclado.teclaPulsada = TECLA_NO_PRES;
	teclado.teclaSostenida = TECLA_NO_PRES;
	teclado.teclaAnterior = TECLA_NO_PRES;
	teclado.cuentaAntirreb = 0;
	teclado.periodoIncremento = PERIODO_INCR_0;

	//Inicialización del puerto de teclado
	AD1PCFGLbits.PCFG12 = 1;	//RB12 - GLCD_D4
	AD1PCFGLbits.PCFG11 = 1;	//RB13 - GLCD_D5
	AD1PCFGLbits.PCFG10 = 1;	//RB14 - GLCD_D6
	AD1PCFGLbits.PCFG9 = 1;		//RB15 - GLCD_D7
	
}	//Fin IniTeclado()

//DEFINICIÓN DE FUNCIONES
/*Proceso Teclado------------------------------------------------------------------------------------------------------------------------
Descripción: Proceso que barre el teclado matricial buscando cual tecla ha sido presionada. Y luego asigna a Tecla_Presionada el valor de la tecla presionada 
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ProcesoTeclado(void)
{
	/*unsigned int valTrisDPT;
	unsigned int valPortDPT;*/
	
	//Salvar estado en que se encuentra el puerto
	valPortDPT = PUERTO_TECLADO;
	valTrisDPT = TRIS_PUERTO_TECLADO; 
	//Configuración de los puertos como entrada o salida
	TRIS_PUERTO_TECLADO = TRIS_PUERTO_TECLADO & 0xF0FF;	//Seteamos las salidas
	TRIS_PUERTO_TECLADO = TRIS_PUERTO_TECLADO | 0xF000;	//Seteamos  las entradas
	DelayTcy(100);	//Delay100TCYx(1);	//Delay_10useg();	//Hago una demora para que se estabilicen los valores del puerto D en cero y se anulen los transitorios. Sin esta demora no funciona						

	//Apagar todas las salidas
	salida0 = 0;    
	salida1 = 0;
	salida2 = 0;
	salida3 = 0;

	//Poner en 1 una de las salidas dependiendo del valor de Columna
	switch (teclado.columna)
	{
		case 0:
			salida0 = 1;
			break;
		case 1:
			salida1 = 1;
			break;
		case 2:
			salida2 = 1;
			break;
		case 3:
			salida3 = 1;
			break;
	}

	//Recorrer las entradas preguntando si están en 1 y setear Aux_Fila a un valor dependiendo de cual este activada
	teclado.auxFila = TECLA_NO_PRES;
	if (entrada0 == 1)
		teclado.auxFila = 0;
	if (entrada1 == 1)
		teclado.auxFila = 4; //Esto se calcula como: (NumMaxCol + 1) * NumeroDeFila;
	if (entrada2 == 1)
		teclado.auxFila = 8; //Esto se calcula como: (NumMaxCol + 1) * NumeroDeFila;
	if (entrada3 == 1)
		teclado.auxFila = 12; //Esto se calcula como: (NumMaxCol + 1) * NumeroDeFila;
	
	//Detectar si se presionó una tecla
	if (teclado.auxFila != TECLA_NO_PRES)	//SI se presionó una tecla
	{	
		teclado.teclaActual = teclado.columna + teclado.auxFila; //Calcular la tecla
		//Verificar si es o no igual a la última tecla presionada
		if (teclado.teclaActual == teclado.teclaAnterior) //SI son iguales
		{
			teclado.cuentaAntirreb++;	//Incrementar el contador de verificaciones antirrebote
			if (teclado.cuentaAntirreb == ANTIRREBOTE) //Si ya se han cumplido las verificaciones antirrebote
			{
				teclado.cuentaAntirreb = 0;
				if (teclado.teclaSostenida == TECLA_NO_PRES)		//Esto se hace para evitar que una misma tecla sea tomada dos veces al mantenerla apretada
				{
					teclado.teclaPulsada = teclado.teclaAnterior;
					teclado.teclaSostenida = teclado.teclaAnterior;
					//reseteo de variable de tecla sostenida
					teclado.contTeclaSostenida = 0;
					//reseteo de variables de aceleracion
					teclado.velIncremento = 0;
					teclado.contIncremento = 0;
					teclado.bHabIncremento = 0;

					//Actualizar estructura de teclas
					switch (teclado.teclaAnterior)
					{
						case TECLA_ACEPTAR:
							teclado.aceptar.bPulsada = 1;
							teclado.aceptar.bSostenida = 1;
							break;
						case TECLA_CANCELAR:
							teclado.aceptar.bPulsada = 1;
							teclado.aceptar.bSostenida = 1;
							break;
						case TECLA_ARRIBA:
							teclado.aceptar.bPulsada = 1;
							teclado.aceptar.bSostenida = 1;
							break;
						case TECLA_ABAJO:
							teclado.aceptar.bPulsada = 1;
							teclado.aceptar.bSostenida = 1;
							break;
						case TECLA_DERECHA:
							teclado.aceptar.bPulsada = 1;
							teclado.aceptar.bSostenida = 1;
							break;
						case TECLA_IZQUIERDA:
							teclado.aceptar.bPulsada = 1;
							teclado.aceptar.bSostenida = 1;
							break;	 		
							
						////////////////////////////////////// CODIGO DE PRUEBA
						case 3:
							if (sd.bSDInic == 1) //¿La SD se encuentra presente e inicializada?
							{
					    	adqui.nroMuestra = 1;
					    	OpenNewMed();
					   	 	//adqui.bGuardarEnSD = 1;
					    	GLCD_Relleno(120,58,4,4,BLANCO);
							}
							break;
						case 2:
							if (sd.bSDInic == 1) //¿La SD se encuentra presente e inicializada?
							{
					    	FSfclose(sd.pNewFile);
								//adqui.bGuardarDatos = 0;
					    	GLCD_Relleno(120,58,4,4,NEGRO);
							}
							break;
						case 1:
							MostrarMsg("Hola mundo!!!", "jas", 50, 4);
							break;
						//////////////////////////////////////	*/
					}	
				}	
				else
				{
					teclado.contTeclaSostenida++;	//Detecté nuevamente que la tecla está sostenida
					switch (teclado.velIncremento)
					{
						case 0:
							if (teclado.contTeclaSostenida >= ESPERA_VEL_0)
							{
								teclado.periodoIncremento = PERIODO_INCR_1;
								teclado.contTeclaSostenida = 0;
								teclado.velIncremento++;
							}
							break;
						case 1:
							if (teclado.contTeclaSostenida >= ESPERA_VEL_1)
							{
								teclado.periodoIncremento = PERIODO_INCR_2;
								teclado.contTeclaSostenida = 0;
								teclado.velIncremento++;
							}
							break;
						case 2:
							if (teclado.contTeclaSostenida >= ESPERA_VEL_2)
							{
								teclado.periodoIncremento = PERIODO_INCR_3;
								teclado.contTeclaSostenida = 0;
								teclado.velIncremento++;
							}
							break;
						case 3:
							if (teclado.contTeclaSostenida >= ESPERA_VEL_3)
							{
								teclado.periodoIncremento = PERIODO_INCR_4;
								teclado.contTeclaSostenida = 0;
								teclado.velIncremento++;
							}
							break;
						case 4:
							if (teclado.contTeclaSostenida >= ESPERA_VEL_4)
							{
								teclado.periodoIncremento = PERIODO_INCR_5;
								teclado.contTeclaSostenida = 0;
								teclado.velIncremento++;
							}
							break;
						case 5:
							if (teclado.contTeclaSostenida >= ESPERA_VEL_5)
							{
								teclado.periodoIncremento = PERIODO_INCR_6;
								teclado.contTeclaSostenida = 0;
								teclado.velIncremento++;
							}
							break;
						default:	//Acá va a caer cuando teclado.velIncremento valga 7, y no va a hacerse nada
							break;
					}
					//teclado.contTeclaSostenida = 0;
					//teclado.velIncremento++;
				}
			}
		}
		else	//NO son iguales
		{
			teclado.teclaAnterior = teclado.teclaActual;
		}				
	}
	else	//NO se presionó una tecla
	{
		teclado.teclaPulsada = TECLA_NO_PRES;	//No se presionó ninguna tecla
		teclado.teclaSostenida  = TECLA_NO_PRES;	//No está siendo sostenida ninguna tecla
		teclado.columna++;	//Pasar a otra columna
		if (teclado.columna == NUM_COLUM)
			teclado.columna = 0;
		
		teclado.contTeclaSostenida = 0;	//Reseteo el contador de tecla sostenida
		teclado.velIncremento = 0;
		teclado.contIncremento = 0;
		teclado.bHabIncremento = 0;
		teclado.periodoIncremento = PERIODO_INCR_0;	
	}
	
	//Restaurar estado en que se encuentra el puerto
	TRIS_PUERTO_TECLADO = valTrisDPT;
	PUERTO_TECLADO = valPortDPT; 
}

