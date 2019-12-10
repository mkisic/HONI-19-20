echo > out
echo > out_brute

while diff -nbqBw out out_brute; do
  ./gen $RANDOM 50 3 simple-simple > in
  ./lampice < in > out
  ./brute_bekup < in > out_brute
  printf '.'
done
