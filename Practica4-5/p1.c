#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // para sleep

void *teclado(void *arg) {
    int c;
    while ((c = getchar()) != 'q') {}
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, teclado, NULL);
    int num_caracteres = 0;
    while (1) {
        printf("Numero de caracteres leidos del teclado: %d\n", num_caracteres);
        fflush(stdout);
        num_caracteres++;
        sleep(1);
    }
    return 0;
}
