#include "Tuner_Cfg.h"

#include "SgnlPlttr_Cfg.h"

#include "ssd1306.h"

uint8_t needle_buffer[CENTS_RANGE]      = {0};
uint8_t needle_bitmap[OLED_BITMAP_SIZE] = {0};

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

NoteInfo_t unknown_note =
{
    .name     = "???",
    .symbol   = ' ',
    .exp_freq = 0U,
    .cur_freq = 0U,
    .cents    = 0
};

Tuner_Cfg_t tuner_cfg;

void NoteTable_Init(void)
{
    char* base = NULL; 
    char* name = NULL;

    for (int i = 0; i < NOTE_TABLE_SIZE; ++i)
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

void Needle_ClearBuffer(void)
{
    memset(needle_buffer, 0x00, CENTS_RANGE);
}

void Needle_ClearBitmap(void) 
{
    memset(needle_bitmap, 0, OLED_SCREEN_BYTES_NO * sizeof(uint8_t));
}

void Needle_FillBuffer(Tuner_Cfg_t* tuner_cfg, NoteInfo_t* note, uint8_t* buffer)
{    
    Needle_ClearBuffer();

    int8_t  cents = note->cents;
    uint8_t index = 0U;

    cents = CLAMP(cents, MIN_CENTS, MAX_CENTS - 1);
    index = cents - MIN_CENTS;

    buffer[index] = 1;
}

void Needle_FillShapedBuffer(Tuner_Cfg_t* tuner_cfg, uint8_t* buffer, uint8_t* bitmap)
{
    /* Initialize auxiliar variables */
    uint8_t x = 0U;       
    uint8_t y = 0U;
    
    /* Clear the bitmap */
    Needle_ClearBitmap();

    /* Scale values */
    for (uint8_t cents = 0; cents < CENTS_RANGE; ++cents)
    {
        if (buffer[cents] == 0) continue;

        x = tuner_cfg->x0 + ((cents * (tuner_cfg->width)) / CENTS_RANGE);
        y = tuner_cfg->y0_n;
        
        BITMAP_DRAW_PIXEL(bitmap, x, y, tuner_cfg->width);
    }
}

void Needle_DisplayBitmap(Tuner_Cfg_t* tuner_cfg, uint8_t* bitmap)
{
    /* Send bitmap to display */
    ssd1306_drawBufferFast(tuner_cfg->x0, tuner_cfg->y0_n, tuner_cfg->width, tuner_cfg->y0_n + 8, bitmap);
}

NoteInfo_t Tuner_GetNoteFromFreq(uint32_t input_freq)
{
    uint8_t low       = 0U;
    uint8_t high      = NOTE_TABLE_SIZE - 1;
    uint8_t idx       = 0U;
    double ratio      = 0.0;
    int8_t cents      = 0;
    
    NoteInfo_t result = unknown_note;

    /* Binary search of closest note */
    while (low <= high)
    {
        uint8_t  mid      = 0U;
        uint32_t mid_freq = 0U;

        mid = (low + high) / 2;

        if (mid >= NOTE_TABLE_SIZE) 
        {
            return result;
        }

        mid_freq = note_table[mid].exp_freq;

        if (input_freq < mid_freq)
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
    idx = (abs(note_table[low].exp_freq - input_freq) < abs(note_table[low - 1].exp_freq - input_freq)) ? low : low - 1;

    /* Cents calculation */
    ratio = (double)input_freq / (double)note_table[idx].exp_freq;
    cents = (int8_t)(1200.0 * log(ratio) / log(2.0));

    /* Fill resulting note */
    result.name     = note_table[idx].name;
    result.symbol   = note_table[idx].symbol;
    result.exp_freq = note_table[idx].exp_freq;
    result.cur_freq = input_freq;
    result.cents    = cents;

    return result;
}

void Tuner_DrawNoteSymbol(Tuner_Cfg_t* tuner_cfg, NoteInfo_t* note)
{
    uint8_t char_width = 0U;
    uint8_t offset     = 0U;

    uint8_t x_pos = 0U;
    uint8_t y_pos = 0U;

    char symbol_str[2] = {'?', '\0'};

    char_width = 6U << tuner_cfg->font_size;
    offset     = (tuner_cfg->width > char_width) ? (tuner_cfg->width - char_width) / 2 : 0;

    x_pos = tuner_cfg->x0 + offset;
    y_pos = tuner_cfg->y0;

    symbol_str[0] = note->symbol; 

    ssd1306_printFixedN(x_pos, y_pos, symbol_str, tuner_cfg->font_type, tuner_cfg->font_size);
}

void Tuner_DrawRule(Tuner_Cfg_t* tuner_cfg)
{
    uint8_t center_x      = 0U;
    uint8_t max_offset    = 0U;
    uint8_t ruler_y       = 0U;

    uint8_t base_start = 0U;
    uint8_t base_limit = 0U;

    /* Array to save ticks positions */
    uint8_t tick_xs[11];
    uint8_t tick_count  = 0U;
    uint8_t tick_x      = 0U;
    uint8_t tick_height = 0U;

    uint8_t next_x = 0U;
    uint8_t prev_x = 0U;

    center_x   = tuner_cfg->x0 + tuner_cfg->width / 2;
    max_offset = tuner_cfg->width / 2;
    ruler_y    = tuner_cfg->y1_n - 1;

    base_start = BASE_LINE_START(center_x, max_offset);
    base_limit = BASE_LINE_LIMIT(center_x, max_offset);

    /* Draw ticks & save positions */
    for (int8_t cents = -50; cents <= 50; cents += 10)
    {
        tick_x = center_x + (cents * max_offset) / 50;
        tick_height = (cents % 20 == 0) ? 4 : 2;

        tick_xs[tick_count++] = tick_x;

        ssd1306_drawLine(tick_x, ruler_y - tick_height, tick_x, ruler_y);
    }

    /* Draw horizontal base in segments between ticks */
    prev_x = base_start;
    for (uint8_t i = 0; i < tick_count; i++)
    {
        next_x = tick_xs[i];

        if (next_x > prev_x)
        {
            ssd1306_drawLine(prev_x, ruler_y, next_x - 1, ruler_y);
        }

        prev_x = next_x + 1;
    }

    /* Last step until the end */
    if (prev_x < base_limit)
    {
        ssd1306_drawLine(prev_x, ruler_y, base_limit, ruler_y);
    }
}

void Tuner_Init(void)
{
    tuner_cfg = TUNER_CFG(hmi_cfg.note_symbol, hmi_cfg.needle);

    NoteTable_Init();
    Tuner_DrawRule(&tuner_cfg);
}

void Tuner_Run(Tuner_Cfg_t* tuner_cfg, NoteInfo_t* note, uint8_t* buffer, uint8_t* bitmap)
{
    Tuner_DrawNoteSymbol(tuner_cfg, note);
    Needle_FillBuffer(tuner_cfg, note, buffer);
    Needle_FillShapedBuffer(tuner_cfg, buffer, bitmap);
    Needle_DisplayBitmap(tuner_cfg, bitmap);
    Tuner_DrawRule(tuner_cfg);
}