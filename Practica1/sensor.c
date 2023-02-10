#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int signal);

int salir = 0;
int estado = 1;
int pisos = 1;
int cantidadsubir = 0;
int cantidadbajar = 0;
int subiendo;
int bajando;
int T_PISO=5;
int pid_ascensor;
int esperando =0;

int main(int argc ,char *argv[]) {

    //Para que sea más facil identificar el proceso imprimo PID
        int p_id, p_pid;

        p_id = getpid(); /*process id*/
        p_pid = getpid(); /*parent process id*/
        pid_ascensor = atoi(argv[1]);
        int piso = atoi(argv[2]);
        int seleccion;
        int salir = 0;

        printf("Numero de proceso: %d\n", p_id);
        printf("Proceso Padre: %d\n", p_pid);
        printf("El ascensor tiene PID %d\n", pid_ascensor);
        printf("Sensor de piso: %d\n", piso);   



    struct sigaction signalstruct;
    signalstruct.sa_handler = handler;


    sigaction(10, &signalstruct, NULL); //SIGUSR1
    sigaction(SIGALRM, &signalstruct, NULL); //SIGALRM

    while (!salir) {
        pause();
        if(esperando){
            alarm(T_PISO);
            esperando =0;
        } 
    }
    return 0;

}

void handler(int signal) {
    printf("Recibida: %d      ",signal);
    switch(signal ) {
        case 10: //SIGUSR1 Subiendo a tu piso
            printf("Esperando ascensor... \n");
            esperando =1;
        break;
        case 14: //SIGALRM alarm(segundos)
            printf("Estado sensor:    ON \n");
            kill(pid_ascensor, SIGALRM);
        break;
        break;
        default: 
        break;
    }

}