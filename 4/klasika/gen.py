#!/usr/bin/python2

doc = """
  Cenerate all test cases in test/:  gen.py
"""

import collections
import sys
import glob
import os
import random
import subprocess
import math

PROBLEM = "klasika"
sys.setrecursionlimit(1000010)

MAXQ = 200000

class Test(object):
    def __init__(self, q, vq):
        self.q = q          # number of queries
        self.vq = vq        # number of queries [(type, a, b)]

    def validate(self):
        assert(1 <= self.q <= MAXQ)
        n = 1
        for (t, a, b) in self.vq:
            if t == False:
                assert(1 <= a <= n)
                assert(1 <= b <= 2**30)
                n += 1
            else:
                assert(1 <= a <= n)
                assert(1 <= b <= n)

    def write(self, fd=sys.stdout):
        print>>fd, self.q
        for (t, a, b) in self.vq:
            if t == False:
                print>>fd, "Add", a, b
            else:
                print>>fd, "Query", a, b


def remove_cases():
    cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
    cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
    cases += glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.out.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)


def gen_chain(q, p_add, subtask3=False):
    vq = []
    n = 1
    for i in range(q):
        if random.random() <= p_add:
            w = random.randint(1, 2**30)
            vq.append((False, n, w))
            n += 1
        else:
            a = random.randint(1, n)
            b = random.randint(1, n)
            if subtask3: b = 1
            vq.append((True, a, b))
    return Test(q, vq)


def gen_tree(q, p_add, subtask3=False):
    vq = []
    n = 1
    for i in range(q):
        if random.random() <= p_add:
            x = random.randint(1, n)
            w = random.randint(1, 2**30)
            vq.append((False, x, w))
            n += 1
        else:
            a = random.randint(1, n)
            b = random.randint(1, n)
            if subtask3: b = 1
            vq.append((True, a, b))
    return Test(q, vq)


def gen_deep_tree(q, p_add, subtask3=False):
    vq = []
    n = 1
    ch = [0]
    for i in range(q):
        if random.random() <= p_add:
            x = random.randint(max(1, n - 10), n)
            w = random.randint(1, 2**30)
            vq.append((False, x, w))
            n += 1
            ch.append(0)
        else:
            a = random.randint(1, n)
            b = random.randint(1, n)
            if subtask3: b = 1
            vq.append((True, a, b))
    return Test(q, vq)


def gen_cases():
    remove_cases()

    real = []
    dummy = []

    dummy.append(Test(
        4,
        [(False, 1, 5),
         (True, 1, 1),
         (False, 1, 7),
         (True, 1, 1)]
    ))

    dummy.append(Test(
        6,
        [(False, 1, 5),
         (False, 2, 7),
         (False, 1, 4),
         (False, 4, 3),
         (True, 1, 1),
         (True, 2, 4)]
    ))

    dummy.append(Test(
        10,
        [(False, 1, 4),
         (False, 1, 9),
         (False, 1, 10),
         (False, 2, 2),
         (False, 3, 3),
         (False, 4, 4),
         (True, 4, 2),
         (True, 1, 3),
         (False, 6, 7),
         (True, 1, 3)]
    ))

    for i, test in enumerate(dummy):
        test.validate()
        print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
        test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

    # 1. subtask -- 1 <= Q <= 200
    subtask1 = []
    for i in range(4):
        subtask1.append(gen_chain(200, (i + 1) * 0.20))
    for i in range(4):
        subtask1.append(gen_tree(200, (i + 1) * 0.20))
    for i in range(4):
        subtask1.append(gen_deep_tree(200, (i + 1) * 0.20))

    # 2. subtask -- 1 <= Q <= 2000
    subtask2 = []
    for i in range(4):
        subtask2.append(gen_chain(2000, (i + 1) * 0.20))
    for i in range(4):
        subtask2.append(gen_tree(2000, (i + 1) * 0.20))
    for i in range(4):
        subtask2.append(gen_deep_tree(2000, (i + 1) * 0.20))

    # 3. subtask -- 1 <= Q <= 200000, b = 1
    subtask3 = []
    for i in range(4):
        subtask3.append(gen_chain(200000, (i + 1) * 0.20, True))
    for i in range(4):
        subtask3.append(gen_tree(200000, (i + 1) * 0.20, True))
    for i in range(4):
        subtask3.append(gen_deep_tree(200000, (i + 1) * 0.20, True))

    # 4. subtask -- 1 <= Q <= 200000
    subtask4 = []
    for i in range(4):
        subtask4.append(gen_chain(200000, (i + 1) * 0.20))
    for i in range(4):
        subtask4.append(gen_tree(200000, (i + 1) * 0.20))
    for i in range(4):
        subtask4.append(gen_deep_tree(200000, (i + 1) * 0.20))

    real.append(subtask1)
    real.append(subtask2)
    real.append(subtask3)
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

