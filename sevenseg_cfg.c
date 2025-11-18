#pragma once
#include "stm32f4xx_hal.h"

/* Segment pins (A..G, DP) */
#define SEG_A_Pin GPIO_PIN_6
#define SEG_A_GPIO_Port GPIOC

#define SEG_B_Pin GPIO_PIN_4
#define SEG_B_GPIO_Port GPIOC

#define SEG_C_Pin GPIO_PIN_3
#define SEG_C_GPIO_Port GPIOC

#define SEG_D_Pin GPIO_PIN_1
#define SEG_D_GPIO_Port GPIOC

#define SEG_E_Pin GPIO_PIN_2
#define SEG_E_GPIO_Port GPIOC

#define SEG_F_Pin GPIO_PIN_5
#define SEG_F_GPIO_Port GPIOC

#define SEG_G_Pin GPIO_PIN_0
#define SEG_G_GPIO_Port GPIOC

#define SEG_DP_Pin GPIO_PIN_7
#define SEG_DP_GPIO_Port GPIOC

/* Common (COM) digit pins (COM1..COM4) */
#define COM_1_Pin GPIO_PIN_11
#define COM_1_GPIO_Port GPIOC

#define COM_2_Pin GPIO_PIN_10
#define COM_2_GPIO_Port GPIOC

#define COM_3_Pin GPIO_PIN_9
#define COM_3_GPIO_Port GPIOC

#define COM_4_Pin GPIO_PIN_8
#define COM_4_GPIO_Port GPIOC

// ---- Funkcja inicjalizująca wszystkie piny wyświetlacza ----
static inline void SevenSeg_HW_Init(void)
{
    // Włącz zegar GPIOC
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // wyzeruj wszystkie piny
    HAL_GPIO_WritePin(GPIOC, SEG_G_Pin|SEG_D_Pin|SEG_E_Pin|SEG_C_Pin
                            |SEG_B_Pin|SEG_F_Pin|SEG_A_Pin|SEG_DP_Pin
                            |COM_4_Pin|COM_3_Pin|COM_2_Pin|COM_1_Pin, GPIO_PIN_RESET);

    // ustaw piny jako wyjścia push-pull
    GPIO_InitStruct.Pin = SEG_G_Pin|SEG_D_Pin|SEG_E_Pin|SEG_C_Pin
                            |SEG_B_Pin|SEG_F_Pin|SEG_A_Pin|SEG_DP_Pin
                            |COM_4_Pin|COM_3_Pin|COM_2_Pin|COM_1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}
