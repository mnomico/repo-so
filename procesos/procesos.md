## [Volver atrás](../readme.md)

# Planificación de Procesos

## Índice

- [Guía Teórica](#guía-teórica)

- [Conceptos](#conceptos)

- [Planificación FCFS](#planificación-fcfs)

- [Planificación SJF](#planificación-sjf)

- [Planificación Round Robin](#planificación-round-robin)

- [Ejercicios](#ejercicios)

- [Algoritmos](#algoritmos)

---

## Guía Teórica

1. Definir qué entiende por proceso y por recursos. ¿Cómo se identifica a un proceso en un sistema multiproceso?

Un proceso es un programa en ejecución, incluyendo el código ejecutable, los datos, el estado de ejecución y los recursos asignados. 

Los recursos son los elementos que el proceso necesita para hacer sus tareas. Incluyen CPU, memoria, archivos, dispositivos de entrada/salida, entre otros. 

En un sistema multiproceso, cada proceso se identifica con un Identificador de Proceso (PID), que es un número único asignado por el sistema operativo cuando el proceso es creado.

---

2. Describir los estados posibles de un proceso. Indicar en qué lugar físico se encuentran los procesos en los distintos estados.

- Nuevo: El proceso fue creado pero todavía no fue ejecutado.

Se encuentra en la memoria principal o en la cola de procesos nuevos.
- Listo: El proceso está esperando ser asignado a la CPU para ejecutarse.

Se encuentra en la cola de procesos listos.
- En ejecución: El proceso está siendo ejecutado por la CPU.

Sus instrucciones y datos están en la memoria principal, y su estado de ejecución está en los registros de la CPU.
- Bloqueado o en espera: El proceso está detenido temporalmente porque está esperando un recurso.

Permanece en la memoria principal, pero en la cola de procesos bloqueados.
- Terminado: El proceso terminó su ejecución y es el sistema.

---

3. ¿Qué tipo de recursos esperan los procesos que se encuentran en estado de preparado (listos) y de qué forma se pueden administrar? Justifique su respuesta.

Los procesos en estado listo están esperando ser ejecutados por la CPU, por lo que el recurso que necesitan es el procesador.
- Planificación por FIFO (First In, First Out): el primer proceso que entra en la cola de listos es el primero en ejecutarse. Simple de implementar, pero puede generar tiempos de espera largos para procesos cortos.
- Planificación por Prioridades: se asigna la CPU al proceso con mayor prioridad. Permite dar preferencia a procesos críticos, pero puede causar inanición de procesos con baja prioridad.
- Round Robin: se asigna la CPU a cada proceso por un período de tiempo fijo. Si el proceso no termina en ese tiempo, vuelve a la cola de listos.Justa y equitativa, evita monopolización del procesador.
- Shortest Job Next (SJN) o Shortest Remaining Time First (SRTF): se ejecuta el proceso más corto disponible. Minimiza el tiempo promedio de espera, pero requiere conocer la duración de los procesos.
- Multilevel Queue Scheduling: divide los procesos en varias colas con diferentes criterios de prioridad y planificación. Separa procesos de usuario y del sistema, permitiendo mejor administración del CPU.

---

4. ¿Qué tipo de recursos esperan los procesos que se encuentran en estado de espera y de qué forma se puede administrar su asignación al recurso? Justifique su respuesta.

Los procesos en estado de espera (bloqueado) no pueden continuar su ejecución porque están esperando la disponibilidad de algún recurso, como:
- Dispositivos de entrada/salida (E/S).
- Memoria.
- Acceso a archivos.
- Sincronización entre procesos.

La asignación de estos recursos puede realizarse mediante diferentes estrategias:
- Planificación de E/S: se usa un planificador de dispositivos para asignar solicitudes de entrada/salida. Optimiza el acceso a dispositivos de almacenamiento, reduciendo tiempos de espera.
- Gestión de Memoria: se asigna memoria mediante paginación, segmentación o particiones dinámicas. Evita fragmentación y maximiza la utilización de la memoria.
- Mecanismos de Sincronización: se usan semáforos, monitores o mutex para gestionar el acceso a recursos compartidos. Evita condiciones de carrera y asegura acceso seguro a recursos compartidos.
- Planificación de Acceso a Archivos: se implementan bloqueos para evitar accesos simultáneos no controlados. Mantiene la coherencia de los datos y evita corrupción de archivos.

---

5. ¿Cuál es el contenido del bloque de control de procesos? Justifique ¿por qué se emplea en un sistema multiproceso? ¿Dónde se encuentra físicamente, y quien maneja su actualización.

El PCB es una estructura de datos que almacena toda la información necesaria para gestionar un proceso dentro del sistema operativo. Sus principales campos incluyen:
- Identificación del proceso (PID).
- Estado del proceso.
- Registros de la CPU.
- Punteros.
- Archivos abiertos por el proceso y sus permisos.
- Dispositivos de entrada/salida asignados.
- Estado de operaciones de E/S en curso.
- Prioridad del proceso.
- Algoritmo de planificación usado.
- Tiempo de ejecución acumulado.

En un sistema multiproceso, múltiples procesos compiten por los recursos del sistema. El PCB permite:
- Mantener el control de cada proceso sin interferencias entre ellos.
- Permitir la conmutación de contexto.
- Facilitar la planificación y administración de procesos.

El PCB se encuentra en una tabla de procesos dentro del espacio de memoria del kernel. Su actualización es manejada por el sistema operativo cada vez que ocurre un cambio en el estado del proceso.

---

6. ¿Qué ventaja introduce el uso de un administrador de corto plazo? Indicar ¿cómo está compuesto?.

Su uso introduce varias ventajas en un sistema operativo multiproceso:
- Mejora la utilización de la CPU.
- Optimiza el tiempo de respuesta.
- Equilibra la carga del sistema.
- Permite la multitarea.
- Soporta diferentes políticas de planificación.

El planificador de corto plazo está compuesto por los siguientes elementos:
- Cola de procesos listos.
- Algoritmo de planificación.
- Mecanismo de selección.
- Conmutación de contexto.

---

7. ¿Qué es el proceso 0, y en qué se convierte una vez que el sistema arranca?

El proceso 0 es el primer proceso creado por el kernel cuando el sistema operativo arranca. Se ejecuta en modo kernel y es responsable de realizar la inicialización del sistema. También se le conoce como el proceso del sistema o proceso swapper.

Una vez que el sistema ha sido inicializado, el proceso 0 se convierte en:
- Proceso idle (inactivo): Se encarga de ejecutar un bucle de espera cuando no hay otros procesos en ejecución.
- Administrador de procesos: Se encarga de crear el proceso 1 (init), que es el ancestro de todos los demás procesos en sistemas Unix/Linux.

---

8. ¿Cómo se crean el proceso 1 y el proceso 2? ¿Qué funciones tienen cada uno dentro del sistema operativo?

Los procesos 1 y 2 son creados por el proceso 0 al iniciarse el sistema operativo.

El proceso 1 (init o systemd) se crea cuando el proceso 0 (swapper o idle) finaliza la inicialización del sistema y ejecuta un fork() seguido de un exec() para reemplazarse con init (en sistemas Unix tradicionales) o systemd (en muchas distribuciones Linux modernas).

El proceso 2 (kthreadd) se crea también por el proceso 0 y es responsable de gestionar los hilos del kernel.

Proceso 1 (init o systemd):
- Es el ancestro de todos los procesos de usuario en el sistema.
- Se encarga de iniciar los servicios del sistema (como demonios y procesos de arranque).
- Maneja el apagado y reinicio del sistema.
- En sistemas modernos, systemd reemplaza a init y gestiona los servicios de manera más eficiente.

Proceso 2 (kthreadd):
- Es el administrador de hilos del kernel.
- Crea y gestiona los procesos en segundo plano (threads del kernel).
- Es responsable de procesos esenciales como el manejo de E/S, paginación y administración de memoria.

---

9. ¿Qué ventaja introduce el uso de un administrador de largo plazo?

El planificador de largo plazo es el encargado de controlar el grado de multiprogramación.

Ventajas:
- Control de la carga del sistema.
- Optimización del rendimiento.
- Mejor uso de los recursos.
- Reducción del overhead (sobrecarga) del planificador de corto plazo.

---

10. Describir ¿cuál es la tarea del planificador de mediano plazo?

Su función principal es manejar la multiprogramación y optimizar el uso de los recursos del sistema mediante la carga y descarga de procesos en la memoria.

Si el sistema tiene demasiados procesos en ejecución, el planificador de mediano plazo decide suspender algunos procesos para liberar memoria, moviéndolos a la memoria secundaria (swap).

Si el sistema tiene demasiado poco trabajo en ejecución o cuando los procesos que están en memoria principal no pueden hacer nada, el planificador de mediano plazo recarga procesos suspendidos desde el disco a la memoria.

---

11. Definir tiempo de espera y tiempo de retorno de un proceso.

El tiempo de espera de un proceso es el tiempo transcurrido entre el momento en que un proceso llega a la cola de listos hasta que comienza a ser ejecutado por la CPU.

El tiempo de retorno de un proceso es el tiempo total en el que el proceso ha estado en el sistema, incluyendo tanto el tiempo de ejecución como el tiempo de espera.

---

12. ¿Qué se entiende por proceso demonio en un SO Unix, cuando son ejecutados, dónde se los declara y cómo se los da de baja del sistema? ¿Cuál son los demonios más comunes dentro del Unix, y qué utilidad brindan?

Un proceso demonio es un proceso en segundo plano. Realizan tareas sistemáticas y de mantenimiento. Son permanentes y se inician durante el arranque del sistema o por un proceso del sistema operativo. Los demonios suelen estar asociados con servicios o funcionalidades del sistema como la gestión de la red, impresión, correo electrónico, etc.

Los demonios pueden ser declarados en archivos de configuración de inicio, en scripts de inicio o por otro proceso.

Se los puede dar de baja mediante el comando kill pasándole como parámetro el PID del demonio.

Demonios más comunes en Unix y su utilidad:

| Demonio                       | Función                                                                                 |
| ----------------------------- | --------------------------------------------------------------------------------------- |
| `init` o `systemd`            | Proceso padre de todos los procesos de usuario, maneja el inicio y apagado del sistema. |
| `kthreadd`                    | Administrador de hilos del kernel.                                                      |
| `cron`                        | Ejecuta tareas programadas automáticamente según el archivo `crontab`.                  |
| `sshd`                        | Maneja conexiones SSH remotas.                                                          |
| `syslogd` o `journald`        | Administra registros de logs del sistema.                                               |
| `udevd`                       | Gestiona eventos de hardware y dispositivos conectados.                                 |
| `dbus-daemon`                 | Maneja la comunicación entre procesos en el sistema.                                    |
| `networkd` o `NetworkManager` | Administra la configuración y conectividad de red.                                      |

---

## Conceptos

### Tiempo de servicio

El ***tiempo de servicio*** es el tiempo total que un proceso necesita utilizar el CPU para completar su ejecución, sin contar los tiempos de espera.

### Tiempo de retorno

El ***tiempo de retorno*** es el tiempo total desde que un proceso se coloca en la cola de listos hasta que finaliza su ejecución. 
Se calcula de la siguiente manera:

> Tiempo de retorno = Tiempo de finalización − Tiempo de llegada

### Tiempo de espera

El ***tiempo de espera*** es el tiempo total que un proceso pasa esperando en la cola de listos antes de ser atendido por el CPU. 
Se calcula de la siguiente manera:

> Tiempo de espera = Tiempo de retorno − Tiempo de servicio

### Tiempo de conmutación (o cambio de contexto)

Cuando se selecciona un proceso de la cola de listos para asignarle el CPU, se debe llevar una serie de acciones para quitarle el CPU al proceso anterior, guardar el estado del proceso, y asignarle el CPU al proceso actual. 
Este tiempo se lo conoce como ***tiempo de conmutación*** o ***cambio de contexto***.

---

## Planificación FCFS

El algoritmo de planificación FCFS (first-come, first-served; primero en llegar, primero en ser servido), es el más simple, ya que le asigna el CPU al primer proceso de la cola de listos. 
La implementación se basa en el uso de una cola FIFO. Cuando un proceso entra en la cola de listos, su PCB (Process Control Block; bloque de control de proceso) se pone al final de la cola. 
Cuando la CPU se encuentra disponible, se lo asigna al primer proceso de la cola y éste es eliminado de la cola.

### Desventaja

El tiempo medio de espera del algoritmo FCFS es muy largo en comparación a los otros algoritmos de planificación.

### Ejemplo

Asumiendo que no hay tiempo de conmutación, y que todos los procesos ingresan en el momento 0:

| Proceso   | Tiempo de Servicio   |
|:----------|:---------------------|
| **P1**    | 24                   |
| **P2**    | 3                    |
| **P3**    | 3                    |

**Diagrama de Gantt**

| Tiempo  | 0| 1| 2| 3| 4| 5| 6| 7| 8| 9|10|11|12|13|14|15|16|17|18|19|20|21|22|23|24|25|26|27|28|29|
|:--------|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|
| **P1**  | █| █| █| █| █| █| █| █| █| █| █| █| █| █| █| █| █| █| █| █| █| █| █| █|  |  |  |  |  |  |
| **P2**  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | █| █| █|  |  |  |
| **P3**  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | █| █| █|

Proceso|Tiempo de espera|Tiempo de retorno
:-    |:-|:-
**P1**|0 |24
**P2**|24|27
**P3**|27|30

Tiempo medio de espera | Tiempo medio de retorno
:- | :-
17 | 27

---

## Planificación SJF

En el algoritmo de planificación SJF (shortest-job-first; primero el trabajo más corto), cuando el CPU está disponible, se lo asigna al proceso con el tiempo de servicio restante más corto. 

### Ventaja

El algoritmo SJF generalmente es el más óptimo, ya que el tiempo medio de espera es menor en comparación con otros algoritmos.

### Desventaja

El problema del algoritmo SJF es saber la duración del tiempo de servicio restante del siguiente proceso. Por este motivo, no se puede implementar en la práctica como un algoritmo de planificación a corto plazo.

Otro problema es el de inanición: si hay un proceso con un tiempo de servicio muy grande, y siempre entran a la cola de listos procesos más cortos que él, nunca va a poder ejecutarse.

### Ejemplo

Proceso | Tiempo de servicio
:- | :-
P1 | 6
P2 | 8
P3 | 7
P4 | 3

**Diagrama de Gantt**

| Tiempo | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |10|11|12|13|14|15|16|17|18|19|20|21|22|23|
|:-------|:--|:--|:--|:--|:--|:--|:--|:--|:--|:--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|
| P4     | █ | █ | █ |   |   |   |   |   |   |   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
| P1     |   |   |   | █ | █ | █ | █ | █ | █ |   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
| P3     |   |   |   |   |   |   |   |   |   | █ | █| █| █| █| █| █|  |  |  |  |  |  |  |  |
| P2     |   |   |   |   |   |   |   |   |   |   |  |  |  |  |  |  | █| █| █| █| █| █| █| █|

Proceso|Tiempo de espera|Tiempo de retorno
:-|:-|:-
P1|3 |9
P2|16|23
P3|9 |16
P4|0 |3

Tiempo medio de espera | Tiempo medio de retorno
:- | :-
7  | 12.75

---

## Planificación Round Robin

El algoritmo de planificación Round Robin o planificación por turnos es similar a la planificación FCFS, pero se agrega el desalojo de procesos para realizar la conmutación entre ellos. 
En este algoritmo se define una unidad de tiempo denominada ***cuanto de tiempo*** o ***quantum***. Su valor está entre 10 y 100 milisegundos.
Este quantum es el intervalo de tiempo máximo que se le asigna el CPU a cada proceso de la cola de procesos listos.

Cuando se le asigna el CPU a un proceso, pueden pasar dos cosas: 
- El proceso termina su ejecución antes de que se termine su quantum, y libera voluntariamente el CPU.
- El quantum del proceso se acaba antes de que éste pueda terminar su trabajo.

En este último caso, cuando sucede, se envía una interrupción al sistema operativo para realizar la conmutación (o cambio de contexto), y al proceso que tenía asignado el CPU se lo pone al final de la cola de procesos listos.
Luego se le asigna el CPU al siguiente proceso situado en la cola de listos.

### Ejemplo

Asumiendo un quantum q = 3:

Proceso | Tiempo de servicio
:- | :-
**P1** | 8
**P2** | 2 
**P3** | 3

**Diagrama de Gantt**

| Tiempo | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |10|11|
|:-------|:--|:--|:--|:--|:--|:--|:--|:--|:--|:--|--|--|
| Proceso|P1 |P1 |P1 |P2 |P2 |P3 |P3 |P3 |P1 |P1 |P1|P1| 


Proceso|Tiempo de espera|Tiempo de retorno
:-|:-|:-
**P1**|5 |12
**P2**|3 | 5
**P3**|5 | 8

Tiempo medio de espera | Tiempo medio de retorno
:- | :-
4.3| 8.3

---

## Ejercicios

#### Ejercicio 14 

Considere el siguiente conjunto de procesos planificados:

| Proceso | Llegada | Duración CPU |
|:--------|:--------|:-------------|
| **P1**  | 1       | 5            |
| **P2**  | 5       | 2            |
| **P3**  | 2       | 1            |
| **P4**  | 4       | 6            |
| **P5**  | 3       | 4            |

**a)** Indicar cuál es el algoritmo de planificación con menor tiempo medio de Retorno

**b)** Indicar cuál es el algoritmo de planificación con menor tiempo medio de Espera

Considerando los siguientes algoritmos:
1) SJF sin desalojo
2) SJF con desalojo
3) Round Robin con quantum de 2 unidades de tiempo

Realizar el Diagrama de Gantt correspondiente

**Tiempos de llegada**

| Tiempo | 1| 2| 3| 4| 5|
|:-------|--|--|--|--|--|
|Procesos|P1|P3|P5|P4|P2| 

**SJF sin desalojo**

| Tiempo | 1| 2| 3| 4| 5| 6| 7| 8| 9|10|11|12|13|14|15|16|17|18|
|:-------|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|
| **P1** | █| █| █| █| █|  |  |  |  |  |  |  |  |  |  |  |  |  |
| **P2** |  |  |  |  |  |  | █| █|  |  |  |  |  |  |  |  |  |  | 
| **P3** |  |  |  |  |  | █|  |  |  |  |  |  |  |  |  |  |  |  | 
| **P4** |  |  |  |  |  |  |  |  |  |  |  |  | █| █| █| █| █| █| 
| **P5** |  |  |  |  |  |  |  |  | █| █| █| █|  |  |  |  |  |  | 

| Proceso | Llegada | Duración CPU | Tiempo espera | Tiempo retorno |
|:--------|:--------|:-------------|---------------|----------------|
| **P1**  | 1       | 5            | 0             | 5              |
| **P2**  | 5       | 2            | 2             | 4              |
| **P3**  | 2       | 1            | 4             | 5              |
| **P4**  | 4       | 6            | 9             | 15             |
| **P5**  | 3       | 4            | 6             | 10             |

|Tiempo medio de espera | Tiempo medio de retorno |
|:----------------------|-------------------------|
| 4.2                   | 7.6                     |

**SJF con desalojo** o **SRT (shortest-remaining-time)**

| Tiempo | 1| 2| 3| 4| 5| 6| 7| 8| 9|10|11|12|13|14|15|16|17|18|
|:-------|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|
| **P1** | █|  | █| █| █| █|  |  |  |  |  |  |  |  |  |  |  |  |
| **P2** |  |  |  |  |  |  | █| █|  |  |  |  |  |  |  |  |  |  | 
| **P3** |  | █|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | 
| **P4** |  |  |  |  |  |  |  |  |  |  |  |  | █| █| █| █| █| █| 
| **P5** |  |  |  |  |  |  |  |  | █| █| █| █|  |  |  |  |  |  | 

| Proceso | Llegada | Duración CPU | Tiempo espera | Tiempo retorno |
|:--------|:--------|:-------------|---------------|----------------|
| **P1**  | 1       | 5            | 1             | 6              |
| **P2**  | 5       | 2            | 2             | 4              |
| **P3**  | 2       | 1            | 0             | 1              |
| **P4**  | 4       | 6            | 9             | 15             |
| **P5**  | 3       | 4            | 6             | 10             |

|Tiempo medio de espera | Tiempo medio de retorno |
|:----------------------|-------------------------|
|3.6                    |7.2                      |

**Round Robin con q = 2**

| Tiempo | 1| 2| 3| 4| 5| 6| 7| 8| 9|10|11|12|13|14|15|16|17|18|
|:-------|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|
| **P1** | █| █|  |  |  |  |  |  |  | █| █|  |  |  |  | █|  |  |
| **P2** |  |  |  |  |  |  |  | █| █|  |  |  |  |  |  |  |  |  | 
| **P3** |  |  | █|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | 
| **P4** |  |  |  |  |  | █| █|  |  |  |  |  |  | █| █|  | █| █| 
| **P5** |  |  |  | █| █|  |  |  |  |  |  | █| █|  |  |  |  |  | 

| Proceso | Llegada | Duración CPU | Tiempo espera | Tiempo retorno |
|:--------|:--------|:-------------|---------------|----------------|
| **P1**  | 1       | 5            | 11            | 16             |
| **P2**  | 5       | 2            | 3             | 5              |
| **P3**  | 2       | 1            | 1             | 2              |
| **P4**  | 4       | 6            | 9             | 15             |
| **P5**  | 3       | 4            | 7             | 11             |
 
|Tiempo medio de espera | Tiempo medio de retorno |
|:----------------------|-------------------------|
| 6.2                   | 9.8                     |

---

## Algoritmos

|SJF| [C](sjf.c) | [Java](SJF.java)|
|:--|------------|-----------------
|**Round Robin**| [**C**](roundRobin.c) | [**Java**](RoundRobin.java)|

---

## [Volver atrás](../readme.md)
