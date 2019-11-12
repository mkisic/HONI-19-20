python gen.py

for f in test/*.in.*
do
    ./slagalica_sluzbeno < $f > ${f/in/out}
done
