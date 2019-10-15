#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    n = int(lines[0])
    assert 4 <= n <= 2*(10**5), "n izvan intervala"
    nl.append("{}{}".format(n, E));

    c = lines[1][:-1]
    assert len(c) == n, "n ne odgovara broju obojenih stranica"
    for i in range(n):
        assert c[i] >= '1' and c[i] <= '3'
    nl.append("{}{}".format(c, E))

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n': n}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'Mali': 1, 'Srednji': 1, 'Veliki': 1}


def what_cluster(data):
    if data['n'] <= 11: return 'Mali'
    if data['n'] <= 1000: return 'Srednji'
    return 'Veliki'


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
        cl = 'Mali'
        for c in b:
            if c == 'Srednji' and cl == 'Mali': cl = c
            if c == 'Veliki': cl = c
        if not cl in clusters:
            clusters[cl] = 0
        clusters[cl] += 1

    assert clusters == expected_clusters, "Kriva raspodjela clustera ({} vs {})".format(clusters, expected_clusters)

    # Buda test - provjeri duplikate
    hashes = set(hashlib.sha1(open(x, 'rb').read()).hexdigest() for x in f)
    assert len(hashes) == len(f), "Ima duplikata!"
