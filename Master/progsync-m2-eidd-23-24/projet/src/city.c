/* --- Generated the 21/12/2023 at 23:30 --- */
/* --- heptagon compiler, version 1.05.00 (compiled tue. oct. 3 15:20:46 CET 2023) --- */
/* --- Command line: /home/chengd/.opam/ocaml-variants/bin/heptc -c -target c city.ept --- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "city.h"

void City__wallclock_reset(City__wallclock_mem* self) {
  self->v_2 = 0;
}

void City__wallclock_step(Globals__status rstatus, City__wallclock_out* _out,
                          City__wallclock_mem* self) {
  Mathext__float_out Mathext__float_out_st;
  
  float v_3;
  int v_1;
  int v;
  int cpt;
  v = (rstatus==Globals__Running);
  if (v) {
    v_1 = 1;
  } else {
    v_1 = 0;
  };
  cpt = (v_1+self->v_2);
  Mathext__float_step(cpt, &Mathext__float_out_st);
  v_3 = Mathext__float_out_st.o;
  _out->time = (Globals__timestep*v_3);
  self->v_2 = cpt;;
}

void City__lookup_phase_step(Globals__phase ph, City__lookup_phase_out* _out) {
  Map__lookup_pos_out Map__lookup_pos_out_st;
  Map__lookup_pos_step(ph.ph_pos, &Map__lookup_pos_out_st);
  _out->data = Map__lookup_pos_out_st.data;
}

void City__light_step(Globals__traflights lights, Globals__phase ph,
                      City__light_out* _out) {
  City__lookup_phase_out City__lookup_phase_out_st;
  
  int v_6;
  Globals__traflight v_5;
  int v_4;
  int v;
  Globals__map_data data;
  v = (ph.ph_vel>0.010000);
  City__lookup_phase_step(ph, &City__lookup_phase_out_st);
  data = City__lookup_phase_out_st.data;
  v_5 = lights[between(data.tl_number, Globals__trafnum)];
  v_6 = (v_5.tl_color==Globals__Red);
  v_4 = (v&&data.tl_required);
  _out->light_run = (v_4&&v_6);;
}

void City__speed_step(Globals__phase ph, City__speed_out* _out) {
  Mathext__float_out Mathext__float_out_st;
  City__lookup_phase_out City__lookup_phase_out_st;
  
  float v_7;
  Globals__map_data v;
  City__lookup_phase_step(ph, &City__lookup_phase_out_st);
  v = City__lookup_phase_out_st.data;
  Mathext__float_step(v.max_speed, &Mathext__float_out_st);
  v_7 = Mathext__float_out_st.o;
  _out->speed_excess = (ph.ph_vel>v_7);;
}

void City__exited_aux_step(Globals__position pos, int acc,
                           City__exited_aux_out* _out) {
  Map__lookup_pos_out Map__lookup_pos_out_st;
  
  Globals__map_data v;
  Map__lookup_pos_step(pos, &Map__lookup_pos_out_st);
  v = Map__lookup_pos_out_st.data;
  _out->accnew = (acc&&v.on_road);;
}

void City__exited_step(Globals__phase ph, City__exited_out* _out) {
  Vehicle__car_geometry_out Vehicle__car_geometry_out_st;
  City__exited_aux_out City__exited_aux_out_st;
  
  int v_9;
  float v_8[2][2];
  Globals__phase v[2];
  Globals__position positions[2];
  Globals__phase dummy[2];
  {
    int i_6;
    for (i_6 = 0; i_6 < 2; ++i_6) {
      v[i_6] = ph;
    }
  };
  v_8[0][0] = -0.000000;
  v_8[0][1] = 3.000000;
  v_8[1][0] = -0.000000;
  v_8[1][1] = -3.000000;
  {
    int i_5;
    for (i_5 = 0; i_5 < 2; ++i_5) {
      Vehicle__car_geometry_step(v[i_5], v_8[i_5],
                                 &Vehicle__car_geometry_out_st);
      positions[i_5] = Vehicle__car_geometry_out_st.newpos;
      dummy[i_5] = Vehicle__car_geometry_out_st.newphase;
    }
  };
  v_9 = true;
  {
    int i;
    for (i = 0; i < 2; ++i) {
      City__exited_aux_step(positions[i], v_9, &City__exited_aux_out_st);
      v_9 = City__exited_aux_out_st.accnew;
    }
  };
  _out->exit_road = !(v_9);;
}

void City__collision_aux_step(Globals__phase ph, Globals__obstacle obst,
                              int acc, City__collision_aux_out* _out) {
  Mathext__cos_out Mathext__cos_out_st;
  Utilities__angle_dist_out Utilities__angle_dist_out_st;
  Utilities__normalize_out Utilities__normalize_out_st;
  Mathext__sin_out Mathext__sin_out_st;
  Utilities__abs_out Utilities__abs_out_st;
  
  int v_24;
  float v_23;
  float v_22;
  int v_21;
  int v_20;
  float v_19;
  float v_18;
  int v_17;
  float v_16;
  float v_15;
  int v_14;
  int v_13;
  int v_12;
  float v_11;
  float v_10;
  float v;
  float ang;
  float angle;
  float dist;
  float distobst;
  int close;
  Utilities__angle_dist_step(ph.ph_pos, obst.o_pos,
                             &Utilities__angle_dist_out_st);
  ang = Utilities__angle_dist_out_st.angle;
  dist = Utilities__angle_dist_out_st.dist;
  v = (ph.ph_head-ang);
  distobst = (dist-Globals__cROBST);
  v_12 = (dist<=Globals__cROBST);
  Utilities__normalize_step(v, &Utilities__normalize_out_st);
  v_10 = Utilities__normalize_out_st.normal;
  Utilities__abs_step(v_10, &Utilities__abs_out_st);
  v_11 = Utilities__abs_out_st.o;
  angle = (0.017453*v_11);
  Mathext__cos_step(angle, &Mathext__cos_out_st);
  v_22 = Mathext__cos_out_st.o;
  v_23 = (v_22*distobst);
  v_24 = (v_23>=-7.000000);
  Mathext__cos_step(angle, &Mathext__cos_out_st);
  v_18 = Mathext__cos_out_st.o;
  v_19 = (v_18*distobst);
  v_20 = (v_19<=Globals__cSA);
  Mathext__sin_step(angle, &Mathext__sin_out_st);
  v_15 = Mathext__sin_out_st.o;
  v_16 = (v_15*distobst);
  v_17 = (v_16<=Globals__cSB);
  v_21 = (v_17&&v_20);
  close = (v_21&&v_24);
  v_13 = (v_12||close);
  v_14 = (obst.o_pres&&v_13);
  _out->accnew = (acc||v_14);;
}

void City__collision_step(Globals__phase ph, Globals__obstacles obstacles,
                          City__collision_out* _out) {
  City__collision_aux_out City__collision_aux_out_st;
  
  Globals__phase v[10];
  {
    int i_4;
    for (i_4 = 0; i_4 < Globals__obstnum; ++i_4) {
      v[i_4] = ph;
    }
  };
  _out->collision_event = false;
  {
    int i;
    for (i = 0; i < Globals__obstnum; ++i) {
      City__collision_aux_step(v[i], obstacles[i], _out->collision_event,
                               &City__collision_aux_out_st);
      _out->collision_event = City__collision_aux_out_st.accnew;
    }
  };;
}

void City__wrong_dir_step(Globals__phase ph, City__wrong_dir_out* _out) {
  Mathext__cos_out Mathext__cos_out_st;
  City__lookup_phase_out City__lookup_phase_out_st;
  Mathext__sin_out Mathext__sin_out_st;
  
  float v_27;
  float v_26;
  float v_25;
  float v;
  Globals__map_data data;
  float error;
  float ang;
  ang = (ph.ph_head*0.017453);
  Mathext__sin_step(ang, &Mathext__sin_out_st);
  v_26 = Mathext__sin_out_st.o;
  Mathext__cos_step(ang, &Mathext__cos_out_st);
  v = Mathext__cos_out_st.o;
  City__lookup_phase_step(ph, &City__lookup_phase_out_st);
  data = City__lookup_phase_out_st.data;
  v_27 = (data.dir_y*v_26);
  v_25 = (data.dir_x*v);
  error = (v_25+v_27);
  _out->wrong = (error<-0.500000);;
}

void City__aggregate_events_step(int lightRun, int speedExcess, int exitRoad,
                                 int collisionEvent, int wrong,
                                 City__aggregate_events_out* _out) {
  if (exitRoad) {
    _out->itr = Globals__Halt;
  } else {
    _out->itr = Globals__Ok;
  };
  _out->o.lightRun = lightRun;
  _out->o.speedExcess = speedExcess;
  _out->o.exitRoad = exitRoad;
  _out->o.collisionEvent = collisionEvent;
  _out->o.dirEvent = wrong;
}

void City__event_detection_step(Globals__sign sign, Globals__phase ph,
                                City__event_detection_out* _out) {
  City__exited_out City__exited_out_st;
  City__aggregate_events_out City__aggregate_events_out_st;
  City__wrong_dir_out City__wrong_dir_out_st;
  City__collision_out City__collision_out_st;
  City__light_out City__light_out_st;
  City__speed_out City__speed_out_st;
  
  int v_31;
  int v_30;
  int v_29;
  int v_28;
  int v;
  City__wrong_dir_step(ph, &City__wrong_dir_out_st);
  v_31 = City__wrong_dir_out_st.wrong;
  City__collision_step(ph, sign.si_obstacles, &City__collision_out_st);
  v_30 = City__collision_out_st.collision_event;
  City__light_step(sign.si_tlights, ph, &City__light_out_st);
  v = City__light_out_st.light_run;
  City__exited_step(ph, &City__exited_out_st);
  v_29 = City__exited_out_st.exit_road;
  City__speed_step(ph, &City__speed_out_st);
  v_28 = City__speed_out_st.speed_excess;
  City__aggregate_events_step(v, v_28, v_29, v_30, v_31,
                              &City__aggregate_events_out_st);
  _out->evts = City__aggregate_events_out_st.o;
  _out->itr = City__aggregate_events_out_st.itr;;
}

void City__ground_color_detection_step(Globals__phase ph,
                                       City__ground_color_detection_out* _out) {
  City__lookup_phase_out City__lookup_phase_out_st;
  
  Globals__map_data v;
  City__lookup_phase_step(ph, &City__lookup_phase_out_st);
  v = City__lookup_phase_out_st.data;
  _out->road_color = v.color;;
}

void City__traffic_light_detection_step(Globals__phase ph,
                                        Globals__traflights traflights,
                                        City__traffic_light_detection_out* _out) {
  City__lookup_phase_out City__lookup_phase_out_st;
  Utilities__encode_color_out Utilities__encode_color_out_st;
  
  Globals__traflight v_33;
  Globals__map_data v_32;
  Globals__traflight v;
  City__lookup_phase_step(ph, &City__lookup_phase_out_st);
  v_32 = City__lookup_phase_out_st.data;
  v.tl_color = Globals__Other;
  v.tl_pos.y = 0.000000;
  v.tl_pos.x = 0.000000;
  if (((v_32.tl_number<Globals__trafnum)&&(0<=v_32.tl_number))) {
    v_33 = traflights[v_32.tl_number];
  } else {
    v_33 = v;
  };
  Utilities__encode_color_step(v_33.tl_color, &Utilities__encode_color_out_st);
  _out->tlight_color = Utilities__encode_color_out_st.a;;
}

void City__obstacles_detection_aux_step(Globals__phase ph,
                                        Globals__obstacle obst, int acc,
                                        City__obstacles_detection_aux_out* _out) {
  Utilities__angle_dist_out Utilities__angle_dist_out_st;
  Utilities__normalize_out Utilities__normalize_out_st;
  Utilities__min_int_out Utilities__min_int_out_st;
  Mathext__int_out Mathext__int_out_st;
  Utilities__abs_out Utilities__abs_out_st;
  
  int v_40;
  int v_39;
  int v_38;
  int v_37;
  int v_36;
  float v_35;
  float v_34;
  float v;
  float a;
  float d;
  float d1;
  int sonar;
  Utilities__angle_dist_step(ph.ph_pos, obst.o_pos,
                             &Utilities__angle_dist_out_st);
  a = Utilities__angle_dist_out_st.angle;
  d = Utilities__angle_dist_out_st.dist;
  v = (ph.ph_head-a);
  Utilities__normalize_step(v, &Utilities__normalize_out_st);
  v_34 = Utilities__normalize_out_st.normal;
  Utilities__abs_step(v_34, &Utilities__abs_out_st);
  v_35 = Utilities__abs_out_st.o;
  v_36 = (v_35<=30.000000);
  d1 = (d-Globals__cROBST);
  Mathext__int_step(d1, &Mathext__int_out_st);
  v_40 = Mathext__int_out_st.o;
  v_37 = (d1<=100.000000);
  v_38 = (v_36&&v_37);
  v_39 = (v_38&&obst.o_pres);
  if (v_39) {
    sonar = v_40;
  } else {
    sonar = 1000;
  };
  Utilities__min_int_step(sonar, acc, &Utilities__min_int_out_st);
  _out->accnew = Utilities__min_int_out_st.o;;
}

void City__obstacle_detection_step(Globals__phase ph,
                                   Globals__obstacles obstacles,
                                   City__obstacle_detection_out* _out) {
  City__obstacles_detection_aux_out City__obstacles_detection_aux_out_st;
  
  Globals__phase v[10];
  {
    int i_3;
    for (i_3 = 0; i_3 < Globals__obstnum; ++i_3) {
      v[i_3] = ph;
    }
  };
  _out->sonar = 1000;
  {
    int i;
    for (i = 0; i < Globals__obstnum; ++i) {
      City__obstacles_detection_aux_step(v[i], obstacles[i], _out->sonar,
                                         &City__obstacles_detection_aux_out_st);
      _out->sonar = City__obstacles_detection_aux_out_st.accnew;
    }
  };;
}

void City__robot_sensors_step(Globals__phase ph, Globals__sign sign,
                              City__robot_sensors_out* _out) {
  City__obstacle_detection_out City__obstacle_detection_out_st;
  City__ground_color_detection_out City__ground_color_detection_out_st;
  City__traffic_light_detection_out City__traffic_light_detection_out_st;
  
  int v_42;
  Globals__color v_41;
  Globals__color v;
  City__obstacle_detection_step(ph, sign.si_obstacles,
                                &City__obstacle_detection_out_st);
  v_42 = City__obstacle_detection_out_st.sonar;
  City__traffic_light_detection_step(ph, sign.si_tlights,
                                     &City__traffic_light_detection_out_st);
  v_41 = City__traffic_light_detection_out_st.tlight_color;
  City__ground_color_detection_step(ph, &City__ground_color_detection_out_st);
  v = City__ground_color_detection_out_st.road_color;
  _out->sens.s_road = v;
  _out->sens.s_front = v_41;
  _out->sens.s_sonar = v_42;;
}

void City__traffic_lights_aux_step(Globals__param_tlight p, float time,
                                   City__traffic_lights_aux_out* _out) {
  Mathext__modulo_out Mathext__modulo_out_st;
  Mathext__int_out Mathext__int_out_st;
  Utilities__max_int_out Utilities__max_int_out_st;
  
  int v_46;
  Globals__colorQ light_false_false;
  Globals__colorQ light_false_true;
  int ck_1;
  Globals__colorQ light_false;
  Globals__colorQ light_true;
  int ck;
  int v_45;
  int v_44;
  int v_43;
  int v;
  int cpt;
  int period;
  Globals__colorQ light;
  Mathext__int_step(time, &Mathext__int_out_st);
  v_44 = Mathext__int_out_st.o;
  v_45 = (v_44+p.ptl_phase);
  v = (p.ptl_amber+p.ptl_green);
  v_43 = (v+p.ptl_red);
  Utilities__max_int_step(1, v_43, &Utilities__max_int_out_st);
  period = Utilities__max_int_out_st.o;
  Mathext__modulo_step(v_45, period, &Mathext__modulo_out_st);
  cpt = Mathext__modulo_out_st.o;
  ck = (cpt<p.ptl_green);
  if (ck) {
    light_true = Globals__Green;
    light = light_true;
  } else {
    v_46 = (p.ptl_amber+p.ptl_green);
    ck_1 = (cpt<v_46);
    if (ck_1) {
      light_false_true = Globals__Amber;
      light_false = light_false_true;
    } else {
      light_false_false = Globals__Red;
      light_false = light_false_false;
    };
    light = light_false;
  };
  _out->tl.tl_pos = p.ptl_pos;
  _out->tl.tl_color = light;;
}

void City__traffic_lights_step(float time, City__traffic_lights_out* _out) {
  Map__read_traffic_lights_out Map__read_traffic_lights_out_st;
  City__traffic_lights_aux_out City__traffic_lights_aux_out_st;
  
  float v[6];
  Globals__param_tlights lights;
  {
    int i_2;
    for (i_2 = 0; i_2 < Globals__trafnum; ++i_2) {
      v[i_2] = time;
    }
  };
  Map__read_traffic_lights_step(&Map__read_traffic_lights_out_st);
  {
    int _1;
    for (_1 = 0; _1 < 6; ++_1) {
      lights[_1] = Map__read_traffic_lights_out_st.tlights[_1];
    }
  };
  {
    int i;
    for (i = 0; i < Globals__trafnum; ++i) {
      City__traffic_lights_aux_step(lights[i], v[i],
                                    &City__traffic_lights_aux_out_st);
      _out->all_lights[i] = City__traffic_lights_aux_out_st.tl;
    }
  };;
}

void City__all_obstacles_aux_step(Globals__param_obst po, float time,
                                  City__all_obstacles_aux_out* _out) {
  
  int v_48;
  int v_47;
  int v;
  v_47 = (time<=po.pot_till);
  v = (po.pot_since<=time);
  v_48 = (v&&v_47);
  _out->o.o_pos = po.pot_pos;
  _out->o.o_pres = v_48;;
}

void City__all_obstacles_step(float time, City__all_obstacles_out* _out) {
  City__all_obstacles_aux_out City__all_obstacles_aux_out_st;
  Map__read_obstacles_out Map__read_obstacles_out_st;
  
  float v_49[10];
  Globals__param_obsts v;
  {
    int i_1;
    for (i_1 = 0; i_1 < Globals__obstnum; ++i_1) {
      v_49[i_1] = time;
    }
  };
  Map__read_obstacles_step(&Map__read_obstacles_out_st);
  {
    int _2;
    for (_2 = 0; _2 < 10; ++_2) {
      v[_2] = Map__read_obstacles_out_st.obst[_2];
    }
  };
  {
    int i;
    for (i = 0; i < Globals__obstnum; ++i) {
      City__all_obstacles_aux_step(v[i], v_49[i],
                                   &City__all_obstacles_aux_out_st);
      _out->obstacles[i] = City__all_obstacles_aux_out_st.o;
    }
  };;
}

void City__simulate_step(Globals__phase ph, float time,
                         City__simulate_out* _out) {
  City__all_obstacles_out City__all_obstacles_out_st;
  City__event_detection_out City__event_detection_out_st;
  City__traffic_lights_out City__traffic_lights_out_st;
  City__robot_sensors_out City__robot_sensors_out_st;
  
  Globals__obstacles v_50;
  Globals__traflights v;
  City__all_obstacles_step(time, &City__all_obstacles_out_st);
  {
    int _3;
    for (_3 = 0; _3 < 10; ++_3) {
      v_50[_3] = City__all_obstacles_out_st.obstacles[_3];
    }
  };
  City__traffic_lights_step(time, &City__traffic_lights_out_st);
  {
    int _4;
    for (_4 = 0; _4 < 6; ++_4) {
      v[_4] = City__traffic_lights_out_st.all_lights[_4];
    }
  };
  {
    int _6;
    for (_6 = 0; _6 < 6; ++_6) {
      _out->sign.si_tlights[_6] = v[_6];
    }
  };
  {
    int _5;
    for (_5 = 0; _5 < 10; ++_5) {
      _out->sign.si_obstacles[_5] = v_50[_5];
    }
  };
  City__robot_sensors_step(ph, _out->sign, &City__robot_sensors_out_st);
  _out->sens = City__robot_sensors_out_st.sens;
  City__event_detection_step(_out->sign, ph, &City__event_detection_out_st);
  _out->itr = City__event_detection_out_st.itr;
  _out->evt = City__event_detection_out_st.evts;;
}

void City__scoringA_reset(City__scoringA_mem* self) {
  Utilities__countdown_reset(&self->countdown);
  Utilities__rising_edge_reset(&self->rising_edge_4);
  Utilities__rising_edge_reset(&self->rising_edge_3);
  Utilities__rising_edge_reset(&self->rising_edge_2);
  Utilities__rising_edge_reset(&self->rising_edge_1);
  Utilities__rising_edge_reset(&self->rising_edge);
  self->v = 10000;
}

void City__scoringA_step(Globals__event e, Globals__status rstatus,
                         City__scoringA_out* _out, City__scoringA_mem* self) {
  Utilities__rising_edge_out Utilities__rising_edge_out_st;
  Utilities__countdown_out Utilities__countdown_out_st;
  
  int v_75;
  int v_74;
  int v_73;
  int v_72;
  int v_71;
  int v_70;
  int v_69;
  int v_68;
  int v_67;
  int v_66;
  int v_65;
  int v_64;
  int v_63;
  int v_62;
  int v_61;
  int v_60;
  int v_59;
  int v_58;
  int v_57;
  int v_56;
  int v_55;
  int v_54;
  int v_53;
  int v_52;
  int v_51;
  int penalty;
  int collision_count;
  v_75 = !(e.collisionEvent);
  Utilities__countdown_step(v_75, 20, &Utilities__countdown_out_st,
                            &self->countdown);
  collision_count = Utilities__countdown_out_st.o;
  v_73 = (collision_count<0);
  if (v_73) {
    v_74 = 10;
  } else {
    v_74 = 0;
  };
  v_70 = (collision_count==0);
  if (v_70) {
    v_71 = -500;
  } else {
    v_71 = 0;
  };
  Utilities__rising_edge_step(e.dirEvent, &Utilities__rising_edge_out_st,
                              &self->rising_edge_4);
  v_67 = Utilities__rising_edge_out_st.e;
  if (v_67) {
    v_68 = -2000;
  } else {
    v_68 = 0;
  };
  Utilities__rising_edge_step(e.exitRoad, &Utilities__rising_edge_out_st,
                              &self->rising_edge_3);
  v_64 = Utilities__rising_edge_out_st.e;
  if (v_64) {
    v_65 = -5000;
  } else {
    v_65 = 0;
  };
  if (e.speedExcess) {
    v_62 = -2;
  } else {
    v_62 = 0;
  };
  Utilities__rising_edge_step(e.speedExcess, &Utilities__rising_edge_out_st,
                              &self->rising_edge_2);
  v_59 = Utilities__rising_edge_out_st.e;
  Utilities__rising_edge_step(e.lightRun, &Utilities__rising_edge_out_st,
                              &self->rising_edge_1);
  v_57 = Utilities__rising_edge_out_st.e;
  if (v_59) {
    v_60 = -100;
  } else {
    v_60 = 0;
  };
  if (v_57) {
    v_58 = -500;
  } else {
    v_58 = 0;
  };
  v_61 = (v_58+v_60);
  v_63 = (v_61+v_62);
  v_66 = (v_63+v_65);
  v_69 = (v_66+v_68);
  v_72 = (v_69+v_71);
  penalty = (v_72+v_74);
  v_53 = (rstatus==Globals__Running);
  if (v_53) {
    v_54 = penalty;
  } else {
    v_54 = 0;
  };
  v_55 = (0+v_54);
  v_51 = (rstatus==Globals__Arrived);
  Utilities__rising_edge_step(v_51, &Utilities__rising_edge_out_st,
                              &self->rising_edge);
  v_52 = Utilities__rising_edge_out_st.e;
  if (v_52) {
    v_56 = 1000;
  } else {
    v_56 = v_55;
  };
  _out->score = (self->v+v_56);
  self->v = _out->score;;
}

void City__scoringB_reset(City__scoringB_mem* self) {
  Utilities__uptime_reset(&self->uptime);
  Utilities__variation_reset(&self->variation);
}

void City__scoringB_step(Globals__phase ph, City__scoringB_out* _out,
                         City__scoringB_mem* self) {
  Utilities__variation_out Utilities__variation_out_st;
  Mathext__int_out Mathext__int_out_st;
  Utilities__uptime_out Utilities__uptime_out_st;
  
  float v_80;
  float v_79;
  float v_78;
  float v_77;
  int v_76;
  float v;
  Utilities__uptime_step(ph.ph_vel, Globals__timestep,
                         &Utilities__uptime_out_st, &self->uptime);
  v_78 = Utilities__uptime_out_st.t;
  v_79 = (1.000000+v_78);
  v_76 = (ph.ph_vel>=1.000000);
  Utilities__variation_step(v_76, ph.ph_head, Globals__timestep,
                            &Utilities__variation_out_st, &self->variation);
  v_77 = Utilities__variation_out_st.o;
  v = (v_77/v_79);
  v_80 = (1000.000000-v);
  Mathext__int_step(v_80, &Mathext__int_out_st);
  _out->score = Mathext__int_out_st.o;;
}

