/*Ejercicio 1 (mini ejemplos):
Consulte el man de msgget.
Escriba un proceso p1 que cree una cola de mensajes. 
Compruebe con el comando ipcs –q que la cola 
se crea correctamente según los permisos indicados.*/
#include <sys/msg.h>
#include <stdio.h>

int main(){
	int cola = msgget(20, 0777 | IPC_CREAT);
	printf("Identificador de cola (msqid): %d\n", cola);
}
