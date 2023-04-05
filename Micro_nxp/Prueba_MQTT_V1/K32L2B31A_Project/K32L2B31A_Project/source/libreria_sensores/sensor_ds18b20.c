/*! @file : sensor_lm35.c
 * @author  Ernesto Andres Rincon Cruz
 * @version 1.0.0
 * @date    12/03/2023
 * @brief   Driver para 
 * @details
 *
*/
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "board.h"
#include "pin_mux.h"
#include "sensor_ds18b20.h"
#include "fsl_adc16.h"
#include "peripherals.h"
#include "clock_config.h"
#include "K32L2B31A.h"
#include "fsl_debug_console.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

uint32_t dato_sensor_0; // PTD6-Debe ser cable Negro
uint32_t dato_sensor_1;	// PTD5----------------Marrón
uint32_t dato_sensor_2; // PTE29---------------Rojo
uint32_t dato_sensor_3; // PTE30---------------Naranja
uint32_t dato_sensor_4; // PTC0----------------Amarillo
uint32_t dato_sensor_5; // PTE20---------------Verde
uint32_t dato_sensor_6; // PTE22---------------Azúl
uint32_t dato_sensor_7; // PTB2----------------Morado
uint32_t dato_sensor_8; // PTB1-Debe ser cable Gris

uint32_t dato_sensor_9; // PTB0-Alternador de sensor

int Alt_sens = 0; //Selecciona la variable medida 0 temperatura 1 potencia

int binario[9];
char binarioString[10];
int decimal;

float temperatura = 0;
float potencia = 0;
/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/


/*******************************************************************************
 * External vars
 ******************************************************************************/


/*******************************************************************************
 * Local vars
 ******************************************************************************/


/*******************************************************************************
 * Private Source Code
 ******************************************************************************/


/*******************************************************************************
 * Public Source Code
 ******************************************************************************/
