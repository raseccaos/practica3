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
/* Variables para la clasificacion */
int clasificacion[N_COCHES];     // Guarda el id de los coches en orden de llegada
int posicion_actual = 0;         // Siguiente posicion libre
pthread_mutex_t mutex_clasificacion = PTHREAD_MUTEX_INITIALIZER;


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
    pthread_mutex_lock(&mutex_clasificacion);

    clasificacion[posicion_actual] = pcoche->id;
    posicion_actual++;

    pthread_mutex_unlock(&mutex_clasificacion);


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
    for (int i = 0; i < N_COCHES; i++) {
        Coches[i].id = i;
        Coches[i].nombre = "Coche";

        if (pthread_create(&hilosCoches[i], NULL, funcion_coche, &Coches[i]) != 0) {
            perror("Error creando hilo");
            exit(EXIT_FAILURE);
        }
    }

    printf("Proceso de creacion de hilos terminado\n\n");

    /* -------------------------------------------------
       BLOQUE A COMPLETAR: CODIGO 3
       Espacio para esperar a la finalizacion de los hilos
       ------------------------------------------------- */
    for (int i = 0; i < N_COCHES; i++) {
        pthread_join(hilosCoches[i], NULL);
    }


    printf("Todos los coches han LLEGADO A LA META\n");

    /* -------------------------------------------------
       BLOQUE A COMPLETAR: CODIGO 5
       Espacio para mostrar la clasificacion final
       ------------------------------------------------- */
    printf("\nCLASIFICACION FINAL:\n");

    for (int i = 0; i < N_COCHES; i++) {
        printf("%dº -> Coche %d\n", i + 1, clasificacion[i]);
    }


    /* Liberar recursos del mutex de salida */
    pthread_mutex_destroy(&mutex_output);

    return 0;
}
