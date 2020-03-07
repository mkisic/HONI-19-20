#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string
import sys
sys.setrecursionlimit(1000010)

v = []
bio = []
brojac = 0

def dfs(cvor):
  bio[cvor] = 1
  for t in v[cvor]:
    if not bio[t]:
      dfs(t)
  return

  
def check(lines):
    global bio, v, brojac
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    n, m, q, k = map(int, lines[0].split())
    assert 1 <= n <= 100000, "n kriv"
    assert 1 <= m <= 200000, "m kriv"
    assert 1 <= q <= n, "q kriv"
    assert 1 <= k <= 100000, "k kriv"
    nl.append("{} {} {} {}{}".format(n, m, q, k, E));
    
    niz = list(map(int, lines[1].split()));
    assert len(niz) == q, "krivi broj brojeva u nizu"

    linija = ""
    for x in niz:
      assert 1 <= x <= n, "krivi x"
      linija += str(x) + " "

    linija = linija[:-1]
    nl.append("{}{}".format(linija, E))

    niz.sort()
    for i in range(1, q):
      assert niz[i - 1] < niz[i], "brojevi u nizu nisu razliciti"

    bio = []
    v = []
    brojac = 0
    for i in range(n + 1):
      L = []
      v.append(L)
      bio.append(0)

    for i in range(2, m+2):
        x, y = map(int, lines[i].split())
        assert 1 <= x <= n
        assert 1 <= y <= n
        assert x != y  
        v[x].append(y)
        v[y].append(x)
        nl.append("{} {}{}".format(x, y, E));

    for i in range(1, n + 1):
      if not bio[i]:
        brojac += 1
        dfs(i)
    assert brojac == 1, "graf ima vise komponenti"

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n': n, 'm': m, 'q': q, 'k': k}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'K_1_mali': 4, 'mali': 3, 'veliki': 7}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if data['k'] == 1 and 1 <= data['n'] <= 100 and 1 <= data['q'] <= 100 and 1 <= data['m'] <= 200: 
      return "K_1_mali"

    if 1 <= data['n'] <= 100 and 1 <= data['q'] <= 100 and 1 <= data['m'] <= 200: 
      return "mali" 
    
    return 'veliki'


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
