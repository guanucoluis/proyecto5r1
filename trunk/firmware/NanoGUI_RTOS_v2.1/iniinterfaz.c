#include "interfaz.h"

// VARIABLES DE InicInterfaz()
volatile unsigned char iII; 	//Variable del "for"
volatile unsigned char iII2;	//Variable del "for"

//rom unsigned char *ptrROM;

const char datosPresenta[] = {
	//OBJETO 0 --> LABEL "MECOEL"
	STRUCT_LABEL,			//Tipo de Estructura
	29,								//Posición en X
	42,								//Posición en Y
	0,								//Número de cadena de texto asociada
	TEXTO_57_MEDIANO,	//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 1 --> LABEL "Medidor de"
	STRUCT_LABEL,			//Tipo de Estructura
	34,								//Posición en X
	24,								//Posición en Y
	1,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 2 --> LABEL "Conductividad"
	STRUCT_LABEL,			//Tipo de Estructura
	25,								//Posición en X
	15,								//Posición en Y
	2,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 3 --> LABEL "Electrica"
	STRUCT_LABEL,			//Tipo de Estructura
	37,								//Posición en X
	5,								//Posición en Y
	3,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO		//Código de color de fondo por defecto
	
	};	//Fin del Vector de Datos	

//1 NULL indica final de cadena - 2 NULLs indican final de los textos del formulario
const char textoPresenta[] = 	"MECOEL\0"					//Cadena 0
																	"Medidor de\0"			//Cadena 1
																	"Conductividad\0"		//Cadena 2
																	"Electrica\0";			//Cadena 3

const char datosInicio[] = {
	//OBJETO 0 --> LABEL "MECOEL"
	STRUCT_LABEL,			//Tipo de Estructura
	45,								//Posición en X
	55,								//Posición en Y
	0,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,	//Tamaño del texto asociado
	COLOR_NEGADO,			//Código de color de fondo por defecto

	//OBJETO 1 --> BUTTON "Ensayo"
	STRUCT_BUTTON,		//Tipo de Estructura
	41,								//Posición en X
	42,								//Posición en Y
	1,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	
	//OBJETO 2 --> BUTTON "Composites"
	STRUCT_BUTTON,		//Tipo de Estructura
	32,								//Posición en X
	29,								//Posición en Y
	2,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,		//Código de color de fondo por defecto

	//OBJETO 3 --> BUTTON "Programas"
	STRUCT_BUTTON,		//Tipo de Estructura
	35,								//Posición en X
	16,								//Posición en Y
	3,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 4 --> BUTTON "Configuracion"
	STRUCT_BUTTON,		//Tipo de Estructura
	23,								//Posición en X
	3,								//Posición en Y
	4,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO		//Código de color de fondo por defecto

	};	//Fin del Vector de Datos

//1 NULL indica final de cadena - 2 NULLs indican final de los textos del formulario
const char textoInicio[] = 	"MECOEL\0"					//Cadena 0
																"Ensayos\0"					//Cadena 1
																"Composites\0"			//Cadena 2
																"Programas\0"				//Cadena 3
																"Configuracion\0";	//Cadena 4

const char datosEnsayo[] = {
	//OBJETO 0 --> LABEL "ENSAYO"
	STRUCT_LABEL,			//Tipo de Estructura
	42,								//Posición en X
	55,								//Posición en Y
	0,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,	//Tamaño del texto asociado
	COLOR_NEGADO,			//Código de color de fondo por defecto

	//OBJETO 1 --> BUTTON "Ensayo Programado"
	STRUCT_BUTTON,		//Tipo de Estructura
	11,								//Posición en X
	38,								//Posición en Y
	1,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	
	//OBJETO 2 --> BUTTON "Ensayo Libre"
	STRUCT_BUTTON,		//Tipo de Estructura
	28,								//Posición en X
	22,								//Posición en Y
	2,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO		//Código de color de fondo por defecto

	};	//Fin del Vector de Datos

//1 NULL indica final de cadena - 2 NULLs indican final de los textos del formulario
const char textoEnsayo[] = 	"ENSAYO\0"						//Cadena 0
																"Ensayo Programado\0"	//Cadena 1
																"Ensayo Libre\0";			//Cadena 2

