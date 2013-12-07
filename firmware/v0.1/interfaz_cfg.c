
#include <interfaz_cfg.h>
#include <interfaz.h>

struct Form formPresenta;
struct Form formInicio;
struct Form formMediciones;
struct Form formTarar;
struct Form formParametros;
struct Form formConfig;

//VECTORES DE OBJETOS
//Arreglos de estructuras con los valores propios
struct ValPropSpinEdit vPSpinEdits[CANT_SPIN_EDIT];
struct ValPropProgBar vPProgBars[CANT_PROGBAR];

union Estado objetosPresenta[CANT_OBJ_FORM_PRESENTA];
union Estado objetosInicio[CANT_OBJ_FORM_INICIO];
union Estado objetosMediciones[CANT_OBJ_FORM_MEDICIONES];
union Estado objetosTarar[CANT_OBJ_FORM_TARAR];
union Estado objetosParametros[CANT_OBJ_FORM_PARAMETROS];
union Estado objetosConfig[CANT_OBJ_FORM_CONFIG];

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
	38,								//Posición en X
	25,								//Posición en Y
	1,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 2 --> LABEL "Eficiencia"
	STRUCT_LABEL,			//Tipo de Estructura
	40,								//Posición en X
	14,								//Posición en Y
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
	35,								//Posición en X
	42,								//Posición en Y
	1,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 2 --> BUTTON "Tarar"
	STRUCT_BUTTON,		//Tipo de Estructura
	47,								//Posición en X
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
	29,								//Posición en X
	3,								//Posición en Y
	4,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO		//Código de color de fondo por defecto

	};	//Fin del Vector de Datos

//1 NULL indica final de cadena - 2 NULLs indican final de los textos del formulario
const char textoInicio[] =  "MeDEf\0" //Cadena 0
                            "Mediciones\0" //Cadena 1
                            "Tarar\0" //Cadena 2
                            "Parametros\0" //Cadena 3
                            "Configuracion\0"; //Cadena 4


const char datosMediciones[] = {
	//OBJETO 0 --> LABEL "MEDICIONES"
	STRUCT_LABEL,			//Tipo de Estructura
	36,								//Posición en X
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
	3,								//Posición en X
	26,								//Posición en Y
	4,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 5 --> LABEL "[gf]"
	STRUCT_LABEL,			//Tipo de Estructura
	38,								//Posición en X
	26,								//Posición en Y
	5,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 6 --> LABEL "Efi:"
	STRUCT_LABEL,			//Tipo de Estructura
	3,								//Posición en X
	15,								//Posición en Y
	6,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 7 --> LABEL "VT:"
	STRUCT_LABEL,			//Tipo de Estructura
	61,								//Posición en X
	26,								//Posición en Y
	7,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 8 --> LABEL "[Km/h]"
	STRUCT_LABEL,			//Tipo de Estructura
	95,								//Posición en X
	26,								//Posición en Y
	8,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 9 --> LABEL "VNT:"
	STRUCT_LABEL,			//Tipo de Estructura
	61,								//Posición en X
	15,								//Posición en Y
	9,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 10 --> LABEL "[Km/h]"
	STRUCT_LABEL,			//Tipo de Estructura
	100,								//Posición en X
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
	47,								//Posición en X
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
	12,								//Posición en X
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
	19,								//Posición en X
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
	73,								//Posición en X
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
	79,								//Posición en X
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

	//OBJETO 22 --> CHECKBOX "Dur:   min"
	STRUCT_CHECK_BOX,	//Tipo de Estructura
	64,								//Posición en X
	38,								//Posición en Y
	13,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,					//Código para determinar si el CheckBox es o no Editable

	//OBJETO 23 --> SPINEDIT de la parte decimal de "VT:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	87,								//Posición en X
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

	//OBJETO 24 --> SPINEDIT de la parte decimal de "VNT:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	93,								//Posición en X
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
	0x00,							//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 25 --> SPINEDIT "Medicion:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	101,							//Posición en X
	47,								//Posición en Y
	11,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,					//Código para determinar si el SpinEdit es o no Editable
	3,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	0,								//Low Byte (LB) del valor mínimo del SpinEdit
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	0x09,							//Low Byte (LB) del valor máximo del SpinEdit		//ValMax = 99
	0x00,							//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 26 --> LABEL "Medicion:"
	STRUCT_LABEL,			//Tipo de Estructura
	64,								//Posición en X
	47,								//Posición en Y
	12,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO		//Código de color de fondo por defecto

	};	//Fin del Vector de Datos

