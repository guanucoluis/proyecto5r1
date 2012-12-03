#include "valEdit.h"

//comienzo valEdit
#ifdef VAL_EDIT

//VARIABLES DE ValEditEditar()
volatile unsigned char iVEE;
char cadenaTemp[9]; //toma el valor temporal del ValEdit hasta que se presione ACEPTAR

//VARIABLES de ValEditGetValor()
volatile signed int valorGV;
volatile unsigned int despDeComaGV;
volatile unsigned char iGV, jGV;

//VARIABLES DE ValEditSetValor()
volatile signed char iSV;
volatile signed int valorSV;

//VARIABLES DE ValEditActualizar()
volatile unsigned char iVEA;
volatile unsigned char offsetXVEA;
volatile unsigned char colorVEA;

//VARIABLES DE ValEditIncDigit()
//signed int valorVEID;
volatile unsigned char indCalculadoVEID;

//FUNCIONES
/*Función ValEditEditar------------------------------------------------------------------------------------------------------------------------
Descripción: función que incrementa el índice de foco de los elementos de un ValEdit
Entrada:
		ptrValEdit: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ValEditEditar(unsigned char accion)
{
	switch(accion)
	{
		case ENTRAR:
			c.valEdit.estado.bEditando = 1; //Entramos en el modo de edición
			c.valEdit.estado.bRedibujar = 1;	//Redibujamos el ValEdit para reflejar los cambios
			c.valEdit.bEntrandoEdicion = 1;	//Hacemos esto para que se redibuje todo el ValEdit
			//Creamos una copia de seguridad por si se cancela la edición
			for(iVEE = 0; iVEE < c.valEdit.cifras; iVEE++)
				cadenaTemp[iVEE] = c.valEdit.ptrDigitos[iVEE]; //Copiamos el valor del ValEdit en la variable temporal
			break;	
		case SALIR:
			//Seteo el ValEdit para que la próxima vez que sea editado, se comience por la unidad
			c.valEdit.offset = c.valEdit.cifras - c.valEdit.cifrasVis;
			c.valEdit.indFocoDigit = c.valEdit.cifrasVis - 1;

			c.valEdit.estado.bEditando = 0;	//Salimos del modo de edición
			c.valEdit.estado.bRedibujar = 1;	//Redibujamos el ValEdit para reflejar los cambios
			break;
		case CANCELAR:
			//Seteo el ValEdit para que la próxima vez que sea editado, se comience por la unidad
			c.valEdit.offset = c.valEdit.cifras - c.valEdit.cifrasVis;
			c.valEdit.indFocoDigit = c.valEdit.cifrasVis - 1;
			
			//Restauramos la copia de seguridad por si se cancela la edición
			for(iVEE = 0; iVEE < c.valEdit.cifras; iVEE++)
				c.valEdit.ptrDigitos[iVEE] = cadenaTemp[iVEE]; //Copiamos el valor de la variable temporal en el ValEdit
			
			c.valEdit.estado.bEditando = 0;	//Salimos del modo de edición
			c.valEdit.estado.bRedibujar = 1;	//Redibujamos el ValEdit para reflejar los cambios
			break;
		case IZQUIERDA:
			//Borrar cursor dibujado, o no, en el elemento actual antes de cambiar el foco al de la derecha
			contTitileo = TITILEO_CURSOR_VAL_ED; // forzamos 'contTitileo' y 'bCursurDib' para borrar cursor
			c.valEdit.bCursorDib = 1;
			ValEditTitCursor();
					
			ValEditLeft();
			break;
		case DERECHA:
			// Borrar cursor dibujado, o no, en el elemento actual antes de cambiar el foco al de la izquierda
			contTitileo = TITILEO_CURSOR_VAL_ED; // forzamos 'contTitileo' y 'bCursurDib' para borrar cursor
			c.valEdit.bCursorDib = 1;
			ValEditTitCursor();
			
			ValEditRight();
			break;
	}
}//fin ValEditEditar()

/*Función ValEditRight------------------------------------------------------------------------------------------------------------------------
Descripción: función que incrementa el índice de foco de los elementos de un ValEdit
Entrada:
		ptrValEdit: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ValEditRight()
{
	c.valEdit.bCursorDib = 0;	//El cursor ya no está
	
	//Incrementar índice de foco del ValEdit
	if ((c.valEdit.offset + c.valEdit.cifrasVis) < c.valEdit.cifras) //Si todavía no se ha llegado al final de la cadena
	{
		if ((c.valEdit.indFocoDigit + 1) == c.valEdit.cifrasVis)	//¿El índice de foco pasará a un elemento que no está graficado?
		{
			c.valEdit.offset++;	//Incrementamos el offset para graficar el elemento que ahora tiene el foco 
			c.valEdit.estado.bRedibujar = 1; //Indicamos que es necesario redibujar todo
		}
		else
			c.valEdit.indFocoDigit++;
	}	
	else
		if (c.valEdit.indFocoDigit < (c.valEdit.cifrasVis - 1))
			c.valEdit.indFocoDigit++;
}//fin ValEditRight()

/*Función ValEditLeft------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que decrementa el índice de foco de los elementos de un ValEdit
Entrada: 
		ptrValEdit: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ValEditLeft()
{
	c.valEdit.bCursorDib = 0;	//El cursor ya no está
	
	if (!(c.valEdit.bHabSigno == 0 && (c.valEdit.indFocoDigit + c.valEdit.offset == 1) ))
	{
		//Decrementar índice de foco de los elementos del ValEdit
		if ((c.valEdit.indFocoDigit + c.valEdit.offset) != 0)	//¿El índice de foco NO está en el primer elemento (valor mínimo o comienzo de la cadena)?
		{
			if (c.valEdit.indFocoDigit == 0)	//¿El índice de foco pasará a un elemento que no está graficado?
			{
				c.valEdit.offset--;
				c.valEdit.estado.bRedibujar = 1; //Indicamos que es necesario redibujar todo
			}
			else
				c.valEdit.indFocoDigit--;
		}
	}
}//fin ValEditLeft()

/*Función ValEditGetValor------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que devuelve la cadena del ValEdit en forma de un int, es  decir, el valor númerico que representa 
Entrada: 
		ptrValEdit: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: 
		int formado por cadena
//-------------------------------------------------------------------------------------------------------------------------------------*/
signed int ValEditGetValor()
{
	/*signed int valorGV;
	unsigned int despDeComaGV;
	unsigned char iGV, jGV;*/

	CargarObjetoGrafico();	//Cargamos el objeto gráfico en memoria

	valorGV = 0;
	despDeComaGV = 1;

	//Calcular valor que representa la cadena del ValEdit
	for(iGV=c.valEdit.cifras - 1;iGV>0;iGV--)
	{
		valorGV = valorGV + (c.valEdit.ptrDigitos[iGV] - CERO_ASCII) * despDeComaGV;
		//Calcular 10^(i-1) (desplazador de coma)
		despDeComaGV = despDeComaGV * 10;
	}
		
	//Asignamos el signo correspondiente
	if (c.valEdit.bSignoPos == 0)
		valorGV = 0 - valorGV;

	return valorGV;
}//fin ValEditGetValor()

