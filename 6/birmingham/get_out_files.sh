for f in test/*.in*;
do
  echo $f
  ./marin < $f > ${f/.in/.out}
done
