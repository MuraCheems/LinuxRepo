#include <stdio.h>
 #include <stdlib.h>





 int main(int argc, char *argv[]) {
    int arr[argc-1];
    int aux = 0;
    for (size_t i = 1; i < argc; i++)
    {
        aux=atoi(argv[i]);
        arr[i-1] = aux;
        printf("Numero: %d \n", arr[i-1]);

    }

    //promedio
    int promedio=0;
    for (size_t i = 0; i < argc-1; i++)
    {
        promedio=promedio+arr[i];
    }
    promedio=(promedio)/(argc-1);
    printf("El promedio es: %d \n" , promedio);


    //Mayor
    aux=arr[0];
    for (size_t i = 0; i < argc-1; i++)
    {
        if (arr[i]>aux)
        {
            aux=arr[i];
        }

    }
    printf("El numero mayor es : %d \n", aux);

     aux=arr[0];
    for (size_t i = 0; i < argc-1; i++)
    {
        if (arr[i]<aux)
        {
            aux=arr[i];
        }

    }
    printf("El numero menor es : %d", aux);


 }


    //PROMEDIO