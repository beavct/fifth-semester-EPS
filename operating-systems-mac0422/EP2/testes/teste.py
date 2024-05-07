
import numpy as np  
import matplotlib.pyplot as plt  

def plota_mem():
    # velodromo
    V = [100,200,400]
    colors = ["#5ad45a", "#8be04e", "#ebdc78"]
    # ciclistas
    labels = [200,300,400]

    memoria = [[7084,7180,7596],
            [3500,7544,5316],
            [6632,7212,7348]]


    for i in range(0, 3):
        X_axis = np.arange(len(labels)) 

        plt.bar(X_axis, memoria[i], 0.4, color=colors) 
        #plt.bar(X_axis+0.2, tempo[i], 0.4, label = 'Tempo') 

        plt.xticks(X_axis, labels) 
        plt.xlabel("Quantidade k de ciclistas") 
        plt.ylabel("Uso máx. de memória em kB") 
        plt.title(f"Velódromo de comprimento {V[i]}") 
        plt.grid(color ='grey',
        linestyle ='-.', linewidth = 0.5,
        alpha = 0.2)
        plt.legend() 
        plt.savefig(f"mem_p{V[i]}")


def plota_tempo():
    # velodromo
    V = [100,200,400]
    colors = ["#5ad45a", "#8be04e", "#ebdc78"]
    # ciclistas
    labels = [200,300,400]

    tempo = [[211.09,456.85,1064.67],
            [246.80,814.10,2014.21],
            [496.45,1842.34,5155.79]]


    for i in range(0, 3):
        X_axis = np.arange(len(labels)) 

        plt.bar(X_axis, tempo[i], 0.4, color=colors) 
        #plt.bar(X_axis+0.2, tempo[i], 0.4, label = 'Tempo') 

        plt.xticks(X_axis, labels) 
        plt.xlabel("Quantidade k de ciclistas") 
        plt.ylabel("Tempo em segundos") 
        plt.title(f"Velódromo de comprimento {V[i]}") 
        plt.grid(color ='grey',
        linestyle ='-.', linewidth = 0.5,
        alpha = 0.2)
        plt.legend() 
        plt.savefig(f"tempo_p{V[i]}")
    

plota_tempo()

'''
X = ['Group A','Group B','Group C','Group D'] 
memoria = [10,20,20,40] 
tempo = [20,30,25,30] 
  
X_axis = np.arange(len(X)) 
  
plt.bar(X_axis - 0.2, memoria, 0.4, label = 'Girls') 
plt.bar(X_axis + 0.2, tempo, 0.4, label = 'Boys') 
  
plt.xticks(X_axis, X) 
plt.xlabel("Groups") 
plt.ylabel("Number of Students") 
plt.title("Number of Students in each group") 
plt.legend() 
plt.show()
'''