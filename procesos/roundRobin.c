#include <stdio.h>
#include <stdlib.h>

typedef struct Proceso {
    int PID;
    int tiempoServicio;
    int tiempoRestante;
} proceso;

typedef struct Registro {
    int PID;
    double tiempoEspera;
    double tiempoRetorno;
} registro;

// Función que calcula el tiempo de servicio restante total de los procesos.
int sumaTiemposServicio(proceso *procesos, int cantProcesos) {
    int suma = 0;
    for (int i = 0; i < cantProcesos; i++) {
        suma += procesos[i].tiempoRestante;
    }
    return suma;
}

registro* roundRobin(proceso *procesos, int cantProcesos, int quantum, double reloj, double tiempoConmutacion) {
    // Defino un procesoAnterior ya que es probable que se vuelva a dar el CPU a un proceso
    // que ya lo tuvo anteriormente. Eso más que nada es para evitar desalojar y alojar
    // un proceso repetidas veces cuando es el único en la cola de preparados.
    proceso *procesoAnterior = NULL;
    registro *registros = malloc(sizeof(registro) * cantProcesos);

    // Mientras haya procesos a ejecutar, se continúa con el algoritmo.
    while (sumaTiemposServicio(procesos, cantProcesos) > 0) {
        for (int i = 0; i < cantProcesos; i++) {

            // Si el proceso ya terminó su ejecución, se procede al siguiente en la cola.
            if (procesos[i].tiempoRestante == 0) {
                continue;
            }

            // Si el proceso es diferente al anterior, y tampoco es el primer proceso en ser
            // procesado, se desaloja
            if (&procesos[i] != procesoAnterior && procesoAnterior != NULL) {
                reloj += tiempoConmutacion / 2;
            }

            // Si el proceso es diferente al anterior, se le asigna el CPU.
            if (&procesos[i] != procesoAnterior) {
                reloj += tiempoConmutacion / 2;
            }

            // Si el tiempo de servicio restante es menor o igual que el quantum, se ejecuta por ese tiempo.
            if (procesos[i].tiempoRestante <= quantum) {
                reloj += procesos[i].tiempoRestante;
                procesos[i].tiempoRestante = 0;
                // Como terminó su ejecución, guardamos sus tiempos en el registro
                registros[i].PID = procesos[i].PID;
                registros[i].tiempoEspera = reloj - procesos[i].tiempoServicio;
                registros[i].tiempoRetorno = reloj;
            } else {
                // Si el tiempo de servicio restante es mayor que el quantum, se ejecuta por el quantum.
                reloj += quantum;
                procesos[i].tiempoRestante -= quantum;
            }

            procesoAnterior = &procesos[i];
        }
    }

    return registros;
}

int main(int argc, char **argv) {
    double reloj = 0;
    // Tomo argv[1] como el quantum.
    int quantum = atoi(argv[1]);
    // En la teoría, el tiempo de conmutación es la décima parte del quantum.
    double tiempoConmutacion = quantum / 10.0;
    // Tomo argc - 2 como la cantidad de procesos.
    // -2 porque no incluyo el nombre del programa ni tampoco el quantum.
    int cantProcesos = argc - 2;
    proceso *procesos = malloc(sizeof(proceso) * cantProcesos);
    for (int i = 0; i < cantProcesos; i++) {
        procesos[i].PID = i;
        procesos[i].tiempoServicio = atoi(argv[i + 2]);
        procesos[i].tiempoRestante = procesos[i].tiempoServicio;
    }
    registro *registros = roundRobin(procesos, cantProcesos, quantum, reloj, tiempoConmutacion);
    double tiempoMedioEspera = 0;
    double tiempoMedioRetorno = 0;
    for (int i = 0; i < cantProcesos; i++) {
        tiempoMedioEspera += registros[i].tiempoEspera;
        tiempoMedioRetorno += registros[i].tiempoRetorno;
    }
    tiempoMedioEspera = tiempoMedioEspera / cantProcesos;
    tiempoMedioRetorno = tiempoMedioRetorno / cantProcesos;
    printf("Tiempo medio espera: %f\n", tiempoMedioEspera);
    printf("Tiempo medio retorno: %f\n", tiempoMedioRetorno);
}