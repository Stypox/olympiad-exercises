if [[ "$*" == *cpp ]]
then
    val="$*"
else
    val="$*.cpp"
fi

python3 rename_input.py && g++ -fsanitize=address -Wall -Wextra -Wpedantic -std=c++2a -g $val && ./a.out < input.txt > output.txt