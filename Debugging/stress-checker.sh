i = 1;
for((i = 1; ; ++i)); do
    echo $i
    ./gen > gen.inp
    ./main < gen.inp > gen-main.out
    ./check > gen-check.out
    diff -w gen-check.out <( printf '%s\n' "AC" ) || break
    echo "TEST ${i} PASSED"
    # diff -w <(./A < int) <(./B < int) || break
done
echo "TEST ${i} GOT WRONG"
