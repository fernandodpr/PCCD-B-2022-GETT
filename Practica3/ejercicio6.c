#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
int id_segmento_memoria_compartida;
//VIOLACIÓN DE EXCLUSIÓN MUTUA: Cuando ambos acceden al pasillo antes de que alguno de ellos pulse, entran ambos en la Sección Crítica.
//INANICIÓN: Un proceso puede salir de su Sección Crítica y, en el mismo cuanto, volver a entrar antes de que el otro pueda decir que quiere hacerlo, de manera indefinida. 

printf("\nEste programa debe ser ejecutado sólo 2 veces con la misma clave para evitar errores. En la primera ejecución se abre P y en la segunda ejecución se abre Q.\n");

// instancia 0 para la primera ejecución (proceso P) y instancia 1 para la segunda ejecución (proceso Q)    
int instancia = 0;

int *quiere_acceder;

id_segmento_memoria_compartida = shmget(361, sizeof(int)*2, IPC_EXCL|IPC_CREAT|0777);

if(id_segmento_memoria_compartida == -1) {
    
    // si el segmento ya existe, accedemos a él (segunda instancia de P)
    id_segmento_memoria_compartida = shmget(361, sizeof(int),0);
    instancia = 1;
    printf("\nPROCESO Q\n\n");

    if (id_segmento_memoria_compartida == -1) {

        printf("Error al crear/obtener el ID del segmento de memoria compartida.");
        return 0;

    }
} else {
    printf("\nPROCESO P\n\n");
}

quiere_acceder = (int *) shmat(id_segmento_memoria_compartida, NULL, 0);

// quiere_acceder[0] == quiere_acceder_P
// quiere_acceder[1] == quiere_acceder_Q
quiere_acceder[0] = 0;
quiere_acceder[1] = 0;


int sigue_P = 0;
int sigue_Q = 0;

while(1) {

    printf("Caminando por mi habitación.\n");

    if(instancia == 0) {

        while(!sigue_P) {

            getchar();

            printf("Intentando acceder al pasillo de entrada a la Sección Crítica...");

            if(quiere_acceder[1] == 0) {

                printf("Dentro del pasillo.\n");
                
                getchar();

                quiere_acceder[0] = 1;
                printf("He accionado el pulsador.\n");
                printf("Dentro de mi Sección Crítica.\n");
                
                getchar();
                printf("He salido de mi Sección Crítica.\n");

                getchar();
                quiere_acceder[0] = 0;
                printf("He accionado el pulsador.\n");
                sigue_P++;
            
            } else {

                printf("Puerta cerrada.\n");

            }

        }

        sigue_P--;

    } else {

        while(!sigue_Q) {

            getchar();

            printf("Intentando acceder al pasillo de entrada a la Sección Crítica...");

            if(quiere_acceder[0] == 0) {

                printf("Dentro del pasillo.\n");
                
                getchar();

                quiere_acceder[1] = 1;
                printf("He accionado el pulsador.\n");
                printf("Dentro de mi Sección Crítica.\n");
                
                getchar();
                printf("He salido de mi Sección Crítica.\n");

                getchar();
                quiere_acceder[1] = 0;
                printf("He accionado el pulsador.\n");
                sigue_Q++;
            
            } else {

                printf("Puerta cerrada.\n");

            }

        }

        sigue_Q--;

    }

}

//NOTA: Al tener que detener el proceso con ctrl+C, no se puede desvincular y eliminar el segmento, si se detiene y se vuelve a ejecutar  más de dos veces (con la misma clave) estará todo el rato sin poder volver a la instancia 0; 
//Deberá cambiarse la clave para crear un nuevo segmento de memoria compartida, y el anterior quedará sin liberar


//No hay ninguna posible situación en la que ambos procesos queden suspendidos sin poder avanzar en su ejecución, es decir, no hay INTERBLOQUEO.

}