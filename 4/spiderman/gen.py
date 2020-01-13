#!/usr/bin/python2

doc = """
  Cenerate all test cases in test/:  gen.py
"""

import collections
import sys
import glob
import os
import random
import subprocess
import math

PROBLEM = "spiderman"
sys.setrecursionlimit(1000010)

MAXN = 300000
MAXH = 1000000

class Test(object):
    def __init__(self, n, k, h):
        self.n = n        # number of skyscrapers
        self.k = k        # constant
        self.h = h        # heights of skyscrapers

    def validate(self):
        assert(1 <= self.n <= MAXN)
        assert(0 <= self.k < MAXH)
        assert(len(self.h) == self.n)
        for hi in self.h:
            assert(1 <= hi <= MAXH)

    def write(self, fd=sys.stdout):
        print>>fd, self.n, self.k
        print>>fd, ' '.join(map(str, self.h))


def remove_cases():
    cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
    cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
    cases = glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.out.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)


def gen_unique_h(n, k_zero=False):
    h = set()
    k = random.randint(1, 500)
    if k_zero: k = 0
    while len(h) < n:
        x = random.randint(1, MAXH)
        if x in h: continue
        h.add(x)
        lim = random.randint(1, 10)
        for i in range(0, lim):
            if len(h) == n: break
            j = random.randint(0, MAXH / x)
            y = x * j + k
            if 1 <= y <= MAXH: h.add(y)
        if len(h) == n: break
        if len(h) % 2 == 0:
            for d in range(1, x - k):
                if d * d > x - k: break
                if (x - k) % d != 0: continue
                h.add(d)
                if len(h) == n: break
                h.add((x - k) / d)
                if len(h) == n: break

    h_list = list(h)
    random.shuffle(h_list)
    return Test(n, k, h_list)


def gen_duplicate_h(n, limit_h, k_zero=False):
    h = set()
    k = random.randint(1, 500)
    if k_zero: k = 0
    while len(h) < limit_h:
        x = random.randint(1, MAXH)
        if x in h: continue
        h.add(x)
        lim = random.randint(1, 10)
        for i in range(0, lim):
            if len(h) == limit_h: break
            j = random.randint(0, MAXH / x)
            y = x * j + k
            if 1 <= y <= MAXH: h.add(y)
        if len(h) == limit_h: break
        if len(h) % 2 == 0:
            for d in range(1, x - k):
                if d * d > x - k: break
                if (x - k) % d != 0: continue
                h.add(d)
                if len(h) == limit_h: break
                h.add((x - k) / d)
                if len(h) == limit_h: break

    h_list = list(h)
    while len(h_list) < n:
        x = h_list[random.randint(0, len(h_list) - 1)]
        for k in range(1, random.randint(1, 10)):
            h_list.append(x)
            if len(h_list) == n: break

    random.shuffle(h_list)
    return Test(n, k, h_list)


def gen_cases():
    remove_cases()

    dummy = []

    dummy.append(Test(
        2, 1,
        [5, 5]
    ))

    dummy.append(Test(
        6, 3,
        [4, 3, 12, 6, 8, 2]
    ))

    dummy.append(Test(
        5, 1,
        [1, 3, 5, 7, 2]
    ))

    for i, test in enumerate(dummy):
        test.validate()
        print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
        test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

    real = []

    # Test 1 -> N = 2000, different hi
    real.append(gen_unique_h(2000))

    # Test 2 -> N = 2000, duplicate hi
    real.append(gen_duplicate_h(2000, 1000))

    # Test 3 -> N = 100 000, 2000 distinct hi
    real.append(gen_duplicate_h(100000, 2000))

    # Test 4 -> N = 300 000, 2000 distinct hi
    real.append(gen_duplicate_h(300000, 2000))

    # Test 5 -> N = 300 000, K = 0, distinct hi
    real.append(gen_unique_h(100000, True))

    # Test 6 -> N = 300 000, K = 0, duplicate hi
    real.append(gen_duplicate_h(300000, 90000, True))

    # Test 7, 8 -> N = 100 000, distinct hi
    for i in range(2):
        real.append(gen_unique_h(100000))

    # Test 9, 10 -> N = 300 000, duplicate hi
    for i in range(2):
        real.append(gen_duplicate_h(300000, 90000))

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

