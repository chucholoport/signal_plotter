#include "Bitmap_Cfg.h"

#include "Dsp_Cfg.h"
#include "Hmi_Cfg.h"

#include "ssd1306.h"

/**
 * @file   Bitmap.c
 * @brief Implementation for Bitmap.
 * @details This file contains the implementation for the Bitmap HMI Blocks.
 */

void Bitmap_Clear(uint8_t* bitmap)
{
    memset(bitmap, 0, BITMAP_SIZE * sizeof(uint8_t));
}

void Bitmap_Shape(Dsp_Cfg_t* i_cfg, HmiBlock_Cfg_t* o_cfg, int16_t* buffer, uint8_t* bitmap)
{
    uint16_t buffer_size = i_cfg->size - 1;
    int16_t buffer_max   = i_cfg->max  - 1;
    int16_t buffer_min   = i_cfg->min;

    uint8_t  block_x0     = o_cfg->x0;
    uint8_t  block_y0     = o_cfg->y0;
    uint8_t  block_x1     = o_cfg->x1;
    uint8_t  block_y1     = o_cfg->y1;
    uint8_t  block_width  = o_cfg->width;

    int16_t source_index   = 0;
    int16_t source_value   = 0;
    int16_t previous_value = 0;

    uint8_t x  = 0U;       
    uint8_t y  = 0U;
    
    uint8_t yp = 0U;
    uint8_t y0 = 0U;
    uint8_t y1 = 0U;

    /* Shape input buffer to bitmap size */
    for (uint8_t bitmap_index = 0; bitmap_index < block_width; bitmap_index++)
    {
        /* Map X & Y to source buffer index */
        source_index = GET_SOURCE_X(bitmap_index, buffer_size, block_width);
        source_value = GET_SOURCE_Y(buffer[source_index], buffer_min, buffer_max);

        if (bitmap_index > 0)
        {
            previous_value = GET_SOURCE_Y(buffer[source_index - 1], buffer_min, buffer_max);
        }
        else
        {
            previous_value = GET_SOURCE_Y(buffer[source_index + 1], buffer_min, buffer_max);
        }

        /* Relative position to Block */
        x = SET_BLOCK_X(bitmap_index, block_x0, block_x1);
        y = SET_BLOCK_Y(source_value, block_y0, block_y1, buffer_min, buffer_max);

        yp = SET_BLOCK_Y(previous_value, block_y0, block_y1, buffer_min, buffer_max);

        y0 = MIN(y, yp);
        y1 = MAX(y, yp);
        
        for (uint8_t dy = y0; dy <= y1; dy++)
        {
            BITMAP_SET_PIXEL(bitmap, x, dy, block_width);
        }
    }
}

void Bitmap_Show(HmiBlock_Cfg_t* cfg, uint8_t* bitmap)
{
    ssd1306_drawBufferFast(cfg->x0, cfg->y0, cfg->width, cfg->height, bitmap);
}

void Bitmap_Run(Dsp_Cfg_t* i_cfg, HmiBlock_Cfg_t* o_cfg, int16_t* buffer, uint8_t* bitmap)
{
    Bitmap_Clear(bitmap);
    Bitmap_Shape(i_cfg, o_cfg, buffer, bitmap);
    Bitmap_Show(o_cfg, bitmap);
}