/*! @file : sensor_de_luz.c
 * @author  Ernesto Andres Rincon Cruz
 * @version 1.0.0
 * @date    4 sept. 2021
 * @brief   Driver para 
 * @details
 *
*/
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "sensor_de_luz.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/
 /*!
  * @brief Inicia captura por ADC de voltaje generado por sensor de luz
  *
  */
 void sensorDeLuzIniciarCaptura(void);
 /*!
  * @brief Espera a que finalice el trabajo del ADC
  *
  */
 void sensorDeLuzEsperarResultado(void);

/*******************************************************************************
 * External vars
 ******************************************************************************/


/*******************************************************************************
 * Local vars
 ******************************************************************************/
 uint32_t adc_sensor_de_luz;


/*******************************************************************************
 * Private Source Code
 ******************************************************************************/
 void sensorDeLuzIniciarCaptura(void){
 	ADC16_SetChannelConfig(
 			SENSOR_DE_LUZ_ADC16_BASE,
 			SENSOR_DE_LUZ_ADC16_CHANNEL_GROUP,
 			&ADC0_channelsConfig[0]);
 }
 /*---------------------------------------------------------------*/
 void sensorDeLuzEsperarResultado(void){
 	while (0U == (kADC16_ChannelConversionDoneFlag
 					& ADC16_GetChannelStatusFlags(
 							SENSOR_DE_LUZ_ADC16_BASE,
 							SENSOR_DE_LUZ_ADC16_CHANNEL_GROUP)))
 	{
 	}
 }
/*******************************************************************************
 * Public Source Code
 ******************************************************************************/
uint32_t sensorDeLuzObtenerdatoADC(void){
 uint32_t resultadoADC;

 sensorDeLuzIniciarCaptura();
 sensorDeLuzEsperarResultado();

 resultadoADC=ADC16_GetChannelConversionValue(
		 	 	 SENSOR_DE_LUZ_ADC16_BASE,
				 SENSOR_DE_LUZ_ADC16_CHANNEL_GROUP);
 
 return(resultadoADC);
}
/*---------------------------------------------------------------*/

void SensorLuz_Task_Run(void){
	  adc_sensor_de_luz=sensorDeLuzObtenerdatoADC();
}


char sensorLuzSt;

enum{
	SENSOR_INIT,
	SENSOR_MEDIR,
	SENSOR_TEST_NIVELES
};

void SensorLuz_Init(void){
	sensorLuzSt = SENSOR_INIT;
}
void SensorLuz_Run(void){
	switch(sensorLuzSt){
		case SENSOR_INIT:
			// !!! Start al ADC
			sensorLuzSt = SENSOR_MEDIR;
			//!! Un retardo
		break;
		case SENSOR_MEDIR:
			//!!! Lee valores
			sensorLuzSt = SENSOR_TEST_NIVELES;
		break;
		case SENSOR_TEST_NIVELES:
			// !!! Compara y toma dec
			sensorLuzSt = SENSOR_INIT;
			//!!! Mailbox al modulo de Modem
			// !!!Notificar valores en Servidor
		break;
	}
}

