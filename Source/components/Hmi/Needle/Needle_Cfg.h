#ifndef NEEDLE_CFG_H
#define NEEDLE_CFG_H

#include <stdint.h>
#include <string.h>

#include "Hmi_Cfg.h"
#include "Ruler_Cfg.h"
#include "Symbol_Cfg.h"
#include "Bitmap_Cfg.h"

/** 
 * @file    Needle_Cfg.h
 * @brief   Configuration for Needle component.
 * @details This file contains the configuration settings for the Needle component.
 */

#define NEEDLE_BUFFER_CFG            \
    (Dsp_Cfg_t){                    \
        .size = RULER_CENTS_RANGE,  \
        .max  = DSP_MAX,            \
        .min  = DSP_MIN,            \
    }


extern int16_t needle_buffer[RULER_CENTS_RANGE];

extern uint8_t needle_bitmap[BITMAP_SIZE];

extern Dsp_Cfg_t needle_buffer_cfg;

extern HmiBlock_Cfg_t needle_cfg;


void Needle_Clear(void);

void Needle_Fill(void);

void Needle_Init(void);

void Needle_Run(void);

#endif