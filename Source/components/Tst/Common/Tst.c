#include "Tst_Cfg.h"

#include "Plot_Cfg.h"

int16_t* tst_buffer = NULL;

void Tst_Init(void)
{
    if (tst_buffer != NULL) 
    {
        free(tst_buffer);
    }

    tst_buffer = (int16_t*)malloc(OLED_SCREEN_BYTES_WIDTH * sizeof(int16_t));
}

void Tst_Clear(void)
{
    if (tst_buffer == NULL)
    {
        return;
    }
    memset(tst_buffer, 0, TEST_BUFFER_SIZE * sizeof(int16_t));
}