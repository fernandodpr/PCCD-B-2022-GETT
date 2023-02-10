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

    sigaction(2, &signalstruct, NULL); //ctrl+C //Esto no es obligatorio en la práctica pero me facilita el matar el proceso
    sigaction(3, &signalstruct, NULL); //SIGQUIT
    sigaction(10, &signalstruct, NULL); //SIGUSR1
    sigaction(12, &signalstruct, NULL); //SIGUSR2
    
    bajando = 0;
    subiendo = 0;

    while (!salir) {

        pause();

        if (subiendo == 1) {
            printf("Pisoactual:  %d\n", estado);
            if (estado < pisos) {
                cantidadsubir++;
                estado++;

                //Subiendo
                printf("Subiendo...");
                alert(T_PISO);
            }else{
                printf("Orden incorrecta, ya estás en el piso superior.\n");
            } 
            subiendo = 0;
        }

        if (bajando == 1) {
            printf("Pisoactual:  %d\n", estado);
            if (estado > 0) {
                printf("a");
                cantidadbajar++;
                estado--;
                printf(" Bajando...");
                alert(T_PISO);

            }else{
                printf("Orden incorrecta, el ascensor se encuentra en el piso más bajo. \n");
            }
            bajando = 0;
        }

    }

    printf("\nSubidas: %i     Bajadas: %i\n", cantidadsubir, cantidadbajar);

    return 0;

}

void handler(int signal) {
    printf("Recibida: %d      ",signal);
    switch(signal ) {
        case 10: //SIGUSR1 SUBIR
            printf("Signal SIGUSR1 (Orden de subir).\n");
            subiendo=1;

        break;
        case 12: //SIGUSR2
            printf("Signal SIGUSR1 (Orden de bajar).\n");
            bajando=1;
        break;
        case 3: //SIGQUIT
            printf("SIGTERM, saliendo del programa\n");
            salir = 1;
        break;
        case 2:
            printf("Signal 2, ctrl+c. Saliendo del programa\n");
            salir = 1;
        break;
        case 14: //SIGALRM alarm(segundos)
            printf("Completado, piso actual:  %d\n", estado);
            bajando=0;
            subiendo=0;
        break;
        default: 
        break;
    }

}