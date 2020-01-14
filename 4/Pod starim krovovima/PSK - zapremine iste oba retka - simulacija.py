N = int(input())

stol = []
ukupno = 0
for i in range(N):
    Ti, Zi = map(int, input().split())
    stol += [[Ti, Zi]]
    ukupno += Ti
#print(stol)

print(N - (ukupno // Zi + (bool(ukupno % Zi))))

while True:
    odakle = 100000000
    c_odakle = 0
    for i in range(N):
        if stol[i][0] < odakle and stol[i][0] != 0:
            odakle = stol[i][0]
            c_odakle = i

    gdje = 0
    c_gdje = 0
    for i in range(N):
        if stol[i][0] > gdje and stol[i][0] != stol[i][1] and i != c_odakle:
            gdje = stol[i][0]
            c_gdje = i

    #print(c_odakle, c_gdje)

    if odakle == 100000000 or gdje == 0:
        break
    
    t = stol[c_gdje][0]
    stol[c_gdje][0] = min(Zi, stol[c_gdje][0] + stol[c_odakle][0])
    stol[c_odakle][0] -= stol[c_gdje][0] - t

    #print(stol)
   
for i in range(N):
    print(stol[i][0], end = ' ')

