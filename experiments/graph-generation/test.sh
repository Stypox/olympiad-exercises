set +e

while true; do
	a="`python graphgenerator.py 100 1000000000 5 2>input2.txt | ./a.out 2>/dev/null`"
	if [ $? -ne 0 ]; then
		break
	fi

	echo $a
	cp input2.txt input1.txt
	python graphconverter.py < input1.txt > input3.txt
	if [ $? -ne 0 ]; then
		break
	fi

	read -t 0.001
	if [ $? -eq 0 ]; then
		break
	fi
done