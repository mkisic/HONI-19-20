#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string

MAXN = 10**18

def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    n = int(lines[0].strip())
    assert 1 <= n <= 10**18, "n kriv"
    nl.append("{}{}".format(n, E));

    A = []
    B = []

    A.append(int(lines[1].strip()))
    for i in range(A[0]):
        A.append(int(lines[2 + i].strip()))

    B.append(int(lines[2 + A[0]].strip()))
    for i in range(B[0]):
        B.append(int(lines[3 + A[0] + i].strip()))

    assert 1 <= len(A) <= 1 + min(1000, n), "kriva duljina prvog niza"
    assert 1 <= len(B) <= 1 + min(1000, n), "kriva duljina drugog niza"

    assert A[0] + 1 == len(A), "kriva duljina prvog niza"
    assert B[0] + 1 == len(B), "kriva duljina prvog niza"

    for i in range(1, len(A)):
        assert 1 <= A[i] <= n, "kriv indeks zadatka"

    for i in range(1, len(B)):
        assert 1 <= B[i] <= n, "kriv indeks zadatka"

    for x in A:
        nl.append("{}{}".format(x, E))

    for x in B:
        nl.append("{}{}".format(x, E))

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n': n, 'p': A[0], 'f': B[0]}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'Mali': 2, 'Srednji': 4, 'int veliki': 2, 'llint veliki': 2}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if data['n'] == 3 and data['p'] == data['f'] == 2: return 'Mali'
    if data['n'] <= 1000: return 'Srednji'
    if data['n'] <= 2*(10**9): return 'int veliki'
    return 'llint veliki'


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
