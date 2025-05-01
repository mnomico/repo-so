#include <stdio.h>
#include <stdlib.h>

#define TIEMPO_CONMUTACION 1.00

typedef struct Proceso {
    int PID;
    int tiempoServicio;
} proceso;

typedef struct Registro {
    int PID;
    double tiempoEspera;
    double tiempoRetorno;
} registro;

int compararProcesos(const void *a, const void *b) {
    const proceso *procesoA = (const proceso *)a;
    const proceso *procesoB = (const proceso *)b;
    
    return procesoA->tiempoServicio - procesoB->tiempoServicio;
}

registro* sjf(proceso *procesos, int cant_procesos, double reloj) {
    // qsort usa una funcion que le pasamos como parametro para ordenar
    // si la funcion devuelve un numero negativo, pone a 'a' primero en el array
    // si devuelve un numero positivo, pone a 'b' primero en el array
    qsort(procesos, cant_procesos, sizeof(proceso), compararProcesos);

    registro *registros = malloc(sizeof(registro) * cant_procesos);

    for (int i = 0; i < cant_procesos; i++) {
        // Ingresa un proceso
        reloj += TIEMPO_CONMUTACION / 2;

        // Se ejecuta el proceso
        reloj += procesos[i].tiempoServicio;

        // Se guarda el tiempo de espera y de retorno del proceso ejecutado
        registros[i].PID = procesos[i].PID;
        registros[i].tiempoEspera = reloj - procesos[i].tiempoServicio;
        registros[i].tiempoRetorno = reloj;

        // Se desaloja el proceso
        reloj += TIEMPO_CONMUTACION / 2;
    }

    return registros;
}

int main(int argc, char **argv) {
    // argc devuelve la cantidad de argumentos
    // por ejemplo si en la terminal ingreso ./programa 1 2 3:
    // argc = 4 (cuenta tambien el nombre del programa)
    // argv es un array de char que contiene el resto de los argumentos
    // argv[] = ['1','2','3']
    int cant_procesos = argc - 1;
    proceso *procesos = malloc(sizeof(proceso) * cant_procesos);
    for (int i = 0; i < cant_procesos; i++){
        procesos[i].PID = i;
        procesos[i].tiempoServicio = atoi(argv[i]); 
    }

    double reloj = 0;
    registro *registros = sjf(procesos, cant_procesos, reloj);

    // Calculo los tiempos medios de espera y de retorno
    double tiempoMedioEspera = 0;
    double tiempoMedioRetorno = 0;
    for (int i = 0; i < cant_procesos; i++) {
        tiempoMedioEspera += registros[i].tiempoEspera;
        tiempoMedioRetorno += registros[i].tiempoRetorno;
    }
    tiempoMedioEspera = tiempoMedioEspera / cant_procesos;
    tiempoMedioRetorno = tiempoMedioRetorno / cant_procesos;

    printf("Tiempo medio espera = %f\n", tiempoMedioEspera);
    printf("Tiempo medio retorno = %f\n", tiempoMedioRetorno);
}