/*Función ValEditSetValor------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que descompone valor en sus respectivos caracteres y los copia a la cadena del ValEdit  
Entrada: 
	ptrValEdit: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
	valor: int que se copia la cadena del  ValEdit
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ValEditSetValor(signed int valor)
{
	//signed char iSV;
	//signed int valorSV;

	CargarObjetoGrafico();	//Cargamos el objeto gráfico en memoria

	valorSV = valor;

	if ((valorSV <= c.valEdit.valMaxSigned.word) && (valorSV >= c.valEdit.valMinSigned.word)) //¿Cae valor dentro del rango del ValEdit?
	{
		BinBCD(valorSV);	//Descomponemos valor en unidad, decena, etc y almacenamos estos valores en el arregllo global BCD
		for (iSV=c.valEdit.cifras - 1;iSV>0;iSV--)
			c.valEdit.ptrDigitos[iSV] = BCD[c.valEdit.cifras - iSV - 1];
		
		//Poner signo
		if (signo == -1)
		{
			c.valEdit.ptrDigitos[0] = MENOS_ASCII; //Colocamos el signo menos para indicar que el número es negativo	
			c.valEdit.bSignoPos = 0;
		}
		else
		{
			c.valEdit.ptrDigitos[0] = ESPACIO_ASCII; //Colocamos un espacio donde iría el signo negativo	
			c.valEdit.bSignoPos = 1;
		}
		
		//Seteo el ValEdit para que la próxima vez que sea editado, se comience por la unidad
		c.valEdit.offset = c.valEdit.cifras - c.valEdit.cifrasVis;
		c.valEdit.indFocoDigit = c.valEdit.cifrasVis - 1;

		//c.valEdit.estado.bRedibujar = 1;	//Redibujar todo de nuevo
	}
}//fin ValEditSetValor

/*Función ValEditIncDigit------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que incrementa el valor del elemento/caracter que tiene el foco 
Entrada: 
		ptrValEdit: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ValEditIncDigit()
{
	/*signed int valorVEID;
	unsigned char indCalculadoVEID;*/
	
	indCalculadoVEID = c.valEdit.offset + c.valEdit.indFocoDigit;
	
	//¿NO estamos en el elemento correspondiente al signo?
	if ((c.valEdit.ptrDigitos[indCalculadoVEID] != MENOS_ASCII)
		&& (c.valEdit.ptrDigitos[indCalculadoVEID] != ESPACIO_ASCII))
	{ 
		if (c.valEdit.bSignoPos == 1) //El valor es positivo?
		{
			//Incrementamos el elemento/caracter de la cadena que tiene el foco
			c.valEdit.ptrDigitos[indCalculadoVEID]++;
			
			if (c.valEdit.ptrDigitos[indCalculadoVEID] > NUEVE_ASCII)	//¿Se excedió el rango?
				c.valEdit.ptrDigitos[indCalculadoVEID] = CERO_ASCII; //Seteamos el cero

			//Verificamos que el nuevo valor que toma el ValEdit cae dentro de su rango, si no es así, seteamos un cero 
			if (ValEditGetValor() < c.valEdit.valMinSigned.word || ValEditGetValor() > c.valEdit.valMaxSigned.word)
			{
				//Verificamos que el nuevo valor que toma el ValEdit cae dentro de su rango, si no es así, seguimos incrementando 
				while(ValEditGetValor() < c.valEdit.valMinSigned.word || ValEditGetValor() > c.valEdit.valMaxSigned.word)
				{
					//Incrementamos el elemento/caracter de la cadena que tiene el foco hasta cumplir lo requerido
					c.valEdit.ptrDigitos[indCalculadoVEID]++;
					
					//Verificamos que el nuevo valor que toma el ValEdit cae dentro de su rango, si no es así, seteamos un cero
					if (c.valEdit.ptrDigitos[indCalculadoVEID] > NUEVE_ASCII)	//¿Se excedió el rango?
						c.valEdit.ptrDigitos[indCalculadoVEID] = CERO_ASCII; //Seteamos el cero
				}
			}
		}
		else  //El valor es negativo	
		{
			//Incrementamos el dígito de la cadena que tiene el foco
			c.valEdit.ptrDigitos[indCalculadoVEID]++;
			
			//Verificamos que el nuevo valor que toma el ValEdit cae dentro de su rango, si no es así, seteamos un cero
			if (c.valEdit.ptrDigitos[indCalculadoVEID] > NUEVE_ASCII)	//¿Se excedió el rango?
				c.valEdit.ptrDigitos[indCalculadoVEID] = CERO_ASCII; //Seteamos el cero
			
			if (ValEditGetValor() < c.valEdit.valMinSigned.word || ValEditGetValor() > c.valEdit.valMaxSigned.word)
			{
				//Verificamos que el nuevo valor que toma el ValEdit cae dentro de su rango, si no es así, seguimos decrementando 
				while(ValEditGetValor() < c.valEdit.valMinSigned.word || ValEditGetValor() > c.valEdit.valMaxSigned.word)
				{
					//Decrementamos el elemento/caracter de la cadena que tiene el foco hasta cumplir lo requerido
					c.valEdit.ptrDigitos[indCalculadoVEID]++;
					
					//Verificamos que el nuevo valor que toma el ValEdit cae dentro de su rango, si no es así, seteamos un cero
					if (c.valEdit.ptrDigitos[indCalculadoVEID] > NUEVE_ASCII)	//¿Se excedió el rango?
						c.valEdit.ptrDigitos[indCalculadoVEID] = CERO_ASCII; //Seteamos el cero
				}
			}
		}
	}
	else
	{
		if (c.valEdit.ptrDigitos[0] == MENOS_ASCII)
		{
			c.valEdit.ptrDigitos[0] = ESPACIO_ASCII; //invierto el signo en el valor
			c.valEdit.bSignoPos = 1; //invierto la bandera de signo
			
			//Si el nuevo valor es mayor al valor maximo
			if (ValEditGetValor() > c.valEdit.valMaxSigned.word)
				ValEditSetValor(c.valEdit.valMaxSigned.word); //Seteamos el valor máximo
			
		}
		else
		{
			c.valEdit.ptrDigitos[0] = MENOS_ASCII; //invierto el signo en el valor
			c.valEdit.bSignoPos = 0; //invierto la bandera de signo
			
			//Si el nuevo valor es menor al valor minimo
			if (ValEditGetValor() < c.valEdit.valMinSigned.word)
				ValEditSetValor(c.valEdit.valMinSigned.word); //Seteamos el valor mínimo
		}
	}

	//Indicar que se actualice el elemento que fue modificado
	c.valEdit.indActualiz = indCalculadoVEID;
}//fin ValEditIncDigit()

