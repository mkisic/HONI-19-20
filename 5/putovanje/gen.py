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

PROBLEM = "putovanje"
sys.setrecursionlimit(1000010)

MAXN = 200000

class Test(object):
    def __init__(self, n, a, b, c1, c2):
        self.n = n   # broj komadica
        self.a = a   # gradovi A
        self.b = b   # gradovi B
        self.c1 = c1 # cijene c1
        self.c2 = c2 # cijene c2

    def validate(self):
        assert(2 <= self.n <= MAXN)
        assert(len(self.a) == self.n - 1)
        assert(len(self.b) == self.n - 1)
        assert(len(self.c1) == self.n - 1)
        assert(len(self.c2) == self.n - 1)
        assert(1 <= min(self.a) <= max(self.a) <= self.n)
        assert(1 <= min(self.b) <= max(self.b) <= self.n)
        assert(1 <= min(self.c1) <= max(self.c1) <= 100000)
        assert(1 <= min(self.c2) <= max(self.c2) <= 100000)
        for i in range(self.n - 1):
            assert(self.a[i] < self.b[i])
            assert(self.c1[i] <= self.c2[i])

    def write(self, fd=sys.stdout):
        print>>fd, self.n
        for i in range(self.n - 1):
            print>>fd, self.a[i], self.b[i], self.c1[i], self.c2[i]


def remove_cases():
    cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
    cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
    cases += glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.out.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)

def gen_random(minn, maxn, minc1, maxc1, minc2, maxc2, lanac):
    n = random.randint(minn, maxn)
    pom = []
    a = []
    b = []
    c1 = []
    c2 = []
    for i in range(n):
        pom.append(i + 1)
    random.shuffle(pom)
    for i in range(1, n):
        a.append(pom[i])
        if lanac:
            b.append(pom[i - 1])
        else:
            b.append(pom[random.randint(0, i - 1)])
        c1.append(random.randint(minc1, maxc1))
        c2.append(random.randint(minc2, maxc2))
    for i in range(n - 1):
        if a[i] > b[i]:
            a[i], b[i] = b[i], a[i]
        if c1[i] > c2[i]:
            c1[i], c2[i] = c2[i], c1[i]
    return Test(n, a, b, c1, c2)

def neprobojni(minn, maxn, minc1, maxc1, minc2, maxc2, dodatni):
    n = random.randint(minn, maxn)
    gornja = n - dodatni
    tr = gornja
    assert(gornja > 1)
    a = []
    b = []
    c1 = []
    c2 = []
    while tr > 0:
        tr -= 2
        if tr > 0:
            a.append(tr)
            b.append(tr + 2)
            c1.append(random.randint(minc1, maxc1))
            c2.append(random.randint(minc2, maxc2))
    assert(tr == 0 or tr == -1)
    if tr == 0:
        tr = 1
    else:
        tr = 2
    a.append(1)
    b.append(2)
    c1.append(random.randint(minc1, maxc1))
    c2.append(random.randint(minc2, maxc2))
    while tr < gornja:
        tr += 2
        if tr < gornja:
            a.append(tr - 2)
            b.append(tr)
            c1.append(random.randint(minc1, maxc1))
            c2.append(random.randint(minc2, maxc2))
    for i in range(dodatni):
        a.append(gornja + i + 1)
        b.append(random.randint(1, gornja + i))
        c1.append(random.randint(minc1, maxc1))
        c2.append(random.randint(minc2, maxc2))
    for i in range(n - 1):
        if a[i] > b[i]:
            a[i], b[i] = b[i], a[i]
        if c1[i] > c2[i]:
            c1[i], c2[i] = c2[i], c1[i]
    return Test(n, a, b, c1, c2)

def gen_cases():
    remove_cases()

    real = []
    dummy = []

    dummy.append(Test(
        4,
        [1, 1, 2],
        [2, 3, 4],
        [3, 2, 1],
        [5, 4, 3]
    ))

    dummy.append(Test(
        4,
        [1, 3, 2],
        [4, 4, 4],
        [5, 4, 2],
        [5, 7, 6]
    ))

    dummy.append(Test(
        5,
        [1, 1, 1, 1],
        [2, 3, 4, 5],
        [2, 2, 2, 2],
        [3, 3, 3, 3]
    ))

    for i, test in enumerate(dummy):
        test.validate()
        print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
        test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

    # N do 2000
    subtask = []
    subtask.append(gen_random(2, 2, 1, 1, 3, 3, False))
    subtask.append(gen_random(1500, 2000, 100, 200, 2000, 40000, False))
    subtask.append(gen_random(2000, 2000, 10, 100, 10, 100, False))
    subtask.append(gen_random(2000, 2000, 10000, 50000, 100000, 100000, False))
    subtask.append(gen_random(2000, 2000, 100000, 100000, 100000, 100000, False))
    subtask.append(gen_random(100, 200, 100, 1000, 1000, 2000, True))
    subtask.append(gen_random(500, 1000, 1000, 5000, 1000, 5000, False))
    subtask.append(gen_random(1000, 2000, 10000, 20000, 50000, 100000, False))
    subtask.append(gen_random(1000, 2000, 1, 1, 10, 20, False))
    real.append(subtask)
    
	# lanac
    subtask = []
    subtask.append(gen_random(50000, 100000, 100, 120, 2000, 2100, True))
    subtask.append(gen_random(80000, 100000, 400, 450, 1000, 1100, True))
    subtask.append(gen_random(90000, 100000, 100000, 100000, 100000, 100000, True))
    subtask.append(gen_random(100000, 100000, 5000, 10000, 80000, 100000, True))
    subtask.append(gen_random(500, 1000, 10000, 20000, 20000, 30000, True))
    subtask.append(gen_random(50000, 100000, 100, 120, 2000, 2100, True))
    subtask.append(gen_random(50000, 100000, 10, 100, 20000, 100000, True))
    subtask.append(gen_random(50000, 100000, 5000, 5100, 5100, 5200, True))
    subtask.append(neprobojni(50000, 100000, 2000, 2100, 10000, 10200, 0))
    subtask.append(neprobojni(90000, 100000, 10000, 20000, 90000, 100000, 0))
    subtask.append(neprobojni(100000, 100000, 30000, 50000, 90000, 100000, 0))
    subtask.append(neprobojni(100000, 100000, 100000, 100000, 100000, 100000, 0))
    real.append(subtask)

    # bez dodatnih ogranicenja
    subtask = []
    subtask.append(gen_random(80000, 100000, 1200, 2000, 50000, 60000, False))
    subtask.append(gen_random(80000, 100000, 2000, 3000, 4000, 5000, False))
    subtask.append(gen_random(90000, 100000, 200, 300, 6000, 8000, False))
    subtask.append(gen_random(1000, 2000, 2100, 3200, 4300, 5400, False))
    subtask.append(gen_random(20000, 50000, 2, 5, 8, 11, False))
    subtask.append(gen_random(80000, 85000, 20000, 30000, 90000, 100000, False))
    subtask.append(neprobojni(80000, 100000, 20, 30, 4000, 5000, 8))
    subtask.append(neprobojni(100000, 100000, 100000, 100000, 100000, 100000, 10))
    subtask.append(neprobojni(90000, 100000, 5000, 10000, 50000, 100000, 100))
    subtask.append(neprobojni(1000, 2000, 5, 10, 100, 500, 5))
    real.append(subtask)
    
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

