#include <stdio.h>
#include "ep3.h"

/*Para as funções de shell*/
#include <readline/readline.h>
#include <readline/history.h>

#include <time.h>
#include <sys/time.h> 
#include <sys/types.h>
#include <stdlib.h> 
#include <string.h> 

/* Variáveis globais */
Sistema_de_arquivos* fs_geral = NULL;
Banco_de_dados* bd_geral = NULL;

// arrumar essa função aqui pra printar mais bonito
void printa_arvore(Arquivo* root, int prof, int ehUlt) {
    if(root == NULL) return;

    // Imprime a identação para a profundidade atual
    for(int i = 0; i < prof; i++) {
        if(i == prof - 1) {
            if(ehUlt)
                printf("└── ");
            else
                printf("├── ");
        } 
        else
            printf("│   ");
    }

    printf("%s%s\n", root->nome, root->ehDir && !root->root ? "/" : "");

    if(root->filho != NULL)
        printa_arvore(root->filho, prof + 1, root->filho->irmao == NULL);

    if(root->irmao != NULL)
        printa_arvore(root->irmao, prof, root->irmao->irmao == NULL);
}

void salva_arquivos(Arquivo* arq, FILE* file){
    if (arq == NULL) {
        int flag_filho = 0;
        fwrite(&flag_filho, sizeof(int), 1, file);
        return;
    }

    int flag_filho = 1;
    fwrite(&flag_filho, sizeof(int), 1, file);

    int nome_len = strlen(arq->nome)+1;
    fwrite(&nome_len, sizeof(int), 1, file);
    fwrite(arq->nome, sizeof(char), nome_len, file);

    fwrite(&arq->tamanho_bytes, sizeof(int), 1, file);
    fwrite(&arq->tempo_criacao, sizeof(time_t), 1, file);
    fwrite(&arq->tempo_ult_mod, sizeof(time_t), 1, file);
    fwrite(&arq->tempo_ult_acess, sizeof(time_t), 1, file);
    fwrite(&arq->ehDir, sizeof(int), 1, file);
    fwrite(&arq->root, sizeof(int), 1, file);

    salva_arquivos(arq->filho, file);
    salva_arquivos(arq->irmao, file);

}

Arquivo* carrega_arquivos(FILE* file){
    int flag_filho;
    fread(&flag_filho, sizeof(int), 1, file);

    if (flag_filho == 0) {
        return NULL;
    }

    Arquivo* arq = (Arquivo*)malloc(sizeof(Arquivo));
    int nome_len;
    fread(&nome_len, sizeof(int), 1, file);
    fread(arq->nome, sizeof(char), nome_len, file);
    arq->nome[nome_len-1] = '\0';  // Garantir a terminação do nome

    fread(&arq->tamanho_bytes, sizeof(int), 1, file);
    fread(&arq->tempo_criacao, sizeof(time_t), 1, file);
    fread(&arq->tempo_ult_mod, sizeof(time_t), 1, file);
    fread(&arq->tempo_ult_acess, sizeof(time_t), 1, file);
    fread(&arq->ehDir, sizeof(int), 1, file);
    fread(&arq->root, sizeof(int), 1, file);

    arq->filho = carrega_arquivos(file);
    arq->irmao = carrega_arquivos(file);

    return arq;
}

void salva_sistema_de_arquivos(Sistema_de_arquivos *fs, const char *arquivo){
    FILE* file = fopen(arquivo, "wb");

    if(file == NULL){
        fprintf(stderr,"fopen :(\n");
        return;
    }

    fwrite(fs->fat, sizeof(int), MAX_BLOCKS, file);
    fwrite(fs->bitmap, sizeof(int), MAX_BLOCKS, file);
    fwrite(&fs->quant_dir, sizeof(int), 1, file);
    fwrite(&fs->quant_arq, sizeof(int), 1, file);
    fwrite(&fs->espaco_livre, sizeof(size_t), 1, file);
    fwrite(&fs->espaco_desperdicado, sizeof(size_t), 1, file);

    salva_arquivos(fs->root, file);
    fclose(file);
}

