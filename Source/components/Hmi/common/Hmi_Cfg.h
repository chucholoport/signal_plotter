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

/* -------------------------------------------------------------------------- */
/* Byte scaling parameters                                                    */
/* Defines byte scaling macros                                                */
/* -------------------------------------------------------------------------- */
#define BYTE_SIZE                       (8U)
#define OLED_SCREEN_BYTES_WIDTH         (128U)
#define OLED_SCREEN_BYTES_HEIGHT        (64U)
#define OLED_SCREEN_BYTES_TOTAL         ((OLED_SCREEN_BYTES_WIDTH * OLED_SCREEN_BYTES_HEIGHT) / BYTE_SIZE)

/* -------------------------------------------------------------------------- */
/* Width & Height Macros                                                      */
/* Defines pixel area macros                                                  */
/* -------------------------------------------------------------------------- */
#define GET_BLOCK_WIDTH(x0, x1)         ((x1) - (x0))
#define GET_BLOCK_HEIGHT(y0, y1)        ((y1) - (y0))

#define TRUNCATE_BLOCK_WIDTH(x)         ((x > OLED_SCREEN_BYTES_WIDTH)  ? OLED_SCREEN_BYTES_WIDTH  : x)
#define TRUNCATE_BLOCK_HEIGHT(y)        ((y > OLED_SCREEN_BYTES_HEIGHT) ? OLED_SCREEN_BYTES_HEIGHT : y)

/* -------------------------------------------------------------------------- */
/* Font defaults Macros                                                       */
/* Defines font defaults macros                                               */
/* -------------------------------------------------------------------------- */
#define DEFAULT_FONT_SIZE         (1U)
#define DEFAULT_FONT_TYPE         STYLE_NORMAL

/* -------------------------------------------------------------------------- */
/* Message Parameters                                                         */
/* Defines Message pixel area macros                                          */
/* -------------------------------------------------------------------------- */
#define BLOCK_MESSAGE_X0                (0U)
#define BLOCK_MESSAGE_X1                (OLED_SCREEN_BYTES_WIDTH)

#define BLOCK_MESSAGE_Y0                (0U)
#define BLOCK_MESSAGE_Y1                (20U)

#define BLOCK_MESSAGE_WIDTH             TRUNCATE_BLOCK_WIDTH(GET_BLOCK_WIDTH(BLOCK_MESSAGE_X0, BLOCK_MESSAGE_X1))
#define BLOCK_MESSAGE_HEIGHT            TRUNCATE_BLOCK_HEIGHT(GET_BLOCK_HEIGHT(BLOCK_MESSAGE_Y0, BLOCK_MESSAGE_Y1))

#define BLOCK_MESSAGE_FONT_SIZE         (DEFAULT_FONT_SIZE)
#define BLOCK_MESSAGE_FONT_TYPE         (DEFAULT_FONT_TYPE)

/* -------------------------------------------------------------------------- */
/* Plot Parameters                                                            */
/* Defines Plot pixel area macros                                             */
/* -------------------------------------------------------------------------- */
#define BLOCK_PLOT_X0                   (40U)
#define BLOCK_PLOT_X1                   (OLED_SCREEN_BYTES_WIDTH)

#define BLOCK_PLOT_Y0                   (BLOCK_MESSAGE_Y1)
#define BLOCK_PLOT_Y1                   (OLED_SCREEN_BYTES_HEIGHT)

#define BLOCK_PLOT_WIDTH                TRUNCATE_BLOCK_WIDTH(GET_BLOCK_WIDTH(BLOCK_PLOT_X0, BLOCK_PLOT_X1))
#define BLOCK_PLOT_HEIGHT               TRUNCATE_BLOCK_HEIGHT(GET_BLOCK_HEIGHT(BLOCK_PLOT_Y0, BLOCK_PLOT_Y1))

#define BLOCK_PLOT_FONT_SIZE            (DEFAULT_FONT_SIZE)
#define BLOCK_PLOT_FONT_TYPE            (DEFAULT_FONT_TYPE)

/* -------------------------------------------------------------------------- */
/* Note Symbol Parameters                                                     */
/* Defines Note Symbol pixel area macros                                      */
/* -------------------------------------------------------------------------- */
#define BLOCK_SYMBOL_X0                 (BLOCK_MESSAGE_X0)
#define BLOCK_SYMBOL_X1                 (BLOCK_PLOT_X0)

#define BLOCK_SYMBOL_Y0                 (BLOCK_MESSAGE_Y1)
#define BLOCK_SYMBOL_Y1                 (40U)

