#include "Hmi_Cfg.h"

void Hmi_MsgInit(const uint8_t* msg_buffer, size_t size)
{
    if (msg_buffer != NULL) 
    {
        free(msg_buffer);
    }

    msg_buffer = (char*)malloc(size * sizeof(char));
}

void Hmi_DisplayInit(void)
{
    DrvDio_InitOledPins();                /* Configure GPIOs used for I²C */
    ssd1306_128x64_i2c_initEx2(DIO_I2C_BUS_OLED, DIO_PIN_OLED_SCL, DIO_PIN_OLED_SDA, DIO_I2C_ADDR_OLED);  /* Initialize SSD1306 controller busId = 0 for ESP8266 */
    ssd1306_setFixedFont(ssd1306xled_font6x8);
    ssd1306_enableAsciiMode();
    ssd1306_clearScreen();                /* Start with blank screen */
}

void Hmi_DisplayMessage(HmiDisplayMsg_t *msg) 
{
    
    /* Check if the message pointer and text are valid */
    if (msg == NULL || msg->text == NULL) 
    {
        return;
    }

    /* If clear flag is set, clear the display */
    if (msg->clear) 
    {
        ssd1306_clearScreen();
    }

    /* Sets cursor position */
    ssd1306_setCursor(msg->x, msg->y);     
    /* Prints text in screen */
    ssd1306_print(msg->text);        

    /* If the time is not zero, it will display the message for the specified duration */
    if (msg->time > 0)
    {
        /* Waits for the specified time */
        vTaskDelay(pdMS_TO_TICKS(msg->time));  
        /* Clears the screen after the delay */
        ssd1306_clearScreen();
    }
}