Sistema_de_arquivos* inicia_sistema_de_arquivos(const char* arquivo){
    Sistema_de_arquivos* fs = (Sistema_de_arquivos*)malloc(sizeof(Sistema_de_arquivos));
    
    fs->root = (Arquivo*)malloc(sizeof(Arquivo)); 
    strcpy(fs->root->nome, "/");
    fs->root->tamanho_bytes = 0;
    fs->root->tempo_criacao = time(NULL);
    fs->root->tempo_ult_acess = fs->root->tempo_criacao;
    fs->root->tempo_ult_mod = fs->root->tempo_criacao;
    fs->root->root = 1;
    fs->root->ehDir = 1;
    fs->root->irmao = NULL;
    fs->root->filho = NULL;

    for(int i=0; i<MAX_BLOCKS; i++){
        fs->fat[i] = -1;
        fs->bitmap[i] = 0;
    }

    fs->espaco_livre = MAX_BLOCKS * BLOCK_SIZE;
    fs->espaco_desperdicado = 0;
    fs->nome = (char*)malloc(strlen(arquivo) + 1);
    strcpy(fs->nome, arquivo);
    fs->quant_dir = 0;
    fs->quant_arq = 0;

    return fs;
}

Sistema_de_arquivos* carrega_sistema_de_arquivos(const char* arquivo){
    FILE *file;

    file = fopen(arquivo, "rb");

    if(file == NULL)
        return NULL;

    Sistema_de_arquivos *fs = (Sistema_de_arquivos*)malloc(sizeof(Sistema_de_arquivos));

    fread(fs->fat, sizeof(int), MAX_BLOCKS, file);
    fread(fs->bitmap, sizeof(int), MAX_BLOCKS, file);
    fread(&fs->quant_dir, sizeof(int), 1, file);
    fread(&fs->quant_arq, sizeof(int), 1, file);
    fread(&fs->espaco_livre, sizeof(size_t), 1, file);
    fread(&fs->espaco_desperdicado, sizeof(size_t), 1, file);
    
    fs->nome = (char*)malloc(strlen(arquivo) + 1);
    strcpy(fs->nome, arquivo);
    
    fs->root = carrega_arquivos(file);
    fclose(file);
    return fs;
}

void monta(const char* arquivo){
    Sistema_de_arquivos* fs = carrega_sistema_de_arquivos(arquivo);

    if(fs == NULL){
        fs = inicia_sistema_de_arquivos(arquivo);
        printf("Sistema de arquivos %s criado :)\n", arquivo);
    }
    else
        printf("Sistema de arquivos montado a partir do arquivo %s :)\n", arquivo);

    printa_arvore(fs->root, 0, 1);

    fs_geral = fs;
}

