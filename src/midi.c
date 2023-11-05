#include "midi.h"
#include <stdbool.h>
#include <stdio.h>

typedef enum {
  READ_CMD,
  READ_DATA,
} midi_parser_states_t;


// Fix this parser. In particular, it seems that it MIGHT skip command bytes if
// the midi messages are very close. Then we just continue with multiple NOTE_ON
// messages. So it seems that if we are in READ_CMD and we read a message with 
// highest bit 0, then we assume that we are just continuing with the previous 
// message. 

// SO we should latch in the curr_cmd so we can "reuse it"
int midi_parser(char recv, midi_base_msg_t * output) {
  static midi_parser_states_t curr = READ_CMD;
  static int bytes_to_read=0;
  static char buffer[3];
  static int buf_idx = 0;
  static int prev_pitch = 0;

  midi_parser_states_t next = curr;
  bool done = false;
  if (((unsigned char)recv )!= 0xfe) printf("Got %02x\n", (unsigned char) recv);


  switch(curr) {
    case READ_CMD: {
      // printf(", READ_CMD");
      bool recognized_type=false;
      int channel = recv & 0xf;
      int type = (recv >> 4) & 0xf;
      // printf(", Type=%u Channel=%u", type, channel);
      
      switch(type) {
        case NOTE_OFF:
          // printf(", NOTE_OFF");
        case NOTE_ON:
          // printf(", NOTE_ON");
          next = READ_DATA;
          output->status.channel = channel;
          output->status.type = type;
          bytes_to_read=2;
          buf_idx=0;
          recognized_type=true;
          break;
      }

      if (!recognized_type && recv == prev_pitch) {
        // Fallthrough to READ_CMD, Wierd optimization on Oxygen 8 MIDI
          // printf(", NOTE_OFF");
          next = READ_DATA;
          output->status.channel = channel;
          output->status.type = NOTE_OFF;
          bytes_to_read=2;
          buf_idx=0;
      } else {
        break;
      }
    }

    case READ_DATA:
      
      // printf(", READ_DATA");
      buffer[buf_idx++] = recv;
      if (bytes_to_read == buf_idx) {
        done = true;
        next = READ_CMD;
      }
      break;
  }

  curr = next;

  if (done) {
    // printf(", DONE");
    done = false;
    prev_pitch = 0;
    switch (output->status.type) {
      case NOTE_OFF:
      case NOTE_ON: {
        midi_note_on_t * tmp = (midi_note_on_t *) output;
        prev_pitch = buffer[0];
        tmp->pitch = buffer[0];
        tmp->velocity = buffer[1];
        break;
      }
    }
    // printf("\n");
    return 0;
  } else {
    // printf("\n");
    return 1;
  }
}

void print_midi(midi_base_msg_t * msg) {
  switch (msg->status.type) {
    case NOTE_ON: {
      midi_note_on_t * tmp = (midi_note_on_t *) msg;
      printf("Type: NOTE_ON\tChannel=%u\tPitch=%u\tVelocity=%u\n", tmp->status.channel, tmp->pitch, tmp->velocity);
      break;
    }
    case NOTE_OFF: {
      midi_note_off_t * tmp = (midi_note_off_t *) msg;
      printf("Type: NOTE_OFF Channel=%u\tPitch=%u\tVelocity=%u\n", tmp->status.channel, tmp->pitch, tmp->velocity);
      break;
    }
    default:
      printf("Type: %u UNRECOGNIZED\tChannel=%u\n", msg->status.type, msg->status.channel);
      break;
  }
}