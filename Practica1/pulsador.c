//Ejercicio 6
#include <signal.h>
#include <stdlib.h> 
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


//PULSADOR (RECIBE EL PID DEL ASCENSOR EN LA LLAMADA)
int main(int argc, char *argv[]) {

    int pid_ascensor = atoi(argv[1]);
    int seleccion;
    int salir = 0;
    

    while(!salir){
        printf("\n1) Enviar orden de SUBIDA.");
        printf("\n2) Enviar orden de BAJADA.");
        printf("\n3) SALIR.\n  ");
        scanf("%d", &seleccion);

        switch(seleccion) {  
            case 1:
            kill(pid_ascensor, SIGUSR1);
            break;

            case 2:
            kill(pid_ascensor, SIGUSR2);
            break;
            
            case 3:
            kill(pid_ascensor, SIGQUIT);
            salir = 1;
            break;

            default:
            break;

        }
    }
    return 0;
}