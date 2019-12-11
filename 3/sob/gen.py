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

PROBLEM = "sob"
sys.setrecursionlimit(1000010)

MAXN = 10**6

class Test(object):
  def __init__(self, n, k):
    self.n = k
    self.m = n - k

  def validate(self):
    assert 1 <= self.n <= self.m
    assert self.n + self.m <= MAXN

  def write(self, fd=sys.stdout):
    print>>fd, self.n, self.m


def remove_cases():
  cases = glob.glob('test/%s.in.*' % PROBLEM)
  cases += glob.glob('test/%s.out.*' % PROBLEM)
  for c in cases:
    print>>sys.stderr, 'Removing ' + c
    os.remove(c)


def rand_pow_2(max_n):
    return 2**random.randint(0, int(math.log(max_n)))

def gen_random(max_n, n_is_pow_2, k_is_pow_2):
    if n_is_pow_2: n = rand_pow_2(max_n)
    else: n = random.randint(2, max_n)

    if k_is_pow_2: k = rand_pow_2(n // 2)
    else: k = random.randint(1, n // 2)

    return Test(n, k)


def gen_cases():
  remove_cases()

  real = []

  # subtask 1 -- K = 2^x
  subtask1 = [gen_random(MAXN, False, True) for _ in range(3)]
  subtask1.append(Test(MAXN, 2**18))
  real.append(subtask1)
  
  # subtask 2 -- N = 2^x
  subtask2 = [gen_random(MAXN, True, False) for _ in range(5)]
  subtask2.append(Test(2**19, 2**18))
  subtask2.append(Test(2**19, 2**17 - random.randint(1, 10000)))
  real.append(subtask2)

  # subtask 3 -- N <= 1000
  subtask3 = [gen_random(1000, False, False) for _ in range(5)]
  subtask3.append(Test(1000, 500))
  subtask3.append(Test(1000, 500 - random.randint(1, 50)))
  real.append(subtask3)

  # subtask 4 -- N <= 10^6
  subtask4 = [gen_random(MAXN, False, False) for _ in range(5)]
  subtask4.append(Test(MAXN, MAXN // 2))
  subtask4.append(Test(MAXN, MAXN // 2 - random.randint(1, 10000)))
  real.append(subtask4)

  for i, batch in enumerate(real):
    for j, test in enumerate(batch):
      test.validate()
      print>>sys.stderr, 'Generating test/%s.in.%d%c' \
              % (PROBLEM, i+1, chr(ord('a')+j))
      input = 'test/%s.in.%d%c' % (PROBLEM, i+1, chr(ord('a')+j))
      test.write(file(input, 'wt'))

def main():
  random.seed(280797)
  gen_cases()


if __name__ == "__main__":
  main()

