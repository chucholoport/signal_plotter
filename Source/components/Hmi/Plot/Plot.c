#include "Plot_Cfg.h"

#include "Hmi_Cfg.h"
#include "Dsp_Cfg.h"

/**
 * @file    Plot.c
 * @brief   Implementation of dynamic signal buffer plotter.
 * @details Functions execute processing for plotting signal buffer.
 */

/* Copy block configuration from HMI configuration */
HmiBlock_Cfg_t plot_cfg;

/* Bitmap buffer for HMI display */
uint8_t plot_bitmap[BITMAP_SIZE] = {0};

void Plot_Init(void)
{
    /* Set configuration */
    plot_cfg = hmi_cfg.plot;
}

void Plot_Run(void)
{

    /* Run DSP Buffer filling & metrics obtention */
    Dsp_Run();

    /* Integrate DSP Buffer & Bitmap converter*/
    Bitmap_Run(&dsp_cfg, &plot_cfg, dsp_buffer, plot_bitmap);
}