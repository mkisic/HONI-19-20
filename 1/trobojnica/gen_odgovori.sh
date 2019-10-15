for test_in in test/trobojnica.in.*; do
    test_out=${test_in/in/out}
    ./paula_tocno < $test_in > $test_out 
done
