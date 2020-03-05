#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string

MAX = 500

def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    n, m = map(int, lines[0].strip().split())
    assert 2 <= n <= MAX, "krivi n"
    assert 2 <= m <= MAX, "krivi m"
    nl.append("{} {}{}".format(n, m, E))

    nule = 0
    jedinice = 0
    for i in range(1, n + 1):
      l = lines[i].strip()
      assert len(l) == m, "nema m znakova"
      nl.append("{}{}".format(l, E))
      for c in l:
        assert c in "10", "znak je != od 1 i 0"
        if c == "0": nule = 1
        else: jedinice += 1
      
      assert l[0] == "1", "znak u prvom stupcu nije 1"
      if i == 1:
        for c in l:
          assert c == "1", "znak u prvom retku nije 1"

    assert nule == 1, "nema nula"

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {"n" : n, "m" : m, "jed" : jedinice}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {"prvi" : 1, "drugi" : 1, "treci" : 1}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if data['jed'] <= 18: return "prvi"
    if data['n'] <= 500 and data['m'] <= 10: return "drugi"
    return "treci"


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
    # hashes = set(hashlib.sha1(open(x, 'rb').read()).hexdigest() for x in f)
    # assert len(hashes) == len(f), "Ima duplikata!"
