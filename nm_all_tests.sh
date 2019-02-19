#!/bin/bash
printf "\e[93mBuilding ft_nm\n"
make fclean
make ft_nm
printf "\e[0m"
for filename in files_test/$1/*; do
	./nm_script.sh "$filename" 1
done
