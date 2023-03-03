//p3-1

#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    int id_segmento;

int *numero;

// Intentamos acceder al segmento de memoria compartida con clave 321
id_segmento = shmget(321, sizeof(int), 0);

if(id_segmento == -1) {
    
    printf("Error accediendo al segmento.");
    return 0;
    
}

// Nos vinculamos al segmento de memoria compartida y obtenemos un puntero a la dirección de memoria donde se encuentra la variable compartida
numero = (int *) shmat(id_segmento, NULL, 0);

// Leemos el número compartido con p3-1 y lo mostramos en pantalla
printf("Numero compartido por p3-1: %d\n", *numero);

// Desvinculamos el segmento de memoria compartida
if(shmdt((void *)numero) == -1) {

    printf("\nError desvinculando la variable asignada al segmento.");
    return 0;

} 

return 0;
}