/*
 * Alarma.c
 *
 *  Created on: 10/12/2022
 *      Author: ggaleano
 *      Modulo para manejo de tiempos en
 *      Segundos
 */

#include <stdio.h>
#include "board.h"
#include "pin_mux.h"
#include "K32L2B31A.h"
#include "fsl_debug_console.h"
#include "stdbool.h"
#include "modem.h"
#include "irq_lptmr0.h"
#include "irq_lpuart0.h"
#include "alarma.h"

// Para modulo Alarma
static volatile uint32_t segAct=0;

// Modulo Alarma
// Inicializa Alarma
void Alarma_Init(void){
	segAct = lptmr0_irq_counter;
}

// retorna el tiempo futuro de la alarma
uint32_t Alarma_Set(uint32_t time2Wait){
	segAct = lptmr0_irq_counter;
	return (segAct + time2Wait);
}

// retorna si la alarma se cumplio
char Alarma_Elapsed(uint32_t time2Test){
	segAct = lptmr0_irq_counter;
	if(segAct >= time2Test) return true;
	else return false;
}


