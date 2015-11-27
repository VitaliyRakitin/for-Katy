/*
 * Процедура автоматического выбора шага
 */

#include "headers/my.h"

double new_step(int c, double *varity, double EPS, double h, double t, struct vect v, struct vect k[DIM], 
                struct vect a, struct vect b[DIM], struct vect p, struct vect pp, 
                double (*f[])(struct  vect,double)){

    /* Посчитаем погрешность */
    double var = Variation(h, t, v, k, p, pp);
    
    /* расчётный коэффициент */
    double coef = 1.0/(POW + 1.0);
    
    /* живём в этом цикле, пока погрешность превышает допустимую точность */
    while (var > EPS){
        
        /* тут будем хранить новые значения чисел Рунге 
         * для обновлённого шага 
         */
        struct vect k_new[DIM];
        for (int i=0;i<DIM;i++) 
            init_copy(k_new + i, k[i]);

        /* Посчитаем новый шаг */
        h = h*min(max(FAC * pow(EPS/var,coef)));
        
        /* Пересчитаем числа Рунге */
        runge_step(h,v,t, f, b, a, k_new);
        
        /* Пересчитаем погрешность на новом шаге */
        var = Variation(h, t, v, k_new, p, pp);

        /* освобождаем память */
        for (int i=0;i<DIM;i++) free(k_new[i].array);
        if (h<H_DEFAULT) break;
    }


    /* НЕ НАДО ЭТУ СТРОЧКУ!!!!!!!!!!! */
    /* Это позволит шагу не стать слишком маленьким */
    if (c == 0) h = h*min(max(FAC * pow(EPS/var,coef)));
    *varity = var;
    return h;
}

double max(double variation){
    if (FACMIN >  variation) return FACMIN;
    return variation;
}

double min(double variation){
    if (FACMAX >  variation) return variation;
    return FACMAX;
}

/* Расчёт погрешности */
double Variation(double h, double t, struct vect v, struct vect k[DIM], struct vect p, struct vect pp){
    
    double dist;

    /* Создадим копии вектора координат, для подсчёта
     * предпологаемых точек попадания с точностью 5 и 6 порядка */
    struct vect v_1, v_2;
    init_copy(&v_2,v);
    init_copy(&v_1,v);

    /* посчитаем значения вектора координат в
    предпологаемых точках попадания с заданными точностями */
    new_parametrs(h,t,&v_1,k,p);
    new_parametrs(h,t,&v_2,k,pp);

    /* найдём расстояние между векторами */
    v_1 = minus(v_1,v_2);
    dist = norm_max(v_1);

    /* освободим память */
    free(v_1.array); free(v_2.array);
    return dist;
}
