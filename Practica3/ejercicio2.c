#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>

int main() {

    // Obtiene el ID del segmento de memoria compartida asociado a la clave 311, sin crear un segmento nuevo.
    int id_segmento = shmget(311, sizeof(int), 0);

    if(id_segmento == -1) {
        
        printf("Error al obtener el segmento.");
        return 0;
        
    }

    int *numero;
    numero = (int *) shmat(id_segmento, NULL, 0);

    printf("Numero compartido por p1: %d\n", *numero);

    return 0;

}