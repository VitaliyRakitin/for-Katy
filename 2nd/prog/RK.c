/* 
 * Основная функция метода Рунге-Кутта
 */

#include "headers/my.h"
 
 double runge(double EPS, struct vect v_init,struct vect *v_out)
{
    struct vect v; // основной вектор координат
	struct vect k[DIM]; // числа Рунгe

    //*инициализация чисел Рунге */
	for (int i=0;i<DIM;i++)
    	init(k + i,RK_NUM);
    
    /* вводим начальные условия */
    init_copy(&v, v_init);
    
    /* Вектор функций и расчётные коэффициенты */
    double (*f[DIM]) (struct vect v, double t);
	struct vect a, p, pp; 
	struct vect b[RK_NUM];

	/* инициализация вектора функций и коэффициентов */
	Create_Vect_func(f); //
	RK_koeff(b,&a,&p,&pp);

    double var = 0.0; // погрешность
    double local_var = 0.0;

    double h = H_0; // шаг
    double t = 0; // время
	
    double errflag = 0;

        for (t = 0;t < WORK_TIME;t+=h){

        	/* обновим координаты  */
            new_parametrs(h,t,&v,k,p);
    
            /* обновляем шаг */
            h = new_step(1,&local_var, EPS,  h,  t,  v,  k,  a,  b,  p,  pp, f);
		
            /* пересчитаем delta-Погрешность */
            var = local_var + var * exp(delta33(t)*h);

            /* проверка последнего шага */
//            if (WORK_TIME - t < h) h = WORK_TIME - t;
			/* обновляем числа Рунге */ 
            runge_step(h,v,t, f, b, a, k);

            /* Проверка на случай особых точек */
            if (h<H_DEFAULT) {errflag = -3; break;} 
        }

//    printf("final step = %e;\n", h);

    /* v_init вернётся со значением конечной точки */
    copy(v, v_out);

    /* освобождаем память */
    free(a.array); free(p.array); free(pp.array); free(v.array); 
    for (int i=0;i< DIM;i++) free(b[i].array);

    return var;
}

/* функция обновления координат */
void new_parametrs(double h, double t, struct vect *v, struct vect k[DIM], struct vect p){
	for (int i = 0; i < DIM; i++){
		v->array[i] = v->array[i] + scalar(k[i],p);
	}
}