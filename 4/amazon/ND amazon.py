N = int(input()) # nosivost drona
M = int(input()) # broj paketa = 3

tezina = 0
polijetanja = 1
for i in range(M):
    Ki = int(input())

    if tezina + Ki > N:
        tezina = Ki
        polijetanja += 1
    else:
        tezina += Ki

print(polijetanja)
