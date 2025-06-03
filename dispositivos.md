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

**1**. Breve investigación

    - Clasificación de dispositivos de E/S: ejemplos y características.
    - Diferencias entre dispositivos de carácter y de bloque.
    - Explicación de los tres métodos de E/S: programada, con interrupciones, y DMA.
    - Rol del sistema operativo en la gestión de E/S.
    - Ejemplos de cómo distintos sistemas operativos (Windows, Linux) manejan dispositivos de E/S.

### Clasificación de dispositivos de E/S

| Clasificación         | Ejemplos                     | Características                                                         |
| :-------------------- | :--------------------------- | :---------------------------------------------------------------------- |
| **De Entrada**        | Teclado, Mouse, Sensor       | Solo envían datos al sistema.                                           |
| **De Salida**         | Monitor, Impresora           | Solo reciben datos del sistema.                                         |
| **De Entrada/Salida** | Disco duro, Pantalla táctil  | Pueden enviar y recibir datos.                                          |
| **De Carácter**       | Teclado, Mouse, Puerto serie | Transmiten secuencias de bytes, sin estructura de bloques.              |
| **De Bloque**         | Disco duro, SSD, DVD         | Transmiten datos en bloques de tamaño fijo, pueden posicionarse (seek). |

### Diferencias entre dispositivos de caracter y de bloque

| Dispositivo de Carácter                                  | Dispositivo de Bloque                        |
| :------------------------------------------------------- | :------------------------------------------- |
| Transfieren datos como secuencias de caracteres (bytes). | Transfieren datos en bloques de tamaño fijo. |
| No permiten acceso aleatorio.                            | Permiten acceso aleatorio (seek).            |
| Ejemplos: teclado, mouse, puerto serie.                  | Ejemplos: disco duro, SSD, pendrive.         |
| No almacenan información intermedia.                     | Pueden almacenar información en caché.       |

### Métodos de E/S

| Método de E/S                      | Descripción                                                                             | Ventajas      | Desventajas                          |
| :--------------------------------- | :-------------------------------------------------------------------------------------- | :------------ | :----------------------------------- |
| **E/S Programada**                 | La CPU espera a que el dispositivo esté listo y transfiere los datos manualmente.       | Simple        | Ineficiente: la CPU queda bloqueada. |
| **E/S con Interrupciones**         | El dispositivo interrumpe a la CPU cuando está listo para transferir datos.             | Más eficiente | Ligeramente más compleja.            |
| **DMA (Acceso Directo a Memoria)** | El controlador transfiere datos entre memoria y dispositivo sin intervención de la CPU. | Muy eficiente | Requiere hardware DMA.               |

### Rol del Sistema Operativo en la Gestión de E/S

El sistema operativo (SO) abstrae y gestiona los dispositivos de E/S. Sus funciones incluyen:

- Detectar y configurar dispositivos conectados.
- Proveer controladores (drivers) que traducen operaciones de alto nivel en instrucciones para el hardware.
- Planificar y administrar las operaciones de E/S para optimizar el uso del CPU y evitar conflictos.
- Gestionar errores y garantizar acceso seguro a los dispositivos.
- Proveer interfaces estándar para que las aplicaciones no dependan de detalles de hardware.

### Ejemplos: Cómo manejan E/S distintos sistemas operativos

| Sistema Operativo | Gestión de Dispositivos de E/S                                                                                                                                   | Características                                                                                                    |
| :---------------- | :--------------------------------------------------------------------------------------------------------------------------------------------------------------- | :----------------------------------------------------------------------------------------------------------------- |
| **Linux**         | Usa archivos especiales en `/dev` (por ejemplo `/dev/sda`, `/dev/tty0`). Provee una interfaz unificada mediante el sistema de archivos virtual `/proc` y `/sys`. | Los dispositivos son tratados como archivos. Utiliza controladores modulares.                                      |
| **Windows**       | Usa el modelo **I/O Manager** y controladores específicos (kernel-mode drivers). Los dispositivos tienen nombres como `COM1`, `LPT1`, `C:`.                      | Emplea un modelo jerárquico de controladores (I/O Request Packets). Dispositivos accesibles desde APIs de Windows. |

---

**2**. Estudio de Caso

    Seleccionar un dispositivo real (por ejemplo, disco rígido, teclado, mouse, impresora o escáner) y responder:
    - ¿Cómo se comunica con el sistema operativo?
    - ¿Qué tipo de controlador requiere?
    - ¿Cómo se realiza la gestión de sus operaciones de E/S?
    - ¿Qué impacto tiene su velocidad o latencia en el rendimiento general del sistema?

**Dispositivo: Disco Rígido (HDD)**

El disco rígido se comunica con el sistema operativo a través de un controlador de dispositivo (driver) específico para la interfaz que utiliza (por ejemplo SATA, NVMe, IDE).

El flujo general es:

- El sistema operativo envía solicitudes de lectura/escritura al controlador.
- El controlador traduce esas solicitudes en comandos que entiende el disco rígido.
- El disco rígido responde con los datos o confirma la operación.
- Puede usarse E/S con interrupciones o DMA para las transferencias.

