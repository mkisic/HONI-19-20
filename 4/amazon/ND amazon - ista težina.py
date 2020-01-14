N = int(input())
M = int(input())

for i in range(M):
    K = int(input())

print((M * K) // N + bool(M * K % N))
