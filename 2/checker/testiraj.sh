for test_in in test/checker.in.$2*; do
    test_out=${test_in/in/out}
    ./$1 < $test_in > tmp_out
    diff -q -w -B $test_out tmp_out
done
rm tmp_out
