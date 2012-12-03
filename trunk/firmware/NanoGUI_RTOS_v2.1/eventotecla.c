#include <interfaz.h>
#include <configinterfaz.h>

//Variables de ButtonOnKeyPress()
unsigned char iBOKP;

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
						case 0: //Botón 'Ensayo'
							CambiarPantalla(PANTALLA_ENSAYO);
							break;
						case 1: //Botón 'Composites'
							//CargarComposites();	//Actualizamos el arreglo de composites
							//vPSpinEdits[0].valor.word = (unsigned int) conduc.iComposite;	//Seteamos el número de composite
							//Seteamos el diámetro en el ValEdit
							c.estado.indDatos = formComposite.ptrObjetos[4].indDatos;	//Indicamos el indice de datos del ValEdit
							ptrForm = &formComposite;	//Indicamos la pantalla del ValEdit
							//ValEditSetValor(conduc.comp[conduc.iComposite].diametro);
							//Seteamos el espesor en el ValEdit
							c.estado.indDatos = formComposite.ptrObjetos[7].indDatos;	//Indicamos el indice de datos del ValEdit
							ptrForm = &formComposite;	//Indicamos la pantalla del ValEdit
							//ValEditSetValor(conduc.comp[conduc.iComposite].espesor);
							//Cargamos la pantalla
							CambiarPantalla(PANTALLA_COMPOSITE);
							break;
						case 2: //Botón 'Programas'
							//if (controlTemp.bProgCargadosDesdeSD == 0)	//Todavía no fueron cargados los programas desde la SD
								//CargarProgramas();	//Actualizamos el arreglo de Programas
							//vPSpinEdits[7].valor.word = controlTemp.iProg;	//Seteamos el número de programa actual
							//vPSpinEdits[8].valor.word = controlTemp.prog[controlTemp.iProg].iSeg;	//Seteamos el número de segmento actual
							//vPComboBoxes[0].opcionSelec = controlTemp.prog[controlTemp.iProg].segmentos[controlTemp.prog[controlTemp.iProg].iSeg].tipo;	//Seteamos el tipo de segmento
							//vPSpinEdits[9].valor.word = controlTemp.prog[controlTemp.iProg].segmentos[controlTemp.prog[controlTemp.iProg].iSeg].setPoint;	//Seteamos la temperatura del segmento actual
							//vPSpinEdits[10].valor.word = controlTemp.prog[controlTemp.iProg].segmentos[controlTemp.prog[controlTemp.iProg].iSeg].duracion;	//Seteamos la duración del segmento actual
							//vPSpinEdits[11].valor.word = controlTemp.prog[controlTemp.iProg].segmentos[controlTemp.prog[controlTemp.iProg].iSeg].dif;	//Seteamos el diferencial del segmento actual
							//Cargamos la pantalla
							CambiarPantalla(PANTALLA_PROGRAMAS);
							break;
						case 3: //Botón 'Configuración'
							CambiarPantalla(PANTALLA_CONFIG);
							break;
					}
					break;

				case PANTALLA_ENSAYO: 
					switch(indFoco)
					{
						case 0: //Botón 'Ensayo Programado'
							CambiarPantalla(PANTALLA_CONFIG_ENSAYO);
							break;
						case 1: //Botón 'Ensayo Libre'
							//if (conduc.bCompositesCargados == 0)	//¿Los composites  todavía no han sido cargados desde la Flash?
								//CargarComposites();
							//vPSpinEdits[1].valor.word = conduc.iComposite;
							//CalibrarConduc();
							CambiarPantalla(PANTALLA_ENSAYO_LIBRE);
							break;
					}
					break;
					
				case PANTALLA_COMPOSITE: 
					//Botón Guardar	presionado
					//GuardarComposites();
					break;

				case PANTALLA_ENSAYO_LIBRE: 
					switch(indFoco)
					{
						case 5: //Botón 'Comenzar'
              //IniciarEnsayoLibre();
							break;
						case 6: //Botón 'Finalizar'
              //TerminarEnsayoLibre();
							break;
					}							
					break;

				case PANTALLA_CONFIG: 
					//GuardarConfigFlash();
					break;		

				case PANTALLA_PROGRAMAS: 
					switch(indFoco)
					{
						case 6: //Botón 'Guardar'
							//GuardarProgramas();
							break;
						case 7: //Botón 'Reset S'
							//Reseteamos el Segmento
							//controlTemp.prog[controlTemp.iProg].segmentos[controlTemp.prog[controlTemp.iProg].iSeg].tipo = SEG_NORMAL;
							//controlTemp.prog[controlTemp.iProg].segmentos[controlTemp.prog[controlTemp.iProg].iSeg].dif = DIFERENCIAL_POR_DEF;
							//controlTemp.prog[controlTemp.iProg].segmentos[controlTemp.prog[controlTemp.iProg].iSeg].setPoint = SET_POINT_POR_DEF;
							//controlTemp.prog[controlTemp.iProg].segmentos[controlTemp.prog[controlTemp.iProg].iSeg].duracion = DURACION_POR_DEF;
							break;
						case 8: //Botón 'Reset P'
							//Reseteamos el Programa
							//for (iBOKP=0;iBOKP < CANT_SEGMENTOS; iBOKP++)
							//{
								//Actualizamos la estructura
								//if (iBOKP == (CANT_SEGMENTOS - 1))	//¿Estoy en el último segmento del programa?
								//	controlTemp.prog[controlTemp.iProg].segmentos[iBOKP].tipo = SEG_FINAL;
								//else
								//	controlTemp.prog[controlTemp.iProg].segmentos[iBOKP].tipo = SEG_NORMAL;
								//controlTemp.prog[controlTemp.iProg].segmentos[iBOKP].dif = DIFERENCIAL_POR_DEF;
								//controlTemp.prog[controlTemp.iProg].segmentos[iBOKP].setPoint = SET_POINT_POR_DEF;
								//controlTemp.prog[controlTemp.iProg].segmentos[iBOKP].duracion = DURACION_POR_DEF;
							//}
							break;
					}		
					ActualizarPantallaProgramas();	//Actualizamos  los componentes con el valor que deberían tener					
					break;	

				case PANTALLA_CONFIG_ENSAYO: 
					//Botón "Comenzar Ensayo"	presionado
					//if (IniciarEnsayoProgramado() == 1)	//¿Se pudo inicial el Ensayo Programado?
						CambiarPantalla(PANTALLA_EJEC_ENSAYO);
					//else
						//Imprimir mensaje acá diciendo que no se pudo ejecutar el Ensayo por que no hay segmentos válidos
					break;	
			}
			break;

		case TECLA_CANCELAR:
			switch (pantallaActual)
			{
				case PANTALLA_INICIO:
					CambiarPantalla(PANTALLA_PRESENTA);
					break;
				case PANTALLA_ENSAYO_LIBRE:
					CambiarPantalla(PANTALLA_ENSAYO);
					break;	
				case PANTALLA_CONFIG_ENSAYO:
					CambiarPantalla(PANTALLA_ENSAYO);
					break;	
				default:
					CambiarPantalla(PANTALLA_INICIO);
					break;
			}
			break;

		case TECLA_ARRIBA:
			switch (pantallaActual)
			{
				case PANTALLA_PROGRAMAS:
					QuitarFoco();	//Le quitamos el foco a quien lo tenga
					//Usando el foco del objeto en el que estoy actualmente, elijo a quién le voy a entregar el foco
					switch (indFocoActual)
					{
						case 6:	//¿Estamos en el Button "Guardar"?
							indFoco = 4; //Le asignamos el foco a "Dif: C"
							break;	
						case 7:	//¿Estamos en el Button "Res S"?
							indFoco = 5; //Le asignamos el foco a "Dur: min"
							break;
						case 8:	//¿Estamos en el Button "Res P"?
							indFoco = 5; //Le asignamos el foco a "Dur: min"
							break;
					}
					AsignarFoco();	//Asignamos  el foco elegido
				break;
			}
			break;

		case TECLA_ABAJO:
			switch (pantallaActual)
			{
				case PANTALLA_PROGRAMAS:
					QuitarFoco();	//Le quitamos el foco a quien lo tenga
					//Usando el foco del objeto en el que estoy actualmente, elijo a quién le voy a entregar el foco
					switch (indFocoActual)
					{
						case 6:	//¿Estamos en el Button "Guardar"?
							indFoco = 0; //Le asignamos el foco a "PROGRAMA:"
							break;	
						case 7:	//¿Estamos en el Button "Res S"?
							indFoco = 1; //Le asignamos el foco a "SEGEMENTO:"
							break;
						case 8:	//¿Estamos en el Button "Res P"?
							indFoco = 1; //Le asignamos el foco a "SEGMENTO:"
							break;
					}
					AsignarFoco();	//Asignamos  el foco elegido
				break;
			}
			break;

		case TECLA_DERECHA:
			switch (pantallaActual)
			{
				case PANTALLA_PROGRAMAS:
					QuitarFoco();	//Le quitamos el foco a quien lo tenga
					//Usando el foco del objeto en el que estoy actualmente, elijo a quién le voy a entregar el foco
					switch (indFoco)
					{
						case 6:	//¿Estamos en el Button "Guardar"?
							indFoco = 7; //Le asignamos el foco a "Res S"
							break;	
						case 7:	//¿Estamos en el Button "Res S"?
							indFoco = 8; //Le asignamos el foco a "Res P"
							break;
						case 8:	//¿Estamos en el Button "Res P"?
							indFoco = 0; //Le asignamos el foco a "PROGRAMA:"
							break;
					}
					AsignarFoco();	//Asignamos  el foco elegido
				break;
			}
			break;

		case TECLA_IZQUIERDA:
			switch (pantallaActual)
			{
				case PANTALLA_PROGRAMAS:
					QuitarFoco();	//Le quitamos el foco a quien lo tenga
					//Usando el foco del objeto en el que estoy actualmente, elijo a quién le voy a entregar el foco
					switch (indFoco)
					{
						case 6:	//¿Estamos en el Button "Guardar"?
							indFoco = 5; //Le asignamos el foco a "Dur: min"
							break;	
						case 7:	//¿Estamos en el Button "Res S"?
							indFoco = 6; //Le asignamos el foco a "Guardar"
							break;
						case 8:	//¿Estamos en el Button "Res P"?
							indFoco = 7; //Le asignamos el foco a "Res S"
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
				case PANTALLA_ENSAYO_LIBRE:
					switch (indFoco)
					{
						case 0:	//¿Estamos en el SpinEdit de "COMPOSITE:"?
							//conduc.iComposite = vPSpinEdits[1].valor.word; //Modificamos el Composite
							//conduc.bCambioDeResis = 1;
							break;
						case 2:	//¿Estamos en el SpinEdit de "T_FINAL"?
							//controlTemp.setPoint = vPSpinEdits[2].valor.word; //Modificamos el SetPoint
							break;	
					}
					break;
				case PANTALLA_PROGRAMAS:
					switch (indFoco)
					{
						case 0:	//¿Estamos en el SpinEdit de cambio de programa?
							//controlTemp.iProg = vPSpinEdits[7].valor.word;	//Cambiamos el número de programa actual
							break;	
						case 1:	//¿Estamos en el SpinEdit de cambio de segmento?
							//controlTemp.prog[controlTemp.iProg].iSeg = vPSpinEdits[8].valor.word; //Cambiamos el número de segmento actual
							break;
						case 2:	//¿Estamos en el SpinEdit de temperatura?
							//controlTemp.prog[controlTemp.iProg].segmentos[controlTemp.prog[controlTemp.iProg].iSeg].setPoint = vPSpinEdits[9].valor.word;	//Cambiamos la temperatura del segmento actual
							break;
						case 4:	//¿Estamos en el SpinEdit de diferencial?
							//controlTemp.prog[controlTemp.iProg].segmentos[controlTemp.prog[controlTemp.iProg].iSeg].dif = (unsigned char) vPSpinEdits[11].valor.word;	//Cambiamos el diferencial del segmento actual
							break;
						case 5:	//¿Estamos en el SpinEdit de duración?
							//controlTemp.prog[controlTemp.iProg].segmentos[controlTemp.prog[controlTemp.iProg].iSeg].duracion = vPSpinEdits[10].valor.word;	//Cambiamos la duración del segmento actual
							break;
					}
					break;	
				case PANTALLA_CONFIG_ENSAYO:
					switch (indFoco)
					{
						case 0:	//El  foco esta en el SpinEdit de "COMPOSITE:"
							//conduc.iComposite = vPSpinEdits[12].valor.word;
							break;
						case 1:
							//controlTemp.iProg = vPSpinEdits[13].valor.word;
							break;
					}
					break;	
				case PANTALLA_EJEC_ENSAYO:
					//Cancelamos  el comportamiento por defecto que le dimos  al SpinEdit que tiene el foco simbólicamente
					c.spinEdit.estado.bEditando = 0;
					c.spinEdit.estado.bRedibujar = 0;
					break;		
			}
			break;

		case TECLA_CANCELAR:
			switch (pantallaActual)
			{
				case PANTALLA_ENSAYO_LIBRE:
					if (c.spinEdit.estado.bRedibujar == 0) 	//¿No estaba en modo edición?
						CambiarPantalla(PANTALLA_ENSAYO);
					break;	
				case PANTALLA_CONFIG_ENSAYO:
					CambiarPantalla(PANTALLA_ENSAYO);
					break;	
				case PANTALLA_COMPOSITE:
					if (c.spinEdit.estado.bRedibujar == 1) 	//¿Acabo de cancelar la edición?
					{
						//conduc.iComposite = c.spinEdit.valorTemp.word;
						//Seteamos el diámetro en el ValEdit
						c.estado.indDatos = formComposite.ptrObjetos[4].indDatos;	//Indicamos el indice de datos del ValEdit
						ptrForm = &formComposite;	//Indicamos la pantalla del ValEdit
						//ValEditSetValor(conduc.comp[vPSpinEdits[0].valor.word].diametro);
						formComposite.ptrObjetos[4].bRedibujar = 1;	//Redibujamos el ValEdit
						//Seteamos el espesor en el ValEdit
						c.estado.indDatos = formComposite.ptrObjetos[7].indDatos;	//Indicamos el indice de datos del ValEdit
						ptrForm = &formComposite;	//Indicamos la pantalla del ValEdit
						//ValEditSetValor(conduc.comp[vPSpinEdits[0].valor.word].espesor);
						formComposite.ptrObjetos[7].bRedibujar = 1;	//Redibujamos el ValEdit
					}
					else	//¿No estaba editando, por lo tanto tengo que volver a la pantalla anterior?
						CambiarPantalla(PANTALLA_INICIO);
					break;
				case PANTALLA_PROGRAMAS:
					if (c.spinEdit.estado.bRedibujar == 1) 	//¿Acabo de cancelar la edición?
					{																													
						//if (indFoco == 0)	//SpinEdit de selección de Programa
							//controlTemp.iProg = c.spinEdit.valorTemp.word;	//Seteamos el número de programa actual
						//if (indFoco == 1)	//SpinEdit de elección de Segmento
							//controlTemp.prog[controlTemp.iProg].iSeg = c.spinEdit.valorTemp.word;	//Seteamos el número de segmento actual
						
						//ActualizarPantallaProgramas();	//Actualizamos  los componentes con el valor que deberían tener
					}
					else	//¿No estaba editando, por lo tanto tengo que volver a la pantalla anterior?
						CambiarPantalla(PANTALLA_INICIO);
					break;
				case PANTALLA_EJEC_ENSAYO:
						//if (ensayo.bEnsayando == 1)	//¿Se está ejecutando un Ensayo Programado?
						//{
							//controlTemp.bEjecucionCancelada = 1;
							//TerminarEnsayoProgramado();
						//}
						//if (ensayo.bEnsayando != 1)	//¿No se está ejecutando un Ensayo Programado?
							CambiarPantalla(PANTALLA_ENSAYO);
						//ensayo.TipoEnsayo = ENSAYO_NINGUNO; //Esto está por las dudas
					break;

			}
			break;
		case TECLA_ARRIBA:
			switch (pantallaActual)
			{
				case PANTALLA_PROGRAMAS:
					if (c.spinEdit.estado.bEditando == 0)	//¿No estoy en el modo edición?
					{
						QuitarFoco();	//Le quitamos el foco a quien lo tenga
						//Usando el foco del objeto en el que estoy actualmente, elijo a quién le voy a entregar el foco
						switch (indFocoActual)
						{
							case 0:	//¿Estamos en el SpinEdit de cambio de programa?
								indFoco = 6; //Le asignamos el foco a "Guardar"
								break;	
							case 1:	//¿Estamos en el SpinEdit de cambio de segmento?
								indFoco = 7; //Le asignamos el foco a "Res S"
								break;
							case 2:	//¿Estamos en el SpinEdit de temperatura?
								indFoco = 0; //Le asignamos el foco a "PROGRAMA"
								break;
							case 4:	//¿Estamos en el SpinEdit de diferencial?
								indFoco = 2; //Le asignamos el foco a "Temp: C"
								break;
							case 5:	//¿Estamos en el SpinEdit de duración?
								indFoco = 3; //Le asignamos el foco a "Tipo"
								break;
						}
						AsignarFoco();	//Asignamos  el foco elegido
					}
					/*else
					{
						switch (indFoco)
						{

							case 2:	//¿Estamos en el SpinEdit de temperatura?
								SetPWMDutyCycle(vPSpinEdits[9].valor.word * 10, PWM_LUZ_FONDO);
								break;
							case 5:	//¿Estamos en el SpinEdit de duración?
								SetPWMDutyCycle(vPSpinEdits[10].valor.word * 10, PWM_CONTRASTE);
								break;
						}
					}*/
					break;
			}
			break;

		case TECLA_ABAJO:
			switch (pantallaActual)
			{
				case PANTALLA_PROGRAMAS:
					if (c.spinEdit.estado.bEditando == 0)	//¿No estoy en el modo edición?
					{
						QuitarFoco();	//Le quitamos el foco a quien lo tenga
						//Usando el foco del objeto en el que estoy actualmente, elijo a quién le voy a entregar el foco
						switch (indFocoActual)
						{
							case 0:	//¿Estamos en el SpinEdit de cambio de programa?
								indFoco = 2; //Le asignamos el foco a "Temp: C"
								break;	
							case 1:	//¿Estamos en el SpinEdit de cambio de segmento?
								indFoco = 3; //Le asignamos el foco a "Tipo"
								break;
							case 2:	//¿Estamos en el SpinEdit de temperatura?
								indFoco = 4; //Le asignamos el foco a "Dif: C"
								break;
							case 4:	//¿Estamos en el SpinEdit de diferencial?
								indFoco = 6; //Le asignamos el foco a "Guardar"
								break;
							case 5:	//¿Estamos en el SpinEdit de duración?
								indFoco = 7; //Le asignamos el foco a "Res S"
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
				case PANTALLA_PROGRAMAS:
					if (c.spinEdit.estado.bEditando == 0)	//¿No estoy en el modo edición?
					{
						QuitarFoco();	//Le quitamos el foco a quien lo tenga
						//Usando el foco del objeto en el que estoy actualmente, elijo a quién le voy a entregar el foco
						switch (indFoco)
						{
							case 0:	//¿Estamos en el SpinEdit de cambio de programa?
								indFoco = 1; //Le asignamos el foco a "SEGMENTO:"
								break;	
							case 1:	//¿Estamos en el SpinEdit de cambio de segmento?
								indFoco = 2; //Le asignamos el foco a "Temp: C"
								break;
							case 2:	//¿Estamos en el SpinEdit de temperatura?
								indFoco = 3; //Le asignamos el foco a "Tipo:"
								break;
							case 4:	//¿Estamos en el SpinEdit de diferencial?
								indFoco = 5; //Le asignamos el foco a "Duración"
								break;
							case 5:	//¿Estamos en el SpinEdit de duración?
								indFoco = 6; //Le asignamos el foco a "Guardar"
								break;
						}
						AsignarFoco();	//Asignamos  el foco elegido
					}
					break;
			}
			break;

		case TECLA_IZQUIERDA:
			switch (pantallaActual)
			{
				case PANTALLA_PROGRAMAS:
					if (c.spinEdit.estado.bEditando == 0)	//¿No estoy en el modo edición?
					{
						QuitarFoco();	//Le quitamos el foco a quien lo tenga
						//Usando el foco del objeto en el que estoy actualmente, elijo a quién le voy a entregar el foco
						switch (indFoco)
						{
							case 0:	//¿Estamos en el SpinEdit de cambio de programa?
								indFoco = 8; //Le asignamos el foco a "Res P"
								break;	
							case 1:	//¿Estamos en el SpinEdit de cambio de segmento?
								indFoco = 0; //Le asignamos el foco a "PROGRAMA:"
								break;
							case 2:	//¿Estamos en el SpinEdit de temperatura?
								indFoco = 1; //Le asignamos el foco a "SEGMENTO:"
								break;
							case 4:	//¿Estamos en el SpinEdit de diferencial?
								indFoco = 3; //Le asignamos el foco a "Tipo"
								break;
							case 5:	//¿Estamos en el SpinEdit de duración?
								indFoco = 4; //Le asignamos el foco a "Dif: C"
								break;
						}
						AsignarFoco();	//Asignamos  el foco elegido
					}
					break;
			}
			break;
	}

	if (pantallaActual == PANTALLA_COMPOSITE)
	{
		if (teclado.teclaPulsada == TECLA_ARRIBA || teclado.teclaPulsada == TECLA_ABAJO)
		{
			//if (vPSpinEdits[0].valor.word < CANT_COMPOSITES)
			//conduc.iComposite = vPSpinEdits[0].valor.word;
			//Seteamos el diámetro en el ValEdit
			c.estado.indDatos = formComposite.ptrObjetos[4].indDatos;	//Indicamos el indice de datos del ValEdit
			ptrForm = &formComposite;	//Indicamos la pantalla del ValEdit
			//ValEditSetValor(conduc.comp[vPSpinEdits[0].valor.word].diametro);
			formComposite.ptrObjetos[4].bRedibujar = 1;	//Redibujamos el ValEdit
			//Seteamos el espesor en el ValEdit
			c.estado.indDatos = formComposite.ptrObjetos[7].indDatos;	//Indicamos el indice de datos del ValEdit
			ptrForm = &formComposite;	//Indicamos la pantalla del ValEdit
			//ValEditSetValor(conduc.comp[vPSpinEdits[0].valor.word].espesor);
			formComposite.ptrObjetos[7].bRedibujar = 1;	//Redibujamos el ValEdit
		}
	}

	if (pantallaActual == PANTALLA_PROGRAMAS)
	{
		if (teclado.teclaPulsada == TECLA_ARRIBA || teclado.teclaPulsada == TECLA_ABAJO)
		{
			//if (indFoco == 0)	//SpinEdit de elección de Programa
				//controlTemp.iProg = vPSpinEdits[7].valor.word;	//Seteamos el número de programa actual
			//if (indFoco == 1)	//SpinEdit de elección de Segmento
				//controlTemp.prog[controlTemp.iProg].iSeg = vPSpinEdits[8].valor.word;	//Seteamos el número de segmento actual
		
			//if (indFoco == 0 || indFoco == 1)	//Hacemos esto para evitar un titileo en el pantalla
				//ActualizarPantallaProgramas();
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

	//ComportamientoPropioValEdit();

	switch (teclado.teclaPulsada)
	{
		case TECLA_CANCELAR:
			if (c.valEdit.estado.bRedibujar == 0) 	//¿No estaba en modo edición?
				switch (pantallaActual)
				{
					case PANTALLA_COMPOSITE:
						CambiarPantalla(PANTALLA_INICIO);
						break;
					default:
						CambiarPantalla(PANTALLA_INICIO);
						break;
				}
			break;

		case TECLA_ACEPTAR:
			switch (pantallaActual)
			{
				case PANTALLA_COMPOSITE:
					//Guardamos el nuevo diámetro en el arreglo de composites
					c.estado.indDatos = formComposite.ptrObjetos[4].indDatos;	//Indicamos el indice de datos del ValEdit
					ptrForm = &formComposite;	//Indicamos la pantalla del ValEdit
					//conduc.comp[conduc.iComposite].diametro = (unsigned int) ValEditGetValor();
					//Guardamos el nuevo espesor en el arreglo de composites
					c.estado.indDatos = formComposite.ptrObjetos[7].indDatos;	//Indicamos el indice de datos del ValEdit
					ptrForm = &formComposite;	//Indicamos la pantalla del ValEdit
					//conduc.comp[conduc.iComposite].espesor = (unsigned int) ValEditGetValor();
					break;
				default:
					CambiarPantalla(PANTALLA_INICIO);
					break;
			}
			break;
	}
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

			break;

		case TECLA_CANCELAR:
			CambiarPantalla(PANTALLA_ENSAYO);
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

	switch (teclado.teclaPulsada)
	{
		case TECLA_ACEPTAR:
			if (pantallaActual == PANTALLA_PROGRAMAS)
				if (c.comboBox.estado.bEditando == 0)	//¿Se acaba de terminar el modo edición?
					//controlTemp.prog[controlTemp.iProg].segmentos[controlTemp.prog[controlTemp.iProg].iSeg].tipo = (unsigned char) vPComboBoxes[0].opcionSelec;	//Cambiamos el tipo del segmento actual
			break;
		case TECLA_CANCELAR:
			if (c.comboBox.estado.bEditando == 0 && c.comboBox.estado.bRedibujar == 0) 	//¿El ComboBox NO está siendo editado
																																				//y NO se acaba de cancelar la edición?
			{
				CambiarPantalla(PANTALLA_INICIO);
			}
			break;

		case TECLA_ARRIBA:
			switch (pantallaActual)
			{
				case PANTALLA_PROGRAMAS:
					if (c.comboBox.estado.bEditando == 0)	//¿No estoy en el modo edición?
					{
						QuitarFoco();	//Le quitamos el foco a quien lo tenga
						indFoco = 1; //Le asignamos el foco a "SEGMENTO"
						AsignarFoco();	//Asignamos  el foco elegido
					}
					break;
			}
			break;

		case TECLA_ABAJO:
			switch (pantallaActual)
			{
				case PANTALLA_PROGRAMAS:
					if (c.comboBox.estado.bEditando == 0)	//¿No estoy en el modo edición?
					{
						QuitarFoco();	//Le quitamos el foco a quien lo tenga
						indFoco = 5; //Le asignamos el foco a "Dur: min"
						AsignarFoco();	//Asignamos  el foco elegido
					}
					break;
			}
			break;

		case TECLA_DERECHA:
			switch (pantallaActual)
			{
				case PANTALLA_PROGRAMAS:
					if (c.comboBox.estado.bEditando == 0)	//¿No estoy en el modo edición?
					{
						QuitarFoco();	//Le quitamos el foco a quien lo tenga
						indFoco = 4; //Le asignamos el foco a "Dif: C"
						AsignarFoco();	//Asignamos  el foco elegido
					}
					break;
			}
			break;

		case TECLA_IZQUIERDA:
			switch (pantallaActual)
			{
				case PANTALLA_PROGRAMAS:
					if (c.comboBox.estado.bEditando == 0)	//¿No estoy en el modo edición?
					{
						QuitarFoco();	//Le quitamos el foco a quien lo tenga
						indFoco = 2; //Le asignamos el foco a "Temp: C"
						AsignarFoco();	//Asignamos  el foco elegido
					}
					break;
			}
			break;
	}
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

}	//Fin ProgBarOnKeyPress()

