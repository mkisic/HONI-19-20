#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string
import sys

sys.setrecursionlimit(10**6)

MAXN = 200000

def max_deg(G):
    return max([len(x) for x in G])


def dfs(node, dad, G, bio):
    ret = 1
    bio.add(node)
    for nxt in G[node]:
        if nxt == dad: continue
        assert nxt not in bio, "graf nije stablo"
        ret += dfs(nxt, node, G, bio)
    return ret


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    n = int(lines[0].strip())
    assert 2 <= n <= MAXN, "n je izvan intervala"
    nl.append("{}{}".format(n, E));

    S = set()

    G = []
    for i in range(n):
        G.append([])

    for i in range(n - 1):
        a, b, c1, c2 = map(int, lines[1 + i].split())
        assert a != b, "a je jednak b"
        assert 1 <= a <= n, "a je izvan intervala"
        assert 1 <= b <= n, "b je izvan intervala"
        assert 1 <= c1 <= c2 <= 100000, "c1 ili c2 su izvan intervala"
        nl.append("{} {} {} {}{}".format(a, b, c1, c2, E))
        S.add((a, b))
        S.add((b, a))
        a -= 1
        b -= 1
        G[a].append(b)
        G[b].append(a)

    assert len(S) == 2 * (n - 1), "ponavljaju se edgevi"
    assert dfs(0, -1, G, set()) == n, "stablo nije jedna komponenata"

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n': n, 'max_deg': max_deg(G)}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'Mali': 1, 'Lanac': 1, 'Normalni': 1}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if data['n'] <= 2000: return 'Mali'
    if data['max_deg'] <= 2: return 'Lanac'
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
        # for c in b:
            # assert c == b[0], "Ima razlicitih cluster-a unutar batcha"
        if not b[0] in clusters:
            clusters[b[0]] = 0
        clusters[b[0]] += 1

    assert clusters == expected_clusters, "Kriva raspodjela clustera ({} vs {})".format(clusters, expected_clusters)

    # Buda test - provjeri duplikate
    hashes = set(hashlib.sha1(open(x, 'rb').read()).hexdigest() for x in f)
    assert len(hashes) == len(f), "Ima duplikata!"
