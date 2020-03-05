#!/bin/bash

python gen.py

for t in test/skandi.in.*
do
  ./skandi_paljak < $t > ${t/in/out}
done
