/*
Ejercicio 2 (mini ejemplos):
Consulte el man de wait() y exit().
Repita el Ejercicio 1 utilizando la función wait() en vez de pause() y sin capturar la señal SIGCHLD.
Incluya la función exit() para finalizar cada proceso hijo. Cada vez que finalice un proceso hijo, el proceso padre deberá imprimir en pantalla el pid del proceso finalizado y el código de finalización utilizado 
en el exit() por dicho proceso hijo.
*/

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
  while(procesos_creados<3){
    pid_t pid;
    pid = fork();
    procesos_creados++;
    procesos_activos++;

    if(pid==0){
      //fork()==0 es el valor que toma en el proceso hijo
      printf("Soy el hijo, mi ID es %d y mi padre es %d\n", getpid(), getppid());
      sleep(3);
      printf("Finalizado %d\n",getpid());
      exit(0);
    } else if (pid > 0) {
      printf("Creado el proceso hijo: %d \n", pid);
      int status;
      pid_t p = wait(&status);
      printf("Finalizado proceso hijo %d con código de salida %d\n", p, WEXITSTATUS(status));
      procesos_activos--;
    }else{
      //Esto implicaría que la creación del proceso hijo ha salido mal

   }
  }
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