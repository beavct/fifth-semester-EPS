#!/bin/bash
PISTA=(100 200 300)
# P M G

CICLISTAS=(200 300 400)
# P N M

# Adiciona cabeçalhos ao arquivo CSV
echo "Memória Utilizada (KB), Tempo de Execução (ms)" > resultados.csv

for p_size in ${PISTA[@]}; do
    for c_size in ${CICLISTAS[@]}; do

        echo "vai rodar para " $p_size " e " $c_size
        
        #start=$(date +%s.%N)
        mem=$(/usr/bin/time time -f "%M" ./ep2 "${p_size}" "${c_size}")
        #pid=$!
        wait $!
        #end=$(date +%s.%N)
        #exec_time=$(echo "($end - $start)" | bc)

        echo "rodou para d= " $p_size " e c= " $c_size " o tempo deu " $mem
        #echo "rodou para " $p_size " e " $c_size " o tempo deu " $exec_time

        
        #for i in $(seq 1 30); do
#
        #    
        #    start=$(date +%s.%N)
        #    ./ep2 "${p_size}" "${c_size}" > /dev/null 2>&1
        #    pid=$!
        #    wait $!
        #    end=$(date +%s.%N)
        #    exec_time=$(echo "($end - $start) * 1000" | bc)
#
        #    #./ep2 "${p_size}" "${c_size}" > /dev/null 2>&1 $
        #    #pid=$!
        #    #mem_usage=$(pmap -x $pid | tail -n 1 | awk '{print $3}')
        #    
        #    # Adiciona os dados ao arquivo CSV
        #    #echo "${mem_usage}, ${exec_time}" >> r_${p_size}_${c_size}.csv
#
        #    # Aguarda a conclusão da execução antes de continuar
        #    #wait
#
        #    echo "rodou para " $p_size " e " $c_size " o tempo deu " $exec_time "\n"
        #done
        
    done
done

exit 0
