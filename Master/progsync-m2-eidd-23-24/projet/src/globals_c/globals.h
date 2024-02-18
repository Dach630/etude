/* --- Generated the 28/11/2023 at 13:4 --- */
/* --- heptagon compiler, version 1.05.00 (compiled tue. oct. 3 15:20:46 CET 2023) --- */
/* --- Command line: /home/chengd/.opam/ocaml-variants/bin/heptc -c -target c globals.ept --- */

#ifndef GLOBALS_H
#define GLOBALS_H

#include "globals_types.h"
#include "debug.h"
typedef struct Globals__dbg_position_out {
} Globals__dbg_position_out;

void Globals__dbg_position_step(string msg, Globals__position p,
                                Globals__dbg_position_out* _out);

typedef struct Globals__dbg_phase_out {
} Globals__dbg_phase_out;

void Globals__dbg_phase_step(string msg, Globals__phase ph,
                             Globals__dbg_phase_out* _out);

typedef struct Globals__dbg_interrupt_out {
} Globals__dbg_interrupt_out;

void Globals__dbg_interrupt_step(string msg, Globals__interrupt itr,
                                 Globals__dbg_interrupt_out* _out);

typedef struct Globals__dbg_status_out {
} Globals__dbg_status_out;

void Globals__dbg_status_step(string msg, Globals__status sta,
                              Globals__dbg_status_out* _out);

typedef struct Globals__dbg_wheels_out {
} Globals__dbg_wheels_out;

void Globals__dbg_wheels_step(string msg, Globals__wheels wh,
                              Globals__dbg_wheels_out* _out);

typedef struct Globals__dbg_action_out {
} Globals__dbg_action_out;

void Globals__dbg_action_step(string msg, Globals__action act,
                              Globals__dbg_action_out* _out);

typedef struct Globals__d_color_out {
  Debug__world w7;
} Globals__d_color_out;

void Globals__d_color_step(Debug__world w0, Globals__color c,
                           Globals__d_color_out* _out);

typedef struct Globals__dbg_color_out {
} Globals__dbg_color_out;

void Globals__dbg_color_step(string msg, Globals__color c,
                             Globals__dbg_color_out* _out);

typedef struct Globals__dbg_colorq_out {
} Globals__dbg_colorq_out;

void Globals__dbg_colorq_step(string msg, Globals__colorQ c,
                              Globals__dbg_colorq_out* _out);

typedef struct Globals__dbg_sensors_out {
} Globals__dbg_sensors_out;

void Globals__dbg_sensors_step(string msg, Globals__sensors s,
                               Globals__dbg_sensors_out* _out);

#endif // GLOBALS_H
