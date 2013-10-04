#include <interfaz_cfg.h>
#include "interfaz.h"
#include "teclado.h"

//Variables de ButtonOnKeyPress()
unsigned char iBOKP;

/*Función OnKeyPress------------------------------------------------------------------------------------------------------------------------
Descripción: evento ejecutado cuando se pulsa una tecla
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void OnKeyPress()
{
  if (config.bDuracionLuzFondo == 1) //¿La duracción para la luz de fondo está habilitada?
  {
    config.contLuzFondo = 0;
    SetLuzFondo();	//Seteamos de nuevo la luz de fondo
  }
}	//end OnKeyPress()


/*Función ButtonOnKeyPress------------------------------------------------------------------------------------------------------------------------
Descripción: evento ejecutado cuando se pulsa una tecla mientras el Button n tiene el foco 
Entrada: 
		ptrButton: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ButtonOnKeyPress()
{
  //unsigned char iBOKP;

  //ComportamientoPropioButton();

  switch (teclado.teclaPulsada)
  {
    case TECLA_ACEPTAR:
      //dependiendo de donde esté el foco voy a realizar una acción determinada
      switch(pantallaActual)
      {
        case PANTALLA_INICIO:
          switch(indFoco)
          {
            case 0: //Botón 'Mediciones'
							adqui.bMuestreando = 1; //Comenzamos el muestreo de velocidades y fuerza
              CambiarPantalla(PANTALLA_MEDICIONES);

              //se reanudan las tareas que se ultilizaran en la pantalla de Mediciones
              OSTaskResume(TAREA_SD_PRIO);
              OSTaskResume(TAREA_ADQUISICION_PRIO);
              OSTaskResume(TAREA_CELDA_DE_CARGA_PRIO);
              OSTaskResume(TAREA_SENS_VEL_PRIO);
              OSTaskResume(TAREA_REFRESCO_PRIO);
            break;
            case 1: //Botón 'Tarar'
							adqui.bMuestreando = 1; //Comenzamos el muestreo de velocidades y fuerza
							CambiarPantalla(PANTALLA_TARAR);

							//se reanudan las tareas que se ultilizaran en la pantalla de Mediciones
              OSTaskResume(TAREA_ADQUISICION_PRIO);
              OSTaskResume(TAREA_CELDA_DE_CARGA_PRIO);
              OSTaskResume(TAREA_REFRESCO_PRIO);
            break;
            case 2: //Botón 'Parametros'
              if (param.bParamCargadosDesdeFlash == 0)	//¿Todavía no fueron cargados los parámetros desde la Flash?
                CargarParametros();	//Actualizamos el arreglo de Parámetros
              vPSpinEdits[9].valor.word = param.iGdP;	//Seteamos el grupo de parámetros actual
              vPSpinEdits[10].valor.word = param.diametros[param.iGdP].diametroTrac;	//Seteamos el diámetro de Tracción
              vPSpinEdits[11].valor.word = param.diametros[param.iGdP].diametroNoTrac;	//Seteamos el diámetro de No Tracción
              //Cargamos la pantalla
              CambiarPantalla(PANTALLA_PARAMETROS);
            break;
            case 3: //Botón 'Configuración'
              //Actualizamos los ProgBars según los valores de Luz de Fondo y Contraste
              vPProgBars[0].progPorcent = (unsigned char) ((float) config.luzFondo * 100 / (float) 15);
              vPProgBars[1].progPorcent = (unsigned char) ((float) config.contraste * 100 / (float) 15);
              //Actualizamos  el SpinEdit "TIEMPO LUZ FONDO:"
              vPSpinEdits[12].valor.word = config.duracionLuzFondo;
              //Actualizamos  el CheckBox "TIEMPO LUZ FONDO:"
              formConfig.ptrObjetos[6].bChequeado = config.bDuracionLuzFondo;
              CambiarPantalla(PANTALLA_CONFIG);
            break;
          }
        break;
        case PANTALLA_MEDICIONES:
          switch (indFoco)
          {
            case 4:	//¿Estamos en el Button "Comenzar"?
              if ((sd.bSDInic == 1) && (ensayo.bEnsayando == 0)) //¿Todavía no comenzó el ensayo?
                MostrarMsg(MENSAJE_SOBRESCRIBIR, "Advertencia!!! Si el archivo ya existia se sobreescribira. Desea Continuar?", MENSAJE_OK_ESC, 90, 0);
              else
              {
                if (sd.bSDPresente == 0)	//¿La SD no está en el zócalo?
                  MostrarMsg(MENSAJE_INSERTAR_SD, "Inserte una tarjeta SD para comenzar el ensayo.", MENSAJE_OK, 90, 0);
                else	//La SD está presente, pero no se pudo inicializar
                  MostrarMsg(MENSAJE_ERROR_SD, "Hubo un error al inicializar la Tarjeta SD!", MENSAJE_OK, 90, 0);
              }
            break;
            case 5:	//¿Estamos en el Button "Finalizar"?
              if (ensayo.bEnsayando == 1) //¿Hay un ensayo corriendo?
              {
                TerminarEnsayo();
								
								//GuardarMuestra();
								//GuardarMuestra();
								//GuardarMuestra();
								//GuardarMuestra();
								
								//FSfclose(sd.pNewFile); //Cierra el archivo
              } 
            break;
          }
        break;
				case PANTALLA_TARAR:
					TararFuerza();
				break;
        case PANTALLA_CONFIG:
          GuardarConfigFlash();
        break;
        case PANTALLA_PARAMETROS:
          switch(indFoco)
          {
            case 3: //Botón 'Guardar'
              GuardarParametros();
            break;
            case 4: //Botón 'Resetear Grupo'
              //Reseteamos el grupo de parámetros
              param.diametros[param.iGdP].diametroTrac = DIAMETRO_TRAC_DEFECTO;
              param.diametros[param.iGdP].diametroNoTrac = DIAMETRO_NO_TRAC_DEFECTO;
            break;
          }
          ActualizarPantallaParametros();	//Actualizamos  los componentes con el valor que deberían tener
        break;
      }
    break;

    case TECLA_CANCELAR:
      switch (pantallaActual)
      {
        case PANTALLA_INICIO:
          CambiarPantalla(PANTALLA_PRESENTA);
        break;
        case PANTALLA_MEDICIONES:
          //se suspenden las tareas que se ultilizaran en la pantalla de Mediciones
          OSTaskSuspend(TAREA_SD_PRIO);
          OSTaskSuspend(TAREA_ADQUISICION_PRIO);
          OSTaskSuspend(TAREA_CELDA_DE_CARGA_PRIO);
          OSTaskSuspend(TAREA_SENS_VEL_PRIO);
          OSTaskSuspend(TAREA_REFRESCO_PRIO);

          adqui.bMuestreando = 0; //Deshabilitamos el muestreo de velocidades y fuerza
          CambiarPantalla(PANTALLA_INICIO);
        break;
				case PANTALLA_TARAR:
					//se suspenden las tareas que se ultilizaran en la pantalla de Mediciones
          OSTaskSuspend(TAREA_ADQUISICION_PRIO);
          OSTaskSuspend(TAREA_CELDA_DE_CARGA_PRIO);
          OSTaskSuspend(TAREA_REFRESCO_PRIO);

          CambiarPantalla(PANTALLA_INICIO);
        break;
        case PANTALLA_PARAMETROS:
          CambiarPantalla(PANTALLA_INICIO);
        break;
        default:
          CambiarPantalla(PANTALLA_INICIO);
        break;
      }
    break;

    case TECLA_ARRIBA:
      switch (pantallaActual)
      {
        case PANTALLA_PARAMETROS:

        break;
      }
    break;

    case TECLA_ABAJO:
      switch (pantallaActual)
      {
        case PANTALLA_PARAMETROS:

        break;
      }
    break;

    case TECLA_DERECHA:
      switch (pantallaActual)
      {
        case PANTALLA_MEDICIONES:
          QuitarFoco();	//Le quitamos el foco a quien lo tenga
          //Usando el foco del objeto en el que estoy actualmente, elijo a quién le voy a entregar el foco
          switch (indFoco)
          {
            case 4:	//¿Estamos en el Button "Comenzar"?
              indFoco = 5; //Le asignamos el foco a "Finalizar"
            break;
            case 5:	//¿Estamos en el Button "Finalizar"?
              indFoco = 0; //Le asignamos el foco a "G de Param:"
            break;
          }
          AsignarFoco();	//Asignamos  el foco elegido
        break;

        case PANTALLA_PARAMETROS:
          QuitarFoco();	//Le quitamos el foco a quien lo tenga
          //Usando el foco del objeto en el que estoy actualmente, elijo a quién le voy a entregar el foco
          switch (indFoco)
          {
            case 3:	//¿Estamos en el Button "Guardar"?
              indFoco = 4; //Le asignamos el foco a "Resetear Grupo"
            break;
            case 4:	//¿Estamos en el Button "Resetear Grupo"?
              indFoco = 0; //Le asignamos el foco a "GRUPO DE PARAMETROS"
            break;
          }
          AsignarFoco();	//Asignamos  el foco elegido
        break;
      }
    break;

    case TECLA_IZQUIERDA:
      switch (pantallaActual)
      {
        case PANTALLA_MEDICIONES:
          QuitarFoco();	//Le quitamos el foco a quien lo tenga
          //Usando el foco del objeto en el que estoy actualmente, elijo a quién le voy a entregar el foco
          switch (indFoco)
          {
            case 4:	//¿Estamos en el Button "Comenzar"?
              indFoco = 3; //Le asignamos el foco a "Dur:"
            break;
            case 5:	//¿Estamos en el Button "Finalizar"?
              indFoco = 4; //Le asignamos el foco a "Comenzar"
            break;
          }
          AsignarFoco();	//Asignamos  el foco elegido
        break;

        case PANTALLA_PARAMETROS:
          QuitarFoco();	//Le quitamos el foco a quien lo tenga
          //Usando el foco del objeto en el que estoy actualmente, elijo a quién le voy a entregar el foco
          switch (indFoco)
          {
            case 3:	//¿Estamos en el Button "Guardar"?
              indFoco = 2; //Le asignamos el foco a "Diametro Traccion:"
            break;
            case 4:	//¿Estamos en el Button "Resetear Grupo"?
              indFoco = 3; //Le asignamos el foco a "Guardar"
            break;
          }
          AsignarFoco();	//Asignamos  el foco elegido
        break;
      }
    break;
  }
}//end ButtonOnKeyPress()

/*Función SpinEditOnKeyPress------------------------------------------------------------------------------------------------------------------------
Descripción: 	evento ejecutado cuando se pulsa una tecla mientras el SpinEdit n tiene el foco 
Entrada: 
		ptrSpinEdit: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SpinEditOnKeyPress()
{

  switch (teclado.teclaPulsada)
  {
    case TECLA_ACEPTAR:
      switch (pantallaActual)
      {
        case PANTALLA_MEDICIONES:
          switch (indFoco)
          {
            case 1:	//¿Estamos en el SpinEdit de "Mediciones:"?
              if (formMediciones.ptrObjetos[25].bEditando == 0)	//¿Se acaba de aceptar un cambio para el SpinEdit?
                      adqui.numMedActual = vPSpinEdits[11].valor.word; //Modificamos el Composite
              //conduc.bCambioDeResis = 1;
            break;
            case 2:	//¿Estamos en el SpinEdit de "T_FINAL"?
              //controlTemp.setPoint = vPSpinEdits[2].valor.word; //Modificamos el SetPoint
            break;
          }
        break;
        case PANTALLA_PARAMETROS:
          switch (indFoco)
          {
            case 0:	//¿Estamos en el SpinEdit "GRUPO DE PARAM"?
              param.iGdP = vPSpinEdits[9].valor.word;	//Cambiamos el grupo de parámetros actual
            break;
            case 1:	//¿Estamos en el SpinEdit "Diametro Traccion:"?
              param.diametros[param.iGdP].diametroTrac = vPSpinEdits[10].valor.word; //Cambiamos el diámetro de tracción
            break;
            case 2:	//¿Estamos en el SpinEdit "Diametro no Traccion:"?
              param.diametros[param.iGdP].diametroNoTrac = vPSpinEdits[11].valor.word; //Cambiamos el diámetro de no tracción
            break;
            case 4:	//¿Estamos en el SpinEdit "TIEMPO LUZ FONDO:"?
              config.duracionLuzFondo = vPSpinEdits[12].valor.word;
            break;
          }
        break;
        case PANTALLA_CONFIG:
          //Estamos en el SpinEdit "TIEMPO LUZ FONDO:"
          config.duracionLuzFondo = vPSpinEdits[12].valor.word;
        break;
      }
    break;

    case TECLA_CANCELAR:
      switch (pantallaActual)
      {
        case PANTALLA_MEDICIONES:
          if (c.spinEdit.estado.bRedibujar == 0) 	//¿No estaba editando, por lo tanto tengo que volver a la pantalla anterior?
          {
            adqui.bMuestreando = 0; //Deshabilitamos el muestreo de velocidades y fuerza
            CambiarPantalla(PANTALLA_INICIO);
          }
        break;
        case PANTALLA_PARAMETROS:
          if (c.spinEdit.estado.bRedibujar == 1) 	//¿Acabo de cancelar la edición?
          {
            if (indFoco == 0)	//SpinEdit "GRUPO DE PARAM"
              param.iGdP = c.spinEdit.valorTemp.word;	//Seteamos el número de programa actual
            ActualizarPantallaParametros();	//Actualizamos  los componentes con el valor que deberían tener
          }
          else	//¿No estaba editando, por lo tanto tengo que volver a la pantalla anterior?
            CambiarPantalla(PANTALLA_INICIO);
        break;
      }
    break;
    case TECLA_ARRIBA:
      switch (pantallaActual)
      {
        case PANTALLA_PARAMETROS:
          if (c.spinEdit.estado.bEditando == 0)	//¿No estoy en el modo edición?
          {
            QuitarFoco();	//Le quitamos el foco a quien lo tenga
            //Usando el foco del objeto en el que estoy actualmente, elijo a quién le voy a entregar el foco
            switch (indFocoActual)
            {
              case 0:	//¿Estamos en el SpinEdit "GRUPO DE PARAMETROS"?
                indFoco = 3; //Le asignamos el foco a "Guardar"
              break;
              case 1:	//¿Estamos en el SpinEdit de cambio "Diametro Traccion:"?
                indFoco = 0; //Le asignamos el foco a "GRUPO DE PARAMETROS"
              break;
              case 2:	//¿Estamos en el SpinEdit "Diametro no Traccion:"?
                indFoco = 1; //Le asignamos el foco a "Diametro Traccion:"
              break;
            }
            AsignarFoco();	//Asignamos  el foco elegido
          }
        break;
      }
    break;

    case TECLA_ABAJO:
      switch (pantallaActual)
      {
        case PANTALLA_PARAMETROS:
          if (c.spinEdit.estado.bEditando == 0)	//¿No estoy en el modo edición?
          {
            QuitarFoco();	//Le quitamos el foco a quien lo tenga
            //Usando el foco del objeto en el que estoy actualmente, elijo a quién le voy a entregar el foco
            switch (indFocoActual)
            {
              case 0:	//¿Estamos en el SpinEdit "GRUPO DE PARAMETROS"?
                indFoco = 1; //Le asignamos el foco a "Diametro Traccion:"
              break;
              case 1:	//¿Estamos en el SpinEdit de cambio "Diametro Traccion:"?
                indFoco = 2; //Le asignamos el foco a "Diametro no Traccion:"
              break;
              case 2:	//¿Estamos en el SpinEdit "Diametro no Traccion:"?
                indFoco = 3; //Le asignamos el foco a "Guardar"
              break;
            }
            AsignarFoco();	//Asignamos  el foco elegido
          }
        break;
      }
    break;

    case TECLA_DERECHA:
      switch (pantallaActual)
      {
        case PANTALLA_MEDICIONES:
          if (c.spinEdit.estado.bEditando == 0)	//¿No estoy en el modo edición?
          {
            QuitarFoco();	//Le quitamos el foco a quien lo tenga
            //Usando el foco del objeto en el que estoy actualmente, elijo a quién le voy a entregar el foco
            switch (indFoco)
            {
              case 0:	//¿Estamos en el SpinEdit "G de Param:"?
                indFoco = 1; //Le asignamos el foco a "Guardar en SD"
              break;
              case 3:	//¿Estamos en el SpinEdit "Dur:"?
                indFoco = 4; //Le asignamos el foco a "Comenzar"
              break;
            }
            AsignarFoco();	//Asignamos  el foco elegido
          }
        break;

        case PANTALLA_PARAMETROS:
          if (c.spinEdit.estado.bEditando == 0)	//¿No estoy en el modo edición?
          {
            QuitarFoco();	//Le quitamos el foco a quien lo tenga
            //Usando el foco del objeto en el que estoy actualmente, elijo a quién le voy a entregar el foco
            switch (indFoco)
            {
              case 0:	//¿Estamos en el SpinEdit "GRUPO DE PARAMETROS"?
                indFoco = 1; //Le asignamos el foco a "Diametro Traccion:"
              break;
              case 1:	//¿Estamos en el SpinEdit "Diametro Traccion:"?
                indFoco = 2; //Le asignamos el foco a "Diametro no Traccion:"
              break;
              case 2:	//¿Estamos en el SpinEdit "Diametro no Traccion:"?
                indFoco = 3; //Le asignamos el foco a "Guardar"
              break;
            }
            AsignarFoco();	//Asignamos el foco elegido
          }
        break;
      }
    break;

    case TECLA_IZQUIERDA:
      switch (pantallaActual)
      {
        case PANTALLA_MEDICIONES:
          if (c.spinEdit.estado.bEditando == 0)	//¿No estoy en el modo edición?
          {
            QuitarFoco();	//Le quitamos el foco a quien lo tenga
            //Usando el foco del objeto en el que estoy actualmente, elijo a quién le voy a entregar el foco
            switch (indFoco)
            {
              case 0:	//¿Estamos en el SpinEdit "G de Param:"?
                indFoco = 5; //Le asignamos el foco a "Finalizar"
              break;
              case 3:	//¿Estamos en el SpinEdit "Dur:"?
                indFoco = 2; //Le asignamos el foco a "Dur:"
              break;
            }
            AsignarFoco();	//Asignamos  el foco elegido
          }
        break;

        case PANTALLA_PARAMETROS:
          if (c.spinEdit.estado.bEditando == 0)	//¿No estoy en el modo edición?
          {
            QuitarFoco();	//Le quitamos el foco a quien lo tenga
            //Usando el foco del objeto en el que estoy actualmente, elijo a quién le voy a entregar el foco
            switch (indFoco)
            {
              case 0:	//¿Estamos en el SpinEdit "GRUPO DE PARAMETROS"?
                indFoco = 4; //Le asignamos el foco a "Resetear Grupo"
              break;
              case 1:	//¿Estamos en el SpinEdit "Diametro Traccion:"?
                indFoco = 0; //Le asignamos el foco a "GRUPO DE PARAMETROS"
              break;
              case 2:	//¿Estamos en el SpinEdit "Diametro no Traccion:"?
                indFoco = 1; //Le asignamos el foco a "Diametro Traccion:"
              break;
            }
            AsignarFoco();	//Asignamos  el foco elegido
          }
        break;
      }
    break;
  }

  if (pantallaActual == PANTALLA_PARAMETROS)
  {
    if (teclado.teclaPulsada == TECLA_ARRIBA || teclado.teclaPulsada == TECLA_ABAJO)
    {
      if (indFoco == 0)	//SpinEdit "GRUPO DE PARAM"
      {
        param.iGdP = vPSpinEdits[9].valor.word;	//Seteamos el grupo de parámetros
        ActualizarPantallaParametros();
      }
    }
  }

}//end SpinEditOnKeyPress()

/*Función ValEditOnKeyPress------------------------------------------------------------------------------------------------------------------------
Descripción: 	evento ejecutado cuando se pulsa una tecla mientras el ValEdit n tiene el foco 
Entrada: 
		ptrValEdit: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ValEditOnKeyPress(void)
{

}//fin ValEditOnKeyPress()


/*Función CheckBoxOnKeyPress------------------------------------------------------------------------------------------------------------------------
Descripción: evento ejecutado cuando se pulsa una tecla mientras el CheckBox n tiene el foco 
Entrada: 
		ptrCheckBox: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void CheckBoxOnKeyPress(void)
{
  //ComportamientoPropioCheckBox();

  switch (teclado.teclaPulsada)
  {
    case TECLA_ACEPTAR:
      switch (pantallaActual)
      {
        case PANTALLA_CONFIG:
          config.contLuzFondo = 0;
          config.bDuracionLuzFondo = formConfig.ptrObjetos[6].bChequeado;
        break;
      }
    break;

    case TECLA_CANCELAR:
      switch (pantallaActual)
      {
        case PANTALLA_MEDICIONES:
          adqui.bMuestreando = 0; //Deshabilitamos el muestreo de velocidades y fuerza
          CambiarPantalla(PANTALLA_INICIO);
        break;

        case PANTALLA_PARAMETROS:
          CambiarPantalla(PANTALLA_INICIO);
        break;
      }
    break;

    case TECLA_DERECHA:
      switch (pantallaActual)
      {
        case PANTALLA_MEDICIONES:
          QuitarFoco();	//Le quitamos el foco a quien lo tenga
          //Usando el foco del objeto en el que estoy actualmente, elijo a quién le voy a entregar el foco
          switch (indFoco)
          {
            case 1:	//¿Estamos en el SpinEdit "Guardar en SD"?
              indFoco = 2; //Le asignamos el foco a "Dur:"
            break;
            case 2:	//¿Estamos en el SpinEdit "Dur:"?
              indFoco = 3; //Le asignamos el foco a "Dur:"
            break;
          }
          AsignarFoco();	//Asignamos  el foco elegido
        break;
      }
    break;

    case TECLA_IZQUIERDA:
      switch (pantallaActual)
      {
        case PANTALLA_MEDICIONES:
          QuitarFoco();	//Le quitamos el foco a quien lo tenga
          //Usando el foco del objeto en el que estoy actualmente, elijo a quién le voy a entregar el foco
          switch (indFoco)
          {
            case 1:	//¿Estamos en el SpinEdit "Guardar en SD"?
              indFoco = 0; //Le asignamos el foco a "G de Param:"
            break;
            case 2:	//¿Estamos en el SpinEdit "Dur:"?
              indFoco = 1; //Le asignamos el foco a "Guardar en SD"
            break;
          }
          AsignarFoco();	//Asignamos  el foco elegido
        break;
      }
    break;
  }
}//end CheckBoxOnKeyPress()

/*Función ComboBoxOnKeyPress------------------------------------------------------------------------------------------------------------------------
Descripción: evento ejecutado cuando se pulsa una tecla mientras el ComboBox n tiene el foco 
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ComboBoxOnKeyPress()
{

}//end ComboBoxOnKeyPress()

/*Función ProgBarOnKeyPress------------------------------------------------------------------------------------------------------------------------
Descripción: evento ejecutado cuando se pulsa una tecla mientras la ProgBar n tiene el foco 
Entrada: 
		ptrProgBar: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ProgBarOnKeyPress()
{
  switch (teclado.teclaPulsada)
  {
    case TECLA_CANCELAR:
      if (pantallaActual == PANTALLA_CONFIG)
        CambiarPantalla(PANTALLA_INICIO);
    break;

    case TECLA_DERECHA:
      if (indFoco == 0) //¿Estoy en la ProgBar de Luz de Fondo?
      {
        if (config.luzFondo < 15)
          config.luzFondo++;
        c.progBar.progPorcent = (unsigned char) ((float) config.luzFondo * 100 / (float) 15);
        SetLuzFondo();
      }
      if (indFoco == 1) //¿Estoy en la ProgBar de Contraste?
      {
        if (config.contraste < 15)
          config.contraste++;
        c.progBar.progPorcent = (unsigned char) ((float) config.contraste * 100 / (float) 15);
        SetContraste();
      }
    break;

    case TECLA_IZQUIERDA:
      if (indFoco == 0) //¿Estoy en la ProgBar de Luz de Fondo?
      {
        if (config.luzFondo > 0)
          config.luzFondo--;
        c.progBar.progPorcent = (unsigned char) ((float) config.luzFondo * 100 / (float) 15);
        SetLuzFondo();
      }
      if (indFoco == 1) //¿Estoy en la ProgBar de Contraste?
      {
        if (config.contraste > 0)
          config.contraste--;
        c.progBar.progPorcent = (unsigned char) ((float) config.contraste * 100 / (float) 15);
        SetContraste();
      }
    break;
  }

  vPProgBars[c.numValProp].progPorcent = c.progBar.progPorcent; //Actualizamos los valores propios de la ProgBar
  ptrFoco[indFoco]->bRedibujar = 1;

}//Fin ProgBarOnKeyPress()

/*Función MsgBoxOnKeyPress------------------------------------------------------------------------------------------------------------------------
Descripción: 	evento ejecutado cuando se pulsa una tecla mientras hay un mensaje activo en pantalla 
Entrada: nada
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void MsgBoxOnKeyPress(void)
{
  switch (pantallaActual)
  {
    case PANTALLA_MEDICIONES:
      switch (c.msgBox.msgID)
      {
        case MENSAJE_INSERTAR_SD:

        break;

        case MENSAJE_SOBRESCRIBIR:
          if (c.msgBox.teclaPulsada == TECLA_ACEPTAR)
						IniciarEnsayo();
        break;
      }
    break;

    case PANTALLA_PARAMETROS:

    break;
  }
}//fin MsgBoxtOnKeyPress()
