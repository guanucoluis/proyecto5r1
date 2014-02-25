#include "SpinEdit.h"

//comienzo de spinEdit
#ifdef SPIN_EDIT

//VARIABLES
//Variables de SpinEditActualizar()
unsigned char iSEA;
unsigned char offsetXSEA;

//Variables de ComportamientoPropioSpinEdit()
	unsigned char iCPSE;
	
//FUNCIONES
/*Función SpinEditIncrementar------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que incrementa el valor del SpinEdit 
Entrada: 
		ptrSpinEdit: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SpinEditIncrementar()
{
	if ((c.spinEdit.valor.word + c.spinEdit.incremento) <= c.spinEdit.valMax.word)
	{
		c.spinEdit.valor.word = c.spinEdit.valor.word + c.spinEdit.incremento;

		//Indicar que se actualice el SpinEdit
		c.spinEdit.estado.bRedibujar = 1;
	}
}//end SpinEditIncrementar()

/*Función SpinEditDecrementar------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que decrementa el valor del SpinEdit 
Entrada: 
		ptrSpinEdit: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SpinEditDecrementar()
{
	if (c.spinEdit.valor.word >= c.spinEdit.incremento)
	{
		if (!((c.spinEdit.valor.word - c.spinEdit.incremento) < c.spinEdit.valMin.word))
		{
			c.spinEdit.valor.word = c.spinEdit.valor.word - c.spinEdit.incremento;

			//Indicar que se actualice el SpinEdit
			c.spinEdit.estado.bRedibujar = 1;
		}
	}
}//end SpinEditDecrementar()

/*Función SpinEditEditar------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que ingresa, sale y guarda el valor, y cancela el modo de edición del SpinEdit
Entrada: 
		ptrSpinEdit: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SpinEditEditar(unsigned char accion)
{
	switch(accion)
	{
		case ENTRAR:
			c.spinEdit.estado.bEditando = 1; //Entramos en el modo de edición
			c.spinEdit.estado.bRedibujar = 1;	//Redibujamos el SpinEdit para reflejar los cambios
			c.spinEdit.valorTemp.word = c.spinEdit.valor.word; //Copiamos el valor del SpinEdit en la variable temporal
			break;	
		case SALIR:
			c.spinEdit.estado.bEditando = 0;	//Salimos del modo de edición
			c.spinEdit.estado.bRedibujar = 1;	//Redibujamos el SpinEdit para reflejar los cambios
			//c.spinEdit.valor.word = c.spinEdit.valorTemp.word; //Copiamos en valor de la variable temporal en el valor del SpinEdit
			break;
		case CANCELAR:
			c.spinEdit.estado.bEditando = 0;	//Salimos del modo de edición
			c.spinEdit.estado.bRedibujar = 1;	//Redibujamos el SpinEdit para reflejar los cambios
			c.spinEdit.valor.word = c.spinEdit.valorTemp.word; //Copiamos en valor de la variable temporal en el valor del SpinEdit
			break;
	}	
}//end SpinEditEditar()


/*Función SpinEditEfectoEdicion------------------------------------------------------------------------------------------------------------------------
Descripción: 	función que dibuja un determinado efecto en la pantalla para indicar que el SpinEdit esta siendo editado
Entrada: 
		ptrSpinEdit: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SpinEditEfectoEdicion()
{
  if (contTitileo >= TITILEO_CURSOR_SPIN_EDIT)
  {
    if (c.spinEdit.bDibujarNeg == 1) //¿Está dibujado el cursor?
    {
      c.spinEdit.bDibujarNeg = 0;        //El cursor ya no está
      c.spinEdit.estado.bRedibujar = 1;
      contTitileo = 0;        //reseteamos la cuenta
    }        
    else
    {
      c.spinEdit.bDibujarNeg = 1;        //El cursor está dibujado
      c.spinEdit.estado.bRedibujar = 1;
      contTitileo = 0;        //reseteamos la cuenta
    }
		c.spinEdit.bNoRedibujar = 0;
  }

	//Actualizamos las banderas del Objeto Gráfico
	ptrFoco[indFoco]->bandEstado = c.spinEdit.estado.bandEstado;

}//end SpinEditEfectoEdicion()

/*Función SpinEditActualizar------------------------------------------------------------------------------------------------------------------------
Descripción: función encargada de dibujar o actualizar los SpinEdits 
Entrada: 
		ptrSpinEdit: puntero a la estructura del objeto de la interfaz sobre el que se quiere trabajar
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void SpinEditActualizar()
{
	/*unsigned char iSEA;
	unsigned char offsetXSEA;*/

	if (c.spinEdit.estado.bEditando == 1)	//¿El SpinEdit está siendo editado?
		SpinEditEfectoEdicion();	//Efecto de edición del SpinEdit
	else	//El SpinEdit no está siendo editado
	{
		if (c.spinEdit.estado.bEnFoco == 1)	//¿El SpinEdit tiene el foco?
		{
			if (c.spinEdit.estado.bRedibujar == 1) //¿Es necesario redibujar todo el SpinEdit?
			{
				if (c.spinEdit.estado.bColorNeg == 0) //¿El SpinEdit debe ser dibujado negado?
					c.spinEdit.bDibujarNeg = !COLOR_FONDO_DEF;
				else
					c.spinEdit.bDibujarNeg = COLOR_FONDO_DEF;
			}
		}
		else	//El SpinEdit no tiene el foco
		{
			if (c.spinEdit.estado.bRedibujar == 1) //¿Es necesario redibujar todo el SpinEdit?
			{
				if (c.spinEdit.estado.bColorNeg == 0) //¿El SpinEdit debe ser dibujado negado?
					c.spinEdit.bDibujarNeg = COLOR_FONDO_DEF;
				else
					c.spinEdit.bDibujarNeg = !COLOR_FONDO_DEF;
			}
		}
	}

	if (c.spinEdit.bNoRedibujar == 1 && c.spinEdit.estado.bEditando == 1)	//¿El SpinEdit no necesita redibujarse?
		return;
 
	if (c.spinEdit.estado.bRedibujar == 1)
	{
		if(c.tamanioTexto == 0) //la letra es de 3x5, sin tener en cuenta las excepciones
		{
			offsetXSEA = c.x + GROSOR_BORDE_SPIN_ED;
			//Ahora dibujamos el SpinEdit
			if (c.spinEdit.estado.bLimpiarFondo == 1 || c.spinEdit.estado.bEnFoco == 1)
				//Limpiar el area donde se va a dibujar el SpinEdit
				GLCD_Relleno(	c.x, c.y
										, ANCHO_LABEL_3X5	* c.spinEdit.cifras
										+ (c.spinEdit.cifras - 1) * SEP_ELEM_SPIN_ED + 2 * GROSOR_BORDE_SPIN_ED
										, ANCHO_CURSOR_SPIN_ED + 2 * GROSOR_BORDE_SPIN_ED + ALTO_LABEL_3X5
										, c.spinEdit.bDibujarNeg);
			//Descomponemos el entero c.spinEdit.valor.word en unidad, decena, centena, etc
			BinBCD(c.spinEdit.valor.word);
			for(iSEA = 0; iSEA < (c.spinEdit.cifras); iSEA++)	
			{
				c.cadenaAux[0] = BCD[c.spinEdit.cifras - iSEA - 1];
				c.cadenaAux[1] = 0; //Hacemos que la cadena termine en NULL
				GLCD_String(	offsetXSEA
										, c.y + 4 + ANCHO_CURSOR_SPIN_ED + GROSOR_BORDE_SPIN_ED
										, c.cadenaAux
										, c.tamanioTexto
										, !(c.spinEdit.bDibujarNeg));
				offsetXSEA = offsetXSEA + GLCD_AnchoLetra(c.cadenaAux[0], c.tamanioTexto) + SEP_ELEM_SPIN_ED; 
			}
		}
		else //la letra es de 5x7, sin tener en cuenta las excepciones
		{
			offsetXSEA = c.x + GROSOR_BORDE_SPIN_ED;
			//Ahora dibujamos el SpinEdit
			if (c.spinEdit.estado.bLimpiarFondo == 1 || c.spinEdit.estado.bEnFoco == 1)
				//Limpiar el area donde se va a dibujar el SpinEdit
				GLCD_Relleno(	c.x, c.y
										, ((ANCHO_ELEM_SPIN_ED * c.tamanioTexto) * c.spinEdit.cifras)
										+ (c.spinEdit.cifras - 1) * (SEP_ELEM_SPIN_ED + c.tamanioTexto - 1) 
										+ 2 * GROSOR_BORDE_SPIN_ED
										, ANCHO_CURSOR_SPIN_ED + 2 * GROSOR_BORDE_SPIN_ED + (ALTO_ELEM_SPIN_ED * c.tamanioTexto)
										, c.spinEdit.bDibujarNeg);
			//Descomponemos el entero c.spinEdit.valor.word en unidad, decena, centena, etc
			BinBCD(c.spinEdit.valor.word);
			for(iSEA = 0; iSEA < (c.spinEdit.cifras); iSEA++)	
			{
				c.cadenaAux[0] = BCD[c.spinEdit.cifras - iSEA - 1];
				c.cadenaAux[1] = 0; //Hacemos que la cadena termine en NULL
				GLCD_String(	offsetXSEA
										, c.y + (6 * c.tamanioTexto) + ANCHO_CURSOR_SPIN_ED + GROSOR_BORDE_SPIN_ED
										, c.cadenaAux
										, c.tamanioTexto
										, !(c.spinEdit.bDibujarNeg));
				offsetXSEA = offsetXSEA + (ANCHO_ELEM_SPIN_ED * c.tamanioTexto) 
										+ SEP_ELEM_SPIN_ED + c.tamanioTexto - 1; 
			}	
		}
		if (c.spinEdit.estado.bEditando != 1)	//Si estoy editando, dejo a bRedibujar como 1
			c.spinEdit.estado.bRedibujar = 0;	//El SpinEdit ya ha sido redibujado
		c.spinEdit.bNoRedibujar = 1;
		c.spinEdit.estado.bLimpiarFondo = 1;
	}	

	//Actualizamos las banderas del Objeto Gráfico
	c.estado.bandEstado = c.spinEdit.estado.bandEstado;
}//end SpinEditActualizar()

