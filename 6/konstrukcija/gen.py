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

PROBLEM = "konstrukcija"
sys.setrecursionlimit(1000010)

MAXN = 10**18

class Test(object):
  def __init__(self, n):
    self.n = n

  def validate(self):
    assert(-MAXN <= self.n <= MAXN)

  def write(self, fd=sys.stdout):
    print>>fd, self.n


def remove_cases():
  cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
  cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
  cases += glob.glob('test/%s.in.*' % PROBLEM)
  cases += glob.glob('test/%s.out.*' % PROBLEM)
  for c in cases:
    print>>sys.stderr, 'Removing ' + c
    os.remove(c)


def gen_cases():
  remove_cases()

  real = []
  dummy = []

  for i, test in enumerate(dummy):
    test.validate()
    print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
    test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

  dummy.append(Test(0))
  dummy.append(Test(1))
  dummy.append(Test(2))

  for i, test in enumerate(dummy):
    test.validate()
    print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
    test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))
  
  # 1 <= N < 500
  
  cluster = []
  for i in range(4):
    cluster.append(Test(random.randint(1, 498)))
  cluster.append(Test(449))
  real.append(cluster)
  
  # -300 < N <= -1

  cluster = []
  for i in range(4):
    cluster.append(Test(random.randint(-298, -1)))
  cluster.append(Test(-299))
  real.append(cluster)

  # |N| < 10**4

  cluster = []
  for i in range(2):
    cluster.append(Test(random.randint(1000, 9999)))
  for i in range(2):
    cluster.append(Test(random.randint(-9999, -1000)))
  cluster.append(Test(0))
  real.append(cluster)

  # |N| < 10**18

  cluster = []

  for i in range(3):
    cluster.append(Test(random.randint(10000, 10**18))) 
  for i in range(3):
    cluster.append(Test(random.randint(-10**18, -10000)))

  cluster.append(Test(2**60 - 1 - 2**58))
  cluster.append(Test(-1 * (2**60 - 1 - 2**58)))
  cluster.append(Test(2**59))
  cluster.append(Test(-2**59))
  cluster.append(Test(2**59 - 1))
  cluster.append(Test(-1 * (2**59 - 1)))

  real.append(cluster)


  for i, batch in enumerate(real):
    for j, test in enumerate(batch):
      test.validate()
      print>>sys.stderr, 'Generating test/%s.in.%d%c' \
              % (PROBLEM, i+1, chr(ord('a')+j))
      input = 'test/%s.in.%d%c' % (PROBLEM, i+1, chr(ord('a')+j))
      test.write(file(input, 'wt'))

def main():
  random.seed(293387)
  gen_cases()


if __name__ == "__main__":
  main()

