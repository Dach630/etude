/* --- Generated the 21/12/2023 at 23:30 --- */
/* --- heptagon compiler, version 1.05.00 (compiled tue. oct. 3 15:20:46 CET 2023) --- */
/* --- Command line: /home/chengd/.opam/ocaml-variants/bin/heptc -c -target c vehicle.ept --- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vehicle.h"

void Vehicle__car_geometry_step(Globals__phase phase, float vec[2],
                                Vehicle__car_geometry_out* _out) {
  Utilities__mat_rot_out Utilities__mat_rot_out_st;
  Utilities__vec_add2_out Utilities__vec_add2_out_st;
  Utilities__mat_vec_prod2_out Utilities__mat_vec_prod2_out_st;
  Utilities__pos2vec_out Utilities__pos2vec_out_st;
  Utilities__vec2pos_out Utilities__vec2pos_out_st;
  
  float v_3[2];
  float v_2[2];
  float v_1[2][2];
  float v[2];
  Utilities__mat_rot_step(phase.ph_head, &Utilities__mat_rot_out_st);
  {
    int _2;
    for (_2 = 0; _2 < 2; ++_2) {
      {
        int _3;
        for (_3 = 0; _3 < 2; ++_3) {
          v_1[_2][_3] = Utilities__mat_rot_out_st.res[_2][_3];
        }
      };
    }
  };
  Utilities__mat_vec_prod2_step(v_1, vec, &Utilities__mat_vec_prod2_out_st);
  {
    int _4;
    for (_4 = 0; _4 < 2; ++_4) {
      v_2[_4] = Utilities__mat_vec_prod2_out_st.o[_4];
    }
  };
  Utilities__pos2vec_step(phase.ph_pos, &Utilities__pos2vec_out_st);
  {
    int _5;
    for (_5 = 0; _5 < 2; ++_5) {
      v[_5] = Utilities__pos2vec_out_st.vec[_5];
    }
  };
  Utilities__vec_add2_step(v, v_2, &Utilities__vec_add2_out_st);
  {
    int _6;
    for (_6 = 0; _6 < 2; ++_6) {
      v_3[_6] = Utilities__vec_add2_out_st.o[_6];
    }
  };
  Utilities__vec2pos_step(v_3, &Utilities__vec2pos_out_st);
  _out->newpos = Utilities__vec2pos_out_st.pos;
  _out->newphase = phase;
  _out->newphase.ph_pos = _out->newpos;;
}

void Vehicle__driver_reset(Vehicle__driver_mem* self) {
  Control__controller_reset(&self->controller);
  self->pnr = false;
  self->ck = Vehicle__St_Preparing;
}

void Vehicle__driver_step(int top, Globals__sensors sens,
                          Globals__interrupt itr, Globals__itielts iti,
                          Vehicle__driver_out* _out,
                          Vehicle__driver_mem* self) {
  Control__controller_out Control__controller_out_st;
  
  int v_5;
  Vehicle__st v_4;
  int v;
  int r_1;
  int arriving;
  int nr_St_Stopped;
  Vehicle__st ns_St_Stopped;
  Globals__status sta_St_Stopped;
  Globals__wheels rspeed_St_Stopped;
  int nr_St_Arrived;
  Vehicle__st ns_St_Arrived;
  Globals__status sta_St_Arrived;
  Globals__wheels rspeed_St_Arrived;
  int nr_St_Running;
  Vehicle__st ns_St_Running;
  Globals__status sta_St_Running;
  Globals__wheels rspeed_St_Running;
  int nr_St_Preparing;
  Vehicle__st ns_St_Preparing;
  Globals__status sta_St_Preparing;
  Globals__wheels rspeed_St_Preparing;
  Vehicle__st ns;
  int r;
  int nr;
  r = self->pnr;
  switch (self->ck) {
    case Vehicle__St_Preparing:
      sta_St_Preparing = Globals__Preparing;
      if (top) {
        nr_St_Preparing = true;
        ns_St_Preparing = Vehicle__St_Running;
      } else {
        nr_St_Preparing = false;
        ns_St_Preparing = Vehicle__St_Preparing;
      };
      _out->sta = sta_St_Preparing;
      ns = ns_St_Preparing;
      nr = nr_St_Preparing;
      rspeed_St_Preparing.right = 0.000000;
      rspeed_St_Preparing.left = 0.000000;
      _out->rspeed = rspeed_St_Preparing;
      break;
    case Vehicle__St_Running:
      sta_St_Running = Globals__Running;
      v = (itr==Globals__Halt);
      if (v) {
        v_5 = true;
        v_4 = Vehicle__St_Stopped;
      } else {
        v_5 = false;
        v_4 = Vehicle__St_Running;
      };
      r_1 = r;
      if (r_1) {
        Control__controller_reset(&self->controller);
      };
      Control__controller_step(sens, iti, &Control__controller_out_st,
                               &self->controller);
      rspeed_St_Running = Control__controller_out_st.rspeed;
      arriving = Control__controller_out_st.arriving;
      if (arriving) {
        nr_St_Running = true;
        ns_St_Running = Vehicle__St_Arrived;
      } else {
        nr_St_Running = v_5;
        ns_St_Running = v_4;
      };
      _out->sta = sta_St_Running;
      ns = ns_St_Running;
      nr = nr_St_Running;
      _out->rspeed = rspeed_St_Running;
      break;
    case Vehicle__St_Arrived:
      sta_St_Arrived = Globals__Arrived;
      nr_St_Arrived = false;
      ns_St_Arrived = Vehicle__St_Arrived;
      _out->sta = sta_St_Arrived;
      ns = ns_St_Arrived;
      nr = nr_St_Arrived;
      rspeed_St_Arrived.right = 0.000000;
      rspeed_St_Arrived.left = 0.000000;
      _out->rspeed = rspeed_St_Arrived;
      break;
    case Vehicle__St_Stopped:
      sta_St_Stopped = Globals__Stopped;
      nr_St_Stopped = false;
      ns_St_Stopped = Vehicle__St_Stopped;
      _out->sta = sta_St_Stopped;
      ns = ns_St_Stopped;
      nr = nr_St_Stopped;
      rspeed_St_Stopped.right = 0.000000;
      rspeed_St_Stopped.left = 0.000000;
      _out->rspeed = rspeed_St_Stopped;
      break;
    default:
      break;
  };
  self->pnr = nr;
  self->ck = ns;;
}

void Vehicle__physical_model_reset(Vehicle__physical_model_mem* self) {
  Utilities__integrator_reset(&self->integrator);
  Utilities__integrator_reset(&self->integrator_1);
  Utilities__integrator_reset(&self->integrator_2);
  self->pnr = false;
  self->ck = Vehicle__St_1_Positioning;
}

void Vehicle__physical_model_step(int top, Globals__wheels rspeed,
                                  Globals__phase ini_ph,
                                  Vehicle__physical_model_out* _out,
                                  Vehicle__physical_model_mem* self) {
  Mathext__cos_out Mathext__cos_out_st;
  Vehicle__car_geometry_out Vehicle__car_geometry_out_st;
  Utilities__normalize_out Utilities__normalize_out_st;
  Utilities__integrator_out Utilities__integrator_out_st;
  Mathext__sin_out Mathext__sin_out_st;
  Utilities__bound_out Utilities__bound_out_st;
  
  float v_23[2];
  Globals__phase v_22;
  Globals__position v_21;
  float v_20;
  float v_19;
  float v_18;
  float v_17;
  float v_16;
  float v_15;
  float v_14;
  float v_13;
  float v_12;
  float v_11;
  float v_10;
  float v_9;
  float v_8;
  float v_7;
  float v_6;
  int r_4;
  int r_3;
  int r_2;
  float si;
  float co;
  float alpha;
  float vL;
  float vR;
  float v;
  Globals__position dummy_1;
  float v_24[2];
  Globals__phase dummy;
  Globals__position pos;
  int nr_St_1_On;
  Vehicle__st_1 ns_St_1_On;
  float y0_St_1_On;
  float x0_St_1_On;
  float alpha0_St_1_On;
  Globals__phase ph_St_1_On;
  int nr_St_1_Positioning;
  Vehicle__st_1 ns_St_1_Positioning;
  float y0_St_1_Positioning;
  float x0_St_1_Positioning;
  float alpha0_St_1_Positioning;
  Globals__phase ph_St_1_Positioning;
  Vehicle__st_1 ns;
  int r;
  int nr;
  float alpha0;
  float x0;
  float y0;
  r = self->pnr;
  switch (self->ck) {
    case Vehicle__St_1_Positioning:
      alpha0_St_1_Positioning = ini_ph.ph_head;
      if (top) {
        nr_St_1_Positioning = true;
        ns_St_1_Positioning = Vehicle__St_1_On;
      } else {
        nr_St_1_Positioning = false;
        ns_St_1_Positioning = Vehicle__St_1_Positioning;
      };
      alpha0 = alpha0_St_1_Positioning;
      ns = ns_St_1_Positioning;
      nr = nr_St_1_Positioning;
      v_24[0] = -0.000000;
      v_24[1] = 0.000000;
      Vehicle__car_geometry_step(ini_ph, v_24, &Vehicle__car_geometry_out_st);
      pos = Vehicle__car_geometry_out_st.newpos;
      dummy = Vehicle__car_geometry_out_st.newphase;
      y0_St_1_Positioning = pos.y;
      x0_St_1_Positioning = pos.x;
      x0 = x0_St_1_Positioning;
      y0 = y0_St_1_Positioning;
      ph_St_1_Positioning = ini_ph;
      ph_St_1_Positioning.ph_vel = 0.000000;
      _out->ph = ph_St_1_Positioning;
      break;
    case Vehicle__St_1_On:
      y0_St_1_On = self->y0_1;
      x0_St_1_On = self->x0_1;
      alpha0_St_1_On = self->alpha0_1;
      Utilities__bound_step(rspeed.right, Globals__cMAXWHEEL,
                            &Utilities__bound_out_st);
      v_11 = Utilities__bound_out_st.o;
      Utilities__bound_step(rspeed.left, Globals__cMAXWHEEL,
                            &Utilities__bound_out_st);
      v_10 = Utilities__bound_out_st.o;
      vR = (v_11*0.047997);
      vL = (v_10*0.047997);
      v_13 = (vR-vL);
      v_14 = (v_13*180.000000);
      v_15 = (v_14/18.849556);
      v_12 = (vL+vR);
      v = (v_12/2.000000);
      nr_St_1_On = false;
      ns_St_1_On = Vehicle__St_1_On;
      r_2 = r;
      r_3 = r;
      r_4 = r;
      alpha0 = alpha0_St_1_On;
      if (r_2) {
        Utilities__integrator_reset(&self->integrator);
      };
      Utilities__integrator_step(v_15, Globals__timestep, alpha0,
                                 &Utilities__integrator_out_st,
                                 &self->integrator);
      v_16 = Utilities__integrator_out_st.o;
      Utilities__normalize_step(v_16, &Utilities__normalize_out_st);
      alpha = Utilities__normalize_out_st.normal;
      v_8 = (alpha*Globals__pi);
      v_9 = (v_8/180.000000);
      Mathext__cos_step(v_9, &Mathext__cos_out_st);
      co = Mathext__cos_out_st.o;
      v_17 = (v*co);
      v_6 = (alpha*Globals__pi);
      v_7 = (v_6/180.000000);
      Mathext__sin_step(v_7, &Mathext__sin_out_st);
      si = Mathext__sin_out_st.o;
      v_19 = (v*si);
      ns = ns_St_1_On;
      nr = nr_St_1_On;
      x0 = x0_St_1_On;
      if (r_3) {
        Utilities__integrator_reset(&self->integrator_1);
      };
      Utilities__integrator_step(v_17, Globals__timestep, x0,
                                 &Utilities__integrator_out_st,
                                 &self->integrator_1);
      v_18 = Utilities__integrator_out_st.o;
      y0 = y0_St_1_On;
      if (r_4) {
        Utilities__integrator_reset(&self->integrator_2);
      };
      Utilities__integrator_step(v_19, Globals__timestep, y0,
                                 &Utilities__integrator_out_st,
                                 &self->integrator_2);
      v_20 = Utilities__integrator_out_st.o;
      v_23[0] = 0.000000;
      v_23[1] = 0.000000;
      v_21.x = v_18;
      v_21.y = v_20;
      v_22.ph_pos = v_21;
      v_22.ph_vel = v;
      v_22.ph_head = alpha;
      Vehicle__car_geometry_step(v_22, v_23, &Vehicle__car_geometry_out_st);
      dummy_1 = Vehicle__car_geometry_out_st.newpos;
      ph_St_1_On = Vehicle__car_geometry_out_st.newphase;
      _out->ph = ph_St_1_On;
      break;
    default:
      break;
  };
  self->y0_1 = y0;
  self->x0_1 = x0;
  self->alpha0_1 = alpha0;
  self->pnr = nr;
  self->ck = ns;;
}

void Vehicle__simulate_reset(Vehicle__simulate_mem* self) {
  Vehicle__driver_reset(&self->driver);
  Vehicle__physical_model_reset(&self->physical_model);
}

void Vehicle__simulate_step(Globals__itielts iti, Globals__sensors sens,
                            Globals__interrupt itr, Globals__phase ini_ph,
                            int top, Vehicle__simulate_out* _out,
                            Vehicle__simulate_mem* self) {
  Vehicle__driver_out Vehicle__driver_out_st;
  Vehicle__physical_model_out Vehicle__physical_model_out_st;
  
  Globals__wheels rspeed;
  Vehicle__driver_step(top, sens, itr, iti, &Vehicle__driver_out_st,
                       &self->driver);
  rspeed = Vehicle__driver_out_st.rspeed;
  _out->sta = Vehicle__driver_out_st.sta;
  Vehicle__physical_model_step(top, rspeed, ini_ph,
                               &Vehicle__physical_model_out_st,
                               &self->physical_model);
  _out->ph = Vehicle__physical_model_out_st.ph;;
}

