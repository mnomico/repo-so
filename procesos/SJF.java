import java.util.Arrays;

public class SJF {

    public final static double tiempo_conmutacion = 1;

    public static class Proceso {
        int PID;
        double tiempoServicio;

        public Proceso(int PID, double tiempoServicio) {
            this.PID = PID;
            this.tiempoServicio = tiempoServicio;
        }
    }

    public static class Registro {
        int PID;
        double tiempoEspera;
        double tiempoRetorno;

        public Registro(int PID, double tiempoEspera, double tiempoRetorno) {
            this.PID = PID;
            this.tiempoEspera = tiempoEspera;
            this.tiempoRetorno = tiempoRetorno;
        }
    }

    public static Registro[] sjf(Proceso procesos[], double reloj) {
        Registro[] registros = new Registro[procesos.length];
        Arrays.sort(procesos, (a,b) -> (int) (a.tiempoServicio - b.tiempoServicio));

        for (int i = 0; i < procesos.length; i++) {
            // Ingresa un proceso
            reloj += tiempo_conmutacion / 2;

            // Se ejecuta el proceso
            reloj += procesos[i].tiempoServicio;

            // Se guarda el tiempo de espera y de retorno del proceso
            int PID = procesos[i].PID;
            double tiempoEspera = reloj - procesos[i].tiempoServicio;
            double tiempoRetorno = reloj;
            registros[i] = new Registro(PID, tiempoEspera, tiempoRetorno);

            // Se desaloja el proceso
            reloj += tiempo_conmutacion / 2;
        }
        return registros;
    }

    public static void main(String[] args) {
        int cantProcesos = args.length;
        Proceso[] procesos = new Proceso[cantProcesos];
        for (int i = 0; i < args.length; i++) {
            procesos[i] = new Proceso(i, Integer.parseInt(args[i]));
        }
        double reloj = 0;
        Registro[] registros = sjf(procesos, reloj);
        double tiempoMedioEspera = 0;
        double tiempoMedioRetorno = 0;
        for (int i = 0; i < cantProcesos; i++) {
            tiempoMedioEspera += registros[i].tiempoEspera;
            tiempoMedioRetorno += registros[i].tiempoRetorno;
        }
        tiempoMedioEspera = tiempoMedioEspera / cantProcesos;
        tiempoMedioRetorno = tiempoMedioRetorno / cantProcesos;

        System.out.println("Tiempo medio espera: \n" + tiempoMedioEspera);
        System.out.println("Tiempo medio retorno: \n" + tiempoMedioRetorno);
    }

}
