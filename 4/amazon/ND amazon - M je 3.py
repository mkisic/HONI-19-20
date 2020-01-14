N = int(input()) # nosivost drona
M = int(input()) # broj paketa = 3

A = int(input()) # prvi paket
B = int(input()) # drugi paket
C = int(input()) # treći paket

if A + B + C <= N:
    print(1)
elif A + B <= N or B + C <= N:
    print(2)
else:
    print(3)
