#!/bin/bash

if [ $# -eq 1 ]
then
	printf "\e[93mBuilding ft_otool\n";
	make fclean;
	make ft_otool;
fi
printf "\e[94mExecuting tests on \e[96m$1\n\e[m"
./ft_otool $1 > ret1
otool -t $1 > ret2
printf "\e[91mDiff: ["
diff ret1 ret2
printf "]\n\n"
