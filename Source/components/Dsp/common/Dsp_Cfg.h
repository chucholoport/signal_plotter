#ifndef DSP_CFG_H 
#define DSP_CFG_H 

#include <stdio.h> 
#include <stdint.h> 
#include <stdlib.h>

/**
 * @file    Dsp_Cfg.h
 * @brief   Configuration for Digital Signal Processing (DSP).
 * @details This file contains the configuration settings for the DSP components. 
 */

/* -------------------------------------------------------------------------- */ 
/* Signal Buffer Parameters                                                   */ 
/* Defines core configuration values for signal acquisition and analysis      */ 
/* -------------------------------------------------------------------------- */
#define SIGNAL_BUFFER_SIZE                          (512U) 
#define SIGNAL_BUFFER_HISTERESIS                    (16U) 
#define SIGNAL_BUFFER_GAIN                          (1U) 
#define SIGNAL_BUFFER_MAX                           (512U)
#define SIGNAL_BUFFER_MIN                           (-512)
#define SIGNAL_BUFFER_CENTER                        (512U) 
#define SIGNAL_BUFFER_LOWER_LIMIT                   (SIGNAL_BUFFER_CENTER - SIGNAL_BUFFER_HISTERESIS) 
#define SIGNAL_BUFFER_UPPER_LIMIT                   (SIGNAL_BUFFER_CENTER + SIGNAL_BUFFER_HISTERESIS) 
#define SIGNAL_BUFFER_THRESHOLD                     (200U)

/* Default operational parameters */ 
#define SIGNAL_BUFFER_DEFAULT_SAMPLE_RATE           (1000000U) 
#define SIGNAL_BUFFER_DEFAULT_AVERAGE               (0U) 
#define SIGNAL_BUFFER_DEFAULT_LEVEL                 (0U) 
#define SIGNAL_BUFFER_DEFAULT_TRIGGER               (0U)

/* -------------------------------------------------------------------------- */ 
/* Signal Buffer Utility Macros                                               */ 
/* Provide safe computations for signal metrics and trigger logic             */ 
/* -------------------------------------------------------------------------- */

/**
 * @brief Computes the effective sample rate based on buffer size and elapsed time.
 *
 * @param size Number of samples acquired.
 * @param time Elapsed time in microseconds.
 * @return Sample rate in Hz. Returns 0 if time is zero. 
 */ 
#define SIGNAL_BUFFER_SAMPLE_RATE(size, time) \
    (((time) > 0U) ? ((SIGNAL_BUFFER_DEFAULT_SAMPLE_RATE * (size)) / (time)) : 0U)

/**
 * @brief Computes the average value of accumulated samples.
 *
 * @param sum Total sum of sample values.
 * @param size Number of samples.
 * @return Average value. Returns 0 if size is zero. 
 */ 
#define SIGNAL_BUFFER_AVERAGE(sum, size) \
    (((size) > 0U) ? ((sum) / (size)) : 0U)

/**
 * @brief Computes the signal level from accumulated energy.
 *
 * @param sum Total energy or amplitude sum.
 * @param size Number of samples.
 * @return Signal level. Returns 0 if size is zero. 
 */ 
#define SIGNAL_BUFFER_LEVEL(sum, size) \
    (((size) > 0U) ? ((sum) / (size)) : 0U)

/**
 * @brief Evaluates whether signal energy exceeds the trigger threshold.
 *
 * @param energy Computed signal energy.
 * @param threshold Trigger threshold value.
 * @return true if energy exceeds threshold, false otherwise. 
 */ 
#define SIGNAL_BUFFER_TRIGGER(energy, threshold) \
    ((energy) > (threshold))

/* -------------------------------------------------------------------------- */ 
/* Signal Buffer Configuration structure.                                     */ 
/* -------------------------------------------------------------------------- */

/**
 * @brief Signal Buffer Configuration structure.
 *
 * This structure is used to initialize the signal buffer with the specified parameters.
 * Modify the values as needed for your specific signal buffering requirements. 
 */ 
 typedef struct 
 { 
    uint32_t buffer_size;  // Size of the signal buffer in samples 
    uint32_t sample_rate;  // Sample rate in Hz 
    uint16_t center;       // Signal center value 
    int16_t  max;          // Signal maximum value
    int16_t  min;          // Signal minimum value
    uint16_t lower_limit;  // Signal lower limit histeresis
    uint16_t upper_limit;  // Signal upper limit histeresis
    int16_t  threshold;    // Signal detectable threshold 
    int16_t  average;      // Signal average 
    int16_t  level;        // Signal level 
    uint8_t  trigger;      // Flag marking if signal is detectable 
} DspBffr_Cfg_t;

/**
 * @brief Signal Buffer Configuration instance.
 *
 * This instance is used to initialize the signal buffer with the specified parameters.
 * Modify the values as needed for your specific signal buffering requirements. 
 */ 
extern DspBffr_Cfg_t dsp_cfg;

/* -------------------------------------------------------------------------- */ 
/* Signal Buffer Public Data and Function Prototypes                          */ 
/* -------------------------------------------------------------------------- */

/**
 * @brief Pointer to the signal buffer.
 *
 * This pointer is used to access the signal buffer in the DSP module.
 * It is allocated dynamically based on the buffer size specified in the configuration. 
 */ 
extern int16_t* dsp_buffer;

/**
 * @brief Initializes the signal buffer with the specified configuration.
 *
 * This function sets up the signal buffer based on the provided configuration parameters. 
 * It allocates memory for the buffer and initializes it to zero.
 * @param buffer Pointer to the signal buffer pointer.
 * @param size Size of the signal buffer in samples.
 */ 
void Dsp_InitBuffer(int16_t** buffer, size_t size);

/**
 * @brief Deinitializes the signal buffer.
 * This function cleans up the signal buffer resources and settings. 
 * It frees the allocated memory for the signal buffer and resets the pointer to NULL.
 * @param buffer Pointer to the signal buffer pointer.
 */ 
void Dsp_Deinit(int16_t** buffer);

/**
 * @brief Normalizes a signal buffer sample.
 *
 * This function scales the samples in the signal buffer to a specified range.
 * It ensures that the maximum absolute value in the buffer is within the defined limits.
 * @param cfg Pointer to the DSP configuration structure.
 * @param sample The sample value to normalize.
 * @return The normalized sample value. 
 */ 
int16_t Dsp_NormalizeSample(DspBffr_Cfg_t* cfg, int16_t sample);

/**
 * @brief Fills signal buffer.
 * This function fills the signal buffer.
 * It reads samples from the ADC, normalizes them, and stores them in the buffer.
 * It also calculates statistics such as average, level, and trigger status.
 * @param cfg Pointer to the DSP configuration structure.
 * @param buffer Pointer to the signal buffer. 
 */ 
void Dsp_FillBuffer(DspBffr_Cfg_t* cfg, int16_t* buffer);

#endif
