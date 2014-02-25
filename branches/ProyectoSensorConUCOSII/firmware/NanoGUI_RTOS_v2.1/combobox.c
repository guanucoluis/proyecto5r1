#include "ComboBox.h"

//comienzo de ComboBox
#ifdef COMBO_BOX

//VARIABLES GLOBALES DE COMBOBOX
volatile unsigned char	iOpcion;		//Indice usado para dibujar cada opción de la lista de opciones en modo edición
volatile unsigned char	offsetCboB;			//Indica si hay desplazamiento en la lista de opciones
//volatile rom const char *ptrCadenaCboB;

//VARIABLES DE CargarTexto()
volatile unsigned char charActualCT;
volatile unsigned char cantOpcionesCT;
volatile unsigned char indCT;

//VARIABLES DE ComboBoxActualizar()
volatile unsigned char	colorBordeCboB;
volatile unsigned char	colorFondoCboB;
//volatile unsigned char	iCBA;
/*volatile unsigned char posXACboB;
volatile unsigned char posYACboB;
volatile unsigned char anchoACboB;
volatile unsigned char altoACboB;*/

//VARIABLES DE InicializarComboBox()
volatile unsigned char iICB;
volatile unsigned char charActualICB;
volatile unsigned char anchoCadenaActualICB;

