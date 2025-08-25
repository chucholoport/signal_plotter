#include "Needle_Cfg.h"

#include "Hmi_Cfg.h"
#include "Ruler_Cfg.h"
#include "Symbol_Cfg.h"
#include "Bitmap_Cfg.h"

int16_t needle_buffer[RULER_CENTS_RANGE] = {0};

/* Bitmap buffer for HMI display */
uint8_t needle_bitmap[BITMAP_SIZE] = {0};

Dsp_Cfg_t needle_buffer_cfg;

/* Copy block configuration from HMI configuration */
HmiBlock_Cfg_t needle_cfg;

void Needle_Clear(void)
{
    memset(needle_buffer, DSP_MAX, RULER_CENTS_RANGE * sizeof(int16_t));
}

void Needle_Fill()
{    
    Needle_Clear();

    int8_t  cents = current_note.cents;
    uint8_t index = 0U;

    cents = CLAMP(cents, MIN_CENTS, MAX_CENTS - 1);
    index = cents - MIN_CENTS;

    needle_buffer[index] = DSP_MIN;
}

void Needle_Init(void)
{
    /* Set configuration */
    needle_cfg = hmi_cfg.needle;
    needle_buffer_cfg  = NEEDLE_BUFFER_CFG;
}

void Needle_Run()
{
    Needle_Fill();
    Bitmap_Run(&needle_buffer_cfg, &needle_cfg, needle_buffer, needle_bitmap);
}