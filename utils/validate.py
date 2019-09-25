#!/usr/bin/python
"""Upotreba ./validate.py test/*.in*"""

import sys
import glob
import hashlib
import string


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    n = int(lines[0])
    assert 1 <= n <= 100, "n nije dobar"
    nl.append(str(n) + E)

    def check_name(name):
        assert 1 <= len(name) <= 10, "krivo ime"
        for c in name:
            if c not in string.lowercase:
                assert "krivi znak u nazivu"

    has_cd = False

    for line in lines[1:]:
        cmd, arg = line.split()

        if cmd == "mkdir":
            check_name(arg)
        elif cmd == "rmdir":
            check_name(arg)
        elif cmd == "cd":
            has_cd = True
            if arg == "..":
                pass
            else:
                check_name(arg)
        else:
            assert False, "kriva naredba: {}".format(cmd)

        nl.append("{} {}".format(cmd, arg) + E)

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return has_cd


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'NemaCd': 3, 'Normalni': 7}


def what_cluster(has_cd):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    return 'Normalni' if has_cd else 'NemaCd'


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
            assert c == b[0], "Ima razlicitih cluster-a unutar batcha"
        if not b[0] in clusters:
            clusters[b[0]] = 0
        clusters[b[0]] += 1

    assert clusters == expected_clusters, "Kriva raspodjela clustera ({} vs {})".format(clusters, expected_clusters)

    # Buda test - provjeri duplikate
    hashes = set(hashlib.sha1(open(x, 'rb').read()).hexdigest() for x in f)
    assert len(hashes) == len(f), "Ima duplikata!"
