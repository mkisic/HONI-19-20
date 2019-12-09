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

PROBLEM = "grudanje"
sys.setrecursionlimit(1000010)

MAXN = 10**5
MAXQ = 10**5

class Test(object):
  def __init__(self, s, q, qs, p):
    self.s = s
    self.n = len(s)
    self.q = q
    self.qs = qs
    self.p = p

  def validate(self):
    assert(1 <= self.n <= MAXN)
    assert(1 <= self.q <= MAXQ)

    for l, r in self.qs:
      assert 1 <= l <= r <= self.n, "krivi interval"

  def write(self, fd=sys.stdout):
    print>>fd, self.s
    print>>fd, self.q
    for l, r in self.qs:
      print>>fd, l, r
    print>>fd, " ".join(list(map(str, self.p)))


def remove_cases():
  cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
  cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
  cases += glob.glob('test/%s.in.*' % PROBLEM)
  cases += glob.glob('test/%s.out.*' % PROBLEM)
  for c in cases:
    print>>sys.stderr, 'Removing ' + c
    os.remove(c)


def gen_random(n, q, abc):
  s = ""
  p = []
  for i in range(n):
    p.append(i + 1)

  for i in range(10):
    l = random.randint(0, n-1)
    r = random.randint(0, n-1)
    t = p[l]
    p[l] = p[r]
    p[r] = t

  alfabet = ""
  for i in range(abc):
    alfabet += chr(ord('a') + i)

  for i in range(n):
    s += random.choice(alfabet)

  qs = []

  for i in range(q):
    l = random.randint(1, n/2)
    r = random.randint(1, n/2)
    l += n//10
    r += n//10
    l %= n
    r %= n
    l += 1
    r += 1
    if r < l:
      t = l
      l = r
      r = t

    qs.append((l, r))

  return Test(s, q, qs, p)



def gen_cases():
  remove_cases()

  real = []
  dummy = []

  for i, test in enumerate(dummy):
    test.validate()
    print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
    test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

  dummy.append(Test("aaaaa", 2, [(1, 2), (4, 5)], [2, 4, 1, 5, 3]));
  dummy.append(Test("abbabaab", 3, [(1, 3), (4, 7), (3, 5)], [6, 3, 5, 1, 4, 2, 7, 8]));
  dummy.append(Test("abcd", 1, [(1, 4)], [1, 2, 3, 4]));

  for i, test in enumerate(dummy):
    test.validate()
    print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
    test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))
  
  # N, Q <= 500
  # 20% - 2 primjera
  
  for test in range(2):
    cluster = []
    cluster.append(gen_random(500, 500, 26))
    cluster.append(gen_random(500, 500, 4))
    real.append(cluster)
  
  # N, Q <= 3000
  # 30% - 3 primjera

  for test in range(3):
    cluster = []
    cluster.append(gen_random(3000, 3000, 26))
    cluster.append(gen_random(3000, 3000, 4))
    real.append(cluster)

  # samo slova "a"
  # 20% - 2 primjera

  for test in range(2):
    cluster = []
    cluster.append(gen_random(MAXN, MAXQ, 1))
    real.append(cluster)

  # N, Q <= 10^5
  # 30% - 3 primjera

  for test in range(3):
    cluster = []
    cluster.append(gen_random(MAXN, MAXQ, 26))
    cluster.append(gen_random(MAXN, MAXQ, 4))
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

