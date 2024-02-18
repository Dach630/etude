/* --- Generated the 28/11/2023 at 13:4 --- */
/* --- heptagon compiler, version 1.05.00 (compiled tue. oct. 3 15:20:46 CET 2023) --- */
/* --- Command line: /home/chengd/.opam/ocaml-variants/bin/heptc -c -target c utilities.ept --- */

#ifndef UTILITIES_H
#define UTILITIES_H

#include "utilities_types.h"
#include "globals.h"
#include "mathext.h"
typedef struct Utilities__min_float_out {
  float o;
} Utilities__min_float_out;

void Utilities__min_float_step(float a, float b,
                               Utilities__min_float_out* _out);

typedef struct Utilities__min_int_out {
  int o;
} Utilities__min_int_out;

void Utilities__min_int_step(int a, int b, Utilities__min_int_out* _out);

typedef struct Utilities__max_float_out {
  float o;
} Utilities__max_float_out;

void Utilities__max_float_step(float a, float b,
                               Utilities__max_float_out* _out);

typedef struct Utilities__max_int_out {
  int o;
} Utilities__max_int_out;

void Utilities__max_int_step(int a, int b, Utilities__max_int_out* _out);

typedef struct Utilities__countdown_mem {
  int v_1;
  int v;
} Utilities__countdown_mem;

typedef struct Utilities__countdown_out {
  int o;
} Utilities__countdown_out;

void Utilities__countdown_reset(Utilities__countdown_mem* self);

void Utilities__countdown_step(int e, int ini,
                               Utilities__countdown_out* _out,
                               Utilities__countdown_mem* self);

typedef struct Utilities__angle_dist_out {
  float angle;
  float dist;
} Utilities__angle_dist_out;

void Utilities__angle_dist_step(Globals__position from, Globals__position to,
                                Utilities__angle_dist_out* _out);

typedef struct Utilities__bound_out {
  float o;
} Utilities__bound_out;

void Utilities__bound_step(float x, float ceiling, Utilities__bound_out* _out);

typedef struct Utilities__norm_color_out {
  float norm;
} Utilities__norm_color_out;

void Utilities__norm_color_step(Globals__color a,
                                Utilities__norm_color_out* _out);

typedef struct Utilities__compare_colors_out {
  float correlation;
} Utilities__compare_colors_out;

void Utilities__compare_colors_step(Globals__color a, Globals__color b,
                                    Utilities__compare_colors_out* _out);

typedef struct Utilities__decode_color_out {
  Globals__colorQ q;
} Utilities__decode_color_out;

void Utilities__decode_color_step(Globals__color a,
                                  Utilities__decode_color_out* _out);

typedef struct Utilities__encode_color_out {
  Globals__color a;
} Utilities__encode_color_out;

void Utilities__encode_color_step(Globals__colorQ q,
                                  Utilities__encode_color_out* _out);

typedef struct Utilities__rising_edge_mem {
  int v_39;
} Utilities__rising_edge_mem;

typedef struct Utilities__rising_edge_out {
  int e;
} Utilities__rising_edge_out;

void Utilities__rising_edge_reset(Utilities__rising_edge_mem* self);

void Utilities__rising_edge_step(int b, Utilities__rising_edge_out* _out,
                                 Utilities__rising_edge_mem* self);

typedef struct Utilities__falling_edge_mem {
  int v;
  Utilities__rising_edge_mem rising_edge;
} Utilities__falling_edge_mem;

typedef struct Utilities__falling_edge_out {
  int e;
} Utilities__falling_edge_out;

void Utilities__falling_edge_reset(Utilities__falling_edge_mem* self);

void Utilities__falling_edge_step(int b, Utilities__falling_edge_out* _out,
                                  Utilities__falling_edge_mem* self);

typedef struct Utilities__after_mem {
  int v_44;
  int v;
} Utilities__after_mem;

typedef struct Utilities__after_out {
  int o;
} Utilities__after_out;

void Utilities__after_reset(Utilities__after_mem* self);

void Utilities__after_step(int ini, Utilities__after_out* _out,
                           Utilities__after_mem* self);

typedef struct Utilities__event_edge_mem {
  Utilities__rising_edge_mem rising_edge;
  Utilities__rising_edge_mem rising_edge_1;
  Utilities__rising_edge_mem rising_edge_2;
  Utilities__rising_edge_mem rising_edge_3;
  Utilities__rising_edge_mem rising_edge_4;
} Utilities__event_edge_mem;

typedef struct Utilities__event_edge_out {
  Globals__event o;
} Utilities__event_edge_out;

void Utilities__event_edge_reset(Utilities__event_edge_mem* self);

void Utilities__event_edge_step(Globals__event e,
                                Utilities__event_edge_out* _out,
                                Utilities__event_edge_mem* self);

typedef struct Utilities__integrator_mem {
  float v_52;
  int v;
} Utilities__integrator_mem;

