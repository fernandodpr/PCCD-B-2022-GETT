#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {

  int segment_id;
  int process_instance = 0; // 0 para la primera instancia del proceso P8, 1
                            // para la segunda instancia (proceso Q)
  int *access_requests;

  printf("\nSe deben ejecutar SOLO 2 instancias del programa CON LA MISMA "
         "CLAVE para evitar errores, ya que a partir de la primera ejecución "
         "se abre Q.\n");

  segment_id = shmget(381, sizeof(int) * 2, IPC_EXCL | IPC_CREAT | 0777);

  if (segment_id == -1) {

    // Si da error porque el segmento ya existe, accedemos a él (segunda
    // instancia de P5)
    segment_id = shmget(381, sizeof(int), 0);
    process_instance = 1;
    printf("\nPROCESO Q\n\n");

    if (segment_id == -1) {
      printf("Error al crear/obtener el ID del segmento.");
      return 0;
    }
  } else {
    printf("\nPROCESO P\n\n");
  }

  access_requests = (int *)shmat(segment_id, NULL, 0);

  // access_requests[0] == access_request_P
  // access_requests[1] == access_request_Q
  access_requests[0] = 0;
  access_requests[1] = 0;

  while (1) {

    printf("Caminando por mi habitación.\n");

    getchar();

    printf("Dentro del pasillo.\n");

    getchar();

    if (process_instance == 0) {

      access_requests[0] = 1;
      printf("He accionado el pulsador.\n");

      getchar();
      printf("Intentando acceder a la Sección Crítica...");

      if (access_requests[1] == 0) {

        printf("Dentro de mi Sección Crítica.\n");

        getchar();
        printf("He salido de mi Sección Crítica.\n");

        getchar();
        access_requests[0] = 0;
        printf("He accionado el pulsador.\n");

      } else {

        printf("Puerta cerrada. Saliendo del pasillo...\n");

        getchar();
        access_requests[0] = 0;
        printf("He accionado el pulsador.\n");
        printf("He salido del pasillo.\n");
      }

    } else {

      access_requests[1] = 1;
      printf("He accionado el pulsador.\n");

      getchar();
      printf("Intentando acceder a la Sección Crítica...");

      if (access_requests[0] == 0) {

        printf("Dentro de mi Sección Crítica.\n");

        getchar();
        printf("He salido de mi Sección Crítica.\n");

        getchar();
        access_requests[1] = 0;
        printf("He accionado el pulsador.\n");

      } else {

        printf("Puerta cerrada. Saliendo del pasillo...\n");

        getchar();
        access_requests[1] = 0;
        printf("He accionado el pulsador.\n");
        printf("He salido del pasillo.\n");
      }
    }
  }
}
