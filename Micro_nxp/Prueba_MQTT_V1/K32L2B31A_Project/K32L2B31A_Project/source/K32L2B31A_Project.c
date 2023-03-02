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

#include <limits.h>
#include <float.h>

#include "iot_sdk_peripherals_bmp280.h"
#include "iot_sdk_hal_i2c1.h"

#include "stdbool.h"
#include "leds.h"
#include "sensor_de_luz.h"
#include "botones.h"
#include "modem.h"
#include "irq_lptmr0.h"
#include "irq_lpuart0.h"
#include "alarma.h"
#include "AppModem.h"
#include "sensor_temperatura.h"
#include "fsl_adc16.h"
#include "irq_lptmr0.h"

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

//uint32_t dato_sensor;

float temperatura_cuarto;
int sens_ready=0;
// Aplicacion Principal
int main(void){

	BOARD_Init();
    Timer_Init();
    Alarma_Init();
    Sens_BMP280_INIT();
    Key_Task_Init();
    //SDK_DelayAtLeastUs(1000000U, SystemCoreClock);
    if (Sens_BMP280_INIT()== 1){
    	SDK_DelayAtLeastUs(1000000U, SystemCoreClock);
    	AplicacionModem_Init();
    	sens_ready = 1;
    }
    //SensorLuz_Init();
    //AplicacionModem_Init();

    for(;;){
    	Key_Task_Run();
    	//SensorTemp_Run();
    	//SensorLuz_Task_Run();
    	AplicacionModem_Run();
    	fun_bm280();
    	//valor_temp();

        //AplicacionModem_Run();
    }
    /*
    while(1){
    	valor_temp();
    	temperatura_cuarto=valor_temp();
		PRINTF("BM280: %2.2f\r\n",temperatura_cuarto);
		SDK_DelayAtLeastUs(1000000U, SystemCoreClock);
    }

    while(1){
    	Configurar canal ADC para lectura de sensores
    	ADC16_SetChannelConfig(ADC0_PERIPHERAL, ADC0_CH0_CONTROL_GROUP, &ADC0_channelsConfig[0]);
		while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC0_PERIPHERAL,
					ADC0_CH0_CONTROL_GROUP))) {
		}
		dato_sensor = ADC16_GetChannelConversionValue(ADC0_PERIPHERAL,ADC0_CH0_CONTROL_GROUP);

		temperatura_cuarto = ((float)dato_sensor/4095)*500.0f;

		PRINTF("ADC Value: %2.2f\r\n",(float)dato_sensor);
		SDK_DelayAtLeastUs(1000000U, SystemCoreClock);
    }
    */
    //1,2,3,5,6,7.
    /* 1-u, 2-d, 3-u, 4-d, 5-d, 6-u,
     * 1-are there
     * 2-there are
     * 3-is there
     * 4-there is
     * 5-is there
     * 6-there is
     * 7-are there
     * 8-there aren't
     * 9-there is
     * 10-there is
     * 11-there aren't*/


}

