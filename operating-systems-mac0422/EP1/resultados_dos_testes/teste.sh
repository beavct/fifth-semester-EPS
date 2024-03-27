#!/bin/bash

for i in $(seq 1 3);do
    
    for j in $(seq 1 3);do

        #$(touch s_tc${i}_esc${j} r_tc${i}_esc${j})
        $(./ep1 ${j} tracefile${i} s_tc${i}_esc${j})
        $(mv resultados.txt r_tc${i}_esc${j})
    
    done

done

exit 0