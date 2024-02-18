/* --- Generated the 21/12/2023 at 23:30 --- */
/* --- heptagon compiler, version 1.05.00 (compiled tue. oct. 3 15:20:46 CET 2023) --- */
/* --- Command line: /home/chengd/.opam/ocaml-variants/bin/heptc -c -target c challenge.ept --- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "challenge.h"

void Challenge__the_challenge_reset(Challenge__the_challenge_mem* self) {
  Vehicle__simulate_reset(&self->simulate);
  City__scoringB_reset(&self->scoringB);
  City__wallclock_reset(&self->wallclock);
  City__scoringA_reset(&self->scoringA);
  Utilities__event_edge_reset(&self->event_edge);
  self->v_4 = Globals__Ok;
  self->v_1 = true;
}

void Challenge__the_challenge_step(Globals__phase initial_ph, int top,
                                   Challenge__the_challenge_out* _out,
                                   Challenge__the_challenge_mem* self) {
  Vehicle__simulate_out Vehicle__simulate_out_st;
  City__scoringB_out City__scoringB_out_st;
  City__scoringA_out City__scoringA_out_st;
  Utilities__event_edge_out Utilities__event_edge_out_st;
  Map__read_itinerary_out Map__read_itinerary_out_st;
  Map__soundEffects_out Map__soundEffects_out_st;
  City__wallclock_out City__wallclock_out_st;
  City__simulate_out City__simulate_out_st;
  
  Globals__event v_5;
  Globals__sensors v_3;
  Globals__itielts v;
  Globals__interrupt itr;
  Globals__sensors ini_sens;
  Globals__sensors sens;
  Map__read_itinerary_step(&Map__read_itinerary_out_st);
  {
    int _1;
    for (_1 = 0; _1 < 50; ++_1) {
      v[_1] = Map__read_itinerary_out_st.iti[_1];
    }
  };
  ini_sens.s_sonar = 1000;
  ini_sens.s_front.blue = 128;
  ini_sens.s_front.green = 128;
  ini_sens.s_front.red = 128;
  ini_sens.s_road.blue = 128;
  ini_sens.s_road.green = 128;
  ini_sens.s_road.red = 128;
  if (self->v_1) {
    v_3 = ini_sens;
  } else {
    v_3 = self->v_2;
  };
  Vehicle__simulate_step(v, v_3, self->v_4, initial_ph, top,
                         &Vehicle__simulate_out_st, &self->simulate);
  _out->ph = Vehicle__simulate_out_st.ph;
  _out->sta = Vehicle__simulate_out_st.sta;
  City__scoringB_step(_out->ph, &City__scoringB_out_st, &self->scoringB);
  _out->scoreB = City__scoringB_out_st.score;
  City__wallclock_step(_out->sta, &City__wallclock_out_st, &self->wallclock);
  _out->time = City__wallclock_out_st.time;
  City__simulate_step(_out->ph, _out->time, &City__simulate_out_st);
  _out->sign = City__simulate_out_st.sign;
  itr = City__simulate_out_st.itr;
  sens = City__simulate_out_st.sens;
  _out->evt = City__simulate_out_st.evt;
  City__scoringA_step(_out->evt, _out->sta, &City__scoringA_out_st,
                      &self->scoringA);
  _out->scoreA = City__scoringA_out_st.score;
  Utilities__event_edge_step(_out->evt, &Utilities__event_edge_out_st,
                             &self->event_edge);
  v_5 = Utilities__event_edge_out_st.o;
  Map__soundEffects_step(v_5, _out->sta, &Map__soundEffects_out_st);
  self->v_4 = itr;
  self->v_2 = sens;
  self->v_1 = false;;
}

