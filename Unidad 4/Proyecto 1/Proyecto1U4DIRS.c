#include <stdio.h>
 #include <stdint.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <errno.h>
 #include <string.h>
 #include <dirent.h>
 #include <sys/types.h>


 void unix_error(char msg) / Unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

int main(int argc, char *argv[])
{
    DIR *streamp;
    DIR *aux;
    struct dirent *dep;
    struct dirent *auxdep;
    char text[60];

     if (argc != 2) {
        printf("usage: %s <pathname>\n", argv[0]);
        exit(1);
    }

    streamp = opendir(argv[1]);
    errno=0;

    strcpy(text,argv[1]);
    strcat(text,"/");

    while((dep=readdir(streamp))!=NULL){
        printf("Archivo ubicado en : %s, de tipo: %d \n",dep->d_name,dep->d_type);
        if (dep->d_type == 4)
        {
            strcat(text,dep->d_name);
            aux=opendir(text);
            while ((auxdep=readdir(aux))!=NULL){
                printf("Subarchivo en: %s, encontrado en directorio: %s \n", auxdep->d_name,text);
            }
            strcpy(text,argv[1]);
            strcat(text,"/");
        }

    }

    if (errno != 0)
    {
        unix_error("Error en readir \n");
    }
    closedir(streamp);

    exit(0);
}