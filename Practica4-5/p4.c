//EJERCICIO CUATRO
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N1 5 // número total de lectores posibles
#define N2 2 // número máximo de lectores que pueden leer simultáneamente

// semáforos
sem_t mutex;
sem_t sem_lectores[N1];

void *lector(void *arg) {
    int id = *(int*) arg;

    while (1) {
        printf("[Lector %d] -> Esperando a intentar leer...\n", id);
        sem_wait(&sem_lectores[id]); // esperar a que el thread principal indique intentar leer
        printf("[Lector %d] -> Intentando leer...\n", id);

        sem_wait(&mutex); // exclusión mutua
        sem_post(&sem_lectores[id]); // liberar semáforo del lector para permitir que otros intenten leer

        printf("[Lector %d] -> Leyendo...\n", id);

        sem_wait(&sem_lectores[id]); // esperar a que el thread principal indique fin de lectura
        sem_post(&mutex); // liberar exclusión mutua

        printf("[Lector %d] -> Fin lectura\n", id);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[N1];
    int ids[N1];

    // inicializar semáforos
    sem_init(&mutex, 0, 1);
    for (int i = 0; i < N1; i++) {
        sem_init(&sem_lectores[i], 0, 0);
    }

    // crear threads de lectores
    for (int i = 0; i < N1; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, lector, &ids[i]);
    }

    while (1) {
        printf("Menú:\n");
        printf("1. Intentar leer\n");
        printf("2. Finalizar leer\n");
        printf("3. Salir\n");

        int opcion, lector_id;
        scanf("%d", &opcion);

        if (opcion == 1) {
            printf("Introduzca el número del lector (de 1 a %d): ", N1);
            scanf("%d", &lector_id);

            sem_post(&sem_lectores[lector_id-1]); // indicar al lector que intente leer
        }
        else if (opcion == 2) {
            printf("Introduzca el número del lector (de 1 a %d): ", N1);
            scanf("%d", &lector_id);

            sem_post(&sem_lectores[lector_id-1]); // indicar al lector que finalice la lectura
        }
        else if (opcion == 3) {
            break;
        }
    }

    // liberar semáforos y esperar a que los threads de lectores terminen
    sem_destroy(&mutex);
    for (int i = 0; i < N1; i++) {
        sem_destroy(&sem_lectores[i]);
        pthread_join(threads[i], NULL);
    }

    return 0;
}
