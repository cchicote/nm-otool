#! /bin/bash

for ((i=1; i<=$2; i++)); do
	newfsize=$2
	((newfsize-=$i))
	dd if=$1 of=degr_otool bs=1 count=$newfsize > /dev/null 2>&1
	./ft_otool degr_otool > /dev/null 2>&1
	if [ $? -gt 2 ]
	then
		valgrind ./ft_otool degr_otool
		exit 1
	fi
done
