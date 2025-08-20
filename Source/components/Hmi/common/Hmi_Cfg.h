#ifndef HMI_CFG_H
#define HMI_CFG_H

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @file   Hmi_Cfg.h
 * @brief Configuration for Human-Machine Interface (HMI).
 * @details This file contains the configuration settings for the HMI.
 */

#define OLED_SCREEN_WIDTH           (128U)
#define OLED_SCREEN_HEIGHT          (64U)
#define OLED_SCREEN_LIMIT           (20U)

#define OLED_BYTES_PER_ROW          (OLED_SCREEN_WIDTH)

#define TRUNCATE_AREA_LIMIT(val, lim) ((lim < val) ? val : lim)   

#define GET_WIDTH(x0, x1)             ((x1) - (x0))
#define GET_HEIGHT(y0, y1)            ((y1) - (y0))

/* -------------------------------------------------------------------------- */
/* Message Parameters                                                         */
/* Defines Message pixel area macros                                          */
/* -------------------------------------------------------------------------- */
#define OLED_MSG_X_START              (0U)
#define OLED_MSG_X_LIMIT              (TRUNCATE_AREA_LIMIT(OLED_SCREEN_WIDTH, OLED_SCREEN_WIDTH))

#define OLED_MSG_Y_START              (0U)
#define OLED_MSG_Y_LIMIT              (TRUNCATE_AREA_LIMIT(10U, 10U))

#define OLED_MSG_FONT_SIZE            (1U)
#define OLED_MSG_FONT_TYPE            STYLE_NORMAL
/* -------------------------------------------------------------------------- */
/* Plot Parameters                                                            */
/* Defines Plot pixel area macros                                             */
/* -------------------------------------------------------------------------- */
#define OLED_PLT_X_START              (40U)
#define OLED_PLT_X_LIMIT              (TRUNCATE_AREA_LIMIT(OLED_SCREEN_WIDTH, OLED_SCREEN_WIDTH))

#define OLED_PLT_Y_START              (20U)
#define OLED_PLT_Y_LIMIT              (TRUNCATE_AREA_LIMIT(OLED_SCREEN_HEIGHT, OLED_SCREEN_HEIGHT))

/* -------------------------------------------------------------------------- */
/* Note Symbol Parameters                                                     */
/* Defines Note Symbol pixel area macros                                      */
/* -------------------------------------------------------------------------- */
#define OLED_SYM_X_START              (0U)
#define OLED_SYM_X_LIMIT              (TRUNCATE_AREA_LIMIT(30U, OLED_PLT_X_START))

#define OLED_SYM_Y_START              (20U)
#define OLED_SYM_Y_LIMIT              (TRUNCATE_AREA_LIMIT(50U, 50U))

#define OLED_SYM_FONT_SIZE            (2U)        
#define OLED_SYM_FONT_TYPE            STYLE_NORMAL

/* -------------------------------------------------------------------------- */
/* Note Needle Parameters                                                     */
/* Defines Note Needle pixel area macros                                      */
/* -------------------------------------------------------------------------- */
#define OLED_NDL_X_START              (OLED_SYM_X_START)
#define OLED_NDL_X_LIMIT              (OLED_SYM_X_LIMIT)

#define OLED_NDL_Y_START              (OLED_SYM_Y_LIMIT)
#define OLED_NDL_Y_LIMIT              (OLED_SCREEN_HEIGHT)

#define OLED_NDL_LENGTH               (4U)
#define OLED_NDL_THICKNESS            (2U)

/**
 * @brief Total number of bytes required to represent the full OLED screen.
 * 
 * Each byte represents 8 vertical pixels. The buffer is organized in pages.
 */
#define OLED_SCREEN_BYTES_NO        ((OLED_SCREEN_WIDTH * OLED_SCREEN_HEIGHT) / 8U)

/**
 * @brief Maximum length of the message to be displayed on the HMI.
 */
#define DISPLAY_MAX_MSG_LEN 128U  



/** 
 * @brief HMI Display Message Parameters
 * 
 * These parameters define the coordinates and duration for displaying messages on the HMI.
 */
typedef struct 
{
    const char *text;   /**< Pointer to the text to be displayed */
    uint8_t clear;      /**< Flag to indicate if the display should be cleared before printing */
    uint16_t time;      /**< Duration in milliseconds to display the text */
    uint8_t x;          /**< X-coordinate for text cursor position */
    uint8_t y;          /**< Y-coordinate for text cursor position */
} HmiDisplayMsg_t;

typedef struct {
    uint8_t x;          /**< X Position */
    uint8_t y;          /**< Y Position */
    uint8_t font_size;  /**< Font size */
} HmiMessage_Cfg_t;

typedef struct {
    uint8_t x0;          /**< X Start Position */
    uint8_t x1;          /**< X Limit Position */
    uint8_t y0;          /**< Y Start Position */
    uint8_t y1;          /**< Y Limit Position */
    uint8_t width;       /**< Plot width */
    uint8_t height;      /**< Plot height */
} HmiPlot_Cfg_t;

