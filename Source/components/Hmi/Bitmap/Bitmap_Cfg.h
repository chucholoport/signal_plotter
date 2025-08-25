#ifndef BITMAP_CFG_H
#define BITMAP_CFG_H

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "Dsp_Cfg.h"
#include "Hmi_Cfg.h"

/**
 * @file   Bitmap_Cfg.h
 * @brief Configuration for Bitmap.
 * @details This file contains the configuration settings for the Bitmap HMI Blocks.
 */

#define BITMAP_SIZE     (OLED_SCREEN_BYTES_TOTAL)

#define CLAMP(val, min, max) (((val) < (min)) ? (min) : (((val) > (max)) ? (max) : (val)))
#define MIN(a,b)             ((a) < (b) ? (a) : (b))
#define MAX(a,b)             ((a) > (b) ? (a) : (b))

/* -------------------------------------------------------------------------- */
/* Coordinate Mapping Macros                                                  */
/* Provide safe computations for mapping signal values to screen coordinates  */
/* -------------------------------------------------------------------------- */
#define GET_SOURCE_X(x, source_width, block_width)          ((x) * (source_width - 1) / (block_width - 1))
#define GET_SOURCE_Y(y, min, max)                           (CLAMP((y), (min), (max)))

#define SET_BLOCK_X(x, offset, limit)                       ((((offset) + (x) < (limit)) ? ((offset) + (x)) : ((limit) - 1)) - (offset))
#define SET_BLOCK_Y(y, offset, limit, min, max)             (((limit) - (((y) - (min)) * ((limit) - (offset)) / ((max) - (min)))) - (offset))

#define BITMAP_BYTE_INDEX(x, y, width)                      (((y) / BYTE_SIZE) * (width) + (x))
#define BITMAP_BIT_MASK(y)                                  (1U << ((y) % BYTE_SIZE))
#define BITMAP_SET_PIXEL(bitmap, x, y, width)               ((bitmap)[BITMAP_BYTE_INDEX((x), (y), (width))] |= BITMAP_BIT_MASK((y)))

/* -------------------------------------------------------------------------- */
/* Bitmap Utility Macros                                                      */
/* Provide safe computations for bitmap pixel manipulation                    */
/* -------------------------------------------------------------------------- */
//#define BITMAP_BYTE_INDEX(x, y, width)                      (((y) / BYTE_SIZE) * (width) + (x))
//#define BITMAP_BIT_MASK(y)                                  (1U << ((y) % BYTE_SIZE))
//#define BITMAP_SET_PIXEL(bitmap, x, y, width)               ((bitmap)[BITMAP_BYTE_INDEX((x), (y), (width))] |= BITMAP_BIT_MASK((y)))

/* -------------------------------------------------------------------------- */
/* Bitmap Public Function Prototypes                                          */
/* -------------------------------------------------------------------------- */

/** 
 * @brief Clears the bitmap buffer.
 * 
 * Resets the bitmap to all zeros, effectively clearing the display.
 */
void Bitmap_Clear(uint8_t* bitmap);

/**
 * @brief Converts buffer values to a shaped buffer for OLED display.
 *
 * @param i_cfg Pointer to the buffer configuration structure for scaling parameters.
 * @param o_cfg Pointer to the Bitmap configuration structure for scaling parameters.
 * @param buffer Pointer to the normalized signal buffer.
 * @param bitmap Pointer to the output shaped buffer for the OLED display.
 */
void Bitmap_Shape(Dsp_Cfg_t* i_cfg, HmiBlock_Cfg_t* o_cfg, int16_t* buffer, uint8_t* bitmap);

/**
 * @brief Displays the provided bitmap on the OLED screen.
 *
 * @param cfg Pointer to the Bitmap configuration structure for scaling parameters.
 * @param bitmap Pointer to the bitmap buffer to be displayed.
 */
void Bitmap_Show(HmiBlock_Cfg_t* cfg, uint8_t* bitmap);

/**
 * @brief Runs bitmap creation from buffer for OLED display.
 *
 * @param i_cfg Pointer to the buffer configuration structure for scaling parameters.
 * @param o_cfg Pointer to the Bitmap configuration structure for scaling parameters.
 * @param buffer Pointer to the normalized signal buffer.
 * @param bitmap Pointer to the output shaped buffer for the OLED display.
 */
void Bitmap_Run(Dsp_Cfg_t* i_cfg, HmiBlock_Cfg_t* o_cfg, int16_t* buffer, uint8_t* bitmap);

#endif /* BITMAP_CFG_H */