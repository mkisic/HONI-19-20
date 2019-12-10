echo > out
echo > out_brute

while diff -nbqBw out out_brute; do
  ./gen $RANDOM 4000 > in
  ./palindromi < in > out
  ./palindromi_brute_hash < in > out_brute
  printf '.'
done
