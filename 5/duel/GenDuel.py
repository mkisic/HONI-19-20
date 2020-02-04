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

MAXN = pow(10,18)
MAXK = 1000

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
        assert(0 <= self.p <= MAXK)
        assert(0 <= self.f <= MAXK)
        assert(len(self.pat) == len(set(self.pat)))
        assert(len(self.fab) == len(set(self.fab)) )           

    def write(self, fd=sys.stdout):
        print>>fd, self.n
        print>>fd, self.p
        for i in self.pat:
            print>>fd, i
        print>>fd, self.f
        for i in self.fab:
            print>>fd, i
            
def remove_cases():
    cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
    cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
    cases += glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.out.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)

def gen_random(case):
    if(case == 1):
        n = 3
        p = f = 2
    elif(case == 2):
        n = random.randint(500, 1000)
        p = random.randint(min(500 ,n // 2), min(1000, n))
        f = random.randint(min(500 ,n // 2), min(1000, n))
        
    elif(case == 3):
        n = random.randint(500000000, 1000000000)
        p = random.randint(min(500 ,n // 2), min(1000, n))
        f = random.randint(min(500 ,n // 2), min(1000, n))
           
    else:
        n = random.randint(MAXN // 2, MAXN)
        p = random.randint(min(500 ,n // 2), min(1000, n))
        f = random.randint(min(500 ,n // 2), min(1000, n))

    t = random.randint(0, min(p,f))
        
    pat = []
    fab = []
    if(n < 2000):
        pat = random.sample(xrange(1, n), p)
    else:
        for i in range(p):
            pat.append(random.randint(1,n))
    for i in range (t):
        fab.append(pat[i])
    while(len(fab) != f):
        x = random.randint(1,n)
        if(not(x in fab)):
            fab.append(x)
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
        1234567890,
        3, [100000, 2000000, 987],
        3, [100000, 24, 8]
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
        elif(i < 7):
            subtask1.append(gen_random(2))
        elif(i < 9):
            subtask1.append(gen_random(3))
        else:
            subtask1.append(gen_random(4))
    real.append(subtask1)
    

    for i, batch in enumerate(real):
        for j, test in enumerate(batch):
            test.validate()
            print>>sys.stderr, 'Generating test/%s.in.%d' \
                    % (PROBLEM, j + 1)
            input = 'test/%s.in.%d' % (PROBLEM, j + 1)
            test.write(file(input, 'wt'))

def main():
    random.seed(293487)
    gen_cases()


if __name__ == "__main__":
    main()
