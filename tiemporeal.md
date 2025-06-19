## [Volver atrás](readme.md)

# Sistemas de Tiempo Real (RTS)

## Guía Teórica

1. ¿Qué entiende por sistema de tiempo real?

Un Sistema de Tiempo Real es un tipo de sistema informático que debe responder a eventos o procesar datos dentro de un tiempo predecible y determinado. El correcto funcionamiento del sistema no solo depende del resultado de las operaciones, sino también de que se ejecuten dentro de un tiempo límite.

---

2. ¿Qué es el Deadline?

El Deadline (fecha límite o plazo de entrega) es el tiempo máximo en el que una tarea debe completarse dentro de un sistema de tiempo real. Si una tarea no se finaliza antes del deadline, el sistema puede experimentar degradación del rendimiento o incluso fallos catastróficos, dependiendo del tipo de sistema.

---

3. ¿Cuál es la estructura general de un RTS? Describa cada componente.

- Sensor o Dispositivo de Entrada: captura datos del entorno en tiempo real.
- Procesador y Sistema Operativo en Tiempo Real (RTOS): el CPU ejecuta los algoritmos y procesos en tiempo real, y el RTOS planifica tareas en base a prioridades y deadlines.
- Memoria y Almacenamiento.
- Módulo de Comunicación: permite la comunicación con otros sistemas o dispositivos.
- Actuadores o Dispositivos de Salida: ejecuta acciones basadas en las decisiones del procesador.
- Módulo de Control y Supervisión: monitorea el sistema y maneja fallos o emergencias.

---

4. Indique qué hardware no es conveniente en un RTS. ¿Por qué?

Los Sistemas en Tiempo Real necesitan hardware determinista, en otras palabras, los tiempos de ejecución deben ser predecibles y constantes. Esto no ocurre en hardware como los siguientes:
- Procesadores que utilizan técnicas de pipeline y predicción de saltos: si el procesador predice mal un salto, debe descartar varias instrucciones, lo que genera latencias impredecibles.
- Caché: si los datos no están en caché, el procesador debe buscarlos en la RAM, lo cual genera latencias variables.
- Discos duros mecánicos (HDDs): su tiempo de acceso depende de la posición del cabezal y la velocidad de rotación, presentando tiempos de respuesta variables.

---

5. Clasifique las tareas que pueden llegar a tener lugar dentro de un sistema informático, por el tiempo que involucra su realización.

- Hard Deadline (Plazo Estricto): si la tarea no se completa antes del deadline, el sistema falla completamente.
- Soft Deadline (Plazo Flexible): si la tarea se retrasa, la calidad del servicio se degrada, pero no hay un fallo total.
- Firm Deadline (Plazo Crítico pero Ocasionalmente Tolerable): si una tarea no se completa a tiempo, su resultado ya no es útil, pero el sistema puede seguir funcionando.

---

6. Clasifique las tareas que pueden llegar a tener lugar dentro de un RTS, por su frecuencia de aparición.

- Tareas Periódicas (Frecuencia fija, altamente predecibles): se ejecutan a intervalos regulares y predecibles. Son prioritarias, ya que el sistema depende de su ejecución en tiempos predecibles.
- Tareas Aperiodicas (Ocurren en momentos indeterminados): se ejecutan en respuesta a un evento externo, pero sin un patrón fijo de repetición. Se manejan con interrupciones o eventos de hardware.
- Tareas Esporádicas (Ocurren rara vez, pero son críticas cuando suceden): se ejecutan de manera poco frecuente, pero su ejecución es prioritaria y crítica.

---

7. ¿Qué tipos de Sistemas Operativos de Tiempo Real se diseñan?

- RTOS Basado en Eventos (Event-Driven RTOS): las tareas se ejecutan en respuesta a eventos externos. Usa interrupciones para activar tareas cuando ocurre un evento. Las tareas se ejecutan cuando son necesarias, no en intervalos fijos.
- RTOS Basado en Tiempo (Time-Driven RTOS): las tareas se ejecutan en intervalos de tiempo fijos, independientemente de los eventos. Usa un reloj del sistema para ejecutar tareas periódicas. Se basa en un planificador cíclico que ejecuta tareas en momentos predefinidos.

---

8. ¿De qué depende la elección del algoritmo de planificación?

- Naturaleza del sistema:
	- Hard RTOS y RTOS basado en Tiempo: se necesita un algoritmo determinista que garantice el cumplimiento estricto de los plazos (ej. RM o EDF).
	- Soft RTOS y RTOS basado en Eventos: se pueden permitir pequeños retrasos, por lo que algoritmos como Round Robin o planificación por prioridades pueden ser suficientes.
