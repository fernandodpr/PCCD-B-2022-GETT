#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
    //Para que sea más facil identificar el proceso imprimo PID
        int p_id, p_pid;

        p_id = getpid(); /*process id*/
        p_pid = getpid(); /*parent process id*/

        printf("Numero de proceso: %d\n", p_id);
        printf("Proceso Padre: %d\n", p_pid);
    //Reviso que la cantidad de parámetros introducidos sean los correctos
        if(sizeof(argc)<2) printf ("La cantidad de parámetros a introducirt es 2");

    //Ejecuto la llamada a la funcion kill
        
        int numero_signal = atoi(argv[1]);
        int pid = atoi(argv[2]);
        printf("Se va a finalizar el poceso: %d\n", pid);
        kill(pid, numero_signal);

    return 0;

}
