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


def randomString(stringLength, a, b):
    letters = []
    for i in range(a ,b):
        letters.append(chr(i))
    return ''.join(random.choice(letters) for i in range(stringLength))

def remove_cases():
    cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
    cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
    cases += glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.out.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)

def gen_random(minn, maxn, mink, maxk, minus, minslovo, maxslovo):
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
                    temp.append(chr(random.randint(minslovo, maxslovo)) + words[i - 1][random.randint(0, k - 1)])
                else:
                    temp.append(words[i - 1][random.randint(0, k - 1)] + chr(random.randint(minslovo, maxslovo)))

        for j in range (k - x):
            temp.append(randomString(i + 1, minslovo, maxslovo))
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
        subtask1.append(gen_random(5, 5, 10, 10, 1, ord('a'), ord('z')))
        
    for i in range(3, 5):
        print('Generating subtask 1, case ', i)
        subtask1.append(gen_random(75,75, 75, 75, 2, ord('a'), ord('z')))
        
    for i in range(5, 6):
        print('Generating subtask 1, case ', i)
        subtask1.append(gen_random(75,75, 75, 75, 2, ord('a'), ord('b')))

    for i in range(6, 8):
        print('Generating subtask 1, case ', i)
        subtask1.append(gen_random(75,75,750,750, 5, ord('a'), ord('z')))

    for i in range(8, 11):
        print('Generating subtask 1, case ', i)
        subtask1.append(gen_random(75,75,750,750, 5, ord('a'), ord('b')))

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
    gen_cases()


if __name__ == "__main__":
    main()
