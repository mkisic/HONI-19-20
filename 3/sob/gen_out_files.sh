for input in test/sob.in.*; do
    output=${input/in/out}
    ./paula_greedy_optimizirani < $input > $output
done
