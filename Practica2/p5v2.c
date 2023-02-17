#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int contador = 0;
int estado;
int pid_Jordi, pid_Thiago_Silva;
int acaba = 0;

int main() { //Cantidad de procesos 4

    printf("De Gea ");

    if(fork() == 0) {
        printf("Ramos ");


        exit(EXIT_SUCCESS);
    } else {

        if(fork() == 0) {

            printf("Piqué ");
            exit(EXIT_SUCCESS);

        } else {

            if((pid_Jordi = fork()) == 0) {

                printf("Jordi Alba ");
                exit(EXIT_SUCCESS);

            } else {

                printf("Carvajal ");

                while(contador < 3) {
                    int pid = wait(&estado);  //Espero hasta que un hijo termina, cualquiera

                    if (pid == pid_Jordi) { //SOLO DESPUES DE JORDI PUEDE IR THIAGO

                        if((pid_Thiago_Silva = fork()) == 0) {
                            printf("Thiago ");
                            printf("Silva ");
                            exit(EXIT_SUCCESS);
                        }

                    } 

                    if (pid != pid_Thiago_Silva) { 

                        contador++;
                    
                    } else {

                        acaba++;

                    }

                } //Terminaron las "tres ramas"

                printf("Busquets ");
                printf("Isco ");
                printf("Aspas ");

                if(!acaba) {
                    wait(&estado);
                }

                printf("Morata\n");
                printf("Respuesta ejemplo:\nDe Gea Ramos Carvajal Piqué Jordi-Alba Busquets Isco Thiago Aspas Silva Morata \n");

            }
        }
    }

    return 0;
    
}
