#!/bin/bash
m=0
n=0
threadTime=0
processtime=0
echo "Running matrix multiplication test script." 
for i in 8 6 4 2 1; do
                for j in 0 1 2 3 4 5; do
                        m=$((50 + 50*$j*10))
                        n=$((30 + 45*$j*9))
                        echo "Generating matrixes $m x $n, $n x $m"
                        ./generator $m $n $n $m 
                        echo "Multiplying with $i threads and processes ten times"
                        for k in $(seq 0 10); do
                                time "-o" "rthread.txt" "-a" "-f" "%e MAT $j N $i" ./matrix_p $i
                                time "-o" "rprocess.txt" "-a" "-f" "%e MAT $j N $i" ./matrix_fork $i
                        done
                done
done