void copia(char* origem,char* destino){
    FILE* origem_file = fopen(origem, "r");
    if (origem_file == NULL) {
        fprintf(stderr,"fopen :(\n");
        return;
    }

    // Verificações de tamanho do arquivo e se há espaço o suficiente no sistema de arquivos
    fseek(origem_file, 0, SEEK_END);
    long tamanho_arquivo = ftell(origem_file);
    fseek(origem_file, 0, SEEK_SET);

    if(tamanho_arquivo > 100 * 1024 * 1024) {
        fprintf(stderr, "O tamanho do arquivo excede o limite de 100MB :(\n");
        fclose(origem_file);
        return;
    }

    int blocos_necessarios = (tamanho_arquivo + 4095) / 4096;
    //printf("quant blocos %d\n", blocos_necessarios);
    //printf("espaco livre %ld\n", fs_geral->espaco_livre);

    if(fs_geral->espaco_livre < (size_t)blocos_necessarios * 4096) {
        fprintf(stderr, "Espaço insuficiente no sistema de arquivos :(\n");
        fclose(origem_file);
        return;
    }

    int blocos_livres = 0;
    for(int i = 0; i < MAX_BLOCKS; i++) {
        if (fs_geral->bitmap[i] == 0) {
            blocos_livres++;
            if (blocos_livres >= blocos_necessarios) {
                break;
            }
        }
    }
    if(blocos_livres < blocos_necessarios) {
        fprintf(stderr, "Não há blocos livres suficientes no sistema de arquivos :(\n");
        fclose(origem_file);
        return;
    }

    char* save_destino = (char*)malloc(strlen(destino) + 1);
    strcpy(save_destino, destino);
    // Infos do arquivo
    Arquivo* novo_arquivo = (Arquivo*) malloc(sizeof(Arquivo));

    novo_arquivo->tamanho_bytes = tamanho_arquivo; 
    novo_arquivo->tempo_criacao = time(NULL);
    novo_arquivo->tempo_ult_mod = novo_arquivo->tempo_criacao;
    novo_arquivo->tempo_ult_acess = novo_arquivo->tempo_criacao;
    novo_arquivo->filho = NULL;
    novo_arquivo->irmao = NULL;
    novo_arquivo->ehDir = 0;
    novo_arquivo->root = 0; 

    novo_arquivo->conteudo = (char*)malloc(sizeof(char)*tamanho_arquivo); 

    char* nome_arq = strrchr(origem, '/');
    if(nome_arq == NULL) {
        strcpy(novo_arquivo->nome, origem);
    } 
    else{
        strcpy(novo_arquivo->nome, nome_arq + 1);
    }

    // Quando quer copiar diretamente para o diretório "/"
    if(strcmp(destino, "/") == 0){
        if(fs_geral->root->filho == NULL)
            fs_geral->root->filho = novo_arquivo;
        else{
            Arquivo* cur_diretorio = fs_geral->root->filho;

            while(cur_diretorio->irmao != NULL){
                cur_diretorio = cur_diretorio->irmao;
            }   

            cur_diretorio->irmao = novo_arquivo;
        }
    }
    else{
        // Percorrer os tokens para encontrar o diretório correto
        char* path_auxiliar1 = strtok(destino, "/");
        char* path_auxiliar2 = path_auxiliar1;
        Arquivo* cur_diretorio = fs_geral->root;

        while(path_auxiliar2 != NULL){
            Arquivo* cur_auxiliar = cur_diretorio->filho;

            while(cur_auxiliar->irmao != NULL && strcmp(path_auxiliar1,cur_auxiliar->nome)){
                cur_auxiliar = cur_auxiliar->irmao;
            }

            cur_diretorio = cur_auxiliar;

            path_auxiliar1 = path_auxiliar2;
            path_auxiliar2 = strtok(NULL, "/");
        }

        while(strcmp(path_auxiliar1, cur_diretorio->nome) != 0 && cur_diretorio != NULL){
            cur_diretorio = cur_diretorio->irmao;
        }

        // Adicionar na árvore de arquivos
        if(cur_diretorio->filho == NULL) {
            cur_diretorio->filho = novo_arquivo;
        }
        else{
            Arquivo* temp = cur_diretorio->filho;
            while (temp->irmao != NULL) {
                temp = temp->irmao;
            }
            temp->irmao = novo_arquivo;
        }
    }

    size_t bytes_lidos = fread(novo_arquivo->conteudo, 1, tamanho_arquivo, origem_file);
    if(bytes_lidos != (size_t)tamanho_arquivo) {
        fprintf(stderr, "Leitura :(\n");
        fclose(origem_file);
        free(novo_arquivo->conteudo);
        free(novo_arquivo);
        return;
    }

    // Atualiza o bitmap e fat
    int bloco_atual = 0;
    int ultimo_bloco = -1;
    int blocos_usados = 0;

    for(long offset = 0; offset < tamanho_arquivo; offset += BLOCK_SIZE) {
        // Encontrar um bloco livre no bitmap
        while(bloco_atual < MAX_BLOCKS && fs_geral->bitmap[bloco_atual] != 0) {
            bloco_atual++;
        }

        // Marcar o bloco como usado no bitmap
        fs_geral->bitmap[bloco_atual] = 1;
        if(ultimo_bloco != -1) {
            fs_geral->fat[ultimo_bloco] = bloco_atual;
        }
        ultimo_bloco = bloco_atual;

        blocos_usados++;
    }

    // Marcar o final da cadeia de blocos na FAT
    if(ultimo_bloco != -1) {
        fs_geral->fat[ultimo_bloco] = -1;
    }

    fs_geral->espaco_livre -= blocos_usados * BLOCK_SIZE;
    fs_geral->espaco_desperdicado += (blocos_usados * BLOCK_SIZE) - tamanho_arquivo;

    printf("Arquivo copiado com sucesso de %s para %s :)\n", origem, save_destino); 

    fs_geral->quant_arq++;  
}

