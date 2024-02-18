/* --- Generated the 21/12/2023 at 23:30 --- */
/* --- heptagon compiler, version 1.05.00 (compiled tue. oct. 3 15:20:46 CET 2023) --- */
/* --- Command line: /home/chengd/.opam/ocaml-variants/bin/heptc -c -target c vehicle.ept --- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vehicle_types.h"

Vehicle__st_1 Vehicle__st_1_of_string(char* s) {
  if ((strcmp(s, "St_1_Positioning")==0)) {
    return Vehicle__St_1_Positioning;
  };
  if ((strcmp(s, "St_1_On")==0)) {
    return Vehicle__St_1_On;
  };
}

char* string_of_Vehicle__st_1(Vehicle__st_1 x, char* buf) {
  switch (x) {
    case Vehicle__St_1_Positioning:
      strcpy(buf, "St_1_Positioning");
      break;
    case Vehicle__St_1_On:
      strcpy(buf, "St_1_On");
      break;
    default:
      break;
  };
  return buf;
}

Vehicle__st Vehicle__st_of_string(char* s) {
  if ((strcmp(s, "St_Stopped")==0)) {
    return Vehicle__St_Stopped;
  };
  if ((strcmp(s, "St_Running")==0)) {
    return Vehicle__St_Running;
  };
  if ((strcmp(s, "St_Preparing")==0)) {
    return Vehicle__St_Preparing;
  };
  if ((strcmp(s, "St_Arrived")==0)) {
    return Vehicle__St_Arrived;
  };
}

char* string_of_Vehicle__st(Vehicle__st x, char* buf) {
  switch (x) {
    case Vehicle__St_Stopped:
      strcpy(buf, "St_Stopped");
      break;
    case Vehicle__St_Running:
      strcpy(buf, "St_Running");
      break;
    case Vehicle__St_Preparing:
      strcpy(buf, "St_Preparing");
      break;
    case Vehicle__St_Arrived:
      strcpy(buf, "St_Arrived");
      break;
    default:
      break;
  };
  return buf;
}

