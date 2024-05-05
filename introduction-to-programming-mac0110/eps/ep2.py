def distancia(P1, P2):
    '''(ponto, ponto) -> float

    Recebe dois pontos P1=[x1, y1] e P2=[x2, y2] e
    retorna a distância entre P1 e P2. 

    Exemplos:
    >>> distancia([1,1],[0,0])
    1.4142135623730951
    >>> distancia([1,0],[1,1])
    1.0
    >>> distancia([0,1],[1,1])
    1.0
    '''
    
    # fórmula da distância entre dois pontos em um plano cartesiano
    
    dist_x = P2[0] - P1[0];
    
    dist_y = P2[1] - P1[1];
    
    
    dist = (dist_x**2 + dist_y**2)**(0.5);
    
    return dist;


def aceleracaoGravitacional(Astro, P):
    '''(astro, ponto) -> [float,float]

    Recebe um astro = [[x_a,y_a],massa_a,...] e um ponto 
    P = [x,y], onde
 
        - [x_a,y_a] é a posição de um astro celeste;
        - massa_a   é a massa de um astro celeste; e
        - [x, y]    é a posição de um objeto.

    Retorna o vetor aceleração [a_x,a_y] da força gravitacional 
    exercida pelo astro sobre um objeto no ponto [x,y].

    Exemplos:
    >>> aceleracaoGravitacional([[0,0],5.97e+24], [300000,300000])
    [-20.286304296591066, -20.286304296591066]
    >>> aceleracaoGravitacional([[0,0],5.97e+24],[6563,0])
    [-119890.73704206462, -0.0]
    >>> aceleracaoGravitacional([[0,0],5.97e+24],[0,6563])
    [-0.0, -119890.73704206462]
    >>> aceleracaoGravitacional([[0,0],5.97e+24],[30000,0])
    [-5737.833333333336, -0.0]
    >>> aceleracaoGravitacional([[0,0],5.97e+24],[90000,0])
    [-637.5370370370372, -0.0]
    >>> aceleracaoGravitacional([[0,0],5.97e+24],[180000,0])
    [-159.3842592592593, -0.0]
    '''
    
    # EQUAÇÃO (4)
    # EQUAÇÃO DO VETOR UNITÁRIO
    
    # constante gravitacional: seu valor aproximado
    G = 8.65e-13;
    
    # distância da ponto P ao centro do Astro
    r_A = distancia(Astro[0], P);
    
    # vetor unitário da direção que vai do ponto P ao Astro
    r_T_chapeu = [(Astro[0][0]-P[0])/r_A, (Astro[0][1]-P[1])/r_A];
    
    # aceleração
    ac =  (G * Astro[1])/(r_A**2);
    
    return [ac*r_T_chapeu[0], ac*r_T_chapeu[1]] ;
    

def aceleracaoResultante(Astros, P):
    '''(lista de astros, ponto) -> [float,float]

    Recebe em 'Astros' uma lista de astros celestes e um
    ponto P = [x,y] e retorna o vetor aceleração [a_x,a_y] da força
    gravitacional exercida pelos astros sobre um objeto no ponto.

    Cada item da lista representa um astro. A parte relevante de cada 
    item tem a forma

        [[x_a,y_a],massa_a,...] 

    onde:
        - [x_a,y_a] é a posição do astro; e
        - massa_a   é a sua massa.

    Esta função DEVE utilizar a função aceleracaoGravitacional.

    Exemplos:
    >>> aceleracaoResultante([[[0,0],5.97e+24], [[384400,0],7.35e+22]], [192200,0])
    [-138.0713730386207, 0.0]
    >>> aceleracaoResultante([[[0,0],8.97e+22], [[100000,0],5e+21]], [80000,0])
    [-1.3110156249999996, 0.0]
    >>> aceleracaoResultante([[[0, 0],8.0e+22], [[100000,0], 5e+21]], [80000,0])
    [0.0, 0.0]
    '''
    
    # EQUAÇÃO 7, a aceleração resultante da nave é calculada como a soma das constribuições exercidas por cada astro
    
    ac_total_x = 0.0;
    ac_total_y = 0.0;
    
    for astro in Astros:
        ac_x, ac_y= aceleracaoGravitacional(astro, P);
        ac_total_x+=ac_x;
        ac_total_y+=ac_y;
        
    
    return [ac_total_x, ac_total_y];
    

