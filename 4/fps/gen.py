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

PROBLEM = "FPS"
sys.setrecursionlimit(1000010)

MAXX = 100
MAXY = 100

class Test(object):
    def __init__(self, x, y):
        self.x = x   # array length
        self.y = y   # number of queries
        
    def validate(self):
        assert(1 <= self.x <= MAXX)
        assert(1 <= self.y <= MAXY)
        
    def write(self, fd=sys.stdout):
        print>>fd, self.x, '\n' ,self.y

def remove_cases():
    cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
    cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
    cases += glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.out.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)

def gen_random():
    x = random.randint(1, 100)
    y = random.randint(1, 100)
    return Test(x,y)

def gen_cases():
    remove_cases()

    real = []
    dummy = []

    dummy.append(Test(
        1,
        1
    ))

    dummy.append(Test(
        10,
        1
    ))

    dummy.append(Test(
        10,
        25
    ))

    for i, test in enumerate(dummy):
        test.validate()
        print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
        test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

##  full task
    subtask1 = []
    for i in range(1, 6):
        print('Generating subtask 1, case ', i)
        subtask1.append(gen_random())
        
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
