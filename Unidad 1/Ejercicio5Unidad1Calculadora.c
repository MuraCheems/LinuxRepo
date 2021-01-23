#include <stdio.h>
#include <unistd.h>

//Comentario xd

char nombre[50];

/*
Comentario de varias lineas
*/


int main(void) {

    int x;
    int y;
    int z;
    int opcion;
    do
    {
        
        printf("Ingrese el 1er operando \n");
        scanf("%d",&x); //Primer operando
        printf("Ingrese el 2ndo operando \n");
        scanf("%d",&y); //2ndo operando
        printf("Que quiere hacer con los dos operandos? \n 1. Sumar \n 2.dividir \n 3.Multiplicar  \n Presione 4 Para salir \n ");
        scanf("%d",&opcion); //seleccion de opcion

      
       
        switch (opcion)
        {
        case 1:
            z=x+y;
            printf("El valor de Z es: %d  \n ", z);
            break;
        case 2 :
            z=x/y;            
            printf("El valor de Z es: %d  \n ", z);
            break;
        case 3 :
            z=x*y;
            printf("El valor de Z es: %d  \n ", z);    
            break;      
        
        default:
           break;
    
       }

    } while (opcion != 4 );
     printf("Fin del programa \n");    
    
    return(0);
}
    
   








