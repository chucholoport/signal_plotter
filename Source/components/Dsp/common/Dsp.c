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

DspBffr_Cfg_t dsp_cfg =
{
    /* data */
    .buffer_size = SIGNAL_BUFFER_SIZE,  
    .sample_rate = SIGNAL_BUFFER_DEFAULT_SAMPLE_RATE,
    .center      = SIGNAL_BUFFER_CENTER,   
    .max         = SIGNAL_BUFFER_MAX,
    .min         = SIGNAL_BUFFER_MIN,
    .lower_limit = SIGNAL_BUFFER_LOWER_LIMIT,
    .upper_limit = SIGNAL_BUFFER_UPPER_LIMIT,   
    .threshold   = SIGNAL_BUFFER_THRESHOLD,
    .average     = SIGNAL_BUFFER_DEFAULT_AVERAGE,
    .level       = SIGNAL_BUFFER_DEFAULT_LEVEL,
    .trigger     = SIGNAL_BUFFER_DEFAULT_TRIGGER
};

void Dsp_InitBuffer(int16_t** buffer, size_t size)
{
    if (*buffer != NULL) 
    {
        free(*buffer);
    }

    *buffer = (int16_t*)malloc(size * sizeof(int16_t));
}

void Dsp_Deinit(int16_t** buffer)
{
    if (*buffer != NULL)
    {
        free(*buffer);
        *buffer = NULL;
    }
}

int16_t Dsp_NormalizeSample(DspBffr_Cfg_t* cfg, int16_t sample)
{
    int16_t nrm = sample;

    /* Apply gain */
    nrm = nrm * SIGNAL_BUFFER_GAIN;

    /* Center and limit */
    if ((nrm > cfg->lower_limit) && (nrm < cfg->upper_limit))
    {
        nrm = 0;
    }
    else
    {
      nrm = nrm - cfg->center;
    }
    
    return nrm;
}

void Dsp_FillBuffer(DspBffr_Cfg_t* cfg, int16_t* buffer)
{
    /* Initialize config statistics */
    cfg->average = (uint32_t) 0U;
    cfg->trigger = (uint8_t)  0U;

    /* Initialize auxiliar variables */
    uint32_t sgnl_sum  = 0U;
    uint32_t sgnl_lvl  = 0U;
    uint64_t exec_time = 0U;

    /* Register startup time */
    uint64_t start_time = esp_timer_get_time();

    /* Iterate signal buffer */
    for (uint32_t i = 0; i < cfg->buffer_size; ++i) 
    {
        /* Data obtention & normalization */
        int16_t raw = Adc_Read();
        int16_t nrm = Dsp_NormalizeSample(cfg, raw);
        
        /* Assign normalized value to buffer */
        buffer[i] = nrm;

        /* Calculate statistics */
        sgnl_sum += nrm;
        sgnl_lvl += raw * raw;
    }

    /* Register ending time */
    uint64_t end_time = esp_timer_get_time();

    /* Calculate execution time */
    exec_time = end_time - start_time;

    /* Update statistics fields */
    cfg->sample_rate = (uint32_t) SIGNAL_BUFFER_SAMPLE_RATE (cfg->buffer_size,  exec_time       );
    cfg->average     = (int16_t)  SIGNAL_BUFFER_AVERAGE     (sgnl_sum,          cfg->buffer_size);
    cfg->level       = (int16_t)  SIGNAL_BUFFER_LEVEL       (sgnl_lvl,          cfg->buffer_size);
    cfg->trigger     = (uint8_t)  SIGNAL_BUFFER_TRIGGER     (cfg->threshold,    cfg->level      );
}