#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>



typedef struct estruclinea{
    char clave[20];
    int value;
}estruclinea;

estruclinea *vectorlineas;

int main(int argc, char const *argv[])
{
    estruclinea auxlinea;
    FILE *IN_FILE;
    FILE OUT_FILE;
    int numerolineas = 0;


    IN_FILE=fopen(argv[1],"r");

    if (IN_FILE==NULL)
    {
        printf("Se ha producido un error al abrir el archivo");
        exit(8);
    }
    char ch = fgetc(IN_FILE);
    char placehold[20];
    int  placeholdint=0;
    while (ch != EOF)
    {
        fscanf(IN_FILE,"%s %d",placehold,&placeholdint);
        numerolineas++;
        ch = fgetc(IN_FILE);
    }

    vectorlineas = (estruclinea)malloc(sizeof(estruclinea)*numerolineas);

    rewind(IN_FILE);

    char auxnombre[20];
    int auxvalue = 0;

    for (size_t i = 0; i < numerolineas; i++)
    {
        fscanf(IN_FILE,"%s %d",auxnombre,&auxvalue);
        strcpy(vectorlineas[i].clave, auxnombre);
        vectorlineas[i].value = auxvalue;
    }

    for (int a = 0; a < numerolineas/2; a++)
    {
       auxlinea=vectorlineas[a];
       vectorlineas[a]=vectorlineas[numerolineas-1-a];
       vectorlineas[numerolineas-1-a]=auxlinea;
    }

    OUT_FILE = fopen("Out1","w");

    for (int i = 1; i < numerolineas; i++)
    {
        fprintf(OUT_FILE,"%s  %d \n", vectorlineas[i].clave, vectorlineas[i].value);
    }
    fclose(OUT_FILE);
    free(vectorlineas);
    return EXIT_SUCCESS;
}