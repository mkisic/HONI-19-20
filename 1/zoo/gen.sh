#!/bin/bash

python gen.py

for f in test/*.in.*
do
  ./zoo < $f > ${f/in/out}
done
