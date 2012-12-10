#ifndef INTERFAZ_C
	#define INTERFAZ_C

#include <interfaz.h>
//#include <objetos.h>
#include <configinterfaz.h>

// VARIABLES DE CambiarPantalla()
volatile unsigned char iCP; //auxiliar para el for

//Variables de RetrocederFoco()
volatile unsigned char iRF;

//Variables de CargarObjetoGrafico()
//volatile unsigned char iCOG;

//Variables de ActualizarInterfaz()
volatile unsigned char iAI;

//Variables de AvanzarFoco()
//volatile unsigned char iAF;

//FUNCIONES
/*Función EncontrarInicioDatos------------------------------------------------------------------------------------------------------------------------
Descripción: función que setea "c.offsetDatos" para que apunte al comienzo de los datos del Objeto gráfico en ROM
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void EncontrarInicioDatos(void)
{
	c.indDatosObjGraf = 0;
	c.offsetDatos = 0;	

	//Buscamos el Inicio de los Datos del objeto
	while((c.indDatosObjGraf < c.estado.indDatos) && (c.indDatosObjGraf < ptrForm->cantObjGraf))
	{
		//En este momento, "ptrForm->ptrDatos[c.offset]" apunta al tipo de estructura del primer objeto
		switch (ptrForm->ptrDatos[c.offsetDatos])	//Hacemos un switch con el tipo de estructura del objeto
		{
			case STRUCT_LABEL:
				c.offsetDatos = c.offsetDatos + TAMANIO_DATOS_LABEL;
				break;
			case STRUCT_BUTTON:
				c.offsetDatos = c.offsetDatos + TAMANIO_DATOS_BUTTON;
				break;
			case STRUCT_SPIN_EDIT:
				c.offsetDatos = c.offsetDatos + TAMANIO_DATOS_SPIN_EDIT;
				break;

			case STRUCT_VAL_EDIT:
				c.offsetDatos = c.offsetDatos + TAMANIO_DATOS_VAL_EDIT;
				break;

			case STRUCT_CHECK_BOX:
				c.offsetDatos = c.offsetDatos + TAMANIO_DATOS_CHECKBOX;
				break;

			case STRUCT_COMBO_BOX:
				c.offsetDatos = c.offsetDatos + TAMANIO_DATOS_COMBOBOX;
				break;

			case STRUCT_PROG_BAR:
				c.offsetDatos = c.offsetDatos + TAMANIO_DATOS_PROGBAR;
				break;
		}
		if ((c.indDatosObjGraf + 1) < ptrForm->cantObjGraf)
			c.indDatosObjGraf++;	//Pasamos al siguiente objeto grafico
	}
}	//Fin EncontrarInicioDatos()

/*Función CargarObjetoGrafico------------------------------------------------------------------------------------------------------------------------
Descripción: función que copia todas las variables del objeto gráfico al Cargador de objetos gráficos
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void CargarObjetoGrafico(void)
{
	c.indCadena = 0;
	c.offsetChar = 0;	
	c.offsetCadena = 0;

	c.estado.bandEstado = ptrForm->ptrObjetos[c.estado.indDatos].bandEstado;	//Cargamos las banderas de estado

	EncontrarInicioDatos();	//Encontrar el inicio de los datos

	//Copiamos los datos a una cadena en RAM para ahorrar memoria de programa en las operaciones que siguen
	for (c.indDatos = 0; c.indDatos < TAMANIO_CADENA_DATOS; c.indDatos++)
		c.cadenaDatos[c.indDatos] = ptrForm->ptrDatos[c.offsetDatos++];

	//A esta altura ptrForm->ptrDatos apunta al inicio de la información de inicialización buscada
	//Cargamos los datos básicos comunes
	c.indDatos = 0;
	c.tipoStruct = c.cadenaDatos[c.indDatos++];
	c.x = c.cadenaDatos[c.indDatos++];
	c.y = c.cadenaDatos[c.indDatos++];

	//Si el Objeto Gráfico tiene texto asociado, lo cargamos
	if (c.tipoStruct == STRUCT_LABEL || c.tipoStruct == STRUCT_BUTTON || c.tipoStruct == STRUCT_CHECK_BOX || c.tipoStruct == STRUCT_COMBO_BOX)
	{
		c.numCadena =	c.cadenaDatos[c.indDatos++];	//Cargamos el índice de la cadena de texto asociada
		while((c.indCadena < c.numCadena) && (c.indCadena < ptrForm->cantCadenas))
		{
			while (ptrForm->ptrCadenas[c.offsetCadena] != NULL)	//Mientras no se encuentre el final de cadena (NULL)
				c.offsetCadena++;	//Pasamos al siguiente caracter
			c.offsetCadena++;
			c.indCadena++;	//Pasamos a la siguiente cadena
		}
		
		if (c.tipoStruct != STRUCT_COMBO_BOX)
		{
			//Copiamos la cadena de texto que le corresponde al objeto gráfico
			while (ptrForm->ptrCadenas[c.offsetCadena] != NULL && c.offsetChar < TAMANIO_CADENA_TEXTO)	//Mientras no se encuentre el final de cadena (NULL)
				c.cadenaTexto[c.offsetChar++] = ptrForm->ptrCadenas[c.offsetCadena++];
			c.cadenaTexto[c.offsetChar] = NULL;	//Agregamos un NULL al final de la cadena
		}
	}

	//Basándonos en el tipo de objeto gráfico, cargamos el resto de los valores
	switch (c.tipoStruct)
	{
			case STRUCT_LABEL:
				#ifdef	LABEL
				c.xLabel = c.x;
				c.yLabel = c.y;
				c.tamanioTexto = c.cadenaDatos[c.indDatos++];	//Cargamos el tamaño del texto
				c.estado.bColorNeg = c.cadenaDatos[c.indDatos];	//Cargamos si color del objeto está negado (1) o no (0)
				c.label.estado = c.estado;	//Copiamos las banderas de estado que correspondan
				LabelCantPixels();	//Calculamos la cantidad de elementos y de píxeles del Label
				#endif
				break;

			case STRUCT_BUTTON:
				#ifdef	BUTTON
				c.xLabel = c.x + GROSOR_BORDE_BT;
				c.yLabel = c.y + GROSOR_BORDE_BT + GROSOR_BORDE_LABEL - 1;
				c.tamanioTexto = c.cadenaDatos[c.indDatos++];	//Cargamos el tamaño del texto
				c.estado.bColorNeg = c.cadenaDatos[c.indDatos];	//Cargamos si color del objeto está negado (1) o no (0)
				c.button.estado = c.estado;	//Copiamos las banderas de estado que correspondan
				LabelCantPixels();	//Calculamos la cantidad de elementos y de píxeles del Label
				#endif
				break;

			case STRUCT_SPIN_EDIT:
				#ifdef	SPIN_EDIT
				c.numValProp =	c.cadenaDatos[c.indDatos++];	//Cargamos el índice del valor propio asociado
				c.tamanioTexto = c.cadenaDatos[c.indDatos++];	//Cargamos el tamaño del texto
				c.estado.bColorNeg = c.cadenaDatos[c.indDatos++];	//Cargamos si color del objeto está negado (1) o no (0)
				c.estado.bEditable = c.cadenaDatos[c.indDatos++];	//Cargamos si es editable o no
				c.spinEdit.cifras = c.cadenaDatos[c.indDatos++];	//Cargamos la cantidad de cifras del SpinEdit
				c.spinEdit.incremento = c.cadenaDatos[c.indDatos++];	//Cargamos el incremento del SpinEdit
				c.spinEdit.valMin.LB	= c.cadenaDatos[c.indDatos++];	//Cargamos el LB del valor mínimo del SpinEdit
				c.spinEdit.valMin.HB	= c.cadenaDatos[c.indDatos++];	//Cargamos el HB del valor mínimo del SpinEdit
				c.spinEdit.valMax.LB	= c.cadenaDatos[c.indDatos++];	//Cargamos el LB del valor máximo del SpinEdit
				c.spinEdit.valMax.HB	= c.cadenaDatos[c.indDatos];	//Cargamos el HB del valor máximo del SpinEdit
				c.spinEdit.estado = c.estado;	//Copiamos las banderas de estado que correspondan
				
				//Cargamos el valor propio
				c.spinEdit.valor.word = vPSpinEdits[c.numValProp].valor.word;
				#endif
				break;

			case STRUCT_VAL_EDIT:
				#ifdef	VAL_EDIT
				c.numValProp =	c.cadenaDatos[c.indDatos++];	//Cargamos el índice del valor propio asociado
				c.tamanioTexto = c.cadenaDatos[c.indDatos++];	//Cargamos el tamaño del texto
				c.estado.bColorNeg = c.cadenaDatos[c.indDatos++];	//Cargamos si color del objeto está negado (1) o no (0)
				c.estado.bEditable = c.cadenaDatos[c.indDatos++];	//Cargamos si es editable o no
				c.valEdit.cifras = c.cadenaDatos[c.indDatos++];	//Cargamos la cantidad de cifras del ValEdit
				c.valEdit.cifrasVis = c.cadenaDatos[c.indDatos++];	//Cargamos la cantidad de cifras visibles del ValEdit
				c.valEdit.valMinSigned.LB	= c.cadenaDatos[c.indDatos++];	//Cargamos el LB del valor mínimo del ValEdit
				c.valEdit.valMinSigned.HB	= c.cadenaDatos[c.indDatos++];	//Cargamos el HB del valor mínimo del ValEdit
				c.valEdit.valMaxSigned.LB	= c.cadenaDatos[c.indDatos++];	//Cargamos el LB del valor máximo del ValEdit
				c.valEdit.valMaxSigned.HB	= c.cadenaDatos[c.indDatos];	//Cargamos el HB del valor máximo del ValEdit
				c.valEdit.estado = c.estado;	//Copiamos las banderas de estado que correspondan

				//Cargamos el puntero sl arreglo de valores propios del ValEdit 
				c.valEdit.ptrDigitos = vPValEdits[c.numValProp].ptrDigitos;
				#endif
				break;

			case STRUCT_CHECK_BOX:
				#ifdef	CHECK_BOX
				c.tamanioTexto = c.cadenaDatos[c.indDatos++];	//Cargamos el tamaño del texto

				if (c.tamanioTexto == TEXTO_35)
					c.xLabel = c.x + GROSOR_BORDE_CB + GROSOR_BORDE_LABEL + SEPAR_CUAD_LABEL_CB + ALTO_TEXTO_35 - 1 + 1;
				else
					c.xLabel = c.x + GROSOR_BORDE_CB + GROSOR_BORDE_LABEL + SEPAR_CUAD_LABEL_CB + (ALTO_TEXTO_57 * c.tamanioTexto) - 1 + 1;
				
				c.yLabel = c.y + GROSOR_BORDE_CB + GROSOR_BORDE_LABEL - 2 + 1;

				c.estado.bColorNeg = c.cadenaDatos[c.indDatos++];	//Cargamos si el color del objeto está negado (1) o no (0)
				c.estado.bEditable = c.cadenaDatos[c.indDatos++];	//Cargamos si el color del objeto está negado (1) o no (0)
				//c.checkBox.estado.bColorNeg = c.estado.bColorNeg;
				LabelCantPixels();	//Calculamos la cantidad de elementos y de píxeles del Label asociado
				
				c.checkBox.estado = c.estado;	//Copiamos las banderas de estado que correspondan
				#endif
				break;

			case STRUCT_COMBO_BOX:
				#ifdef	COMBO_BOX
				c.numValProp =	c.cadenaDatos[c.indDatos++];	//Cargamos el índice del valor propio asociado
				c.tamanioTexto = c.cadenaDatos[c.indDatos++];	//Cargamos el tamaño del texto
				c.estado.bColorNeg = c.cadenaDatos[c.indDatos++];	//Cargamos si color del objeto está negado (1) o no (0)
				c.estado.bEditable = c.cadenaDatos[c.indDatos];	//Cargamos si es editable o no
				c.comboBox.estado = c.estado;	//Copiamos las banderas de estado que correspondan

				InicializarComboBox();

				//Cargamos los valores propios del ComboBox 
				c.comboBox.opcionSelec = vPComboBoxes[c.numValProp].opcionSelec;
				#endif
				break;

			case STRUCT_PROG_BAR:
				#ifdef PROG_BAR
				c.numValProp =	c.cadenaDatos[c.indDatos++];	//Cargamos el índice del valor propio asociado
				c.progBar.bVertical = c.cadenaDatos[c.indDatos++];	//Cargamos la orientación de la ProgBar
				c.estado.bColorNeg = c.cadenaDatos[c.indDatos++];	//Cargamos si color del objeto está negado (1) o no (0)
				c.progBar.longitud = c.cadenaDatos[c.indDatos++];	//Cargamos la longitud
				c.progBar.espesor = c.cadenaDatos[c.indDatos];	//Cargamos el espesor
				//c.progBar.cantSegmentos = ptrForm->ptrDatos[c.offsetDatos];	//Cargamos la cantidad de segmentos
				c.progBar.estado = c.estado;	//Copiamos las banderas de estado que correspondan

				c.progBar.pixPorUnidad = (float) ((float) (c.progBar.longitud - 4) / (float) 100);

				//Cargamos los valores propios de la ProgBar 
				c.progBar.bRedibujarTodo = vPProgBars[c.numValProp].bRedibujarTodo;
				c.progBar.progPorcent = vPProgBars[c.numValProp].progPorcent;
				c.progBar.porcentAnterior = vPProgBars[c.numValProp].porcentAnterior;
				c.progBar.pixAnterior = vPProgBars[c.numValProp].pixAnterior;
				#endif
				break;
	}
	
	/*
	//A esta altura ptrForm->ptrDatos apunta al inicio de la información de inicialización buscada
	//Cargamos los datos básicos comunes
	c.tipoStruct = ptrForm->ptrDatos[c.offsetDatos++];
	c.x = ptrForm->ptrDatos[c.offsetDatos++];
	c.y = ptrForm->ptrDatos[c.offsetDatos++];

	//Si el Objeto Gráfico tiene texto asociado, lo cargamos
	if (c.tipoStruct == STRUCT_LABEL || c.tipoStruct == STRUCT_BUTTON || c.tipoStruct == STRUCT_CHECK_BOX || c.tipoStruct == STRUCT_COMBO_BOX)
	{
		c.numCadena =	ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos el índice de la cadena de texto asociada
		while((c.indCadena < c.numCadena) && (c.indCadena < ptrForm->cantCadenas))
		{
			while (ptrForm->ptrCadenas[c.offsetCadena] != NULL)	//Mientras no se encuentre el final de cadena (NULL)
				c.offsetCadena++;	//Pasamos al siguiente caracter
			c.offsetCadena++;
			c.indCadena++;	//Pasamos a la siguiente cadena
		}
		
		if (c.tipoStruct != STRUCT_COMBO_BOX)
		{
			//Copiamos la cadena de texto que le corresponde al objeto gráfico
			while (ptrForm->ptrCadenas[c.offsetCadena] != NULL && c.offsetChar < TAMANIO_CADENA_TEXTO)	//Mientras no se encuentre el final de cadena (NULL)
				c.cadenaTexto[c.offsetChar++] = ptrForm->ptrCadenas[c.offsetCadena++];
			c.cadenaTexto[c.offsetChar] = NULL;	//Agregamos un NULL al final de la cadena
		}
		//else
			//InicializarComboBox();
	}

	//Basándonos en el tipo de objeto gráfico, cargamos el resto de los valores
	switch (c.tipoStruct)
	{
			case STRUCT_LABEL:
				c.xLabel = c.x;
				c.yLabel = c.y;
				c.tamanioTexto = ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos el tamaño del texto
				c.estado.bColorNeg = ptrForm->ptrDatos[c.offsetDatos];	//Cargamos si color del objeto está negado (1) o no (0)
				c.label.estado = c.estado;	//Copiamos las banderas de estado que correspondan
				LabelCantPixels();	//Calculamos la cantidad de elementos y de píxeles del Label
				break;

			case STRUCT_BUTTON:
				c.xLabel = c.x + GROSOR_BORDE_BT;
				c.yLabel = c.y + GROSOR_BORDE_BT + GROSOR_BORDE_LABEL - 1;
				c.tamanioTexto = ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos el tamaño del texto
				c.estado.bColorNeg = ptrForm->ptrDatos[c.offsetDatos];	//Cargamos si color del objeto está negado (1) o no (0)
				c.button.estado = c.estado;	//Copiamos las banderas de estado que correspondan
				LabelCantPixels();	//Calculamos la cantidad de elementos y de píxeles del Label
				break;

			case STRUCT_SPIN_EDIT:
				c.numValProp =	ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos el índice del valor propio asociado
				c.tamanioTexto = ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos el tamaño del texto
				c.estado.bColorNeg = ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos si color del objeto está negado (1) o no (0)
				c.estado.bEditable = ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos si es editable o no
				c.spinEdit.cifras = ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos la cantidad de cifras del SpinEdit
				c.spinEdit.incremento = ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos el incremento del SpinEdit
				c.spinEdit.valMin.LB	= ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos el LB del valor mínimo del SpinEdit
				c.spinEdit.valMin.HB	= ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos el HB del valor mínimo del SpinEdit
				c.spinEdit.valMax.LB	= ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos el LB del valor máximo del SpinEdit
				c.spinEdit.valMax.HB	= ptrForm->ptrDatos[c.offsetDatos];	//Cargamos el HB del valor máximo del SpinEdit
				c.spinEdit.estado = c.estado;	//Copiamos las banderas de estado que correspondan
				
				//Cargamos el valor propio
				c.spinEdit.valor.word = vPSpinEdits[c.numValProp].valor.word;
				break;

			case STRUCT_VAL_EDIT:
				c.numValProp =	ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos el índice del valor propio asociado
				c.tamanioTexto = ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos el tamaño del texto
				c.estado.bColorNeg = ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos si color del objeto está negado (1) o no (0)
				c.estado.bEditable = ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos si es editable o no
				c.valEdit.cifras = ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos la cantidad de cifras del ValEdit
				c.valEdit.cifrasVis = ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos la cantidad de cifras visibles del ValEdit
				c.valEdit.valMinSigned.LB	= ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos el LB del valor mínimo del ValEdit
				c.valEdit.valMinSigned.HB	= ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos el HB del valor mínimo del ValEdit
				c.valEdit.valMaxSigned.LB	= ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos el LB del valor máximo del ValEdit
				c.valEdit.valMaxSigned.HB	= ptrForm->ptrDatos[c.offsetDatos];	//Cargamos el HB del valor máximo del ValEdit
				c.valEdit.estado = c.estado;	//Copiamos las banderas de estado que correspondan

				//Cargamos el puntero sl arreglo de valores propios del ValEdit 
				c.valEdit.ptrDigitos = vPValEdits[c.numValProp].ptrDigitos;
				break;

			case STRUCT_CHECK_BOX:
				c.tamanioTexto = ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos el tamaño del texto

				if (c.tamanioTexto == TEXTO_35)
					c.xLabel = c.x + GROSOR_BORDE_CB + GROSOR_BORDE_LABEL + SEPAR_CUAD_LABEL_CB + ALTO_TEXTO_35 - 1 + 1;
				else
					c.xLabel = c.x + GROSOR_BORDE_CB + GROSOR_BORDE_LABEL + SEPAR_CUAD_LABEL_CB + (ALTO_TEXTO_57 * c.tamanioTexto) - 1 + 1;
				
				c.yLabel = c.y + GROSOR_BORDE_CB + GROSOR_BORDE_LABEL - 2 + 1;

				c.estado.bColorNeg = ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos si el color del objeto está negado (1) o no (0)
				c.estado.bEditable = ptrForm->ptrDatos[c.offsetDatos];	//Cargamos si el color del objeto está negado (1) o no (0)
				//c.checkBox.estado.bColorNeg = c.estado.bColorNeg;
				LabelCantPixels();	//Calculamos la cantidad de elementos y de píxeles del Label asociado
				
				c.checkBox.estado = c.estado;	//Copiamos las banderas de estado que correspondan
				break;

			case STRUCT_COMBO_BOX:
				c.numValProp =	ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos el índice del valor propio asociado
				c.tamanioTexto = ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos el tamaño del texto
				c.estado.bColorNeg = ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos si color del objeto está negado (1) o no (0)
				c.estado.bEditable = ptrForm->ptrDatos[c.offsetDatos];	//Cargamos si es editable o no
				c.comboBox.estado = c.estado;	//Copiamos las banderas de estado que correspondan

				InicializarComboBox();

				//Cargamos los valores propios del ComboBox 
				c.comboBox.opcionSelec = vPComboBox[c.numValProp].opcionSelec;
				break;

			case STRUCT_PROG_BAR:
				c.numValProp =	ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos el índice del valor propio asociado
				c.progBar.bVertical = ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos la orientación de la ProgBar
				c.estado.bColorNeg = ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos si color del objeto está negado (1) o no (0)
				c.progBar.longitud = ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos la longitud
				c.progBar.espesor = ptrForm->ptrDatos[c.offsetDatos++];	//Cargamos el espesor
				//c.progBar.cantSegmentos = ptrForm->ptrDatos[c.offsetDatos];	//Cargamos la cantidad de segmentos
				c.progBar.estado = c.estado;	//Copiamos las banderas de estado que correspondan

				c.progBar.pixPorUnidad = (float) ((float) (c.progBar.longitud - 4) / (float) 100);

				//Cargamos los valores propios de la ProgBar 
				c.progBar.bRedibujarTodo = vPProgBar[c.numValProp].bRedibujarTodo;
				c.progBar.progPorcent = vPProgBar[c.numValProp].progPorcent;
				c.progBar.porcentAnterior = vPProgBar[c.numValProp].porcentAnterior;
				c.progBar.pixAnterior = vPProgBar[c.numValProp].pixAnterior;
				break;
	}
	*/
}	//Fin CargarObjetoGrafico()


