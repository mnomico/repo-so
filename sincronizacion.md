## [Volver atrás](readme.md)

# Sincronización de Procesos

## Índice

- [Guía Teórica](#guía-teórica)

- [Conceptos](#conceptos)

- [Introducción](#introducción)

- [Semáforos](#semáforos)

- [Ejercicios](#ejercicios)

---

## Guía Teórica

1. ¿Cómo sería el algoritmo de envejecimiento en una cola multinivel? ¿Por qué es necesario para el sistema?

El algoritmo de envejecimiento en una cola multinivel es una técnica para evitar que los procesos de baja prioridad queden bloqueados indefinidamente, incrementando su prioridad a medida que pasan el tiempo esperando. Este enfoque es esencial para prevenir la inanición, garantizar la equidad en el uso de los recursos del sistema y mejorar la eficiencia general del sistema operativo.

Si un proceso lleva un tiempo determinado en una cola de baja prioridad, se incrementa su prioridad o se mueve a una cola de prioridad más alta para asegurar que se ejecute en algún momento.

---

2. ¿ Cuándo un recurso se convierte en una sección crítica?

Un recurso se convierte en una sección crítica cuando es accedido o modificado por varios procesos o hilos de manera concurrente, y su acceso debe ser sincronizado para evitar que se presenten condiciones de carrera, inconsistencias o errores en el sistema.

---

3. Indique si la sección crítica es software o hardware, justifique su respuesta.

La sección crítica es un concepto de software porque se refiere a cómo se gestionan los recursos compartidos entre procesos o hilos mediante técnicas de programación. Aunque puede implicar el uso de hardware, como instrucciones atómicas, el control y manejo de las secciones críticas es una decisión de diseño en el software.

---

4. ¿Qué significa el término espera ocupada?

El término espera ocupada es un mecanismo de sincronización en el que un proceso o hilo se mantiene en un ciclo activo, verificando repetidamente una condición en lugar de ser suspendido mientras espera a que esa condición se cumpla, lo cual consume recursos de CPU sin realizar trabajo útil.

---

5. ¿Qué consecuencia puede tener en el Clock del sistema, deshabilitar las interrupciones?

Deshabilitar las interrupciones en un sistema operativo puede tener varias consecuencias graves:
- Pérdida de la actualización del reloj del sistema.
- Impacto en la planificación de procesos.
- Fallos en el temporizador de actividades programadas.
- Problemas con la sincronización y el manejo de tiempo real.
- Pérdida de capacidad de manejar señales.
- Problemas en la gestión de E/S.

---

6. ¿Por qué decimos que si las operaciones wait y signal no son ejecutadas atómicamente, la exclusión mutua puede ser violada?

Si las operaciones wait y signal no son atómicas, pueden ocurrir condiciones de carrera y múltiples procesos o hilos pueden acceder a la sección crítica, violando la exclusión mutua.

---

7. Dos procesos se comunican a través de un archivo, de forma que uno escribe en el archivo y el otro lee del mismo. Para sincronizarse, el proceso escritor envía una señal al lector. Proponga un esquema del código de ambos procesos. ¿Qué problema plantea la solución anterior?

El proceso lector puede recibir la señal antes de que el proceso escritor haya completado la escritura en el archivo. Si el lector empieza a leer antes de que el escritor termine de escribir, el proceso lector leería datos incompletos o incorrectos.

---

8. ¿Qué tipo de soluciones se pueden adoptar para lograr exclusión mutua en una sección crítica? Describa cada una (por lo menos tres)

El algoritmo de Peterson es un algoritmo que garantiza la exclusión mutua para dos procesos sin la necesidad de hardware especializado o primitivos adicionales. Es un algoritmo basado en el uso de variables compartidas.

Se utilizan dos variables:
- flag'[i]': Indica si el proceso i quiere entrar a la sección crítica.
- turn: Indica qué proceso debe entrar primero en la sección crítica.

El proceso pone su bandera (flag[i]) en verdadero y luego verifica si el otro proceso también quiere entrar en la sección crítica. Si ambos lo hacen, entonces el proceso espera hasta que el otro proceso termine, basándose en la variable turn.

El uso de semáforos es una solución más general y robusta para la exclusión mutua, especialmente en sistemas con múltiples procesos o hilos. Un semáforo es una variable que controla el acceso a un recurso compartido.

Un semáforo binario mutex puede tener dos valores: 0 y 1.
- Valor 1: Indica que el recurso está disponible.
- Valor 0: Indica que el recurso está en uso.

Los procesos deben esperar con wait() si el valor del semáforo es 0, y señalar con signal() cuando terminen su ejecución en la sección crítica.

Los monitores son un mecanismo de sincronización de alto nivel que agrupa las variables compartidas y las operaciones que las manipulan en un único objeto.

Los monitores permiten que solo un proceso o hilo tenga acceso a la sección crítica en un momento dado. La exclusión mutua se maneja automáticamente.

Permiten condiciones de espera para los procesos, de modo que si un proceso no puede entrar a la sección crítica, puede esperar hasta que la condición se cumpla.

---

9. ¿Qué desventaja presenta el TSL para el sistema?

El mayor problema del TSL (Test-and-Set Lock) es que introduce espera activa. Cuando un proceso intenta acceder a la sección crítica y encuentra el candado (lock) ocupado, sigue ejecutando repetidamente la instrucción TSL, consumiendo ciclos de CPU innecesariamente. Esto reduce la eficiencia del sistema, especialmente si el recurso bloqueado tarda mucho en liberarse.

---

10. El siguiente fragmento de código intenta resolver el problema de la sección crítica para dos procesos P0 y P1.

```
While (turno != i);
a. SECCIÓN CRíTICA;
b. Turno = j;
```

La variable turno tiene valor inicial 0. La variable i vale 0 en el proceso P0 y 1 en el proceso P1. La variable j vale 1 en el proceso P0 y 0 en el proceso P1. ¿Resuelve este código correctamente el problema de la sección crítica?

El código garantiza que los procesos no entren en la sección crítica al mismo tiempo, pero no es una solución general al problema de la sección crítica porque no permite que un proceso entre en la sección crítica más de una vez si el otro proceso no lo hace.

---

11. Compare el resultado anterior con el Algoritmo de Peterson.

---

12. ¿ Qué significa el término Abrazo Mortal?

El término Abrazo Mortal (Deadlock) se refiere a una situación en la que dos o más procesos quedan bloqueados indefinidamente porque cada uno espera un recurso que está siendo utilizado por otro proceso del mismo conjunto. Como ninguno de los procesos puede continuar su ejecución hasta que los demás liberen los recursos, el sistema entra en un estado de bloqueo permanente.

---

13. ¿ Qué condiciones se deben dar para el interbloqueo y cómo se puede evitar?

Para que se produzca un deadlock, deben cumplirse estas cuatro condiciones simultáneamente:
- Exclusión mutua: un recurso solo puede ser utilizado por un proceso a la vez.
- Retención y espera: un proceso que ya tiene un recurso asignado puede esperar por otro recurso sin liberar el que ya posee.
- Sin desalojo: un recurso no puede ser forzado a liberarse; solo el proceso que lo tiene puede liberarlo.
- Espera circular: existe una cadena cerrada de procesos en la que cada uno espera un recurso que está siendo usado por el siguiente proceso de la cadena.

Existen varias estrategias para manejar el problema del deadlock:
- Prevención de Deadlock: se elimina alguna de las condiciones de Coffman. Por ejemplo:
	- Evitar la espera circular: imponer un orden estricto en la solicitud de recursos.
	- No retención y espera: obligar a los procesos a solicitar todos los recursos que necesitarán desde el inicio.
- Evitación de Deadlock: se usa un algoritmo como el Algoritmo del Banquero, que analiza si la asignación de un recurso puede llevar a un estado seguro antes de concederlo.
- Detección y recuperación: se permite que ocurra el deadlock y luego se detecta y resuelve, por ejemplo:
	- Finalizando procesos en el ciclo de espera.
	- Liberando recursos y reasignándolos.
- Ignorar el problema: en algunos sistemas operativos se "ignora el problema" y se confia que los deadlocks ocurren raramente y pueden ser resueltos manualmente si es necesario.

---

14. ¿En qué puede ayudar el uso de un diagrama de grafo? ¿Siempre se puede detectar un abrazo mortal con un ciclo cerrado o depende de algo más?

Un diagrama de grafo de asignación de recursos es una herramienta útil para analizar la asignación de recursos en un sistema y detectar posibles deadlocks (abrazos mortales). Si en este grafo se forma un ciclo cerrado, significa que hay un grupo de procesos esperando recursos de manera circular, lo que puede indicar un deadlock.

Un ciclo cerrado en el grafo solo garantiza un deadlock cuando los recursos son de una sola instancia. Cuando hay múltiples instancias de un recurso, puede que el ciclo no implique necesariamente un deadlock, y se requieren algoritmos adicionales para detectarlo, como el Algoritmo del Banquero.

---

15. Si se agregara un tiempo límite de espera de un recurso, qué ventaja y/o desventaja podría tener lugar en el sistema.

---

16. ¿Qué entiende por estado seguro?

Un estado seguro es aquel en el que el sistema puede garantizar que todos los procesos terminarán su ejecución sin caer en un deadlock (abrazo mortal).

Esto significa que el sistema puede secuenciar la asignación de recursos de tal manera que cada proceso pueda ejecutar, obtener los recursos que necesita y liberar los recursos a tiempo para que otros procesos continúen.

---

17. Explique en qué consiste el algoritmo del banquero. Si se anima construya uno semejante.

Cuando un proceso entra al sistema, declara la cantidad de instancias de recursos máxima que puede utilizar.

Luego el sistema va a determinar si dichos recursos seguirán dejando en estado seguro al sistema, si es el caso se los da, sino lo deja esperando.

Es menos eficiente que el grafo, pero se puede utilzar en sistema de múltiples instancias a diferencia del grafo.

---

18. ¿Qué consideraciones se pueden tener para terminar un proceso y recuperarse de un abrazo
mortal?

Antes de que ocurra el deadlock, el sistema puede aplicar estrategias preventivas como evitar cualquiera de las condiciones para que se produzca un interbloqueo.

Sin embargo, estas técnicas pueden ser poco eficientes y afectar el rendimiento.

Si el deadlock ya ha ocurrido, se deben aplicar estrategias para romperlo y restaurar el sistema.

Una opción es terminar uno o más procesos involucrados en el deadlock. Hay dos enfoques:
- Terminar todos los procesos en deadlock → Solución drástica pero garantiza la recuperación.
- Terminar procesos de uno en uno hasta romper el ciclo → Se elige el proceso menos crítico para la ejecución del sistema.

Criterios para elegir qué proceso finalizar
- Prioridad del proceso (procesos críticos se mantienen).
- Tiempo de ejecución restante (procesos que han avanzado menos son eliminados).
- Cantidad de recursos usados (se finalizan los que tienen mayor impacto en la recuperación).
- Si el proceso puede reiniciarse sin pérdida de datos.

Otra opción es quitar recursos de algunos procesos y reasignarlos. Para esto, el sistema debe:
- Elegir un proceso "víctima" al cual quitarle un recurso.
- Guardar su estado si es posible (checkpointing).
- Liberar recursos y reasignarlos a otros procesos bloqueados.
- Reiniciar el proceso interrumpido después de resolver el deadlock.

Este método evita la terminación de procesos, pero puede causar inconsistencias o pérdida de datos si no se maneja correctamente.

En algunos casos, los procesos pueden ejecutar operaciones en un modo reversible.
- Si ocurre un deadlock, el sistema revierte las acciones de ciertos procesos hasta un estado anterior.
- Se reintenta la ejecución con una asignación de recursos diferente.
- Esto es común en bases de datos, donde se usan transacciones con rollback para evitar bloqueos permanentes.

---

## Conceptos

### Sección crítica

Una sección crítica es un segmento del código de un proceso que accede a recursos compartidos, como variables, archivos o dispositivos, que no deben ser accedidos por más de un proceso al mismo tiempo para evitar problemas de concurrencia. Si más de un proceso accede concurrentemente a su sección crítica, puede ocurrir lo siguiente:

- **Condiciones de carrera**: el resultado depende del orden impredecible de ejecución de los procesos.
- **Inconsistencia de los datos**: ocurre cuando las operaciones no son atómicas y los datos quedan en estados incompletos.
- **Resultados incorrectos**: se producen cálculos erróneos debido al acceso simultáneo.

Para solucionar el problema de la sección crítica, se deben cumplir estas 3 características:

- Exclusión mutua: sólo un proceso puede acceder a su sección crítica a la vez.
- Progreso: si ningún proceso está ejecutando su sección crítica, cualquier proceso que solicite entrar a su sección crítica debería poder hacerlo, y dicha solicitud sólo debe resolverse entre aquellos procesos que estén queriendo entrar a sus secciones críticas. También esa solicitud debe concretarse en el menor tiempo posible.
- Espera limitada: ningún proceso debe esperar indefinidamente para entrar a su sección crítica. Esto implica que debe haber un límite en la cantidad de veces que otros procesos puedan acceder a sus secciones críticas, para evitar la inanición.

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

## Semáforos

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
