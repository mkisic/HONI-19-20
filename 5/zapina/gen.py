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

PROBLEM = "zapina"
sys.setrecursionlimit(1000010)

MAXN = 350

class Test(object):
  def __init__(self, n):
    self.n = n

  def validate(self):
    assert(1 <= self.n <= MAXN)

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

  dummy.append(Test(1))
  dummy.append(Test(2))
  dummy.append(Test(314))

  for i, test in enumerate(dummy):
    test.validate()
    print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
    test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))
  
  # N <= 7
  
  cluster = []
  for i in range(3, 8):
    cluster.append(Test(i))
  real.append(cluster)
  
  # N <= 20

  cluster = []
  for i in range(10, 21):
    cluster.append(Test(i))
  real.append(cluster)

  # N <= 350

  cluster = []
  for i in range(10):
    cluster.append(Test(random.randint(20, 339)))

  for i in range(340, 351):
    cluster.append(Test(i))

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

