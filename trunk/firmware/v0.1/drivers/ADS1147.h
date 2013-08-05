#ifndef ADQUISICIONADS1147_H
#define ADQUISICIONADS1147_H
#include "globals.h"
#include <os_cpu.h>

//Registros del ADS1147
#define MUX0 		0x00
#define VBIAS 	0x01
#define MUX1 		0x02
#define SYS0 		0x03
#define OFC0 		0x04
#define OFC1 		0x05
#define OFC2 		0x06
#define FSC0 		0x07
#define FSC1 		0x08
#define FSC2 		0x09
#define IDAC0 	0x0A
#define IDAC1 	0x0B
#define GPIOCFG 0x0C
#define GPIODIR 0x0D
#define GPIODAT 0x0E

//Corrientes de BurnOut
#define BOC_OFF		0
#define BOC_05UA	1
#define BOC_2UA		2
#define BOC_10UA	3

//Entradas
#define AIN0	0
#define AIN1	1
#define AIN2	2
#define AIN3	3

#define CANAL0_POS_IN	AIN0
#define CANAL0_NEG_IN	AIN1

#define CANAL1_POS_IN	AIN2
#define CANAL1_NEG_IN	AIN3


//Canales
#define CANAL_0		0
#define CANAL_1		1
#define CANAL_2		2
#define CANAL_3		3

#define CANAL_TEMP		CANAL_0
#define CANAL_CONDUC	CANAL_1

//Entradas y Voltages de Polarización VBIAS
#define VBIAS_AIN0	1
#define VBIAS_AIN1	2
#define VBIAS_AIN2	4
#define VBIAS_AIN3	8

//Referencia Interna
#define ALWAYS_OFF	0
#define ALWAYS_ON		1
#define ON_OFF			2

//Referencia
#define REF0					0
#define REF1					1
#define REF_INT				2
#define REF_INT_REF0	3

//System Monitor
#define NORMAL			0
#define OFFSET			1
#define GAIN				2
#define TEMPERATURE	3
#define EXT_REF1		4
#define EXT_REF0		5
#define AVDD				6
#define DVDD				7

//PGA gains
#define GAIN_1			0
#define GAIN_2			1
#define GAIN_4			2
#define GAIN_8			3
#define GAIN_16			4
#define GAIN_32			5
#define GAIN_64			6
#define GAIN_128		7

//Frecuencia de Muestreo
#define SPS_5				0
#define SPS_10			1
#define SPS_20			2
#define SPS_40			3
#define SPS_80			4
#define SPS_160			5
#define SPS_320			6
#define SPS_640			7
#define SPS_1000		8
#define SPS_2000		9

//IDACX Current
#define IDAC_OFF		0
#define IDAC_50U		1
#define IDAC_100U		2
#define IDAC_250U		3
#define IDAC_500U		4
#define IDAC_750U		5
#define IDAC_1000U	6
#define IDAC_1500U	7

//IDACX Output pin
#define IDAC_AIN0		0
#define IDAC_AIN1		1
#define IDAC_AIN2		2
#define IDAC_AIN3		3
#define IDAC_DISCON	12

#define CS_PIN         	PORTBbits.RB6      // Chip Select
#define CS_ADC_PIN			CS_PIN
#define TRIS_CS_PIN    	TRISBbits.TRISB6
#define DIN_PIN        	PORTCbits.RC1     // Data in
#define TRIS_DIN_PIN   	TRISCbits.TRISC1
#define DOUT_PIN       	PORTCbits.RC0    // Data out
#define TRIS_DOUT_PIN  	TRISCbits.TRISC0
#define SCK_PIN        	PORTCbits.RC2     // Clock
#define TRIS_SCK_PIN   	TRISCbits.TRISC2
#define START_PIN				PORTBbits.RB7			// pata para iniciar la converción
#define TRIS_START_PIN	TRISBbits.TRISB7
#define DRDY_PIN				PORTBbits.RB5			// pata para avisar cuando la conversión esté lista 
#define TRIS_DRDY_PIN		TRISBbits.TRISB5
#define DRDY_IE					CNEN2bits.CN27IE	//Habilitación de la interrupción de DRDY
#define DRDY_IF					IFS1.CNIF					//Flag de interrupción de DRDY
#define DRDY_IP					IPC4.CNIP					//Prioridad de interrupción de DRDY
#define DRDY_EDGE				INTCON2bits.INTEDG2	//Flanco de interrupción de DRDY
#define RESET_PIN				PORTCbits.RC5			// pata para resetear ADS1147
#define TRIS_RESET_PIN	TRISCbits.TRISC5

