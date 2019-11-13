#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string


def parse(s, smije):
  assert len(s), "vjv previse razmaka izmedju rijeci"
  verdict = s[0]
  if smije:
    assert verdict in "-+?", "verdict kriv"
  else:
    assert verdict in "-+", "verdict kriv poslije"

  if len(s) == 1:
    assert verdict == "-", "len 1, a verdict nije -"
    return (verdict, 0, 0)
  
  try:
    x = int(s[1])
    assert 1 <= x <= 9, "kriva zanamenka"
  except:
    assert 0, "poslije {} nije broj".format(verdict)

  if len(s) == 2:
    assert verdict == "-", "len 2, a verdict nije -"
    return (verdict, 0, 0)
  
  if smije:
    assert verdict != "-", "len >2, a verdict je -"

  assert len(s) == 11, "na + i ? (i - u zadnjem) len mora biti 11"
  assert s[2] == "/", "s[2] nije /"

  vrijeme = s[3:]
  assert vrijeme[2] == ":" and vrijeme[5] == ":", "krive dvotocke"

  try:
    H = int(vrijeme[0:2])
    M = int(vrijeme[3:5])
    S = int(vrijeme[6:8])

    maks = 5 * 60 * 60
    assert H * 60 * 60 + M * 60 + S < maks, "vrijeme >= 5h"
    assert 0 <= M < 60, "minute krive"
    assert 0 <= S < 60, "sekunde krive"
    assert vrijeme[0] == "0", "vodeca 0 kod h krivo"
    if M < 10: assert vrijeme[3] == "0", "nema vodece 0 kod m"
    if S < 10: assert vrijeme[6] == "0", "nema vodece 0 kod s"
    return (verdict, H * 60 * 60 + M * 60 + S, int(s[1]))
  except:
    assert 0, "vrijeme je krivo"

  assert 0, "nes sam ja zeznul u validatoru"


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    n, m = map(int, lines[0].strip().split())
    assert 1 <= n <= 1000, "n kriv"
    assert 1 <= m <= 15, "m kriv"
    nl.append("{} {}{}".format(n, m, E))

    imena = set()
    ja = []
    cnt = 0
    for i in range(n):
      ret = lines[i + 1].strip().split()
      nl.append("{}{}".format(" ".join(ret), E))
      assert len(ret) == m + 1, "len != m + 1 rijeci u redu"
      ime = ret[0]
      assert 1 <= len(ime) <= 20, "ime krive duzine"
      for C in ime:
        c = ord(C)
        if (c >= ord('a') and c <= ord('z')) or (c >= ord('A') and c <= ord('Z')): continue
        assert 0, "slovo imena nije slovo"
      
      imena.add(ime)
      for j in range(1, len(ret)):
        t = parse(ret[j], 1)
        if ime == "NijeZivotJedanACM":
          ja.append(t)
      
      for c in lines[i + 1].strip():
        cnt += (c == "?")

    assert len(imena) == n, "imena nisu razlicita"

    red = lines[n + 1].strip().split()
    nl.append("{}{}".format(" ".join(red), E))
    assert len(red) == m + 1, "len != m + 1 rijeci u zadnjem redu"
    ime = red[0]
    assert ime == "NijeZivotJedanACM", "zadnje ime krivo"
    tmp = []
    for i in range(1, len(red)):
      tmp.append(parse(red[i], 0))

    for i in range(len(tmp)):
      if ja[i][0] != '?':
        assert ja[i] == tmp[i], "podaci nisu konzistentni"
        continue
      if tmp[i][0] == '-': continue
      assert ja[i][1] <= tmp[i][1] and ja[i][2] <= tmp[i][2], "podaci nisu konzistentni"


    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {"u" : cnt}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'bez_upitnika': 2, "normalni" : 3}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if data["u"]: return "normalni"
    return "bez_upitnika"


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
