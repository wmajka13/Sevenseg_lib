Biblioteka działa dla wyświetlacza siedmiosegmentowego umieszczonego na rozszerzeniu do stm32: KA-Nucleo-Multisensor (https://kamami.pl/kamod-kamami/563404-ka-nucleo-multisensor-shield-dla-stm32-nucleo-z-wyswietlaczem-i-czujnikami-mems-5906623433278.html)

Najpierw należy wrzucić pliki .h do folderu Inc, natomiast .c do Src

Dalej w main.c zrobić:
#include "sevenseg_cfg.h"
#include "sevenseg.h"

Przy używaniu biblioteki należy najpierw:
- Użyć funkcji static inline void SevenSeg_HW_Init(void) - żeby zainicjalizować odpowiednie piny
- Stworzyć strukturę odpowiadającą za wyświetlacz: SevenSeg_Handle seg; (w każdej funkcji *h to wksaźnik na strukturę, czyli należy jako argument podawać &seg)
- Użyć funkjcji void SevenSeg_Init_Set_Segments(SevenSeg_Handle *h) - żeby przypisać odpowiednie piny i porty do struktury
- W main używać void SevenSeg_DisplayNumber(SevenSeg_Handle *h, uint16_t num);
- Natomiast w przerwaniu od zegara* void SevenSeg_Task(SevenSeg_Handle *h);

*Ustawianie zegara: Należy ustawić zegar z przerwaniami tak żeby przerwanie pojawiało się co 1ms, wówczas multipleksowanie będzie możliwe