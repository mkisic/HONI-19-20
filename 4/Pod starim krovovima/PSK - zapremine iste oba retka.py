N = int(input())

ukupno = 0
for i in range(N):
    Ti, Zi = map(int, input().split())
    ukupno += Ti

print(N - (ukupno // Zi + (bool(ukupno % Zi))))

print(ukupno)
for i in range(N):
    if ukupno - Zi > 0:
        print(Zi, end = ' ')
        ukupno -= Zi
    elif ukupno > 0:
        print(ukupno, end = ' ')
        ukupno = 0
    else:
        print(0, end = ' ')
