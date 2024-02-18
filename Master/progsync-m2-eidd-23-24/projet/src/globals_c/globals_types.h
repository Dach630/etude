/* --- Generated the 28/11/2023 at 13:4 --- */
/* --- heptagon compiler, version 1.05.00 (compiled tue. oct. 3 15:20:46 CET 2023) --- */
/* --- Command line: /home/chengd/.opam/ocaml-variants/bin/heptc -c -target c globals.ept --- */

#ifndef GLOBALS_TYPES_H
#define GLOBALS_TYPES_H

#include "stdbool.h"
#include "assert.h"
#include "pervasives.h"
#include "debug_types.h"
static const int Globals__obstnum = 10;

static const int Globals__trafnum = 6;

static const int Globals__itinum = 50;

typedef struct Globals__color {
  int red;
  int green;
  int blue;
} Globals__color;

typedef enum {
  Globals__Red,
  Globals__Green,
  Globals__Amber,
  Globals__Other
} Globals__colorQ;

Globals__colorQ Globals__colorQ_of_string(char* s);

char* string_of_Globals__colorQ(Globals__colorQ x, char* buf);

typedef struct Globals__position {
  float x;
  float y;
} Globals__position;

typedef enum {
  Globals__Wait,
  Globals__Halt,
  Globals__Ok
} Globals__interrupt;

Globals__interrupt Globals__interrupt_of_string(char* s);

char* string_of_Globals__interrupt(Globals__interrupt x, char* buf);

typedef enum {
  Globals__Preparing,
  Globals__Running,
  Globals__Arrived,
  Globals__Stopped
} Globals__status;

Globals__status Globals__status_of_string(char* s);

char* string_of_Globals__status(Globals__status x, char* buf);

typedef struct Globals__event {
  int lightRun;
  int speedExcess;
  int exitRoad;
  int collisionEvent;
  int dirEvent;
} Globals__event;

typedef struct Globals__obstacle {
  Globals__position o_pos;
  int o_pres;
} Globals__obstacle;

typedef Globals__obstacle Globals__obstacles[10];
  
typedef struct Globals__traflight {
  Globals__position tl_pos;
  Globals__colorQ tl_color;
} Globals__traflight;

typedef Globals__traflight Globals__traflights[6];
  
typedef struct Globals__sign {
  Globals__traflights si_tlights;
  Globals__obstacles si_obstacles;
} Globals__sign;

typedef struct Globals__phase {
  Globals__position ph_pos;
  float ph_vel;
  float ph_head;
} Globals__phase;

typedef struct Globals__sensors {
  Globals__color s_road;
  Globals__color s_front;
  int s_sonar;
} Globals__sensors;

typedef enum {
  Globals__Go,
  Globals__Turn,
  Globals__Stop
} Globals__action;

Globals__action Globals__action_of_string(char* s);

char* string_of_Globals__action(Globals__action x, char* buf);

typedef struct Globals__itielt {
  Globals__action act;
  float param;
} Globals__itielt;

typedef Globals__itielt Globals__itielts[50];
  
typedef struct Globals__wheels {
  float left;
  float right;
} Globals__wheels;

typedef struct Globals__map_data {
  int on_road;
  Globals__color color;
  int max_speed;
  int tl_number;
  int tl_required;
  float dir_x;
  float dir_y;
} Globals__map_data;

typedef struct Globals__param_obst {
  Globals__position pot_pos;
  float pot_since;
  float pot_till;
} Globals__param_obst;

typedef Globals__param_obst Globals__param_obsts[10];
  
typedef struct Globals__param_tlight {
  Globals__position ptl_pos;
  int ptl_green;
  int ptl_amber;
  int ptl_red;
  int ptl_phase;
} Globals__param_tlight;

typedef Globals__param_tlight Globals__param_tlights[6];
  
static const float Globals__pi = 3.141593;

static const Globals__color Globals__red = {255, 0, 0};

static const Globals__color Globals__green = {0, 255, 0};

static const Globals__color Globals__blue = {0, 0, 255};

static const Globals__color Globals__amber = {255, 191, 0};

static const Globals__color Globals__cyan = {0, 255, 255};

static const Globals__color Globals__gray = {128, 128, 128};

static const Globals__color Globals__magenta = {255, 0, 255};

static const float Globals__cB = 6.000000;

static const float Globals__cD = 5.500000;

static const float Globals__cDELTA = 0.000000;

static const float Globals__cMAXWHEEL = 500.000000;

static const float Globals__cMAXSPEED = 25.000000;

static const int Globals__cSONARFAR = 1000;

static const float Globals__cROBST = 1.500000;

static const float Globals__cSA = 3.000000;

static const float Globals__cSB = 3.000000;

static const float Globals__cSC = 7.000000;

static const Globals__wheels Globals__idlew = {0.000000, 0.000000};

static const float Globals__timestep = 0.010000;

#endif // GLOBALS_TYPES_H
