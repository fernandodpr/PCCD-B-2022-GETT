//Ejercicio 1 de la práctica 1
//Ejercicio 1 (mini ejemplos):
//Consulte el man del comando kill.
//Escriba un proceso p1 que espere a recibir una señal utilizando la función pause() (consulte el man de
//dicha función). Envíe a dicho proceso, utilizando el comando kill, cada una de las señales definidas y
//compruebe la acción por defecto de cada una de ellas.
#include <unistd.h>
#include <stdio.h>

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
        
    int resultado = pause();

    printf("Se ha retomado la ejecucuión del programa\n");
    printf("El resultado de pause() es: %d \n",resultado);

    return 0;


}