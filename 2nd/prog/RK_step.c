/* 
 * Подсчёт коеффициентов Рунге.
 */
#include "headers/my.h"

void runge_step(double h,struct vect v, double t,double (*f[])(struct  vect,double), struct vect b[RK_NUM],struct vect a, struct vect K[DIM]){

/* Создадим новый вектор new_v,
 * куда будут записаны "добавки" к координатам в функциях  */
  struct vect new_v;
  init(&new_v,DIM); 

/* пойдём по всем числам от 0 до RK_NUM (количество чисел Рунге) */
  for (int i = 0; i < RK_NUM; i++){
    /* задаём new_v */
    for (int k = 0; k < DIM; k++)
       new_v.array[k] = scalar(K[k],b[i]);   
        
    /* считаем числа Рунге */
    for (int j = 0; j < DIM; j++)
      K[j].array[i] =h * f[j](sum(v,new_v),t + h * a.array[i] );
  }
}