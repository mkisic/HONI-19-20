#!/usr/bin/python3

# PAZI OVO NIJE OK ZA CMS EVALUATOR

# Checker to be used by HSIN evaluator.

# Usage: [checker] [input] [official_output] [contestant_output]

# Score (real between 0.0 and 1.0) written on stdout.
# Textual description of the result written on stderr.

import sys
import random

WRONG_OUTPUT_FORMAT = "Krivo formatiran izlaz."
TEST_DATA_ERROR = "Greska u sluzbenom ulazu ili izlazu."
WRONG_K = "Netocan broj naredbi."
WRONG_COMMAND_FORMAT = "Naredba nije ispravno formatirana."
WRONG = "Netocno."
CORRECT = "Tocno."

MAX_COMMAND_LEN = 1000
MAX_VAR_COUNT = 6 # 1 lhs + 5 rhs
ALLOWED_CHARS = "A=()1234567890+-|&<>"

sys.setrecursionlimit(10**6)

def gen_with_bits(n, k):
    A = 0
    bits = random.sample(range(n), k)
    for bit in bits:
        A |= 1 << bit
    return A


# make sure to output pts without any trailing decimal zeroes.
# It should be 0, not 0.0! (perl specifics...)
def finish(pts, msg):
    print(pts)
    print(msg, file=sys.stderr)
    exit(0)


# The recursive definition of <izraz> is checked during evaluation
def check_command_format(n, command):
    if len(command) > MAX_COMMAND_LEN: return False
    if not command.startswith("A="): return False
    if command.count("A") > MAX_VAR_COUNT: return False
    if command.count("AA") != 0: return False
    for c in command:
        if c not in ALLOWED_CHARS:
            return False
    return True


def my_popcount(x):
    return bin(x).count('1')


def evaluate_basic_expression(lhs, rhs, oper, n):
    assert 0 <= lhs < 2**n, "There is a bug in ms evaluation"
    assert 0 <= rhs < 2**n, "There is a bug in ms evaluation"

    if oper == "+": return (lhs + rhs) % (2**n)
    if oper == "-": return (lhs - rhs + (2**n)) % (2**n)
    if oper == "|": return lhs | rhs
    if oper == "&": return lhs & rhs
    if oper == "<<":
        if rhs >= n: return 0
        return (lhs << rhs) & ((1 << n) - 1)
    if oper == ">>":
        if rhs >= n: return 0
        return (lhs >> rhs)

    assert False, "There is a bug in ms evaluation"


def evaluate_ms_expression(lo, hi, n, expr, format_msg):
    if lo >= hi: finish(0, format_msg)
    if expr[lo] != '(':
        # catches wrongly formated numbers such as "+3"
        if expr[lo] not in "0123456789": finish(0, format_msg)
        ret = -1
        try:
            ret = int(expr[lo:hi])
        except:
            finish(0, format_msg)
        if ret < 0 or ret >= 2**n: finish(0, format_msg)
        return ret

    if expr[hi - 1] != ')': finish(0, format_msg)
    oper = ""
    par_cnt = 0
    oper_i = 0
    for i in range(lo + 1, hi - 1):
        if expr[i] == '(': par_cnt += 1
        if expr[i] == ')': par_cnt -= 1
        if par_cnt != 0: continue
        if expr[i] in "+-|&":
            oper_i = i
            oper = expr[i]
            break
        if expr[i] in "<>" and i + 1 < hi - 1 and expr[i + 1] == expr[i]:
            oper_i = i
            oper = expr[i:(i+2)]
            break

    if oper == "": finish(0, format_msg)

    lhs = evaluate_ms_expression(lo + 1, oper_i, n, expr, format_msg)
    rhs = evaluate_ms_expression(oper_i + len(oper), hi - 1, n, expr, format_msg)

    return evaluate_basic_expression(lhs, rhs, oper, n)


def evaluate_ms(n, A, source, format_msg):
    for line in source:
        expression = line[2:].replace("A", str(A))
        A = evaluate_ms_expression(0, len(expression), n, expression, format_msg)
    return A


def checker(fin, foff, fout):
    # Read official input (fin)
    fin_lines = fin.readlines()
    n, k = map(int, fin_lines[0].split())

    # Don't need to read official output (foff)

    # Read contestant's output (fout) and check
    fout_lines = fout.readlines()
    if len(fout_lines) < 1: finish(0, WRONG_OUTPUT_FORMAT)
    k_contestant = 0
    try:
        k_contestant = int(fout_lines[0])
    except:
        finish(0, WRONG_OUTPUT_FORMAT)
    if len(fout_lines) != k_contestant + 1: finish(0, WRONG_K)
    if k_contestant < 0 or k_contestant > k: finish(0, WRONG_K)

    ms_contestant = []
    for i in range(k_contestant):
        command = fout_lines[i + 1].strip()
        if not check_command_format(n, command): finish(0, WRONG_COMMAND_FORMAT)
        ms_contestant.append(command)

    # Check everything for sufficiently small n
    if n <= 9:
        for i in range(2**n):
            contestant_popcount = evaluate_ms(n, i, ms_contestant, WRONG_COMMAND_FORMAT)
            correct_popcount = my_popcount(i)
            if contestant_popcount != correct_popcount: finish(0, WRONG)
        finish(1, CORRECT)

    # Check 150 random numbers
    for i in range(150):
        A = random.randint(0, 2**n)
        contestant_popcount = evaluate_ms(n, A, ms_contestant, WRONG_COMMAND_FORMAT)
        correct_popcount = my_popcount(A)
        if contestant_popcount != correct_popcount: finish(0, WRONG)

    # Check 100 numbers with small numbers of 1s
    for i in range(100):
        k = min(n, random.randint(0, 100))
        A = gen_with_bits(n, k)
        contestant_popcount = evaluate_ms(n, A, ms_contestant, WRONG_COMMAND_FORMAT)
        correct_popcount = my_popcount(A)
        if contestant_popcount != correct_popcount: finish(0, WRONG)

    for i in range(100):
        k = random.randint(max(0, n - 100), n)
        A = gen_with_bits(n, k)
        contestant_popcount = evaluate_ms(n, A, ms_contestant, WRONG_COMMAND_FORMAT)
        correct_popcount = my_popcount(A)
        if contestant_popcount != correct_popcount: finish(0, WRONG)

    finish(1, CORRECT)


def main():
    assert len(sys.argv) == 4, "Wrong amount of command line arguments"

    fin = open(sys.argv[1], "r");
    foff = open(sys.argv[2], "r");
    fout = open(sys.argv[3], "r");

    checker(fin, foff, fout)
    assert False, "Program didn't end in checker function"


if __name__ == '__main__':
    random.seed(545261)
    main()
