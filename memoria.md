## [Volver atrás](readme.md)

# Administración de Memoria

## Índice

[Conceptos](#conceptos)

[Paginación](#paginación)

[Ejercicios](#ejercicios)

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