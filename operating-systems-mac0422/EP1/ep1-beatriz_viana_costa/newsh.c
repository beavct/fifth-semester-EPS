/*Cabeçalho retirado da "man syscall"*/
#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>
#include "newsh.h"

#include <readline/readline.h>
#include <readline/history.h>

#include <sys/utsname.h> /*struct utsname*/
#include <sys/time.h> /*gettimeofday*/
#include <sys/types.h> /*uid_t*/
#include <pwd.h> /*mexer no arquivo pwd*/
#include <stdlib.h> /*free*/
#include <string.h> /*strtok*/
#include <sys/wait.h> /*waitpid*/

/* Printa o prompt com o nome de usuário + hora atual */
char *get_prompt(){
    /* Syscall: getuid() */
    uid_t myuid = getuid();

    /* Procurar o nome de usuário no /etc/passwd (primeira coluna) */
    struct passwd *passwd_info;

    passwd_info = getpwuid(myuid);

    /* Printar [HH:MM::SS] */
    struct timeval time; 
    char buffer[13];

    /* Syscall: gettimeofday() */
    gettimeofday(&time, NULL);
    strftime(buffer, 13, " [%T]:", localtime(&time.tv_sec)); 

    char *response = (char*)malloc(sizeof(char)*((int)sizeof(passwd_info->pw_name)+15));
    strcpy(response, passwd_info->pw_name);
    strcat(response, buffer);
    strcat(response, " ");

    return response;
}

void cd_command(char *path){

    /* Syscall: chdir (change working directory) */
    chdir(&path[3]);

    /* printing current working directory */
    /*char s[100];
    printf("%s\n", getcwd(s, 100));    */
}

void rm_command(char *path){

    /* Syscall: unlink, remove the specified FILE*/
    if(unlink(&path[3])==-1){
        /* Não era um ARQUIVO, e sim um DIRETÓRIO*/
        /* Syscall: rmdir
        * Só serve para diretórios VAZIOS*/
        rmdir(&path[3]);
    }    
}

void uname_command(void){

    /* Syscall: uname, get system info*/
    struct utsname system_info;
    uname(&system_info);
    printf("%s %s %s %s %s GNU/Linux\n", system_info.sysname, system_info.nodename, system_info.release, system_info.version, system_info.machine);

}

void main_loop(){
    static char *line_read = (char *)NULL;

    /* Initialize history */
    using_history();  

    char *prompt = get_prompt();

    while((line_read = readline(prompt))){

        add_history(line_read);

        char *firstArg = strtok(line_read, " ");

        /* Comandos internos */
        if(!strcmp(firstArg, "cd")){
            
            char* path = strtok(line_read, " ");
            cd_command(path);

        }
        else if(!strcmp(firstArg, "rm")){

            char* path = strtok(line_read, " ");
            rm_command(path);
        
        }
        else if(!strcmp(firstArg, "uname")){

            uname_command();

        }
        else{
            int status;

            if(fork() != 0)
                waitpid(-1, &status, 0);
            else{
                /*Pega os argumentos do comando*/
                char *argv[256];
                argv[0]=NULL;
                int i=0;

                if(strcmp(firstArg, "./ep1")==0)
                    argv[i++]=firstArg;

                argv[i]=strtok(NULL, " ");
                while(argv[i]!= NULL){
                    i++;
                    argv[i]=strtok(NULL, " ");
                }

                int ret;

                ret = execve(firstArg, argv, NULL);

                if(ret == -1)
                    printf("newsh: command not found: %s\n", firstArg);
            }            
        }

        free(line_read);
        free(prompt);

        prompt = get_prompt();

    }

}

int main(){

    main_loop();

    return 0;
}
