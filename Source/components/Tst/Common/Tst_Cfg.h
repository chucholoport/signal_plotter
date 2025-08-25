#ifndef TST_CFG_H
#define TST_CFG_H

#include <stdint.h>
#include <string.h>
#include <stddef.h>

#define TEST_BUFFER_SIZE            512
#define TEST_BUFFER_MAX             (TEST_BUFFER_SIZE)
#define TEST_BUFFER_MIN             (-(TEST_BUFFER_SIZE))

extern int16_t* tst_buffer;

void Tst_Init(void);

void Tst_Clear(void);

#endif