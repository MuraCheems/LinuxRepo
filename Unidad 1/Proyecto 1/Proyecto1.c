#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 typedef struct estudiante
 {
     int cedulaestudiante;
     char nombreestudiante[30];
     int semestreestudiante;
 }estudiante;

 typedef struct basedatos
 {
     char nombre[30];
     int tamanomaximo;  
     estudiante *ptrestudiante;  
 }basedatos;
 


int main(int argc, char const *argv[])
{
    FILE *IN_FILE;
    FILE *OUT_FILE;
    basedatos *ptrbases;
    char comando [10];
    char param1 [20];
    int param2;
    char param3 [20];
    int contadorestudiante = 0;
    char c;
    int actualsize = 0;
    

    scanf("%s", comando);

    if ((strncmp("mkdb", comando, 4) == 0))
    {
        scanf("%s %d", param1, &param2);
        while ( (c = getchar()) != '\n' && c != EOF ) { }
        ptrbases = malloc(sizeof(basedatos));
        strcpy(ptrbases -> nombre,param1);
        ptrbases -> tamanomaximo = param2;
        ptrbases -> ptrestudiante = (estudiante*)malloc(sizeof(estudiante)*param2);  
    }
    else if ((strncmp("loaddb", comando, 6) == 0))
    {
        scanf("%s" , param1);
        while ( (c = getchar()) != '\n' && c != EOF ) { }
        IN_FILE=fopen(param1, "r");
        if (IN_FILE == NULL)
        {
        printf("Imposible abrir la base de datos o no existe");
        exit(8);
        }
        
        ptrbases = malloc(sizeof(basedatos));
        fscanf(IN_FILE,"%s %d", param1,&param2);
        strcpy(ptrbases -> nombre,param1);
        ptrbases -> ptrestudiante = (estudiante*)malloc(sizeof(estudiante)*param2);
        actualsize=param2;

        int semestre;
        int cedula;
        char nombre[30];

        for (size_t i = 0; i < param2; i++)
        {
            fscanf(IN_FILE, "%d %s %d", &cedula, nombre, &semestre);
            strcpy(ptrbases -> ptrestudiante[i].nombreestudiante,nombre);
            ptrbases -> ptrestudiante[i].cedulaestudiante = cedula;
            ptrbases -> ptrestudiante[i].semestreestudiante = semestre;
        }

        printf("%s",  ptrbases -> ptrestudiante[1].nombreestudiante);
        

    }
    else if ((strncmp("savedb", comando, 6) == 0))
    {
        const char OUTPUT_FILE[40];
        scanf("%s", OUTPUT_FILE);
        while ( (c = getchar()) != '\n' && c != EOF ) { }
        
        
        OUT_FILE=fopen(OUTPUT_FILE, "w");
        if (OUT_FILE == NULL)
        {
        printf("NO fue posible crear el archivo?");
        exit(8);
        }
        fprintf(OUT_FILE,"%s %d",OUTPUT_FILE, actualsize);
        for (size_t i = 0; i < actualsize; i++)
        {
            fprintf(OUT_FILE,"%d %s %d ",ptrbases -> ptrestudiante[i].cedulaestudiante,ptrbases -> ptrestudiante[i].nombreestudiante, ptrbases -> ptrestudiante[i].semestreestudiante);
        }
        
    }
    else if ((strncmp("readall", comando, 7) == 0))
    {
        scanf("%s", comando); //GENERA ERROR SI SE LEE EL \N
    }
    else if ((strncmp("readsize", comando, 8) == 0))
    {
        scanf("%s", comando);
    }
     else if ((strncmp("mkreg", comando, 5) == 0))
    {
        scanf("%s", comando);
    }
    else if ((strncmp("readreg", comando, 7) == 0))
    {
        scanf("%s", comando);
    }
    else if ((strncmp("exit", comando, 4) == 0))
    {
        while ( (c = getchar()) != '\n' && c != EOF ) { }
        printf("ENtra al EXIT SIUUUU");
    }
    else
    {
        //LImpia flujo de entrada
    }
    
    
    
  


}