const char datosComposite[] = {
	//OBJETO 0 --> LABEL "COMPOSITES"
	STRUCT_LABEL,			//Tipo de Estructura
	33,								//Posición en X
	55,								//Posición en Y
	0,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NEGADO,			//Código de color de fondo por defecto

	//OBJETO 1 --> LABEL "Tipo:"
	STRUCT_LABEL,			//Tipo de Estructura
	37,								//Posición en X
	43,								//Posición en Y
	1,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	
	//OBJETO 2 --> SPINEDIT "Tipo:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	70,								//Posición en X
	43,								//Posición en Y
	0,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	2,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	0,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	9,	//Low Byte (LB) del valor máximo del SpinEdit
	0,								//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 3 --> LABEL "Diametro:"
	STRUCT_LABEL,			//Tipo de Estructura
	7,								//Posición en X
	30,								//Posición en Y
	2,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 4 --> VALEDIT "Diametro:"
	STRUCT_VAL_EDIT,	//Tipo de Estructura
	73,								//Posición en X
	29,								//Posición en Y
	0,								//Índice del valor propio asociado en el vector de valores propios de los ValEdits
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,					//Código para determinar si el ValEdit es o no Editable
	DIG_VAL_EDIT_COMP_DIAM,	//Cantidad de cifras del ValEdit
	DIG_VIS_VAL_EDIT_COMP_DIAM,	//Cantidad de cifras visibles del ValEdit
	1,								//Low Byte (LB) del valor mínimo del ValEdit
	0,								//High Byte (HB) del valor mínimo del ValEdit
	0x0F,							//Low Byte (LB) del valor máximo del ValEdit	- ValMax = 9999
	0x27,							//High Byte (HB) del valor máximo del ValEdit
	
	//OBJETO 5 --> LABEL "um"
	STRUCT_LABEL,			//Tipo de Estructura
	104,							//Posición en X
	30,								//Posición en Y
	3,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 6 --> LABEL "Espesor:"
	STRUCT_LABEL,			//Tipo de Estructura
	7,								//Posición en X
	17,								//Posición en Y
	4,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,		//Código de color de fondo por defecto

	//OBJETO 7 --> VALEDIT "Espesor:"
	STRUCT_VAL_EDIT,	//Tipo de Estructura
	73,								//Posición en X
	16,								//Posición en Y
	1,								//Índice del valor propio asociado en el vector de valores propios de los ValEdits
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,					//Código para determinar si el ValEdit es o no Editable
	DIG_VAL_EDIT_COMP_ESP,	//Cantidad de cifras del ValEdit
	DIG_VIS_VAL_EDIT_COMP_ESP,	//Cantidad de cifras visibles del ValEdit
	1,								//Low Byte (LB) del valor mínimo del ValEdit
	0,								//High Byte (HB) del valor mínimo del ValEdit
	0x0F,							//Low Byte (LB) del valor máximo del ValEdit	- ValMax = 9999
	0x27,							//High Byte (HB) del valor máximo del ValEdit

	//OBJETO 8 --> LABEL "um"
	STRUCT_LABEL,			//Tipo de Estructura
	104,								//Posición en X
	17,								//Posición en Y
	3,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,		//Código de color de fondo por defecto

	//OBJETO 9 --> BUTTON "Guardar"
	STRUCT_BUTTON,		//Tipo de Estructura
	48,								//Posición en X
	2,								//Posición en Y
	5,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,		//Código de color de fondo por defecto

	};	//Fin del Vector de Datos

//1 NULL indica final de cadena - 2 NULLs indican final de los textos del formulario
const char textoComposite[] = "COMPOSITES\0"	//Cadena 0
																	"Tipo:\0"				//Cadena 1
																	"Diametro:\0"		//Cadena 2
																	"um\0"					//Cadena 3
																	"Espesor:\0"		//Cadena 4
																	"Guardar\0";		//Cadena 5

