#ifndef OBJETOS_H
#define OBJETOS_H

#include	<stdint.h>
//#include	"globals.h"

#define	TAMANIO_CADENA_TEXTO	70
#define	TAMANIO_CADENA_DATOS	15
#define	TAMANIO_CADENA_AUX	2

//Estructura de tiempo
struct Tmp{
	unsigned int 	ms;		//Milisegundos
	unsigned char seg;	//Segundos
	unsigned char min;	//Minutos
	unsigned char hs;		//Horas
};

union Int16{
	unsigned char byte;
	unsigned int word;
	struct {
		unsigned char LB; //Lower Byte
		unsigned char HB; //High Byte
	};
};

union Estado{
	struct {
		unsigned	bVisible	: 1;		//Indica si el Objeto Gr�fico debe ser dibujado o no
		unsigned	bRedibujar	: 1;	//Indica si el Objeto Gr�fico debe ser redibujado completamente
		unsigned	bLimpiarFondo: 1;	//Indica si se debe limpiar el fondo del Objeto Gr�fico antes de dibujarlo
		unsigned	bEnFoco		: 1;		//Indica si el Objeto Gr�fico tiene actualmente el foco
		unsigned	bEditable	: 1;		//Indica si el Objeto Gr�fico se puede editar o no
		unsigned	bEditando	: 1;		//Indica si el Objeto Gr�fico est� siendo editado en este momento
		unsigned	bColorNeg	: 1;		//Indica si el Objeto Gr�fico debe dibujarse de un color negado
		unsigned	bChequeado	: 1;	//Usada en el CheckBox,  indica si el mismo  est� chequeado (1) o no (0) 
		unsigned char	indDatos;			//N�mero de �ndice del Objeto Gr�fico en la matriz de datos en ROM
	};
	unsigned char bandEstado;
};

//#include <configinterfaz.h>

//ESTRUCTURAS DE LOS OBJETOS GRAFICOS
struct Label{	
	//VARIABLES COMUNES
	union Estado estado;
	//VARIABLES PROPIAS
	
	//VARIABLES TEMPORALES
	//unsigned char cantCaracteres;		//Indica cuantos caracteres tiene la cadena asociada al Label
	//unsigned char cantPixeles;	//Indica cuantos pixeles tiene la cadena, sin espacios entre letras
	uint8_t	*ptrTexto;	//Puntero al texto que tiene que imprimir el label	
	//VARIABLES DE CONSTANTES
	//unsigned char tipoStruct;	//Tipo de estructura  del Objeto Gr�fico
	//unsigned char posX;			//Posici�n en X del Objeto Gr�fico
	//unsigned char posY; 		//Posici�n en Y del Objeto Gr�fico
	//unsigned char numCadena;		//N�mero de la cadena de texto asociada al objeto gr�fico
	unsigned char tamanioTexto; //Indica el multiplicador que tiene el tama�o del texto con el que se dibuja el Objeto Gr�fico
	unsigned bColorNeg : 1;	//Indica si el Label debe dibujarse de color negado	
};

struct Button{
	//VARIABLES COMUNES
	union Estado estado;
	//VARIABLES PROPIAS
	
	//VARIABLES TEMPORALES
	//unsigned char cantCaracteres;		//Indica cuantos caracteres tiene la cadena de texto asociada al Button
	//unsigned char cantPixeles;	//Indica cuantos pixeles tiene la cadena de texto asociada al Button, sin espacios entre letras
	//VARIABLES DE CONSTANTES
	//unsigned char tipoStruct;	//Tipo de estructura  del Objeto Gr�fico
	//unsigned char posX;			//Posici�n en X del Objeto Gr�fico
	//unsigned char posY; 		//Posici�n en Y del Objeto Gr�fico
	//unsigned char numCadena;		//N�mero de la cadena de texto asociada al objeto gr�fico
	unsigned char tamanioTexto; //Indica el multiplicador que tiene el tama�o del texto con el que se dibuja el Objeto Gr�fico
	//char texto[32];				//Cadena de caracteres que va a contener el texto del Objeto Gr�fico
	//unsigned char indLabel;		//Indice del Label asociado al Objeto Gr�fico
};

