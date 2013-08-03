#include "interfaz.h"
#include "msgbox.h"

// VARIABLES DE InicInterfaz()
volatile unsigned char iII; 	//Variable del "for"
volatile unsigned char iII2;	//Variable del "for"

extern struct Form formPresenta;
extern struct Form formInicio;
extern struct Form formMediciones;
extern struct Form formParametros;
extern struct Form formConfig;


extern union Estado objetosPresenta[CANT_OBJ_FORM_PRESENTA];
extern union Estado objetosInicio[CANT_OBJ_FORM_INICIO];
extern union Estado objetosMediciones[CANT_OBJ_FORM_MEDICIONES];
extern union Estado objetosParametros[CANT_OBJ_FORM_PARAMETROS];
extern union Estado objetosConfig[CANT_OBJ_FORM_CONFIG];

//rom unsigned char *ptrROM;

const char datosPresenta[] = {
	//OBJETO 0 --> LABEL "MeDEf"
	STRUCT_LABEL,			//Tipo de Estructura
	35,								//Posición en X
	40,								//Posición en Y
	0,								//Número de cadena de texto asociada
	TEXTO_57_MEDIANO,	//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 1 --> LABEL "Medidor de"
	STRUCT_LABEL,			//Tipo de Estructura
	33,								//Posición en X
	25,								//Posición en Y
	1,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 2 --> LABEL "Eficiencia"
	STRUCT_LABEL,			//Tipo de Estructura
	33,								//Posición en X
	15,								//Posición en Y
	2,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO	//Código de color de fondo por defecto
	
	};	//Fin del Vector de Datos	

//1 NULL indica final de cadena - 2 NULLs indican final de los textos del formulario
const char textoPresenta[] = 	"MeDEf\0"					//Cadena 0
															"Medidor de\0"			//Cadena 1
															"Eficiencia\0";		//Cadena 2

