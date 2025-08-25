#ifndef PLOT_CFG_H
#define PLOT_CFG_H

#include <stdint.h>

#include "Dsp_Cfg.h"
#include "Hmi_Cfg.h"
#include "Bitmap_Cfg.h"

/**
 * @file Plot_Cfg.h
 * @brief Contains macros and function prototypes for processing an input ADC signal
 *        and displaying the results on a 128x64 OLED display.
 *
 * This header centralizes all necessary definitions and declarations required for
 * acquiring, processing, and visualizing analog signals using an ADC and rendering
 * the processed data on a 128x64 pixel OLED screen. It is intended to be included
 * in projects where real-time signal monitoring and graphical representation are needed.
 */

/* -------------------------------------------------------------------------- */
/* External Buffers                                                           */
/* Used for intermediate signal shaping and final display rendering           */
/* -------------------------------------------------------------------------- */

/**
 * @brief Output buffer representing the OLED bitmap.
 * 
 * This buffer is sent to the display driver for rendering.
 */
extern uint8_t plot_bitmap[BITMAP_SIZE];

HmiBlock_Cfg_t plot_cfg;

/* -------------------------------------------------------------------------- */
/* Plot Public Function Prototypes                                            */
/* -------------------------------------------------------------------------- */

/** 
 * @brief Initializes the plot block.
 * 
 * This block displays a DSP buffer plotted on HMI.
 */
void Plot_Init(void);

/** 
 * @brief Runs the plot block.
 * 
 * This function integrates DSP buffer & Bitmap conversor for HMI display.
 */
void Plot_Run(void);

#endif /* PLOT_CFG_H */