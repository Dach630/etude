/* --- Generated the 21/12/2023 at 23:30 --- */
/* --- heptagon compiler, version 1.05.00 (compiled tue. oct. 3 15:20:46 CET 2023) --- */
/* --- Command line: /home/chengd/.opam/ocaml-variants/bin/heptc -c -target c control.ept --- */

#ifndef CONTROL_TYPES_H
#define CONTROL_TYPES_H

#include "stdbool.h"
#include "assert.h"
#include "pervasives.h"
#include "globals_types.h"
#include "mathext_types.h"
#include "utilities_types.h"
typedef enum {
  Control__St_Turn,
  Control__St_Stop,
  Control__St_Go
} Control__st;

Control__st Control__st_of_string(char* s);

char* string_of_Control__st(Control__st x, char* buf);

#endif // CONTROL_TYPES_H
