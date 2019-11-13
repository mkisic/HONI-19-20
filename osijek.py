N = int(input())
K = int(input())

if N % K == 0:
    print(N // K)
else:
    print(N // K + 1)
