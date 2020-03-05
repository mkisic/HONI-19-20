#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string


mjesec = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

def solve(d, m, g):
  while 1:
    d += 1
    X = mjesec[m - 1]
    if g % 4 == 0 and m == 2: X += 1
    if d > X:
      d = 1
      m += 1
      if m > 12:
        m = 1
        if g == 9999:
          assert 0, "nema rjesenja"
        g += 1

    D = ""
    if d < 10: D = "0" + str(d)
    else: D = str(d)
    M = ""
    if m < 10: M = "0" + str(m)
    else: M = str(m)
    G = ""
    if g < 10: G = "000" + str(g)
    if g >= 10 and g < 100: G = "00" + str(g)
    if g >= 100 and g < 1000: G = "0" + str(g)
    if g > 1000: G = str(g)

    s = D + M + G
    s1 = s[::-1]
    if s == s1: return (d, m, g)
  assert 0, "tu nije trebalo doci"
  return (-1,-1,-1)

def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    n = int(lines[0])
    assert 1 <= n <= 10000, "krivi n"
    nl.append("{}{}".format(n, E))

    isti_mjesec = 1
    ista_god = 1
    for i in range(1, n + 1):
      s = lines[i].strip()
      assert len(s) == 11, "kriva duljina"
      assert s[2] == s[5] == s[-1] == '.', "krive tocke"
      nl.append("{}{}".format(s, E))
      d = int(s[0:2])
      m = int(s[3:5])
      g = int(s[6:-1])
      M = mjesec[m - 1]
      if g % 4 == 0 and m == 2: M += 1
      assert 1 <= d <= M, "krivi dan"
      assert 1 <= m <= 12, "krivi mjesec"
      assert 0 <= g <= 9999, "kriva godina"

      ans = solve(d, m, g)
      if ans[1] != m: isti_mjesec = 0
      if ans[2] != g: ista_god = 0

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {"n" : n, "mje" : isti_mjesec, "god" : ista_god}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {"prvi" : 2, "drugi" : 2, "treci" : 4, "cet" : 2}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if data['n'] == 10 and data['mje'] == 1: return "prvi"
    if data['n'] == 10 and data['god'] == 1: return "drugi"
    if data['n'] == 10: return "treci"
    return "cet"


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
