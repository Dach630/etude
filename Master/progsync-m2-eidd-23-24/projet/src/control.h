/* --- Generated the 21/12/2023 at 23:30 --- */
/* --- heptagon compiler, version 1.05.00 (compiled tue. oct. 3 15:20:46 CET 2023) --- */
/* --- Command line: /home/chengd/.opam/ocaml-variants/bin/heptc -c -target c control.ept --- */

#ifndef CONTROL_H
#define CONTROL_H

#include "control_types.h"
#include "globals.h"
#include "mathext.h"
#include "utilities.h"
typedef struct Control__vitesse_limit_out {
  float vit;
} Control__vitesse_limit_out;

void Control__vitesse_limit_step(float limit,
                                 Control__vitesse_limit_out* _out);

typedef struct Control__pid_mem {
  Utilities__integrator_mem integrator;
  Utilities__derivative_mem derivative;
} Control__pid_mem;

typedef struct Control__pid_out {
  float corr;
} Control__pid_out;

void Control__pid_reset(Control__pid_mem* self);

void Control__pid_step(float err, Control__pid_out* _out,
                       Control__pid_mem* self);

typedef struct Control__correction_left_mem {
  Control__pid_mem pid;
} Control__correction_left_mem;

typedef struct Control__correction_left_out {
  float left;
} Control__correction_left_out;

void Control__correction_left_reset(Control__correction_left_mem* self);

void Control__correction_left_step(Globals__sensors sens, float limit,
                                   Control__correction_left_out* _out,
                                   Control__correction_left_mem* self);

typedef struct Control__correction_right_mem {
  Control__pid_mem pid;
} Control__correction_right_mem;

typedef struct Control__correction_right_out {
  float right;
} Control__correction_right_out;

void Control__correction_right_reset(Control__correction_right_mem* self);

void Control__correction_right_step(Globals__sensors sens, float limit,
                                    Control__correction_right_out* _out,
                                    Control__correction_right_mem* self);

typedef struct Control__is_colors_equals_out {
  int o;
} Control__is_colors_equals_out;

void Control__is_colors_equals_step(Globals__color c1, Globals__color c2,
                                    Control__is_colors_equals_out* _out);

typedef struct Control__nouvelle_etape_mem {
  Globals__color tmp;
} Control__nouvelle_etape_mem;

typedef struct Control__nouvelle_etape_out {
  int nouv;
} Control__nouvelle_etape_out;

void Control__nouvelle_etape_reset(Control__nouvelle_etape_mem* self);

void Control__nouvelle_etape_step(Globals__sensors sens, int tourne,
                                  Control__nouvelle_etape_out* _out,
                                  Control__nouvelle_etape_mem* self);

typedef struct Control__int_of_bool_out {
  int i;
} Control__int_of_bool_out;

void Control__int_of_bool_step(int b, Control__int_of_bool_out* _out);

typedef struct Control__feu_tricolore_out {
  int arret;
} Control__feu_tricolore_out;

void Control__feu_tricolore_step(Globals__sensors sens,
                                 Control__feu_tricolore_out* _out);

typedef struct Control__correction_vitesse_virage_out {
  float n_left;
  float n_right;
} Control__correction_vitesse_virage_out;

void Control__correction_vitesse_virage_step(float left, float right,
                                             Control__correction_vitesse_virage_out* _out);

typedef struct Control__rotation_out {
  float temps_rotation;
  Globals__wheels roue;
} Control__rotation_out;

void Control__rotation_step(float degre, float limit,
                            Control__rotation_out* _out);

typedef struct Control__controller_mem {
  Control__st ck;
  float v_58;
  float temps_rotation_2;
  float v_49;
  int v_46;
  int pnr;
  int a_tourner_1;
  float v_right_1;
  float v_left_1;
  Globals__wheels rspeed_1;
  int compteur_etape;
  Control__correction_right_mem correction_right;
  Control__correction_left_mem correction_left;
  Control__nouvelle_etape_mem nouvelle_etape;
} Control__controller_mem;

typedef struct Control__controller_out {
  Globals__wheels rspeed;
  int arriving;
} Control__controller_out;

void Control__controller_reset(Control__controller_mem* self);

void Control__controller_step(Globals__sensors sens, Globals__itielts iti,
                              Control__controller_out* _out,
                              Control__controller_mem* self);

#endif // CONTROL_H
