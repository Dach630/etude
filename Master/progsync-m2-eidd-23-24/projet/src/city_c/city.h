/* --- Generated the 21/12/2023 at 23:30 --- */
/* --- heptagon compiler, version 1.05.00 (compiled tue. oct. 3 15:20:46 CET 2023) --- */
/* --- Command line: /home/chengd/.opam/ocaml-variants/bin/heptc -c -target c city.ept --- */

#ifndef CITY_H
#define CITY_H

#include "city_types.h"
#include "globals.h"
#include "map.h"
#include "mathext.h"
#include "utilities.h"
#include "vehicle.h"
typedef struct City__wallclock_mem {
  int v_2;
} City__wallclock_mem;

typedef struct City__wallclock_out {
  float time;
} City__wallclock_out;

void City__wallclock_reset(City__wallclock_mem* self);

void City__wallclock_step(Globals__status rstatus, City__wallclock_out* _out,
                          City__wallclock_mem* self);

typedef struct City__lookup_phase_out {
  Globals__map_data data;
} City__lookup_phase_out;

void City__lookup_phase_step(Globals__phase ph, City__lookup_phase_out* _out);

typedef struct City__light_out {
  int light_run;
} City__light_out;

void City__light_step(Globals__traflights lights, Globals__phase ph,
                      City__light_out* _out);

typedef struct City__speed_out {
  int speed_excess;
} City__speed_out;

void City__speed_step(Globals__phase ph, City__speed_out* _out);

typedef struct City__exited_aux_out {
  int accnew;
} City__exited_aux_out;

void City__exited_aux_step(Globals__position pos, int acc,
                           City__exited_aux_out* _out);

typedef struct City__exited_out {
  int exit_road;
} City__exited_out;

void City__exited_step(Globals__phase ph, City__exited_out* _out);

typedef struct City__collision_aux_out {
  int accnew;
} City__collision_aux_out;

void City__collision_aux_step(Globals__phase ph, Globals__obstacle obst,
                              int acc, City__collision_aux_out* _out);

typedef struct City__collision_out {
  int collision_event;
} City__collision_out;

void City__collision_step(Globals__phase ph, Globals__obstacles obstacles,
                          City__collision_out* _out);

typedef struct City__wrong_dir_out {
  int wrong;
} City__wrong_dir_out;

void City__wrong_dir_step(Globals__phase ph, City__wrong_dir_out* _out);

typedef struct City__aggregate_events_out {
  Globals__event o;
  Globals__interrupt itr;
} City__aggregate_events_out;

void City__aggregate_events_step(int lightRun, int speedExcess, int exitRoad,
                                 int collisionEvent, int wrong,
                                 City__aggregate_events_out* _out);

typedef struct City__event_detection_out {
  Globals__interrupt itr;
  Globals__event evts;
} City__event_detection_out;

void City__event_detection_step(Globals__sign sign, Globals__phase ph,
                                City__event_detection_out* _out);

typedef struct City__ground_color_detection_out {
  Globals__color road_color;
} City__ground_color_detection_out;

void City__ground_color_detection_step(Globals__phase ph,
                                       City__ground_color_detection_out* _out);

typedef struct City__traffic_light_detection_out {
  Globals__color tlight_color;
} City__traffic_light_detection_out;

void City__traffic_light_detection_step(Globals__phase ph,
                                        Globals__traflights traflights,
                                        City__traffic_light_detection_out* _out);

typedef struct City__obstacles_detection_aux_out {
  int accnew;
} City__obstacles_detection_aux_out;

void City__obstacles_detection_aux_step(Globals__phase ph,
                                        Globals__obstacle obst, int acc,
                                        City__obstacles_detection_aux_out* _out);

typedef struct City__obstacle_detection_out {
  int sonar;
} City__obstacle_detection_out;

void City__obstacle_detection_step(Globals__phase ph,
                                   Globals__obstacles obstacles,
                                   City__obstacle_detection_out* _out);

typedef struct City__robot_sensors_out {
  Globals__sensors sens;
} City__robot_sensors_out;

void City__robot_sensors_step(Globals__phase ph, Globals__sign sign,
                              City__robot_sensors_out* _out);

typedef struct City__traffic_lights_aux_out {
  Globals__traflight tl;
} City__traffic_lights_aux_out;

void City__traffic_lights_aux_step(Globals__param_tlight p, float time,
                                   City__traffic_lights_aux_out* _out);

typedef struct City__traffic_lights_out {
  Globals__traflights all_lights;
} City__traffic_lights_out;

void City__traffic_lights_step(float time, City__traffic_lights_out* _out);

typedef struct City__all_obstacles_aux_out {
  Globals__obstacle o;
} City__all_obstacles_aux_out;

void City__all_obstacles_aux_step(Globals__param_obst po, float time,
                                  City__all_obstacles_aux_out* _out);

typedef struct City__all_obstacles_out {
  Globals__obstacles obstacles;
} City__all_obstacles_out;

void City__all_obstacles_step(float time, City__all_obstacles_out* _out);

typedef struct City__simulate_out {
  Globals__sign sign;
  Globals__interrupt itr;
  Globals__sensors sens;
  Globals__event evt;
} City__simulate_out;

void City__simulate_step(Globals__phase ph, float time,
                         City__simulate_out* _out);

typedef struct City__scoringA_mem {
  int v;
  Utilities__rising_edge_mem rising_edge;
  Utilities__rising_edge_mem rising_edge_1;
  Utilities__rising_edge_mem rising_edge_2;
  Utilities__rising_edge_mem rising_edge_3;
  Utilities__rising_edge_mem rising_edge_4;
  Utilities__countdown_mem countdown;
} City__scoringA_mem;

typedef struct City__scoringA_out {
  int score;
} City__scoringA_out;

void City__scoringA_reset(City__scoringA_mem* self);

void City__scoringA_step(Globals__event e, Globals__status rstatus,
                         City__scoringA_out* _out, City__scoringA_mem* self);

typedef struct City__scoringB_mem {
  Utilities__variation_mem variation;
  Utilities__uptime_mem uptime;
} City__scoringB_mem;

typedef struct City__scoringB_out {
  int score;
} City__scoringB_out;

void City__scoringB_reset(City__scoringB_mem* self);

void City__scoringB_step(Globals__phase ph, City__scoringB_out* _out,
                         City__scoringB_mem* self);

#endif // CITY_H