void criadir(char* diretorio){
    Arquivo* cur_diretorio = fs_geral->root;
    Arquivo* save_dir = NULL;

    char* path_auxiliar1 = strtok(diretorio, "/");
    char* path_auxiliar2 = strtok(NULL, "/");

    // percorre os diretórios 
    while(path_auxiliar2 != NULL){
        Arquivo* cur_auxiliar = cur_diretorio->filho;

        if(!cur_auxiliar->ehDir)
            save_dir = cur_diretorio;
        else
            save_dir = NULL;

        while(strcmp(path_auxiliar1,cur_auxiliar->nome) && cur_auxiliar != NULL){
            cur_auxiliar = cur_auxiliar->irmao;
        }

        cur_diretorio = cur_auxiliar;

        path_auxiliar1 = path_auxiliar2;
        path_auxiliar2 = strtok(NULL, "/");
    }

    Arquivo* novo_diretorio = (Arquivo*)malloc(sizeof(Arquivo));
    strcpy(novo_diretorio->nome, path_auxiliar1);
    novo_diretorio->irmao= NULL;
    novo_diretorio->filho= NULL;
    novo_diretorio->ehDir = 1;
    novo_diretorio->root = 0;
    novo_diretorio->tamanho_bytes = 0;
    novo_diretorio->tempo_criacao = time(NULL);
    novo_diretorio->tempo_ult_acess = novo_diretorio->tempo_criacao;
    novo_diretorio->tempo_ult_mod = novo_diretorio->tempo_criacao;

    // Encontrar um bloco livre no bitmap
    int bloco_livre = -1;
    for (int i = 0; i < MAX_BLOCKS; ++i) {
        if (fs_geral->bitmap[i] == 0) {
            bloco_livre = i;
            fs_geral->bitmap[i] = 1; // Marcar como usado no bitmap
            break;
        }
    }

    if (bloco_livre == -1) {
        printf("Não há blocos livres para criar o diretório :(\n");
        free(novo_diretorio);
        return;
    }

    // Atualizar o FAT com o bloco livre
    fs_geral->fat[bloco_livre] = -1; // Como é um diretório, o valor no FAT é -1

    if(cur_diretorio->filho == NULL)
        cur_diretorio->filho = novo_diretorio;
    else if(save_dir != NULL){
        // Para que os diretórios fiquem sempre antes dos arquivos regulares
        Arquivo* aux = save_dir->filho;
        save_dir->filho = novo_diretorio;
        novo_diretorio->irmao = aux;
    }
    else{
        if(cur_diretorio->filho->ehDir){
            cur_diretorio = cur_diretorio->filho;

            while(cur_diretorio->irmao!=NULL && cur_diretorio->irmao->ehDir)
                cur_diretorio = cur_diretorio->irmao;
            
            if(cur_diretorio->irmao == NULL)
                cur_diretorio->irmao = novo_diretorio;
            else{
                // Para que os diretórios fiquem sempre antes dos arquivos regulares
                Arquivo* aux = cur_diretorio->irmao;

                cur_diretorio->irmao = novo_diretorio;
                novo_diretorio->irmao = aux;
            }
        }
        else{
            Arquivo* aux = cur_diretorio->filho;

            cur_diretorio->filho = novo_diretorio;
            novo_diretorio->irmao = aux;
        }
    }

    fs_geral->espaco_livre -= BLOCK_SIZE;

    printf("Diretório %s criado com sucesso :)\n", novo_diretorio->nome);

    fs_geral->quant_dir++;

}

void libera_espaco(Arquivo* arq){
    if (arq == NULL || arq->ehDir) 
        return;

    int blocos_usados = (arq->tamanho_bytes + BLOCK_SIZE - 1) / BLOCK_SIZE;
    //int bloco_atual = 0;
    int blocos_liberados = 0;

    for (int i = 0; i < MAX_BLOCKS; ++i) {
        if (fs_geral->fat[i] != -1) {
            //int bloco_proximo = fs_geral->fat[i];
            fs_geral->fat[i] = -1;
            fs_geral->bitmap[i] = 0;
            fs_geral->espaco_livre += BLOCK_SIZE;
            blocos_liberados++;
            if (blocos_liberados == blocos_usados) break;
        }
    }

    fs_geral->espaco_desperdicado -= (blocos_liberados * BLOCK_SIZE) - arq->tamanho_bytes;
}

void apaga_arquivos(Arquivo* arq) {
    if (arq == NULL) return;

    // Recursivamente apaga os filhos e irmãos
    apaga_arquivos(arq->filho);
    apaga_arquivos(arq->irmao);

    // VERIFICAR SE ESTA CORRETO
    if(!arq->ehDir){
        libera_espaco(arq);
        free(arq->conteudo);
        fs_geral->quant_arq--;
    }
    else
        fs_geral->quant_dir--;

    free(arq);

}

