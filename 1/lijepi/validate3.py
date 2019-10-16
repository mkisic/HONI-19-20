#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string

MAX = 10**9

def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    n = int(lines[0].strip())
    assert 1 <= n <= 10, "n kriv"
    nl.append("{}{}".format(n, E));
    dvo = 1
    for i in range(1, n + 1):
      a, b = map(int, lines[i].split())
      assert 1 <= a <= MAX, "a kriv"
      assert 1 <= b <= MAX, "b kriv"
      nl.append("{} {}{}".format(a, b, E));
      if len(str(a)) != 2 or len(str(b)) != 2: dvo = 0

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n': n, 'dvo': dvo}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'prvi': 9, 'drugi' : 2, 'sve' : 4}


def what_cluster(data):
    if data['n'] == 1 and data['dvo'] == 1: return 'prvi'
    if data['dvo']: return 'drugi'
    return 'sve'


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
