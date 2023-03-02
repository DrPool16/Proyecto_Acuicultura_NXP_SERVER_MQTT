/*! @file : sensor_temperatura.c
 * @author  Ernesto Andres Rincon Cruz
 * @version 1.0.0
 * @date    24/02/2023
 * @brief   Driver para 
 * @details
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

#include "sensor_temperatura.h"
#include "iot_sdk_hal_i2c1.h"
#include "iot_sdk_peripherals_bmp280.h"

#include "irq_lptmr0.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define HABILITAR_SENSOR_BMP280		1
#define HABILITAR_I2C1				1
#define HABILITAR_TLPTMR0			1

/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/


/*******************************************************************************
 * External vars
 ******************************************************************************/


/*******************************************************************************
 * Local vars
 ******************************************************************************/
//float temperature_value;
float temperature_process;
status_t status;
bmp280_data_t bmp280_datos;
uint8_t bmp280_detectado=0;
uint8_t bmp280_base_de_tiempo=0;
/*******************************************************************************
 * Private Source Code
 ******************************************************************************/


/*******************************************************************************
 * Public Source Code
 ******************************************************************************/
int Sens_BMP280_INIT(void){

	/*
#if HABILITAR_SENSOR_BMP280
	bmp280_data_t bmp280_datos;
	uint8_t bmp280_detectado=0;
	uint8_t bmp280_base_de_tiempo=0;
#endif
*/

    /* Activa LPTMR0 para que iniciar contador y posterior IRQ cada 1 segundo*/
    printf("Inicializa LPTMR0:");
    LPTMR_StartTimer(LPTMR0);
    printf("OK\r\n");

    /* Inicializa I2C1 para lectura de sensores SHT31 y BME280*/
    //Solo avanza si es exitoso el proceso
    printf("Inicializa I2C1:");
    if(i2c1MasterInit(100000)!=kStatus_Success){	//100kbps
    	printf("Error");
    	//return 0 ;
    }
    printf("OK\r\n");

    printf("Detectando BME280:");
    //LLamado a funcion que identifica sensor BME280
    if (bmp280WhoAmI() == kStatus_Success){
    	printf("OK\r\n");
    	(void)bmp280Init();	//inicializa sensor bme280
    	bmp280_detectado=1;	//activa bandera que indica (SI HAY BME280)
    }



    return(1);
}
void fun_bm280(void){
	//while(1){
    	if(lptmr0_ticks>10){
    		lptmr0_ticks=0;

	#if HABILITAR_SENSOR_BMP280
						if(bmp280_detectado==1){
							bmp280_base_de_tiempo++;	//incrementa base de tiempo para tomar dato bme280
							if(bmp280_base_de_tiempo>0){	//	>10 equivale aproximadamente a 2s
								bmp280_base_de_tiempo=0; //reinicia contador de tiempo
								if(bmp280ReadData(&bmp280_datos)==kStatus_Success){	//toma lectura humedad, presion, temperatura
									//printf("BME280 ->");
									//printf("temperatura:0x%X ",bmp280_datos.temperatura);	//imprime temperatura sin procesar
									//printf("humedad:0x%X ",bme280_datos.humedad);	//imprime humedad sin procesar
									//printf("presion:0x%X ",bmp280_datos.presion);	//imprime presion sin procesar
									//printf("\r\n");	//Imprime cambio de linea
									//temperature_process=ProcessingTemp(bmp280_datos.temperatura);
								}
							}
						}
	#endif
			temperature_process=ProcessingTemp(bmp280_datos.temperatura);

			}
	//}
}
float valor_temp(void){


			//return(temperature_process);
		   //}
    	return(temperature_process);
		//printf("Temperatura procesada: %2.2f\r\n", temperature_process);
}