void apagadir(char* diretorio) {
    char* diretorio_copia = strdup(diretorio);
    strcpy(diretorio_copia, diretorio);

    char* path_auxiliar1 = strtok(diretorio, "/");
    char* path_auxiliar2 = strtok(NULL, "/");

    // Percorre os diretórios do caminho fornecido
    // Não é possível apagar o diretório "/" 
    Arquivo* cur_diretorio = fs_geral->root->filho;

    // Ponteiro para o nó anterior enquanto percorremos a lista de irmãos
    Arquivo* anterior = fs_geral->root;

    // Flag para saber se o anterior é irmão ou pai
    int flag_parentesco = 1; // 1: pai, 2: irmao  

    while(path_auxiliar2 != NULL) {
        Arquivo* cur_auxiliar = cur_diretorio->filho;
        anterior = cur_diretorio;

        // Percorre os filhos do diretório atual para encontrar o próximo diretório no caminho
        while (cur_auxiliar != NULL && strcmp(path_auxiliar2, cur_auxiliar->nome) != 0) {
            anterior = cur_auxiliar;
            cur_auxiliar = cur_auxiliar->irmao;
        }

        cur_diretorio = cur_auxiliar;

        path_auxiliar1 = path_auxiliar2;
        path_auxiliar2 = strtok(NULL, "/");
    }

    while(strcmp(path_auxiliar1, cur_diretorio->nome) != 0 && cur_diretorio != NULL){
        anterior = cur_diretorio;
        cur_diretorio = cur_diretorio->irmao;

        flag_parentesco = 2;
    }

    // Verificar se o diretório a ser excluído está vazio
    if(cur_diretorio->filho == NULL) {
        // Remover o diretório da lista de irmãos do diretório pai
        if(anterior == NULL) {
            // O diretório a ser excluído é o primeiro filho do diretório pai
            fs_geral->root->filho = cur_diretorio->irmao;

        } 
        else{
            if(flag_parentesco == 1 && anterior->ehDir){
                anterior->filho = cur_diretorio->irmao;
            }
            else{
                anterior->irmao = cur_diretorio->irmao;
            }
        }

        printf("Diretório %s foi apagado :)\n", diretorio);
    } 
    else {
        apaga_arquivos(cur_diretorio->filho);

        // Remover o diretório da lista de irmãos do diretório pai
        if (anterior == NULL) {
            // O diretório a ser excluído é o primeiro filho do diretório pai
            fs_geral->root->filho = cur_diretorio->irmao;
        } 
        else {
            if(flag_parentesco == 1){
                anterior->filho = cur_diretorio->irmao;
            }
            else{
                anterior->irmao = cur_diretorio->irmao;
            }
        }

        printf("Diretório %s e todo o seu conteúdo foram apagados :)\n", diretorio);
    }

    free(diretorio_copia);
    free(cur_diretorio);

    fs_geral->quant_dir--;
}

void mostra(char* arquivo){
    // Percorrer os tokens para encontrar o diretório correto
    char* path_auxiliar1 = strtok(arquivo, "/");
    char* path_auxiliar2 = path_auxiliar1;
    Arquivo* cur_arquivo = fs_geral->root;

    while(path_auxiliar2 != NULL){
        Arquivo* cur_auxiliar = cur_arquivo->filho;

        while(cur_auxiliar->irmao != NULL && strcmp(path_auxiliar1,cur_auxiliar->nome)){
            cur_auxiliar = cur_auxiliar->irmao;
        }

        cur_arquivo = cur_auxiliar;

        path_auxiliar1 = path_auxiliar2;
        path_auxiliar2 = strtok(NULL, "/");
    }

    while(strcmp(path_auxiliar1, cur_arquivo->nome) != 0 && cur_arquivo != NULL){
        cur_arquivo = cur_arquivo->irmao;
    }

    printf("%s \n%s\n", cur_arquivo->nome, cur_arquivo->conteudo);
}

