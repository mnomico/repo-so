#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIRECTOS 12
#define BLOCK_SIZE 4096                     // bytes, o sea 4KB
#define BLOQUES 256                         

char disco[BLOQUES][BLOCK_SIZE];            // 256 bloques de 4KB c/u
int bloques[BLOQUES];                       // 0 = libre; 1 = ocupado
int bloques_ocupados = 0;

typedef struct 
{
    int directos[DIRECTOS];
    int indirecto;
    int doble_indirecto;
    int triple_indirecto; 
    int tamaño;
}
Inodo;

int* asignar_bloques(int cant_bloques)
{
    if (cant_bloques >= BLOQUES - bloques_ocupados)
    {
        return NULL;
    }

    int* bloques_libres = malloc(sizeof(int) * cant_bloques);
    int asignados = 0;
    int i = 0;
    while (asignados < cant_bloques)
    {
        if (bloques[i] == 0)
        {
            bloques_libres[asignados++] = i;
            bloques_ocupados++;
            bloques[i] = 1;
        }
        i++;
    }
    return bloques_libres;
}

void set_inodo(Inodo* inodo)
{
    for (int i = 0; i < DIRECTOS; i++)
    {
        inodo->directos[i] = -1;
    }
    inodo->indirecto = -1;
    inodo->doble_indirecto = -1;
    inodo->triple_indirecto = -1;
    inodo->tamaño = 0;
}

void crear_archivo(Inodo* inodo, char* contenido)
{
    set_inodo(inodo);
    inodo->tamaño = strlen(contenido);
    int bloques_necesarios = inodo->tamaño / BLOCK_SIZE;
    if (inodo->tamaño % BLOCK_SIZE != 0)
    {
        bloques_necesarios++;
    }

    if (bloques_necesarios >= BLOQUES - bloques_ocupados)
    {
        printf("\nNo hay suficiente espacio en disco.");
        return;
    }

    // Bloques que se utilizan para escribir el contenido
    int* bloques_asignados = asignar_bloques(bloques_necesarios);
    int bloque_actual = 0;

    // Asignación de punteros directos
    for (int i = 0; i < DIRECTOS && bloque_actual < bloques_necesarios; i++)
    {
        strncpy(disco[bloques_asignados[bloque_actual]], contenido + (bloque_actual * BLOCK_SIZE), BLOCK_SIZE);
        inodo->directos[i] = bloques_asignados[bloque_actual++];
    }

    // Asignación de punteros indirectos
    if (bloque_actual < bloques_necesarios)
    {
        int* bloque_indirecto = asignar_bloques(1);
        if (bloque_indirecto == NULL)
        {
            printf("\nNo hay suficiente espacio en disco.");
            free(bloques_asignados);
            free(bloque_indirecto);
            return;
        }

        inodo->indirecto = *bloque_indirecto;
        free(bloque_indirecto);

        int punteros_por_bloque = BLOCK_SIZE / sizeof(int);
        int* bloques_indirectos = (int *) disco[inodo->indirecto];
        for (int i = 0; i < punteros_por_bloque && bloque_actual < bloques_necesarios; i++)
        {
            strncpy(disco[bloques_asignados[bloque_actual]], contenido + (bloque_actual * BLOCK_SIZE), BLOCK_SIZE);
            bloques_indirectos[i] = bloques_asignados[bloque_actual++];
        }
    }

    // Asignación de punteros indirectos dobles
    if (bloque_actual < bloques_necesarios)
    {

    }
}