/*Función ActualizarObjetoGrafico------------------------------------------------------------------------------------------------------------------------
Descripción: función que grafica el objeto gráfico en pantalla
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ActualizarObjetoGrafico(void)
{
	//Basándonos en el tipo de objeto gráfico, llamamos a la función que debe actualizarlo en pantalla
	switch (c.tipoStruct)
	{
		case STRUCT_LABEL:
			#ifdef	LABEL
			LabelActualizar();
			c.estado.bandEstado = c.label.estado.bandEstado;	//Actualizamos las variables de estado que se hayan modificado
			#endif
			break;
		case STRUCT_BUTTON:
			#ifdef	BUTTON
			ButtonActualizar();
			c.estado.bandEstado = c.button.estado.bandEstado;	//Actualizamos las variables de estado que se hayan modificado
			break;
			#endif
		case STRUCT_SPIN_EDIT:
			#ifdef	SPIN_EDIT
			SpinEditActualizar();
			c.estado.bandEstado = c.spinEdit.estado.bandEstado;	//Actualizamos las variables de estado que se hayan modificado
			#endif
			break;
		
		case STRUCT_VAL_EDIT:
			#ifdef	VAL_EDIT
			ValEditActualizar();
			c.estado.bandEstado = c.valEdit.estado.bandEstado;	//Actualizamos las variables de estado que se hayan modificado
			#endif
			break;
		
		case STRUCT_CHECK_BOX:
			#ifdef	CHECK_BOX
			CheckBoxActualizar();
			c.estado.bandEstado = c.checkBox.estado.bandEstado;	//Actualizamos las variables de estado que se hayan modificado
			#endif
			break;
		
		case STRUCT_COMBO_BOX:
			#ifdef	COMBO_BOX
			ComboBoxActualizar();
			c.estado.bandEstado = c.comboBox.estado.bandEstado;	//Actualizamos las variables de estado que se hayan modificado
			#endif
			break;
		
		case STRUCT_PROG_BAR:
			#ifdef	PROG_BAR
			ProgBarActualizar();
			c.estado.bandEstado = c.progBar.estado.bandEstado;	//Actualizamos las variables de estado que se hayan modificado
			#endif
			break;
	}
}	//Fin ActualizarObjetoGrafico()

/*Función ActualizarInterfaz------------------------------------------------------------------------------------------------------------------------
Descripción: función que consulta todos los objetos de interfaz y los actualiza si son visibles
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ActualizarInterfaz(void)
{
	//Variables de ActualizarInterfaz()
	//volatile unsigned char iAI;

	//Cargamos la pantalla actual para actualizarla
	CargarPantalla();

	for (iAI=0; iAI < ptrForm->cantObjGraf; iAI++)
	{
		//Preguntamos si el Objeto Gráfico es visible y si tengo que redibujarlo
		if(ptrForm->ptrObjetos[iAI].bVisible == 1 && ptrForm->ptrObjetos[iAI].bRedibujar == 1)
		{
			//c.estado.bandEstado = ptrForm->ptrObjetos[iAI].bandEstado;	//Cargamos las banderas de estado
			c.estado.indDatos = ptrForm->ptrObjetos[iAI].indDatos;	//Indicamos cual es el índice del objeto que vamos a cargar	
			CargarObjetoGrafico();	//Cargamos el objeto gráfico en memoria
			ActualizarObjetoGrafico();	//Actualizamos el objeto gráfico en pantalla
			ptrForm->ptrObjetos[iAI].bandEstado = c.estado.bandEstado;	//Actualizamos las variables del objeto gráfico con los cambios que hayan sufrido
			//DescargarObjetoGrafico();	//Actualizamos las variables del objeto gráfico con los cambios que hayan sufrido
		}		
	}
}//fin ActualizarInterfaz()

/*Función QuitarFoco------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que quita el foco al Objeto que lo tiene actualmente y lo redibuja 
Entrada: 
		indFoco: es una variable global.
Salida: 
//-------------------------------------------------------------------------------------------------------------------------------------*/
void QuitarFoco()
{
	//Le quitamos el foco al objeto gráfico que lo tiene actualmente
	ptrFoco[indFoco]->bEnFoco = 0;
	ptrFoco[indFoco]->bRedibujar = 1;

	if (c.tipoStruct == STRUCT_PROG_BAR)	//¿El objeto actual es una ProgBar?
		ptrFoco[indFoco]->bLimpiarFondo = 1;	//Obligamos a la ProgBar que entrega el foco a que se redibuje toda

	//c.progBar.bRedibujarTodo = 1;	//Hacemos esto por si se trata de una ProgBar
}//end QuitarFoco


