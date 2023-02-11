/*
Ejercicio 1 (mini ejemplos):
Consulte el man de fork(). 
Escriba un proceso p1 que cree tres procesos hijo y espere en un bucle a recibir una señal utilizando la 
función pause(). Incluya un sleep en los procesos hijo para que finalicen unos segundos después de 
ser creados. El proceso padre deberá imprimir un mensaje en pantalla cada vez que finalice un proceso 
hijo, y finalizar cuando lo hayan hecho todos sus hijos.
*/

// #define SIGCHLD 17 /* Child status has changed (POSIX). */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


void handler_sigchld(int signal);

void mask_signal(int signal);
void unmask_signal(int signal);
void PID_printer();

int procesos_creados=0;
int procesos_activos=0;

int main(int argc ,char *argv[]) {
    PID_printer();

    struct sigaction signalstruct;
    signalstruct.sa_handler = handler_sigchld;
    sigaction(SIGCHLD, &signalstruct, NULL);

    while(procesos_creados<3){
      pid_t pid;
      pid = fork();
      procesos_creados++;
      procesos_activos++;

      if(pid==0){
        //fork()==0 es el valor que toma en el proceso hijo
        printf("Soy el hijo, mi ID es %d y mi padre es %d\n", getpid(), getppid());
        sleep(3);
        printf("Finalizado %d",getpid());
        return 0;
      } else if (pid > 0) {
        printf("Creado el proceso hijo: %d \n", pid);
      }else{
        //Esto implicaría que la creación del proceso hijo ha salido mal

      }
    }
    pause();

}

void handler_sigchld(int signal){
  //Esta señal es recibida cuando un proceso hijo.
  printf("Ha finalizado un proceso hijo.\n");
  procesos_activos--;
  if(procesos_activos==0) return;
  
}

void mask_signal(int signal) {
  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, signal);
  sigprocmask(SIG_BLOCK, &set, NULL);
}
//mask_signal(SIGUSR2); // Bloquea la señal SIGUSR2
void unmask_signal(int signal) {
  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, signal);
  sigprocmask(SIG_UNBLOCK, &set, NULL);
}
//unmask_signal(SIGUSR2); // Desbloquea la señal SIGUSR2

void PID_printer(){
    int p_id, p_pid;
    p_id = getpid(); /*process id*/
    p_pid = getpid(); /*parent process id*/
    printf("Numero de proceso: %d\n", p_id);
    printf("Proceso Padre: %d\n", p_pid); 
}
//PID_printer();