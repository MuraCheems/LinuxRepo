#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>




typedef struct registro{
    char nombre[20];
    char ocupacion [20];
    int edad;
}registro;

struct parametro{
    registro *punteroregistros;
    int numerolineas;
    char salida[20];
};


void inverso(void* params)
{

    struct parametro* p = (struct parametro*) params;
    registro auxlinea;
    FILE *OUT_FILE;
     for (int a = 0; a < (p[0].numerolineas/2); a++)
    {
       auxlinea=p[0].punteroregistros[a];
       p[0].punteroregistros[a] = p[0].punteroregistros[p[0].numerolineas-1-a];
       p[0].punteroregistros[p[0].numerolineas-1-a]=auxlinea;    
    }
    
    OUT_FILE = fopen(p[0].salida,"w");

    for (int i = 0; i < p[0].numerolineas; i++)
    {
        fprintf(OUT_FILE,"%s %s %d\n", p[0].punteroregistros[i].nombre,p[0].punteroregistros[i].ocupacion,p[0].punteroregistros[i].edad);
    }
    fclose(OUT_FILE);
}

void orden(void* params){
    struct parametro* p = (struct parametro*) params;
    registro auxlinea;
    FILE *OUT_FILE;  
    
   for (int a = 0; a < p[0].numerolineas-1; a++)
    {
        for (int b = a+1; b<p[0].numerolineas; b++)
        {
            if (strcmp(p[0].punteroregistros[a].ocupacion,p[0].punteroregistros[b].ocupacion) > 0)
            {
                
                auxlinea=p[0].punteroregistros[a];
                p[0].punteroregistros[a]=p[0].punteroregistros[b];
                p[0].punteroregistros[b]=auxlinea;
            }
            
            
        }
        
    }  
    OUT_FILE = fopen(p[0].salida,"w");

    for (int i = 0; i < p[0].numerolineas; i++)
    {
        fprintf(OUT_FILE,"%s %s %d\n", p[0].punteroregistros[i].nombre,p[0].punteroregistros[i].ocupacion,p[0].punteroregistros[i].edad);
    }
    fclose(OUT_FILE);
}

int main(int argc, char const *argv[])
{
    int numerolineas=0;
    registro *vectorlineas;
    registro *vectorlineas2;
    FILE *IN_FILE;
    FILE *IN_FILE2;
    FILE *IN_FILE3;

    IN_FILE=fopen(argv[1],"r");
    
    if (IN_FILE==NULL)
    {
        printf("Se ha producido un error al abrir el archivo");
        exit(8);
    }
    char ch = fgetc(IN_FILE);
    char placehold[20];
    char placeholdjob[20];
    int  placeholdint=0;
    while (ch != EOF)
    {
        fscanf(IN_FILE,"%s %s %d",placehold,placeholdjob,&placeholdint);
        numerolineas++;
        ch = fgetc(IN_FILE);
    }
    numerolineas--;

    vectorlineas = (registro*)malloc(sizeof(registro)*numerolineas);
    vectorlineas2 = (registro*)malloc(sizeof(registro)*numerolineas);

     rewind(IN_FILE);

    char auxnombre[20];
    char auxempleo[20];
    int auxvalue = 0;

    for (size_t i = 0; i < numerolineas; i++)
    {
        fscanf(IN_FILE,"%s %s %d ",auxnombre,auxempleo,&auxvalue);
        strcpy(vectorlineas[i].nombre, auxnombre);
        strcpy(vectorlineas[i].ocupacion, auxempleo);
        vectorlineas[i].edad = auxvalue;

        strcpy(vectorlineas2[i].nombre, auxnombre);
        strcpy(vectorlineas2[i].ocupacion, auxempleo);
        vectorlineas2[i].edad = auxvalue;
    }

  
    struct parametro hilo1param;
    struct parametro hilo2param;
   


    hilo1param.punteroregistros = vectorlineas;
    hilo1param.numerolineas = numerolineas;
    strcpy(hilo1param.salida, argv[2]);



    hilo2param.punteroregistros = vectorlineas2;
    hilo2param.numerolineas = numerolineas;
    strcpy(hilo2param.salida, argv[3]);

     printf("REGISTROS SIN ORDENAR \n");
    for (int i = 0; i < numerolineas; i++)
    {
        printf("%s %s %d \n", vectorlineas[i].nombre, vectorlineas[i].ocupacion,vectorlineas[i].edad);
    }



   
    
        pthread_t hilos_id1;
        pthread_t hilos_id2;

        pthread_create(&hilos_id1,NULL,(void *)inverso,&hilo1param);     
        pthread_create(&hilos_id2,NULL,(void *)orden,&hilo2param);                   
        pthread_join(hilos_id1,NULL);
        pthread_join(hilos_id2,NULL);
        
        IN_FILE2=fopen(argv[2],"r");
    
    if (IN_FILE2==NULL)
    {
        printf("Se ha producido un error al abrir el archivo");
        exit(8);
    }
    ch = fgetc(IN_FILE2);
    placeholdint=0;
    numerolineas=0;
    while (ch != EOF)
    {
        fscanf(IN_FILE2,"%s %s %d",placehold,placeholdjob,&placeholdint);
        numerolineas++;
        ch = fgetc(IN_FILE2);
    }
    rewind(IN_FILE2);
    numerolineas--;


    printf(" /////////// REGISTROS DE OUT 1 //////// \n");
    for (int i = 0; i < numerolineas; i++)
    {
       fscanf(IN_FILE2,"%s %s %d \n",placehold,placeholdjob,&placeholdint);
       printf("%s %s %d\n",placehold,placeholdjob,placeholdint);
    }

    IN_FILE3=fopen(argv[3],"r");
     if (IN_FILE3==NULL)
    {
        printf("Se ha producido un error al abrir el archivo");
        exit(8);
    }
    printf(" /////////// REGISTROS DE OUT 2 //////// \n");
    for (int i = 0; i < numerolineas; i++)
    {
       fscanf(IN_FILE3,"%s %s %d \n",placehold,placeholdjob,&placeholdint);
       printf("%s %s %d\n",placehold,placeholdjob,placeholdint);
    }
    


        
}