const char datosEnsayoLibre[] = {
	//OBJETO 0 --> LABEL "ENSAYO_LIBRE"
	STRUCT_LABEL,			//Tipo de Estructura
	27,								//Posición en X
	55,								//Posición en Y
	0,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NEGADO,			//Código de color de fondo por defecto

	//OBJETO 1 --> LABEL "COMPOSITE:"
	STRUCT_LABEL,			//Tipo de Estructura
	2,								//Posición en X
	47,								//Posición en Y
	1,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	
	//OBJETO 2 --> LABEL "T FINAL:"
	STRUCT_LABEL,			//Tipo de Estructura
	2,								//Posición en X
	39,								//Posición en Y
	2,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 3 --> LABEL "C"
	STRUCT_LABEL,			//Tipo de Estructura
	52,								//Posición en X
	39,								//Posición en Y
	3,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 4 --> LABEL "T REAL:"
	STRUCT_LABEL,			//Tipo de Estructura
	2,								//Posición en X
	29,								//Posición en Y
	4,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 5 --> LABEL "C"
	STRUCT_LABEL,			//Tipo de Estructura
	53,								//Posición en X
	29,								//Posición en Y
	3,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 6 --> LABEL "TIEMP:"
	STRUCT_LABEL,			//Tipo de Estructura
	66,								//Posición en X
	29,								//Posición en Y
	5,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 7 --> LABEL "CONDUCTIVIDAD:"
	STRUCT_LABEL,			//Tipo de Estructura
	2,								//Posición en X
	21,								//Posición en Y
	6,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 8 --> LABEL "S/m"
	STRUCT_LABEL,			//Tipo de Estructura
	100,								//Posición en X
	21,								//Posición en Y
	7,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 9 --> LABEL "RESISTENCIA:"
	STRUCT_LABEL,			//Tipo de Estructura
	2,								//Posición en X
	13,								//Posición en Y
	8,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 10 --> LABEL "&"
	STRUCT_LABEL,			//Tipo de Estructura
	100,								//Posición en X
	13,								//Posición en Y
	9,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 11 --> BUTTON "Comenzar"
	STRUCT_BUTTON,		//Tipo de Estructura
	18,								//Posición en X
	2,								//Posición en Y
	10,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,		//Código de color de fondo por defecto

	//OBJETO 12 --> BUTTON "Finalizar"
	STRUCT_BUTTON,		//Tipo de Estructura
	72,								//Posición en X
	2,								//Posición en Y
	11,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,		//Código de color de fondo por defecto
	
	//OBJETO 13 --> SPINEDIT "Composite:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	45,								//Posición en X
	47,								//Posición en Y
	1,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	1,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	0,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	9,	//Low Byte (LB) del valor máximo del SpinEdit
	0,								//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 14 --> SPINEDIT "T Final:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	38,								//Posición en X
	39,								//Posición en Y
	2,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	3,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	1,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	250,	//Low Byte (LB) del valor máximo del SpinEdit
	0,								//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 15 --> SPINEDIT "Dur:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	91,								//Posición en X
	39,								//Posición en Y
	3,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	3,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	1,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	0xE7,							//Low Byte (LB) del valor máximo del SpinEdit		//ValMax = 250
	0x03,							//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 16 --> SPINEDIT "Horas"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	93,								//Posición en X
	29,								//Posición en Y
	4,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	NO_EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	2,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	0,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	99,							//Low Byte (LB) del valor máximo del SpinEdit		//ValMax = 250
	0,							//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 17 --> SPINEDIT "Minutos"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	105,								//Posición en X
	29,								//Posición en Y
	5,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	NO_EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	2,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	0,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	59,							//Low Byte (LB) del valor máximo del SpinEdit		//ValMax = 250
	0,							//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 18 --> SPINEDIT "Segundos"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	117,								//Posición en X
	29,								//Posición en Y
	6,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	NO_EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	2,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	0,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	59,							//Low Byte (LB) del valor máximo del SpinEdit		//ValMax = 250
	0,							//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 19 --> CHECKBOX "Guardar en SD"
	STRUCT_CHECK_BOX,	//Tipo de Estructura
	64,								//Posición en X
	46,								//Posición en Y
	12,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,					//Código para determinar si el CheckBox es o no Editable

	//OBJETO 20 --> CHECKBOX "Dur:   min"
	STRUCT_CHECK_BOX,	//Tipo de Estructura
	64,								//Posición en X
	38,								//Posición en Y
	13,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,					//Código para determinar si el CheckBox es o no Editable

	//OBJETO 21 --> LABEL "min"
	STRUCT_LABEL,			//Tipo de Estructura
	105,							//Posición en X
	39,								//Posición en Y
	14,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO		//Código de color de fondo por defecto

	};	//Fin del Vector de Datos

//1 NULL indica final de cadena - 2 NULLs indican final de los textos del formulario
const char textoEnsayoLibre[] = "ENSAYO LIBRE\0"		//Cadena 0
																		"COMPOSITE:\0"			//Cadena 1
																		"T FINAL:\0"				//Cadena 2
																		"C\0"								//Cadena 3
																		"T REAL:\0"					//Cadena 4
																		"TIEMP:\0"					//Cadena 5
																		"CONDUCTIVIDAD:\0"	//Cadena 6
																		"S/m\0"							//Cadena 7
																		"RESISTENCIA:\0"		//Cadena 8
																		"&\0"								//Cadena 9
																		"Comenzar\0"				//Cadena 10
																		"Finalizar\0"				//Cadena 11
																		"Guardar en SD\0"		//Cadena 12
																		"Dur:\0"						//Cadena 13
																		"min\0";						//Cadena 14

