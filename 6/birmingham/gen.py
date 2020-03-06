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

PROBLEM = "birmingham"
sys.setrecursionlimit(1000010)

MAXN = 100000
MAXM = 200000

class Test(object):
  def __init__(self, n, m, q, k, p, E):
    self.n = n
    self.m = m
    self.q = q
    self.k = k
    self.p = p
    self.E = E

  def validate(self):
    assert(1 <= self.n <= MAXN)
    assert(1 <= self.m <= MAXM)
    assert(1 <= self.k <= MAXN)
    assert(1 <= self.q <= self.n)
    assert(len(self.p) == self.q)
    assert(len(self.E) == self.m)
    for x in self.p:
      assert 1 <= int(x) <= self.n
    
    for x in self.E:
      assert 1 <= x[0] <= self.n and 1 <= x[1] <= self.n and x[0] != x[1]


  def write(self, fd=sys.stdout):
    print>>fd, self.n, self.m, self.q, self.k
    print>>fd, " ".join(map(str, self.p))
    for x in self.E:
      print>>fd, x[0], x[1]


def remove_cases():
  cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
  cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
  cases += glob.glob('test/%s.in.*' % PROBLEM)
  cases += glob.glob('test/%s.out.*' % PROBLEM)
  for c in cases:
    print>>sys.stderr, 'Removing ' + c
    os.remove(c)


def gen(n, m, q, k):
  p = []
  E = []
  perm = []
  for i in range(1, n + 1):
    perm.append(i)

  random.shuffle(perm)
  for i in range(q):
    p.append(perm[i])

  edges = set()
  for i in range(2, n + 1):
    a = i
    b = random.randint(1, i - 1)
    edges.add((a, b))
    E.append((a, b))

  for i in range(m - (n - 1)):
    a = random.randint(1, n)
    b = random.randint(1, n)
    if a > b:
      pom = a
      a = b
      b = pom
    while (a == b) or ((a, b) in edges):
      a = random.randint(1, n)
      b = random.randint(1, n)
      if a > b:
        pom = a
        a = b
        b = pom
    edges.add((a, b))
    E.append((a, b))

  return Test(n, m, q, k, p, E)


def gen_cases():
  remove_cases()

  real = []
  dummy = []

  for i, test in enumerate(dummy):
    test.validate()
    print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
    test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

  dummy.append(Test(6, 8, 1, 1, [6], [(1, 3), (1, 5), (1, 6), (2, 5), (2, 6), (3, 4), (3, 5), (5, 6)]))
  dummy.append(Test(6, 8, 2, 1, [6, 4], [(1, 3), (1, 5), (1, 6), (2, 5), (2, 6), (3, 4), (3, 5), (5, 6)]))
  dummy.append(Test(6, 8, 1, 2, [6], [(1, 3), (1, 5), (1, 6), (2, 5), (2, 6), (3, 4), (3, 5), (5, 6)]))

  for i, test in enumerate(dummy):
    test.validate()
    print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
    test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))
  
  # K = 1, N, Q <= 100, M <= 200 - 4 primjera
  for num in range(4):
    cluster = []
    cluster.append(gen(100, 200 - random.randint(0, 10), 1, 1))
    cluster.append(gen(100, 200 - random.randint(0, 10), random.randint(2, 5), 1))
    cluster.append(gen(100, 200 - random.randint(0, 10), 70 + random.randint(5, 10), 1))
    real.append(cluster)
  
  # N, Q <= 100, M <= 200 - 3 primjera
  for num in range(3):
    cluster = []
    cluster.append(gen(100, 200 - random.randint(0, 10), 1, random.randint(2, 8)))
    cluster.append(gen(100, 200 - random.randint(0, 10), random.randint(2, 5), random.randint(2, 8)))
    cluster.append(gen(100, 200 - random.randint(0, 10), random.randint(2, 3), random.randint(50, 100)))
    cluster.append(gen(100, 200 - random.randint(0, 10), 70 + random.randint(5, 10), random.randint(2, 8)))
    real.append(cluster)
  
  # N, Q <= 100000, M <= 200000 - 7 primjera
  for num in range(7):
    cluster = []
    cluster.append(gen(100000, 200000 - random.randint(0, 50000), 1, random.randint(2, 8)))
    cluster.append(gen(100000, 200000 - random.randint(0, 50000), 2, 1))
    cluster.append(gen(100000, 200000 - random.randint(0, 50000), random.randint(30000, 50000), 1))
    cluster.append(gen(100000, 200000 - random.randint(0, 50000), random.randint(2, 5), random.randint(2, 8)))
    cluster.append(gen(100000, 200000 - random.randint(0, 50000), random.randint(2, 3), random.randint(50000, 100000)))
    cluster.append(gen(100000, 200000 - random.randint(0, 50000), 70000 + random.randint(5000, 10000), random.randint(2, 8)))
    real.append(cluster)

  for i, batch in enumerate(real):
    for j, test in enumerate(batch):
      test.validate()
      print>>sys.stderr, 'Generating test/%s.in.%d%c' \
              % (PROBLEM, i+1, chr(ord('a')+j))
      input = 'test/%s.in.%d%c' % (PROBLEM, i+1, chr(ord('a')+j))
      test.write(file(input, 'wt'))

def main():
  random.seed(303387)
  gen_cases()


if __name__ == "__main__":
  main()

