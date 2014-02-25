#include "SValEdit.h"

//comienzo sValEdit
#ifdef SVAL_EDIT

//VARIABLES
struct SValEdit SValEd0;
struct SValEdit SValEd1;
struct SValEdit SValEd2;
struct SValEdit SValEd3;

char cadenaSValEd0[NUM_ELEM_SVAL_ED_0];
char cadenaSValEd1[NUM_ELEM_SVAL_ED_1];
char cadenaSValEd2[NUM_ELEM_SVAL_ED_2];
char cadenaSValEd3[NUM_ELEM_SVAL_ED_3];

//FUNCIONES
/*Función SValEd_AvFocoElem------------------------------------------------------------------------------------------------------------------------
Descripción: función que incrementa el índice de foco de los elementos de un SValEdit
Entrada:
		ptrSValEd: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SValEd_AvFocoElem()
{
	//Borrar cursor dibujado, o no, en el elemento actual antes de cambiar el foco al de la derecha
	GLCD_Relleno(	ptrSValEd->posX + GROSOR_BORDE_SVAL_ED + ptrSValEd->indFocoElem * ((ANCHO_ELEM_SVAL_ED * ptrSValEd->tamanioTexto) + SEP_ELEM_SVAL_ED + ptrSValEd->tamanioTexto - 1)
							, ptrSValEd->posY + 1
							, (ANCHO_ELEM_SVAL_ED * ptrSValEd->tamanioTexto)
							, ANCHO_CURSOR_SVAL_ED
							, COLOR_FONDO_DEF);
	ptrSValEd->bCursorDib = 0;	//El cursor ya no está
	
	//Incrementar índice de foco del SValEdit
	if (ptrSValEd->indFocoElem < (ptrSValEd->numElem - 1))	//Todavía no llegue al final del SValEdit
		ptrSValEd->indFocoElem++;
}//end SValEd_AvFocoElem

/*Función SValEd_RetFocoElem------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que decrementa el índice de foco de los elementos de un SValEdit
Entrada: 
		ptrSValEd: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SValEd_RetFocoElem()
{
	//Borrar cursor dibujado, o no, en el elemento actual antes de cambiar el foco al de la izquierda
	GLCD_Relleno(	ptrSValEd->posX + GROSOR_BORDE_SVAL_ED + ptrSValEd->indFocoElem * ((ANCHO_ELEM_SVAL_ED * ptrSValEd->tamanioTexto) + SEP_ELEM_SVAL_ED + ptrSValEd->tamanioTexto - 1)
							, ptrSValEd->posY + 1
							, (ANCHO_ELEM_SVAL_ED * ptrSValEd->tamanioTexto)
							, ANCHO_CURSOR_SVAL_ED
							, COLOR_FONDO_DEF);
	ptrSValEd->bCursorDib = 0;	//El cursor ya no está
	
	//Decrementar índice de foco de los elementos del SValEdit
	if (ptrSValEd->indFocoElem > 0)	
		ptrSValEd->indFocoElem--;
}//end SValEd_RetFocoElem

/*Función SValEd_GetValor------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que devuelve la cadena del SValEdit en forma de un int, es  decir, el valor númerico que representa 
Entrada: 
		ptrSValEd: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: 
		int formado por cadena
//-------------------------------------------------------------------------------------------------------------------------------------*/
signed int SValEd_GetValor()
{
	signed int valor;
	unsigned int despDeComa;
	unsigned char i, j;

	valor = 0;
	despDeComa = 1;

	//Calcular valor que representa la cadena del SValEdit
	for(i=ptrSValEd->numElem - 1;i>0;i--)
	{
		valor = valor + (ptrSValEd->ptrCadena[i] - CERO_ASCII) * despDeComa;
		//Calcular 10^(i-1) (desplazador de coma)
		despDeComa = despDeComa * 10;
	}
		
	//Asignamos el signo correspondiente
	if (ptrSValEd->bSignoPos == 0)
		valor = -valor;

	return valor;
}//end SValEd_GetValor

