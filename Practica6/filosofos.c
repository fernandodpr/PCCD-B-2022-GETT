#include <stdio.h>
#include <pthread.h>
#include <sys/msg.h>
#include <unistd.h>

// IDs de las colas de mensajes
int fork_queue_id;
int philosopher_queue_id;

// Estructura de mensaje para las colas de mensajes
struct message {
    long type;
    char text[0];
};

// Función que se ejecuta en cada hilo de filósofo
void *filosofo_thread (int *id_filosofo);

int main() {

    // Crear las colas de mensajes
    fork_queue_id = msgget(4238, IPC_CREAT|0777);
    if (fork_queue_id == -1) {
        printf("Error creando la cola de tenedores.\n");
        return 1;
    } 

    philosopher_queue_id = msgget(4239, IPC_CREAT|0777);
    if (philosopher_queue_id == -1) {
        printf("Error creando la cola de filósofos.\n");
        return 1;
    }

    // Enviar mensajes para indicar que los tenedores están libres
    for (int i = 1; i <= 5; i++) {
        struct message new_message;
        new_message.type = i; // Cada tenedor tiene un tipo diferente
        if (msgsnd(fork_queue_id, &new_message, sizeof(char[0]), 0) != 0) {
            printf("Error al enviar un mensaje a la cola de tenedores.\n");
            return 1;
        }
    }

    // Enviar 4 mensajes a la cola de filósofos para limitar la entrada a la Sección Crítica
    for (int i = 0; i < 4; i++) {
        struct message new_message;
        new_message.type = 1; // Todos los mensajes son del mismo tipo
        if (msgsnd(philosopher_queue_id, &new_message, sizeof(char[0]), 0) != 0) {
            printf("Error al enviar un mensaje a la cola de filósofos.\n");
            return 1;
        }
    }
    // Crear los hilos
    int parametro[5];
    for(int i = 1; i < 6; i++) {
        parametro[i-1] = i;
        pthread_t filo;
        if(pthread_create(&filo, NULL, (void *) filosofo_thread, &parametro[i-1]) != 0) {
            printf("Error creando los filósofos.\n");
            return 0;
        }
    }

    while(1) {} // Dejo aqui el programa porque ahora ya es cosa de los hilos
    return 0;
}
void *filosofo_thread (int *id_filosofo) {    
    while(1) {
        // El filósofo piensa
        printf("Filósofo [%d]: Pensando...\n", *id_filosofo);

        // Intenta acceder a la sección crítica para obtener dos tenedores
        struct message obtener_tenedores;
        msgrcv(philosopher_queue_id, &obtener_tenedores, sizeof(char[0]), 1, 0);

        // Obtiene el primer tenedor (izquierdo)
        struct message coger_tenedor1;
        if (*id_filosofo == 7) {
            msgrcv(fork_queue_id, &coger_tenedor1, sizeof(char[0]), 1, 0);
            printf("Filósofo [%d]: Cogiendo el tenedor (1) de mi izquierda.\n", *id_filosofo);
        } else {
            msgrcv(fork_queue_id, &coger_tenedor1, sizeof(char[0]), *id_filosofo, 0);
            printf("Filósofo [%d]: Cogiendo el tenedor (%d) de mi izquierda.\n", *id_filosofo, *id_filosofo);
        }

        // Obtiene el segundo tenedor (derecho)
        struct message coger_tenedor2;
        if (*id_filosofo == 1) {
            msgrcv(fork_queue_id, &coger_tenedor2, sizeof(char[0]), 5, 0);
            printf("Filósofo [%d]: Cogiendo el tenedor (5) de mi derecha.\n", *id_filosofo);
        } else {
            msgrcv(fork_queue_id, &coger_tenedor2, sizeof(char[0]), *id_filosofo-1, 0);
            printf("Filósofo [%d]: Cogiendo el tenedor (%d) de mi derecha.\n", *id_filosofo, *id_filosofo-1);
        }
        printf("Filósofo [%d]: tengo todos los tenedores entonces puedo comer...\n", *id_filosofo);
        sleep(10);
        //Despues de comer hay que dejar los tenedores
        
        //Dejar tenedor izquierdo
        struct message  dejar_tenedor1;
        if (*id_filosofo == 7) {
            printf("Filósofo [%d]: Dejando el tenedor (1) de mi izquierda.\n", *id_filosofo);
            dejar_tenedor1.type = 1;
        } else {
            printf("Filósofo [%d]: Dejando el tenedor (%d) de mi izquierda.\n", *id_filosofo, *id_filosofo);
            dejar_tenedor1.type = *id_filosofo;
        }

        msgsnd(fork_queue_id, &dejar_tenedor1, sizeof(char[0]), 0);
        //Dejar el tenedor de la derecha
        struct message  dejar_tenedor2;
        if (*id_filosofo == 1) {
            printf("Filósofo [%d]: Dejando el tenedor (5) de mi derecha.\n", *id_filosofo);
            dejar_tenedor2.type = 5;
        } else {
            printf("Filósofo [%d]: Dejando el tenedor (%d) de mi derecha.\n", *id_filosofo, *id_filosofo-1);
            dejar_tenedor2.type = *id_filosofo-1;
        }
        msgsnd(fork_queue_id, &dejar_tenedor2, sizeof(char[0]), 0);

        msgsnd(philosopher_queue_id, &obtener_tenedores,sizeof(char[0]), 0);
    }
}