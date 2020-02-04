#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import copy
import string

dr = [-1, -1, 0, 1, 1, 1, 0, -1]
ds = [0, 1, 1, 1, 0, -1, -1, -1]

def inside(r, s, R, S):
    return r >= 0 and r < R and s >= 0 and s < S


def check_singles(r, s, grid):
    for i in range(r):
        for j in range(s):
            if grid[i][j] == '.': continue
            for k in range(8):
                ii = i + dr[k]
                jj = j + ds[k]
                if inside(ii, jj, r, s) and grid[ii][jj] == '*':
                    return False
    return True


def check_intersections(r, s, grid):
    curr = 2
    for i in range(r):
        for j in range(s):
            if grid[i][j] != 1: continue
            ii = i
            jj = j
            while ii < r and grid[ii][j] == 1:
                ii += 1
            while jj < s and grid[i][jj] == 1:
                jj += 1
            for k in range(i, ii):
                for l in range(j, jj):
                    if grid[k][l] != 1: return False;
                    grid[k][l] = curr
            curr += 1

    for i in range(r):
        for j in range(s):
            if grid[i][j] == 0: continue;
            for k in range(8):
                ii = i + dr[k]
                jj = j + ds[k]
                if inside(ii, jj, r, s) and grid[ii][jj] != 0 and grid[ii][jj] != grid[i][j]:
                    return False

    return True

def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    n, m = map(int, lines[0].split())
    assert 1 <= n <= 100, "n kriv"
    assert 1 <= m <= 100, "m kriv"
    nl.append("{} {}{}".format(n, m, E));

    grid = []

    for i in range(1, n+1):
        row = lines[i].strip()
        grid.append(row)
        assert len(row) == m, "cudna duljina reda"
        assert all([(c in ".*") for c in row]), "cudni znakovi u retku"
        nl.append("{}{}".format(row, E))

    singles = check_singles(n, m, grid)

    num_grid = []
    for row in grid:
        num_row = []
        for ch in row:
            if ch == '*':
                num_row.append(1)
            else:
                num_row.append(0)
        num_grid.append(num_row)

    assert check_intersections(n, m, num_grid), "pravokutnici se diraju ili sijeku"

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n': n, 'm': m, 'singles': singles}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'singles': 2, 'n je 1': 3, 'normalni': 5}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if data['singles']: return 'singles'
    if data['n'] == 1: return 'n je 1'
    return 'normalni'


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
