#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
const char INPUT_FILE[40];
const char OUTPUT_FILE[40];
*/
char *function;


void XOR(FILE * IN_FILE, FILE * OUT_FILE);
void NOT(FILE * IN_FILE, FILE * OUT_FILE);

int main(int argc, char * argv[]){
    /*
    printf("ingresar el nombre del archivo de entrada \n");
    scanf("%s", INPUT_FILE);
    printf("Ingresar nombre de archivo de salida\n");
    scanf("%s", OUTPUT_FILE);
    */
    FILE *IN_FILE;
    FILE *OUT_FILE;
    IN_FILE = fopen(argv[1], "r");
    OUT_FILE = fopen(argv[2], "w");
    function = argv[3];

    if (IN_FILE == NULL || OUT_FILE == NULL)
    {
        printf("Imposible abrir uno de los archivos, probablemente el input \n");
        exit(8);
    }

    if ((strncmp("xor", function, 3) == 0))
    {
       XOR(IN_FILE, OUT_FILE);
    }
    else if ((strncmp("not", function, 3) == 0))
    {
        NOT(IN_FILE, OUT_FILE);
    }
    else
    {
        printf("Error, opcion equivocada el programa se terminara por que me da pereza hacer un do while :) \n");
    }

}



//Funciones de encriptar / Desencriptar


void XOR(FILE * IN_FILE, FILE * OUT_FILE){

    int ch;
    while (1)
    {
        ch=fgetc(IN_FILE);
        if (ch == EOF)
        {
           break;
        }
        ch=ch^0xFF;
        fputc(ch,OUT_FILE);
    }
}



void NOT(FILE * IN_FILE, FILE * OUT_FILE){

    int ch;
    while (1)
    {
        ch=fgetc(IN_FILE);
        if (ch == EOF)
        {
           break;
        }
        ch=~ch;
        fputc(ch,OUT_FILE);
    }
}