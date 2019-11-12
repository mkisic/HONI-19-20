#!/bin/bash

python gen.py

for t in test/popcount.in.*
do
  python3 popcount.py < $t > ${t/in/out}
done
