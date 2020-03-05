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

PROBLEM = "ulica"
sys.setrecursionlimit(1000010)

MAXN = 100

class Test(object):
  def __init__(self, n, p):
    self.n = n
    self.p = p

  def validate(self):
    assert(1 <= self.n <= MAXN)
    for x in self.p:
      assert 1 <= int(x) <= 1000000


  def write(self, fd=sys.stdout):
    print>>fd, self.n
    print>>fd, " ".join(self.p)


def remove_cases():
  cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
  cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
  cases += glob.glob('test/%s.in.*' % PROBLEM)
  cases += glob.glob('test/%s.out.*' % PROBLEM)
  for c in cases:
    print>>sys.stderr, 'Removing ' + c
    os.remove(c)


def f(a, b):
  n = a + b
  p = []
  x = random.randint(1, a)

  for i in range(x):
    p.append(str((i + 1) * 2))

  for i in range(a - x):
    rnd = random.randint(x + 5, 500000)
    while str(rnd * 2) in p:
      rnd = random.randint(x + 5, 500000)

    p.append(str(rnd * 2))

  if b:

    y = random.randint(1, b)

    for i in range(y):
      p.append(str((i * 2 + 1)))

    for i in range(b - y):
      rnd = random.randint(y + 5, 499999)
      while str(rnd * 2 + 1) in p:
        rnd = random.randint(y + 5, 499999)

      p.append(str(rnd * 2 + 1))

  random.shuffle(p)
  return Test(n, p)

def gen_cases():
  remove_cases()

  real = []
  dummy = []

  for i, test in enumerate(dummy):
    test.validate()
    print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
    test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

  dummy.append(Test(3, ["10", "12", "4"]))
  dummy.append(Test(5, ["20", "2", "22", "2020", "2002"]))
  dummy.append(Test(5, ["9", "2", "7", "4", "11"]))

  for i, test in enumerate(dummy):
    test.validate()
    print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
    test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))
  
  # parni
  
  for tt in range(2):
    cluster = []
    cluster.append(f(100, 0))
    real.append(cluster)
  
  # sve

  for tt in range(4):
    cluster = []
    rnd = random.randint(1, 99)
    x = rnd
    y = 100 - rnd
    if tt < 2: cluster.append(f(max(x,y),min(x,y)))
    else: cluster.append(f(min(x,y), max(x,y)))
    real.append(cluster)

  for i, batch in enumerate(real):
    for j, test in enumerate(batch):
      test.validate()
      print>>sys.stderr, 'Generating test/%s.in.%d' \
              % (PROBLEM, i+1)
      input = 'test/%s.in.%d' % (PROBLEM, i+1)
      test.write(file(input, 'wt'))

def main():
  random.seed(303387)
  gen_cases()


if __name__ == "__main__":
  main()

