#! /bin/bash

success=0
fail=0

rm -f diff_nm
for OUT in /usr/bin/*;
do
	echo "$OUT"
	./ft_nm $OUT > out_ft_nm 2>> error_nm
	if [ $? -gt 2 ]
	then
		valgrind ./ft_nm $OUT
		exit 1
	fi
	nm $OUT > out_nm 2>> error_nm
	diff "out_ft_nm" "out_nm"
	res=$?
	if [ $res == 1 ]
	then
		echo -e "\n\n$OUT :" >> diff_nm
		diff "out_ft_nm" "out_nm" >> diff_nm
		((fail++))
	elif [ $res == 0 ]
	then
		((success++))
	else
		echo -e "$OUT Error diff"
	fi
done
for OUT in /bin/*;
do
	echo "$OUT"
	./ft_nm $OUT > out_ft_nm 2>> error_nm
	if [ $? -gt 2 ]
	then
		valgrind ./ft_nm $OUT
		exit 1
	fi
	nm $OUT > out_nm 2>> error_nm
	diff "out_ft_nm" "out_nm"
	res=$?
	if [ $res == 1 ]
	then
		echo -e "\n\n$OUT :" >> diff_nm
		diff "out_ft_nm" "out_nm" >> diff_nm
		((fail++))
	elif [ $res == 0 ]
	then
		((success++))
	else
		echo -e "$OUT Error diff"
	fi
done
for OUT in /sbin/*;
do
	echo "$OUT"
	./ft_nm $OUT > out_ft_nm 2>> error_nm
	if [ $? -gt 2 ]
	then
		valgrind ./ft_nm $OUT
		exit 1
	fi
	nm $OUT > out_nm 2>> error_nm
	diff "out_ft_nm" "out_nm"
	res=$?
	if [ $res == 1 ]
	then
		echo -e "\n\n$OUT :" >> diff_nm
		diff "out_ft_nm" "out_nm" >> diff_nm
		((fail++))
	elif [ $res == 0 ]
	then
		((success++))
	else
		echo -e "$OUT Error diff"
	fi
done
for OUT in /usr/lib/*;
do
	echo "$OUT"
	./ft_nm $OUT > out_ft_nm 2>> error_nm
	if [ $? -gt 2 ]
	then
		valgrind ./ft_nm $OUT
		exit 1
	fi
	nm $OUT > out_nm 2>> error_nm
	diff "out_ft_nm" "out_nm"
	res=$?
	if [ $res == 1 ]
	then
		echo -e "\n\n$OUT :" >> diff_nm
		diff "out_ft_nm" "out_nm" >> diff_nm
		((fail++))
	elif [ $res == 0 ]
	then
		((success++))
	else
		echo -e "$OUT Error diff"
	fi
done
for OUT in /usr/sbin/*;
do
	echo "$OUT"
	./ft_nm $OUT > out_ft_nm 2>> error_nm
	if [ $? -gt 2 ]
	then
		valgrind ./ft_nm $OUT
		exit 1
	fi
	nm $OUT > out_nm 2>> error_nm
	diff "out_ft_nm" "out_nm"
	res=$?
	if [ $res == 1 ]
	then
		echo -e "\n\n$OUT :" >> diff_nm
		diff "out_ft_nm" "out_nm" >> diff_nm
		((fail++))
	elif [ $res == 0 ]
	then
		((success++))
	else
		echo -e "$OUT Error diff"
	fi
done
for OUT in objs/*;
do
	echo "$OUT"
	./ft_nm $OUT > out_ft_nm 2>> error_nm
	if [ $? -gt 2 ]
	then
		valgrind ./ft_nm $OUT
		exit 1
	fi
	nm $OUT > out_nm 2>> error_nm
	diff "out_ft_nm" "out_nm"
	res=$?
	if [ $res == 1 ]
	then
		echo -e "\n\n$OUT :" >> diff_nm
		diff "out_ft_nm" "out_nm" >> diff_nm
		((fail++))
	elif [ $res == 0 ]
	then
		((success++))
	else
		echo -e "$OUT Error diff"
	fi
done
for OUT in libft/*;
do
	echo "$OUT"
	./ft_nm $OUT > out_ft_nm 2>> error_nm
	if [ $? -gt 2 ]
	then
		valgrind ./ft_nm $OUT
		exit 1
	fi
	nm $OUT > out_nm 2>> error_nm
	diff "out_ft_nm" "out_nm"
	res=$?
	if [ $res == 1 ]
	then
		echo -e "\n\n$OUT :" >> diff_nm
		diff "out_ft_nm" "out_nm" >> diff_nm
		((fail++))
	elif [ $res == 0 ]
	then
		((success++))
	else
		echo -e "$OUT Error diff"
	fi
done
for OUT in /usr/libexec/*;
do
	echo "$OUT"
	./ft_nm $OUT > out_ft_nm 2>> error_nm
	if [ $? -gt 2 ]
	then
		valgrind ./ft_nm $OUT
		exit 1
	fi
	nm $OUT > out_nm 2>> error_nm
	diff "out_ft_nm" "out_nm"
	res=$?
	if [ $res == 1 ]
	then
		echo -e "\n\n$OUT :" >> diff_nm
		diff "out_ft_nm" "out_nm" >> diff_nm
		((fail++))
	elif [ $res == 0 ]
	then
		((success++))
	else
		echo -e "$OUT Error diff"
	fi
done
for OUT in /usr/libexec/apache2/*;
do
	echo "$OUT"
	./ft_nm $OUT > out_ft_nm 2>> error_nm
	if [ $? -gt 2 ]
	then
		valgrind ./ft_nm $OUT
		exit 1
	fi
	nm $OUT > out_nm 2>> error_nm
	diff "out_ft_nm" "out_nm"
	res=$?
	if [ $res == 1 ]
	then
		echo -e "\n\n$OUT :" >> diff_nm
		diff "out_ft_nm" "out_nm" >> diff_nm
		((fail++))
	elif [ $res == 0 ]
	then
		((success++))
	else
		echo -e "$OUT Error diff"
	fi
done
echo $success "success"
echo $fail "fail"
