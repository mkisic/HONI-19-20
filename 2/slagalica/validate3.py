#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    n = int(lines[0].strip())
    assert 2 <= n <= 100000, "n kriv"
    nl.append("{}{}".format(n, E))

    imam = []
    for i in range(10):
      imam.append(0)

    kom = set()
    for i in range(n):
      x, a = map(int, lines[1 + i].strip().split())
      assert 1 <= x <= 8, "xi kriv"
      assert 1 <= a <= (10**9), "ai kriv"
      imam[x] += 1
      kom.add(a)
      nl.append("{} {}{}".format(x, a, E))

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n' : n, 'imam' : imam}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {"Prvi" : 1, "Drugi": 1, "Treci" : 2, "Cetvrti" : 4, "Peti" : 6}


def what_cluster(data):
    n = data['n']
    imam = data['imam']
    if n <= 4: return "Prvi"
    if n <= 10: return "Drugi"
    if imam[2] == 0 and imam[3] == 0: return "Treci"
    if imam[1] + imam[4] <= 1: return "Cetvrti"
    return "Peti"


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
