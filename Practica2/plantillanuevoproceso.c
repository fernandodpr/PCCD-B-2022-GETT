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
void PID_printer():

int main(int argc ,char *argv[]) {
    PID_printer();
    /*
    //Definciones de los handler
    struct sigaction signalstruct;
    signalstruct.sa_handler = handler;

    signalstruct.sa_handler = handler_sigusr1;
        sigaction(SIGUSR1, &signalstruct, NULL); //SIGUSR1
    signalstruct.sa_handler = handler_sigusr2;
        sigaction(SIGUSR2, &signalstruct, NULL); //SIGUSR2
    signalstruct.sa_handler = handler_sigalarm;
        sigaction(SIGALRM, &signalstruct, NULL); //SIGALRM
    */

}


void handler(int signal) {

}

void handler_sigusr1(int signal){

}
void handler_sigusr2(int signal){

}
void handler_sigalarm(int signal){

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