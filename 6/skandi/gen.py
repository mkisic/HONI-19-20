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

PROBLEM = "skandi"
sys.setrecursionlimit(1000010)

MAXN = 500

class Test(object):
    def __init__(self, r, s, grid):
        self.r = r        # number of rows
        self.s = s        # number of columns
        self.grid = grid  # crossword puzzle

    def validate(self):
        assert(2 <= self.r <= MAXN)
        assert(2 <= self.s <= MAXN)

        assert(len(self.grid) == self.r)
        has_zero = False
        for row in self.grid:
            assert(len(row) == self.s)
            has_zero |= '0' in row
            assert(all([c == '0' or c == '1' for c in row]))

        for i in range(self.r):
            assert(self.grid[i][0] == '1')

        for j in range(self.s):
            assert(self.grid[0][j] == '1')

    def write(self, fd=sys.stdout):
        print>>fd, self.r, self.s
        for row in self.grid:
            print>>fd, row


def remove_cases():
    cases = glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.out.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)


def gen_random(r, s, q):
    grid = [[0] * s for i in range(r)]
    for i in range(r):
        grid[i][0] = 1
    for j in range(s):
        grid[0][j] = 1
    for qq in range(q):
        i = random.randint(1, r - 1)
        j = random.randint(1, s - 1)
        grid[i][j] = 1
    char_grid = [''.join(list(map(str, row))) for row in grid]
    return Test(r, s, char_grid)


def gen_cases():
    remove_cases()

    real = []
    dummy = []

    dummy.append(Test(
        4, 5,
        ["11111",
         "10000",
         "10000",
         "10000"]
    ))

    dummy.append(Test(
        6, 4,
        ["1111",
         "1011",
         "1000",
         "1011",
         "1010",
         "1000"]
    ))

    for i, test in enumerate(dummy):
        test.validate()
        print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
        test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

    real = []

    # subtask 1 -> najvise 9 jedinica
    subtask1 = []
    subtask1.append(gen_random(2, 7, 1))
    subtask1.append(gen_random(4, 4, 2))
    subtask1.append(gen_random(4, 4, 2))
    subtask1.append(gen_random(4, 4, 2))
    subtask1.append(gen_random(4, 4, 2))
    subtask1.append(gen_random(4, 4, 2))
    subtask1.append(gen_random(4, 4, 2))
    subtask1.append(gen_random(5, 3, 2))
    subtask1.append(gen_random(3, 5, 2))
    subtask1.append(gen_random(5, 3, 2))
    subtask1.append(gen_random(5, 3, 2))
    subtask1.append(gen_random(5, 3, 2))
    subtask1.append(gen_random(3, 5, 2))
    subtask1.append(gen_random(3, 5, 2))
    subtask1.append(gen_random(3, 5, 2))
    subtask1.append(gen_random(4, 3, 3))
    subtask1.append(gen_random(3, 4, 3))
    subtask1.append(gen_random(4, 3, 3))
    subtask1.append(gen_random(3, 4, 3))
    subtask1.append(gen_random(4, 3, 3))
    subtask1.append(gen_random(3, 4, 3))
    subtask1.append(gen_random(4, 3, 3))
    subtask1.append(gen_random(3, 4, 3))

    real.append(subtask1)

    # subtask 2 -> r <= 500, s <= 10
    subtask2 = []
    for i in range(26):
        r = random.randint(2, 500)
        s = random.randint(2, 10)
        if (i + 2 < 10):
            s = i + 2
        else:
            r = 500
            s = 10
        t = random.randint(0, 2)
        q = random.randint(0, r * s // 2)
        if t == 1: q = random.randint(r * s // 4, 3 * r * s // 4)
        if t == 2: q = random.randint(r * s // 2, r * s)
        subtask2.append(gen_random(r, s, q))

    real.append(subtask2)

    # subtask 3 -> r, s <= 500
    subtask3 = []
    for i in range(26):
        r = random.randint(400, 500)
        s = random.randint(400, 500)
        if i > 10:
            if random.randint(0, 1) == 0:
                r = 500
            else:
                s = 500
        if i > 20: r = s = 500
        t = random.randint(0, 2)
        q = random.randint(0, r * s // 2)
        if t == 1: q = random.randint(r * s // 4, 3 * r * s // 4)
        if t == 2: q = random.randint(r * s // 2, r * s)
        subtask3.append(gen_random(r, s, q))

    real.append(subtask3)

    for i, batch in enumerate(real):
        for j, test in enumerate(batch):
            test.validate()
            print>>sys.stderr, 'Generating test/%s.in.%d%c' \
                    % (PROBLEM, i+1, chr(ord('a')+j))
            input = 'test/%s.in.%d%c' % (PROBLEM, i+1, chr(ord('a')+j))
            test.write(file(input, 'wt'))


def main():
    random.seed(293731)
    gen_cases()


if __name__ == "__main__":
    main()