/*Función CargarTexto------------------------------------------------------------------------------------------------------------------------
Descripción: función que analiza la matriz de cadena de caracteres del ComboBox y basándose en la opción
							seleccionada temporalmente apunta el label a la opción que corresponda
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void CargarTexto(void)
{
	indCT = 0;
	if (iOpcion != c.comboBox.cantOpciones) //¿No estamos en la última opción?
	{
		cantOpcionesCT = c.comboBox.cantOpciones;
		//charActualCT = (unsigned char) *(&ptrComboBox->ptrCadena[0]);	//Cargamos el primer caracter de la cadena
		charActualCT = ptrForm->ptrCadenas[c.offsetCadena];
		while(charActualCT != '\n')	//¿Se encontró un enter? El enter indica el final de las opciones
		{
			if (charActualCT == NULL)	//
				cantOpcionesCT--;	//Decrementamos la cantidad de opciones
			
			indCT++;	//Pasamos al siguiente caracter
	
			if (cantOpcionesCT == iOpcion)	//¿Se llegó al inicio de la cadena de la opción deseada?
				charActualCT = '\n';	//Terminamos el bucle
			else
				//charActualCT = (unsigned char) *((rom const char *) ptrComboBox->ptrCadena + indCT);	//Cargamos el próximo caracter
				charActualCT = ptrForm->ptrCadenas[c.offsetCadena + indCT];
		}	
	
		//ptrComboBox->CboBLabel.ptrCadena = ptrComboBox->ptrCadena + indCT;	//Apuntamos al inicio de la cadena de la opción actual
	}
	//else
		//ptrComboBox->CboBLabel.ptrCadena = ptrComboBox->ptrCadena;

	//Copiamos la cadena de texto que corresponda a la opción
	c.offsetChar = 0;
	while (ptrForm->ptrCadenas[c.offsetCadena] != NULL && c.offsetChar < TAMANIO_CADENA_TEXTO)	//Mientras no se encuentre el final de cadena (NULL)
		c.cadenaTexto[c.offsetChar++] = ptrForm->ptrCadenas[c.offsetCadena + indCT + c.offsetChar];
	c.cadenaTexto[c.offsetChar] = NULL;	//Agregamos un NULL al final de la cadena
}

/*Función InicializarComboBox------------------------------------------------------------------------------------------------------------------------
Descripción: función que analiza la matriz de cadena de caracteres del ComboBox y basándose en ésta setea la cantidad
						de Opciones disponibles, cadena más larga, etc.
Entrada: 
	ptrComboBox: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void InicializarComboBox()
{
	//Determinar el número de opciones del ComboBox y cuál es la más larga
	iICB = 0;
	c.comboBox.cantOpciones = 0;
	c.comboBox.anchoMayorOp = 0;
	anchoCadenaActualICB = 0;
	//charActualICB = (unsigned char) *(&ptrComboBox->ptrCadena[0]);	//Cargamos el primer caracter de la cadena
	charActualICB = ptrForm->ptrCadenas[c.offsetCadena]; //Cargamos el primer caracter de la cadena
	while(charActualICB != '\n')	//¿Se encontró un enter?	El enter indica el final de las opciones
	{
		if (charActualICB == NULL)	//¿Pasamos a otra opción?
		{
			c.comboBox.cantOpciones++;	//Aumentamos la cantidad de opciones
			if (anchoCadenaActualICB > c.comboBox.anchoMayorOp)	//¿Es la cadena actual la más larga hasta ahora?
				c.comboBox.anchoMayorOp = anchoCadenaActualICB;
			anchoCadenaActualICB = 0;	//Empezamos a contar de cero el ancho de la nueva cadena
		}
		else	//Se trata de un caracter común
		{
			anchoCadenaActualICB = anchoCadenaActualICB + GLCD_AnchoLetra(charActualICB, c.tamanioTexto);
			anchoCadenaActualICB++;	//Incrementamos en 1 debido al espacio entre letras	
		}
		iICB++;
		charActualICB = ptrForm->ptrCadenas[c.offsetCadena + iICB];	//Cargamos el próximo caracter
	}	
	c.comboBox.cantOpciones--;
	c.comboBox.anchoMayorOp--; //Decrementamos en 1 debido al último espacio agregado de más
}

/*Función ComboBoxDesdibujar------------------------------------------------------------------------------------------------------------------------
Descripción: función encargada de limpiar el área donde se dibujó el ComboBox y ordenar el redibujado de los 
							componentes que estaban debajo 
Entrada: 
	ptrComboBox: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ComboBoxDesdibujar()
{
	//Limpiamos el área donde se dibujo el ComboBox
	GLCD_Relleno(	c.x
			, c.y - (CANT_OPCIONES_MOST * ALTO_LABEL_3X5) 
				- GROSOR_BORDE_CBOB - (2 * GROSOR_BORDE_LABEL) * CANT_OPCIONES_MOST
			, 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp + ANCHO_BARRA_DESPLAZ_CBOB
			, 2 * GROSOR_BORDE_CBOB + (2 * GROSOR_BORDE_LABEL) * (CANT_OPCIONES_MOST + 1) + ((CANT_OPCIONES_MOST + 1) * ALTO_LABEL_3X5)
			, COLOR_FONDO_DEF);

	//Redibujamos los componentes que estaban debajo del ComboBox
	objetosProgramas[3].bRedibujar = 1; //OBJETO 3 --> LABEL "Dur:     min"
	objetosProgramas[13].bRedibujar = 1; //OBJETO 13 --> SPINEDIT "Duracion:"
	objetosProgramas[9].bRedibujar = 1; //OBJETO 9 --> BUTTON "Res P"
}	//Fin ComboBoxDesdibujar()

/*Función ComboBoxActualizar------------------------------------------------------------------------------------------------------------------------
Descripción: función encargada de dibujar o actualizar los ComboBoxs 
Entrada: 
	ptrComboBox: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ComboBoxActualizar()
{
	/*unsigned char	colorBordeCboB;
	unsigned char	colorFondoCboB;*/

	if (c.comboBox.estado.bRedibujar == 1) //¿Es necesario redibujar el ComboBox?
	{
		c.label.estado.bRedibujar = 1;
		if (c.comboBox.estado.bEnFoco == 1) //¿El ComboBox está en foco?
		{
			colorFondoCboB = !COLOR_FONDO_DEF;
			colorBordeCboB = COLOR_FONDO_DEF;
			c.label.estado.bColorNeg = 1;	//Dibujar el Label del ComboBox con color negado

		}
		else	//El ComboBox no está en foco
		{
			colorFondoCboB = COLOR_FONDO_DEF;
			colorBordeCboB = !COLOR_FONDO_DEF;
			c.label.estado.bColorNeg = 0;	//Dibujar el Label del ComboBox con color negado
		}
	}

	if (c.comboBox.estado.bRedibujar == 1)
	{
		if (c.comboBox.estado.bEditando == 1)	//¿El ComboBox está siendo editado?
		{
			if(c.tamanioTexto == TEXTO_35) //la letra es de 3x5, sin tener en cuenta las excepciones
			{
				if (c.comboBox.bDibujarTodoDeNuevo == 1)
				{
					if (c.comboBox.estado.bLimpiarFondo == 1)
						//Limpiamos el área donde vamos a dibujar el ComboBox
						GLCD_Relleno(	c.x - ESPACIO_LIMPIO_BORDE
								, c.y - (CANT_OPCIONES_MOST * ALTO_LABEL_3X5) 
									- GROSOR_BORDE_CBOB - (2 * GROSOR_BORDE_LABEL) * CANT_OPCIONES_MOST - ESPACIO_LIMPIO_BORDE
								, 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp 
									+ ANCHO_BARRA_DESPLAZ_CBOB + 2 * ESPACIO_LIMPIO_BORDE
								, 2 * GROSOR_BORDE_CBOB + (2 * GROSOR_BORDE_LABEL) * (CANT_OPCIONES_MOST + 1) 
								+ ((CANT_OPCIONES_MOST + 1) * ALTO_LABEL_3X5) + 2 * ESPACIO_LIMPIO_BORDE
								, colorBordeCboB);
				
					//Dibujar marco exterior de la opción seleccionada
					GLCD_Rectangulo(	c.x
							, c.y
							, 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp
							, 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + ALTO_LABEL_3X5
							, colorFondoCboB);
					//Dibujar marco exterior del conjunto de opciones
					GLCD_Rectangulo(	c.x
							, c.y - (CANT_OPCIONES_MOST * ALTO_LABEL_3X5) 
								- (2 * GROSOR_BORDE_LABEL) * CANT_OPCIONES_MOST - GROSOR_BORDE_CBOB
							, 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp
							, 2 * GROSOR_BORDE_CBOB + (2 * GROSOR_BORDE_LABEL) * CANT_OPCIONES_MOST + (CANT_OPCIONES_MOST * ALTO_LABEL_3X5)
							, colorFondoCboB);

					//Dibujar fondo de la barra de desplazamiento
					GLCD_Relleno(	c.x + GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp
							, c.y - (CANT_OPCIONES_MOST * ALTO_LABEL_3X5) - (2 * GROSOR_BORDE_LABEL) * CANT_OPCIONES_MOST - GROSOR_BORDE_CBOB
							, ANCHO_BARRA_DESPLAZ_CBOB
							, 2 * GROSOR_BORDE_CBOB + (2 * GROSOR_BORDE_LABEL) * (CANT_OPCIONES_MOST + 1) 
								+ ((CANT_OPCIONES_MOST + 1) * ALTO_LABEL_3X5) + 1
							, colorFondoCboB);

					//Dibujar flecha hacia arriba
					GLCD_Punto( c.x + 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp + 1 + 2
											, c.y - 2
											, colorBordeCboB);
					GLCD_Linea(	c.x + 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp + 1 + 1
											, c.y - 3
											,c.x + 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp + 1 + 3
											, c.y - 3
											, colorBordeCboB);
					GLCD_Linea(	c.x + 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp + 1 + 0
											, c.y - 4
											,c.x + 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp + 1 + 4
											, c.y - 4
											, colorBordeCboB);
					
					//Dibujar flecha hacia abajo
					GLCD_Linea(	c.x + 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp + 1 + 0
											, c.y - (CANT_OPCIONES_MOST * ALTO_LABEL_3X5) 
											- (2 * GROSOR_BORDE_LABEL) * CANT_OPCIONES_MOST - GROSOR_BORDE_CBOB + 4
											,c.x + 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp + 1 + 4
											, c.y - (CANT_OPCIONES_MOST * ALTO_LABEL_3X5) 
											- (2 * GROSOR_BORDE_LABEL) * CANT_OPCIONES_MOST - GROSOR_BORDE_CBOB + 4
											, colorBordeCboB);
					GLCD_Linea(	c.x + 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp + 1 + 1
											, c.y - (CANT_OPCIONES_MOST * ALTO_LABEL_3X5) 
											- (2 * GROSOR_BORDE_LABEL) * CANT_OPCIONES_MOST - GROSOR_BORDE_CBOB + 3
											,c.x + 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp + 1 + 3
											, c.y - (CANT_OPCIONES_MOST * ALTO_LABEL_3X5) 
											- (2 * GROSOR_BORDE_LABEL) * CANT_OPCIONES_MOST - GROSOR_BORDE_CBOB + 3
											, colorBordeCboB);
					GLCD_Punto( c.x + 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp + 1 + 2
											, c.y - (CANT_OPCIONES_MOST * ALTO_LABEL_3X5) 
											- (2 * GROSOR_BORDE_LABEL) * CANT_OPCIONES_MOST - GROSOR_BORDE_CBOB + 2
											, colorBordeCboB);

					//Dibujar el texto de la opción seleccionada
					c.xLabel = c.x + GROSOR_BORDE_BT + GROSOR_BORDE_LABEL - 1;	//La posición X es la misma para todas las opciones (labels)
					c.yLabel = c.y + GROSOR_BORDE_BT + GROSOR_BORDE_LABEL - 1; //Dibujar opción (Label) seleccionada
					iOpcion = c.comboBox.opcionSelec;	//Le indicamos a CargarTexto() que queremos apuntar al texto de la opción seleccionada
					CargarTexto(); //Apuntamos el Label al texto de la opción seleccionada
					LabelCantPixels(); // Contamos y asignamos la cantidad de caracteres, más la cantidad de pixels del Label
					c.label.estado.bColorNeg = 0;
					c.label.estado.bRedibujar = 1;
					LabelActualizar();
			
					c.comboBox.bDibujarTodoDeNuevo = 0;	//Indicamos que el modo edición ya ha sido dibujado y ya no
																								//será necesario redibujar todo de nuevo
				}

				for (iOpcion = offsetCboB; iOpcion < (offsetCboB + CANT_OPCIONES_MOST); iOpcion++)
				{
					CargarTexto();	//Apuntamos el Label al texto de la opción que corresponda
					LabelCantPixels(); //Contamos y asignamos la cantidad de caracteres, más la cantidad de pixels del Label

					//Determinamos si debe estar negado o no
					if (iOpcion == c.comboBox.opcionTemp)	//¿Se está dibujando la opción que está selecionada temporalmente?
						c.label.estado.bColorNeg = 1; //Entonces dibujamos el label negado
					else
						c.label.estado.bColorNeg = 0; //Entonces dibujamos el label NO negado
				
					//Determinamos la posición en Y del label
					c.yLabel = c.y - ((iOpcion - offsetCboB + 1) * ALTO_LABEL_3X5) 
																				- (iOpcion - offsetCboB + 1) * (2 * GROSOR_BORDE_LABEL);
					//Limpiamos  el área donde se dibujará el label de opción
					GLCD_Relleno(	c.x + GROSOR_BORDE_CBOB
							, c.yLabel
							, 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp
							, 2 * GROSOR_BORDE_LABEL + ALTO_LABEL_3X5
							, !colorFondoCboB);
					c.label.estado.bRedibujar = 1;
					LabelActualizar();
				}
			}
			else //la letra es de 5x7, sin tener en cuenta las excepciones
			{
				if (c.comboBox.bDibujarTodoDeNuevo == 1)
				{
					if (c.comboBox.estado.bLimpiarFondo == 1)
						//Limpiamos el área donde vamos a dibujar el ComboBox
						GLCD_Relleno(	c.x
								, c.y - ((CANT_OPCIONES_MOST + 1) * ALTO_TEXTO_57 * c.tamanioTexto) 
									- CANT_OPCIONES_MOST
								, 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp
								, 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL 
									+ ((CANT_OPCIONES_MOST + 1) * ALTO_TEXTO_57 * c.tamanioTexto)
								, colorFondoCboB);

					//Dibujar marco exterior de la opción seleccionada
					GLCD_Rectangulo(	c.x, c.y
							, 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp
							, 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + (ALTO_ELEM_LABEL * c.tamanioTexto)
							, colorBordeCboB);
					//Dibujar marco exterior del conjunto de opciones
					GLCD_Rectangulo(	c.x
							, c.y - (CANT_OPCIONES_MOST * ALTO_TEXTO_57 * c.tamanioTexto) 
								- CANT_OPCIONES_MOST
							, 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp
							, 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + (CANT_OPCIONES_MOST * ALTO_TEXTO_57 * c.tamanioTexto)
							, colorBordeCboB);
	
					//Dibujar fondo de la barra de desplazamiento
					GLCD_Relleno(	c.x + 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp
							, c.y - ((CANT_OPCIONES_MOST + 1) * ALTO_TEXTO_57 * c.tamanioTexto) - CANT_OPCIONES_MOST
							, ANCHO_BARRA_DESPLAZ_CBOB
							, 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + ((CANT_OPCIONES_MOST + 1) * ALTO_TEXTO_57 * c.tamanioTexto)
							, colorBordeCboB);
	
					//Dibujar flecha hacia arriba
					GLCD_Punto( c.x + 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp + 2 + 2
											, c.y - 1
											, colorBordeCboB);
					GLCD_Linea(	c.x + 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp + 2 + 1
											, c.y - 2
											, c.x + 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp + 2 + 3
											, c.y - 2
											, colorBordeCboB);
					GLCD_Linea(	c.x + 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp + 2 + 0
											, c.y - 2
											, c.x + 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp + 2 + 5
											, c.y - 2
											, colorBordeCboB);
	
					//Dibujar flecha hacia abajo
					GLCD_Linea(	c.x + 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp + 2 + 0
											, c.y - ((CANT_OPCIONES_MOST + 1) * ALTO_TEXTO_57 * c.tamanioTexto)
												- CANT_OPCIONES_MOST + 4
											, c.x + 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp + 2 + 5
											, c.y - ((CANT_OPCIONES_MOST + 1) * ALTO_TEXTO_57 * c.tamanioTexto) 
												- CANT_OPCIONES_MOST + 4
											, colorBordeCboB);
					GLCD_Linea(	c.x + 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp + 2 + 1
											, c.y - ((CANT_OPCIONES_MOST + 1) * ALTO_TEXTO_57 * c.tamanioTexto)
												- CANT_OPCIONES_MOST + 3
											, c.x + 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp + 2 + 3
											, c.y - ((CANT_OPCIONES_MOST + 1) * ALTO_TEXTO_57 * c.tamanioTexto)
												- CANT_OPCIONES_MOST + 3
											, colorBordeCboB);
					GLCD_Punto( c.x + 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp + 2 + 2
											, c.y - ((CANT_OPCIONES_MOST + 1) * ALTO_TEXTO_57 * c.tamanioTexto)
												- CANT_OPCIONES_MOST + 2
											, colorBordeCboB);
				
					c.comboBox.bDibujarTodoDeNuevo = 0;	//Indicamos que el modo edición ya ha sido dibujado y ya no
																								//será necesario redibujar todo de nuevo
				}

				//Dibujar el texto de las opciones
				c.xLabel = c.x + GROSOR_BORDE_BT + GROSOR_BORDE_LABEL - 1;	//La posición X es la misma para todas las opciones (labels)
				for (iOpcion = 0; iOpcion < c.comboBox.cantOpciones; iOpcion++)
				{
					//Apuntamos el Label al texto de la opción que corresponda
					CargarTexto();

					//Determinamos si debe estar negado o no
					if ((iOpcion - 1) == c.comboBox.opcionTemp)	//¿Se está dibujando la opción que está selecionada temporalmente?
						c.label.estado.bColorNeg = 1; //Entonces dibujamos el label negado
					else
						c.label.estado.bColorNeg = 0; //Entonces dibujamos el label NO negado
				
					//Determinamos la posición en Y del label
					if (iOpcion = 0)	//¿Estamos en el primer label (la opción seleccionada)?
						c.yLabel = c.y + GROSOR_BORDE_BT + GROSOR_BORDE_LABEL - 1; //Dibujar opción (Label) seleccionada
					else	//Estamos en una de las opciones
						c.yLabel = c.y - (iOpcion * ALTO_TEXTO_57 * c.tamanioTexto) - iOpcion - c.comboBox.opcionSelec;
					LabelActualizar();
				}
			}	
		}
		else	//El ComboBox NO ESTÁ EN MODO EDICIÓN
		{
			if(c.tamanioTexto == TEXTO_35) //la letra es de 3x5, sin tener en cuenta las excepciones
			{
				if (c.comboBox.estado.bLimpiarFondo == 1 || c.comboBox.estado.bEnFoco == 1)
					//Limpiamos el área donde vamos a dibujar el ComboBox
					GLCD_Relleno(	c.x
							, c.y
							, 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp
							, 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + ALTO_LABEL_3X5
							, colorFondoCboB);
				//Dibujar marco exterior de la opción seleccionada
				GLCD_Rectangulo(	c.x
						, c.y
						, 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp
						, 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + ALTO_LABEL_3X5
						, colorBordeCboB);

				//Limpiar área de la barra de desplazamiento
				GLCD_Relleno(	c.x + 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp - 1
						, c.y
						, ANCHO_BARRA_DESPLAZ_CBOB
						, 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + ALTO_LABEL_3X5
						, colorFondoCboB);
				//if (c.comboBox.estado.bEnFoco != 1)
				//{
					GLCD_Rectangulo(	c.x + 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp - 1
						, c.y
						, ANCHO_BARRA_DESPLAZ_CBOB
						, 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + ALTO_LABEL_3X5
						, colorBordeCboB);
				//}
				//Dibujar flecha hacia abajo
				GLCD_Linea(	c.x + 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp + 2 + 0 - 1
										, c.y + 5
										, c.x + 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp + 2 + 4 - 1
										, c.y + 5
										, colorBordeCboB);
				GLCD_Linea(	c.x + 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp + 2 + 1 - 1
										, c.y + 4
										, c.x + 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp + 2 + 3 - 1
										, c.y + 4
										, colorBordeCboB);
				GLCD_Punto( c.x + 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp + 2 + 2 - 1
										, c.y + 3
										, colorBordeCboB);
			}
			else //la letra es de 5x7, sin tener en cuenta las excepciones
			{
				if (c.comboBox.estado.bLimpiarFondo == 1 || c.comboBox.estado.bEnFoco == 1)
					//Limpiamos el área donde vamos a dibujar el ComboBox
					GLCD_Relleno(	c.x
							, c.y
							, 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp
							, 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + ALTO_TEXTO_57 * c.tamanioTexto
							, colorFondoCboB);
				//Dibujar marco exterior de la opción seleccionada
				GLCD_Rectangulo(	c.x, c.y
						, 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + c.comboBox.anchoMayorOp
						, 2 * GROSOR_BORDE_CBOB + 2 * GROSOR_BORDE_LABEL + (ALTO_ELEM_LABEL * c.tamanioTexto)
						, colorBordeCboB);
			}	

			//Dibujar el texto de las opciones
			c.xLabel = c.x + GROSOR_BORDE_BT + GROSOR_BORDE_LABEL - 1;	//La posición X es la misma para todas las opciones (labels)
			c.yLabel = c.y + GROSOR_BORDE_BT + GROSOR_BORDE_LABEL - 1;
			if (c.comboBox.estado.bEnFoco == 1) 
				c.label.estado.bColorNeg = 1;
			else
				c.label.estado.bColorNeg = 0;
			iOpcion = c.comboBox.opcionSelec;
			CargarTexto();
			LabelActualizar();
		}
		c.comboBox.estado.bRedibujar = 0;	//El ComboBox ya fué dibujado
		c.comboBox.estado.bLimpiarFondo = 1;
		c.label.estado.bRedibujar = 0; //El Label del ComboBox ya fué dibujado
	}
}

