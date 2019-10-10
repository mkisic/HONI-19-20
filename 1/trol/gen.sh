#!/bin/bash

python gen.py

for f in test/*.in.*
do
  ./trol < $f > ${f/in/out}
done
