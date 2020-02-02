for f in test/*.in*;
do
  echo $f
  ./marin < $f > ${f/.in/.out}
  ./paula < $f > tmp
  diff -q -b -B tmp ${f/.in/.out}
  rm tmp
done
