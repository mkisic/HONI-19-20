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

PROBLEM = "trobojnica"
sys.setrecursionlimit(1000010)

MAXN = 200000  # 2*10^5

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

# probably a NO
def gen_random(n):
    x = [random.randint(1, 3) for i in range(n)]
    return Test(n, x)

def gen_random_yes(n):
    x = [random.randint(1, 3) for i in range(n - 2)]
    a = x.count(1)
    b = x.count(2)
    c = x.count(3)

    if a % 2 == b % 2 == c % 2:
        x += [random.randint(1, 3)] * 2
    else:
        if a % 2 != n % 2:
            x.append(1)
        if b % 2 != n % 2:
            x.append(2)
        if c % 2 != n % 2:
            x.append(3)

    return Test(n, x)

def gen_allthesame(n):
    u = random.randint(1, 3)
    x = [u for x in range(n)]
    return Test(n, x)

# n is odd, 12333...3
def gen_type_1(n):
    colors = [1, 2, 3]
    random.shuffle(colors)
    return Test(n, colors + [colors[-1]] * (n - 3))

# n is divisible by 4, 11112222
def gen_type_2(n):
    colors = random.sample([1, 2, 3], 2)
    return Test(n, [colors[0]] * (n / 2) + [colors[1]] * (n / 2))



def gen_cases():
    remove_cases()

    real = []
    dummy = []


    dummy.append(Test(
        4,
        [1, 2, 1, 2]
    ))

    dummy.append(Test(
        4,
        [1, 2, 1, 3]
    ))

    dummy.append(Test(
        7,
        [1, 2, 2, 3, 1, 2, 1]
    ))


    for i, test in enumerate(dummy):
        test.validate()
        print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
        test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))


    # 1. subtask -- 4 <= n <= 11
    subtask1 = [
        gen_random(10),
        gen_random(11),
        gen_allthesame(10),
        gen_random_yes(11),
        gen_random_yes(5),
        gen_random_yes(8),
        gen_type_1(5),
        gen_type_1(11),
        gen_type_2(8),
        gen_random_yes(9),
    ]
    random.shuffle(subtask1)
    real.append(subtask1)

    # 2.subtask -- 4 <= n <= 1000
    subtask2 = [
        gen_random(10),
        gen_random(1000),
        gen_allthesame(1000 - 1),
        gen_random_yes(11),
        gen_random_yes(1000),
        gen_random_yes(999),
        gen_type_1(5),
        gen_type_1(999),
        gen_type_2(12),
        gen_type_2(1000),
    ]
    random.shuffle(subtask2)
    real.append(subtask2)

    # 3.subtask -- 4 <= n <= 200000
    subtask3 = [
        gen_random(10),
        gen_random(200000),
        gen_allthesame(200000 - 1),
        gen_random_yes(11),
        gen_random_yes(200000),
        gen_random_yes(100001),
        gen_type_1(5),
        gen_type_1(200000 - 1),
        gen_type_2(16),
        gen_type_2(200000),
    ]
    random.shuffle(subtask3)
    real.append(subtask3)
    
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

