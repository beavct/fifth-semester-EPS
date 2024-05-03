
import numpy as np  
import matplotlib.pyplot as plt  

def plota_mem():
    # velodromo
    V = [20,70,200]
    colors = ["#5ad45a", "#8be04e", "#ebdc78"]
    # ciclistas
    labels = [10, 40, 200]

    memoria = [[1960,2300,3736],
            [2036,2252,3532],
            [2000,2256,3712]]


    for i in range(0, 3):
        X_axis = np.arange(len(labels)) 

        plt.bar(X_axis, memoria[i], 0.4, color=colors) 
        #plt.bar(X_axis+0.2, tempo[i], 0.4, label = 'Tempo') 

        plt.xticks(X_axis, labels) 
        plt.xlabel("Quantidade k de ciclistas") 
        plt.ylabel("Uso de memória em kB") 
        plt.title(f"Velódromo de comprimento {V[i]}") 
        plt.grid(color ='grey',
        linestyle ='-.', linewidth = 0.5,
        alpha = 0.2)
        plt.legend() 
        plt.savefig(f"tempo_p{V[i]}")


def plota_tempo():
    # velodromo
    V = [20,70,200]
    colors = ["#5ad45a", "#8be04e", "#ebdc78"]
    # ciclistas
    labels = [10, 40, 200]

    tempo = [[0.037800349, 0.554299521, 0.210188426],
            [0.109301736,0.790978198,2.035625333],
            [0.230458596,2.857424442,233.778823073]]


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
    

plota_mem()

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