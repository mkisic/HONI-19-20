for f in test/*in*;
do
  echo $f
  python3 marin.py < $f > tmp
  diff -q -Z -B tmp ${f/in/out}
  rm tmp
done
