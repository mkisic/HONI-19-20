for input in test/sobovi.in.*; do
    output=${input/in/out}
    ./$1 < $input > tmp
    ./checker_hr $input $output tmp
done
