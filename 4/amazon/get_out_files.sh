for f in test/*.in*;
do
  echo "Provjera" $f
  ./m3 < $f > tmp
  diff -q tmp ${f/.in/.out}
  rm tmp
  echo "--------------------"
done
