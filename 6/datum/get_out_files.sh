for f in test/*.in*;
do
  echo "Provjera" $f
  ./fabijan < $f > tmp
  diff -q tmp ${f/.in/.out}
  rm tmp
  echo "--------------------"
done