/*Función ComportamientoPropioComboBox------------------------------------------------------------------------------------------------------------------------
Descripción: función que ejecuta las acciones que definen el comportamiento del objeto ante las distintas
							pulsaciones de tecla
Entrada: 
		ptrComboBox: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ComportamientoPropioComboBox(void)
{
	switch (teclado.teclaPulsada)
	{
		case TECLA_ACEPTAR:
			if (c.comboBox.estado.bEditando == 1) //¿El ComboBox está siendo editado?
			{
				ComboBoxDesdibujar();	//Desdibujamos el ComboBox y redibujamos los componentes que estaban abajo			
	
				c.comboBox.opcionSelec = c.comboBox.opcionTemp;	//Cargamos la nueva  opción seleccionada
				c.comboBox.estado.bEditando = 0;	//Salimos del modo Edición
			}
			else	//El ComboBox NO está siendo editado
			{
				offsetCboB = 0;
				c.comboBox.opcionTemp = 0;	//Indicamos que la opción temporal sea la primera

				c.comboBox.estado.bEditando = 1;	//Entramos en el modo edición
				c.comboBox.bDibujarTodoDeNuevo = 1;	//Por ser la primera vez, dibujamos todo
			}
			c.comboBox.estado.bRedibujar = 1;						
			break;
		case TECLA_CANCELAR:
			if (c.comboBox.estado.bEditando == 1) //¿El ComboBox está siendo editado?
			{
				ComboBoxDesdibujar();	//Desdibujamos el ComboBox y redibujamos los componentes que estaban abajo

				c.comboBox.estado.bEditando = 0;	//Salimos del modo Edición
				c.comboBox.estado.bRedibujar = 1;
			}
			break;
		case TECLA_ARRIBA:
			if (c.comboBox.estado.bEditando == 1) //¿El ComboBox está siendo editado?
			{
				//Cambiamos la  opción temporal seleccionada
				if (c.comboBox.opcionTemp > 0)
					c.comboBox.opcionTemp--;
				else
					c.comboBox.opcionTemp = c.comboBox.cantOpciones;

				//Calculamos el valor del offset
				if (c.comboBox.opcionTemp < offsetCboB)			
					offsetCboB--;
				
				if ((c.comboBox.opcionTemp + 1) > CANT_OPCIONES_MOST)
					while(((c.comboBox.opcionTemp + 1) - CANT_OPCIONES_MOST) > offsetCboB)
						offsetCboB++;

				c.comboBox.estado.bRedibujar = 1;
			}
			else
				RetrocederFoco();
			break;
		case TECLA_ABAJO:
			if (c.comboBox.estado.bEditando == 1) //¿El ComboBox está siendo editado?
			{
				//Cambiamos la  opción temporal seleccionada
				if (c.comboBox.opcionTemp < c.comboBox.cantOpciones)
					c.comboBox.opcionTemp++;
				else
					c.comboBox.opcionTemp = 0;

				//Calculamos el valor del offset
				if ((c.comboBox.opcionTemp - offsetCboB) >= CANT_OPCIONES_MOST)			
					offsetCboB++;
				
				while(offsetCboB > c.comboBox.opcionTemp)
					offsetCboB--;

				c.comboBox.estado.bRedibujar = 1;
			}
			else
				AvanzarFoco();
			break;
	}

	//if (c.comboBox.estado.bEditando == 1)	//¿El ComboBox está siendo editado?
		ptrFoco[indFoco]->bandEstado = c.comboBox.estado.bandEstado;	//Actualizamos las banderas del Objeto Gráfico

	vPComboBoxes[c.numValProp].opcionSelec = c.comboBox.opcionSelec; //Actualizamos la opción seleccionada del ComboBox
	
}	//Fin ComportamientoPropioComboBox()

#endif //end COMBO_BOX


