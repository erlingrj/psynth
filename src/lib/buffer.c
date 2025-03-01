#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "buffer.h"

float magnitude(kiss_fft_cpx val) {
  return sqrtf(val.i * val.i + val.r * val.r);
}

float phase(kiss_fft_cpx val) { return atan(val.i / val.r); }
