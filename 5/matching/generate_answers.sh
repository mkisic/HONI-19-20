rm test/matching.out.*

for inp in test/matching.in.*; do
    out=${inp/in/smece}
    out=${out/in/out}
    out=${out/smece/in}
    echo $out
    ./paula < $inp > $out
done
