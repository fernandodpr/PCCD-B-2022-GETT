#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct msgStruct{
	long num;
	char payload[256];
};

int main(int argc, char *argv[]){
	if(argc == 1) printf("Intorduce los parámetros correctamente\n");
	else{
		int cola = strtol(argv[1], NULL, 10);
		char * payload = "Mensaje importante.";
		struct msgStruct mensaje;
		
		mensaje.num = 1;
		strcpy(mensaje.payload, payload);
		int res = msgsnd(cola, &mensaje, strlen(payload), 0);
		if(res != -1) printf("Enviado\n");
		else printf("Error al enviar\n");
	}
}
