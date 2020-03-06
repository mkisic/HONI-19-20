#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string

months = ["SIJECANJ", "VELJACA", "OZUJAK", "TRAVANJ", "SVIBANJ", "LIPANJ", "SRPANJ",
          "KOLOVOZ", "RUJAN", "LISTOPAD", "STUDENI", "PROSINAC"]


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    n = int(lines[0].strip())
    assert 1 <= n <= 100, "n je izvan intervala"
    nl.append("{}{}".format(n, E));

    curr = 1;
    for i in range(n):
        x = int(lines[curr].strip())
        curr += 1
        s = lines[curr].strip()
        curr += 1
        assert 1 <= x <= 30, "D je izvan intervala"
        assert s in months, "M nije tocan mjesec"
        nl.append("{}{}".format(x, E))
        nl.append("{}{}".format(s, E))

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n': n}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'Mali': 5, 'Normalni': 5}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if data['n'] == 3: return 'Mali'
    return 'Normalni'


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