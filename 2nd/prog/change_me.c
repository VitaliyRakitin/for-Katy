/*
 * Математический осцилятор
 */

#include "headers/my.h"


/* Исходные функции системы для осцилятора 
 * 
 
double  f1(struct vect v, double t){
	//t=t;
	return v.array[1];
}
double  f2(struct vect v, double t){
	//t=t;
	return -v.array[0];
}

*/ 

/* Мой вектор = {x , y , px , py , phi , a} */
/* Основные функции производных */
double f1(struct vect v, double t){
 	return v.array[1];
}
//dx
double f2(struct vect v, double t){
    return  v.array[3];//*(1 + ALPHA * t * t * t * t);
}
//y
double f3(struct vect v, double t){
    return v.array[5];
}
//dy
double f4(struct vect v, double t){
    return -v.array[2];
}
double f5(struct vect v, double t){
    return v.array[0];
}
double f6(struct vect v, double t){
    return 0;
}



/* Создание вектор-функции из имеющихся начальных функций */
void Create_Vect_func(double (*f[DIM]) (struct vect v, double t)){
f[0] = f1;
f[1] = f2;
f[2] = f3;
f[3] = f4;
f[4] = f5;
f[5] = f6;
}

/* Начальные условия */
int initials(struct vect *vect){
	init(vect,DIM);
	if ((vect->length <= 0)||(vect->array == NULL)) return -2;

	vect->array[0] = X_0;
	vect->array[1] = Y_0;
	vect->array[4] = PHI_0;

	vect->array[5] = -28;
	vect->array[3] = 13;

	vect->array[2] = 30;

	return 0;
}
