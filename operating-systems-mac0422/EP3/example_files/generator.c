/* Gerador de comandos que o Ivan Gabriel Ferreira Dias fez para o exercício-programa */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc < 4) {
    printf("Uso: %s <profundidade> <arquivos_por_nivel> <saida>\n", argv[0]);
    return 1;
  }
  if (strcmp(argv[3], "generator.c") == 0) {
    printf("Olha a besteira!\n");
    return 1;
  }
  FILE *fs = fopen(argv[3], "w+");

  long profundidade = strtol(argv[1], NULL, 10);
  long largura = strtol(argv[2], NULL, 10);

  char *caminho = calloc(3 * (profundidade + 1), sizeof(char));
  caminho[0] = '/';

  char *comando;
  int diretorios = 0;
  for (int i = 33; diretorios < profundidade && i < 127; i++) {
    if ((char)i == '/' || (char)i == '.' || i == '"' || i == '\'')
      continue;
    comando =
        calloc(strlen("criadir ") + 1 + strlen(caminho) + 4, sizeof(char));

    strcat(comando, "criadir ");
    caminho[strlen(caminho)] = (char)i;
    strcat(comando, caminho);
    strcat(comando, "\n");
    caminho[strlen(caminho)] = '/';

    fwrite(comando, strlen(comando), sizeof(char), fs);
    diretorios++;
  }

  if (largura > 0) {
    memset(caminho + 1, 0, 3 * (profundidade + 1) - 1);

    int posicao_letra = strlen(caminho);
    int dir_lidos = 0;
    for (int i = 32; dir_lidos < diretorios + 1; i++) {
      if (i + 1 == '/' || i + 1 == '.' || i + 1 == '"' || i + 1 == '\'')
        continue;
      int arquivos_criados = 0;
      for (int j = 33; arquivos_criados < largura && j < 127; j++) {
        if (j == '/' || j == '"' || j == '\'')
          continue;
        for (int k = 33; arquivos_criados < largura && k < 127; k++) {
          if (k == '/' || (j == '.' && k == '.') || k == '"' || k == '\'')
            continue;
          comando =
              calloc(strlen("toca ") + 1 + strlen(caminho) + 4, sizeof(char));

          strcat(comando, "toca ");
          caminho[posicao_letra] = (char)j;
          caminho[posicao_letra + 1] = (char)k;
          strcat(comando, caminho);
          strcat(comando, "\n");

          fwrite(comando, strlen(comando), sizeof(char), fs);
          arquivos_criados++;
        }
      }
      caminho[strlen(caminho) - 2] = (char)(i + 1);
      caminho[strlen(caminho) - 1] = '/';
      //      strcat(caminho, "/");
      posicao_letra = strlen(caminho);
      dir_lidos++;
    }
  }
  fclose(fs);
  free(caminho);
  return 0;
}
