#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "RK_koeff.h"

/* Параметры метода РК */
#define RK_NUM 7
#define H_DEFAULT 1e-20
#define FAC 	0.9
#define FACMIN	0.3
#define FACMAX 	2
#define POW 	5.0

/* начальный шаг */
#define H_0 1e-4

#include "vect.h"
#include "change_me.h"
#include "delta.h"
#include "newton.h"

/* объявления функций метода Рунге-Кутта */
double runge(double EPS, struct vect v_init, struct vect *v_out);
double runge_out(double EPS, struct vect v_init,struct vect *v_out, const char*filename);
void RK_koeff(struct vect B[RK_NUM], struct vect *A, struct vect *P, struct  vect *PP);
void runge_step(double h,struct vect v, double t,double (*f[])(struct  vect,double), struct vect b[RK_NUM],struct vect a, struct vect K[DIM]);
double new_step(int, double *varity, double EPS, double h, double t, struct vect v, struct vect k[DIM], struct vect a, struct vect b[DIM], struct vect p, struct vect pp,double (*f[])(struct  vect,double));
double max(double variation);
double min(double variation);
double Variation(double h, double t, struct vect v, struct vect k[DIM], struct vect p, struct vect pp);
void new_parametrs(double h, double t, struct vect *v, struct vect k[DIM], struct vect p);
