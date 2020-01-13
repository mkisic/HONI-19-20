while true; do
    python random_gen.py > inp
    ./$1 < inp > off
    ./$2 < inp > out
    ./checker_hr inp off out
done
