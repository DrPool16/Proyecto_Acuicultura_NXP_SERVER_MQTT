/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PERIPHERALS_H_
#define _PERIPHERALS_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "fsl_common.h"
#include "fsl_adc16.h"
#include "fsl_lptmr.h"
#include "fsl_lpuart.h"
#include "fsl_clock.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/
/* Definitions for BOARD_InitPeripherals functional group */
/* Alias for ADC0 peripheral */
#define ADC0_PERIPHERAL ADC0
/* Definition of custom name for ADC0 configuration #0 (channel 7b, control group 0) */
#define ADC0_P_BIN_0 0U
/* Definition of custom name for ADC0 configuration #1 (channel 6b, control group 0) */
#define ADC0_P_BIN_1 1U
/* Definition of custom name for ADC0 configuration #2 (channel 4b, control group 0) */
#define ADC0_P_BIN_2 2U
/* Definition of custom name for ADC0 configuration #3 (channel 23, control group 0) */
#define ADC0_P_BIN_3 3U
/* Definition of custom name for ADC0 configuration #4 (channel 14, control group 0) */
#define ADC0_P_BIN_4 4U
/* Definition of custom name for ADC0 configuration #5 (channel 0, control group 0) */
#define ADC0_P_BIN_5 5U
/* Definition of custom name for ADC0 configuration #6 (channel 3, control group 0) */
#define ADC0_P_BIN_6 6U
/* Definition of custom name for ADC0 configuration #7 (channel 12, control group 0) */
#define ADC0_P_BIN_7 7U
/* Definition of custom name for ADC0 configuration #8 (channel 9, control group 0) */
#define ADC0_P_BIN_8 8U
/* Definition of custom name for ADC0 configuration #9 (channel 8, control group 0) */
#define ADC0_P_ATL_9 9U
/* ADC0 interrupt vector ID (number). */
#define ADC0_IRQN ADC0_IRQn
/* ADC0 interrupt handler identifier. */
#define ADC0_IRQHANDLER ADC0_IRQHandler
/* Channel 0 (SE.7b) conversion control group. */
#define ADC0_CH0_CONTROL_GROUP 0
/* Channel 1 (SE.6b) conversion control group. */
#define ADC0_CH1_CONTROL_GROUP 0
/* Channel 2 (SE.4b) conversion control group. */
#define ADC0_CH2_CONTROL_GROUP 0
/* Channel 3 (SE.23) conversion control group. */
#define ADC0_CH3_CONTROL_GROUP 0
/* Channel 4 (SE.14) conversion control group. */
#define ADC0_CH4_CONTROL_GROUP 0
/* Channel 5 (SE.0) conversion control group. */
#define ADC0_CH5_CONTROL_GROUP 0
/* Channel 6 (SE.3) conversion control group. */
#define ADC0_CH6_CONTROL_GROUP 0
/* Channel 7 (SE.12) conversion control group. */
#define ADC0_CH7_CONTROL_GROUP 0
/* Channel 8 (SE.9) conversion control group. */
#define ADC0_CH8_CONTROL_GROUP 0
/* Channel 9 (SE.8) conversion control group. */
#define ADC0_CH9_CONTROL_GROUP 0
/* BOARD_InitPeripherals defines for LPTMR0 */
/* Definition of peripheral ID */
#define LPTMR0_PERIPHERAL LPTMR0
/* Definition of the clock source frequency */
#define LPTMR0_CLK_FREQ 1000UL
/* Definition of the prescaled clock source frequency */
#define LPTMR0_INPUT_FREQ 1000UL
/* Definition of the timer period in us */
#define LPTMR0_USEC_COUNT 1000000UL
/* Definition of the timer period in number of ticks */
#define LPTMR0_TICKS 1000UL
/* LPTMR0 interrupt vector ID (number). */
#define LPTMR0_IRQN LPTMR0_IRQn
/* LPTMR0 interrupt handler identifier. */
#define LPTMR0_IRQHANDLER LPTMR0_IRQHandler
/* Definition of peripheral ID */
#define LPUART0_PERIPHERAL LPUART0
/* Definition of the clock source frequency */
#define LPUART0_CLOCK_SOURCE 48000000UL
/* LPUART0 interrupt vector ID (number). */
#define LPUART0_SERIAL_RX_TX_IRQN LPUART0_IRQn
/* LPUART0 interrupt handler identifier. */
#define LPUART0_SERIAL_RX_TX_IRQHANDLER LPUART0_IRQHandler

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
extern adc16_channel_config_t ADC0_channelsConfig[10];
extern const adc16_config_t ADC0_config;
extern const adc16_channel_mux_mode_t ADC0_muxMode;
extern const lptmr_config_t LPTMR0_config;
extern const lpuart_config_t LPUART0_config;

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/

void BOARD_InitPeripherals(void);

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void);

#if defined(__cplusplus)
}
#endif

#endif /* _PERIPHERALS_H_ */
