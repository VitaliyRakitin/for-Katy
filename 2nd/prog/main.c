#include "headers/my.h"
#include <time.h>

void ErrCheck(int errflag);

int main(void){
    unsigned int start, finish;
    start = clock();
	double var = 0.0;
	
	struct vect v_init, v1,v2,v3;
	init(&v1,DIM);
	init(&v2,DIM);
	init(&v3,DIM);
	Newton(1e-11,&v_init);
	var = runge_out(1e-11, v_init, &v1, "out/out.csv");
	var = runge_out(1e-9, v_init, &v2,"out/out.csv");
	var = runge_out(1e-7, v_init, &v3,"out/out.csv");
	printf("The result vectors:\n" );
	print(v1);
	print(v2);
	print(v3);

	double R;
	for (int i=0;i<v1.length;i++){
		R = (v3.array[i]- v2.array[i])/(v2.array[i]-v1.array[i]);
		printf("R_%d = %e\n",i,R);
	}
	printf("Delta-Error:\t%e\n",var );
    finish = clock();
    printf("Work-time: %e sec.\n", (double)(finish-start)/CLOCKS_PER_SEC);
    free(v_init.array);
    free(v1.array);
    free(v2.array);
    free(v3.array);
	return 0;
}

void ErrCheck(int errflag){
	switch(errflag){
	case -1: {printf("Ошибка выделения памяти.\n"); break;}
	case -2: {printf("Неинициализированный вектор.\n"); break;}
	default: {printf("Другая ошибка.\n");break;}
	}
}