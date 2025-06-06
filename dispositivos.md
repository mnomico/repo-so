## [Volver atrás](readme.md)

# Dispositivos de entrada y salida

## Índice

- [Guía Teórica](#guía-teórica)

- [Ejercicios](#ejercicios)

## Guía Teórica

1. ¿Qué son los spooling y el buffering en el contexto de E/S? ¿En qué se diferencian y qué problemas ayudan a resolver?

Son técnicas de administración de E/S que buscan mejorar la eficiencia y coordinación entre los dispositivos de entrada/salida (que suelen ser lentos) y el procesador (mucho más rápido).

Buffering consiste en utilizar áreas intermedias de memoria (buffers) donde se almacenan temporalmente los datos mientras se transfieren entre un dispositivo de E/S y el procesador.

Sirve para:
- Evitar que el procesador quede bloqueado esperando a que un dispositivo lento complete una operación.
- Permitir que los dispositivos trabajen de forma asíncrona respecto al procesador.
- Mejorar el rendimiento general del sistema.

Spooling (Simultaneous Peripheral Operations On-Line) es una técnica más general que implica colocar los datos de una operación de E/S en un archivo o área de almacenamiento intermedio en disco (spool) antes de enviarlos al dispositivo de destino.

Sirve para:
- Permitir que varios procesos puedan generar operaciones de E/S sin esperar que el dispositivo esté libre.
- Centralizar y organizar el acceso a dispositivos compartidos (como impresoras o correos).
- Evitar que procesos se bloqueen esperando el uso exclusivo de un dispositivo lento o único.

| Buffering                                                                   |  Spooling                                                               |
| :----------------------------------------------------------------------------- | :------------------------------------------------------------------------ |
| Usa **memoria RAM** para almacenar datos temporalmente.                        | Usa **archivos en disco** como almacenamiento intermedio.                 |
| Pensado para mejorar la eficiencia de **una transferencia de E/S** específica. | Pensado para coordinar el acceso a **dispositivos compartidos**.          |
| Suele trabajar en **tiempo real o casi inmediato**.                            | Se basa en **colas o archivos temporales** que pueden procesarse después. |
| Gestiona datos en **bloques pequeños o buffers**.                              | Gestiona **operaciones completas o archivos**.                            |
| Ej: buffer de audio o video, buffer de teclado.                                | Ej: cola de impresión, servidor de correo.                                |

Resuelven los siguientes problemas:
- Reducen los tiempos de espera del procesador por operaciones de E/S.
- Permiten el trabajo concurrente de procesos y dispositivos lentos.
- Organizan el acceso a recursos compartidos como impresoras o discos.
- Aumentan la eficiencia y rendimiento del sistema operativo.

---

2. ¿Cuál es la función del módulo de gestión de dispositivos (device driver) en un sistema operativo y cómo interactúa con el sistema operativo y el hardware?

Un device driver es un módulo de software dentro del sistema operativo que permite que el sistema y las aplicaciones puedan comunicarse correctamente con un dispositivo de hardware.

- Traduce las peticiones de alto nivel del sistema operativo (como “leer este archivo del disco” o “enviar datos por la impresora”) a instrucciones específicas que el hardware puede entender y ejecutar.
- Oculta los detalles técnicos del hardware al resto del sistema operativo, proporcionando una interfaz estandarizada para que todos los dispositivos se gestionen de forma coherente aunque sean de diferentes marcas o modelos.
- Gestiona operaciones de E/S (lectura, escritura, control, configuración) controlando el acceso a los dispositivos de forma segura y eficiente.

Interacción con el sistema operativo y el hardware:
1. Una aplicación solicita una operación de E/S (ej: leer un archivo).
2. El sistema operativo envía la solicitud al device driver correspondiente.
3. El driver traduce esa solicitud en comandos específicos para el hardware.
4. El hardware ejecuta la operación y devuelve el resultado al driver.
5. El driver notifica al sistema operativo, que a su vez informa a la aplicación.

---

3. ¿Cuál es el objetivo de un administrador de interrupciones y la de un driver del dispositivo?

El administrador de interrupciones (interrupt handler o interrupt controller) es responsable de:
- Detectar, gestionar y atender interrupciones generadas por dispositivos de hardware, temporizadores, o incluso por software.
- Decidir qué hacer cuando ocurre una interrupción:
    - Pausar temporalmente la ejecución del proceso actual.
    - Guardar su estado (contexto).
    - Atender la interrupción mediante una rutina específica (ISR, Interrupt Service Routine).
    - Restaurar el estado del proceso previo y reanudar su ejecución.

Sirve para que los dispositivos puedan notificar al procesador de eventos importantes (ej: llegó un dato desde el teclado, terminó de transferirse un archivo) sin tener que esperar activamente (polling).

El driver del dispositivo es un módulo de software que:
- Traduce las solicitudes del sistema operativo o de las aplicaciones en comandos específicos que entiende el hardware.
- Administra y controla las operaciones del dispositivo (lectura, escritura, configuración, etc.).
- Recibe información del hardware y la devuelve de forma comprensible al sistema operativo.

Sirve para abstraer las diferencias entre distintos dispositivos y permitir que el sistema operativo y las aplicaciones trabajen con ellos mediante una interfaz común, sin preocuparse por los detalles técnicos.

---

4. ¿Qué es la abstracción de dispositivo y cómo ayuda a lograr la independencia de hardware en el diseño del sistema operativo?

La abstracción de dispositivo es un mecanismo por el cual el sistema operativo oculta los detalles específicos de hardware y ofrece una interfaz uniforme y estandarizada para que las aplicaciones y procesos interactúen con los dispositivos de entrada/salida (E/S).

Gracias a esta abstracción:
- Las aplicaciones no necesitan conocer cómo funciona un dispositivo específico (por ejemplo, cómo se comunica una impresora HP frente a una Epson).
- Se puede cambiar un dispositivo físico por otro de diferente marca o modelo sin tener que modificar las aplicaciones ni el resto del sistema operativo.
- El sistema operativo se vuelve más flexible, modular y portable, ya que sólo los drivers de dispositivo se encargan de las diferencias concretas de hardware.

---

5. ¿Qué se entiende por independencia del dispositivo?

La independencia del dispositivo se refiere a la capacidad de una aplicación o sistema para funcionar correctamente sin depender de un tipo específico de hardware o dispositivo. En otras palabras, una aplicación independiente del dispositivo puede ejecutarse en diferentes dispositivos o plataformas sin requerir modificaciones significativas en su código o funcionalidad.

---

6. Describe las principales funciones del sistema operativo relacionadas con la gestión de E/S. ¿Cómo se organiza la pila de  software de E/S desde la aplicación hasta el dispositivo físico?

Las funciones principales del sistema operativo relacionadas con la gestión de E/S son:

| Función                                 | Descripción                                                                                              |
| :----------------------------------------- | :---------------------------------------------------------------------------------------------------------- |
| **Control de dispositivos**                | Gestiona la activación, desactivación y configuración de dispositivos.                                      |
| **Planificación de E/S**                   | Determina qué peticiones de E/S se atienden y en qué orden, para optimizar el uso de recursos.              |
| **Gestión de buffers**                     | Utiliza áreas de memoria intermedias (buffers) para almacenar datos mientras se transfieren.                |
| **Gestión de caché**                       | Almacena datos frecuentemente usados en memoria para acelerar accesos a dispositivos lentos.                |
| **Spooling**                               | Administra trabajos en cola, como la impresión, para evitar que un proceso monopolice un recurso.           |
| **Asignación y liberación de recursos**    | Controla qué proceso accede a qué dispositivo y cuándo, evitando conflictos y asegurando la disponibilidad. |
| **Detección y manejo de errores**          | Supervisa y gestiona errores que ocurren durante las operaciones de E/S.                                    |
| **Interfaz de abstracción de dispositivo** | Ofrece una interfaz uniforme a las aplicaciones independientemente del hardware subyacente.                 |

La pila de software de E/S se organiza en capas o niveles, cada una con responsabilidades bien definidas. Esto permite modularidad, abstracción y facilidad de mantenimiento.

| Capa                                      | Descripción                                                                |
| :---------------------------------------- | :------------------------------------------------------------------------- |
| **Aplicación**                            | Solicita operaciones de E/S sin preocuparse por cómo se realizan.          |
| **Llamadas al sistema**                   | Proveen funciones estandarizadas para E/S (open, read, write, etc.).       |
| **Gestor de E/S del SO**                  | Coordina operaciones de E/S, gestiona buffers, decide orden de atención.   |
| **Driver de dispositivo (device driver)** | Controla el hardware específico, traduce comandos genéricos a específicos. |
| **Dispositivo físico**                    | Realiza la operación física de E/S.                                        |

---

7. ¿Por qué los archivos de salida de la impresora normalmente se manejan por cola de impresión en el disco antes de ser impresos?

Porque la impresora es un dispositivo de E/S lento y secuencial, y para evitar que un proceso o usuario tenga que esperar a que termine de imprimirse un archivo antes de continuar, el sistema operativo usa spooling.

Ventajas de usar colas de impresión:

|  Ventaja                                      |  Descripción                                                              |
| :-------------------------------------------- | :-------------------------------------------------------------------------- |
| **Evita bloquear procesos**                   | Los programas no tienen que esperar a que el trabajo se imprima.            |
| **Permite la planificación de impresiones**   | Se pueden ordenar, pausar, reanudar o cancelar trabajos en la cola.         |
| **Mejora el uso del sistema**                 | Permite que varios procesos envíen trabajos simultáneamente sin conflictos. |
| **Reduce la pérdida de datos**                | Si la impresora falla o se apaga, los trabajos siguen guardados en disco.   |
| **Permite gestionar prioridades de trabajos** | Se pueden organizar según importancia o tamaño.                             |

Si no existiera este mecanismo:
- Solo un proceso podría imprimir a la vez.
- El proceso que imprime quedaría bloqueado hasta terminar.
- Si la impresora falla, se perdería el trabajo o todo se detendría.

---

8. Describa en qué consiste el estancamiento y qué condiciones deben darse para que se produzca.

(esto es de procesos, no se qué hace acá)

El estancamiento o deadlock es una situación en un sistema operativo donde un conjunto de procesos quedan bloqueados permanentemente, porque cada uno espera por un recurso que está siendo retenido por otro proceso del mismo conjunto.

|  Condición                        |  Descripción                                                                                                          |
| :---------------------------------- | :---------------------------------------------------------------------------------------------------------------------- |
| **Mutua exclusión**                 | Al menos un recurso debe estar en modo exclusivo (solo un proceso puede usarlo a la vez).                               |
| **Retención y espera**              | Un proceso que ya posee uno o más recursos puede solicitar recursos adicionales y debe esperar si no están disponibles. |
| **No expropiación (No-preemption)** | Los recursos no se pueden quitar a un proceso hasta que los libere voluntariamente.                                     |
| **Espera circular**                 | Debe existir una cadena de procesos, donde cada uno espera un recurso que otro de la cadena posee.                      |


---

9. ¿Qué ventaja introduce la capacidad de “localización superpuesta en unos discos”, y cuáles son los tiempos involucrados en la lectura o escritura de un bloque de disco?

La "localización superpuesta en unos discos" (interleaving) es una técnica que se utiliza en sistemas de almacenamiento, especialmente en discos duros, para mejorar la eficiencia en el acceso a los datos. La ventaja principal de esta técnica es mejorar el rendimiento de lectura y escritura al reducir los tiempos de acceso.

La localización superpuesta consiste en distribuir los datos de manera que la lectura o escritura de bloques en el disco no dependa de un acceso secuencial estricto a cada bloque de manera consecutiva. Esto puede implicar distribuir bloques de datos de forma alternada o en un patrón diseñado para aprovechar la velocidad de acceso del disco.

Cuando se realiza una operación de lectura o escritura en un disco, hay varios tiempos involucrados:
- Latencia (o tiempo de búsqueda): es el tiempo que tarda el disco en posicionar el cabezal de lectura/escritura sobre el bloque de datos deseado. Depende de la posición actual del cabezal y de cuán lejos esté el bloque de los datos solicitados. En discos duros, la latencia depende del tiempo de búsqueda, que se divide en tiempo de búsqueda aleatoria y tiempo de búsqueda secuencial.
	- El tiempo necesario para mover el brazo del cabezal a la pista donde se encuentra el bloque de datos es generalmente entre 4 y 10 milisegundos en discos tradicionales.
- Latencia rotacional: después de que el cabezal se haya posicionado correctamente, puede ser necesario esperar a que el bloque de datos se alinee con el cabezal, ya que los discos giran a una velocidad constante (revoluciones por minuto, RPM). La latencia rotacional es el tiempo que tarda el disco en girar hasta que el bloque deseado pasa por debajo del cabezal.
	- En discos tradicionales, la latencia rotacional es típicamente de 4 a 10 milisegundos dependiendo de la velocidad de rotación del disco.
- Transferencia de datos: este tiempo es relativamente bajo en comparación con la latencia y puede estar en el orden de los microssegundos o milisegundos, dependiendo de la velocidad de transferencia del disco.
- Tiempo total de acceso: es la suma de la latencia de búsqueda, la latencia rotacional y el tiempo de transferencia de datos.

        Tiempo total de acceso = Latencia de búsqueda + Latencia rotacional + Tiempo de transferencia

---

10. ¿Cómo maneja un sistema operativo los errores de E/S? Menciona tipos comunes de errores y las estrategias utilizadas para su detección y recuperación.

Los sistemas operativos gestionan las operaciones de entrada/salida (E/S) a través de controladores de dispositivo (drivers) y capas de software. Durante estas operaciones pueden ocurrir errores, que deben ser detectados, informados y en muchos casos recuperados para mantener la estabilidad del sistema.

Cuando ocurre un error:
- El driver o el hardware genera una señal de error o código de estado.
- El sistema operativo lo detecta y decide cómo manejarlo según la política del sistema y la gravedad.

Tipos comunes de errores de E/S:
| Tipo de error                     | Ejemplo                                                 |
| :----------------------------------- | :--------------------------------------------------------- |
| **Error de dispositivo**             | Falla de disco, desconexión de un pendrive.                |
| **Error de medio**                   | Sectores defectuosos en disco, error de lectura en CD/DVD. |
| **Error de comunicación**            | Paquetes de red corruptos o no recibidos.                  |
| **Tiempo excedido (timeout)**        | El dispositivo no responde en el tiempo esperado.          |
| **Error de paridad/datos corruptos** | Bytes recibidos con error de verificación de integridad.   |
| **Permisos o acceso denegado**       | Proceso intenta acceder a dispositivo no autorizado.       |

Estrategias para detección y recuperación de errores de E/S:

Detección:
- Códigos de estado devueltos por el driver.
- Interrupciones de error enviadas por el hardware.
- Chequeo de timeout si el dispositivo no responde a tiempo.
- Verificación de integridad (CRC, paridad, checksum).

Recuperación:
- Reintentar la operación (por ejemplo, una lectura de disco).
- Ignorar el error (si es leve o no crítico).
- Notificar al usuario o proceso afectado.
- Registrar el error en el log del sistema.
- Marcar sectores defectuosos para no usarlos (disco).
- Abortar la operación y cerrar la conexión al dispositivo.
- Remover o reinicializar el dispositivo si es posible.

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

Repetir con un segundo disco que tiene:

Latencia: 3 ms, Velocidad: 50 MB/s, mismo tamaño de bloque.

Comparar rendimiento y tomar decisiones basadas en los cálculos.

**a)**

    

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

---

7. En cuál de los cuatro estratos del software de E/S se hace cada una de las siguientes actividades:

    **a**. Determinación de la pista, sector y cabeza en una lectura de disco

    **b**. Conservación de una reserva de bloques usados recientemente

    **c**. Escritura de comandos en los registros de dispositivos

    **d**. Verificación de sí el usuario tiene permiso de utilizar el dispositivo

    **e**. Conversión de enteros binarios a ASCII para su impresión

| Actividad                                                                  | Estrato                                                                                                                                                         |
| :---------------------------------------------------------------------------- | :----------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **a. Determinación de la pista, sector y cabeza en una lectura de disco**     | **Controlador de dispositivos (3)** → porque aquí se traduce la dirección lógica a física y se envían los comandos específicos al hardware.                        |
| **b. Conservación de una reserva de bloques usados recientemente**            | **Manejadores independientes de dispositivos (2)** → aquí se administra la caché de bloques, buffers o bloques reservados de disco.                                |
| **c. Escritura de comandos en los registros de dispositivos**                 | **Controlador de dispositivos (3)** → porque este estrato interactúa directamente con los registros de control del hardware.                                       |
| **d. Verificación de si el usuario tiene permiso de utilizar el dispositivo** | **Nivel de usuario / Llamadas de sistema (1)** → porque el SO verifica los permisos de acceso antes de permitir la operación.                                      |
| **e. Conversión de enteros binarios a ASCII para su impresión**               | **Nivel de usuario / Llamadas de sistema (1)** → porque la conversión de formatos es parte de las funciones de la aplicación o el runtime antes de invocar la E/S. |


---

8. Indicar cómo se puede construir un disco en RAM, y para qué puede resultar ventajoso hacerlo.

Un RAM disk (o disco RAM) es una porción de la memoria RAM del sistema que se reserva y se utiliza como si fuera una unidad de disco (como /dev/ram0 en Linux). Se monta como un sistema de archivos y permite leer y escribir archivos en ella.

Ventajas:
- Altísima velocidad de acceso (lectura/escritura mucho más rápida que un disco físico o SSD).
- Ideal para:
    - Almacenar archivos temporales que se usan intensivamente y se descartan luego.
    - Ejecutar programas que hacen uso constante de archivos pequeños.
    - Compilar software o realizar operaciones de E/S pesadas más rápido.
    - Evitar escrituras innecesarias en discos SSD, prolongando su vida útil.

En Linux:
- Crear un directorio donde se montará:

        sudo mkdir /mnt/ramdisk
- Montar un sistema de archivos tmpfs (que vive en RAM):

        sudo mount -t tmpfs -o size=512M tmpfs /mnt/ramdisk

Eso crea un disco de 512 MB en RAM accesible desde /mnt/ramdisk.

---

9. Describir cómo funciona el software de entrada, el de salida de un terminal, y los problemas asociados.

Un terminal (físico o emulado) es un dispositivo de E/S secuencial, que permite a los usuarios interactuar con un sistema. El software de E/S de terminal se encarga de gestionar la entrada de teclado y la salida a pantalla, mediado por el sistema operativo.

**Software de Entrada de Terminal**

Responsabilidades:
- Leer caracteres ingresados desde teclado.
- Interpretar teclas especiales (retroceso, Enter, Ctrl+C…).
- Realizar edición de línea si es necesario (según modo de operación: crudo, cocinado…).
- Enviar los datos al programa o shell que los espera.

Modos comunes de entrada:
- Modo cocinado (canonical): la entrada se procesa línea por línea. El sistema espera a que el usuario pulse Enter para enviar la línea completa al programa.
- Modo crudo (raw): los caracteres se envían al programa inmediatamente sin procesar.

**Software de Salida de Terminal**

Responsabilidades:
- Recibir datos de los procesos que quieren mostrar información.
- Interpretar caracteres de control (salto de línea, tabulación, retroceso, códigos ANSI para colores, mover cursor, etc.).
- Mandar los caracteres a la pantalla o terminal emulada.

Consideraciones:
- La salida es secuencial.
- Se puede usar buffers de salida para optimizar el envío en bloques.