const char datosProgramas[] = {
	//OBJETO 0 --> LABEL "PROGRAMAS"
	STRUCT_LABEL,			//Tipo de Estructura
	35,								//Posición en X
	55,								//Posición en Y
	0,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NEGADO,			//Código de color de fondo por defecto

	//OBJETO 1 --> LABEL "PROGRAMA:"
	STRUCT_LABEL,			//Tipo de Estructura
	11,								//Posición en X
	47,								//Posición en Y
	1,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	
	//OBJETO 2 --> LABEL "SEGMENTO:"
	STRUCT_LABEL,			//Tipo de Estructura
	72,								//Posición en X
	47,								//Posición en Y
	2,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 3 --> LABEL "Dur:     min"
	STRUCT_LABEL,			//Tipo de Estructura
	63,								//Posición en X
	18,								//Posición en Y
	3,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 4 --> LABEL "Temp:     C"
	STRUCT_LABEL,			//Tipo de Estructura
	5,								//Posición en X
	31,								//Posición en Y
	4,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 5 --> LABEL "Tipo:"
	STRUCT_LABEL,			//Tipo de Estructura
	62,								//Posición en X
	31,								//Posición en Y
	5,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 6 --> LABEL "Dif:    C"
	STRUCT_LABEL,			//Tipo de Estructura
	5,								//Posición en X
	18,								//Posición en Y
	6,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 7 --> BUTTON "Guardar"
	STRUCT_BUTTON,		//Tipo de Estructura
	10,								//Posición en X
	2,								//Posición en Y
	7,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,		//Código de color de fondo por defecto

	//OBJETO 8 --> BUTTON "Res S"
	STRUCT_BUTTON,		//Tipo de Estructura
	56,								//Posición en X
	2,								//Posición en Y
	8,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,		//Código de color de fondo por defecto

	//OBJETO 9 --> BUTTON "Res P"
	STRUCT_BUTTON,		//Tipo de Estructura
	96,								//Posición en X
	2,								//Posición en Y
	9,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,		//Código de color de fondo por defecto
	
	//OBJETO 10 --> SPINEDIT "PROGRAMA:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	50,								//Posición en X
	47,								//Posición en Y
	7,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	1,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	0,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	5,	//Low Byte (LB) del valor máximo del SpinEdit
	0,								//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 11 --> SPINEDIT "SEGMENTO:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	113,								//Posición en X
	47,								//Posición en Y
	8,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	2,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	0,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	9,	//Low Byte (LB) del valor máximo del SpinEdit
	0,								//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 12 --> SPINEDIT "Temp:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	27,								//Posición en X
	31,								//Posición en Y
	9,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	3,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	1,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	0xE7,							//Low Byte (LB) del valor máximo del SpinEdit		//ValMax = 250
	0x03,							//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 13 --> SPINEDIT "Duracion:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	80,								//Posición en X
	18,								//Posición en Y
	10,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	3,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	0,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	0xE7,							//Low Byte (LB) del valor máximo del SpinEdit		//ValMax = 999
	0x03,							//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 14 --> SPINEDIT "Dif:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	21,								//Posición en X
	18,								//Posición en Y
	11,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	2,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	0,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	15,								//Low Byte (LB) del valor máximo del SpinEdit		//ValMax = 250
	0,								//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 15 --> COMBOBOX "Tipo:"
	STRUCT_COMBO_BOX,	//Tipo de Estructura
	83,								//Posición en X
	31,								//Posición en Y
	10,								//Número de cadena de texto asociada que contiene las opciones del ComboBox 
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,					//Código para determinar si el ComboBox es o no Editable
	0									//Índice del valor propio asociado en el vector de valores propios de los ComboBox

	};	//Fin del Vector de Datos

//1 NULL indica final de cadena - 2 NULLs indican final de los textos del formulario
const char textoProgramas[] = 	"PROGRAMAS\0"		//Cadena 0
																		"PROGRAMA:\0"		//Cadena 1
																		"SEGMENTO:\0"		//Cadena 2
																		"Dur:     min\0"//Cadena 3
																		"Temp:     C\0"	//Cadena 4
																		"Tipo:\0"				//Cadena 5
																		"Dif:    C\0"		//Cadena 6
																		"Guardar\0"			//Cadena 7
																		"Res S\0"				//Cadena 8
																		"Res P\0"				//Cadena 9
																		"Nulo\0"				//Cadena 10
																		"Final\0"				//Cadena 11
																		"Normal\0\n";		//Cadena 12

