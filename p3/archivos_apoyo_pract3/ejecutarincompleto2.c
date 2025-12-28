#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define N_COCHES 8

typedef struct {
    int id;
    char *nombre;
} coche_t;

coche_t Coches[N_COCHES];

/* -------------------------------------------------
   BLOQUE A COMPLETAR: CODIGO 0
   Espacio para variables globales adicionales si fueran necesarias
   ------------------------------------------------- */

pthread_mutex_t mutex_output = PTHREAD_MUTEX_INITIALIZER;

void *funcion_coche(void *arg)
{
    coche_t *pcoche = (coche_t *)arg;

    /* Inicializar semilla distinta para cada hilo */
    unsigned int semilla = pcoche->id + (unsigned int)time(NULL);
    int retardo = rand_r(&semilla) % 10 + 1;

    /* Mensaje de salida del coche */
    pthread_mutex_lock(&mutex_output);
    printf("Salida de %s %d\n", pcoche->nombre, pcoche->id);
    fflush(stdout);
    pthread_mutex_unlock(&mutex_output);

    /* Simulacion de la carrera mediante retardo aleatorio */
    sleep(retardo);

    /* Mensaje de llegada del coche */
    pthread_mutex_lock(&mutex_output);
    printf("Llegada de %s %d\n", pcoche->nombre, pcoche->id);
    pthread_mutex_unlock(&mutex_output);

    /* -------------------------------------------------
       BLOQUE A COMPLETAR: CODIGO 4
       Espacio para registrar la posicion o clasificacion
       ------------------------------------------------- */

    /* -------------------------------------------------
       BLOQUE A COMPLETAR: CODIGO 6 (opcional)
       Espacio para devolver informacion al hilo principal
       ------------------------------------------------- */

    return NULL;
}

int main(void)
{
    pthread_t hilosCoches[N_COCHES];

    printf("Se inicia proceso de creacion de hilos...\n\n");
    printf("SALIDA DE COCHES\n");

    /* -------------------------------------------------
       BLOQUE A COMPLETAR: CODIGO 1
       Espacio para inicializar estructuras y crear hilos
       ------------------------------------------------- */

    printf("Proceso de creacion de hilos terminado\n\n");

    /* -------------------------------------------------
       BLOQUE A COMPLETAR: CODIGO 3
       Espacio para esperar a la finalizacion de los hilos
       ------------------------------------------------- */

    printf("Todos los coches han LLEGADO A LA META\n");

    /* -------------------------------------------------
       BLOQUE A COMPLETAR: CODIGO 5
       Espacio para mostrar la clasificacion final
       ------------------------------------------------- */

    /* Liberar recursos del mutex de salida */
    pthread_mutex_destroy(&mutex_output);

    return 0;
}
