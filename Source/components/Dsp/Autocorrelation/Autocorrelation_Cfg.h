#ifndef AUTOCORRELATION_CFG_H
#define AUTOCORRELATION_CFG_H

#include <stdio.h>  
#include <stdint.h> 
#include <stdlib.h>
#include <string.h>

#include "Dsp_Cfg.h"

/**
 * @brief Number of microseconds in one second
 *
 * Used to convert elapsed time measured in microseconds to seconds,
 * or to compute sampling frequency as samples per second. This constant
 * is useful when working with `micros()`-based timing.
 */
#define MICROSECONDS_PER_SECOND (1000000.0f)

/**
 * @brief Energy threshold for signal detection
 *
 * Minimum average energy required to consider a signal valid.
 * Used to suppress silence or low-amplitude noise.
 */
#define SIGNAL_UMBRAL (80.0f)

/* =======================================================================
 *                        Autocorrelation Parameters
 * =======================================================================
 */

/**
 * @brief Maximum lag for autocorrelation (related to lowest frequency)
 */
#define MAX_LAG (1000U)

/**
 * @brief Minimum lag for autocorrelation (related to highest frequency)
 */
#define MIN_LAG (16U)

/**
 * @brief Epsilon to avoid division by zero in normalization
 */
#define EPSILON (1.0e-8f)

/**
 * @brief Minimum detectable frequency based on MAX_LAG
 */
#define MIN_FREQ 70

/**
 * @brief Maximum detectable frequency based on MIN_LAG
 */
#define MAX_FREQ 600

extern int32_t* frq_buffer;

extern uint32_t frequency;

/**
 * @brief Initializes the signal buffer with the specified configuration.
 * 
 * This function sets up the signal buffer based on the provided configuration parameters.
 * 
 */
void Frq_Init(void);

/**
 * @brief Clears the signal buffer.
 *
 * This function resets the signal buffer, removing all stored samples.
 */
void Frq_ClearBuffer(void);

/**
 * @brief Estimate frequency using a specified frequency search range
 *
 * Searches for the best-matching lag between freq_min and freq_max
 * using autocorrelation. The signal must already be DC-removed and normalized.
 *
 */
void Frq_EstimateFundamental(void);

#endif /* AUTOCORRELATION_CFG_H */