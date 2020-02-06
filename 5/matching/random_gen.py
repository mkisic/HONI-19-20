#!/usr/bin/python3

import sys
import random

n = int(sys.argv[1])
n //= 2

p = [i + 1 for i in range(n)]
random.shuffle(p)
q = [i + 1 for i in range(n)]
random.shuffle(q)

A = list(zip(p + p, q + q[1:] + q[:1]))
assert len(A) == len(set(A))

A = random.sample(A, random.randint(n - 2, n) * 2)

print(len(A))
for a in A:
    print(*a)
