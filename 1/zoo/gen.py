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

PROBLEM = "zoo"
sys.setrecursionlimit(1000010)

MAXN = 1000

class Test(object):
    def __init__(self, r, s, grid):
        self.r = r        # number of rows
        self.s = s        # number of columns
        self.grid = grid  # rxs rectangular grid

    def validate(self):
        assert(2 <= self.r <= MAXN)
        assert(2 <= self.s <= MAXN)
        assert(len(self.grid) == self.r)

        animals = 0
        for i in range(self.r):
            assert(len(self.grid[i]) == self.s)
            for j in range(self.s):
                assert(self.grid[i][j] == 'T' or self.grid[i][j] == 'B' or
                        self.grid[i][j] == '*')
                if self.grid[i][j] != '*': animals += 1

        # Check if everything is in single component
        bio, Q = set([(0, 0)]), collections.deque([(0, 0)])
        dr = [0, 1, 0, -1]
        ds = [1, 0, -1, 0]
        while Q:
            r, s = Q.popleft()
            for k in range(4):
                rr = r + dr[k]
                ss = s + ds[k]
                if rr >= 0 and rr < self.r and ss >= 0 and ss < self.s and \
                   (rr, ss) not in bio and self.grid[rr][ss] != '*':
                       bio.add((rr, ss))
                       Q.append((rr, ss))

        assert(len(bio) == animals)

        # Check if a single animal can traverse from start to finish
        bio, Q = set([(0, 0)]), collections.deque([(0, 0)])
        while Q:
            r, s = Q.popleft()
            for k in range(4):
                rr = r + dr[k]
                ss = s + ds[k]
                if rr >= 0 and rr < self.r and ss >= 0 and ss < self.s and \
                   (rr, ss) not in bio and self.grid[rr][ss] == self.grid[0][0]:
                       bio.add((rr, ss))
                       Q.append((rr, ss))

        assert((self.r - 1, self.s - 1) in bio)


    def write(self, fd=sys.stdout):
        print>>fd, self.r, self.s
        for i in range(self.r):
            print>>fd, self.grid[i]


def remove_cases():
    cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
    cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
    cases += glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.out.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)


def clear_leftover_components(R, S, grid):
    bio, Q = set([(0, 0)]), collections.deque([(0, 0)])
    dr = [0, 1, 0, -1]
    ds = [1, 0, -1, 0]
    while Q:
        r, s = Q.popleft()
        for k in range(4):
            rr = r + dr[k]
            ss = s + ds[k]
            if rr >= 0 and rr < R and ss >= 0 and ss < S and \
               (rr, ss) not in bio and grid[rr][ss] != '*':
                   bio.add((rr, ss))
                   Q.append((rr, ss))

    for i in range(R):
        for j in range(S):
            if (i, j) not in bio:
                grid[i][j] = '*'


def random_walks(r, s):
    grid = []
    for i in range(r):
        row = []
        for j in range(s):
            row.append('*')
        grid.append(row)

    k = random.randint(25, 50)
    c1, c2 = 'B', 'T'
    for i in range(k):
        rr, ss = 0, 0
        grid[rr][ss] = c1
        while rr != r - 1 or ss != s - 1:
            dr = [1, 0]
            ds = [0, 1]
            if random.randint(0, 1) == 0:
                dr, ds = ds, dr
            if random.randint(0, 2) == 0:
                for i in range(2):
                    dr[i] *= -1
                    ds[i] *= -1
            for k in range(len(dr)):
                rrr = rr + dr[k]
                sss = ss + ds[k]
                if rrr >= 0 and rrr < r and sss >= 0 and sss < s:
                    rr = rrr
                    ss = sss
                    break
            grid[rr][ss] = c1
        c1, c2 = c2, c1

    g = []
    for i in range(r):
        g.append("".join(grid[i]))

    return Test(r, s, g)


def random_grid_with_one_walk(r, s):
    grid = []
    for i in range(r):
        row = []
        for j in range(s):
            x = random.randint(0, 2)
            if x == 0: row.append('*')
            if x == 1: row.append('T')
            if x == 2: row.append('B')
        grid.append(row)

    rr, ss = 0, 0
    grid[rr][ss] = 'T'
    while rr != r - 1 or ss != s - 1:
        dr = [1, 0]
        ds = [0, 1]
        if random.randint(0, 1) == 0:
            dr, ds = ds, dr
        if random.randint(0, 2) == 0:
            for i in range(2):
                dr[i] *= -1
                ds[i] *= -1
        for k in range(len(dr)):
            rrr = rr + dr[k]
            sss = ss + ds[k]
            if rrr >= 0 and rrr < r and sss >= 0 and sss < s:
                rr = rrr
                ss = sss
                break
        grid[rr][ss] = 'T'

    clear_leftover_components(r, s, grid)

    g = []
    for i in range(r):
        g.append("".join(grid[i]))

    return Test(r, s, g)


def gen_cases():
    remove_cases()

    real = []
    dummy = []

    dummy.append(Test(
        4, 4,
        ["TT*T",
         "*TTT",
         "***T",
         "***T"]
    ))

    dummy.append(Test(
        3, 5,
        ["TTBB*",
         "*T*B*",
         "*TTTT"]
    ))

    dummy.append(Test(
        7, 5,
        ["BT***",
         "BTBBB",
         "BTTTB",
         "BBT*B",
         "BBT*B",
         "BBT**",
         "*BBBB"]
    ))

    for i, test in enumerate(dummy):
        test.validate()
        print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
        test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

    # 1. subtask -- 1 <= R, S <= 100
    subtask1 = []
    for i in range(1, 4):
        subtask1.append(random_walks(random.randint(2, 30),\
                                     random.randint(2, 30)))
    for i in range(4, 8):
        if i < 6:
            subtask1.append(random_walks(random.randint(50, 100),\
                                         random.randint(50, 100)))
        else:
            subtask1.append(random_walks(100, 100))

    for i in range(8, 16):
        subtask1.append(random_grid_with_one_walk(random.randint(75, 100),\
                                                  random.randint(75, 100)))

    real.append(subtask1)

    # 2. subtask -- 1 <= R, S <= 1000
    subtask2 = []
    for i in range(1, 6):
        subtask2.append(random_walks(random.randint(950, 1000),\
                                     random.randint(950, 1000)))

    for i in range(6, 16):
        subtask2.append(random_grid_with_one_walk(random.randint(950, 1000),\
                                                  random.randint(950, 1000)))

    real.append(subtask2)

    # # 1. test -- 1 <= l <= r <= 9
    # real.append(gen_all_pairs(1, 9))

    # # 2. test -- r - l <= 1000, everything fits in 32-bit integer
    # real.append(gen_random(100, 1000, 10**6))

    # # 3. test -- r - l <= 1000
    # real.append(gen_random(100, 1000, 2**60))

    # # 4. test, everything fits in 32 bit integer
    # real.append(gen_random(100, 10**8, 10**9))

    # # 5. test
    # real.append(gen_random(100, 10**13, 2**60))

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

