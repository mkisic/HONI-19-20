for f in test/*in.*;
do
  echo $f
  ./marin_rj < $f > tmp
  diff -q -w -Z -B -b ${f/in./out.} tmp 
  rm tmp
done