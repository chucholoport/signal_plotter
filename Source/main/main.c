/* Include ADC module */
#include "Adc_Cfg.h"

/* Include DSP algorithms */
#include "Dsp_Cfg.h"
#include "Autocorrelation_Cfg.h"

/* Include SSD1306 functions */
#include "Hmi_Cfg.h"
#include "Message_Cfg.h"
#include "Plot_Cfg.h"
#include "Symbol_Cfg.h"
#include "Ruler_Cfg.h"
#include "Needle_Cfg.h"

/* Include test signal generation */
#include "Tst_Cfg.h"
#include "Trngl_Cfg.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define TEST_MODE_ON 0

char* main_msg_buffer = NULL;

void Test_Task(void* pvParameters)
{

    /* Hardware components initialization */
    Adc_Init();
    Dsp_Init();
    Hmi_Init();

    /* HMI Blocks initialization */
    Message_Init();
    Plot_Init();
    Symbol_Init();
    Ruler_Init();
    Needle_Init();

    /* Welcome message */
    sprintf(text, "Signal Plotter 2.0");
    Message_Update();
    Needle_Run();

    vTaskDelay(pdMS_TO_TICKS(50));
    
    if (TEST_MODE_ON)
    {
        
        Triangle_Run();
        
        while(true)
        {
            vTaskDelay(pdMS_TO_TICKS(50));
        }
    }

    while(true)
    {
        Dsp_Run();
    
        Plot_Run();

        Symbol_Run();
        Needle_Run();
        
        if (current_note.symbol != ' ')
        {
            sprintf(text, "%s frq: %-3d Hz       ", current_note.name, current_note.exp_freq);
        }
        else
        {
            sprintf(text, "Signal Plotter 2.0    ");
            
        }
        Message_Update();
        
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