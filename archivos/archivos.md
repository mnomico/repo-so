## [Volver atrás](../readme.md)

# Sistemas de Archivos

## Índice

- [Ejercicios](#ejercicios)

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

**Resolución**

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

**Resolución**

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
[root@nomico home]$ cp ./UNLu/*.cpp ./textos/DOC
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

**Resolución**

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
En este caso se puede pedir ayuda al sistema mediante el uso: " comando --help" o el empleo del mandato "man comando". 
¿Da lo mismo usar “ls home –l” que ” ls –l home”?

**Resolución**

---

## [Volver atrás](../readme.md)