/*Función CambiarPantalla------------------------------------------------------------------------------------------------------------------------
Descripción: función que setea todos los valores de los objetos de interfaz para cambiar de una pantalla a la otra 
Entrada: 
		numPant: entero que representa el número de pantalla a la que se quiere pasar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void CambiarPantalla(unsigned char numPant)
{
	//unsigned char iCP; //auxiliar para el for
	
	//Cargamos la pantalla anterior (es decir, la que está viendose ahora)
	CargarPantalla();

	//Seteamos como no visibles y sin foco todos los objetos de la pantalla anterior
	for (iCP=0; iCP < ptrForm->cantObjGraf; iCP++)
	{
		ptrForm->ptrObjetos[iCP].bVisible = 0;	
		ptrForm->ptrObjetos[iCP].bEnFoco = 0;
	}

	pantallaActual = numPant; //cambio de pantalla
	//Cargamos la nueva pantalla (la que será graficada)
	CargarPantalla();

	GLCD_Init(NEGRO); //Limpiar pantalla del LCD
	
	//Seteamos como visibles todos los objetos de la pantalla nueva
	for (iCP=0; iCP < ptrForm->cantObjGraf; iCP++)
	{
		ptrForm->ptrObjetos[iCP].bVisible = 1;	
		ptrForm->ptrObjetos[iCP].bRedibujar = 1;

		c.estado.indDatos = ptrForm->ptrObjetos[iCP].indDatos;	//Indicamos cual es el índice del objeto que vamos a cargar
		EncontrarInicioDatos();	//Encontrar el inicio de los datos del objeto gráfico
		if (ptrForm->ptrDatos[c.offsetDatos] == STRUCT_PROG_BAR)	//¿El objeto actual es una PROGBAR?
		{
			//c.offsetDatos = c.offsetDatos + 3; //Apuntamos al índice de valor propio asociado de la ProgBar
			//c.numValProp = ptrForm->ptrDatos[c.offsetDatos];	//Cargamos el índice de valor propio asociado
			//vPProgBars[c.numValProp].bRedibujarTodo = 1;
			ptrForm->ptrObjetos[iCP].bLimpiarFondo = 1;	//Obligamos a la ProgBar que se redibuje toda
		}	
	}

	//Ejecutamos el código específico que sea necesario en cada pantalla
	ExtrasDePantalla();
	//Setear el Foco de la pantalla que corresponda
	SetFoco();
}//end CambiarPantalla


/*Función AsignarFoco------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que asigna el foco y redibuja el objeto en ptrFoco indicado por indFoco 
Entrada: 
		indFoco: es una variable global.
Salida: 
	Devuelve NULL (cero) si el objeto de la interfaz al cual fue enviado el foco no lo acepto, y 1 en caso contrario
//-------------------------------------------------------------------------------------------------------------------------------------*/
unsigned char AsignarFoco()
{
	//Le asignamos el foco al objeto gráfico indicado por indFoco
	if (ptrFoco[indFoco] != NULL)	//¿El foco es válido?
	{
		if (ptrFoco[indFoco]->bVisible == 1)	//¿El objeto al que se quiere asignar el foco es visible?
		{
			ptrFoco[indFoco]->bEnFoco = 1;
			ptrFoco[indFoco]->bRedibujar = 1;
	
			c.spinEdit.bNoRedibujar = 0;
	
			c.estado.indDatos = ptrFoco[indFoco]->indDatos;	//Indicamos cual es el índice del objeto que vamos a cargar
			EncontrarInicioDatos();	//Encontrar el inicio de los datos del objeto gráfico
			if (ptrForm->ptrDatos[c.offsetDatos] == STRUCT_PROG_BAR)	//¿El objeto actual es una PROGBAR?
			{
				ptrFoco[indFoco]->bLimpiarFondo = 1;	//Obligamos a la ProgBar que recibe el foco a que se redibuje toda
				
			}
			return 1; //Se pudo asignar el foco
		}
		else
			return 0; //No se pudo asignar el foco
	}	
}//end AsignarFoco

