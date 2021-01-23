#include <stdio.h>
#include <unistd.h>

//Comentario xd

char nombre[50];

/*
Comentario de varias lineas
*/


int main() {
    int pid = getpid();
    printf("Ingresu su nombre  : ");
    scanf("%s", nombre);
    printf("Hola %s, su ID de proceso es %d ", nombre, pid);
    return 0;
}


