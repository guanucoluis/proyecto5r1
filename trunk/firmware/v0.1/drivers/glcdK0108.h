#ifndef GLCD_K0108_H
#define GLCD_K0108_H

//INCLUDES
#include "globals.h"
#include <os_cpu.h>

//DEFINES

/*#define PIN_DISPLAY_ON_OFF	PORTAbits.RA1
#define	LATA_DISPLAY_ON_OFF	LATAbits.LATA1
#define TRIS_DISPLAY_ON_OFF	TRISAbits.RA1
#define	EncenderDisplay();	TRIS_DISPLAY_ON_OFF = 0; PIN_DISPLAY_ON_OFF = 1;	LATA_DISPLAY_ON_OFF = 1;
#define	ApagarDisplay();	TRIS_DISPLAY_ON_OFF = 0; PIN_DISPLAY_ON_OFF = 0;	LATA_DISPLAY_ON_OFF = 0;*/

//Pines de datos del GLCD
#define Puerto_GLCD     PORTD

//Pines de control del GLCD
/*#define GLCD_CS1     PORTCbits.RC0
#define GLCD_CS2     PORTCbits.RC1
#define GLCD_DI      PORTEbits.RE2
#define GLCD_RW      PORTEbits.RE1
#define GLCD_E       PORTEbits.RE0
#define GLCD_RESET   PORTCbits.RC6*/

/*#define GLCD_CS1     PORTEbits.RE3
#define GLCD_CS2     PORTEbits.RE4
#define GLCD_DI      PORTEbits.RE2
#define GLCD_RW      PORTEbits.RE1
#define GLCD_E       PORTEbits.RE0
#define GLCD_RESET   PORTCbits.RC6*/

#define GLCD_CS1     	PORTAbits.RA0
#define	TRIS_GLCD_CS1	TRISAbits.TRISA0
#define GLCD_CS2     	PORTAbits.RA1
#define	TRIS_GLCD_CS2	TRISAbits.TRISA1
#define GLCD_DI      	PORTAbits.RA10
#define TRIS_GLCD_DI  TRISAbits.TRISA10
#define GLCD_RW      	PORTAbits.RA7
#define TRIS_GLCD_RW	TRISAbits.TRISA7
#define GLCD_E       	PORTAbits.RA4
#define	TRIS_GLCD_E		TRISAbits.TRISA4

#define	HabilitarISRs();		SRbits.IPL = 0;	//Habilitar las interrupciones
//#define	HabilitarISRs();		INTCONbits.GIE = 1; //Habilitar las interrupciones
#define DeshabilitarISRs();	SRbits.IPL = 7;	//Deshabilitar las interrupciones
//#define DeshabilitarISRs();	INTCONbits.GIE = 0;		//Deshabilitar las interrupciones

#define	ENTRADA	1
#define	SALIDA	0

//Lados del GLCD
#define GLCD_LADO_CS1   1
#define GLCD_LADO_CS2   0

//Defines relativos al tamaño del texto
#define TEXTO_35					0
#define TEXTO_57_CHICO		1
#define TEXTO_57_MEDIANO	2
#define TEXTO_57_GRANDE		3

//ESTRUCTURAS
struct Display{
	unsigned char offsetX;	//Almacena el desplazamiento relativo en X del display real respecto del virtual
	unsigned char offsetY;	//Almacena el desplazamiento relativo en Y del display real respecto del virtual
	unsigned int ancho;			//Almacena el ancho del display real
	unsigned int alto;			//Almacena el alto del display real
};

//Defines relativos al Display
#define OFFSETX_DISP_REAL	0
#define OFFSETY_DISP_REAL	0
#define	ALTO_DISP_REAL		64
#define	ANCHO_DISP_REAL		128			
#define	NEGRO							1
#define	BLANCO						0
#define	COLOR_FONDO_DEF			BLANCO		//Color de fondo por defecto	
#define	COLOR_TEXTO_DEF			NEGRO			//Color de texto por defecto

//Defines del texto
#define ESPACIO_ASCII		32
#define Z_ASCII					90
#define CERO_ASCII			48
#define NUEVE_ASCII			57
#define	MENOS_ASCII			45

//ARREGLO DE CARACTERES RELATIVO AL DISPLAY
extern const char TEXT_5X7_1[51][5];		
extern const char TEXT_5X7_2[44][5];
extern const char TEXT_3X5_1[51][3];
extern const char TEXT_3X5_2[44][3];
extern char pixelData[5];  					// Guarda los datos del caracter

//typedef unsigned char INT8U;

// VARIABLES DE GLCD_enviaBYTE()
extern volatile unsigned int TrisVal_GeB;

// VARIABLES DE GLCD_leeBYTE()
extern volatile unsigned char Dato_GlB;
extern volatile unsigned int TrisVal_GlB;

// VARIABLES DE GLCD_Listo()
extern volatile unsigned char Status_GL;

// VARIABLES DE GLCD_limpiar()
extern volatile unsigned char i_Gl;
extern volatile unsigned char j_Gl;

// VARIABLES DE GLCD_punto()
extern volatile unsigned char Dato_Gp;
extern volatile unsigned char Lado_Gp;

// VARIABLES DE GLCD_LineaVertRapida()
extern volatile unsigned char Lado_LVR;
extern volatile unsigned char i_LVR;
extern volatile signed char 	PagComp_LVR;
extern volatile unsigned char Byte_LVR;
extern volatile unsigned char Byte1_LVR;
extern volatile unsigned char SIP_LVR;
extern volatile unsigned char SFA_LVR;
extern volatile unsigned char PagInic_LVR;
extern volatile unsigned char PagFin_LVR;

//VARIABLES DEL DISPLAY
extern struct Display DispReal;	


unsigned char GLCD_Listo(char Lado);
void SetearPuertoDatos(INT8U	modo);
void RestaurarPuertoDatos(void);
signed char Abs(signed char Valor);
void BitSet(volatile unsigned char* Dato, char Bit);
void BitClear(volatile unsigned char* Dato, char Bit);
char BitTest(unsigned char Dato, unsigned char n);
void delay(void);
void GLCD_enviaBYTE(char Lado, char Dato);
char GLCD_leeBYTE(char Lado);
unsigned char GLCD_Listo(char Lado);
void GLCD_limpiar(char Color);
void GLCD_Init(char Modo);
void GLCD_Punto(unsigned char x, unsigned char y, unsigned char Color);
unsigned char GLCD_GetColorPunto(unsigned char x, unsigned char y);
void GLCD_LineaVertRapida(unsigned char x, unsigned char y1, unsigned char y2, unsigned char color);
void GLCD_LineaPuntoAPunto(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char color);
void GLCD_Linea(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char color);
void GLCD_Rectangulo(unsigned char x, unsigned char y, unsigned char ancho, unsigned char alto, unsigned char color);
void GLCD_Relleno(unsigned char x, unsigned char y, unsigned char ancho, unsigned char alto, unsigned char color);

unsigned char GLCD_AnchoLetra(char ptrChar, unsigned char size);
void GLCD_RendString35(unsigned char x, unsigned char y, char* textptr, unsigned char color);
void GLCD_RendString57(unsigned char x, unsigned char y, char* textptr, unsigned char size, unsigned char color);
void GLCD_String(unsigned char x, unsigned char y, char* ptrText, unsigned char size, unsigned char color);

#endif //GLCD_K0108_H

