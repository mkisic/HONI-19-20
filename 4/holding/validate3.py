#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    n, l, r, k = map(int, lines[0].split())
    assert 1 <= l <= r <= n <= 100, "n, l, r odnos je kriv"
    assert 0 <= k <= 10000, "k izvan intervala"
    nl.append("{} {} {} {}{}".format(n, l, r, k, E));

    a = list(map(int, lines[1].split()))
    assert len(a) == n, "duljina niza je kriva"
    for ai in a:
        assert 0 <= ai <= 10**6, "ai izvan intervala"
    nl.append("{}{}".format(' '.join(list(map(str, a))), E))

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n': n, 'r': r}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'subtask 1': 1, 'subtask 2': 1, 'subtask 3': 1, 'subtask 4': 1}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if data['n'] <= 13 and data['r'] == data['n']: return 'subtask 1'
    if data['n'] <= 50 and data['r'] == data['n']: return 'subtask 2'
    if data['n'] <= 50: return 'subtask 3'
    return 'subtask 4'


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
