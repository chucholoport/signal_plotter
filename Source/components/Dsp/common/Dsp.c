#include "Dsp_Cfg.h"

#include "Adc_Cfg.h"
#include "Dio_Cfg.h"
#include "Hmi_Cfg.h"

#include "esp_timer.h"

/**
 * @file    Dsp.c
 * @brief   Implementation of dynamic signal buffer.
 * @details Functions execute processing for signal buffer.
 */

int16_t* dsp_buffer = NULL;

Dsp_Cfg_t dsp_cfg =
{
    .size           = DSP_BUFFER_SIZE,  
    .sample_rate    = DSP_DEFAULT_SAMPLE_RATE,
    .gain           = DSP_GAIN,
    .offset         = DSP_OFFSET,   
    .threshold      = DSP_THRESHOLD,
    .max            = DSP_MAX,
    .min            = DSP_MIN,
    .fall_edge      = LOW_PASS_FILTER_FALL_EDGE,
    .rise_edge      = LOW_PASS_FILTER_RISE_EDGE,   
    .average        = DSP_DEFAULT_AVERAGE,
    .level          = DSP_DEFAULT_LEVEL,
    .trigger        = DSP_DEFAULT_TRIGGER
};

void Dsp_Init(void)
{
    if (dsp_buffer != NULL) 
    {
        free(dsp_buffer);
    }

    dsp_buffer = (int16_t*)malloc(DSP_BUFFER_SIZE * sizeof(int16_t));
}

void Dsp_Run(void)
{
    /* Initialize config statistics */
    dsp_cfg.sample_rate = DSP_DEFAULT_SAMPLE_RATE;
    dsp_cfg.average     = DSP_DEFAULT_AVERAGE;
    dsp_cfg.level       = DSP_DEFAULT_LEVEL;
    dsp_cfg.trigger     = DSP_DEFAULT_TRIGGER;

    /* Initialize auxiliar variables */
    uint32_t sgnl_sum  = 0U;
    uint32_t sgnl_lvl  = 0U;

    /* Register startup time */
    uint64_t start_time = esp_timer_get_time();

    /* Iterate signal buffer */
    for (uint32_t i = 0U; i < dsp_cfg.size; i++) 
    {
        /* Data obtention & normalization */
        int16_t raw = Adc_Read();
        int16_t nrm = DSP_NORMALIZE(raw);

        /* Assign normalized value to buffer */
        dsp_buffer[i] = nrm;

        /* Calculate statistics */
        sgnl_sum += nrm;
        sgnl_lvl += raw * raw;
    }

    /* Register ending time */
    uint64_t end_time = esp_timer_get_time();

    /* Calculate execution time */
    uint64_t exec_time = end_time - start_time;

    /* Update statistics fields */
    dsp_cfg.sample_rate = (uint32_t) DSP_SAMPLE_RATE (dsp_cfg.size,      exec_time    );
    dsp_cfg.average     = (int16_t)  DSP_AVERAGE     (sgnl_sum,          dsp_cfg.size );
    dsp_cfg.level       = (int16_t)  DSP_LEVEL       (sgnl_lvl,          dsp_cfg.size );
    dsp_cfg.trigger     = (uint8_t)  DSP_TRIGGER     (dsp_cfg.threshold, dsp_cfg.level);
}