#ifndef MIDI_H
#define MIDI_H

#define MIDI_MAX_PAYLOAD_BYTES 8

typedef enum {
    INVALID             = 0,
    NOTE_OFF            = 8,
    NOTE_ON             = 9, 
    AFTER_TOUCH         = 0xA,
    CONTROL_CHANGE      = 0xB,
    PATCH_CHANGE        = 0xC,
    CHANNEL_PRESSURE    = 0xD,
    PITCH_BEND          = 0xE,
    SYS_MSG             = 0xF
} midi_type_t;

// This enum describes the different CONTROL_CHANGE messages.
// This is inspired by Circuit Tracks.
typedef enum {
    OSCILLATOR = 80,
    OSCILLATOR_MOD = 81,
    AMP_ENVELOPE = 82,
    FILTER_ENVELOPE = 83,
    FILTER_FREQ = 84,
    RESONANCE = 85,
    MODULATION = 86,
    FX = 87,
    MASTER_FILTER = 74,
    VOLUME = RESONANCE,
} midi_controller_type_t;

// TODO: Create some macros to turn an enum into a string

// Define the byte struct
typedef struct {
    unsigned int channel:4;
    midi_type_t type:4;
} midi_status_t;

// The base message for MIDI. Any MIDI message can be casted to this
typedef struct {
    midi_status_t status;
    char padding[MIDI_MAX_PAYLOAD_BYTES];
} midi_base_msg_t;

typedef struct {
    midi_status_t status;
    unsigned int pitch;
    unsigned int velocity;
} midi_note_on_t;

typedef struct {
    midi_status_t status;
    unsigned char pitch;
    unsigned char velocity;
} midi_note_off_t;

typedef struct {
    midi_status_t status;
    unsigned char program;
} midi_program_change_t;

typedef struct {
    midi_status_t status;
    unsigned char controller;
    unsigned char value;
} midi_controller_change_t;

void print_midi(midi_base_msg_t * msg);

typedef enum {
    OSC_SINE    = 0,
    OSC_TRI     = 1,
    OSC_SQUARE  = 2,
    OSC_SAW     = 3,
    NUM_OSC
} osc_type_t;

typedef enum {
  READ_CMD,
  READ_DATA,
} midi_parser_states_t;

typedef struct midi_parser{
  midi_parser_states_t state;
  char buffer[3];
  int buf_idx;
  int bytes_to_read;
  midi_type_t type;
  int channel;
  midi_base_msg_t msg;
} midi_parser_t;

int midi_parser(midi_parser_t *p, char recv);

midi_parser_t *create_midi_parser();

#define MIDI_NOTE_ON(x) {.status.channel=0, .status.type=NOTE_ON, .pitch=(x), .velocity=60}
#define MIDI_NOTE_OFF(x) {.status.channel=0, .status.type=NOTE_OFF, .pitch=(x), .velocity=60}
#define MIDI_OSC_CHANGE(x){.status.channel=0, .status.type=CONTROL_CHANGE, .controller=OSCILLATOR, .value=((x) << 5)}
#define MIDI_FILTER_CUTOFF(x){.status.channel=0, .status.type=CONTROL_CHANGE, .controller=FILTER_FREQ, .value=(x)}

typedef enum {
    LANE_IDLE = -1,
    LANE_RELEASING = -2,
} lane_state_t;

#define NOTE_CN1	0
#define NOTE_CSN1	1
#define NOTE_DN1	2
#define NOTE_DSN1	3
#define NOTE_EN1	4
#define NOTE_FN1	5
#define NOTE_FSN1	6
#define NOTE_GN1	7
#define NOTE_GSN1	8
#define NOTE_AN1	9
#define NOTE_ASN1	10
#define NOTE_BN1	11
#define NOTE_C0		12
#define NOTE_CS0	13
#define NOTE_D0		14
#define NOTE_DS0	15
#define NOTE_E0		16
#define NOTE_F0		17
#define NOTE_FS0	18
#define NOTE_G0		19
#define NOTE_GS0	20
#define NOTE_A0		21
#define NOTE_AS0	22
#define NOTE_B0		23
#define NOTE_C1		24
#define NOTE_CS1	25
#define NOTE_D1		26
#define NOTE_DS1	27
#define NOTE_E1		28
#define NOTE_F1		29
#define NOTE_FS1	30
#define NOTE_G1		31
#define NOTE_GS1	32
#define NOTE_A1		33
#define NOTE_AS1	34
#define NOTE_B1		35
#define NOTE_C2		36
#define NOTE_CS2	37
#define NOTE_D2		38
#define NOTE_DS2	39
#define NOTE_E2		40
#define NOTE_F2		41
#define NOTE_FS2	42
#define NOTE_G2		43
#define NOTE_GS2	44
#define NOTE_A2		45
#define NOTE_AS2	46
#define NOTE_B2		47
#define NOTE_C3		48
#define NOTE_CS3	49
#define NOTE_D3		50
#define NOTE_DS3	51
#define NOTE_E3		52
#define NOTE_F3		53
#define NOTE_FS3	54
#define NOTE_G3		55
#define NOTE_GS3	56
#define NOTE_A3		57
#define NOTE_AS3	58
#define NOTE_B3		59
#define NOTE_C4		60
#define NOTE_CS4	61
#define NOTE_D4		62
#define NOTE_DS4	63
#define NOTE_E4		64
#define NOTE_F4		65
#define NOTE_FS4	66
#define NOTE_G4		67
#define NOTE_GS4	68
#define NOTE_A4		69
#define NOTE_AS4	70
#define NOTE_B4		71
#define NOTE_C5		72
#define NOTE_CS5	73
#define NOTE_D5		74
#define NOTE_DS5	75
#define NOTE_E5		76
#define NOTE_F5		77
#define NOTE_FS5	78
#define NOTE_G5		79
#define NOTE_GS5	80
#define NOTE_A5		81
#define NOTE_AS5	82
#define NOTE_B5		83
#define NOTE_C6		84
#define NOTE_CS6	85
#define NOTE_D6		86
#define NOTE_DS6	87
#define NOTE_E6		88
#define NOTE_F6		89
#define NOTE_FS6	90
#define NOTE_G6		91
#define NOTE_GS6	92
#define NOTE_A6		93
#define NOTE_AS6	94
#define NOTE_B6		95
#define NOTE_C7		96
#define NOTE_CS7	97
#define NOTE_D7		98
#define NOTE_DS7	99
#define NOTE_E7		100
#define NOTE_F7		101
#define NOTE_FS7	102
#define NOTE_G7		103
#define NOTE_GS7	104
#define NOTE_A7		105
#define NOTE_AS7	106
#define NOTE_B7		107
#define NOTE_C8		108
#define NOTE_CS8	109
#define NOTE_D8		110
#define NOTE_DS8	111
#define NOTE_E8		112
#define NOTE_F8		113
#define NOTE_FS8	114
#define NOTE_G8		115
#define NOTE_GS8	116
#define NOTE_A8		117
#define NOTE_AS8	118
#define NOTE_B8		119
#define NOTE_C9		120
#define NOTE_CS9	121
#define NOTE_D9		122
#define NOTE_DS9	123
#define NOTE_E9		124
#define NOTE_F9		125
#define NOTE_FS9	126
#define NOTE_G9		127

#endif