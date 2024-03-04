/*Cabeçalho retirado da "man syscall"*/
/* #define _GNU_SOURCE */
#include <sys/syscall.h>
#include <unistd.h>

#include <stdio.h>
#include "newsh.h"

#include <readline/readline.h>
#include <readline/history.h>

/* Confirmar se pode usar */
#include <sys/time.h>
#include <time.h>
#include <sys/types.h>
#include <pwd.h> /*mexer no arquivo pwd*/
#include <string.h>
#include <sys/utsname.h>
#include <stdlib.h> /*free*/
#include <dirent.h> /*conteúdo do diretório*/
#include <sys/stat.h> /* syscall stat*/

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
    printf("cd\n");

    /* Syscall: chdir (change working directory) */
    chdir(&path[3]);

    /* printing current working directory */
    char s[100];
    printf("%s\n", getcwd(s, 100));    
}

void rm_command(char *path){
    printf("rm\n");

    /* Syscall: unlink, remove the specified FILE*/
    if(unlink(&path[3])==-1){
        /* Não era um ARQUIVO, e sim um DIRETÓRIO*/
        /* Syscall: rmdir
        * Só serve para diretórios VAZIOS*/
        rmdir(&path[3]);
    }    
}

void uname_command(void){
    printf("uname -a\n");

    /* Syscall: uname, get system info*/
    struct utsname system_info;
    uname(&system_info);
    printf("%s %s %s %s %s GNU/Linux\n", system_info.sysname, system_info.nodename, system_info.release, system_info.version, system_info.machine);
    /* Falta o operating-system que vem no final
    * Perguntar para o Daniel se precisa fazer uma verificação para ver se o processor e hardware-platform são conhecidos para printa-los ou se não precisa mostrar essa informação*/

}

void ps_command(){

    /* -a: Select all processes except both session leaders  (see  getsid(2))  and  processes  not
    *  associated with a terminal. */
    printf("/bin/ps a\n");

}

void ls_command(){
    printf("/bin/ls --color=never -1t\n");
    /*-1 um por coluna, -t ordenar por tempo, mais novos primeiro (da pra usar o stat que é syscall)*/

    /* Syscall: getcwd, conseguir o caminho atual */
    char path[1024];
    getcwd(path, 1024);

    DIR *diretory_pointer;
    diretory_pointer = opendir(path);

    struct dirent *entry;
    /*struct stat *files_info;*/

    /*struct file_info{
        char*
    }*/


    /* Syscall: readdir, */
    while( (entry=readdir(diretory_pointer)) ){
        printf("%s\n", entry->d_name);
        /*stat(entry->d_name, files_info);*/
        /*printf("%s\n", );*/
    }

    /*verificar ordem e arquivos a mais*/


    closedir(diretory_pointer);

}

void ep1_command(){
    printf("ep1\n");

    /* Syscall: getcwd, conseguir o caminho atual */
    char path[1024];
    char ep1_string[4] = "ep1";
    getcwd(path, 1024);
    strcat(path, ep1_string);
    char *argv_ex[] = {"./ep1 2 trace.txt output.txt", (char*)0}; 
    /*char* envp[] = { "some", "environment", NULL };*/

    printf("RESULTADO %d\n", execve(path, argv_ex, NULL));    
}

void main_loop(){
    /* Para verificar os comandos "cd" e "rm" */
    char command1[3];
    /* Para verificar o comando "ep1" */
    char command2[4];

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

        strncpy(command2, line_read, 3);
        command2[3] = '\0';

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
        else if(!strcmp(command2, "ep1")){

            ep1_command();

        }
        else if(!strcmp(line_read, "/bin/ps a")){

            ps_command();

        }
        else if(!strcmp(line_read, "/bin/ls --color=never -1t")){

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
