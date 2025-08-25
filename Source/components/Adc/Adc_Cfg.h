#ifndef ADC_CFG_H
#define ADC_CFG_H

#include <stdio.h>
#include <stdint.h>

#include "driver/adc.h"

/**
 * @file    HalAdc_Cfg.h
 * @brief   Configuration for ADC (Analog-to-Digital Converter).
 * @details This file contains the configuration settings for the ADC.
 */

/* -------------------------------------------------------------------------- */
/* ADC Parameters                                                             */
/* Defines ADC Configuration parameters for modular access                    */
/* -------------------------------------------------------------------------- */

#define ADC_MODE                     (ADC_READ_TOUT_MODE)
#define ADC_CLK_DIV                  (4U)

#define ADC_CFG \
    (adc_config_t){ \
        .mode        = ADC_MODE, \
        .clk_div     = ADC_CLK_DIV \
    }

/* -------------------------------------------------------------------------- */
/* Configuration                                                              */
/* Used for configuring ADC                                                   */
/* -------------------------------------------------------------------------- */

/** 
 * @brief ADC configuration instance.
 * 
 * This instance is used to initialize the ADC with the specified parameters.
 * Modify the values as needed for your specific ADC configuration.
 */
extern adc_config_t adc_cfg;

/* -------------------------------------------------------------------------- */
/* ADC Public Function Prototypes                                             */
/* -------------------------------------------------------------------------- */

/** * @brief Initializes the ADC with the specified configuration.
 * 
 * This function sets up the ADC based on the provided configuration parameters.
 * 
 * @param cfg Pointer to the ADC configuration structure.
 */
void Adc_Init(void);

/** 
 * @brief Reads a sample from the ADC.
 * 
 * This function reads a single sample from the ADC and returns its value.
 * 
 * @return The raw ADC value as an integer.
 */
int16_t Adc_Read(void);

#endif