//1 NULL indica final de cadena - 2 NULLs indican final de los textos del formulario
const char textoMediciones[] =  "MEDICIONES\0" //Cadena 0
                                "G de Param:\0" //Cadena 1
                                "T:\0" //Cadena 2
                                "min\0" //Cadena 3
                                "F:\0" //Cadena 4
                                "[gf]\0" //Cadena 5
                                "Efi:\0" //Cadena 6
                                "VT:\0" //Cadena 7
                                "[Km/h]\0" //Cadena 8
                                "VM:\0" //Cadena 9
                                "Comenzar\0" //Cadena 10
                                "Finalizar\0" //Cadena 11
                                "Medicion:\0" //Cadena 12
                                "Dur:\0"; //Cadena 13

const char datosTarar[] = {
	//OBJETO 0 --> LABEL "TARAR"
	STRUCT_LABEL,			//Tipo de Estructura
	49,								//Posición en X
	55,								//Posición en Y
	0,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NEGADO,			//Código de color de fondo por defecto

	//OBJETO 1 --> LABEL "Fuerza de Tara:"
	STRUCT_LABEL,			//Tipo de Estructura
	8,								//Posición en X
	40,								//Posición en Y
	1,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,			//Código de color de fondo por defecto

	//OBJETO 2 --> LABEL "Fuerza Actual:"
	STRUCT_LABEL,			//Tipo de Estructura
	8,								//Posición en X
	25,								//Posición en Y
	2,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,			//Código de color de fondo por defecto

	//OBJETO 3 --> LABEL "[Kgf]"
	STRUCT_LABEL,			//Tipo de Estructura
	94,								//Posición en X
	40,								//Posición en Y
	3,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,			//Código de color de fondo por defecto

	//OBJETO 4 --> LABEL "[Kgf]"
	STRUCT_LABEL,			//Tipo de Estructura
	94,								//Posición en X
	25,								//Posición en Y
	3,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,			//Código de color de fondo por defecto

	//OBJETO 5 --> BUTTON "Tarar"
	STRUCT_BUTTON,		//Tipo de Estructura
	48,								//Posición en X
	5,								//Posición en Y
	4,								//Número de cadena de texto asociada
	TEXTO_57_CHICO,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,		//Código de color de fondo por defecto

	//OBJETO 6 --> SPINEDIT "Fuerza de Tara:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	66,								//Posición en X
	40,								//Posición en Y
	13,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	NO_EDITABLE,			//Código para determinar si el SpinEdit es o no Editable
	4,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	0,								//Low Byte (LB) del valor mínimo del SpinEdit			-> valor inicial 0
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	0x27,								//Low Byte (LB) del valor máximo del SpinEdit			-> valor final 9999
	0x0F,								//High Byte (HB) del valor máximo del SpinEdit

	//OBJETO 7 --> SPINEDIT "Fuerza Actual"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	66,								//Posición en X
	25,								//Posición en Y
	14,								//Índice del valor propio asociado en el vector de valores propios de los SpinEdits
	TEXTO_57_CHICO,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	NO_EDITABLE,			//Código para determinar si el SpinEdit es o no Editable
	4,								//Cantidad de cifras del SpinEdit
	1,								//Tamaño del incremento del SpinEdit
	0,								//Low Byte (LB) del valor mínimo del SpinEdit			-> valor inicial 0
	0,								//High Byte (HB) del valor mínimo del SpinEdit
	0x27,								//Low Byte (LB) del valor máximo del SpinEdit			-> valor final 9999
	0x0F								//High Byte (HB) del valor máximo del SpinEdit
};

//1 NULL indica final de cadena - 2 NULLs indican final de los textos del formulario
const char textoTarar[] =		"TARAR\0" //Cadena 0
														"Fuerza de Tara:\0" //Cadena 1
														"Fuerza Actual:\0" //Cadena 2
														"[Kgf]\0" //Cadena 3
														"Tarar\0"; //Cadena 4


