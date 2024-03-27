from matplotlib import pyplot as plt


def plota_atraso():
        colors = ["#5ad45a", "#8be04e", "#ebdc78"]
        labels = ["Shortes Job First", "Round-Robin", "Escalonador com prioridade"]

        dados_atraso = [[41,12,6],
                [38,21,42],
                [392,516,314]]


        for i in range(0,3):
                # atraso em segundos
                plt.bar(labels, dados_atraso[i], color=colors)
                plt.xlabel("Escalonador")
                plt.ylabel("Média do atraso(s)")

                plt.title(f"Tracefile{i+1} - Máquina A")
                plt.grid(color ='grey',
                linestyle ='-.', linewidth = 0.5,
                alpha = 0.2)
                plt.xticks(labels)
                plt.savefig(f"atraso_tc{i+1}_A.png")

                plt.bar(labels, dados_atraso[i], color=colors)
                plt.xlabel("Escalonador")
                plt.ylabel("Média do atraso(s)")

                plt.title(f"Tracefile{i+1} - Máquina B")
                plt.grid(color ='grey',
                linestyle ='-.', linewidth = 0.5,
                alpha = 0.2)
                plt.xticks(labels)
                plt.savefig(f"atraso_tc{i+1}_B.png")


def plota_deadline():
        colors = ["#5ad45a", "#8be04e", "#ebdc78"]
        labels = ["Shortes Job First", "Round-Robin", "Escalonador com prioridade"]    

        dados_deadline = [[4, 3, 1],
                [2, 7, 3],
                [12, 16, 12]]

        for i in range(0,3):        
                # atraso da deadline
                plt.bar(labels, dados_deadline[i], color=colors)
                plt.xlabel("Escalonador")
                plt.ylabel("Quantidade de atrasos da deadline")
                
                plt.title(f"Tracefile{i+1} - Máquina A")
                plt.grid(color ='grey',
                linestyle ='-.', linewidth = 0.5,
                alpha = 0.2)
                plt.xticks(labels)
                plt.savefig(f"deadl_tc{i+1}_A")
                
                plt.bar(labels, dados_deadline[i], color=colors)
                plt.xlabel("Escalonador")
                plt.ylabel("Quantidade de atrasos da deadline")
                
                plt.title(f"Tracefile{i+1} - Máquina B")
                plt.grid(color ='grey',
                linestyle ='-.', linewidth = 0.5,
                alpha = 0.2)
                plt.xticks(labels)
                plt.savefig(f"deadl_tc{i+1}_B.png")

def plota_mud_cont():
        colors = ["#5ad45a", "#8be04e", "#ebdc78"]
        labels = ["Shortes Job First", "Round-Robin", "Escalonador com prioridade"]

        dados_mud_cont = [[7, 28, 28],
                [11, 23, 23],
                [16, 34, 34]]

        for i in range(0,3):        
                # quant. de mudanças de contexto
                plt.bar(labels, dados_mud_cont[i], color=colors)
                plt.xlabel("Escalonador")
                plt.ylabel("Quantidade de mudanças de contexto")

                plt.title(f"Tracefile{i+1} - Máquina A")
                plt.grid(color ='grey',
                linestyle ='-.', linewidth = 0.5,
                alpha = 0.2)
                plt.xticks(labels)
                plt.savefig(f"mudcont_tc{i+1}_A")

                plt.bar(labels, dados_mud_cont[i], color=colors)
                plt.xlabel("Escalonador")
                plt.ylabel("Quantidade de mudanças de contexto")

                plt.title(f"Tracefile{i+1} - Máquina B")
                plt.grid(color ='grey',
                linestyle ='-.', linewidth = 0.5,
                alpha = 0.2)
                plt.xticks(labels)
                plt.savefig(f"mudcont_tc{i+1}_B.png")    
                    
                    
                    
#plota_atraso()
#plota_deadline()
plota_mud_cont()