
/*
 * Метод пристрелки Ньютона
 */

#include "headers/my.h"
int Newton(double eps, struct vect *v_init){

	/* Зададим вектор начальных значений */
	initials(v_init);

	/* зададим "вспомогательный" вектор координат
	 * дабы прогнать метод РК перый раз 
	 */
	struct vect v;
	init(&v,DIM);

	double err = runge(eps, *v_init, &v);
	/* зададим вектор невязок beta в виде массива */
	double beta[NUM_NV];
	for (int i=0;i<NUM_NV;i++) beta[i] = 0;	

	/* достанем из вектора координат параметры невязки */
	synchronization(beta, v);

	//	print(v);
	/* Основной цикл
	 * живём в цикле пока наши значения в точке 1 не совпадут с требуемыми,
	 * с точность eps.
	 */
	int counter = 0;
	while((absolute(beta[0] - ZERO_1) > EPPPS)||(absolute(beta[1] - ONE_1) > EPPPS)){
		err = shot(1e-7, v_init, beta);
		counter++;
		printf("%d itteration of the Newton's method is done!\n", counter);
	}

	printf("Done!\nBest initials are: ");
	print(*v_init);
	free(v.array);
	return 0;
}



int shot(double eps, struct vect *v_init, double beta[NUM_NV]){
	double err;
	/* derivative1 и derivative2 --- строки матрицы Якоби  
	 * то есть производные функций по alpha и по betta соответственно
	 */
	double derivative1[NUM_NV];
	double derivative2[NUM_NV];


	/* Посчитаем матрицу Якоби 
	 * Считаем сначала при одном отклонённом параметре
	 * потом на втором
	 */
	shot_step(eps, derivative1, 0, *v_init);
	shot_step(eps, derivative2, 1, *v_init);

	/* подсчёт определителя матрицы Якоби невязок */
	double det;
	det = derivative1[0]*derivative2[1] - derivative2[0]*derivative1[1];


	/* посчитаем результат интегрирования при двух отклонениях сразу РК */
	struct vect v_init_eps;
	init_copy(&v_init_eps, *v_init);
	init_plus_eps(2, &v_init_eps, eps);
	struct vect v;
	init(&v,DIM);
	err = runge(eps, v_init_eps, &v);

	/* создадим вектор-функцию невязок */
	double nvz[NUM_NV];
	Create_Vect_NVZ(nvz,v);
	
	/* пересчитаем новые начальные значения неизвестных параметров */
	v_init->array[UNKNOWN_1] += (derivative2[0] * nvz[1] - derivative2[1]*nvz[0])/det;
	v_init->array[UNKNOWN_2] -= (derivative1[0] * nvz[1] - derivative1[1]*nvz[0])/det;
	v_init->array[UNKNOWN_3] = - v_init->array[UNKNOWN_2];
	/* обновим beta для проверки условий цикла */
	synchronization(beta, v);

	/* освободим память */
	free(v_init_eps.array);
	free(v.array);
	return 0;
}


void shot_step(double eps, double derivative[NUM_NV], double param, struct vect v_init){
	double err;

	/* b --- значения в точке, db --- значения в точке + eps */
	double db[NUM_NV], b[NUM_NV];

	/* создадим 2 вспомогательных вектора для 2х прогонок метода РК */
	struct vect v, v_new;
	init(&v,DIM);
	init(&v_new, DIM);

	/* Сделаем новый вектор начальных условий + eps */
	struct vect v_init_eps;
	init_copy(&v_init_eps, v_init);
	init_plus_eps(param, &v_init_eps,eps);
	
	/* Прогонка метода РК */
	err = runge(eps, v_init, &v);
	err = runge(eps, v_init_eps, &v_new);

	/* вытаскиваем нужные координаты */
	synchronization(db, v_new);
	synchronization(b, v);

	/* считаем производные */
	count_derivative(eps,derivative,b,db);

	free(v.array);
	free(v_new.array);
	free(v_init_eps.array);
}


/* создаем точку с координатами престрелки + eps */
void init_plus_eps(int param, struct vect *v, double eps){
	if (param == 0) v->array[UNKNOWN_1] += eps;
	if (param == 1) v->array[UNKNOWN_2] += eps;
	if (param == 2){
		v->array[UNKNOWN_1] += eps; 
		v->array[UNKNOWN_2] += eps;
	}
}
/* считаем производную */
void count_derivative(double eps, double derivative[NUM_NV], double b[NUM_NV], double db[NUM_NV]){
	for (int i = 0;i < NUM_NV; i++){
		derivative[i] = (db[i] - b[i])/eps;
	}
}

/* выбираем нужные точки из вектора координат с позициями элементов невязок */
void synchronization(double a[NUM_NV], struct vect b){
	a[0] = b.array[ZERO];
	a[1] = b.array[ONE];
}

/*  невязок вектор сборка */
void Create_Vect_NVZ(double ideal[NUM_NV], struct vect v){
	ideal[0] = v.array[ZERO] - ZERO_1;
	ideal[1] = v.array[ONE] - ONE_1;
}