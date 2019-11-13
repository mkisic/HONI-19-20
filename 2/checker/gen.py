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

PROBLEM = "checker"
sys.setrecursionlimit(1000010)

MAXN = 200000  # 2*10^5

class Test(object):
    def __init__(self, t, n, p):
        self.t = t   # batch number
        self.n = n   # array length
        self.x = p[0]   # [(1, 2), (2, 3), (n-1, n), (n, 1)]
        self.l = p[1]   # diagonals, list of (x, y, c)


    def validate(self):
        assert(1 <= self.t <= 5)
        assert(4 <= self.n <= MAXN)
        assert(len(self.x) == self.n)
        assert(1 <= min(self.x) <= max(self.x) <= 3)
        assert(len(self.l) == self.n - 3)
        for d in self.l:
            assert(1 <= d[0] <= self.n)
            assert(1 <= d[1] <= self.n)
            assert(d[0] != d[1])
            assert(d[0] % self.n + 1 != d[1])
            assert(d[1] % self.n + 1 != d[0])
            assert(1 <= d[2] <= 3)


    def write(self, fd=sys.stdout):
        print>>fd, self.t
        print>>fd, self.n
        print>>fd, ''.join(map(str, self.x))
        for d in self.l:
            print>>fd, ' '.join(map(str, d))


def remove_cases():
    #cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
    #cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
    cases = glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.out.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)


# util functions
def random_triangle():
    triangle = [1, 2, 3]
    random.shuffle(triangle)
    return triangle

def change_colors(p, c1, c2):
    for i in range(len(p[0])):
        if p[0][i] == c1: p[0][i] = c2
        elif p[0][i] == c2: p[0][i] = c1
    for i in range(len(p[1])):
        if p[1][i][2] == c1: p[1][i][2] = c2
        elif p[1][i][2] == c2: p[1][i][2] = c1

def random_rotate(p, n):
    random.shuffle(p[1])
    delta = random.randint(0, n - 1)
    tmp = [p[0][(i + delta) % n] for i in range(n)]
    for i in range(n): p[0][i] = tmp[i]
    for i in range(n - 3):
        for j in [0, 1]:
            p[1][i][j] = (p[1][i][j] - delta - 1 + n) % n + 1

def random_diagonal(n):
    a = 1
    b = random.randint(3, n - 1)
    delta = random.randint(1, n)
    a = (a + delta - 1) % n + 1
    b = (b + delta - 1) % n + 1
    return [a, b]


def gen_polygon(n):
    assert(n >= 3)
    if n == 3:
        return random_triangle(), []

    x = random.randint(3, n - 1)
    p = gen_polygon(x)
    q = gen_polygon(n - x + 2)
    if p[0][-1] != q[0][-1]:
        change_colors(q, q[0][-1], p[0][-1])
    for i in range(len(q[1])):
        q[1][i][0] += x - 1
        q[1][i][1] += x - 1

    r = p[0][:-1] + q[0][:-1], p[1] + q[1] + [[1, x, p[0][-1]]]
    random_rotate(r, n)
    return r


# odgovor je tocno
def gen_random_correct(t, n):
    return Test(t, n, gen_polygon(n))

