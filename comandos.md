## [Volver atrás](readme.md)

# Comandos UNIX

A continuación se detallan comandos que se piden en los TPs, junto con algunos (no todos) de los argumentos que se pueden utilizar en ellos.

## Índice

- [Particionado de disco](#particionado-de-disco)

- [Procesos](#procesos)

- [Usuarios y grupos](#usuarios-y-grupos)

- [Otros comandos](#otros-comandos)

---

# **Particionado de disco**

## ``` fdisk ```

Uso: ``` fdisk DEVICE ```

Herramienta para maniupular la tabla de particiones de disco.

**Argumentos**

``` -b SECTOR_SIZE ```: especifica el tamaño de los sectores del disco.

``` -l ```: muestra la lista de tablas de partición de los dispositivos ingresados.

``` -C ```: especifica el número de cilindros del disco.

``` -H ```: especifica el número de cabezales del disco.

``` -S ```: especifica el número de sectores por pista del disco.

---

## ``` mkfs ```

Uso: ``` mkfs.<type> DEVICE [SIZE] ```

Crea un sistema de archivos de Linux con el tipo ingresado. type puede ser de cualquier tipo de sistema de archivos que soporte Linux, como ext2, ext3, ext4, o fat, entre otros. El argumento device puede ser el nombre de la partición (como por ejemplo /dev/sda1). Si la partición ya existe, se elimina y se formatea.

---

# **Procesos**

## ``` ps ```

Devuelve una captura de los procesos en ejecución.

Si se utiliza sin parámetros, devuelve una captura con los procesos asociados a la terminal en la que se ingresó el comando.

**Argumentos**

``` -e ```: evuelve todos los procesos del sistema.

``` -f ```: muestra los procesos en formato completo.

``` -u USER ```: muestra los procesos de un usuario específico.

``` -p PIDLIST ```: muestra los procesos con los PIDs ingresados.

---

## ``` top ```

Devuelve una captura en tiempo real de los procesos en ejecución, ordenados de mayor a menor uso de CPU.

**Argumentos**

``` -n N ```: actualizar N veces antes de salir.

``` -d SECS ```: actualizar cada SECS segundos. 

``` -u USER ```: muestra los procesos de un usuario específico.

``` -p PIDLIST ```: muestra los procesos con los PIDs ingresados.

---

## ```pmap ```

Uso: ```pmap PID```

Devuelve un informe de la memoria virtual que utilizan los procesos ingresados.

**Argumentos**

``` -x ```: muestra el formato extendido.

``` -d ```: muestra el formato de dispositivo.

``` -A low, high ```: mostrar el rango ingresado de direcciones virtuales que utilizan los procesos ingresados.

---

## ``` kill ```

Uso: ``` kill PID ```

Termina un proceso con el PID ingresado mediante el envío de señales.

**Argumentos**

``` -15 ```: envía una señal al proceso para que termine, puede ser interceptada por el proceso para que antes libere sus recursos y termine operaciones importantes.

``` -9 ```: envía una señal al proceso para que termine inmediatamente, de manera forzada.

---

## ``` nice ```

Uso: ``` nice [COMMAND] ```

Inicia un proceso con la prioridad ingresada.

**Argumentos**

``` -n N ```: se le asigna una prioridad N al proceso. Por defecto es 10, y N puede estar entre -20 y 19, siendo -20 la prioridad más alta y 19 la prioridad más baja.

---

## ``` renice ```

Uso: ``` renice PRIORITY ```

Altera la prioridad de los procesos en ejecución.

**Argumentos**

``` --priority N ```: se le asigna una prioridad N al proceso.

``` --relative N ```: se incrementa/decrementa la prioridad del proceso por el valor N ingresado

``` -g ID ```: interpretar ID como GIDs de procesos.

``` -p ID ```: interpretar ID como PIDs.

``` -u ID ```: interpretar ID como nombres de usuarios o UIDs.

---

# **Usuarios y grupos**

## ``` useradd ```

Uso: ``` useradd LOGIN ```

Crea un nuevo usuario o actualiza la información que se utiliza por defecto de un usuario nuevo.

**Argumentos**

``` -d HOME_DIR ```: define el directorio HOME del usuario.

``` -g GROUP_NAME ```: define el grupo primario del usuario.

``` -p PASSWORD ```: define la contraseña del usuario.

``` -u UID ```: define el UID del usuario.

---

## ``` usermod ```

Uso: ``` usermod LOGIN ```

Modifica un usuario existente.

**Argumentos**

``` -d HOME_DIR ```: cambia el directorio HOME del usuario.

``` -g GROUP_NAME ```: cambia el grupo primario del usuario.

``` -l NEW_LOGIN ```: cambia el nombre del usuario.

``` -L ```: bloquea el acceso de una cuenta con contraseña.

``` -p PASSWORD ```: define la contraseña del usuario.

``` -u UID ```: cambia la constraseña del usuario.

``` -U ```: desbloquea el acceso de una cuenta con contraseña.

---

## ``` userdel ```

Uso: ``` userdel LOGIN ```

Elimina un usuario existente y sus archivos.

**Argumentos**

``` -f ```: fuerza la eliminación del usuario, salteando chequeos de seguridad.

``` -r ```: elimina los archivos del directorio HOME del usuario.

---

## ``` groupadd ```

Uso: ``` groupadd NEWGROUP ```

Crea un nuevo grupo o actualiza la información que se utiliza por defecto de un grupo nuevo.

**Argumentos**

``` -g GID ```: define el GID del grupo.

``` -p PASSWORD ```: define la contraseña del grupo.

``` -U USERLIST ```: agrega una lista de usuarios separada por comas al grupo.

---

## ``` groupmod ```

Uso: ``` groupmod GROUP ```

Modifica un grupo existente.

**Argumentos**

``` -g GID ```: cambia el GID del grupo.

``` -n NEW_GROUP ```: cambia el nombre del grupo.

``` -p PASSWORD ```: cambia la contraseña del grupo.

``` -U USERLIST ```: agrega una lista de usuarios separada por comas al grupo.

---

## ``` groupdel ```

Uso: ``` groupdel GROUP ```

Elimina un grupo existente.

**Argumentos**

``` -f ```: fuerza la eliminación del grupo, salteando chequeos de seguridad.

---

## ``` chfn ```

Modifica los datos personales de un usuario.

**Argumentos**

``` -f full-name ```: define el nombre completo del usuario.

``` -o office ```: define el número de oficina.

``` -p office-phone ```: define el teléfono de la oficina.

``` -h home-phone ```: define el teléfono del hogar.

---

## ``` write ```

Uso: ``` write USER MESSAGE ```

Envía un mensaje a otro usuario.

---

## ``` talk ```

Uso: ``` talk USER MESSAGE ```

Cliente que abre una sesión para que dos usuarios hablen.

---

# **Otros comandos**

## ``` man ```

Interfaz para consultar los manuales del sistema.

---

## ``` shutdown ```

Uso: ``` shutdown [TIME] [WALL] ```

Detiene, apaga o reinicia la computadora. El argumento TIME puede ser un string que indica el tiempo en el que se ejecutará la operación, seguido por un mensaje WALL que se enviará a los usuarios antes de ejecutar la operación.

**Argumentos**

``` -H ```: detiene el sistema y lo apaga.

``` -P ```: apaga el sistema.

``` -r ```: reinicia el sistema.

---

## [Volver atrás](readme.md)
