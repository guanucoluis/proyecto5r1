#ifndef ADQUISICION_H
#define ADQUISICION_H
//#include "globals.h"

//Modos de Adquisicion
#define MODO_ESPERA				0
#define MODO_CALIBRACION	1
#define MODO_CONTINUO			2
#define MODO_PROGRAMADO		3

//Tipos de Ensayo
#define ENSAYO_NINGUNO		0
#define ENSAYO_LIBRE			1
#define ENSAYO_PROGRAMADO	2

#define PERIODO_GRAFICADO				60	//Per�odo, en segundos, con que se grafican los  puntos en el Ensayo Programado
#define	OFFSET_EN_X_DEL_GRAFICO	15	//Cantidad de p�xeles desde el borde izquierdo de la pantalla hasta el comienzo del gr�fico
#define	OFFSET_EN_Y_DEL_GRAFICO	8		//Cantidad de p�xeles desde el borde inferior de la pantalla hasta el comienzo del gr�fico
#define	ALTURA_GRAFICO	48					//Altura en p�xeles del gr�fico
#define RANGO_DE_TEMP	266						//Grados en las ordenadas del gr�fico
#define PIXELES_POR_GRADO	(float) ALTURA_GRAFICO / (float) RANGO_DE_TEMP

//#define	PERIODO_MUESTREO_CALIBRACION 200
#define	PERIODO_MUESTREO_CONTINUO	400
#define	PERIODO_MUESTREO_ENSAYO_LIBRE	1000
#define	PERIODO_MUESTREO_ENSAYO_PROG	1000

//Estructuras
struct Adquisicion{

	unsigned modo						:3;		//Indica el modo en el que se estan tomando los datos
	unsigned bGuardarEnSD		:1;		//Indica si los datos de cada muestra deben ser guardados en la SD
	unsigned bProcesarMuestra:1;		//Bandera que permite procesar los datos a determinados tiempos
	unsigned bMuestreando		:1;		//Indica si el m�dulo se encuentra en proceso de muestreo
	unsigned bMuestraLista	:1;		//Indica si tanto el valor de temperatura como el de Conduc est�n listos
	unsigned bGuardandoEnSD	:1;		//Esta bandera sirve como sem�foro para la SD
	unsigned bGraficarPunto	:1;		//Indica si se debe graficar un nuevo punto en la pantalla
	unsigned bMostrandoConduc:1;	//Indica si en la pantalla de Ensayo Programado se est� mostrando la Conductividad (1) o la Resistencia (0)
	//unsigned bCuentaHabilitada:1;	//Indica si la temperatura est� dentro del rango diferencial y se habilita la cuenta (1) o no (0)

	unsigned char numMedActual;	//Indica el n�mero de medici�n con el que se est� trabajando actualmente
	unsigned int nroMuestra;		//N�mero de la muestra actual

	unsigned int contMuestreo;		//Contador para el per�odo de Muestreo
	unsigned int periodoMuestreo;	//Per�odo de Muestreo

	//Variables de la gr�fica de Ensayo Programado
	unsigned char	contGraficado;	//Contador para el per�odo de graficado de puntos
	unsigned char posX;						//�ndice que almacena la columna de la pantalla donde debemos graficar el nuevo punto
	unsigned char	posY;						//Coordenada en Y del p�xel
};

struct Ensayo{
	unsigned bEnsayando	:1;	//Indica si actualmente se est� realizando un ensayo
	unsigned TipoEnsayo	:2;	//Indica el tipo de ensayo, Libre o Programado

	unsigned int duracion;		//Duraci�n del ensayo libre
};

//Variables
extern struct Adquisicion adqui;
extern struct Ensayo ensayo;

//Prototipos
void InicAdquisicion(void);

#endif //ADQUISICION_H

