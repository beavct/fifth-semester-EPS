#include <stdio.h>
#include <stdlib.h>
#include "ep1.h"

void read_tracefile(char *name){
    FILE *fptr;

    fptr = fopen(name, "r");

    char myString[1024];

    while(fgets(myString, 1024, fptr) != NULL)
        printf("%s", myString);

    printf("\n");
    
    fclose(fptr);    
}

void write_file(char *name){
    FILE *fptr;

    fptr = fopen(name, "w");

    fprintf(fptr, "oiee\n");

    fclose(fptr);     
}

int main(int argc, char **argv){

    if (argc < 3) {
        fprintf(stderr,"Uso: ./ep1 <# escalonador> <trace file> <output file>\n");
        fprintf(stderr,"Vai rodar um simulador de processos utilizando o escalonador <# escalonador> e os dados de <trace file>, os resultados serão salvos em <output file>\n");
        exit(1);
    }
    
    read_tracefile(argv[1]);
    write_file(argv[2]);

    return 0;
}