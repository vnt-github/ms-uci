#!/bin/bash
make

n=7000

# echo "for single disable other in main.c"
# ./hw5.bin 2 1 1 0
# for n in `seq 100 100 10000`
# do
#         echo -n $n ", "
#         ./hw5.bin $n 1 1 0
# done

# echo ""
# echo "fine-grain grain="1 "n="$n
# for t in 1 2 3 4 5 6 8 16 24 32 64 128
# do
#         let c=1
#         echo n: $n c: $c t: $t
#         ./hw5.bin $n $c $t 0
# done


# echo "coarse-grain grain=((n*n-n)/2)/threads n="$n
# for t in 1 2 3 4 5 6 8 16 24 32 64 128
# do
#         let c=$n*$((n-1))/$((2*t))
#         ./hw5.bin $n $c $t 0
# done

# echo ""
# echo "coarse-grain grain="$n "n="$n
# for t in 1 2 3 4 5 6 8 16 24 32 64 128
# do
#         let c=$n
#         ./hw5.bin $n $c $t 0
# done

echo "for single disable other in main.c"
./hw5.bin 2 1 1 0
for n in `seq 100 100 10000`
do
        let t=128
        let c=$n*$((n-1))/$((2*t))
        ./hw5.bin $n $c 128 0
done