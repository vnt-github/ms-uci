# python3 hw8.py 100 2 1 1 10
# python3 hw8.py 100 100 1 1 10

# python3 hw8.py 10 1 1 1 10
# python3 hw8.py 10 100 1 1 10

# for no_processors in 5 10 100
# do
#     for give_max in `seq 1000 10 10000`
#     do
#         python3 hw8.py $no_processors $give_max 1 1 10
#     done
#     echo ''
# done


# for no_processors in 5 10 100
# do
#     for local_diff_max in `seq  1 10 1000`
#     do
#         python3 hw8.py $no_processors 1000 $local_diff_max 0.5 10
#     done
#     echo ''
# done

# for no_processors in 100
# do
#     for fr in `seq  0.01 0.01 1`
#     do
#         python3 hw8.py $no_processors 1000 1000 $fr 10
#     done
#     echo ''
# done

for no_processors in 100
do
    for test_no in `seq 1 1 100`
    do
        python3 hw8.py $no_processors 1000 1000 0.85 10
        python3 hw8.py $no_processors 10 10 0.85 10
        echo ''
    done
    echo '---------------------------------------------'
done
