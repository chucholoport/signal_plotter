#ifndef TUNER_CFG_H
#define TUNER_CFG_H

#include <stdint.h>
#include <string.h>
#include <math.h>

#include "Dsp_Cfg.h"
#include "SgnlPlttr_Cfg.h"

/** 
 * @file    Tuner_Cfg.h
 * @brief   Configuration for Tuner component.
 * @details This file contains the configuration settings for the Tuner component.
 */

#define NOTE_TABLE_SIZE (88U)
#define MIDI_A0         (21U)
#define NOTES_NUMBER    (12U)

#define MIN_CENTS       (-50)
#define MAX_CENTS       (50U)
#define CENTS_RANGE     (MAX_CENTS - MIN_CENTS)  // 100

extern const char* note_names[];

extern const uint16_t freq_scale_table[88];

#define GET_FREQ(midi_num) (freq_scale_table[(midi_num) - MIDI_A0])

#define BASE_LINE_START(center, offset) (center - offset)
#define BASE_LINE_LIMIT(center, offset) (center + offset)

/* -------------------------------------------------------------------------- */ 
/* Tuner Configuration Parameters                                             */ 
/* Defines core configuration values for tuner operation                      */ 
/* -------------------------------------------------------------------------- */

typedef struct
{
    uint8_t font_size;         // Font size for display
    uint8_t font_type;         // Font type for display
    uint8_t x0;
    uint8_t x1;
    uint8_t y0;
    uint8_t y1;
    uint8_t y0_n;
    uint8_t y1_n;
    uint8_t width;
    uint8_t height;
    uint8_t length;
    uint8_t thickness;
} Tuner_Cfg_t;

typedef struct 
{
    char*    name;      // Note name, e.g., "A4"
    char     symbol;    // Note symbol, e.g., "A"
    uint32_t exp_freq;  // Expected note frequency, e.g., 440.0
    uint32_t cur_freq;  // Current note frequency, e.g., 440.0
    int8_t   cents;     // cents between current & expected frequencies
} NoteInfo_t;

#define TUNER_CFG(sym_cfg, ndl_cfg)         \
    (Tuner_Cfg_t){                          \
        .font_size = (sym_cfg).font_size,   \
        .font_type = (sym_cfg).font_type,   \
        .x0        = (sym_cfg).x0,          \
        .x1        = (sym_cfg).x1,          \
        .y0        = (sym_cfg).y0,          \
        .y1        = (sym_cfg).y1,          \
        .y0_n      = (ndl_cfg).y0,          \
        .y1_n      = (ndl_cfg).y1,          \
        .width     = (sym_cfg).width,       \
        .height    = (sym_cfg).height,      \
        .length    = (ndl_cfg).length,      \
        .thickness = (ndl_cfg).thickness    \
    }

extern uint8_t needle_buffer[CENTS_RANGE];
extern uint8_t needle_bitmap[OLED_BITMAP_SIZE];

extern NoteInfo_t note_table[NOTE_TABLE_SIZE];

extern Tuner_Cfg_t tuner_cfg;

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
void NoteTable_Init(void);

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
void Needle_InitBuffer(uint8_t** buffer, size_t size);

void Needle_ClearBuffer(void);

void Needle_FillBuffer(Tuner_Cfg_t* tuner_cfg, NoteInfo_t* note, uint8_t* buffer);

void Needle_FillShapedBuffer(Tuner_Cfg_t* tuner_cfg, uint8_t* buffer, uint8_t* bitmap);

void Needle_DisplayBitmap(Tuner_Cfg_t* tuner_cfg, uint8_t* bitmap);

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
NoteInfo_t Tuner_GetNoteFromFreq(uint32_t input_freq);

void Tuner_DrawNoteSymbol(Tuner_Cfg_t* tuner_cfg, NoteInfo_t* note);

void Tuner_DrawRule(Tuner_Cfg_t* cfg);

void Tuner_Init(void);

void Tuner_Run(Tuner_Cfg_t* tuner_cfg, NoteInfo_t* note, uint8_t* buffer, uint8_t* bitmap);

#endif /* TUNER_CFG_H */