struct SpinEdit{
	//VARIABLES COMUNES
	union Estado estado;
	//VARIABLES PROPIAS
	union Int16 valor;	//Valor del SpinEdit
	union Int16 valorTemp; //Toma el valor temporal del SpinEdit hasta que se presione ACEPTAR - Valor que muestra el SpinEdit mientras est� siendo editado
	//VARIABLES TEMPORALES
	unsigned bDibujarNeg : 1;	//Bandera usada para dibujar negado o no el SpinEdit durante el titileo de la edici�n
	unsigned bNoRedibujar : 1; //Bandera usada en el efecto de edici�n
	//VARIABLES DE CONSTANTES
	//unsigned char tipoStruct;	//Tipo de estructura  del Objeto Gr�fico
	//unsigned char posX;			//Posici�n en X del Objeto Gr�fico
	//unsigned char posY; 		//Posici�n en Y del Objeto Gr�fico
	unsigned char tamanioTexto; //Indica el multiplicador que tiene el tama�o del texto con el que se dibuja el Objeto Gr�fico
	unsigned	bColorNeg	:	1;	//Indica si el SpinEdit debe dibujarse de color negado
	unsigned char indValProp;	//Indice del valor propio del SpinEdit en el Vector de valores propios
	unsigned char cifras;		//Indica la cantidad de cifras que se muestran del SpinEdit
	unsigned char incremento;		//Valor del incremento/decremento del SpinEdit
	union Int16 valMin;		//Valor m�nimo capaz de almacenar el SpinEdit en modo N�merico
	union Int16 valMax;		//Valor m�ximo capaz de almacenar el SpinEdit en modo N�merico
};


struct ValPropSpinEdit{	//Estructura/union con la/las variables propias del SpinEdit
	//VARIABLES PROPIAS 
	union Int16 valor;	//Valor del SpinEdit
};

struct ValEdit{
	//VARIABLES COMUNES
	union Estado estado;
	//VARIABLES PROPIAS
	unsigned char	*ptrDigitos;	//Puntero a la Cadena de d�gitos que contiene el valor del ValEdit
	//VARIABLES TEMPORALES
	unsigned bSignoPos : 1;		//Indica si el signo del valor del ValEdit es positivo cuando est� en modo num�rico
	unsigned bCursorDib : 1;	//Indica si el cursor esta dibujado debajo del caracter que se esta editando
	unsigned bEntrandoEdicion : 1; //Bandera usada en el efecto de edici�n
	unsigned char offset; 		//offset que mueve a la izquierda el valor que se muestra del ValEdit
	unsigned char indFocoDigit;	//Indica cual  de los elementos del ValEdit tiene el foco (esta siendo editado) dentro de la  m�scara de edici�n
	unsigned char indActualiz;	//Indica cual de los  elementos debe ser actualizado en pantalla (redibujado) - 255 indica que no es necesario actualizar
	//VARIABLES DE CONSTANTES
	//unsigned char tipoStruct;	//Tipo de estructura  del Objeto Gr�fico
	//unsigned char posX;			//Posici�n en X del Objeto Gr�fico
	//unsigned char posY; 		//Posici�n en Y del Objeto Gr�fico
	unsigned char tamanioTexto;	//Indica el multiplicador que tiene el tama�o del texto
	unsigned bHabSigno : 1;		//Indica si el ValEdit tiene o no signo
	unsigned char cifras;		//Indica cuantas cifras tiene la cadena del ValEdit
	unsigned char cifrasVis;	//Indica cuantas cifras se muestran en el ValEdit
	union Int16 valMinSigned;	//Valor m�nimo capaz de almacenar el ValEdit en modo N�merico
	union Int16 valMaxSigned;	//Valor m�ximo capaz de almacenar el ValEdit en modo N�merico
};

