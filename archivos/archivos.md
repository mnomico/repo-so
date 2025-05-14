## [Volver atrás](readme.md)

# Sistemas de Archivos

## Índice

- [Ejercicios](#ejercicios)

---

## Ejercicios

**1**. Construya la siguiente estructura de directorio en su disco, 
indicar los comandos utilizados.

![Ejercicio 1](ej1.png)

**Resolución**

[terminal]$ mkdir home

[terminal]$ cd home

[terminal home]$ mkdir sueldos

[terminal home]$ mkdir contab

[terminal home]$ cd contab

[terminal contab]$ mkdir arch

[terminal contab]$ mkdir TXT

[terminal contab]$ cd ..

[terminal home]$ mkdir textos

[terminal home]$ cd textos

[terminal textos]$ mkdir DOC

[terminal textos]$ cd ..

[terminal home]$ mkdir hojasXLS

[terminal home]$ cd hojasXLS

[terminal hojasXLS]$ mkdir Horarios

[terminal hojasXLS]$ mkdir Graph

[terminal hojasXLS]$ cd ..

[terminal home]$ mkdir UNLu

---

**2**. En el subdirectorio UNLu se tiene un conjunto de archivos, se pide copiar aquellos cuya extensión sea:

"txt" en el subdirectorio ../textos/DOC,

".cpp" en ../contab/arch,

"txt" en /contab/TXT, 

"xls" en ../hojasXLS/Horarios, 

"grp" en ../hojasXLS/Graph. 

Indicar los comandos utilizados.

**Resolución**

Primero para no tener que estar indicando el directorio *home* en cada referencia a un directorio, nos ubicamos en él:

[terminal]$ cd home 

Para copiar los archivos utilizamos el comando cp. Se usa de la siguiente manera:

**cp ARCHIVO DIRECTORIO_DESTINO**

Ahora cuando queremos tomar un conjunto de archivos con un mismo formato, usamos un * seguido del formato del archivo.

- **"txt" en el subdirectorio ../textos/DOC**

[terminal home]$ cp ./UNLu/*.txt ./textos/DOC

- **".cpp" en ../contab/arch**

[terminal home]$ cp ./UNLu/*.cpp ./textos/DOC

- **"txt" en /contab/TXT**

[terminal home]$ cp ./UNLu/*.txt ./contab/TXT

- **"xls" en ../hojasXLS/Horarios**

[terminal home]$ cp ./UNLu/*.xls ./hojasXLS/Horarios

- **"grp" en ../hojasXLS/Graph**

[terminal home]$ cp ./UNLu/*.grp ./hojasXLS/Graph

Una manera más corta de hacer esto sería ubicándonos en el directorio *UNLu*...

[terminal]$ cd home 

[terminal home]$ cd UNLu

... y a partir de acá hacer lo mismo que antes, pero en vez de indicar el directorio *UNLu* en cada referencia a un directorio, indicamos el directorio *home* de la siguiente manera, por ejemplo:

- **"txt" en el subdirectorio ../textos/DOC**

[terminal UNLu]$ cp *.txt ../textos/DOC

Cuando usamos ".." estamos haciendo referencia al directorio padre del directorio en el que nos situamos actualmente, en este caso estamos en el directorio *UNLu* y con ".." hacemos referencia a su directorio padre, el cual es *home*.

---


