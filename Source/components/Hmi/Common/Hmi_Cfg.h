#ifndef HMI_CFG_H
#define HMI_CFG_H

#include <stdint.h>

/**
 * @file   Hmi_Cfg.h
 * @brief Configuration for Human-Machine Interface (HMI).
 * @details This file contains the configuration settings for the HMI.
 */

/** 
 * @brief HMI Display Message Parameters
 * 
 * These parameters define the coordinates and duration for displaying messages on the HMI.
 */
typedef struct 
{
    const char *text;   /**< Pointer to the text to be displayed */
    uint8_t clear;      /**< Flag to indicate if the display should be cleared before printing */
    uint8_t time;       /**< Duration in milliseconds to display the text */
    uint8_t x;          /**< X-coordinate for text cursor position */
    uint8_t y;          /**< Y-coordinate for text cursor position */
} HmiDisplayMsg_t;

/** 
 * @brief Initializes the message text buffer.
 * 
 * This buffer is used to store the text messages that will be displayed on the HMI.
 * Modify the size as needed for your specific application.
 */
void Hmi_MsgInit(const uint8_t* msg_buffer, size_t size);

/**
 * @brief Initializes the HMI display.
 *
 * This function sets up the display for the HMI, including initializing the
 * necessary hardware components and clearing the display.
 */
void Hmi_DisplayInit(void);

/**
 * @brief Prints a Message in the HMI display.
 *
 * This function clears the display and prints the specified message for specified period at the given coordinates.
 * @param msg Pointer to the HmiDisplayMsg_t structure containing the message parameters.
 */
void Hmi_DisplayMessage(HmiDisplayMsg_t *msg);