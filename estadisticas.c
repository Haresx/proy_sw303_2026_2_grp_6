#include <stdio.h>
#include <math.h>
#include "simulador.h"

/*
typedef struct{
    double tiempoActual;
    double posicionActual;
    double velocidadActual;
}Estado;
*/

void calcular_estadisticas (Estado *resultados, int total_pasos, double *x_max, double *t_estabilizacion){ 
    if(total_pasos <= 0){
        //No hay pasos que realizar, se devuelven ceros para no dejar variables sin inicializar
        *x_max = 0.0;
        *t_estabilizacion = 0.0;
        return;
    }
    double xmax=0.0; 

    //Hallando desplazamiento maximo
    for(int i=0; i< total_pasos; i++){
        if( xmax < fabs(resultados[i].posicionActual) ){
            xmax = fabs(resultados[i].posicionActual);
        }
    }
    *x_max = xmax;

    //Caso borde 
    if(*x_max == 0.0){ //El sistema nunca se movio
        *t_estabilizacion = 0.0;
        return;
    }

    //Hallando tiempo de estabilizacion

    //Se necesita la condicion del desplazamiento cruza o se mantiene debajo del 2% o 5% del valor maximo, se usara 5%
    double condicion = (0.05)*(*x_max);

    *t_estabilizacion = 0.0;
    for(int i=total_pasos-1; i>=0; i--){ //Del final hacia el inicio para detectar el ultimo valor estabilizado ya que al final ya esta estabilizado
        double pos_abs = fabs(resultados[i].posicionActual);

        if( pos_abs > condicion ){ //Se salio del margen de 5%
            if( i + 1 < total_pasos){ //Se toma la posicion que le sigue debido a que no llego al 5% de tolerancia
                *t_estabilizacion = resultados[i+1].tiempoActual;
            }
            else {  //Caso borde que sea el ultimo caso entonces al no existir (i+1) se toma el ultimo valor
                *t_estabilizacion = resultados[i].tiempoActual;
            }
            break;
        }
    }
}
