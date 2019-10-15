#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string

v = []
bio = []

def dfs(cvor, veza):
  if bio[cvor]: return 0
  bio[cvor] = 1
  
  ret = 1
  for t in v[cvor]:
    ncvor = t[0]
    nveza = t[1]
    if veza == nveza: continue
    ret &= dfs(ncvor, nveza)
  
  return ret


def stablo():
  ret = 1
  for i in range(1, 501):
    if not bio[i]: 
      ret &= dfs(i, -1)

  return ret


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    global bio, v
    v = []
    bio = []
    for i in range(501):
      L = []
      v.append(L)
      bio.append(0)

    n, m = map(int, lines[0].split())
    assert 1 <= n <= 500, "n kriv"
    assert 0 <= m < n, "m kriv"
    nl.append("{} {}{}".format(n, m, E));

    d = list(map(int, lines[1].split()))
    assert len(d) == n, "nema N brojeva u 2. liniji"
    nl.append(" ".join(map(str, d)) + E)

    for x in d:
      assert 1 <= x <= 10**9, "krivi Di"

    for i in range(2, 2 + m):
      x, y = map(int, lines[i].split())
      assert x != y, "x == y"
      assert 1 <= x <= n, "x krivi"
      assert 1 <= y <= n, "y krivi"
      v[x].append((y, i))
      v[y].append((x, i))
      nl.append("{} {}{}".format(x, y, E))

    q = int(lines[2 + m].strip())
    assert 1 <= q <= 200000, "q krivi"
    nl.append("{}{}".format(q, E))

    maks = 0
    for i in range(2 + m + 1, 2 + m + 1 + q):
      si = int(lines[i].strip())
      assert 1 <= si <= 10**9
      nl.append("{}{}".format(si, E))
      maks = max(maks, si)

    assert stablo(), "nije suma stabala"

    deg = 0
    for i in range(501): deg = max(deg, len(v[i]))

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n': n, 'm': m, "deg" : deg, "maks" : maks}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'Normalni': 1, "Lanac" : 1}


def what_cluster(data):
    if data['n'] == data['m'] + 1 and data['deg'] <= 2 and data['maks'] <= 1000: return 'Lanac'
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
        for c in b:
            assert c == b[0], "Ima razlicitih cluster-a unutar batcha"
        if not b[0] in clusters:
            clusters[b[0]] = 0
        clusters[b[0]] += 1

    assert clusters == expected_clusters, "Kriva raspodjela clustera ({} vs {})".format(clusters, expected_clusters)

    # Buda test - provjeri duplikate
    hashes = set(hashlib.sha1(open(x, 'rb').read()).hexdigest() for x in f)
    assert len(hashes) == len(f), "Ima duplikata!"
