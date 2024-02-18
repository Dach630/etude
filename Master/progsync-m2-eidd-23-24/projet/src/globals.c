/* --- Generated the 28/11/2023 at 13:4 --- */
/* --- heptagon compiler, version 1.05.00 (compiled tue. oct. 3 15:20:46 CET 2023) --- */
/* --- Command line: /home/chengd/.opam/ocaml-variants/bin/heptc -c -target c globals.ept --- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "globals.h"

void Globals__dbg_position_step(string msg, Globals__position p,
                                Globals__dbg_position_out* _out) {
  Debug__d_init_out Debug__d_init_out_st;
  Debug__d_float_out Debug__d_float_out_st;
  Debug__d_string_out Debug__d_string_out_st;
  
  Debug__world v;
  Debug__world w0;
  Debug__world w1;
  Debug__world w2;
  Debug__world w3;
  Debug__world w4;
  Debug__world w5;
  Debug__d_init_step(&Debug__d_init_out_st);
  v = Debug__d_init_out_st.n;
  Debug__d_string_step(v, msg, &Debug__d_string_out_st);
  w0 = Debug__d_string_out_st.n;
  Debug__d_string_step(w0, "{ x = ", &Debug__d_string_out_st);
  w1 = Debug__d_string_out_st.n;
  Debug__d_float_step(w1, p.x, &Debug__d_float_out_st);
  w2 = Debug__d_float_out_st.n;
  Debug__d_string_step(w2, "; y = ", &Debug__d_string_out_st);
  w3 = Debug__d_string_out_st.n;
  Debug__d_float_step(w3, p.y, &Debug__d_float_out_st);
  w4 = Debug__d_float_out_st.n;
  Debug__d_string_step(w4, " }\n", &Debug__d_string_out_st);
  w5 = Debug__d_string_out_st.n;;
}

void Globals__dbg_phase_step(string msg, Globals__phase ph,
                             Globals__dbg_phase_out* _out) {
  Debug__d_init_out Debug__d_init_out_st;
  Debug__d_float_out Debug__d_float_out_st;
  Debug__d_string_out Debug__d_string_out_st;
  
  Debug__world v;
  Debug__world w0;
  Debug__world w1;
  Debug__world w2;
  Debug__world w3;
  Debug__world w4;
  Debug__world w5;
  Debug__world w6;
  Debug__world w7;
  Debug__world w8;
  Debug__world w9;
  Debug__d_init_step(&Debug__d_init_out_st);
  v = Debug__d_init_out_st.n;
  Debug__d_string_step(v, msg, &Debug__d_string_out_st);
  w0 = Debug__d_string_out_st.n;
  Debug__d_string_step(w0, "{ x = ", &Debug__d_string_out_st);
  w1 = Debug__d_string_out_st.n;
  Debug__d_float_step(w1, ph.ph_pos.x, &Debug__d_float_out_st);
  w2 = Debug__d_float_out_st.n;
  Debug__d_string_step(w2, "; y = ", &Debug__d_string_out_st);
  w3 = Debug__d_string_out_st.n;
  Debug__d_float_step(w3, ph.ph_pos.y, &Debug__d_float_out_st);
  w4 = Debug__d_float_out_st.n;
  Debug__d_string_step(w4, "; head = ", &Debug__d_string_out_st);
  w5 = Debug__d_string_out_st.n;
  Debug__d_float_step(w5, ph.ph_head, &Debug__d_float_out_st);
  w6 = Debug__d_float_out_st.n;
  Debug__d_string_step(w6, "; vel = ", &Debug__d_string_out_st);
  w7 = Debug__d_string_out_st.n;
  Debug__d_float_step(w7, ph.ph_vel, &Debug__d_float_out_st);
  w8 = Debug__d_float_out_st.n;
  Debug__d_string_step(w8, " }\n", &Debug__d_string_out_st);
  w9 = Debug__d_string_out_st.n;;
}

void Globals__dbg_interrupt_step(string msg, Globals__interrupt itr,
                                 Globals__dbg_interrupt_out* _out) {
  Debug__d_init_out Debug__d_init_out_st;
  Debug__d_string_out Debug__d_string_out_st;
  
  Debug__world w1_Ok;
  Debug__world w1_Halt;
  Debug__world w1_Wait;
  Globals__interrupt ck;
  Debug__world v;
  Debug__world w0;
  Debug__world w1;
  Debug__world w2;
  ck = itr;
  Debug__d_init_step(&Debug__d_init_out_st);
  v = Debug__d_init_out_st.n;
  Debug__d_string_step(v, msg, &Debug__d_string_out_st);
  w0 = Debug__d_string_out_st.n;
  switch (ck) {
    case Globals__Wait:
      Debug__d_string_step(w0, "Wait", &Debug__d_string_out_st);
      w1_Wait = Debug__d_string_out_st.n;
      w1 = w1_Wait;
      break;
    case Globals__Halt:
      Debug__d_string_step(w0, "Halt", &Debug__d_string_out_st);
      w1_Halt = Debug__d_string_out_st.n;
      w1 = w1_Halt;
      break;
    case Globals__Ok:
      Debug__d_string_step(w0, "Ok", &Debug__d_string_out_st);
      w1_Ok = Debug__d_string_out_st.n;
      w1 = w1_Ok;
      break;
    default:
      break;
  };
  Debug__d_string_step(w1, "\n", &Debug__d_string_out_st);
  w2 = Debug__d_string_out_st.n;;
}

void Globals__dbg_status_step(string msg, Globals__status sta,
                              Globals__dbg_status_out* _out) {
  Debug__d_init_out Debug__d_init_out_st;
  Debug__d_string_out Debug__d_string_out_st;
  
  Debug__world w1_Stopped;
  Debug__world w1_Arrived;
  Debug__world w1_Running;
  Debug__world w1_Preparing;
  Globals__status ck;
  Debug__world v;
  Debug__world w0;
  Debug__world w1;
  Debug__world w2;
  ck = sta;
  Debug__d_init_step(&Debug__d_init_out_st);
  v = Debug__d_init_out_st.n;
  Debug__d_string_step(v, msg, &Debug__d_string_out_st);
  w0 = Debug__d_string_out_st.n;
  switch (ck) {
    case Globals__Preparing:
      Debug__d_string_step(w0, "Preparing", &Debug__d_string_out_st);
      w1_Preparing = Debug__d_string_out_st.n;
      w1 = w1_Preparing;
      break;
    case Globals__Running:
      Debug__d_string_step(w0, "Running", &Debug__d_string_out_st);
      w1_Running = Debug__d_string_out_st.n;
      w1 = w1_Running;
      break;
    case Globals__Arrived:
      Debug__d_string_step(w0, "Arrived", &Debug__d_string_out_st);
      w1_Arrived = Debug__d_string_out_st.n;
      w1 = w1_Arrived;
      break;
    case Globals__Stopped:
      Debug__d_string_step(w0, "Stopped", &Debug__d_string_out_st);
      w1_Stopped = Debug__d_string_out_st.n;
      w1 = w1_Stopped;
      break;
    default:
      break;
  };
  Debug__d_string_step(w1, "\n", &Debug__d_string_out_st);
  w2 = Debug__d_string_out_st.n;;
}

void Globals__dbg_wheels_step(string msg, Globals__wheels wh,
                              Globals__dbg_wheels_out* _out) {
  Debug__d_init_out Debug__d_init_out_st;
  Debug__d_float_out Debug__d_float_out_st;
  Debug__d_string_out Debug__d_string_out_st;
  
  Debug__world v;
  Debug__world w0;
  Debug__world w1;
  Debug__world w2;
  Debug__world w3;
  Debug__world w4;
  Debug__world w5;
  Debug__d_init_step(&Debug__d_init_out_st);
  v = Debug__d_init_out_st.n;
  Debug__d_string_step(v, msg, &Debug__d_string_out_st);
  w0 = Debug__d_string_out_st.n;
  Debug__d_string_step(w0, "{ left = ", &Debug__d_string_out_st);
  w1 = Debug__d_string_out_st.n;
  Debug__d_float_step(w1, wh.left, &Debug__d_float_out_st);
  w2 = Debug__d_float_out_st.n;
  Debug__d_string_step(w2, "; right = ", &Debug__d_string_out_st);
  w3 = Debug__d_string_out_st.n;
  Debug__d_float_step(w3, wh.right, &Debug__d_float_out_st);
  w4 = Debug__d_float_out_st.n;
  Debug__d_string_step(w4, " }\n", &Debug__d_string_out_st);
  w5 = Debug__d_string_out_st.n;;
}

void Globals__dbg_action_step(string msg, Globals__action act,
                              Globals__dbg_action_out* _out) {
  Debug__d_init_out Debug__d_init_out_st;
  Debug__d_string_out Debug__d_string_out_st;
  
  Debug__world w1_Stop;
  Debug__world w1_Turn;
  Debug__world w1_Go;
  Globals__action ck;
  Debug__world v;
  Debug__world w0;
  Debug__world w1;
  Debug__world w2;
  ck = act;
  Debug__d_init_step(&Debug__d_init_out_st);
  v = Debug__d_init_out_st.n;
  Debug__d_string_step(v, msg, &Debug__d_string_out_st);
  w0 = Debug__d_string_out_st.n;
  switch (ck) {
    case Globals__Go:
      Debug__d_string_step(w0, "Go", &Debug__d_string_out_st);
      w1_Go = Debug__d_string_out_st.n;
      w1 = w1_Go;
      break;
    case Globals__Turn:
      Debug__d_string_step(w0, "Turn", &Debug__d_string_out_st);
      w1_Turn = Debug__d_string_out_st.n;
      w1 = w1_Turn;
      break;
    case Globals__Stop:
      Debug__d_string_step(w0, "Stop", &Debug__d_string_out_st);
      w1_Stop = Debug__d_string_out_st.n;
      w1 = w1_Stop;
      break;
    default:
      break;
  };
  Debug__d_string_step(w1, "\n", &Debug__d_string_out_st);
  w2 = Debug__d_string_out_st.n;;
}

void Globals__d_color_step(Debug__world w0, Globals__color c,
                           Globals__d_color_out* _out) {
  Debug__d_int_out Debug__d_int_out_st;
  Debug__d_string_out Debug__d_string_out_st;
  
  Debug__world w1;
  Debug__world w2;
  Debug__world w3;
  Debug__world w4;
  Debug__world w5;
  Debug__world w6;
  Debug__d_string_step(w0, "{ red = ", &Debug__d_string_out_st);
  w1 = Debug__d_string_out_st.n;
  Debug__d_int_step(w1, c.red, &Debug__d_int_out_st);
  w2 = Debug__d_int_out_st.n;
  Debug__d_string_step(w2, "; green = ", &Debug__d_string_out_st);
  w3 = Debug__d_string_out_st.n;
  Debug__d_int_step(w3, c.green, &Debug__d_int_out_st);
  w4 = Debug__d_int_out_st.n;
  Debug__d_string_step(w4, "; blue = ", &Debug__d_string_out_st);
  w5 = Debug__d_string_out_st.n;
  Debug__d_int_step(w5, c.blue, &Debug__d_int_out_st);
  w6 = Debug__d_int_out_st.n;
  Debug__d_string_step(w6, " }", &Debug__d_string_out_st);
  _out->w7 = Debug__d_string_out_st.n;;
}

void Globals__dbg_color_step(string msg, Globals__color c,
                             Globals__dbg_color_out* _out) {
  Debug__d_init_out Debug__d_init_out_st;
  Globals__d_color_out Globals__d_color_out_st;
  Debug__d_string_out Debug__d_string_out_st;
  
  Debug__world v;
  Debug__world w0;
  Debug__world w1;
  Debug__world w2;
  Debug__d_init_step(&Debug__d_init_out_st);
  v = Debug__d_init_out_st.n;
  Debug__d_string_step(v, msg, &Debug__d_string_out_st);
  w0 = Debug__d_string_out_st.n;
  Globals__d_color_step(w0, c, &Globals__d_color_out_st);
  w1 = Globals__d_color_out_st.w7;
  Debug__d_string_step(w1, "\n", &Debug__d_string_out_st);
  w2 = Debug__d_string_out_st.n;;
}

void Globals__dbg_colorq_step(string msg, Globals__colorQ c,
                              Globals__dbg_colorq_out* _out) {
  Debug__d_init_out Debug__d_init_out_st;
  Debug__d_string_out Debug__d_string_out_st;
  
  Debug__world w1_Other;
  Debug__world w1_Amber;
  Debug__world w1_Green;
  Debug__world w1_Red;
  Globals__colorQ ck;
  Debug__world v;
  Debug__world w0;
  Debug__world w1;
  Debug__world w2;
  ck = c;
  Debug__d_init_step(&Debug__d_init_out_st);
  v = Debug__d_init_out_st.n;
  Debug__d_string_step(v, msg, &Debug__d_string_out_st);
  w0 = Debug__d_string_out_st.n;
  switch (ck) {
    case Globals__Red:
      Debug__d_string_step(w0, "Red", &Debug__d_string_out_st);
      w1_Red = Debug__d_string_out_st.n;
      w1 = w1_Red;
      break;
    case Globals__Green:
      Debug__d_string_step(w0, "Green", &Debug__d_string_out_st);
      w1_Green = Debug__d_string_out_st.n;
      w1 = w1_Green;
      break;
    case Globals__Amber:
      Debug__d_string_step(w0, "Amber", &Debug__d_string_out_st);
      w1_Amber = Debug__d_string_out_st.n;
      w1 = w1_Amber;
      break;
    case Globals__Other:
      Debug__d_string_step(w0, "Other", &Debug__d_string_out_st);
      w1_Other = Debug__d_string_out_st.n;
      w1 = w1_Other;
      break;
    default:
      break;
  };
  Debug__d_string_step(w1, "\n", &Debug__d_string_out_st);
  w2 = Debug__d_string_out_st.n;;
}

void Globals__dbg_sensors_step(string msg, Globals__sensors s,
                               Globals__dbg_sensors_out* _out) {
  Debug__d_init_out Debug__d_init_out_st;
  Globals__d_color_out Globals__d_color_out_st;
  Debug__d_int_out Debug__d_int_out_st;
  Debug__d_string_out Debug__d_string_out_st;
  
  Debug__world v;
  Debug__world w0;
  Debug__world w1;
  Debug__world w2;
  Debug__world w3;
  Debug__world w4;
  Debug__world w5;
  Debug__world w6;
  Debug__world w7;
  Debug__d_init_step(&Debug__d_init_out_st);
  v = Debug__d_init_out_st.n;
  Debug__d_string_step(v, msg, &Debug__d_string_out_st);
  w0 = Debug__d_string_out_st.n;
  Debug__d_string_step(w0, "{ s_road = ", &Debug__d_string_out_st);
  w1 = Debug__d_string_out_st.n;
  Globals__d_color_step(w1, s.s_road, &Globals__d_color_out_st);
  w2 = Globals__d_color_out_st.w7;
  Debug__d_string_step(w2, "; s_front = ", &Debug__d_string_out_st);
  w3 = Debug__d_string_out_st.n;
  Globals__d_color_step(w3, s.s_front, &Globals__d_color_out_st);
  w4 = Globals__d_color_out_st.w7;
  Debug__d_string_step(w4, "; s_sonar = ", &Debug__d_string_out_st);
  w5 = Debug__d_string_out_st.n;
  Debug__d_int_step(w5, s.s_sonar, &Debug__d_int_out_st);
  w6 = Debug__d_int_out_st.n;
  Debug__d_string_step(w6, " }\n", &Debug__d_string_out_st);
  w7 = Debug__d_string_out_st.n;;
}

