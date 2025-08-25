#include "Hmi_Cfg.h"

#include "Dio_Cfg.h"

#include "ssd1306.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

HmiScreen_Cfg_t hmi_cfg;

void Hmi_RunSetup(void)
{
    /* Initialize DIO */
    Dio_InitOledPins();
    
    /* Initialize I2C */
    ssd1306_128x64_i2c_initEx2(DIO_I2C_BUS_OLED, DIO_PIN_OLED_SCL, DIO_PIN_OLED_SDA, DIO_I2C_ADDR_OLED);

    /* Set screen font & ASCII */
    ssd1306_setFixedFont(ssd1306xled_font6x8);
    ssd1306_enableAsciiMode();

    /* Cleanup screen */
    ssd1306_clearScreen();
}

void Hmi_Init(void)
{
    /* Set screen blocks configuration */
    hmi_cfg = HMI_SCREEN_CFG;

    /* Run screen setup */
    Hmi_RunSetup();
}