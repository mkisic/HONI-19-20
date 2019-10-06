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

MAXN = 100000
MAXQ = 100000

class Test(object):
    def __init__(self, n, q, x, qs):
        self.n = n   # array length
        self.q = q   # number of queries
        self.x = x   # [x1, x2, ... xn]
        self.qs = qs # [(l1, r1, l2, r2), ...]

    def validate(self):
        assert(1 <= self.n <= MAXN)
        assert(1 <= self.q <= MAXQ)
        assert(len(self.x) == self.n)
        assert(0 <= min(self.x) <= max(self.x) <= 10**9)
        assert(len(self.qs) == self.q)
        for l1, r1, l2, r2 in self.qs:
            assert(r1 - l1 == r2 - l2)
            assert(1 <= l1 <= r1 <= self.n)
            assert(1 <= l2 <= r2 <= self.n)

    def write(self, fd=sys.stdout):
        print>>fd, self.n, self.q
        print>>fd, ' '.join(map(str, self.x))
        for l1, r1, l2, r2 in self.qs:
            print>>fd, l1, r1, l2, r2


def remove_cases():
    cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
    cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
    cases += glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.out.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)

def gen_random(n, q, xmax, szmax):
    x = [random.randint(0, xmax) for x in range(n)]
    qs = []
    for i in range(q):
        if i < q / 2:
            sz = random.randint(1, n)
        else:
            sz = random.randint(1, szmax)
        l1 = random.randint(1, n - sz + 1)
        l2 = random.randint(1, n - sz + 1)
        qs.append((l1, l1 + sz - 1, l2, l2 + sz - 1))
    return Test(n, q, x, qs)

def gen_smart(n, q, xmax, szmax, tresh = 0):
    x = [random.randint(0, xmax) for x in range(n)]
    qs = []
    tresh = max(tresh, q/2)
    for i in range(q):
        if i < tresh:
            sz = random.randint(1, n)
        else:
            sz = random.randint(1, szmax)
        l1 = random.randint(1, n - sz + 1)
        l2 = random.randint(1, n - sz + 1)
        qs.append((l1, l1 + sz - 1, l2, l2 + sz - 1))

        if i >= tresh:
            l = x[l1-1:l1+sz-1]
            random.shuffle(l)
            l[random.randint(0, sz - 1)] = random.randint(0, xmax)
            x[l2-1:l2+sz-1] = l

    return Test(n, q, x, qs)

def gen_puno_da(n, q, xmax):
    x = [random.randint(0, xmax)] * n
    kor = int(math.sqrt(n))
    for i in range(0, n, 3*kor):
        x[i] = random.randint(0, xmax)
    qs = []
    for i in range(q):
        sz = random.randint(1, n)
        l1 = random.randint(1, n - sz + 1)
        l2 = random.randint(1, n - sz + 1)
        qs.append((l1, l1 + sz - 1, l2, l2 + sz - 1))
    return Test(n, q, x, qs)

def gen_jos_vise_da(n, q, xmax):
    assert(n % 2 == 0)
    x = [random.randint(0, xmax) for i in range(n/2)]
    x = x + x[::-1]
    assert(len(x) == n)

    qs = []
    for i in range(q):
        if i > q - 100:
            sz = random.randint(1, n)
            l1 = random.randint(1, n - sz + 1)
            l2 = random.randint(1, n - sz + 1)
        else:
            sz = random.randint(1, n/2)
            l1 = random.randint(1, n/2 - sz + 1)
            l2 = n - l1 - sz + 1
        qs.append((l1, l1 + sz - 1, l2, l2 + sz - 1))
    random.shuffle(qs)
    return Test(n, q, x, qs)