struct ValPropValEdit{	//Estructura/union con la/las variables propias del ValEdit
	//VARIABLES PROPIAS
	unsigned char	*ptrDigitos;	//Puntero a la Cadena de d�gitos que contiene el valor del ValEdit
};

struct CheckBox{
	//VARIABLES COMUNES
	union Estado estado;
	//VARIABLES PROPIAS
	
	//VARIABLES TEMPORALES
	//unsigned char cantCaracteres;		//Indica cuantos caracteres tiene la cadena de texto asociada al CheckBox
	//unsigned char cantPixeles;	//Indica cuantos pixeles tiene la cadena de texto asociada al CheckBox, sin espacios entre letras
	//VARIABLES DE CONSTANTES
	//unsigned char tipoStruct;	//Tipo de estructura  del Objeto Gr�fico
	//unsigned char posX;			//Posici�n en X del Objeto Gr�fico
	//unsigned char posY; 		//Posici�n en Y del Objeto Gr�fico
	//unsigned char numCadena;		//N�mero de la cadena de texto asociada al objeto gr�fico
	unsigned char tamanioTexto;	//Indica el multiplicador que tiene el tama�o del texto
	//unsigned char indLabel;		//Indice del Label asociado al Objeto Gr�fico
};

struct ComboBox{
	//VARIABLES COMUNES
	union Estado estado;
	//VARIABLES PROPIAS
	unsigned char opcionSelec;	//Indica c�al opci�n ha sido seleccionada
	//VARIABLES TEMPORALES
	unsigned bDibujarTodoDeNuevo : 1;	//Indica si en el modo edici�n es necesario redibujar las felchas, barra, etc
	unsigned char cantOpciones;	//Indica la cantidad de opciones que se muestran en el ComboBox
	unsigned char opcionTemp;	//Indica cual opci�n esta seleccionada temporalmente durante el proceso de edici�n
	unsigned char anchoMayorOp;	//Cantidad de p�xeles de ancho de la cadena de opci�n m�s larga del ComboBox
	//VARIABLES DE CONSTANTES
	//unsigned char tipoStruct;	//Tipo de estructura  del Objeto Gr�fico
	//unsigned char posX;			//Posici�n en X del Objeto Gr�fico
	//unsigned char posY; 		//Posici�n en Y del Objeto Gr�fico
	//unsigned char numCadena;		//N�mero de la cadena de texto asociada al objeto gr�fico
	unsigned char tamanioTexto;	//Indica el multiplicador que tiene el tama�o del texto
	//rom const char *ptrCadena;		//Puntero a la matriz de cadena de caracteres que muestra el ComboBox
};

struct ValPropComboBox{	//Estructura/union con la/las variables propias del ComboBox
	//VARIABLES PROPIAS
	unsigned char opcionSelec;	//Indica c�al opci�n ha sido seleccionada
};

struct ProgBar{
	//VARIABLES COMUNES
	union Estado estado;
	//VARIABLES PROPIAS
	unsigned bRedibujarTodo : 1;//Indica si es necesario redibujar todo la barra
	unsigned char progPorcent;	//Progreso porcentual de la barra (0-100)
	unsigned char porcentAnterior;//Almacena el porcentaje al que se encontraba la barra antes de ser modificada
	unsigned char pixAnterior;		//Almacena la cantidad de p�xeles que hab�a con el progPorcent anterior
	//VARIABLES TEMPORALES

	//VARIABLES DE CONSTANTES
	//unsigned char tipoStruct;	//Tipo de estructura  del Objeto Gr�fico
	//unsigned char posX;			//Posici�n en X del Objeto Gr�fico
	//unsigned char posY; 		//Posici�n en Y del Objeto Gr�fico
	unsigned bColorNeg : 1;		//Indica si la Barra  de Progreso debe  dibujarse de color negado
	unsigned bVertical : 1;		//Indica si la barra es vertical (1) u horizontal (0)
	float pixPorUnidad;			//Cantidad de p�xeles por unidad (pixPorUnidad = 100/(longitud - 4)
	unsigned char longitud;		//Longitud en p�xeles de la barra
	unsigned char espesor;		//Espesor en p�xeles de la barra
	//unsigned char cantSegmentos;	//Cantidad de segmentos en que se divide la ProgBar
	//float	incremento;							//Incremento de la ProgBar por cada pulsaci�n derecha o izquierda
};