void toca(char* arquivo){
    // Percorrer os tokens para encontrar o diretório correto
    char* save = (char*)malloc(sizeof(strlen(arquivo)+1));
    strcpy(save, arquivo);
    char* path_auxiliar1 = strtok(arquivo, "/");
    char* path_auxiliar2 = path_auxiliar1;
    Arquivo* cur_arquivo = fs_geral->root;
    Arquivo* anterior = fs_geral->root;

    int flag_parentesco = 1;

    while(path_auxiliar2 != NULL){
        Arquivo* cur_auxiliar = cur_arquivo->filho;
        anterior = cur_arquivo;
        flag_parentesco = 1;

        while(cur_auxiliar != NULL && strcmp(path_auxiliar2,cur_auxiliar->nome)){
            anterior = cur_auxiliar;
            cur_auxiliar = cur_auxiliar->irmao;
            flag_parentesco = 2;
        }
        
        cur_arquivo = cur_auxiliar;

        if(cur_auxiliar == NULL){
            break;
        }

        path_auxiliar1 = path_auxiliar2;
        path_auxiliar2 = strtok(NULL, "/");
    }

    while(cur_arquivo != NULL && strcmp(path_auxiliar1, cur_arquivo->nome) != 0){
        anterior = cur_arquivo;
        cur_arquivo = cur_arquivo->irmao;
        flag_parentesco=2;
    }

    // Se o arquivo existe, muda o instante do último acesso
    if(cur_arquivo != NULL){
        cur_arquivo->tempo_ult_acess = time(NULL);
    }   
    // Se o arquivo não existe, cria um novo arquivo vazio
    else{
        Arquivo* novo_arquivo = (Arquivo*)malloc(sizeof(Arquivo));
        char* nome_arq = strrchr(save, '/'); 
        if (nome_arq != NULL) {
            strcpy(novo_arquivo->nome, nome_arq+1); 
        } else {
            strcpy(novo_arquivo->nome, save);
        }
        novo_arquivo->irmao= NULL;
        novo_arquivo->filho= NULL;
        novo_arquivo->ehDir = 0;
        novo_arquivo->root = 0;
        novo_arquivo->tamanho_bytes = 0;
        novo_arquivo->tempo_criacao = time(NULL);
        novo_arquivo->tempo_ult_acess = novo_arquivo->tempo_criacao;
        novo_arquivo->tempo_ult_mod = novo_arquivo->tempo_criacao;
        novo_arquivo->conteudo = (char*)malloc(sizeof(char));
        strcpy(novo_arquivo->conteudo, "");

        if (fs_geral->espaco_livre < BLOCK_SIZE) {
            fprintf(stderr, "Espaço insuficiente no sistema de arquivos para criar um novo arquivo :(\n");
            return;
        }

        int bloco_atual = 0;
        while (bloco_atual < MAX_BLOCKS && fs_geral->bitmap[bloco_atual] != 0) {
            bloco_atual++;
        }

        if (bloco_atual == MAX_BLOCKS) {
            fprintf(stderr, "Não há blocos livres disponíveis para criar um novo arquivo :(\n");
            return;
        }

        fs_geral->bitmap[bloco_atual] = 1;
        fs_geral->fat[bloco_atual] = -1;
        fs_geral->espaco_livre -= BLOCK_SIZE;
        //novo_arquivo->bloco_inicio = bloco_atual;

        if(flag_parentesco == 1)
            anterior->filho = novo_arquivo;
        else
            anterior->irmao = novo_arquivo;

        fs_geral->quant_arq++;

        fs_geral->espaco_livre -= BLOCK_SIZE;
        fs_geral->espaco_desperdicado += BLOCK_SIZE;
    }
}

void apaga(char* arquivo){
    char* save = (char*)malloc(strlen(arquivo) + 1);
    strcpy(save, arquivo);

    // Percorrer os tokens para encontrar o diretório correto
    char* path_auxiliar1 = strtok(arquivo, "/");
    char* path_auxiliar2 = path_auxiliar1;
    Arquivo* cur_arquivo = fs_geral->root;
    Arquivo* anterior = cur_arquivo; 

    int flag_parentesco = 1;

    while(path_auxiliar2 != NULL){
        Arquivo* cur_auxiliar = cur_arquivo->filho;
        anterior = cur_arquivo;
        flag_parentesco = 1;

        // tem alguma função usando path_auziliar1, achar ela e ver se n da segfault
        while(cur_auxiliar->irmao != NULL && strcmp(path_auxiliar2,cur_auxiliar->nome)){
            anterior = cur_auxiliar;
            cur_auxiliar = cur_auxiliar->irmao;
            flag_parentesco = 2;
        }

        cur_arquivo = cur_auxiliar;

        path_auxiliar1 = path_auxiliar2;
        path_auxiliar2 = strtok(NULL, "/");
    }

    while(strcmp(path_auxiliar1, cur_arquivo->nome) != 0 && cur_arquivo != NULL){
        cur_arquivo = cur_arquivo->irmao;
        flag_parentesco = 2;
    }   

    Arquivo* aux = cur_arquivo->irmao; 

    if(flag_parentesco == 1){
        anterior->filho = aux;
    }
    else{
        anterior->irmao = aux;
    }

    printf("Arquivo %s apagado :)\n", save);

    libera_espaco(cur_arquivo);

    free(cur_arquivo->conteudo);
    free(cur_arquivo);

    fs_geral->quant_arq--;

}

