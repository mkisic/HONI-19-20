#!/usr/bin/python
"""Upotreba ./validate.py test/*.in*"""

import sys
import glob
import hashlib
import string

def ccw(p1, p2, p3):
    c = p1[0] * (p2[1] - p3[1]) + p2[0] * (p3[1] - p1[1]) + p3[0] * (p1[1] - p2[1])
    if c > 0: return 1
    if c < 0: return -1
    return 0

def poly_ok(n, p):
    for i in range(n):
        if ccw(p[i], p[(i+1)%n], p[(i+2)%n]) <= 0:
            return False
    return True

def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    t = int(lines[0])
    assert 0 <= t <= 1, "t nije dobar"
    nl.append("{}{}".format(t, E))

    n = int(lines[1])
    assert 3 <= n <= 10**5, "n nije dobar"
    nl.append("{}{}".format(n, E))

    p = []
    for i in range(n):
        x, y = map(int, lines[i + 2].split())
        nl.append('{} {}{}'.format(x, y, E))
        assert -10**9 <= x and x <= 10**9, "krive koordinate vrhova poligona"
        assert -10**9 <= y and y <= 10**9, "krive koordinate vrhova poligona"
        p.append((x, y))

    q = int(lines[n+2])
    assert 1 <= q <= 10**5
    nl.append("{}{}".format(q, E))

    for i in range(0, q):
        a, b = map(int, lines[n+3+i].split())
        assert -2*(10**18) <= a <= 2*(10**18), "a krivi"
        assert -2*(10**18) <= b <= 2*(10**18), "a krivi"
        nl.append("{} {}{}".format(a, b, E))

    assert poly_ok(n, p), 'poly not ok'

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n': n, 'q': q, 't': t}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'c1': 1, 'c2': 1, 'c3': 1}


def what_cluster(summary):
    n = summary['n']
    q = summary['q']
    t = summary['t']
    if 1 <= n <= 2000 and 1 <= q <= 2000 and t == 0:
        return 'c1'
    if 1 <= n <= 10**5 and 1 <= q <= 10**5 and t == 0:
        return 'c2'
    if 1 <= n <= 10**5 and 1 <= q <= 10**5 and t == 1:
        return 'c3'
    assert False, "nepostojeci cluster"


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
            # assert c == b[0], "Ima razlicitih cluster-a unutar batcha"
	    pass
        if not b[0] in clusters:
            clusters[b[0]] = 0
        clusters[b[0]] += 1

    assert clusters == expected_clusters, "Kriva raspodjela clustera ({} vs {})".format(clusters, expected_clusters)

    # Buda test - provjeri duplikate
    hashes = set(hashlib.sha1(open(x, 'rb').read()).hexdigest() for x in f)
    assert len(hashes) == len(f), "Ima duplikata!"
