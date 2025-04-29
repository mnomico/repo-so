## [Volver atrás](readme.md)

# Planificación de Procesos

## Conceptos

### Tiempo de servicio

El ***tiempo de servicio*** es el tiempo total que un proceso necesita utilizar el CPU para completar su ejecución, sin contar los tiempos de espera.

### Tiempo de retorno

El ***tiempo de retorno*** es el tiempo total desde que un proceso se coloca en la cola de listos hasta que finaliza su ejecución. Se calcula de la siguiente manera:

> Tiempo de retorno = Tiempo de finalización − Tiempo de llegada

Cuando hacemos los ejercicios, no consideramos el tiempo inicial: todos los procesos llegan en el tiempo 0. Por lo tanto, en los ejercicios el tiempo de retorno va a ser el tiempo en el que el proceso se termina de ejecutar.

### Tiempo de espera

El ***tiempo de espera*** es el tiempo total que un proceso pasa esperando en la cola de listos antes de ser atendido por el CPU. Se calcula de la siguiente manera:

> Tiempo de espera = Tiempo de retorno − Tiempo de servicio

### Tiempo de conmutación (o cambio de contexto)

Cuando se selecciona un proceso de la cola de listos para asignarle el CPU, se debe llevar una serie de acciones para quitarle el CPU al proceso anterior, guardar el estado del proceso, y asignarle el CPU al proceso actual. Este tiempo se lo conoce como ***tiempo de conmutación*** o ***cambio de contexto***.

---

## Planificación FCFS

El algoritmo de planificación FCFS (first-come, first-served; primero en llegar, primero en ser servido), es el más simple, ya que le asigna el CPU al primer proceso de la cola de listos. La implementación se basa en el uso de una cola FIFO. Cuando un proceso entra en la cola de listos, su PCB (Process Control Block; bloque de control de proceso) se pone al final de la cola. Cuando la CPU se encuentra disponible, se lo asigna al primer proceso de la cola y éste es eliminado de la cola.

### Desventaja

El tiempo medio de espera del algoritmo FCFS es muy largo en comparación a los otros algoritmos de planificación.

### Ejemplo

Asumiendo que no hay tiempo de conmutación, y que todos los procesos ingresan en el momento 0:

| Proceso   | Tiempo de Servicio   |
|:----------|:---------------------|
| P1        | 24                   |
| P2        | 3                    |
| P3        | 3                    |

**Diagrama de Gantt**

| Tiempo | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |10|11|12|13|14|15|16|17|18|19|20|21|22|23|24|25|26|27|28|29|30|
|:---------|:--|:--|:--|:--|:--|:--|:--|:--|:--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|
| P1      | █ | █ | █ | █ | █ | █ | █ | █ | █ | █| █| █| █| █| █| █| █| █| █| █| █| █| █| █|   |   |   |   |   |   |
| P2      |   |   |   |   |   |   |   |   |   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | █ | █ | █ |   |   |   |
| P3      |   |   |   |   |   |   |   |   |   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |   |   |   | █ | █ | █ |

Proceso|Tiempo de espera|Tiempo de retorno
:-|:-|:-
P1|0 |24
P2|24|27
P3|27|30

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

### Ejemplo

Proceso | Tiempo de servicio
:- | :-
P1 | 6
P2 | 8
P3 | 7
P4 | 3

**Diagrama de Gantt**

| Tiempo | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |10|11|12|13|14|15|16|17|18|19|20|21|22|23
|:----------|:--|:--|:--|:--|:--|:--|:--|:--|:--|:--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|
| P4       | █ | █ | █ |   |   |   |   |   |   |   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
| P1       |   |   |   | █ | █ | █ | █ | █ | █ |   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
| P3       |   |   |   |   |   |   |   |   |   | █ | █| █| █| █| █| █|   |  |  |  |  |  |  |  |  |
| P2       |   |   |   |   |   |   |   |   |   |   |  |  |  |  |  |  | █ | █| █| █| █| █| █| █|  |

Proceso|Tiempo de espera|Tiempo de retorno
:-|:-|:-
P1|3 |9
P2|16|23
P3|9 |16
P4|0 |3

Tiempo medio de espera | Tiempo medio de retorno
:- | :-
7 | 12.75

---

## Planificación por turnos (Round Robin)

---

## [Volver atrás](readme.md)