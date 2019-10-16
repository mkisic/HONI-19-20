N = int(input())

zbroj = 0

for i in range(N):
    X, Y = input().split()

    rjesenje = int(X) * 10**len(Y) + int(Y)
    #print(rjesenje)

    zbroj += rjesenje

print(zbroj)
    
