#include "SgnlPlttr_Cfg.h"

#include "Hmi_Cfg.h"
#include "Dsp_Cfg.h"

#include "ssd1306.h"

/**
 * @file    SgnlPlttr.c
 * @brief   Implementation of dynamic signal buffer plotter.
 * @details Functions execute processing for plotting signal buffer.
 */

uint8_t oled_bitmap[OLED_BITMAP_SIZE] = {0};

SgnlPlttr_Cfg_t plt_cfg;

void SgnlPlttr_Init(void)
{
    plt_cfg = SGNLPLTTR_CFG(hmi_cfg.plot, OLED_BITMAP_SIZE);
}

void SgnlPlttr_ClearBitmap(void) 
{
    memset(oled_bitmap, 0, OLED_SCREEN_BYTES_NO * sizeof(uint8_t));
}

void SgnlPlttr_FillShapedBuffer(DspBffr_Cfg_t* dsp_cfg, int16_t* buffer, SgnlPlttr_Cfg_t* plt_cfg, uint8_t* bitmap)
{
    /* Initialize auxiliar variables */
    uint16_t src_idx = 0U;
    int16_t  plot_y  = 0U;
    uint8_t  x       = 0U;       
    uint8_t  y       = 0U;
    uint8_t  xp      = 0U;
    uint8_t  yp      = 0U;  
    
    /* Clear the bitmap */
    SgnlPlttr_ClearBitmap();

    /* Scale values */
    for (uint8_t plot_x = 0; plot_x < plt_cfg->width; ++plot_x)
    {   
        /* Map X to source buffer index */
        src_idx = GET_SOURCE_INDEX(plot_x, dsp_cfg->buffer_size, plt_cfg->width);

        /* Normalize & Clamp to defined limits */
        plot_y = CLAMP(buffer[src_idx], dsp_cfg->min, dsp_cfg->max);

        /* Linear scaling to bitmap */
        x = MAP_TO_X(plot_x, plt_cfg->x0, plt_cfg->x1);
        y = MAP_TO_Y(plot_y, plt_cfg->y0, plt_cfg->y1, dsp_cfg->min, dsp_cfg->max);

        /* Relative position to bitmap */
        xp = MAP_TO_BITMAP(x, plt_cfg->x0);
        yp = MAP_TO_BITMAP(y, plt_cfg->y0);

        /* Set pixel in bitmap */
        BITMAP_DRAW_PIXEL(bitmap, xp, yp, plt_cfg->width);
    }
}

void SgnlPlttr_DisplayBitmap(SgnlPlttr_Cfg_t* plt_cfg, uint8_t* bitmap)
{
    /* Send bitmap to display */
    ssd1306_drawBufferFast(plt_cfg->x0, plt_cfg->y0, plt_cfg->width, plt_cfg->height, bitmap);
}

void SgnlPlttr_Run(DspBffr_Cfg_t* dsp_cfg, int16_t* buffer, SgnlPlttr_Cfg_t* plt_cfg, uint8_t* bitmap)
{
    /* Convert signal to bitmap */
    SgnlPlttr_FillShapedBuffer(dsp_cfg, buffer, plt_cfg, bitmap);

    /* Display the signal */
    SgnlPlttr_DisplayBitmap(plt_cfg, bitmap);
}