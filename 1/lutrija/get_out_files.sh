for f in test/*in*;
do
  echo $f
  ./marin_rj < $f > ${f/in/out}
done
