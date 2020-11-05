for n in 64 128 256 512 1024 2048
do
        for t in 2 4 8 16
        do
            echo n: $n t: $t
            ./hw4.bin $n $t 0
        done
        echo "---------------------"
done
