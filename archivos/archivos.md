## [Volver atrás](../readme.md)

# Sistemas de Archivos

## Índice

- [Guía Teórica](#guía-teórica)

- [Ejercicios](#ejercicios)

---

## Guía Teórica

1. Describir las distintas operaciones que se pueden realizar sobre un archivo.

	- **Creación**: permite generar un nuevo archivo en el sistema de archivos. Reserva un espacio en disco, crea una entrada en el directorio correspondiente e inicializa los metadatos del archivo.
	- **Apertura**: antes de acceder a un archivo, se debe abrir. Se asigna un descriptor de archivo y carga los metadatos en memoria.
	- **Lectura**: permite extraer datos de un archivo abierto. Se leen bloques de datos en la memoria del proceso.
	- **Escritura**: guarda datos en un archivo, ya sea sobrescribiendo o agregando información.
	- **Cierre**: libera los recursos asociados al archivo y garantiza que los datos escritos se guarden correctamente en el disco.
	- **Eliminación**: borra un archivo del sistema, eliminando su entrada del directorio y liberando el espacio en disco.
	- **Cambio de nombre**.
	- **Búsqueda**: permite posicionarse en una parte específica del archivo.

---

2. Describir los diferentes métodos de acceso a los archivos, indicar si existen ventajas o desventajas.

	- **Acceso Secuencial**: los datos se leen o escriben en un orden secuencial, desde el principio hasta el final del archivo.
	    
        **Ventajas**:
		- Simple y fácil de implementar.
		- Eficiente para operaciones que requieren procesar todo el archivo.
		
        **Desventajas**:
		- Ineficiente para acceder a datos específicos en una posición aleatoria.
	- **Acceso Aleatorio** (o Directo): permite acceder a cualquier parte del archivo directamente, sin necesidad de recorrer los datos anteriores.
		
        **Ventajas**:
		- Rápido acceso a cualquier posición del archivo.
		
        **Desventajas**:
		- Más complejo de implementar que el acceso secuencial, y puede requerir más recursos.
	
    - **Acceso Indexado**: utiliza un índice para acceder a los datos del archivo. El índice contiene punteros a las ubicaciones de los datos dentro del archivo.
		
        **Ventajas**:
		- Combina las ventajas del acceso secuencial y aleatorio.
		- Permite búsquedas rápidas y eficientes, especialmente en archivos grandes.
		
        **Desventajas**:
		- Requiere espacio adicional para almacenar el índice.
		- La gestión del índice puede añadir complejidad al sistema.

---

3. Describir el método de asignación contigua. ¿Qué entiende por compactación?
	
    Es un método de almacenamiento en el que un archivo se almacena en bloques contiguos del disco
	
    - Se busca un bloque contiguo de tamaño suficiente en el disco.
	- Se asigna todo el espacio necesario en una ubicación única y continua.
	- Se almacena una referencia en la tabla de archivos indicando la dirección inicial y la longitud del archivo.
	
    **Ventajas**:
	- Rápido acceso secuencial y directo.
	- Implementación simple.
	- Eficiencia en lectura y escritura, ya que reduce los movimientos del cabezal del disco.
	
    **Desventajas**:
	- Fragmentación externa.
	- Dificultad para expandir archivos.
	- Uso ineficiente del espacio: si un archivo reserva más espacio del necesario para futuras expansiones, puede desperdiciar almacenamiento.
	
    La **compactación** es una técnica utilizada para reducir la fragmentación externa en la asignación contigua. Consiste en mover archivos en el disco para juntar los espacios libres y crear bloques contiguos más grandes.
	
    Requiere tiempo y procesamiento, ya que implica mover datos físicamente en el disco.

---

4. Describir el método de asignación enlazada.
		
    Es un método de almacenamiento en el que cada bloque contiene un puntero que indica la ubicación del siguiente bloque del archivo.
	
    - Cuando se crea un archivo, el sistema encuentra bloques disponibles. Cada bloque almacena parte del archivo + un puntero al siguiente bloque.
	- El sistema mantiene una referencia al primer bloque (cabeza) del archivo en la tabla de archivos.
	- Para leer el archivo, el sistema sigue la cadena de punteros hasta el último bloque.
	
    **Ventajas**:
	- Elimina la fragmentación externa.
	- Facilita la expansión de archivos.

	**Desventajas**:
	- Acceso más lento que el contiguo.
	- Mayor uso de espacio.
	- No es eficiente para acceso directo.

---

5. Describir el método de asignación indexada.
	
    Es un método en el que los bloques de un archivo se almacenan en cualquier lugar del disco. Sus ubicaciones se guardan en un bloque índice.
	
    - Cada archivo tiene un bloque índice que almacena las direcciones de todos los bloques que contienen sus datos.
	- Para acceder a un bloque específico, el sistema primero consulta el bloque índice y luego accede directamente al bloque de datos.
	
    **Ventajas**: 
	- Acceso directo eficiente.
	- Elimina la fragmentación externa.
	- Más eficiente que la asignación enlazada.
		
    **Desventajas**:
	- Uso adicional de espacio.
	- Límite de tamaño.
	- Sobrecarga en archivos pequeños.

---

6. Crear un cuadro comparativo de los distintos métodos de asignación de espacio en disco indicando ventajas y desventajas.	![[asignacionDeEspacio.png]]
    
    | Método                  | Descripción                                                                      | Ventajas                                                                      | Desventajas                                                                                                        |
    |:------------------------|:---------------------------------------------------------------------------------|:------------------------------------------------------------------------------|:-------------------------------------------------------------------------------------------------------------------|
    | **Asignación Contigua** | Los bloques del archivo se almacenan de forma contigua en el disco.              | Acceso rápido (acceso directo y secuencial eficiente). Fácil de implementar.  | Fragmentación externa. Difícil expansión de archivos.                                                              |
    | **Asignación Enlazada** | Cada bloque contiene un puntero al siguiente, formando una lista enlazada.       | No hay fragmentación externa. Permite archivos dinámicos sin realocación.     | Acceso más lento (se debe seguir la cadena de punteros). No permite acceso aleatorio eficiente.                    |
    | **Asignación Indexada** | Se usa un bloque índice que almacena las direcciones de los bloques del archivo. | Permite acceso aleatorio eficiente. No hay fragmentación externa.             | Se necesita espacio adicional para el bloque índice. Puede requerir múltiples bloques índice en archivos grandes.  |

---

7. ¿Qué ventajas introduce el empleo de un sistema de directorio?
	
    El uso de un sistema de directorios mejora la organización, seguridad y eficiencia del almacenamiento, facilitando la gestión de archivos en sistemas operativos modernos.

---

8. Describa cada uno de los componentes de un sistema de archivos que se tiene luego de formatear lógicamente un disco de almacenamiento masivo, en UNIX.
	
    - **Bloque de arranque**: se encuentra en el primer bloque del sistema de archivos. Contiene el código del cargador de arranque si el sistema de archivos es el principal del disco.
	- **Superbloque**: contiene metadatos sobre el sistema de archivos, como:
		- Tamaño del sistema de archivos.
		- Número de inodos y bloques de datos.
		- Ubicación del bloque índice de inodos.
		- Información sobre espacio libre y ocupado.
	- **Tabla de inodos**: es una estructura de metadatos donde cada archivo y directorio tiene un inodo asociado. Cada inodo almacena información sobre un archivo:
		- Tipo de archivo.
		- Permisos y propietario.
		- Tamaño del archivo.
		- Tiempos de acceso, modificación y creación.
		- Punteros a bloques de datos.
	- **Bloques de datos**: almacenan el contenido de los archivos.
	- **Gestión del espacio libre**: mantiene un registro de los bloques y los inodos libres.

---

9. Ídem anterior para un sistema del tipo DOS.
	
    - **Sector de arranque**: ubicado en el primer sector del disco. Contiene el código de arranque del sistema y los parámetros del sistema de archivos, como:
		- Tamaño del sector y del clúster.
		- Número de sectores por pista y cabezales.
		- Ubicación de la Tabla de Asignación de Archivos (FAT).
	- **FAT**: almacena la asignación de los clústeres en el disco. Cada entrada en la FAT indica si un clúster:
		- Está libre.
		- Es el final de un archivo.
		- Está asignado a un archivo y enlazado a otro clúster.
	- **Directorio raíz**: contiene entradas de archivos y subdirectorios, cada una con:
		- Nombre del archivo.
		- Atributos.
		- Fecha y hora de creación/modificación.
		- Número del primer clúster del archivo.
		- Tamaño del archivo.
	- **Área de datos**: contiene el contenido de los archivos. Se divide en clústeres (bloques de tamaño fijo). Los archivos pueden ocupar múltiples clústeres no contiguos, con la FAT manteniendo la lista de enlaces.

---

10. ¿Qué utilidad tiene el campo de bits o free list?
	
    En los sistemas de archivos, se necesita una forma eficiente de rastrear qué bloques o clústeres están libres y cuáles están ocupados. Para ello, se utilizan dos métodos principales.
	
    - **Bitmap** (Campo de Bits): es una estructura en la que cada bit representa un bloque o clúster (0 = libre; 1 = ocupado).
		
        **Ventajas**: 
		- Búsqueda eficiente de bloques libres secuenciales.
		- Bajo consumo de espacio.
		- Se puede recorrer secuencialmente para encontrar fragmentación.
	    
        **Desventajas**:
		- Puede ser ineficiente en discos muy grandes, ya que la estructura crece proporcionalmente.
		- Requiere exploración para encontrar un bloque libre en sistemas muy fragmentados.
	
    - **Free List** (Lista de Bloques Libres): es una lista enlazada de bloques disponibles. Cada bloque libre contiene un puntero al siguiente bloque libre.
	
    	**Ventajas**:
		- Se puede recorrer fácilmente sin necesidad de leer toda la estructura.
		- No requiere un área reservada fija para almacenar la lista.
	
    	**Desventajas**:
		- Acceso menos eficiente que un bitmap, ya que se debe recorrer la lista.
		- Puede generar fragmentación si no se ordenan los bloques libres correctamente.

---

11. ¿Cómo está conformado el i-nodo, describa cada parte? De qué forma se los emplea al guardar o leer un archivo en disco.
	
    - **Número del i-nodo**: identificador único.
	- **Permisos de acceso** (r = read / w = write / x = execute).
	- **Propietario** (UID) y **grupo** (GID).
	- **Tiempos de acceso**: almacena los tres tipos de tiempos del archivo:
		- Acceso (atime): La última vez que se accedió al archivo.
		- Modificación (mtime): La última vez que se modificó el contenido del archivo.
		- Cambio de i-nodo (ctime): La última vez que se cambió la estructura del i-nodo.
	- **Tamaño del archivo** (en bytes).
	- **Punteros a bloques de datos**: existen varios tipos de punteros:
		- Punteros directos: señalan bloques de datos directamente.
		- Punteros indirectos: apuntan a bloques que contienen punteros a bloques de datos.
		- Punteros dobles y triples indirectos: usados cuando el archivo es muy grande y requiere más punteros.
	- **Número de enlaces**: indica cuántos enlaces duros apuntan a este i-nodo (es decir, cuántos nombres de archivo corresponden al mismo i-nodo). Cuando el contador llega a cero, el sistema puede liberar el i-nodo y sus bloques asociados.
	
    Cuando se **crea o escribe** un archivo, el sistema operativo realiza los siguientes pasos:
	- Asignación del i-nodo.
	- Ajuste de los permisos y metadatos: Se establecen el propietario, grupo, y los permisos de acceso.
	- Asignación de bloques de datos: Se ubican bloques de datos en el disco donde se almacenará el contenido del archivo. El i-nodo se actualiza con punteros a estos bloques.
	- Actualización del contador de enlaces: Si el archivo tiene enlaces duros, el contador aumenta.
	
    Cuando se **lee** un archivo, el sistema operativo realiza los siguientes pasos:
	- Recuperación del i-nodo: El sistema utiliza el número de i-nodo para acceder a la información sobre el archivo.
	- Acceso a los bloques de datos: Con los punteros del i-nodo, el sistema localiza los bloques de datos en disco y lee el contenido del archivo.
	- Lectura de metadatos: Se puede obtener información adicional como el tamaño del archivo, los tiempos de acceso, etc.

---

12. Ídem anterior para la FAT del DOS.
	
    La **FAT** es simplemente una lista de entradas, donde cada entrada representa un clúster del disco y contiene un valor de 12, 16 o 32 bits dependiendo de la versión de FAT (FAT12, FAT16 o FAT32).
	
    **Guardar un Archivo**:
	- Se busca espacio libre en la FAT.
	- Se asignan clústeres al archivo y se crea una lista enlazada.
	- Se actualiza el directorio raíz con la información del archivo (nombre, primer clúster, tamaño).
	
    **Leer un Archivo**:
	- El sistema busca el nombre del archivo en el directorio raíz.
	- Obtiene su primer clúster de la FAT.
	- Sigue la lista enlazada de clústeres en la FAT para recuperar todo el archivo.
	- Lee los datos del área de datos y los carga en memoria.

---

13. ¿Qué entiende por BootLoader? ¿Cuál es su contenido, bajo que tipo de formateo lógico?
	
    El **BootLoader** (o cargador de arranque) es un programa pequeño que se ejecuta cuando se enciende una computadora o dispositivo. Su principal función es cargar el sistema operativo en la memoria RAM y transferirle el control. El BootLoader es el primer software que se ejecuta después de que el BIOS/UEFI realiza las comprobaciones iniciales del hardware (POST, Power-On Self-Test).
	
    El BootLoader generalmente contiene:
	- Código de inicialización: realiza tareas básicas de configuración del hardware, como inicializar la memoria, los controladores de disco y otros dispositivos críticos.
	- Cargador del kernel: localiza el kernel del sistema operativo en el disco duro y lo carga en la memoria RAM.
	- Gestión de particiones: identifica la partición activa o la partición que contiene el sistema operativo.
	- Interfaz de usuario: algunos BootLoaders, como GRUB, ofrecen un menú para seleccionar entre múltiples sistemas operativos o kernels.
	- Módulos adicionales: algunos BootLoaders pueden cargar módulos adicionales, como controladores de hardware o sistemas de archivos, para facilitar el arranque.
	
    El BootLoader generalmente se almacena en una partición específica del disco duro o en un área reservada del medio de almacenamiento. Dependiendo del sistema, el formateo lógico y la ubicación pueden variar.
	
    El BootLoader debe ser compatible con el sistema de archivos de la partición donde reside el sistema operativo (por ejemplo, NTFS para Windows, ext4 para Linux, etc.).

---

14. Describir las operaciones posibles a realizar sobre un directorio.

	- Creción / eliminación de un directorio.
	- Apertura / lectura / modificación de un directorio.
	- Copiar un directorio.
	- Cambio de permisos y atributos.
	- Creación / eliminación de enlaces: permite crear y eliminar referencias (accesos directos) a archivos y directorios dentro del sistema de archivos.
	- Montaje / desmontaje de un directorio.

---

15. ¿Qué ventajas introduce una estructura de directorios arborescente?
	
    Un sistema de archivos con estructura de árbol jerárquico (o arborescente) organiza los archivos y directorios de manera estructurada, comenzando desde un directorio raíz (/ en Unix/Linux o C:\ en Windows) y permitiendo múltiples niveles de subdirectorios.
	
    **Ventajas**:
	- Organización y Estructura Clara
	- Uso Eficiente del Espacio: reduce la duplicación de archivos mediante enlaces y optimiza la asignación de espacio en disco al evitar archivos dispersos sin relación.
	- Permite Control de Acceso: se pueden establecer permisos de lectura, escritura y ejecución a nivel de directorio o subdirectorio.
	- Facilita la Búsqueda y Administración
	- Permite Implementar Sistemas de Seguridad y Backup: se pueden hacer copias de seguridad (backup) de directorios específicos sin necesidad de respaldar todo el sistema.
	- Mejora la Escalabilidad: permite agregar nuevas carpetas y archivos sin afectar el funcionamiento del sistema.

---

16. Indicar que inconvenientes se pueden llegar a tener en una estructura de directorios con forma de grafos acíclicos.
	
    Una estructura de directorios en forma de grafo acíclico dirigido permite que un mismo archivo o directorio tenga múltiples padres a través de enlaces duros o simbólicos. Esto introduce varias ventajas, como la reutilización de archivos sin duplicarlos, pero también algunos problemas:
	- Complejidad en la Gestión de Archivos y Directorios: como un archivo puede pertenecer a varios directorios, su administración se vuelve más difícil.
	- Eliminación de Archivos (Problema de Referencias): en sistemas que permiten enlaces duros, un archivo no se elimina inmediatamente al borrar un enlace a él. Se debe contar el número de referencias y eliminar el archivo solo cuando ninguna referencia lo usa. Si el conteo de referencias falla, el archivo puede quedar inaccesible pero seguir ocupando espacio.
	- Problema de Accesos y Permisos: si un archivo tiene varios padres, pueden existir conflictos con los permisos de acceso.
	- Complejidad en el Recorrido del Sistema de Archivos.
	- Posible Desincronización con Copias de Seguridad.

---

17. Indicar que tipos de protección se pueden incorporar a los archivos en general, qué ventaja aporta hacerlo.

	La protección de archivos es esencial en un sistema operativo para evitar accesos no autorizados, corrupción de datos y garantizar la seguridad de la información.
	
    - **Permisos de Usuario y Grupos** (Control de Acceso Basado en Usuarios): se basa en la asignación de permisos a usuarios y grupos. Se pueden establecer diferentes niveles de acceso ( (r)ead/(w)rite/e(x)ecute )
	- **Listas de Control de Acceso** (ACLs - Access Control Lists): son un método más flexible que los permisos tradicionales. Permiten definir permisos específicos para varios usuarios o grupos sobre un mismo archivo.
	- **Contraseñas**: se cifra el archivo con una clave secreta para que solo pueda ser abierto con una contraseña.

---

18. Indique cuántos subdirectorios encuentra en el directorio principal del disco rígido, de su instalación Linux. Describir cuál es el contenido de cada uno.

| Directorio        | Contenido               |
|:------------------|:------------------------|
| `/` (raíz)        | Contiene todos los archivos del sistema. Sin este, el sistema no puede funcionar. |
| `/bin`            | Contiene **ejecutables esenciales** (`ls`, `cp`, `mv`, `cat`, `bash`). Sin esto, no podrías usar comandos básicos. |
| `/sbin`           | Ejecutables de administración (`shutdown`, `fdisk`). Solo lo usa `root`. |
| `/etc`            | Contiene **archivos de configuración** (`/etc/passwd`, `/etc/fstab`, `/etc/network/interfaces`). Sin esto, el sistema no sabría cómo iniciar o configurarse. |
| `/home`           | Carpeta personal de los usuarios. Si se borra, se pierden los archivos de cada usuario. |
| `/root`           | Carpeta personal del usuario `root`. Si se borra, `root` pierde su configuración. |
| `/lib` y `/lib64` | Bibliotecas necesarias para los binarios de `/bin` y `/sbin`. Si se eliminan, los comandos básicos dejan de funcionar. |
| `/boot`           | Contiene el kernel (`vmlinuz`), el cargador de arranque (`grub`). Sin esto, **el sistema no arranca**. |
| `/dev`            | Archivos de dispositivos (`/dev/sda`, `/dev/tty`). Permite que el sistema acceda a discos, USBs y terminales. |
| `/proc` y `/sys`  | Contienen **información en tiempo real** sobre el sistema. Si desaparecen, algunos comandos como `top` o `ps` no funcionarían. |
| `/usr`            | Contiene programas y herramientas (`/usr/bin`, `/usr/lib`). Es donde se almacenan la mayoría de los ejecutables. |
| `/var`            | Contiene archivos **variables** como logs (`/var/log`), colas de impresión y bases de datos temporales. Si se borra, el sistema pierde registros importantes. |

---

## Ejercicios

Para los ejercicios lo más probable es que necesitemos permisos de superusuario. Para loguearse como superusuario se usa el comando:

```
su -
```

Una vez ingresado nos piden la contraseña, la ingresamos y ya estamos como root:

```
[nomico@nomico ~]$ su -
Password: 
[root@nomico ~]# 
```

---

**1**. Construya la siguiente estructura de directorio en su disco, 
indicar los comandos utilizados.

![Ejercicio 1](ej1.png)

Para crear directorios, utilizamos el comando mkdir (make directory), que se utiliza de la siguiente manera:

```
mkdir NOMBRE_DIRECTORIO
```

Pueden crearse varios directorios con una sola invocación de mkdir, por ejemplo:

```
mkdir rojo verde
```

Crea una carpeta "rojo" y una carpeta "verde".

Con el argumento -p podemos crear directorios y sus subdirectorios, por ejemplo:

```
mkdir -p hola/mundo
```

Crea el directorio "hola" y su subdirectorio "mundo".

Usamos el comando cd (change directory) para movernos entre los directorios. Se utiliza de la siguiente manera:

```
cd DIRECTORIO
```

El comando cd puede usarse también con "." o con "..". El "." hace referencia al directorio en el que nos ubicamos actualmente,
mientras que ".." hace referencia al directorio padre del directorio actual.

```
[root@nomico ~]# cd /home
[root@nomico home]# mkdir sueldos
[root@nomico home]# mkdir -p contab/arch
[root@nomico home]# mkdir -p contab/TXT
[root@nomico home]# mkdir -p textos/DOC
[root@nomico home]# mkdir -p hojasXLS/Horarios hojasXLS/Graph
[root@nomico home]# mkdir -p UNLu
```

---

**2**. En el subdirectorio UNLu se tiene un conjunto de archivos, se pide copiar aquellos cuya extensión sea:

"txt" en el subdirectorio ../textos/DOC,

".cpp" en ../contab/arch,

"txt" en /contab/TXT, 

"xls" en ../hojasXLS/Horarios, 

"grp" en ../hojasXLS/Graph. 

Indicar los comandos utilizados.

Primero creo unos archivos para hacer el ejercicio:

```
touch NOMBRE_ARCHIVO
```

El nombre del archivo también puede ser una ruta, por ejemplo:

```
touch ./cosas/texto.dat
```

Crea un archivo "texto.dat" dentro de la carpeta cosas del directorio actual.

```
[root@nomico home]# touch ./UNLu/archivo1.txt
[root@nomico home]# touch ./UNLu/archivo2.txt
[root@nomico home]# touch ./UNLu/archivo3.cpp
[root@nomico home]# touch ./UNLu/archivo4.txt
[root@nomico home]# touch ./UNLu/archivo5.xls
[root@nomico home]# touch ./UNLu/archivo6.grp
```

Para copiar los archivos utilizamos el comando cp. Se usa de la siguiente manera:

```
cp ARCHIVO DIRECTORIO_DESTINO
```

Ahora cuando queremos tomar un conjunto de archivos con un mismo formato, usamos un * seguido del formato del archivo.



- **".txt" en el subdirectorio /textos/DOC**
```
[root@nomico home]$ cp ./UNLu/*.txt ./textos/DOC
```

- **".cpp" en /contab/arch**
```
[root@nomico home]$ cp ./UNLu/*.cpp ./contab/arch
```

- **".txt" en /contab/TXT**
```
[root@nomico home]$ cp ./UNLu/*.txt ./contab/TXT
```

- **".xls" en /hojasXLS/Horarios**
```
[root@nomico home]$ cp ./UNLu/*.xls ./hojasXLS/Horarios
```

- **".grp" en /hojasXLS/Graph**
```
[root@nomico home]$ cp ./UNLu/*.grp ./hojasXLS/Graph
```

Otra manera de hacer esto sería ubicándonos en el directorio "UNLu"...

```
[root@nomico ~]$ cd home 
[root@nomico home]$ cd UNLu
```

... y a partir de acá hacer lo mismo que antes, pero en vez de indicar el directorio "UNLu" en cada referencia a un directorio, indicamos el directorio "home" de la siguiente manera, por ejemplo:

- **"txt" en el subdirectorio ../textos/DOC**
```
[root@nomico UNLu]$ cp *.txt ../textos/DOC
```

Cuando usamos ".." estamos haciendo referencia al directorio padre del directorio en el que nos situamos actualmente, en este caso estamos en el directorio "UNLu" y con ".." hacemos referencia a su directorio padre, el cual es "home".

---

**3**. Mover la estructura y el contenido del subdirectorios /contab 
a partir del subdirectorio /sueldos. Indicar los comandos utilizados.

```
[root@nomico ~]$ cd home
```

Para mover archivos o directorios, utilizamos el comando mv (move). Se usa de la siguiente manera:

```
mv ARCHIVO DIRECTORIO_DESTINO
```

```
[root@nomico home]$ mv ./contab/* ./sueldos
```

En este caso, cuando usamos el "*" con un directorio, estamos haciendo referencia a todo el contenido del directorio, 
sin tener en cuenta el directorio mismo. Si nos pidieran mover también el directorio contab, el comando sería el siguiente:

```
[root@nomico home]$ mv ./contab ./sueldos
```

---

**4**. Indicar que comandos utilizaría para conocer el contenido de un subdirectorio, y qué modificadores usaría 
(describir por los menos 6 de ellos), indique cuál es el que brinda mayor cantidad de información. 
En este caso se puede pedir ayuda al sistema mediante el uso del comando "--help" o el empleo del mandato "man comando". 
¿Da lo mismo usar “ls home –l” que ” ls –l home”?

Para ver el contenido de un directorio podemos usar el comando ls (list).

Algunos de sus argumentos son los siguientes:

```
ls -a
```
Muestra todos los archivos, incluso los ocultos (empiezan con ".") y también el directorio actual (.) y el directorio padre (..).

```
ls -i
```
Muestra el contenido del directorio y el inodo índice de cada archivo

```
ls -l
```
Muestra el contenido del directorio en un formato más largo. Este es el que brinda mayor cantidad de información, y se puede combinar con otros argumentos para mostrar aún más información.

```
ls -r
```
Muestra el contenido del directorio de forma inversa

```
ls -S
```
Muestra el contenido del directorio de forma ordenada, de mayor a menor tamaño.

```
ls -t
```
Muestra el contenido del directorio de forma ordenada, de más nuevo a más antiguo.

Un detalle a tener en cuenta es que **el orden de los argumentos no afecta la salida**, entonces si hago:

```
ls -l /home
```
ó
```
ls /home -l
```
La salida resulta ser la misma.

---

**5**. Indique qué comando utilizaría para ver el contenido de un archivo.

```
cat archivo
```
Muestra todo el contenido de un archivo.

```
more archivo
```
Muestra el contenido de un archivo de forma paginada.

```
less archivo
```
Similar a more, pero permite desplazarse en el archivo libremente y otras funciones como búsqueda de palabras y modificar el archivo.

```
head archivo [-n cantidad]
```
Muestra las primeras n líneas del archivo, por defecto son 10 y se pueden especificar con -n.

```
tail archivo [-n cantidad]
```
Igual que head pero para ver las últimas n líneas del archivo. En general se utiliza para ver logs.

---

**6**. Indicar que tipos de protección se pueden incorporar a los archivos.

A cada archivo se le puede asignar permisos, los cuales pueden variar entre los tres tipos de usuarios (owner, group y other).

Con chmod se pueden cambiar los permisos de un archivo:

```
chmod opciónes archivo
```

Dentro de las opciones que se pueden especificar, hay que tener en cuenta lo siguientes caracteres:

**Tipos de usuarios**

- **a**: todos los usuarios
- **u**: owner del archivo
- **g**: group del archivo
- **o**: other (otros usuarios)

**Operadores**

- **+**: agregar permiso
- **-**: remover permiso
- **=**: asignar permiso

**Permisos**

- **r**: lectura. También se representa con el valor **4**.
- **w**: escritura. También se representa con el valor **2**.
- **x**: ejecución. También se representa con el valor **1**.

Ejemplos:

```
chmod a=r archivo.txt
```
Da permisos de lectura a todos los usuarios para archivo.txt. También se puede hacer de esta manera:

```
chmod 444 archivo.txt
```
Cada unidad del número representa a un tipo de usuario. El primer 4 significa que se le asigna el permiso de lectura al owner, el segundo 4 le asigna permiso de lectura al group, y el tercer 4 le asigna permiso de lectura al resto de usuarios (other).

```
chmod u=w archivo.txt
```
Da permisos de escritura sólo al propietario. También se puede hacer de esta manera:

```
chmod 200 archivo.txt
```

Se pueden asignar varios permisos para los diferentes tipos de usuarios al mismo tiempo. Por ejemplo:

```
chmod 671 juego
```
En este comando:
- 6: se le da permiso de lectura y escritura al owner. 6 porque 4 (lectura) + 2 (escritura).
- 7: se le dan todos los permisos al group. 7 porque 4 (lectura) + 2 (escritura) + 1 (ejecución).
- 1: se le da permiso de ejecución a other.

El comando chown se puede utilizar para cambiar el propietario del archivo:

```
chown usuario archivo
```

Por ejemplo:

```
chown nomico /home/UNLu/archivo1.txt
```

Cambio el owner a nomico para archivo1.txt.

El comando chgrp se puede utilizar para cambiar el grupo del archivo, de manera similar a chown:

```
chgrp devs /home/contab/arch/*.cpp
```
Cambio el grupo a devs para todos los archivos que terminan con .cpp.

---

**7**. Para los archivos ubicados en el subdirectorio /hojasXLS/Horarios 
cambie los permisos que presentan al modo de sólo lectura para los usuarios del sistema,
lectura / escritura para los miembros del grupo y lectura/escritura y ejecución para el dueño. 
Indicar el comando utilizado.

Para cambiar los permisos de un directorio y de sus archivos, se puede utilizar el argumento -R:

```
chmod -R opciones directorio
```
Lo que hace es cambiar de manera recursiva los permisos del directorio.

Para este caso, si queremos:

- Darle permisos de lectura, escritura, y ejecución para el owner: 7
- Darle permisos de lectura y escritura para el group: 6
- Darle permisos de lectura a other: 4

Entonces el comando sería:
```
[root@nomico ~]# chmod -R 764 /home/hojasXLS/Horarios
```

Podemos verificar si se hizo correctamente con el comando ls:
```
[root@nomico ~]# ls -l /home/hojasXLS/Horarios
total 0
-rwxrw-r-- 1 root root 0 may 26 12:57 texto.txt
```

---

**8**. ¿Qué comando me permite ver el sistema de archivo donde residen los archivos? 
Indique si tiene modificadores.

Para ver el sistema de archivo donde residen los archivos se puede usar el comando df.

Uso:

```
df [archivo]
```

Modificadores:

```
df -h
```
Muestra tamaños en formato legible (KB, MB, GB)

```
df -T
```
Muestra el tipo de sistema de archivos (ext4, xfs, etc.)

```
df -i
```
Muestra información sobre inodos (total, usados, libres)

---

**9**. Indique como se usa el comando “mount” para conectar un dispositivo portátil
de almacenamiento de diferente tipo de Sistema de Archivo, de un ejemplo.
¿Cuál sería el comando para desmontarlo antes de sacarlo físicamente?

La forma estándar para invocar el comando mount es la siguiente:

```
mount [-t tipo] dispositivo directorio
```

- El argumento -t se utiliza para especificar el tipo de sistema de archivos del dispositivo. En general, el comando mount es capaz de detectarlo, por lo que puede ser opcional usarlo.
- dispositivo es el archivo que representa al dispositivo. Se puede encontrar usando el comando lsblk. Es un archivo cuya ruta es /dev/sdXY siendo X una letra e Y un número, por ejemplo /dev/sda1 o /dev/sdb2.
- directorio es el punto de montaje, es decir el lugar en donde se va a montar el contenido del dispositivo. Es un directorio vacío cuya ruta es /mnt/dir siendo dir un nombre cualquiera, por ejemplo /mnt/usb.

Ejemplo:

Si quiero montar un pendrive cuyo sistema de archivos es de tipo exfat, hago lo siguiente:
- Conecto el pendrive a la computadora (obviamente)
- Uso lsblk para encontrar el archivo asociado con el pendrive. Puedo usarlo con el argumento -f para que me de más información para poder identificarlo mejor. En este caso supongamos que es /dev/sda4
- Creo un directorio en /mnt con un nombre, en este caso podría ser pendrive
```
mkdir /mnt/pendrive
```
- Ya tengo la ruta del archivo del dispositivo y la del directorio en donde se montará el contenido, ahora invoco el comando mount con toda la información:
```
mount /dev/sda4 /mnt/pendrive
```
ó
```
mount -t exfat /dev/sda4 /mnt/pendrive
```
si mount no puede detectar automáticamente el tipo de sistema de archivos que utiliza el dispositivo.

Ahora, si lo quiero desmontar, uso el comando umount:
```
umount archivo | directorio
```

- archivo hace referencia al archivo asociado con el dispositivo, que puede ser por ejemplo /dev/sdXY como dijimos antes.
- En vez de usar el archivo asociado con el dispositivo podemos usar el directorio en donde está montado el dispositivo, como por ejemplo /mnt/usb.

Para desmontar el pendrive del ejemplo anterior, podemos hacerlo de la siguiente manera:
```
umount /dev/sda3
```
ó
```
umount /mnt/pendrive
```

---

**10**. ¿Qué información puede ser útil al usar el “stat” y el “tune2fs”? De ejemplos.

```
stat archivo
```
El comando stat sirve para ver los siguientes parámetros de un archivo:

- Nombre del archivo
- Tamaño del archivo
- Cantidad de bloques que ocupa
- Número de inodo
- Permisos de acceso
- UID y GID del owner y del group
- Tiempos de último acceso, creación, y modificación

```
tune2fs -l dispositivo
```
El comando tune2fs sirve para ajustar parámetros de sistemas de archivos ext2, ext3 y ext4. Con el argumento -l se pueden ver algunos parámetros:

- Tipo de sistema de archivos
- Directorio en el cual está montado
- Cantidad de inodos y bloques (total, ocupados y libres)
- Porcentaje de espacio reservado
- Fecha del último montaje
- Fecha del último chequeo
- Número de chequeos antes de forzar un fsck
- UUID del sistema de archivos

---

**11**. Ídem anterior para “fsck” y “fdisk”

```
fsck dispositivo
```

El comando fsck se utiliza para chequear y opcionalmente reparar sistemas de archivos de Linux. Puede brindar la siguiente información:

- Estado del sistema de archivos (si está limpio o dañado)
- Cantidad de errores encontrados y corregidos
- Cantidad de bloques libres y usados
- Cantidad de inodos libres y usados
- Información sobre directorios huérfanos, bloques dañados, etc.

```
fdisk -l disco
```

El comando fdisk se utiliza para crear y manipular tablas de particionado de un disco. Con el argumento -l muestra la siguiente información sobre el disco:

- Nombre del dispositivo y tamaño total
- Tipo de tabla de particiones (MBR o GPT)

Detalle de cada partición:
- Nombre (/dev/sda1)
- Tipo de partición (Linux, EFI, swap, etc.)
- Tamaño
- Comienzo y fin de sector
- Indicador de arranque (bootable)

---


## [Volver atrás](../readme.md)