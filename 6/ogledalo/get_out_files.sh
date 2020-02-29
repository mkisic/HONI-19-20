for f in test/*.in*;
do
  echo $f
  python3 marin.py < $f > ${f/.in/.out}
done
