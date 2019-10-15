program=$1
my_out=tmp_out

for test_in in test/trobojnica.in.*; do
    test_out=${test_in/in/out}
    ./$program < $test_in > $my_out
    ./checker $test_in $test_out $my_out
done

rm $my_out
