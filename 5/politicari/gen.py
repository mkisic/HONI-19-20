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

PROBLEM = "politicari"
sys.setrecursionlimit(1000010)

MAXN = 500
MAXK = 10**18

class Test(object):
    def __init__(self, n, k, mat):
        self.n = n      # number of politicians
        self.k = k      # TV show episode
        self.mat = mat  # transition matrix

    def validate(self):
        assert(2 <= self.n <= MAXN)
        assert(1 <= self.k <= MAXK)

        for i, row in enumerate(self.mat):
            assert(row[i] == 0)
            for j, x in enumerate(row):
                if i == j: continue
                assert(1 <= x <= self.n)
                assert(x != i + 1)

    def write(self, fd=sys.stdout):
        print>>fd, self.n, self.k
        for row in self.mat:
            print>>fd, ' '.join(list(map(str, row)))


def remove_cases():
    cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
    cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
    cases += glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.out.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)


def gen_rand(n, k):
    mat = []
    for i in range(n):
        row = []
        for j in range(n):
            if i == j:
                row.append(0)
            else:
                x = i + 1
                while x == i + 1:
                    x = random.randint(1, n)
                row.append(x)
        mat.append(row)
    return Test(n, k, mat)

def gen_cases():
    remove_cases()

    real = []
    dummy = []

    dummy.append(Test(
        2, 4,
        [[0, 2],
         [1, 0]]
    ))

    dummy.append(Test(
        3, 7,
        [[0, 3, 2],
         [3, 0, 3],
         [2, 1, 0]]
    ))

    dummy.append(Test(
        4, 7,
        [[0, 4, 3, 2],
         [4, 0, 4, 1],
         [2, 1, 0, 1],
         [3, 2, 3, 0]]
    ))

    for i, test in enumerate(dummy):
        test.validate()
        print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
        test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

    real = []

    # gen 250 random small tests
    # for i in range(250):
        # real.append(gen_rand(random.randint(1, 500), random.randint(1, 100000)))

    # gen 7 small tests
    real.append(gen_rand(10, 1))
    real.append(gen_rand(20, 2))
    real.append(gen_rand(134, random.randint(1, 100000)))
    real.append(gen_rand(231, random.randint(1, 100000)))
    real.append(gen_rand(450, random.randint(50000, 100000)))
    real.append(gen_rand(500, random.randint(50000, 100000)))
    real.append(gen_rand(500, 100000))

    # gen 7 large tests
    real.append(gen_rand(51, random.randint(10**9, 2*(10**9))))
    real.append(gen_rand(134, random.randint(10**9, 2*(10**9))))
    real.append(gen_rand(217, random.randint(10**17, 10**18)))
    real.append(gen_rand(397, random.randint(10**17, 10**18)))
    real.append(gen_rand(450, random.randint(10**17, 10**18)))
    real.append(gen_rand(500, random.randint(10**17, 10**18)))
    real.append(gen_rand(500, 10**18))

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

