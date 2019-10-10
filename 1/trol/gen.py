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

PROBLEM = "trol"
sys.setrecursionlimit(1000010)

MAXN = 2**60
MAXQ = 100

class Test(object):
    def __init__(self, q, l, r):
        self.q = q  # number of queries
        self.l = l  # left interval bounds
        self.r = r  # right interval bounds

    def validate(self):
        assert(1 <= self.q <= MAXQ)
        assert(len(self.l) == self.q)
        assert(len(self.r) == self.q)
        for i in range(self.q):
            assert(1 <= self.l[i] <= self.r[i] <= MAXN)

    def write(self, fd=sys.stdout):
        print>>fd, self.q
        for i in range(self.q):
            print>>fd, self.l[i], self.r[i]


def remove_cases():
    cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
    cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
    cases += glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.out.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)


def gen_all_pairs(minval, maxval):
    l = []
    r = []
    for i in range(minval, maxval + 1):
        for j in range(i, maxval + 1):
            l.append(i)
            r.append(j)
    return Test(len(l), l, r)


def gen_random(q, maxdiff, maxval):
    l = []
    r = []
    for i in range(q):
        ll = random.randint(1, maxval)
        rr = min(maxval, ll + random.randint(0, maxdiff))
        l.append(ll)
        r.append(rr)
    return Test(q, l, r)


def gen_cases():
    remove_cases()

    real = []
    dummy = []

    dummy.append(Test(
        1,
        [1],
        [5]
    ))

    dummy.append(Test(
        2,
        [9, 44],
        [13, 45]
    ))

    dummy.append(Test(
        1,
        [1998],
        [2018]
    ))

    for i, test in enumerate(dummy):
        test.validate()
        print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
        test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))


    # 1. test -- 1 <= l <= r <= 9
    real.append(gen_all_pairs(1, 9))

    # 2. test -- r - l <= 1000, everything fits in 32-bit integer
    real.append(gen_random(100, 1000, 10**6))

    # 3. test -- r - l <= 1000
    real.append(gen_random(100, 1000, 2**60))

    # 4. test, everything fits in 32 bit integer
    real.append(gen_random(100, 10**8, 10**9))

    # 5. test
    real.append(gen_random(100, 10**13, 2**60))

    for i, test in enumerate(real):
        test.validate()
        print>>sys.stderr, 'Generating test/%s.in.%d' \
                % (PROBLEM, i+1)
        input = 'test/%s.in.%d' % (PROBLEM, i+1)
        test.write(file(input, 'wt'))


def main():
    random.seed(293487)
    gen_cases()


if __name__ == "__main__":
    main()

