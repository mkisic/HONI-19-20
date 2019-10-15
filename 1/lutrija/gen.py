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

PROBLEM = "lutrija"
sys.setrecursionlimit(1000010)

MAX = 10**14


class Test(object):
  def __init__(self, a, b):
    self.a = a 
    self.b = b

  def validate(self):
    assert(1 <= self.a <= MAX)
    assert(1 <= self.b <= MAX)

  def write(self, fd=sys.stdout):
    print>>fd, self.a, self.b


def remove_cases():
  cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
  cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
  cases += glob.glob('test/%s.in.*' % PROBLEM)
  cases += glob.glob('test/%s.out.*' % PROBLEM)
  for c in cases:
    print>>sys.stderr, 'Removing ' + c
    os.remove(c)


def prime(x):
  if x < 2: return 0
  i = 2
  while i * i <= x:
    if x % i == 0: return 0
    i += 1
  
  return 1


def singe(n):
  x = 1
  while not prime(x) or prime(x + 2) or prime(x - 2):
    x = random.randint(2, n / 2 - 1) * 2 + 1
  
  return x


def twin(n):
  x = 1
  while not prime(x) or (not prime(x + 2)) and (not prime(x - 2)):
    x = random.randint(2, n / 2 - 1) * 2 + 1

  if prime(x + 2): return (x, x + 2)
  return (x - 2, x)


def double_twin(n):
  x = twin(n)
  return Test(x[0], x[1])


def prevara(n):
  return Test(singe(n), twin(n)[0])


def gen_cases():
  remove_cases()

  real = []
  dummy = []

  dummy.append(Test(13, 11))
  dummy.append(Test(37, 11))
  dummy.append(Test(2, 17))

  for i, test in enumerate(dummy):
    test.validate()
    print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
    test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

  # 1. subtask -- 2 <= A, B <= 1000 i duljina niza je max 3
  # 20%
  
  for i in range(2):
    print("Generiram cluster {}".format(i + 1))
    cluster = []
    
    if not i:
			cluster.append(Test(3, 7))
    else:
		  cluster.append(Test(2, twin(1000)[0]))

    x = twin(1000)
    y = twin(1000)
    while x == y: y = twin(1000)

    cluster.append(Test(x[1], y[1]))

    cluster.append(double_twin(1000))
    cluster.append(prevara(1000))

    real.append(cluster)
  
  # 2. subtask -- 2 <= A, B <= 1000
  # 40%

  for i in range(4):
    print("Generiram cluster {}".format(i + 3))
    cluster = []

    prvi = twin(1000)[0]
    drugi = twin(1000)[0]

    while prvi == drugi or max(prvi - drugi, drugi - prvi) == 2:
      drugi = twin(1000)[0]

    cluster.append(Test(prvi, drugi))
    cluster.append(prevara(1000))

    real.append(cluster)

  # 3. subtask -- 2 <= A, B <= 10^14
  # 40%

  for i in range(4):
    print("Generiram cluster {}".format(i + 7))
    cluster = []

    cluster.append(Test(twin(MAX)[0], twin(MAX)[0]))
    cluster.append(prevara(MAX))
    cluster.append(double_twin(MAX))
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

