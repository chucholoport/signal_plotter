#ifndef TRNGL_CFG_H
#define TRNGL_CFG_H

#include <stdint.h>

#include "Dsp_Cfg.h"

#define TRIANGLE_WAVE_LEGEND "Test Signal: Triangle Wave"

extern DspBffr_Cfg_t trngl_cfg;

void generate_triangle_wave(void);

#endif