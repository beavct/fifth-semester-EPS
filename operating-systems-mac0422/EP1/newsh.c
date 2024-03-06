/*Cabeçalho retirado da "man syscall"*/
/* #define _GNU_SOURCE */
#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>
#include "newsh.h"

#include <readline/readline.h>
#include <readline/history.h>

/* Confirmar se pode usar */
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
    char s[100];
    printf("%s\n", getcwd(s, 100));    
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
    /* Falta o operating-system que vem no final
    * Perguntar para o Daniel se precisa fazer uma verificação para ver se o processor e hardware-platform são conhecidos para printa-los ou se não precisa mostrar essa informação*/

}

void ps_command(){

    char *path = "/bin/ps";
    char *argv[] = {"x", (char *)0};
    /*char *envp[] = {"ok", (char *)0};    */

    execve(path, argv, NULL);

}

void ls_command(){

    char *path = "/bin/ls";
    char *argv[] = {"--color=never", "-1t", (char *)0};
    /*char *envp[] = {"ok", (char *)0};    */

    execve(path, argv, NULL);        
}

void ep1_command(char *argv){

    /* Pegar argumentos da string argv e separá-los */
    char *ep1str = strtok(argv, " ");
    char *escalonador = strtok(NULL, " ");
    char *tracefile = strtok(NULL, " ");
    char *outputfile = strtok(NULL, " ");

    char *argv_ex[] = {ep1str, escalonador, tracefile, outputfile, (char *)0};

    execve("./ep1", argv_ex, NULL);

}

void main_loop(){
    /* Para verificar os comandos "cd" e "rm" */
    char command1[3];
    /* Para verificar o comando "ep1" */
    char command2[6];

    static char *line_read = (char *)NULL;

    /* Initialize history */
    using_history();  

    char *prompt = get_prompt();

    /*while(fgets(buff, 259, stdin) != NULL){*/
    while((line_read = readline(prompt))){

        add_history(line_read);

        /* Verifica se o que foi lido pelo fgets() tem "\n", se tiver, o remove*/
        int buff_len = strlen(line_read);
        if(line_read[buff_len - 1] == '\n') line_read[--buff_len] = 0;

        strncpy(command1, line_read, 2);
        command1[2] = '\0';

        strncpy(command2, line_read, 5);
        command2[5] = '\0';

        /* Comandos internos */
        if(!strcmp(command1, "cd")){

            cd_command(line_read);

        }
        else if(!strcmp(command1, "rm")){

            rm_command(line_read);
        
        }
        else if(!strcmp(line_read, "uname -a")){

            uname_command();

        }
        else if(!strcmp(command2, "./ep1")){
            int status;

            if(fork() != 0)
                waitpid(-1, &status, 0);
            else
                ep1_command(line_read);

        }
        else if(!strcmp(line_read, "/bin/ps a")){
            int status;

            if(fork() != 0)
                waitpid(-1, &status, 0);
            else
                ps_command();


        }
        else if(!strcmp(line_read, "/bin/ls --color=never -1t")){
            int status;

            if(fork() != 0)
                waitpid(-1, &status, 0);
            else
                ls_command();

        }
        else{
            printf("newsh: command not found: %s\n", line_read);
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
