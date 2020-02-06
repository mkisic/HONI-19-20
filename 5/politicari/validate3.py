#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    n, k = map(int, lines[0].strip().split())
    assert 2 <= n <= 500, "n kriv"
    assert 1 <= k <= 10**18, "k kriv"
    nl.append("{} {}{}".format(n, k, E))

    for i in range(1, 1 + n):
      p = list(map(int, lines[i].strip().split()))
      assert len(p) == n, "nema n brojeva"
      assert p[i - 1] == 0, "i,i nije 0"
      for j in range(n):
        if j != i - 1: assert p[j] != i and p[j] >= 1 and p[j] <= n, "krivo optuzeni"

      lajna = ""
      for x in p:
        lajna += str(x) + " "

      lajna = lajna[:-1]
      nl.append("{}{}".format(lajna, E))

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {"n" : n, "k" : k}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'malik': 7, "normalni" : 7}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if data['k'] <= 10**5: return "malik"
    return 'normalni'


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
