#!/bin/bash
printf "\e[93mBuilding ft_otool\n"
make fclean
make ft_otool
printf "\e[0m"
for filename in files_test/$1/*; do
	./otool_script.sh "$filename" 1
done
