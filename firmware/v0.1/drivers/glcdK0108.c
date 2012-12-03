/////////////////////////////////////////////////////////////////////////
// Conexiones de pines del GLCD (Con chipset K0108)                    //
//                                                                			//
//        1: CS1    <-> C0                                             //
//        2: CS1    <-> C1                                             //
//        6: R/S    <-> E2                                             //
//        7: R/W    <-> E1                                             //
//        8: E      <-> E0                                             //
//    9..16: D0..D7 <-> D0..D7                                         //
//       17: Reset  <-> B5                                             //
//                                                                     //
//  Los valores pueden cambiarse con los DEFINE que están más abajo    //
//---------------------------------------------------------------------//
//  > GLCD_limpiar(color)                                              //
//   "Borra" la pantalla, llenandola del color seleccionado.           //
//   color = 0 : puntos apagados                                       //
//   color = 1 : puntos encendidos                                     //
//                                                                     //
//  > GLCD_RAM2LCD()                                                   //
//   Vuelca el contenido de la RAM a la pantalla.                      //
//   solo funciona si FAST_GLCD está definido.                         //
//---------------------------------------------------------------------//
//  > GLCD_inicializa(modo)                                            //
//   Inicializa el GLCD, y debe llamarse ANTES de cualquier otra.      //
//   modo = 0 : GLCD en ON                                             //
//   modo = 1 : GLCD en OFF                                            //
//                                                                     //
//   EN LAS SIGUIENTES FUNCIONES, SIEMPRE SE RESPETA QUE:              //
//   color = 0 : puntos apagados                                       //
//   color = 1 : puntos encendidos                                     //
//                                                                     //
//  > GLCD_Punto(x,y,color)                                            //
//   Dibuja un punto en x,y. 0,0 es la esquina superior izquierda.     //
//                                                                     //
//  > GLCD_Linea(x1,y1,x2,y2,color)                                    //
//   Dibuja una linea desde (x1,y1) a (x2,y2)                          //
//                                                                     //
//  >GLCD_rectangulo (x1,y1,x2,y2,color)                               //
//  Dibuja un rectangulo con esquinas en (x1,y1) y (x2,y2)             //
//                                                                     //
//  >GLCD_caja (x1,y1,x2,y2,color)                                     //
//  Dibuja un rectangulo pintado con esquinas en (x1,y1) y (x2,y2)     //
//                                                                     //
//  >GLCD_circulo (x1,y1,r,color)                                      //
//  Dibuja un circulo con centro en (x1,y1) y radio R                  //
//                                                                     //
/////////////////////////////////////////////////////////////////////////

#include "glcdK0108.h"

