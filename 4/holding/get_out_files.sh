for f in test/*.in*;
do
  echo $f
  ./marin < $f > ${f/.in/.out}
  ./interval_fabijan < $f > tmp
  diff -q tmp ${f/.in/.out}
  rm tmp
done