/*Función RetrocederFoco------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que decrementa el índice de foco
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void RetrocederFoco()
{	
	//unsigned char iRF;
	
	indFocoActual = indFoco;	//Salvamos el índice de foco previo a ejecutar el comportamiento por defecto
	
	//Primero quitamos el foco del objeto que lo tiene actualmente para que solo éste se redibuje
	QuitarFoco();
	
	//Decrementamos el índice de foco e intentamos asignarlo
	if (indFoco > 0)	//¿Todavía no llegué al cero?
		indFoco--; //decremento de foco
	else
	{
		//Buscamos el mayor de los indices del vector de foco que tiene un objeto válido. Empezamos la búsqueda desde el mayor indice y vamos bajando
		for(iRF = CANT_FOCO - 1; iRF > 0; iRF--)
			if (ptrFoco[iRF] != 0)	//¿Ya encontramos un objeto de interfaz válido?
				break;	//Terminamos el bucle
		if (ptrFoco[iRF] != 0)	//¿Se encontró un foco válido?
			indFoco = iRF;	//Asignamos el foco válido
		else
			indFoco = FOCO_NINGUNO;	//La pantalla no tiene focos válidos
	}
	
	AsignarFoco();
}//fin RetrocederFoco()

/*Función AvanzarFoco------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que incrementa el índice de foco
Entrada:
		indFoco: es una variable global.
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void AvanzarFoco()
{
	indFocoActual = indFoco;	//Salvamos el índice de foco previo a ejecutar el comportamiento por defecto

	//Primero quitamos el foco del objeto que lo tiene actualmente para que éste se redibuje
	QuitarFoco();	

	indFoco++;	//Incrementamos el foco
	if (ptrFoco[indFoco] == 0)	//¿Con el incremento anterior salimos del rango de objetos de la pantalla?
																		//Es decir, ¿caimos en un índice que no tiene foco válido?
		if (ptrFoco[0] != 0)	//¿El primer objeto es un foco válido?
			indFoco = 0;	//Asignamos el primer objeto
		else
			indFoco = FOCO_NINGUNO;	//La pantalla no tiene focos válidos

	AsignarFoco();
}//Fin AvanzarFoco()

/*Función EventoTecla------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que llama al  objeto que tiene el foco  para que procese la tecla  presionada 
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void EventoTecla(void)
//Llamar al elemento que tiene el foco para que procese la tecla presionada
{
	c.estado.bandEstado = ptrFoco[indFoco]->bandEstado;	//Cargamos las banderas de estado del objeto que tiene el foco
	c.estado.indDatos = ptrFoco[indFoco]->indDatos;	//Indicamos cual es el índice del objeto que vamos a cargar	
	CargarObjetoGrafico();	//Cargamos el objeto gráfico en memoria

	//Identifico el tipo de objeto/estructura y llamo a la función que corresponda
	switch (c.tipoStruct)
	{
		#ifdef BUTTON
		case STRUCT_BUTTON:
			ComportamientoPropioButton();
			ButtonOnKeyPress();
			break;
		#endif
		#ifdef	SPIN_EDIT
		case STRUCT_SPIN_EDIT:
			ComportamientoPropioSpinEdit();
			SpinEditOnKeyPress();
			break;
		#endif
		#ifdef	VAL_EDIT
		case STRUCT_VAL_EDIT:
			ComportamientoPropioValEdit();
			ValEditOnKeyPress();
			break;
		#endif
		#ifdef CHECK_BOX
		case STRUCT_CHECK_BOX:
			ComportamientoPropioCheckBox();
			CheckBoxOnKeyPress();	
			break;
		#endif
		#ifdef COMBO_BOX
		case STRUCT_COMBO_BOX:
			ComportamientoPropioComboBox();
			ComboBoxOnKeyPress();	
			break;
		#endif
		#ifdef	PROG_BAR
		case STRUCT_PROG_BAR:
			ComportamientoPropioProgBar();
			ProgBarOnKeyPress();	
			break;
		#endif
	}
	
	teclado.teclaPulsada = TECLA_NO_PRES;	//Indico que la tecla ya ha sido usada
	
}	//end EventoTecla


#endif // Fin de INTERFAZ_C


