for f in test/*in*;
do
  echo $f
  ./marin < $f > ${f/in/out}
  ./2naN < $f > tmp
  ./checker_hr $f ${f/in/out} tmp
  rm tmp
done
