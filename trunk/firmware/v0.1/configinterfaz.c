
#include <configinterfaz.h>
#include <interfaz.h>

struct Form formPresenta;
struct Form formInicio;
struct Form formMediciones;
struct Form formParametros;
struct Form formConfig;

//VECTORES DE OBJETOS
struct Form *ptrForm; //puntero a un vector de Form
struct Cargador c;

//Arreglos de estructuras con los valores propios
struct ValPropSpinEdit vPSpinEdits[CANT_SPIN_EDIT];
struct ValPropProgBar vPProgBars[CANT_PROGBAR];

unsigned char indFoco;  //Entero con el índice del objeto de la interfaz que tiene el foco
unsigned char indFocoActual;	//Guarda el foco del objeto actual antes de ejecutar su comportamiento predefinido. 
															//Esta variable sirve para redefinir el comportamiento por defecto del foco
INT16U contTitileo;  //Contador que sirve para hacer titilar el cursor 
unsigned char	pantallaActual;  //Número de pantalla en la que se encuentra el usuario
union Estado *ptrFoco[CANT_FOCO];

union Estado objetosPresenta[CANT_OBJ_FORM_PRESENTA];
union Estado objetosInicio[CANT_OBJ_FORM_INICIO];
union Estado objetosMediciones[CANT_OBJ_FORM_MEDICIONES];
union Estado objetosParametros[CANT_OBJ_FORM_PARAMETROS];
union Estado objetosConfig[CANT_OBJ_FORM_CONFIG];


//VARIABLES DE SetFoco()
volatile unsigned char iSF; //variable para el for

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

			//////////////////////////////
      
			tiempo.hs = 0;
			tiempo.min = 0;
			tiempo.seg = 0;
			//sd.bGuardarDatos = 0;
			//pot.bHabPotencia = 0;
			//PIN_SALIDA_POTENCIA	= 0;
			//////////////////////////////	
			break; //Fin PANTALLA_ENSAYO_LIBRE
			
		case PANTALLA_PARAMETROS:
			GLCD_Linea(	0, 45, 127, 45, !COLOR_FONDO_DEF);
			break; //Fin PANTALLA_PROGRAMAS
	}
}	//Fin ExtrasDePantalla()

/*Función SetFoco------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que setea el foco asignándolo al Objeto que tiene como índice de foco el valor pasado como argumento 
Entrada: 
		indFoco: entero que representa el índice de foco que se quiere asignar
Salida: 
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetFoco(void)
{
	//unsigned char iSF; //variable para el for
	
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
			ptrFoco[1] = &objetosMediciones[22];	//OBJETO 22 --> CHECKBOX "Guardar en SD"
			ptrFoco[2] = &objetosMediciones[23];	//OBJETO 23 --> CHECKBOX "Dur:"
			ptrFoco[3] = &objetosMediciones[17];	//OBJETO 17 --> SPINEDIT "Dur: min"
			ptrFoco[4] = &objetosMediciones[11];	//OBJETO 11 --> BUTTON "Comenzar"
			ptrFoco[5] = &objetosMediciones[12];	//OBJETO 12 --> BUTTON "Finalizar"

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


