echo > out
echo > out_brute

while diff -nbqBw out out_brute; do
  ./gen $RANDOM 100 > in
  ./palindromi < in > out
  ./brute < in > out_brute
  printf '.'
done
