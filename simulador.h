#ifndef SIMULADOR_H
#define SIMULADOR_H

typedef struct{
    double m;       //Masa
    double k;       //Rigidez del resorte
    double c;       //constante de amortiguamiento
    double x0;      //Posicion inicial
    double v0;      //Velocidad inicial
    double tMax;    //Tiempo maximo de la simulacion
    double dt;      //Diferencial del tiempo
    int tipoFuerza; //Constante, impulso y senoidal
}Parametros;

typedef struct{
    double tiempoActual;
    double posicionActual;
    double velocidadActual;
}Estado;

//Funciones
//Persona 1 (Leyton)
int leer_parametros (Parametros *p);             //Puntero para modificar directamente los valores
void clasificar_amortiguamiento (Parametros p)  //Sin puntero (procedimiento de lectura);

//Persona 2 (Ramiro)
double calcular_fuerza (double t, int tipo_fuerza)  //validar primero el tipo de fuerza (1,2 o 3)

//Persona 3 (Diego)
void calcular_estadisticas (Estado *resultados, int total_pasos, double *x_max, double *t_estabilizacion);
int generar_csv (const char *nombre_archivo, Estado *resultados, int total_pasos);  //gestor de archivos

//Persona 4 (Leonardo)
void runge_kutta4 (Parametros p, Estado *resultados, int *total_pasos);     //parte esencial de la parte matematica
#endif