#ifndef RULER_CFG_H
#define RULER_CFG_H

#include <stdint.h>
#include <string.h>

#include "Hmi_Cfg.h"
#include "Symbol_Cfg.h"
#include "Bitmap_Cfg.h"

/** 
 * @file    Ruler_Cfg.h
 * @brief   Configuration for Ruler component.
 * @details This file contains the configuration settings for the Ruler component.
 */

#define RULER_MIN_CENTS                 (MIN_CENTS * SAMPLES_PER_CENT)
#define RULER_MAX_CENTS                 (MAX_CENTS * SAMPLES_PER_CENT)
#define RULER_CENTS_RANGE               (CENTS_RANGE * SAMPLES_PER_CENT)

#define RULER_CENTS_TO_X(cents)         (((cents) - RULER_MIN_CENTS))         

#define RULER_BUFFER_CFG            \
    (Dsp_Cfg_t){                    \
        .size = RULER_CENTS_RANGE,  \
        .max  = DSP_MAX,            \
        .min  = DSP_MIN,            \
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

extern int16_t ruler_buffer[RULER_CENTS_RANGE];

extern uint8_t ruler_bitmap[BITMAP_SIZE];

extern Dsp_Cfg_t ruler_buffer_cfg;
extern Dsp_Cfg_t ruler_compact_cfg;

extern HmiBlock_Cfg_t ruler_cfg;

/* -------------------------------------------------------------------------- */
/* Ruler Public Function Prototypes                                           */
/* -------------------------------------------------------------------------- */

void Ruler_Draw(void);

void Ruler_Init(void);

#endif /* RULER_CFG_H */