#define	SPISTAT	SPI1STAT
#define	SPICON1	SPI1CON1
#define	SPICON2	SPI1CON2
#define	SPIBUF	SPI1BUF
#define	SPIIF		IFS0bits.SPI1IF
#define	SPISMP	SPI1CON1bits.SMP
#define	SPICKE	SPI1CON1bits.CKE
#define	SPICKP	SPI1CON1bits.CKP
#define	SPIEN		SPI1STATbits.SPIEN
#define	SPIRBF	SPI1STATbits.SPIRBF

#define   SYNC_MODE_TIMER2  0x03	// Description: This macro is used to initialize a PIC18 SPI module with the TIMER 2.

#define OFFSET_ADC 0

//Constantes
#define VOLTIOS_REF_INT					2.048
#define CUENTAS_16_BITS					65536
#define	CUENTAS_15_BITS					32768
#define	VOLTIOS_25GRADOS						0.118
#define	VOLTIOS_POR_GRADO_SYS_MON		0.000405
#define VOLTIOS_POR_BIT_REF_INT	((float) VOLTIOS_REF_INT / (float) CUENTAS_15_BITS)
#define VAL_MAX_BITS						930
#define VAL_MIN_BITS						83
//#define	VOLTIOS_POR_BIT					((float) VOLTIOS_REF_2048 / (float) BITS_AD16BITS)

//Timeouts (tiempo límite) en milisegundos
#define TIMEOUT_CALIB_INTER	4000	//Timeout de la calibración interna del ADS1147
#define TIMEOUT_MUESTREO		4000	//Timeout del muestreo del ADS1147

//Funciones del AD
#define WakeUpCmdADC(); WriteSPI1(0x01);	//Despertar al  ADC
//#define StartHighADC(); START_PIN = 1;	//Llevar a 1 el START (que equivale a hacer que el ADC se despierte)
//#define StartLowADC(); START_PIN = 0;	//Llevar a 0 el START (que equivale a hacer que el ADC se duerma)
#define SleepADC(); START_PIN = 1; WriteSPI1(0x02); START_PIN = 0;	//Dormir al ADC
#define ResetADC();	START_PIN = 1; WriteSPI1(0x06); START_PIN = 0;	//Resetear ADC
#define NopADC();	WriteSPI1(0xFF);	//No Operation
#define ReadOnceADC(); WriteSPI1(0x12);	//Leer el valor de la última conversión del ADC
#define ReadContADC(); WriteSPI1(0x14);	//Leer el valor de las conversiones continuamente
#define StopReadContADC(); WriteSPI1(0x16);	//Terminar de leer el valor de las conversiones continuamente
#define SysOCalADC();	START_PIN = 1; WriteSPI1(0x60); START_PIN = 0;	//Calibra el Offset del sistema
#define SysGCalADC();	START_PIN = 1; WriteSPI1(0x61); START_PIN = 0;	//Calibra la ganancia del sistema
#define SelfOCalADC(); START_PIN = 1;	WriteSPI1(0x62); START_PIN = 0;	//Calibra el Offset del ADC

