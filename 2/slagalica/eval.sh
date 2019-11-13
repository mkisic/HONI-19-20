# Pokrece se s
# bash eval.sh ime
# npr. 
# bash eval.sh slagalica_paljak

for f in test/slagalica.in.*;
do
  echo $f
  ./$1 < $f > tmp
  ./checker_hr $f ${f/in/out} tmp
  rm tmp
  echo "-------------------------------"
done
