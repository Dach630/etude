/* --- Generated the 28/11/2023 at 13:4 --- */
/* --- heptagon compiler, version 1.05.00 (compiled tue. oct. 3 15:20:46 CET 2023) --- */
/* --- Command line: /home/chengd/.opam/ocaml-variants/bin/heptc -c -target c utilities.ept --- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utilities.h"

void Utilities__min_float_step(float a, float b,
                               Utilities__min_float_out* _out) {
  
  int v;
  v = (a<b);
  if (v) {
    _out->o = a;
  } else {
    _out->o = b;
  };;
}

void Utilities__min_int_step(int a, int b, Utilities__min_int_out* _out) {
  
  int v;
  v = (a<b);
  if (v) {
    _out->o = a;
  } else {
    _out->o = b;
  };;
}

void Utilities__max_float_step(float a, float b,
                               Utilities__max_float_out* _out) {
  
  int v;
  v = (a<b);
  if (v) {
    _out->o = b;
  } else {
    _out->o = a;
  };;
}

void Utilities__max_int_step(int a, int b, Utilities__max_int_out* _out) {
  
  int v;
  v = (a<b);
  if (v) {
    _out->o = b;
  } else {
    _out->o = a;
  };;
}

void Utilities__countdown_reset(Utilities__countdown_mem* self) {
  self->v = true;
}

void Utilities__countdown_step(int e, int ini,
                               Utilities__countdown_out* _out,
                               Utilities__countdown_mem* self) {
  
  int v_2;
  int mem;
  if (e) {
    v_2 = 1;
  } else {
    v_2 = 0;
  };
  if (self->v) {
    mem = ini;
  } else {
    mem = self->v_1;
  };
  _out->o = (mem-v_2);
  self->v_1 = _out->o;
  self->v = false;;
}

void Utilities__angle_dist_step(Globals__position from, Globals__position to,
                                Utilities__angle_dist_out* _out) {
  Mathext__atan2_out Mathext__atan2_out_st;
  Mathext__hypot_out Mathext__hypot_out_st;
  
  float v_7;
  float v_6;
  float v_5;
  float v_4;
  float v_3;
  float v;
  v_5 = (to.x-from.x);
  v_4 = (to.y-from.y);
  Mathext__atan2_step(v_4, v_5, &Mathext__atan2_out_st);
  v_6 = Mathext__atan2_out_st.o;
  v_7 = (v_6*180.000000);
  _out->angle = (v_7/Globals__pi);
  v_3 = (to.y-from.y);
  v = (to.x-from.x);
  Mathext__hypot_step(v, v_3, &Mathext__hypot_out_st);
  _out->dist = Mathext__hypot_out_st.o;;
}

void Utilities__bound_step(float x, float ceiling, Utilities__bound_out* _out) {
  
  float v_11;
  int v_10;
  float v_9;
  int v_8;
  float v;
  v_10 = (x>ceiling);
  if (v_10) {
    v_11 = ceiling;
  } else {
    v_11 = x;
  };
  v_9 = -(ceiling);
  v = -(ceiling);
  v_8 = (x<v);
  if (v_8) {
    _out->o = v_9;
  } else {
    _out->o = v_11;
  };;
}

void Utilities__norm_color_step(Globals__color a,
                                Utilities__norm_color_out* _out) {
  Mathext__float_out Mathext__float_out_st;
  Mathext__sqrt_out Mathext__sqrt_out_st;
  
  float v_21;
  float v_20;
  float v_19;
  float v_18;
  float v_17;
  float v_16;
  float v_15;
  float v_14;
  float v_13;
  float v_12;
  float v;
  Mathext__float_step(a.blue, &Mathext__float_out_st);
  v_19 = Mathext__float_out_st.o;
  Mathext__float_step(a.blue, &Mathext__float_out_st);
  v_18 = Mathext__float_out_st.o;
  v_20 = (v_18*v_19);
  Mathext__float_step(a.green, &Mathext__float_out_st);
  v_15 = Mathext__float_out_st.o;
  Mathext__float_step(a.green, &Mathext__float_out_st);
  v_14 = Mathext__float_out_st.o;
  v_16 = (v_14*v_15);
  Mathext__float_step(a.red, &Mathext__float_out_st);
  v_12 = Mathext__float_out_st.o;
  Mathext__float_step(a.red, &Mathext__float_out_st);
  v = Mathext__float_out_st.o;
  v_13 = (v*v_12);
  v_17 = (v_13+v_16);
  v_21 = (v_17+v_20);
  Mathext__sqrt_step(v_21, &Mathext__sqrt_out_st);
  _out->norm = Mathext__sqrt_out_st.o;;
}

void Utilities__compare_colors_step(Globals__color a, Globals__color b,
                                    Utilities__compare_colors_out* _out) {
  Utilities__norm_color_out Utilities__norm_color_out_st;
  Mathext__float_out Mathext__float_out_st;
  
  float v_34;
  float v_33;
  float v_32;
  float v_31;
  float v_30;
  float v_29;
  float v_28;
  float v_27;
  float v_26;
  float v_25;
  float v_24;
  float v_23;
  float v_22;
  float v;
  Utilities__norm_color_step(b, &Utilities__norm_color_out_st);
  v_33 = Utilities__norm_color_out_st.norm;
  Utilities__norm_color_step(a, &Utilities__norm_color_out_st);
  v_32 = Utilities__norm_color_out_st.norm;
  v_34 = (v_32*v_33);
  Mathext__float_step(b.blue, &Mathext__float_out_st);
  v_29 = Mathext__float_out_st.o;
  Mathext__float_step(a.blue, &Mathext__float_out_st);
  v_28 = Mathext__float_out_st.o;
  v_30 = (v_28*v_29);
  Mathext__float_step(b.green, &Mathext__float_out_st);
  v_25 = Mathext__float_out_st.o;
  Mathext__float_step(b.red, &Mathext__float_out_st);
  v_22 = Mathext__float_out_st.o;
  Mathext__float_step(a.green, &Mathext__float_out_st);
  v_24 = Mathext__float_out_st.o;
  Mathext__float_step(a.red, &Mathext__float_out_st);
  v = Mathext__float_out_st.o;
  v_26 = (v_24*v_25);
  v_23 = (v*v_22);
  v_27 = (v_23+v_26);
  v_31 = (v_27+v_30);
  _out->correlation = (v_31/v_34);;
}

void Utilities__decode_color_step(Globals__color a,
                                  Utilities__decode_color_out* _out) {
  Utilities__compare_colors_out Utilities__compare_colors_out_st;
  
  Globals__colorQ v_38;
  Globals__colorQ v_37;
  int v_36;
  int v_35;
  int v;
  float rr;
  float gg;
  float aa;
  Utilities__compare_colors_step(a, Globals__amber,
                                 &Utilities__compare_colors_out_st);
  aa = Utilities__compare_colors_out_st.correlation;
  v_36 = (aa>0.850000);
  if (v_36) {
    v_37 = Globals__Amber;
  } else {
    v_37 = Globals__Other;
  };
  Utilities__compare_colors_step(a, Globals__green,
                                 &Utilities__compare_colors_out_st);
  gg = Utilities__compare_colors_out_st.correlation;
  Utilities__compare_colors_step(a, Globals__red,
                                 &Utilities__compare_colors_out_st);
  rr = Utilities__compare_colors_out_st.correlation;
  v_35 = (gg>0.850000);
  if (v_35) {
    v_38 = Globals__Green;
  } else {
    v_38 = v_37;
  };
  v = (rr>0.850000);
  if (v) {
    _out->q = Globals__Red;
  } else {
    _out->q = v_38;
  };;
}

void Utilities__encode_color_step(Globals__colorQ q,
                                  Utilities__encode_color_out* _out) {
  switch (q) {
    case Globals__Red:
      _out->a.blue = 0;
      _out->a.green = 0;
      _out->a.red = 255;
      break;
    case Globals__Green:
      _out->a.blue = 0;
      _out->a.green = 255;
      _out->a.red = 0;
      break;
    case Globals__Amber:
      _out->a.blue = 0;
      _out->a.green = 191;
      _out->a.red = 255;
      break;
    case Globals__Other:
      _out->a.blue = 128;
      _out->a.green = 128;
      _out->a.red = 128;
      break;
    default:
      break;
  };
}

void Utilities__rising_edge_reset(Utilities__rising_edge_mem* self) {
  self->v_39 = false;
}

void Utilities__rising_edge_step(int b, Utilities__rising_edge_out* _out,
                                 Utilities__rising_edge_mem* self) {
  
  int v;
  _out->e = (b&&self->v_39);
  v = !(b);
  self->v_39 = v;;
}

void Utilities__falling_edge_reset(Utilities__falling_edge_mem* self) {
  Utilities__rising_edge_reset(&self->rising_edge);
  self->v = true;
}

void Utilities__falling_edge_step(int b, Utilities__falling_edge_out* _out,
                                  Utilities__falling_edge_mem* self) {
  Utilities__rising_edge_out Utilities__rising_edge_out_st;
  
  int v_41;
  int v_40;
  v_40 = !(b);
  Utilities__rising_edge_step(v_40, &Utilities__rising_edge_out_st,
                              &self->rising_edge);
  v_41 = Utilities__rising_edge_out_st.e;
  if (self->v) {
    _out->e = false;
  } else {
    _out->e = v_41;
  };
  self->v = false;;
}

void Utilities__after_reset(Utilities__after_mem* self) {
  self->v = true;
}

void Utilities__after_step(int ini, Utilities__after_out* _out,
                           Utilities__after_mem* self) {
  
  int v_43;
  int v_42;
  int n;
  if (self->v) {
    n = ini;
  } else {
    n = self->v_44;
  };
  _out->o = (n==0);
  v_42 = (n-1);
  if (_out->o) {
    v_43 = n;
  } else {
    v_43 = v_42;
  };
  self->v_44 = v_43;
  self->v = false;;
}

void Utilities__event_edge_reset(Utilities__event_edge_mem* self) {
  Utilities__rising_edge_reset(&self->rising_edge_4);
  Utilities__rising_edge_reset(&self->rising_edge_3);
  Utilities__rising_edge_reset(&self->rising_edge_2);
  Utilities__rising_edge_reset(&self->rising_edge_1);
  Utilities__rising_edge_reset(&self->rising_edge);
}

void Utilities__event_edge_step(Globals__event e,
                                Utilities__event_edge_out* _out,
                                Utilities__event_edge_mem* self) {
  Utilities__rising_edge_out Utilities__rising_edge_out_st;
  
  int v_48;
  int v_47;
  int v_46;
  int v_45;
  int v;
  Utilities__rising_edge_step(e.dirEvent, &Utilities__rising_edge_out_st,
                              &self->rising_edge_4);
  v_48 = Utilities__rising_edge_out_st.e;
  Utilities__rising_edge_step(e.collisionEvent,
                              &Utilities__rising_edge_out_st,
                              &self->rising_edge_3);
  v_47 = Utilities__rising_edge_out_st.e;
  Utilities__rising_edge_step(e.exitRoad, &Utilities__rising_edge_out_st,
                              &self->rising_edge_2);
  v_46 = Utilities__rising_edge_out_st.e;
  Utilities__rising_edge_step(e.speedExcess, &Utilities__rising_edge_out_st,
                              &self->rising_edge_1);
  v_45 = Utilities__rising_edge_out_st.e;
  Utilities__rising_edge_step(e.lightRun, &Utilities__rising_edge_out_st,
                              &self->rising_edge);
  v = Utilities__rising_edge_out_st.e;
  _out->o.lightRun = v;
  _out->o.speedExcess = v_45;
  _out->o.exitRoad = v_46;
  _out->o.collisionEvent = v_47;
  _out->o.dirEvent = v_48;;
}

void Utilities__integrator_reset(Utilities__integrator_mem* self) {
  self->v = true;
}

void Utilities__integrator_step(float x, float step, float ini,
                                Utilities__integrator_out* _out,
                                Utilities__integrator_mem* self) {
  
  float v_56;
  float v_55;
  float v_54;
  float v_53;
  float v_51;
  float v_50;
  float v_49;
  float s;
  v_55 = (step*x);
  v_56 = (v_55/2.000000);
  v_54 = (step*x);
  v_49 = (step*x);
  v_50 = (v_49/2.000000);
  v_51 = (ini-v_50);
  if (self->v) {
    v_53 = v_51;
  } else {
    v_53 = self->v_52;
  };
  s = (v_53+v_54);
  _out->o = (s-v_56);
  self->v_52 = s;
  self->v = false;;
}

void Utilities__integrator_en_reset(Utilities__integrator_en_mem* self) {
  Utilities__integrator_reset(&self->integrator);
  self->v = true;
}

void Utilities__integrator_en_step(float x, float step, float ini, int en,
                                   Utilities__integrator_en_out* _out,
                                   Utilities__integrator_en_mem* self) {
  Utilities__integrator_out Utilities__integrator_out_st;
  
  float v_58;
  float oi;
  if (en) {
    Utilities__integrator_step(x, step, ini, &Utilities__integrator_out_st,
                               &self->integrator);
    oi = Utilities__integrator_out_st.o;
    _out->o = oi;
  } else {
    if (self->v) {
      v_58 = ini;
    } else {
      v_58 = self->v_57;
    };
    _out->o = v_58;
    self->v = false;
  };
  self->v_57 = _out->o;;
}

void Utilities__derivative_reset(Utilities__derivative_mem* self) {
  self->v = 0.000000;
}

void Utilities__derivative_step(float x, float step,
                                Utilities__derivative_out* _out,
                                Utilities__derivative_mem* self) {
  
  float v_59;
  v_59 = (x-self->v);
  _out->y = (v_59/step);
  self->v = x;;
}

void Utilities__lowpass_reset(Utilities__lowpass_mem* self) {
  self->v_61 = 0.000000;
}

void Utilities__lowpass_step(float x, float a, Utilities__lowpass_out* _out,
                             Utilities__lowpass_mem* self) {
  
  float v_62;
  float v_60;
  float v;
  v_60 = (1.000000-a);
  v_62 = (v_60*self->v_61);
  v = (a*x);
  _out->y = (v+v_62);
  self->v_61 = _out->y;;
}

void Utilities__normalize_step(float angle, Utilities__normalize_out* _out) {
  Mathext__floor_out Mathext__floor_out_st;
  
  float v_65;
  float v_64;
  float v_63;
  float v;
  v = (angle+180.000000);
  v_63 = (v/360.000000);
  Mathext__floor_step(v_63, &Mathext__floor_out_st);
  v_64 = Mathext__floor_out_st.o;
  v_65 = (360.000000*v_64);
  _out->normal = (angle-v_65);;
}

void Utilities__pos2vec_step(Globals__position pos,
                             Utilities__pos2vec_out* _out) {
  _out->vec[0] = pos.x;
  _out->vec[1] = pos.y;
}

void Utilities__vec2pos_step(float vec[2], Utilities__vec2pos_out* _out) {
  
  float v_66;
  float v;
  v_66 = vec[1];
  v = vec[0];
  _out->pos.x = v;
  _out->pos.y = v_66;;
}

void Utilities__mat_rot_step(float alpha, Utilities__mat_rot_out* _out) {
  Mathext__cos_out Mathext__cos_out_st;
  Mathext__sin_out Mathext__sin_out_st;
  
  float v_71[2];
  float v_70;
  float v_69[2];
  float v_68;
  float v_67;
  float v;
  float si;
  float co;
  v_67 = (alpha*0.017453);
  Mathext__cos_step(v_67, &Mathext__cos_out_st);
  co = Mathext__cos_out_st.o;
  v = (alpha*0.017453);
  Mathext__sin_step(v, &Mathext__sin_out_st);
  si = Mathext__sin_out_st.o;
  v_70 = -(si);
  v_68 = -(si);
  v_71[0] = v_70;
  v_71[1] = co;
  v_69[0] = co;
  v_69[1] = v_68;
  {
    int _1;
    for (_1 = 0; _1 < 2; ++_1) {
      _out->res[0][_1] = v_69[_1];
    }
  };
  {
    int _2;
    for (_2 = 0; _2 < 2; ++_2) {
      _out->res[1][_2] = v_71[_2];
    }
  };;
}

void Utilities__vec_add_params_2__step(float v1[2], float v2[2],
                                       Utilities__vec_add_params_2__out* _out) {
  {
    int i;
    for (i = 0; i < 2; ++i) {
      _out->o[i] = (v1[i]+v2[i]);
    }
  };
}

void Utilities__vec_prod_params_2__step(float v1[2], float v2[2],
                                        Utilities__vec_prod_params_2__out* _out) {
  {
    int i;
    for (i = 0; i < 2; ++i) {
      _out->o[i] = (v1[i]*v2[i]);
    }
  };
}

void Utilities__dotp_params_2__step(float v1[2], float v2[2],
                                    Utilities__dotp_params_2__out* _out) {
  Utilities__vec_prod_params_2__out Utilities__vec_prod_params_2__out_st;
  
  float v[2];
  Utilities__vec_prod_params_2__step(v1, v2,
                                     &Utilities__vec_prod_params_2__out_st);
  {
    int _3;
    for (_3 = 0; _3 < 2; ++_3) {
      v[_3] = Utilities__vec_prod_params_2__out_st.o[_3];
    }
  };
  _out->o = 0.000000;
  {
    int i;
    for (i = 0; i < 2; ++i) {
      _out->o = (v[i]+_out->o);
    }
  };;
}

void Utilities__mat_vec_prod_params_2__step(float mat[2][2], float vec[2],
                                            Utilities__mat_vec_prod_params_2__out* _out) {
  Utilities__dotp_params_2__out Utilities__dotp_params_2__out_st;
  
  float v[2][2];
  {
    int i_1;
    for (i_1 = 0; i_1 < 2; ++i_1) {
      {
        int _4;
        for (_4 = 0; _4 < 2; ++_4) {
          v[i_1][_4] = vec[_4];
        }
      };
    }
  };
  {
    int i;
    for (i = 0; i < 2; ++i) {
      Utilities__dotp_params_2__step(mat[i], v[i],
                                     &Utilities__dotp_params_2__out_st);
      _out->o[i] = Utilities__dotp_params_2__out_st.o;
    }
  };;
}

void Utilities__vec_add2_step(float v1[2], float v2[2],
                              Utilities__vec_add2_out* _out) {
  Utilities__vec_add_params_2__out Utilities__vec_add_params_2__out_st;
  Utilities__vec_add_params_2__step(v1, v2,
                                    &Utilities__vec_add_params_2__out_st);
  {
    int _5;
    for (_5 = 0; _5 < 2; ++_5) {
      _out->o[_5] = Utilities__vec_add_params_2__out_st.o[_5];
    }
  };
}

void Utilities__mat_vec_prod2_step(float mat[2][2], float vec[2],
                                   Utilities__mat_vec_prod2_out* _out) {
  Utilities__mat_vec_prod_params_2__out Utilities__mat_vec_prod_params_2__out_st;
  Utilities__mat_vec_prod_params_2__step(mat, vec,
                                         &Utilities__mat_vec_prod_params_2__out_st);
  {
    int _6;
    for (_6 = 0; _6 < 2; ++_6) {
      _out->o[_6] = Utilities__mat_vec_prod_params_2__out_st.o[_6];
    }
  };
}

void Utilities__abs_step(float x, Utilities__abs_out* _out) {
  
  float v_72;
  int v;
  v_72 = -(x);
  v = (x<0.000000);
  if (v) {
    _out->o = v_72;
  } else {
    _out->o = x;
  };;
}

void Utilities__uptime_reset(Utilities__uptime_mem* self) {
  Utilities__integrator_reset(&self->integrator);
}

void Utilities__uptime_step(float x, float step, Utilities__uptime_out* _out,
                            Utilities__uptime_mem* self) {
  Utilities__integrator_out Utilities__integrator_out_st;
  Utilities__abs_out Utilities__abs_out_st;
  
  float v_74;
  int v_73;
  float v;
  Utilities__abs_step(x, &Utilities__abs_out_st);
  v = Utilities__abs_out_st.o;
  v_73 = (v>=1.000000);
  if (v_73) {
    v_74 = 1.000000;
  } else {
    v_74 = 0.000000;
  };
  Utilities__integrator_step(v_74, step, 0.000000,
                             &Utilities__integrator_out_st, &self->integrator);
  _out->t = Utilities__integrator_out_st.o;;
}

void Utilities__variation_reset(Utilities__variation_mem* self) {
  Utilities__integrator_en_reset(&self->integrator_en);
  self->v = 0.000000;
}

void Utilities__variation_step(int enabled, float x, float step,
                               Utilities__variation_out* _out,
                               Utilities__variation_mem* self) {
  Utilities__normalize_out Utilities__normalize_out_st;
  Utilities__integrator_en_out Utilities__integrator_en_out_st;
  Utilities__abs_out Utilities__abs_out_st;
  
  float v_78;
  float v_77;
  float v_76;
  float v_75;
  v_75 = (x-self->v);
  Utilities__normalize_step(v_75, &Utilities__normalize_out_st);
  v_76 = Utilities__normalize_out_st.normal;
  v_77 = (v_76/step);
  Utilities__abs_step(v_77, &Utilities__abs_out_st);
  v_78 = Utilities__abs_out_st.o;
  Utilities__integrator_en_step(v_78, step, 0.000000, enabled,
                                &Utilities__integrator_en_out_st,
                                &self->integrator_en);
  _out->o = Utilities__integrator_en_out_st.o;
  self->v = x;;
}

