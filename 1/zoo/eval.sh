for f in test/*.in.*
do
  echo $f
  ./$1 < $f > out
  DIFF=$(diff out ${f/in/out})
  if [ "$DIFF" != "" ]
  then
    echo "WA"
  else
    echo "OK"
  fi
done
