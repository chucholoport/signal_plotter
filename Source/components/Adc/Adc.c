#include "Adc_Cfg.h"

#include "Hmi_Cfg.h"

#include "driver/adc.h"

/**
 * @file    Adc.c
 * @brief   Implementation of ADC control for ESP8266.
 * @details Functions abstract the ADC interface through APIs.
 */

adc_config_t adc_cfg;

void Adc_Init(void)
{
    /* Initialize ADC configuration */
    adc_cfg = ADC_CFG;
    
    /* Initialize the ADC with ESP RTOS API */
    adc_init(&adc_cfg);
}

int16_t Adc_Read(void)
{
    uint16_t adc_value = 0;

    /* Read ADC value with ESP RTOS API */
    esp_err_t ret = adc_read(&adc_value);

    if (ret == ESP_OK) 
    {
        /* Return the raw ADC value */
        return (int16_t)adc_value;
    } 
    else 
    {
        /* Return -1 on error */
        return -1;
    }
}