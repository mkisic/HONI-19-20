#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string

MAXN = 10**5

def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    n = int(lines[0].strip())
    assert 2 <= n <= MAXN, "n je izvan intervala"
    assert n % 2 == 0, "n je neparan"
    nl.append("{}{}".format(n, E));

    x_dict = {}
    y_dict = {}

    P = set()

    for i in range(n):
        x, y = map(int, lines[1 + i].split())
        if x not in x_dict: x_dict[x] = set()
        if y not in y_dict: y_dict[y] = set()
        x_dict[x].add(y)
        y_dict[y].add(x)
        assert (x, y) not in P, "dupla tocka"
        P.add((x, y))
        nl.append("{} {}{}".format(x, y, E))

    for k in x_dict:
        assert len(x_dict[k]) <= 2, "previse tocaka u istom retku"

    for k in y_dict:
        assert len(y_dict[k]) <= 2, "previse tocaka u istom stupcu"

    parno = True
    for (x, y) in P:
        for a in [x, y]:
            if a in x_dict and len(x_dict[a]) % 2 == 1: parno = False
            if a in y_dict and len(y_dict[a]) % 2 == 1: parno = False

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n': n, 'parno': parno}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'mali parno': 1, "mali": 1, "malo veci": 1, "srednji": 1, "veliki": 1}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if data['n'] <= 20 and data['parno']: return 'mali parno'
    if data['n'] <= 20: return 'mali'
    if data['n'] <= 40: return 'malo veci'
    if data['n'] <= 2000: return 'srednji'
    return 'veliki'


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
