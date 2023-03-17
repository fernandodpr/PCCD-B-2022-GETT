#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h> // para sleep

bool salir = true;
int cont = 0;
void *teclado(void *arg) {
    char leer;
    do{
        scanf("%c", &leer);
        if(leer == 'q') salir = false;
        cont++;
    }while(salir);
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, teclado, NULL);
    do{
        printf("Caracteres pulsados: %d\n", cont);
        sleep(1);
    }while(salir);
}


/**/