const char datosConfig[] = {
	//OBJETO 0 --> LABEL "CONFIGURACION"
	STRUCT_LABEL,			//Tipo de Estructura
	21,								//Posición en X
	55,								//Posición en Y
	0,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,	//Tamaño del texto asociado
	COLOR_NEGADO,			//Código de color de fondo por defecto

	//OBJETO 1 --> LABEL "LUZ DE FONDO:"
	STRUCT_LABEL,			//Tipo de Estructura
	5,								//Posición en X
	45,								//Posición en Y
	1,								//Número de cadena de texto asociada
	TEXTO_35,	//Tamaño del texto asociado
	COLOR_NO_NEGADO,			//Código de color de fondo por defecto

	//OBJETO 2 --> LABEL "CONTRASTE:"
	STRUCT_LABEL,			//Tipo de Estructura
	5,								//Posición en X
	36,								//Posición en Y
	2,								//Número de cadena de texto asociada
	TEXTO_35,	//Tamaño del texto asociado
	COLOR_NO_NEGADO,			//Código de color de fondo por defecto

	//OBJETO 3 --> BUTTON "Guardar"
	STRUCT_BUTTON,		//Tipo de Estructura
	48,								//Posición en X
	2,								//Posición en Y
	3,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	
	//OBJETO 4 --> PROGBAR "LUZ DE FONDO:"
	STRUCT_PROG_BAR,	//Tipo de Estructura
	65,								//Posición en X
	45,								//Posición en Y
	0,								//Índice del valor propio asociado en el vector de valores propios de las ProgBars
	HORIZONTAL,				//Código de orientación de la ProgBar
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	54,								//Longitud en píxeles de la ProgBar
	3, 								//Espesor en píxeles de la barra central de la ProgBar
	//16,								//Cantidad de segmentos en que se divide la ProgBar							

	//OBJETO 5 --> PROGBAR "CONTRASTE:"
	STRUCT_PROG_BAR,	//Tipo de Estructura
	53,								//Posición en X
	36,								//Posición en Y
	1,								//Índice del valor propio asociado en el vector de valores propios de las ProgBars
	HORIZONTAL,				//Código de orientación de la ProgBar
	COLOR_NO_NEGADO,		//Código de color de fondo por defecto
	66,								//Longitud en píxeles de la ProgBar
	3 								//Espesor en píxeles de la barra central de la ProgBar

	};	//Fin del Vector de Datos

//1 NULL indica final de cadena - 2 NULLs indican final de los textos del formulario
const char textoConfig[] = 	"CONFIGURACION\0"			//Cadena 0
																"LUZ DE FONDO:\0"			//Cadena 1
																"CONTRASTE:\0"				//Cadena 2
																"Guardar\0";					//Cadena 3

const char datosConfigEnsayo[] = {
	//OBJETO 0 --> LABEL "CONFIG. ENSAYO"
	STRUCT_LABEL,			//Tipo de Estructura
	14,								//Posición en X
	55,								//Posición en Y
	0,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,	//Tamaño del texto asociado
	COLOR_NEGADO,			//Código de color de fondo por defecto

	//OBJETO 1 --> LABEL "COMPOSITE:"
	STRUCT_LABEL,			//Tipo de Estructura
	40,								//Posición en X
	46,								//Posición en Y
	1,								//Número de cadena de texto asociada
	TEXTO_35,	//Tamaño del texto asociado
	COLOR_NO_NEGADO,			//Código de color de fondo por defecto

	//OBJETO 2 --> LABEL "PROGRAMA A EJECUTAR:"
	STRUCT_LABEL,			//Tipo de Estructura
	24,								//Posición en X
	37,								//Posición en Y
	2,								//Número de cadena de texto asociada
	TEXTO_35,	//Tamaño del texto asociado
	COLOR_NO_NEGADO,			//Código de color de fondo por defecto

	//OBJETO 3 --> BUTTON "Comenzar Ensayo"
	STRUCT_BUTTON,		//Tipo de Estructura
	33,								//Posición en X
	2,								//Posición en Y
	3,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	
	//OBJETO 4 --> SPINEDIT "COMPOSITE:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	83,								//Posición en X
	46,								//Posición en Y
	12,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	1,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	0,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	9,	//Low Byte (LB) del valor máximo del SpinEdit		//ValMax = 250
	0,								//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 5 --> SPINEDIT "PROGRAMA A EJECUTAR:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	107,								//Posición en X
	37,								//Posición en Y
	13,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	1,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	0,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	9,	//Low Byte (LB) del valor máximo del SpinEdit		//ValMax = 250
	0,								//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 6 --> CHECKBOX "Guardar en SD"
	STRUCT_CHECK_BOX,	//Tipo de Estructura
	32,								//Posición en X
	26,								//Posición en Y
	4,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,					//Código para determinar si el CheckBox es o no Editable

	//OBJETO 7 --> CHECKBOX "Apagar al terminar"
	STRUCT_CHECK_BOX,	//Tipo de Estructura
	24,								//Posición en X
	15,								//Posición en Y
	5,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE					//Código para determinar si el CheckBox es o no Editable

	};	//Fin del Vector de Datos

//1 NULL indica final de cadena - 2 NULLs indican final de los textos del formulario
const char textoConfigEnsayo[] = 	"CONFIG. DE ENSAYO\0"			//Cadena 0
																			"COMPOSITE:\0"						//Cadena 1
																			"PROGRAMA A EJECUTAR:\0"	//Cadena 2
																			"Comenzar Ensayo\0"				//Cadena 3
																			"Guardar en SD\0"					//Cadena 4
																			"Apagar al terminar\0";		//Cadena 5

