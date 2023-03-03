#include <stdio.h>
#include <pthread.h>

int bandera[2] = {0,0};
int turno = 0;

void *proceso(void *ptr) {

    int id = *(int*)ptr;

    int otro = 1-id;

    int i = 0;
            printf("Soy el proceso %d y estoy caminando por mi habitación.\n", id);
        getchar();
        printf("Estoy intentando entrar en mi sección critica");
        printf("Soy el proceso %d y estoy dentro de mi Sección Crítica.\n", id);
        getchar();
        printf("He salido de mi sección crítica");
        fflush(stdout);


    pthread_exit(NULL);
}

int main() {

    pthread_t hilo[2];

    int id1 = 0;
    int id2 = 1;

    pthread_create(&hilo[0], NULL, proceso, &id1);
    pthread_create(&hilo[1], NULL, proceso, &id2);

    pthread_join(hilo[0], NULL);
    pthread_join(hilo[1], NULL);

    return 0;
}