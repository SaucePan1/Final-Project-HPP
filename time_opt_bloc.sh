script="test_optimal_blocksz_life_doLess.c"
input_file="glider_at_10.txt"
MAX_GEN=100

make generate_with_01 argument="$script"
printf '\n \n \n'
counter_N=1
N=2
while [ $counter_N -le 10 ]
do
  N=$(($N*2))
  counter=1
  while [ $counter -le 10 ]
  do
  	./first_optimization $N $MAX_GEN 0 "$input_file"
  	((counter++))
  done
  echo "Result with "
  printf $N
  printf '\n'
  python3 print_mean_std.py
  rm time_test.txt
  ((counter_N++))
done