const char datosInicio[] = {
	//OBJETO 0 --> LABEL "MeDEf"
	STRUCT_LABEL,			//Tipo de Estructura
	48,								//Posición en X
	55,								//Posición en Y
	0,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,	//Tamaño del texto asociado
	COLOR_NEGADO,			//Código de color de fondo por defecto

	//OBJETO 1 --> BUTTON "Mediciones"
	STRUCT_BUTTON,		//Tipo de Estructura
	34,								//Posición en X
	42,								//Posición en Y
	1,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	
	//OBJETO 2 --> BUTTON "Tarar"
	STRUCT_BUTTON,		//Tipo de Estructura
	50,								//Posición en X
	29,								//Posición en Y
	2,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,		//Código de color de fondo por defecto

	//OBJETO 3 --> BUTTON "Parametros"
	STRUCT_BUTTON,		//Tipo de Estructura
	34,								//Posición en X
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
const char textoInicio[] = 	"MeDEf\0" //Cadena 0
														"Mediciones\0" //Cadena 1
														"Tarar\0" //Cadena 2
														"Parametros\0" //Cadena 3
														"Configuracion\0"; //Cadena 4


const char datosMediciones[] = {
	//OBJETO 0 --> LABEL "MEDICIONES"
	STRUCT_LABEL,			//Tipo de Estructura
	30,								//Posición en X
	55,								//Posición en Y
	0,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NEGADO,			//Código de color de fondo por defecto

	//OBJETO 1 --> LABEL "G de Param:"
	STRUCT_LABEL,			//Tipo de Estructura
	3,								//Posición en X
	47,								//Posición en Y
	1,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	
	//OBJETO 2 --> LABEL "T:"
	STRUCT_LABEL,			//Tipo de Estructura
	10,								//Posición en X
	39,								//Posición en Y
	2,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 3 --> LABEL "min"
	STRUCT_LABEL,			//Tipo de Estructura
	104,								//Posición en X
	39,								//Posición en Y
	3,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 4 --> LABEL "F:"
	STRUCT_LABEL,			//Tipo de Estructura
	5,								//Posición en X
	26,								//Posición en Y
	4,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 5 --> LABEL "[N]"
	STRUCT_LABEL,			//Tipo de Estructura
	39,								//Posición en X
	26,								//Posición en Y
	5,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 6 --> LABEL "Efi:"
	STRUCT_LABEL,			//Tipo de Estructura
	5,								//Posición en X
	15,								//Posición en Y
	6,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 7 --> LABEL "VT:"
	STRUCT_LABEL,			//Tipo de Estructura
	62,								//Posición en X
	26,								//Posición en Y
	7,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 8 --> LABEL "Km/h"
	STRUCT_LABEL,			//Tipo de Estructura
	95,								//Posición en X
	26,								//Posición en Y
	8,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 9 --> LABEL "VNT:"
	STRUCT_LABEL,			//Tipo de Estructura
	62,								//Posición en X
	15,								//Posición en Y
	9,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 10 --> LABEL "Km/h"
	STRUCT_LABEL,			//Tipo de Estructura
	101,								//Posición en X
	15,								//Posición en Y
	8,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NEGADO,	//Código de color de fondo por defecto

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
	
	//OBJETO 13 --> SPINEDIT "G de Param:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	50,								//Posición en X
	47,								//Posición en Y
	0,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	1,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	0,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	CANT_GRUP_PARAM - 1,	//Low Byte (LB) del valor máximo del SpinEdit
	0,								//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 14 --> SPINEDIT "Horas"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	19,								//Posición en X
	39,								//Posición en Y
	1,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	NO_EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	2,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	0,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	59,	//Low Byte (LB) del valor máximo del SpinEdit
	0,								//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 15 --> SPINEDIT "Minutos"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	31,								//Posición en X
	39,								//Posición en Y
	2,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	NO_EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	2,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	0,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	59,							//Low Byte (LB) del valor máximo del SpinEdit		//ValMax = 250
	0,							//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 16 --> SPINEDIT "Segundos"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	43,								//Posición en X
	39,								//Posición en Y
	3,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	NO_EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	2,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	0,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	59,							//Low Byte (LB) del valor máximo del SpinEdit		//ValMax = 250
	0,							//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 17 --> SPINEDIT "Dur: min"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	90,								//Posición en X
	39,								//Posición en Y
	4,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	3,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	1,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	0xE7,							//Low Byte (LB) del valor máximo del SpinEdit		//ValMax = 999
	0x03,							//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 18 --> SPINEDIT "F:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	13,								//Posición en X
	26,								//Posición en Y
	5,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NEGADO,	//Código de color de fondo por defecto
	NO_EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	4,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	0,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	0x0F,							//Low Byte (LB) del valor máximo del SpinEdit		//ValMax = 9999
	0x27,							//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 19 --> SPINEDIT "Efi:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	21,								//Posición en X
	15,								//Posición en Y
	6,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NEGADO,	//Código de color de fondo por defecto
	NO_EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	3,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	0,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	0xE7,							//Low Byte (LB) del valor máximo del SpinEdit		//ValMax = 999
	0x03,							//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 20 --> SPINEDIT de la parte entera de "VT:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	74,								//Posición en X
	26,								//Posición en Y
	7,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NEGADO,	//Código de color de fondo por defecto
	NO_EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	2,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	1,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	0x63,							//Low Byte (LB) del valor máximo del SpinEdit		//ValMax = 99
	0x00,							//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 21 --> SPINEDIT de la parte entera de "VNT:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	80,								//Posición en X
	15,								//Posición en Y
	8,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NEGADO,	//Código de color de fondo por defecto
	NO_EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	2,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	1,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	0x63,							//Low Byte (LB) del valor máximo del SpinEdit		//ValMax = 99
	0x00,							//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 22 --> CHECKBOX "Guardar en SD"
	STRUCT_CHECK_BOX,	//Tipo de Estructura
	64,								//Posición en X
	46,								//Posición en Y
	12,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,					//Código para determinar si el CheckBox es o no Editable

	//OBJETO 23 --> CHECKBOX "Dur:   min"
	STRUCT_CHECK_BOX,	//Tipo de Estructura
	64,								//Posición en X
	38,								//Posición en Y
	13,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,					//Código para determinar si el CheckBox es o no Editable

	//OBJETO 24 --> SPINEDIT de la parte decimal de "VT:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	88,								//Posición en X
	26,								//Posición en Y
	9,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NEGADO,	//Código de color de fondo por defecto
	NO_EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	1,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	1,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	0x09,							//Low Byte (LB) del valor máximo del SpinEdit		//ValMax = 99
	0x00,							//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 25 --> SPINEDIT de la parte decimal de "VNT:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	94,								//Posición en X
	15,								//Posición en Y
	10,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NEGADO,	//Código de color de fondo por defecto
	NO_EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	1,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	1,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	0x09,							//Low Byte (LB) del valor máximo del SpinEdit		//ValMax = 99
	0x00							//High Byte (HB) del valor máximo del SpinEdit

	};	//Fin del Vector de Datos

//1 NULL indica final de cadena - 2 NULLs indican final de los textos del formulario
const char textoMediciones[] = "MEDICIONES\0" //Cadena 0
																"G de Param:\0" //Cadena 1
																"T:\0" //Cadena 2
																"min\0" //Cadena 3
																"F:\0" //Cadena 4
																"[N]\0" //Cadena 5
																"Efi:\0" //Cadena 6
																"VT:\0" //Cadena 7
																"[Km/h]\0" //Cadena 8
																"VNT:\0" //Cadena 9
																"Comenzar\0" //Cadena 10
																"Finalizar\0" //Cadena 11
																"Guardar en SD\0" //Cadena 12
																"Dur:\0"; //Cadena 13
																

const char datosParametros[] = {
	//OBJETO 0 --> LABEL "PARAMETROS"
	STRUCT_LABEL,			//Tipo de Estructura
	31,								//Posición en X
	55,								//Posición en Y
	0,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NEGADO,			//Código de color de fondo por defecto

	//OBJETO 1 --> LABEL "GRUPO DE PARAMETROS:"
	STRUCT_LABEL,			//Tipo de Estructura
	21,								//Posición en X
	47,								//Posición en Y
	1,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	
	//OBJETO 2 --> LABEL "Diametro Traccion:"
	STRUCT_LABEL,			//Tipo de Estructura
	10,								//Posición en X
	33,								//Posición en Y
	2,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 3 --> LABEL "[cm]"
	STRUCT_LABEL,			//Tipo de Estructura
	103,								//Posición en X
	33,								//Posición en Y
	3,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 4 --> LABEL "Diametro no Traccion"
	STRUCT_LABEL,			//Tipo de Estructura
	4,								//Posición en X
	17,								//Posición en Y
	4,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 5 --> LABEL "[cm]"
	STRUCT_LABEL,			//Tipo de Estructura
	109,								//Posición en X
	17,								//Posición en Y
	3,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	
	//OBJETO 6 --> BUTTON "Guardar"
	STRUCT_BUTTON,		//Tipo de Estructura
	13,								//Posición en X
	2,								//Posición en Y
	5,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,		//Código de color de fondo por defecto

	//OBJETO 7 --> BUTTON "Resetear Grupo"
	STRUCT_BUTTON,		//Tipo de Estructura
	56,								//Posición en X
	2,								//Posición en Y
	6,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,		//Código de color de fondo por defecto
	
	//OBJETO 8 --> SPINEDIT "GRUPO DE PARAMETROS:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	103,							//Posición en X
	47,								//Posición en Y
	9,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	1,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	0,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	CANT_GRUP_PARAM - 1,			//Low Byte (LB) del valor máximo del SpinEdit
	0,								//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 9 --> SPINEDIT "Diametro Traccion:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	84,								//Posición en X
	33,								//Posición en Y
	10,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,			//Código para determinar si el SpinEdit es o no Editable
	3,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	0,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	0xE7,	//Low Byte (LB) del valor máximo del SpinEdit
	0x03,								//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 10 --> SPINEDIT "Diametro no Traccion:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	90,								//Posición en X
	17,								//Posición en Y
	11,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	3,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	1,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	0xE7,							//Low Byte (LB) del valor máximo del SpinEdit		//ValMax = 250
	0x03							//High Byte (HB) del valor máximo del SpinEdit
	
	};	//Fin del Vector de Datos

//1 NULL indica final de cadena - 2 NULLs indican final de los textos del formulario
const char textoParametros[] = 	"PARAMETROS\0" //Cadena 0
																		"GRUPO DE PARAMETROS:\0" //Cadena 1
																		"Diametro Traccion:\0" //Cadena 2
																		"[cm]\0" //Cadena 3
																		"Diametro no Traccion:\0" //Cadena 4
																		"Guardar\0" //Cadena 5
																		"Resetear Grupo\0"; //Cadena 6
																	

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
	3, 								//Espesor en píxeles de la barra central de la ProgBar

	//OBJETO 6 --> CHECKBOX "TIEMPO LUZ FONDO:"
	STRUCT_CHECK_BOX,	//Tipo de Estructura
	5,								//Posición en X
	25,								//Posición en Y
	4,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,					//Código para determinar si el CheckBox es o no Editable

	//OBJETO 7 --> SPINEDIT "TIEMPO LUZ FONDO:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	99,								//Posición en X
	26,								//Posición en Y
	12,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits 
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	3,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	1,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	0xE7,							//Low Byte (LB) del valor máximo del SpinEdit		//ValMax = 999
	0x03,							//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 8 --> LABEL "[s]"
	STRUCT_LABEL,			//Tipo de Estructura
	113,							//Posición en X
	26,								//Posición en Y
	5,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO		//Código de color de fondo por defecto

	};	//Fin del Vector de Datos

