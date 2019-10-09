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

PROBLEM = "zapatak"
sys.setrecursionlimit(1000010)

MAXN = 300000

class Test(object):
    def __init__(self, n, x):
        self.n = n   # array length
        self.x = x   # [(1, 2), (2, 3), (n-1, n), (n, 1)]

    def validate(self):
        assert(1 <= self.n <= MAXN)
        assert(len(self.x) == self.n)
        assert(1 <= min(self.x) <= max(self.x) <= 3)

    def write(self, fd=sys.stdout):
        print>>fd, self.n
        print>>fd, ''.join(map(str, self.x))


def remove_cases():
    cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
    cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
    cases += glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.out.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)

def gen_random(n):
    x = [random.randint(1, 3) for x in range(n)]
    return Test(n, x)

# n is odd
def gen_random_yes(n):
    x = [random.randint(1, 3) for x in range(n-2)]
    a = x.count(1)
    b = x.count(2)
    c = x.count(3)
    if a%2 == 0:
        x.append(1)
    if b%2 == 0:
        x.append(2)
    if c%2 == 0:
        x.append(3)
    if len(x) < n:
        x.append(1)
        x.append(1)
    return Test(n, x)

def gen_allthesame(n):
    u = random.randint(1, 3)
    x = [u for x in range(n)]
    return Test(n, x)

def gen_cases():
    remove_cases()

    real = []
    dummy = []

    dummy.append(Test(
        5,
        [3, 2, 3, 1, 3]
    ))



    for i, test in enumerate(dummy):
        test.validate()
        print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
        test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

    # 1. subtask -- 4 <= n <= 50
    subtask1 = []
    for i in range(1, 6):
        print('Generating subtask 1, case ', i)
        subtask1.append(gen_random(10))

    for i in range(6, 20):
        print('Generating subtask 1, case ', i)
        subtask1.append(gen_random(40))

    real.append(subtask1)

    # 1.subtask -- 4 <= n <= 100000
    subtask2 = []
    for i in range(10):
        print('Generating subtask 2, case ', i)
        subtask2.append(gen_random_yes(random.randint(48000, 50000)*2 + 1))

    real.append(subtask2)
    
    for i, batch in enumerate(real):
        for j, test in enumerate(batch):
            test.validate()
            print>>sys.stderr, 'Generating test/%s.in.%d%c' \
                    % (PROBLEM, i+1, chr(ord('a')+j))
            input = 'test/%s.in.%d%c' % (PROBLEM, i+1, chr(ord('a')+j))
            test.write(file(input, 'wt'))

def main():
    random.seed(2934387)
    gen_cases()


if __name__ == "__main__":
    main()

