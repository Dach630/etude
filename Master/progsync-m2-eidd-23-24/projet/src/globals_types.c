/* --- Generated the 28/11/2023 at 13:4 --- */
/* --- heptagon compiler, version 1.05.00 (compiled tue. oct. 3 15:20:46 CET 2023) --- */
/* --- Command line: /home/chengd/.opam/ocaml-variants/bin/heptc -c -target c globals.ept --- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "globals_types.h"

Globals__colorQ Globals__colorQ_of_string(char* s) {
  if ((strcmp(s, "Red")==0)) {
    return Globals__Red;
  };
  if ((strcmp(s, "Green")==0)) {
    return Globals__Green;
  };
  if ((strcmp(s, "Amber")==0)) {
    return Globals__Amber;
  };
  if ((strcmp(s, "Other")==0)) {
    return Globals__Other;
  };
}

char* string_of_Globals__colorQ(Globals__colorQ x, char* buf) {
  switch (x) {
    case Globals__Red:
      strcpy(buf, "Red");
      break;
    case Globals__Green:
      strcpy(buf, "Green");
      break;
    case Globals__Amber:
      strcpy(buf, "Amber");
      break;
    case Globals__Other:
      strcpy(buf, "Other");
      break;
    default:
      break;
  };
  return buf;
}

Globals__interrupt Globals__interrupt_of_string(char* s) {
  if ((strcmp(s, "Wait")==0)) {
    return Globals__Wait;
  };
  if ((strcmp(s, "Halt")==0)) {
    return Globals__Halt;
  };
  if ((strcmp(s, "Ok")==0)) {
    return Globals__Ok;
  };
}

char* string_of_Globals__interrupt(Globals__interrupt x, char* buf) {
  switch (x) {
    case Globals__Wait:
      strcpy(buf, "Wait");
      break;
    case Globals__Halt:
      strcpy(buf, "Halt");
      break;
    case Globals__Ok:
      strcpy(buf, "Ok");
      break;
    default:
      break;
  };
  return buf;
}

Globals__status Globals__status_of_string(char* s) {
  if ((strcmp(s, "Preparing")==0)) {
    return Globals__Preparing;
  };
  if ((strcmp(s, "Running")==0)) {
    return Globals__Running;
  };
  if ((strcmp(s, "Arrived")==0)) {
    return Globals__Arrived;
  };
  if ((strcmp(s, "Stopped")==0)) {
    return Globals__Stopped;
  };
}

char* string_of_Globals__status(Globals__status x, char* buf) {
  switch (x) {
    case Globals__Preparing:
      strcpy(buf, "Preparing");
      break;
    case Globals__Running:
      strcpy(buf, "Running");
      break;
    case Globals__Arrived:
      strcpy(buf, "Arrived");
      break;
    case Globals__Stopped:
      strcpy(buf, "Stopped");
      break;
    default:
      break;
  };
  return buf;
}

Globals__action Globals__action_of_string(char* s) {
  if ((strcmp(s, "Go")==0)) {
    return Globals__Go;
  };
  if ((strcmp(s, "Turn")==0)) {
    return Globals__Turn;
  };
  if ((strcmp(s, "Stop")==0)) {
    return Globals__Stop;
  };
}

char* string_of_Globals__action(Globals__action x, char* buf) {
  switch (x) {
    case Globals__Go:
      strcpy(buf, "Go");
      break;
    case Globals__Turn:
      strcpy(buf, "Turn");
      break;
    case Globals__Stop:
      strcpy(buf, "Stop");
      break;
    default:
      break;
  };
  return buf;
}

