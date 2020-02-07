import matplotlib.pyplot as plt

n = int(input())
P = [list(map(int, input().split())) for i in range(n)]

for x in P:
    for y in P:
        if x != y and (x[0] == y[0] or x[1] == y[1]):
            plt.plot(*zip(x, y), color='k')

plt.scatter(*zip(*P), color='r')

plt.show()
