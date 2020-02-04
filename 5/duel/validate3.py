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

    A = list(map(int, lines[1].split()))
    B = list(map(int, lines[2].split()))

    assert 1 <= len(A) <= 1 + min(1000, n), "kriva duljina prvog niza"
    assert 1 <= len(B) <= 1 + min(1000, n), "kriva duljina drugog niza"

    assert A[0] + 1 == len(A), "kriva duljina prvog niza"
    assert B[0] + 1 == len(B), "kriva duljina prvog niza"

    for i in range(1, len(A)):
        assert 1 <= A[i] <= n, "kriv indeks zadatka"

    for i in range(1, len(B)):
        assert 1 <= B[i] <= n, "kriv indeks zadatka"

    nl.append("{}{}".format(' '.join(list(map(str, A))), E))
    nl.append("{}{}".format(' '.join(list(map(str, B))), E))

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n': n, 'p': A[0], 'f': B[0]}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'Mali': 1, 'Srednji': 5, 'int veliki': 2, 'llint veliki': 2}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if data['n'] == 2 and data['p'] == data['f'] == 1: return 'Mali'
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
