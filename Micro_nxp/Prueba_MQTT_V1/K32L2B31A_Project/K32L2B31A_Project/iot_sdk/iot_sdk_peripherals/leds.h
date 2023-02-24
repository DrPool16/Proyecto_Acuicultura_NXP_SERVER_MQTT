/*! @file : leds.h
 * @author  Ernesto Andres Rincon Cruz
 * @version 1.0.0
 * @date    28 ago. 2021
 * @brief   Driver para controlar LEDs de tarjeta FRDM-K32L2B3
 * @details
 *
 */
#ifndef IOT_SDK_PERIPHERALS_LEDS_H_
#define IOT_SDK_PERIPHERALS_LEDS_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/


/*!
 * @addtogroup PERIPHERALS
 * @{
 */
/*!
 * @addtogroup LEDS
 * @{
 */
/*******************************************************************************
 * Public Definitions
 ******************************************************************************/

/*******************************************************************************
 * External vars
 ******************************************************************************/

/*******************************************************************************
 * Public vars
 ******************************************************************************/

/*******************************************************************************
 * Public Prototypes
 ******************************************************************************/
/*!
 * @brief enciende led verde de tarjeta FRDM-K32L2B3
 *
 */
 void encender_led_verde();
 /*---------------------------------------------------------------*/
 /*!
  * @brief apaga led verde de tarjeta FRDM-K32L2B3
  *
  */
 void apagar_led_verde();
 /*!
  * @brief invierte estado de led rojo de tarjeta FRDM-K32L2B3
  *
  */
 void toggle_led_rojo();

/** @} */ // end of X LEDS
/** @} */ // end of X PERIPHERALS

#endif /* IOT_SDK_PERIPHERALS_LEDS_H_ */