- Tipo de tareas:
	- Periódicas: las tareas que ocurren en intervalos regulares se benefician de Rate Monotonic (RM) o Earliest Deadline First (EDF).
	 - Aperiódicas: ocurren en cualquier momento sin patrón fijo. Se pueden manejar con FIFO o por prioridades.
- Carga del sistema:
	- Si el sistema está muy cargado, se necesita un algoritmo que optimice el uso de CPU (ej. EDF o Least Laxity First (LLF)).
	- Si el sistema tiene poca carga, algoritmos más simples como FIFO o Round Robin pueden ser suficientes.
- Overhead de planificación:
	- Algoritmos más complejos como EDF requieren cálculos adicionales.
	- Si la CPU es limitada, puede ser mejor usar planificación cíclica fija para reducir la carga de planificación.
- Equidad vs. Prioridad:
	- Sistemas críticos: se prioriza garantizar que las tareas críticas se ejecuten a tiempo (Prioridad Estática o Dinámica).
	- Sistemas interactivos: se busca que todas las tareas reciban una parte justa del tiempo de CPU (Round Robin).

---

9. Describa la taxonomía de planificación.

La taxonomía de planificación es la clasificación de los distintos métodos y enfoques utilizados para gestionar la ejecución de tareas en un sistema operativo. Se puede dividir en varios niveles según diferentes criterios:
- Entorno del procesador:
	1. Uniprocesador:
	    - Planificación estática (las prioridades se asignan antes de la ejecución y no cambian).
		- Planificación dinámica (las prioridades cambian en tiempo de ejecución).
	2. Multiprocesador:
	    - Planificación particionada (cada tarea se asigna a un procesador fijo).
	    - Planificación global (las tareas pueden migrar entre procesadores).
- Naturaleza del sistema.
- Estrategia de planificación:
	- Planificación con prioridades fijas: cada tarea tiene una prioridad establecida de antemano.
	- Planificación con prioridades dinámicas: las prioridades cambian en función de las condiciones del sistema.
	- Planificación cooperativa: una tarea solo cede la CPU cuando termina o la libera voluntariamente.
	- Planificación con desalojo (preemptive scheduling): una tarea de mayor prioridad puede interrumpir a una de menor prioridad.

Ejemplos de planificaciones según el enfoque del RTOS:
- Enfoque estático (prioridades fijas):
    - Rate Monotonic Scheduling (RMS): asigna prioridad fija basada en la frecuencia de ejecución de las tareas. Mayor frecuencia = Mayor prioridad.

    Desventaja: No permite cambios dinámicos en los períodos de las tareas.
- Enfoque dinámico (prioridades cambiantes):
    - Earliest Deadline First (EDF): prioridad basada en el deadline más cercano. Las tareas con menor tiempo restante tienen mayor prioridad. Adaptable a cambios en los períodos de las tareas.
    - Minimum Urgency First (MUF) (Variante de EDF): usa dos prioridades fijas:
        - Criticidad de la tarea
        - Prioridad de usuario

    Se ajusta mejor en sistemas con diferentes niveles de urgencia.

---

10. ¿Qué parámetros se debe especificar para un RTOS?

- Parámetros relacionados con las tareas:
	- Período: tiempo entre dos ejecuciones consecutivas de una tarea periódica.
	- Tiempo de ejecución.
	- Deadline.
	- Prioridad.
- Parámetros de planificación:
    - Tipo de planificación (estática o dinámica).
	- Preemptividad: si una tarea puede ser interrumpida por otra de mayor prioridad (preemptiva) o no (cooperativa).
	- Parámetros de sincronización y comunicación:
	- Mecanismos de sincronización: Uso de semáforos, mutexes o monitores para evitar condiciones de carrera.
	- Tiempo de respuesta a interrupciones.
	- Jitter: Variabilidad en el tiempo de ejecución de una tarea respecto a su período esperado.
- Parámetros de recursos y rendimiento:
    - Uso de memoria.
    - Consumo de CPU.
    - Latencia de interrupción.
    - Tiempo de conmutación de contexto.

---

11. ¿Qué entiende por inversión de prioridad y cuándo ocurre?

La inversión de prioridad es un problema en la planificación de sistemas de tiempo real donde una tarea de alta prioridad se ve bloqueada porque una tarea de baja prioridad retiene un recurso compartido que la de mayor prioridad necesita.

Soluciones para evitar la Inversión de Prioridad:
	- Herencia de Prioridad: cuando una tarea de baja prioridad bloquea a otra de alta prioridad, hereda temporalmente la prioridad más alta hasta que libere el recurso.
	- Techo de Prioridad: se asigna una prioridad fija a los recursos compartidos. Solo las tareas con prioridad mayor o igual pueden acceder al recurso.
	- Evitar bloqueos innecesarios: diseñar el sistema de manera que las tareas de baja prioridad no retengan recursos por mucho tiempo.