#include <stdio.h>
#include <pthread.h>

// Función que imprime un mensaje en la pantalla
void *imprimir(void *arg) {
    // Se convierte el argumento a un puntero a un entero
    int pos = *((int*)arg);
    // Se imprime el mensaje con la posición correspondiente
    printf("Mensaje desde el hilo %d\n", pos);
    // El hilo termina y devuelve NULL
    return NULL;
}

int main() {
    // Se define un array de hilos
    pthread_t threads[5];
    int i;
    // Se crea un hilo para cada elemento del array de hilos
    for (i = 0; i < 5; i++) {
        // Se reserva memoria para un entero
        int *arg = malloc(sizeof(int));
        // Se asigna el valor de la posición al entero
        *arg = i;
        // Se crea el hilo con la función imprimir() y el argumento correspondiente
        pthread_create(&threads[i], NULL, imprimir, arg);
    }
    // Se espera a que todos los hilos terminen
    for (i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }
    // El programa termina
    return 0;
}