/*Función SValEd_SetValor------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que descompone valor en sus respectivos caracteres y los copia a la cadena del SValEdit  
Entrada: 
	ptrSValEd: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
	valor: int que se copia la cadena del  SValEdit
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SValEd_SetValor( signed int valor)
{
	signed char i;

	if ((valor <= ptrSValEd->valMax) && (valor >= ptrSValEd->valMin)) //¿Cae valor dentro del rango del SValEdit?
	{
		BinBCD(valor);	//Descomponemos valor en unidad, decena, etc y almacenamos estos valores en el arregllo global BCD
		for (i=ptrSValEd->numElem - 1;i>0;i--)
			ptrSValEd->ptrCadena[i] = BCD[ptrSValEd->numElem - i - 1];
		
		//Poner signo
		if (signo == -1)
		{
			ptrSValEd->ptrCadena[0] = MENOS_ASCII; //Colocamos el signo menos para indicar que el número es negativo	
			ptrSValEd->bSignoPos = 0;
		}
		else
		{
			ptrSValEd->ptrCadena[0] = ESPACIO_ASCII; //Colocamos un espacio donde iría el signo negativo	
			ptrSValEd->bSignoPos = 1;
		}
		ptrSValEd->bRedibujar;	//Redibujamos el SValEdit por completo
		
		//Seteo el SValEdit para que la próxima vez que sea editado, se comience por la unidad
		ptrSValEd->indFocoElem = ptrSValEd->numElem - 1;

		ptrSValEd->bRedibujar = 1;	//Redibujar todo de nuevo
	}
}//end SValEd_SetValor

/*Función SValEd_SetElemSup------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que incrementa el valor del elemento/caracter que tiene el foco 
Entrada: 
		ptrSValEd: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SValEd_SetElemSup()
{
	signed int valor;
	
	if ((ptrSValEd->ptrCadena[ptrSValEd->indFocoElem] != MENOS_ASCII) && (ptrSValEd->ptrCadena[ptrSValEd->indFocoElem] != ESPACIO_ASCII)) //¿NO estamos en el elemento correspondiente al signo?
	{ 
		//Incrementamos el elemento/caracter de la cadena que tiene el foco
		ptrSValEd->ptrCadena[ptrSValEd->indFocoElem]++;
		//Verificamos que el nuevo elemento/caracter cae dentro del rango de caracteres admitidos por un SValEdit Numérico
		if (ptrSValEd->ptrCadena[ptrSValEd->indFocoElem] > NUEVE_ASCII)	//¿Se excedió el rango?
		{
			//Seteamos el cero para el elemento actual, incrementamos el siguiente y ordenamos que se redibuje todo
			ptrSValEd->ptrCadena[ptrSValEd->indFocoElem] = CERO_ASCII; //Seteamos el espacio
		}
		//Verificamos que el nuevo valor que toma el SValEdit cae dentro de su rango, si no es así, seteamos un cero 
		if (!((SValEd_GetValor() <= ptrSValEd->valMax) && (SValEd_GetValor() >= ptrSValEd->valMin)))
			ptrSValEd->ptrCadena[ptrSValEd->indFocoElem] = CERO_ASCII;
	}
	else
	{
		if (ptrSValEd->ptrCadena[0] == MENOS_ASCII)
		{
			ptrSValEd->ptrCadena[0] = ESPACIO_ASCII;
			SValEd_SetValor(ptrSValEd->valMax); //Seteamos el valor máximo
		}
		else
		{
			ptrSValEd->ptrCadena[0] = MENOS_ASCII;
			SValEd_SetValor(ptrSValEd->valMin);	//Seteamos el valor mínimo
		}
	}

	//Indicar que se actualice el SValEdit
	ptrSValEd->bRedibujar = 1;
}//end SValEd_SetElemSup

/*Función SValEd_SetElemInf------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que decrementa el valor del elemento que tiene el foco 
Entrada: 
		ptrSValEd: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SValEd_SetElemInf()
{
	unsigned char i;

	if ((ptrSValEd->ptrCadena[ptrSValEd->indFocoElem] != MENOS_ASCII) && (ptrSValEd->ptrCadena[ptrSValEd->indFocoElem] != ESPACIO_ASCII)) //¿NO estamos en el elemento correspondiente al signo?
	{ 
		//Decrementamos el elemento/caracter de la cadena que tiene el foco
		ptrSValEd->ptrCadena[ptrSValEd->indFocoElem]--;
		//Verificamos que el nuevo elemento/caracter cae dentro del rango de caracteres admitidos por un SValEdit Numérico
		if (ptrSValEd->ptrCadena[ptrSValEd->indFocoElem] < CERO_ASCII)	//¿Se excedió el rango?
		{
			//Si no es así, buscamos el mayor  de los valores que cumpla el rango
			for(i=0;i<10;i++)
			{
				ptrSValEd->ptrCadena[ptrSValEd->indFocoElem] = NUEVE_ASCII - i;
				if ((SValEd_GetValor() <= ptrSValEd->valMax) && (SValEd_GetValor() >= ptrSValEd->valMin))
					break;	//Cumplió, salimos del bucle
			}
		}
		else
			//Verificamos que el nuevo valor que toma el SValEdit cae dentro de su rango, si no es así, descartamos el cambio 
			if (!((SValEd_GetValor() <= ptrSValEd->valMax) && (SValEd_GetValor() >= ptrSValEd->valMin)))
				ptrSValEd->ptrCadena[ptrSValEd->indFocoElem]++;
	}
	else
	{
		if (ptrSValEd->ptrCadena[0] == MENOS_ASCII)
		{
			ptrSValEd->ptrCadena[0] = ESPACIO_ASCII;
			SValEd_SetValor(ptrSValEd->valMax); //Seteamos el valor máximo
		}
		else
		{
			ptrSValEd->ptrCadena[0] = MENOS_ASCII;
			SValEd_SetValor(ptrSValEd->valMin); //Seteamos el valor mínimo
		}
	}

	//Indicar que se actualice el SValEdit
	ptrSValEd->bRedibujar = 1;
}//end SValEd_SetElemInf

/*Función SValEd_OnKeyPress------------------------------------------------------------------------------------------------------------------------
Descripción: 	evento ejecutado cuando se pulsa una tecla mientras el SValEdit n tiene el foco 
Entrada: 
		ptrSValEd: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SValEd_OnKeyPress()
{
	switch (teclado.teclaPulsada)
	{
		case TECLA_ACEPTAR:
			if (ptrSValEd->bEditando == 1)	//¿El SValEdit está siendo editado?
			{
				//Seteo el SValEdit para que la próxima vez que sea editado, se comience por la unidad
				ptrSValEd->indFocoElem = ptrSValEd->numElem - 1;

				ptrSValEd->bEditando = 0;	//Salimos del modo de edición
				ptrSValEd->bRedibujar = 1;	//Redibujamos el SValEdit para reflejar los cambios
			} 
			else	//El SValEdit no está siendo editado
			{
				ptrSValEd->bEditando = 1; //Entramos en el modo de edición
				ptrSValEd->bRedibujar = 1;	//Redibujamos el SValEdit para reflejar los cambios
			}
			break;

		case TECLA_CANCELAR:
			if (ptrSValEd->bEditando == 1)	//¿El SValEdit está siendo editado?
			{
				//Seteo el SValEdit para que la próxima vez que sea editado, se comience por la unidad
				ptrSValEd->indFocoElem = ptrSValEd->numElem - 1;
				
				ptrSValEd->bEditando = 0;	//Salimos del modo de edición
				ptrSValEd->bRedibujar = 1;	//Redibujamos el SValEdit para reflejar los cambios
			} 
			break;

		case TECLA_ARRIBA:
			if (ptrSValEd->bEditando == 1)	//¿El SValEdit está siendo editado?
				SValEd_SetElemSup();
			else
			{
				RetrocederFoco();

				//Seteo el SValEdit para que la próxima vez que sea editado, se comience por la unidad
				ptrSValEd->indFocoElem = ptrSValEd->numElem - 1;
				
			}
			break;

		case TECLA_ABAJO:
			if (ptrSValEd->bEditando == 1)	//¿El SValEdit está siendo editado?
				SValEd_SetElemInf();
			else
			{
				AvanzarFoco();

				//Seteo el SValEdit para que la próxima vez que sea editado, se comience por la unidad
				ptrSValEd->indFocoElem = ptrSValEd->numElem - 1;
			}
			break;

		case TECLA_DERECHA:
			if (ptrSValEd->bEditando == 1)	//¿El SValEdit está siendo editado?
				SValEd_AvFocoElem();
			break;

		case TECLA_IZQUIERDA:
			if (ptrSValEd->bEditando == 1)	//¿El SValEdit está siendo editado?
				SValEd_RetFocoElem();
			break;
	}
}//end SValEd_OnKeyPress


/*Función SValEd_TitCursor------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que hace titilar el cursor del SValEdit que tiene el foco 
Entrada: 
		ptrSValEd: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SValEd_TitCursor()
{
	unsigned char color;

	contTitileo++;
	if (contTitileo >= TITILEO_CURSOR_SVAL_ED)
	{
		if (ptrSValEd->bCursorDib == 1) //¿Está dibujado el cursor?
		{
			color = COLOR_FONDO_DEF;
			ptrSValEd->bCursorDib = 0;	//El cursor ya no está
			contTitileo = 0;	//reseteamos la cuenta
		}	 
		else
		{
			color = !COLOR_FONDO_DEF;
			ptrSValEd->bCursorDib = 1;	//El cursor está dibujado
			contTitileo = 0;	//reseteamos la cuenta
		}
		//Borramos o dibujamos el cursor
		GLCD_Relleno(	ptrSValEd->posX + GROSOR_BORDE_SVAL_ED + ptrSValEd->indFocoElem * ((ANCHO_ELEM_SVAL_ED * ptrSValEd->tamanioTexto) + SEP_ELEM_SVAL_ED + ptrSValEd->tamanioTexto - 1)
								, ptrSValEd->posY + 1
								, (ANCHO_ELEM_SVAL_ED * ptrSValEd->tamanioTexto) 
								, ANCHO_CURSOR_SVAL_ED
								, color);
	}
}//end SValEd_TitCursor

/*Función SValEd_Actualizar------------------------------------------------------------------------------------------------------------------------
Descripción: función encargada de dibujar o actualizar los SValEdits 
Entrada: 
		ptrSValEd: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SValEd_Actualizar()
{
	unsigned char i;
	unsigned char offsetX;
	unsigned char color;

	if (ptrSValEd->bEditando == 1)	//¿El SValEdit está siendo editado?
	{
		if (ptrSValEd->bRedibujar == 1) //¿Es necesario redibujar todo el SValEdit?
			color = COLOR_FONDO_DEF;
		//Titileo de cursores de los SValEdit
		SValEd_TitCursor();
	}
	else	//El SValEdit no está siendo editado
	{
		if (ptrSValEd->bEnFoco == 1)	//¿El SValEdit tiene el foco?
		{
			if (ptrSValEd->bRedibujar == 1) //¿Es necesario redibujar todo el SValEdit?
				color = !COLOR_FONDO_DEF;
		}
		else	//El SValEdit no tiene el foco
		{
			if (ptrSValEd->bRedibujar == 1) //¿Es necesario redibujar todo el SValEdit?
				color = COLOR_FONDO_DEF;
		}
	}

	if (ptrSValEd->bRedibujar == 1)
	{
		offsetX = ptrSValEd->posX + GROSOR_BORDE_SVAL_ED;
		//Ahora dibujamos el SValEdit
		//Limpiar el area donde se va a dibujar el SValEdit
		GLCD_Relleno(	ptrSValEd->posX
								, ptrSValEd->posY
								, ((ANCHO_ELEM_SVAL_ED * ptrSValEd->tamanioTexto) * ptrSValEd->numElem) + (ptrSValEd->numElem - 1) * (SEP_ELEM_SVAL_ED + ptrSValEd->tamanioTexto - 1) + 2 * GROSOR_BORDE_SVAL_ED
								, ANCHO_CURSOR_SVAL_ED + GROSOR_BORDE_SVAL_ED + (ALTO_ELEM_SVAL_ED * ptrSValEd->tamanioTexto) + GROSOR_BORDE_SVAL_ED
								, color);
		for(i = 0; i < (ptrSValEd->numElem); i++)	
		{
			cadenaAux[0] = ptrSValEd->ptrCadena[i];
			cadenaAux[1] = 0; //Hacemos que la cadena termine en NULL
			GLCD_RendString57(	offsetX
												, ptrSValEd->posY + (6 * ptrSValEd->tamanioTexto) + ANCHO_CURSOR_SVAL_ED + GROSOR_BORDE_SVAL_ED
												, cadenaAux
												, ptrSValEd->tamanioTexto
												, !color);
			offsetX = offsetX + (ANCHO_ELEM_SVAL_ED * ptrSValEd->tamanioTexto) + SEP_ELEM_SVAL_ED + ptrSValEd->tamanioTexto - 1; 
		}
		ptrSValEd->bRedibujar = 0;	//El SValEdit ya ha sido redibujado
	}	
}//end SValEd_Actualizar

#endif //end sValEdit
