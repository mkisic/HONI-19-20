#!/usr/bin/python3

doc = """
  Cenerate all test cases in test/:  gen.py
"""

import sys
import glob
import os
import random
import subprocess
import math
import string

PROBLEM = 'nivelle'
sys.setrecursionlimit(1000010)

MAXN = 10**5
ALPHA = 26

class Test(object):
  def __init__(self, s):
    self.n = len(s)
    self.s = s

  def validate(self):
    assert 1 <= self.n <= MAXN
    assert len(self.s) == self.n

  def write(self, fd=sys.stdout):
    print(self.n, file=fd)
    print(self.s, file=fd)


def remove_cases():
  cases = glob.glob('test/%s.in.*' % PROBLEM)
  cases += glob.glob('test/%s.out.*' % PROBLEM)
  for c in cases:
    print('Removing ' + c, file=sys.stderr)
    os.remove(c)


def gen_smart(n, a):
    b = random.randint(1, a - 1)
    m = min(n, n * b // a + random.randint(1, int(math.sqrt(n))))

    A = string.ascii_lowercase[:a]
    B = random.sample(A, b)

    d = random.randint(0, n - m)

    s = ''.join(random.choices(A, k=d) +
                random.choices(B, k=m) +
                random.choices(A, k=n - d - m))
    return Test(s)

def gen_random(n, a):
    assert n >= a
    A = string.ascii_lowercase[:a]
    s = list(A) + random.choices(A, k=n - a)
    random.shuffle(s)
    s = ''.join(s)
    return Test(s)


def gen_cases():
  remove_cases()

  real = []

  # subtask 1 -- N <= 100
  subtask1 = [gen_smart(100, ALPHA) for _ in range(5)]
  subtask1.append(gen_random(100, ALPHA))
  real.append(subtask1)

  # subtask 2 -- N <= 2000
  subtask2 = [gen_smart(2000, ALPHA) for _ in range(5)]
  subtask2.append(gen_random(2000, ALPHA))
  real.append(subtask2)

  # subtask 3 -- N <= 10^5, 2 letters
  subtask3 = [gen_smart(10**5, 2) for _ in range(5)]
  subtask3.append(gen_random(10**5, 2))
  real.append(subtask3)

  # subtask 4 -- N <= 10^5, 5 letters
  subtask4 = [gen_smart(10**5, 5) for _ in range(5)]
  subtask4.append(gen_random(10**5, 5))
  real.append(subtask4)

  # subtask 5 -- N <= 10^5
  subtask5 = [gen_smart(10**5, ALPHA) for _ in range(5)]
  subtask5.append(gen_random(10**5, ALPHA))
  real.append(subtask5)
  

  for i, batch in enumerate(real):
    for j, test in enumerate(batch):
      test.validate()
      print('Generating test/%s.in.%d%c' % (PROBLEM, i+1, chr(ord('a')+j)),
          file=sys.stderr)
      input = 'test/%s.in.%d%c' % (PROBLEM, i+1, chr(ord('a')+j))
      with open(input, 'w') as f:
          test.write(f)

def main():
  random.seed(280797)
  gen_cases()


if __name__ == '__main__':
  main()

