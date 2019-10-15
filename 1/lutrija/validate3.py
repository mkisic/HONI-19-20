#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string

from math import sqrt
from itertools import count, islice

MAXN = 10**14

def prime(x):
    return x > 1 and all(x % i for i in islice(count(2), int(sqrt(x)-1)))


def exists3(a, b):
    if prime(abs(a - b)): return True
    for i in range(2, 1001):
        if i == a or i == b: continue
        if not prime(i): continue
        if prime(abs(a - i)) and prime(abs(b - i)): return True
    return False


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    a, b = map(int, lines[0].split())

    assert 2 <= a <= MAXN, "a je izvan intervala"
    assert 2 <= b <= MAXN, "b je izvan intervala"

    assert a != b, "a je jednak b"

    assert prime(a), "a nije prost"
    assert prime(b), "b nije prost"

    nl.append("{} {}{}".format(a, b, E));

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'a': a, 'b': b}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'parcijala1': 2, "parcijala2": 2, "parcijala3": 4}


def what_cluster(data):
    a = data['a']
    b = data['b']
    if 2 <= a <= 1000 and 2 <= b <= 1000:
        if exists3(a, b): return 'parcijala1'
        return 'parcijala2'
    return 'parcijala3'


################### Zadatak-specifican kod iznad ove linije #########################

import sys
import glob
import hashlib


def group_in_batches(files):
    # mnozenje.in.1a, mnozenje.in.1b sprema u isti batch

    files.sort()
    B = []
    for f in files:
        if f[-1].islower() and len(B) > 0 and f[:-1] == B[-1][-1][:-1]:
            B[-1].append(f)
        else:
            B.append([f])
    return B


if __name__ == "__main__":
    f = []
    for pattern in sys.argv[1:]:
        for filename in glob.glob(pattern):
            f.append(filename)

    bc = []
    for batch in group_in_batches(f):
        if 'dummy' not in batch[0]:
            bc.append([])
        for filename in batch:
            print("{}: ".format(filename), end="")
            try:
                lines = open(filename).readlines()
                summary = check(lines)
                c = what_cluster(summary)
                if 'dummy' not in batch[0]:
                    bc[-1].append(c)
            except Exception as e:
                print("Greska!", e)
                raise
            else:
                print("Sve ok! (cluster {}, summary = {})".format(c, summary))

    clusters = {}
    for b in bc:
        for c in b:
            assert c == b[0], "Ima razlicitih cluster-a unutar batcha"
        if not b[0] in clusters:
            clusters[b[0]] = 0
        clusters[b[0]] += 1

    assert clusters == expected_clusters, "Kriva raspodjela clustera ({} vs {})".format(clusters, expected_clusters)

    # Buda test - provjeri duplikate
    hashes = set(hashlib.sha1(open(x, 'rb').read()).hexdigest() for x in f)
    assert len(hashes) == len(f), "Ima duplikata!"
