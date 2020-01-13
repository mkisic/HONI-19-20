import random
import string

n = 100
print(n)
#print(''.join(random.choice(string.ascii_lowercase) for _ in range(n)))

s = ''
while len(s) < n:
    s += random.choice(string.ascii_lowercase[:5]) * random.randint(1, n // 4)

print(s[:n])
