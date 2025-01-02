#ifndef BUFFER_H
#define BUFFER_H

#include <stdbool.h>
#include "common.h"

typedef struct {
  SAMPLE_TYPE buffer[SAMPLE_SIZE];
} sample_buffer_t;

typedef struct {
  kiss_fft_cpx buffer[SAMPLE_SIZE];
} fsample_buffer_t;

float magnitude(kiss_fft_cpx val);
float phase(kiss_fft_cpx val);

#endif