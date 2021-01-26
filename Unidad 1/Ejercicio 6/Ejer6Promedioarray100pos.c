#include <stdio.h>
#include <unistd.h>

int promedio(int *ptr, int size);
int a [100];
int rand(void);
int main(void){

    int *ptr1;
    ptr1 = a;
    for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++)
    {
        a[i] = rand() % 50;
        printf("Num %d", *(ptr1+i));
    }

    printf("El promedio de los 100 numeros dentro del vector es de %d,", promedio(ptr1,sizeof(a)/sizeof(int)));
}

    int promedio(int *ptr, int size){
    int retorno;
    retorno=0;
    for (int i = 0; i < size; i++)
    {
        retorno = retorno + *(ptr+i);
    }
    retorno = (retorno/size);
    return retorno;
}