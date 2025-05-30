## [Volver atrás](readme.md)

# Dispositivos de entrada y salida

## Índice

- [Guía Teórica](#guía-teórica)

- [Ejercicios](#ejercicios)

## Guía Teórica

1. ¿Qué son los spooling y el buffering en el contexto de E/S? ¿En qué se diferencian y qué problemas ayudan a resolver?

---

2. ¿Cuál es la función del módulo de gestión de dispositivos (device driver) en un sistema operativo y cómo interactúa con el sistema operativo y el hardware?

---

3. ¿Cuál es el objetivo de un administrador de interrupciones y la de un driver del dispositivo?

---

4. ¿Qué es la abstracción de dispositivo y cómo ayuda a lograr la independencia de hardware en el diseño del sistema operativo?

---

5. ¿Qué se entiende por independencia del dispositivo?

---

6. Describe las principales funciones del sistema operativo relacionadas con la gestión de E/S. ¿Cómo se organiza la pila de  software de E/S desde la aplicación hasta el dispositivo físico?

---

7. ¿Por qué los archivos de salida de la impresora normalmente se manejan por cola de impresión en el disco antes de ser impresos?

---

8. Describa en qué consiste el estancamiento y qué condiciones deben darse para que se produzca.

---

9. ¿Qué ventaja introduce la capacidad de “localización superpuesta en unos discos”, y cuáles son los tiempos involucrados en la lectura o escritura de un bloque de disco?

---

10. ¿Cómo maneja un sistema operativo los errores de E/S? Menciona tipos comunes de errores y las estrategias utilizadas para su detección y recuperación.

---

## Ejercicios

1. Breve investigación

    - Clasificación de dispositivos de E/S: ejemplos y características.
    - Diferencias entre dispositivos de carácter y de bloque.
    - Explicación de los tres métodos de E/S: programada, con interrupciones, y DMA.
    - Rol del sistema operativo en la gestión de E/S.
    - Ejemplos de cómo distintos sistemas operativos (Windows, Linux) manejan dispositivos de E/S.

2. Estudio de Caso

    Seleccionar un dispositivo real (por ejemplo, disco rígido, teclado, mouse, impresora o escáner) y responder:
    - ¿Cómo se comunica con el sistema operativo?
    - ¿Qué tipo de controlador requiere?
    - ¿Cómo se realiza la gestión de sus operaciones de E/S?
    - ¿Qué impacto tiene su velocidad o latencia en el rendimiento general del sistema?

3. Exploración práctica sobre Linux

    - Listar los dispositivos de E/S presentes con el comando lsblk, o dmesg (describir los mensajes de pantalla).
    - Identificar los controladores usados.
    - Analizar los logs del sistema relacionados con eventos de E/S (mirar subdirectorio Var).
    - Realizar una prueba de lectura/escritura en disco y medir tiempos con “dd”.


**Marco Conceptual (resumen operativo)**

Los dispositivos de E/S presentan características que impactan en el rendimiento global del sistema.

Algunas magnitudes clave:

- **Latencia** (L): Tiempo que tarda el dispositivo en comenzar la transferencia.
- **Velocidad de transferencia** (T): En bytes/segundo, MB/s, etc.
- **Tamaño del bloque** (B): Cantidad de datos transferidos por operación.
- **Tiempo total de E/S** (E): Tiempo que tarda una operación completa, incluyendo latencia y transferencia.

**Modelo simplificado**: E = L + B / T

4. Cálculo práctico de tiempo de E/S

    Dado el siguiente dispositivo de disco:
    - Latencia: 8 ms
    - Velocidad de transferencia: 100 MB/s
    - Tamaño de bloque: 4 KB

    **a**. Calcular el tiempo total de E/S para una sola operación.

    **b**. Calcular cuántas operaciones completas se pueden hacer en 1 segundo.

    **c**. Si el sistema necesita leer 10 MB de datos, ¿cuánto tiempo tomaría?

    Repetir con un segundo disco que tiene:

    Latencia: 3 ms, Velocidad: 50 MB/s, mismo tamaño de bloque.

    Comparar rendimiento y tomar decisiones basadas en los cálculos.

5. Comparación de métodos de E/S

    Considerar tres formas de operar con un dispositivo:

    **a**. E/S programada: El CPU espera activamente.

    **b**. E/S con interrupciones: El CPU puede seguir ejecutando otros procesos.

    **c**. DMA (Acceso Directo a Memoria): Transferencia sin intervención del CPU.

    Suponer que el CPU procesa 1.000 MIPS (millones de instrucciones por segundo), y que:

    - Una instrucción de E/S programada requiere 500 instrucciones por byte transferido.
    - Con interrupciones, solo 1 interrupción cada 4 KB (1000 instrucciones por interrupción).
    - Con DMA, el overhead es de 2000 instrucciones por transferencia de 4 KB.

    **a**. Calcular cuántas instrucciones por segundo consume el CPU en cada caso, para una tasa de transferencia de 1 MB/s.

    **b**. ¿Qué porcentaje del CPU se dedica a la E/S en cada caso?

6. Simulación de un buffer circular

    Un sistema usa un buffer circular para almacenar datos de un sensor que entrega 512 bytes cada 10 ms. El buffer tiene capacidad de 4096 bytes.

    **a**. ¿Cuánto tiempo tarda en llenarse si el sistema no lo vacía?

    **b**. Si el sistema lee el buffer cada 25 ms y extrae 1024 bytes, ¿el sistema puede mantenerse sin pérdida de datos? Justificar.

7. En cuál de los cuatro estratos del software de E/S se hace cada una de las siguientes actividades:

    **a**. Determinación de la pista, sector y cabeza en una lectura de disco

    **b**. Conservación de una reserva de bloques usados recientemente

    **c**. Escritura de comandos en los registros de dispositivos

    **d**. Verificación de sí el usuario tiene permiso de utilizar el dispositivo

    **e**. Conversión de enteros binarios a ASCII para su impresión

8. Indicar cómo se puede construir un disco en RAM, y para qué puede resultar ventajoso hacerlo.

9. Describir cómo funciona el software de entrada, el de salida de un terminal, y los problemas asociados.