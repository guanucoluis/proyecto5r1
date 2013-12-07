#include "FlashMem_cfg.h"
#include "globals.h"
#include "sensores.h"

//Variables de Configuración
//extern struct ConfigdsPIC33 config;
int8_t buffFlash[64*8];	//Buffer temporal para los datos leidos desde la Flash
int8_t flashData[TAMANIO_BLOQUE_BORRADO] __attribute__((space(prog),section("FlashData"),address(BLOQUE_FLASH)));


/*Función GuardarConfigFlash()------------------------------------------------------------------------------------------------------------------------
Descripción: Función que guarda la configuración en la memoria flash
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void GuardarConfigFlash(void)
{
  #if (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
  CPU_SR        cpu_sr;
  #endif

  OS_ENTER_CRITICAL();

  //Indicamos la dirección del bloque de Flash
  config.rtsp.nvmAdru=__builtin_tblpage(&flashData); // NVM = NON VOLATILE MEMORY
  config.rtsp.nvmAdr=__builtin_tbloffset(&flashData);
  config.rtsp.nvmAdrPageAligned = config.rtsp.nvmAdr & 0xFC00;			// Get the Flash Page Aligned address
  config.rtsp.nvmRow=((config.rtsp.nvmAdr>>7) & 7);					// Row in the page
  config.rtsp.nvmSize=64;

  flashPageRead(config.rtsp.nvmAdru, config.rtsp.nvmAdrPageAligned, buffFlash);	//Leemos el bloque de flash y lo almacenamos en buffFlash

  //Modificamos el arreglo con los cambios que queremos aplicar
  config.ptrStruct = (void *) (buffFlash + OFFSET_CONFIG);
  ((struct ConfigdsPIC33*) config.ptrStruct)->luzFondo = config.luzFondo;
  ((struct ConfigdsPIC33*) config.ptrStruct)->contraste = config.contraste;
  ((struct ConfigdsPIC33*) config.ptrStruct)->bDuracionLuzFondo = config.bDuracionLuzFondo;
  ((struct ConfigdsPIC33*) config.ptrStruct)->duracionLuzFondo = config.duracionLuzFondo;

  flashPageErase(config.rtsp.nvmAdru, config.rtsp.nvmAdrPageAligned);	//Borramos  la página que queremos escribir
  flashPageWrite(config.rtsp.nvmAdru, config.rtsp.nvmAdrPageAligned, buffFlash);	//Escribimos la página en Flash con el buffer modificado

  OS_EXIT_CRITICAL();
}// Fin GuardarConfigFlash()

/*Función CargarConfigFlash()------------------------------------------------------------------------------------------------------------------------
Descripción: Función que setea el valor de los parámetros de configuración cargándolos desde la Memoria Flash
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void CargarConfigFlash(void)
{
  #if (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
  CPU_SR        cpu_sr;
  #endif

  OS_ENTER_CRITICAL();

	//Indicamos la dirección del bloque de Flash
  config.rtsp.nvmAdru=__builtin_tblpage(&flashData);
  config.rtsp.nvmAdr=__builtin_tbloffset(&flashData);
  config.rtsp.nvmAdrPageAligned = config.rtsp.nvmAdr & 0xFC00;			// Get the Flash Page Aligned address
  config.rtsp.nvmRow=((config.rtsp.nvmAdr>>7) & 7);					// Row in the page
  config.rtsp.nvmSize=64;

  flashPageRead(config.rtsp.nvmAdru, config.rtsp.nvmAdrPageAligned, buffFlash);	//Leemos el bloque de flash y lo almacenamos en buffFlash

  //Modificamos el arreglo con los cambios que queremos aplicar
  config.ptrStruct = (void *) (buffFlash + OFFSET_CONFIG);
  config.luzFondo = ((struct ConfigdsPIC33*) config.ptrStruct)->luzFondo;
  config.contraste = ((struct ConfigdsPIC33*) config.ptrStruct)->contraste;
  config.bDuracionLuzFondo = ((struct ConfigdsPIC33*) config.ptrStruct)->bDuracionLuzFondo;
  if (((struct ConfigdsPIC33*) config.ptrStruct)->duracionLuzFondo != 0xFFFF)
    config.duracionLuzFondo = ((struct ConfigdsPIC33*) config.ptrStruct)->duracionLuzFondo;
  else
    config.duracionLuzFondo = DUR_LUZ_FONDO_DEF;
    

  OS_EXIT_CRITICAL();
}// Fin CargarConfigFlash()()

/*Función GuardarParametros------------------------------------------------------------------------------------------------------------------------
Descripción: función que guarda el arreglo de parámetros en la Flash
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void GuardarParametros(void)
{
	uint8_t iGP;	//Índice del for

  #if (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
  CPU_SR        cpu_sr;
  #endif

  OS_ENTER_CRITICAL();

  //Indicamos la dirección del bloque de Flash
  config.rtsp.nvmAdru=__builtin_tblpage(&flashData);
  config.rtsp.nvmAdr=__builtin_tbloffset(&flashData);
  config.rtsp.nvmAdrPageAligned = config.rtsp.nvmAdr & 0xFC00;			// Get the Flash Page Aligned address
  config.rtsp.nvmRow=((config.rtsp.nvmAdr>>7) & 7);					// Row in the page
  config.rtsp.nvmSize=64;

  flashPageRead(config.rtsp.nvmAdru, config.rtsp.nvmAdrPageAligned, buffFlash);	//Leemos el bloque de flash y lo almacenamos en buffFlash

  //Modificamos el arreglo con los cambios que queremos aplicar
  config.ptrStruct = (void *) (buffFlash + OFFSET_PARAMETROS);
  for (iGP=0;iGP < CANT_GRUP_PARAM; iGP++)
  {
    //Actualizamos la estructura
    ((struct GrupoDeParam *) config.ptrStruct)->diametros[iGP].diametroTrac = param.diametros[iGP].diametroTrac;
    ((struct GrupoDeParam *) config.ptrStruct)->diametros[iGP].diametroNoTrac = param.diametros[iGP].diametroNoTrac;
  }

  flashPageErase(config.rtsp.nvmAdru, config.rtsp.nvmAdrPageAligned);	//Borramos  la página que queremos escribir
  flashPageWrite(config.rtsp.nvmAdru, config.rtsp.nvmAdrPageAligned, buffFlash);	//Escribimos la página en Flash con el buffer modificado

  param.bParamCargadosDesdeFlash = 1;	//Indicamos que los  parametros  ya han sido cargados

  OS_EXIT_CRITICAL();
} //Fin GuardarParametros()

/*Función CargarParametros------------------------------------------------------------------------------------------------------------------------
Descripción: función que actualiza el arreglo de parámetros según lo que lee desde la Flash
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void CargarParametros(void)
{
  uint8_t iCParam;	//Índice del for
  
  //unsigned char iCParam;	//Índice del for
  #if (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
  CPU_SR        cpu_sr;
  #endif

  OS_ENTER_CRITICAL();

  //Indicamos la dirección del bloque de Flash
  config.rtsp.nvmAdru=__builtin_tblpage(&flashData);
  config.rtsp.nvmAdr=__builtin_tbloffset(&flashData);
  config.rtsp.nvmAdrPageAligned = config.rtsp.nvmAdr & 0xFC00;			// Get the Flash Page Aligned address
  config.rtsp.nvmRow=((config.rtsp.nvmAdr>>7) & 7);					// Row in the page
  config.rtsp.nvmSize=64;

  flashPageRead(config.rtsp.nvmAdru, config.rtsp.nvmAdrPageAligned, buffFlash);	//Leemos el bloque de flash y lo almacenamos en buffFlash

  //Modificamos el arreglo con los cambios que queremos aplicar
  config.ptrStruct = (void *) (buffFlash + OFFSET_PARAMETROS);
  for (iCParam=0;iCParam < CANT_GRUP_PARAM; iCParam++)
  {
    //Actualizamos la estructura
    if (((struct GrupoDeParam *) config.ptrStruct)->diametros[iCParam].diametroTrac != 0xFFFF)
      param.diametros[iCParam].diametroTrac = ((struct GrupoDeParam *) config.ptrStruct)->diametros[iCParam].diametroTrac;
    else
      param.diametros[iCParam].diametroTrac = DIAMETRO_TRAC_DEFECTO;

    if (((struct GrupoDeParam *) config.ptrStruct)->diametros[iCParam].diametroNoTrac != 0xFFFF)
      param.diametros[iCParam].diametroNoTrac = ((struct GrupoDeParam *) config.ptrStruct)->diametros[iCParam].diametroNoTrac;
    else
      param.diametros[iCParam].diametroNoTrac = DIAMETRO_NO_TRAC_DEFECTO;
  }
  param.bParamCargadosDesdeFlash = 1;	//Indicamos que los  parametros  ya han sido cargados

  OS_EXIT_CRITICAL();
} //Fin CargarParametros()

/*Función GuardarTarar------------------------------------------------------------------------------------------------------------------------
Descripción: función que guarda el valor de la Tara en la Flash
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void GuardarTarar(void)
{
  #if (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
  CPU_SR        cpu_sr;
  #endif

  OS_ENTER_CRITICAL();

  //Indicamos la dirección del bloque de Flash
  config.rtsp.nvmAdru=__builtin_tblpage(&flashData);
  config.rtsp.nvmAdr=__builtin_tbloffset(&flashData);
  config.rtsp.nvmAdrPageAligned = config.rtsp.nvmAdr & 0xFC00;			// Get the Flash Page Aligned address
  config.rtsp.nvmRow=((config.rtsp.nvmAdr>>7) & 7);					// Row in the page
  config.rtsp.nvmSize=64;

  flashPageRead(config.rtsp.nvmAdru, config.rtsp.nvmAdrPageAligned, buffFlash);	//Leemos el bloque de flash y lo almacenamos en buffFlash

  //Modificamos el arreglo con los cambios que queremos aplicar
  config.ptrStruct = (void *) (buffFlash + OFFSET_TARA);
	
	config.ptrStruct = celdaDeCarga.tara;
  
  flashPageErase(config.rtsp.nvmAdru, config.rtsp.nvmAdrPageAligned);	//Borramos  la página que queremos escribir
  flashPageWrite(config.rtsp.nvmAdru, config.rtsp.nvmAdrPageAligned, buffFlash);	//Escribimos la página en Flash con el buffer modificado

  OS_EXIT_CRITICAL();
} //Fin GuardarTarar()

/*Función CargarParametros------------------------------------------------------------------------------------------------------------------------
Descripción: función que actualiza el valor de la Tara según lo que lee desde la Flash
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void CargarTarar(void)
{
  //unsigned char iCParam;	//Índice del for
  #if (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
  CPU_SR        cpu_sr;
  #endif

  OS_ENTER_CRITICAL();

  //Indicamos la dirección del bloque de Flash
  config.rtsp.nvmAdru=__builtin_tblpage(&flashData);
  config.rtsp.nvmAdr=__builtin_tbloffset(&flashData);
  config.rtsp.nvmAdrPageAligned = config.rtsp.nvmAdr & 0xFC00;			// Get the Flash Page Aligned address
  config.rtsp.nvmRow=((config.rtsp.nvmAdr>>7) & 7);					// Row in the page
  config.rtsp.nvmSize=64;
	
  flashPageRead(config.rtsp.nvmAdru, config.rtsp.nvmAdrPageAligned, buffFlash);	//Leemos el bloque de flash y lo almacenamos en buffFlash

  //Modificamos el arreglo con los cambios que queremos aplicar
  config.ptrStruct = (void *) (buffFlash + OFFSET_TARA);
  if (((uint16_t *) config.ptrStruct) != 0xFFFF)
    celdaDeCarga.tara = config.ptrStruct;
  else
	  celdaDeCarga.tara = 0;
  
  OS_EXIT_CRITICAL();
} //Fin CargarTarar()

/*Función GuardarFocos------------------------------------------------------------------------------------------------------------------------
Descripción: Función que almacena los focos de las pantallas en la Memoria Flash
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void GuardarFocos(void)
{
  /*config.address.u24 = BLOQUE_FLASH;	//Cargamos la dirección del bloque con el que queremos trabajar
  FlashBlockRead();	//Leemos el bloque de Flash completo
  //Modificamos el arreglo con los cambios que queremos aplicar
  config.ptrStruct = (void *) (gDataBuffer + OFFSET_FOCOS);
  *((unsigned char*) config.ptrStruct + 0) = formInicio.saveFoco;
  *((unsigned char*) config.ptrStruct + 1) = formEnsayo.saveFoco;
  *((unsigned char*) config.ptrStruct + 2) = formComposite.saveFoco;
  *((unsigned char*) config.ptrStruct + 3) = formEnsayoLibre.saveFoco;
  *((unsigned char*) config.ptrStruct + 4) = formProgramas.saveFoco;
  *((unsigned char*) config.ptrStruct + 5) = formConfig.saveFoco;
  *((unsigned char*) config.ptrStruct + 6) = formConfigEnsayo.saveFoco;
  //NOTA: Antes de realizar una escritura a la mem flash,  se debe borrar el bloque donde se desea escribir
  FlashBlockErase();	//Borramos el bloque de Flash completo
  FlashBlockWrite();	//Escribimos el bloque entero en la Mem Flash*/
}// Fin GuardarFocos()

