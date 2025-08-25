#ifndef MESSAGE_CFG_H
#define MESSAGE_CFG_H

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @file   Message_Cfg.h
 * @brief Configuration for Message HMI Block.
 * @details This file contains the configuration settings for the Message HMI Block.
 */

/* -------------------------------------------------------------------------- */
/* Message behavior parameters                                                */
/* Defines Message behavior macros                                            */
/* -------------------------------------------------------------------------- */

#define MESSAGE_EMPTY               (" \0")

#define MESSAGE_KEEP                (0U)
#define MESSAGE_CLEAR               (1U)

#define MESSAGE_KEEP_TIMER_MS       (0U)
#define MESSAGE_CLEAR_TIMER_MS      (200U)

/* -------------------------------------------------------------------------- */
/* Message Structure                                                          */
/* Defines Message Structure for modular access                               */
/* -------------------------------------------------------------------------- */

/** 
 * @brief HMI Display Message Parameters
 * 
 * These parameters define the coordinates and duration for displaying messages on the HMI.
 */
typedef struct 
{
    char*    text;      /**< Pointer to the text to be displayed */
    uint8_t  clear;     /**< Flag to indicate if the display should be cleared before printing */
    uint16_t time;      /**< Duration in milliseconds to display the text */
} Message_t;

/* -------------------------------------------------------------------------- */
/* Message Instances                                                          */
/* Defines Message Instances for modular access                               */
/* -------------------------------------------------------------------------- */

/**
 * @brief Hmi message text buffer.
 *
 * Instance of message text buffer.
 */
extern char* text;

/**
 * @brief Hmi message structure.
 *
 * Instance of message structure.
 */
extern Message_t msg;

/* -------------------------------------------------------------------------- */
/* Message Public Function Prototypes                                         */
/* -------------------------------------------------------------------------- */

/** 
 * @brief Initializes the message text buffer.
 * 
 * This buffer is used to store the text messages that will be displayed on the HMI.
 * Modify the size as needed for your specific application.
 */
void Message_Init(void);

/**
 * @brief Fills a Message in the HMI display.
 *
 * This function updates the specified message with buffer contents.
 */
void Message_Fill(void);

/**
 * @brief Keeps the message on the display without clearing it.
 *
 * This function sets the parameters for keeping the message on the screen without refreshing it.
 */
void Message_Keep(void);

/**
 * @brief Clears the message on the display.
 *
 * This function sets the parameters for clearing the message on the screen.
 */
void Message_Clear(void);

/**
 * @brief Prints a Message in the HMI display.
 *
 * This function clears the display and prints the specified message for specified period at the given coordinates.
 */
void Message_Show(void);

/**
 * @brief Prints a Message in the HMI display.
 *
 * This function updates the display printing the specified message.
 */
void Message_Update(void);

/**
 * @brief Prints a Message in the HMI display.
 *
 * This function updates the display printing the specified message.
 */
void Message_Reload(void);

#endif /* MESSAGE_CFG_H */