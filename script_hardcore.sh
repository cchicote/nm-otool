#! /bin/bash

for ((i=1; i<=10000; i++)); do

	random_cpy=$RANDOM
	let "random_cpy %= $2"
	begin=$2
	let "begin -= $random_cpy"
	dd if=$1 of=hard_nm1 bs=1 count=$begin > /dev/null 2>&1
	dd if=/dev/random of=hard_nm2 bs=1 count=$random_cpy > /dev/null 2>&1
	cat hard_nm2 >> hard_nm1
	./ft_nm hard_nm1 > /dev/null 2>&1
	if [ $? -gt 2 ]
	then
		valgrind ./ft_nm hard_nm1
		exit 1
	fi
done
