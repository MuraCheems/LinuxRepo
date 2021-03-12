#include <unistd.h>
 #include <stdio.h>
 #include <stdlib.h>

 int main(int argc, char *argv[]) {
     pid_t pid_hijo1;
     pid_t pid_hijo2;
     pid_t pid_hijo3;



     printf("Este proceso va a crear otros 3 procesos que llamaran a 3 programas\n");
     printf("El pid del programa principal es: %d\n",(int)getpid());

    for (int i = 0; i < 3; i++)
    {
        if (i==0) //AQUI LLAMARA AL PRIMERO
        {
            pid_hijo1 = fork();

            if (pid_hijo1 == 0)
            {
                execv("./EXECpromedio",argv);
            }

        }

        else if (i==1)
        {
            pid_hijo2=fork();

            if (pid_hijo2==0)
            {
                execv("./EXECmayor",argv);
            }

        }

        else  if (i==2)
        {
            pid_hijo3=fork();

            if (pid_hijo3==0)
            {
                execv("./EXECmenor",argv);
            }

        }


    }
    wait(NULL);
    wait(NULL);
    wait(NULL);
    return EXIT_SUCCESS;


 }