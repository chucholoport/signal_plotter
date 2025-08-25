#include "Ruler_Cfg.h"

#include "Hmi_Cfg.h"
#include "Symbol_Cfg.h"
#include "Bitmap_Cfg.h"

/** 
 * @file    Ruler.c
 * @brief   Implementation for Ruler component.
 * @details This file contains the implementation logic for the Ruler component.
 */

Dsp_Cfg_t ruler_buffer_cfg;

/* Copy block configuration from HMI configuration */
HmiBlock_Cfg_t ruler_cfg;

int16_t ruler_buffer[RULER_CENTS_RANGE] = {0};

/* Bitmap buffer for HMI display */
uint8_t ruler_bitmap[BITMAP_SIZE] = {0};


void Ruler_Draw(void)
{
    uint8_t index      = 0U;
    int16_t max_height = DSP_MAX / 2;
    int16_t mid_height = DSP_MAX / 4; 
    int16_t min_height = 0; 
    
    char symbol[RULER_CENTS_RANGE];

    for (int16_t cents = RULER_MIN_CENTS; cents < RULER_MAX_CENTS; cents += CENTS_STEP)
    {
        index = RULER_CENTS_TO_X(cents);

        if (cents % 20 == 0)
        {
            /* Main mark */
            ruler_buffer[index] = max_height; 
            symbol[index] = '|';
        }            
        else if (cents % 10 == 0)
        {
            /* Middle mark */
            ruler_buffer[index] = mid_height;
            symbol[index] = ':';
        }
        else
        {
            /* Minor mark */
            ruler_buffer[index] = min_height;
            symbol[index] = '.';
        }
        printf("cent %+3d → index %3d → symbol %c\n", cents, index, symbol[index]);
    }
    symbol[100] = '\n';
    printf("%s", symbol);
}


void Ruler_Init(void)
{
    /* Set configuration */
    ruler_cfg         = hmi_cfg.ruler;
    ruler_buffer_cfg  = RULER_BUFFER_CFG;

    /* Fill buffer with drawing */
    Ruler_Draw();

    /* Display bitmap */
    Bitmap_Shape(&ruler_buffer_cfg, &ruler_cfg, ruler_buffer, ruler_bitmap);
    Bitmap_Show(&ruler_cfg, ruler_bitmap);
}

