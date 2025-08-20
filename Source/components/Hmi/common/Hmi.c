#include "Hmi_Cfg.h"

#include "Dio_Cfg.h"

#include "ssd1306.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

HmiScreen_Cfg_t hmi_cfg;

void Hmi_InitMessage(char** buffer, size_t size)
{
    if (*buffer != NULL) 
    {
        free(*buffer);
    }

    *buffer = (char*)malloc(size);
}

void Hmi_ClearMessage(HmiDisplayMsg_t* msg, char* buffer)
{
    size_t len = strlen(msg->text);

    memset(buffer, ' ', len);
    buffer[len] = '\0';
}

void Hmi_KeepMessage(HmiDisplayMsg_t* msg, char* buffer)
{
    /* Set parameters for keeping message on screen without refresh */
    msg->text  = buffer;
    msg->clear = 0;
    msg->time  = 0;
}

void Hmi_DisplayInit(void)
{
    Dio_InitOledPins();
    ssd1306_128x64_i2c_initEx2(DIO_I2C_BUS_OLED, DIO_PIN_OLED_SCL, DIO_PIN_OLED_SDA, DIO_I2C_ADDR_OLED);
    ssd1306_setFixedFont(ssd1306xled_font6x8);
    ssd1306_enableAsciiMode();
    ssd1306_clearScreen();
}

void Hmi_DisplayMessage(HmiDisplayMsg_t* msg) 
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
        char clear_line[DISPLAY_MAX_MSG_LEN];

        /* Waits for the specified time */
        vTaskDelay(pdMS_TO_TICKS(msg->time));  
        /* Clears the screen after the delay */
        Hmi_ClearMessage(msg, clear_line);
        ssd1306_setCursor(msg->x, msg->y);
        ssd1306_print(clear_line);

    }
}

void Hmi_WriteMessage(HmiDisplayMsg_t* msg, char* buffer)
{
    msg->text = buffer;
    Hmi_DisplayMessage(msg);
}

void Hmi_UpdateMessage(HmiDisplayMsg_t* msg, char* buffer)
{
    Hmi_KeepMessage(msg, buffer);
    Hmi_DisplayMessage(msg);
}

void Hmi_Init(void)
{
    hmi_cfg = HMI_CFG_DEFAULT;
    Hmi_DisplayInit();
}