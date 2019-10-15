program=$1
my_out=tmp_out
points_file=points.txt

for i in 1 2 3; do
    subtask_points=1
    for test_in in test/trobojnica.in.$i*; do
        test_out=${test_in/in/out}
        ./$program < $test_in > $my_out
        ./checker $test_in $test_out $my_out > $points_file
        points=$(head -n 1 $points_file)
        if (( $(echo "$points < $subtask_points" | bc -l) )); then
            subtask_points=$points
        fi
        echo $test_in `head -2 $points_file | tail -1`
    done
    echo === subtask \#$i $subtask_points
done

rm $my_out $points_file
