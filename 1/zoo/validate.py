#!/usr/bin/python
"""Upotreba ./validate.py test/*.in*"""

import sys
import glob
import hashlib
import string


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    r, s = map(int, lines[0].split())
    assert 1 <= r <= 1000, "r kriv"
    assert 1 <= s <= 1000, "s kriv"
    nl.append("{} {}{}".format(r, s, E))
    
    for i in range(1, r + 1):
      red = str(lines[i].split())
      nl.append("{}{}".format(red, E)
      assert len(red) == s, 'Kriva duljina reda'
      zvjezdica = red.count('*')
      tigar = red.count('T')
      bik = red.count('B')
      assert zvjezdica + tigar + bik == s, 'krivi znakovi!'

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"

    return {'r': r, 's': s}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'mali': 9, 'veliki': 13}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if data['r'] <= 100 and data['s'] <= 100: return 'mali'
    return 'veliki'


################### Zadatak-specifican kod iznad ove linije #########################

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
            print filename, ":",
            try:
                lines = file(filename).readlines()
                summary = check(lines)
                c = what_cluster(summary)
                if 'dummy' not in batch[0]:
                    bc[-1].append(c)
            except Exception, e:
                print "Greska! ", e
                raise
            else:
                print "Sve ok! (cluster {} summary {})".format(c, summary)

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
