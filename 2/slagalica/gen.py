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

    # 1. subtask -- 2 <= n <= 10
    subtask1 = []
    print('Generating subtask 1, case ', 1)
    subtask1.append(gen_random(10, 10, 2, 2, 6, 7))

    real.append(subtask1)

    # 2. subtask -- 2 <= n <= 10^5, samo 1 i 4
    subtask2 = []

    print('Generating subtask 2, case ', 1)
    n = random.randint(80000, 99999)
    if n % 2 == 0:
        n += 1
    subtask2.append(gen_random(n, n, (n - 2) // 2, (n - 2) // 2 + 1, 5, 7))

    print('Generating subtask 2, case ', 2)
    n = random.randint(80000, 99999)
    if n % 2 == 1:
        n += 1
    subtask2.append(gen_random(n, n, (n - 2) // 2, (n - 2) // 2, 6, 7))

    real.append(subtask2)

    # 3. subtask -- 2 <= n <= 10^5, najvise jedan 1 ili 4

    subtask3 = []

    print('Generating subtask 3, case ', 1)
    subtask3.append(gen_random(80000, 100000, 0, 0, 6, 8))

    print('Generating subtask 3, case ', 2)
    subtask3.append(gen_random(80000, 100000, 1, 0, 6, 8))

    print('Generating subtask 3, case ', 3)
    subtask3.append(gen_random(80000, 100000, 0, 1, 6, 7))

    print('Generating subtask 3, case ', 4)
    subtask3.append(gen_random(80000, 100000, 0, 0, 5, 8))
    for i in range(len(subtask3[-1].x)):
        if subtask3[-1].x[i] == 2:
            subtask3[-1].x[i] = 3

    real.append(subtask3)

    # 4. subtask -- 2 <= n <= 10^5

    subtask4 = []

    print('Generating subtask 4, case ', 1)
    br1 = random.randint(20000, 30000)
    br4 = random.randint(20000, 30000)
    subtask4.append(gen_random(80000, 100000, br1, br4, 6, 8))

    print('Generating subtask 4, case ', 2)
    br1 = random.randint(20000, 30000)
    br4 = br1 + 1
    subtask4.append(gen_random(80000, 100000, br1, br4, 5, 8))

    print('Generating subtask 4, case ', 3)
    br1 = random.randint(20000, 30000)
    br4 = br1 + 1
    subtask4.append(gen_random(80000, 100000, br1, br4, 5, 7))

    print('Generating subtask 4, case ', 4)
    br1 = random.randint(20000, 30000)
    br4 = br1
    subtask4.append(gen_random(80000, 100000, br1, br4, 5, 8))

    print('Generating subtask 4, case ', 5)
    br1 = random.randint(20000, 30000)
    br4 = br1
    subtask4.append(gen_random(80000, 100000, br1, br4, 6, 7))

    print('Generating subtask 4, case ', 6)
    br1 = random.randint(20000, 30000)
    br4 = br1 - 1
    subtask4.append(gen_random(80000, 100000, br1, br4, 6, 8))

    print('Generating subtask 4, case ', 7)
    br1 = random.randint(20000, 30000)
    br4 = br1 + 1
    subtask4.append(gen_random(80000, 100000, br1, br4, 5, 7))
    
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

