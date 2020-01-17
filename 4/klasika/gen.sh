#!/bin/bash

python gen.py

for t in test/*.in.*
do
  ./klasika_paljak < $t > ${t/in/out}
done
