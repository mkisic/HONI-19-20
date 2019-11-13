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

PROBLEM = "slagalica"
sys.setrecursionlimit(1000010)

MAXN = 100000

class Test(object):
    def __init__(self, n, x, a):
        self.n = n   # broj komadica
        self.x = x   # [x1, x2, ... xn]
        self.a = a   # [a1, a2, ... an]

    def validate(self):
        assert(2 <= self.n <= MAXN)
        assert(len(self.x) == self.n)
        assert(len(self.a) == self.n)
        assert(1 <= min(self.x) <= max(self.x) <= 8)
        assert(1 <= min(self.a) <= max(self.a) <= 10**9)

    def write(self, fd=sys.stdout):
        print>>fd, self.n
        for i in range(self.n):
            print>>fd, self.x[i], self.a[i]


def remove_cases():
    cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
    cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
    cases += glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.out.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)

def gen_random(minn, maxn, br1, br4, poc, kraj):
    n = random.randint(minn, maxn)
    a = []
    ai = random.randint(1, n)
    for i in range(n):
        a.append(ai)
        increment = random.randint(1, 10**9 // n)
        ai += increment
    random.shuffle(a)
    x = []
    x.append(poc)
    x.append(kraj)
    for i in range(br1):
        x.append(1)
    for i in range(br4):
        x.append(4)
    for i in range(n - 2 - br1 - br4):
        x.append(random.randint(2, 3))
    random.shuffle(x)
    return Test(n, x, a)

def gen_cases():
    remove_cases()

    real = []
    dummy = []

    dummy.append(Test(
        5,
        [1, 2, 2, 8, 6],
        [5, 7, 3, 4, 1]
    ))

    dummy.append(Test(
        3,
        [5, 7, 4],
        [1, 2, 3]
    ))

    dummy.append(Test(
        5,
        [2, 2, 2, 8, 6],
        [5, 7, 3, 4, 1]
    ))

    for i, test in enumerate(dummy):
        test.validate()
        print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
        test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

    # N do 4
    # 1
    subtask1 = []
    subtask1.append(gen_random(4, 4, 1, 1, 5, 8))
    subtask1.append(gen_random(4, 4, 1, 0, 5, 8))
    real.append(subtask1)
    
    # N do 10
    # 2
    subtask2 = []
    subtask2.append(gen_random(10, 10, 2, 2, 6, 7))
    subtask2.append(gen_random(10, 10, 2, 3, 6, 7))
    real.append(subtask2)

    # samo 1 i 4
    # 3
    subtask3 = []
    n = random.randint(80000, 99999)
    if n % 2 == 0:
        n += 1
    subtask3.append(gen_random(n, n, (n - 2) // 2, (n - 2) // 2 + 1, 5, 7))
    n = random.randint(80000, 99999)
    if n % 2 == 1:
        n += 1
    subtask3.append(gen_random(n, n, (n - 2) // 2, (n - 2) // 2, 5, 7))
    real.append(subtask3)
    # 4
    subtask4 = []
    n = random.randint(80000, 99999)
    if n % 2 == 1:
        n += 1
    subtask4.append(gen_random(n, n, (n - 2) // 2, (n - 2) // 2, 6, 7))
    n = random.randint(80000, 99999)
    if n % 2 == 0:
        n += 1
    subtask4.append(gen_random(n, n, (n - 2) // 2, (n - 2) // 2 + 1, 6, 7))
    real.append(subtask4)

    # max jedan 1 ili 4
    # 5
    subtask5 = []
    subtask5.append(gen_random(80000, 100000, 0, 0, 6, 8))
    subtask5.append(gen_random(80000, 100000, 1, 0, 6, 8))
    real.append(subtask5)
    # 6
    subtask6 = []
    subtask6.append(gen_random(80000, 100000, 0, 1, 6, 7))
    subtask6.append(gen_random(80000, 100000, 0, 0, 6, 7))
    for i in range(len(subtask6[-1].x)):
        if subtask6[-1].x[i] == 3:
            subtask6[-1].x[i] = 2
    real.append(subtask6)
    # 7
    subtask7 = []
    subtask7.append(gen_random(80000, 100000, 0, 1, 5, 7))
    subtask7.append(gen_random(80000, 100000, 0, 0, 5, 7))
    real.append(subtask7)
    # 8
    subtask8 = []
    subtask8.append(gen_random(80000, 100000, 0, 0, 5, 8))
    for i in range(len(subtask8[-1].x)):
        if subtask8[-1].x[i] == 2:
            subtask8[-1].x[i] = 3
    subtask8.append(gen_random(80000, 100000, 1, 0, 5, 8))
    real.append(subtask8)

    # bez dodatnih ogranicenja
    # 9
    subtask9 = []
    br1 = random.randint(20000, 30000)
    br4 = random.randint(20000, 30000)
    subtask9.append(gen_random(80000, 100000, br1, br4, 6, 8))
    subtask9.append(gen_random(80000, 100000, br1, br1 - 1, 6, 8))
    real.append(subtask9)
    # 10
    subtask10 = []
    br1 = random.randint(20000, 30000)
    subtask10.append(gen_random(80000, 100000, br1, br1 + 1, 5, 7))
    subtask10.append(gen_random(80000, 100000, br1, br1, 5, 7))
    real.append(subtask10)
    # 11
    subtask11 = []
    br1 = random.randint(20000, 30000)
    subtask11.append(gen_random(80000, 100000, br1, br1, 6, 7))
    subtask11.append(gen_random(80000, 100000, br1, br1 + 1, 6, 7))
    real.append(subtask11)
    # 12
    subtask12 = []
    br1 = random.randint(20000, 30000)
    subtask12.append(gen_random(80000, 100000, br1, br1 - 1, 6, 8))
    subtask12.append(gen_random(80000, 100000, br1, br1 + 1, 6, 8))
    real.append(subtask12)
    # 13
    subtask13 = []
    br1 = random.randint(20000, 30000)
    subtask13.append(gen_random(80000, 100000, br1, br1, 5, 8))
    subtask13.append(gen_random(80000, 100000, br1, br1 + 1, 5, 8))
    real.append(subtask13)
    # 14
    subtask14 = []
    br1 = random.randint(20000, 30000)
    subtask14.append(gen_random(80000, 100000, br1, br1 + 1, 5, 7))
    subtask14.append(gen_random(80000, 100000, br1, br1 - 1, 5, 7))
    real.append(subtask14)

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

