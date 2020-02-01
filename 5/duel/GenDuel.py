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

PROBLEM = "duel"
sys.setrecursionlimit(1000010)

MAXN = 100

class Test(object):
    def __init__(self, n, p, pat, f, fab):
        self.n = n      #num of tasks
        self.p = p
        self.f = f
        self.pat = pat
        self.fab = fab
        self.bio = []

    def validate(self):
        assert(1 <= self.n <= MAXN)
        assert(0 <= self.p <= MAXN)
        assert(0 <= self.f <= MAXN)
        for i in range(MAXN):
            self.bio.append(0)
        for i in self.pat:
            assert(1 <= i <= self.n)
            assert(self.bio[i] == 0)
            self.bio[i] = 1
        for i in range(MAXN):
            self.bio[i] = 0
        for i in self.fab:
            assert(1 <= i <= self.n)
            assert(self.bio[i] == 0)
            self.bio[i] = 1
            
    def write(self, fd=sys.stdout):
        print>>fd, self.n
        print>>fd, self.p, ' '.join(map(str, self.pat))
        print>>fd, self.f, ' '.join(map(str, self.fab))


def remove_cases():
    cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
    cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
    cases += glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.out.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)

def gen_random(case):
    n = random.randint(MAXN // 2, MAXN)
    if(case == 1):
        n = 2
        p = f = 1
    elif(case == 2):
        p = f = random.randint(0,n)
    else:
        p = random.randint(n // 2,n)
        f = random.randint(n // 2,n)
    pat = random.sample(xrange(1, n), p)
    fab = random.sample(xrange(1, n), f)
        
    return Test(n, p, pat, f, fab)


def gen_cases():
    remove_cases()

    real = []
    dummy = []

    dummy.append(Test(
        4,
        3, [1, 3, 4],
        2, [1, 2]
    ))
    dummy.append(Test(
        4,
        4, [1, 2, 3, 4],
        0, []
    ))
    dummy.append(Test(
        3,
        3, [1, 2, 3],
        3, [1, 2, 3]
    ))

    for i, test in enumerate(dummy):
        test.validate()
        print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
        test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

    subtask1 = []
    for i in range(1, 11):
        print('Generating subtask 1, case ', i)
        if(i < 3):
            subtask1.append(gen_random(1))
        elif(i < 5):
            subtask1.append(gen_random(2))
        else:
            subtask1.append(gen_random(3))

    real.append(subtask1)
    

    for i, batch in enumerate(real):
        for j, test in enumerate(batch):
            test.validate()
            print>>sys.stderr, 'Generating test/%s.in.%d' \
                    % (PROBLEM, j)
            input = 'test/%s.in.%d' % (PROBLEM, j)
            test.write(file(input, 'wt'))

def main():
    random.seed(293487)
    gen_cases()


if __name__ == "__main__":
    main()
