#ifndef SYMBOL_CFG_H
#define SYMBOL_CFG_H

#include <stdint.h>
#include <string.h>
#include <math.h>

#include "Hmi_Cfg.h"
#include "Dsp_Cfg.h"

/** 
 * @file    Symbol_Cfg.h
 * @brief   Configuration for Note Symbol component.
 * @details This file contains the configuration settings for the Note Symbol component.
 */

#define NOTE_TABLE_SIZE     (88U)
#define MIDI_A0             (21U)
#define NOTES_NUMBER        (12U)

#define MIN_CENTS           (-50)
#define MAX_CENTS           (50)
#define CENTS_STEP          (1)
#define SAMPLES_PER_CENT    (1)
#define CENTS_RANGE         (MAX_CENTS - MIN_CENTS)

extern const char* note_names[];

extern const uint16_t freq_scale_table[88];

#define GET_FREQ(midi_num) (freq_scale_table[(midi_num) - MIDI_A0])

typedef struct 
{
    char*    name;      // Note name, e.g., "A4"
    char     symbol;    // Note symbol, e.g., "A"
    uint32_t exp_freq;  // Expected note frequency, e.g., 440.0
    uint32_t cur_freq;  // Current note frequency, e.g., 440.0
    int8_t   cents;     // cents between current & expected frequencies
} NoteInfo_t;

#define UNKNOWN_NOTE        \
    (NoteInfo_t){           \
        .name     = "???",  \
        .symbol   = ' ',    \
        .exp_freq = 0U,     \
        .cur_freq = 0U,     \
        .cents    = 0       \
    }

extern NoteInfo_t note_table[NOTE_TABLE_SIZE];

extern NoteInfo_t current_note;

extern HmiBlock_Cfg_t symbol_cfg;

void Symbol_FillTable(void);

void Symbol_GetNote(void);

void Symbol_Show(void);

void Symbol_Init(void);

void Symbol_Run(void);

#endif /* SYMBOL_CFG_H */