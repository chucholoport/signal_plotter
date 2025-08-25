#ifndef DIO_CFG_H
#define DIO_CFG_H

#include <stdint.h>

/**
 * @file    Dio_Cfg.h
 * @brief   Digital I/O Configuration for ESP8266.
 * @details Logical mappings for application-level I/O connections.
 *          Designed for embedded systems using ESP8266 hardware peripherals.
 */

/** 
 * @brief   Logic levels for digital signals.
 * @details Defines the logic high and low levels used in the application.
 *          These values are used to set or clear GPIO pins.
 */
#define LOGIC_HIGH_LEVEL    (1U)
#define LOGIC_LOW_LEVEL     (0U)

/* =======================================================================
 *                     Logical Pin Definitions
 * ======================================================================= */

/**
 * @brief   GPIO pin assigned to OLED SCL line (I²C clock).
 */
#define DIO_PIN_OLED_SCL        (5U)    /**< GPIO5 → D1 */

/**
 * @brief   GPIO pin assigned to OLED SDA line (I²C data).
 */
#define DIO_PIN_OLED_SDA        (4U)    /**< GPIO4 → D2 */

/** 
 * @brief I2C bus ID used for OLED communication.
 * ESP8266 only supports bus 0.
 */
#define DIO_I2C_BUS_OLED        (0U)

/**
 * @brief I2C address of the OLED display (SSD1306).
 */
#define DIO_I2C_ADDR_OLED       (0x3CU)

/**
 * @brief   Analog input channel used for MAX4466 microphone module.
 * @note    This maps to ADC0 (A0) on the ESP8266.
 */
#define DIO_ADC_MIC_CHANNEL     (0U)    /**< ADC0 → A0 */

/* You may optionally define helper aliases for clarity or expansion */
#define DIO_OLED_BUS_COUNT      (2U)

/** 
 * @brief   GPIO pin assigned to onboard LED on NodeMCU v3.
 * @note    This is typically GPIO2 (D4).
 */
#define DIO_PIN_LED_ONBOARD     (2U)    /**< GPIO2 → D4 */

/* =======================================================================
 *                       Public Function Prototypes
 * ======================================================================= */

/**
 * @brief   Configures the specified GPIO pin as output.
 *
 * @param[in]  pin_id  GPIO number (e.g., 0 to 16).
 */
extern void Dio_SetPinOutput(uint8_t pin_id);

/**
 * @brief   Configures the specified GPIO pin as input.
 *
 * @param[in]  pin_id  GPIO number (e.g., 0 to 16).
 */
extern void Dio_SetPinInput(uint8_t pin_id);

/**
 * @brief   Sets the specified pin to logic high level.
 *
 * @param[in]  pin_id  GPIO number to set.
 */
extern void Dio_SetPinHigh(uint8_t pin_id);

/**
 * @brief   Clears the specified pin to logic low level.
 *
 * @param[in]  pin_id  GPIO number to clear.
 */
extern void Dio_SetPinLow(uint8_t pin_id);

/**
 * @brief   Initializes I²C pin configuration for OLED display.
 */
extern void Dio_InitOledPins(void);

#endif /* DIO_CFG_H */