#define SelecADC(); CS_ADC_PIN = 0;	//Selecciona (mediante el CS) el ADC para comunicación SPI 
#define DeselecADC(); CS_ADC_PIN = 1;	//Deselecciona (mediante el CS) el ADC para comunicación SPI 


//Estructuras
struct ADConverter{

	unsigned canal				:2;				//Indica el canal desde el cual se tomó la última muestra
	unsigned estadoSysMon	:3;				//Indica en que "modo" se encuentra el System Monitor del ADS1147
	signed long int sumaMuestras;	//Acumula la suma de las muestras parciales
	unsigned char contMuestras;			//Indica la cantidad de muestras parciales que han sido adquiridas
	unsigned char nroMuestras;			//Número de muestras promediadas
	signed int offset;							//Offset medido durante la calibración
	uint16_t valorTemp;						//Valor de la última muestra del ADC 
	signed int signedValor;					//Valor promedio de nroMuestras muestras parciales con signo
	float voltage;									//Variable auxiliar para calcular el voltage diferencial en la entrada
	unsigned int unsignedValor;			//Valor promedio de nroMuestras muestras parciales sin signo
	unsigned int timeout;						//Timeout en milisegundos
	unsigned char tempAmb;			//Temperatura interna del ADC

	INT16S 	offsetADC;
	INT8U		gainADC;

	//unsigned bEsperandoMedida:1;	//Indica que se está haciendo una espera por polling en el main,  
																	//por lo tanto las conversiones deben gatillarse desde la interrupción
																	//y no desde el proceso de adquisición
	unsigned bCalibrando	:1;				//Indica que el ADC está en proceso de calibración interna
	unsigned bMuestreando	:1;				//Indica que el ADC está en proceso de muestreo
	unsigned bCalibInter	:1;				//Indica si el ADC está (1) o no está (0) calibrado internamente
	unsigned bErrorTimeout:1;				//Indica si el ADC tardó demasiado en responder o no respondió a la solicitud de muestreo
	unsigned bLibre				:1;				//Indica si el AD esta  siendo usado (0) por algún proceso o no (1)
	unsigned bMuestraLista:1;				//Indica si está disponible (1) una nueva muestra
	unsigned bValorListo 	:1;				//Indica si ya se completo la adquisición de "nroMuestras" muestras y se calculó su promedio
																	//guardando el resultado en "valor"
	
};

//Variables
extern volatile struct ADConverter adc;
extern unsigned char backUpSSPSTAT;	//Variables para salvar temporalmente el estado de este reg y luego restaurarlo
extern unsigned char backUpSSPCON1;	//Variables para salvar temporalmente el estado de este reg y luego restaurarlo

//PROTOTIPOS
unsigned char WriteSpiADC( unsigned char data_out );
unsigned char ReadSpiADC( void );
void WriteRegADC(unsigned char reg, unsigned char dato);
void WriteRegsADC(unsigned char reg, unsigned char n);
unsigned char ReadRegADC(unsigned char reg);
void ReadRegsADC(unsigned char reg, unsigned char n);
void IniciarMuestra(void);
void TomarMuestra(void);
void LeerMuestraADC(void);
void SetBurnOutCurrent(unsigned char burnOutCurrent);
void SetPosIn(unsigned char PosIn);
void SetNegIn(unsigned char NegIn);
void SetFuenteConv(unsigned char canal);
void ConfRefInt(unsigned char RefInt);
void SetRef(unsigned char Ref);
void SetSystemMonitor(unsigned char estadoSysMon);
void SetPGAGain(unsigned char gain);
void SetFrecMuestreo(unsigned char frec);
void SetIDACCurrent(unsigned char current);
void SetIDAC1Out(unsigned char pin);
void SetIDAC2Out(unsigned char pin);
void LeerRegistrosADC(void);
void GetOffset();
void CalibrarADC(void);
void GetTempAmb();
void InicConversorAD(void);

#endif //ADQUISICIONADS1147_H

