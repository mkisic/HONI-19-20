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

MAXN = 50
MAXK = 1500

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
    for i in range(a ,b + 1):
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
def gen_extra(minn, maxn, mink, maxk):
    n = random.randint(minn,maxn)
    k = random.randint(mink, maxk)
    words = []
    for j in range(n):
        temp = []
        x = 0
        if(j >= 5):
            x = random.randint(0,2)
        for i in range(x):
            a = random.randint(0, n - 1)
            word = words[j - 1][a]
            if(a % 2 == 0):
                word = word + chr(random.randint(ord('a'), ord('b')))
            else:
                word = chr(random.randint(ord('a'), ord('b'))) + word
            temp.append(word)
        for i in range(k - x):
            temp.append(randomString(j + 1, ord('x'), ord('x')))
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
    subtask2 = []
    subtask3 = []
    for i in range(1, 3):
        print('Generating subtask 1, case ', i)
        subtask1.append(gen_random(5, 5, 10, 10, 1, ord('a'), ord('z')))
        
    for i in range(3, 4):
        print('Generating subtask 1, case ', i)
        subtask1.append(gen_random(5, 5, 10, 10, 2, ord('a'), ord('z')))
        
    for i in range(4, 5):
        print('Generating subtask 1, case ', i)
        subtask1.append(gen_random(5, 5, 10, 10, 1, ord('x'), ord('x')))
        
    for i in range(5,7):
        print('Generating subtask 2, case ', i)
        subtask2.append(gen_random(50, 50, 100, 100, 2, ord('a'), ord('z')))
        
    for i in range(7,8):
        print('Generating subtask 2, case ', i)
        subtask2.append(gen_random(50, 50, 100, 100, 3, ord('a'), ord('z')))
        
    for i in range(8,9):
        print('Generating subtask 2, case ', i)
        subtask2.append(gen_random(50, 50, 100, 100, 2, ord('c'), ord('c')))
        
    for i in range(9, 11):
        print('Generating subtask 2, case ', i)
        subtask2.append(gen_random(50, 50, 100, 100, 2, ord('a'), ord('b')))
    subtask2.append(gen_extra(50,50,100,100))

    for i in range(11, 13):
        print('Generating subtask 3, case ', i)
        subtask3.append(gen_random(MAXN, MAXN, MAXK, MAXK, 5, ord('a'), ord('z')))

    for i in range(13, 15):
        print('Generating subtask 3, case ', i)
        subtask3.append(gen_random(MAXN, MAXN, MAXK, MAXK, 8, ord('a'), ord('z')))

    for i in range(15, 16):
        print('Generating subtask 3, case ', i)
        subtask3.append(gen_random(MAXN, MAXN, MAXK, MAXK, 5, ord('a'), ord('a')))
        
    for i in range(16, 21):
        print('Generating subtask 3, case ', i)
        subtask3.append(gen_random(MAXN, MAXN, MAXK, MAXK, 5, ord('a'), ord('b')))
    subtask3.append(gen_extra(50,50,1500,1500))

    real.append(subtask1)
    real.append(subtask2)
    real.append(subtask3)


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
