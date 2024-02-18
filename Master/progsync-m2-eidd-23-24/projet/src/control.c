/* --- Generated the 21/12/2023 at 23:30 --- */
/* --- heptagon compiler, version 1.05.00 (compiled tue. oct. 3 15:20:46 CET 2023) --- */
/* --- Command line: /home/chengd/.opam/ocaml-variants/bin/heptc -c -target c control.ept --- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "control.h"

void Control__vitesse_limit_step(float limit,
                                 Control__vitesse_limit_out* _out) {
  
  float v;
  v = (Globals__cMAXWHEEL*limit);
  _out->vit = (v/Globals__cMAXSPEED);;
}

void Control__pid_reset(Control__pid_mem* self) {
  Utilities__derivative_reset(&self->derivative);
  Utilities__integrator_reset(&self->integrator);
}

void Control__pid_step(float err, Control__pid_out* _out,
                       Control__pid_mem* self) {
  Utilities__integrator_out Utilities__integrator_out_st;
  Utilities__derivative_out Utilities__derivative_out_st;
  
  float v_2;
  float v_1;
  float v;
  float p;
  float i;
  float d;
  Utilities__derivative_step(err, Globals__timestep,
                             &Utilities__derivative_out_st, &self->derivative);
  v_1 = Utilities__derivative_out_st.y;
  d = (1.000000*v_1);
  Utilities__integrator_step(err, Globals__timestep, 0.000000,
                             &Utilities__integrator_out_st, &self->integrator);
  v = Utilities__integrator_out_st.o;
  i = (1.000000*v);
  p = (1.000000*err);
  v_2 = (p+i);
  _out->corr = (v_2+d);;
}

void Control__correction_left_reset(Control__correction_left_mem* self) {
  Control__pid_reset(&self->pid);
}

void Control__correction_left_step(Globals__sensors sens, float limit,
                                   Control__correction_left_out* _out,
                                   Control__correction_left_mem* self) {
  Control__pid_out Control__pid_out_st;
  Mathext__float_out Mathext__float_out_st;
  Control__vitesse_limit_out Control__vitesse_limit_out_st;
  
  int v_9;
  float v_8;
  float v_7;
  float v_6;
  int v_5;
  int v_4;
  int v_3;
  float v;
  float tmp;
  Mathext__float_step(sens.s_road.red, &Mathext__float_out_st);
  v_6 = Mathext__float_out_st.o;
  Control__pid_step(v_6, &Control__pid_out_st, &self->pid);
  v_7 = Control__pid_out_st.corr;
  v_4 = (sens.s_road.blue>0);
  v_3 = (sens.s_road.red>0);
  v_5 = (v_3&&v_4);
  if (v_5) {
    v_8 = v_7;
  } else {
    v_8 = 0.000000;
  };
  Control__vitesse_limit_step(limit, &Control__vitesse_limit_out_st);
  v = Control__vitesse_limit_out_st.vit;
  tmp = (v-v_8);
  v_9 = (tmp<0.000000);
  if (v_9) {
    _out->left = 0.000000;
  } else {
    _out->left = tmp;
  };;
}

void Control__correction_right_reset(Control__correction_right_mem* self) {
  Control__pid_reset(&self->pid);
}

void Control__correction_right_step(Globals__sensors sens, float limit,
                                    Control__correction_right_out* _out,
                                    Control__correction_right_mem* self) {
  Control__pid_out Control__pid_out_st;
  Mathext__float_out Mathext__float_out_st;
  Control__vitesse_limit_out Control__vitesse_limit_out_st;
  
  int v_16;
  float v_15;
  float v_14;
  float v_13;
  int v_12;
  int v_11;
  int v_10;
  float v;
  float tmp;
  Mathext__float_step(sens.s_road.green, &Mathext__float_out_st);
  v_13 = Mathext__float_out_st.o;
  Control__pid_step(v_13, &Control__pid_out_st, &self->pid);
  v_14 = Control__pid_out_st.corr;
  v_11 = (sens.s_road.blue>0);
  v_10 = (sens.s_road.green>0);
  v_12 = (v_10&&v_11);
  if (v_12) {
    v_15 = v_14;
  } else {
    v_15 = 0.000000;
  };
  Control__vitesse_limit_step(limit, &Control__vitesse_limit_out_st);
  v = Control__vitesse_limit_out_st.vit;
  tmp = (v-v_15);
  v_16 = (tmp<0.000000);
  if (v_16) {
    _out->right = 0.000000;
  } else {
    _out->right = tmp;
  };;
}

void Control__is_colors_equals_step(Globals__color c1, Globals__color c2,
                                    Control__is_colors_equals_out* _out) {
  
  int v_19;
  int v_18;
  int v_17;
  int v;
  v_19 = (c1.blue==c2.blue);
  v_17 = (c1.green==c2.green);
  v = (c1.red==c2.red);
  v_18 = (v&&v_17);
  _out->o = (v_18&&v_19);;
}

void Control__nouvelle_etape_reset(Control__nouvelle_etape_mem* self) {
  self->tmp.blue = 255;
  self->tmp.green = 0;
  self->tmp.red = 0;
}

void Control__nouvelle_etape_step(Globals__sensors sens, int tourne,
                                  Control__nouvelle_etape_out* _out,
                                  Control__nouvelle_etape_mem* self) {
  Control__is_colors_equals_out Control__is_colors_equals_out_st;
  
  int v_23;
  int v_22;
  int v_21;
  int v_20;
  int v;
  Control__is_colors_equals_step(self->tmp, Globals__green,
                                 &Control__is_colors_equals_out_st);
  v_20 = Control__is_colors_equals_out_st.o;
  v_23 = !(tourne);
  v_21 = !(v_20);
  Control__is_colors_equals_step(sens.s_road, Globals__green,
                                 &Control__is_colors_equals_out_st);
  v = Control__is_colors_equals_out_st.o;
  v_22 = (v&&v_21);
  _out->nouv = (v_22&&v_23);
  self->tmp = sens.s_road;;
}

void Control__int_of_bool_step(int b, Control__int_of_bool_out* _out) {
  if (b) {
    _out->i = 1;
  } else {
    _out->i = 0;
  };
}

void Control__feu_tricolore_step(Globals__sensors sens,
                                 Control__feu_tricolore_out* _out) {
  Control__is_colors_equals_out Control__is_colors_equals_out_st;
  
  int v_26;
  int v_25;
  int v_24;
  int v;
  Control__is_colors_equals_step(sens.s_front, Globals__amber,
                                 &Control__is_colors_equals_out_st);
  v_25 = Control__is_colors_equals_out_st.o;
  Control__is_colors_equals_step(sens.s_front, Globals__red,
                                 &Control__is_colors_equals_out_st);
  v_24 = Control__is_colors_equals_out_st.o;
  Control__is_colors_equals_step(sens.s_road, Globals__red,
                                 &Control__is_colors_equals_out_st);
  v = Control__is_colors_equals_out_st.o;
  v_26 = (v_24||v_25);
  _out->arret = (v&&v_26);;
}

void Control__correction_vitesse_virage_step(float left, float right,
                                             Control__correction_vitesse_virage_out* _out) {
  
  float v_31;
  int v_30;
  int v_29;
  float v_28;
  int v_27;
  int v;
  v_31 = (right*0.750000);
  v_29 = (left==right);
  v_30 = !(v_29);
  if (v_30) {
    _out->n_right = v_31;
  } else {
    _out->n_right = right;
  };
  v_28 = (left*0.750000);
  v = (left==right);
  v_27 = !(v);
  if (v_27) {
    _out->n_left = v_28;
  } else {
    _out->n_left = left;
  };;
}

void Control__rotation_step(float degre, float limit,
                            Control__rotation_out* _out) {
  Control__vitesse_limit_out Control__vitesse_limit_out_st;
  
  Globals__wheels v_39;
  float v_38;
  Globals__wheels v_37;
  float v_36;
  int v_35;
  float v_34;
  float v_33;
  float v_32;
  int v;
  float perimetre_tour;
  float distance_rotation;
  Control__vitesse_limit_step(limit, &Control__vitesse_limit_out_st);
  v_38 = Control__vitesse_limit_out_st.vit;
  Control__vitesse_limit_step(limit, &Control__vitesse_limit_out_st);
  v_36 = Control__vitesse_limit_out_st.vit;
  v_35 = (degre>0.000000);
  v_32 = -(degre);
  v = (degre>0.000000);
  if (v) {
    v_33 = degre;
  } else {
    v_33 = v_32;
  };
  perimetre_tour = 37.699111;
  v_34 = (perimetre_tour*v_33);
  distance_rotation = (v_34/360.000000);
  _out->temps_rotation = (distance_rotation/limit);
  v_39.left = v_38;
  v_39.right = 0.000000;
  v_37.left = 0.000000;
  v_37.right = v_36;
  if (v_35) {
    _out->roue = v_37;
  } else {
    _out->roue = v_39;
  };;
}

void Control__controller_reset(Control__controller_mem* self) {
  Control__nouvelle_etape_reset(&self->nouvelle_etape);
  Control__correction_left_reset(&self->correction_left);
  Control__correction_right_reset(&self->correction_right);
  self->v_58 = 0.000000;
  self->a_tourner_1 = false;
  self->v_right_1 = 0.000000;
  self->v_left_1 = 0.000000;
  self->rspeed_1.right = 0.000000;
  self->rspeed_1.left = 0.000000;
  self->pnr = false;
  self->ck = Control__St_Go;
  self->v_46 = true;
  self->compteur_etape = 0;
}

void Control__controller_step(Globals__sensors sens, Globals__itielts iti,
                              Control__controller_out* _out,
                              Control__controller_mem* self) {
  Control__correction_vitesse_virage_out Control__correction_vitesse_virage_out_st;
  Control__feu_tricolore_out Control__feu_tricolore_out_st;
  Control__rotation_out Control__rotation_out_st;
  Control__nouvelle_etape_out Control__nouvelle_etape_out_st;
  Control__correction_left_out Control__correction_left_out_st;
  Control__correction_right_out Control__correction_right_out_st;
  Control__int_of_bool_out Control__int_of_bool_out_st;
  Control__vitesse_limit_out Control__vitesse_limit_out_st;
  
  int v_53;
  Control__st v_52;
  int v_51;
  int v_50;
  int v_57;
  Control__st v_56;
  int v_55;
  int v_54;
  int r_St_Stop;
  Control__st s_St_Stop;
  int r_St_Turn;
  Control__st s_St_Turn;
  int r_St_Go;
  Control__st s_St_Go;
  int v_65;
  int v_64;
  Globals__wheels v_63;
  float v_62;
  float v_61;
  int v_60;
  float v_59;
  float temps_rotation;
  float temps_total;
  Globals__wheels roue;
  Globals__wheels v_72;
  Globals__wheels v_71;
  int v_70;
  int v_69;
  int v_68;
  float v_67;
  float v_66;
  int r_2;
  int r_1;
  int nr_St_Stop;
  Control__st ns_St_Stop;
  int a_tourner_St_Stop;
  float v_right_St_Stop;
  float v_left_St_Stop;
  int arriving_St_Stop;
  Globals__wheels rspeed_St_Stop;
  int nr_St_Turn;
  Control__st ns_St_Turn;
  int a_tourner_St_Turn;
  float v_right_St_Turn;
  float v_left_St_Turn;
  int arriving_St_Turn;
  Globals__wheels rspeed_St_Turn;
  int nr_St_Go;
  Control__st ns_St_Go;
  int a_tourner_St_Go;
  float v_right_St_Go;
  float v_left_St_Go;
  int arriving_St_Go;
  Globals__wheels rspeed_St_Go;
  Control__st ck_1;
  float v_48;
  int v_47;
  int v_45;
  Globals__itielt v_44;
  int v_43;
  int v_42;
  int v_41;
  int v_40;
  int v;
  Control__st s;
  Control__st ns;
  int r;
  int nr;
  Globals__itielt itine;
  float v_left;
  float v_right;
  int a_tourner;
  float limit;
  v_45 = (self->compteur_etape%Globals__itinum);
  Control__int_of_bool_step(self->a_tourner_1, &Control__int_of_bool_out_st);
  v_42 = Control__int_of_bool_out_st.i;
  Control__nouvelle_etape_step(sens, self->a_tourner_1,
                               &Control__nouvelle_etape_out_st,
                               &self->nouvelle_etape);
  v = Control__nouvelle_etape_out_st.nouv;
  Control__int_of_bool_step(v, &Control__int_of_bool_out_st);
  v_40 = Control__int_of_bool_out_st.i;
  v_41 = (self->compteur_etape+v_40);
  v_43 = (v_41+v_42);
  switch (self->ck) {
    case Control__St_Stop:
      r_St_Stop = self->pnr;
      s_St_Stop = Control__St_Stop;
      break;
    default:
      break;
  };
  v_44.param = 0.000000;
  v_44.act = Globals__Go;
  if (((v_45<Globals__itinum)&&(0<=v_45))) {
    itine = iti[v_45];
  } else {
    itine = v_44;
  };
  if (self->v_46) {
    limit = itine.param;
  } else {
    limit = self->v_49;
  };
  v_47 = (itine.act==Globals__Go);
  if (v_47) {
    v_48 = itine.param;
  } else {
    v_48 = limit;
  };
  switch (self->ck) {
    case Control__St_Go:
      v_55 = (itine.act==Globals__Stop);
      if (v_55) {
        v_57 = true;
        v_56 = Control__St_Stop;
      } else {
        v_57 = self->pnr;
        v_56 = Control__St_Go;
      };
      v_54 = (itine.act==Globals__Turn);
      if (v_54) {
        r_St_Go = true;
        s_St_Go = Control__St_Turn;
      } else {
        r_St_Go = v_57;
        s_St_Go = v_56;
      };
      s = s_St_Go;
      r = r_St_Go;
      break;
    case Control__St_Turn:
      v_51 = (itine.act==Globals__Stop);
      if (v_51) {
        v_53 = true;
        v_52 = Control__St_Stop;
      } else {
        v_53 = self->pnr;
        v_52 = Control__St_Turn;
      };
      v_50 = (itine.act==Globals__Go);
      if (v_50) {
        r_St_Turn = true;
        s_St_Turn = Control__St_Go;
      } else {
        r_St_Turn = v_53;
        s_St_Turn = v_52;
      };
      s = s_St_Turn;
      r = r_St_Turn;
      break;
    case Control__St_Stop:
      s = s_St_Stop;
      r = r_St_Stop;
      break;
    default:
      break;
  };
  ck_1 = s;
  switch (ck_1) {
    case Control__St_Go:
      v_69 = (sens.s_sonar<1000);
      Control__feu_tricolore_step(sens, &Control__feu_tricolore_out_st);
      v_68 = Control__feu_tricolore_out_st.arret;
      v_70 = (v_68||v_69);
      a_tourner_St_Go = false;
      arriving_St_Go = false;
      nr_St_Go = false;
      ns_St_Go = Control__St_Go;
      r_1 = r;
      if (r_1) {
        Control__correction_left_reset(&self->correction_left);
      };
      Control__correction_left_step(sens, limit,
                                    &Control__correction_left_out_st,
                                    &self->correction_left);
      v_66 = Control__correction_left_out_st.left;
      r_2 = r;
      if (r_2) {
        Control__correction_right_reset(&self->correction_right);
      };
      Control__correction_right_step(sens, limit,
                                     &Control__correction_right_out_st,
                                     &self->correction_right);
      v_67 = Control__correction_right_out_st.right;
      Control__correction_vitesse_virage_step(v_66, v_67,
                                              &Control__correction_vitesse_virage_out_st);
      v_left_St_Go = Control__correction_vitesse_virage_out_st.n_left;
      v_right_St_Go = Control__correction_vitesse_virage_out_st.n_right;
      _out->arriving = arriving_St_Go;
      v_left = v_left_St_Go;
      v_right = v_right_St_Go;
      a_tourner = a_tourner_St_Go;
      ns = ns_St_Go;
      nr = nr_St_Go;
      v_72.left = v_left;
      v_72.right = v_right;
      v_71.right = 0.000000;
      v_71.left = 0.000000;
      if (v_70) {
        rspeed_St_Go = v_71;
      } else {
        rspeed_St_Go = v_72;
      };
      _out->rspeed = rspeed_St_Go;
      break;
    case Control__St_Turn:
      v_right_St_Turn = self->v_right_1;
      v_left_St_Turn = self->v_left_1;
      v_64 = (self->a_tourner_1==false);
      Control__vitesse_limit_step(limit, &Control__vitesse_limit_out_st);
      v_62 = Control__vitesse_limit_out_st.vit;
      Control__vitesse_limit_step(limit, &Control__vitesse_limit_out_st);
      v_61 = Control__vitesse_limit_out_st.vit;
      if (r) {
        v_59 = 0.000000;
      } else {
        v_59 = self->v_58;
      };
      temps_rotation = (v_59+Globals__timestep);
      Control__rotation_step(itine.param, limit, &Control__rotation_out_st);
      temps_total = Control__rotation_out_st.temps_rotation;
      roue = Control__rotation_out_st.roue;
      v_65 = (temps_rotation>temps_total);
      a_tourner_St_Turn = (v_64&&v_65);
      v_60 = (temps_rotation<temps_total);
      arriving_St_Turn = false;
      nr_St_Turn = false;
      ns_St_Turn = Control__St_Turn;
      _out->arriving = arriving_St_Turn;
      v_left = v_left_St_Turn;
      v_right = v_right_St_Turn;
      a_tourner = a_tourner_St_Turn;
      ns = ns_St_Turn;
      nr = nr_St_Turn;
      v_63.left = v_61;
      v_63.right = v_62;
      if (v_60) {
        rspeed_St_Turn = roue;
      } else {
        rspeed_St_Turn = v_63;
      };
      _out->rspeed = rspeed_St_Turn;
      self->temps_rotation_2 = temps_rotation;
      self->v_58 = temps_rotation;
      break;
    case Control__St_Stop:
      a_tourner_St_Stop = self->a_tourner_1;
      v_right_St_Stop = self->v_right_1;
      v_left_St_Stop = self->v_left_1;
      rspeed_St_Stop = self->rspeed_1;
      arriving_St_Stop = true;
      nr_St_Stop = false;
      ns_St_Stop = Control__St_Stop;
      _out->arriving = arriving_St_Stop;
      v_left = v_left_St_Stop;
      v_right = v_right_St_Stop;
      a_tourner = a_tourner_St_Stop;
      ns = ns_St_Stop;
      nr = nr_St_Stop;
      _out->rspeed = rspeed_St_Stop;
      break;
    default:
      break;
  };
  self->a_tourner_1 = a_tourner;
  self->v_right_1 = v_right;
  self->v_left_1 = v_left;
  self->rspeed_1 = _out->rspeed;
  self->pnr = nr;
  self->ck = ns;
  self->v_49 = v_48;
  self->v_46 = false;
  self->compteur_etape = v_43;;
}

