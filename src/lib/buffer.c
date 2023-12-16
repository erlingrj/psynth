#include "buffer.h"
#include "platform.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "util.h"
#define NUM_BUFFERS 1024

sample_buffer_t _data[NUM_BUFFERS];
fsample_buffer_t _fdata[NUM_BUFFERS];
bool _used[NUM_BUFFERS] = {false};
bool _fused[NUM_BUFFERS] = {false};

lf_mutex_t lock;

int buffers_used=0;

void print_used() {
  printf("%d Used: ", buffers_used);
  for (int i = 0; i<NUM_BUFFERS; i++) {
    if (_used[i]) {
      printf("%d ", i);
    }
  }
  printf("\n");
}

static int get_buf_idx(void * buf, bool tdomain) {
  int idx;
  if (tdomain) {
    idx = (int) ((sample_buffer_t *) buf - &_data[0]);
  } else {
    idx = (int) ((fsample_buffer_t *) buf - &_fdata[0]);
  }
  return idx;
}

void* _buffer_ctor(bool tdomain) {
  if (lf_critical_section_enter(NULL) != 0) {
    lf_print_error_and_exit("Could not enter critical section");
  }
  buffers_used++;
  void* res = NULL;
  for (int i = 0; i<NUM_BUFFERS; i++) {
    if (tdomain) {
      if (!_used[i]) {
        _used[i] = true;
        res = (void *) &_data[i];
        break;
      }
    } else {
      if (!_fused[i]) {
        _fused[i] = true;
        res = (void *) &_fdata[i];
        break;
      }
    }
  }
  lf_critical_section_exit(NULL);
  if (res == NULL) lf_print_error_and_exit("Failed to allocate buffer");
  return res;
}

void _buffer_destructor(void* array, bool tdomain) {
  if (lf_critical_section_enter(NULL) != 0) {
    lf_print_error_and_exit("Could not enter critical section");
  }
  buffers_used--;
  int idx = get_buf_idx(array, tdomain);
  if (idx >= NUM_BUFFERS) {
    lf_print_error_and_exit("ERROR Tried to free something that wasnt allocated");
  }
  if (tdomain) {
    if (!_used[idx]) {
      lf_print_error_and_exit("ERROR Tried to free something that wasnt allocated");
    }
    memset(&_data[idx],0,sizeof(sample_buffer_t));
    _used[idx] = false;
  } else {
    if (!_fused[idx]) {
      lf_print_error_and_exit("ERROR Tried to free something that wasnt allocated");
    }
    memset(&_fdata[idx],0,sizeof(fsample_buffer_t));
    _fused[idx] = false;
  }
  // print_used();
  lf_critical_section_exit(NULL);
}

fsample_buffer_t* fsample_buffer_ctor() {
  return _buffer_ctor(false);
}
sample_buffer_t* sample_buffer_ctor() {
  return _buffer_ctor(true);
}
void fsample_buffer_destructor(void* array) {
  _buffer_destructor(array, false);
}
void sample_buffer_destructor(void* array) {
  _buffer_destructor(array, true);
}
void* sample_buffer_copy(void *_source) {
  int idx = (int) ((sample_buffer_t *) _source - &_data[0]);
  sample_buffer_t * source = (sample_buffer_t *) _source;
  sample_buffer_t * copy = _buffer_ctor(true);
  memcpy(copy, source, sizeof(sample_buffer_t));
  return (void *) copy;
}

void* fsample_buffer_copy(void *_source) {
  int idx = (int) ((fsample_buffer_t *) _source - &_fdata[0]);
  fsample_buffer_t * source = (fsample_buffer_t *) _source;
  fsample_buffer_t * copy = _buffer_ctor(false);
  memcpy(copy, source, sizeof(fsample_buffer_t));
  return (void *) copy;
}

float magnitude(kiss_fft_cpx val) {
  return sqrtf(val.i*val.i + val.r*val.r);
}
float phase(kiss_fft_cpx val) {
  return atan(val.i/val.r);
}