#include "midi.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int midi_parser(midi_parser_t *p, char recv);

midi_parser_t *create_midi_parser() {
  midi_parser_t *p = (midi_parser_t *) malloc(sizeof(midi_parser_t));
  if (!p) return NULL;
  p->state=READ_CMD;
  p->buf_idx = 0;
}

int midi_parser(midi_parser_t *p, char recv) {
  midi_parser_states_t next = p->state;
  bool done = false;
  // printf("Got %02x\n", (unsigned char) recv);


  switch(p->state) {
    case READ_CMD: {
      // printf(", READ_CMD");
      bool cmd_msg=true;
      int channel = recv & 0xf;
      int type = (recv >> 4) & 0xf;
      // printf(", Type=%u Channel=%u\n", type, channel);

      if (type & 8) {
        cmd_msg = true;
        p->channel = channel;
        p->type = type;
        p->msg.status.channel = channel;
        p->msg.status.type = type;
        switch(type) {
          case NOTE_OFF:
            // printf(", NOTE_OFF");
          case NOTE_ON:
            // printf(", NOTE_ON");
            next = READ_DATA;
            p->bytes_to_read=2;
            p->buf_idx=0;
            break;
        }
        break;
      } else {
        // We did not receive a command message. Check if we can 
        // do fallthrough.
        if (p->type == NOTE_ON) {
          next = READ_DATA;
          p->msg.status.channel = p->channel;
          p->msg.status.type = p->type;
          p->bytes_to_read=2;
          p->buf_idx=0;
        } else {
          p->type = 0;
          p->channel = 0;
          break;
        }
      }
    }

    case READ_DATA:
      if (p->buf_idx >= 3) {
        exit(1);
      }
      p->buffer[p->buf_idx++] = recv;
      if (p->bytes_to_read == p->buf_idx) {
        done = true;
        next = READ_CMD;
      }
      break;
  }

  p->state = next;

  if (done) {
    done = false;
    switch (p->msg.status.type) {
      case NOTE_OFF:
      case NOTE_ON: {
        midi_note_on_t * tmp = (midi_note_on_t *) &p->msg;
        tmp->pitch = p->buffer[0];
        tmp->velocity = p->buffer[1];
        break;
      }
    }
    return true;
  } else {
    return false;
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