for f in test/*.in.*
do
  echo $f
  ./$1 < $f > out
  ./checker_hr $f ${f/.in./.out.} out
done
