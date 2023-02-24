/*! @file : botones.h
 * @author  Ernesto Andres Rincon Cruz
 * @version 1.0.0
 * @date    4 sept. 2021
 * @brief   Driver para lectura de botones en FRDM-K32L2B
 * @details
 *
 */
#ifndef IOT_SDK_PERIPHERALS_BOTONES_H_
#define IOT_SDK_PERIPHERALS_BOTONES_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "peripherals.h"
#include "fsl_gpio.h"
/*!
 * @addtogroup PERIPHERALS
 * @{
 */
/*!
 * @addtogroup BOTONES
 * @{
 */
/*******************************************************************************
 * Public Definitions
 ******************************************************************************/
#define TECLA_DER_CAMBIO	0xFE
#define TECLA_IZQ_CAMBIO	0xFD

/*******************************************************************************
 * External vars
 ******************************************************************************/

/*******************************************************************************
 * Public vars
 ******************************************************************************/

/*******************************************************************************
 * Public Prototypes
 ******************************************************************************/
 bool boton1LeerEstado();
 bool boton2LeerEstado();

 void Key_Task_Init(void);
 void Key_Task_Run(void);
 char Boton1_Presionado(void);

/** @} */ // end of BOTONES group
/** @} */ // end of PERIPHERALS group

#endif /* IOT_SDK_PERIPHERALS_BOTONES_H_ */
