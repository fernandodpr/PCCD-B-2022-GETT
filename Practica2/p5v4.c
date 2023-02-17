#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int contador = 0; // contador de procesos hijos
int estado; // estado de un proceso hijo al terminar
int pid_Jordi, pid_Thiago_Silva; // PID de procesos hijos específicos
int acaba = 0; // flag para indicar si Thiago Silva terminó

int main() {
    printf("De Gea "); // imprime el primer nombre
    //NIVEL 1
    if (fork() == 0) { // crea un proceso hijo
        printf("Ramos "); // imprime el nombre del proceso hijo
        exit(EXIT_SUCCESS); // el proceso hijo termina y sale
    } else {
        if (fork() == 0) {
            printf("Piqué ");
            exit(EXIT_SUCCESS);
        } else {
            if ((pid_Jordi = fork()) == 0) {
                printf("Jordi Alba ");
                if ((pid_Thiago_Silva = fork()) == 0) {
                    printf("Thiago ");
                    printf("Silva ");
                    exit(EXIT_SUCCESS);
                }
                exit(EXIT_SUCCESS);

            } else {
                printf("Carvajal ");

                
                while (contador < 3) { // espera a que tres procesos hijos terminen
                    int pid = wait(&estado); // espera a que cualquier proceso hijo termine y guarda su estado

                    if (pid == pid_Jordi) { // si Jordi Alba termina, crea un nuevo proceso hijo

                    }

                    if (pid != pid_Thiago_Silva) {
                        contador++; // si el proceso hijo que terminó NO es Thiago Silva, incrementa el contador
                    } else {
                        acaba++; // si es Thiago Silva, actualiza la bandera
                    }
                }

                printf("Busquets ");
                printf("Isco ");
                printf("Aspas ");

                if (!acaba) { // si Thiago Silva no terminó, espera a que termine
                    wait(&estado);
                }

                printf("Morata\n"); // imprime el último nombre
                printf("Respuesta ejemplo:\nDe Gea Ramos Carvajal Piqué Jordi-Alba Busquets Isco Thiago Aspas Silva Morata \n");
            }
        }
    }

    return 0;
}