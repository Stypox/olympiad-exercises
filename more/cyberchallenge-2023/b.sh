python3 rename_input.py
for i in {0..9..1}
do
    ./$i.out < input.txt > output$i.txt &
done
wait