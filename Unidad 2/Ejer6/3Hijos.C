#include <unistd.h>
 #include <stdio.h>
 #include <stdlib.h>

 int main(int argc, char argv[]) {
     pid_t pid_hijo;
     int factorial=1;


     printf("Este proceso va a crear otro 3 procesos\n");
     printf("El pid del programa principal es: %d\n",(int)getpid());

    for (int i = 0; i < 3; i++)
    {
        pid_hijo = fork();


        if(pid_hijo==0){
        printf("Se creo  y se esta ejecutando el proceso hijo numero %d con numero de proceso %d \n", i, (int)getpid());

        break;
        }
        else{

            printf("Se termino el proceso %d \n", (int)wait(NULL)); //DE ESTA MANERA REVISO QUE CADA UNO DE LOS PROCESOS SE ESTE TERMINANDO CORRECTAMENTE, TAMBIEN PUEDO HACER UN WAIT DESPUES DEL FOR PERO SERIAN WAIT POR CADA 1 
        }
    }


        if (pid_hijo==0)
        {
            for (int i = 1; i < 11; i++)
            {
                factorial=factoriali;

                printf("Fact(%d) = %d \n", i,factorial);
            }

        }







 }