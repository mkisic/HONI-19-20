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

PROBLEM = "popcount"
sys.setrecursionlimit(1000010)

MAXN = 500

class Test(object):
    def __init__(self, n, k):
        self.n = n        # number of bits
        self.k = k        # number of commands

    def validate(self):
        assert(1 <= self.n <= MAXN)
        assert(1 <= 2**self.k >= self.n)

    def write(self, fd=sys.stdout):
        print>>fd, self.n, self.k


def remove_cases():
    # ovaj puta ne diramo dummy primjere jer je output rucno napisan
    # cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
    # cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
    cases = glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.out.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)


def gen_cases():
    remove_cases()

    real = []

    # 1. subtask -- 1 <= N <= 100, K = N - 1
    subtask1 = []
    for i in range(2, 10):
        subtask1.append(Test(i, i - 1))

    for i in range(10, 16):
        n = random.randint(10, 100)
        subtask1.append(Test(n, n - 1))

    real.append(subtask1)

    # 2. subtask -- N = 500, K = 128
    subtask2 = [Test(500, 128)]
    real.append(subtask2)

    # 3. subtask -- 1 <= N = 40, K = 7
    subtask3 = []
    subtask3.append(Test(1, 7))
    for i in range(21, 41):
        subtask3.append(Test(i, 7))

    real.append(subtask3)

    # 4. subtask -- 100 <= N <= 500, K = 10
    subtask4 = []

    # 5 random
    for i in range(1, 6):
        subtask4.append(Test(random.randint(100, 500), 10))

    # blizu 2^k
    subtask4.append(Test(127, 10))
    subtask4.append(Test(128, 10))
    subtask4.append(Test(129, 10))
    subtask4.append(Test(255, 10))
    subtask4.append(Test(256, 10))
    subtask4.append(Test(257, 10))

    # max primjer
    subtask4.append(Test(500, 10))
    real.append(subtask4)

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

