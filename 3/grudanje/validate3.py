#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string


def check_permutation(p):
    p.sort()
    for i in range(len(p)):
        if i + 1 != p[i]: return False
    return True


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    s = lines[0].strip()
    n = len(s)
    for c in s:
        assert c >= 'a' and c <= 'z', "rijec se ne sastoji od malih slova"
    assert 1 <= n <= 10**5, "n izvan intervala"
    nl.append("{}{}".format(s, E))

    q = int(lines[1])
    assert 1 <= q <= 10**5, "q izvan intervala"
    nl.append("{}{}".format(q, E))

    for i in range(q):
        a, b = map(int, lines[2 + i].split())
        assert 1 <= a <= b <= n, "a i b izvan intervala"
        nl.append("{} {}{}".format(a, b, E))

    p = list(map(int, lines[2 + q].split()))
    nl.append('{}{}'.format(' '.join(map(str, p)), E))
    assert check_permutation(p), "p nije permutacija"

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n': n, 'q': q, 's': s}

# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'Mali': 2, 'Srednji': 3, 'Samo a': 2, 'Veliki': 3}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if data['n'] <= 500 and data['q'] <= 500: return 'Mali'
    if data['n'] <= 3000 and data['q'] <= 3000: return 'Srednji'
    if all(c == 'a' for c in data['s']): return 'Samo a'
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
                summary['s'] = len(summary['s'])
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
