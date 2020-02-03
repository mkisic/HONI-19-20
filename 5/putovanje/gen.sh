python gen.py

for f in test/*.in.*
do
    ./marin_lca < $f > ${f/in/out}
done
