#include "Tst_Cfg.h"

#include "SgnlPlttr_Cfg.h"

int16_t* tst_buffer = NULL;

void TstBffr_Init(void)
{
    if (tst_buffer != NULL) 
    {
        free(tst_buffer);
    }

    tst_buffer = (int16_t*)malloc(OLED_SCREEN_WIDTH * sizeof(int16_t));
}

void TstBffr_ClearBuffer(void)
{
    if (tst_buffer == NULL)
    {
        return;
    }
    memset(tst_buffer, 0, TEST_BUFFER_SIZE * sizeof(int16_t));
}