
/*
 * Функция Рунге-Кутта с выводом в файл 
 */

#include "headers/my.h"

double runge_out(double EPS, struct vect v_init,struct vect *v_out, const char*filename)
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

    FILE *file = fopen(filename, "w");

    if (file == NULL) errflag = -1;
    else{
        fprintf(file, "t \t x \t y \t px \t py \t phi \t a\n");

        for (t = 0;t<=WORK_TIME+h;t+=h){

        	/* обновим координаты  */
            new_parametrs(h,t,&v,k,p);
       	
            /* выведем новые параметры в файл */
    		fprintf(file, "%e", t);
            fprint(v,file);
            fprintf(file, "\n");
    
            /* обновляем шаг */
            h = new_step(0,&local_var, EPS,  h,  t,  v,  k,  a,  b,  p,  pp, f);
			
            /* пересчитаем delta-Погрешность */
            var = local_var + var * exp(delta(t)*h);

			/* обновляем числа Рунге */ 
            runge_step(h,v,t, f, b, a, k);

            /* Проверка на случай особых точек */
            if (h<H_DEFAULT) {errflag = -3; break;} 
        }
    }

    printf("final step = %e;\n", h);

    /* v_init вернётся со значением конечной точки */
    copy(v, v_out);

    /* освобождаем память */
    fclose(file);
    free(a.array); free(p.array); free(pp.array); free(v.array); 
    for (int i=0;i< DIM;i++) free(b[i].array);

    return var;
}