const char datosEjecEnsayo[] = {
	//OBJETO 0 --> LABEL "P:"
	STRUCT_LABEL,			//Tipo de Estructura
	1,								//Posición en X
	57,								//Posición en Y
	0,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NEGADO,			//Código de color de fondo por defecto

	//OBJETO 1 --> LABEL "S:"
	STRUCT_LABEL,			//Tipo de Estructura
	17,								//Posición en X
	57,								//Posición en Y
	1,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NEGADO,			//Código de color de fondo por defecto
	
	//OBJETO 2 --> LABEL "DS:   min"
	STRUCT_LABEL,			//Tipo de Estructura
	53,								//Posición en X
	57,								//Posición en Y
	2,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 3 --> LABEL ":  :"
	STRUCT_LABEL,			//Tipo de Estructura
	102,								//Posición en X
	58,								//Posición en Y
	3,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 4 --> LABEL "C:"
	STRUCT_LABEL,			//Tipo de Estructura
	37,								//Posición en X
	57,								//Posición en Y
	4,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 5 --> LABEL "SP:"
	STRUCT_LABEL,			//Tipo de Estructura
	1,								//Posición en X
	0,								//Posición en Y
	5,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 6 --> LABEL "T:"
	STRUCT_LABEL,			//Tipo de Estructura
	29,								//Posición en X
	0,								//Posición en Y
	6,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 7 --> LABEL "C:"
	STRUCT_LABEL,			//Tipo de Estructura
	67,								//Posición en X
	0,								//Posición en Y
	4,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 8 --> SPINEDIT "P:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	9,								//Posición en X
	57,								//Posición en Y
	14,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	NO_EDITABLE,			//Código para determinar si el SpinEdit es o no Editable
	1,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	0,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	9,	//Low Byte (LB) del valor máximo del SpinEdit
	0,								//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 9 --> SPINEDIT "S:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	25,								//Posición en X
	57,								//Posición en Y
	15,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NEGADO,			//Código de color de fondo por defecto
	NO_EDITABLE,			//Código para determinar si el SpinEdit es o no Editable
	2,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	1,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	9,	//Low Byte (LB) del valor máximo del SpinEdit
	0,								//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 10 --> SPINEDIT "C:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	45,								//Posición en X
	57,								//Posición en Y
	16,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NEGADO,			//Código de color de fondo por defecto
	NO_EDITABLE,			//Código para determinar si el SpinEdit es o no Editable
	1,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	0,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	9,	//Low Byte (LB) del valor máximo del SpinEdit	
	0,								//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 11 --> SPINEDIT "DS:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	65,								//Posición en X
	57,								//Posición en Y
	17,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NEGADO,			//Código de color de fondo por defecto
	NO_EDITABLE,			//Código para determinar si el SpinEdit es o no Editable
	3,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	1,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	0xE7,							//Low Byte (LB) del valor máximo del SpinEdit		//ValMax = 999
	0x03,							//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 12 --> SPINEDIT "Horas"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	94,								//Posición en X
	57,								//Posición en Y
	18,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NEGADO,			//Código de color de fondo por defecto
	NO_EDITABLE,			//Código para determinar si el SpinEdit es o no Editable
	2,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	0,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	99,							//Low Byte (LB) del valor máximo del SpinEdit		//ValMax = 99
	0,							//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 13 --> SPINEDIT "Minutos"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	106,							//Posición en X
	57,								//Posición en Y
	19,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NEGADO,			//Código de color de fondo por defecto
	NO_EDITABLE,			//Código para determinar si el SpinEdit es o no Editable
	2,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	0,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	59,								//Low Byte (LB) del valor máximo del SpinEdit		//ValMax = 250
	0,								//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 14 --> SPINEDIT "Segundos"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	118,								//Posición en X
	57,								//Posición en Y
	20,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NEGADO,			//Código de color de fondo por defecto
	NO_EDITABLE,			//Código para determinar si el SpinEdit es o no Editable
	2,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	0,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	59,								//Low Byte (LB) del valor máximo del SpinEdit		//ValMax = 250
	0,								//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 15 --> SPINEDIT "SP:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	13,								//Posición en X
	0,								//Posición en Y
	21,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NEGADO,			//Código de color de fondo por defecto
	NO_EDITABLE,			//Código para determinar si el SpinEdit es o no Editable
	3,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	0,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	250,							//Low Byte (LB) del valor máximo del SpinEdit		//ValMax = 250
	0,								//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 16 --> LABEL "S/m"
	STRUCT_LABEL,			//Tipo de Estructura
	111,							//Posición en X
	0,								//Posición en Y
	7,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 17 --> LABEL "C"
	STRUCT_LABEL,			//Tipo de Estructura
	60,								//Posición en X
	0,								//Posición en Y
	8,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NEGADO	//Código de color de fondo por defecto

	};	//Fin del Vector de Datos

//1 NULL indica final de cadena - 2 NULLs indican final de los textos del formulario
const char textoEjecEnsayo[] = 	"P:\0"				//Cadena 0
																		"S:\0"				//Cadena 1
																		"DS:   min\0"	//Cadena 2
																		":  :\0"			//Cadena 3
																		"C:\0"				//Cadena 4
																		"SP:\0"				//Cadena 5
																		"T:\0"				//Cadena 6
																		"S/m\0"				//Cadena 7
																		"C\0";				//Cadena 8

