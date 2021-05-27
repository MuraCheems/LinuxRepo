#include <stdio.h>
 #include <string.h>
 #include <errno.h>
 #include <unistd.h>
 #include <stdlib.h>
 #include <pthread.h>
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <signal.h>

 #define PORT 6666
 #define BUF_SIZE 128


 int aux=0;
 int numerousuarios[5];

 

 struct client_t{
     int socket;
     int rxState;
     char username[40];
     int id;
 };

 struct client_t *client; //APuntador del cliente
 pthread_t *rxThreadId; //Hilo 


 void * readThread(void *arg){
     struct client_t *clientactual = ((struct client_t *)arg);
     //printf("Llego aqui papi"); //PRUEBITA
     ssize_t numOfBytes;
     char buf[BUF_SIZE];
     int status;
     int idName = 0;
     char username[40];

     while(1){
         numOfBytes = read(clientactual->socket, buf, BUF_SIZE);
         if(0 == numOfBytes){
             printf("client closed the socket end\n");
             break;
         }
         else if(-1 == numOfBytes){
             perror("ReadThread read() fails: ");
             break;
         }
         else if(numerousuarios[clientactual->id-1]==1){
             if (idName==0)
             {
                 idName=1;
                 strcpy(username,buf); //ALmacenamos el nombre del usuario que se conecto
                 strcpy(clientactual->username,username);
                 strcat(buf, " Se ha unido al chat\n"); //Aqui avisamos quien se conecto
             }
             
             for (int i = 1; i <= 5; i++) //Igual al tamano de numerodeusuarios
             {
                 if (clientactual->id != client[i-1].id && numerousuarios[i-1]!=0){
                     status = write(client[i-1].socket,buf,strlen(buf)+1);
                     if (status==-1)
                     {
                        break; //Error
                     }
                     
                 }

                 
             }
          
         }

         }
     
     strcpy(buf, username);
     strcat(buf," Se ha desconectado del chat\n");
     printf("%s", buf);

     for (int i = 1; i <= 5; i++)
     {
         if (clientactual->id != client[i-1].id && numerousuarios[i-1]!=0)
         {
             status=write(client[i-1].socket, buf,strlen(buf)+1);
             if (status==-1)
             {
                 break;
                 perror("Server write to cliente fails: ");
                 //Error aqui
             }
             
         }
         
     }
     idName=0;
     clientactual->rxState=0;
     numerousuarios[clientactual->id-1]=0;
     close(clientactual->socket);
     aux--;
     printf("Terminate Pthread for reading\n");
     client->rxState = 0;
     return NULL;
 }
 int main(int argc, char *argv[]){
     int status;
     int enable = 1;
     int server_sd;
     int client_sd;
     rxThreadId = malloc(sizeof(pthread_t)*5); //Por el numero de clientes
     // 1. Ignore SIGPIPE
     client= malloc(sizeof(struct client_t)*5);//por el numero de clientes
     signal(SIGPIPE, SIG_IGN);

     // 2. Create socket
     server_sd = socket(AF_INET, SOCK_STREAM, 0);
     if (server_sd == -1) {
         perror("Socket creation fails\n");
         exit(EXIT_FAILURE);
     }
     printf("Socket created\n");

     // 3. turn off bind address checking
     status = setsockopt(server_sd, SOL_SOCKET, SO_REUSEADDR,(int *) &enable, sizeof(enable));
     if (-1 == status){
         perror("setsockopt error: ");
     }

     //4. BIND the socket to an address
     // Prepare the address
     struct sockaddr_in addr;
     memset(&addr, 0, sizeof(addr));
     addr.sin_family = AF_INET;
     addr.sin_addr.s_addr = INADDR_ANY;
     addr.sin_port = htons(PORT);

     status = bind(server_sd, (struct sockaddr*)&addr, sizeof(addr));
     if (-1 == status) {
         perror("Bind fails: ");
         close(server_sd);
         exit(EXIT_FAILURE);
     }
     printf("Socket binded\n");

     // 5. Set backlog

     status = listen(server_sd, 1);

     if (-1 == status) {
         perror("Listen fails: ");
         close(server_sd);
         exit(EXIT_FAILURE);
     }

     printf("Server listening\n");


    while (1)
    {
        int usernumber=0;
        client_sd=accept(server_sd,NULL,NULL);
        if (aux<5)
        {
            aux++;
            printf("El cliente numero %d se ha conectado\n",aux);
            if (client_sd==-1)
            {
                perror("Error aceptando al cliente");
                close(server_sd);
                exit(EXIT_FAILURE); //validamos en el caso que haya un error aceptando al cliente
            }
            
            for (int i = 1; i <=5; i++)
            {
                if (numerousuarios[i-1]==0)
                {
                    numerousuarios[i-1]=1;
                    usernumber=i;
                    break;
                }
                
            }

            client[usernumber-1].socket=client_sd;
            client[usernumber-1].rxState=1;
            client[usernumber-1].id=usernumber;
            //ASIGNO VALORES AL OBJETO DE CLIENTE
            status=pthread_create(&(rxThreadId[usernumber-1]),NULL,&readThread,&(client[usernumber-1])); //DEdico uno de los hilos del vector al cliente

            
        
        
    } //EN EL CASO QUE EL SERVIDOR ESTE LLENO
    else{
        char buf[BUF_SIZE];
        int status;
        strcpy(buf,"Server full\n");
        status=write(client_sd,buf,strlen(buf)+1);
        if(status==-1){
        perror("Error mandando mensaje al cliente");
        break;
        }
        close(client_sd);
    }

    
 }
 return 0;
 }