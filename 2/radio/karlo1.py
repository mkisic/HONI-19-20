n,x = map(int, raw_input().split())

for i in range(n):
    a,b = map(int, raw_input().split())
    x = x - a + b
print(x)
