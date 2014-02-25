#include "msgbox.h"

//comienzo de MsgBox
#ifdef MSG_BOX

//Variables de MostrarMensaje
uint8_t	iMM;

/*Función DibujarRecuadroMsg------------------------------------------------------------------------------------------------------------------------
Descripción: función que borra el área de la pantalla donde se va a imprimir el mensaje y dibuja un borde
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void DibujarRecuadroMsg(void)
{
	//Limpiamos el area donde vamos a dibujar el Mensaje
	GLCD_Relleno(	c.x - BORDE_EXT_CAJA
							, c.y - BORDE_EXT_CAJA - ANCHO_EFECTO_3D
							, c.msgBox.anchoCaja + 2 * BORDE_EXT_CAJA + ANCHO_EFECTO_3D
							, c.msgBox.altoCaja + 2 * BORDE_EXT_CAJA + ANCHO_EFECTO_3D
							, COLOR_FONDO_DEF);
	//Dibujamos el rectangulo del Mensaje
	GLCD_Rectangulo(c.x
								, c.y
								, c.msgBox.anchoCaja
								, c.msgBox.altoCaja 
								, !COLOR_FONDO_DEF);
	//Dibujamos el efecto 3D
	GLCD_Linea(		c.x + 1
							,	c.y - 1
							,	c.x + c.msgBox.anchoCaja
							,	c.y - 1
							,	!COLOR_FONDO_DEF);	//Línea del borde inferior
	GLCD_Linea(		c.x + c.msgBox.anchoCaja
							,	c.y
							,	c.x + c.msgBox.anchoCaja
							,	c.y + c.msgBox.altoCaja - 2
							,	!COLOR_FONDO_DEF);	//Línea del costado derecho

}//end DibujarRecuadroMsg

/*Función MostrarMsg------------------------------------------------------------------------------------------------------------------------
Descripción: función que muestra un mensaje en pantalla sobre el formulario de fondo 
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void MostrarMsg(const uint8_t *ptrTexto, uint8_t tipoMsg, uint8_t anchoMax, uint8_t segundos)
{
	c.msgBox.tiempo.ms = 0;
	c.msgBox.tiempo.seg = 0;
	c.msgBox.segundos = segundos;
	c.msgBox.bCerrarMensaje = 0;
	c.msgBox.bImprimiendo = 0;
	c.msgBox.bCalculandoLineas = 1;
	c.msgBox.bFinCadena = 0;
	c.msgBox.cantLineas = 0;
	c.msgBox.bCambioEspacioNull = 0;
	c.msgBox.pixelesNuevaCadena = 0;
	c.msgBox.bRecuadroDibujado = 0;
	c.msgBox.anchoMaxCadena = 0;
	c.msgBox.anchoCaja = anchoMax;
	c.offsetChar = 0;
	c.tamanioTexto = TEXTO_35;
	c.msgBox.tipoMensaje = tipoMsg;
	c.msgBox.bMensajeActivo = 1;
	//"c.offsetChar" es usada para indicar el offset dentro de la línea a imprimir

	//Copiamos los datos a una cadena en RAM para ahorrar memoria de programa en las operaciones que siguen
	while (ptrTexto[c.offsetChar] != NULL && c.offsetChar < TAMANIO_CADENA_TEXTO)	//Mientras no se encuentre el final de cadena (NULL)
		c.cadenaTexto[c.offsetChar] = ptrTexto[c.offsetChar++];
	
	c.cadenaTexto[c.offsetChar] = NULL;	//Terminamos la cadena en NULL 
	c.cadenaTexto[c.offsetChar + 1] = NULL;	//Hacemos esto por  las dudas

	while(c.msgBox.bCalculandoLineas == 1 || c.msgBox.bImprimiendo == 1)
	{
		if (c.msgBox.cantLineas != 0)	//¿Ya fueron calculadas las líneas del texto?
		{
			c.msgBox.bCalculandoLineas = 0;
			c.msgBox.bImprimiendo = 1;
			c.msgBox.bFinCadena = 0;
			c.msgBox.pixelesNuevaCadena = 0;
		}
		c.label.ptrTexto = c.cadenaTexto;
		//Separamos el texto en cadenas menores al ancho máximo y las vamos imprimiendo
		while (*c.label.ptrTexto != NULL)	//¿Todavía no llegué al final de la cadena?
		{
			//Comenzamos el análisis de una nueva cadena
			c.cantCaracteres = 0;
			c.offsetChar = 0;
			c.msgBox.bAgregarOtraPalabra = 0; //Por defecto consideramos que no se deberá agregar otra palabra
			c.msgBox.cantPalabras = 1;
			do {
				//Agregamos otra palabra a la cadena
				while (	c.label.ptrTexto[c.offsetChar] != ' ' && c.label.ptrTexto[c.offsetChar] != NULL)	//Mientras no encuentre el espacio ni el NULL, sigo agregando caracteres
				{
					c.offsetChar++;	
					c.cantCaracteres++;	//Agregamos otro caracter
				}
				if (c.label.ptrTexto[c.offsetChar] != NULL)
					c.offsetChar++;

				c.cantCaracteres++;	//Agregamos el espacio

				c.cantPixeles = c.msgBox.pixelesNuevaCadena; // pixels contados la vez anterior, la primera vez es 0
				c.msgBox.pixelesNuevaCadena = 0;
				iMM=0;
				//Calculamos el nuevo tamaño de la cadena
				for(iMM = 0; iMM < c.cantCaracteres; iMM++)
				{
					c.msgBox.pixelesNuevaCadena += GLCD_AnchoLetra(c.label.ptrTexto[iMM], c.tamanioTexto);
					c.msgBox.pixelesNuevaCadena++;	//Sumamos 1 por el espacio entre letras
				}
				//Calculamos la cadena más ancha
				if (c.msgBox.anchoMaxCadena < c.msgBox.pixelesNuevaCadena)
					c.msgBox.anchoMaxCadena = c.msgBox.pixelesNuevaCadena;					

				if (c.msgBox.pixelesNuevaCadena < (c.msgBox.anchoCaja - 2 * MARGEN_A_CAJA - 2 * ANCHO_BORDE_MSG - 1)) //¿La palabra recién agregada entra dentro del ancho de la caja de texto?
				{
					c.msgBox.bAgregarOtraPalabra = 1;
					c.msgBox.cantPalabras++;	//Se pudo agregar  otra palabra satisfactoriamente
					if (c.label.ptrTexto[c.offsetChar] == NULL)	//¿Era la última palabra?
						break;	//Rompemos el bucle
				}
				else //La palabra agregada  no  entra en el ancho  de la caja de texto
				{
					c.msgBox.bAgregarOtraPalabra = 0;	//No debo probar de agregar otra palabra
					if (c.msgBox.cantPalabras == 1)	//¿La palabra con la que estoy probando es la primera?
					{
						//Esto significa que el texto tiene una palabra que es más ancha que el ancho especificado
						//Por lo tanto, aumentamos el ancho de la caja al mínimo necesario
						c.msgBox.anchoCaja = c.msgBox.anchoMaxCadena;	
					}
				}
			}	while (c.msgBox.bAgregarOtraPalabra == 1); //¿No se llego al final o la cadena todavía no es muy ancha?
			
			if (c.msgBox.bCalculandoLineas == 1)		
				c.msgBox.cantLineas++;

			if (c.label.ptrTexto[c.offsetChar] != NULL)	//¿No se llego al final de la cadena?
			{
				c.offsetChar = c.offsetChar - 2;
				if (c.msgBox.cantPalabras > 1) //¿Hay más de una palabra en la cadena?
				{
					//Retrocedemos hasta  encontrar el espacio anterior
					while (c.label.ptrTexto[c.offsetChar] != ' ') //Mientras no encuentre el espacio anterior, continua decrementando
						c.offsetChar--;
				}

				c.cantPixeles = c.cantPixeles - 5; //Descuento  los píxeles del espacio del final de la cadena

				if (c.msgBox.bImprimiendo == 1)	//¿Se deben imprimir las líneas?
				{
					c.label.ptrTexto[c.offsetChar] = NULL; //Ponemos temporalmente un NULL para que el Label imprima la cadena solo hasta ese NULL
					c.msgBox.bCambioEspacioNull = 1;
				}	
			}
			else	//Se llegó al final de la cadena
			{
				if (c.msgBox.bAgregarOtraPalabra == 0)	//¿La última palabra agregada no  entró?
				{
					if (c.msgBox.cantPalabras > 1) //¿Hay más de una palabra en la cadena?
					{
						//Retrocedemos hasta  encontrar el espacio anterior
						while (c.label.ptrTexto[c.offsetChar] != ' ') //Mientras no encuentre el espacio anterior, continua decrementando
							c.offsetChar--;
					}

					c.cantPixeles = c.cantPixeles - 5; //Descuento  los píxeles del espacio del final de la cadena

					if (c.msgBox.bImprimiendo == 1)	//¿Se deben imprimir las líneas?
					{
						c.label.ptrTexto[c.offsetChar] = NULL; //Ponemos temporalmente un NULL para que el Label imprima la cadena solo hasta ese NULL
						c.msgBox.bCambioEspacioNull = 1;
					}	
				}
				else
					c.cantPixeles = c.msgBox.pixelesNuevaCadena - 5;	
			}
			

			if (c.msgBox.bImprimiendo == 1) //¿Se deben imprimir las líneas?
			{
				if (c.msgBox.bRecuadroDibujado == 0) //¿Todavía no se dibujó el recuadro del mensaje?
				{
					//Calcular el alto de la caja
					c.msgBox.altoCaja = c.msgBox.cantLineas * ALTO_TEXTO_35 + ((c.msgBox.cantLineas - 1) * SEPARACION_OBJETOS) 
															+ 2 * MARGEN_A_CAJA + 2 * ANCHO_BORDE_MSG;
					if (c.msgBox.tipoMensaje != MENSAJE_POR_TIEMPO)	//¿El mensaje tiene botones?
						c.msgBox.altoCaja = c.msgBox.altoCaja + ESPACIO_BOTONES; 
					//Calcular posición x de la caja del mensaje
					c.x = ((ANCHO_DISP_REAL - c.msgBox.anchoCaja) >> 1);
					//Calcular posición y de la caja del mensaje
					c.y = ((ALTO_DISP_REAL - c.msgBox.altoCaja) >> 1);

					DibujarRecuadroMsg();
					c.msgBox.bRecuadroDibujado = 1;
				}
				//Calculamos la posición x de la cadena actual
				c.xLabel = c.x + MARGEN_A_CAJA + ((c.msgBox.anchoCaja - 2 * MARGEN_A_CAJA - 2 * ANCHO_BORDE_MSG - c.cantPixeles) >> 1);
				c.yLabel = c.y + MARGEN_A_CAJA + (c.msgBox.cantLineas - 1) * ALTO_TEXTO_35 
										+ ((c.msgBox.cantLineas - 1) * SEPARACION_OBJETOS);
				if (c.msgBox.tipoMensaje != MENSAJE_POR_TIEMPO)	//¿El mensaje tiene botones?
					c.yLabel = c.yLabel + ESPACIO_BOTONES;
				c.msgBox.cantLineas--;
				//Imprimimos el Label
				//LabelCantPixels(); // Contamos y asignamos la cantidad de caracteres, más la cantidad de pixels del Label
				c.label.estado.bColorNeg = 0;
				c.label.estado.bRedibujar = 1;
				c.label.estado.bLimpiarFondo = 0;	//No es necesario limpiar el fondo
				LabelActualizar();

				if (c.msgBox.cantLineas == 0)	//¿Se terminaron de imprimir todas las líneas?
					c.msgBox.bImprimiendo = 0;	//Ya no debemos imprimir más

				if (c.msgBox.bCambioEspacioNull == 1)
					c.label.ptrTexto[c.offsetChar] = ' '; //Restauramos lo que originalmente era un espacio
				c.msgBox.bCambioEspacioNull = 0;
			}
			c.label.ptrTexto = c.label.ptrTexto + c.offsetChar + 1;
		}
	}

	c.msgBox.formPadre = pantallaActual;
	//limpio el vector de focos
	for (iMM=0; iMM < CANT_FOCO; iMM++)
		ptrFoco[iMM] = 0;
	ptrForm = &formMsgBox; //Cargamos el formulario de mensajes
	c.xAux = c.x;	//Salvamos la coordenada en x de la caja del mensaje
	c.yAux = c.y;	//Salvamos la coordenada en y de la caja del mensaje

	//Seteamos el vector de foco
	ptrFoco[0] = &objetosMsgBox[0];	//OBJETO 0 --> BUTTON "Ok"
	ptrFoco[2] = FOCO_NINGUNO;
	indFoco = 1; //Ponemos el foco en el botón "Ok"
	formMsgBox.ptrObjetos[0].bRedibujar = 1;
	formMsgBox.ptrObjetos[0].bEnFoco = 0;
	formMsgBox.ptrObjetos[1].bRedibujar = 1;
	formMsgBox.ptrObjetos[1].bEnFoco = 0;
	if (c.msgBox.tipoMensaje == MENSAJE_POR_TIEMPO) //¿Es un mensaje sin botones?
		formMsgBox.ptrObjetos[0].bVisible = 0;	
	else //Es un mensaje con al menos un botón
	{
		formMsgBox.ptrObjetos[0].bVisible = 1;
		ptrFoco[1] = FOCO_NINGUNO;
		formMsgBox.ptrObjetos[1].bVisible = 0; //Ocultamos el botón "Esc"
		//Dibujamos el Botón "Ok"
		c.estado.indDatos = formMsgBox.ptrObjetos[0].indDatos;
		CargarObjetoGrafico();	//Cargamos el objeto gráfico en memoria
		c.y = c.yAux + 3;
		if (c.msgBox.tipoMensaje != MENSAJE_OK_ESC) //¿No es un mensaje de dos botones?
			c.x = c.xAux + (c.msgBox.anchoCaja >> 1) - 4;
		else	//Es un mensaje de dos botones
			c.x = c.xAux + (c.msgBox.anchoCaja >> 1) - 4 - 18;
		c.xLabel = c.x + GROSOR_BORDE_BT;
		c.yLabel = c.y + GROSOR_BORDE_BT + GROSOR_BORDE_LABEL - 1;
		ActualizarObjetoGrafico();	//Actualizamos el objeto gráfico en pantalla
		formMsgBox.ptrObjetos[0].bandEstado = c.estado.bandEstado;	//Actualizamos las variables del objeto gráfico con los cambios que hayan sufrido
		if (c.msgBox.tipoMensaje == MENSAJE_OK_ESC) //¿Es un mensaje de dos botones?
		{
			ptrFoco[1] = &objetosMsgBox[1];	//OBJETO 1 --> BUTTON "Esc"
			formMsgBox.ptrObjetos[1].bVisible = 1; //Mostramos el botón "Esc"
			//Dibujamos el botón "Esc"
			c.estado.indDatos = formMsgBox.ptrObjetos[1].indDatos;
			CargarObjetoGrafico();	//Cargamos el objeto gráfico en memoria
			c.y = c.yAux + 3;
			c.x = c.xAux + (c.msgBox.anchoCaja >> 1) - 4 + 15;
			c.xLabel = c.x + GROSOR_BORDE_BT;
			c.yLabel = c.y + GROSOR_BORDE_BT + GROSOR_BORDE_LABEL - 1;
			ActualizarObjetoGrafico();	//Actualizamos el objeto gráfico en pantalla
			formMsgBox.ptrObjetos[1].bandEstado = c.estado.bandEstado;	//Actualizamos las variables del objeto gráfico con los cambios que hayan sufrido
		}
	}
}//end MostrarMsg

/*Función ComportamientoPropioMsgBox------------------------------------------------------------------------------------------------------------------------
Descripción: función que ejecuta las acciones que definen el comportamiento del objeto ante las distintas
							pulsaciones de tecla
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ComportamientoPropioMsgBox(void)
{
	switch (teclado.teclaPulsada)
	{
		case TECLA_ACEPTAR:
			if (c.msgBox.tipoMensaje != MENSAJE_OK_ESC)
				c.msgBox.teclaPulsada = TECLA_ACEPTAR;
			CambiarPantalla(c.msgBox.formPadre); //Devolvemos el control a la pantalla que llamo al mensaje
			c.msgBox.bMensajeActivo = 0;
			break;
		case TECLA_CANCELAR:
			c.msgBox.teclaPulsada = TECLA_CANCELAR;
			CambiarPantalla(c.msgBox.formPadre); //Devolvemos el control a la pantalla que llamo al mensaje
			c.msgBox.bMensajeActivo = 0;
			break;
	}
}	//Fin ComportamientoPropioMsgBox()

#endif //fin de MSGBOX


