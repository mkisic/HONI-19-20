N = int(input())

ukupno = 0

for i in range(N):
    Ti, Zi = map(int, input().split())
    ukupno += Ti

print(N - (ukupno // Zi + (bool(ukupno % Zi))))
