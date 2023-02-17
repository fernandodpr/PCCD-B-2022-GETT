#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

int procesos_creados=0;
int procesos_activos=0;

void PID_printer();

int main(int argc ,char *argv[]) {
    PID_printer();
    while(procesos_creados<3){
        pid_t pid;
        pid = fork();
        procesos_creados++;
        procesos_activos++;

        if(pid==0){
            //fork()==0 es el valor que toma en el proceso hijo
            srand(time(NULL));
            int sleep_time = 3 + rand() % 6;
            printf("Soy el hijo, mi ID es %d y mi padre es %d\n", getpid(), getppid());
            sleep(sleep_time);
            printf("Finalizado %d\n",getpid());
            exit(0);
        } else if (pid > 0) {
            printf("Creado el proceso hijo: %d \n", pid);
        }else{
            //Esto implicaría que la creación del proceso hijo ha salido mal

        }
    }
    int status;
    pid_t pid_hijo;
    while (procesos_activos > 0) {
        pid_hijo = waitpid(-1, &status, WNOHANG);
        if (pid_hijo > 0) {
            procesos_activos--;
            printf("Finalizado proceso hijo con PID %d y codigo de estado %d\n", pid_hijo, WEXITSTATUS(status));
            system("ps");
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