#ifndef SEVENSEG_H_
#define SEVENSEG_H_

#include "stm32f4xx_hal.h"

typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
} seg_pin_t;

typedef struct {
    seg_pin_t segments[8];   // A,B,C,D,E,F,G,DP
    seg_pin_t digits[4];     // COM1–COM4
    uint8_t currentDigit;
    uint8_t buffer[4];
} SevenSeg_Handle;


// ---- API ----
void SevenSeg_Init_Set_Segments(SevenSeg_Handle *h);
void SevenSeg_Init(SevenSeg_Handle *h);
void SevenSeg_DisplayNumber(SevenSeg_Handle *h, uint16_t num);
void SevenSeg_Task(SevenSeg_Handle *h);

#endif
