for f in test/*in*;
do
  echo $f
  ./marin < $f > ${f/in/out}
  #time ./brut < $f > tmp
  time ./grudanje_paljak < $f > tmp
  diff -q tmp ${f/in/out}
  rm tmp
done
