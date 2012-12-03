
#include <configinterfaz.h>
#include <interfaz.h>

struct Form formPresenta;
struct Form formInicio;
struct Form formEnsayo;
struct Form formComposite;
struct Form formEnsayoLibre;
struct Form formProgramas;
struct Form formConfig;
struct Form formConfigEnsayo;
struct Form formEjecEnsayo;

//VECTORES DE OBJETOS
struct Form *ptrForm; //puntero a un vector de Form
struct Cargador c;

//Arreglos de estructuras con los valores propios
struct ValPropSpinEdit vPSpinEdits[CANT_SPIN_EDIT];
struct ValPropValEdit vPValEdits[CANT_VAL_EDIT];
struct ValPropComboBox vPComboBoxes[CANT_COMBOBOX];
struct ValPropProgBar vPProgBars[CANT_PROGBAR];

//Arreglos de los ValEdits
unsigned char valEditCompositeDiametro[DIG_VAL_EDIT_COMP_DIAM];
unsigned char valEditCompositeEspesor[DIG_VAL_EDIT_COMP_ESP];

unsigned char indFoco;  //Entero con el índice del objeto de la interfaz que tiene el foco
unsigned char indFocoActual;	//Guarda el foco del objeto actual antes de ejecutar su comportamiento predefinido. 
															//Esta variable sirve para redefinir el comportamiento por defecto del foco
volatile unsigned char contTitileo;  //Contador que sirve para hacer titilar el cursor 
unsigned char	pantallaActual;  //Número de pantalla en la que se encuentra el usuario

