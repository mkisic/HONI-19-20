for f in test/*.in*;
do
  echo $f
  ./marin < $f > ${f/.in/.out}
  ./fabijan < $f > tmp
  diff -q tmp ${f/.in/.out}
  rm tmp
done
