#include "Trngl_Cfg.h"

#include "Tst_Cfg.h"
#include "Dsp_Cfg.h"
#include "Bitmap_Cfg.h"
#include "Plot_Cfg.h"

Dsp_Cfg_t trngl_cfg =
{
    /* data */
    .size         = TEST_BUFFER_SIZE,          // Size of the triangle wave buffer
    .sample_rate  = DSP_DEFAULT_SAMPLE_RATE,   // Sample rate for the triangle wave
    .gain         = DSP_GAIN,                  // Center value for the triangle wave
    .offset       = DSP_OFFSET,                // Center value for the triangle wave
    .threshold    = DSP_THRESHOLD,             // Threshold for detecting the triangle wave
    .max          = TEST_BUFFER_MAX,           // Maximum value for the triangle wave
    .min          = TEST_BUFFER_MIN,           // Minimum value for the triangle wave
    .fall_edge    = LOW_PASS_FILTER_FALL_EDGE, // Lower limit for the triangle wave histeresis
    .rise_edge    = LOW_PASS_FILTER_RISE_EDGE, // Upper limit for the triangle wave histeresis
    .average      = DSP_DEFAULT_AVERAGE,       // Default average value
    .level        = DSP_DEFAULT_LEVEL,         // Default level value
    .trigger      = DSP_DEFAULT_TRIGGER        // Trigger flag for the triangle wave
};

void generate_triangle_wave(void) 
{
  const float amplitude = (float)(TEST_BUFFER_MAX - TEST_BUFFER_MIN) / 2.0f;  // 512
  const float offset    = (float)(TEST_BUFFER_MAX + TEST_BUFFER_MIN) / 2.0f;  // 0
  const float period    = (float)(TEST_BUFFER_SIZE);

  for (size_t i = 0; i < TEST_BUFFER_SIZE; ++i) 
  {
    float phase = (float)i / period;
    float triangle = 0.0f;

    if (phase < 0.5f) 
    {
      // Rising edge: -1.0 to +1.0
      triangle = 4.0f * phase - 1.0f;
    } 
    else 
    {
      // Falling edge: +1.0 to -1.0
      triangle = -4.0f * phase + 3.0f;
    }

    // Scale and center in range [-512, 512]
    tst_buffer[i] = (int16_t)(triangle * amplitude + offset);
  }
}

void Triangle_Run(void)
{
  Tst_Init();

  generate_triangle_wave();
  Bitmap_Run(&trngl_cfg, &plot_cfg, tst_buffer, plot_bitmap);
}