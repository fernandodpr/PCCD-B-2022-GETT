#include <unistd.h>
#include <stdio.h>
#include <signal.h>


void handler(int signal);


int usr1,usr2;
int done = 0; 
int signalInteres[4] = {10,15,12,2};
int main(){
    //If the signal causes a handler function to be executed, then pause returns. 
    //This is considered an unsuccessful return (since “successful” behavior would be to suspend the program forever), so the return value is -1. 
    //Even if you specify that other primitives should resume when a system handler returns (see Primitives Interrupted by Signals), this has no effect on pause; it always fails when a signal is handled.

    //Para que sea más facil identificar el proceso imprimo PID
        int p_id, p_pid;

        p_id = getpid(); /*process id*/
        p_pid = getpid(); /*parent process id*/

        printf("Numero de proceso: %d\n", p_id);
        printf("Proceso Padre: %d\n", p_pid);
    //Creo la estructura sigaction y defino el signal handler.
        struct sigaction sigaction_parametro;
        sigaction_parametro.sa_handler = handler;
        /*
        SA_RESTART
                Provide behavior compatible with BSD signal semantics by
                making certain system calls restartable across signals.
                This flag is meaningful only when establishing a signal
                handler.  See signal(7) for a discussion of system call
                restarting.
        */
        /* 
        SA_RESETHAND
            Restore the signal action to the default upon entry to the
            signal handler.  This flag is meaningful only when
            establishing a signal handler.
        Restablece la señal a su default después de la primera ejecución
        
        */
        sigaction_parametro.sa_flags = SA_RESETHAND; 
    // Ahora utilizando la función sigcation tengo que definir a cada señal los parámetros sigaction_parametro 

        //Cuantas señales hay? Creo que hay 31 y después hay otras 32 más de tiempo real??

        for(int i=0;i<sizeof(signalInteres);i++){
            sigaction(signalInteres[i],&sigaction_parametro,NULL);
            //sigactionint signum,const struct sigaction *restrict act, struct sigaction *restrict oldact)            
            printf("Definida:  %i\n",signalInteres[i]);

        }

        usr1=0;
        usr2=0;


        while(!done){
            pause();
        }


        printf("Se han recibido %d señales SIGUSR1\n", usr1);
        printf("Se han recibido %d señales SIGUSR2\n", usr2);
}


void handler(int signal) {
    printf("Recibida: %d      ",signal);
    switch(signal ) {
        case 10: //SIGUSR1
            printf("Signal SIGUSR1\n");
            usr1++;
        break;
        case 12: //SIGUSR2
            printf("Signal SIGUSR2\n");
            usr2++;
        break;
        case 15: //SIGTERM
            printf("SIGTERM, saliendo del programa\n");
            done = 1;
        break;
        case 2:
            printf("Signal 2, ctrl+c. Saliendo del programa\n");
            done = 1;
        break;

        default: 
        break;
    }

}