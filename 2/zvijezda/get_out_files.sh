for f in test/*in*;
do
  echo $f
  ./marin < $f > ${f/in/out}
  ./Zvijezda_Josip < $f > tmp
  diff -q tmp ${f/in/out}
  rm tmp
done
