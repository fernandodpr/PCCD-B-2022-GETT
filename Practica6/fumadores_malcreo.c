#include <stdio.h>
#include <pthread.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
//creo que esto que son colas únicas no es lo adecuado
int ID_fumador1, ID_fumador2, ID_fumador3, ID_proveedor;

void *fumador1(), *fumador2(), *fumador3(), *proveedor();

struct mensaje {
    long mstype;
    char mstxt[0];

};

int main() {

    //Creamos las colas
    ID_fumador1 = msgget(1245, IPC_CREAT|0777);
    ID_fumador2 = msgget(2584, IPC_CREAT|0777);
    ID_fumador3 = msgget(3589, IPC_CREAT|0777);
    ID_proveedor = msgget(1478, IPC_CREAT|0777);

    if((ID_fumador1 == -1)||(ID_fumador2 == -1)||(ID_fumador3 == -1)||(ID_proveedor == -1)) {

        printf("Problema al crear colas.\n");
        return 0;

    }

    //Creamos los hilos
    pthread_t fum1, fum2, fum3, prov;

    if((pthread_create(&fum1, NULL, fumador1, NULL) != 0)||(pthread_create(&fum2, NULL, fumador2, NULL) != 0)||(pthread_create(&fum3, NULL, fumador3, NULL) != 0)||(pthread_create(&prov, NULL, proveedor, NULL) != 0)) {

        printf("Problema al crear filósofos.\n");
        return 0;

    }

    while(1) {}

    return 0;
 
}



void *fumador1 () {
    
    while(1) {
        struct mensaje mi_turno;
        printf("Fumador 1: Tengo papel.\n");
        printf("Fumador 1: Esperando tabaco y fósforos...\n");
        msgrcv(ID_fumador1, &mi_turno, sizeof(char[0]), 1, 0);
        printf("Fumador 1: Estoy fumando...\n");
        printf("Fumador 1: Acabé de fumar.\n");
        struct mensaje continua;
        continua.mstype = 1;
        msgsnd(ID_proveedor, &continua, sizeof(char[0]), 0);
    }

}

void *fumador2 () {
    while(1) {
        struct mensaje mi_turno;

        printf("Fumador 2: Tengo tabaco.\n");
        printf("Fumador 2: Esperando papel y fósforos...\n");
        msgrcv(ID_fumador2, &mi_turno, sizeof(char[0]), 2, 0); 
        printf("Fumador 2: Estoy fumando...\n");
        printf("Fumador 2: Acabé de fumar.\n");
        struct mensaje continua;
        continua.mstype = 1;
        msgsnd(ID_proveedor, &continua, sizeof(char[0]), 0);
    }

}

void *fumador3() {
    while(1) {  
        struct mensaje mi_turno;
        printf("Fumador 3: Tengo fósforos.\n");
        printf("Fumador 3: Esperando papel y tabaco...\n");
        msgrcv(ID_fumador3, &mi_turno, sizeof(char[0]), 3, 0);
        printf("Fumador 3: Estoy fumando...\n");
        printf("Fumador 3: Acabé de fumar.\n");
        struct mensaje continua;
        continua.mstype = 1;
        msgsnd(ID_proveedor, &continua, sizeof(char[0]), 0);
    }
}

void *proveedor() {

    while(1) {
        printf("Proveedor: Eligiendo 2 elementos al azar...\n");
        struct mensaje aviso;
        srand(time(NULL));
        switch(rand()%3) {
            case 0:
            printf("Proveedor: Tabaco y fósforos colocados.\n");
            aviso.mstype = 1;
            break;
            case 1:
            printf("Proveedor: Papel y fósforos colocados.\n");
            aviso.mstype = 2;
            break;
            case 2:
            printf("Proveedor: Papel y tabaco colocados.\n");
            aviso.mstype = 3;
            break;            
        }
        msgsnd(ID_fumador1, &aviso, sizeof(char[0]), 0);
        msgsnd(ID_fumador2, &aviso, sizeof(char[0]), 0);
        msgsnd(ID_fumador3, &aviso, sizeof(char[0]), 0);
        printf("Proveedor: Esperando a que el fumador acabe...\n");
        struct mensaje sigo;
        msgrcv(ID_proveedor, &sigo, sizeof(char[0]), 1, 0);
    }
}