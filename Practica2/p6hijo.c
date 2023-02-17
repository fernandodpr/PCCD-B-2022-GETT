#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    for(int i = 0; i < argc; i++) {
        //Imprime los strings entregados
        printf("%s", argv[i]);
    }
    return 0;
}