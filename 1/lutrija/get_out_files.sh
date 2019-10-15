for f in test/*in*;
do
  echo $f
  ./marin_rj < $f > ${f/in/out}
  ./marin_druga < $f > tmp
  ./hsin_checker $f ${f/in/out} tmp 
  rm tmp
done
