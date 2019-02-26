#! /bin/bash

success=0
fail=0

rm -f diff_otool
rm -f fail_otool
for OUT in /usr/bin/*;
do
	echo "$OUT"
	./ft_otool $OUT > out_ft_otool 2>> error_otool
	if [ $? -gt 2 ]
	then
		valgrind ./ft_otool $OUT
		exit 1
	fi
	otool -t $OUT > out_otool 2>> error_otool
	diff "out_ft_otool" "out_otool"
	res=$?
	if [ $res == 1 ]
	then
		echo -e "$OUT :\n\n" >> diff_otool
		echo -e "$OUT :\n" >> fail_otool
		diff "out_ft_otool" "out_otool" >> diff_otool
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
	./ft_otool $OUT > out_ft_otool 2>> error_otool
	if [ $? -gt 2 ]
	then
		valgrind ./ft_otool $OUT
		exit 1
	fi
	otool -t $OUT > out_otool 2>> error_otool
	diff "out_ft_otool" "out_otool"
	res=$?
	if [ $res == 1 ]
	then
		echo -e "$OUT :\n\n" >> diff_otool
		echo -e "$OUT :\n" >> fail_otool
		diff "out_ft_otool" "out_otool" >> diff_otool
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
	./ft_otool $OUT > out_ft_otool 2>> error_otool
	if [ $? -gt 2 ]
	then
		valgrind ./ft_otool $OUT
		exit 1
	fi
	otool -t $OUT > out_otool 2>> error_otool
	diff "out_ft_otool" "out_otool"
	res=$?
	if [ $res == 1 ]
	then
		echo -e "$OUT :\n\n" >> diff_otool
		echo -e "$OUT :\n" >> fail_otool
		diff "out_ft_otool" "out_otool" >> diff_otool
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
	./ft_otool $OUT > out_ft_otool 2>> error_otool
	if [ $? -gt 2 ]
	then
		valgrind ./ft_otool $OUT
		exit 1
	fi
	otool -t $OUT > out_otool 2>> error_otool
	diff "out_ft_otool" "out_otool"
	res=$?
	if [ $res == 1 ]
	then
		echo -e "$OUT :\n\n" >> diff_otool
		echo -e "$OUT :\n" >> fail_otool
		diff "out_ft_otool" "out_otool" >> diff_otool
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
	./ft_otool $OUT > out_ft_otool 2>> error_otool
	if [ $? -gt 2 ]
	then
		valgrind ./ft_otool $OUT
		exit 1
	fi
	otool -t $OUT > out_otool 2>> error_otool
	diff "out_ft_otool" "out_otool"
	res=$?
	if [ $res == 1 ]
	then
		echo -e "$OUT :\n\n" >> diff_otool
		echo -e "$OUT :\n" >> fail_otool
		diff "out_ft_otool" "out_otool" >> diff_otool
		((fail++))
	elif [ $res == 0 ]
	then
		((success++))
	else
		echo -e "$OUT Error diff"
	fi
done
for OUT in obj/*;
do
	echo "$OUT"
	./ft_otool $OUT > out_ft_otool 2>> error_otool
	if [ $? -gt 2 ]
	then
		valgrind ./ft_otool $OUT
		exit 1
	fi
	otool -t $OUT > out_otool 2>> error_otool
	diff "out_ft_otool" "out_otool"
	res=$?
	if [ $res == 1 ]
	then
		echo -e "$OUT :\n\n" >> diff_otool
		echo -e "$OUT :\n" >> fail_otool
		diff "out_ft_otool" "out_otool" >> diff_otool
		((fail++))
	elif [ $res == 0 ]
	then
		((success++))
	else
		echo -e "$OUT Error diff"
	fi
done
for OUT in libft/obj/*;
do
	echo "$OUT"
	./ft_otool $OUT > out_ft_otool 2>> error_otool
	if [ $? -gt 2 ]
	then
		valgrind ./ft_otool $OUT
		exit 1
	fi
	otool -t $OUT > out_otool 2>> error_otool
	diff "out_ft_otool" "out_otool"
	res=$?
	if [ $res == 1 ]
	then
		echo -e "$OUT :\n\n" >> diff_otool
		echo -e "$OUT :\n" >> fail_otool
		diff "out_ft_otool" "out_otool" >> diff_otool
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
	./ft_otool $OUT > out_ft_otool 2>> error_otool
	if [ $? -gt 2 ]
	then
		valgrind ./ft_otool $OUT
		exit 1
	fi
	otool -t $OUT > out_otool 2>> error_otool
	diff "out_ft_otool" "out_otool"
	res=$?
	if [ $res == 1 ]
	then
		echo -e "$OUT :\n\n" >> diff_otool
		echo -e "$OUT :\n" >> fail_otool
		diff "out_ft_otool" "out_otool" >> diff_otool
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
	./ft_otool $OUT > out_ft_otool 2>> error_otool
	if [ $? -gt 2 ]
	then
		valgrind ./ft_otool $OUT
		exit 1
	fi
	otool -t $OUT > out_otool 2>> error_otool
	diff "out_ft_otool" "out_otool"
	res=$?
	if [ $res == 1 ]
	then
		echo -e "$OUT :\n\n" >> diff_otool
		echo -e "$OUT :\n" >> fail_otool
		diff "out_ft_otool" "out_otool" >> diff_otool
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