/*Función CargarFocos------------------------------------------------------------------------------------------------------------------------
Descripción: Función que carga los focos de las pantallas desde la Memoria Flash
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void CargarFocos(void)
{
  //unsigned char iCF;

  /*config.address.u24 = BLOQUE_FLASH;	//Cargamos la dirección del bloque con el que queremos trabajar
  FlashBlockRead();	//Leemos el bloque de Flash completo
  //Cargamos los focos leídos desde la Memoria Flash
  config.ptrStruct = (void *) (gDataBuffer + OFFSET_FOCOS);
  for(iCF=0;iCF<NUM_PANTALLAS-1;iCF++)
    if (*((unsigned char*) config.ptrStruct + iCF) == 255)  //¿Los focos por algún motivo no están inicializados?
      *((unsigned char*) config.ptrStruct + iCF) = 0; //Los inicializamos  a cero por defecto
      formInicio.saveFoco = *((unsigned char*) config.ptrStruct + 0);
      formEnsayo.saveFoco = *((unsigned char*) config.ptrStruct + 1);
      formComposite.saveFoco = *((unsigned char*) config.ptrStruct + 2);
      formEnsayoLibre.saveFoco = *((unsigned char*) config.ptrStruct + 3);
      formProgramas.saveFoco = *((unsigned char*) config.ptrStruct + 4);
      formConfig.saveFoco = *((unsigned char*) config.ptrStruct + 5);
      formConfigEnsayo.saveFoco = *((unsigned char*) config.ptrStruct + 6);
      //NOTA: Antes de realizar una escritura a la mem flash,  se debe borrar el bloque donde se desea escribir*/
}// Fin CargarFocos()

