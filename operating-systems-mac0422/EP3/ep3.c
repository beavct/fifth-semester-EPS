/*Cabeçalho retirado da "man syscall"*/
#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>
#include "ep3.h"

#include <readline/readline.h>
#include <readline/history.h>

#include <sys/utsname.h> /*struct utsname*/
#include <sys/time.h> /*gettimeofday*/
#include <sys/types.h> /*uid_t*/
#include <pwd.h> /*mexer no arquivo pwd*/
#include <stdlib.h> /*free*/
#include <string.h> /*strtok*/
#include <sys/wait.h> /*waitpid*/

void monta(char* arquivo){
    
}

void copia(char* origem, char* destino){
    
}

void criadir(char* diretorio){
    
}

void apagadir(char* diretorio){
    
}

void mostra(char* arquivo){
    
}

void toca(char* arquivo){
    
}

void apaga(char* arquivo){
    
}

void lista(char* diretorio){
    
}

void atualizadb(){
    
}

void busca(char* string){
    
}

void status(){
    
}

void desmonta(){
    
}

void sai(){
    exit(0);
}

void main_loop(){
    static char *line_read = (char *)NULL;

    /* Initialize history */
    using_history();  

    while((line_read = readline("{ep3}: "))){

        add_history(line_read);

        char *firstArg = strtok(line_read, " ");

        /* Comandos internos */
        if(!strcmp(firstArg, "monta")){
            
            char* arquivo = strtok(line_read, " ");
            monta(arquivo);

        }
        else if(!strcmp(firstArg, "copia")){

            char* origem = strtok(line_read, " ");
            char* destino = strtok(line_read, " ");
            copia(origem, destino);
        
        }
        else if(!strcmp(firstArg, "criadir")){

            char* diretorio = strtok(line_read, " ");
            criadir(diretorio);

        }
        else if(!strcmp(firstArg, "apagadir")){

            char* diretorio = strtok(line_read, " ");
            apagadir(diretorio);

        }
        else if(!strcmp(firstArg, "mostra")){

            char* arquivo = strtok(line_read, " ");
            mostra(arquivo);

        }
        else if(!strcmp(firstArg, "toca")){

            char* arquivo = strtok(line_read, " ");
            toca (arquivo);
        
        }
        else if(!strcmp(firstArg, "apaga")){

            char* arquivo = strtok(line_read, " ");
            apaga(arquivo);

        }
        else if(!strcmp(firstArg, "lista")){

            char* diretorio = strtok(line_read, " ");
            lista(diretorio);

        }
        else if(!strcmp(firstArg, "atualizadb")){

            atualizadb();

        }
        else if(!strcmp(firstArg, "busca")){

            char* str = strtok(line_read, " ");
            busca(str);

        }
        else if(!strcmp(firstArg, "status")){

            status();

        }
        else if(!strcmp(firstArg, "desmonta")){

            desmonta();

        }
        else if(!strcmp(firstArg, "sai")){

            sai();

        }
        else
            printf("{ep3}: comando não encontrado: %s\n", firstArg);

        free(line_read);

    }

}

int main(){

    main_loop();

    return 0;
}