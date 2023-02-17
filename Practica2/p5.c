#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


//Cantidad de procesos 6
int main() {
int pid; 

pid = fork();
if (pid == 0) {
// Nodo De Gea
pid = fork();
if (pid == 0) {
// Nodo Ramos
printf("  Ramos");
} else {
// Nodo Carvajal
wait(NULL);
printf("  Carvajal");
}
} else {
// Nodo Pique
wait(NULL);
printf("  Piqué");
pid = fork();
if (pid == 0) {
  // Nodo Jordi Alba
  printf("  Jordi-Alba");
} else {
  // Nodo Busquets
  wait(NULL);
  printf("  Busquets");

  pid = fork();
  if (pid == 0) {
    // Nodo Isco
    printf("  Isco");
  } else {
    // Nodo Thiago
    wait(NULL);
    printf("  Thiago");

    pid = fork();
    if (pid == 0) {
      // Nodo Aspas
      printf("  Aspas");
    } else {
      // Nodo Silva
      wait(NULL);
      printf("  Silva");

      pid = fork();
      if (pid == 0) {
        // Nodo Morata
        printf("  Morata\n");
      } else {
        // Nodo padre
        wait(NULL);
      }
    }
  }
}
}
return 0;
}