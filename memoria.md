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
log 2 (16) = 4
```

Por lo tanto necesitamos 4 bits para representar el número de página.

Ahora necesitamos obtener la cantidad de bits para el desplazamiento o tamaño de página. Para obtenerla, calculamos el logaritmo en base 2 de 1024:

```
log 2 (1024) = 10
```
Por lo tanto necesitamos 10 bits para representar el desplazamiento de página.

Ahora que tenemos tanto los bits necesarios para especificar el número de página y para especificar el desplazamiento de página, podemos obtener la cantidad de bits necesarios para especificar una dirección lógica de la siguiente manera:

```
bits para dirección lógica = bits para número de página + bits para desplazamiento
bits para dirección lógica = 4 bits + 10 bits
bits para dirección lógica = 14 bits
```

**a.** Se necesitan 14 bits para especificar una dirección lógica.

Para saber cuantos bits necesitamos para especificar una dirección física, hacemos lo mismo que antes.

La única diferencia con lo anterior es que no tenemos el tamaño de marco, pero cuando no nos lo dicen, asumimos que es igual al tamaño de página. Por lo tanto:

- Número de marcos (m) = 64
- Desplazamiento (d) = 1024 bytes

Aplicamos el logaritmo en base 2 de 64 para saber los bits que necesitamos para representar el número de marcos:

```
log 2 (64) = 6
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

## [Volver atrás](readme.md)