#include <stdlib.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

bool bucle = true;  // Variable para controlar el bucle principal
sem_t sem;  // Semáforo para el acceso a la sección crítica

// Estructura que se utiliza para pasar parámetros a la función 'leer'
struct ParametrosLector{
    int num;
    sem_t *semaforoIn;
    sem_t *semaforoOut;
};

// Función que se ejecuta en un hilo para leer datos
void *leer(void *parametro){
    struct ParametrosLector *parametros = parametro;
    int num = parametros->num;
    sem_t *in = parametros->semaforoIn;
    sem_t *out = parametros->semaforoOut;
    
    while(bucle){
        printf("[Lector %d] Esperando a intentar leer\n", num);
        sem_wait(in);
        printf("[Lector %d] Intentando leer\n", num);
        sem_wait(&sem);
        printf("[Lector %d] Leyendo...\n", num);
        sem_wait(out);
        printf("[Lector %d] Fin lectura\n", num);
        sem_post(&sem);
    }
}

int main(int argc, char* argv[]){
    if(argc != 3) printf("Introcuce N1 y N2 como parámetros.\n");
    else{
        int n1 = strtol(argv[1], NULL, 10);  // Número de lectores
        int n2 = strtol(argv[2], NULL, 10);  // Número máximo de lectores simultáneos
        int menu;
        sem_t sincsIn[n1];  // Semáforos para la entrada de los lectores
        sem_t sincsOut[n1];  // Semáforos para la salida de los lectores
        struct ParametrosLector parametros[n1];
        
        if(n1 < n2) printf("N1 tiene que ser mayor que N2\n");
        else{
            sem_init(&sem, 0, n2);  // Inicializar el semáforo para el acceso a la sección crítica
            pthread_t threadID;
            
            for(int i=0; i<n1; i++){
                sem_init(&sincsIn[i], 0, 0);
                sem_init(&sincsOut[i], 0, 0);
                parametros[i].num = i+1;
                parametros[i].semaforoIn = &sincsIn[i];
                parametros[i].semaforoOut = &sincsOut[i];
                void *parametro = &parametros[i];
                pthread_create(&threadID, NULL, leer, parametro);  // Crear un hilo para cada lector
            }
            
            while(bucle){
                printf("1.-Intentar leer\n");
                printf("2.-Finalizar leer\n");
                printf("3.-Salir\n");
                
                scanf("%d", &menu);
                
                switch(menu){
                    case 1:
                        printf("Introduce un número de 1 a %d: ", n1);
                        scanf("%d", &menu);
                        sem_post(&sincsIn[menu-1]);  // Señalar que el lector puede intentar leer
                        break;
                    case 2:
                        printf("Introduce un número de 1 a %d: ", n1);
                        scanf("%d", &menu);
                        if(menu <= n1 && menu >= 1){
                            sem_post(&sincsOut[menu-1]);
                        }
                        else{
                            printf("Introduce un número válido\n");
                        }
	                    break;
                    case 3:
	                    bucle = false;
	                    break;
                    default:
                        bucle = false;
                        for(int i=0; i<n1; i++){
                            sem_post(&sincsIn[i]);
                        }
                        for(int i=0; i<n1; i++){
                            pthread_join(threadID, NULL);
                            sem_destroy(&sincsIn[i]);
                            sem_destroy(&sincsOut[i]);
                        }
                        sem_destroy(&sem);
                        break;
                }
            }
        }
    }
}
