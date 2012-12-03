#include "StringEdit.h"

//comienzo de stringEdit
#ifdef STRING_EIDT

//VARIABLES
struct StringEdit StrEd0;
struct StringEdit StrEd1;
struct StringEdit StrEd2;
struct StringEdit StrEd3;

char cadenaStrEd0[NUM_ELEM_STR_ED_0];
char cadenaStrEd1[NUM_ELEM_STR_ED_1];
char cadenaStrEd2[NUM_ELEM_STR_ED_2];
char cadenaStrEd3[NUM_ELEM_STR_ED_3];

//FUNCIONES
/*Función StrEd_AvFocoElem------------------------------------------------------------------------------------------------------------------------
Descripción: función que incrementa el índice de foco de los elementos de un StringEdit
Entrada:
		ptrStrEd: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void StrEd_AvFocoElem()
{
	//Borrar cursor dibujado, o no, en el elemento actual antes de cambiar el foco al de la derecha
	GLCD_Relleno(	ptrStrEd->posX + GROSOR_BORDE_STR_ED + ptrStrEd->indFocoElem * ((ANCHO_ELEM_STR_ED * ptrStrEd->tamanioTexto) + SEP_ELEM_STR_ED + ptrStrEd->tamanioTexto - 1)
							, ptrStrEd->posY + 1
							, (ANCHO_ELEM_STR_ED * ptrStrEd->tamanioTexto)
							, ANCHO_CURSOR_STR_ED
							, COLOR_FONDO_DEF);
	ptrStrEd->bCursorDib = 0;	//El cursor ya no está
	
	//Incrementar índice de foco del StringEdit
	if ((ptrStrEd->offset + ptrStrEd->numElemVis) < ptrStrEd->numElem) //Si todavía no se ha llegado al final de la cadena
	{
		if ((ptrStrEd->indFocoElem + 1) == ptrStrEd->numElemVis)	//¿El índice de foco pasará a un elemento que no está graficado?
		{
			ptrStrEd->offset++;	//Incrementamos el offset para graficar el elemento que ahora tiene el foco 
			ptrStrEd->bRedibujar = 1; //Indicamos que es necesario redibujar todo
		}
		else
			ptrStrEd->indFocoElem++;
	}	
	else
		if (ptrStrEd->indFocoElem < (ptrStrEd->numElemVis - 1))
			ptrStrEd->indFocoElem++;
}//end StrEd_AvFocoElem

/*Función StrEd_RetFocoElem------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que decrementa el índice de foco de los elementos de un StringEdit
Entrada: 
		ptrStrEd: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void StrEd_RetFocoElem()
{
	//Borrar cursor dibujado, o no, en el elemento actual antes de cambiar el foco al de la izquierda
	GLCD_Relleno(	ptrStrEd->posX + GROSOR_BORDE_STR_ED + ptrStrEd->indFocoElem * ((ANCHO_ELEM_STR_ED * ptrStrEd->tamanioTexto) + SEP_ELEM_STR_ED + ptrStrEd->tamanioTexto - 1)
							, ptrStrEd->posY + 1
							, (ANCHO_ELEM_STR_ED * ptrStrEd->tamanioTexto)
							, ANCHO_CURSOR_STR_ED
							, COLOR_FONDO_DEF);
	ptrStrEd->bCursorDib = 0;	//El cursor ya no está
	
	//Decrementar índice de foco de los elementos del StringEdit
	if ((ptrStrEd->indFocoElem + ptrStrEd->offset) != 0)	//¿El índice de foco NO está en el primer elemento (valor mínimo o comienzo de la cadena)?
	{
		if (ptrStrEd->indFocoElem == 0)	//¿El índice de foco pasará a un elemento que no está graficado?
		{
			ptrStrEd->offset--;
			ptrStrEd->bRedibujar = 1; //Indicamos que es necesario redibujar todo
		}
		else
			ptrStrEd->indFocoElem--;
	}
}//end StrEd_RetFocoElem

/*Función StrEd_SetString------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que setea la cadena de texto de un StringEdit alfanumerico en funcion de una cadena pasada como argumento
Entrada: 
		ptrStrEd: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
		ptrString: Cadena (terminada en NULL) a copiar en el StringEdit
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void StrEd_SetString( char *ptrString)
{
	unsigned char i;

	for(i=0;(ptrString[i]!=0) && (i <= ptrStrEd->numElem);i++) //Mientras que el elemento no sea nulo...
		ptrStrEd->ptrCadena[i] = ptrString[i];
}//end StrEd_SetString

/*Función StrEd_SetCaractSup------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que incrementa el valor del elemento/caracter que tiene el foco 
Entrada: 
		ptrStrEd: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
-------------------------------------------------------------------------------------------------------------------------------------*/
void StrEd_SetElemSup()
{
	signed int valor;
	
	//Incrementamos el elemento/caracter de la cadena que tiene el foco
	ptrStrEd->ptrCadena[ptrStrEd->offset + ptrStrEd->indFocoElem]++;
	//Verificamos que el nuevo elemento/caracter cae dentro del rango de caracteres admitidos por un StringEdit Alfanumérico
	if (ptrStrEd->ptrCadena[ptrStrEd->offset + ptrStrEd->indFocoElem] > Z_ASCII)	//¿Se excedió el rango?
		ptrStrEd->ptrCadena[ptrStrEd->offset + ptrStrEd->indFocoElem] = ESPACIO_ASCII; //Seteamos el espacio
	//Indicar que se actualice el elemento que fue modificado
	ptrStrEd->indActualiz = ptrStrEd->offset + ptrStrEd->indFocoElem;
}//end StrEd_SetElemSup

