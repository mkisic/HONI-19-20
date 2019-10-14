for f in test/*in*;
do
  echo $f
  ./marin_rj < $f > ${f/in/out}
  ./marin_druga < $f > tmp
  diff -w tmp ${f/in/out}
  rm tmp
done