/*Función ValEditDecDigit------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que decrementa el valor del elemento que tiene el foco 
Entrada: 
		ptrValEdit: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ValEditDecDigit()
{
	unsigned char i;
	unsigned char indCalculado;
	
	indCalculado = c.valEdit.offset + c.valEdit.indFocoDigit;

	//¿NO estamos en el elemento correspondiente al signo?
	if ((c.valEdit.ptrDigitos[indCalculado] != MENOS_ASCII) 
		&& (c.valEdit.ptrDigitos[indCalculado] != ESPACIO_ASCII)) 
	{ 
		if (c.valEdit.bSignoPos == 1) //El valor es positivo?
		{
			//Decrementamos el elemento/caracter de la cadena que tiene el foco
			c.valEdit.ptrDigitos[indCalculado]--;
			
			if (c.valEdit.ptrDigitos[indCalculado] < CERO_ASCII)	//¿Bajó el rango inferior?
				c.valEdit.ptrDigitos[indCalculado] = NUEVE_ASCII; //Seteamos el nueve
				
			//Verificamos que el nuevo valor que toma el ValEdit cae dentro de su rango, si no es así, seteamos un 
			if (ValEditGetValor() < c.valEdit.valMinSigned.word || ValEditGetValor() > c.valEdit.valMaxSigned.word)
			{
				//c.valEdit.ptrDigitos[indCalculado] = NUEVE_ASCII; //Seteamos el nueve
				
				//Verificamos que el nuevo valor que toma el ValEdit cae dentro de su rango, si no es así, seguimos decrementando 
				while(ValEditGetValor() < c.valEdit.valMinSigned.word || ValEditGetValor() > c.valEdit.valMaxSigned.word)
				{
					//Decrementamos el elemento/caracter de la cadena que tiene el foco hasta cumplir lo requerido
					c.valEdit.ptrDigitos[indCalculado]--;
				
					if (c.valEdit.ptrDigitos[indCalculado] < CERO_ASCII)	//¿Bajó el rango inferior?
						c.valEdit.ptrDigitos[indCalculado] = NUEVE_ASCII; //Seteamos el nueve
				}
			}
		}
		else //El valor es negativo	
		{
			//Decrementamos el dígito de la cadena que tiene el foco
			c.valEdit.ptrDigitos[indCalculado]--;
			
			if (c.valEdit.ptrDigitos[indCalculado] < CERO_ASCII)	//¿Se excedió el rango?
				c.valEdit.ptrDigitos[indCalculado] = NUEVE_ASCII; //Seteamos el nueve
			
			//Verificamos que el nuevo valor que toma el ValEdit cae dentro de su rango, si no es así, seteamos un nueve 
			if (ValEditGetValor() < c.valEdit.valMinSigned.word || ValEditGetValor() > c.valEdit.valMaxSigned.word)
			{
				//c.valEdit.ptrDigitos[indCalculado] = NUEVE_ASCII; //Seteamos el nueve
				
				//Verificamos que el nuevo valor que toma el ValEdit cae dentro de su rango, si no es así, seguimos decrementando 
				while(ValEditGetValor() < c.valEdit.valMinSigned.word || ValEditGetValor() > c.valEdit.valMaxSigned.word)
				{
					//Decrementamos el elemento/caracter de la cadena que tiene el foco hasta cumplir lo requerido
					c.valEdit.ptrDigitos[indCalculado]--;
					
					if (c.valEdit.ptrDigitos[indCalculado] < CERO_ASCII)	//¿Bajó el rango inferior?
						c.valEdit.ptrDigitos[indCalculado] = NUEVE_ASCII; //Seteamos el nueve
				}
			}
		}
	}
	else
	{
		if (c.valEdit.ptrDigitos[0] == MENOS_ASCII)
		{
			c.valEdit.ptrDigitos[0] = ESPACIO_ASCII; //invierto el signo en el valor
			c.valEdit.bSignoPos = 1; //invierto la bandera de signo
						
			//Si el nuevo valor es mayor al valor maximo
			if (ValEditGetValor() > c.valEdit.valMaxSigned.word)
				ValEditSetValor(c.valEdit.valMaxSigned.word); //Seteamos el valor máximo
			
		}
		else
		{
			c.valEdit.ptrDigitos[0] = MENOS_ASCII; //invierto el signo en el valor
			c.valEdit.bSignoPos = 0; //invierto la bandera de signo
			
			//Si el nuevo valor es menor al valor minimo
			if (ValEditGetValor() < c.valEdit.valMinSigned.word)
				ValEditSetValor(c.valEdit.valMinSigned.word); //Seteamos el valor mínimo
		}
	}

	//Indicar que se actualice el elemento que fue modificado
	c.valEdit.indActualiz = indCalculado;
}//fin ValEditDecDigit()

/*Función ValEditTitCursor------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que hace titilar el cursor del ValEdit que tiene el foco 
Entrada: 
		ptrValEdit: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ValEditTitCursor()
{
	unsigned char color;

	if (contTitileo >= TITILEO_CURSOR_VAL_ED)
	{
		contTitileo = 0;	//reseteamos la cuenta
		if (c.valEdit.bCursorDib == 1) //¿Está dibujado el cursor?
		{
			color = COLOR_FONDO_DEF;
			c.valEdit.bCursorDib = 0;	//El cursor ya no está
			//contTitileo = 0;	//reseteamos la cuenta
		}	 
		else
		{
			color = !COLOR_FONDO_DEF;
			c.valEdit.bCursorDib = 1;	//El cursor está dibujado
			//contTitileo = 0;	//reseteamos la cuenta
		}
		//Borramos o dibujamos el cursor
		if(c.tamanioTexto == 0) //la letra es de 3x5, sin tener en cuenta las excepciones
		{
			GLCD_Relleno(	c.x + GROSOR_BORDE_VAL_ED 
				+ c.valEdit.indFocoDigit * (ANCHO_LABEL_3X5 + SEP_ELEM_VAL_ED)
				, c.y
				, ANCHO_LABEL_3X5
				, ANCHO_CURSOR_VAL_ED
				, color);
		}
		else //la letra es de 5x7, sin tener en cuenta las excepciones
		{
			GLCD_Relleno(	c.x + GROSOR_BORDE_VAL_ED 
				+ c.valEdit.indFocoDigit * ((ANCHO_ELEM_VAL_ED * c.tamanioTexto) 
				+ SEP_ELEM_VAL_ED + c.tamanioTexto - 1)
				, c.y
				, (ANCHO_ELEM_VAL_ED * c.tamanioTexto) 
				, ANCHO_CURSOR_VAL_ED
				, color);
		}		

		//c.valEdit.bNoRedibujar = 0;	//Indicamos que se debe redibujar el ValEdit
	}
}//fin ValEditTitCursor()

/*Función ValEditActualizar------------------------------------------------------------------------------------------------------------------------
Descripción: función encargada de dibujar o actualizar los ValEdits 
Entrada: 
		ptrValEdit: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ValEditActualizar()
{
	/*unsigned char iVEA;
	unsigned char offsetXVEA;
	unsigned char colorVEA;*/
	
	if (c.valEdit.estado.bEditando == 1 && c.valEdit.bEntrandoEdicion == 0)	//¿El ValEdit está siendo editado?
	{
		//if (c.valEdit.estado.bRedibujar == 1) //¿Es necesario redibujar todo el ValEdit?
			colorVEA = COLOR_FONDO_DEF;
		//else	//Si no es necesario redibujar todo el ValEdit, veo si es necesario actualizar algún dígito
			if (c.valEdit.indActualiz != NO_ACTUALIZAR_DIG)	//¿Hay algún dígito para actualizar?
			{
				//Comprobar que el elemento que hay que actualizar cae dentro del rango visible
				if ( (c.valEdit.indActualiz >= c.valEdit.offset) 
							&& (c.valEdit.indActualiz < (c.valEdit.offset + c.valEdit.cifrasVis)))
				{
					//Cargar el elemento del ValEdit a Dibujar
					c.cadenaAux[0] = c.valEdit.ptrDigitos[c.valEdit.indActualiz];
					c.cadenaAux[1] = 0; //Hacemos que la cadena termine en NULL
					
					if(c.tamanioTexto == TEXTO_35) //la letra es de 3x5, sin tener en cuenta las excepciones
					{
						if (c.valEdit.estado.bLimpiarFondo == 1 || c.valEdit.estado.bEnFoco == 1)
							//Limpiar el área donde se va a dibujar el elemento del ValEdit
							GLCD_Relleno(	c.x 
								+ (c.valEdit.indActualiz - c.valEdit.offset) * (ANCHO_LABEL_3X5	+ SEP_ELEM_VAL_ED)
								, c.y
								, ANCHO_LABEL_3X5 + SEP_ELEM_VAL_ED
								, ANCHO_CURSOR_VAL_ED + GROSOR_BORDE_VAL_ED + ALTO_LABEL_3X5
								, COLOR_FONDO_DEF);
						//Dibujar el elemento del ValEdit
						GLCD_String(	c.x
							+ (c.valEdit.indActualiz - c.valEdit.offset) * (ANCHO_LABEL_3X5	+ SEP_ELEM_VAL_ED)
							+ GROSOR_BORDE_VAL_ED
							, c.y + 4 + GROSOR_BORDE_VAL_ED
							, c.cadenaAux, c.tamanioTexto, !COLOR_FONDO_DEF);
					}
					else //la letra es de 5x7, sin tener en cuenta las excepciones
					{
						if (c.valEdit.estado.bLimpiarFondo == 1 || c.valEdit.estado.bEnFoco == 1)
							//Limpiar el área donde se va a dibujar el elemento del ValEdit
							GLCD_Relleno(	c.x 
								+ (c.valEdit.indActualiz - c.valEdit.offset) * ((ANCHO_ELEM_VAL_ED * c.tamanioTexto)
								+ (SEP_ELEM_VAL_ED + c.tamanioTexto - 1))
								, c.y
								, (ANCHO_ELEM_VAL_ED * c.tamanioTexto) + (SEP_ELEM_VAL_ED + c.tamanioTexto - 1)
								, ANCHO_CURSOR_VAL_ED + GROSOR_BORDE_VAL_ED + (ALTO_ELEM_VAL_ED * c.tamanioTexto)
								, COLOR_FONDO_DEF);
						//Dibujar el elemento del ValEdit
						GLCD_String(	c.x
							+ (c.valEdit.indActualiz - c.valEdit.offset) * ((ANCHO_ELEM_VAL_ED * c.tamanioTexto)
							+ SEP_ELEM_VAL_ED + c.tamanioTexto - 1) + GROSOR_BORDE_VAL_ED
							, c.y + (6 * c.tamanioTexto) + GROSOR_BORDE_VAL_ED
							, c.cadenaAux, c.tamanioTexto, !COLOR_FONDO_DEF);
					}
				}
				c.valEdit.indActualiz = NO_ACTUALIZAR_DIG;	//Indico que el ValEdit ya se actualizó o no es necesario actualizarlo
				//c.valEdit.bNoRedibujar = 1;	//Indicamos que ya no se debe redibujar el ValEdit
			}	

		ValEditTitCursor();	//Titileo de cursores de los ValEdit
	}
	else	//El ValEdit no está siendo editado
	{
		if (c.valEdit.estado.bEnFoco == 1)	//¿El ValEdit tiene el foco?
		{
			if (c.valEdit.estado.bRedibujar == 1) //¿Es necesario redibujar todo el ValEdit?
				if (c.valEdit.estado.bEditando == 0)
					colorVEA = !COLOR_FONDO_DEF;
				else
					colorVEA = COLOR_FONDO_DEF;
		}
		else	//El ValEdit no tiene el foco
		{
			if (c.valEdit.estado.bRedibujar == 1) //¿Es necesario redibujar todo el ValEdit?
				colorVEA = COLOR_FONDO_DEF;
		}

		if (c.valEdit.estado.bRedibujar == 1)
		{
			if(c.tamanioTexto == TEXTO_35) //la letra es de 3x5, sin tener en cuenta las excepciones
			{
				if (c.valEdit.estado.bLimpiarFondo == 1 || c.valEdit.estado.bEnFoco == 1)
					//Limpiar el área donde se va a dibujar el elemento del ValEdit
					GLCD_Relleno(	c.x , c.y
							, (ANCHO_LABEL_3X5 * c.valEdit.cifrasVis) 
							+ (c.valEdit.cifrasVis - 1) * SEP_ELEM_VAL_ED + 2 * GROSOR_BORDE_VAL_ED
							, 2 * GROSOR_BORDE_VAL_ED + ALTO_LABEL_3X5
							, colorVEA);
				//Ahora dibujamos el ValEdit
				offsetXVEA = c.x + GROSOR_BORDE_VAL_ED;
				for(iVEA = c.valEdit.offset; iVEA < (c.valEdit.offset + c.valEdit.cifrasVis); iVEA++)	
				{
					c.cadenaAux[0] = c.valEdit.ptrDigitos[iVEA];
					c.cadenaAux[1] = 0; //Hacemos que la cadena termine en NULL
					GLCD_String(offsetXVEA
							, c.y + 4 + GROSOR_BORDE_VAL_ED
							, c.cadenaAux
							, c.tamanioTexto
							, !colorVEA);
						
					offsetXVEA = offsetXVEA + GLCD_AnchoLetra(c.cadenaAux[0], c.tamanioTexto) + SEP_ELEM_VAL_ED; 
				}
			}
			else //la letra es de 5x7, sin tener en cuenta las excepciones
			{	
				if (c.valEdit.estado.bLimpiarFondo == 1 || c.valEdit.estado.bEnFoco == 1)
					//Limpiar el área donde se va a dibujar el elemento del ValEdit
					GLCD_Relleno(	c.x , c.y
							, ((ANCHO_ELEM_VAL_ED * c.tamanioTexto) * c.valEdit.cifrasVis) 
							+ (c.valEdit.cifrasVis - 1) * (SEP_ELEM_VAL_ED + c.tamanioTexto - 1) + 2 * GROSOR_BORDE_VAL_ED
							, ANCHO_CURSOR_VAL_ED + (ALTO_ELEM_VAL_ED * c.tamanioTexto) + GROSOR_BORDE_VAL_ED
							, colorVEA);
				//Ahora dibujamos el ValEdit
				offsetXVEA = c.x + GROSOR_BORDE_VAL_ED;
				for(iVEA = c.valEdit.offset; iVEA < (c.valEdit.offset + c.valEdit.cifrasVis); iVEA++)	
				{
					c.cadenaAux[0] = c.valEdit.ptrDigitos[iVEA];
					c.cadenaAux[1] = 0; //Hacemos que la cadena termine en NULL
					GLCD_String(offsetXVEA
						, c.y + (6 * c.tamanioTexto) + GROSOR_BORDE_VAL_ED
						, c.cadenaAux, c.tamanioTexto, !colorVEA);
					offsetXVEA = offsetXVEA + (ANCHO_ELEM_VAL_ED * c.tamanioTexto) + SEP_ELEM_VAL_ED + c.tamanioTexto - 1; 
				}
			}	
			if (c.valEdit.estado.bEditando != 1)	//Si estoy editando, dejo a bRedibujar como 1
				c.valEdit.estado.bRedibujar = 0;	//El ValEdit ya ha sido redibujado
			c.valEdit.bEntrandoEdicion = 0;	//Indicamos que ya no se debe redibujar todo el ValEdit
			c.valEdit.estado.bLimpiarFondo = 1;
		}
	}

	//Actualizamos las banderas del Objeto Gráfico
	c.estado.bandEstado = c.valEdit.estado.bandEstado;
}//fin ValEditActualizar()

