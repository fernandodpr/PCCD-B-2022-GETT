#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {

  int id_segmento; // ID del segmento de memoria compartida

  printf("\nDeben ejecutarse SÓLO 2 instancias del programa CON LA MISMA CLAVE "
         "para evitar errores, ya que a partir de la primera ejecución se abre "
         "Q.\n");

  // SI ES LA PRIMERA INSTANCIA DE P7, SERA LA INSTANCIA 0 (PROCESO P), SI ES LA
  // SEGUNDA, SERÁ LA 1 (PROCESO Q)
  int instancia =
      0; // identificador de la instancia actual (0 para P, 1 para Q)

  int *quiere; // puntero a la memoria compartida que indica si el proceso
               // quiere entrar en la sección crítica

  id_segmento = shmget(
      371, sizeof(int) * 2,
      IPC_EXCL | IPC_CREAT |
          0777); // crea un segmento de memoria compartida para la clave 371

  if (id_segmento == -1) {

    // Si da error porque el segmento ya existe, accedemos a él (segunda
    // instancia de P o Q)
    id_segmento = shmget(371, sizeof(int), 0);
    instancia =
        1; // Si se accede a un segmento existente, la instancia es la 1 (Q)
    printf("\nPROCESO Q\n\n");

    if (id_segmento == -1) {
      // Error al crear/obtener el ID del segmento
      printf("Error al crear/obtener el ID del segmento.");
      return 0;
    }
  } else {
    printf("\nPROCESO P\n\n");
  }

  quiere = (int *)shmat(
      id_segmento, NULL,
      0); // vincula el segmento de memoria compartida con el proceso actual

  // quiere[0] indica si el proceso P quiere entrar en la sección crítica
  // quiere[1] indica si el proceso Q quiere entrar en la sección crítica
  quiere[0] = 0;
  quiere[1] = 0;

  int sigue_P = 0; // contador para controlar que el proceso P no entre varias
                   // veces en la sección crítica
  int sigue_Q = 0; // contador para controlar que el proceso Q no entre varias
                   // veces en la sección crítica

  while (1) {
    printf("Caminando por mi habitación.\n");
    getchar();
    printf("Dentro del pasillo.\n");
    getchar();

    if (instancia == 0) {
      // El proceso P quiere entrar en la sección crítica
      quiere[0] = 1;
      printf("He accionado el pulsador.\n");

      while (!sigue_P) {
        getchar();
        printf("Intentando acceder a la Sección Crítica...");
        if (quiere[1] == 0) {
          // Si la otra instancia no quiere entrar en la sección crítica, el
          // proceso P entra en ella
          printf("Dentro de mi Sección Crítica.\n");
          sigue_P++;
          getchar();
          printf("He salido de mi Sección Crítica.\n");
          getchar();
          quiere[0] = 0;
          printf("He accionado el pulsador.\n");
        } else {
          // La otra instancia está en la sección crítica
          getchar();
          printf("Esperando a que Q salga de la Sección Crítica...\n");
        }
      }
      sigue_P = 0; // Reseteamos el contador para futuras iteraciones

    } else {
      // El proceso Q quiere entrar en la sección crítica
      quiere[1] = 1;
      printf("He accionado el pulsador.\n");

      while (!sigue_Q) {
        getchar();
        printf("Intentando acceder a la Sección Crítica...");
        if (quiere[0] == 0) {
          // Si la otra instancia no quiere entrar en la sección crítica, el
          // proceso Q entra en ella
          printf("Dentro de mi Sección Crítica.\n");
          sigue_Q++;
          getchar();
          printf("He salido de mi Sección Crítica.\n");
          getchar();
          quiere[1] = 0;
          printf("He accionado el pulsador.\n");
        } else {
          // La otra instancia está en la sección crítica
          getchar();
          printf("Esperando a que P salga de la Sección Crítica...\n");
        }
      }

      sigue_Q = 0; // Reseteamos el contador para futuras iteraciones
    }
  }

  return 0;
}