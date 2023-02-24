/*
 * Teclado.c
 *
 *  Created on: 10/12/2022
 *      Author: ggaleano
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "K32L2B31A.h"
#include "fsl_debug_console.h"
#include "stdbool.h"
#include "leds.h"
#include "sensor_de_luz.h"
#include "botones.h"
#include "modem.h"

extern bool boton1,boton2;


#define TeclaIzqSupPress() !boton2
#define TeclaDerSupPress() !boton1


// Retorna la Tecla que cambio
char Teclas_CambianEstado(void){
static char teclaIzqSupAnt,teclaDerSupAnt,teclaIzqSupAct,teclaDerSupAct;
	teclaIzqSupAct = TeclaIzqSupPress();
	teclaDerSupAct = TeclaDerSupPress();
	if((teclaIzqSupAct != teclaIzqSupAnt)){
		teclaIzqSupAnt = teclaIzqSupAct;
		return TECLA_IZQ_CAMBIO;
	}
	if((teclaDerSupAct != teclaDerSupAnt)){
		teclaDerSupAnt = teclaDerSupAct;
		return TECLA_DER_CAMBIO;
	}
	return 0; // no hay cambios
}

