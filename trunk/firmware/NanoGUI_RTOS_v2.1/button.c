#include "button.h"

//comienzo de button
#ifdef BUTTON

//VARIABLES DE ButtonActualizar()
volatile unsigned char	colorBordeBA;
volatile unsigned char	colorFondoBA;

/*Función ButtonActualizar------------------------------------------------------------------------------------------------------------------------
Descripción: función encargada de dibujar o actualizar los Buttons 
Entrada: 
	ptrButton: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ButtonActualizar()
{
	/*unsigned char	colorBordeBA;
	unsigned char	colorFondoBA;*/

	if (c.button.estado.bRedibujar == 1) //¿Es necesario redibujar el Button?
	{
		c.label.estado.bRedibujar = 1;
		if (c.button.estado.bEnFoco == 1) //¿El Button está en foco?
		{
			colorFondoBA = !COLOR_FONDO_DEF;
			colorBordeBA = COLOR_FONDO_DEF;
			c.label.estado.bColorNeg = 1;	//Dibujar el Label del Button con color negado

		}
		else	//El Button no está en foco
		{
			colorFondoBA = COLOR_FONDO_DEF;
			colorBordeBA = !COLOR_FONDO_DEF;
			c.label.estado.bColorNeg = 0;	//Dibujar el Label del Button con color negado
		}
	}

	if (c.button.estado.bRedibujar == 1)
	{
		if(c.tamanioTexto == TEXTO_35) //la letra es de 3x5, sin tener en cuenta las excepciones
		{
			if (c.button.estado.bLimpiarFondo == 1 || c.button.estado.bEnFoco == 1)
				//Limpiamos el área donde vamos a dibujar el Button
				GLCD_Relleno(	c.x, c.y
						, 2 * GROSOR_BORDE_BT + 2 * GROSOR_BORDE_LABEL
						+ c.cantPixeles + (c.cantCaracteres - 1) * SEP_ELEM_BT_LABEL
						, 2 * GROSOR_BORDE_BT + 2 * GROSOR_BORDE_LABEL + ALTO_LABEL_3X5
						, colorFondoBA);
			//Dibujar marco exterior
			GLCD_Rectangulo(	c.x, c.y
					, 2 * GROSOR_BORDE_BT + 2 * GROSOR_BORDE_LABEL
					+ c.cantPixeles + (c.cantCaracteres - 1) * SEP_ELEM_BT_LABEL
					, 2 * GROSOR_BORDE_BT + 2 * GROSOR_BORDE_LABEL + ALTO_LABEL_3X5
					, colorBordeBA);
		}
		else //la letra es de 5x7, sin tener en cuenta las excepciones
		{
			/*if (c.button.estado.bLimpiarFondo == 1 || c.button.estado.bEnFoco == 1)
				//Limpiamos el área donde vamos a dibujar el Button
				GLCD_Relleno(	c.x, c.y
						, 2 * GROSOR_BORDE_BT + 2 * GROSOR_BORDE_LABEL
						+ (ANCHO_ELEM_LABEL * c.tamanioTexto) * c.cantCaracteres
						+ (c.cantCaracteres - 1) * (SEP_ELEM_BT_LABEL + c.tamanioTexto - 1)
						, 2 * GROSOR_BORDE_BT + 2 * GROSOR_BORDE_LABEL + (ALTO_ELEM_LABEL * c.tamanioTexto)
						, colorFondoBA);*/
			//Dibujar marco exterior
			GLCD_Rectangulo(	c.x, c.y
					, 2 * GROSOR_BORDE_BT + 2 * GROSOR_BORDE_LABEL
					+ (ANCHO_ELEM_LABEL * c.tamanioTexto) * c.cantCaracteres
					+ (c.cantCaracteres - 1) * (SEP_ELEM_BT_LABEL + c.tamanioTexto - 1)
					, 2 * GROSOR_BORDE_BT + 2 * GROSOR_BORDE_LABEL + (ALTO_ELEM_LABEL * c.tamanioTexto)
					, colorBordeBA);
		}			
		//ptrLabel = &ptrButton->BtLabel;
		LabelActualizar();
    //Ahora redondeamos los bordes del button
    if (c.tamanioTexto != 0)
    {
      if (c.button.estado.bEnFoco != 1)  //¿El Button no tiene el foco?
      {
        //Esquina inferior izquierda
        GLCD_Punto(	c.x, c.y, COLOR_FONDO_DEF);
        GLCD_Punto(	c.x + 1, c.y, COLOR_FONDO_DEF);
        GLCD_Punto(	c.x, c.y + 1, COLOR_FONDO_DEF);
        GLCD_Punto(	c.x + 1, c.y + 1, !COLOR_FONDO_DEF);
        //Esquina superior izquierda
        GLCD_Punto(	c.x,
                    c.y - 1 + 2 * GROSOR_BORDE_BT + 2 * GROSOR_BORDE_LABEL
                    + (ALTO_ELEM_LABEL * c.tamanioTexto),
                    COLOR_FONDO_DEF);
        GLCD_Punto(	c.x + 1,
                    c.y - 1 + 2 * GROSOR_BORDE_BT + 2 * GROSOR_BORDE_LABEL
                    + (ALTO_ELEM_LABEL * c.tamanioTexto),
                    COLOR_FONDO_DEF);
        GLCD_Punto(	c.x,
                    c.y - 2 + 2 * GROSOR_BORDE_BT + 2 * GROSOR_BORDE_LABEL
                    + (ALTO_ELEM_LABEL * c.tamanioTexto),
                    COLOR_FONDO_DEF);
        GLCD_Punto(	c.x + 1,
                    c.y - 2 + 2 * GROSOR_BORDE_BT + 2 * GROSOR_BORDE_LABEL
                    + (ALTO_ELEM_LABEL * c.tamanioTexto),
                    !COLOR_FONDO_DEF);
        //Esquina inferior derecha
        GLCD_Punto(	c.x - 1 + 2 * GROSOR_BORDE_BT + 2 * GROSOR_BORDE_LABEL
                    + (ANCHO_ELEM_LABEL * c.tamanioTexto) * c.cantCaracteres
                    + (c.cantCaracteres - 1) * (SEP_ELEM_BT_LABEL + c.tamanioTexto - 1),
                    c.y,
                    COLOR_FONDO_DEF);
        GLCD_Punto(	c.x - 2 + 2 * GROSOR_BORDE_BT + 2 * GROSOR_BORDE_LABEL
                    + (ANCHO_ELEM_LABEL * c.tamanioTexto) * c.cantCaracteres
                    + (c.cantCaracteres - 1) * (SEP_ELEM_BT_LABEL + c.tamanioTexto - 1),
                    c.y,
                    COLOR_FONDO_DEF);
        GLCD_Punto(	c.x - 1 + 2 * GROSOR_BORDE_BT + 2 * GROSOR_BORDE_LABEL
                    + (ANCHO_ELEM_LABEL * c.tamanioTexto) * c.cantCaracteres
                    + (c.cantCaracteres - 1) * (SEP_ELEM_BT_LABEL + c.tamanioTexto - 1),
                    c.y + 1,
                    COLOR_FONDO_DEF);
        GLCD_Punto(	c.x - 2 + 2 * GROSOR_BORDE_BT + 2 * GROSOR_BORDE_LABEL
                    + (ANCHO_ELEM_LABEL * c.tamanioTexto) * c.cantCaracteres
                    + (c.cantCaracteres - 1) * (SEP_ELEM_BT_LABEL + c.tamanioTexto - 1),
                    c.y + 1,
                    !COLOR_FONDO_DEF);
        //Esquina superior derecha
        GLCD_Punto(	c.x - 1 + 2 * GROSOR_BORDE_BT + 2 * GROSOR_BORDE_LABEL
                    + (ANCHO_ELEM_LABEL * c.tamanioTexto) * c.cantCaracteres
                    + (c.cantCaracteres - 1) * (SEP_ELEM_BT_LABEL + c.tamanioTexto - 1),
                    c.y - 1 + 2 * GROSOR_BORDE_BT + 2 * GROSOR_BORDE_LABEL
                    + (ALTO_ELEM_LABEL * c.tamanioTexto),
                    COLOR_FONDO_DEF);
        GLCD_Punto(	c.x - 2 + 2 * GROSOR_BORDE_BT + 2 * GROSOR_BORDE_LABEL
                    + (ANCHO_ELEM_LABEL * c.tamanioTexto) * c.cantCaracteres
                    + (c.cantCaracteres - 1) * (SEP_ELEM_BT_LABEL + c.tamanioTexto - 1),
                    c.y - 1 + 2 * GROSOR_BORDE_BT + 2 * GROSOR_BORDE_LABEL
                    + (ALTO_ELEM_LABEL * c.tamanioTexto),
                    COLOR_FONDO_DEF);
        GLCD_Punto(	c.x - 1 + 2 * GROSOR_BORDE_BT + 2 * GROSOR_BORDE_LABEL
                    + (ANCHO_ELEM_LABEL * c.tamanioTexto) * c.cantCaracteres
                    + (c.cantCaracteres - 1) * (SEP_ELEM_BT_LABEL + c.tamanioTexto - 1),
                    c.y - 2 + 2 * GROSOR_BORDE_BT + 2 * GROSOR_BORDE_LABEL
                    + (ALTO_ELEM_LABEL * c.tamanioTexto),
                    COLOR_FONDO_DEF);
        GLCD_Punto(	c.x - 2 + 2 * GROSOR_BORDE_BT + 2 * GROSOR_BORDE_LABEL
                    + (ANCHO_ELEM_LABEL * c.tamanioTexto) * c.cantCaracteres
                    + (c.cantCaracteres - 1) * (SEP_ELEM_BT_LABEL + c.tamanioTexto - 1),
                    c.y - 2 + 2 * GROSOR_BORDE_BT + 2 * GROSOR_BORDE_LABEL
                    + (ALTO_ELEM_LABEL * c.tamanioTexto),
                    !COLOR_FONDO_DEF);
      }
      else  //El Button tiene el foco
      {
        GLCD_Punto(	c.x + 1, c.y + 1, COLOR_FONDO_DEF);
        GLCD_Punto(	c.x + 1,
                    c.y - 2 + 2 * GROSOR_BORDE_BT + 2 * GROSOR_BORDE_LABEL
                    + (ALTO_ELEM_LABEL * c.tamanioTexto),
                    COLOR_FONDO_DEF);
         GLCD_Punto(	c.x - 2 + 2 * GROSOR_BORDE_BT + 2 * GROSOR_BORDE_LABEL
                    + (ANCHO_ELEM_LABEL * c.tamanioTexto) * c.cantCaracteres
                    + (c.cantCaracteres - 1) * (SEP_ELEM_BT_LABEL + c.tamanioTexto - 1),
                    c.y + 1,
                    COLOR_FONDO_DEF);
         GLCD_Punto(	c.x - 2 + 2 * GROSOR_BORDE_BT + 2 * GROSOR_BORDE_LABEL
                    + (ANCHO_ELEM_LABEL * c.tamanioTexto) * c.cantCaracteres
                    + (c.cantCaracteres - 1) * (SEP_ELEM_BT_LABEL + c.tamanioTexto - 1),
                    c.y - 2 + 2 * GROSOR_BORDE_BT + 2 * GROSOR_BORDE_LABEL
                    + (ALTO_ELEM_LABEL * c.tamanioTexto),
                    COLOR_FONDO_DEF);
      }
    }
		c.button.estado.bRedibujar = 0;	//El Button ya fué dibujado
		c.button.estado.bLimpiarFondo = 1;
		c.label.estado.bRedibujar = 0; //El Label del Button ya fué dibujado
	}
}

/*Función ComportamientoPropioButton------------------------------------------------------------------------------------------------------------------------
Descripción: función que ejecuta las acciones que definen el comportamiento del objeto ante las distintas
							pulsaciones de tecla
Entrada: 
		ptrButton: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ComportamientoPropioButton(void)
{
	switch (teclado.teclaPulsada)
	{
		#ifdef MSG_BOX
		case TECLA_ACEPTAR:
		if (c.msgBox.bMensajeActivo == 1) //¿Hay un mensaje activo en la pantalla?
			if (c.msgBox.tipoMensaje == MENSAJE_OK_ESC) //¿Estoy en un mensaje de dos botones?
			{
				if (indFoco == 0) //Estoy en el botón "Ok"
					c.msgBox.teclaPulsada = TECLA_ACEPTAR;
				else	//Estoy en el botón escape
					c.msgBox.teclaPulsada = TECLA_CANCELAR;
			}
			break;
		#endif
		case TECLA_ARRIBA:
			RetrocederFoco();
			break;
		case TECLA_ABAJO:
			AvanzarFoco();
			break;
	}
}	//Fin ComportamientoPropioButton()

#endif //end button


