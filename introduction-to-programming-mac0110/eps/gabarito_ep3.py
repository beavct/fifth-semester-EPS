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
        lista_palavras = cria_lista_palavras('palavras.txt')
    elif lingua =='I':
        lista_palavras = cria_lista_palavras('words.txt')

    # sorteia uma palavra da lista
    palavra = lista_palavras[random.randint(0,len(lista_palavras)-1)]
    num_tentativas = 0
    lista_tentativas = []
    ganhou = False
    teclado =  inicializa_teclado()
	
    while num_tentativas < MAX_TENTATIVAS and not ganhou:
        # completar
        imprime_teclado(teclado)
        chute = input("Digite a palavra: ")
        chute = remove_acentos(chute.lower())
        #if chute == palavra:
        #    ganhou = True
        while chute not in lista_palavras:
            print("Palavra inválida!")
            chute = input("Digite a palavra: ")
            chute = remove_acentos(chute.lower())
         # modifica marca
        feedback = checa_tentativa(palavra,chute) 
        lista_tentativas.append([chute, feedback])
        imprime_resultado(lista_tentativas)   
        atualiza_teclado(chute,feedback,teclado)
        num_tentativas += 1
        if chute == palavra:
            ganhou = True        
    if ganhou: 
       print("PARABÉNS!")
    else: 
       print("Que pena... A palavra era",palavra,".")
# funcao auxiilar adicional
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

def cria_lista_palavras(nome_arquivo):
    ''' recebe uma string com o nome do arquivo e devolve uma lista
        contendo as palavras do arquivo'''
    # fazer
    palavras = []
    with open(nome_arquivo) as a:
        for line in a:
            l = line.split()
            for p in l:
                palavras.append(remove_acentos(p.lower()))
    return palavras


def inicializa_teclado():
    '''
    Devolve a lista com as teclas na ordem.
    As letras que aparecem nos chutes e que não estão no teclado são substtuídas por ' '.
    '''
    
    teclado = [['q','w','e','r','t','y','u','i','o','p'],
               ['a','s','d','f','g','h','j','k','l'],
               ['z','x','c','v','b','n','m']]
    return teclado

        

def checa_tentativa(palavra,chute):
    ''' Recebe a `palavra` secreta e o `chute` do usuario e modifica as
     `marca`s para indicar acertos e erros. A lista `marca` deve conter o 
     valor 1 (verde) se a letra correspondente em `chute` ocorre na mesma posicao
     em `palavra` (letra certa no lugar certo), deve conter 2 se a letra 
     em `chute` ocorre em outra posicao em `palavra` (letra certa no lugar errado),
     e deve conter 0 caso contrario (letra errada). Esta funcao nao devolve valor. '''
    # fazer
    marca = [0,0,0,0,0]
    for i in range(len(palavra)):
            if palavra[i]==chute[i]:
                marca[i] = 1  # verde
            else:
                achou = 0
                j = 0
                while j < len(palavra) and achou == 0:
                    if palavra[i]==chute[j] and marca[j]==0:
                        marca[j] = 2 # amarela
                        achou = 1
                    j += 1
    return marca

def  imprime_resultado(lista):
    ''' Recebe a lista de tentativas e imprime as tentativas,
      usando * para verde e + para amarelo. '''
    #fazer
    for tentativa in lista:
        for i in tentativa[0]: #a palavra chutada
            print(i,end=' ')
        print()
        for i in tentativa[1]: #a marcação de acertos
            if i == 0: print ("_",end=' ')
            elif i == 1: print ("*",end=' ') #verde
            elif i == 2: print ("+",end=' ') #amarelo
        print()

def imprime_teclado(teclado):
    ''' Exibe o teclado com as letras possiveis. '''   
    print('-----------------------------------------')
    for linha in teclado:
        for letra in linha:
            print(letra, end = ' ')
        print()
    print('-----------------------------------------')
            

def atualiza_teclado(chute,marca,teclado):
    ''' Modifica teclado para que as letras marcadas como inexistentes
	 no chute sejam substituidas por espacos. '''
    # fazer
    for i in range(len(marca)):
        apaga = True
        if marca[i] == 0:
            #verifica se a letra não aparece nenhuma outra vez antes de apagar 
            for j in range(len(marca)):
                if chute[j]==chute[i] and marca[j]!=0:
                    apaga = False
            if apaga:    
                for linha in teclado:
                    for j in range(len(linha)):
                        if linha[j] == chute[i]:
                            linha[j] = ' '
                            break

if __name__ == "__main__":
    main()