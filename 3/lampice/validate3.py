#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string
import sys


sys.setrecursionlimit(10**6)


def dfs(node, v, bio):
    # print(len(bio))
    ret = 1
    bio.add(node)
    for nxt in v[node]:
        if nxt in bio: continue
        ret += dfs(nxt, v, bio)
    return ret



def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    n = int(lines[0])
    assert 1 <= n <= 50000, "n kriv"
    nl.append("{}{}".format(n, E))

    s = lines[1].strip()
    assert len(s) == n, "duljina stringa nije n"
    nl.append("{}{}".format(s, E))

    v = []
    for i in range(n):
        v.append([])

    for i in range(n - 1):
        a, b = map(int, lines[i + 2].split())
        assert 1 <= a <= n, "a kriv"
        assert 1 <= b <= n, "b kriv"
        assert a != b, "a jednako b"
        nl.append("{} {}{}".format(a, b, E))
        a -= 1
        b -= 1
        v[a].append(b)
        v[b].append(a)

    assert dfs(0, v, set()) == n, "nije stablo"
    leaves = 0
    for i in range(n):
        if len(v[i]) == 1: leaves += 1

    chain_v = []
    for i in range(n): chain_v.append([])
    for i in range(1, n):
        chain_v[i - 1].append(i)
        chain_v[i].append(i - 1)

    for i in range(n):
        chain_v[i].sort()
        v[i].sort()

    chain = v == chain_v

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n' : n, 'chain' : chain, 'leaves': leaves}

# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'Mali': 1, 'Lanac': 1, 'Veliki': 1}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if data['n'] <= 3000: return 'Mali'
    if data['chain']: return 'Lanac'
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
        for c in b:
            assert c == b[0], "Ima razlicitih cluster-a unutar batcha"
        if not b[0] in clusters:
            clusters[b[0]] = 0
        clusters[b[0]] += 1

    assert clusters == expected_clusters, "Kriva raspodjela clustera ({} vs {})".format(clusters, expected_clusters)

    # Buda test - provjeri duplikate
    hashes = set(hashlib.sha1(open(x, 'rb').read()).hexdigest() for x in f)
    assert len(hashes) == len(f), "Ima duplikata!"
