#include "adquisicion.h"

//Variables
struct Adquisicion adqui;
struct Ensayo ensayo;

/*Funci�n InicAdquisici�n------------------------------------------------------------------------------------------------------------------------
Descripci�n: funci�n que inicializa el m�dulo de adquisici�n
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void InicAdquisicion(void)
{
  //Inicializaci�n del m�dulo de Adquisici�n
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

/*Funci�n ContinuarAdquisicion------------------------------------------------------------------------------------------------------------------------
Descripci�n: Funci�n que se encarga de adquirir la temperatura y la conductividad, y grabarlas a la SD 
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ContinuarAdquisicion(void)
{
  /*
  if ((adqui.bMuestraLista == 0) && (adqui.bMuestreando == 0))	//�No se est�n tomando muestras y no hay muestra lista?
  {
    MedirTempEnBits();
    adqui.bMuestreando = 1;
  }
  else
  {
    if (adqui.bMuestraLista == 0)	//�Estoy muestreando pero todav�a no termin�?
    {
      if (temp.bValorListo == 1) //�Ya est� lista la temperatura?
      {
        if (conduc.bValoresListos == 1) //�Ya est� lista la conductividad?
        {
          adqui.bMuestraLista = 1;
          adqui.bMuestreando = 0;
        }
        else
        {
          if (ADC.bMuestreando == 0)	//�A�n no empece la muestra de conductividad?
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

