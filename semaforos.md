## [Volver atrás](readme.md)

# Semáforos

## Índice

- [Conceptos](#conceptos)

- [Introducción](#introducción)

- [Tipos de semáforos](#tipos-de-semáforos)

- Ejercicios

---

## Conceptos

### Sección crítica

Una sección crítica es un segmento del código de un proceso que accede a recursos compartidos, como variables, archivos o dispositivos, que no deben ser accedidos por más de un proceso al mismo tiempo para evitar problemas de concurrencia. Si más de un proceso accede concurrentemente a una sección crítica, puede ocurrir lo siguiente:

- **Condiciones de carrera**: el resultado depende del orden impredecible de ejecución de los procesos.
- **Inconsistencia de los datos**: ocurre cuando las operaciones no son atómicas y los datos quedan en estados incompletos.
- **Resultados incorrectos**: se producen cálculos erróneos debido al acceso simultáneo.

Para solucionar el problema de la sección crítica, se deben cumplir estas 3 características:

- Exclusión mutua: sólo un proceso puede acceder a una sección crítica a la vez.
- Progreso: si ningún proceso está ejecutando su sección crítica, cualquier proceso que solicite entrar debería poder hacerlo.
- Espera limitada: ningún proceso debe esperar indefinidamente para entrar.

### Cerrojo

Toda solución al problema de la sección crítica requiere de la implementación de un **cerrojo**. Un proceso debe adquirir un cerrojo antes de entrar en una sección crítica y liberarlo cuando sale de la misma. 

### Operación atómica

Las **operaciones atómicas** son operaciones que se ejecutan completamente sin interrupciones, como si fuera una sola instrucción que no se puede dividir.

---

## Introducción

Un **semáforo** es una variable entera que sólo se accede mediante dos operaciones atómicas: **wait()** y **signal()**.

La operación wait() se define de la siguiente manera:
```
wait(Semaphore S) {
   while S<=0
     ; //no operation
   S--;
}
```
La operación signal() se define de la siguiente manera:
```
signal(S) {
   S++;
}
```
Todas las modificaciones del valor entero del semáforo en las operaciones wait() y signal() deben ser ejecutadas de manera indivisible, es decir, que cuando un proceso modifica el valor del semáforo, ningún otro proceso puede modificar el valor de dicho semáforo.

---

## Tipos de semáforos

El valor que puede tomar un **semáforo contador** puede variar, mientras que el valor que puede tomar un **semáforo binario** sólo puede ser 0 o 1. A los semáforos binarios se los llama **mútex** ya que proporcionan exclusión mutua.

Los semáforos contadores se utilizan para controlar el acceso a un recurso que tiene un número limitado de instancias. El semáforo se inicia con la cantidad de instancias disponibles. Cada proceso que quiera usar una instancia del recurso debe hacerlo mediante wait(), decrementando la cuenta. Cuando un proceso libera una instancia del recurso, ejecuta signal(), incrementando la cuenta. Cuando la cuenta llega a 0, significa que todas las instancias de ese recurso están siendo utilizadas, y cualquier otro proceso que quiera utilizar dicho recurso deberá esperar hasta que se libere alguna instancia.

...

---

## [Volver atrás](readme.md)