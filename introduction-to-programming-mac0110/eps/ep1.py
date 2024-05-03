# define o valor inicial das variáveis
entrada = -1
esp_ini = -1
esp_fim = -1
delta_s = 0
segundos = 0
bpm_max = 0

print("digite (ou copie e cole) os dados do seu gps linha por linha e termine com a linha 000:")

# pega os dados de entrada
while entrada != 0:
    entrada = int(input())
    
    if(entrada != 0):
        segundos+=1

        esp_fim = entrada/1000
        if(esp_ini != -1):
            dist = esp_fim-esp_ini
            if dist < 0:
                dist=-dist
                
            delta_s += dist
            
        esp_ini = esp_fim
            
        aux = entrada % 1000
        
        if aux>bpm_max:
            bpm_max = aux
        

# calcula idade e velocidade média
idade = 220 - bpm_max
v_media = delta_s//(segundos-1)
print(v_media)

# define equipe 
equipe = ""

if v_media >= 4:
    equipe = "QUENIA"
elif v_media >= 2:
    equipe = "AZUL"
else:
    equipe = "BRANCO"
    
# calcula se é número abundante
n_abundante=0
i = 1

while i<=bpm_max/2:
    if bpm_max%i == 0:
        n_abundante+=i
    
    i+=1

# printa os resultados
print("##### seguem as suas estatisticas #####")

if idade >= 10:
    print("sua idade de aptidao fisica eh:", idade)
else: 
    print("sua idade de aptidao fisica nao pode ser calculada")

print("seu pelotao eh o", equipe)

if n_abundante>bpm_max:
    print("parabens! voce terah desconto na inscricao da prova! \o/\o/\o/")