#define BLOCK_SYMBOL_WIDTH              TRUNCATE_BLOCK_WIDTH(GET_BLOCK_WIDTH(BLOCK_SYMBOL_X0, BLOCK_SYMBOL_X1))
#define BLOCK_SYMBOL_HEIGHT             TRUNCATE_BLOCK_HEIGHT(GET_BLOCK_HEIGHT(BLOCK_SYMBOL_Y0, BLOCK_SYMBOL_Y1))

#define BLOCK_SYMBOL_FONT_SIZE          (1U)        
#define BLOCK_SYMBOL_FONT_TYPE          (DEFAULT_FONT_TYPE)

/* -------------------------------------------------------------------------- */
/* Note Needle Parameters                                                     */
/* Defines Note Needle pixel area macros                                      */
/* -------------------------------------------------------------------------- */
#define BLOCK_NEEDLE_X0                 (BLOCK_MESSAGE_X0)
#define BLOCK_NEEDLE_X1                 (BLOCK_PLOT_X0)

#define BLOCK_NEEDLE_Y0                 (BLOCK_SYMBOL_Y1)
#define BLOCK_NEEDLE_Y1                 (50U)

#define BLOCK_NEEDLE_WIDTH              TRUNCATE_BLOCK_WIDTH(GET_BLOCK_WIDTH(BLOCK_NEEDLE_X0, BLOCK_NEEDLE_X1))
#define BLOCK_NEEDLE_HEIGHT             TRUNCATE_BLOCK_HEIGHT(GET_BLOCK_HEIGHT(BLOCK_NEEDLE_Y0, BLOCK_NEEDLE_Y1))

#define BLOCK_NEEDLE_FONT_SIZE          (DEFAULT_FONT_SIZE)
#define BLOCK_NEEDLE_FONT_TYPE          (DEFAULT_FONT_TYPE)

/* -------------------------------------------------------------------------- */
/* Note Ruler Parameters                                                      */
/* Defines Note Needle pixel area macros                                      */
/* -------------------------------------------------------------------------- */
#define BLOCK_RULER_X0                  (BLOCK_MESSAGE_X0)
#define BLOCK_RULER_X1                  (BLOCK_PLOT_X0)

#define BLOCK_RULER_Y0                  (BLOCK_NEEDLE_Y1)
#define BLOCK_RULER_Y1                  (OLED_SCREEN_BYTES_HEIGHT)

#define BLOCK_RULER_WIDTH               TRUNCATE_BLOCK_WIDTH(GET_BLOCK_WIDTH(BLOCK_RULER_X0, BLOCK_RULER_X1))
#define BLOCK_RULER_HEIGHT              TRUNCATE_BLOCK_HEIGHT(GET_BLOCK_HEIGHT(BLOCK_RULER_Y0, BLOCK_RULER_Y1))

#define BLOCK_RULER_FONT_SIZE           (DEFAULT_FONT_SIZE)
#define BLOCK_RULER_FONT_TYPE           (DEFAULT_FONT_TYPE)

/** 
 * @brief HMI Block Parameters
 * 
 * These parameters define the coordinates and font for configuring blocks on the HMI.
 */
typedef struct {
    uint8_t x0;          /**< X0 Position */
    uint8_t x1;          /**< X1 Position */
    uint8_t y0;          /**< Y0 Position */
    uint8_t y1;          /**< Y1 Position */
    uint8_t width;       /**< Block width */
    uint8_t height;      /**< Block height */
    uint8_t font_size;   /**< Font size */
    uint8_t font_type;   /**< Font type */
} HmiBlock_Cfg_t;

/** 
 * @brief HMI Screen Parameters
 * 
 * These parameters define the blocks for configuring screen on the HMI.
 */
typedef struct {
    HmiBlock_Cfg_t message;
    HmiBlock_Cfg_t plot;
    HmiBlock_Cfg_t symbol;
    HmiBlock_Cfg_t needle;
    HmiBlock_Cfg_t ruler;
} HmiScreen_Cfg_t;

/* -------------------------------------------------------------------------- */
/* Screen Blocks Structures                                                   */
/* Defines Screen Blocks Structures for modular access                        */
/* -------------------------------------------------------------------------- */