/*Función ComportamientoPropioSpinEdit------------------------------------------------------------------------------------------------------------------------
Descripción: función que ejecuta las acciones que definen el comportamiento del objeto ante las distintas
							pulsaciones de tecla
Entrada: 
		c: cargador debidamente seteado
Salida: nada
//-------------------------------------------------------------------------------------------------------------------------------------*/
void ComportamientoPropioSpinEdit(void)
{
	//unsigned char iCPSE;

	c.spinEdit.bNoRedibujar = 0;

	switch (teclado.teclaPulsada)
	{
		case TECLA_ACEPTAR:
			if (c.spinEdit.estado.bEditando == 1)	//¿El SpinEdit está siendo editado?
			{
				SpinEditEditar(SALIR);
				ptrFoco[indFoco]->bandEstado = c.spinEdit.estado.bandEstado;	//Actualizamos las banderas del Objeto Gráfico
			}
			else	//El SpinEdit no está siendo editado
				if (c.spinEdit.estado.bEditable == 1)	//¿El SpinEdit es editable?
					SpinEditEditar(ENTRAR);	//Entramos en modo edición			
			break;

		case TECLA_CANCELAR:
			if (c.spinEdit.estado.bEditando == 1)	//¿El SpinEdit está siendo editado?
			{
				SpinEditEditar(CANCELAR);
				ptrFoco[indFoco]->bandEstado = c.spinEdit.estado.bandEstado;	//Actualizamos las banderas del Objeto Gráfico
			}
			break;

		case TECLA_ARRIBA:
			if (c.spinEdit.estado.bEditando == 1)	//¿El SpinEdit está siendo editado?
				SpinEditIncrementar();
			else
				RetrocederFoco();
			break;

		case TECLA_ABAJO:
			if (c.spinEdit.estado.bEditando == 1)	//¿El SpinEdit está siendo editado?
				SpinEditDecrementar();
			else
				AvanzarFoco();
			break;

		case TECLA_NO_PRES:	//Me fijo en la tecla Sostenida solo si la tecla presionada ya ha sido atendida
			//Pulsación sostenida de tecla
			if (teclado.teclaSostenida != TECLA_NO_PRES)
			{
				switch (teclado.teclaSostenida)
				{
					case TECLA_ARRIBA:
						if (c.spinEdit.estado.bEditando == 1)	//¿El SpinEdit está siendo editado?
						{
							if (teclado.bHabIncremento == 1)	//Si se está habilitado para hacer el incremento...
							{
								switch (teclado.velIncremento)
								{
									case 0:
										iCPSE = CANT_INCREMENTOS_0;
										break;
									case 1:
										iCPSE = CANT_INCREMENTOS_1;
										break;
									case 2:
										iCPSE = CANT_INCREMENTOS_2;
										break;
									case 3:
										iCPSE = CANT_INCREMENTOS_3;
										break;
									case 4:
										iCPSE = CANT_INCREMENTOS_4;
										break;
									case 5:
										iCPSE = CANT_INCREMENTOS_5;
										break;
									case 6:
										iCPSE = CANT_INCREMENTOS_6;
										break;
								}
								for(;iCPSE>0;iCPSE--)
									SpinEditIncrementar();
								teclado.bHabIncremento = 0;
							}
						}
						break;
			
					case TECLA_ABAJO:
						if (c.spinEdit.estado.bEditando == 1)	//¿El SpinEdit está siendo editado?
						{
							if (teclado.bHabIncremento == 1)	//Si se está habilitado para hacer el incremento...
							{
								switch (teclado.velIncremento)
								{
									case 0:
										iCPSE = CANT_INCREMENTOS_0;
										break;
									case 1:
										iCPSE = CANT_INCREMENTOS_1;
										break;
									case 2:
										iCPSE = CANT_INCREMENTOS_2;
										break;
									case 3:
										iCPSE = CANT_INCREMENTOS_3;
										break;
									case 4:
										iCPSE = CANT_INCREMENTOS_4;
										break;
									case 5:
										iCPSE = CANT_INCREMENTOS_5;
										break;
									case 6:
										iCPSE = CANT_INCREMENTOS_6;
										break;
								}
								for(;iCPSE>0;iCPSE--)
									SpinEditDecrementar();
								teclado.bHabIncremento = 0;
							}
						}
						break;
				}
				//if (c.spinEdit.estado.bRedibujar == 1 && c.spinEdit.estado.bEditando == 0)
					//c.spinEdit.bNoRedibujar = 0;
				//else
					//c.spinEdit.bNoRedibujar = 1;
			}		
			else	//No hay ninguna tecla sostenida ni pulsada
			{
				if (c.spinEdit.estado.bRedibujar == 1)
					c.spinEdit.bNoRedibujar = 0;
				else
					c.spinEdit.bNoRedibujar = 1;
			}
			break;
	}
	
	if (c.spinEdit.estado.bEditando == 1)	//¿El SpinEdit está siendo editado?
		ptrFoco[indFoco]->bandEstado = c.spinEdit.estado.bandEstado;	//Actualizamos las banderas del Objeto Gráfico

	vPSpinEdits[c.numValProp].valor.word = c.spinEdit.valor.word; //Actualizamos el valor propio del SpinEdit

}	//Fin ComportamientoPropioSpinEdit()

#endif//end SpinEdit
