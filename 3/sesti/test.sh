while true; do
    python3 gen.py > in
    ./$1 < in > out
    ./checker_hr in tmp out
done
