/*
 * В данном файле содержатся все изначальные функции и начальные условия
 * (всё то, что нужно изменять под конкретную задачу)
 */

 /* размерность пространства (количество уравнений и неизвестных) */
 #define DIM 6

 /* Время работы программы */ 
  #define WORK_TIME 1
 
/* Начальные условия */
 #define X_0 0.
 #define Y_0 1.
 #define PHI_0 0.

 #define ALPHA 0.1


/* Основные функции */ 
double  f1(struct vect v, double t);
double  f2(struct vect v, double t);
double  f3(struct vect v, double t);
double  f4(struct vect v, double t);
double  f5(struct vect v, double t);
double  f6(struct vect v, double t);



/*  Объеявления всех остальных функций */
void Create_Vect_func(double (*f[DIM]) (struct vect v, double t));
int initials(struct vect *v);