void sens_temp_agua(void){

	/*Configurar canal ADC para lectura de sensores*/
	ADC16_SetChannelConfig(ADC0_PERIPHERAL, ADC0_CH0_CONTROL_GROUP, &ADC0_channelsConfig[0]);
	while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC0_PERIPHERAL,
				ADC0_CH0_CONTROL_GROUP))) {
	}
	dato_sensor_0 = ADC16_GetChannelConversionValue(ADC0_PERIPHERAL,ADC0_CH0_CONTROL_GROUP);

	/*Configurar canal ADC para lectura de sensores*/
	ADC16_SetChannelConfig(ADC0_PERIPHERAL, ADC0_CH1_CONTROL_GROUP, &ADC0_channelsConfig[1]);
	while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC0_PERIPHERAL,
				ADC0_CH1_CONTROL_GROUP))) {
	}
	dato_sensor_1 = ADC16_GetChannelConversionValue(ADC0_PERIPHERAL,ADC0_CH1_CONTROL_GROUP);

	/*Configurar canal ADC para lectura de sensores*/
	ADC16_SetChannelConfig(ADC0_PERIPHERAL, ADC0_CH2_CONTROL_GROUP, &ADC0_channelsConfig[2]);
	while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC0_PERIPHERAL,
				ADC0_CH2_CONTROL_GROUP))) {
	}
	dato_sensor_2 = ADC16_GetChannelConversionValue(ADC0_PERIPHERAL,ADC0_CH2_CONTROL_GROUP);

	/*Configurar canal ADC para lectura de sensores*/
	ADC16_SetChannelConfig(ADC0_PERIPHERAL, ADC0_CH3_CONTROL_GROUP, &ADC0_channelsConfig[3]);
	while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC0_PERIPHERAL,
				ADC0_CH3_CONTROL_GROUP))) {
	}
	dato_sensor_3 = ADC16_GetChannelConversionValue(ADC0_PERIPHERAL,ADC0_CH3_CONTROL_GROUP);

	/*Configurar canal ADC para lectura de sensores*/
	ADC16_SetChannelConfig(ADC0_PERIPHERAL, ADC0_CH4_CONTROL_GROUP, &ADC0_channelsConfig[4]);
	while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC0_PERIPHERAL,
				ADC0_CH4_CONTROL_GROUP))) {
	}
	dato_sensor_4 = ADC16_GetChannelConversionValue(ADC0_PERIPHERAL,ADC0_CH4_CONTROL_GROUP);

	/*Configurar canal ADC para lectura de sensores*/
	ADC16_SetChannelConfig(ADC0_PERIPHERAL, ADC0_CH5_CONTROL_GROUP, &ADC0_channelsConfig[5]);
	while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC0_PERIPHERAL,
				ADC0_CH5_CONTROL_GROUP))) {
	}
	dato_sensor_5 = ADC16_GetChannelConversionValue(ADC0_PERIPHERAL,ADC0_CH5_CONTROL_GROUP);

	/*Configurar canal ADC para lectura de sensores*/
	ADC16_SetChannelConfig(ADC0_PERIPHERAL, ADC0_CH6_CONTROL_GROUP, &ADC0_channelsConfig[6]);
	while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC0_PERIPHERAL,
				ADC0_CH6_CONTROL_GROUP))) {
	}
	dato_sensor_6 = ADC16_GetChannelConversionValue(ADC0_PERIPHERAL,ADC0_CH6_CONTROL_GROUP);

	/*Configurar canal ADC para lectura de sensores*/
	ADC16_SetChannelConfig(ADC0_PERIPHERAL, ADC0_CH7_CONTROL_GROUP, &ADC0_channelsConfig[7]);
	while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC0_PERIPHERAL,
				ADC0_CH7_CONTROL_GROUP))) {
	}
	dato_sensor_7 = ADC16_GetChannelConversionValue(ADC0_PERIPHERAL,ADC0_CH7_CONTROL_GROUP);

	/*Configurar canal ADC para lectura de sensores*/
	ADC16_SetChannelConfig(ADC0_PERIPHERAL, ADC0_CH8_CONTROL_GROUP, &ADC0_channelsConfig[8]);
	while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC0_PERIPHERAL,
				ADC0_CH8_CONTROL_GROUP))) {
	}
	dato_sensor_8 = ADC16_GetChannelConversionValue(ADC0_PERIPHERAL,ADC0_CH8_CONTROL_GROUP);

	ADC16_SetChannelConfig(ADC0_PERIPHERAL, ADC0_CH9_CONTROL_GROUP, &ADC0_channelsConfig[9]);
	while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC0_PERIPHERAL,
				ADC0_CH9_CONTROL_GROUP))) {
	}
	dato_sensor_9 = ADC16_GetChannelConversionValue(ADC0_PERIPHERAL,ADC0_CH9_CONTROL_GROUP);


	if(dato_sensor_0 > 2650){
		binario[0] = 1;
	}else{
		binario[0] = 0;
	}
	if(dato_sensor_1 > 1950){
		binario[1] = 1;
	}else{
		binario[1] = 0;
	}
	if(dato_sensor_2 > 1950){
		binario[2] = 1;
	}else{
		binario[2] = 0;
	}
	if(dato_sensor_3 > 1950){
		binario[3] = 1;
	}else{
		binario[3] = 0;
	}
	if(dato_sensor_4 > 1950){
		binario[4] = 1;
	}else{
		binario[4]= 0;
	}
	if(dato_sensor_5 > 1950){
		binario[5] = 1;
	}else{
		binario[5] = 0;
	}
	if(dato_sensor_6 > 1950){
		binario[6] = 1;
	}else{
		binario[6] = 0;
	}
	if(dato_sensor_7 > 1950){
		binario[7] = 1;
	}else{
		binario[7] = 0;
	}
	if(dato_sensor_8 > 1950){
		binario[8] = 1;
	}else{
		binario[8] = 0;
	}
	if(dato_sensor_9 > 2450){
		Alt_sens = 1;
	}else{
		Alt_sens = 0;
	}


	//sprintf(binary, "%d%d%d%d%d%d%d%d%d", binario[0], binario[1], binario[2], binario[3], binario[4], binario[5], binario[6], binario[7], binario[8]);

    // convertir el array de valores binarios en una cadena de caracteres
    for (int i = 0; i < 9; i++) {
        sprintf(&binarioString[i], "%d", binario[i]);
    }
    binarioString[9] = '\0'; // agregar el carácter nulo para indicar el final de la cadena

    // convertir la cadena de caracteres en un número entero
    decimal = atoi(binarioString);

    int decimal_temp = 0;
    int base = 1;

    // Recorrer los bits del número binario
    while(decimal > 0){
        int digit = decimal % 10;
        decimal_temp += digit * base;
        decimal /= 10;
        base *= 2;
    }
    if (Alt_sens == 0){
    	temperatura = decimal_temp/10.0f;
    }else{
    	potencia = decimal_temp/10.0f;
    }

    //SDK_DelayAtLeastUs(1000000U, SystemCoreClock);
}

float valor_temp_agua(void){
	return(temperatura);
}

float valor_potencia(void){
	return(potencia);
}
