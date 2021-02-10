#include <stdio.h>
#include <string.h>
#include <stdint.h>



uint8_t arrayCommon(int32_t* arr1, int32_t arr1Size,int32_t* arr2, int32_t arr2Size, int32_t* arrRes, int32_t arrResSize);
int rand(void);


int main(void){
    

    /*
    printf("Cual es el tamano del vector 1 \n");
    int tamano = 0;
    scanf("%d", &tamano);
    int a [tamano];
    
    int *ptr1;
    ptr1 = a;
    for (int i = 0; i < tamano; i++)
    {
        printf("Ingresa el valor de la pos %d, VECTOR 1, acuerdate que es un arreglo de INTS: \n", i);
        scanf("%d", &(a[i]));
    }

    int tamano2=0;
    printf("Cual es el tamano del vector 2 \n");
    scanf("%d" , &tamano2);
    int b [tamano2];
    int *ptr2;
    ptr2 = b;

    for (int i = 0; i < tamano2; i++)
    {
        printf("Ingresa el valor de la pos %d, VECTOR 2, acuerdate que es un arreglo de INTS: \n", i);
        scanf("%d", &(a[i]));
    }


    int *ptr3;
    int tamano3=0;
    tamano3 = tamano;
    int c[tamano3];
    ptr3=c;
        
    
    printf("%d \n", arrayCommon(ptr1, tamano, ptr2, tamano2, ptr3, tamano3));
    */


   

    int *ptr1;
    int *ptr2;
    int *ptr3;
    int a[]={5,10,15,20,25,30,35,40,45,50,55,60}; //12
    int b[]={10,20,30,40,50,60}; //6
    int c[10];
    int tamano1=12;
    int tamano2=6;
    int tamano3=10;
    ptr1 = a;
    ptr2 = b;
    ptr3 = c;
    for (size_t i = 0; i < tamano3; i++)
    {
        c[i] = 0; //ESTO LIMPIARA LOS DATOS BASURA
    } 
    
    arrayCommon(ptr1,tamano1,ptr2,tamano2,ptr3,tamano3);

    for (int i = 0; i < tamano3; i++)
    {
        printf(" Los numeros repetidos entre vectores son : %d\n",c[i]); //ignorar los 0 que imprime, queria que el usuario eligira los tamanos de los vectores ppero por alguna razon no funciona a la hora de substituir los datos , revisar comentarios arriba
    }
    return 0;




}

uint8_t arrayCommon(int32_t* arr1, int32_t arr1Size,int32_t* arr2, int32_t arr2Size, int32_t* arrRes, int32_t arrResSize){

    int repetidos =0;
    int memoria = 0;
    int vectorpos =0;
    int bool = 0;
    
    for (size_t i = 0; i < arr1Size; i++)
    {
        for (size_t j = 0; j < arr2Size; j++)
        {
            if (*(arr1+i) == *(arr2+j)){
                
                memoria = *(arr1+i);

                for (size_t k = 0; k < arrResSize; k++)
                {
                    if (memoria == *(arrRes+k))
                    {
                        bool = 0;
                    }
                    else
                    {
                        bool = 1;
                    }                                       
                }

                if (bool == 1)
                {
                (*(arrRes+vectorpos++)) = memoria;
                repetidos++;
                }
                                 
            }                                       
        }
    }
    printf("El numero de repetidos es: %d \n", repetidos);
    return repetidos;
}





   

  
