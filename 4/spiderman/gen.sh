#!/bin/bash

python gen.py

for t in test/spiderman.in.*
do
  ./spiderman_paljak < $t > ${t/in/out}
done
