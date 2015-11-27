
/* координаты вектора невязок */
#define ZERO 1
#define ONE  4

/* координаты неизвестных параметров */
#define UNKNOWN_1 3
#define UNKNOWN_2 5
#define UNKNOWN_3 2

/* конечные значения вектора невязок */
#define ZERO_1 0.
#define ONE_1 1.

/* точность */
#define EPPPS 1e-4

/* количество функций невязок */
#define NUM_NV 2 

/* Определения функция метода Ньютона */
int Newton(double eps, struct vect *v_init);
int shot(double eps, struct vect *v_init, double beta[NUM_NV]);
void shot_step(double eps, double derivative[NUM_NV], double param, struct vect v_init);
void count_derivative(double eps, double derivative[NUM_NV], double b[NUM_NV], double db[NUM_NV]);
void init_plus_eps(int param, struct vect *v, double eps);
void recount_beta(double eps, double beta[NUM_NV], double b[NUM_NV], double db[NUM_NV]);
void synchronization(double a[NUM_NV], struct vect b);
void Create_Vect_NVZ(double *, struct vect );