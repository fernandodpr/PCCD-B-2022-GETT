#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    int id_segmento;

    printf("\nSolo se deben ejecutar 2 instancias del programa CON LA MISMA CLAVE para evitar errores, ya que a partir de la primera ejecución se abre la sección crítica.\n");

    // Si es la primera instancia de P5, será la instancia 0 (proceso P), si es la segunda, será la 1 (proceso Q)
    int num_instancia = 0;

    // turno 0 = puerta abierta para P, cerrada para Q
    // turno 1 = puerta abierta para Q, cerrada para P
    int *turno = NULL;

    id_segmento = shmget(351, sizeof(int), IPC_EXCL | IPC_CREAT | 0777);

    if (id_segmento == -1) {
        // Si da error porque el segmento ya existe, accedemos a él (segunda instancia de P5)
        id_segmento = shmget(351, sizeof(int), 0);
        printf("\nPROCESO Q\n\n");

        num_instancia++;

        if (num_instancia > 1) {
            if (id_segmento == -1) {
                printf("Error al crear/obtener el ID del segmento.\n");
                return 0;
            }
        }
    } else {
        printf("\nPROCESO P\n\n");
    }

    turno = (int *)shmat(id_segmento, NULL, 0);

    int sigue_P = 0;
    int sigue_Q = 0;
    
    while (1) {
        printf("Caminando por mi habitación.\n");

        if (num_instancia == 0) {
            while (!sigue_P) {
                getchar();

                printf("Intentando entrar a mi sección crítica...\n");

                if (*turno == 1) {
                    printf("Puerta cerrada.\n");
                } else {
                    printf("Dentro de mi sección crítica.\n");
                    getchar();
                    sigue_P++;
                }
            }

            printf("He salido de mi sección crítica.\n");
            getchar();
            *turno = 1;
            printf("He accionado mi pulsador.\n");
            sigue_P--;
        } else {
            while (!sigue_Q) {
                getchar();

                printf("Intentando entrar a mi sección crítica...\n");

                if (*turno == 0) {
                    printf("Puerta cerrada.\n");
                } else {
                    printf("Dentro de mi sección crítica.\n");
                    getchar();
                    sigue_Q++;
                }
            }

            printf("He salido de mi sección crítica.\n");
            getchar();
            *turno = 0;
            printf("He accionado mi pulsador.\n");
            sigue_Q--;
        }
    }

    // NOTA: Al tener que detener el proceso con ctrl+C, no se puede desvincular y eliminar el segmento, si se detiene y se vuelve a ejecutar más de dos veces (con la misma clave) estará todo el rato sin poder volver a la instancia 0; 
    // Deberá cambiarse la clave para crear un nuevo segmento de memoria compartida, y el anterior
}