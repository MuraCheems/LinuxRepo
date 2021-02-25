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
     int actualsize;
     int tamanomaximo;
     estudiante *ptrestudiante;  
 }basedatos;
    char c;
    int indicebases=0; //Me senala en cual base me estoy parando
    basedatos *ptrbases; //El puntero lo hice global ya que enserio me estaba tirando demasiados errores cuando lo ponia en el main y cuando se lo pasaba a las funciones
    //FUNCIONES prototipadas
    void  mdb(char nombre[20], int registromax, int contador); // Creabase
    void  ldb(const char nombrearchivo[30], int contadorbases); //Carga base en un espacio del malloc de las bases
    void  lsdbs(int contadorbases);//Lista todas las bases del malloc
    void  sdb(char nombre[20],int contadorbases);//Cambia el indice del ptrbases
    void  svdb(); // Guarda la base de datos usando el nombre de la estructura
    void  gdb();//Lista caracteristicas de la base de datos la cual el indice y el ptr apuntan
    void  radb();//Retorna cuantos registros ahi en la base de datos la cual el indice y el ptr apuntan
    void  rsdb();//REtorna registros y registros restantes en la base de datos seleccionada 
    void  rr(int cedula);//busca una cedula especifica en la bd seleccionada
    void  mreg(char nombreparametro[20], int cedulaparametro, int semestreparametro);//registra un nuevo estudiante en la bd seleccionada
   
    int main(int argc, char const *argv[])
 {
    const char OUTPUT_FILE[40];
    FILE *OUT_FILE;
    ptrbases = (basedatos*)malloc(sizeof(basedatos)*30); // DEfinimos el maximo de base de datos en este caso 30
    char comando [10];
    char param1 [20];
    int param2;
    int param3;
    int contadorbases=0;  
    
    int bool=1;
    const char nombrearchivo[30];      
         do
         {
        scanf("%s", comando);

    if ((strncmp("mdb", comando, 3) == 0))
    {
        scanf("%s %d", param1, &param2);
        while ( (c = getchar()) != '\n' && c != EOF ) { }
        mdb(param1, param2,contadorbases);
        contadorbases++; //Pasa el puntero a la siguiente direccion del malloc
       
    }
    else if ((strncmp("ldb", comando, 3) == 0))
    {
        scanf("%s",nombrearchivo);
        while ( (c = getchar()) != '\n' && c != EOF ) { }
        ldb(nombrearchivo,contadorbases);
        contadorbases++;
    }
     else if ((strncmp("lsdbs", comando, 5) == 0))
    {
        while ( (c = getchar()) != '\n' && c != EOF ) { }
        lsdbs(contadorbases);
       
    }
     else if ((strncmp("sdb", comando, 3) == 0))
    {
        scanf("%s", param1);
        while ( (c = getchar()) != '\n' && c != EOF ) { }
        sdb(param1,contadorbases);
        printf("Se ha seleccionado la base de datos: %s \n", ptrbases[indicebases].nombre);
    }
     else if ((strncmp("svdb", comando, 4) == 0))
    {
        while ( (c = getchar()) != '\n' && c != EOF ) { }
        svdb();
    }
     else if ((strncmp("gdb", comando, 3) == 0))
    {
        while ( (c = getchar()) != '\n' && c != EOF ) { }
        gdb();
    }
      else if ((strncmp("mreg", comando, 4) == 0))
    {
        scanf("%d %s %d", &param2, param1, &param3);
        mreg(param1,param2,param3);
        while ( (c = getchar()) != '\n' && c != EOF ) { }
    }
      else if ((strncmp("radb", comando, 4) == 0))
    {
        while ( (c = getchar()) != '\n' && c != EOF ) { }
        radb();
    }
      else if ((strncmp("rsdb", comando, 4) == 0))
    {
        while ( (c = getchar()) != '\n' && c != EOF ) { }
        rsdb();
    }
       else if ((strncmp("rr", comando, 2) == 0))
    {
        scanf("%d", &param2);
        while ( (c = getchar()) != '\n' && c != EOF ) { }
        rr(param2);
    }
    
    

    else if ((strncmp("exit", comando, 4) == 0))
    {
        while ( (c = getchar()) != '\n' && c != EOF ) { }
        
        printf("Seguro desea salir de la base de datos? y/n ? Oprimiendo Y guardara la base de datos ACTUAL \n");
        scanf("%s", param1);


       if ( ((strncmp("y",param1, 1) == 0)))
       {
        svdb();
        bool=0;
       }
       else{bool=0;}
       
       
    }
    else
    {
        while ( (c = getchar()) != '\n' && c != EOF ) { }
    }
    
    
    } while (bool == 1);

 }

 void mdb(char nombre[20], int registromax, int contadorbases)
 {
    strcpy(ptrbases[contadorbases].nombre,nombre);
    ptrbases[contadorbases].tamanomaximo = registromax;
    ptrbases[contadorbases].actualsize = 0;
    ptrbases[contadorbases].ptrestudiante = (estudiante*)malloc(sizeof(estudiante)*registromax);
    printf("Se ha creado la base de datos numero %d \n",contadorbases);
 }

 void ldb(const char archivito[30], int contadorbases){
        FILE *IN_FILE;
        IN_FILE=fopen(archivito, "r");
        if (IN_FILE == NULL)
        {
            printf("Imposible abrir la base de datos o no existe");
            exit(8);
        }
        
        char nombrebd[20];
        int limitemax;
        int actualsize;

        fscanf(IN_FILE,"%s %d %d", nombrebd,&limitemax,&actualsize);
        strcpy(ptrbases[contadorbases].nombre,nombrebd);
        ptrbases[contadorbases].tamanomaximo = limitemax;
        ptrbases[contadorbases].actualsize = actualsize;
        ptrbases[contadorbases].ptrestudiante = (estudiante*)malloc(sizeof(estudiante)*limitemax);
        

        int semestre;
        int cedula;
        char nombre[30];
        

        for (size_t i = 0; i < actualsize; i++)
        {
            fscanf(IN_FILE, "%d %s %d", &cedula, nombre, &semestre);
            strcpy(ptrbases[contadorbases].ptrestudiante[i].nombreestudiante,nombre);
            ptrbases[contadorbases].ptrestudiante[i].cedulaestudiante = cedula;
            ptrbases[contadorbases].ptrestudiante[i].semestreestudiante = semestre;
        }

       
}
 

