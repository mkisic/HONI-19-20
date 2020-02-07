import matplotlib.pyplot as plt
import sys

assert(len(sys.argv) == 3)

with open(sys.argv[1], 'r') as f:
    n = int(f.readline())
    P = [list(map(int, f.readline().split())) for i in range(n)]

for i in [0, 1]:
    Q = sorted(P, key=lambda x: x[i])
    for j in range(len(Q) - 1):
        x, y = Q[j], Q[j + 1]
        if x[i] == y[i]:
            plt.plot(*zip(x, y), color='k', linewidth=0.2)

with open(sys.argv[2], 'r') as f:
    if f.readline() == 'DA\n':
        for _ in range(n // 2):
            i, j = map(int, f.readline().split())
            plt.plot(*zip(P[i - 1], P[j - 1]), color='k')


plt.scatter(*zip(*P), color='r')

plt.show()
