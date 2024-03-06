/* FUNÇÕES DO SHELL*/

/* FUNÇÕES BASE */
/* Gera o prompt <nome de usuário> [HH:MM:SS]*/
char *get_prompt();
/* Loop principal de leitura de comandos enviados pelo usuário*/
void main_loop();

/* COMANDOS EMBUTIDOS (INTERNOS) */
/* Comando cd <repositório> */
void cd_command(char *path);
/* Comando rm <arquivo/repositório>*/
void rm_command(char *path);
/* Comando uname -a */
void uname_command(void);

/* INVOCAÇÃO EXTERNA (EXECUÇÃO) */
/* Comando ps a */
void ps_command();
/* Comando ls */
void ls_command();
/* Comando executável externo (ep1) */
void ep1_command(char *argv);