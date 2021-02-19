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
 


    const char OUTPUT_FILE[40];
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
    int bool=1;
    int cedulaparametro=0;
    int semestreparametro=0;
    char nombreaparametro[50];
    int limite = 0;

    void mkdb();
    void loaddb();
    void savedb();
    void readall();
    void readsize();
    void readreg();
    void mkreg();
    
   

    
    

int main(int argc, char const *argv[])
{
    
    

    do
    {
        scanf("%s", comando);

    if ((strncmp("mkdb", comando, 4) == 0))
    {
        scanf("%s %d", param1, &param2);
        while ( (c = getchar()) != '\n' && c != EOF ) { }
        mkdb();
       
    }
    else if ((strncmp("loaddb", comando, 6) == 0))
    {
        scanf("%s" , param1);
        while ( (c = getchar()) != '\n' && c != EOF ) { }
        loaddb();
    }
    else if ((strncmp("savedb", comando, 6) == 0))
    {
        
        scanf("%s", OUTPUT_FILE);
        while ( (c = getchar()) != '\n' && c != EOF ) { }     
        savedb();       
        
        
    }
    else if ((strncmp("readall", comando, 7) == 0)) 
    {
       while ( (c = getchar()) != '\n' && c != EOF ) { }
        readall();
    }
    else if ((strncmp("readsize", comando, 8) == 0))
    {
        readsize();
    }
     else if ((strncmp("mkreg", comando, 5) == 0))
    {
        scanf("%d %s %d", &cedulaparametro,nombreaparametro,&semestreparametro);
        mkreg();
    }
    else if ((strncmp("readreg", comando, 7) == 0))
    {
        scanf("%d", &param2);
        while ( (c = getchar()) != '\n' && c != EOF ) { }
        readreg();
      
    }
    else if ((strncmp("exit", comando, 4) == 0))
    {
        while ( (c = getchar()) != '\n' && c != EOF ) { }
        bool=0;
    }
    else
    {
        while ( (c = getchar()) != '\n' && c != EOF ) { }
    }
    
    
    } while (bool == 1);
    
    
}


void mkdb(){
 ptrbases = malloc(sizeof(basedatos));
        strcpy(ptrbases -> nombre,param1);
        ptrbases -> tamanomaximo = param2;
        ptrbases -> ptrestudiante = (estudiante*)malloc(sizeof(estudiante)*param2);  
}

void loaddb(){
 IN_FILE=fopen(param1, "r");
        if (IN_FILE == NULL)
        {
            printf("Imposible abrir la base de datos o no existe");
            exit(8);
        }
        
        ptrbases = malloc(sizeof(basedatos));
        fscanf(IN_FILE,"%s %d %d", param1,&limite,&actualsize);
        strcpy(ptrbases -> nombre,param1);
        ptrbases -> tamanomaximo = limite;
        ptrbases -> ptrestudiante = (estudiante*)malloc(sizeof(estudiante)*limite);
        

        int semestre;
        int cedula;
        char nombre[30];
        

        for (size_t i = 0; i < actualsize; i++)
        {
            fscanf(IN_FILE, "%d %s %d", &cedula, nombre, &semestre);
            strcpy(ptrbases -> ptrestudiante[i].nombreestudiante,nombre);
            ptrbases -> ptrestudiante[i].cedulaestudiante = cedula;
            ptrbases -> ptrestudiante[i].semestreestudiante = semestre;
        }
}

void savedb(){
        OUT_FILE=fopen(OUTPUT_FILE, "w");
        if (OUT_FILE == NULL)
        {
        printf("NO fue posible crear el archivo?");
        exit(8);
        }
        fprintf(OUT_FILE,"%s %d %d \n",OUTPUT_FILE,ptrbases -> tamanomaximo,actualsize);
        for (size_t i = 0; i < actualsize; i++)
        {
            fprintf(OUT_FILE,"%d %s %d \n ",ptrbases -> ptrestudiante[i].cedulaestudiante,ptrbases -> ptrestudiante[i].nombreestudiante, ptrbases -> ptrestudiante[i].semestreestudiante);  
}
}

void readall(){
       for (size_t i = 0; i < actualsize; i++)
        {
            printf("%d %s %d \n",ptrbases -> ptrestudiante[i].cedulaestudiante,ptrbases -> ptrestudiante[i].nombreestudiante, ptrbases -> ptrestudiante[i].semestreestudiante);
        }
}
void readsize(){
    printf("El numero de registros en la base de datos es : %d \n", actualsize);
}

void readreg(){
      for (size_t i = 0; i < actualsize; i++)
        {
            if (param2 == ptrbases -> ptrestudiante[i].cedulaestudiante )
            {
                printf("%d %s %d \n",ptrbases -> ptrestudiante[i].cedulaestudiante,ptrbases -> ptrestudiante[i].nombreestudiante, ptrbases -> ptrestudiante[i].semestreestudiante);
            }
            
        }
}

void mkreg(){
      while ( (c = getchar()) != '\n' && c != EOF ) { }

            strcpy(ptrbases -> ptrestudiante[actualsize].nombreestudiante,nombreaparametro);
            ptrbases -> ptrestudiante[actualsize].cedulaestudiante = cedulaparametro;
            ptrbases -> ptrestudiante[actualsize].semestreestudiante = semestreparametro;

        actualsize++;
}


