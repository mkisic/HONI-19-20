if [[ $# -ne 3 ]] ; then
    echo "Pokreni ./random_test.sh N prvo_rjesenje drugo_rjesenje"
    exit 0
fi

while true ; do
    ./random_gen.py $1 > inp
    ./$2 < inp > off
    ./$3 < inp > out
    sed -n 1p off
    ./checker_hr inp off out > checker_out
    cat checker_out
    if [ "0" == "$(sed -n 1p checker_out)" ]; then
        break
    fi
done
