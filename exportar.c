#include <stdio.h>
#include "simulador.h"

/*
typedef struct{
    double tiempoActual;
    double posicionActual;
    double velocidadActual;
}Estado;

void calcular_estadisticas (Estado *resultados, int total_pasos, double *x_max, double *t_estabilizacion);
*/

int generar_csv (const char *nombre_archivo, Estado *resultados, int total_pasos){
    FILE *archivo;
    archivo = fopen(nombre_archivo, "w");

    if(archivo == NULL){
        printf("Error en crear el archivo resultados\n");
        return 0;
    }

    fprintf(archivo, "Tiempo,Posicion,Velocidad\n");

    for(int i=0; i<total_pasos; i++){
        fprintf(archivo, "%.4f,%.4f,%.4f\n", resultados[i].tiempoActual, resultados[i].posicionActual, resultados[i].velocidadActual);
    }
    fclose(archivo);
    return 1;

}