/*Función StrEd_SetElemInf------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que decrementa el valor del elemento que tiene el foco 
Entrada: 
		ptrStrEd: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
-------------------------------------------------------------------------------------------------------------------------------------*/
void StrEd_SetElemInf()
{
	unsigned char i;

	//Decrementamos el elemento/caracter de la cadena que tiene el foco
	ptrStrEd->ptrCadena[ptrStrEd->offset + ptrStrEd->indFocoElem]--;
	//Verificamos que el nuevo elemento/caracter cae dentro del rango de caracteres admitidos por un StringEdit Alfanumérico
	if (ptrStrEd->ptrCadena[ptrStrEd->offset + ptrStrEd->indFocoElem] < ESPACIO_ASCII)	//¿Se excedió el rango?
		ptrStrEd->ptrCadena[ptrStrEd->offset + ptrStrEd->indFocoElem] = Z_ASCII; 
	//Indicar que se actualice el elemento que fue modificado
	ptrStrEd->indActualiz = ptrStrEd->offset + ptrStrEd->indFocoElem;
}

/*Función StrEd_OnKeyPress------------------------------------------------------------------------------------------------------------------------
Descripción: 	evento ejecutado cuando se pulsa una tecla mientras el StringEdit n tiene el foco 
Entrada: 
		ptrStrEd: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
-------------------------------------------------------------------------------------------------------------------------------------*/
void StrEd_OnKeyPress()
{
	switch (teclado.teclaPulsada)
	{
		case TECLA_ACEPTAR:
			if (ptrStrEd->bEditando == 1)	//¿El StringEdit está siendo editado?
			{
				//Seteo el StringEdit para que la próxima vez que sea editado, se comience por el primer caracter
				ptrStrEd->offset = 0;
				ptrStrEd->indFocoElem = 0;
				
				ptrStrEd->bEditando = 0;	//Salimos del modo de edición
				ptrStrEd->bRedibujar = 1;	//Redibujamos el StringEdit para reflejar los cambios
			} 
			else	//El StringEdit no está siendo editado
			{
				ptrStrEd->bEditando = 1; //Entramos en el modo de edición
				ptrStrEd->bRedibujar = 1;	//Redibujamos el StringEdit para reflejar los cambios
			}
			break;

		case TECLA_CANCELAR:
			if (ptrStrEd->bEditando == 1)	//¿El StringEdit está siendo editado?
			{
				//Seteo el StringEdit para que la próxima vez que sea editado, se comience por el primer caracter
				ptrStrEd->offset = 0;
				ptrStrEd->indFocoElem = 0;
	
				ptrStrEd->bEditando = 0;	//Salimos del modo de edición
				ptrStrEd->bRedibujar = 1;	//Redibujamos el StringEdit para reflejar los cambios
			} 
			break;

		case TECLA_ARRIBA:
			if (ptrStrEd->bEditando == 1)	//¿El StringEdit está siendo editado?
				StrEd_SetElemSup();
			else
			{
				RetrocederFoco();
				//Seteo el StringEdit para que la próxima vez que sea editado, se comience por el primer caracter
				ptrStrEd->offset = 0;
				ptrStrEd->indFocoElem = 0;
			}
			break;

		case TECLA_ABAJO:
			if (ptrStrEd->bEditando == 1)	//¿El StringEdit está siendo editado?
				StrEd_SetElemInf();
			else
			{
				AvanzarFoco();
				//Seteo el StringEdit para que la próxima vez que sea editado, se comience por el primer caracter
				ptrStrEd->offset = 0;
				ptrStrEd->indFocoElem = 0;
			}
			break;

		case TECLA_DERECHA:
			if (ptrStrEd->bEditando == 1)	//¿El StringEdit está siendo editado?
				StrEd_AvFocoElem();
			break;

		case TECLA_IZQUIERDA:
			if (ptrStrEd->bEditando == 1)	//¿El StringEdit está siendo editado?
				StrEd_RetFocoElem();
			break;
	}
}


