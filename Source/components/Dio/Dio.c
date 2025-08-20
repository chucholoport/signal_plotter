#include "Dio_Cfg.h"

#include "driver/gpio.h"

/**
 * @file    Dio.c
 * @brief   ESP8266 digital I/O interfaces.
 * @details Provides high-level abstraction for application-level GPIO access.
 */

void Dio_SetPinOutput(uint8_t pin_id)
{
    gpio_set_direction(pin_id, GPIO_MODE_OUTPUT);
}

void Dio_SetPinInput(uint8_t pin_id)
{
    gpio_set_direction(pin_id, GPIO_MODE_INPUT);
}

void Dio_SetPinHigh(uint8_t pin_id)
{
    gpio_set_level(pin_id, GPIO_INTR_HIGH_LEVEL);
}

void Dio_SetPinLow(uint8_t pin_id)
{
    gpio_set_level(pin_id, GPIO_INTR_LOW_LEVEL);
}

void Dio_InitOutputs(void)
{
    /* Example: if future output pins are added, they are configured here */
    /* Currently not used; initialization handled by DrvDio_InitOledPins() */
}

/**
 * @brief   Initializes I²C pins connected to OLED display.
 * @details Configures GPIOs used for SDA and SCL as digital outputs.
 *          This is only necessary for software-based I²C control.
 */
void Dio_InitOledPins(void)
{
    Dio_SetPinOutput(DIO_PIN_OLED_SCL);
    Dio_SetPinOutput(DIO_PIN_OLED_SDA);

    Dio_SetPinHigh(DIO_PIN_OLED_SCL);
    Dio_SetPinHigh(DIO_PIN_OLED_SDA);
}