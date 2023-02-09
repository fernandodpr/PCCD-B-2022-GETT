#include <unistd.h>
#include <stdio.h>
#include <signal.h>


void handler(int signal);


int bits[32];
int done = 0; 
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
    // Ahora utilizando la función sigcation tengo que definir a cada señal los parámetros sigaction_parametro 

        //Cuantas señales hay? Creo que hay 31 y después hay otras 32 más de tiempo real??

        for(int i=0;i<32;i++){
            sigaction(i,&sigaction_parametro,NULL);
            //sigactionint signum,const struct sigaction *restrict act, struct sigaction *restrict oldact)
            bits[i] = 0; //El resultado es este vector de bits
            printf("Definida:  %i\n",i);
        }

        while(!done){
            pause();
        }


        for (int i=0; i<32; ++i)
            printf(" Senhal %d -> %d \n",i,bits[i]);
        

}


void handler(int signal) {

    printf("Se ha recibido la señal:  %d \n",signal);
        bits[signal]=1;
    switch(signal) {
        case 15:
            printf("Signal 15, saliendo del programa");
            done =1;
        break;
        case 2:
            printf("Signal 2, ctrl+c. Saliendo del programa");
            done = 1;
        break;

        default: 
        break;
    }

}