//1 NULL indica final de cadena - 2 NULLs indican final de los textos del formulario
const char textoConfig[] = 	"CONFIGURACION\0"				//Cadena 0
														"LUZ DE FONDO:\0"				//Cadena 1
														"CONTRASTE:\0"					//Cadena 2
														"Guardar\0"							//Cadena 3
														"TIEMPO LUZ DE FONDO:\0"		//Cadena 4
														"[s]\0";								//Cadena 5


//TABLA DE INDICES DE VALORES PROPIOS
//vPSpinEdits[CANT_SPIN_EDIT];
		//OBJETO 13 --> SPINEDIT "G de Param:"	--> formMediciones --> IndValProp = 0
		//OBJETO 14 --> SPINEDIT "Horas"	--> formMediciones --> IndValProp = 1
		//OBJETO 15 --> SPINEDIT "Minutos"	--> formMediciones --> IndValProp = 2
		//OBJETO 16 --> SPINEDIT "Segundos"	--> formMediciones --> IndValProp = 3
		//OBJETO 17 --> SPINEDIT "Dur: min"	--> formMediciones --> IndValProp = 4
		//OBJETO 18 --> SPINEDIT "Fuerza:"	--> formMediciones --> IndValProp = 5
		//OBJETO 19 --> SPINEDIT "Efi:"	--> formMediciones --> IndValProp = 6
		//OBJETO 20 --> SPINEDIT "Val T:"	--> formMediciones --> IndValProp = 7
		//OBJETO 21 --> SPINEDIT "Val No T:"	--> formMediciones --> IndValProp = 8
		//OBJETO 8 --> SPINEDIT "GRUPO DE PARAMETROS:"	--> formParametros --> IndValProp = 9
		//OBJETO 9 --> SPINEDIT "Diametro Traccion:"	--> formParametros --> IndValProp = 10
		//OBJETO 10 --> SPINEDIT "Diametro no Traccion:"	--> formParametros --> IndValProp = 11
		//OBJETO 7 --> SPINEDIT "TIEMPO LUZ FONDO:"	--> formConfig --> IndValProp = 12

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

	#ifdef MSG_BOX
	formMsgBox.cantObjGraf = 2;
	formMsgBox.cantCadenas = 2;
	formMsgBox.ptrObjetos = &objetosMsgBox[0];
	formMsgBox.ptrDatos =	&datosMsgBox[0];
	formMsgBox.ptrCadenas =	&textoMsgBox[0];
	formMsgBox.ptrObjetos[0].indDatos = 0;	//Indice de datos del Botón "Ok"
	formMsgBox.ptrObjetos[1].indDatos = 1;	//Indice de datos del Botón "Esc"
	#endif
	
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
	formPresenta.cantCadenas = 3;
	formPresenta.ptrObjetos = &objetosPresenta[0];
	formPresenta.ptrDatos =	&datosPresenta[0];
	formPresenta.ptrCadenas =	&textoPresenta[0];

	//PANTALLA INICIO
	formInicio.cantObjGraf = CANT_OBJ_FORM_INICIO;
	formInicio.cantCadenas = 5;
	formInicio.ptrObjetos = &objetosInicio[0];
	formInicio.ptrDatos =	&datosInicio[0];
	formInicio.ptrCadenas =	&textoInicio[0];

	//PANTALLA MEDICIONES
	formMediciones.cantObjGraf = CANT_OBJ_FORM_MEDICIONES;
	formMediciones.cantCadenas = 14;
	formMediciones.ptrObjetos = &objetosMediciones[0];
	formMediciones.ptrDatos =	&datosMediciones[0];
	formMediciones.ptrCadenas =	&textoMediciones[0];

	//PANTALLA PARAMETROS
	formParametros.cantObjGraf = CANT_OBJ_FORM_PARAMETROS;
	formParametros.cantCadenas = 7;
	formParametros.ptrObjetos = &objetosParametros[0];
	formParametros.ptrDatos =	&datosParametros[0];
	formParametros.ptrCadenas =	&textoParametros[0];

	//PANTALLA CONFIG
	formConfig.cantObjGraf = CANT_OBJ_FORM_CONFIG;
	formConfig.cantCadenas = 6;
	formConfig.ptrObjetos = &objetosConfig[0];
	formConfig.ptrDatos =	&datosConfig[0];
	formConfig.ptrCadenas =	&textoConfig[0];

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


