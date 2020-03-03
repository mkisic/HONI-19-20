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

PROBLEM = "datum"
sys.setrecursionlimit(1000010)

MAXN = 100000
ALL = []
DAYS = [31,29,31,30,31,30,31,31,30,31,30,31]

class Test(object):
    def __init__(self, n, dates):
        self.n = n   # array length
        self.dates = dates

    def validate(self):
        assert(1 <= self.n <= MAXN)
        for i in self.dates:
            day = 10 * (ord(i[0]) - ord('0')) + ord(i[1]) - ord('0')
            month = 10 * (ord(i[3]) - ord('0')) + ord(i[4]) - ord('0')
            assert (1 <= month <= 12 and 1 <= day <= DAYS[month - 1])

    def write(self, fd=sys.stdout):
        print>>fd, self.n
        for i in self.dates:
            print>>fd, i
def rev(x):
    return x[::-1]

def tostr(x, y):
    assert(x != 0)
    ret = str(x)
    while(len(ret) < y):
        ret = "0" + ret
    return ret

def palin(d, m ,y):
    if(m > 12 or m <= 0):
        return 0
    if(d > DAYS[m - 1] or d == 0):
        return 0

    return tostr(d, 2) + tostr(m, 2) == rev(tostr(y, 4))
def init():
    for i in range (1, 9999):
        if(palin((i % 10) * 10 + (i // 10) % 10, ((i // 100) % 10) * 10 + (i // 1000), i)):
            ALL.append(i)

def remove_cases():
    cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
    cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
    cases += glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.out.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)

def palin2 (s):
    return s == rev(s)

def gen_random(n, case, cnt = 0):

    dates = []
    if(case == 1):
        for i in range(10):
            y = d = m = "00"
            while(palin2(tostr(d, 2) + tostr(m, 2) + tostr(y, 4))):
                y = ALL[random.randint(0, 365)]
                d = random.randint (1, (y % 10) * 10 + (y // 10) % 10)
                m = ((y // 100) % 10) * 10 + (y // 1000)
            dates.append(tostr(d, 2) + "." + tostr(m, 2) + "." + tostr(y, 4))
    
    elif(case == 2):
        for i in range(10):
            y = d = m = "00"
            while(palin2(tostr(d, 2) + tostr(m, 2) + tostr(y, 4))):
                y = ALL[random.randint(0, 365)]
                d = random.randint (1, (y % 10) * 10 + (y // 10) % 10)
                m = random.randint(1, ((y // 100) % 10) * 10 + (y // 1000))
            dates.append(tostr(d, 2) + "." + tostr(m, 2) + "." + tostr(y, 4))
    else:
        for i in range(n):
            y = random.randint(1, ALL[365] - 1)
            m = random.randint(1,12)
            d = random.randint(1, DAYS[m - 1] - 1)
            dates.append(tostr(d, 2) + "." + tostr(m, 2) + "." + tostr(y, 4))
    if(cnt != 0):
        dates[1] = "30.03.2091"
    return Test(n, dates)

def gen_cases():
    remove_cases()

    real = []
    dummy = []

    dummy.append(Test(
        1,
        ["02.02.2020"]
    ))

    dummy.append(Test(
        2,
        ["01.01.1000",
         "31.12.2026"]
    ))
    dummy.append(Test(
        3,
        ["01.01.0100",
         "05.07.0321",
         "05.05.0505"]
    ))

    for i, test in enumerate(dummy):
        test.validate()
        print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
        test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

    # 1. subtask -- 1 <= n, q <= 1000, 0 <= xi <= 10^9
    subtask1 = []
    for i in range(1, 3):
        print('Generating subtask 1, case ', i)
        subtask1.append(gen_random(10, 1))
    for i in range(3, 5):
        print('Generating subtask 2, case ', i)
        subtask1.append(gen_random(10 , 2))
    for i in range(5, 9):
        print('Generating subtask 3, case ', i)
        subtask1.append(gen_random(10 , 3, i == 5))
    for i in range(9, 11):
        print('Generating subtask 4, case ', i)
        subtask1.append(gen_random(MAXN, 4))
    real.append(subtask1)

    for i, batch in enumerate(real):
        for j, test in enumerate(batch):
            test.validate()
            print>>sys.stderr, 'Generating test/%s.in.%d%c' \
                    % (PROBLEM, i+1, chr(ord('a')+j))
            input = 'test/%s.in.%d%c' % (PROBLEM, i+1, chr(ord('a')+j))
            test.write(file(input, 'wt'))

def main():
    random.seed(293487)
    init()
    gen_cases()


if __name__ == "__main__":
    main()
