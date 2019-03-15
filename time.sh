#!/bin/bash
input_file=$1
script=$2


make generate_with_01 argument="$script"
printf '\n \n \n'
printf '\n \n \n'
pwd
counter=1
while [ $counter -le 3 ]
do
	./first_optimization "$input_file"

	((counter++))
done
printf '\n \n \n'
echo "Result with O1 flag -------------------------------"
echo "<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
printf '\n \n \n'
python3 print_mean_std.py
make clean

make generate_with_02 argument="$script"
printf '\n \n \n'
printf '\n \n \n'
pwd
counter=1
while [ $counter -le 3 ]
do
	./second_optimization "$input_file"
	((counter++))
done
printf '\n \n \n'
echo "Result with O2 flag -------------------------------"
echo "<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
printf '\n \n \n'
python3 print_mean_std.py
make clean

make generate_with_03 argument="$script"
printf '\n \n \n'
printf '\n \n \n'
pwd
counter=1
while [ $counter -le 3 ]
do
	./third_optimization "$input_file"
	((counter++))
done
printf '\n \n \n'
echo "Result with O3 flag -------------------------------"
echo "<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
printf '\n \n \n'
python3 print_mean_std.py
make clean

make generate_with_ffast_math argument="$script"
printf '\n \n \n'
printf '\n \n \n'
pwd
counter=1
while [ $counter -le 3 ]
do
	./ffast_math "$input_file"
	((counter++))
done
printf '\n \n \n'
echo "Result with 03 ffast-math flag -------------------------------"
echo "<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
printf '\n \n \n'
python3 print_mean_std.py
make clean

make generate_with_ffast_native argument="$script"
printf '\n \n \n'
printf '\n \n \n'
pwd
counter=1
while [ $counter -le 3 ]
do
	./ffast_native "$input_file"
	((counter++))
done
printf '\n \n \n'
echo "Result with O3 ffast-math -march=native flag -------------------------------"
echo "<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
printf '\n \n \n'
python3 print_mean_std.py
make clean

make generate_with_ffast_msse4 argument="$script"
printf '\n \n \n'
printf '\n \n \n'
pwd
counter=1
while [ $counter -le 3 ]
do
	./ffast_native "$input_file"
	((counter++))
done
printf '\n \n \n'
echo "Result with O3 ffast-math -mmse4 flag -------------------------------"
echo "<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
printf '\n \n \n'
python3 print_mean_std.py
make clean