void lsdbs(int contadorbases){

    for (int i = 0; i < contadorbases; i++)
    {
       printf("Base Numero %d \n Nombre de la base de datos %s \n Numero Maximo de Registros %d \n Numero actual de registros %d \n",i,ptrbases[i].nombre,ptrbases[i].tamanomaximo,ptrbases[i].actualsize);
    }
    

}

void sdb(char nombrebase[20], int contadorbases){

    for (int i = 0; i < contadorbases; i++)
    {
      if ((strncmp(ptrbases[i].nombre,nombrebase, 40) == 0))
      {
          indicebases=i;
          i=contadorbases;
      }
    }
}

void svdb(){
        FILE *OUT_FILE;
        OUT_FILE=fopen(ptrbases[indicebases].nombre, "w");
        if (OUT_FILE == NULL)
        {
        printf("NO fue posible crear el archivo?");
        exit(8);
        }
        fprintf(OUT_FILE,"%s %d %d \n",ptrbases[indicebases].nombre, ptrbases[indicebases].tamanomaximo, ptrbases[indicebases].actualsize);
        for (size_t i = 0; i <ptrbases[indicebases].actualsize; i++)
        {
        fprintf(OUT_FILE,"%d %s %d \n ",ptrbases[indicebases].ptrestudiante[i].cedulaestudiante,ptrbases[indicebases].ptrestudiante[i].nombreestudiante,ptrbases[indicebases].ptrestudiante[i].semestreestudiante);  

        }
        printf("Se ha guardado la base de datos exitosamente \n");
}

void gdb(){
    printf("La base de datos activa es: %s \nTiene capacidad para %d registro(s) \ntodavia le quedan %d registros disponible(s) \n ",ptrbases[indicebases].nombre,ptrbases[indicebases].tamanomaximo,ptrbases[indicebases].tamanomaximo-ptrbases[indicebases].actualsize);
}
    

void radb(){
       for (size_t i = 0; i < ptrbases[indicebases].actualsize; i++)
        {
            printf("%d %s %d \n",ptrbases[indicebases].ptrestudiante[i].cedulaestudiante,ptrbases[indicebases].ptrestudiante[i].nombreestudiante, ptrbases[indicebases].ptrestudiante[i].semestreestudiante);
        }
}
void mreg(char nombreparametro[20], int cedulaparametro, int semestreparametro){
            strcpy(ptrbases[indicebases].ptrestudiante[ptrbases[indicebases].actualsize].nombreestudiante,nombreparametro);
            ptrbases[indicebases].ptrestudiante[ptrbases[indicebases].actualsize].cedulaestudiante = cedulaparametro;
            ptrbases[indicebases].ptrestudiante[ptrbases[indicebases].actualsize].semestreestudiante = semestreparametro;
            ptrbases[indicebases].actualsize++; 
}    

void rsdb(){
 printf("El numero de registros de la base de datos: %s  es de %d registros \n",ptrbases[indicebases].nombre, ptrbases[indicebases].actualsize);
}

void rr(int cedula){

         for (size_t i = 0; i < ptrbases[indicebases].actualsize; i++)
        {
            if (cedula == ptrbases[indicebases].ptrestudiante[i].cedulaestudiante )
            {
                printf("%d %s %d \n",ptrbases[indicebases].ptrestudiante[i].cedulaestudiante,ptrbases[indicebases].ptrestudiante[i].nombreestudiante, ptrbases[indicebases].ptrestudiante[i].semestreestudiante);
            }
            
        }
}


    
 
