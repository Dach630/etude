/* --- Generated the 21/12/2023 at 23:30 --- */
/* --- heptagon compiler, version 1.05.00 (compiled tue. oct. 3 15:20:46 CET 2023) --- */
/* --- Command line: /home/chengd/.opam/ocaml-variants/bin/heptc -c -target c control.ept --- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "control_types.h"

Control__st Control__st_of_string(char* s) {
  if ((strcmp(s, "St_Turn")==0)) {
    return Control__St_Turn;
  };
  if ((strcmp(s, "St_Stop")==0)) {
    return Control__St_Stop;
  };
  if ((strcmp(s, "St_Go")==0)) {
    return Control__St_Go;
  };
}

char* string_of_Control__st(Control__st x, char* buf) {
  switch (x) {
    case Control__St_Turn:
      strcpy(buf, "St_Turn");
      break;
    case Control__St_Stop:
      strcpy(buf, "St_Stop");
      break;
    case Control__St_Go:
      strcpy(buf, "St_Go");
      break;
    default:
      break;
  };
  return buf;
}

