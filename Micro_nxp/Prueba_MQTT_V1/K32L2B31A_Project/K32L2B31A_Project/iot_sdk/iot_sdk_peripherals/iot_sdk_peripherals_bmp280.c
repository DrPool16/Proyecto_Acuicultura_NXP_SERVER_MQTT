/*! @file : iot_sdk_peripherals_bmp280.c
 * @author  Ernesto Andres Rincon Cruz
 * @version 1.0.0
 * @date    28/02/2023
 * @brief   Driver para 
 * @details
 *
*/
/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "iot_sdk_peripherals_bmp280.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/


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
//------------------------------------
 status_t bmp280WhoAmI(void) {
	status_t status;
	uint8_t i2c_data;

	status = bmp280ReadByte(&i2c_data, 1, BMP280_ADDRESS, BMP280_REG_ID, 1);

	if (status == kStatus_Success) {
		if (i2c_data == 0x58)
			return (kStatus_Success);
		else
			return (kStatus_Fail);
	} else {
		return (status);
	}
}
 //------------------------------------
 status_t bmp280Init(void){
 	status_t status;
 	uint8_t i2c_data;

    /*  write 00000 101 = 0x05 to CTRL_HUM */
 	/*  [2-0] = 101	humidity oversampling x 16*/
 	//i2c_data = 0x05;
 	//status = bmp280WriteByte(&i2c_data, 1, BMP280_ADDRESS, BMP280_REG_CTRL_HUM, 1);

    /*  write 101 101 11 = 0xB7 to CTRL_MEAS */
 	/*  [7-5] = 101 temperature oversampling x 16*/
 	/*  [4-2] = 101	pressure oversampling x 16*/
 	/*  [1-0] = 11 	Normal Mode*/
 	i2c_data = 0xB7;
 	status = bmp280WriteByte(&i2c_data, 1, BMP280_ADDRESS, BMP280_REG_CTRL_MEAS, 1);

 	if(status!=kStatus_Success)
 		return(status);

 	return(kStatus_Success);
 }
 //------------------------------------
status_t bmp280ReadData(bmp280_data_t *data) {
	status_t status;
	uint8_t i2c_data[6];

	status = bmp280ReadByte(&i2c_data[0], 6, BMP280_ADDRESS, BMP280_REG_PRESS_MSB, 1);
	if (status == kStatus_Success) {
		data->presion = (uint32_t)(i2c_data[0] << 16);
		data->presion |= (uint32_t)(i2c_data[1] << 8);
		data->presion |= (uint32_t)(i2c_data[2]);

		data->temperatura = (uint32_t)(i2c_data[3] << 16);
		data->temperatura |= (uint32_t)(i2c_data[4] << 8);
		data->temperatura |= (uint32_t)(i2c_data[5]);

		//data->humedad |= (uint32_t)(i2c_data[6] << 8);
		//data->humedad |= (uint32_t)(i2c_data[7]);

		return (kStatus_Success);
	}else{
		return (status);
	}
}

float ProcessingTemp(uint32_t data){
	int32_t var1, var2;
	  //if (!_sensorID) prueba si el sensor es el correcto
	  //  return NAN; // begin) not called yet

	  uint16_t _bmp280_calib_dig_T1 = 27504;
	  int16_t _bmp280_calib_dig_T2 = 26435;
	  int16_t _bmp280_calib_dig_T3 = -1000;
	  int32_t t_fine;
	  int32_t adc_T = data;
	  adc_T >>= 4;

	  var1 = ((((adc_T >> 3) - ((int32_t)_bmp280_calib_dig_T1 << 1))) *
	          ((int32_t)_bmp280_calib_dig_T2)) >>
	         11;

	  var2 = (((((adc_T >> 4) - ((int32_t)_bmp280_calib_dig_T1)) *
	            ((adc_T >> 4) - ((int32_t)_bmp280_calib_dig_T1))) >>
	           12) *
	          ((int32_t)_bmp280_calib_dig_T3)) >>
	         14;

	  t_fine = var1 + var2;

	  float T = (t_fine * 5 + 128) >> 8;
	  return (T / 100);
}
