#ifndef BUFFER_H
#define BUFFER_H

#include <stdbool.h>
#include "common.h"

typedef struct {
  SAMPLE_TYPE samples[SAMPLE_SIZE];
} sample_buffer_t;

typedef struct {
  kiss_fft_cpx samples[SAMPLE_SIZE];
} fsample_buffer_t;

fsample_buffer_t* fsample_buffer_ctor();
sample_buffer_t* sample_buffer_ctor();
void fsample_buffer_destructor(void* array);
void sample_buffer_destructor(void* array);
void* fsample_buffer_copy(void *_source);
void* sample_buffer_copy(void *_source);

#endif