void printa_recursivo(Arquivo *arq){
    if(arq == NULL)
        return;

    printf("    +\n");
    printf("    | Nome: %s%s\n", arq->nome, arq->ehDir && !arq->root ? "/" : "");
    printf("    +\n");
    printf("    | Tamanho: %d bytes\n", arq->tamanho_bytes);
    printf("    +\n");
    printf("    | Data de criação: %s", ctime(&(arq->tempo_criacao)));
    printf("    +\n");
    printf("    | Data de última modificação: %s", ctime(&(arq->tempo_ult_mod)));
    printf("    +\n");
    printf("    | Data de último acesso: %s", ctime(&(arq->tempo_ult_acess)));
    printf("    +\n");
    printf("-------------------------------------------------------------\n");
    printa_recursivo(arq->filho);
    printa_recursivo(arq->irmao);
}

void lista(char* diretorio){
    // Percorrer os tokens para encontrar o diretório correto
    char* path_auxiliar1 = strtok(diretorio, "/");
    char* path_auxiliar2 = path_auxiliar1;
    Arquivo* cur_diretorio = fs_geral->root;

    if(strcmp(diretorio, "/") !=0){
        while(path_auxiliar2 != NULL){
            Arquivo* cur_auxiliar = cur_diretorio->filho;

            while(cur_auxiliar->irmao != NULL && strcmp(path_auxiliar1,cur_auxiliar->nome)){
                cur_auxiliar = cur_auxiliar->irmao;
            }

            cur_diretorio = cur_auxiliar;

            path_auxiliar1 = path_auxiliar2;
            path_auxiliar2 = strtok(NULL, "/");
        }

        while(strcmp(path_auxiliar1, cur_diretorio->nome) != 0 && cur_diretorio != NULL){
            cur_diretorio = cur_diretorio->irmao;
        }    
    }

    Arquivo* cur_arquivo = cur_diretorio->filho;

    printf("-------------------------------------------------------------\n");
    printa_recursivo(cur_arquivo);

    //printa_recursivo(cur_diretorio);
}

void apagadb_recursivo(Banco_de_dados* bd){
    if(bd==NULL)    
        return;

    apagadb_recursivo(bd->filho);
    apagadb_recursivo(bd->irmao);

    free(bd->nome);
    free(bd);
}

Banco_de_dados* atualizadb_recursivo(Arquivo *arq){
    if(arq == NULL)
        return NULL;
    
    Banco_de_dados *aux = (Banco_de_dados*)malloc(sizeof(Banco_de_dados)*1);
    aux->nome = (char*)malloc(sizeof(char)*sizeof(arq->nome)+1);
    strcpy(aux->nome, arq->nome);

    aux->irmao = atualizadb_recursivo(arq->irmao);
    aux->filho = atualizadb_recursivo(arq->filho);

    return aux;
}

void atualizadb(){
    apagadb_recursivo(bd_geral);    

    // Sempre cria um banco de dados novo
    bd_geral = (Banco_de_dados*)malloc(sizeof(Banco_de_dados));

    bd_geral->nome = (char*)malloc(sizeof(char)*2);
    strcpy(bd_geral->nome,"/");

    bd_geral->irmao = NULL;
    bd_geral->filho = atualizadb_recursivo(fs_geral->root->filho);
}

void busca_recursivo(Banco_de_dados* bd, const char* string, char* caminho_atual){
    if(bd == NULL) 
    return;

    // Adicionar o nome atual ao caminho
    char* novo_caminho = (char*)malloc(strlen(caminho_atual) + strlen(bd->nome) + 2);
    sprintf(novo_caminho, "%s/%s", caminho_atual, bd->nome);

    // Verificar se o nome contém a string de busca
    if (strstr(bd->nome, string) != NULL) {
        printf("%s\n", novo_caminho);
    }

    busca_recursivo(bd->filho, string, novo_caminho);
    busca_recursivo(bd->irmao, string, caminho_atual);

    free(novo_caminho);
}

