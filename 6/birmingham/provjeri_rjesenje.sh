for f in test/*.in.*
do
  echo $f
  ./$1 < $f > out
  if diff -q -b ${f/.in./.out.} out;
  then
    echo ok!
  else
    echo greska!
  fi
done
