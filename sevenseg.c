#include "sevenseg.h"
#include "sevenseg_cfg.h"


// LUT 0–9
static const uint8_t SEGMENT_LUT[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

// Przypisanie pinów i portów
void SevenSeg_Init_Set_Segments(SevenSeg_Handle *h) {
    h->segments[0] = (seg_pin_t){SEG_A_GPIO_Port, SEG_A_Pin};
    h->segments[1] = (seg_pin_t){SEG_B_GPIO_Port, SEG_B_Pin};
    h->segments[2] = (seg_pin_t){SEG_C_GPIO_Port, SEG_C_Pin};
    h->segments[3] = (seg_pin_t){SEG_D_GPIO_Port, SEG_D_Pin};
    h->segments[4] = (seg_pin_t){SEG_E_GPIO_Port, SEG_E_Pin};
    h->segments[5] = (seg_pin_t){SEG_F_GPIO_Port, SEG_F_Pin};
    h->segments[6] = (seg_pin_t){SEG_G_GPIO_Port, SEG_G_Pin};
    h->segments[7] = (seg_pin_t){SEG_DP_GPIO_Port, SEG_DP_Pin};

    h->digits[0] = (seg_pin_t){COM_1_GPIO_Port, COM_1_Pin};
    h->digits[1] = (seg_pin_t){COM_2_GPIO_Port, COM_2_Pin};
    h->digits[2] = (seg_pin_t){COM_3_GPIO_Port, COM_3_Pin};
    h->digits[3] = (seg_pin_t){COM_4_GPIO_Port, COM_4_Pin};
}


void SevenSeg_Init(SevenSeg_Handle *h) {

    h->currentDigit = 0;

    for (int i = 0; i < 4; i++) {
        HAL_GPIO_WritePin(h->digits[i].port, h->digits[i].pin, GPIO_PIN_SET);
    }
}

//Ustawia odpowiednie segmenty żeby wyświetlić daną cyfrę
static void SevenSeg_SetSegments(SevenSeg_Handle *h, uint8_t number) {
    uint8_t binary = SEGMENT_LUT[number];

    for (uint8_t i = 0; i < 8; i++) {
        HAL_GPIO_WritePin(h->segments[i].port,
                          h->segments[i].pin,
                          (binary & (1 << i)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
}


void SevenSeg_DisplayNumber(SevenSeg_Handle *h, uint16_t num) {
    h->buffer[3] = (num / 1)    % 10;
    h->buffer[2] = (num / 10)   % 10;
    h->buffer[1] = (num / 100)  % 10;
    h->buffer[0] = (num / 1000) % 10;
}


void SevenSeg_Task(SevenSeg_Handle *h) {

    // wygaszamy wszystkie cyfry
    for (int i = 0; i < 4; i++) {
        HAL_GPIO_WritePin(h->digits[i].port, h->digits[i].pin, GPIO_PIN_SET);
    }

    // segmenty aktualnej cyfry
    SevenSeg_SetSegments(h, h->buffer[h->currentDigit]);

    // włącz właściwy COM
    HAL_GPIO_WritePin(h->digits[h->currentDigit].port,
                      h->digits[h->currentDigit].pin,
                      GPIO_PIN_RESET);

    // następna cyfra
    h->currentDigit = (h->currentDigit + 1) % 4;
}