void busca(const char* string){
    if(bd_geral == NULL){
        printf("Não há banco de dados para realizar a busca :(\n");
        return;
    }

    char aux[1] = "";
    busca_recursivo(bd_geral->filho, string, aux);
}

void status(){
    printf("    +\n");
    printf("    | Quantidade de diretórios: %d\n", fs_geral->quant_dir);
    printf("    +\n");
    printf("    | Quantidade de arquivos: %d\n", fs_geral->quant_arq);
    printf("    +\n");
    printf("    | Espaço livre: %ld bytes\n", fs_geral->espaco_livre);
    printf("    +\n");
    printf("    | Espaço desperdiçado: %ld bytes\n", (fs_geral->espaco_desperdicado%BLOCK_SIZE));
    printf("    +\n");
}

void libera_arvore(Arquivo *arq){
    if (arq == NULL) return;

    libera_arvore(arq->filho);
    libera_arvore(arq->irmao);

    free(arq);
}

void desmonta(){
    if (fs_geral == NULL) {
        printf("Nenhum sistema de arquivos montado para desmontar :(\n");
        return;
    }

    //atualizadb();

    free(fs_geral->nome);
    for(int i=0; i<MAX_BLOCKS; i++){
        fs_geral->fat[i] = -1;
        fs_geral->bitmap[i] = 0;
    }

    libera_arvore(fs_geral->root);

    free(fs_geral);

    fs_geral = NULL;

    printf("Sistema de arquivos desmontado :)\n");  
}

void sai(){
    exit(0);
}

void main_loop(){
    static char *line_read = (char *)NULL;

    using_history();  

    char prompt[8] = "{ep3}: ";

    while((line_read = readline(prompt))){

        add_history(line_read);

        char *firstArg = strtok(line_read, " ");

        // PARA O TESTE DE MEDIÇÃO DE TEMPO
        /*
        clock_t start_time, end_time;
        double elapsed_time;

        start_time = clock();
        */

        if(!strcmp(firstArg, "monta")){
            
            char* arquivo = strtok(NULL, " ");

            monta(arquivo);

        }
        else if(!strcmp(firstArg, "sai")){

            sai();

        }
        else if(fs_geral==NULL){
            printf("Não há sistema de arquivos montado :(\n");
        }
        else if(!strcmp(firstArg, "copia")){

            char* origem = strtok(NULL, " ");
            char* destino = strtok(NULL, " ");
            copia(origem, destino);
        
        }
        else if(!strcmp(firstArg, "criadir")){

            char* diretorio = strtok(NULL, " ");
            criadir(diretorio);

        }
        else if(!strcmp(firstArg, "apagadir")){

            char* diretorio = strtok(NULL, " ");
            apagadir(diretorio);

        }
        else if(!strcmp(firstArg, "mostra")){

            char* arquivo = strtok(NULL, " ");
            mostra(arquivo);

        }
        else if(!strcmp(firstArg, "toca")){

            char* arquivo = strtok(NULL, " ");
            toca(arquivo);
        
        }
        else if(!strcmp(firstArg, "apaga")){

            char* arquivo = strtok(NULL, " ");
            apaga(arquivo);

        }
        else if(!strcmp(firstArg, "lista")){

            char* diretorio = strtok(NULL, " ");
            lista(diretorio);

        }
        else if(!strcmp(firstArg, "atualizadb")){

            atualizadb();

        }
        else if(!strcmp(firstArg, "busca")){

            char* str = strtok(NULL, " ");
            busca(str);

        }
        else if(!strcmp(firstArg, "status")){

            status();

        }
        else if(!strcmp(firstArg, "desmonta")){

            desmonta();

        }
        else
            printf("{ep3}: comando não encontrado: %s\n", firstArg);

        free(line_read);

        if(fs_geral != NULL)
            salva_sistema_de_arquivos(fs_geral, fs_geral->nome);

        // PARA O TESTE DE MEDIÇÃO DE TEMPO
        /*
        end_time = clock();
        elapsed_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
        printf("Tempo de execução: %.9f segundos\n", elapsed_time);
        */


        // Para testes -> comentar para realizar a entrega
        //if(fs_geral != NULL)
        //    printa_arvore(fs_geral->root, 0, 1);
    }

}

int main(){

    main_loop();

    return 0;
}