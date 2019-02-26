#! /bin/bash

for ((i=1; i<=$2; i++)); do
	newfsize=$2
	((newfsize-=$i))
	dd if=$1 of=degr_nm bs=1 count=$newfsize > /dev/null 2>&1
	./ft_nm degr_nm > /dev/null 2>&1
	if [ $? -gt 2 ]
	then
		valgrind ./ft_nm degr_nm
		exit 1
	fi
done
