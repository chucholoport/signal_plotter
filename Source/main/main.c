/* Include ADC module */
#include "Adc_Cfg.h"

/* Include DSP algorithms */
#include "Dsp_Cfg.h"
#include "AtCrrltn_Cfg.h"

/* Include SSD1306 functions */
#include "Hmi_Cfg.h"
#include "SgnlPlttr_Cfg.h"
#include "Tuner_Cfg.h"

/* Include test signal generation */
#include "Tst_Cfg.h"
#include "Trngl_Cfg.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "ssd1306.h"

#define TEST_MODE_ON 0

#define MAIN_MESSAGE_TEXT_BUFFER_SIZE 30

char* main_msg_buffer = NULL;

/* Initialize message structure */
HmiDisplayMsg_t msg = 
{
    .text  = "Signal Plotter",
    .clear = 1,
    .time  = 500,
    .x     = 0,
    .y     = 0
};

void Test_Task(void* pvParameters)
{
    /* Initialize configuration structures */
    uint32_t   freq = 0U;

    NoteInfo_t note = 
    {
        .name     = "A#0",
        .symbol   = 'A',
        .exp_freq = 466,
        .cur_freq = 466,
        .cents    = 0
    };

    /* Initialize components */
    Hmi_Init();                                                         // Initialize the HMI display
    Hmi_InitMessage(&main_msg_buffer, MAIN_MESSAGE_TEXT_BUFFER_SIZE);   // Initialize the HMI message
    Adc_Init();                                                         // Initialize the ADC with the configuration
    Dsp_InitBuffer(&dsp_buffer, dsp_cfg.buffer_size);                   // Initialize the DSP buffer
    Frq_InitBuffer(&frq_buffer, dsp_cfg.buffer_size / 2);               // Initialize the Frequency buffer

    sprintf(main_msg_buffer, "Signal Plotter Ready!");
    Hmi_WriteMessage(&msg, main_msg_buffer);

    /* Initialize OLED blocks */
    SgnlPlttr_Init();
    Tuner_Init();

    if (TEST_MODE_ON)
    {
        TstBffr_Init();  // Initialize the test buffer
        TstBffr_ClearBuffer();  // Clear the test buffer
        
        generate_triangle_wave();
        
        SgnlPlttr_ClearBitmap();

        SgnlPlttr_FillShapedBuffer(&trngl_cfg, tst_buffer, &plt_cfg, oled_bitmap);

        SgnlPlttr_DisplayBitmap(&plt_cfg, oled_bitmap);

        while(true)
        {
            vTaskDelay(pdMS_TO_TICKS(1));
        }
    }


    while (true)
    {
        /* Fill the DSP buffer */
        Dsp_FillBuffer(&dsp_cfg, dsp_buffer);

        if (dsp_cfg.trigger)
        {
            /* Estimate frequency */
            freq = Frq_EstimateFundamental(&dsp_cfg, dsp_buffer);
            note = Tuner_GetNoteFromFreq(freq); 
            sprintf(main_msg_buffer, "Note: %-3s Frq: %-3dHz", note.name, freq);

        }
        else
        {
            /* No signal */
            freq = 0U;
            note = Tuner_GetNoteFromFreq(freq); 
            sprintf(main_msg_buffer, "Waiting for signal...");
        }
        
        /* Update message with main buffer */
        Hmi_UpdateMessage(&msg, main_msg_buffer);

        /* Run Signal Plotter*/
        SgnlPlttr_Run(&dsp_cfg, dsp_buffer, &plt_cfg, oled_bitmap);

        /* Run Tuner */
        Tuner_Run(&tuner_cfg, &note, needle_buffer, needle_bitmap);

        vTaskDelay(pdMS_TO_TICKS(50));
    }
    
}

void app_main(void)
{
    xTaskCreatePinnedToCore(
        Test_Task,
        "Test Task",
        4096,              // Tamaño de pila suficiente
        NULL,
        5,                 // Prioridad media
        NULL,
        1                  // Núcleo 1 (puedes cambiar a 0 si lo prefieres)
    );
}