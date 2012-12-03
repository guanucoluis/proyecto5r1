#include "CheckBox.h"

//comienzo de CheckBox
#ifdef CHECK_BOX

//VARIABLES DE CheckBoxActualizar()
volatile unsigned char	colorBordeCBA;
volatile unsigned char	colorFondoCBA;


/*Función CheckBoxActualizar------------------------------------------------------------------------------------------------------------------------
Descripción: función encargada de dibujar o actualizar los CheckBox 
Entrada: 
	ptrCheckBox: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void CheckBoxActualizar()
{
	/*unsigned char	colorBordeCBA;
	unsigned char	colorFondoCBA;*/

	if (c.checkBox.estado.bRedibujar == 1) //¿Es necesario redibujar el CheckBox?
	{
		c.label.estado.bRedibujar = 1;
		if (c.checkBox.estado.bEnFoco == 1) //¿El CheckBox está en foco?
		{
			colorFondoCBA = !COLOR_FONDO_DEF;
			colorBordeCBA = COLOR_FONDO_DEF;
			c.label.estado.bColorNeg = 1;	//Dibujar el Label del CheckBox con color negado

		}
		else	//El CheckBox no está en foco
		{
			colorFondoCBA = COLOR_FONDO_DEF;
			colorBordeCBA = !COLOR_FONDO_DEF;
			c.label.estado.bColorNeg = 0;	//Dibujar el Label del CheckBox con color negado
		}
	}

	if (c.checkBox.estado.bRedibujar == 1)
	{
		if(c.tamanioTexto == TEXTO_35) //la letra es de 3x5, sin tener en cuenta las excepciones
		{
			if (c.checkBox.estado.bLimpiarFondo == 1 || c.checkBox.estado.bEnFoco == 1)
				//Limpiamos el área donde vamos a dibujar el CheckBox
				GLCD_Relleno(	c.x, c.y
						, 2 * GROSOR_BORDE_CB + 2 * GROSOR_BORDE_LABEL
						+ c.cantPixeles + (c.cantCaracteres - 1) * SEP_ELEM_CB_LABEL
						+ ALTO_TEXTO_35 + SEPAR_CUAD_LABEL_CB
						, 2 * GROSOR_BORDE_CB + 2 * GROSOR_BORDE_LABEL + ALTO_LABEL_3X5
						, colorFondoCBA);
			//Dibujar cuadrado del CheckBox
			GLCD_Rectangulo(	c.x + 1, c.y + 1
					, ALTO_TEXTO_35 + 2
					, ALTO_TEXTO_35 + 2
					, colorBordeCBA);
			//Dibujar la cruz de chequeado dentro del cuadrado
			if (c.checkBox.estado.bChequeado == 1)	//¿El CheckBox está chequeado?
			{
				//Dibujar primera línea oblicua
				GLCD_Linea(	c.x + 3
										,c.y + 3
										,c.x + ALTO_TEXTO_35 //+ 1
										,c.y + ALTO_TEXTO_35 //+ 1
										,colorBordeCBA);
				//Dibujar segunda línea oblicua
				GLCD_Linea(	c.x + 3
										,c.y + ALTO_TEXTO_35 //+ 1
										,c.x + ALTO_TEXTO_35 //+ 1
										,c.y + 3
										,colorBordeCBA);
			}
		}
		else //la letra es de 5x7, sin tener en cuenta las excepciones
		{
			if (c.checkBox.estado.bLimpiarFondo == 1 || c.checkBox.estado.bEnFoco == 1)
				//Limpiamos el área donde vamos a dibujar el CheckBox
				GLCD_Relleno(	c.x, c.y
						, 2 * GROSOR_BORDE_CB + 2 * GROSOR_BORDE_LABEL
						+ (ANCHO_ELEM_LABEL * c.tamanioTexto) * c.cantCaracteres
						+ (c.cantCaracteres - 1) * (SEP_ELEM_CB_LABEL + c.tamanioTexto - 1)
						+ SEPAR_CUAD_LABEL_CB + (ALTO_TEXTO_57 * c.tamanioTexto)
						, 2 * GROSOR_BORDE_CB + 2 * GROSOR_BORDE_LABEL + (ALTO_ELEM_LABEL * c.tamanioTexto)
						, colorFondoCBA);
			//Dibujar cuadrado del CheckBox
			GLCD_Rectangulo(	c.x + 1, c.y + 1
					, ALTO_TEXTO_57 * c.tamanioTexto + 2
					, ALTO_TEXTO_57 * c.tamanioTexto + 2
					, colorBordeCBA);
			//Dibujar la cruz de chequeado dentro del cuadrado
			if (c.checkBox.estado.bChequeado == 1)	//¿El CheckBox está chequeado?
			{
				//Dibujar primera línea oblicua
				GLCD_Linea(	c.x + 2
										,c.y + 2
										,c.x + ALTO_TEXTO_57 * c.tamanioTexto + 2
										,c.y + ALTO_TEXTO_57 * c.tamanioTexto + 2
										,colorBordeCBA);
				//Dibujar segunda línea oblicua
				GLCD_Linea(	c.x + 2
										,c.y + ALTO_TEXTO_57 * c.tamanioTexto + 2
										,c.x + ALTO_TEXTO_57 * c.tamanioTexto + 2
										,c.y + 2
										,colorBordeCBA);
			}
		}			
		//ptrLabel = &ptrCheckBox->CbLabel;
		LabelActualizar();
		c.checkBox.estado.bRedibujar = 0;	//El CheckBox ya fué dibujado
		c.checkBox.estado.bLimpiarFondo = 1;
		c.label.estado.bRedibujar = 0; //El Label del CheckBox ya fué dibujado
	}
}

/*Función ComportamientoPropioCheckBox------------------------------------------------------------------------------------------------------------------------
Descripción: función que ejecuta las acciones que definen el comportamiento del objeto ante las distintas
							pulsaciones de tecla
Entrada: 
		ptrCheckBox: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ComportamientoPropioCheckBox(void)
{
	switch (teclado.teclaPulsada)
	{
		case TECLA_ACEPTAR:
			//Acción por defecto para todos los CheckBox
			if (c.checkBox.estado.bEditable == 1)	//¿El CheckBox actual es modificable?
			{
				if (c.checkBox.estado.bChequeado == 1)
					c.checkBox.estado.bChequeado = 0;
				else
					c.checkBox.estado.bChequeado = 1;
				
				c.checkBox.estado.bRedibujar = 1;
			}	
			ptrFoco[indFoco]->bandEstado = c.checkBox.estado.bandEstado;	//Actualizamos las banderas del Objeto Gráfico							
			break;
		case TECLA_ARRIBA:
			RetrocederFoco();
			break;
		case TECLA_ABAJO:
			AvanzarFoco();
			break;
	}
}	//Fin ComportamientoPropioCheckBox()

#endif //end CHECKBOX


