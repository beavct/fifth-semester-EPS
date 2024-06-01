"""
  AO PREENCHER ESSE CABEÇALHO COM O MEU NOME E O MEU NÚMERO USP, 
  DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESSE PROGRAMA. 
  TODAS AS PARTES ORIGINAIS DESSE EXERCÍCIO PROGRAMA (EP) FORAM 
  DESENVOLVIDAS E IMPLEMENTADAS POR MIM SEGUINDO AS INSTRUÇÕES
  DESSE EP E QUE PORTANTO NÃO CONSTITUEM DESONESTIDADE ACADÊMICA
  OU PLÁGIO.  
  DECLARO TAMBÉM QUE SOU RESPONSÁVEL POR TODAS AS CÓPIAS
  DESSE PROGRAMA E QUE EU NÃO DISTRIBUI OU FACILITEI A
  SUA DISTRIBUIÇÃO. ESTOU CIENTE QUE OS CASOS DE PLÁGIO E
  DESONESTIDADE ACADÊMICA SERÃO TRATADOS SEGUNDO OS CRITÉRIOS
  DIVULGADOS NA PÁGINA DA DISCIPLINA.
  ENTENDO QUE EPS SEM ASSINATURA NÃO SERÃO CORRIGIDOS E,
  AINDA ASSIM, PODERÃO SER PUNIDOS POR DESONESTIDADE ACADÊMICA.

  Nome :
  NUSP :
  Prof.:

  Referências: Com exceção das rotinas fornecidas no enunciado
  e em sala de aula, caso você tenha utilizado alguma refência,
  liste-as abaixo para que o seu programa não seja considerado
  plágio ou irregular.
"""
import random
import unicodedata

MAX_TENTATIVAS = 6
NUM_LETRAS = 5


def main():
    ' Implementa mecanismo principal do jogo. '   
    # pede opção de lingua
    lingua = ''
    while lingua != 'P' and lingua != 'I':
        lingua = input("Qual o idioma (I para inglês ou P para português)? ")
    
    # carrega lista de palavras do arquivo correspondente
    if lingua == 'P':
        # completar
        lista_palavras = cria_lista_palavras("palavras.txt")
    elif lingua =='I':
        # completar
        lista_palavras = cria_lista_palavras("words.txt")

    # sorteia uma palavra da lista
    palavra = lista_palavras[random.randint(0,len(lista_palavras)-1)]
    
    num_tentativas = 0
    lista_tentativas = []
    ganhou = False
    teclado =  inicializa_teclado()

    while num_tentativas < MAX_TENTATIVAS and not ganhou:
        imprime_teclado(teclado)
        
        chute = remove_acentos(input("Digite a palavra : ").lower())
        
        feedback = checa_tentativa(palavra, chute)
        
        while chute not in lista_palavras or len(chute)!=NUM_LETRAS:
            print("Palavra inválida!")
            chute = remove_acentos(input("Digite a palavra : ").lower())
            feedback = checa_tentativa(palavra, chute)
            
        
        lista_tentativas.append([chute, feedback])
        
        imprime_resultado(lista_tentativas)
        
        atualiza_teclado(chute, feedback, teclado)
                
        errou=False
        for num in feedback:
            if num != 1:
                errou=True
                break
                
        if not errou:
            ganhou=True
            
        num_tentativas+=1
            

    if ganhou: 
       print("PARABÉNS!")
    else: 
       print("Que pena... A palavra era",palavra,".")


##### FUNÇÕES PRONTAS #####

def inicializa_teclado():
    '''
    Devolve a lista com as teclas na ordem.
    As letras que aparecem nos chutes e que não estão no teclado são substtuídas por ' '.
    '''
    
    teclado = [['q','w','e','r','t','y','u','i','o','p'],
               ['a','s','d','f','g','h','j','k','l'],
               ['z','x','c','v','b','n','m']]
    return teclado


def imprime_teclado(teclado):
    ''' Exibe o teclado com as letras possiveis. '''   
    print('-----------------------------------------')
    for linha in teclado:
        for letra in linha:
            print(letra, end = ' ')
        print()
    print('-----------------------------------------')


##### FUNÇÕES OBRIGATÓRIAS #####


def cria_lista_palavras(nome_arquivo):
    ''' recebe uma string com o nome do arquivo e devolve uma lista
        contendo as palavras do arquivo'''
    # fazer
    
    arq = open(nome_arquivo, "r")
    lista = arq.readlines()
    arq.close()
    
    lista_palavras=[]
    
    # se não tirar o espaço da erro
    for palavra in lista:
        lista_palavras.append(remove_acentos(palavra.strip().lower()))
    
    return lista_palavras



def checa_tentativa(palavra,chute):
    ''' Recebe a `palavra` secreta e o `chute` do usuario e devolve
     uma lista ‘feedback’ de 5 elementos para indicar acertos e erros. 
     A lista `feedback` deve conter o 
     valor 1 (verde) se a letra correspondente em `chute` ocorre na mesma posicao
     em `palavra` (letra certa no lugar certo), deve conter 2 se a letra 
     em `chute` ocorre em outra posicao em `palavra` (letra certa no lugar errado),
     e deve conter 0 caso contrario. '''
    # fazer
    
    feedback = []
    for i, letra in enumerate(chute):
        if letra == palavra[i]:
            feedback.append(1)
        elif letra in palavra:
            feedback.append(2)
        else:
            feedback.append(0)
    return feedback

    
def  imprime_resultado(lista):
    ''' Recebe a lista de tentativas e imprime as tentativas,
      usando * para verde , + para amarelo e _ para letras que não aparecem na 
      palavra sorteada. A lista de tentativas tem formato 
      [[chute1, feedback1], [chute2, feedback2], …, [chuten,feedbackn]. 
      Esta funcao nao devolve valor. '''
    
    for [chute, feedback] in lista:
        print(chute)
        
        f_aux=""
        
        for num in feedback:
            if num == 0:
                f_aux+="_ "
            elif num == 1:
                f_aux+="* "
            else:
                f_aux+="+ "
            
        print(f_aux)

            

def atualiza_teclado(chute, feedback, teclado):
    ''' Modifica teclado para que as letras marcadas como inexistentes
	 no chute sejam substituidas por espacos. Esta funcao nao devolve valor.'''
    # fazer
    for i, letra in enumerate(chute):
        if feedback[i] == 0:
            # tem q olhar todas as linhas
            for linha in teclado:
                if letra in linha:
                    linha[linha.index(letra)] = " "
    

##### FUNÇÕES EXTRAS (caso existam) #####

#peguei do gabarito
# aparemente nos teste s não foram utilizadas entradas com acento
def remove_acentos(palavra):
    'Remove caracteres nao ASCii.'
    return ''.join(c for c in unicodedata.normalize('NFD', palavra)
                  if unicodedata.category(c) != 'Mn')    
    # nova_palavra = ''
    # for letra in palavra:
    #     if letra in 'áàâã': nova_palavra+='a'
    #     elif letra in 'éê': nova_palavra+='e'
    #     elif letra == 'í': nova_palavra+='i'
    #     elif letra in 'óôõ': nova_palavra+='o'
    #     elif letra in 'úü': nova_palavra+='u'
    #     elif letra == 'ç': nova_palavra+='c'
    #     else: nova_palavra+=letra
    # return nova_palavra

##### NÃO ALTERE O TRECHO ABAIXO #####
if __name__ == "__main__":
    main()
