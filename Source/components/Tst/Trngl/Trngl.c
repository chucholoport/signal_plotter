#include "Trngl_Cfg.h"

#include "Dsp_Cfg.h"
#include "Tst_Cfg.h"

DspBffr_Cfg_t trngl_cfg =
{
    /* data */
    .buffer_size = TEST_BUFFER_SIZE,  // Size of the triangle wave buffer
    .sample_rate = SIGNAL_BUFFER_DEFAULT_SAMPLE_RATE,  // Sample rate for the triangle wave
    .center      = SIGNAL_BUFFER_CENTER,  // Center value for the triangle wave
    .max         = TEST_BUFFER_MAX,  // Maximum value for the triangle wave
    .min         = TEST_BUFFER_MIN,  // Minimum value for the triangle wave
    .lower_limit = SIGNAL_BUFFER_LOWER_LIMIT,  // Lower limit for the triangle wave histeresis
    .upper_limit = SIGNAL_BUFFER_UPPER_LIMIT,  // Upper limit for the triangle wave histeresis
    .threshold   = SIGNAL_BUFFER_THRESHOLD,  // Threshold for detecting the triangle wave
    .average     = SIGNAL_BUFFER_DEFAULT_AVERAGE,  // Default average value
    .level       = SIGNAL_BUFFER_DEFAULT_LEVEL,  // Default level value
    .trigger     = SIGNAL_BUFFER_DEFAULT_TRIGGER  // Trigger flag for the triangle wave
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