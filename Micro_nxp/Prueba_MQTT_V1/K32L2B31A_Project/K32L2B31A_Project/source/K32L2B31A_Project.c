/*! @file : K32L2B31A_Project.c
 * @author  Ernesto Andres Rincon Cruz
 * @ Revision para soporte de Modem Quectel:
 * Gustavo Galeano Oct 2 2021
 * @version 0.0.000
 * @date    23/08/2021
 * @brief   Funcion principal main
 * @details
 *			v0.0.000	Proyecto base creado usando MCUXpresso
 *
 *
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
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
#include "irq_lptmr0.h"
#include "irq_lpuart0.h"
#include "alarma.h"
#include "AppModem.h"

#define Timer_Init() LPTMR_StartTimer(LPTMR0)

/* Init board hardware. */
void BOARD_Init(void){
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif
}

// Scratch

	// 1. crear codigo nuevo
	// 2. Se compilar
	// 3. Se prueba en el board
	// 4. Se depura
	// 5.Funciona??? NO --> va al punto 1.
	// Funciona??? SI ---> punto 6.
	// 6. Backup Version
	// 7.Modularizar el modulo que Funciono
	// 8. Ensayar el Funcionamiento ya modularizado
	// 9. Comentar y organizar
	// 10.Optimizar codigo si es necesario
	// 11. Clean y Build
	// 12. Liberar version V2.0

//end Scratch


// Aplicacion Principal
int main(void) {
	BOARD_Init();
    Timer_Init();
    Alarma_Init();
    Key_Task_Init();
    AplicacionModem_Init();
    SensorLuz_Init();

    for(;;){
    	Key_Task_Run();
    	AplicacionModem_Run();
    	//SensorLuz_Task_Run();
    }
}

