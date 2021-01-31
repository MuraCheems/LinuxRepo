#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char (*memoria)[40];
double *memoria2;
int *memoria3;

const char INPUT_FILE[40];
const char OUTPUT_FILE[40];





int main(){
    
    char string1[20],string2[20],string3[20],string4[20];
    int Numeromaterias;
    printf("ingresar el nombre del archivo de entrada \n");
    scanf("%s", INPUT_FILE);
    printf("Ingresar nombre de archivo de salida\n");
    scanf("%s", OUTPUT_FILE);
     // DESPUES DE HABER PREGUNTADO SOBRE LOS ARCHIVOS VAMOS A ABRIRLOS/CREARLOS
    FILE *IN_FILE;
    FILE *OUT_FILE;
    IN_FILE = fopen(INPUT_FILE, "r");
    OUT_FILE = fopen(OUTPUT_FILE, "r+");


    
    

    if (IN_FILE == NULL || OUT_FILE == NULL)
    {
        printf("Imposible abrir uno de los archivos, probablemente el input");
        exit(8);
    }
    fprintf(OUT_FILE, "Materia Nota Creditos \n");
    char ch = fgetc(IN_FILE);
    while (ch != EOF)
    {
        fscanf(IN_FILE, "%s %s %s %s %s %s" ,string1,string4,string2,string4,string3,string4);
        Numeromaterias++;
        ch = fgetc(IN_FILE);
    }

    memoria = (char (*) [40])  malloc (sizeof(char[40]) * Numeromaterias );
    memoria2 = (double * ) malloc (sizeof(double) * Numeromaterias );
    memoria3 = (int * ) malloc(sizeof(int) * Numeromaterias); 

    rewind(IN_FILE);
    for (size_t i = 0; i < Numeromaterias; i++)
    {
       fscanf (IN_FILE, "%s %s %s %lf %s %d", string1,(char *)(memoria+i),string2, (double *) (memoria2+i), string3, (int *) (memoria3+i));
       printf ("%s    %f    %d \n", (char *)(memoria+i),*(memoria2+i),*(memoria3+i));
       fprintf(OUT_FILE, "%s    %lf    %d \n", (char *)(memoria+i),*(memoria2+i),*(memoria3+i));
    }
    int matganadas=0;
    int matperdidas = 0;

    for (size_t i = 0; i < Numeromaterias; i++)
    {
        if (*(memoria2+i)>=3.0)
        {
            matganadas++;
        }
        else
        {
            matperdidas++;
        }
        
        
    }
    fprintf(OUT_FILE, "Materias en total: %d \n" ,Numeromaterias-1);
    fprintf(OUT_FILE, "Materias en total ganadas: %d \n",matganadas);
    fprintf(OUT_FILE, "Materias en total perdidas: %d \n",matperdidas-1);
    

    

    free(memoria);
    free(memoria2);
    free(memoria3);
    fclose(IN_FILE);
    fclose(OUT_FILE);

    return(0);
    
}