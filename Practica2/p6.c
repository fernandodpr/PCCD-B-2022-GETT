#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int contador = 0;
int estado;
int pid_Jordi, pid_Thiago_Silva;
int acaba = 0;

int main() {

    printf("De Gea \n");
    if(fork() == 0) {

        execl("p6hijo", "Ramos ", (char*) 0);

    } else {

        if(fork() == 0) {

            execl("p6hijo", "Piqué ", (char*) 0);

        } else {

            if((pid_Jordi = fork()) == 0) {

                execl("p6hijo", "Jordi Alba ", (char*) 0);

            } else {

                printf("Carvajal ");

                while(contador < 3) {

                    int pid = wait(&estado);

                    if (pid == pid_Jordi) {

                        if((pid_Thiago_Silva = fork()) == 0) {

                            execl("p6hijo", "Thiago ", "Silva ", (char*) 0);
                
                        }

                    } 
                    if (pid != pid_Thiago_Silva) {
                        contador++;
                    } else {
                        acaba++;
                    }
                }
                printf("Busquets ");
                printf("Isco ");
                printf("Aspas ");

                if(!acaba) {
                    wait(&estado);
                }
                printf("Morata\n");

            }
        }
    }

    return 0;
    
}
