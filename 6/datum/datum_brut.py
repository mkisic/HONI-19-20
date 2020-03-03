import time

dates = [];
mj= [31,29,31,30,31,30,31,31,30,31,30,31];

def palin(y):
	day = (y % 10) * 10 + (y % 100) / 10;
	month = y / 1000 + ((y / 100) % 10) * 10;
	return (month != 0 and month <= 12 and day <= mj[month - 1] and day != 0);

def ispis(y):
	ret = "";
	ret += str(y % 10)
	ret += str((y / 10) % 10)
	ret += "."
	ret += str((y / 100) % 10)
	ret += str(y / 1000)
	ret += ".";
	ret += str((y / 1000))
	ret += str((y / 100) % 10)
	ret += str((y / 10) % 10)
	ret += str(y % 10)
	return ret;

def bins(y):
	lo = 0
	hi = 365
	mi = -1
	while(lo < hi):
		mi = (hi + lo) // 2
		if(dates[mi] < y):
			lo = mi + 1
		else:
			hi = mi
	return dates[lo]

def nadi(y):
	lo = 0
	hi = 365
	mi = -1
	while(lo < hi):
		#print(mi, dates[mi])
		mi = lo + (hi - lo) // 2
		if(dates[mi] == y):
			return 1
		elif(dates[mi] < y):
			lo = mi + 1
		else:
			hi = mi
	return 0

def kasnije(a, b):
	mja = (ord(a[3])- nul) * 10 + ord(a[4]) - nul;
	mjb = (ord(b[3])- nul) * 10 + ord(b[4]) - nul;
	daa = (ord(a[0])- nul) * 10 + ord(a[1]) - nul;
	dab = (ord(b[0])- nul) * 10 + ord(b[1]) - nul;
	if(mja > mjb):
		return 1
	if(mja == mjb):
		if(daa > dab):
			return 1
		return 0
	return 0


start_time = time.time()

for i in range(10000):
	if(palin(i)):
		dates.append(i);

q = int(input())
nul = ord('0')

while(q):
	q = q - 1
	date = raw_input()
	year = (ord(date[6]) - nul) * 1000 + (ord(date[7]) - nul) * 100 + (ord(date[8]) - nul) * 10 + ord(date[9]) - nul
	for i in range(366):
		if(year == dates[i]):
			pal = ispis(year)
			if(kasnije(pal, date)):
				print(pal)
			else:
				print(ispis(dates[i + 1]))
			break
		elif(year < dates[i]):
			print(ispis(dates[i]))
			break
print("--- %s seconds ---" % (time.time() - start_time))