def gen_cases():
    remove_cases()

    real = []
    dummy = []

    dummy.append(Test(
        6,
        4,
        [1, 3, 2, 3, 1, 2],
        [(1, 1, 2, 2),
         (2, 3, 3, 4),
         (2, 3, 4, 5),
         (1, 3, 2, 4)]
    ))

    dummy.append(Test(
        10,
        5,
        [3, 3, 3, 1, 2, 2, 1, 2, 2, 1],
        [(2, 3, 5, 6),
         (9, 10, 5, 6),
         (5, 6, 4, 5),
         (5, 8, 3, 6),
         (3, 7, 5, 9)]
    ))

    for i, test in enumerate(dummy):
        test.validate()
        print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
        test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

    # 1. subtask -- 1 <= n, q <= 1000, 0 <= xi <= 10^9
    subtask1 = []
    for i in range(1, 6):
        print('Generating subtask 1, case ', i)
        subtask1.append(gen_random(1000, 1000, 1000 / i, 20))

    for i in range(6, 11):
        print('Generating subtask 1, case ', i)
        subtask1.append(gen_smart(1000, 1000, 1000, 100))

    real.append(subtask1)

    # 2. subtask -- 1 <= n, q <= 5*10^4, 0 <= xi <= 30
    subtask2 = []

    print('Generating subtask 2, case ', 1)
    subtask2.append(gen_random(50000, 50000, 30, 100))

    print('Generating subtask 2, case ', 2)
    subtask2.append(gen_random(50000, 50000, 15, 100))

    print('Generating subtask 2, case ', 3)
    subtask2.append(gen_random(50000, 50000, 10, 100))

    print('Generating subtask 2, case ', 4)
    subtask2.append(gen_random(50000, 50000, 5, 100))

    print('Generating subtask 2, case ', 5)
    subtask2.append(gen_random(50000, 50000, 3, 100))

    print('Generating subtask 2, case ', 6)
    subtask2.append(gen_puno_da(50000, 50000, 30))

    print('Generating subtask 2, case ', 7)
    subtask2.append(gen_jos_vise_da(50000, 50000, 30))

    real.append(subtask2)

    # 3. subtask -- 1 <= n <= 10^5, 1 <= q <= 10^4, 0 <= xi <= 10^9

    subtask3 = []

    print('Generating subtask 3, case ', 1)
    subtask3.append(gen_random(100000, 10000, 1000000000, 10000))

    print('Generating subtask 3, case ', 2)
    subtask3.append(gen_random(100000, 10000, 1000000000, 500))

    print('Generating subtask 3, case ', 3)
    subtask3.append(gen_random(100000, 10000, 250, 10000))

    print('Generating subtask 3, case ', 4)
    subtask3.append(gen_random(100000, 10000, 250, 500))

    print('Generating subtask 3, case ', 5)
    subtask3.append(gen_smart(100000, 10000, 1000000000, 800))

    print('Generating subtask 3, case ', 6)
    subtask3.append(gen_smart(100000, 10000, 1000000000, 400))

    print('Generating subtask 3, case ', 7)
    subtask3.append(gen_smart(100000, 10000, 1000000000, 10000, 9900))

    print('Generating subtask 3, case ', 8)
    subtask3.append(gen_smart(100000, 10000, 250, 800))

    print('Generating subtask 3, case ', 9)
    subtask3.append(gen_smart(100000, 10000, 250, 400))

    print('Generating subtask 3, case ', 10)
    subtask3.append(gen_smart(100000, 10000, 250, 10000, 9900))

    print('Generating subtask 3, case ', 11)
    subtask3.append(gen_puno_da(100000, 10000, 1000000000))

    print('Generating subtask 3, case ', 12)
    subtask3.append(gen_puno_da(100000, 10000, 100))

    print('Generating subtask 3, case ', 13)
    subtask3.append(gen_jos_vise_da(100000, 10000, 1000000000))

    real.append(subtask3)

    # 4. subtask -- 1 <= n, q <= 10^5, 0 <= xi <= 10^9

    subtask4 = []

    print('Generating subtask 4, case ', 1)
    subtask4.append(gen_random(100000, 100000, 1000000000, 100000))

    print('Generating subtask 4, case ', 2)
    subtask4.append(gen_random(100000, 100000, 1000000000, 1000))

    print('Generating subtask 4, case ', 3)
    subtask4.append(gen_random(100000, 100000, 250, 10000))

    print('Generating subtask 4, case ', 4)
    subtask4.append(gen_random(100000, 100000, 250, 1000))

    print('Generating subtask 4, case ', 5)
    subtask4.append(gen_smart(100000, 100000, 1000000000, 1000))

    print('Generating subtask 4, case ', 6)
    subtask4.append(gen_smart(100000, 100000, 1000000000, 500))

    print('Generating subtask 4, case ', 7)
    subtask4.append(gen_smart(100000, 100000, 1000000000, 10000, 90900))

    print('Generating subtask 4, case ', 8)
    subtask4.append(gen_smart(100000, 100000, 250, 1000))

    print('Generating subtask 4, case ', 9)
    subtask4.append(gen_smart(100000, 100000, 250, 500))

    print('Generating subtask 4, case ', 10)
    subtask4.append(gen_smart(100000, 100000, 250, 10000, 90900))

    print('Generating subtask 4, case ', 11)
    subtask4.append(gen_puno_da(100000, 100000, 1000000000))

    print('Generating subtask 4, case ', 12)
    subtask4.append(gen_puno_da(100000, 100000, 100))

    print('Generating subtask 4, case ', 13)
    subtask4.append(gen_jos_vise_da(100000, 100000, 1000000000))

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

