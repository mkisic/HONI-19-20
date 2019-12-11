#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string


def case(n, h, a0, a1):
    a = [a0, a1]
    b = []
    for i in range(n):
        if h[i] - a[-1] == a1 - a0:
            a.append(h[i])
        if len(a) == n / 2: break

    ptr = 0
    for i in range(n):
        if ptr < len(a) and h[i] == a[ptr]:
            ptr += 1
            continue
        b.append(h[i])

    if len(b) >= 2:
        for i in range(1, len(b)):
            if b[i] - b[i - 1] != b[1] - b[0]: return False

    for i in range(1, len(a)):
        assert a[i] - a[i - 1] == a[1] - a[0], "wtf"

    return len(a) == n or (len(a) == n / 2 and len(b) == n / 2)


def check_same_len(n, h):
    if n % 2 == 1: return False
    h.sort()
    return case(n, h, h[0], h[1]) or case(n, h, h[0], h[2]) or case(n, h, h[1], h[2])


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    n = int(lines[0])
    assert 1 <= n <= 10**5, "n izvan intervala"
    nl.append("{}{}".format(n, E))

    h = list(map(int, lines[1].split()))
    assert len(h) == n, "kriva duljina niza"
    for hi in h:
        assert 1 <= hi <= 10**9, "kriva visina drvca"
    nl.append('{}{}'.format(' '.join(map(str, h)), E))

    same_len = check_same_len(n, h)

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n': n, 'same len': same_len}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'Mali': 1, 'Srednji': 1, 'Same Len': 1, 'Veliki': 2}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if data['n'] <= 15: return 'Mali'
    if data['n'] <= 300: return 'Srednji'
    if data['same len']: return 'Same Len'
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

    # clusters = {}
    # for b in bc:
        # for c in b:
            # assert c == b[0], "Ima razlicitih cluster-a unutar batcha"
        # if not b[0] in clusters:
            # clusters[b[0]] = 0
        # clusters[b[0]] += 1

    # assert clusters == expected_clusters, "Kriva raspodjela clustera ({} vs {})".format(clusters, expected_clusters)

    # Buda test - provjeri duplikate
    hashes = set(hashlib.sha1(open(x, 'rb').read()).hexdigest() for x in f)
    assert len(hashes) == len(f), "Ima duplikata!"
