#!/usr/bin/python2

doc = """
  Cenerate all test cases in test/:  gen.py
"""

import sys
import glob
import os
import random
import subprocess
import math

PROBLEM = "drvca"
sys.setrecursionlimit(1000010)

MAXN = 10**5
MAXH = 10**9


class Test(object):
  def __init__(self, n, p):
    self.n = n
    self.p = p


  def validate(self):
    assert(1 <= self.n <= MAXN)

    for x in self.p:
      assert 1 <= x <= MAXH, "kriva visina"


  def write(self, fd=sys.stdout):
    print>>fd, self.n
    print>>fd, " ".join(list(map(str, self.p)))


def remove_cases():
  cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
  cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
  cases += glob.glob('test/%s.in.*' % PROBLEM)
  cases += glob.glob('test/%s.out.*' % PROBLEM)
  for c in cases:
    print>>sys.stderr, 'Removing ' + c
    os.remove(c)


def generiraj(n, a, sijeku, krivo):
  p = []
  x = MAXH - random.randint(1235, 123456)
  k = random.randint(1, 10**4)

  for i in range(a):
    p.append(x - i * k)

  x = MAXH - random.randint(1234, 123456)
  k += (-1)**(random.randint(1,2)) * random.randint(0, 5)
  if k < 0: k = -k

  if sijeku:
    x = p[-random.randint(1, min(5, a-1))] + random.randint(1, min(10, max(2, a-4))) * k

  for i in range(n - a):
    p.append(x - i * k)

  for i in range(10):
    random.shuffle(p)

  if krivo:
    ind = random.randint(0, len(p)-1)
    p[ind] += random.randint(1, MAXH - p[ind] - 5)

  return Test(n, p)


def isti(n, t):
  k = random.randint(2, n - 5)
  a = random.randint(124, MAXH - 421)
  b = a + 1
  if t: b = a
  p = []
  for i in range(k):
    p.append(a)
  for i in range(n - k):
    p.append(b)

  for i in range(5):
    random.shuffle(p)

  return Test(n, p)

def preklopljeni(n, isti, maks):
  d2 = random.randint(2, 10)
  d1 = d2 * random.randint(2, 10)

  n1 = n // 4
  if n <= 15:
    n1 = min(n - 1, 7)
  n2 = n - n1

  if isti:
    n1 = n // 2
    n2 = n - n1
    d1 = d2 * random.randint(2, 4)
    assert n1 == n2

  r = random.randint(n1 // 8, n1 // 4)
  if n <= 15:
    r = 2
    d1 = d2 * 2

  p = []
  for i in range(1, n1 + 1):
    p.append(i * d1)
  for i in range(1, n2 + 1):
    p.append(i * d2 + d1 * (n1 - r))

  for i in range(5):
    random.shuffle(p)

  if i in range(n):
    if maks:
      p[i] = MAXH - p[i]

  return Test(n, p)

def dva():
  n = 2
  p = []
  for i in range(2):
    p.append(random.randint(123,1234))
  return Test(n, p)

def gen_cases():
  remove_cases()

  real = []
  dummy = []

  for i, test in enumerate(dummy):
    test.validate()
    print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
    test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

  dummy.append(Test(4, [1, 3, 2, 4]))
  dummy.append(Test(6, [23, 4, 7, 6, 8, 15]))
  dummy.append(Test(6, [1, 2, 3, 7, 9, 10]))

  for i, test in enumerate(dummy):
    test.validate()
    print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
    test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))
  
  # N <= 15
  cluster = []
  for i in range(4):
    cluster.append(generiraj(14 + (i%2), random.randint(2, 10), i % 2, 0))
    cluster.append(generiraj(14 + (i%2), random.randint(2, 10), i % 2, 1))

  cluster.append(preklopljeni(14, 0, 0))
  cluster.append(preklopljeni(15, 0, 0))
  cluster.append(preklopljeni(14, 0, 1))
  cluster.append(isti(15, 0))
  cluster.append(isti(15, 1))
  cluster.append(dva())
  real.append(cluster)
  
  # N <= 300
  cluster = []
  for i in range(4):
    cluster.append(generiraj(299 + (i%2), random.randint(100, 250), i % 2, 0))
    cluster.append(generiraj(299 + (i%2), random.randint(100, 250), i % 2, 1))
    cluster.append(preklopljeni(299 + (i%2), 0, 0))
  
  cluster.append(preklopljeni(300, 0, 1))

  cluster.append(isti(300, 0))
  cluster.append(isti(300, 1))
  cluster.append(dva())
  real.append(cluster)

  # postoji rjesenje s 2 niza jednake duljine
  cluster = []
  for i in range(8):
    cluster.append(generiraj(100000, 50000, i % 2, 0))

  cluster.append(preklopljeni( 99998, 1, 0))
  cluster.append(preklopljeni(100000, 1, 1))
  cluster.append(isti(100000, 1))
  cluster.append(dva())
  real.append(cluster)

  # N <= 10^5
  cluster = []
  for i in range(4):
    cluster.append(generiraj(99999 + (i%2), random.randint(20000, 50000), i % 2, 0))
    cluster.append(generiraj(99999 + (i%2), random.randint(20000, 50000), i % 2, 1))
    cluster.append(preklopljeni(99999 + (i % 2), 0, 0))

  cluster.append(preklopljeni(100000, 0, 1))
  cluster.append(isti(100000, 0))
  cluster.append(isti(100000, 1))
  cluster.append(dva())
  real.append(cluster)

  for i, batch in enumerate(real):
    for j, test in enumerate(batch):
      test.validate()
      print>>sys.stderr, 'Generating test/%s.in.%d%c' \
              % (PROBLEM, i+1, chr(ord('a')+j))
      input = 'test/%s.in.%d%c' % (PROBLEM, i+1, chr(ord('a')+j))
      test.write(file(input, 'wt'))


def main():
  random.seed(293487)
  gen_cases()


if __name__ == "__main__":
  main()
