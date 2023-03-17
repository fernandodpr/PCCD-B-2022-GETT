#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

bool running = true; // Variable para controlar el bucle principal
sem_t sem;           // Semáforo para controlar la escritura

struct paramStruct {
  int num;       // Número del escritor
  sem_t *semIn;  // Semáforo para iniciar la escritura
  sem_t *semOut; // Semáforo para finalizar la escritura
};

void *escribir(void *arg) {
  struct paramStruct *parametros = arg;
  int num = parametros->num;
  sem_t *in = parametros->semIn;
  sem_t *out = parametros->semOut;
  while (running) {
    printf("[Escritor %d] Esperando a intentar escribir\n", num);
    sem_wait(in);
    printf("[Escritor %d] Intentando escribir\n", num);
    sem_wait(&sem);
    printf("[Escritor %d] Escribiendo\n", num);
    sem_wait(out);
    printf("[Escritor %d] Fin escritura\n", num);
    sem_post(&sem);
  }
}

int main(int argc, char *argv[]) {
if(argc != 2) printf("Por favor, introduce un parámetro que sea un número entero\n");
    else{
        int num_escritores = strtol(argv[1], NULL, 10); // Número de escritores que se van a crear
        int opcion_menu;
        sem_t semIn[num_escritores]; // Semáforos para iniciar la escritura de cada escritor
        sem_t semOut[num_escritores]; // Semáforos para finalizar la escritura de cada escritor
        struct paramStruct parametros[num_escritores]; // Parámetros para los hilos escritores
        sem_init(&sem, 0, 1); // Inicialización del semáforo principal
        pthread_t threadID;
        void *param;
        for(int i=0; i<num_escritores; i++){
            sem_init(&semIn[i], 0, 0); // Inicialización de los semáforos de inicio de escritura
            sem_init(&semOut[i], 0, 0); // Inicialización de los semáforos de fin de escritura
            parametros[i].num = i+1; // Asignación del número del escritor
            parametros[i].semIn = &semIn[i]; // Asignación del semáforo de inicio de escritura
            parametros[i].semOut = &semOut[i]; // Asignación del semáforo de fin de escritura
            param = &parametros[i];
            pthread_create(&threadID, NULL, escribir, param); // Creación del hilo escritor
        }
        int menu;
        while(running){
            printf("1.-Intentar escribir\n");
            printf("2.-Finalizar escribir\n");
            printf("3.-Salir\n");

            scanf("%d", &menu); // Lectura de la opción del menú

        switch (menu) {
            case 1:
                printf("Introduce un número de 1 a %d: ", num_escritores);
                scanf("%d", &menu);
                sem_post(&semIn[menu - 1]);
            break;
      case 2:
        printf("Introduce un número de 1 a %d: ", num_escritores);
        scanf("%d", &menu);
        sem_post(&semOut[menu - 1]);
        break;
      case 3:
        running = false;
        break;
      default:
        printf("Elige una opción correcta\n");
        break;
      }
    }
  }
}