def deteccaoColisao(Nave, Astros):
    '''(nave, lista de astros) -> bool

    Recebe:
    - uma nave através de 'Nave = [[x,y],[vx,vy],raio]' e
    - uma lista de astros através de 'Astros'

    e retorna True se a nave colidiu com algum astro,
    caso contrário a função retorna False.  
 
    Pré-condição: 
        A função supõe que a nave está ativa.   
    '''
    
    for astro in Astros:
        n_raio = Nave[2]
        a_raio = astro[2]
        
        # Verifica a distância entre a nave e o astro
        d = distancia(Nave[0], astro[0])
        
        # Verifica se houve colisão
        if d-(n_raio + a_raio) <= 0:
            return True
        
    return False


def atualizaNave(Nave, Astros, delta_t):
    '''(nave, lista de astros, número) -> None

    Recebe 
        - uma nave através de 'Nave',
        - uma lista de astros através de 'Astros'
        - um intervalo de tempo 'delta_t'

    A nave é representada através de uma lista que tem 
    a forma

        [[x_t,y_t], [vx_t,vy_t], raio]

    onde:
        - [x_t,y_t]     é a posição da nave em um instante t
        - [vx_t,vy_t]   é a velocidade da nave em um instante t
        - raio          indica o raio da nave

    Esta função deve calcular a posição e velocidade da nave no 
    instante t+delta_t e atualizá-las.

    Está função DEVE usar a função 'aceleracaoResultante'.

    Pré-condição: 
        A função supõe que a nave está ativa.
    '''
    
    posicao_atual = Nave[0]
    velocidade_atual = Nave[1]
    
    aceleracao = aceleracaoResultante(Astros, posicao_atual)
    
    # EQUAÇÃO (9)
    # x' = x + v Delta_t + (a Delta_t^2)/2 
    nova_posicao = [
        posicao_atual[0] + velocidade_atual[0] * delta_t + 0.5 * aceleracao[0] * delta_t ** 2,
        posicao_atual[1] + velocidade_atual[1] * delta_t + 0.5 * aceleracao[1] * delta_t ** 2
    ]
    
    # EQUAÇÃO (10)
    # v' = v + a Delta_t
    nova_velocidade = [
        velocidade_atual[0] + aceleracao[0] * delta_t,
        velocidade_atual[1] + aceleracao[1] * delta_t
    ]
    
    Nave[0] = nova_posicao
    Nave[1] = nova_velocidade
    
    return None

    
def distanciaAstroMaisProximo(Nave, Astros):
    '''(nave, lista de astros) -> float

    Recebe: 
        - uma nave em 'Nave',
        - uma lista de astros em 'Astros'

    Devolve:
        - a distância da nave em relação ao astro mais próximo.
          A distância deve ser medida em relação a superfície do astro e da nave.
          Em caso de nave colidida, a distância deve ser zero.
    '''
    # infinito: pode usar um valor muito grande também
    menor_distancia = float('inf')
    
    for astro in Astros:
        distancia_nave_astro = distancia(Nave[0], astro[0]) - Nave[2] - astro[2]
        
        # precisa ser em relação ao astro mais próximo
        if distancia_nave_astro < menor_distancia:
            menor_distancia = distancia_nave_astro
    
    # colidiu
    if menor_distancia < 0:
        return 0.0
    else:
        return menor_distancia


def simulacao(Naves, Astros, niter, delta_t):
    '''(lista de naves, lista de astros, int, float) -> (Trajetorias, Distancias)

    Recebe: 
        - uma lista de naves em 'Naves',
        - uma lista de astros em 'Astros',
        - o número de iterações 'niter' da simulação,
        - intervalo de tempo 'delta_t'

    e simula as trajetórias das naves em 'Naves'
    sob o efeito da força gravitacional exercida pelos
    astros em 'Astros'. 

    Devolve:
        - Trajetorias: Uma lista [T1, T2, ..., Tn] das trajetórias
                       de cada nave, sendo n o número total de naves.
                       Cada trajetória Ti é por sua vez uma lista das
                       posições da i-ésima nave ao longo da simulação.
        - Distancias:  Uma lista [D1, D2, ..., Dn], em que n é
                       o número total de naves e Di representa
                       uma lista com as distâncias da i-ésima nave
                       em relação ao seu astro mais próximo a cada iteração.

    O instante inicial da simulação é zero e a cada 
    passo da simulação o tempo de simulação é acrescido
    de 'delta_t'. 

    As posições das naves serão atualizadas em cada passo da 
    simulação. Uma nave será desativada assim que colodir
    com algum astro. Neste caso a nave conserva a posição
    em que ocorreu a colisão ao longo das próximas iterações.

    Não serão consideradas colisões entre naves.

    A simulação termina quando o número de iterações
    executadas atingir 'niter'.

    Esta função DEVE usar as funções 'atualizaNave',
    'deteccaoColisao' e 'distanciaAstroMaisProximo'.

    Exemplos:
     >>> simulacao([[[20000,0],[0,0],500], [[0,25000],[100,-200],200]], [[[0,0],5.97e+24, 5000], [[384400,0],7.35e+22, 4000]], 2, 1)
    ([[[13545.176895903343, 0.0], [-13437.380528213638, 0.0]], [[100.21377507987808, 20668.746096834035], [171.5514201156242, 6162.332357329415]]], [[8045.176895903343, 7937.380528213638], [15468.989041946581, 964.7197804874131]])
    '''
    
    trajetorias = []
    distancias = []
    
    # Simula para cada uma das naves
    for nave in Naves:
        
        # Inicializa as variáveis
        trajetoria_nave = []
        distancia_nave = []
        
        # Itera pera quantidade de iterações
        for i in range(0, niter):
            
            # Se teve colisão então só copia até o fim da simulação dessa nave
            if deteccaoColisao(nave, Astros):
                # Copia a posição atual da nave
                trajetoria_nave.append(nave[0][:]) 
                # Coloca a distância ao astro mais próximo como 0 (colisão)
                distancia_nave.append(0.0)
                continue
            else:
                atualizaNave(nave, Astros, delta_t)
                trajetoria_nave.append(nave[0][:])
                distancia_nave.append(distanciaAstroMaisProximo(nave, Astros))
        
        # Colona na lista de saída
        trajetorias.append(trajetoria_nave)
        distancias.append(distancia_nave)
    
    return trajetorias, distancias



