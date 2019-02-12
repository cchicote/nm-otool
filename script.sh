#!/bin/bash

if [ $# -eq 1 ]
then
	printf "\e[93mBuilding ft_nm\n";
	make fclean;
	make ft_nm;
fi
printf "\e[94mExecuting tests on \e[96m$1\n\e[m"
./ft_nm $1 > ret1
nm $1 > ret2
printf "\e[91mDiff: ["
diff ret1 ret2
printf "]\n\n"
