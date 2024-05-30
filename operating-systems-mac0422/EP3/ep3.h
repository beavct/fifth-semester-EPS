/* FUNÇÕES DO SHELL*/

/* FUNÇÕES BASE */
/* Loop principal de leitura de comandos enviados pelo usuário*/
void main_loop();

/* COMANDOS DE ARQUIVO */
void monta(char* arquivo);

void copia(char* origem, char* destino);

void criadir(char* diretorio);

void apagadir(char* diretorio);

void mostra(char* arquivo);

void toca(char* arquivo);

void apaga(char* arquivo);

void lista(char* diretorio);

void atualizadb();

void busca(char* string);

void status();

void desmonta();

void sai();