/*Función ComportamientoPropioValEdit------------------------------------------------------------------------------------------------------------------------
Descripción: función que ejecuta las acciones que definen el comportamiento del objeto ante las distintas
							pulsaciones de tecla
Entrada: 
		ptrValEdit: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ComportamientoPropioValEdit(void)
{
	//c.valEdit.bNoRedibujar = 0;

	switch (teclado.teclaPulsada)
	{
		case TECLA_ACEPTAR:
			if (c.valEdit.estado.bEditando == 1)	//¿El ValEdit está siendo editado?
			{
				ValEditEditar(SALIR);
				ptrFoco[indFoco]->bandEstado = c.valEdit.estado.bandEstado;	//Actualizamos las banderas del Objeto Gráfico
			}
			else	//El ValEdit no está siendo editado
				ValEditEditar(ENTRAR);
			break;

		case TECLA_CANCELAR:
			if (c.valEdit.estado.bEditando == 1)	//¿El ValEdit está siendo editado?
			{
				ValEditEditar(CANCELAR);
				ptrFoco[indFoco]->bandEstado = c.valEdit.estado.bandEstado;	//Actualizamos las banderas del Objeto Gráfico
			}
			break;

		case TECLA_ARRIBA:
			if (c.valEdit.estado.bEditando == 1)	//¿El ValEdit está siendo editado?
				ValEditIncDigit();
			else
			{
				RetrocederFoco();
				//Seteo el ValEdit para que la próxima vez que sea editado, se comience por la unidad
				c.valEdit.offset = c.valEdit.cifras - c.valEdit.cifrasVis;
				c.valEdit.indFocoDigit = c.valEdit.cifrasVis - 1;
			}
			break;

		case TECLA_ABAJO:
			if (c.valEdit.estado.bEditando == 1)	//¿El ValEdit está siendo editado?
				ValEditDecDigit();
			else
			{
				AvanzarFoco();
				//Seteo el ValEdit para que la próxima vez que sea editado, se comience por la unidad
				c.valEdit.offset = c.valEdit.cifras - c.valEdit.cifrasVis;
				c.valEdit.indFocoDigit = c.valEdit.cifrasVis - 1;
			}
			break;

		case TECLA_DERECHA:
			if (c.valEdit.estado.bEditando == 1)	//¿El ValEdit está siendo editado?
				ValEditEditar(DERECHA);
			else
				ValEditRight();
			break;

		case TECLA_IZQUIERDA:
			if (c.valEdit.estado.bEditando == 1)	//¿El ValEdit está siendo editado?
				ValEditEditar(IZQUIERDA);
			else
				ValEditRight();
			break;

		case TECLA_NO_PRES:	//Me fijo en la tecla Sostenida solo si la tecla presionada ya ha sido atendida
			//Pulsación sostenida de tecla
			if (teclado.teclaSostenida != TECLA_NO_PRES)
			{
				//if (c.valEdit.estado.bRedibujar == 1 && c.valEdit.estado.bEditando == 0)
					//c.valEdit.bNoRedibujar = 0;
				//else
					//c.valEdit.bNoRedibujar = 1;
			}		
			else	//No hay ninguna tecla sostenida ni pulsada
			{
				//if (c.valEdit.estado.bRedibujar == 1)
					//c.valEdit.bNoRedibujar = 0;
				//else
					//c.valEdit.bNoRedibujar = 1;
			}
			break;
	}

	if (c.valEdit.estado.bEditando == 1)	//¿El ValEdit está siendo editado?
		ptrFoco[indFoco]->bandEstado = c.valEdit.estado.bandEstado;	//Actualizamos las banderas del Objeto Gráfico

}	//Fin ComportamientoPropioValEdit()

#endif	//end ValEdit


