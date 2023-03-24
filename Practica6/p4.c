#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

struct msgStruct{
	long int num;
	char payload[256];
};
int main(int argc, char *argv[]){
	if(argc == 1) printf("Introduce los parámetros \n");
	else{
		int cola = strtol(argv[1], NULL, 10);
		struct msgStruct mensaje;
		
		mensaje.num = 1;
		int res = msgrcv(cola, &mensaje, 23, 1, 0);
		if(res != -1) printf("Mensaje %d recuperado: '%s'\n", mensaje.num,mensaje.payload);
		else printf("Ha ocurrido el error %d al recuperar el mensaje del buzón %d\n", errno, cola);
	}
}
