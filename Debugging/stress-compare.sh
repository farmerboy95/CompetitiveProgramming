i = 1;
for((i = 1; ; ++i)); do
    echo $i
    ./gen > gen.inp
    ./main < gen.inp > gen-main.out
    ./test < gen.inp > gen-test.out
    diff -w gen-main.out gen-test.out || break
    echo "TEST ${i} PASSED"
    # diff -w <(./A < int) <(./B < int) || break
done
echo "TEST ${i} GOT WRONG"
