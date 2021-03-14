#include <unistd.h>
 #include <stdio.h>
 #include <stdlib.h>

 int main(int argc, char *argv[]) {
     pid_t pid_hijo1;
     pid_t pid_hijo2;
     FILE *IN_FILE1;
     FILE *IN_FILE2;



     printf(" Este proceso va a crear otros 2 procesos que llamaran a 2 programas\n ");
     printf("El pid del programa principal es: %d\n",(int)getpid());

    for (int i = 0; i < 2; i++)
    {
        if (i==0) //AQUI LLAMARA AL PRIMERO
        {
            pid_hijo1 = fork();

            if (pid_hijo1 == 0)
            {
                execv("./EXECp1",argv);
            }
            
        }

        else if (i==1)
        {
            pid_hijo2=fork();

            if (pid_hijo2==0)
            {
                execv("./EXECp2",argv);
            }       
        }
    }
    wait(NULL);
    wait(NULL);

    IN_FILE1=fopen(argv[2],"r");
    
    if (IN_FILE1==NULL)
    {
        printf("Se ha producido un error al abrir el archivo");
        exit(8);
    }
    int numerolineas=0;
    char ch = 'X';
    char placehold[20];
    int  placeholdint=0;
    while (ch != EOF)
    {
        fscanf(IN_FILE1,"%s %d",placehold,&placeholdint);
        numerolineas++;
        ch = fgetc(IN_FILE1);
    }
    rewind(IN_FILE1);
    numerolineas=numerolineas-1; //XDXDXDCDXXDDXDXDXDXDXDX
    
    printf("Contenido de OUT1 \n");
    for (size_t i = 0; i < numerolineas; i++)
    {
        fscanf(IN_FILE1,"%s %d",placehold,&placeholdint);
        printf("%s %d \n", placehold, placeholdint);
        ch = fgetc(IN_FILE1);
    }
    

    IN_FILE2=fopen(argv[3],"r");
    
    if (IN_FILE2==NULL)
    {
        printf("Se ha producido un error al abrir el archivo");
        exit(8);
    }
    ch = 'X';
    placeholdint=0;
    printf("Contenido de OUT2 \n");
    for (size_t i = 0; i < numerolineas; i++)
    {
        fscanf(IN_FILE2,"%s %d",placehold,&placeholdint);
        printf("%s %d \n", placehold, placeholdint);
        ch = fgetc(IN_FILE2);
    }
    
    return EXIT_SUCCESS;

    
 }
    

     