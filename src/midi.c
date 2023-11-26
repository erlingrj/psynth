#include "midi.h"
#include "util.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int midi_parser(midi_parser_t *p, char recv);

#ifdef MIDI_DEBUG
#define MIDI_DBG_PRINT(fmt, args...) do {printf(fmt, ##args)} while(0)
#else
#define MIDI_DBG_PRINT(fmt, args...) while(0) {}
#endif


midi_parser_t *create_midi_parser() {
  midi_parser_t *p = (midi_parser_t *) malloc(sizeof(midi_parser_t));
  if (!p) return NULL;
  p->state=READ_CMD;
  p->buf_idx = 0;
  p->type = INVALID;
  return p;
}

int midi_parser(midi_parser_t *p, char recv) {
  midi_parser_states_t next = p->state;
  bool done = false;
  MIDI_DBG_PRINT("%02x", (unsigned char) recv);
  switch(p->state) {
    case READ_CMD: {
      MIDI_DBG_PRINT(", READ_CMD");
      bool cmd_msg=true;
      int channel = recv & 0xf;
      int type = (recv >> 4) & 0xf;
      // MIDI_DBG_PRINT(", Type=%u Channel=%u\n", type, channel);

      if (type & 8) {
        cmd_msg = true;
        p->channel = channel;
        p->type = type;
        p->msg.status.channel = channel;
        p->msg.status.type = type;
        switch(type) {
          case NOTE_OFF:
            // MIDI_DBG_PRINT(", NOTE_OFF");
          case NOTE_ON:
            MIDI_DBG_PRINT(", NOTE_ON");
            next = READ_DATA;
            p->bytes_to_read=2;
            p->buf_idx=0;
            break;
          case AFTER_TOUCH:
            MIDI_DBG_PRINT(", AFTER_TOUCH");
            break;
          case CONTROL_CHANGE:
            MIDI_DBG_PRINT(", CONTROL_CHANGE");
            next = READ_DATA;
            p->bytes_to_read=2;
            p->buf_idx=0;
            break;
          case PATCH_CHANGE:
            MIDI_DBG_PRINT(", PATCH_CHANGE");
            next = READ_DATA;
            p->bytes_to_read=1;
            p->buf_idx=0;
            break;
          case CHANNEL_PRESSURE:
            MIDI_DBG_PRINT(", CHANNEL_PRESSURE");
            next = READ_DATA;
            p->bytes_to_read=1;
            p->buf_idx=0;
            break;
          case PITCH_BEND:
            MIDI_DBG_PRINT(", PITCH_BEND");
            next = READ_DATA;
            p->bytes_to_read=1;
            p->buf_idx=0;
            break;
          case SYS_MSG:
            MIDI_DBG_PRINT(", SYS_MSG");
            break;
          }
          break;
      } else if (p->type != INVALID){
        // We did not receive a command message. Check if we can 
        // do fallthrough.
          MIDI_DBG_PRINT(", RUNNING_STATUS  ");
          next = READ_DATA;
          p->msg.status.channel = p->channel;
          p->msg.status.type = p->type;
          p->buf_idx=0;
      } else {
        break;
      }
    }

    case READ_DATA:
      MIDI_DBG_PRINT(", READ_DATA-%d", p->buf_idx);
      if (p->buf_idx >= 3) {
        lf_print_error_and_exit("midi_parser: buf_idx=3");
      }
      p->buffer[p->buf_idx++] = recv;
      if (p->bytes_to_read == p->buf_idx) {
        MIDI_DBG_PRINT(", DONE");
        done = true;
        next = READ_CMD;
      }
      break;
  }

  p->state = next;

  MIDI_DBG_PRINT("\n");

  if (done) {
    done = false;
    bool recognized = false;
    switch (p->msg.status.type) {
      case NOTE_OFF:
      case NOTE_ON: {
        midi_note_on_t * tmp = (midi_note_on_t *) &p->msg;
        tmp->pitch = p->buffer[0];
        tmp->velocity = p->buffer[1];
        recognized = true;
        break;
      }
      case AFTER_TOUCH:
        break;
      case CONTROL_CHANGE: {
        midi_controller_change_t * tmp = (midi_controller_change_t *) &p->msg;
        tmp->controller = p->buffer[0];
        tmp->value = p->buffer[1];
        recognized = true;
        break;
      }
      case PATCH_CHANGE: {
        midi_program_change_t * tmp = (midi_program_change_t *) &p->msg;
        tmp->program = p->buffer[0];
        recognized = true;
        break;
      }
      case CHANNEL_PRESSURE:
        break;
      case PITCH_BEND:
        break;
      case SYS_MSG:
        break;
      }
    return recognized;
  } else {
    return false;
  }
}

void print_midi(midi_base_msg_t * msg) {
  switch (msg->status.type) {
    case NOTE_ON: {
      midi_note_on_t * tmp = (midi_note_on_t *) msg;
      lf_print("Type: NOTE_ON\tChannel=%u\tPitch=%u\tVelocity=%u", tmp->status.channel, tmp->pitch, tmp->velocity);
      break;
    }
    case NOTE_OFF: {
      midi_note_off_t * tmp = (midi_note_off_t *) msg;
      lf_print("Type: NOTE_OFF Channel=%u\tPitch=%u\tVelocity=%u", tmp->status.channel, tmp->pitch, tmp->velocity);
      break;
    }
    case CONTROL_CHANGE: {
      midi_controller_change_t * tmp = (midi_controller_change_t *) msg;
      lf_print("Type: CONTROL_CHANGE Channel=%u\tController=%u\tValue=%u", tmp->status.channel, tmp->controller, tmp->value);
      break;
    }
    case PATCH_CHANGE: {
      midi_program_change_t * tmp = (midi_program_change_t *) msg;
      lf_print("Type: PROGRAM_CHANGE Channel=%u\tProgram=%u", tmp->status.channel, tmp->program);
      break;
    }
    default:
      lf_print("Type: %u UNRECOGNIZED\tChannel=%u", msg->status.type, msg->status.channel);
      break;
  }
}