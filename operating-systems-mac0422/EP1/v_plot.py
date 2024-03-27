# Utiliza violinplot

import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# Carregar dados do arquivo CSV
dados = pd.read_csv('data.csv', sep=',')

# Nomes das colunas
coluna1 = 'Shorterst Job First'
coluna2 = 'Round-Robin'
coluna3 = 'Escalonador por prioridade'

# Estilo do seaborn
sns.set(style="whitegrid")

# Criar figura e eixo
f, ax = plt.subplots(figsize=(8, 8))

# Plotar cada distribuição com violinos e pontos
sns.violinplot(x="variable", y="value", data=pd.melt(dados), palette="rocket", inner="box", cut=2 , linewidth=2)

#sns.violinplot(x="variable", y="value", data=pd.melt(dados), inner="box", box=True, palette="Set3", cut=2.5, linewidth=2)


# Título do gráfico
f.suptitle('Atraso de cada escalonador', fontsize=18, fontweight='bold')

# Rótulos dos eixos
#ax.set_xlabel("Escalonador", size=16, alpha=0.7)
ax.set_ylabel("Atraso em segundos", size=16, alpha=0.7)

plt.ylim(-20, 70)  # Ajuste conforme necessário

# Mostrar o plot
plt.show()