typedef struct {
    uint8_t font_size;   /**< Font size */
    uint8_t font_type;   /**< Font type */
    uint8_t x0;          /**< X Start Position */
    uint8_t x1;          /**< X Limit Position */
    uint8_t y0;          /**< Y Start Position */
    uint8_t y1;          /**< Y Limit Position */
    uint8_t width;       /**< Tuner width */
    uint8_t height;      /**< Tuner height */
} HmiNoteSymbol_Cfg_t;

typedef struct {
    uint8_t x0;          /**< X Start Position */
    uint8_t x1;          /**< X Limit Position */
    uint8_t y0;          /**< Y Start Position */
    uint8_t y1;          /**< Y Limit Position */
    uint8_t length;     /**< Needle length */
    uint8_t thickness;  /**< Needle thickness */
} HmiNeedle_Cfg_t;


typedef struct {
    HmiMessage_Cfg_t    message;
    HmiPlot_Cfg_t       plot;
    HmiNoteSymbol_Cfg_t note_symbol;
    HmiNeedle_Cfg_t     needle;
} HmiScreen_Cfg_t;


#define HMI_MSG_CFG_DEFAULT             \
    (HmiMessage_Cfg_t){                 \
        .x = OLED_MSG_X_START,          \
        .y = OLED_MSG_Y_START,          \
        .font_size = OLED_MSG_FONT_SIZE \
    }

#define HMI_PLT_CFG_DEFAULT         \
    (HmiPlot_Cfg_t){                \
        .x0 = OLED_PLT_X_START,     \
        .x1 = OLED_PLT_X_LIMIT,     \
        .y0 = OLED_PLT_Y_START,     \
        .y1 = OLED_PLT_Y_LIMIT,     \
        .width  = GET_WIDTH (OLED_PLT_X_START, OLED_PLT_X_LIMIT), \
        .height = GET_HEIGHT(OLED_PLT_Y_START, OLED_PLT_Y_LIMIT)  \
    }

#define HMI_SYM_CFG_DEFAULT              \
    (HmiNoteSymbol_Cfg_t){               \
        .font_size = OLED_SYM_FONT_SIZE, \
        .font_type = OLED_SYM_FONT_TYPE, \
        .x0 = OLED_SYM_X_START,          \
        .x1 = OLED_SYM_X_START,          \
        .y0 = OLED_SYM_Y_START,          \
        .y1 = OLED_SYM_Y_START,          \
        .width  = GET_WIDTH (OLED_SYM_X_START, OLED_SYM_X_LIMIT), \
        .height = GET_HEIGHT(OLED_SYM_Y_START, OLED_SYM_Y_LIMIT)  \
    }

#define HMI_NDL_CFG_DEFAULT             \
    (HmiNeedle_Cfg_t){                  \
        .x0 = OLED_NDL_X_START,         \
        .x1 = OLED_NDL_X_LIMIT,         \
        .y0 = OLED_NDL_Y_START,         \
        .y1 = OLED_NDL_Y_LIMIT,         \
        .length = OLED_NDL_LENGTH,      \
        .thickness = OLED_NDL_THICKNESS \
    }

#define HMI_CFG_DEFAULT                     \
    (HmiScreen_Cfg_t){                      \
        .message     = HMI_MSG_CFG_DEFAULT, \
        .plot        = HMI_PLT_CFG_DEFAULT, \
        .note_symbol = HMI_SYM_CFG_DEFAULT, \
        .needle      = HMI_NDL_CFG_DEFAULT  \
    }

extern HmiScreen_Cfg_t hmi_cfg;

/** 
 * @brief Initializes the message text buffer.
 * 
 * This buffer is used to store the text messages that will be displayed on the HMI.
 * Modify the size as needed for your specific application.
 */
void Hmi_InitMessage(char** msg_buffer, size_t size);

/** 
 * @brief Clears the message text buffer.
 * 
 * This function clears the message text buffer to prepare it for new messages.
 *
 * @param msg Pointer to the HmiDisplayMsg_t structure containing the message parameters.
 * @param buffer Pointer to the buffer to be cleared.
 * @return A string of spaces to clear the line on the display.
 */ 
void Hmi_ClearMessage(HmiDisplayMsg_t* msg, char* buffer);

/**
 * @brief Keeps the message on the display without clearing it.
 * This function sets the parameters for keeping the message on the screen without refreshing it.
 * @param msg Pointer to the HmiDisplayMsg_t structure containing the message parameters.
 * @param buffer Pointer to the buffer that holds the message text.
 */
void Hmi_KeepMessage(HmiDisplayMsg_t* msg, char* buffer);

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
void Hmi_DisplayMessage(HmiDisplayMsg_t* msg);

void Hmi_WriteMessage(HmiDisplayMsg_t* msg, char* buffer);

void Hmi_UpdateMessage(HmiDisplayMsg_t* msg, char* buffer);

void Hmi_Init(void);

#endif /* HMI_CFG_H */