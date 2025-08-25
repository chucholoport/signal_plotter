#include "Autocorrelation_Cfg.h"

#include "Dsp_Cfg.h"


int32_t* frq_buffer = NULL;

uint32_t frequency = 0U;

static uint16_t frq_buffer_size = 0U;


void Frq_Init(void)
{
    frq_buffer_size = dsp_cfg.size / 2;

    if (frq_buffer != NULL) 
    {
        free(frq_buffer);
    }
    frq_buffer = (int32_t*)malloc(frq_buffer_size * sizeof(int32_t));
}

void Frq_ClearBuffer(void)
{
    if (frq_buffer == NULL)
    {
        return;
    }
    memset(frq_buffer, 0, frq_buffer_size * sizeof(int32_t));
}

void Frq_EstimateFundamental(void)
{

    /* Constants */
    uint16_t min_lag        = 0U;
    uint16_t max_lag_search = 0U;
    uint16_t max_lag        = 0U;

    /* Constants */
    max_lag_search  = (uint16_t)(dsp_cfg.sample_rate / MIN_FREQ);
    min_lag         = (uint16_t)(dsp_cfg.sample_rate / MAX_FREQ);
    max_lag         = (uint16_t)(dsp_cfg.size / 2U);

    /* Truncate values */
    if (max_lag_search > max_lag) 
    {
        max_lag_search = max_lag;
    }

    /* Fill Frequency buffer */
    for (uint16_t lag = 1U; lag < max_lag; lag++) 
    {
        int64_t sum = 0U;
        
        for (uint32_t i = 0U; i < dsp_cfg.size - lag; i++) 
        {
            int32_t s1 = 0U;
            int32_t s2 = 0U;

            s1 = dsp_buffer[i] - dsp_cfg.average;
            s2 = dsp_buffer[i + lag] - dsp_cfg.average;

            sum += (int64_t) s1 * s2;
        }

        frq_buffer[lag] = (int32_t)(sum / (dsp_cfg.size - lag));
    }

    /* Search best lag */
    int32_t  max_corr   = 0U;
    uint16_t best_lag   = 0U;
    uint8_t  peak_found = 0U;

    max_corr = INT32_MIN;

    for (uint16_t lag = min_lag; lag < max_lag_search; lag++) 
    {
        if (frq_buffer[lag] > max_corr) 
        {
            max_corr   = frq_buffer[lag];
            best_lag   = lag;
            peak_found = 1U;
        }
    }

    /* Calculate fundamental frequency */
    uint32_t result = 0U;

    if (peak_found && best_lag > 0U) 
    {
        result = dsp_cfg.sample_rate / best_lag;
    }

    /* Validate frequency range */
    if ((result < MIN_FREQ) || (result > MAX_FREQ)) 
    {
        result = 0U;
    }

    frequency = result;
}