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
import string

PROBLEM = "trener"
sys.setrecursionlimit(1000010)

MAXN = 75
MAXK = 1000

class Test(object):
    def __init__(self, n, k, words):
        self.n = n   # number of boxes
        self.k = k   # number of words in each box
        self.words = words   # words

    def validate(self):
        assert(1 <= self.n <= MAXN)
        assert(1 <= self.k <= MAXK)
        for i in range (self.n):
            for j in range (self.k):
                assert(len(self.words[i][j]) == i + 1)

    def write(self, fd=sys.stdout):
        print>>fd, self.n, self.k
        for i in range (self.n):
            print>>fd, ' '.join(map(str, self.words[i]))


def randomString(stringLength):
    letters = string.ascii_lowercase
    return ''.join(random.choice(letters) for i in range(stringLength))

def remove_cases():
    cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
    cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
    cases += glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.out.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)

def gen_random(minn, maxn, mink, maxk, minus):
    n = random.randint(minn,maxn)
    k = random.randint(mink, maxk)
    words = []
    for i in range (n):
        temp = []
        x = 0;
        if(i != 0):
            x = random.randint(k - random.randint(0, minus), k)
            for j in range (x):
                if(j % 2):
                    temp.append(chr(random.randint(ord('a'),ord('z'))) + words[i - 1][random.randint(0, k - 1)])
                else:
                    temp.append(words[i - 1][random.randint(0, k - 1)] + chr(random.randint(ord('a'),ord('z'))))

        for j in range (k - x):
            temp.append(randomString(i + 1))
        random.shuffle(temp)
        words.append(temp)
    return Test(n, k, words)

def gen_cases():
    remove_cases()

    real = []
    dummy = []

    dummy.append(Test(
        3, 2,
        [["a", "b"],
        ["ab", "bd"],
        ["abc", "abd"]]
    ))

    dummy.append(Test(
        3, 3,
        [["a", "b", "c"],
        ["aa", "ab", "ac"],
        ["aaa", "aab", "aca"]]
    ))

    dummy.append(Test(
        3, 1,
        [["a"],
        ["bc",],
        ["def"]]
    ))
    
    for i, test in enumerate(dummy):
        test.validate()
        print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
        test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

    # 1. subtask -- N = 75, K = 750
    subtask1 = []
    for i in range(1, 3):
        print('Generating subtask 1, case ', i)
        subtask1.append(gen_random(5, 5, 10, 10, 1))
        
    for i in range(3, 6):
        print('Generating subtask 1, case ', i)
        subtask1.append(gen_random(75,75, 75, 75, 2))

    for i in range(6, 11):
        print('Generating subtask 1, case ', i)
        subtask1.append(gen_random(75,75,750,750, 5))

    real.append(subtask1)
##
##    # 2. subtask -- 1 <= n, q <= 5*10^4, 0 <= xi <= 30
##    subtask2 = []
##
##    print('Generating subtask 2, case ', 1)
##    subtask2.append(gen_random(50000, 50000, 30, 100))
##
##    print('Generating subtask 2, case ', 2)
##    subtask2.append(gen_random(50000, 50000, 15, 100))
##
##    print('Generating subtask 2, case ', 3)
##    subtask2.append(gen_random(50000, 50000, 10, 100))
##
##    print('Generating subtask 2, case ', 4)
##    subtask2.append(gen_random(50000, 50000, 5, 100))
##
##    print('Generating subtask 2, case ', 5)
##    subtask2.append(gen_random(50000, 50000, 3, 100))
##
##    print('Generating subtask 2, case ', 6)
##    subtask2.append(gen_puno_da(50000, 50000, 30))
##
##    print('Generating subtask 2, case ', 7)
##    subtask2.append(gen_jos_vise_da(50000, 50000, 30))
##
##    real.append(subtask2)
##
##    # 3. subtask -- 1 <= n <= 10^5, 1 <= q <= 10^4, 0 <= xi <= 10^9
##
##    subtask3 = []
##
##    print('Generating subtask 3, case ', 1)
##    subtask3.append(gen_random(100000, 10000, 1000000000, 10000))
##
##    print('Generating subtask 3, case ', 2)
##    subtask3.append(gen_random(100000, 10000, 1000000000, 500))
##
##    print('Generating subtask 3, case ', 3)
##    subtask3.append(gen_random(100000, 10000, 250, 10000))
##
##    print('Generating subtask 3, case ', 4)
##    subtask3.append(gen_random(100000, 10000, 250, 500))
##
##    print('Generating subtask 3, case ', 5)
##    subtask3.append(gen_smart(100000, 10000, 1000000000, 800))
##
##    print('Generating subtask 3, case ', 6)
##    subtask3.append(gen_smart(100000, 10000, 1000000000, 400))
##
##    print('Generating subtask 3, case ', 7)
##    subtask3.append(gen_smart(100000, 10000, 1000000000, 10000, 9900))
##
##    print('Generating subtask 3, case ', 8)
##    subtask3.append(gen_smart(100000, 10000, 250, 800))
##
##    print('Generating subtask 3, case ', 9)
##    subtask3.append(gen_smart(100000, 10000, 250, 400))
##
##    print('Generating subtask 3, case ', 10)
##    subtask3.append(gen_smart(100000, 10000, 250, 10000, 9900))
##
##    print('Generating subtask 3, case ', 11)
##    subtask3.append(gen_puno_da(100000, 10000, 1000000000))
##
##    print('Generating subtask 3, case ', 12)
##    subtask3.append(gen_puno_da(100000, 10000, 100))
##
##    print('Generating subtask 3, case ', 13)
##    subtask3.append(gen_jos_vise_da(100000, 10000, 1000000000))
##
##    real.append(subtask3)
##
##    # 4. subtask -- 1 <= n, q <= 10^5, 0 <= xi <= 10^9
##
##    subtask4 = []
##
##    print('Generating subtask 4, case ', 1)
##    subtask4.append(gen_random(100000, 100000, 1000000000, 100000))
##
##    print('Generating subtask 4, case ', 2)
##    subtask4.append(gen_random(100000, 100000, 1000000000, 1000))
##
##    print('Generating subtask 4, case ', 3)
##    subtask4.append(gen_random(100000, 100000, 250, 10000))
##
##    print('Generating subtask 4, case ', 4)
##    subtask4.append(gen_random(100000, 100000, 250, 1000))
##
##    print('Generating subtask 4, case ', 5)
##    subtask4.append(gen_smart(100000, 100000, 1000000000, 1000))
##
##    print('Generating subtask 4, case ', 6)
##    subtask4.append(gen_smart(100000, 100000, 1000000000, 500))
##
##    print('Generating subtask 4, case ', 7)
##    subtask4.append(gen_smart(100000, 100000, 1000000000, 10000, 90900))
##
##    print('Generating subtask 4, case ', 8)
##    subtask4.append(gen_smart(100000, 100000, 250, 1000))
##
##    print('Generating subtask 4, case ', 9)
##    subtask4.append(gen_smart(100000, 100000, 250, 500))
##
##    print('Generating subtask 4, case ', 10)
##    subtask4.append(gen_smart(100000, 100000, 250, 10000, 90900))
##
##    print('Generating subtask 4, case ', 11)
##    subtask4.append(gen_puno_da(100000, 100000, 1000000000))
##
##    print('Generating subtask 4, case ', 12)
##    subtask4.append(gen_puno_da(100000, 100000, 100))
##
##    print('Generating subtask 4, case ', 13)
##    subtask4.append(gen_jos_vise_da(100000, 100000, 1000000000))
##
##    real.append(subtask4)

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
