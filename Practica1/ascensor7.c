#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int signal);
void handler_sigusr1(int signal);
void handler_sigusr2(int signal);
void handler_sigalarm(int signal);
void mask_signal(int signal);
void unmask_signal(int signal);

int salir = 0;
int estado = 1;
int pisos = 1;
int cantidadsubir = 0;
int cantidadbajar = 0;
int subiendo;
int bajando;
int T_PISO=5;
int pid_sensor_0;
int pid_sensor_1;

int main(int argc ,char *argv[]) {

    //Para que sea más facil identificar el proceso imprimo PID
        int p_id, p_pid;

        p_id = getpid(); /*process id*/
        p_pid = getpid(); /*parent process id*/

        printf("Numero de proceso: %d\n", p_id);
        printf("Proceso Padre: %d\n", p_pid);    
    
    printf("Iniciando el ascensor...\n");

    struct sigaction signalstruct;
    signalstruct.sa_handler = handler;

    sigaction(2, &signalstruct, NULL); //ctrl+C
    sigaction(SIGQUIT, &signalstruct, NULL); //SIGQUIT


    signalstruct.sa_handler = handler_sigusr1;
        sigaction(SIGUSR1, &signalstruct, NULL); //SIGUSR1
    signalstruct.sa_handler = handler_sigusr2;
        sigaction(SIGUSR2, &signalstruct, NULL); //SIGUSR2
    signalstruct.sa_handler = handler_sigalarm;
    sigaction(SIGALRM, &signalstruct, NULL); //SIGALRM

    bajando = 0;
    subiendo = 0;

    printf("\nIntroduce el PID del sensor 0: ");
    scanf("%d", &pid_sensor_0);
    printf("\nIntroduce el PID del sensor 1: ");
    scanf("%d", &pid_sensor_1);


    while (!salir) {

        pause();

        if (subiendo == 1) {
            printf("Pisoactual:  %d\n", estado);
            if (estado < pisos) {
                cantidadsubir++;
                estado++;
                //Subiendo
                printf("Subiendo...");
                //alarm(T_PISO);
                kill(pid_sensor_1, SIGUSR1);

            }else{
                printf("Orden incorrecta, ya estás en el piso superior.\n");
            }
            subiendo=0;
        }

        if (bajando == 1) {
            printf("Pisoactual:  %d\n", estado);
            if (estado > 0) {
                printf("Bajando...");
                cantidadbajar++;
                estado--;
                //alarm(T_PISO);
                kill(pid_sensor_0, SIGUSR1);

            }else{
                printf("Orden incorrecta, el ascensor se encuentra en el piso más bajo. \n");
            }
            bajando=0;
        }

    }

    printf("\nSubidas: %i     Bajadas: %i\n", cantidadsubir, cantidadbajar);

    return 0;

}

void handler(int signal) {
    printf("Recibida: %d      ",signal);
    switch(signal ) {
        case 3: //SIGQUIT
            printf("SIGTERM, saliendo del programa\n");
            salir = 1;
        break;
        case 2:
            printf("Signal 2, ctrl+c. Saliendo del programa\n");
            salir = 1;
        break;
        default: 
        break;
    }

}

void handler_sigusr1(int signal){
    printf("Signal SIGUSR1 (Orden de subir).\n");
    mask_signal(SIGUSR1); // Bloquea la señal SIGUSR1
    mask_signal(SIGUSR2); // Bloquea la señal SIGUSR2
    subiendo=1;
}
void handler_sigusr2(int signal){
    printf("Signal SIGUSR1 (Orden de bajar).\n");
    mask_signal(SIGUSR1); // Bloquea la señal SIGUSR1
    mask_signal(SIGUSR2); // Bloquea la señal SIGUSR2
    bajando=1;
}
void handler_sigalarm(int signal){
    printf("Completado, piso actual:  %d\n", estado);
    unmask_signal(SIGUSR1); // Desbloquea la señal SIGUSR1
    unmask_signal(SIGUSR2); // Desbloquea la señal SIGUSR2
}



void mask_signal(int signal) {
  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, signal);
  sigprocmask(SIG_BLOCK, &set, NULL);
}
void unmask_signal(int signal) {
  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, signal);
  sigprocmask(SIG_UNBLOCK, &set, NULL);
}