//TABLA DE INDICES DE VALORES PROPIOS
//vPSpinEdits[CANT_SPIN_EDIT];
		//OBJETO 2 --> SPINEDIT "Tipo:"	--> formComposites --> IndValProp = 0
		//OBJETO 13 --> SPINEDIT "Composite:"	--> formEnsayoLibre --> IndValProp = 1
		//OBJETO 14 --> SPINEDIT "T Final:"	--> formEnsayoLibre --> IndValProp = 2
		//OBJETO 15 --> SPINEDIT "Dur:"	--> formEnsayoLibre --> IndValProp = 3
		//OBJETO 16 --> SPINEDIT "Horas"	--> formEnsayoLibre --> IndValProp = 4
		//OBJETO 17 --> SPINEDIT "Minutos"	--> formEnsayoLibre --> IndValProp = 5
		//OBJETO 18 --> SPINEDIT "Segundos"	--> formEnsayoLibre --> IndValProp = 6
		//OBJETO 10 --> SPINEDIT "PROGRAMA:"	--> formProgramas --> IndValProp = 7
		//OBJETO 11 --> SPINEDIT "SEGMENTO:"	--> formProgramas --> IndValProp = 8
		//OBJETO 12 --> SPINEDIT "Temp:"	--> formProgramas --> IndValProp = 9
		//OBJETO 13 --> SPINEDIT "Duracion:"	--> formProgramas --> IndValProp = 10
		//OBJETO 14 --> SPINEDIT "Dif:"	--> formProgramas --> IndValProp = 11
		//OBJETO 4 --> SPINEDIT "COMPOSITE:"	--> formConfigEnsayo --> IndValProp = 12
		//OBJETO 5 --> SPINEDIT "PROGRAMA A EJECUTAR:"	--> formConfigEnsayo --> IndValProp = 13
		//OBJETO 8 --> SPINEDIT "P:"	--> formEjecEnsayo --> IndValProp = 14
		//OBJETO 9 --> SPINEDIT "S:"	--> formEjecEnsayo --> IndValProp = 15
		//OBJETO 10 --> SPINEDIT "C:"	--> formEjecEnsayo --> IndValProp = 16
		//OBJETO 11 --> SPINEDIT "DS:"	--> formEjecEnsayo --> IndValProp = 17
		//OBJETO 12 --> SPINEDIT "Horas"	--> formEjecEnsayo --> IndValProp = 18
		//OBJETO 13 --> SPINEDIT "Minutos"	--> formEjecEnsayo --> IndValProp = 19
		//OBJETO 14 --> SPINEDIT "Segundos"	--> formEjecEnsayo --> IndValProp = 20
		//OBJETO 15 --> SPINEDIT "SP:"	--> formEjecEnsayo --> IndValProp = 21

//vPValEdits[CANT_VAL_EDIT];
		//OBJETO 4 --> VALEDIT "Diametro:" --> formComposites --> IndValProp = 0
		//OBJETO 7 --> VALEDIT "Espesor:" --> formComposites --> IndValProp = 1
//vPComboBox[CANT_COMBOBOX];
		//OBJETO 15 --> COMBOBOX "Tipo:" --> formProgramas --> IndValProp = 0
//vPProgBar[CANT_PROGBAR];
		//OBJETO 4 --> PROGBAR "LUZ DE FONDO:" --> formConfig --> IndValProp = 0
		//OBJETO 5 --> PROGBAR "CONTRASTE:" --> formConfig --> IndValProp = 1

