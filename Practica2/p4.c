#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
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
      execl("./p4hijo.o", "nuevo_programa", "param1", "param2", (char *)NULL);
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
void PID_printer(){
    int p_id, p_pid;
    p_id = getpid(); //process id/
    p_pid = getpid(); //parent process id/
    printf("Numero de proceso: %d\n", p_id);
    printf("Proceso Padre: %d\n", p_pid);
}