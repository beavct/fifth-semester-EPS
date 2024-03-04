#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

    printf("Olá mundo\n");
    if (argc != 4) {
        fprintf(stderr,"Uso: %s <# escalonador> <trace file> <output file>\n",argv[0]);
        /*fprintf(stderr,"Vai rodar um servidor de echo na porta <Porta> TCP\n");*/
        /*exit(1);*/
    }

    return 0;
}