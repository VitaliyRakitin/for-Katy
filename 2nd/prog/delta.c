/* 
 * Подсчёт дельта-погрешности 
 **/

#include "headers/my.h"

/* Осцилятор */
double delta(double t){
return 0;
}

/* Для задачи 33 */
double delta33(double t){
	double err1, err2, err3;
	double err=0.0;

	/* A = 1 - at^4 */
	double A = 1 - ALPHA * t * t * t * t; 
	
	err1 = 3.0 * absolute(1.0 - A * A/2.0); 
	err2 = pow(3.0/8.0 * A * A + 3.0/4. ,1.0/2.0);
	err3 = pow(3.0/64.0 * A * A, 1.0/3.0);
	
	err = maximum(maximum(err1,err2),err3);

	return err;
}

/* модуль */
double absolute(double a){
	if (a > 0.0) return a;
	return -a;
}

/* функция максимума */
double maximum(double a, double b){
	if (a > b) return a;
	return b;
}