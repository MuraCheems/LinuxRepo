#include <stdio.h>
#include <string.h>

int oogaabooga(int *ptr, int size);

int rand(void);


int main(void){

    printf("Cual es el tamano del vector \n");
    int tamano = 0;
    scanf("%d", &tamano);
    int a [tamano];
    int *ptr1;
    ptr1 = a;
    for (int i = 0; i < tamano; i++)
    {
        printf("Ingresa el valor de la pos %d, acuerdate que es un arreglo de INTS: \n", i);
        scanf("%d", &(a[i]));
    }

    oogaabooga(ptr1,tamano);

    printf("Desar hacer un cambio en alguna posicion 1 = si 0=no \n");
    int opcion;
    scanf("%d",&opcion);

    if (opcion == 1)
    {
        printf("En que posicion desea hacer el cambio? \n");
        int pos;
        scanf("%d", &pos);
        pos = pos-1;

        printf("Ingresa el valor \n");
        scanf("%d", &(a[pos]));

        oogaabooga(ptr1,tamano);


    }
     else if (opcion == 0){

     }

}

    int oogaabooga(int *ptr, int size){
    int retorno;
    retorno=0;
    for (int i = 0; i < size; i++)
    {
        printf("Numero en la pos %d es %d \n", i, *(ptr+i));
    }
    retorno = (retorno/size);
    return retorno;
}