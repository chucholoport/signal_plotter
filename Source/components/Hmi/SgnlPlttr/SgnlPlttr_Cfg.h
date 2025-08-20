#ifndef SGNLPLTTR_CFG_H
#define SGNLPLTTR_CFG_H

#include <stdint.h>

#include "Hmi_Cfg.h"
#include "Dsp_Cfg.h"

/**
 * @file SgnlPlttr_Cfg.h
 * @brief Contains macros and function prototypes for processing an input ADC signal
 *        and displaying the results on a 128x64 OLED display.
 *
 * This header centralizes all necessary definitions and declarations required for
 * acquiring, processing, and visualizing analog signals using an ADC and rendering
 * the processed data on a 128x64 pixel OLED screen. It is intended to be included
 * in projects where real-time signal monitoring and graphical representation are needed.
 */

/* -------------------------------------------------------------------------- */
/* Signal Plotter Parameters                                                  */
/* Defines screen geometry and buffer layout for OLED rendering               */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* Bitmap Parameters                                                          */
/* Defines bitmap size and pixel manipulation macros                          */
/* -------------------------------------------------------------------------- */
#define OLED_BITMAP_SIZE            (OLED_SCREEN_BYTES_NO)

/* -------------------------------------------------------------------------- */
/* Coordinate Mapping Macros                                                  */
/* Provide safe computations for mapping signal values to screen coordinates  */
/* -------------------------------------------------------------------------- */
#define GET_SOURCE_INDEX(x, source_size, x_range)  ((x) * (source_size - 1) / (x_range - 1))
#define CLAMP(val, min, max)                       (((val) < (min))                          ? (min)                : (((val) > (max)) ? (max) : (val)))
#define MAP_TO_X(local, offset, limit)             ((uint8_t)(((offset) + (local) < (limit)) ? ((offset) + (local)) : ((limit) - 1)))
#define MAP_TO_Y(local, offset, limit, min, max)   ((uint8_t)((limit) - (((local) - (min)) * ((limit) - (offset)) / ((max) - (min)))))
#define MAP_TO_BITMAP(coord, offset)               ((uint8_t)((coord) - (offset)))

/* -------------------------------------------------------------------------- */
/* Bitmap Utility Macros                                                      */
/* Provide safe computations for bitmap pixel manipulation                    */
/* -------------------------------------------------------------------------- */
#define BITMAP_BYTE_INDEX(x, y, width)          (((y) / 8) * (width) + (x))
#define BITMAP_BIT_MASK(y)                      (1U << ((y) % 8))
#define BITMAP_DRAW_PIXEL(bitmap, x, y, width)  ((bitmap)[BITMAP_BYTE_INDEX((x), (y), (width))] |= BITMAP_BIT_MASK((y)))

typedef struct 
{
    uint16_t bitmap_size;   /**< Size of the signal buffer */
    uint8_t  x0;            /**< Start X index for plotting */
    uint8_t  x1;            /**< Limit X index for plotting */
    uint8_t  y0;            /**< Start Y index for plotting */
    uint8_t  y1;            /**< Limit Y index for plotting */
    uint8_t  width;         /**< Plot width */
    uint8_t  height;        /**< Plot height */
} SgnlPlttr_Cfg_t;

extern SgnlPlttr_Cfg_t plt_cfg;

#define SGNLPLTTR_CFG(hmi_cfg, buffer_size)  \
    (SgnlPlttr_Cfg_t){                       \
        .bitmap_size = (buffer_size),        \
        .x0          = (hmi_cfg).x0,         \
        .x1          = (hmi_cfg).x1,         \
        .y0          = (hmi_cfg).y0,         \
        .y1          = (hmi_cfg).y1,         \
        .width       = (hmi_cfg).width,      \
        .height      = (hmi_cfg).height      \
    }

/* -------------------------------------------------------------------------- */
/* External Buffers                                                           */
/* Used for intermediate signal shaping and final display rendering           */
/* -------------------------------------------------------------------------- */

/**
 * @brief Output buffer representing the OLED bitmap.
 * 
 * This buffer is sent to the display driver for rendering.
 */
extern uint8_t oled_bitmap[OLED_SCREEN_BYTES_NO];

extern uint8_t shaped_buffer[OLED_SCREEN_WIDTH];

/* -------------------------------------------------------------------------- */
/* Signal Plotter Public Function Prototypes                                   */
/* -------------------------------------------------------------------------- */

void SgnlPlttr_Init(void);

/** 
 * @brief Clears the OLED bitmap buffer.
 * 
 * Resets the bitmap to all zeros, effectively clearing the display.
 */
void SgnlPlttr_ClearBitmap(void);

/**
 * @brief Converts normalized signal buffer values to a shaped buffer for OLED display.
 *
 * @param dsp_cfg Pointer to the DSP configuration structure for scaling parameters.
 * @param buffer Pointer to the normalized signal buffer.
 * @param bitmap_cfg Pointer to the Bitmap configuration structure for scaling parameters.
 * @param shaped Pointer to the output shaped buffer for the OLED display.
 */
void SgnlPlttr_FillShapedBuffer(DspBffr_Cfg_t* dsp_cfg, int16_t* buffer, SgnlPlttr_Cfg_t* bitmap_cfg, uint8_t* bitmap);

/**
 * @brief Displays the provided bitmap on the OLED screen.
 *
 * @param bitmap Pointer to the bitmap buffer to be displayed.
 */
void SgnlPlttr_DisplayBitmap(SgnlPlttr_Cfg_t* bitmap_cfg, uint8_t* bitmap);

void SgnlPlttr_Run(DspBffr_Cfg_t* dsp_cfg, int16_t* buffer, SgnlPlttr_Cfg_t* plt_cfg, uint8_t* bitmap);

#endif