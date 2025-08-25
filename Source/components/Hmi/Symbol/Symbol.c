#include "Symbol_Cfg.h"

#include "Hmi_Cfg.h"
#include "Autocorrelation_Cfg.h"

#include "ssd1306.h"

/** 
 * @file    Symbol_Cfg.h
 * @brief   Implementation for Note Symbol component.
 * @details This file contains the implementation logic for the Note Symbol component.
 */

const char* note_names[] = 
{
    "C",    "C#",   "D",    "D#",   "E",    "F",
    "F#",   "G",    "G#",   "A",    "A#",   "B"
};

const uint16_t freq_scale_table[88] = 
{
    62,     66,     70,     74,     78,     83,     88,     93,     98,     104,    110,    117,
    124,    131,    139,    147,    156,    165,    175,    185,    196,    208,    220,    233,
    247,    262,    277,    294,    311,    330,    349,    370,    392,    415,    440,    466,
    494,    523,    554,    587,    622,    659,    698,    740,    784,    831,    880,    932,
    988,    1047,   1109,   1175,   1245,   1319,   1397,   1480,   1568,   1661,   1760,   1865,
    1976,   2093,   2217,   2349,   2489,   2637,   2794,   2960,   3136,   3322,   3520,   3729,
    3951,   4186,   4434,   4698,   4978,   5274,   5588,   5920,   6272,   6645,   7040,   7458,
    7902,   8372
};

NoteInfo_t note_table[NOTE_TABLE_SIZE] = {0};

NoteInfo_t current_note;

HmiBlock_Cfg_t symbol_cfg;

void Symbol_FillTable(void)
{
    char* base = NULL; 
    char* name = NULL;

    for (uint8_t i = 0; i < NOTE_TABLE_SIZE; ++i)
    {
        uint8_t midi_num   = 0U;
        uint8_t octave     = 0U;
        uint8_t note_index = 0U;
        int32_t freq       = 0;

        /* MIDI note number (A0 = 21) */
        midi_num   = i + MIDI_A0;

        /* Octave & Note Index calculation */
        octave     = (midi_num / NOTES_NUMBER) - 1;
        note_index = midi_num % NOTES_NUMBER;

        /* Base & Name definition */
        base = (char*)note_names[note_index];
        name = malloc(6);
        sprintf(name, "%s%d", base, octave);

        /* Expected frequency calculation */
        freq = GET_FREQ(midi_num);

        /* Fill note table item */
        note_table[i].name     = name;
        note_table[i].symbol   = base[0];
        note_table[i].exp_freq = freq;
    }
}

void Symbol_GetNote(void)
{
    uint8_t low       = 0U;
    uint8_t high      = NOTE_TABLE_SIZE - 1;
    uint8_t idx       = 0U;
    double  ratio     = 0.0;
    int8_t  cents     = 0;

    current_note = UNKNOWN_NOTE;

    /* Binary search of closest note */
    while (low <= high)
    {
        uint8_t  mid      = 0U;
        uint32_t mid_freq = 0U;

        mid = (low + high) / 2;

        if (mid >= NOTE_TABLE_SIZE) 
        {
            return;
        }

        mid_freq = note_table[mid].exp_freq;

        if (frequency < mid_freq)
        {
            high = mid - 1; 
        }
        else
        {
            low = mid + 1;
        }
    }

    /* Truncate invalid values */
    if (low == 0U)
    {
        low = 1U;
    }
    if (low >= NOTE_TABLE_SIZE)
    {
        low = NOTE_TABLE_SIZE - 1;
    }

    /* Current frequency estimation */
    idx = (abs(note_table[low].exp_freq - frequency) < abs(note_table[low - 1].exp_freq - frequency)) ? low : low - 1;

    /* Cents calculation */
    ratio = (double)frequency / (double)note_table[idx].exp_freq;
    cents = (int8_t)(1200.0 * log(ratio) / log(2.0));

    /* Fill resulting note */
    current_note.name     = note_table[idx].name;
    current_note.symbol   = note_table[idx].symbol;
    current_note.exp_freq = note_table[idx].exp_freq;
    current_note.cur_freq = frequency;
    current_note.cents    = cents;
}

void Symbol_Show(void)
{
    uint8_t char_width = 0U;
    uint8_t offset     = 0U;

    uint8_t x_pos = 0U;
    uint8_t y_pos = 0U;

    char symbol_str[3] = {' ', ' ', '\0'};

    char_width = 6U << symbol_cfg.font_size;
    offset     = (symbol_cfg.width > char_width) ? (symbol_cfg.width - char_width) / 2 : 0;

    x_pos = symbol_cfg.x0 + offset;
    y_pos = symbol_cfg.y0;

    if (current_note.name[0] != '?')
    {
        symbol_str[0] = current_note.name[0];
    }

    if (current_note.name[1] == '#')
    {
        symbol_str[1] = current_note.name[1]; 
    }

    ssd1306_printFixedN(x_pos, y_pos, symbol_str, symbol_cfg.font_type, symbol_cfg.font_size);
}

void Symbol_Init(void)
{
    /* Set configuration */
    symbol_cfg = hmi_cfg.symbol;

    /* Initialize frequencimeter */
    Frq_Init();
    
    /* Fill Table of symbols */
    Symbol_FillTable();
    
    /* Initialize current note */
    current_note = UNKNOWN_NOTE;
}

void Symbol_Run(void)
{
    Frq_EstimateFundamental();
    Symbol_GetNote();
    Symbol_Show();
}