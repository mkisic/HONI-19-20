#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string

print("Provjeri rucno .out fileove da validiras ogovore na 3. i 4. clusteru!")

def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    cluster = int(lines[0].strip())
    assert 1 <= cluster <= 5, "cluster kriv"
    nl.append("{}{}".format(cluster, E))
    n = int(lines[1].strip())
    
    ogr = [300, 2000, 200000, 200000, 200000]
    assert 4 <= n <= ogr[cluster - 1], "n kriv"
    nl.append("{}{}".format(n, E))

    boje = str(lines[2].strip())
    assert len(boje) == n, "nema n boja"

    cbp = "123"
    for c in boje:
      assert c in cbp, "boja nije domoljubna, jesam se ja za ovo borijo???"
    
    nl.append("{}{}".format(boje,E))

    for i in range(n - 3):
      x, y, b = map(int, lines[3 + i].strip().split())
      assert 1 <= x <= n, "x van ogr"
      assert 1 <= y <= n, "y van ogr"
      assert str(b) in cbp, "boja dije nije domoljubna, volis li ti rvacku uopce???"
      nl.append("{} {} {}{}".format(x, y, b, E))
      x -= 1
      y -= 1
      assert x != y, "x == y"
      assert x != ((y + 1) % n), "x i y susjedni"
      assert y != ((x + 1) % n), "x i y susjedni"

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'cluster' : str(cluster)}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'1' : 1, '2' : 1, '3' : 1, '4' : 1, '5' : 1}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    return data['cluster']


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

print("Provjeri rucno .out fileove da validiras ogovore na 3. i 4. clusteru!")