El disco rígido requiere un controlador de bloque, ya que:

- Transfiere datos en bloques de tamaño fijo (512 bytes, 4 KB, etc.)
- Permite acceso aleatorio (seek) a posiciones específicas del disco.

El sistema operativo gestiona las operaciones de E/S del disco de la siguiente forma:

- Planificación de E/S: usa algoritmos para optimizar el orden de lectura/escritura
- Caché de disco: mantiene en memoria datos recientemente leídos o a escribir.
- Métodos de E/S:
    - Con interrupciones: el disco avisa a la CPU cuando completa una operación.
    - DMA (Direct Memory Access): transfiere datos directo a la RAM sin intervención del CPU, liberando recursos.
- Gestión de buffers y caché de páginas para organizar los datos antes y después de acceder al disco.

El disco rígido tiene un impacto considerable en el rendimiento del sistema porque:

- Alta latencia (tiempo en posicionar cabezal y esperar al sector).
- Es más lento que RAM y CPU: tiempos de acceso de milisegundos vs. nanosegundos.
- Afecta operaciones como:
    - Carga de programas
    - Acceso a archivos
    - Uso de memoria virtual (swap)

---

**3**. Exploración práctica sobre Linux

    - Listar los dispositivos de E/S presentes con el comando lsblk, o dmesg (describir los mensajes de pantalla).
    - Identificar los controladores usados.
    - Analizar los logs del sistema relacionados con eventos de E/S (mirar subdirectorio Var).
    - Realizar una prueba de lectura/escritura en disco y medir tiempos con “dd”.

**Comando lsblk**

Muestra los dispositivos de bloque (discos, particiones):

    lsblk

Salida ejemplo:

    NAME   MAJ:MIN RM   SIZE RO TYPE MOUNTPOINTS
    sda      8:0    0 232.9G  0 disk 
    ├─sda1   8:1    0   512M  0 part /boot
    ├─sda2   8:2    0    16G  0 part [SWAP]
    └─sda3   8:3    0 216.4G  0 part /

**Comando dmesg**

Muestra mensajes del kernel, incluyendo detección de dispositivos al iniciar.

    dmesg | grep sd

**Comando grep**

Filtra una salida de texto por la palabra que se pasa como parámetro. En el caso anterior, de la salida que brinda dmesg solo se muestran aquellas líneas que contienen sd

Salida ejemplo:

    [    2.345678] sd 0:0:0:0: [sda] 234441648 512-byte logical blocks
    [    2.345689] sd 0:0:0:0: [sda] Attached SCSI disk

**Comando lsmod**

Para ver qué módulos (drivers) usa el kernel para manejar los dispositivos:

    lsmod

Salida ejemplo:

    ahci                   45056  0
    libahci                32768  1 ahci
    sd_mod                 57344  4

Los logs se guardan en /var/log/. Para buscar la actividad de los discos:

    cat /var/log/syslog | grep sd

El comando cat se utiliza para la lectura de archivos, syslog es el log que registra eventos y errores en el sistema.

**Prueba de lectura/escritura en disco con dd:**

Para medir velocidad de escritura:

    dd if=/dev/zero of=prueba.img bs=1M count=1024 status=progress

El comando dd copia bloques de datos desde un origen (if, input file) hacia un destino (of, output file).
Se usa mucho en Linux para clonar discos, hacer backups, o medir rendimiento.

- **if=/dev/zero**: origen de los datos. /dev/zero es un dispositivo especial que genera ceros (0x00) infinitos.
- **of=prueba.img**: archivo destino.
- **bs=1M**: tamaño de cada bloque que se copia en cada operación.
- **count=1024**: cantidad de bloques a copiar.
- **status=progress**: muestra en pantalla el progreso en tiempo real.

Salida ejemplo:

    1073741824 bytes (1.1 GB, 1.0 GiB) copied, 3.21034 s, 334 MB/s

Para medir velocidad de lectura:

    dd if=prueba.img of=/dev/null bs=1M status=progress

- **of=/dev/null**: destino especial que descarta todo lo que recibe (sirve para medir lectura sin escribir nada).

---

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

**Resolución**

Dado el siguiente dispositivo de disco:

- Latencia: 8 ms
- Velocidad de transferencia: 100 MB/s
- Tamaño de bloque: 4 KB

**a)** 

    Tamaño de bloque: 4 KB -> 0.004MB
    E = L + B / T
    E = 8ms + 0.004MB / 100MB/s
    E = 8ms + 0.00004s
    E = 8ms + 0.04ms
    E = 8.04ms

El tiempo total de E/S para una sola operación es 8.04 milisegundos.

**b)**

    E = 8.04ms
    E = 0.00804s
    Operaciones completas en 1 segundo:
    1s / 0.00804s = 124.3781

En 1 segundo se pueden hacer 124 operaciones completas.

**c)**

    Tamaño de bloque: 0.004MB
    Datos a leer: 10MB
    Tiempo en completar una operación: 8.04ms
    Cantidad de bloques a leer = 10MB / 0.004MB = 2500 bloques
    Cantidad que tomaría leer 2500 bloques = 2500 * 8.04ms = 20100ms = 20.1s

---

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