#Não altere o código abaixo:
def main():
    
    '''Já realiza a leitura de todos os dados conforme especificado no enunciado'''
    
    niter = int(input("Número máximo de iterações: "))    
    delta_t = float(input("Delta t: "))
    nnaves = int(input("Número de naves: "))
    Naves = []
    for i in range(nnaves):
        print("*** Nave %d ***"%(i+1))
        x,y = input("Digite a posição (x,y): ").split()
        x,y = float(x),float(y)
        vx,vy = input("Digite a velocidade inicial (vx,vy): ").split()
        vx,vy = float(vx),float(vy)
        r = float(input("Digite o raio: "))
        Naves.append([[x,y], [vx,vy], r])

    nastros = int(input("Número de astros: "))
    Astros = []
    for i in range(nastros):
        print("*** Astro %d ***"%(i+1))
        x,y = input("Digite a posição (x,y): ").split()
        x,y = float(x),float(y)
        massa = float(input("Digite a massa: "))
        R = float(input("Digite o raio: "))        
        Astros.append([[x,y], massa, R])
        
        
    ##################################################################################

    T, D = simulacao(Naves, Astros, niter, delta_t)
    for i in range(niter):
        print("********* iteração %d *********"%(i+1))
        for j in range(nnaves):
            print("*** Nave %d ***"%(j+1))
            print("Posição: ",end="")
            P = T[j][i]
            print("(%.3f,%.3f)"%(P[0],P[1]))
            print("Distância ao astro mais próximo: ",end="")
            print("%.3f"%(D[j][i]))



#Não altere o código abaixo.
#O propósito do comando condicional abaixo será explicado em aula 
#em um momento oportuno. Sem o seu uso, o corretor do VPL não irá 
#funcionar adequadamente.
if __name__ == "__main__":
    main()
'''
TESTES

print(aceleracaoGravitacional([[0,0],5.97e+24], [300000,300000]))
print(aceleracaoGravitacional([[0,0],5.97e+24],[6563,0]))
print(aceleracaoGravitacional([[0,0],5.97e+24],[0,6563]))
print(aceleracaoGravitacional([[0,0],5.97e+24],[30000,0]))
print(aceleracaoGravitacional([[0,0],5.97e+24],[90000,0]))
print(aceleracaoGravitacional([[0,0],5.97e+24],[180000,0]))

print(aceleracaoResultante([[[0,0],5.97e+24], [[384400,0],7.35e+22]], [192200,0]))
print(aceleracaoResultante([[[0,0],8.97e+22], [[100000,0],5e+21]], [80000,0]))
print(aceleracaoResultante([[[0, 0],8.0e+22], [[100000,0], 5e+21]], [80000,0]))

print(distancia([1,1],[0,0]))
print(distancia([1,0],[1,1]))
print(distancia([0,1],[1,1]))

print(simulacao([[[20000,0],[0,0],500], [[0,25000],[100,-200],200]], [[[0,0],5.97e+24, 5000], [[384400,0],7.35e+22, 4000]], 2, 1))
#print(simulacao([[[20000,0],[0,0],500]], [[[0,0],5.97e+24, 5000], [[384400,0],7.35e+22, 4000]], 2, 1))
'''
