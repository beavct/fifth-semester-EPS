#include <stdio.h>
#include <stdlib.h>
#include "ep1.h"

void read_tracefile(char *name){
    FILE *fptr;

    fptr = fopen(name, "r");

    char myString[100];

    fgets(myString, 100, fptr);

    printf("%s", myString);

    fclose(fptr);    
}

void write_file(char *name){
    FILE *fptr;

    fptr = fopen(name, "w");

    fprintf(fptr, "oiee\n");

    fclose(fptr);     
}

int main(int argc, char **argv){
    int i;

    for(i=0; i<argc; i++){
        printf("%d %s\n",i, argv[i]);
    }

    printf("teste\n");
    if (argc < 3) {
        fprintf(stderr,"Uso: %s <# escalonador> <trace file> <output file>\n",argv[0]);
        /*exit(1);*/
    }
    read_tracefile(argv[2]);
    write_file(argv[3]);

    return 0;
}