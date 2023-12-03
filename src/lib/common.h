#ifndef COMMON_H
#define COMMON_H

#include "kiss_fft.h"
#include <math.h>

#define SAMPLE_SIZE 128
#define SAMPLE_TYPE float
#define SAMPLE_RATE 44100
#define SAMPLE_NUM_BYTES SAMPLE_SIZE*sizeof(SAMPLE_TYPE)
#define SAMPLE_STEP 0.000022676
    
#define PI 3.14159

#ifndef MIN
#define MIN(x, y)  ((x) < (y) ? (x) : (y))
#endif
#ifndef MAX
#define MAX(x, y)  ((x) > (y) ? (x) : (y))
#endif

#define MAG(x) (x.i*x.i + x.r*x.r)
#define PHASE(x) (atan(x.i/x.r))

#endif
