#include <stdio.h>
#include <pthread.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
//creo que esto que son colas únicas no es lo adecuado
int cola_papel, cola_tabaco, cola_fosforo, proveedor;
int cola;
void *fumador1(), *fumador2(), *fumador3(), *proveedor_th();

struct mensaje {
    long type;
    char txt[0];

};

int main() {

    //Creamos las colas
    cola_papel = msgget(1245, IPC_CREAT|0777);
    cola_tabaco = msgget(2584, IPC_CREAT|0777);
    cola_fosforo = msgget(3589, IPC_CREAT|0777);
    proveedor = msgget(1478, IPC_CREAT|0777);
    cola = msgget(1479, IPC_CREAT|0777);

    if((cola_papel == -1)||(cola_tabaco == -1)||(proveedor == -1)||(cola_fosforo == -1)||(cola == -1)) {

        printf("Problema al crear colas.\n");
        return 0;

    }

    //Creamos los hilos
    pthread_t fumador1th, fumador2th, fumador3th, proveedorth;
    int vuelta =1;
    if((pthread_create(&fumador1th, NULL, fumador1, &vuelta) != 0)||(pthread_create(&fumador2th, NULL, fumador2, &vuelta) != 0)||(pthread_create(&fumador3th, NULL, fumador3, &vuelta) != 0)||(pthread_create(&proveedorth, NULL, proveedor_th, NULL) != 0)) {
        printf("Problema al crear filósofos.\n");
        return 0;
    }

    //Creamos los hilos
    pthread_t fumador4th, fumador5th, fumador6th;
    vuelta ++;
    if((pthread_create(&fumador4th, NULL, fumador1, &vuelta) != 0)||(pthread_create(&fumador5th, NULL, fumador2, &vuelta) != 0)||(pthread_create(&fumador6th, NULL, fumador3, &vuelta) != 0)) {
        printf("Problema al crear filósofos.\n");
        return 0;
    }

    while(1) {}

    return 0;
 
}



void *fumador1 (int *fumador) {
    struct mensaje aviso;
    aviso.type=1;
    while(1) {
        struct mensaje mi_turno;
        printf("Fumador 1 %d: Tengo papel.\n",*fumador);

        printf("Fumador 1 %d: Esperando tabaco...\n",*fumador);
        msgrcv(cola_tabaco, &mi_turno, sizeof(char[0]), 1, 0);
        printf("Fumador 1 %d: Tengo tabaco, y lo suelto\n",*fumador);
        msgsnd(cola_tabaco, &aviso, sizeof(char[0]), 0);
        printf("Fumador 1 %d: Esperando fosforo...\n",*fumador);
        msgrcv(cola_fosforo, &mi_turno, sizeof(char[0]), 1, 0);
        printf("Fumador 1 %d: Tengo fosforo, recupero el tabaco\n",*fumador);
        msgrcv(cola_tabaco, &mi_turno, sizeof(char[0]), 1, 0);

        printf("Fumador 1 %d: Estoy fumando...🚬\n",*fumador);
        sleep(2);
        printf("Fumador 1 %d: Acabé de fumar.\n",*fumador);
        struct mensaje continua;
        continua.type = 1;
        msgsnd(proveedor, &continua, sizeof(char[0]), 0);
    }

}

void *fumador2 (int *fumador) {
    struct mensaje aviso;
    aviso.type=1;
    while(1) {
        struct mensaje mi_turno;
        printf("Fumador 2 %d: Tengo tabaco.\n",*fumador);

        printf("Fumador 2 %d: Esperando papel...\n",*fumador);
        msgrcv(cola_papel, &mi_turno, sizeof(char[0]), 1, 0);
        printf("Fumador 2 %d: Tengo papel, y lo suelto\n",*fumador);
        msgsnd(cola_papel, &aviso, sizeof(char[0]), 0);
        printf("Fumador 2 %d: Esperando fosforo...\n",*fumador);
        msgrcv(cola_fosforo, &mi_turno, sizeof(char[0]), 1, 0);
        printf("Fumador 2 %d: Tengo fosforo, recupero el papel\n",*fumador);
        msgrcv(cola_papel, &mi_turno, sizeof(char[0]), 1, 0);

        printf("Fumador 2 %d: Estoy fumando...🚬\n",*fumador);
        sleep(2);
        printf("Fumador 2 %d: Acabé de fumar.\n",*fumador);
        struct mensaje continua;
        continua.type = 1;
        msgsnd(proveedor, &continua, sizeof(char[0]), 0);
    }

}

void *fumador3(int *fumador) {
    struct mensaje aviso;
    aviso.type=1;
    while(1) {
        struct mensaje mi_turno;
        printf("Fumador 3 %d: Tengo fósforo.\n",*fumador);

        printf("Fumador 3 %d: Esperando papel...\n",*fumador);
        msgrcv(cola_papel, &mi_turno, sizeof(char[0]), 1, 0);
        printf("Fumador 3 %d: Tengo papel, y lo suelto\n",*fumador);
        msgsnd(cola_papel, &aviso, sizeof(char[0]), 0);
        printf("Fumador 3 %d: Esperando tabaco...\n",*fumador);
        msgrcv(cola_tabaco, &mi_turno, sizeof(char[0]), 1, 0);
        printf("Fumador 3 %d: Tengo tabaco, recupero el papel\n",*fumador);
        msgrcv(cola_papel, &mi_turno, sizeof(char[0]), 1, 0);

        printf("Fumador 3 %d: Estoy fumando...🚬\n",*fumador);
        sleep(2);
        printf("Fumador 3 %d: Acabé de fumar.\n",*fumador);
        struct mensaje continua;
        continua.type = 1;
        msgsnd(proveedor, &continua, sizeof(char[0]), 0);
    }
}

void *proveedor_th() {

    while(1) {
        printf("Proveedor: Eligiendo 2 elementos al azar...\n");
        struct mensaje aviso;
        int anterior = -1;
        int nuevo = -1;
        for(int i=0;i<2;i++){
            srand(time(NULL));
            
            do{
                nuevo=rand()%3;
            }while(nuevo==anterior);
            switch(nuevo) {
                case 0:
                printf("Proveedor: Suministro tabaco.\n");
                aviso.type = 1;
                msgsnd(cola_tabaco, &aviso, sizeof(char[0]), 0);
                break;
                case 1:
                printf("Proveedor: Suministro papel.\n");
                aviso.type = 1;
                msgsnd(cola_papel, &aviso, sizeof(char[0]), 0);
                break;
                case 2:
                printf("Proveedor:Suministro fosforo.\n");
                aviso.type = 1;
                msgsnd(cola_fosforo, &aviso, sizeof(char[0]), 0);
                break;            
            }
            anterior=nuevo;
        }
        
     
        printf("Proveedor: Esperando a que el fumador acabe...\n");
        struct mensaje seguir;
        msgrcv(proveedor, &seguir, sizeof(char[0]), 1, 0);
    }
}