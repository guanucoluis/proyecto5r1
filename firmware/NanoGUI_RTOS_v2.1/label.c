#include "label.h"

//comienzo de label
#ifdef LABEL

//VARIABLES DE LabelNumPixels()
volatile unsigned char iLNP, contPixel;

//VARIABLES DE LabelActualizar()
volatile unsigned char iLA;
volatile unsigned char offsetXLA;
volatile unsigned char colorLA;

/*Función LabelCantPixels ------------------------------------------------------------------------------------------------
Descripción: cuenta la cantidad de pixeles y caracteres que tiene el Label, sin tener en cuenta los espacios.
Entrada: 
	ptrLabel: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
-----------------------------------------------------------------------------------------------------------------------*/
void LabelCantPixels()
{
	c.cantCaracteres = 0;
	c.cantPixeles = 0;
	
	for(iLNP=0; c.cadenaTexto[iLNP] != '\0'; ++iLNP)
	{
		c.cantCaracteres ++;
		c.cantPixeles += GLCD_AnchoLetra(c.cadenaTexto[iLNP], c.tamanioTexto);
	}
}// Fin LabelCantPixels()

/*Función LabelActualizar------------------------------------------------------------------------------------------------------------------------
Descripción: función encargada de dibujar o actualizar los Labels 
Entrada: 
	ptrLabel: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void LabelActualizar()
{
	/*unsigned char iLA;
	unsigned char offsetXLA;
	unsigned char colorLA;*/
	

	if (c.label.estado.bRedibujar == 1) //¿Es necesario redibujar el Label?
	{
		if(c.tamanioTexto == TEXTO_35) //la letra es de 3x5, sin tener en cuenta las excepciones
		{
			if (c.label.estado.bColorNeg == 0) //¿El Label NO debe graficarse negado?
				colorLA = COLOR_FONDO_DEF;
			else
				colorLA = !COLOR_FONDO_DEF;
			
			if (c.label.estado.bLimpiarFondo == 1 || c.label.estado.bColorNeg == 1)
				//Limpiar el area donde se va a dibujar el Label
				GLCD_Relleno(	c.xLabel, c.yLabel
										, c.cantPixeles	+ (c.cantCaracteres - 1) * (SEP_ELEM_LABEL) + 2 * GROSOR_BORDE_LABEL
										, 2 * GROSOR_BORDE_LABEL + ALTO_LABEL_3X5
										, colorLA);
			
			if (c.label.estado.bColorNeg == 0) //¿El Label NO debe graficarse negado?
				colorLA = !COLOR_FONDO_DEF;
			else
				colorLA = COLOR_FONDO_DEF;						
			
			//Dibujar Label
			offsetXLA = c.xLabel + GROSOR_BORDE_LABEL;
			/*for(iLA = 0; c.cadena[iLA] != '\0'; iLA++)
				cadenaAux[iLA] = c.cadena[iLA];
			cadenaAux[iLA] = 0; //Hacemos que la cadena termine en NULL*/
			
			//Renderizamos el texto
			GLCD_String(	offsetXLA
									, c.yLabel + 4 + GROSOR_BORDE_LABEL
									, c.label.ptrTexto
									, c.tamanioTexto
									, colorLA);
				
				/*offsetXLA = offsetXLA + ANCHO_LABEL_3X5 * ptrLabel->tamanioTexto + ptrLabel->tamanioTexto + SEP_ELEM_LABEL - 1; 
			}*/
		}
		else //la letra es de 5x7, sin tener en cuenta las excepciones
		{		
			//Limpiar el area donde se va a dibujar el Label
			if (c.label.estado.bColorNeg == 0) //¿El Label NO debe graficarse negado?
				colorLA = COLOR_FONDO_DEF;
			else
				colorLA = !COLOR_FONDO_DEF;
			
			if (c.label.estado.bLimpiarFondo == 1 || c.label.estado.bColorNeg == 1)
				//Limpiar el area donde se va a dibujar el Label
				GLCD_Relleno(	c.xLabel, c.yLabel
										, c.tamanioTexto * (ANCHO_ELEM_LABEL * c.cantCaracteres)
										+ (c.cantCaracteres - 1) * (SEP_ELEM_LABEL + c.tamanioTexto - 1) + 2 * GROSOR_BORDE_LABEL
										, GROSOR_BORDE_LABEL + ALTO_ELEM_LABEL * c.tamanioTexto + GROSOR_BORDE_LABEL
										, colorLA);
			
			if (c.label.estado.bColorNeg == 0) //¿El Label NO debe graficarse negado?
				colorLA = !COLOR_FONDO_DEF;
			else
				colorLA = COLOR_FONDO_DEF;						
			
			//Dibujar Label
			offsetXLA = c.xLabel + GROSOR_BORDE_LABEL;
			for(iLA = 0; iLA < c.cantCaracteres; iLA++)	
			{
				c.cadenaAux[0] = c.label.ptrTexto[iLA];
				c.cadenaAux[1] = 0; //Hacemos que la cadena termine en NULL
				//Renderizamos el texto
				GLCD_String(	offsetXLA
										, c.yLabel + (6 * c.tamanioTexto) + GROSOR_BORDE_LABEL
										, c.cadenaAux
										, c.tamanioTexto
										, colorLA);
				
				offsetXLA = offsetXLA + ANCHO_ELEM_LABEL * c.tamanioTexto + c.tamanioTexto + SEP_ELEM_LABEL - 1; 
			}
		}	
		c.label.estado.bRedibujar = 0;	//El Label ya ha sido redibujado
		c.label.estado.bLimpiarFondo = 1;
	}
}//end LabelActualizar

#endif //fin de label


