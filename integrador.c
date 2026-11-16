#include "INTEGRADOR_H"
#include "FUERZA_EXTERNA_H" 

double calcular_aceleracion(double t, double x, double v, Parametros p) {
    
    double fuerza = calcular_fuerza(t, p); 
    return (fuerza - (p.c * v) - (p.k * x)) / p.m; //formula de la segunda derivada despejada(aceleracion)
}

void ejecutar_rk4(Parametros p, Estado *resultados, int *total_pasos) { 
    double t = 0.0; 
    double x = p.x0; 
    double v = p.v0; 
    double dt = p.dt; 
    
    int paso = 0;

    // Valores iniciales
    resultados[paso].t = t;
    resultados[paso].x = x;
    resultados[paso].v = v;

    paso++;

    //Como es una edo de segundo orden se usa una matriz posicion-velocidad
    while (t < p.t_max) { 
        
        double k1x = v;
        double k1v = calcular_aceleracion(t, x, v, p);

        double k2x = v + k1v * (dt / 2.0);
        double k2v = calcular_aceleracion(t + (dt / 2.0), x + k1x * (dt / 2.0), v + k1v * (dt / 2.0), p); 

        double k3x = v + k2v * (dt / 2.0);
        double k3v = calcular_aceleracion(t + (dt / 2.0), x + k2x * (dt / 2.0), v + k2v * (dt / 2.0), p); 


        double k4x = v + k3v * dt;
        double k4v = calcular_aceleracion(t + dt, x + k3x * dt, v + k3v * dt, p);


        x = x + (dt / 6.0) * (k1x + 2.0 * k2x + 2.0 * k3x + k4x);
        v = v + (dt / 6.0) * (k1v + 2.0 * k2v + 2.0 * k3v + k4v);
        t = t + dt; 

        //se guarda el estado en el arreglo de resultados(se usara en graficarlo mas tarde)
        resultados[paso].t = t;
        resultados[paso].x = x;
        resultados[paso].v = v;
        paso++;
    }

   
    *total_pasos = paso;
}