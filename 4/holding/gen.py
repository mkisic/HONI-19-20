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

PROBLEM = "holding"
sys.setrecursionlimit(1000010)

MAXN = 10**2
MAXK = 10**4
MAX = 10**6

class Test(object):
  def __init__(self, n, l, r, k, p):
    self.n = n
    self.l = l
    self.r = r
    self.k = k
    self.p = p

  def validate(self):
    assert(1 <= self.n <= MAXN)
    assert(1 <= self.l <= self.r <= self.n)
    assert(1 <= self.k <= MAXK)

    for x in self.p:
      assert(0 <= x <= MAX)


  def write(self, fd=sys.stdout):
    print>>fd, str(self.n) + " " + str(self.l) + " " + str(self.r) + " " + str(self.k)
    print>>fd, " ".join(list(map(str, self.p)))


def remove_cases():
  cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
  cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
  cases += glob.glob('test/%s.in.*' % PROBLEM)
  cases += glob.glob('test/%s.out.*' % PROBLEM)
  for c in cases:
    print>>sys.stderr, 'Removing ' + c
    os.remove(c)


def random_test(n, rjedn, maks, K):
  k = random.randint(0, K)
  l = random.randint(1, n)
  r = random.randint(l, n)
  if rjedn:
    r = n

  p = []
  for i in range(n):
    p.append(random.randint(0, maks))

  return Test(n, l, r, k, p)


def grdo(n):
  l = n // 2
  r = n
  k = 10000
  p = []
  for i in range(n):
    p.append(1)
  
  for i in range(l-1, r):
    p[i] += 1
  return Test(n, l, r, k, p)


def gen_cases():
  remove_cases()

  real = []
  dummy = []

  for i, test in enumerate(dummy):
    test.validate()
    print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
    test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

  dummy.append(Test(3, 2, 2, 1, [1, 2, 3]))
  dummy.append(Test(5, 2, 3, 3, [21, 54, 12, 2, 0]))
  dummy.append(Test(6, 4, 6, 100, [1, 2, 3, 4, 5, 6]))

  for i, test in enumerate(dummy):
    test.validate()
    print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
    test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))
  
  # N <= 13, R = N
  
  cluster = []
  cluster.append(Test(5, 4, 5, 4, [0, 1, 1, 7, 6]))
  for i in range(1, 6):
    if i % 2 == 1: cluster.append(random_test(13, 1, MAX, 13 * i))
    if i % 2 == 0: cluster.append(random_test(13, 1, 20, 13 * i))

  cluster.append(grdo(12))
  real.append(cluster)
  
  # N <= 50, R = N

  cluster = []
  for i in range(1, 6):
    if i % 2 == 1: cluster.append(random_test(50, 1, MAX, 50 * i))
    if i % 2 == 0: cluster.append(random_test(50, 1, 20, 50 * i))
  cluster.append(grdo(50))
  real.append(cluster)

  # N <= 50

  cluster = []
  for i in range(1, 6):
    if i % 2 == 1: cluster.append(random_test(50, 0, MAX, 50 * i))
    if i % 2 == 0: cluster.append(random_test(50, 0, 20, 50 * i))
  cluster.append(grdo(50))
  real.append(cluster)

  # N <= 100

  cluster = []
  for i in range(1, 6):
    if i % 2 == 1: cluster.append(random_test(100, 0, MAX, 10 * 100 * i))
    if i % 2 == 0: cluster.append(random_test(100, 0, 50, 10 * 100 * i))

  cluster.append(grdo(100))
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

