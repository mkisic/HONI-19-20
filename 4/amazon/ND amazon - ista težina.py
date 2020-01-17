N = int(input())
M = int(input())

for i in range(M):
    K = int(input())

print(M // (N // K) + bool(M % (N // K)))
