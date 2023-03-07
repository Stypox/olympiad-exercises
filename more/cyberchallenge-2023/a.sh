for i in {0..9..1}
do
    g++ -Wall -Wextra -Wpedantic -std=c++2a -O3 -DTTOCONSIDER=$i d.cpp -o $i.out
done