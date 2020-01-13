for inp in test/nivelle*in*; do
    out=${inp/in/out}
    echo "running on $inp"
    ./$1 < $inp > tmp
    ./checker_hr $inp $out tmp
done
rm tmp
