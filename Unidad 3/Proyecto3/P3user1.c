#include <stdio.h>
 #include <stdint.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <fcntl.h>
 #include <errno.h>
 #include <string.h>
 #include <sys/mman.h>
 #include <sys/wait.h>
 #include <semaphore.h>
 #include <pthread.h>
 #define SIZE 40
sem_t *semf1;
sem_t *semf2;
sem_t *semf3;
sem_t *semf4;
void* mapeo1;
void* mapeo2;

int shm_fd1=0;
int shm_fd2=0;


void cerrarmemoria(){ //AQUI CIERRO LA MEMORIA RESERVADA
    if (close(shm_fd1)<0)
    {
        perror("Error al cerrar memoria");
        exit(EXIT_FAILURE);
    }
    if(shm_unlink("shm1")<0){ //desconectamos del archivo
        perror("unlink failed");
        exit(EXIT_FAILURE);
    }

}

void reservarmemoria(){ //AQUI RESERVO
    shm_fd1 = shm_open("shm1",O_RDWR,0600); // REservo espacio de memoria
    if (shm_fd1<0)
    {
        shm_fd1 = shm_open("shm1", O_CREAT | O_RDWR,0600);
        if (shm_fd1<0)
        {
            perror("Error memoria en  USER1");
            exit(EXIT_FAILURE);
        }
        if (ftruncate(shm_fd1,SIZE * sizeof(char)) < 0)
        {
            perror("Fallo en la trucation USER1");
            exit(EXIT_FAILURE);
        }
        
        
    }

    shm_fd2 = shm_open("shm2",O_RDWR,0600); // REservo espacio de memoria
    if (shm_fd2<0) //SI hay error la creo
    {
        shm_fd2 = shm_open("shm2", O_CREAT | O_RDWR,0600); //
        if (shm_fd2<0) //VErifico si hay error
        {
            perror("Error memoria en USER1");
            exit(EXIT_FAILURE);
        }
        if (ftruncate(shm_fd2,SIZE * sizeof(char)) < 0)
        {
            perror("Fallo en la trucation USER1");
            exit(EXIT_FAILURE);
        }
        
        
    }

}


void encender(){ //Aqui encendemos los semaforos Y LOS CREAMOS en el caso que no esten creados

    
    semf1 = sem_open("semaforo1", 0); 
    if(semf1== SEM_FAILED){ //Si falla entonces lo creamos
        mode_t perms = 0666;
        int flags = O_CREAT;
        unsigned int value =0; 
        semf1 = sem_open("semaforo1", flags, perms, value); //creamos el semaforo
        if(semf1 == SEM_FAILED){
            perror("Usuario1 sem1_open: ");
            exit(EXIT_FAILURE); //SI FALLA LLORELO
        }
    }
    semf2 = sem_open("semaforo2", 0); 
    while(semf2== SEM_FAILED){
        sleep(1); //va a ejecutar esta instruccion hasta que se cree por el otro usuario
        semf2 = sem_open("semaforo2", 0); 
    }
    semf3 = sem_open("semaforo3", 0); 
    if(semf3== SEM_FAILED){
        mode_t perms = 0666;
        int flags = O_CREAT;
        unsigned int value =0; 
        semf3 = sem_open("semaforo3", flags, perms, value);
        if(semf3 == SEM_FAILED){
            perror("Error en el semaforo 3");
            exit(EXIT_FAILURE);
        }
    }
    semf4 = sem_open("semaforo4", 0); 
    while(semf4== SEM_FAILED){
        sleep(1);
        semf4 = sem_open("semaforo4", 0); 
    }

}


void apagar(){ //AQUI CERRAMOS LOS SEMAFOROS Y CERRAMOS LOS LINKS DE LOS SEMAFOROS


//Cerramos los semaforos que usamos para la lectura y escritura
    if(sem_close(semf1)==-1){
        perror("FALLO EN EL CLOSE DEL SEM1");
        exit(EXIT_FAILURE);
    }
    if(sem_close(semf3)==-1){
        perror("FALLO EN EL CLOSE DEL SEM3");
        exit(EXIT_FAILURE);
    }
    //HACEMOS EL UNLINK DE LOS SEMAFORITOS
    if(sem_unlink("semaforo1")==-1){
        perror("FALLO EN EL UNLINK SEM DEL SEMAFORO1");
        exit(EXIT_FAILURE);
    }
    if(sem_unlink("semaforo3")==-1){
        perror("FALLO EN EL UNLINK DEL SEMAFORO3");
        exit(EXIT_FAILURE);
    }


}

void *msgescribir(){
char* msgbuf;
char buf[SIZE];
while (1)
{
    //Primero antes de mapear, debemos truncar la memoria, lo cual ya esta hecho, en el main
    mapeo1 = mmap(NULL,SIZE,PROT_WRITE,MAP_SHARED,shm_fd1,0);
    if (mapeo1 == MAP_FAILED)
    {
        perror("Errorsito en el mapeo 1 ESCRITURA");
        exit(EXIT_FAILURE);
    }
    msgbuf= (char*)mapeo1;
    if(fgets(buf,SIZE,stdin) == NULL){
        break;
    }
    for (size_t i = 0; i < SIZE; i++)
    {
        msgbuf[i] = buf[i];
    }

    
    //ABRIMOS EL SEMF1
    if (sem_post(semf1) == -1)
    {
        perror("sem_post error en escritura SEMAFORO 1");
        exit(EXIT_SUCCESS);
    }

    //CERRAMOS EL SEMF3
    if (sem_wait(semf3)==-1)
    {
       perror("sem_WAIT error en escritura SEMAFORO 3");
       exit(EXIT_SUCCESS);
    }
      
}
apagar();
cerrarmemoria();
return 0;

}

void *msgleer(){

    char* msgbuf;
    while (1)
    {
        if (sem_wait(semf2)==-1)
        {
            perror("sem_wait error en semaforo 2 USER1");
            exit(EXIT_SUCCESS);
        }
        
        mapeo2 = mmap(NULL,SIZE,PROT_READ,MAP_SHARED,shm_fd2,0);
        if (mapeo2==MAP_FAILED)
        {
            perror("ERROR EN EL MAPEO LECTURA USER 1");
            exit(EXIT_SUCCESS);
        }
        msgbuf = (char*)mapeo2;
        if (mapeo2==NULL)
        {
            return NULL;
        }
        fprintf(stdout,"Usuario 2 dice: %s", msgbuf);

        //UNMAPEAMOS
        if (munmap(msgbuf,SIZE)<0)
        {
            perror("Error en el unmapeo de lectura USER1");
            exit(EXIT_SUCCESS);
        }
        if (sem_post(semf4)==-1) //Abrimos el semaforo 4 que es el del otro usuario para avisarle
        {
            perror("Error en sempost lectura SEM4 user1");
            exit(EXIT_SUCCESS);
        }
             
    }
    return 0;
    
}













int main(void){

    pthread_t hilo1;
    pthread_t hilo2;

    encender();
    reservarmemoria();

    pthread_create(&hilo1,NULL,&msgescribir,NULL);
    pthread_create(&hilo2,NULL,&msgleer,NULL);

    pthread_join(hilo1,NULL);
    exit(EXIT_SUCCESS);

}