#define HMI_MESSAGE_CFG                         \
    (HmiBlock_Cfg_t){                           \
        .x0        = BLOCK_MESSAGE_X0,          \
        .x1        = BLOCK_MESSAGE_X1,          \
        .y0        = BLOCK_MESSAGE_Y0,          \
        .y1        = BLOCK_MESSAGE_Y1,          \
        .width     = BLOCK_MESSAGE_WIDTH,       \
        .height    = BLOCK_MESSAGE_HEIGHT,      \
        .font_size = BLOCK_MESSAGE_FONT_SIZE,   \
        .font_type = BLOCK_MESSAGE_FONT_TYPE    \
    }

#define HMI_PLOT_CFG                            \
    (HmiBlock_Cfg_t){                           \
        .x0        = BLOCK_PLOT_X0,          \
        .x1        = BLOCK_PLOT_X1,          \
        .y0        = BLOCK_PLOT_Y0,          \
        .y1        = BLOCK_PLOT_Y1,          \
        .width     = BLOCK_PLOT_WIDTH,       \
        .height    = BLOCK_PLOT_HEIGHT,      \
        .font_size = BLOCK_PLOT_FONT_SIZE,   \
        .font_type = BLOCK_PLOT_FONT_TYPE    \
    }

#define HMI_SYMBOL_CFG                          \
    (HmiBlock_Cfg_t){                           \
        .x0        = BLOCK_SYMBOL_X0,          \
        .x1        = BLOCK_SYMBOL_X1,          \
        .y0        = BLOCK_SYMBOL_Y0,          \
        .y1        = BLOCK_SYMBOL_Y1,          \
        .width     = BLOCK_SYMBOL_WIDTH,       \
        .height    = BLOCK_SYMBOL_HEIGHT,      \
        .font_size = BLOCK_SYMBOL_FONT_SIZE,   \
        .font_type = BLOCK_SYMBOL_FONT_TYPE    \
    }

#define HMI_NEEDLE_CFG                          \
    (HmiBlock_Cfg_t){                           \
        .x0        = BLOCK_NEEDLE_X0,          \
        .x1        = BLOCK_NEEDLE_X1,          \
        .y0        = BLOCK_NEEDLE_Y0,          \
        .y1        = BLOCK_NEEDLE_Y1,          \
        .width     = BLOCK_NEEDLE_WIDTH,       \
        .height    = BLOCK_NEEDLE_HEIGHT,      \
        .font_size = BLOCK_NEEDLE_FONT_SIZE,   \
        .font_type = BLOCK_NEEDLE_FONT_TYPE    \
    }

#define HMI_RULER_CFG                           \
    (HmiBlock_Cfg_t){                           \
        .x0        = BLOCK_RULER_X0,          \
        .x1        = BLOCK_RULER_X1,          \
        .y0        = BLOCK_RULER_Y0,          \
        .y1        = BLOCK_RULER_Y1,          \
        .width     = BLOCK_RULER_WIDTH,       \
        .height    = BLOCK_RULER_HEIGHT,      \
        .font_size = BLOCK_RULER_FONT_SIZE,   \
        .font_type = BLOCK_RULER_FONT_TYPE    \
    }

/* -------------------------------------------------------------------------- */
/* Screen Structure                                                           */
/* Defines Screen Structure for modular access                                */
/* -------------------------------------------------------------------------- */

#define HMI_SCREEN_CFG                      \
    (HmiScreen_Cfg_t){                      \
        .message     = HMI_MESSAGE_CFG,     \
        .plot        = HMI_PLOT_CFG,        \
        .symbol      = HMI_SYMBOL_CFG,      \
        .needle      = HMI_NEEDLE_CFG,      \
        .ruler       = HMI_RULER_CFG        \
    }

/* -------------------------------------------------------------------------- */
/* Configuration                                                              */
/* Used for configuring HMI screen                                            */
/* -------------------------------------------------------------------------- */

/**
 * @brief Hmi Screen configuration instance.
 *
 * Instance of structure containing screen configuration
 * and blocks singular configurations definition.
 */
extern HmiScreen_Cfg_t hmi_cfg;

/* -------------------------------------------------------------------------- */
/* HMI Public Function Prototypes                                             */
/* -------------------------------------------------------------------------- */

/**
 * @brief Runs Set Up for the HMI display.
 *
 * This function sets up the display for the HMI, including initializing the
 * necessary hardware components and clearing the display.
 */
void Hmi_RunSetup(void);

/**
 * @brief Initializes the HMI display.
 *
 * This function sets up the display for the HMI, including initializing the
 * necessary blocks for project.
 */
void Hmi_Init(void);

#endif /* HMI_CFG_H */