
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
int segment_id;
int *shared_number;

//Se crea una clave de segmento y se asigna un tamaño y flags para asignar el segmento a la memoria compartida. 
segment_id = shmget(311, sizeof(int), IPC_EXCL|IPC_CREAT|0777);
//Los flags IPC_CREAT y IPC_EXCL se utilizan para crear el segmento y asegurar que no existe un ID de segmento asociado con la misma clave. Los permisos de acceso son 0777.


if(segment_id == -1) {
    
    printf("Error al crear el segmento.");
    return 0;
    
}

//shmat devuelve un puntero void, que se convierte al tipo int. 
//El ID del segmento y los flags se utilizan para asociar el segmento de memoria compartida con la variable.
shared_number = (int *) shmat(segment_id, NULL, 0);

*shared_number = atoi(argv[1]);

printf("\nEl proceso P1 entrará en suspensión por medio minuto para que se ejecute el proceso P2 y acceda al número. Después, P1 desasignará y liberará el espacio.");

printf("\nNúmero compartido: %d\n", *shared_number);

sleep(15);

//Desasigna el espacio del segmento asociado a la variable. 
//El parámetro es un puntero void.
if(shmdt((void *)shared_number) == -1) {

    printf("\nError al desvincular la variable asignada al segmento.");
    return 0;

} 

//Realiza operaciones de control sobre el segmento de memoria compartida.
//El ID del segmento y los flags se utilizan para eliminar el segmento.
if(shmctl(segment_id, IPC_RMID, NULL) == -1) {

    printf("\nError al eliminar el segmento.");
    return 0;

}

return 0;
}