# slucaj koji rusi naivno n^2 rjesenje
def gen_special_case(t, n):
    x = [1] * n
    l = []
    x[n // 2 - 1] = x[n - 1] = 2
    c = 3
    for i in range(n // 2 - 1, 0, -1):
        l.append([i, n // 2 + 1, c])
        c = 5 - c
    for i in range(n // 2 + 2, n, 1):
        l.append([1, i, c])
        c = 5 - c
    assert(c == 2)
    p = (x, l)
    random_rotate(p, n)
    return Test(t, n, p)

def gen_special_case_reversed(t, n):
    test = gen_special_case(t, n)
    test.x.reverse()
    for i in range(n - 3):
        for j in [0, 1]:
            test.l[i][j] = n + 1 - test.l[i][j]
    return test

# od tocnog napravi nespravnu triangulaciju
def gen_wrong_triangulation(t, n, correct_gen, changes):
    test = correct_gen(t, n)
    for _ in range(changes):
        i = random.randint(0, n - 4)
        test.l[i] = random_diagonal(n) + [test.l[i][2]]
    return test

# od tocnog napravi neispravno bojenje
def gen_wrong_coloring(t, n, correct_gen, swaps_s, swaps_d):
    test = correct_gen(t, n)
    for _ in range(swaps_s):
        while True:
            i = random.randint(0, n - 1)
            j = random.randint(0, n - 1)
            if test.x[i] != test.x[j]: break
        test.x[i], test.x[j] = test.x[j], test.x[i]
    for _ in range(swaps_d):
        while True:
            i = random.randint(0, n - 4)
            j = random.randint(0, n - 4)
            if test.l[i][2] != test.l[j][2]: break
        test.l[i][2], test.l[j][2] = test.l[j][2], test.l[i][2]
    return test



def gen_cases():
    remove_cases()

    real = []

    # 1. subtask -- 4 <= n <= 100
    subtask1 = [
        gen_random_correct(1, 100),
        gen_random_correct(1, 99),
        gen_wrong_triangulation(1, 100, gen_random_correct, 1),
        gen_wrong_triangulation(1, 99, gen_random_correct, 10),
        gen_wrong_coloring(1, 100, gen_random_correct, 1, 0),
        gen_wrong_coloring(1, 99, gen_random_correct, 0, 1),
        gen_wrong_coloring(1, 100, gen_random_correct, 10, 10),
    ]
    #random.shuffle(subtask1)
    real.append(subtask1)

    # 2.subtask -- 4 <= n <= 2000
    subtask2 = [
        gen_random_correct(2, 2000),
        gen_random_correct(2, 1999),
        gen_wrong_triangulation(2, 2000, gen_random_correct, 1),
        gen_wrong_triangulation(2, 1999, gen_random_correct, 200),
        gen_wrong_coloring(2, 2000, gen_random_correct, 1, 0),
        gen_wrong_coloring(2, 1999, gen_random_correct, 0, 1),
        gen_wrong_coloring(2, 2000, gen_random_correct, 200, 200),
    ]
    #random.shuffle(subtask2)
    real.append(subtask2)

    # 3.subtask -- 4 <= n <= 200000, samo triangulacija
    subtask3 = [
        gen_random_correct(3, 200000),
        gen_random_correct(3, 199999),
        gen_wrong_triangulation(3, 200000, gen_random_correct, 1),
        gen_wrong_triangulation(3, 199999, gen_random_correct, 100),
        gen_wrong_triangulation(3, 200000, gen_random_correct, 1000),
        gen_special_case(3, 200000),
        gen_special_case_reversed(3, 200000),
        gen_wrong_triangulation(3, 200000, gen_special_case, 10),
        gen_wrong_triangulation(3, 200000, gen_special_case_reversed, 10),
    ]
    #random.shuffle(subtask3)
    real.append(subtask3)

    # 4.subtask -- 4 <= n <= 200000, samo bojenje
    subtask4 = [
        gen_random_correct(4, 200000),
        gen_random_correct(4, 199999),
        gen_wrong_coloring(4, 200000, gen_random_correct, 1, 0),
        gen_wrong_coloring(4, 199999, gen_random_correct, 0, 1),
        gen_wrong_coloring(4, 200000, gen_random_correct, 10, 10),
        gen_special_case(4, 200000),
        gen_special_case_reversed(4, 200000),
        gen_wrong_coloring(4, 200000, gen_special_case, 10, 0),
        gen_wrong_coloring(4, 200000, gen_special_case_reversed, 0, 10),
    ]
    #random.shuffle(subtask4)
    real.append(subtask4)

    # 5.subtask -- 4 <= n <= 200000
    subtask5 = [
        gen_random_correct(5, 200000),
        gen_random_correct(5, 199999),
        gen_wrong_triangulation(5, 200000, gen_random_correct, 1),
        gen_wrong_triangulation(5, 199999, gen_random_correct, 200),
        gen_wrong_coloring(5, 200000, gen_random_correct, 1, 0),
        gen_wrong_coloring(5, 199999, gen_random_correct, 0, 1),
        gen_wrong_coloring(5, 199999, gen_random_correct, 20, 20),
        gen_special_case(5, 200000),
        gen_special_case_reversed(5, 200000),
        gen_wrong_triangulation(5, 200000, gen_special_case, 1),
        gen_wrong_coloring(5, 200000, gen_special_case, 1, 0),
    ]
    #random.shuffle(subtask5)
    real.append(subtask5)
    
    for i, batch in enumerate(real):
        for j, test in enumerate(batch):
            test.validate()
            print>>sys.stderr, 'Generating test/%s.in.%d%c' \
                    % (PROBLEM, i+1, chr(ord('a')+j))
            input = 'test/%s.in.%d%c' % (PROBLEM, i+1, chr(ord('a')+j))
            test.write(file(input, 'wt'))

def main():
    random.seed(28071997)
    gen_cases()

if __name__ == "__main__":
    main()

