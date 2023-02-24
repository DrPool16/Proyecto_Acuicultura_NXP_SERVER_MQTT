/*! @file : irq_lpuart0.h
 * @author  Ernesto Andres Rincon Cruz
 * @version 1.0.0
 * @date    11 sept. 2021
 * @brief   Driver para 
 * @details
 *
 */
#ifndef IOT_SDK_IRQ_IRQ_LPUART0_H_
#define IOT_SDK_IRQ_IRQ_LPUART0_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "peripherals.h"

/*!
 * @addtogroup IRQ
 * @{
 */
/*!
 * @addtogroup LPUART0
 * @{
 */
/*******************************************************************************
 * Public Definitions
 ******************************************************************************/
/*! @brief Ring buffer size (Unit: Byte). */
#define RX_RING_BUFFER_SIZE 	100
/*******************************************************************************
 * External vars
 ******************************************************************************/

/*******************************************************************************
 * Public vars
 ******************************************************************************/

/*******************************************************************************
 * Public Prototypes
 ******************************************************************************/
uint8_t pullByteDesdeBufferCircular();
int32_t numeroDeBytesDisponiblesEnBufferRx();
void ClearBufRx(void);
/** @} */ // end of LPUART0 group
/** @} */ // end of IRQ group

#endif /* IOT_SDK_IRQ_IRQ_LPUART0_H_ */
