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


PROBLEM = "radio"
sys.setrecursionlimit(1000010)

MAXN = 100000
MAXX = 100000

class Test(object):
    def __init__(self, n, x, a, b):
        self.n = n
        self.x = x
        self.a = a
        self.b = b

    def validate(self):
        assert(1 <= self.n <= MAXN)
        assert(1 <= self.x <= MAXX)
        assert(len(self.a) == self.n and len(self.b) == self.n)
        assert(0 <= min(self.a) <= max(self.a) <= 10**5)
        assert(0 <= min(self.b) <= max(self.b) <= 10**5)
        rez = self.x
        for i in range(self.n):
            rez = rez -self.a[i] + self.b[i]
        assert(rez >= 0 and rez < 2**63)

    def write(self, fd=sys.stdout):
        print>>fd, self.n, self.x
        for i in range (self.n):
            print>>fd, self.a[i], self.b[i]


def remove_cases():
    cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
    cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
    cases += glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.out.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)

def gen_random(minn, maxn, maxa, minb):
    n = random.randint(minn, maxn)
    x = random.randint(1, 100000)
    a = []
    b = []
    rez = x
    for i in range(n):
        b.append(random.randint(minb, 100000))
        rez = rez + b[i]
        a.append(random.randint(1, min(maxa, rez)))
        rez = rez - a[i]
    return Test(n,x,a,b)
    
def gen_cases():
    remove_cases()

    real = []
    dummy = []

    dummy.append(Test(
        1,
        10,
        [1],
        [5]

    ))

    dummy.append(Test(
        2,
        7,
        [4, 3],
        [1, 1]
    ))
    
    dummy.append(Test(
        3,
        500,
        [400, 100, 100],
        [200, 50, 20]
    ))

    for i, test in enumerate(dummy):
        test.validate()
        print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
        test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

    # 1. subtask -- N = 1
    for i in range(1, 4):
        print('Generating subtask 1, case ', i)
        real.append(gen_random(1, 1, 100000, 1))
    
    # 2. subtask
    for i in range(4,5):
        print('Generating subtask 1, case ', i)
        real.append(gen_random(1, 100000, 100000, 1))
    
    # 3. subtask --> long long
    for i in range(5,7):
        print('Generating subtask 1, case ', i)
        real.append(gen_random(90000, 100000, 100, 90000))

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
