#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string

MAX = 2**60

def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    q = int(lines[0].strip())
    assert 1 <= q <= 100, "n kriv"
    nl.append("{}{}".format(q, E));
    maksi = 0
    najveca_razlika = 0
    for i in range(1, q + 1):
      a, b = map(int, lines[i].split())
      assert 1 <= a <= MAX, "a kriv"
      assert 1 <= b <= MAX, "b kriv"
      assert a <= b, "a > b!"
      maksi = max(maksi, a)
      maksi = max(maksi, b)
      najveca_razlika = max(najveca_razlika, b - a)
      nl.append("{} {}{}".format(a, b, E));

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    
    tip = 3
    if maksi <= 9: tip = 1
    elif najveca_razlika <= 1000: tip = 2
    
    return {'q': q, 'tip': tip}

# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'prvi': 1, 'drugi' : 2, 'sve' : 2}


def what_cluster(data):
    if data['tip'] == 1: return 'prvi'
    if data['tip'] == 2: return 'drugi'
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
