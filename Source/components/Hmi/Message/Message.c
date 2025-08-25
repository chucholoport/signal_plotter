#include "Message_Cfg.h"

#include "Hmi_Cfg.h"

#include "ssd1306.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/**
 * @file    Message.c
 * @brief   Implementation for Message HMI Block.
 * @details This file contains the implementation for the Message HMI Block.
 */

/* Text buffer */
char* text = NULL;

/* Message struct */
Message_t msg =
{
    .text  = MESSAGE_EMPTY,
    .clear = MESSAGE_CLEAR,
    .time  = MESSAGE_CLEAR_TIMER_MS
};

/* Copy block configuration from HMI configuration */
static HmiBlock_Cfg_t cfg;

void Message_Init(void)
{
    /* Validate if text buffer is valid */
    if (text != NULL) 
    {
        free(text);
    }

    /* Set text buffer memory allocation*/
    text = (char*)malloc(strlen(MESSAGE_EMPTY) + 1);

    /* Set configuration */
    cfg = hmi_cfg.message;
}

void Message_Fill(void)
{
    /* Fills message with buffer */
    msg.text = text;
}

void Message_Keep(void)
{
    /* Set parameters for keeping message on screen without refresh */
    msg.clear = MESSAGE_KEEP;
    msg.time  = MESSAGE_KEEP_TIMER_MS;
}

void Message_Clear(void)
{
    /* Set parameters for clearing message on screen */
    msg.clear = MESSAGE_CLEAR;
    msg.time  = MESSAGE_CLEAR_TIMER_MS;
}


void Message_Show(void) 
{
    /* If clear flag is set, clear the display */
    if (msg.clear) 
    {
        ssd1306_clearScreen();
    }

    /* Sets cursor position  & prints text in screen */
    ssd1306_setCursor(cfg.x0, cfg.y0);
    ssd1306_print(msg.text);        

    /* If the time is not zero, it will display the message for the specified duration */
    if (msg.time > 0)
    {
        size_t msg_len = strlen(msg.text); 

        /* Waits for the specified time */
        vTaskDelay(pdMS_TO_TICKS(msg.time));  
        
        /* Generate empty message for display */
        memset(msg.text, ' ', msg_len);
        msg.text[msg_len] = '\0';
        
        /* Sets cursor position  & prints empty text in screen */
        ssd1306_setCursor(cfg.x0, cfg.y0);
        ssd1306_print(msg.text);
    }
}

void Message_Update(void)
{
    Message_Fill();
    Message_Keep();
    Message_Show();
}

void Message_Reload(void)
{
    Message_Fill();
    Message_Clear();
    Message_Show();
}