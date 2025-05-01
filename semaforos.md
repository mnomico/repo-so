## [Volver atrás](readme.md)

# Semáforos

## Índice

- [Conceptos](#conceptos)

- [Introducción](#introducción)

- [Tipos de semáforos](#tipos-de-semáforos)

- [Ejercicios](#ejercicios)

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

---

## Ejercicios

**10.** El siguiente fragmento de código intenta resolver el problema de la sección crítica para dos procesos P0 y P1.
```
While (turno != i);
    a. SECCIÓN CRíTICA;
    b. Turno = j;
```
La variable turno tiene valor inicial 0. La variable i vale 0 en el proceso P0 y 1 en el proceso P1. 
La variable j vale 1 en el proceso P0 y 0 en el proceso P1. 
¿Resuelve este código correctamente el problema de la sección crítica?

**Resolución**

| Turno | i en P0 | j en P0 | i en P1 | j en P1 |
|:------|---------|---------|---------|---------|
| 0     | 0       | 1       | 1       | 0       | 
| 0     | 0       | 1       | 1       | 0       |

El proceso P0 nunca va a poder acceder a la sección crítica.

Para solucionarlo, hay dos maneras:
- Modificar el código de la siguiente manera:
```
While (turno == i);
    a. SECCIÓN CRíTICA;
    b. Turno = j;
```
| Turno | i en P0 | j en P0 | i en P1 | j en P1 |
|:------|---------|---------|---------|---------|
| 0     | 0       | 1       | 1       | 0       | 
| 1     | 0       | 1       | 1       | 0       |

Ahora tanto P0 como P1 pueden acceder a la sección crítica, respetando la exclusión mutua.

- Otra manera:
```
While (turno != i);
    a. SECCIÓN CRíTICA;
    b. Turno = i;
```

En este caso sucede lo mismo que en el anterior, sin la necesidad de utilizar la variable j.

**11.** Compare el resultado anterior con el Algoritmo de Peterson.

El Algoritmo de Peterson utiliza un flag para cada proceso, indicando si está listo para entrar a la sección crítica. Esto permite que si un proceso no desea entrar, el otro pueda hacerlo sin esperar (progreso). Además, la combinación de flag y turno evita que un proceso siempre tome la sección crítica cuando hay competencia, garantizando que ambos procesos tengan la oportunidad de ingresar (evitando inanición).

Algoritmo del proceso i:
```
flag[i] = true;       // quiero entrar a la sección crítica
turno = j;            // le cedo la preferencia al otro

while (flag[j] && turno == j)
    ;                 // espera activa (busy waiting)

// ---- sección crítica ----

// al salir:
flag[i] = false;
```
Algoritmo del proceso j:
```
flag[j] = true;       // quiero entrar a la sección crítica
turno = i;            // le cedo la preferencia al otro

while (flag[i] && turno == i)
    ;                 // espera activa (busy waiting)

// ---- sección crítica ----


// al salir:
flag[j] = false;
```

---

## [Volver atrás](readme.md)