#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

bool bucle = true;
int papel = 0;
sem_t semEsc;
sem_t semLec;
sem_t semGen;

struct paramStruct{
	bool *tru;
	int num;
};

void *escribir(void *arg){
	struct paramStruct *parametros = arg;
	int num = parametros->num;
	bool *escribe;
	bool inercia = false;
	while(bucle){
		escribe = parametros->tru;
		if(inercia && *escribe) printf("[Escritor %d]Escribiendo...\n", num);
		else if(*escribe){
			printf("[Escritor %d]Intentando escribir...\n", num);
			papel++;
			sem_wait(&semGen);
			sem_wait(&semEsc);
			printf("[Escritor %d]Escribiendo...\n", num);
			inercia = true;
		}
		else if(inercia){
			sem_post(&semEsc);
			papel--;
			sem_post(&semGen);
			printf("[Escritor %d]Fin escritura\n", num);
			inercia = false;
		}
		else printf("[Escritor %d]Esperando a intentar escribir...\n", num);
		sleep(2);
	}
}

void *leer(void *arg){
	struct paramStruct *parametros = arg;
	int num = parametros->num;
	bool *lee;
	bool inercia = false;
	while(bucle){
		lee = parametros->tru;
		if(inercia && *lee) printf("[Lector %d]Leyendo...\n", num);
		else if(*lee){
			printf("[Lector %d]Intentando leer...\n", num);
			while(papel != 0){
				sem_wait(&semGen);
				sem_post(&semGen);
			}
			sem_wait(&semLec);
			printf("[Lector %d]Leyendo...\n", num);
			inercia = true;
		}
		else if(inercia){
			sem_post(&semLec);
			printf("[Lector %d]Fin lectura\n", num);
			inercia = false;
		}
		else printf("[Lector %d]Esperando a intentar leer...\n", num);
		sleep(2);
	}
}

int main(int argc, char* argv[]){
	if(argc != 4) printf("Por favor, introduce tres parámetros que sean números enteros\n");
	else{
		int n1 = strtol(argv[1], NULL, 10);
		int n2 = strtol(argv[2], NULL, 10);
		int n3 = strtol(argv[3], NULL, 10);
		
		bool leyendo[n1];
		bool escribiendo[n3];
		for(int i=0; i<n1; i++) leyendo[i] = false;
		for(int i=0; i<n3; i++) escribiendo[i] = false;
		
		sem_init(&semEsc, 0, 1);
		sem_init(&semLec, 0, n2);
		sem_init(&semGen, 0, 1);
		pthread_t threadID;
		struct paramStruct escritores[n3];
		struct paramStruct lectores[n1];
		void *esc, *lec;
		
		for(int i=0; i<n1; i++){
			lectores[i].num = i+1;
			lectores[i].tru = &leyendo[i];
			lec = &lectores[i];
			pthread_create(&threadID, NULL, leer, lec);
		}
		for(int i=0; i<n3; i++){
			escritores[i].num = i+1;
			escritores[i].tru = &escribiendo[i];
			esc = &escritores[i];
			pthread_create(&threadID, NULL, escribir, esc);
		}
		
		int menu;
		
		while(bucle){
			printf("1.-Intentar escribir\n");
			printf("2.-Finalizar escribir\n");
			printf("3.-Intentar leer\n");
			printf("4.-Finalizar leer\n");
			printf("5.-Salir\n");
			
			scanf("%d", &menu);
			
			switch(menu){
				case 1:
					printf("Introduce un número de 1 a %d: ", n3);
					scanf("%d", &menu);
					escribiendo[menu-1] = true;
					break;
				case 2:
					printf("Introduce un número de 1 a %d: ", n3);
					scanf("%d", &menu);
					escribiendo[menu-1] = false;
					break;
				case 3:
					printf("Introduce un número de 1 a %d: ", n1);
					scanf("%d", &menu);
					leyendo[menu-1] = true;
					break;
				case 4:
					printf("Introduce un número de 1 a %d: ", n1);
					scanf("%d", &menu);
					leyendo[menu-1] = false;
					break;
				case 5:
					bucle = false;
					break;
				default:
					printf("Introduce una opción válida\n");
					break;
			}
		}
	}
}