struct ValPropProgBar{	//Estructura/union con la/las variables propias de la ProgBar
	//VARIABLES PROPIAS
	unsigned bRedibujarTodo : 1;//Indica si es necesario redibujar todo la barra
	unsigned progPorcent : 7;	//Progreso porcentual de la barra (0-100)
	unsigned char porcentAnterior;//Almacena el porcentaje al que se encontraba la barra antes de ser modificada
	unsigned char pixAnterior;		//Almacena la cantidad de p�xeles que hab�a con el progPorcent anterior
};

struct MsgBox{
	unsigned bFinCadena	:1;	//Indica que se ha llegado al final de la cadena
	unsigned bRecuadroDibujado :1;			//Indica si es necesario limpiar el �rea donde se va a imprimir el mensaje
	unsigned bCalculandoLineas:1;	//Indica si la pasada actual del bucle es solo para calcular las l�neas
	unsigned bImprimiendo :1;	//Indica si en la pasada actual  del bucle de deben imprimir las cadenas
	unsigned bCambioEspacioNull :1; //Bandera que indica si se ha reemplazado un espacio por un NULL
	unsigned bAgregarOtraPalabra :1;	//Indica si se debe probar agregando  otra palabra a la l�nea actual
	unsigned bRetrocederHastaEspacio :1;	//Indica si se debe retroceder hasta encontrar un espacio
	unsigned bCerrarMensaje :1;	//Indica cuando el mensaje ha terminado y debe actualizarse el formulario de fondo	

	struct Tmp tiempo;	//Estructura para temporizar los segundos durante los cuales se muestra el mensaje, a menos que se presione una tecla	
	uint8_t segundos;	//Cantidad de segundos durante los cuales me muestra el mensaje

	uint8_t tipoMensaje; //Indica si el mensaje es por tiempo, solo con aceptar, con aceptar y cancelar, etc...
	uint8_t	altoCaja;	//Alto en p�xeles de la caja que  contiene el mensaje
	uint8_t anchoCaja;	//Ancho en p�xeles de la caja que  contiene el mensaje
	uint8_t	anchoMaxCadena;	//Cadena de texto con el ancho en p�xeles m�ximo
	uint8_t	cantLineas;	//Cantidad de l�neas que tiene el mensaje
	uint8_t cantPalabras;	//Cantidad de palabras que se van agregando a la cadena
	//uint8_t comienzoNuevaCadena;	//Comienzo de la cadena de texto a imprimir en el MsgBox
	//uint8_t offsetTotal;	//Offset desde el inicio del texto del mensaje
	uint8_t	pixelesNuevaCadena;	//Variable para calcular los p�xeles de la nueva cadena que se est� probando
	uint8_t offsetBordeCaja;		//Offset de la l�nea de texto desde el borde de la caja 

	//unsigned char posX;			//Posici�n en X del Objeto Gr�fico
	//unsigned char posY; 		//Posici�n en Y del Objeto Gr�fico
};

struct Form{	//Datos Propios del Formulario
	union Estado estado;
	unsigned char saveFoco;	//Variable utilizada para salvar el foco al salir del Form
	
	union Estado *ptrObjetos;	//Puntero al arreglo de Estados de los Objetos Gr�ficos del Formulario
	unsigned char	cantObjGraf;	//Cantidad de Objetos Gr�ficos del Formulario
	unsigned char cantCadenas;	//Cantidad de cadenas de texto del Formulario
	const char *ptrDatos;	//Puntero a la matriz de datos de los Objetos Gr�ficos del Formulario
	const char *ptrCadenas;	//Puntero a la matriz que contiene las cadenas de texto asociadas a los objetos gr�ficos del Formulario
};

#endif	//OBJETOS

