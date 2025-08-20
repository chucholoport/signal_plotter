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

/**
 * @brief ADC Initialization Status Message Parameters
 * 
 * These parameters define the coordinates and duration for displaying the ADC initialization status message.
 */
#define ADC_INIT_STATUS_CLEAR        1U
#define ADC_INIT_STATUS_COORDINATE_X 0U
#define ADC_INIT_STATUS_COORDINATE_Y 10U
#define ADC_INIT_STATUS_DURATION_MS  100U

#define ADC_MODE    ADC_READ_TOUT_MODE
#define ADC_CLK_DIV 4U

/**
 * @brief Message text buffer.
 *
 * This buffer is used to store the text messages that will be displayed on the HMI.
 * Modify the size as needed for your specific application.
 */
#define ADC_MESSAGE_TEXT_BUFFER_SIZE 30U

extern char* adc_msg_buffer;

#define ADC_CFG_DEFAULT \
    (adc_config_t){ \
        .mode        = ADC_MODE, \
        .clk_div     = ADC_CLK_DIV \
    }

/** 
 * @brief ADC configuration instance.
 * 
 * This instance is used to initialize the ADC with the specified parameters.
 * Modify the values as needed for your specific ADC configuration.
 */
extern adc_config_t adc_cfg;

/** * @brief Initializes the ADC with the specified configuration.
 * 
 * This function sets up the ADC based on the provided configuration parameters.
 * 
 * @param cfg Pointer to the ADC configuration structure.
 */
void Adc_Init(void);

/** * @brief Deinitializes the ADC.
 * 
 * This function cleans up the ADC resources and settings.
 */
void HalAdc_Deinit(void);

/** 
 * @brief Reads a sample from the ADC.
 * 
 * This function reads a single sample from the ADC and returns its value.
 * 
 * @return The raw ADC value as an integer.
 */
int16_t Adc_Read(void);

#endif