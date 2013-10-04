#include "adquisicion.h"

//Variables
struct Adquisicion adqui;
struct Ensayo ensayo;

/*Función InicAdquisición------------------------------------------------------------------------------------------------------------------------
Descripción: función que inicializa el módulo de adquisición
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void InicAdquisicion(void)
{
  //Inicialización del módulo de Adquisición
  //ensayo.tipoEnsayo = ENSAYO_NINGUNO;
  ensayo.bEnsayando = 0;
  //adqui.modo = MODO_CALIBRACION;
  adqui.periodoMuestreo = PERIODO_MUESTREO;
  adqui.contMuestreo = 0;
  //adqui.bMuestraLista = 0;
  adqui.bGuardarEnSD = 0;
  adqui.bGuardandoEnSD = 0;
  adqui.bMuestreando = 0;
  adqui.nroMuestra = 1;
}//Fin InicAdquisicion

/*Función ContinuarAdquisicion------------------------------------------------------------------------------------------------------------------------
Descripción: Función que se encarga de adquirir la temperatura y la conductividad, y grabarlas a la SD 
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ContinuarAdquisicion(void)
{
  /*
  if ((adqui.bMuestraLista == 0) && (adqui.bMuestreando == 0))	//¿No se están tomando muestras y no hay muestra lista?
  {
    MedirTempEnBits();
    adqui.bMuestreando = 1;
  }
  else
  {
    if (adqui.bMuestraLista == 0)	//¿Estoy muestreando pero todavía no terminé?
    {
      if (temp.bValorListo == 1) //¿Ya está lista la temperatura?
      {
        if (conduc.bValoresListos == 1) //¿Ya está lista la conductividad?
        {
          adqui.bMuestraLista = 1;
          adqui.bMuestreando = 0;
        }
        else
        {
          if (ADC.bMuestreando == 0)	//¿Aún no empece la muestra de conductividad?
          {
            MedirConducEnBits();	//Lanzamos la muestra de Conductividad
            adqui.bMuestreando = 1;
          }
        }
      }
    }
  }
  */
}// Fin ContinuarAdquisicion()

