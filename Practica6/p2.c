#include <stdlib.h>
#include <sys/msg.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	if(argc <= 1) printf("Inttroduce los marámetros correctos.\n");
	else{
		int cola = strtol(argv[1], NULL, 10);
		int res = msgctl(cola, IPC_RMID, NULL);
		if(res != -1) printf("Se ha eliminado la cola con msqid %d \n", cola);
		else printf("Error al eliminar la cola con msqid %d\n", cola);
	}
}
