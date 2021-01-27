#include <stdio.h>
#include <stdlib.h>



char(* memoria) [30];
char memoriastring [30];
int *memorianotas;
int; memoriacreditos;


int main(void){
    int Numeromaterias;
    double Promedio;
    int creditostotal;


    printf("Ingrese el numero de materias \n");  //Preguntandole el numero de materias podemos saber cuanta memoria en el heap tenemos que guardar
    scanf("%d", &Numeromaterias);
    getc(stdin);

    memoria = (char () [30])  malloc (sizeof(char[30]) * Numeromaterias );
    memorianotas = (double * ) malloc (sizeof(int) * Numeromaterias );
    memoriacreditos = (int * ) malloc(sizeof(int) * Numeromaterias); 
    //Reservamos la memoria enm el heap de cada materia 


    //Vamos a preguntarle la info de las materias al usuario

    for (int i = 0; i < Numeromaterias ; i++)
    {
        printf("Ingresar nombre de la materia\n");
        scanf("%s" , (char*) (memoria + i)); //SUmamos i para que no reescriba en la memoria

        printf("Ingresar nota de la mamteria\n");
        scanf("%d", (int * ) (memorianotas+i));
        getc(stdin);

        printf ("Ingresar creditos de la materia\n");
        scanf("%d" ,  (int *) (memoriacreditos + i));
        getc(stdin);
    }


    //vamos a imprimiar las notas 
    //Demosle un formato

    printf("///Materia///Nota///Creditos\n");

    for(int i = 0; i < Numeromaterias; i++)
    {
        printf("///%s///%d///%d\n" , (char *) (memoria+i), *(memorianotas+i), *(memoriacreditos+i) ); //Imprime las materias con sus notas

    }


    free(memoria);
    free(memoriacreditos);
    free(memorianotas);






}