/*Función StrEd_TitCursor------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que hace titilar el cursor del StringEdit que tiene el foco 
Entrada: 
		ptrStrEd: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void StrEd_TitCursor()
{
	unsigned char color;

	contTitileo++;
	if (contTitileo >= TITILEO_CURSOR_STR_ED)
	{
		if (ptrStrEd->bCursorDib == 1) //¿Está dibujado el cursor?
		{
			color = COLOR_FONDO_DEF;
			ptrStrEd->bCursorDib = 0;	//El cursor ya no está
			contTitileo = 0;	//reseteamos la cuenta
		}	 
		else
		{
			color = !COLOR_FONDO_DEF;
			ptrStrEd->bCursorDib = 1;	//El cursor está dibujado
			contTitileo = 0;	//reseteamos la cuenta
		}
		//Borramos o dibujamos el cursor
		GLCD_Relleno(	ptrStrEd->posX + GROSOR_BORDE_STR_ED + ptrStrEd->indFocoElem * ((ANCHO_ELEM_STR_ED * ptrStrEd->tamanioTexto) + SEP_ELEM_STR_ED + ptrStrEd->tamanioTexto - 1)
								, ptrStrEd->posY + 1
								, (ANCHO_ELEM_STR_ED * ptrStrEd->tamanioTexto) 
								, ANCHO_CURSOR_STR_ED
								, color);
	}
}

/*Función StrEd_Actualizar------------------------------------------------------------------------------------------------------------------------
Descripción: función encargada de dibujar o actualizar los StringEdits 
Entrada: 
		ptrStrEd: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void StrEd_Actualizar()
{
	unsigned char i;
	unsigned char offsetX;
	unsigned char color;
	
	if (ptrStrEd->bEditando == 1)	//¿El StringEdit está siendo editado?
	{
		if (ptrStrEd->bRedibujar == 1) //¿Es necesario redibujar todo el StringEdit?
			color = COLOR_FONDO_DEF;
		else	//Si no es necesario redibujar todo el StringEdit, veo si es necesario actualizarlo
			if (ptrStrEd->indActualiz != NO_ACTUALIZAR_STR_ED)	//¿Hay algún elemento para actualizar?
			{
				//Comprobar que el elemento que hay que actualizar cae dentro del rango visible
				if ( (ptrStrEd->indActualiz >= ptrStrEd->offset) && (ptrStrEd->indActualiz < (ptrStrEd->offset + ptrStrEd->numElemVis)))
				{
					//Limpiar el área donde se va a dibujar el elemento del StringEdit
					GLCD_Relleno(	ptrStrEd->posX + (ptrStrEd->indActualiz - ptrStrEd->offset) * ((ANCHO_ELEM_STR_ED * ptrStrEd->tamanioTexto) + (SEP_ELEM_STR_ED + ptrStrEd->tamanioTexto - 1))
											, ptrStrEd->posY
											, (ANCHO_ELEM_STR_ED * ptrStrEd->tamanioTexto) + (SEP_ELEM_STR_ED + ptrStrEd->tamanioTexto - 1)
											, ANCHO_CURSOR_STR_ED + GROSOR_BORDE_STR_ED + (ALTO_ELEM_STR_ED * ptrStrEd->tamanioTexto)
											, COLOR_FONDO_DEF);
					//Dibujar el elemento del StringEdit
					cadenaAux[0] = ptrStrEd->ptrCadena[ptrStrEd->indActualiz];
					cadenaAux[1] = 0; //Hacemos que la cadena termine en NULL
					GLCD_RendString57(	ptrStrEd->posX + (ptrStrEd->indActualiz - ptrStrEd->offset) * ((ANCHO_ELEM_STR_ED * ptrStrEd->tamanioTexto) + SEP_ELEM_STR_ED + ptrStrEd->tamanioTexto - 1) + GROSOR_BORDE_STR_ED
														, ptrStrEd->posY + (6 * ptrStrEd->tamanioTexto) + ANCHO_CURSOR_STR_ED + GROSOR_BORDE_STR_ED
														, cadenaAux
														, ptrStrEd->tamanioTexto
														, !COLOR_FONDO_DEF);	
				}
				ptrStrEd->indActualiz = NO_ACTUALIZAR_STR_ED;	//Indico que el StringEdit ya se actualizó o no es necesario actualizarlo
			}	
		//Titileo de cursores de los StringEdit
		StrEd_TitCursor();

	}
	else	//El StringEdit no está siendo editado
	{
		if (ptrStrEd->bEnFoco == 1)	//¿El StringEdit tiene el foco?
		{
			if (ptrStrEd->bRedibujar == 1) //¿Es necesario redibujar todo el StringEdit?
				color = !COLOR_FONDO_DEF;
		}
		else	//El StringEdit no tiene el foco
		{
			if (ptrStrEd->bRedibujar == 1) //¿Es necesario redibujar todo el StringEdit?
				color = COLOR_FONDO_DEF;
		}
	}

	if (ptrStrEd->bRedibujar == 1)
	{
		//Limpiar el area donde se va a dibujar el StringEdit
		GLCD_Relleno(	ptrStrEd->posX
								, ptrStrEd->posY
								, ((ANCHO_ELEM_STR_ED * ptrStrEd->tamanioTexto) * ptrStrEd->numElemVis) + (ptrStrEd->numElemVis - 1) * (SEP_ELEM_STR_ED + ptrStrEd->tamanioTexto - 1) + 2 * GROSOR_BORDE_STR_ED
								, ANCHO_CURSOR_STR_ED + GROSOR_BORDE_STR_ED + (ALTO_ELEM_STR_ED * ptrStrEd->tamanioTexto) + GROSOR_BORDE_STR_ED
								, color);
		//Ahora dibujamos el StringEdit
		offsetX = ptrStrEd->posX + GROSOR_BORDE_STR_ED;
		for(i = ptrStrEd->offset; i < (ptrStrEd->offset + ptrStrEd->numElemVis); i++)	
		{
			cadenaAux[0] = ptrStrEd->ptrCadena[i];
			cadenaAux[1] = 0; //Hacemos que la cadena termine en NULL
			GLCD_RendString57(	offsetX
												, ptrStrEd->posY + (6 * ptrStrEd->tamanioTexto) + ANCHO_CURSOR_STR_ED + GROSOR_BORDE_STR_ED
												, cadenaAux, ptrStrEd->tamanioTexto
												, !color);
			offsetX = offsetX + (ANCHO_ELEM_STR_ED * ptrStrEd->tamanioTexto) + SEP_ELEM_STR_ED + ptrStrEd->tamanioTexto - 1; 
		}
		ptrStrEd->bRedibujar = 0;	//El StringEdit ya ha sido redibujado
	}

}

#endif	//end tringEdit