//ARREGLO DE CARACTERES RELATIVO AL DISPLAY
#ifdef __18CXX
rom const char TEXT_5X7_1[51][5] ={0x00, 0x00, 0x00, 0x00, 0x00, // SPACE
#else 
const char TEXT_5X7_1[51][5] ={0x00, 0x00, 0x00, 0x00, 0x00, // SPACE
#endif
                         0x00, 0x00, 0x5F, 0x00, 0x00, // !
                         0x00, 0x03, 0x00, 0x03, 0x00, // "
                         0x14, 0x3E, 0x14, 0x3E, 0x14, // #
                         0x24, 0x2A, 0x7F, 0x2A, 0x12, // $
                         0x43, 0x33, 0x08, 0x66, 0x61, // %
                         0x36, 0x49, 0x55, 0x22, 0x50, // &
                         0x00, 0x05, 0x03, 0x00, 0x00, // '
                         0x00, 0x1C, 0x22, 0x41, 0x00, // (
                         0x00, 0x41, 0x22, 0x1C, 0x00, // )
                         0x14, 0x08, 0x3E, 0x08, 0x14, // *
                         0x08, 0x08, 0x3E, 0x08, 0x08, // +
                         0x00, 0x50, 0x30, 0x00, 0x00, // ,
                         0x08, 0x08, 0x08, 0x08, 0x08, // -
                         0x00, 0x60, 0x60, 0x00, 0x00, // .
                         0x20, 0x10, 0x08, 0x04, 0x02, // /
                         0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
                         0x04, 0x02, 0x7F, 0x00, 0x00, // 1
                         0x42, 0x61, 0x51, 0x49, 0x46, // 2
                         0x22, 0x41, 0x49, 0x49, 0x36, // 3
                         0x18, 0x14, 0x12, 0x7F, 0x10, // 4
                         0x27, 0x45, 0x45, 0x45, 0x39, // 5
                         0x3E, 0x49, 0x49, 0x49, 0x32, // 6
                         0x01, 0x01, 0x71, 0x09, 0x07, // 7
                         0x36, 0x49, 0x49, 0x49, 0x36, // 8
                         0x26, 0x49, 0x49, 0x49, 0x3E, // 9
                         0x00, 0x6C, 0x6C, 0x00, 0x00, // : -> 0x00, 0x36, 0x36, 0x00, 0x00, // :
                         0x00, 0x56, 0x36, 0x00, 0x00, // ; 
                         0x08, 0x14, 0x22, 0x41, 0x00, // <
                         0x14, 0x14, 0x14, 0x14, 0x14, // =
                         0x00, 0x41, 0x22, 0x14, 0x08, // >
                         0x02, 0x01, 0x51, 0x09, 0x06, // ?
                         0x3E, 0x41, 0x59, 0x55, 0x5E, // @
                         0x7E, 0x09, 0x09, 0x09, 0x7E, // A	//65
                         0x7F, 0x49, 0x49, 0x49, 0x36, // B
                         0x3E, 0x41, 0x41, 0x41, 0x22, // C
                         0x7F, 0x41, 0x41, 0x41, 0x3E, // D
                         0x7F, 0x49, 0x49, 0x49, 0x41, // E
                         0x7F, 0x09, 0x09, 0x09, 0x01, // F
                         0x3E, 0x41, 0x41, 0x49, 0x3A, // G
                         0x7F, 0x08, 0x08, 0x08, 0x7F, // H
                         0x00, 0x41, 0x7F, 0x41, 0x00, // I
                         0x30, 0x40, 0x40, 0x40, 0x3F, // J
                         0x7F, 0x08, 0x14, 0x22, 0x41, // K
                         0x7F, 0x40, 0x40, 0x40, 0x40, // L
                         0x7F, 0x02, 0x0C, 0x02, 0x7F, // M
                         0x7F, 0x02, 0x04, 0x08, 0x7F, // N
                         0x3E, 0x41, 0x41, 0x41, 0x3E, // O
                         0x7F, 0x09, 0x09, 0x09, 0x06, // P	//80
                         0x1E, 0x21, 0x21, 0x21, 0x5E, // Q
                         0x7F, 0x09, 0x09, 0x09, 0x76};// R

#ifdef __18CXX
rom const char TEXT_5X7_2[44][5]={0x26, 0x49, 0x49, 0x49, 0x32, // S
#else
const char TEXT_5X7_2[44][5]={0x26, 0x49, 0x49, 0x49, 0x32, // S
#endif
                         0x01, 0x01, 0x7F, 0x01, 0x01, // T
                         0x3F, 0x40, 0x40, 0x40, 0x3F, // U
                         0x1F, 0x20, 0x40, 0x20, 0x1F, // V
                         0x7F, 0x20, 0x10, 0x20, 0x7F, // W
                         0x41, 0x22, 0x1C, 0x22, 0x41, // X
                         0x07, 0x08, 0x70, 0x08, 0x07, // Y
                         0x61, 0x51, 0x49, 0x45, 0x43, // Z
                         0x00, 0x7F, 0x41, 0x00, 0x00, // [
                         0x02, 0x04, 0x08, 0x10, 0x20, // Barra invertida
                         0x00, 0x00, 0x41, 0x7F, 0x00, // ]
                         0x04, 0x02, 0x01, 0x02, 0x04, // ^
                         0x40, 0x40, 0x40, 0x40, 0x40, // _
                         0x00, 0x01, 0x02, 0x04, 0x00, // `
                         0x20, 0x54, 0x54, 0x54, 0x78, // a //97
                         0x7F, 0x44, 0x44, 0x44, 0x38, // b
                         0x38, 0x44, 0x44, 0x44, 0x44, // c
                         0x38, 0x44, 0x44, 0x44, 0x7F, // d
                         0x38, 0x54, 0x54, 0x54, 0x18, // e
                         0x04, 0x04, 0x7E, 0x05, 0x05, // f
                         0x08, 0x54, 0x54, 0x54, 0x3C, // g
                         0x7F, 0x08, 0x04, 0x04, 0x78, // h
                         0x00, 0x44, 0x7D, 0x40, 0x00, // i	//105
                         0x20, 0x40, 0x44, 0x3D, 0x00, // j
                         0x7F, 0x10, 0x28, 0x44, 0x00, // k
                         0x00, 0x41, 0x7F, 0x40, 0x00, // l
                         0x7C, 0x04, 0x78, 0x04, 0x78, // m
                         0x7C, 0x08, 0x04, 0x04, 0x78, // n
                         0x38, 0x44, 0x44, 0x44, 0x38, // o
                         0x7C, 0x14, 0x14, 0x14, 0x08, // p
                         0x08, 0x14, 0x14, 0x14, 0x7C, // q
                         0x00, 0x7C, 0x08, 0x04, 0x04, // r
                         0x48, 0x54, 0x54, 0x54, 0x20, // s
                         0x04, 0x04, 0x3F, 0x44, 0x44, // t
                         0x3C, 0x40, 0x40, 0x20, 0x7C, // u	//117
                         0x1C, 0x20, 0x40, 0x20, 0x1C, // v
                         0x3C, 0x40, 0x30, 0x40, 0x3C, // w
                         0x44, 0x28, 0x10, 0x28, 0x44, // x
                         0x0C, 0x50, 0x50, 0x50, 0x3C, // y
                         0x44, 0x64, 0x54, 0x4C, 0x44, // z
                         0x00, 0x08, 0x36, 0x41, 0x41, // {
                         0x00, 0x00, 0x7F, 0x00, 0x00, // |
                         0x41, 0x41, 0x36, 0x08, 0x00, // }
                         0x02, 0x01, 0x02, 0x04, 0x02};// ~

// Si la letra posee excepcion se pone 1 en el MSB de la primera columna y se analiza la tercer columna
//que con el digito 0x1X (p letras de 5x5) o 0x2X (p letras de 4x5) para elegir la matriz de excepciones
//y el digito 0x_N para elegir la excepción de la letra correspondiente, empezando con 0
#ifdef __18CXX
rom const char TEXT_3X5_1[51][3] ={0x00, 0x00, 0x00, // SPACE
#else
const char TEXT_3X5_1[51][3] ={0x00, 0x00, 0x00, // SPACE
#endif
                         0x17, 0x00, 0x00, // !
                         0x07, 0x00, 0x07, // "
                         0x9A, 0x1F, 0x10, // # -> excepcion, agregar: 0x0A, 0x1F, 0x0A
                         0x7F, 0x2A, 0x12, // $ -> no implementada
                         0x92, 0x08, 0x20, // % -> excepcion, agregar: 0x04, 0x12
                         0x96, 0x19, 0x11, // Ohm(&) -> excepcion, agregar: 0x01, 0x09, 0x16
                         0x03, 0x00, 0x00, // '
                         0x0E, 0x11, 0x00, // (
                         0x11, 0x0E, 0x00, // )
                         0x01, 0x00, 0x00, // ` (*)
                         0x04, 0x0E, 0x04, // +
                         0x14, 0x0c, 0x00, // ,
                         0x08, 0x08, 0x08, // - 
                         0x00, 0x10, 0x00, // .
                         0x90, 0x08, 0x21, // / -> excepcion, agregar: 0x04, 0x02
                         0x0E, 0x11, 0x0E, // 0 
                         0x12, 0x1F, 0x10, // 1
                         0x13, 0x19, 0x17, // 2
                         0x11, 0x15, 0x1F, // 3
                         0x07, 0x04, 0x1F, // 4
                         0x17, 0x15, 0x1D, // 5
                         0x1F, 0x15, 0x1D, // 6
                         0x01, 0x01, 0x1F, // 7
                         0x1F, 0x15, 0x1F, // 8
                         0x17, 0x15, 0x1F, // 9
                         0x00, 0x14, 0x00, // :
                         0x10, 0x1A, 0x00, // ;
                         0x04, 0x0A, 0x11, // <
                         0x14, 0x14, 0x14, // =
                         0x11, 0x0A, 0x04, // >
                         0x01, 0x15, 0x03, // ?
                         0x9F, 0x11, 0x22, // @ -> excepcion, agregar: 0x15, 0x17
                         0x1E, 0x05, 0x1E, // A
                         0x1F, 0x15, 0x0A, // B
                         0x0E, 0x11, 0x11, // C
                         0x1F, 0x11, 0x0E, // D
                         0x1F, 0x15, 0x11, // E
                         0x1F, 0x05, 0x01, // F
                         0x1F, 0x15, 0x1D, // G
                         0x1F, 0x04, 0x1F, // H
                         0x11, 0x1F, 0x11, // I
                         0x18, 0x10, 0x1F, // J
                         0x9F, 0x04, 0x23, // K -> excepcion, agregar: 0x0A, 0x11
                         0x1F, 0x10, 0x10, // L
                         0x9F, 0x02, 0x12, // M -> excepcion, agregar: 0x04, 0x02, 0x1F -- fila 45
                         0x9F, 0x02, 0x13, // N -> excepcion, agregar: 0x04, 0x08, 0x1F
                         0x1F, 0x11, 0x1F, // O
                         0x1F, 0x05, 0x07, // P
                         0x8E, 0x11, 0x24, // Q -> excepcion, agregar: 0x09, 0x16
                         0x1F, 0x05, 0x1A};// R

#ifdef __18CXX
rom const char TEXT_3X5_2[44][3]={0x12, 0x15, 0x09, // S -
#else
const char TEXT_3X5_2[44][3]={0x12, 0x15, 0x09, // S -
#endif
                         0x01, 0x1F, 0x01, // T
                         0x1F, 0x10, 0x1F, // U
                         0x07, 0x18, 0x07, // V
                         0x8F, 0x10, 0x14, // W -> excepcion, agregar: 0x0C, 0x10, 0x0F
                         0x1B, 0x04, 0x1B, // X
                         0x1B, 0x1C, 0x1B, // Y
                         0x19, 0x15, 0x13, // Z
                         0x1F, 0x11, 0x00, // [
                         0x82, 0x04, 0x25, // Barra invertida -> excepcion, agregar: 0x08, 0x10
                         0x11, 0x1F, 0x00, // ]
                         0x02, 0x01, 0x02, // ^
                         0x01, 0x01, 0x01, // _
                         0x01, 0x02, 0x00, // `
                         0x08, 0x14, 0x1C, // a
                         0x1F, 0x14, 0x1C, // b
                         0x1C, 0x14, 0x14, // c
                         0x1C, 0x14, 0x1F, // d
                         0x1E, 0x16, 0x16, // e
                         0x1E, 0x09, 0x03, // f
                         0x16, 0x16, 0x0E, // g
                         0x1F, 0x04, 0x1C, // h
                         0x1D, 0x10, 0x00, // i
                         0x18, 0x10, 0x1D, // j
                         0x1F, 0x08, 0x14, // k
                         0x1F, 0x10, 0x00, // l
                         0x9C, 0x04, 0x15, // m -> excepcion, agregar: 0x1C, 0x04, 0x1C
                         0x1C, 0x04, 0x1C, // n
                         0x1C, 0x14, 0x1C, // o
                         0x1C, 0x0C, 0x0C, // p
                         0x0C, 0x0C, 0x1C, // q
                         0x1C, 0x04, 0x0C, // r
                         0x14, 0x12, 0x0A, // s
                         0x02, 0x1F, 0x12, // t
                         0x1C, 0x10, 0x1C, // u
                         0x0C, 0x10, 0x0C, // v
                         0x8C, 0x10, 0x16, // w -> excepcion, agregar: 0x0C, 0x10, 0x0C
                         0x14, 0x08, 0x14, // x
                         0x16, 0x14, 0x1E, // y
                         0x92, 0x1A, 0x26, // z -> excepcion, agregar: 0x16, 0x11
                         0x36, 0x41, 0x41, // { -> no implementada
                         0x00, 0x1F, 0x00, // |
                         0x36, 0x08, 0x00, // } -> no implementada
                         0x84, 0x02, 0x27};// ~ -> excepcion, agregar: 0x04, 0x11

// Matriz de excepciones par
#ifdef __18CXX
rom const char TEXT_3X5_E1[7][3]={0x0A, 0x1F, 0x0A, // #
#else
const char TEXT_3X5_E1[7][3]={0x0A, 0x1F, 0x0A, // #
#endif
													0x01, 0x19, 0x16, // Ohm(&)
													0x04, 0x02, 0x1F, // M
													0x04, 0x08, 0x1F, // N
													0x0C, 0x10, 0x0F, // W
													0x1C, 0x04, 0x1C, // m
													0x0C, 0x10, 0x0C};// w

#ifdef __18CXX
rom const char TEXT_3X5_E2[8][2]={0x04, 0x12, // %
#else
const char TEXT_3X5_E2[8][2]={0x04, 0x12, // %
#endif
													0x04, 0x02, // /
													0x15, 0x17, // @
													0x0A, 0x11, // K
													0x09, 0x16, // Q
													0x08, 0x10, // Barra Invertida
													0x16, 0x12, // z
													0x04, 0x11};// ~
													

//#pragma romdata	

//VARIABLES DEL DISPLAY
struct Display DispReal;	

char pixelData[5];  		// Guarda los datos del caracter

// VARIABLES DE BitClear()
volatile unsigned char iBC;
volatile unsigned char ValBC;

// VARIABLES DE BitSet()
volatile unsigned char iBS;
volatile unsigned char ValBS;

// VARIABLES DE GLCD_enviaBYTE()
volatile unsigned int TrisVal_GeB;

// VARIABLES DE GLCD_leeBYTE()
volatile unsigned char Dato_GlB;
volatile unsigned int TrisVal_GlB;

// VARIABLES DE GLCD_Listo()
volatile unsigned char Status_GL;

// VARIABLES DE GLCD_limpiar()
volatile unsigned char i_Gl;
volatile unsigned char j_Gl;

// VARIABLES DE GLCD_Punto()
volatile unsigned char Dato_Gp;
volatile unsigned char Lado_Gp;

// VARIABLES DE GLCD_LineaVertRapida()
volatile unsigned char ladoLVR;
volatile unsigned char iLVR;
volatile signed char 	pagCompLVR;
volatile unsigned char byteLVR;
volatile unsigned char byte1LVR;
volatile unsigned char SIPLVR;
volatile unsigned char SFALVR;
volatile unsigned char pagInicLVR;
volatile unsigned char pagFinLVR;

// VARIABLES DE GLCD_AnchoLetra()
volatile unsigned char calcFilaAL;

// VARIABLES DE GLCD_RendString35()
volatile unsigned char iRS35, jRS35, kRS35, uRS35, lRS35, mRS35;               			// Indices
volatile unsigned char calcFilaRS35;
volatile unsigned char calcFila1RS35;
volatile unsigned char calcFila2RS35;

// VARIABLES DE GLCD_RendString57()
volatile unsigned char iRS57, jRS57, kRS57, uRS57, lRS57, mRS57;               			// Indices
volatile unsigned char calcFilaRS57;
volatile unsigned char calcFila1RS57;
volatile unsigned char calcFila2RS57;

// VARIABLES DE GLCD_Relleno()
volatile unsigned char iGLCDR;

//VARIABLES DE GLCD_LineaPuntoAPunto()
volatile signed char incrementoXLPAP, incrementoYLPAP, distanciaXLPAP, distanciaYLPAP;
volatile unsigned char xLPAP, yLPAP;
volatile signed long PLPAP;
volatile unsigned char iLPAP;


/*Función SetearPuertoDatos------------------------------------------------------------------------------------------------------------------------
Descripción: Función que guarda el estado del puerto de datos y lo setea para enviarle datos al GLCD
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SetearPuertoDatos(INT8U	modo)
{
	if (modo == SALIDA)
	{
		TrisVal_GeB = TRISB;	//Guardo el estado del TRISD para luego restaurarlo y asi evitar conflictos
		TRISB = TRISB & 0x00FF;	//Seteo desde RB8 hasta RB15 como salida
	}
	else
	{
		TrisVal_GeB = TRISB;	//Guardo el estado del TRISD para luego restaurarlo y asi evitar conflictos
		TRISB = TRISB | 0xFF00;	//Seteo desde RB8 hasta RB15 como entrada
	}
}// Fin SetearPuertoDatos()

/*Función RestaurarPuertoDatos------------------------------------------------------------------------------------------------------------------------
Descripción: Función que restaura el estado del puerto de datos
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void RestaurarPuertoDatos(void)
{
	TRISB = TrisVal_GeB;	//Restauro el estado del puerto de datos
}// Fin RestaurarPuertoDatos()

/* Función Abs ----------------------------------------------------------------------
Descripción: Función que devuelve el valor absoluto del argumento pasado (valor) 
Entrada: 
		valor: valor del cual se desea obtener el valor absoluto
Salida: 
		Abs: valor absoluto de "valor"
-----------------------------------------------------------------------------------*/
signed char Abs(signed char valor)
{
	if (valor < 0)
		return -valor;
	return valor;
} //Fin Abs()

//-----------------------------------------------------------------------
//Pone en uno el bit Bit de Dato 
//-----------------------------------------------------------------------
void BitSet(volatile unsigned char* Dato, char Bit)
{
	//char iBS, ValBS = 1;
	ValBS = 1;
	for(iBS=0;iBS<Bit;iBS++)
		ValBS = ValBS * 2;
	*Dato = (*Dato) | ValBS;
} //Fin BitSet()

//-----------------------------------------------------------------------
//Pone en cero el bit Bit de Dato 
//-----------------------------------------------------------------------
void BitClear(volatile unsigned char* Dato, char Bit)
{
	//char iBC, ValBC=1;
	ValBC = 1;
	for(iBC=0;iBC<Bit;iBC++)
		ValBC = ValBC * 2;
	ValBC = ~ValBC;
	*Dato = (*Dato) & ValBC;
} //Fin BitClear()

/* Función BitTest ----------------------------------------------------------------------
Descripción: Función que determina si el bit n del byte dato está seteado o no
Entrada:
		dato: byte que contiene el bit que se (quiere testear
		n: número de bit dentro del byte que se quiere testear
Salida: 
		GLCD_BitTest: byte de valor 0 si el bit no está seteado, y 1 si lo está
---------------------------------------------------------------------------------------*/
char BitTest(unsigned char dato, unsigned char n)
{
	if ((dato & (1<<n)) > 0)
		return 1;
	return 0;
} //Fin BitTest()

//-----------------------------------------------------------------------
//Provoca una demora de Cant_us de microsegundos, considerando que T=100ns, o sea Finst = 10 MHZ 
//-----------------------------------------------------------------------
void delay(void) //Esta función hace una demora de 1.3 useg para 40Mhz 
{
	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();
} //Fin delay()

//-----------------------------------------------------------------------
//Escribe un byte en una de las mitades de la pantalla (lado=0:izq Lado=1:der)
//-----------------------------------------------------------------------
void GLCD_enviaBYTE(char Lado, char Dato)
{
	//unsigned int TrisVal_GeB;
	//Espera de al menos 50 ns
	Nop();	
	Nop();
	Nop(); Nop(); Nop();	//Tres Tcy extras de tiempo por seguridad

	DeshabilitarISRs();		//Desactivo interrupciones durante esta función para evitar problemas

	Nop();	//Espera de al menos 25 ns
	Nop(); Nop(); Nop();	//Tres Tcy extras de tiempo por seguridad

	if (Lado == GLCD_LADO_CS2) 
		GLCD_CS2 = 1;  // Selecciono la mitad correspondiente
	else
		GLCD_CS1 = 1;

	Nop();	//Espera de al menos 25 ns
	Nop(); Nop(); Nop();	//Tres Tcy extras de tiempo por seguridad

	GLCD_RW = 0;       // Modo escritura

	Nop();	//Espera de al menos 25 ns
	Nop(); Nop(); Nop();	//Tres Tcy extras de tiempo por seguridad

	SetearPuertoDatos(SALIDA);	//Salvamos el estado del puerto de datos y lo seteamos para enviarle datos al GLCD

	//Espera de al menos 400 ns
	DelayTcy(1);
	Nop(); Nop(); Nop();	//Tres Tcy extras de tiempo por seguridad

	PORTB = (PORTB & 0x00FF) | (Dato << 8);            // Coloco el dato en el puerto de datos

	//Espera de al menos 200 ns
	Nop();	Nop();	Nop();	Nop();	Nop();	//5 Nops
	Nop();	Nop();	Nop();	//3 Nops
	Nop(); Nop(); Nop();	//Tres Tcy extras de tiempo por seguridad

	GLCD_E = 1;       // Pongo el bit Enable en alto y...

	//Espera de al menos 2 useg
	DelayTcy(14);
	Nop(); Nop(); Nop();	//Tres Tcy extras de tiempo por seguridad

  GLCD_E = 0;        // Pongo el bit Enable en bajo.

	//Espera de al menos 2 useg
	DelayTcy(14);	
	Nop(); Nop(); Nop();	//Tres Tcy extras de tiempo por seguridad

  GLCD_CS1 = 0;      // Libero la linea CS1 y...
	Nop();
  GLCD_CS2 = 0;      // CS2.
	RestaurarPuertoDatos();
	HabilitarISRs(); //Habilito nuevamente las interrupciones
} //Fin GLCD_enviaBYTE()

//-----------------------------------------------------------------------
// Lee un byte de una de las dos mitades de la pantalla
//-----------------------------------------------------------------------
char GLCD_leeBYTE(char Lado)
{
  /*char dato4;
	char TrisVal;*/

	//Espera de al menos 50 ns
	Nop();	
	Nop();
	Nop(); Nop(); Nop();	//Tres Tcy extras de tiempo por seguridad

	DeshabilitarISRs();		//Desactivo interrupciones durante esta función para evitar problemas
	SetearPuertoDatos(ENTRADA);	//Salvamos el estado del puerto de datos y lo seteamos para enviarle datos al GLCD
  
	//Espera de al menos 575 ns
	DelayTcy(2);
	Nop(); Nop(); Nop();	//Tres Tcy extras de tiempo por seguridad

	GLCD_RW = 1;      			// GLCD en Modo lectura

	//Espera de al menos 75 ns
	Nop();	
	Nop();	
	Nop();
	Nop(); Nop(); Nop();	//Tres Tcy extras de tiempo por seguridad

  // Selecciono la mitad del display a leer.
  if (Lado == GLCD_LADO_CS2) 
		GLCD_CS2 = 1;
  else 
		GLCD_CS1 = 1;

	//Espera de al menos 75 ns
	Nop();	
	Nop();	
	Nop();
	Nop(); Nop(); Nop();	//Tres Tcy extras de tiempo por seguridad

	GLCD_E = 1;  			     	// Pongo en alto el pin enable y...

	//Espera de al menos 2 useg
	DelayTcy(10);
	Nop(); Nop(); Nop();	//Tres Tcy extras de tiempo por seguridad

  Dato_GlB = (PORTB >> 8);          // Guardo en "dato" el valor devuelto y...
	
	//Espera de al menos 325 ns
	DelayTcy(1);
	Nop(); Nop(); Nop();	//Tres Tcy extras de tiempo por seguridad

	GLCD_E = 0;        			// ...pongo en bajo el pin enable.

	//Espera de al menos 2 useg
	DelayTcy(10);
	Nop(); Nop(); Nop();	//Tres Tcy extras de tiempo por seguridad

	// Vuelvo a poner en bajo las lineas CS1 y CS2.
  GLCD_CS1 = 0;
	Nop();	
  GLCD_CS2 = 0;
	RestaurarPuertoDatos();
  HabilitarISRs(); //Habilito nuevamente las interrupciones
	return Dato_GlB;
} //Fin GLCD_leeBYTE()

//-----------------------------------------------------------------------
//Espera hasta que el GLCD este listo para ser escrito o leido 
//-----------------------------------------------------------------------
unsigned char GLCD_Listo(char Lado)
{
	//unsigned char Status_GL;
  GLCD_DI = 0;   // Modo instruccion
	do	
	{
		Nop();
	} while ((Status_GL = GLCD_leeBYTE(Lado)) & 0x80);
	return 1;
} //Fin GLCD_Listo()

//-----------------------------------------------------------------------
// Limpia el GLCD (pinta toda la pantalla de un color)
//-----------------------------------------------------------------------
void GLCD_limpiar(char Color)
{
   // Recorre las 8 paginas (vertical)
   for(i_Gl = 0; i_Gl < 8; ++i_Gl)
   {
      GLCD_DI = 0;   // Modo instruccion

      //Comienzo, en cada página, desde la dirección 0
      GLCD_enviaBYTE(GLCD_LADO_CS1, 0b01000000);
      GLCD_enviaBYTE(GLCD_LADO_CS2, 0b01000000);

      //Selecciono la direccion dentro de la pagina
      GLCD_enviaBYTE(GLCD_LADO_CS1, i_Gl | 0b10111000);
      GLCD_enviaBYTE(GLCD_LADO_CS2, i_Gl | 0b10111000);

      GLCD_DI = 1;   // Modo datos

      // Recorre las dos mitades (horizontales)
			//NOTA: el compilador tiene problemas para implementar esto, asi que el codigo es rebuscado a proposito
			for(j_Gl = 0; j_Gl < 64; ++j_Gl)
			{
				GLCD_enviaBYTE(GLCD_LADO_CS1, 0xFF * Color);  // Enciende/apaga pixeles
   		  //GLCD_Listo(GLCD_LADO_CS1);
				GLCD_enviaBYTE(GLCD_LADO_CS2, 0xFF * Color);  // Enciende/apaga pixeles
      	//GLCD_Listo(GLCD_LADO_CS2);
			}
   }
} //Fin GLCD_limpiar()

//-----------------------------------------------------------------------
//Esta funcion inicializa el LCD.
//-----------------------------------------------------------------------
void GLCD_Init(char Modo)
{
	//unsigned int i;
	//Configuro los pines de control como salida
	TRIS_GLCD_CS1 = 0;
	TRIS_GLCD_CS2 = 0;
	TRIS_GLCD_DI = 0;
	TRIS_GLCD_RW = 0;
	TRIS_GLCD_E = 0;
	
	//Configuro los pines de control como digitales
	AD1PCFGLbits.PCFG0 = 1;	//RA0 - GLCD_CS1
	AD1PCFGLbits.PCFG1 = 1;	//RA1 - GLCD_CS2
	AD1PCFGLbits.PCFG12 = 1;	//RB12 - GLCD_D4
	AD1PCFGLbits.PCFG11 = 1;	//RB13 - GLCD_D5
	AD1PCFGLbits.PCFG10 = 1;	//RB14 - GLCD_D6
	AD1PCFGLbits.PCFG9 = 1;		//RB15 - GLCD_D7

	//GLCD_CONTRASTE = 1;
	//GLCD_BACKLIGHT = 1;

	//EncenderDisplay();
	//ApagarDisplay();

  // Pongo los pines de control en el estado correcto.
	//GLCD_RESET = 0;

	DelayTcy(10000);			//Delay10TCYx(100);

	//GLCD_RESET = 1;
  GLCD_E = 0;
	Nop();
  GLCD_CS1 = 0;
	Nop();
  GLCD_CS2 = 0;
	Nop();
  GLCD_DI = 0;   // Modo instruccion

  // Envio datos de inicialización -----------------------
  GLCD_enviaBYTE(GLCD_LADO_CS1, 0xC0);
  GLCD_enviaBYTE(GLCD_LADO_CS2, 0xC0);
  GLCD_enviaBYTE(GLCD_LADO_CS1, 0x40);
  GLCD_enviaBYTE(GLCD_LADO_CS2, 0x40);
  GLCD_enviaBYTE(GLCD_LADO_CS1, 0xB8);
  GLCD_enviaBYTE(GLCD_LADO_CS2, 0xB8);
  // Si modo = 1 inicializa encendido. Sino, apagado.
  if(Modo == NEGRO)
  {  	
		GLCD_enviaBYTE(GLCD_LADO_CS1,  0x3F); // Enciendo el GLCD
    GLCD_enviaBYTE(GLCD_LADO_CS2, 0x3F);
	}
  else 
	{
   	GLCD_enviaBYTE(GLCD_LADO_CS1,  0x3E); // Apago el GLCD
   	GLCD_enviaBYTE(GLCD_LADO_CS2, 0x3E); 
	}

  // Borro la pantalla
  GLCD_limpiar(COLOR_FONDO_DEF);
} //Fin GLCD_Init()

/* Función GLCD_Punto ----------------------------------------------------------------------
Descripción: 	función que dibuja un pixel de color "color" en las coordenadas (x,y)
Entrada: 
	x: coordenada x
	y: coordenada y
	color: color del punto (píxel)
Salida: nada
------------------------------------------------------------------------------------------*/
void GLCD_Punto(unsigned char x, unsigned char y, unsigned char Color)
{
  //Verificamos que las coordenadas pasadas caen dentro del área donde está el display real, sino no se grafica.
	if (!((x >= DispReal.offsetX) && (x < (DispReal.offsetX + DispReal.ancho))))
		return;
	
	//Ahora verificamos que cumpla en Y
	if (!((y >= DispReal.offsetY) && (y < (DispReal.offsetY + DispReal.alto))))
		return;

	//Cálculo de las coordenadas relativas al display real para X
	x = x - DispReal.offsetX;	
	y = y - DispReal.offsetY;	//Cálculo de las coordenadas relativas al display real para Y
	
	//Invertir ordenadas (y) para ubicar el origen en la parte de abajo del display real
	y = ALTO_DISP_REAL - y - 1;

	//x++;
  if(x > 63)                  // Veo si cae del otro lado
  { 
		x -= 64;
    Lado_Gp = GLCD_LADO_CS2;
	}
	else
		Lado_Gp = GLCD_LADO_CS1;

  GLCD_DI = 0;      // Modo instruccion
  x = x & 0x7F; //BitClear(x,7);           // Limpio bit MSB...
  x = x | 0x40; //BitSet(x,6);             // ...y pongo el bit 6 en 1
  GLCD_enviaBYTE(Lado_Gp, x);  //Envio la dirección de la coordenada X

  // Calculo en que pagina de las 8 cae...
  GLCD_enviaBYTE(Lado_Gp, (y/8 & 0xBF) | 0xB8);
  GLCD_DI = 1;     // ...y paso a Modo datos

  //Se necesitan dos lecturas para que devuelva el dato en la nueva direccion
  GLCD_leeBYTE(Lado_Gp);
  Dato_Gp = GLCD_leeBYTE(Lado_Gp);

  //De acuerdo al valor de color...
  if(Color == 1) 
		BitSet(&Dato_Gp, y%8);    // Enciendo el pixel
  else 
		BitClear(&Dato_Gp, y%8);  // apago el pixel

  GLCD_DI = 0;          // Modo instruccion
  GLCD_enviaBYTE(Lado_Gp, x);      // Fijo el lado a escribir,
  GLCD_DI = 1;         // pongo en Modo Datos y....
  GLCD_enviaBYTE(Lado_Gp, Dato_Gp);   // dibujo el pixel
} //Fin GLCD_Punto()


/* Función GLCD_GetColorPunto ----------------------------------------------------------------------
Descripción: 	función que devuelve el color del pixel en las coordenadas (x,y)
Entrada: 
	x: coordenada x
	y: coordenada y
Salida:
	color: color del punto (píxel)
------------------------------------------------------------------------------------------*/
unsigned char GLCD_GetColorPunto(unsigned char x, unsigned char y)
{
  //Verificamos que las coordenadas pasadas caen dentro del área donde está el display real, sino no se grafica.
	if (!((x >= DispReal.offsetX) && (x < (DispReal.offsetX + DispReal.ancho))))
		return;
	
	//Ahora verificamos que cumpla en Y
	if (!((y >= DispReal.offsetY) && (y < (DispReal.offsetY + DispReal.alto))))
		return;

	//Cálculo de las coordenadas relativas al display real para X
	x = x - DispReal.offsetX;	
	y = y - DispReal.offsetY;	//Cálculo de las coordenadas relativas al display real para Y
	
	//Invertir ordenadas (y) para ubicar el origen en la parte de abajo del display real
	y = ALTO_DISP_REAL - y - 1;

	//x++;
  if(x > 63)                  // Veo si cae del otro lado
  { 
		x -= 64;
    Lado_Gp = GLCD_LADO_CS2;
	}
	else
		Lado_Gp = GLCD_LADO_CS1;

  GLCD_DI = 0;      // Modo instruccion
  x = x & 0x7F; //BitClear(x,7);           // Limpio bit MSB...
  x = x | 0x40; //BitSet(x,6);             // ...y pongo el bit 6 en 1
  GLCD_enviaBYTE(Lado_Gp, x);  //Envio la dirección de la coordenada X

  // Calculo en cual página de las 8 cae...
  GLCD_enviaBYTE(Lado_Gp, (y/8 & 0xBF) | 0xB8);
  GLCD_DI = 1;     // ...y paso a Modo datos

  //Se necesitan dos lecturas para que devuelva el dato en la nueva direccion
  GLCD_leeBYTE(Lado_Gp);
  Dato_Gp = GLCD_leeBYTE(Lado_Gp);

  //De acuerdo al valor de color...
  //if(Color == 1) 
		//BitSet(&Dato_Gp, y%8);    // Enciendo el pixel
  //else 
		//BitClear(&Dato_Gp, y%8);  // apago el pixel

  GLCD_DI = 0;          // Modo instruccion
  GLCD_enviaBYTE(Lado_Gp, x);      // Fijo el lado a escribir,
  GLCD_DI = 1;         // pongo en Modo Datos y....
  GLCD_enviaBYTE(Lado_Gp, Dato_Gp);   // dibujo el pixel
} //Fin GLCD_GetColorPunto()


//------------------------------------------------------------
//Rutina que traza una línea vertical desde y1 hasta y2 de forma mucho mas rapida que GLCD_Linea
//------------------------------------------------------------
void GLCD_LineaVertRapida(unsigned char x, unsigned char y1, unsigned char y2, unsigned char color)
{	
  /*unsigned char lado;  			//Lado en que voy a dibujar.
	unsigned char i;
	signed char 	PagComp;
	unsigned char Byte;				//Aca guardo el byte que leo para no sobreescribir lo que había antes
	unsigned char Byte1;
	unsigned char SIP;				//Sobrante Inicial Posterior
	unsigned char SFA;				//Sobrante Final Anterior
	unsigned char PagInic;
	unsigned char	PagFin;*/
	
	//Verifico que y2 sea mayor que y1, y si no es así, los invierto
	if (y2 < y1)	//Si se pasaron los argumentos "al reves", los doy vuelta usando como variable auxiliar Byte_LVR
	{
		byteLVR = y1;
		y1 = y2;
		y2 = byteLVR;
	}

	//Verificamos que x cae dentro del área del display real, sino no se grafica.
	if ((x >= DispReal.offsetX) && (x < (DispReal.offsetX + DispReal.ancho)))
	{
		//Siendo y2 > y1 se verifica si parte de la linea cae dentro del DispReal
		if (y1 < DispReal.offsetY)
			if (y2 >= DispReal.offsetY)
				y1 = DispReal.offsetY; //Se corrige y1 porque está debajo del DispReal
			else
				return;	//No se grafica porque y1 e y2 están abajo del DispReal
		if (y2 > (DispReal.offsetY + DispReal.alto - 1))
			if (y1 <= (DispReal.offsetY + DispReal.alto - 1))
				y2 = DispReal.offsetY + DispReal.alto - 1; //Se corrige y2 porque está arriba del DispReal
			else
				return; //No se grafica porque y1 e y2 están arriba del DispReal
		//Verificamos si y1 y y2 son iguales, si es así, solo es necesario graficar un punto
		if (y1 == y2)
		{
			//GLCD_Punto(x + DispReal.offsetX, (ALTO_DISP_REAL - y1 - 1) + DispReal.offsetY, color);
			GLCD_Punto(x, y1, color);
			return;
		}
	}
	else
		return; //retorno sin graficar porque la línea no cae dentro del DispReal
	
	//Cálculo de las coordenadas relativas al display real
	y1 = y1 - DispReal.offsetY;	
	y2 = y2 - DispReal.offsetY;
	x = x - DispReal.offsetX;

	//Invertir ordenadas (y) para ubicar el origen en la parte de abajo del display
	y1 = ALTO_DISP_REAL - y1 - 1;
	y2 = ALTO_DISP_REAL - y2 - 1;

	if(x > 63)                  // Veo si cae del otro lado
  { 
		x -= 64;
    ladoLVR = GLCD_LADO_CS2;
	}
	else
		ladoLVR = GLCD_LADO_CS1;

	if (y2 < y1)		//Si se pasaron los argumentos "al reves", los doy vuelta usando como variable auxiliar Byte_LVR
	{
		byteLVR = y1;
		y1 = y2;
		y2 = byteLVR;
	}
	
	//Cálculo de páginas de Inicio y Fin de la línea
	pagInicLVR = (y1 >> 3); 						//Divido a y1 por 8 y eso me da la página de inicio de la linea vertical
	pagFinLVR = (y2 >> 3);							//Divido a y2 por 8 y eso me da la página de Finalización de la linea vertical

	//Cálculo de la cantidad de páginas completas que tengo que escribir
	//PagComp_LVR = (y2/8 + 1) - (y1/8 + 1)	//La cantidad de páginas completas es igual a la Página Final menos la Página Inicial 
	pagCompLVR = pagFinLVR - pagInicLVR;		//Hago la diferencia entre la página de finalización y la de inicio para ver cuentas paginas tengo que escribir 
	
	//Cálculo del sobrante inicial
	if ((pagCompLVR == 0) && (y1 != y2))		//Si PagComp_LVR es cero, y1 y y2 caen en la misma página 
	{	
		//Leer Byte de la Página Inicial
		GLCD_DI = 0;   // Modo instruccion
	  //Seteo la dirección en x
	  GLCD_enviaBYTE(ladoLVR, x | 0b01000000);
		//Seteo la dirección en y
	  GLCD_enviaBYTE(ladoLVR, pagInicLVR | 0b10111000);
		
		//Leer Byte existente en esa dirección
		//Se necesitan dos lecturas para que devuelva el dato en la nueva dirección
 		GLCD_DI = 1;   // Modo datos
		GLCD_leeBYTE(ladoLVR);
 		byteLVR = GLCD_leeBYTE(ladoLVR);
			
		GLCD_DI = 0;   // Modo instruccion
		//Seteo la dirección en x nuevamente debido a los incrementos que me produjeron las dos lecturas
	  GLCD_enviaBYTE(ladoLVR, x | 0b01000000);
		//Seteo la dirección en y nuevamente debido a los incrementos que me produjeron las dos lecturas
	  GLCD_enviaBYTE(ladoLVR, pagInicLVR | 0b10111000);
			
		//Calculo el Byte a enviar
		byte1LVR = (255 << (y1 - (pagInicLVR * 8)) & (255 >> (8 - (y2 - (pagFinLVR * 8)) - 1)));

		//Pisar con unos o ceros los datos del byte que tienen que ser pintados por la línea dependiendo del color elegido
		GLCD_DI = 1;   // Modo datos
		if (color == NEGRO)	//Pinto de NEGRO (pongo unos)
			GLCD_enviaBYTE(ladoLVR, byteLVR | byte1LVR);
		else								//Pinto de Blanco (pongo ceros)
			GLCD_enviaBYTE(ladoLVR, byteLVR & (~byte1LVR));
	}
	else
	{
		//Cálculo del sobrante inicial
		SIPLVR = ((pagInicLVR + 1) * 8) - y1;
	
		//Leer Byte de la Página Inicial
		GLCD_DI = 0;   // Modo instruccion
  	//Seteo la dirección en x
  	GLCD_enviaBYTE(ladoLVR, x | 0b01000000);
		//Seteo la dirección en y
  	GLCD_enviaBYTE(ladoLVR, pagInicLVR | 0b10111000);
	
		//Leer Byte existente en esa dirección
		//Se necesitan dos lecturas para que devuelva el dato en la nueva dirección
 		GLCD_DI = 1;   // Modo datos
		GLCD_leeBYTE(ladoLVR);
 		byteLVR = GLCD_leeBYTE(ladoLVR);
		
		GLCD_DI = 0;   // Modo instruccion
		//Seteo la dirección en x nuevamente debido a los incrementos que me produjeron las dos lecturas
  	GLCD_enviaBYTE(ladoLVR, x | 0b01000000);
		//Seteo la dirección en y nuevamente debido a los incrementos que me produjeron las dos lecturas
  	GLCD_enviaBYTE(ladoLVR, pagInicLVR | 0b10111000);

		//Pisar con unos o ceros los datos del byte que tienen que ser pintados por la línea dependiendo del color elegido
		GLCD_DI = 1;   // Modo datos
		if (color == NEGRO)	//Pinto de NEGRO (pongo unos)
			GLCD_enviaBYTE(ladoLVR, byteLVR | (255 << (8 - SIPLVR)));
		else								//Pinto de Blanco (pongo ceros)
			GLCD_enviaBYTE(ladoLVR, byteLVR & (255 >> SIPLVR));
		
		//Pintar las páginas completas (páginas intermedias) con unos o ceros según el color elegido
		for (iLVR=1; iLVR < pagCompLVR; iLVR++)
		{
			GLCD_DI = 0;   // Modo instruccion
 			//Seteo la dirección en x
 			GLCD_enviaBYTE(ladoLVR, x | 0b01000000);
			//Seteo la dirección en y de la página
 			GLCD_enviaBYTE(ladoLVR, (pagInicLVR + iLVR) | 0b10111000);
			//Escribo los unos o ceros
			GLCD_DI = 1;   // Modo datos
			if (color == NEGRO)
				GLCD_enviaBYTE(ladoLVR, 0b11111111);
			else
				GLCD_enviaBYTE(ladoLVR, 0b00000000);
		}

		//Cálculo del sobrante final
		SFALVR = 8 - (((pagFinLVR + 1) * 8) - y2) + 1;

		//Leer Byte de la Página Final
		GLCD_DI = 0;   // Modo instruccion
  	//Seteo la dirección en x
  	GLCD_enviaBYTE(ladoLVR, x | 0b01000000);
		//Seteo la dirección en y
  	GLCD_enviaBYTE(ladoLVR, pagFinLVR | 0b10111000);
	
		//Leer Byte existente en esa dirección
		//Se necesitan dos lecturas para que devuelva el dato en la nueva dirección
 		GLCD_DI = 1;   // Modo datos
		GLCD_leeBYTE(ladoLVR);
 		byteLVR = GLCD_leeBYTE(ladoLVR);
		
		GLCD_DI = 0;   // Modo instruccion
		//Seteo la dirección en x nuevamente debido a los incrementos que me produjeron las dos lecturas
  	GLCD_enviaBYTE(ladoLVR, x | 0b01000000);
		//Seteo la dirección en y nuevamente debido a los incrementos que me produjeron las dos lecturas
  	GLCD_enviaBYTE(ladoLVR, pagFinLVR | 0b10111000);

		//Pisar con unos o ceros los datos del byte que tienen que ser pintados por la línea dependiendo del color elegido
		GLCD_DI = 1;   // Modo datos
		if (color == NEGRO) //Pinto de NEGRO (pongo unos)
			GLCD_enviaBYTE(ladoLVR, byteLVR | (255 >> (8 - SFALVR)));
		else								//Pinto de Blanco (pongo ceros)
			GLCD_enviaBYTE(ladoLVR, byteLVR & (255 << SFALVR));
	}
} //Fin GLCD_LineaVertRapida()

/* Función GLCD_LineaPuntoAPunto ----------------------------------------------------------
Descripción: función que dibuja una línea punto por punto. Esta función es lenta.
Entrada: 
	P1(x1;y1)
	P2(x2;y2)
	color: color del punto (píxel)
Salida: nada
------------------------------------------------------------------------------------------*/
void GLCD_LineaPuntoAPunto(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char color)
{
   //Declaro variables-------------------
  /*signed char incrementoXLPAP, incrementoYLPAP, distanciaXLPAP, distanciaYLPAP;
	unsigned char xLPAP, yLPAP;
	signed long PLPAP;
  unsigned char iLPAP;*/

	//Calculo las diferencias entre las coordenadas de origen y destino
  distanciaXLPAP = Abs((signed char)(x2 - x1));
  distanciaYLPAP = Abs((signed char)(y2 - y1));

  //Inicializo x e y con las coordenadas de origen
  xLPAP =  x1;
  yLPAP =  y1;

  //Calculo el sentido de los incrementos (positivos o negativos)
  //en funcion de la posicion del origen y el destino
  if(x1 > x2) 
		incrementoXLPAP = -1; 
	else 
		incrementoXLPAP = 1;
  if(y1 > y2) 
		incrementoYLPAP = -1; 
	else 
		incrementoYLPAP = 1;

  //Si la distancia horizontal es mayor a la vertical...
  if(distanciaXLPAP >= distanciaYLPAP)
	{ 
		PLPAP = 2 * distanciaYLPAP - distanciaXLPAP;
    for(iLPAP=0; iLPAP<=distanciaXLPAP; ++iLPAP)
    {
			GLCD_Punto( xLPAP, yLPAP, color);
			if(PLPAP < 0)
			{ 
				PLPAP += 2 * distanciaYLPAP;
				xLPAP += incrementoXLPAP; }
			else
			{ 
				PLPAP += 2*distanciaYLPAP - 2*distanciaXLPAP;
				xLPAP += incrementoXLPAP;
				yLPAP += incrementoYLPAP;}
			}
		}
  //Si la distancia vertical es mayor a la horizontal...
	else
	{ 
		PLPAP = 2 * distanciaXLPAP - distanciaYLPAP;
		for(iLPAP=0; iLPAP<=distanciaYLPAP; ++iLPAP)
		{ 
			GLCD_Punto(xLPAP, yLPAP, color);
      if(PLPAP < 0)
      {  
				PLPAP += 2 * distanciaXLPAP;
        yLPAP += incrementoYLPAP; 
			}
      else
      {  
				PLPAP += 2 * distanciaXLPAP - 2 * distanciaYLPAP;
        xLPAP += incrementoXLPAP;
        yLPAP += incrementoYLPAP; 
			}
    }
  }
} //Fin GLCD_LineaPuntoAPunto()

/* Función GLCD_Linea ---------------------------------------------------------------------
Descripción: función que dibuja una línea en el GLCD determinando por sí sola la forma más rápida de hacerlo.
Entrada: 
	x1: coordenada x del punto inicial de la línea
	x2: coordenada x del punto final de la línea
	y1: coordenada y del punto inicial de la línea
	y2: coordenada y del punto final de la línea
	color: color de la línea
Salida: nada
------------------------------------------------------------------------------------------*/
void GLCD_Linea(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char color)
{
	if (x1 == x2)	//Si se trata de una línea vertical, llamamos a la función GLCDLineaVertRapida
		GLCD_LineaVertRapida(x1,y1,y2,color);
	else	//Sino, trazamos una línea de dirección arbitraria punto por punto, pero es más lento
		GLCD_LineaPuntoAPunto(x1,y1,x2,y2,color);	
} //Fin GLCD_Linea()

/* Función GLCD_Rectangulo ----------------------------------------------------------------
Descripción: función que dibuja un rectángulo.
Entrada: 
	x: coordenada x del punto inferior izquierdo del rectángulo
	y: coordenada y del punto inferior izquierdo del rectángulo
	ancho: ancho del rectángulo
	alto: alto del rectángulo
	color: color del rectángulo
Salida: nada
------------------------------------------------------------------------------------------*/
void GLCD_Rectangulo(unsigned char x, unsigned char y, unsigned char ancho,
											unsigned char alto, unsigned char color)
{
  if (ancho != 0)
		ancho--;
	if (alto != 0)
		alto--;

	GLCD_Linea(x, y, x+ancho, y, color);
	GLCD_Linea(x, y, x, y + alto, color);
	GLCD_Linea(x, y+alto, x+ancho, y+alto, color);
	GLCD_Linea(x+ancho, y, x+ancho, y+alto, color);	
} //Fin GLCD_Rectangulo()

/* Función GLCD_Relleno -------------------------------------------------------------------
Descripción: función que dibuja un rectángulo relleno.
Entrada: 
	x: coordenada x del punto inferior izquierdo del rectángulo relleno
	y: coordenada y del punto inferior izquierdo del rectángulo relleno
	ancho: ancho del rectángulo relleno
	alto: alto del rectángulo relleno
	color: color del rectángulo relleno
Salida: nada
------------------------------------------------------------------------------------------*/
void GLCD_Relleno(unsigned char x, unsigned char y, unsigned char ancho,
									unsigned char alto, unsigned char color)
{
	//unsigned char iGLCDR;

	if (ancho != 0)
		ancho--;
	if (alto != 0)
		alto--;
	
	if (ancho == 0)
	{
		for(iGLCDR=y;iGLCDR <= (y + alto);iGLCDR++) 
			GLCD_Punto(x - 1,iGLCDR,color);
	}
	else
 		for(iGLCDR=x;iGLCDR <= (x + ancho);iGLCDR++) 
			GLCD_Linea(iGLCDR,y,iGLCDR,y + alto, color);
} //Fin GLCD_Relleno()

/*Función GLCD_AnchoLetra ---------------------------------------------------------------------------------------
Descripción: identifica el ancho, en pixeles, que tiene una letra
Entrada: 
	textptr (char*): puntero a la letra que se debe analizar
	size (unsigned char): indica el tipo de letra a analizar
Salida: número de columnas (píxeles) que posee la letra
---------------------------------------------------------------------------------------------------------------------*/
unsigned char GLCD_AnchoLetra(char ptrChar, unsigned char size)
{
	if(size == 0) // Pregunta si la letra, sin excepciones es de 3x5
	{
		if(ptrChar < 'S') 		// Pregunta si la letra entra en el primer array
		{
			calcFilaAL = ptrChar - ' ';
			if((TEXT_3X5_1[calcFilaAL][0] & 0x80) == 0x80) // Pregunta si la letra es una excepcion
			{
				switch (TEXT_3X5_1[calcFilaAL][2] & 0xF0)
				{
					case 0x10: // es una letra de 5x5
						return 5;	
						break;
					case 0x20: // es una letra de 4x5
						return 4;	
						break;
				}
			}
			else // No tiene excepciones => es una letra de 3x5
				return 3;
		}	
		else 
		{
			if(ptrChar <= '~') // Pregunta si la letra entra en el segundo array
			{
				calcFilaAL = ptrChar - 'S';
				if((TEXT_3X5_2[calcFilaAL][0] & 0x80) == 0x80) // Pregunta si la letra es una excepcion
				{
					switch (TEXT_3X5_2[calcFilaAL][2] & 0xF0)
					{
						case 0x10: // es una letra de 5x5
							return 5;	
							break;
						case 0x20: // es una letra de 4x5
							return 4;	
							break;
					}
				}
				else // No tiene excepciones => es una letra de 3x5
					return 3;
			}
			else // letra que no pertenece a la matriz de caracteres
				return 3;	// Default to space
		}	
	}
	else // La letra, sin excepciones es de 5x7
	{
		if(ptrChar < 'S') 		// Pregunta si la letra entra en el primer array
		{
			calcFilaAL = ptrChar - ' ';
			if((TEXT_5X7_1[calcFilaAL][0] & 0x80) == 0x80) // Pregunta si la letra es una excepcion
			{
				switch (TEXT_5X7_1[calcFilaAL][2] & 0xF0)
				{
					case 0x10: // es una letra de 3x7
						return 3;	
						break;
					case 0x20: // es una letra de 4x7
						return 4;	
						break;
				}
			}
			else // No tiene excepciones => es una letra de 5x7
				return 5;
		}	
		else 
		{
			if(ptrChar <= '~') // Pregunta si la letra entra en el segundo array
			{
				calcFilaAL = ptrChar - 'S';
				if((TEXT_5X7_2[calcFilaAL][0] & 0x80) == 0x80) // Pregunta si la letra es una excepcion
				{
					switch (TEXT_5X7_2[calcFilaAL][2] & 0xF0)
					{
						case 0x10: // es una letra de 3x7
							return 3;	
							break;
						case 0x20: // es una letra de 4x7
							return 4;	
							break;
					}
				}
				else // No tiene excepciones => es una letra de 5x7
					return 5;
			}
			else // letra que no pertenece a la matriz de caracteres
				return 5;	// Default to space
		}	
	}
}//Fin GLCD_ContAnchoLetra(char* textptr)

/*Función GLCD_RendString35--------------------------------------------------------------------------------------------
Descripción: función que dibuja una cadena de texto (terminada en NULL) apuntada por textptr con tipo de letra 3x5 y
	excepciones
Entrada: 
	x: coordenada x del punto inferior izquierdo del texto
	y: coordenada y del punto inferior izquierdo del texto
	textptr: puntero a la cadena de texto terminada en NULL
	size: Tamaño del texto
	color: color del texto
Salida: nada
---------------------------------------------------------------------------------------------------------------------*/
void GLCD_RendString35(unsigned char x, unsigned char y, char* textptr, unsigned char color)
{
	//volatile unsigned char iRS35, jRS57, kRS57, uRS57; 	// Indices
	//volatile unsigned char calcFilaRS57;
	//volatile unsigned char calcFila1RS57;
	//volatile unsigned char calcFila2RS57;

	for(iRS35=0; textptr[iRS35] != '\0'; ++iRS35, ++x) // Bucle para tomar letra por letra de la cadena pasada como argumento
	{				
		if(textptr[iRS35] < 'S') 		// Pregunta si la letra entra en el primer array
		{
			calcFilaRS35 = textptr[iRS35]-' ';
			for(uRS35=0; uRS35<3; uRS35++) // Se cargan las columnas de la letra
				pixelData[uRS35] = TEXT_3X5_1[calcFilaRS35][uRS35];
		}
		else 
		{
			if(textptr[iRS35] <= '~') // Pregunta si la letra entra en el segundo array
			{
				//calcFila1RS35 = textptr[iRS35]-'S'-1;
				calcFila2RS35 = textptr[iRS35]-'S';
				/*if (textptr[iRS35] >= 93)
					for(uRS35=0; uRS35<3; uRS35++) // Se cargan las columnas de la letra
						pixelData[uRS35] = TEXT_3X5_2[calcFila1RS35][uRS35];
				else*/
					for(uRS35=0; uRS35<3; uRS35++) // Se cargan las columnas de la letra
						pixelData[uRS35] = TEXT_3X5_2[calcFila2RS35][uRS35];
			}
			else
				for(uRS35=0; uRS35<3; uRS35++)
					pixelData[uRS35] = TEXT_3X5_1[0][uRS35];   		// Default to space
		}
		
		if((pixelData[0] & 0x80) != 0) // Pregunta si la letra es una excepcion
		{
			if((pixelData[2] & 0xF0) == 0x10) // Pregunta si son letras de 5x5
			{
				calcFilaRS35 = pixelData[2] & 0x0F; // Calculo la Fila de la excepcion
				for(uRS35=0; uRS35<3; uRS35++)
					pixelData[2 + uRS35] = TEXT_3X5_E1[calcFilaRS35][uRS35]; // Se cargan las excepciones
				
				// Grafico la letra 5x5
				for(jRS35=0; jRS35<5; ++jRS35, x++)       // Loop through character byte data
					for(kRS35=0; kRS35<5; ++kRS35)          // Loop through the vertical pixels
						if(BitTest(pixelData[jRS35], kRS35)) 	// Check if the pixel should be set
							GLCD_Punto(x, y-kRS35, color); 			// Draws the pixel
							/*for(lRS35=0; lRS35<1; ++lRS35)      	// The next two loops change the character's size                    
								for(mRS35=0; mRS35<1; ++mRS35)
									GLCD_Punto(x+mRS35, y-kRS35+lRS35, color); // Draws the pixel
							*/
			}
			else if((pixelData[2] & 0xF0) == 0x20) // Pregunta si son letras 4x5
			{
				calcFilaRS35 = pixelData[2] & 0x0F; // Calculo la Fila de la excepcion
				for(uRS35=0; uRS35<2; uRS35++)
					pixelData[2 + uRS35] = TEXT_3X5_E2[calcFilaRS35][uRS35]; // Se cargan las excepciones
						
				// Grafico la letra 4x5
				for(jRS35=0; jRS35<4; ++jRS35, x++)       // Loop through character byte data
					for(kRS35=0; kRS35<5; ++kRS35)          // Loop through the vertical pixels
						if(BitTest(pixelData[jRS35], kRS35)) 	// Check if the pixel should be set
							GLCD_Punto(x, y-kRS35, color); 			// Draws the pixel
							/*for(lRS35=0; lRS35<1; ++lRS35)      	// The next two loops change the character's size                    
								for(mRS35=0; mRS35<1; ++mRS35)
									GLCD_Punto(x+mRS35, y-kRS35+lRS35, color); // Draws the pixel
							*/
			}
		}
		else
			for(jRS35=0; jRS35<3; ++jRS35, x++)       // Loop through character byte data
				for(kRS35=0; kRS35<5; ++kRS35)          // Loop through the vertical pixels
					if(BitTest(pixelData[jRS35], kRS35)) 	// Check if the pixel should be set
						GLCD_Punto(x, y-kRS35, color); 			// Draws the pixel
						/*for(lRS35=0; lRS35<1; ++lRS35)      	// The next two loops change the character's size                    
							for(mRS35=0; mRS35<1; ++mRS35)
								GLCD_Punto(x+mRS35, y-kRS35+lRS35, color); // Draws the pixel
						*/
	}
} //Fin GLCD_RendString35()

/*Función GLCD_RendString57------------------------------------------------------------------------------------------------------------------------
Descripción: función que renderiza graficamente (dibuja) una cadena de texto (terminada en NULL) apuntada por textptr. El tamanio del texto si size=1 será 5x7
Entrada: 
	x: coordenada x del punto inferior izquierdo del texto
	y: coordenada y del punto inferior izquierdo del texto
	textptr: puntero a la cadena de texto terminada en NULL
	size: Tamaño del texto
	color: color del texto
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void GLCD_RendString57(unsigned char x, unsigned char y, char* textptr, unsigned char size, unsigned char color)
{
	/*volatile unsigned char iRS57, jRS57, kRS57, lRS57, mRS57, uRS57;               			// Indices
	volatile unsigned char calcFilaRS57;
	volatile unsigned char calcFila1RS57;
	volatile unsigned char calcFila2RS57;*/
	
	for(iRS57=0; textptr[iRS57] != '\0'; ++iRS57, ++x) // Bucle para tomar letra por letra de la cadena pasada como argumento
  {					
		if(textptr[iRS57] < 'S') 							// Checkea si la letra entra en el primer array
		{
			calcFilaRS57 = textptr[iRS57]-' ';
			for(uRS57=0; uRS57<5; uRS57++)
				pixelData[uRS57] = TEXT_5X7_1[calcFilaRS57][uRS57];
		}
		else 
		{
			if(textptr[iRS57] <= '~') 				// Checkea si la letra entra en el segundo array
			{
		 		//calcFila1RS57 = textptr[iRS57]-'S'-1;
				calcFila2RS57 = textptr[iRS57]-'S';
				/*if (textptr[iRS57] >= 93)
					for(uRS57=0; uRS57<5; uRS57++) // Se cargan las columnas de la letra
						pixelData[uRS57] = TEXT_5X7_2[calcFila1RS57][uRS57];
				else*/
					for(uRS57=0; uRS57<5; uRS57++) // Se cargan las columnas de la letra
						pixelData[uRS57] = TEXT_5X7_2[calcFila2RS57][uRS57];
			}
			else
		  	for(uRS57=0; uRS57<5; uRS57++)
					pixelData[uRS57] = TEXT_5X7_1[0][uRS57];   		// Default to space
		}
		
		for(jRS57=0; jRS57<5; ++jRS57, x+=size)       // Loop through character byte data
			for(kRS57=0; kRS57<7*size; ++kRS57)         // Loop through the vertical pixels
				if(BitTest(pixelData[jRS57], kRS57)) 			// Check if the pixel should be set
					for(lRS57=0; lRS57<size; ++lRS57)      	// The next two loops change the character's size                    
						for(mRS57=0; mRS57<size; ++mRS57)
							GLCD_Punto(x+mRS57, y-kRS57*size+lRS57, color); // Draws the pixel
	}
} //Fin GLCD_RendString57()


/*Función GLCD_String ------------------------------------------------------------------------------------------------------------------------
Descripción: selecciona el tipo de letra que se debe dibujar según el tamaño
Entrada: 
	x: coordenada x del punto inferior izquierdo del texto
	y: coordenada y del punto inferior izquierdo del texto
	textptr: puntero a la cadena de texto terminada en NULL
	size: Tamaño del texto
	color: color del texto
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void GLCD_String(unsigned char x, unsigned char y, char* ptrText, unsigned char size, unsigned char color)
{
	if(size == 0)
		GLCD_RendString35(x, y, ptrText, color);
	else
		GLCD_RendString57(x, y, ptrText, size, color);
} //Fin GLCD_String
