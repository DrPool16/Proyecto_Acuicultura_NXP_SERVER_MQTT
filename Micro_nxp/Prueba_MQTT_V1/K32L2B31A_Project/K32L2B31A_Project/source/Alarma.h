/*
 * Alarma.c
 *
 *  Created on: 10/12/2022
 *      Author: ggaleano
 *      Modulo para manejo de tiempos en
 *      Segundos
 */

// Modulo Alarma
// Inicializa Alarma
void Alarma_Init(void);
// retorna el tiempo futuro de la alarma
uint32_t Alarma_Set(uint32_t time2Wait);
// retorna si la alarma se cumplio
char Alarma_Elapsed(uint32_t time2Test);
