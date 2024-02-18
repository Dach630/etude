/* --- Generated the 21/12/2023 at 23:30 --- */
/* --- heptagon compiler, version 1.05.00 (compiled tue. oct. 3 15:20:46 CET 2023) --- */
/* --- Command line: /home/chengd/.opam/ocaml-variants/bin/heptc -c -target c vehicle.ept --- */

#ifndef VEHICLE_H
#define VEHICLE_H

#include "vehicle_types.h"
#include "control.h"
#include "globals.h"
#include "mathext.h"
#include "utilities.h"
typedef struct Vehicle__car_geometry_out {
  Globals__position newpos;
  Globals__phase newphase;
} Vehicle__car_geometry_out;

void Vehicle__car_geometry_step(Globals__phase phase, float vec[2],
                                Vehicle__car_geometry_out* _out);

typedef struct Vehicle__driver_mem {
  Vehicle__st ck;
  int pnr;
  Control__controller_mem controller;
} Vehicle__driver_mem;

typedef struct Vehicle__driver_out {
  Globals__wheels rspeed;
  Globals__status sta;
} Vehicle__driver_out;

void Vehicle__driver_reset(Vehicle__driver_mem* self);

void Vehicle__driver_step(int top, Globals__sensors sens,
                          Globals__interrupt itr, Globals__itielts iti,
                          Vehicle__driver_out* _out,
                          Vehicle__driver_mem* self);

typedef struct Vehicle__physical_model_mem {
  Vehicle__st_1 ck;
  int pnr;
  float y0_1;
  float x0_1;
  float alpha0_1;
  Utilities__integrator_mem integrator_2;
  Utilities__integrator_mem integrator_1;
  Utilities__integrator_mem integrator;
} Vehicle__physical_model_mem;

typedef struct Vehicle__physical_model_out {
  Globals__phase ph;
} Vehicle__physical_model_out;

void Vehicle__physical_model_reset(Vehicle__physical_model_mem* self);

void Vehicle__physical_model_step(int top, Globals__wheels rspeed,
                                  Globals__phase ini_ph,
                                  Vehicle__physical_model_out* _out,
                                  Vehicle__physical_model_mem* self);

typedef struct Vehicle__simulate_mem {
  Vehicle__physical_model_mem physical_model;
  Vehicle__driver_mem driver;
} Vehicle__simulate_mem;

typedef struct Vehicle__simulate_out {
  Globals__phase ph;
  Globals__status sta;
} Vehicle__simulate_out;

void Vehicle__simulate_reset(Vehicle__simulate_mem* self);

void Vehicle__simulate_step(Globals__itielts iti, Globals__sensors sens,
                            Globals__interrupt itr, Globals__phase ini_ph,
                            int top, Vehicle__simulate_out* _out,
                            Vehicle__simulate_mem* self);

#endif // VEHICLE_H
