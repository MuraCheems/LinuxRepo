 #include <stdio.h>
     #include <stdlib.h>
     #include <string.h>

    typedef struct arma
    {
        int balas;
    }gun_t;

    gun_t* nueva_arma();
    void constructorArma(gun_t*, int);
    void disparar(gun_t*);
    void recargar(gun_t*);

    
    typedef struct jugador
    {
        char* name;
        gun_t* arma;
    }player_t;

    player_t* nuevo_jugador();
    void constructor_jugador( player_t*,char*);
    void destructor_jugador(player_t*);
    void recoger_arma( player_t*, gun_t*);
    void disparodejugador(player_t*);
    void tirararma( player_t*);
    
    
    



    int main(int argc, char const *argv[])
    {
       //ANTES DE EMPEZAR DEBERIAMOS CREAR UN ARMA

       gun_t* armita = nueva_arma();
       constructorArma(armita,25);
       char nombrejugador[20];
       player_t* jugador = nuevo_jugador();
       printf("Bienvenido a SuperZOMBIEShooter 3000, Ingrese el nombre de su personaje \n");
       scanf("%s", nombrejugador);
       constructor_jugador(jugador,nombrejugador);
        char c;
        int booleano=1;
        char accion[5];
       do
       {
           
          printf("Que Deseas hacer? \n Buscar un Arma: X \n Caminar a buscar ZOMBIEs: Y \n");
          scanf("%s", accion);

          if ((strncmp("X", accion, 1) == 0))
          {
              while ( (c = getchar()) != '\n' && c != EOF ) { }
              recoger_arma(jugador,armita);
              booleano=0;
          }
          if ((strncmp("Y", accion, 1) == 0))
          {
              while ( (c = getchar()) != '\n' && c != EOF ) { }
              printf("Un extrano en la taberna en la que apareces te dice que no deberias buscar ZOMBIEs sin antes conseguir un arma \n ");
          }
          
       
       } while (booleano);
       

        booleano=1;
       do
       {
            
          printf("Que Deseas hacer? \n Dejar tu arma X \n Caminar a buscar ZOMBIEs: Y \n Recargar tu Arma R \n Disparar M \n Disparar en automatico N \n Borrar Personaje Actual P \n");
          scanf("%s", accion);
          if ((strncmp("X", accion, 1) == 0))
          {
             tirararma(jugador);
             while ( (c = getchar()) != '\n' && c != EOF ) { }
          }
          else if ((strncmp("Y", accion, 1) == 0))
          {
              while ( (c = getchar()) != '\n' && c != EOF ) { }
              printf("Te has encontrado un ZOMBIE, deberias dispararle \n");
          }
          else if ((strncmp("R", accion, 1) == 0))
          {
              while ( (c = getchar()) != '\n' && c != EOF ) { }
              recargar(armita);
          }
          else if ((strncmp("M", accion, 1) == 0))
          {
              while ( (c = getchar()) != '\n' && c != EOF ) { }
              
              disparodejugador(jugador);            
          }
          else if ((strncmp("N", accion, 1) == 0)){
              while ( (c = getchar()) != '\n' && c != EOF ) { }
              while (armita->balas>0)
              {
                  disparodejugador(jugador);
              }

              printf("El recoil de tu AK47 te ha matado, F \n");
              destructor_jugador(jugador);
              exit(8);

          }
          else if  ((strncmp("P", accion, 1) == 0))
          {
              while ( (c = getchar()) != '\n' && c != EOF ) { }
              destructor_jugador(jugador);
          }
          else if (armita->balas == 0)
          {
              while ( (c = getchar()) != '\n' && c != EOF ) { }
              printf("Bro deberias recargar \n");
          }
          
                 
       } while (booleano);
       

        exit(8);
    }
    

    //FUNCIONES ARMAS
    gun_t* nueva_arma(){
        return (gun_t*) malloc(sizeof(gun_t));
    }

    void constructorArma(gun_t* arma, int balitas){

    arma->balas=0;
    if(balitas>0){
        arma->balas=balitas;
     }
    }

    void disparar(gun_t* arma){
        arma->balas--;
        printf("Pichium \n");
    }

    void recargar(gun_t* arma){
        arma->balas=10;
        printf("Recargaste COrrectamente \n");
    }



    //FUNCIONES JUGADOR

    player_t* nuevo_jugador(){
        return (player_t*)malloc(sizeof(player_t));
    }

    void constructor_jugador(player_t* jugador,char* nombre){
        jugador->name = (char*)malloc((strlen(nombre)+1)*sizeof(char));
        strcpy(jugador->name,nombre);
        jugador->arma=NULL; // El jugador no necesita una arma para existir
    }

    void destructor_jugador(player_t* jugador){
        free(jugador->name);
    }

    void recoger_arma(player_t* jugador,gun_t* ak47){
        jugador->arma=ak47;
    }

    void disparodejugador(player_t* jugador){
        if (jugador->arma)
        {
            disparar(jugador->arma);
        }
        else
        printf("No tienes un arma, tas bien? \n ");
        
    }

    void tirararma(player_t* jugador){
        jugador->arma=NULL;
    }