#include "Adc_Cfg.h"

#include "Hmi_Cfg.h"

#include "driver/adc.h"

/**
 * @file    Adc.c
 * @brief   Implementation of ADC control for ESP8266.
 * @details Functions abstract the ADC interface through APIs.
 */

/* Initialize message buffer */
char* adc_msg_buffer = NULL;

/* Initialize message struct */
HmiDisplayMsg_t adc_msg = 
{
    .text  = "ADC Init",
    .clear = ADC_INIT_STATUS_CLEAR,
    .time  = ADC_INIT_STATUS_DURATION_MS,
    .x     = ADC_INIT_STATUS_COORDINATE_X,
    .y     = ADC_INIT_STATUS_COORDINATE_Y
};

/* Component Configuration Instance */
adc_config_t adc_cfg;

void Adc_Init(void)
{
    /* Initialize ADC configuration */
    adc_cfg = ADC_CFG_DEFAULT;
    
    /* Initialize the ADC with the provided configuration */
    adc_init(&adc_cfg);

    /* Show ADC init status on display */
    Hmi_InitMessage(&adc_msg_buffer, ADC_MESSAGE_TEXT_BUFFER_SIZE);
    sprintf(adc_msg_buffer, "ADC: mode=%d, clk_div=%d", adc_cfg.mode, adc_cfg.clk_div);
    Hmi_WriteMessage(&adc_msg, adc_msg_buffer);
}

void Adc_Deinit(void)
{
    // Currently, no specific deinitialization is required for ADC on ESP8266.
    // This function can be used to clean up resources if needed in the future.
}

int16_t Adc_Read(void)
{
    uint16_t adc_value = 0;

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