typedef struct Utilities__integrator_out {
  float o;
} Utilities__integrator_out;

void Utilities__integrator_reset(Utilities__integrator_mem* self);

void Utilities__integrator_step(float x, float step, float ini,
                                Utilities__integrator_out* _out,
                                Utilities__integrator_mem* self);

typedef struct Utilities__integrator_en_mem {
  float v_57;
  int v;
  Utilities__integrator_mem integrator;
} Utilities__integrator_en_mem;

typedef struct Utilities__integrator_en_out {
  float o;
} Utilities__integrator_en_out;

void Utilities__integrator_en_reset(Utilities__integrator_en_mem* self);

void Utilities__integrator_en_step(float x, float step, float ini, int en,
                                   Utilities__integrator_en_out* _out,
                                   Utilities__integrator_en_mem* self);

typedef struct Utilities__derivative_mem {
  float v;
} Utilities__derivative_mem;

typedef struct Utilities__derivative_out {
  float y;
} Utilities__derivative_out;

void Utilities__derivative_reset(Utilities__derivative_mem* self);

void Utilities__derivative_step(float x, float step,
                                Utilities__derivative_out* _out,
                                Utilities__derivative_mem* self);

typedef struct Utilities__lowpass_mem {
  float v_61;
} Utilities__lowpass_mem;

typedef struct Utilities__lowpass_out {
  float y;
} Utilities__lowpass_out;

void Utilities__lowpass_reset(Utilities__lowpass_mem* self);

void Utilities__lowpass_step(float x, float a, Utilities__lowpass_out* _out,
                             Utilities__lowpass_mem* self);

typedef struct Utilities__normalize_out {
  float normal;
} Utilities__normalize_out;

void Utilities__normalize_step(float angle, Utilities__normalize_out* _out);

typedef struct Utilities__pos2vec_out {
  float vec[2];
} Utilities__pos2vec_out;

void Utilities__pos2vec_step(Globals__position pos,
                             Utilities__pos2vec_out* _out);

typedef struct Utilities__vec2pos_out {
  Globals__position pos;
} Utilities__vec2pos_out;

void Utilities__vec2pos_step(float vec[2], Utilities__vec2pos_out* _out);

typedef struct Utilities__mat_rot_out {
  float res[2][2];
} Utilities__mat_rot_out;

void Utilities__mat_rot_step(float alpha, Utilities__mat_rot_out* _out);

typedef struct Utilities__vec_add_params_2__out {
  float o[2];
} Utilities__vec_add_params_2__out;

void Utilities__vec_add_params_2__step(float v1[2], float v2[2],
                                       Utilities__vec_add_params_2__out* _out);

typedef struct Utilities__vec_prod_params_2__out {
  float o[2];
} Utilities__vec_prod_params_2__out;

void Utilities__vec_prod_params_2__step(float v1[2], float v2[2],
                                        Utilities__vec_prod_params_2__out* _out);

typedef struct Utilities__dotp_params_2__out {
  float o;
} Utilities__dotp_params_2__out;

void Utilities__dotp_params_2__step(float v1[2], float v2[2],
                                    Utilities__dotp_params_2__out* _out);

typedef struct Utilities__mat_vec_prod_params_2__out {
  float o[2];
} Utilities__mat_vec_prod_params_2__out;

void Utilities__mat_vec_prod_params_2__step(float mat[2][2], float vec[2],
                                            Utilities__mat_vec_prod_params_2__out* _out);

typedef struct Utilities__vec_add2_out {
  float o[2];
} Utilities__vec_add2_out;

void Utilities__vec_add2_step(float v1[2], float v2[2],
                              Utilities__vec_add2_out* _out);

typedef struct Utilities__mat_vec_prod2_out {
  float o[2];
} Utilities__mat_vec_prod2_out;

void Utilities__mat_vec_prod2_step(float mat[2][2], float vec[2],
                                   Utilities__mat_vec_prod2_out* _out);

typedef struct Utilities__abs_out {
  float o;
} Utilities__abs_out;

void Utilities__abs_step(float x, Utilities__abs_out* _out);

typedef struct Utilities__uptime_mem {
  Utilities__integrator_mem integrator;
} Utilities__uptime_mem;

typedef struct Utilities__uptime_out {
  float t;
} Utilities__uptime_out;

void Utilities__uptime_reset(Utilities__uptime_mem* self);

void Utilities__uptime_step(float x, float step, Utilities__uptime_out* _out,
                            Utilities__uptime_mem* self);

typedef struct Utilities__variation_mem {
  float v;
  Utilities__integrator_en_mem integrator_en;
} Utilities__variation_mem;

typedef struct Utilities__variation_out {
  float o;
} Utilities__variation_out;

void Utilities__variation_reset(Utilities__variation_mem* self);

void Utilities__variation_step(int enabled, float x, float step,
                               Utilities__variation_out* _out,
                               Utilities__variation_mem* self);

#endif // UTILITIES_H
