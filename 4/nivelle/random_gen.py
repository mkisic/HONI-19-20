#!/usr/bin/python3

import random
import string
import math
import sys

n = int(sys.argv[1])
a = int(sys.argv[2])

b = random.randint(1, a)
m = min(n, n * b // a + random.randint(1, int(math.sqrt(n))))

A = string.ascii_lowercase[:a]
B = random.sample(A, b)

d = random.randint(0, n - m)

s = ''.join(random.choices(A, k=d) +
            random.choices(B, k=m) +
            random.choices(A, k=n - d - m))

print(len(s))
print(s)
