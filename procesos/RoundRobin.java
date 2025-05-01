public class RoundRobin {

    static class Proceso {
        int PID;
        int tiempoServicio;
        int tiempoRestante;

        public Proceso(int PID, int tiempoServicio) {
            this.PID = PID;
            this.tiempoServicio = tiempoServicio;
            this.tiempoRestante = tiempoServicio;
        }
    }

    static class Registro {
        int PID;
        double tiempoEspera;
        double tiempoRetorno;

        public Registro(int PID, double tiempoEspera, double tiempoRetorno) {
            this.PID = PID;
            this.tiempoEspera = tiempoEspera;
            this.tiempoRetorno = tiempoRetorno;
        }
    }

    // Método que calcula el tiempo de servicio restante total de los procesos.
    private static int sumaTiemposServicio(Proceso[] procesos) {
        int suma = 0;
        for (int i = 0; i < procesos.length; i++) {
            suma += procesos[i].tiempoRestante;
        }
        return suma;
    }


    public static Registro[] roundRobin(Proceso[] procesos, int quantum, double tiempoConmutacion) {
        Registro[] registros = new Registro[procesos.length];
        double reloj = 0;
        // Defino un procesoAnterior ya que es probable que se vuelva a dar el CPU a un proceso
        // que ya lo tuvo anteriormente. Eso más que nada es para evitar desalojar y alojar
        // un proceso repetidas veces cuando es el único en la cola de preparados.
        Proceso procesoAnterior = null;

        // Mientras haya procesos a ejecutar, se continúa con el algoritmo.
        while (sumaTiemposServicio(procesos) > 0) {
            for (int i = 0; i < procesos.length; i++) {
                Proceso actual = procesos[i];

                // Si el proceso ya terminó su ejecución, se procede al siguiente en la cola.
                if (actual.tiempoRestante == 0) {
                    continue;
                }

                // Si el proceso es diferente al anterior, y tampoco es el primer proceso en ser
                // procesado, se desaloja
                if (procesoAnterior != null && actual != procesoAnterior) {
                    reloj += tiempoConmutacion / 2;
                }

                // Si el proceso es diferente al anterior, se le asigna el CPU.
                if (actual != procesoAnterior) {
                    reloj += tiempoConmutacion / 2;
                }

                // Si el tiempo de servicio restante es menor o igual que el quantum, se ejecuta por ese tiempo.
                if (actual.tiempoRestante <= quantum) {
                    reloj += actual.tiempoRestante;
                    actual.tiempoRestante = 0;
                    // Como terminó su ejecución, guardamos sus tiempos en el registro
                    double tiempoEspera = reloj - actual.tiempoServicio;
                    double tiempoRetorno = reloj;
                    registros[i] = new Registro(procesos[i].PID, tiempoEspera, tiempoRetorno);
                } else {
                    // Si el tiempo de servicio restante es mayor que el quantum, se ejecuta por el quantum.
                    reloj += quantum;
                    actual.tiempoRestante -= quantum;
                }

                procesoAnterior = actual;
            }
        }

        return registros;
    }

    public static void main(String[] args) {
        // Tomo args[0] como el quantum.
        int quantum = Integer.parseInt(args[0]);
        // En la teoría, el tiempo de conmutación es la décima parte del quantum.
        double tiempoConmutacion = quantum / 10.0;
        // Tomo args.length - 1 como la cantidad de procesos.
        // -1 porque no incluyo el quantum.
        int cantProcesos = args.length - 1;
        Proceso[] procesos = new Proceso[cantProcesos];
        for (int i = 0; i < cantProcesos; i++) {
            procesos[i] = new Proceso(i, Integer.parseInt(args[i+1]));
        }
        Registro[] registros = roundRobin(procesos, quantum, tiempoConmutacion);
        double tiempoMedioEspera = 0;
        double tiempoMedioRetorno = 0;
        for (int i = 0; i < cantProcesos; i++) {
            tiempoMedioEspera += registros[i].tiempoEspera;
            tiempoMedioRetorno += registros[i].tiempoRetorno;
        }
        tiempoMedioEspera /= cantProcesos;
        tiempoMedioRetorno /= cantProcesos;
        System.out.printf("Tiempo medio espera: %.2f\n", tiempoMedioEspera);
        System.out.printf("Tiempo medio retorno: %.2f\n", tiempoMedioRetorno);
    }
}