const char datosParametros[] = {
	//OBJETO 0 --> LABEL "PARAMETROS"
	STRUCT_LABEL,			//Tipo de Estructura
	32,								//Posición en X
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
	5,								//Posición en X
	18,								//Posición en Y
	4,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 5 --> LABEL "[cm]"
	STRUCT_LABEL,			//Tipo de Estructura
	107,								//Posición en X
	18,								//Posición en Y
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
	86,								//Posición en X
	18,								//Posición en Y
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
	34,								//Posición en Y
	2,								//Número de cadena de texto asociada
	TEXTO_35,	//Tamaño del texto asociado
	COLOR_NO_NEGADO,			//Código de color de fondo por defecto

	//OBJETO 3 --> BUTTON "Guardar"
	STRUCT_BUTTON,		//Tipo de Estructura
	48,								//Posición en X
	5,								//Posición en Y
	3,								//Número de cadena de texto asociada
	TEXTO_35,		//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto

	//OBJETO 4 --> PROGBAR "LUZ DE FONDO:"
	STRUCT_PROG_BAR,	//Tipo de Estructura
	65,								//Posición en X
	44,								//Posición en Y
	0,								//Índice del valor propio asociado en el vector de valores propios de las ProgBars
	HORIZONTAL,				//Código de orientación de la ProgBar
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	54,								//Longitud en píxeles de la ProgBar
	3, 								//Espesor en píxeles de la barra central de la ProgBar
	//16,								//Cantidad de segmentos en que se divide la ProgBar

	//OBJETO 5 --> PROGBAR "CONTRASTE:"
	STRUCT_PROG_BAR,	//Tipo de Estructura
	53,								//Posición en X
	33,								//Posición en Y
	1,								//Índice del valor propio asociado en el vector de valores propios de las ProgBars
	HORIZONTAL,				//Código de orientación de la ProgBar
	COLOR_NO_NEGADO,		//Código de color de fondo por defecto
	66,								//Longitud en píxeles de la ProgBar
	3, 								//Espesor en píxeles de la barra central de la ProgBar

	//OBJETO 6 --> CHECKBOX "TIEMPO LUZ FONDO:"
	STRUCT_CHECK_BOX,	//Tipo de Estructura
	5,								//Posición en X
	21,								//Posición en Y
	4,								//Número de cadena de texto asociada
	TEXTO_35,					//Tamaño del texto asociado
	COLOR_NO_NEGADO,	//Código de color de fondo por defecto
	EDITABLE,					//Código para determinar si el CheckBox es o no Editable

	//OBJETO 7 --> SPINEDIT "TIEMPO LUZ FONDO:"
	STRUCT_SPIN_EDIT,	//Tipo de Estructura
	90,								//Posición en X
	22,								//Posición en Y
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
	105,							//Posición en X
	22,								//Posición en Y
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


//---------- TABLA DE INDICES DE VALORES PROPIOS ----------
//vPSpinEdits[CANT_SPIN_EDIT];
	//IndValProp = 0 --> OBJETO 13 --> SPINEDIT "G de Param:"	--> formMediciones
	//IndValProp = 1 --> OBJETO 14 --> SPINEDIT "Horas"	--> formMediciones
	//IndValProp = 2 --> OBJETO 15 --> SPINEDIT "Minutos"	--> formMediciones
	//IndValProp = 3 --> OBJETO 16 --> SPINEDIT "Segundos"	--> formMediciones
	//IndValProp = 4 --> OBJETO 17 --> SPINEDIT "Dur: min"	--> formMediciones
	//IndValProp = 5 --> OBJETO 18 --> SPINEDIT "Fuerza:"	--> formMediciones
	//IndValProp = 6 --> OBJETO 19 --> SPINEDIT "Efi:"	--> formMediciones
	//IndValProp = 7 --> OBJETO 20 --> SPINEDIT "Val T:"	--> formMediciones
	//IndValProp = 8 --> OBJETO 21 --> SPINEDIT "Val M:"	--> formMediciones

	//IndValProp = 9 --> OBJETO 8 --> SPINEDIT "GRUPO DE PARAMETROS:"	--> formParametros
	//IndValProp = 10 --> OBJETO 9 --> SPINEDIT "Diametro Traccion:"	--> formParametros
	//IndValProp = 11 --> OBJETO 10 --> SPINEDIT "Diametro Maquinaria:"	--> formParametros

	//IndValProp = 12 --> OBJETO 7 --> SPINEDIT "TIEMPO LUZ FONDO:"	--> formConfig

	//IndValProp = 13 --> OBJETO 7 --> SPINEDIT "Fuerza de Tara:"	--> formTarar
	//IndValProp = 14 --> OBJETO 8 --> SPINEDIT "Fuerza Actual"	--> formTarar

//vPProgBar[CANT_PROGBAR];
	//IndValProp = 0 --> OBJETO 4 --> PROGBAR "LUZ DE FONDO:" --> formConfig
	//IndValProp = 1 --> OBJETO 5 --> PROGBAR "CONTRASTE:" --> formConfig
//---------- FIN TABLA DE INDICES DE VALORES PROPIOS ----------

//FUNCIONES
/*Función InicInterfaz------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que inicializa la Interfaz
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void InicInterfaz(void)
{
  unsigned char iII; // variable del "for"
  unsigned char iII2;	//variable del "for"

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

	//PANTALLA TARAR
  formTarar.cantObjGraf = CANT_OBJ_FORM_TARAR;
  formTarar.cantCadenas = 5;
  formTarar.ptrObjetos = &objetosTarar[0];
  formTarar.ptrDatos =	&datosTarar[0];
  formTarar.ptrCadenas =	&textoTarar[0];

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

/*Función CargarPantalla------------------------------------------------------------------------------------------------------------------------
Descripción: función que setea el "vector de pantalla" según la pantalla seleccionada
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void CargarPantalla(void)
{
  switch (pantallaActual)
  {
    case PANTALLA_PRESENTA:
      ptrForm = &formPresenta;
    break;
    case PANTALLA_INICIO:
      ptrForm = &formInicio;
    break;
    case PANTALLA_MEDICIONES:
      ptrForm = &formMediciones;
    break;
		case PANTALLA_TARAR:
      ptrForm = &formTarar;
    break;
    case PANTALLA_PARAMETROS:
      ptrForm = &formParametros;
    break;
    case PANTALLA_CONFIG:
      ptrForm = &formConfig;
    break;
  }
}	//Fin CargarPantalla()

/*Función ExtrasDePantalla------------------------------------------------------------------------------------------------------------------------
Descripción: función que dibuja líneas, rellenos, etc. que no pertenecen a los objetos de interfaz comunes y setea el nuevo foco 
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ExtrasDePantalla(void)
{
  GLCD_Rectangulo(0, 0, 128, 64, NEGRO); //Marco de las pantallas
  if (pantallaActual != PANTALLA_PRESENTA)	//NO dibujamos el relleno de título para la pantalla de presentación
    GLCD_Relleno(1, 55, 126, 8, NEGRO); //fondo para el título

  switch (pantallaActual)
  {
    case PANTALLA_PRESENTA:
      Contador1ms = 0; //reinicia el contador del tiempo de espera
    break; //Fin PANTALLA_PRESENTA

    case PANTALLA_CONFIG:
      //Dibujamos las flechas al lado de las ProgBars de LUZ DE FONDO y CONTRASTE
      GLCD_Relleno(	61, 45, 5, 7, !COLOR_FONDO_DEF);
      GLCD_Relleno(	118, 45, 5, 7, !COLOR_FONDO_DEF);
      GLCD_Relleno(	49, 36, 5, 7, !COLOR_FONDO_DEF);
      GLCD_Relleno(	118, 36, 5, 7, !COLOR_FONDO_DEF);
      //Flechas hacia la izquierda
      GLCD_Punto(	62, 48, COLOR_FONDO_DEF);
      GLCD_Linea(	63, 47, 63, 49, COLOR_FONDO_DEF);
      GLCD_Linea(	64, 46, 64, 50, COLOR_FONDO_DEF);
      GLCD_Punto(	50, 39, COLOR_FONDO_DEF);
      GLCD_Linea(	51, 38, 51, 40, COLOR_FONDO_DEF);
      GLCD_Linea(	52, 37, 52, 41, COLOR_FONDO_DEF);
      //Flechas hacia la derecha
      GLCD_Linea(	119, 46, 119, 50, COLOR_FONDO_DEF);
      GLCD_Linea(	120, 47, 120, 49, COLOR_FONDO_DEF);
      GLCD_Punto(	121, 48, COLOR_FONDO_DEF);
      GLCD_Linea(	119, 37, 119, 41, COLOR_FONDO_DEF);
      GLCD_Linea(	120, 38, 120, 40, COLOR_FONDO_DEF);
      GLCD_Punto(	121, 39, COLOR_FONDO_DEF);
    break; //Fin PANTALLA_CONFIG

    case PANTALLA_MEDICIONES:
      //GLCD_Linea(1, 37, 127, 37, NEGRO); //Linea divisora entre lo deseado y lo real
      GLCD_Relleno(	1, 14, 126, 23, !COLOR_FONDO_DEF);

      GLCD_Punto(29, 43, NEGRO);	//Punto superior de los dos puntos de la edición horas:minutos
      GLCD_Punto(29, 41, NEGRO);	//Punto inferior de los dos puntos de la edición horas:minutos
      GLCD_Punto(41, 43, NEGRO);	//Punto superior de los dos puntos de la edición minutos:segundos
      GLCD_Punto(41, 41, NEGRO);	//Punto inferior de los dos puntos de la edición minutos:segundos

      GLCD_Punto(85, 26, BLANCO);	//Punto decimal de la velocidad VT
      GLCD_Punto(91, 15, BLANCO);	//Punto decimal de la velocidad VNT
      //////////////////////////////

      tiempo.hs = 0;
      tiempo.min = 0;
      tiempo.seg = 0;

      vPSpinEdits[11].valor.word = adqui.numMedActual;

      //sd.bGuardarDatos = 0;
      //pot.bHabPotencia = 0;
      //PIN_SALIDA_POTENCIA	= 0;
      //////////////////////////////
    break; //Fin PANTALLA_ENSAYO_LIBRE

    case PANTALLA_PARAMETROS:
      GLCD_Linea(	0, 45, 127, 45, !COLOR_FONDO_DEF);
    break; //Fin PANTALLA_PROGRAMAS
  }
}//Fin ExtrasDePantalla()

/*Función SetFoco------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que setea el foco asignándolo al Objeto que tiene como índice de foco el valor pasado como argumento 
Entrada: 
		indFoco: entero que representa el índice de foco que se quiere asignar
Salida: 
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetFoco(void)
{
	unsigned char iSF; //variable para el for
	
	//limpio el vector de focos
	for (iSF=0; iSF < CANT_FOCO; iSF++)
		ptrFoco[iSF] = 0;
	
	//se identifica la pantalla actual y se asigna los objetos al vector void ptrFoco[]
	switch (pantallaActual)
	{
		//se inicializa, como uno desee, el vector ptrFoco, en cada pantalla, con los objetos de formInicio
		//que soportan foco; donde ptrFoco[0] apunta a NULL = 0 para indicar que nadie tiene el foco.
		case PANTALLA_PRESENTA:
			ptrFoco[0] = FOCO_NINGUNO;
			break;
		case PANTALLA_INICIO:
			ptrFoco[0] = &objetosInicio[1];	//OBJETO 1 --> BUTTON "Mediciones"
			ptrFoco[1] = &objetosInicio[2];	//OBJETO 2 --> BUTTON "Tarar"
			ptrFoco[2] = &objetosInicio[3];	//OBJETO 3 --> BUTTON "Parametros"
			ptrFoco[3] = &objetosInicio[4];	//OBJETO 4 --> BUTTON "Configuracion"
			break;
		case PANTALLA_MEDICIONES:			
			ptrFoco[0] = &objetosMediciones[13];	//OBJETO 13 --> SPINEDIT "G de Param:"
			ptrFoco[1] = &objetosMediciones[25];	//OBJETO 22 --> SPINEDIT "Medicion"
			ptrFoco[2] = &objetosMediciones[22];	//OBJETO 23 --> CHECKBOX "Dur:"
			ptrFoco[3] = &objetosMediciones[17];	//OBJETO 17 --> SPINEDIT "Dur: min"
			ptrFoco[4] = &objetosMediciones[11];	//OBJETO 11 --> BUTTON "Comenzar"
			ptrFoco[5] = &objetosMediciones[12];	//OBJETO 12 --> BUTTON "Finalizar"
			break;
		case PANTALLA_TARAR:
			ptrFoco[0] = &objetosTarar[5];	//OBJETO 6 --> BUTTON "Tarar"
			break;
		case PANTALLA_PARAMETROS:			
			ptrFoco[0] = &objetosParametros[8];	//OBJETO 8 --> SPINEDIT "GRUPO DE PARAMETROS:"
			ptrFoco[1] = &objetosParametros[9];	//OBJETO 9 --> SPINEDIT "Diametro Traccion:"
			ptrFoco[2] = &objetosParametros[10];	//OBJETO 10 --> SPINEDIT "Diametro no Traccion:"
			ptrFoco[3] = &objetosParametros[6];	//OBJETO 6 --> BUTTON "Guardar"
			ptrFoco[4] = &objetosParametros[7];	//OBJETO 7 --> BUTTON "Resetear Grupo"
			break;
		case PANTALLA_CONFIG:
			ptrFoco[0] = &objetosConfig[4];	//OBJETO 4 --> PROGBAR "LUZ DE FONDO:"
			ptrFoco[1] = &objetosConfig[5];	//OBJETO 5 --> PROGBAR "CONTRASTE:"
			ptrFoco[2] = &objetosConfig[6];	//OBJETO 6 --> CHECKBOX "TIEMPO LUZ FONDO:"
			ptrFoco[3] = &objetosConfig[7];	//OBJETO 7 --> SPINEDIT "TIEMPO LUZ FONDO:"
			ptrFoco[4] = &objetosConfig[3];	//OBJETO 3 --> BUTTON "Guardar"
			break;
	}
	
	indFoco = ptrForm->saveFoco; //Seteamos el Foco de la pantalla que corresponda
	AsignarFoco();
}//end SetFoco