union Estado *ptrFoco[CANT_FOCO];
union Estado objetosPresenta[CANT_OBJ_FORM_PRESENTA];
union Estado objetosInicio[CANT_OBJ_FORM_INICIO];
union Estado objetosEnsayo[CANT_OBJ_FORM_ENSAYO];
union Estado objetosComposite[CANT_OBJ_FORM_COMPOSITE];
union Estado objetosEnsayoLibre[CANT_OBJ_FORM_ENSAYO_LIBRE];
union Estado objetosProgramas[CANT_OBJ_FORM_PROGRAMAS];
union Estado objetosConfig[CANT_OBJ_FORM_CONFIG];
union Estado objetosConfigEnsayo[CANT_OBJ_FORM_CONFIG_ENSAYO];
union Estado objetosEjecEnsayo[CANT_OBJ_FORM_EJEC_ENSAYO];


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
		case PANTALLA_ENSAYO:
			ptrForm = &formEnsayo;
			break;
		case PANTALLA_COMPOSITE:
			ptrForm = &formComposite;
			break;
		case PANTALLA_ENSAYO_LIBRE:
			ptrForm = &formEnsayoLibre;
			break;
		case PANTALLA_PROGRAMAS:
			ptrForm = &formProgramas;
			break;
		case PANTALLA_CONFIG:
			ptrForm = &formConfig;
			break;
		case PANTALLA_CONFIG_ENSAYO:
			ptrForm = &formConfigEnsayo;
			break;
		case PANTALLA_EJEC_ENSAYO:
			ptrForm = &formEjecEnsayo;
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
	if (pantallaActual != PANTALLA_PRESENTA && pantallaActual != PANTALLA_EJEC_ENSAYO)	//NO dibujamos el relleno de título para la pantalla de presentación
		GLCD_Relleno(1, 55, 126, 8, NEGRO); //fondo para el título

	switch (pantallaActual)
	{
		case PANTALLA_PRESENTA:
			Contador1ms = 0; //reinicia el contador del tiempo de espera
			break; //Fin PANTALLA_PRESENTA

		case PANTALLA_CONFIG:						
			#ifdef	PROG_BAR
			//Actualizamos los ProgBars según los valores de Luz de Fondo y Contraste
			vPProgBars[0].progPorcent = (unsigned char) ((float) config.luzFondo * 100 / (float) 15);
			vPProgBars[1].progPorcent = (unsigned char) ((float) config.contraste * 100 / (float) 15);
			#endif
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
			
		case PANTALLA_ENSAYO_LIBRE:
			GLCD_Linea(1, 37, 127, 37, NEGRO); //Linea divisora entre lo deseado y lo real
			
			GLCD_Punto(103, 33, NEGRO);	//Punto superior de los dos puntos de la edición horas:minutos
			GLCD_Punto(103, 31, NEGRO);	//Punto inferior de los dos puntos de la edición horas:minutos
			GLCD_Punto(115, 33, NEGRO);	//Punto superior de los dos puntos de la edición minutos:segundos
			GLCD_Punto(115, 31, NEGRO);	//Punto inferior de los dos puntos de la edición minutos:segundos

			//////////////////////////////
      formEnsayoLibre.ptrObjetos[19].bChequeado = 1;
      //vPSpinEdits[1].valor.word = conduc.iComposite;	//Composite
      vPSpinEdits[2].valor.word = 60;	//Temperatura Final
      vPSpinEdits[3].valor.word = 60;	//Duración
			tiempo.hs = 0;
			tiempo.min = 0;
			tiempo.seg = 0;
			//sd.bGuardarDatos = 0;
			//pot.bHabPotencia = 0;
			//PIN_SALIDA_POTENCIA	= 0;
			//////////////////////////////	
			break; //Fin PANTALLA_ENSAYO_LIBRE
			
		case PANTALLA_PROGRAMAS:
			GLCD_Linea(	0, 45, 127, 45, !COLOR_FONDO_DEF);
			GLCD_Linea(	65, 46, 65, 55, !COLOR_FONDO_DEF);
			break; //Fin PANTALLA_PROGRAMAS

		case PANTALLA_EJEC_ENSAYO:
			GLCD_Relleno(1, 57, 126, 7, !COLOR_FONDO_DEF); //Barra de arriba
			GLCD_Relleno(1, 0, 126, 7, !COLOR_FONDO_DEF); //Barra de abajo
			//Dibujamos líneas de separación entre datos
			GLCD_Linea(	15, 57, 15, 63, COLOR_FONDO_DEF);
			GLCD_Linea(	35, 57, 35, 63, COLOR_FONDO_DEF);
			GLCD_Linea(	51, 57, 51, 63, COLOR_FONDO_DEF);
			GLCD_Linea(	93, 57, 93, 63, COLOR_FONDO_DEF);
			GLCD_Linea(	27, 0, 27, 7, COLOR_FONDO_DEF);
			GLCD_Linea(	65, 0, 65, 7, COLOR_FONDO_DEF);
			//Imprimimos el sistema de coordenadas
			GLCD_Linea(	15, 8, 15, 55, !COLOR_FONDO_DEF); //Eje Y
			//Dibujamos la flecha del eje Y
			GLCD_Punto(14, 54, !COLOR_FONDO_DEF);
			GLCD_Punto(16, 54, !COLOR_FONDO_DEF);
			GLCD_Punto(13, 53, !COLOR_FONDO_DEF);
			GLCD_Punto(14, 53, !COLOR_FONDO_DEF);
			GLCD_Punto(16, 53, !COLOR_FONDO_DEF);
			GLCD_Punto(17, 53, !COLOR_FONDO_DEF);
			c.cadenaTexto[0] = 'C';
			c.cadenaTexto[1] = NULL;
			GLCD_String(8, 55, c.cadenaTexto, TEXTO_35, !COLOR_FONDO_DEF);	//"C"
			c.cadenaTexto[0] = '2';
			c.cadenaTexto[1] = '0';
			c.cadenaTexto[2] = '0';
			c.cadenaTexto[3] = NULL;
			GLCD_String(2, 48, c.cadenaTexto, TEXTO_35, !COLOR_FONDO_DEF);	//"200"
			c.cadenaTexto[0] = '1';
			c.cadenaTexto[1] = '5';
			c.cadenaTexto[2] = '0';
			c.cadenaTexto[3] = NULL;
			GLCD_String(2, 39, c.cadenaTexto, TEXTO_35, !COLOR_FONDO_DEF);	//"150"
			c.cadenaTexto[0] = '1';
			c.cadenaTexto[1] = '0';
			c.cadenaTexto[2] = '0';
			c.cadenaTexto[3] = NULL;
			GLCD_String(2, 30, c.cadenaTexto, TEXTO_35, !COLOR_FONDO_DEF);	//"100"
			c.cadenaTexto[0] = '5';
			c.cadenaTexto[1] = '0';
			c.cadenaTexto[2] = NULL;
			GLCD_String(6, 21, c.cadenaTexto, TEXTO_35, !COLOR_FONDO_DEF);	//"50"
			c.cadenaTexto[0] = '0';
			c.cadenaTexto[1] = NULL;
			GLCD_String(10, 12, c.cadenaTexto, TEXTO_35, !COLOR_FONDO_DEF);	//"0"

			//Imprimimos algunos textos extras
			/*c.cadenaTexto[0] = 'C';
			c.cadenaTexto[1] = NULL;
			GLCD_String(60, 5, cadenaAux, TEXTO_35, COLOR_FONDO_DEF);	//"C"
			c.cadenaTexto[0] = 'S';
			c.cadenaTexto[1] = '/';
			c.cadenaTexto[2] = 'm';
			c.cadenaTexto[3] = NULL;
			GLCD_String(111, 5, cadenaAux, TEXTO_35, COLOR_FONDO_DEF);	//"C"*/

			GLCD_Punto(14, 44, !COLOR_FONDO_DEF);	//Marca en el eje Y para "200"
			GLCD_Punto(14, 35, !COLOR_FONDO_DEF);	//Marca en el eje Y para "150"
			GLCD_Punto(14, 26, !COLOR_FONDO_DEF);	//Marca en el eje Y para "100"
			GLCD_Punto(14, 17, !COLOR_FONDO_DEF);	//Marca en el eje Y para "50"
			GLCD_Punto(14, 8, !COLOR_FONDO_DEF);	//Marca en el eje Y para "0"
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
			ptrFoco[0] = &objetosInicio[1];	//OBJETO 1 --> BUTTON "Ensayo"
			ptrFoco[1] = &objetosInicio[2];	//OBJETO 2 --> BUTTON "Composites"
			ptrFoco[2] = &objetosInicio[3];	//OBJETO 3 --> BUTTON "Programas"
			ptrFoco[3] = &objetosInicio[4];	//OBJETO 4 --> BUTTON "Configuracion"
			break;
		case PANTALLA_ENSAYO:
			ptrFoco[0] = &objetosEnsayo[1];	//OBJETO 1 --> BUTTON "Ensayo Programado"
			ptrFoco[1] = &objetosEnsayo[2];	//OBJETO 2 --> BUTTON "Ensayo Libre"
			break;
		case PANTALLA_COMPOSITE:	
			ptrFoco[0] = &objetosComposite[2];	//OBJETO 2 --> SPINEDIT "Tipo:"
			ptrFoco[1] = &objetosComposite[4];	//OBJETO 4 --> VALEDIT "Diametro:"
			ptrFoco[2] = &objetosComposite[7];	//OBJETO 7 --> VALEDIT "Espesor:"
			ptrFoco[3] = &objetosComposite[9];	//OBJETO 9 --> LABEL "Guardar"
			break;
		case PANTALLA_ENSAYO_LIBRE:			
			ptrFoco[0] = &objetosEnsayoLibre[13];	//OBJETO 13 --> SPINEDIT "Composite:"
			ptrFoco[1] = &objetosEnsayoLibre[19];	//OBJETO 19 --> CHECKBOX "Guardar en SD"
			ptrFoco[2] = &objetosEnsayoLibre[14];	//OBJETO 14 --> SPINEDIT "T Final:"
			ptrFoco[3] = &objetosEnsayoLibre[20];	//OBJETO 20 --> CHECKBOX "Dur: min"
			ptrFoco[4] = &objetosEnsayoLibre[15];	//OBJETO 15 --> SPINEDIT "Dur: min"
			//ptrFoco[5] = &objetosEnsayoLibre[16];	//OBJETO 16 --> SPINEDIT "Horas"
			//ptrFoco[6] = &objetosEnsayoLibre[17];	//OBJETO 17 --> SPINEDIT "Minutos"
			//ptrFoco[7] = &objetosEnsayoLibre[18];	//OBJETO 18 --> SPINEDIT "Segundos"
			ptrFoco[5] = &objetosEnsayoLibre[11];	//OBJETO 11 --> BUTTON "Comenzar"
			ptrFoco[6] = &objetosEnsayoLibre[12];	//OBJETO 12 --> BUTTON "Finalizar"

			break;
		case PANTALLA_PROGRAMAS:			
			ptrFoco[0] = &objetosProgramas[10];	//OBJETO 10 --> SPINEDIT "PROGRAMA:"
			ptrFoco[1] = &objetosProgramas[11];	//OBJETO 11 --> SPINEDIT "SEGMENTO:"
			ptrFoco[2] = &objetosProgramas[12];	//OBJETO 12 --> SPINEDIT "Temp:"
			ptrFoco[3] = &objetosProgramas[15];	//OBJETO 15 --> COMBOBOX "Tipo:"
			ptrFoco[4] = &objetosProgramas[14];	//OBJETO 14 --> SPINEDIT "Dif:"
			ptrFoco[5] = &objetosProgramas[13];	//OBJETO 13 --> SPINEDIT "Duracion:"
			ptrFoco[6] = &objetosProgramas[7];	//OBJETO 7 --> BUTTON "Guardar"
			ptrFoco[7] = &objetosProgramas[8];	//OBJETO 8 --> BUTTON "Res S"
			ptrFoco[8] = &objetosProgramas[9];	//OBJETO 9 --> BUTTON "Res P"
			break;
		case PANTALLA_CONFIG:
			ptrFoco[0] = &objetosConfig[4];	//OBJETO 4 --> PROGBAR "LUZ DE FONDO:"
			ptrFoco[1] = &objetosConfig[5];	//OBJETO 5 --> PROGBAR "CONTRASTE:"
			ptrFoco[2] = &objetosConfig[3];	//OBJETO 3 --> BUTTON "Guardar"
			break;
		case PANTALLA_CONFIG_ENSAYO:	
			ptrFoco[0] = &objetosConfigEnsayo[4];	//OBJETO 4 --> SPINEDIT "COMPOSITE:"
			ptrFoco[1] = &objetosConfigEnsayo[5];	//OBJETO 5 --> SPINEDIT "PROGRAMA A EJECUTAR:"
			ptrFoco[2] = &objetosConfigEnsayo[6];	//OBJETO 6 --> CHECKBOX "Guardar en SD"
			ptrFoco[3] = &objetosConfigEnsayo[7];	//OBJETO 7 --> CHECKBOX "Apagar al terminar"
			ptrFoco[4] = &objetosConfigEnsayo[3];	//OBJETO 3 --> BUTTON "Comenzar Ensayo"	
			break;
		case PANTALLA_EJEC_ENSAYO:	
			ptrFoco[0] = &objetosEjecEnsayo[8];	//OBJETO 8 --> SPINEDIT "P:"
			break;
	}
	
	indFoco = ptrForm->saveFoco; //Seteamos el Foco de la pantalla que corresponda
	AsignarFoco();
}//end SetFoco


