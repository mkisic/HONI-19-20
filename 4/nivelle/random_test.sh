while true; do
    ./random_gen.py 10000 26 > inp
    ./$1 < inp > off
    ./$2 < inp > out
    ./checker_hr inp off out > checker_out
    cat checker_out
    if [ "0" == "$(sed -n 1p checker_out)" ]; then
        break
    fi
done
