import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import t

# Carrega os dados do CSV para um DataFrame
data = pd.read_csv('ex.csv', names=['Memoria', 'Tempo'])

# Calcula a média de cada coluna
mean_memoria = data['Memoria'].mean()
mean_tempo = data['Tempo'].mean()

# Calcula o desvio padrão de cada coluna
std_memoria = data['Memoria'].std()
std_tempo = data['Tempo'].std()

# Calcula o intervalo de confiança de 95% para a média de cada coluna
n = len(data)
t_value = t.ppf(0.975, df=n-1)
ci_memoria = t_value * std_memoria / np.sqrt(n)
ci_tempo = t_value * std_tempo / np.sqrt(n)

# Define os dados para o gráfico de barras
labels = ['Memoria', 'Tempo']
means = [mean_memoria, mean_tempo]
cis = [ci_memoria, ci_tempo]

print(cis)

# Define a largura das barras
#bar_width = 0.3
#x = np.arange(len(labels))
#
## Plota o gráfico de barras
#fig, ax = plt.subplots()
#bars1 = ax.bar(x - bar_width/2, means, bar_width, yerr=cis, label='Média com Intervalo de Confiança de 95%', color=['blue', 'red'])
#
## Adiciona rótulos e títulos
#ax.set_ylabel('Valores')
#ax.set_title('Uso de Memória e Tempo de Execução')
#ax.set_xticks(x)
#ax.set_xticklabels(labels)
#ax.legend()
#
## Mostra o gráfico
#plt.show()