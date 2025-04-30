## [Volver atrás](readme.md)

# Planificación de Procesos

## Índice

- [Conceptos](#conceptos)

- [Planificación FCFS](#planificación-fcfs)

- [Planificación SJF](#planificación-sjf)

- [Planificación Round Robin](#planificación-round-robin)

- [Ejercicios](#ejercicios)

- [Algoritmos](#algoritmos)

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
| **P2**  | 5       | 2            | 2             | 3              |
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
| **P1** |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
| **P2** |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | 
| **P3** |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | 
| **P4** |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | 
| **P5** |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | 

|Tiempo medio de espera | Tiempo medio de retorno |
|:----------------------|-------------------------|
|                       |                         |

---

## Algoritmos

---

## [Volver atrás](readme.md)