//FUNCIONES
/*Función InicInterfaz------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que inicializa la Interfaz
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void InicInterfaz(void)
{
	//unsigned char iII; // variable del "for"
	//unsigned char iII2;	//variable del "for"
	
	pantallaActual = 255; //inicio en un nro alto que no existe
	
	//Inicialización del display real
	DispReal.offsetX = OFFSETX_DISP_REAL;
	DispReal.offsetY = OFFSETY_DISP_REAL;
	DispReal.ancho = 	ANCHO_DISP_REAL;
	DispReal.alto = 	ALTO_DISP_REAL;
	
	//Seteamos el número de elementos por formulario
	//Primero reseteamos los valores de todos los Formulario
	for (iII=1; iII <= NUM_PANTALLAS; iII++)
	{
		pantallaActual = iII;
		CargarPantalla();	//Cargamos la pantalla
		ptrForm->saveFoco = 0;
		ptrForm->cantObjGraf = 0;
		ptrForm->cantCadenas = 0;
		ptrForm->ptrDatos = 0;
		ptrForm->ptrCadenas = 0;
		ptrForm->estado.bandEstado = 0;
		ptrForm->estado.indDatos = 0;
	}

	//Ahora asignamos la cantidad de objetos que tiene cada pantalla
	//PANTALLA PRESENTA
	formPresenta.cantObjGraf = CANT_OBJ_FORM_PRESENTA;
	formPresenta.cantCadenas = 4;
	formPresenta.ptrObjetos = &objetosPresenta[0];
	formPresenta.ptrDatos =	&datosPresenta[0];
	formPresenta.ptrCadenas =	&textoPresenta[0];

	//PANTALLA INICIO
	formInicio.cantObjGraf = CANT_OBJ_FORM_INICIO;
	formInicio.cantCadenas = 5;
	formInicio.ptrObjetos = &objetosInicio[0];
	formInicio.ptrDatos =	&datosInicio[0];
	formInicio.ptrCadenas =	&textoInicio[0];

	//PANTALLA ENSAYO
	formEnsayo.cantObjGraf = CANT_OBJ_FORM_ENSAYO;
	formEnsayo.cantCadenas = 5;
	formEnsayo.ptrObjetos = &objetosEnsayo[0];
	formEnsayo.ptrDatos =	&datosEnsayo[0];
	formEnsayo.ptrCadenas =	&textoEnsayo[0];
	
	//PANTALLA COMPOSITE
	formComposite.cantObjGraf = CANT_OBJ_FORM_COMPOSITE;
	formComposite.cantCadenas = 6;
	formComposite.ptrObjetos = &objetosComposite[0];
	formComposite.ptrDatos =	&datosComposite[0];
	formComposite.ptrCadenas =	&textoComposite[0];

	//Inicialización de los ValEdits
	vPValEdits[0].ptrDigitos = &valEditCompositeDiametro[0];
	vPValEdits[1].ptrDigitos = &valEditCompositeEspesor[0];

	//PANTALLA ENSAYO LIBRE
	formEnsayoLibre.cantObjGraf = CANT_OBJ_FORM_ENSAYO_LIBRE;
	formEnsayoLibre.cantCadenas = 15;
	formEnsayoLibre.ptrObjetos = &objetosEnsayoLibre[0];
	formEnsayoLibre.ptrDatos =	&datosEnsayoLibre[0];
	formEnsayoLibre.ptrCadenas =	&textoEnsayoLibre[0];

	//PANTALLA PROGRAMAS
	formProgramas.cantObjGraf = CANT_OBJ_FORM_PROGRAMAS;
	formProgramas.cantCadenas = 13;
	formProgramas.ptrObjetos = &objetosProgramas[0];
	formProgramas.ptrDatos =	&datosProgramas[0];
	formProgramas.ptrCadenas =	&textoProgramas[0];

	//PANTALLA CONFIG
	formConfig.cantObjGraf = CANT_OBJ_FORM_CONFIG;
	formConfig.cantCadenas = 4;
	formConfig.ptrObjetos = &objetosConfig[0];
	formConfig.ptrDatos =	&datosConfig[0];
	formConfig.ptrCadenas =	&textoConfig[0];

	//PANTALLA CONFIG ENSAYO
	formConfigEnsayo.cantObjGraf = CANT_OBJ_FORM_CONFIG_ENSAYO;
	formConfigEnsayo.cantCadenas = 6;
	formConfigEnsayo.ptrObjetos = &objetosConfigEnsayo[0];
	formConfigEnsayo.ptrDatos =	&datosConfigEnsayo[0];
	formConfigEnsayo.ptrCadenas =	&textoConfigEnsayo[0];

	//PANTALLA EJEC ENSAYO
	formEjecEnsayo.cantObjGraf = CANT_OBJ_FORM_EJEC_ENSAYO;
	formEjecEnsayo.cantCadenas = 9;
	formEjecEnsayo.ptrObjetos = &objetosEjecEnsayo[0];
	formEjecEnsayo.ptrDatos =	&datosEjecEnsayo[0];
	formEjecEnsayo.ptrCadenas =	&textoEjecEnsayo[0];

	//Seteo general de variables de estado e índices de datos para todos los objetos de todos los formularios
	for (iII=0; iII < NUM_PANTALLAS; iII++)
	{
		pantallaActual = iII;
		CargarPantalla();	//Cargamos la pantalla
		for (iII2=0; iII2 < ptrForm->cantObjGraf; iII2++)
		{
			ptrForm->ptrObjetos[iII2].bandEstado = 0;	//Reseteamos las banderas de estado
			ptrForm->ptrObjetos[iII2].indDatos = iII2;
		}
	}

	//Inicializamos el contador genérico
	Contador1ms = 0;
	//Cargamos los focos de las pantallas
	//CargarFocos();
	//Setear Pantalla de Inicio
	CambiarPantalla(PANTALLA_PRESENTA);
}//fin InicInterfaz()


