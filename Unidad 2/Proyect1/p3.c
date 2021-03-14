#include <unistd.h>
 #include <stdio.h>
 #include <stdlib.h>

 int main(int argc, char *argv[]) {
     pid_t pid_hijo1;
     pid_t pid_hijo2;




     printf("Este proceso va a crear otros 2
      procesos que llamaran a 2 programas\n");
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
    wait(NULL);
    wait(NULL);

    return EXIT_SUCCESS;


 }
