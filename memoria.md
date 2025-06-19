## [Volver atrás](readme.md)

# Administración de Memoria

## Índice

[Guía Teórica](#guía-teórica)

[Conceptos](#conceptos)

[Paginación](#paginación)

[Ejercicios](#ejercicios)

---

## Guía Teórica

1. ¿En qué consiste la reubicación de los programas del usuario?

La reubicación consiste en la capacidad de cargar un programa en cualquier dirección de memoria disponible en lugar de una dirección fija, permitiendo un uso más eficiente de la memoria. Esto es importante en sistemas multiprogramados, donde los procesos se cargan y descargan dinámicamente.

Tipos de Reubicación:
- Reubicación Estática: ocurre antes de la ejecución del programa. El compilador o el cargador del sistema ajusta todas las direcciones de memoria a una ubicación específica. Si el programa debe moverse a otra dirección, debe ser recompilado.
- Reubicación Dinámica: ocurre durante la ejecución del programa. Se usa un registro base que contiene la dirección de inicio del proceso en memoria. Todas las direcciones lógicas del programa se suman a este valor en tiempo de ejecución. Permite mover un programa en memoria sin modificar su código.
- Reubicación con Memoria Virtual (Paginación/Segmentación): usa una Unidad de Administración de Memoria (MMU) para traducir direcciones lógicas en direcciones físicas. No es necesario modificar el código del programa, ya que la MMU asigna dinámicamente los marcos de página o segmentos. Permite que el proceso se mueva en memoria sin afectar su ejecución.

---

2. ¿Qué es el swapping, cuándo se lo requiere?

Swapping es una técnica de administración de memoria en la que procesos completos se intercambian entre la memoria principal y el disco para permitir la ejecución de más procesos de los que físicamente entran en la RAM.

El swapping se requiere:
- Cuando hay más procesos listos de los que caben en la memoria principal.
- Cuando un proceso está inactivo por mucho tiempo y se necesita espacio para otros procesos.
- En sistemas con memoria limitada, donde algunos procesos deben esperar su turno en disco.

---

3. ¿Qué se entiende por particiones múltiples, registros límites de cada partición?

Las particiones múltiples son una técnica de administración de memoria en la que la memoria principal se divide en varias regiones fijas o dinámicas para permitir la ejecución de múltiples procesos al mismo tiempo.

Se pueden clasificar en:
- Particiones fijas (estáticas): la memoria se divide en bloques de tamaño fijo al inicio.
- Particiones dinámicas: se asignan bloques de tamaño variable según la necesidad de cada proceso.

Los registros de límites son mecanismos de hardware o software que controlan los accesos de los procesos a la memoria dentro de sus particiones asignadas.

Cada partición tiene dos registros clave:
- Registro base: indica la dirección de inicio de la partición.
- Registro límite: indica el tamaño o la dirección final de la partición.

Desventajas:
- Puede haber fragmentación interna (en particiones fijas).
- En particiones dinámicas, la fragmentación externa puede desperdiciar espacio.

---

4. Describir el método de planificación de memoria por regiones fijas.

La planificación de memoria por regiones fijas es una técnica de gestión de memoria en la que la memoria principal se divide en bloques de tamaño fijo (particiones) antes de la ejecución del sistema. Cada proceso que se carga en memoria recibe una de estas regiones.

Desventajas:
- Fragmentación interna: si un proceso no usa toda la región, el espacio restante se desperdicia.
- Uso ineficiente de memoria: si un proceso es muy grande y no cabe en ninguna región, no puede ejecutarse.
- No permite reubicación dinámica: una vez que un proceso ocupa una región, no se puede mover sin reiniciar.

---

5. ¿Cuándo se produce fragmentación interna o externa de la memoria?

La fragmentación de memoria ocurre cuando la asignación de memoria no es eficiente, lo que genera espacio desperdiciado. Existen dos tipos principales:
- Fragmentación Interna: se produce cuando un proceso ocupa menos espacio del asignado, dejando memoria inutilizable dentro del bloque asignado.
- Fragmentación Externa: se produce cuando hay suficiente memoria libre en el sistema, pero está fragmentada en pequeños bloques dispersos, impidiendo la carga de procesos grandes.

---

6. Indicar cómo funciona el método de planificación de trabajos de partición variable.

El método de planificación de memoria por particiones variables permite asignar memoria de forma dinámica, ajustándose al tamaño exacto de cada proceso. No hay un tamaño fijo para cada partición, lo que mejora la utilización de la memoria en comparación con las particiones fijas.
- Un proceso llega al sistema: se busca un bloque de memoria libre lo suficientemente grande para alojarlo.
- Se asigna la memoria: la memoria se divide en una partición del tamaño justo para el proceso. El resto del espacio libre queda disponible para otros procesos.
- El proceso termina: su memoria se libera, creando espacio libre. Si hay espacios libres contiguos, se pueden combinar para evitar fragmentación externa.

---

7. ¿Cómo funciona la protección en páginas de memoria compartidas?

Los sistemas operativos permiten que múltiples procesos compartan páginas de memoria para optimizar el uso de la RAM y facilitar la comunicación entre procesos (IPC). Sin embargo, compartir memoria sin control puede provocar corrupción de datos, accesos indebidos o violaciones de seguridad. Para evitar esto, el sistema usa protección en las páginas compartidas.

Cada página en la tabla de páginas de un proceso tiene bits de protección que definen los permisos de acceso, tales como solo lectura, lectura y escritura, o ejecutable.

Implementación:
- Uso de una Tabla de Páginas: cada proceso tiene su propia tabla de páginas, pero una misma entrada en varias tablas puede apuntar al mismo marco de memoria.
- Bits de Protección: cada entrada en la tabla de páginas tiene bits que indican qué tipo de acceso está permitido.
- Interruptores de Protección: si un proceso intenta acceder a una página de forma no permitida, el sistema genera una excepción de protección de memoria.

---

8. Introducir un bit de validez en las tablas de asignación ¿Qué ventajas introduce y por qué?

El bit de validez es un bit agregado a cada entrada de la tabla de páginas o de segmentos que indica si la dirección de memoria asociada es válida o no.

Bit = 1 (válido): La página o segmento está cargado en memoria RAM y puede ser accedido.

Bit = 0 (inválido): La página o segmento no está en memoria RAM (puede estar en disco o no asignado).

Ventajas del bit de validez:
- Protección de memoria: evita accesos a direcciones de memoria no asignadas o no permitidas. Si un proceso intenta acceder a una página o segmento marcado como inválido, se genera una interrupción (page fault o segmentation fault), permitiendo al sistema operativo manejar la situación de forma segura.
- Soporte para memoria virtual: permite implementar técnicas de paginación bajo demanda, donde solo se cargan en RAM las páginas necesarias, reduciendo el uso de memoria física. Si una página está marcada como inválida, el sistema puede buscarla en el disco y cargarla cuando sea necesario.
- Mayor eficiencia en la gestión de memoria: se pueden reservar direcciones de memoria sin ocupar espacio real en RAM hasta que sean necesarias. Evita que procesos lean o escriban en áreas de memoria no asignadas, previniendo fallos y corrupción de datos.
- Implementación de espacios de direcciones separadas: cada proceso puede tener su propio espacio de direcciones, y el bit de validez impide que un proceso acceda a la memoria de otro, aumentando la seguridad del sistema.

---

9. Introducir un bit de modificación en las tablas de asignación. ¿Qué debo hacer en el caso de que valga “1” y por qué?

El bit de modificación es un bit adicional en la tabla de páginas o tabla de segmentos, que indica si una página o segmento ha sido modificado desde que se cargó en memoria.

Bit = 0 (No modificado): La página o segmento no ha cambiado desde que fue cargado en memoria.

Bit = 1 (Modificado): La página o segmento ha sido alterado y su contenido en RAM es diferente del que está en disco.

Si el bit de modificación de una página o segmento es 1 y el sistema necesita reemplazarla (swap out), debo escribirla en el disco antes de eliminarla de la RAM. Si una página modificada se descarta sin escribirla en el disco, los cambios se perderían, lo que puede provocar corrupción de datos o resultados incorrectos cuando el proceso acceda nuevamente a esa página.

Pasos cuando el bit de modificación es "1":
- Escribir la página en el disco: antes de reemplazar la página, el sistema operativo guarda los cambios en el archivo de paginación o en el disco (swap o memoria secundaria).
- Actualizar la tabla de páginas: se marca la entrada como inválida (bit de validez = 0) para indicar que la página ya no está en RAM.
- Seleccionar una nueva página para cargar: Se asigna un nuevo marco de página en la RAM y se actualizan los registros de la tabla de páginas.

Ventajas:
- Evita escrituras innecesarias en disco: si el bit de modificación es 0, la página no ha cambiado y no es necesario escribirla en disco, lo que reduce el tráfico de E/S y mejora el rendimiento.
- Optimiza el reemplazo de páginas: los algoritmos de reemplazo de páginas pueden dar prioridad a páginas no modificadas para minimizar escrituras en disco.
- Mejora la eficiencia en sistemas con memoria virtual: solo se escriben en disco las páginas que realmente han cambiado, reduciendo el tiempo de swapping.

---

10. Describir los pasos que intervienen en un fallo de página.

Un fallo de página ocurre cuando un proceso intenta acceder a una página que no está en la memoria principal (RAM), sino en la memoria secundaria (disco). Esto genera una interrupción que el sistema operativo debe manejar para cargar la página en RAM.

- El proceso intenta acceder a una página que no está en RAM. Se genera una excepción de fallo de página porque la tabla de páginas indica que la página está en disco.
- El sistema operativo verifica si la dirección es válida. Si la página no pertenece al proceso se genera un error de segmentación (segfault). Si la página es válida pero está en disco se continúa con la carga de la página.
- Se elige un marco de página en RAM. Si hay espacio libre, la nueva página se carga directamente. Si no hay espacio se usa un algoritmo de reemplazo de páginas (FIFO, LRU, etc.) para elegir qué página expulsar.
- Si se expulsa una página, se verifica si estaba modificada. Si estaba modificada, se guarda en disco antes de expulsarla. Si no estaba modificada simplemente se sobrescribe.
- Se carga la página faltante desde el disco a RAM. Este paso es lento porque implica lectura desde el disco.
- Se actualiza la tabla de páginas del proceso. Se marca la página como presente en memoria y se asigna el marco de página correspondiente.
- Se reintenta la instrucción que causó el fallo de página. Ahora el acceso a memoria es exitoso.

---

11. ¿Que ventajas introduce el empleo de la paginación por demanda?

La paginación por demanda es un esquema de administración de memoria en el que las páginas de un proceso se cargan en RAM solo cuando son necesarias. En lugar de cargar todo el proceso en memoria al inicio, se trae cada página desde el disco solo cuando el proceso intenta acceder a ella.

Ventajas de la Paginación por Demanda:
- Uso eficiente de la memoria: solo se cargan las páginas necesarias, reduciendo el uso de RAM.
- Permite ejecutar procesos más grandes que la memoria física: al cargar páginas conforme se necesitan, se pueden ejecutar programas que excedan el tamaño de la RAM.
- Reducción del tiempo de carga inicial: no es necesario cargar todo el proceso en memoria al inicio.
- Mejor utilización de la memoria secundaria (swap): se optimiza el uso del espacio en disco al almacenar solo las páginas activas.
- Mayor flexibilidad en la multiprogramación: permite más procesos en ejecución al repartir mejor la memoria.

---

12. Describa dos métodos para la selección de página victima.

- FIFO (First-In, First-Out – Primero en entrar, primero en salir):
	- Se reemplaza la página más antigua en la memoria.
	- Fácil de implementar con una cola.
	- Desventaja: Puede expulsar páginas aún en uso (Anomalía de Belady).
- LRU (Least Recently Used – Menos recientemente usada):
	- Se reemplaza la página que no se ha usado en más tiempo.
	- Se basa en el historial de uso de las páginas.
	- Desventaja: Requiere hardware especializado o una estructura de datos eficiente.
- Óptimo (OPT – Belady’s Algorithm):
	- Se reemplaza la página que no será utilizada en más tiempo en el futuro.
	- Ideal en teoría, pero imposible de implementar en tiempo real (requiere conocimiento futuro).
	- Se usa como referencia para comparar otros algoritmos.
- Segunda Oportunidad (Clock Algorithm – Algoritmo del reloj):
	- Variante de FIFO con un bit de referencia (1 = usada, 0 = no usada).
	- Si la página tiene el bit en 1, se le da una segunda oportunidad y se mueve al final de la cola.
	- Eficiente en la práctica y evita expulsar páginas que aún se usan.

---

13. ¿Qué entiende por hiperpaginación?

La hiperpaginación o thrashing ocurre cuando un sistema operativo pasa más tiempo manejando fallos de página que ejecutando procesos útiles. Esto sucede cuando la cantidad de memoria asignada a los procesos es insuficiente, lo que provoca una alta tasa de intercambio de páginas entre la RAM y la memoria secundaria (swap).

Causas de la Hiperpaginación:
- Demasiados procesos activos: si el sistema ejecuta más procesos de los que la RAM puede manejar, cada uno tendrá muy poca memoria disponible.
- Asignación de memoria insuficiente: si un proceso necesita más páginas de las que tiene asignadas, causará constantes fallos de página.
- Tamaño de marco inadecuado: si los marcos de página son muy pequeños, puede aumentar la fragmentación y los fallos de página.
- Algoritmos de reemplazo ineficientes: un mal algoritmo puede reemplazar páginas que aún son necesarias, generando más fallos de página.

Métodos que se utilizan para evitar la hiperpaginación:
- Política de Working Set: asegurar que cada proceso tenga suficiente memoria para su conjunto de trabajo.
- Asignación Dinámica de Marcos: dar más marcos a procesos que tienen muchos fallos de página y quitar a los que tienen pocos.
- Matar o suspender procesos: reducir la cantidad de procesos en ejecución para liberar memoria.
- Aumentar la memoria RAM: reduce la necesidad de swap.

---

14. Qué ventaja le introduce al modelo de administración de memoria el empleo de la
memoria cache en la arquitectura de computadora.

- Reducción del tiempo de acceso a memoria.
- Disminución de la carga en el sistema de memoria: menos accesos a RAM implica menos congestión en el bus de memoria y menos fallos de página, ya que los datos se pueden recuperar más rápido sin necesidad de swap.
- Mayor eficiencia en la paginación y segmentación: almacenar las tablas de páginas y segmentos en caché evita accesos constantes a la RAM para traducir direcciones. La TLB (Translation Lookaside Buffer) es una caché especial que guarda traducciones de direcciones virtuales a físicas, acelerando la gestión de memoria virtual.
- Reducción de latencias en procesos de E/S: las operaciones de lectura/escritura en disco son muy lentas comparadas con la RAM y la caché. Una buena estrategia de caché puede almacenar temporalmente datos que están por ser escritos o que se leen con frecuencia, minimizando los accesos al disco.

---

## Conceptos

### Protección de memoria

Cada proceso debe tener su propio espacio de memoria, sin invadir el de otros.
Esto se logra usando dos registros por proceso:

- **Registro base**: guarda la dirección física inicial que puede usar el proceso.
- **Registro límite**: guarda el tamaño del rango de memoria legal que puede usar el proceso.

Por ejemplo, si base = 300040 y límite = 120900, el proceso puede acceder a direcciones de 300040 a 420940 (300040 + 120900).

Cada vez que un proceso genera una dirección:

- El hardware compara esa dirección contra los registros base y límite.
- Si está fuera de ese rango, se envía una una interrupción al sistema operativo.

Esto evita que un proceso acceda a la memoria de otro proceso o a la del sistema operativo. **El sistema operativo es el único que tiene acceso no restringido a la memoria.**

### Direcciones lógicas y físicas

Una **dirección lógica** es una dirección generada por la CPU durante la ejecución de un proceso, mientras que una **dirección física** es la posición real en la memoria en donde se almacena el dato.

El conjunto de todas las direcciones lógicas generadas por un proceso es lo que se denomina como **espacio de direcciones lógicas**, y el conjunto de direcciones físicas que corresponden a estas direcciones lógicas se lo conoce como **espacio de direcciones físicas**.

La **MMU** (memory-management-unit) es el hardware que se encarga de traducir las direcciones lógicas en físicas.

---

## Paginación

La **paginación** es un esquema de gestión de memoria que permite que el espacio de direcciones físicas no sea contiguo. Divide la memoria en bloques de tamaño fijo llamados **marcos** (frames) y el espacio lógico en **páginas** del mismo tamaño.

Una dirección lógica se divide en dos:

- Número de página (p): índice para buscar en la tabla de páginas.
- Desplazamiento dentro de la página (d).

La **tabla de páginas** guarda la dirección base en la memoria física de cada página. El **tamaño de página** suele ser una potencia de 2.

---

## Ejercicios

**5**. Considere un espacio de direcciones lógicas de 16 páginas de 1024 bytes cada una, 
y un espacio de direcciones físicas de 64 frames.

**a**. ¿Cuántos bits son necesarios para especificar una dirección lógica?
**b**. ¿Cuántos bits son necesarios para especificar una dirección física?

**Resolución**

- Número de páginas (p) = 16
- Tamaño de página (d) = 1024 bytes
- Número de marcos (m) = 64

Para especificar la dirección lógica, necesitamos dos cosas: saber la cantidad de bits que ocupa el número de páginas y la cantidad de bits que ocupa el desplazamiento dentro de la página (que también lo podemos pensar como el tamaño de página).

Para el número de páginas, vamos a tener que poder representar las páginas 0 a 15. Para sacar la cantidad de bits que necesitamos, calculamos el logaritmo en base 2 de 16:

```
Bits para número de página = log 2 (16) = 4 bits
```

Por lo tanto necesitamos 4 bits para representar el número de página.

Ahora necesitamos obtener la cantidad de bits para el desplazamiento o tamaño de página. Para obtenerla, calculamos el logaritmo en base 2 de 1024:

```
Bits para desplazamiento = log 2 (1024) = 10 bits
```
Por lo tanto necesitamos 10 bits para representar el desplazamiento de página.

Ahora que tenemos tanto los bits necesarios para especificar el número de página y para especificar el desplazamiento de página, podemos obtener la cantidad de bits necesarios para especificar una dirección lógica de la siguiente manera:

```
Bits para dirección lógica = Bits para número de página + Bits para desplazamiento
Bits para dirección lógica = 4 bits + 10 bits
Bits para dirección lógica = 14 bits
```

**a.** Se necesitan 14 bits para especificar una dirección lógica.

Para saber cuantos bits necesitamos para especificar una dirección física, hacemos lo mismo que antes.

La única diferencia con lo anterior es que no tenemos el tamaño de marco, pero cuando no nos lo dicen, asumimos que es igual al tamaño de página. Por lo tanto:

- Número de marcos (m) = 64
- Desplazamiento (d) = 1024 bytes

Aplicamos el logaritmo en base 2 de 64 para saber los bits que necesitamos para representar el número de marcos:

```
Bits para número de marco = log 2 (64) = 6 bits
```

Entonces necesitamos 6 bits para especificar el número de marco.

No necesitamos calcular la cantidad de bits que necesitamos para el desplazamiento ya que asumimos que los marcos tienen el mismo tamaño que las páginas.

Por último sumamos la cantidad de bits que obtuvimos:

```
Bits para dirección física = bits para número de marco + bits para desplazamiento
Bits para dirección física = 6 bits + 10 bits
Bits para dirección física = 16 bits
```

**b.** Se necesitan 16 bits para especificar una dirección física.

---

**6**. Considere un sistema con un espacio lógico de memoria de 64K páginas con 4KB cada una,
una memoria física de 64Mb y direccionamiento al nivel de byte. ¿Cuántos bits hay en la
dirección lógica y en la dirección física?

**Resolución**

- Número de páginas = 64K
- Tamaño de página = 4KB
- Memoria física = 64MB

Primero vamos a calcular el número exacto de páginas:

```
Número de páginas = 64K = 64 * 1024 = 65536
```

Ahora podemos calcular la cantidad de bits que necesitamos para especificar el número de página:

```
Bits para número de página = log 2 (65536) = 16 bits
```

Luego la consigna nos dice que el tamaño de página es de 4KB, y también que el direccionamiento es a nivel de byte.
Esto quiere decir que cada dirección va a apuntar a un byte. Realmente no agrega nada necesario, simplemente trabajamos con bytes.

```
Tamaño de página = 4KB = 4 * 1024 = 4096 bytes
```

Ahora que tenemos el tamaño de página en bytes, calculamos la cantidad de bits que necesitamos para el desplazamiento:

```
Bits para desplazamiento = log 2 (4096) = 12 bits
```

Por último, calculamos la cantidad de bits necesaria para especificar una dirección lógica:

```
Bits para dirección lógica = 16 bits + 12 bits
Bits para dirección lógica = 28 bits
```

Luego nos piden la cantidad de bits necesaria para especificar una dirección física.

Tenemos los siguientes datos:

- Tamaño de memoria física = 64MB
- Tamaño de marco = 4KB (asumiendo que tiene el mismo tamaño que el de página)

El tamaño de memoria física es el espacio de direcciones físicas, a partir de él podemos sacar la cantidad de bits que ocupa una dirección física.

Primero convertimos el tamaño de memoria en bytes:

```
Tamaño de memoria = 64 MB = 64 * 1024 * 1024 = 67108864 bytes
```

Aplicamos el logaritmo en base 2 de 67108864 para obtener la cantidad de bits que dispone la memoria física:

```
Bits para dirección física = log 2 (67108864) = 26 bits
```

Ya con esto podríamos responder la pregunta, pero, ¿y si nos piden la cantidad de bits que necesitamos para el número de marco?

Tenemos la cantidad de bits para dirección física y la cantidad de bits de tamaño de marco. 
Con esto podemos calcular la cantidad de bits que necesitamos para especificar el número de marcos:

```
Bits para dirección física = Bits para número de marco + Bits para desplazamiento
26 bits = Bits para número de marco + 12 bits
26 bits - 12 bits = Bits para número de marco
14 bits = Bits para número de marco
```

---

**7**. Dado un sistema de paginación donde cada frame direcciona 2048 palabras de 32 bits cada una, 
se alojan en memoria principal 4 procesos, con los siguientes requerimientos de memoria:
A – 2048Kb, B – 6394Kb, C – 4160Kb, D – 2600Kb. 
Se pide, indicar cuántos frames demanda cada proceso y el mínimo de frames que debe tener la memoria para
almacenar a los 4 procesos simultáneamente.

**Resolución**

"Cada frame direcciona 2048 palabras de 32 bits cada una"

Podemos convertir el tamaño de palabra (32 bits) a bytes, luego calcular el tamaño total del frame en bytes,
y por último convertir el tamaño de frame a Kb para trabajar con los requerimientos de memoria de los procesos.

Conversión del tamaño de palabra (32 bits) a bytes:
```
Tamaño de palabra = 32 bits 
Tamaño de palabra = 32 bits / 8 = 4 bytes
```

Ahora calculo el tamaño en bytes del marco:
```
Tamaño de marco = 2048 palabras de 4 bytes
Tamaño de marco = 2048 * 4 bytes
Tamaño de marco = 8192 bytes
```

Ahora convierto el tamaño del marco a Kb:
```
Tamaño de marco = 8192 bytes
Tamaño de marco = 8192 bytes / 1024 = 8Kb
```

Ahora que tenemos el tamaño de marco en Kb, podemos calcular cuantos marcos necesita cada proceso.

| Proceso | Requisito de Memoria |      Frames necesarios       |
|:--------|:---------------------|:-----------------------------|
|   **A** |     2048Kb           | 2048Kb / 8Kb = 256           |
|   **B** |     6394Kb           | 6394Kb / 8Kb = 799.25 = 800  |
|   **C** |     4160Kb           | 4160Kb / 8Kb = 520           |
|   **D** |     2600Kb           | 2600Kb / 8Kb = 325           |

Si un número nos da con decimales, se redondea hacia arriba. 
Si no lo hacemos, estaríamos dejando un segmento de código de un proceso sin memoria a asignar.

Ahora sumamos todos los frames necesarios para calcular la cantidad de frames mínimos que necesitamos para almacenar
los cuatro procesos al mismo tiempo:

```
Mínimo de frames necesarios = 256 + 800 + 520 + 325 = 1901 frames
```

---

**8**. Sea un sistema de memoria virtual paginada con direcciones lógicas de 32 bits que
proporcionan un espacio lógico virtual de 2^20 páginas y con una memoria física de 32 MB.
¿Cuánto ocupará la tabla de marcos de página si cada entrada de la misma ocupa 32 bits?

**Resolución**

- Bits para dirección lógica = 32 bits
- Tamaño de entrada de tabla de marcos = 32 bits
- Memoría física = 32 MB

Para saber cuanto va a ocupar la tabla de marcos, necesitamos saber:
- Cantidad de entradas
- Tamaño de entradas
El tamaño de entrada ya lo tenemos, nos falta la cantidad de entradas. Una entrada = un marco = una página,
por lo tanto tenemos que calcular el tamaño de una página (o su desplazamiento).

Como tenemos la cantidad de bits que ocupa una dirección lógica, y la cantidad de páginas, podemos calcular la cantidad de bits que ocupa el número de página, y a partir de este dato, podemos calcular la cantidad de bits que ocupa el desplazamiento.

```
Bits para número de página = log 2 (2^20) = 20 bits
```

Ahora calculamos la cantidad de bits necesarios para el desplazamiento:

```
Bits para desplazamiento = Bits para dirección lógica - Bits para número de página
Bits para desplazamiento = 32 bits - 20 bits
Bits para desplazamiento = 12 bits
```

A partir de la cantidad de bits que necesitamos para el desplazamiento, podemos obtener el tamaño de página:

```
Tamaño de página = 2^12 bytes = 4096 bytes = 4KB
```

Ahora que tenemos el tamaño de página, asumimos que el tamaño de marco es igual a éste, y podemos calcular la cantidad de marcos que se pueden almacenar en memoria:

```
Número de marcos = Tamaño de memoria física / Tamaño de marco
Número de marcos = 32MB / 4KB
Número de marcos = 32MB * 1024 / 4KB
Número de marcos = 32768KB / 4KB
Número de marcos = 8192 marcos
```

Finalmente, con el número de marcos, podemos saber cuánto ocupa la tabla de marcos:

```
Tamaño tabla de marcos = Número de entradas * Tamaño de entrada
Tamaño tabla de marcos = 8192 marcos * 32 bits
Tamaño tabla de marcos = 262144 bits = 32768 bytes = 32KB
```

---

## [Volver atrás](readme.md)