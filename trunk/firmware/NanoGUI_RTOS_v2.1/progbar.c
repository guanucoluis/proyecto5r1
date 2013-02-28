#include "ProgBar.h"

//ProgBar
#ifdef PROG_BAR

//VARIABLES DE ProgBarActualizar()
unsigned char iPBA;
unsigned char pixelesPBA;
signed char difPixelesPBA;
unsigned char colorPBA;
unsigned char anchoPBA;
unsigned char altoPBA;

/*Función ProgBarActualizar------------------------------------------------------------------------------------------------------------------------
Descripción: función encargada de dibujar o actualizar las Barras de Progreso 
Entrada: 
	ptrProgBar: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ProgBarActualizar()
{
	/*unsigned char iPBA;
	unsigned char pixelesPBA;
	unsigned char colorPBA;
	unsigned char anchoPBA;
	unsigned char altoPBA*/

	if (c.progBar.estado.bRedibujar == 1) //¿Es necesario redibujar la ProgBar?
	{
		if (c.progBar.estado.bEnFoco == 1) //¿La ProgBar está en foco?
			c.progBar.estado.bColorNeg = 1;
		else
			c.progBar.estado.bColorNeg = 0;
		//Limpiar el area donde se va a dibujar la ProgBar
		if (c.progBar.estado.bColorNeg == 0) //¿La ProgBar NO debe graficarse negada?
			colorPBA = COLOR_FONDO_DEF;
		else
			colorPBA = !COLOR_FONDO_DEF;

		//if(c.progBar.bRedibujarTodo == 1)	//¿Es la primera vez que se va a dibujar la barra?
		if (c.progBar.estado.bLimpiarFondo == 1)	//¿Es la primera vez que se va a dibujar la barra?
		{
			//Determinar si la barra es horizontal o vertical y calcular el ancho
			if (c.progBar.bVertical == 1) //¿La barra es vertical?
			{
				anchoPBA = 4 + c.progBar.espesor;	
				altoPBA = c.progBar.longitud;	
			}	
			else
			{
				anchoPBA = c.progBar.longitud;
				altoPBA = 4 + c.progBar.espesor;
			}
			if (c.progBar.estado.bLimpiarFondo == 1 || c.progBar.estado.bEnFoco == 1)
				//Limpiar el area donde se va a dibujar el Label
				GLCD_Relleno(	c.x
										, c.y
										, anchoPBA
										, altoPBA
										, colorPBA);

			//Dibujar borde
			GLCD_Rectangulo( c.x
											, c.y
											, anchoPBA
											, altoPBA
											, !COLOR_FONDO_DEF);
			//c.progBar.bRedibujarTodo = 0;
			c.progBar.estado.bLimpiarFondo = 0;

			//Corregimos el valor del porcentaje
			if (c.progBar.progPorcent > 100)
				if (c.progBar.progPorcent < 180)
					c.progBar.progPorcent = 100;
				else
					c.progBar.progPorcent = 0;
				
			//Calculamos la cantidad de píxeles que tenemos que pintar
			pixelesPBA = (unsigned char) ((float) c.progBar.pixPorUnidad * (float) c.progBar.progPorcent);
			
			for(iPBA = 0; iPBA < pixelesPBA; iPBA++)	
			{
				if (c.progBar.bVertical == 1) //¿La barra es vertical?
					GLCD_Linea(c.x + 2, c.y + 2 + iPBA, c.x + 2 + c.progBar.espesor - 1, c.y + 2 + iPBA, !colorPBA);
				else
					GLCD_Linea(c.x + 2 + iPBA, c.y + 2, c.x + 2 + iPBA, c.y + 2 + c.progBar.espesor - 1, !colorPBA);
			}
			
			//c.progBar.pixAnterior	= pixelesPBA;	//Actualizamos la cantidad de píxeles pintados
			c.progBar.porcentAnterior = c.progBar.progPorcent;
		}
		else	//No es la primera vez que la ProgBar se dibuja
		{
			//Calculamos la cantidad de píxeles que tenemos que pintar
			pixelesPBA = (unsigned char) ((float) c.progBar.pixPorUnidad * (float) c.progBar.progPorcent);
				
			if (c.progBar.porcentAnterior != c.progBar.progPorcent)
			{ 
				difPixelesPBA = (signed char) c.progBar.pixAnterior - (signed char) pixelesPBA;
				
				if (difPixelesPBA < 0) //¿Hay que pintar más pixeles?
				{
					for(iPBA = 0; iPBA < (unsigned char) -difPixelesPBA; iPBA++)	
					{
						if (c.progBar.bVertical == 1) //¿La barra es vertical?
							GLCD_Linea(	c.x + 2
												, c.y + 2 + c.progBar.pixAnterior + iPBA
												, c.x + 2 + c.progBar.espesor - 1
												, c.y + 2 + c.progBar.pixAnterior + iPBA
												, !colorPBA);
						else
							GLCD_Linea( c.x + 2 + iPBA + c.progBar.pixAnterior
												, c.y + 2
												, c.x + 2 + iPBA + c.progBar.pixAnterior
												, c.y + 2 + c.progBar.espesor - 1
												, !colorPBA);
					}
					/*GLCD_Relleno(	c.x + 2
											, (unsigned char) (1 + c.y + (signed char) c.progBar.pixAnterior)
											, c.progBar.espesor
											, (unsigned char) -difPixelesPBA
											, !colorPBA);*/
				}
				else	//Tenemos que borrar píxeles
				{
					for(iPBA = 0; iPBA < (unsigned char) difPixelesPBA; iPBA++)	
					{
						if (c.progBar.bVertical == 1) //¿La barra es vertical?
							GLCD_Linea(	c.x + 2
												, c.y + 2 + c.progBar.pixAnterior - iPBA
												, c.x + 2 + c.progBar.espesor - 1
												, c.y + 2 + c.progBar.pixAnterior - iPBA
												, colorPBA);
						else
							GLCD_Linea( c.x + 1 - iPBA + c.progBar.pixAnterior
												, c.y + 2
												, c.x + 1 - iPBA + c.progBar.pixAnterior
												, c.y + 2 + c.progBar.espesor - 1
												, colorPBA);
					}
					/*GLCD_Relleno(	c.x + 2
											, (unsigned char) (1 + (signed char) c.y + (signed char) c.progBar.pixAnterior - (signed char) difPixelesPBA)
											, c.progBar.espesor
											, (unsigned char) difPixelesPBA
											, colorPBA);*/
				}
				c.progBar.pixAnterior = pixelesPBA;
				c.progBar.porcentAnterior = c.progBar.progPorcent;
			}
		}
		c.progBar.pixAnterior	= pixelesPBA;	//Actualizamos la cantidad de píxeles pintados
		c.progBar.estado.bRedibujar = 0;	//La ProgBar ya ha sido redibujada
		//c.progBar.estado.bLimpiarFondo = 1;
	}

	//Actualizamos los valores propios de la ProgBar 
	vPProgBars[c.numValProp].bRedibujarTodo = c.progBar.bRedibujarTodo;
	vPProgBars[c.numValProp].porcentAnterior = c.progBar.porcentAnterior;
	vPProgBars[c.numValProp].pixAnterior = c.progBar.pixAnterior;

	c.estado.bandEstado = c.progBar.estado.bandEstado;	//Actualizamos las banderas del Objeto Gráfico

}	//Fin de ProgBarActualizar()

/*Función ComportamientoPropioProgBar------------------------------------------------------------------------------------------------------------------------
Descripción: función que ejecuta las acciones que definen el comportamiento del objeto ante las distintas
							pulsaciones de tecla
Entrada: 
		ptrProgBar: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ComportamientoPropioProgBar(void)
{
	switch (teclado.teclaPulsada)
	{
		case TECLA_ARRIBA:
			RetrocederFoco();
			break;

		case TECLA_ABAJO:
			AvanzarFoco();
			break;
	}

	c.estado.bandEstado = c.progBar.estado.bandEstado;	//Actualizamos las banderas del Objeto Gráfico

}	//Fin ComportamientoPropioProgBar()

#endif	//PROG_BAR

