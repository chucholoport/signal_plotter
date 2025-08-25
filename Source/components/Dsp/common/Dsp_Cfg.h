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
/* DSP Parameters                                                             */ 
/* Defines core configuration values for signal acquisition and analysis      */ 
/* -------------------------------------------------------------------------- */
 
/* Signal Processing parameters */
#define DSP_BUFFER_SIZE                     (512U)
#define DSP_GAIN                            (1U) 
#define DSP_OFFSET                          (590)
#define DSP_THRESHOLD                       (100)
#define DSP_MAX                             (512)
#define DSP_MIN                             (-512)

/* Low Pass Filter parameters */
#define LOW_PASS_FILTER_HISTERESIS          (16U) 
#define LOW_PASS_FILTER_FALL_EDGE           (DSP_OFFSET - LOW_PASS_FILTER_HISTERESIS) 
#define LOW_PASS_FILTER_RISE_EDGE           (DSP_OFFSET + LOW_PASS_FILTER_HISTERESIS) 

/* Signal Processing formulas */
#define DSP_INSIDE_LOW_PASS_FILTER(sample)  ((sample) < LOW_PASS_FILTER_FALL_EDGE && (sample) > LOW_PASS_FILTER_RISE_EDGE)
#define DSP_APPLY_LOW_PASS_FILTER(sample)   (DSP_INSIDE_LOW_PASS_FILTER(sample) ? 0 : (DSP_REMOVE_OFFSET(sample)))
#define DSP_REMOVE_OFFSET(sample)           (sample - DSP_OFFSET)
#define DSP_APPLY_GAIN(sample)              (sample * DSP_GAIN)
#define DSP_NORMALIZE(sample)               (DSP_APPLY_LOW_PASS_FILTER(DSP_APPLY_GAIN(sample)))

/* -------------------------------------------------------------------------- */ 
/* DSP Utility Macros                                                         */ 
/* Provide safe computations for signal metrics and trigger logic             */ 
/* -------------------------------------------------------------------------- */

/* Default operational parameters */ 
#define DSP_DEFAULT_SAMPLE_RATE             (1000000U) 
#define DSP_DEFAULT_AVERAGE                 (0U) 
#define DSP_DEFAULT_LEVEL                   (0U) 
#define DSP_DEFAULT_TRIGGER                 (0U)

/* Operational parameters formulas */
#define DSP_SAMPLE_RATE(size, time)         (((time) > 0U) ? ((DSP_DEFAULT_SAMPLE_RATE * (size)) / (time))  : 0U)
#define DSP_AVERAGE(sum, size)              (((size) > 0U) ? ((sum) / (size))                               : 0U)
#define DSP_LEVEL(sum, size)                (((size) > 0U) ? ((sum) / (size))                               : 0U)
#define DSP_TRIGGER(energy, threshold)      ((energy) > (threshold))

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
    uint32_t size;         // Size of the signal buffer in samples 
    uint32_t sample_rate;  // Sample rate in Hz 
    uint8_t  gain;         // Signal gain value
    int16_t  offset;       // Signal offset value 
    int16_t  threshold;    // Signal detectable threshold 
    int16_t  max;          // Signal maximum value
    int16_t  min;          // Signal minimum value
    int16_t  fall_edge;    // Signal low pass filter fall edge
    int16_t  rise_edge;    // Signal low pass filter rise edge
    int16_t  average;      // Signal average 
    int16_t  level;        // Signal level 
    uint8_t  trigger;      // Flag marking if signal is detectable 
} Dsp_Cfg_t;

/**
 * @brief Signal Buffer Configuration instance.
 *
 * This instance is used to initialize the signal buffer with the specified parameters.
 * Modify the values as needed for your specific signal buffering requirements. 
 */ 
extern Dsp_Cfg_t dsp_cfg;

/* -------------------------------------------------------------------------- */
/* External Buffers                                                           */
/* Used for intermediate signal shaping and final display rendering           */
/* -------------------------------------------------------------------------- */

/**
 * @brief Pointer to the signal buffer.
 *
 * This pointer is used to access the signal buffer in the DSP module.
 * It is allocated dynamically based on the buffer size specified in the configuration. 
 */ 
extern int16_t* dsp_buffer;

/* -------------------------------------------------------------------------- */
/* DSP Public Function Prototypes                                             */
/* -------------------------------------------------------------------------- */

/**
 * @brief Initializes the signal buffer with the specified configuration.
 *
 * This function sets up the signal buffer based on the provided configuration parameters. 
 * It allocates memory for the buffer and initializes it to zero.
 */ 
void Dsp_Init(void);

/**
 * @brief Fills signal buffer.
 *
 * This function fills the signal buffer.
 * It reads samples from the ADC, normalizes them, and stores them in the buffer.
 * It also calculates statistics such as average, level, and trigger status.
 */ 
void Dsp_Run(void);

#endif
