/*
Ejercicio 3 (mini ejemplos):
Consulte el man de pthread_join.
Escriba dos soluciones alternativas, p3 y p4, al grafo de precedencia del ejercicio 5 de la práctica 2 
utilizando threads.
*/
#include <pthread.h>
#include <stdio.h>

// función que se ejecutará en los hilos, recibe un argumento tipo void*
void *hilo(void arg){
char string = arg; // se convierte el argumento en un string
printf("%s", string); // se imprime el string recibido como argumento
}

// función que se ejecutará en el segundo hilo
void *hilo2(void *arg){
printf("Thiago, ");
printf("Silva, ");
}

int main(){
// se crean las variables para los identificadores de los hilos
pthread_t pique, ramos, carvajal, thiago;

printf("De Gea, ");
// se crean los hilos y se les pasa la función a ejecutar y el argumento correspondiente
pthread_create(&pique, NULL, hilo, "Piqué, ");
pthread_create(&ramos, NULL, hilo, "Ramos, ");
pthread_create(&carvajal, NULL, hilo, "Carvajal, ");
printf("Jordi Alba, ");

// se espera a que terminen los hilos creados previamente
pthread_join(pique, NULL);
pthread_join(ramos, NULL);
pthread_join(carvajal, NULL);

// se crea un nuevo hilo y se le pasa la función a ejecutar y el argumento correspondiente
pthread_create(&thiago, NULL, hilo2, "Thiago, ");

printf("Busquets, ");
printf("Isco, ");
printf("Aspas, ");

// se espera a que termine el hilo creado previamente
pthread_join(thiago, NULL);

printf("Morata\n");
}