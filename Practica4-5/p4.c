#include <pthread.h>
#include <stdio.h>

void *hilo(void *arg){
    char* string = arg;
    printf("%s", string);
}

void *hilo2(void *arg){
    printf("Busquets, ");
    printf("Isco, ");
    printf("Aspas, ");
}

int main(){
    pthread_t pique, ramos, carvajal, busquets;
    
    // Imprime el primer jugador
    printf("De Gea, ");
    
    // Crea los hilos para imprimir los nombres de los jugadores
    pthread_create(&pique, NULL, hilo, "Piqué, ");
    pthread_create(&ramos, NULL, hilo, "Ramos, ");
    pthread_create(&carvajal, NULL, hilo, "Carvajal, ");
    
    // Imprime el siguiente jugador
    printf("Jordi Alba, ");
    
    // Espera a que los hilos terminen antes de continuar
    pthread_join(pique, NULL);
    pthread_join(ramos, NULL);
    pthread_join(carvajal, NULL);
    
    // Crea un nuevo hilo para imprimir los siguientes jugadores
    pthread_create(&busquets, NULL, hilo2, "Busquets, ");
    
    // Imprime los siguientes jugadores
    printf("Thiago, ");
    printf("Silva, ");
    
    // Espera a que el hilo termine antes de continuar
    pthread_join(busquets, NULL);
    
    // Imprime el último jugador
    printf("Morata\n");
}
