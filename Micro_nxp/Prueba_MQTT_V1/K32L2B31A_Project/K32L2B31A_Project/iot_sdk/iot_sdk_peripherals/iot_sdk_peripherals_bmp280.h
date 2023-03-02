/*! @file : iot_sdk_peripherals_bmp280.h
 * @author  Ernesto Andres Rincon Cruz
 * @version 1.0.0
 * @date    28/02/2023
 * @brief   Driver para 
 * @details
 *
 */
#ifndef IOT_SDK_PERIPHERALS_IOT_SDK_PERIPHERALS_BMP280_H_
#define IOT_SDK_PERIPHERALS_IOT_SDK_PERIPHERALS_BMP280_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "iot_sdk_hal_i2c1.h"

/*!
 * @addtogroup PERIPHERAL
 * @{
 */
/*!
 * @addtogroup BME280
 * @{
 */
/*******************************************************************************
 * Public Definitions
 ******************************************************************************/
#define BMP280_ADDRESS  (0x76) //!< BME280 Dirección I2C.

/*! @brief Listado de registros del sensor BME280 */
enum _BMP280_registers{
	BMP280_REG_ID=0xD0,
	//BME280_REG_CTRL_HUM=0XF2,
	BMP280_REG_STATUS,
	BMP280_REG_CTRL_MEAS=0xF4,
	BMP280_REG_CONFIG,
	BMP280_REG_PRESS_MSB=0XF7,
	BMP280_REG_PRESS_lSB,
	BMP280_REG_PRESS_XlSB,
	BMP280_REG_TEMP_MSB,
	BMP280_REG_TEMP_lSB,
	BMP280_REG_TEMP_XlSB,
	BMP280_REG_HUM_MSB,
	BMP280_REG_HUM_lSB,
};

/*!
 * @brief Define tipo de datos estructura que permite organizar los datos del sensor BM280
 */
typedef struct _bmp280_data{
	uint32_t temperatura;
	//uint32_t humedad;
	uint32_t presion;
}bmp280_data_t;



//Define interconexión entre capa de firmware Peripherals (PPH) y HardwareAbstractionLayer (HAl)
#define bmp280WriteByte	i2c1MasterWriteByte
#define bmp280ReadByte	i2c1MasterReadByte

/*******************************************************************************
 * External vars
 ******************************************************************************/

/*******************************************************************************
 * Public vars
 ******************************************************************************/

/*******************************************************************************
 * Public Prototypes
 ******************************************************************************/
float ProcessingTemp(uint32_t data);

/*!
 * @brief Lee registro de identificacion sensor BME280
 *
 * @return	resultado ejecución
 * @code
 * 		kStatus_Success
 * 		kStatus_Fail
 * @endcode
 */
status_t bmp280WhoAmI(void);

/*!
 * @brief Lee temperatura, humedad y presión del sensor BME280
 * @param data	apuntador de memoria  a estructura donde almacenar los  datos
 * @return	resultado ejecución
 * @code
 * 		kStatus_Success
 * 		kStatus_Fail
 * @endcode
 */
status_t	bmp280ReadData(bmp280_data_t *data );

/*!
 * @brief Inicialización de registros en sensor BME280
 * @return	resultado ejecución
 * @code
 * 		kStatus_Success
 * 		kStatus_Fail
 * @endcode
 */
status_t bmp280Init(void);

/** @} */ // end of X group
/** @} */ // end of X group

#endif /* IOT_SDK_PERIPHERALS_IOT_SDK_PERIPHERALS_BMP280_H_ */
